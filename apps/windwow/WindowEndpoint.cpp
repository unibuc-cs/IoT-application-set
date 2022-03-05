#include <algorithm>
#include <iostream>
#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
#include <signal.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <chrono>
#include <thread>
#include "Window.cpp"


using namespace std;
using json = nlohmann::json;
using namespace Pistache;



namespace Generic {

    void handleReady(const Rest::Request&, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "Ready");
    }

}


// Definition of the WindowEnpoint class
class WindowEndpoint {
public:
    explicit WindowEndpoint(Address addr)
        : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
    { }

    // Initialization of the server. Additional options can be provided here
    void init(size_t thr = 2) {
        auto opts = Http::Endpoint::options()
            .threads(static_cast<int>(thr))
            .maxRequestSize(64000);
        httpEndpoint->init(opts);
        // Server routes are loaded up
        setupRoutes();
    }

    // Server is started threaded.
    void start() {
        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serveThreaded();
    }

    // When signaled server shuts down
    void stop(){
        httpEndpoint->shutdown();
    }

private:
    void setupRoutes() {
        using namespace Rest;

        Routes::Get(router, "/ready", Routes::bind(&Generic::handleReady));
        Routes::Get(router, "/auth", Routes::bind(&WindowEndpoint::doAuth, this));
        Routes::Post(router, "/settings", Routes::bind(&WindowEndpoint::setSettingsJSON, this));
        Routes::Post(router, "/settings/:settingName/:value", Routes::bind(&WindowEndpoint::setSetting, this));
        Routes::Get(router, "/settings/:settingName/", Routes::bind(&WindowEndpoint::getSetting, this));
        Routes::Post(router, "/userSettings", Routes::bind(&WindowEndpoint::setUserSettingsJSON, this));
    }

    void setUserSettingsJSON(const Rest::Request& request, Http::ResponseWriter response){
        string userSettings[3] = {"username", "password", "phonenumber"};
        
        Guard guard(WindowLock);
        json jj = json::parse(request.body())["settings"];
        string res = "";

        for(json::iterator it = jj["buffer-tokens"].begin(); it!=jj["buffer-tokens"].end(); it ++){
            bool is_setting = false;
            for(int i = 0; i < 3; i++){
                if(it.value()["name"] == userSettings[i]){
                    is_setting = true;
                }
            }

            if(is_setting == false){
                res += (string)it.value()["name"] + "is not an user setting\n";
            } else {
                int response = our_window.setUserSetting(it.value()["name"], it.value()["value"]);
                if(response == 1){
                    res += "userSetting " + (string)it.value()["name"] + " was set to " + (string)it.value()["value"] + "\n";
                } else {
                    res += "userSetting " + (string)it.value()["name"] + " was not found\n";
                }
            }
        }
        
        response.send(Http::Code::Ok, res);
    }

    void setSettingsJSON(const Rest::Request& request, Http::ResponseWriter response) {
        bool alerted = false, critical_air_quality = false, critical_humidity = false;
        int nr_settings = 5, nr_states = 5;
        string settings[nr_settings] = {"luminosity", "temperature", "humidity", "air_quality", "impact"};
        string states[nr_states] = {"windows_open", "windows_semi_open", "windows_closed", "curtains_open", "alerted"};

        Guard guard(WindowLock);

        map<string, int> actualized_state_dict = our_window.getActualizedStateDictWindow();

        auto jj = json::parse(request.body())["input_buffers"];
        json jj_settings = jj["settings"];
        json jj_states;
        //cout << jj["states"].size() << '\n';
        if(!jj["states"].size()) {
            std::ifstream input_json("window_settings_original.json");
            json content_json;
            input_json >> content_json;
            jj_states = content_json["input_buffers"]["states"];
            input_json.close();
        } else {
            jj_states = jj["states"];
        }
        string res = "";
        nr_settings = jj_settings["buffer-tokens"].size();
        //cout << nr_settings << '\n';

        for (json::iterator it = jj_settings["buffer-tokens"].begin(); it != jj_settings["buffer-tokens"].end(); ++it) {

            bool is_setting = false;
            json js = it.value();
            string js_setting  = js["name"];
            //cout << js_setting << '\n';
            int i;

            for (i = 0; i < nr_settings; i++) {
                if (js_setting == settings[i]) {
                         is_setting = true;
                }
            }
            if (is_setting == false) {
                res += js_setting + " is not a setting\n";
            }
            else {
                string val = js["value"];

                double numerical_val = std::stod(val);
                auto change_state_prev = our_window.getChangedState();
                int setResponse = our_window.setSetting(js_setting, val);

                actualized_state_dict = our_window.getActualizedStateDictWindow();

                if(actualized_state_dict["alerted"] == 1){
                    //cout << "THEFT ALERT!!!" << endl;
                    //cout << "AN ATTEMPT TO BREAK THE WINDOW WAS MADE!" << endl;
                    res += "alerted was set to true\n";
                    string str = "mosquitto_pub -t test/t1 -m \"AN ATTEMPT TO BREAK THE WINDOW WAS MADE!\" ";
                    const char *command = str.c_str();
                    //cout << "Am intrat unde trebuie";
                    system(command);
                    alerted = true;
                    response.send(Http::Code::Ok, res);
                    std::ifstream input_json("window_output.json");
                    json content_json;
                    input_json >> content_json;
                    auto& output = content_json["output_buffers"];
                    output[0]["value"] = false;
                    output[1]["value"] = false;
                    output[2]["value"] = false;
                    output[3]["value"] = false;
                    output[4]["value"] = true;
                    input_json.close();
                    // write json output
                    std::ofstream output_json ("window_output.json");
                    output_json << std::setw(4) << content_json << std::endl;
                    output_json.close();
                    return;
                }

                if(actualized_state_dict["windows_closed"] == 1 && js_setting == "air_quality" && numerical_val < 50) {
                    cout << "AIR QUALITY ALERT!!!" << endl;
                    critical_air_quality = true;
                }

                if(actualized_state_dict["windows_closed"] == 1 && js_setting == "humidity" && numerical_val > 50) {
                    cout << "HUMIDITY ALERT!!!" << endl;
                    critical_humidity = true;
                }

                string affected_state = "";

                if(setResponse == 2) {
                    auto change_state_after = our_window.getChangedState();
                    for(int j=0; j<change_state_after.size(); j++) {
                        if(change_state_after[j] != change_state_prev[j] && js_setting == settings[j]) {
                            affected_state = states[j];
                            // int setNewResponse = change_state_after[j] % 2;
                            break;
                        }
                    }
                }

                if (setResponse)
                    res += js_setting + " was set to " + val + "\n";
                else
                    res += js_setting +  " was not found and or '" + val + "' was not a valid value\n";
            }
        }

        actualized_state_dict = our_window.getActualizedStateDictWindow();

        for (json::iterator it = jj_states["buffer-tokens"].begin(); it != jj_states["buffer-tokens"].end(); ++it) {

            bool is_state = false;

            json js = it.value();

            string js_state  = js["name"];

            int i;
            for (i = 0; i < nr_states; i++) {
                if (js_state == states[i]) {
                         is_state = true;
                         break;
                }
            }
            if (is_state == false) {
                res += js_state + " is not a state\n";
            }
            else {
                string val = js["value"];
                int setResponse;
                if(actualized_state_dict.find(js_state) == actualized_state_dict.end()) {
                    int setResponse = our_window.setState(js_state, val);
                } else {
                    int setSettingsResponse = actualized_state_dict[js_state];
                    setResponse = 1;// setSettingsResponse;
                    if(setSettingsResponse == 1){
                        val = "true";
                    } else {
                        val = "false";
                    }
                }
                if(critical_air_quality || critical_humidity) {
                    if(val == "true" && (js_state == "windows_open" || js_state == "windows_semi_open")) {
                        actualized_state_dict[js_state] = 0;
                        val = "false";
                    }
                    if(val == "false" && js_state == "windows_closed") {
                        actualized_state_dict[js_state] = 1;
                        val = "true";
                    }
                }
                if (setResponse)
                    res += js_state + " was set to " + val + "\n";
                else
                    res += js_state +  " was not found and or " + val + " was not a valid value\n";
            }
        }

        // read json output
        std::ifstream input_json("window_output.json");
        json content_json;
        input_json >> content_json;
        auto& output = content_json["output_buffers"];
        output[0]["value"] = actualized_state_dict["windows_open"];
        output[1]["value"] = actualized_state_dict["windows_semi_open"];
        output[2]["value"] = actualized_state_dict["windows_closed"];
        output[3]["value"] = actualized_state_dict["curtains_open"];
        output[4]["value"] = actualized_state_dict["alerted"];
        input_json.close();

        // write json output
        std::ofstream output_json ("window_output.json");
        output_json << std::setw(4) << content_json << std::endl;
        output_json.close();


        our_window.setActualizedStateDictWindow(actualized_state_dict);
        response.send(Http::Code::Ok, res);
    }

    void doAuth(const Rest::Request& request, Http::ResponseWriter response) {
        // Function that prints cookies
        printCookies(request);
        // In the response object, it adds a cookie regarding the communications language.
        response.cookies()
            .add(Http::Cookie("lang", "en-US"));
        // Send the response
        response.send(Http::Code::Ok);
    }

    // Endpoint to configure one of the Window's settings.
    void setSetting(const Rest::Request& request, Http::ResponseWriter response){
        // You don't know what the parameter content that you receive is, but you should
        // try to cast it to some data structure. Here, I cast the settingName to string.
        auto settingName = request.param(":settingName").as<std::string>();
        // This is a guard that prevents editing the same value by two concurent threads.
        Guard guard(WindowLock);

        //std::cout << "Setter" << endl;
        string val = "";
        if (request.hasParam(":value")) {
            auto value = request.param(":value");

            val = value.as<string>();
        }

        // Setting the Window's setting to value
        int setResponse = our_window.setSetting(settingName, val);

        // Sending some confirmation or error response.
        if (setResponse) {
            response.send(Http::Code::Ok, settingName + " was set to " + val);
        }
        else {
            response.send(Http::Code::Not_Found, settingName + " was not found and or '" + val + "' was not a valid value ");
        }

    }

    // Setting to get the settings value of one of the configurations of the Window
    void getSetting(const Rest::Request& request, Http::ResponseWriter response){
        auto settingName = request.param(":settingName").as<std::string>();
        auto settingDetails = request.body();

        Guard guard(WindowLock);

        string valueSetting = our_window.get(settingName);

        //std::cout << valueSetting << endl;

        if (valueSetting != "") {

            // In this response I also add a couple of headers, describing the server that sent this response, and the way the content is formatted.
            using namespace Http;
            response.headers()
                        .add<Header::Server>("pistache/0.1")
                        .add<Header::ContentType>(MIME(Text, Plain));

            response.send(Http::Code::Ok, settingName + " is " + valueSetting);
        }
        else {
            response.send(Http::Code::Not_Found, settingName + " was not found");
        }
    }
      // Create the lock which prevents concurrent editing of the same variable
    using Lock = std::mutex;
    using Guard = std::lock_guard<Lock>;
    Lock WindowLock;

    // Instance of the Window model
    Window our_window;

    // Defining the httpEndpoint and a router.
    std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;
};
