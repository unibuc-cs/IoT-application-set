#include <algorithm>
#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <chrono>
#include <time.h>
#include <string>
#include <signal.h>
#include <nlohmann/json.hpp>
#include <boost/random.hpp>
#include <boost/nondet_random.hpp>
#include "./models/models.cpp"
#include <mosquitto.h>


// General advice: pay attention to the namespaces that you use in various contexts. Could prevent headaches.
using namespace std;
using namespace Pistache;


// paths to the storage
const string VISCOSITY_INFO_PATH = "./data/viscosity_intervals.json";
const string SCHEDULER_INFO_PATH = "./data/scheduler.json";
const string BOIL_HISTORY_INFO_PATH = "./data/boil_history.json";


class Utils {
public:

    static int computeViscosity() {
        return rand() % 70 + 30;
    }


    static string getCurrentTime() {
        auto current_time = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(current_time);
        std::string ts = std::ctime(&now_c);
        ts.resize(ts.size() - 1);
        return ts;
    }


    static string getBadRequestResponse() {
        json jsonObject =
                {
                        {"httpCode", Http::Code::Bad_Request},
                        {"message",  "Wrong parameter type"}

                };
        return jsonObject.dump();
    }

    static string getOkResponseBody(string message) {

        string timestamp = getCurrentTime();

        InfoMessage msg;
        msg.setMessage(message);
        msg.setTimeStamp(timestamp);

        return json(msg).dump(2);
    }

    static string findViscosityTemperature(vector<ViscosityInfo> &viscosity_data, int containingLiquidViscosity) {

        // find the interval of viscosity and the associated temperature of the containing liquid
        for (int index = 0; index < viscosity_data.size() - 1; index++) {
            if (viscosity_data[index].getLowerBound() <= containingLiquidViscosity &&
                containingLiquidViscosity < viscosity_data[index + 1].getLowerBound()) {

                return viscosity_data[index].getTemperature();

            }

        }

        // if is greater than the last value then set the temperature to max
        return viscosity_data[viscosity_data.size() - 1].getTemperature();
    }

    static json readJson(string fname) {
        ifstream i(fname);
        json in;
        i >> in;
        return in;
    }

    static void writeJson(string fname, json j) {
        ofstream o(fname);
        o << setw(4) << j << '\n';
    }

};
// Some generic namespace, with a simple function we could use to test the creation of the endpoints.
namespace Generic {

    void handleReady(const Rest::Request &, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "1");
    }


    // GET /warmLiquid/:temperature/:scale
    void warmLiquid(const Rest::Request &request, Http::ResponseWriter response) {
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));


        Temperature temperature;
        try {

            auto temp = request.param(":temperature").as<string>();
            auto scale = request.param(":scale").as<string>();


            auto boilHistory = Utils::readJson(BOIL_HISTORY_INFO_PATH).get<vector<Temperature>>();
            string settingsMessage;
            // if temperature is set to 0 degrees then use the last value - stateful
            if (temp == "0") {

                auto lastBoil = boilHistory[boilHistory.size() - 1];
                temp = lastBoil.getTemperature();
                scale = lastBoil.getScale();

                settingsMessage = "Retrieved the last boiling settings. ";

            } else {
                // add the new action to the history of boiling
                Temperature t;
                t.setTemperature(temp);
                t.setScale(scale);
                boilHistory.push_back(t);

                settingsMessage = "Kettle settings saved. ";
                Utils::writeJson(BOIL_HISTORY_INFO_PATH, json(boilHistory));

            }


            string responseMessage = settingsMessage +
                                     "The water is warming at " + temp +
                                     " degrees " + scale;

            response.send(Http::Code::Ok, Utils::getOkResponseBody(responseMessage));

        }
        catch (...) {

            response.send(Http::Code::Bad_Request, Utils::getBadRequestResponse());
        }


    }

    // GET /stirLiquid/:rmp
    void stirLiquid(const Rest::Request &request, Http::ResponseWriter response) {
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));


        try {
            // the the value of rmp param
            auto temp = request.param(":rpm").as<string>();

            // send an appropriate message
            string message = "Started stirring the content of the kettle at " + temp + " rmp";
            response.send(Http::Code::Ok, Utils::getOkResponseBody(message));

        }
        catch (...) {
            response.send(Http::Code::Bad_Request, Utils::getBadRequestResponse());

        }
    }

    // GET /boilLiquidByViscosity
    void boilLiquidByViscosity(const Rest::Request &request, Http::ResponseWriter response) {
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));


        // get the information about the invervals of viscosity
        auto viscosity_data = Utils::readJson(VISCOSITY_INFO_PATH).get<vector<ViscosityInfo>>();

//        cout << "SIZE " << viscosity_data.size() << '\n';

        // compute the viscosity of the containing liquid
        // dumb computation: generate a number between min and max value
        int containingLiquidViscosity = Utils::computeViscosity();
        bool ok = false;
        string optimalTemperature;
        optimalTemperature = Utils::findViscosityTemperature(viscosity_data, containingLiquidViscosity);

        string message =
                "The temperature has been set to " + optimalTemperature + " degrees";

        response.send(Http::Code::Ok, Utils::getOkResponseBody(message));


    }

    // POST /makeTea - see input_buffer.json for more information about the body structure
    void makeTea(const Rest::Request &request, Http::ResponseWriter response) {

        auto requestJson = nlohmann::json::parse(request.body());
        auto teaInformation = requestJson.get<TeaInformation>();

        string warmMessage = "";
        if (teaInformation.getWarm())
            warmMessage = "Your tea will remain warm.";


        string message = "Preparing your tea...The temperature has been set to " +
                         teaInformation.getTempInfo().getTemperature() + " " +
                         teaInformation.getTempInfo().getScale() + " degrees. Infusion time: " +
                         to_string(teaInformation.getTime()) + " minutes. " +
                         warmMessage;


        response.send(Http::Code::Ok, Utils::getOkResponseBody(message));

    }

    // POST / warmLiquidByDate - see input_buffer.json for more information about the body structure

    void warmLiquidByDate(const Rest::Request &request, Http::ResponseWriter response) {

        auto requestJson = nlohmann::json::parse(request.body());
        auto kettleScheduler = requestJson.get<KettleScheduler>();


        // retrieve the information about the last scheduler's options
        auto previousSchedule = Utils::readJson(SCHEDULER_INFO_PATH).get<KettleScheduler>();

        string recurrentMessage = "";

        // choose an appropriate message considering the previous configuration - stateful
        if (previousSchedule.getIsRecurrent() && !kettleScheduler.getIsRecurrent())
            recurrentMessage = "Recurrent mode disabled";
        else if (!previousSchedule.getIsRecurrent() && kettleScheduler.getIsRecurrent())
            recurrentMessage = "Recurrent mode enabled";


        Utils::writeJson(SCHEDULER_INFO_PATH, requestJson);

        string message = "Scheduler is set at " + kettleScheduler.getHour() + ". Temperature: " +
                         kettleScheduler.getTempInfo().getTemperature() + " degrees " +
                         kettleScheduler.getTempInfo().getScale() + ". " + recurrentMessage;

        response.send(Http::Code::Ok, Utils::getOkResponseBody(message));


    }

}

// Definition of the SmartKettleEndpoint class

class SmartKettleEndpoint {
public:
    explicit SmartKettleEndpoint(Address addr)
            : httpEndpoint(make_shared<Http::Endpoint>(addr)) {
    }

    // Initialization of the server. Additional options can be provided here
    void init(size_t thr = 2) {
        auto opts = Http::Endpoint::options()
                .threads(static_cast<int>(thr));
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
    void stop() {
        httpEndpoint->shutdown();
    }


private:
    void setupRoutes() {
        using namespace Rest;
        // Defining various endpoints
        // Generally say that when http://localhost:9080/ready is called, the handleReady function should be called.
        Routes::Get(router, "/ready", Routes::bind(&Generic::handleReady));
        Routes::Get(router, "/warmLiquid/:temperature/:scale", Routes::bind(&Generic::warmLiquid));
        Routes::Post(router, "/warmLiquidByDate", Routes::bind(&Generic::warmLiquidByDate));
        Routes::Get(router, "/stirLiquid/:rpm", Routes::bind(&Generic::stirLiquid));
        Routes::Post(router, "/makeTea", Routes::bind(&Generic::makeTea));
        Routes::Get(router, "/boilLiquidByViscosity", Routes::bind(&Generic::boilLiquidByViscosity));
    }

    // Defining the class of the SmartJuiceMaker. It should model the entire configuration of the SmartJuiceMaker
    class SmartKettle {
    public:
        explicit SmartKettle() {}
    };

    // Create the lock which prevents concurrent editing of the same variable
    using Lock = mutex;
    using Guard = lock_guard<Lock>;
    Lock kettleLock;

    // Instance of SmartKettle
    SmartKettle sktl;

    // Defining the httpEndpoint and a router.
    shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;
};

int main(int argc, char *argv[]) {

// This code is needed for gracefull shutdown of the server when no longer needed.
    sigset_t signals;
    if (sigemptyset(&signals) != 0
        || sigaddset(&signals, SIGTERM) != 0
        || sigaddset(&signals, SIGINT) != 0
        || sigaddset(&signals, SIGHUP) != 0
        || pthread_sigmask(SIG_BLOCK, &signals, nullptr) != 0) {
        perror("install signal handler failed");
        return 1;
    }

    // Set a port on which your server to communicate
    Port port(9080);

    // Number of threads used by the server
    int thr = 2;

    if (argc >= 2) {
        port = static_cast<uint16_t>(std::stol(argv[1]));

        if (argc == 3)
            thr = std::stoi(argv[2]);
    }

    Address addr(Ipv4::any(), port);

    cout << "Cores = " << hardware_concurrency() << endl;
    cout << "Using " << thr << " threads" << endl;

    // Instance of the class that defines what the server can do.
    SmartKettleEndpoint stats(addr);

    // Initialize and start the server
    stats.init(thr);
    stats.start();

    struct mosquitto *mosq;

    int pid = fork();

    if (pid == 0) {
        try {
            mosquitto_lib_init();

            // create a new client as publisher

            mosq = mosquitto_new("publisher", true, NULL);

            // connect to port 1883
            int rc = mosquitto_connect(mosq, "mqtt_server", 1883, 60);

            if (rc != 0) {
                mosquitto_destroy(mosq);
                throw string("Could not connect to server") + to_string(rc);
            }


            string message;
            message = " Warming your tea at 70 degrees C";

            mosquitto_publish(mosq, NULL, "kettle/temp/70/C", message.size(), message.c_str(), 0, false);




            // get scheduler settings

            message = Utils::readJson(SCHEDULER_INFO_PATH).dump();
            mosquitto_publish(mosq, NULL, "kettle/scheduler", message.size(), message.c_str(), 0, true);




            // interact with the viscosity sensor and retrieve data about the containing liquid

            auto viscosity_data = Utils::readJson(VISCOSITY_INFO_PATH).get<vector<ViscosityInfo>>();
            int viscosity = Utils::computeViscosity();
            json data = {
                    {"viscosity",        to_string(viscosity)},
                    {"rec. temperature", Utils::findViscosityTemperature(viscosity_data, viscosity)}
            };
            message = data.dump();

            mosquitto_publish(mosq, NULL, "kettle/viscosity", message.size(), message.c_str(), 0, true);
        } catch (string err) {
            cerr << "[MQTT] " << err << endl;
        } catch (...) {
            cerr << "[MQTT] Some unknown exception was thrown" << endl;
        }
    }

    // Code that waits for the shutdown signal for the server
    int signal = 0;
    int status = sigwait(&signals, &signal);
    if (status == 0) {
        std::cout << "received signal " << signal << std::endl;
    } else {
        std::cerr << "sigwait returns " << status << std::endl;
    }

    stats.stop();
}
