///
/// @file SmartPotEndpoint.hpp
///
/// @brief Class which represents the HTTP and MQTT endpoints for
/// the @b SmartPot class.
///
#include "SmartPotEndpoint.hpp"

// Our JSON Parser.
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <fstream>
#include <string>
#include <omp.h>
using namespace rapidjson;

namespace pot
{
    SmartPotEndpoint::SmartPotEndpoint(Address address)
    {   
        // Create a default SmartPot object.
        map<int, map<string, Sensor>> sensorsAux;
        map<string, Sensor> s;
        map<string, Sensor> s_2;
        map<string, Sensor> s_3;
        Sensor s1("soilHumidity", 2, 3, 6);
        Sensor s2("luminosity", 2,4,5);
        Sensor s3("temperature", 3,3,3);
        Sensor s4("soilType", "Red",3,3);
        Sensor s5("humidity", 3,3,3);
        Sensor s6("soilPh", 3,3,3);
        s["soilHumidity"] = s1;
        s["soilType"] = s4;
        s["soilPh"] = s6;
        s_2["temperature"] = s3;
        s_2["luminosity"] = s2;
        s_2["humidity"] = s5;
        Sensor sPh("phosphorus", 1, 2, 3);
        Sensor sN("nitrogen", 1, 2, 3);
        Sensor sP("potassium", 1, 2, 3);
        s_3["phosphorus"] = sPh;
        s_3["nitrogen"] = sN;
        s_3["potassium"] = sP;
        sensorsAux[3] = s;
        sensorsAux[2] = s_2;
        sensorsAux[1] = s_3;
        Plant p("Cactus", "Green", 1.3, "Desert", "Red");
        smartPot = new SmartPot(p, sensorsAux);

        // Create the HTTP Endpoint.
        httpEndpoint = std::make_shared<Http::Endpoint>(address);

        // Create the MQTT Subscriber.
        mosquitto_lib_init();
        //                            HostName   CleanSession SessionID
        mosquittoSub = mosquitto_new("SmartPot", true, NULL);
    }

    SmartPotEndpoint::~SmartPotEndpoint(void)
    {
        // Stop the HTTP server.
        httpEndpoint->shutdown();

        mosquitto_destroy(mosquittoSub);
        mosquitto_lib_cleanup();
    }

    ///
    /// @brief Server initialization.
    ///
    void SmartPotEndpoint::init(void)
    {
        // Get the optimal settings for our HTTP endpoint.
        auto settings = Http::Endpoint::options();
        httpEndpoint->init(settings);
        // Create the http routes we'll use.
        createHttpRoutes();

        // Setup MQTT function calls for connection and received messages.
        mosquitto_connect_callback_set(mosquittoSub, mosquittoOnConnect);
        mosquitto_message_callback_set(mosquittoSub, mosquittoOnMessage);
        //mosquitto_subscribe_callback_set(mosquittoSub, mosquittoOnSubscribe);
    }

    ///
    /// @brief Servers start.
    ///
    void SmartPotEndpoint::start(void)
    {
        // Start the parallel region for the HTTP and MQTT servers.
        #pragma omp parallel sections 
        {
            // The HTTP server.
            #pragma omp section
            {
                // cout << "HTTP " << omp_get_thread_num() << endl;
                httpEndpoint->setHandler(router.handler());
                httpEndpoint->serveThreaded();
            }

            // The MQTT server.
            #pragma omp section
            {
                // cout << "MQTT " << omp_get_thread_num() << endl;
                if (mosquitto_connect(mosquittoSub, "mqtt_server", 1883, 60))
                {
                    std::cout << "Could not connect to MQTT broker." << endl;
                }
                else
                {
                    mosquitto_loop_start(mosquittoSub);
                    //publish('test', smartPot.status())
                }
            }
        }
    }

    ///
    /// @brief Server stop.
    ///
    void SmartPotEndpoint::stop(void)
    {
        // Stop the HTTP server.
        httpEndpoint->shutdown();

        // Stop the MQTT server and disconnect from the broker.
        mosquitto_loop_stop(mosquittoSub, true);
        mosquitto_disconnect(mosquittoSub);
    }

    ///
    /// @brief Function which creates our http routes, called at
    /// server initialization.
    ///
    void SmartPotEndpoint::createHttpRoutes(void)
    {
        using namespace Rest;

        Routes::Get(router, "/settings/:settingName/",
                    Routes::bind(&SmartPotEndpoint::getSetting, this));
        
        Routes::Get(router, "/status",
                    Routes::bind(&SmartPotEndpoint::getStatus, this));

        Routes::Get(router, "/soilStatus",
                    Routes::bind(&SmartPotEndpoint::soilStatus, this));
                    
        Routes::Get(router, "/shovel",
                    Routes::bind(&SmartPotEndpoint::shovel, this));

        Routes::Get(router, "/irrigateSoil",
                    Routes::bind(&SmartPotEndpoint::irrigationSoil, this));

        Routes::Get(router, "/injectMinerals",
                    Routes::bind(&SmartPotEndpoint::injectMinerals, this));

        Routes::Get(router, "/activateSolarLamp",
                    Routes::bind(&SmartPotEndpoint::activateSolarLamp, this));


        Routes::Put(router, "/settings/:settingName/:settingValue",
                    Routes::bind(&SmartPotEndpoint::putSetting, this));

        Routes::Put(router, "/settings",
                    Routes::bind(&SmartPotEndpoint::putSettingUpdate, this));

        Routes::Put(router, "/plantInfo",
                    Routes::bind(&SmartPotEndpoint::putPlantType, this));
    }

    ///
    /// @brief GET request function which returns the value of the
    /// desired setting found in the :settingName parameter.
    ///
    /// @returns A response with the setting name and value if the setting exists
    /// or a "Setting was not found" message otherwise.
    ///
    void SmartPotEndpoint::getSetting(const Rest::Request &request,
                                      Http::ResponseWriter response)
    {
        // Lock the pot settings.
        // TODO: REVISE THIS.
        Guard guard(potLock);

        // Setup some headers for the response.
        using namespace Http;
        response.headers()
            .add<Header::Server>("pistache/0.2")
            .add<Header::ContentType>(MIME(Text, Plain));

        // Retrieve the setting name.
        string settingName = request.param(":settingName").as<string>();

        // Retrieve the setting value.
        string settingValue = "";
        // If it does NOT exist.
        if (smartPot->Get(settingName, settingValue))
        {
            response.send(Http::Code::Not_Found, settingName + " was not found");
        }
        else
        {
            response.send(Http::Code::Ok, settingValue);
        }
    }


    ///
    /// @brief GET request function which returns the value of the
    /// desired setting found in the :settingName parameter.
    ///
    /// @returns A response with the setting name and value if the setting exists
    /// or a "Setting was not found" message otherwise.
    ///
    void SmartPotEndpoint::putSetting(const Rest::Request &request,
                                      Http::ResponseWriter response)
    {
        // Lock the pot settings.
        // TODO: REVISE THIS.
        Guard guard(potLock);

        // Setup some headers for the response.
        using namespace Http;
        response.headers()
            .add<Header::Server>("pistache/0.2")
            .add<Header::ContentType>(MIME(Text, Plain));

        // Retrieve the setting name.
        string settingName = request.param(":settingName").as<string>();

        // Retrieve the setting value.
        string settingValue = request.param(":settingName").as<string>();

        // If it does NOT exist.
        if (smartPot->Get(settingName, settingValue))
        {
            response.send(Http::Code::Not_Found, settingName + " was not found");
        }
        else
        {
            response.send(Http::Code::Ok, settingValue);
        }
    }

    void SmartPotEndpoint::putSettingUpdate(const Rest::Request &request,
                                             Http::ResponseWriter response)
    {
        // Lock the pot settings.
        // TODO: REVISE THIS
        Guard guard(potLock);

        // Setup some headers for the response.
        using namespace Http;
        using namespace rapidjson;

        response.headers()
            .add<Header::Server>("pistache/0.2")
            .add<Header::ContentType>(MIME(Text, Plain));

        Document document;
        if (document.Parse(request.body().c_str()).HasParseError() || document.IsObject() == false)
        {
            response.send(Http::Code::Unprocessable_Entity,
                          "The schema is not a valid JSON. Impossible to parse.");
        }
        
        string message = "";

        double sensorTypeID = document["sensorType"].GetDouble();
        double sensorMin = document["min"].GetDouble();
        double sensorMax = document["max"].GetDouble();

        // Valoarea o updatam in MQTT.
        if (document["nutrientType"].IsNull())
        {
            Sensor aux = smartPot->GetSensor(sensorNameMap[sensorTypeID]);
            aux.SetMinValue(sensorMin);
            aux.SetMaxValue(sensorMax);

            smartPot->Set(sensorNameMap[sensorTypeID], aux);
            
            Sensor aux2 = smartPot->GetSensor(sensorNameMap[sensorTypeID]);
        }
        else
        {   
            Sensor aux = smartPot->GetSensor(document["nutrientType"].GetString());
            aux.SetMinValue(sensorMin);
            aux.SetMaxValue(sensorMax);

            smartPot->Set(document["nutrientType"].GetString(), aux);
            
            Sensor aux2 = smartPot->GetSensor(document["nutrientType"].GetString());
        }

        response.send(Http::Code::Ok, message);
    }

    void SmartPotEndpoint::putPlantType(const Rest::Request &request,
                                         Http::ResponseWriter response)
    {
        // Lock the pot settings.
        // TODO: REVISE THIS
        Guard guard(potLock);

        // Setup some headers for the response.
        using namespace Http;
        using namespace rapidjson;

        response.headers()
            .add<Header::Server>("pistache/0.2")
            .add<Header::ContentType>(MIME(Text, Plain));

        Document document;
        if (document.Parse(request.body().c_str()).HasParseError() || document.IsObject() == false)
        {
            response.send(Http::Code::Unprocessable_Entity,
                          "The schema is not a valid JSON. Impossible to parse.");
        }

        string message = "";

        if(!document["species"].IsString())
        {
            response.send(Http::Code::Unprocessable_Entity, "species field shall be a string.");
        }
        if(!document["color"].IsString())
        {
            response.send(Http::Code::Unprocessable_Entity, "color field shall be a string.");
        }
        if(!document["type"].IsString())
        {
            response.send(Http::Code::Unprocessable_Entity, "type field shall be a string.");
        }
        if(!document["height"].IsNumber())
        {
            response.send(Http::Code::Unprocessable_Entity, "height field shall be a double.");
        }
        if(!document["suitableSoilType"].IsString())
        {
            response.send(Http::Code::Unprocessable_Entity, "height field shall be a double.");
        }

        string species = document["species"].GetString();
        string color = document["color"].GetString();
        string type = document["type"].GetString();
        double height = document["height"].GetDouble();
        string suitableSoilType = document["suitableSoilType"].GetString();

        message += species + "  " + color + " " + " ";
        
        Plant p(species, color, height, type, suitableSoilType);
        smartPot->SetPlant(p);

        response.send(Http::Code::Ok, message);
    }

    void SmartPotEndpoint::getStatus(const Rest::Request &request,
                                     Http::ResponseWriter response)
    {
        string status = "";
        status += smartPot->DisplayPlantData()
                + string("\n")
                + smartPot->DisplayEnvironmentData();

        ofstream statusFile("../../status.txt");
        statusFile << status;
        
        response.send(Http::Code::Ok, status);
    }

    void SmartPotEndpoint::shovel(const Rest::Request &request,
                                      Http::ResponseWriter response)
    {
        response.send(Http::Code::Ok, smartPot->Shovel());
    }
    
    void SmartPotEndpoint::soilStatus(const Rest::Request &request,
                                      Http::ResponseWriter response)
    {
        response.send(Http::Code::Ok, smartPot->SoilStatus());
    }

    void SmartPotEndpoint::irrigationSoil(const Rest::Request &request,
                                          Http::ResponseWriter response)
    {
        response.send(Http::Code::Ok, smartPot->IrrigateSoil());
    }

    void SmartPotEndpoint::injectMinerals(const Rest::Request &request,
                                          Http::ResponseWriter response)
    {
        response.send(Http::Code::Ok, smartPot->NutrientsInjector());
    }

    void SmartPotEndpoint::activateSolarLamp(const Rest::Request &request,
                                             Http::ResponseWriter response)
    {
        response.send(Http::Code::Ok, smartPot->SolarLamp());
    }

    void SmartPotEndpoint::mosquittoOnMessage (struct mosquitto *mosq,
                                                void *obj,
                                                const struct mosquitto_message *msg)
    {   
        Document document;
        if (document.Parse((char *) msg->payload).HasParseError() || document.IsObject() == false)
        {
            return ;
        }

        string message = "";

        double sensorTypeID = document["sensorType"].GetDouble();

        string nutrientType = document["nutrientType"].IsNull() ? "" : document["nutrientType"].GetString();

        
        message += string("Senzorul ") + sensorNameMap[sensorTypeID] + " " +  nutrientType;
        
        if(document["value"].IsNumber())
        {
            Sensor aux = smartPot->GetSensor(document["nutrientType"].IsNull() 
                                            ? sensorNameMap[sensorTypeID] : nutrientType);
            aux.SetValue(document["value"].GetDouble());
            smartPot->Set(document["nutrientType"].IsNull() ? sensorNameMap[sensorTypeID] : nutrientType, aux);

            message += string(" ") + (document["nutrientType"].IsNull() ? "NULL" : nutrientType);
            message += string(" ") + to_string(document["value"].GetDouble());
        }
        else if(document["value"].IsString())
        {
            Sensor aux = smartPot->GetSensor(document["nutrientType"].IsNull() 
                                            ? sensorNameMap[sensorTypeID] : nutrientType);
            aux.SetValue(document["value"].GetString());
            smartPot->Set(document["nutrientType"].IsNull() ? sensorNameMap[sensorTypeID] : nutrientType, aux);

            message += string(" ") + (document["nutrientType"].IsNull() ? "NULL" : nutrientType);
            message += string(" ") + document["value"].GetString();
        }

        mosquitto_publish(mosq, NULL, "test/response", 100, message.c_str(), 0, false);
    }
    
    void SmartPotEndpoint::mosquittoOnConnect (struct mosquitto *mosq,
                                               void *obj,
                                               int rc)
    {
	    std::cout << string("MQTT Client ID: ") + to_string(* (int *) obj) << endl;

        if(rc)
        {
            std::cout << string("Error with result code: ") +  to_string(rc) << endl;
        }

        // Subscribe to our "endpoint" topics.
        mosquitto_subscribe(mosq, NULL, "test", 0);
    }   

    // void SmartPotEndpoint::mosquittoOnSubscribe (struct mosquitto *mosq,
    //                                              void *userdata, 
    //                                              int mid, int qos_count, 
    //                                              const int *granted_qos)
    // {
    //     cout<<"Subscribed to topic: " <<endl;
    // }

    map <int, string> SmartPotEndpoint::sensorNameMap = {
            {1, "ground"},
            {2, "temperature"},
            {3, "luminosity"},
            {4, "humidity"},
            {5, "fertiliser"},
            {6, "soilPh"},
            {7, "soilHumidity"},
            {8, "soilType"}
    };

    SmartPot*  SmartPotEndpoint::smartPot;
}