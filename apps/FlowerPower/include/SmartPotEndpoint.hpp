///
/// @file SmartPotEndpoint.hpp
///
/// @brief Class which represents the HTTP and MQTT endpoints for
/// the @b SmartPot class.
///
#ifndef SMART_POT_ENDPOINT_HPP
#define SMART_POT_ENDPOINT_HPP

#include "SmartPot.hpp"

#include <iostream>
#include <signal.h>
// Our HTTP library.
#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
// Our MQTT library.
#include <mosquitto.h>

using namespace std;
using namespace Pistache;
using Lock = mutex;
using Guard = lock_guard<Lock>;

namespace pot
{

    class SmartPotEndpoint
    {
    public:
        SmartPotEndpoint(Address address);
        ~SmartPotEndpoint(void);

        // Server initialization.
        void init(void);

        // Server start.
        void start(void);

        // Server stop.
        void stop(void);

        
    private:
        void createHttpRoutes(void);

        // GETs.
        void getSetting         (const Rest::Request &request,
                                Http::ResponseWriter response);

        void getStatus          (const Rest::Request &request,
                                Http::ResponseWriter response);

        void shovel             (const Rest::Request &request,
                                Http::ResponseWriter response);

        void soilStatus         (const Rest::Request &request,
                                Http::ResponseWriter response);

        void irrigationSoil     (const Rest::Request &request,
                                Http::ResponseWriter response);

        void injectMinerals     (const Rest::Request &request,
                                Http::ResponseWriter response);

        void activateSolarLamp  (const Rest::Request &request,
                                Http::ResponseWriter response);
        
        // PUTs.
        
        void putSetting         (const Rest::Request &request,
                                Http::ResponseWriter response);

        void putSettingUpdate  (const Rest::Request &request,
                                Http::ResponseWriter response);

        void putPlantType      (const Rest::Request &request,
                                Http::ResponseWriter response);

        // Mosquitto calbacks.
        static void mosquittoOnMessage  (struct mosquitto *mosq,
                                        void *obj,
                                        const struct mosquitto_message *msg);
                                        
        static void mosquittoOnConnect  (struct mosquitto *mosq,
                                        void *obj,
                                        int rc);

        // static void mosquittoOnSubscribe (struct mosquitto *mosq,
        //                                   void *userdata, 
        //                                   int mid, int qos_count, 
        //                                   const int *granted_qos);

        static map <int, string> sensorNameMap;

        // Our Endpoint for the http server thread.
        std::shared_ptr<Http::Endpoint> httpEndpoint;
        // The router for our HTTP routes.
        Rest::Router router;

        // Our MQTT Subscriber.
        struct mosquitto *mosquittoSub;

        // The actual smart pot.
        static SmartPot *smartPot;

        // Prohibits the threads to concurrently edit the same variable.
        Lock potLock;
    };

}

#endif