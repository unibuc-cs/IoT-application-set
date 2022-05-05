#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <utility>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <pistache/endpoint.h>
#include <pistache/router.h>

#include "brushing.hpp"
#include "configuration.hpp"
#include "directions.hpp"
#include "health.hpp"
#include "json.hpp"
#include "mqtt.hpp"
#include "statistics.hpp"

using namespace Pistache;
using namespace Pistache::Http;
using namespace Pistache::Rest;

void setConfigurationRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    const auto params = json::parse(request.body());

    std::cout << "Input received: " << params << '\n';

    const auto name = params["name"];

    Configuration config;
    config.name = name;
    config.age = params["age"];
    config.program = params["program"];

    for (int tooth : params["teeth"])
    {
        if (tooth < 1 || tooth > 32)
        {
            std::cout << "Ignoring invalid tooth " << tooth << '\n';
            continue;
        }

        // Elimina duplicatele
        if (find(config.teeth.begin(), config.teeth.end(), tooth) != config.teeth.end())
        {
            std::cout << "Ignoring duplicate tooth " << tooth << '\n';
            continue;
        }

        config.teeth.push_back(tooth);
    }

    setConfiguration(name, config);
    saveConfigurations();

    response.send(Http::Code::Ok, "Configuration Saved!");
}

void getConfigurationRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    const auto name = request.param(":name").as<std::string>();
    const auto config = getConfiguration(name);

    json j;

    j["age"] = config.age;
    j["program"] = getProgramName(config.program);
    j["teeth"] = config.teeth;

    response.send(Http::Code::Ok, j.dump());
}

void setConditionsRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    const auto name = request.param(":name").as<std::string>();
    const auto value = request.param(":value").as<int>();

    setConditions(name, value);

    response.send(Http::Code::Ok);
}

void checkConditionsRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    try
    {
        checkConditions();

        response.send(Http::Code::Ok, "Ready for brushing");
    }
    catch (const std::exception &e)
    {
        response.send(Http::Code::Ok, e.what());
    }
}

void startBrushingRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    const auto configName = request.param(":name").as<std::string>();

    const Configuration *config;
    try
    {
        config = &getConfiguration(configName);
    }
    catch (std::exception)
    {
        response.send(Http::Code::Bad_Request, "Config not found");
        return;
    }

    startBrushing(config);

    response.send(Http::Code::Ok, "Brushing started");
}

void stopBrushingRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    stopBrushing();

    response.send(Http::Code::Ok);
}

void to_json(json &output, const BrushingTimeReport &r)
{
    output = json{
        {"area", r.area},
        {"time", r.time},
        {"sufficientTime", r.sufficientTime}};
}

void getBrushingDirectionRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    const auto colorAndDirections = getLedsColorAndDirections();

    std::string output;
    output += "color: " + getLedsColorAsString(colorAndDirections.first) + "\n";
    output += getDirectionsAsString(colorAndDirections.second);

    response.send(Http::Code::Ok, output);
}

void moveBrushRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    moveBrush();

    response.send(Http::Code::Ok);
}

void checkBrushingRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    std::string result;
    if (checkBrushing())
    {
        result = "done";
    }
    else
    {
        result = "not done";
    }

    response.send(Http::Code::Ok, result);
}

void checkBrushingTimeRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    json j = checkBrushingTime();

    response.send(Http::Code::Ok, j.dump());
}

void updateToothColorRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    const auto value = request.param(":value").as<int>();

    updateToothColor(value);

    response.send(Http::Code::Ok);
}

void checkTartrumRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    const auto info = checkTartrum();

    json j = {
        {"tooth", getCurrentTooth()},
        {"intensity", info.intensity},
        {"hasTartrum", info.overThreshold}};

    response.send(Http::Code::Ok, j.dump());
}

void checkGumBleedingRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    const auto info = checkGumBleeding();

    json j = {
        {"tooth", getCurrentTooth()},
        {"intensity", info.intensity},
        {"isBleeding", info.overThreshold}};

    response.send(Http::Code::Ok, j.dump());
}

void getStatisticsRoute(const Rest::Request &request, Http::ResponseWriter response)
{
    const auto name = request.param(":name").as<std::string>();

    const auto stats = getStatistics(name);

    response.send(Http::Code::Ok, stats.dump());
}

int main()
{
    // Load saved configs from disk
    loadConfigurations();

    // Set up routes
    Router router;

    // POST /configuration
    // {
    //     "name": "David",
    //     "age": 24,
    //     "program": 3,
    //     "teeth": [1,2,6,4,2,6,4,1,36,99,8]
    // }
    router.post("/configuration", Routes::bind(setConfigurationRoute));
    // GET /configuration/David
    router.get("/configuration/:name", Routes::bind(getConfigurationRoute));

    // POST /brushing/conditions/{toothpasteWeight,temperature,humidty}/<integer value>
    router.post("/brushing/conditions/:name/:value", Routes::bind(setConditionsRoute));
    // GET /brushing/conditions/check
    router.get("/brushing/conditions/check", Routes::bind(checkConditionsRoute));

    // POST /brushing/start/{configuration name}
    router.post("/brushing/start/:name", Routes::bind(startBrushingRoute));
    // POST /brushing/stop
    router.post("/brushing/stop", Routes::bind(stopBrushingRoute));

    // GET /brushing/direction
    router.get("/brushing/direction", Routes::bind(getBrushingDirectionRoute));
    // POST /brushing/move
    router.post("/brushing/move", Routes::bind(moveBrushRoute));
    // GET /brushing/check
    router.get("/brushing/check", Routes::bind(checkBrushingRoute));
    // GET /brushing/time
    router.get("/brushing/time", Routes::bind(checkBrushingTimeRoute));

    // POST /health/toothColor/<integer value>
    router.post("/health/toothColor/:value", Routes::bind(updateToothColorRoute));
    router.get("/health/tartrum", Routes::bind(checkTartrumRoute));
    router.get("/health/gumBleeding", Routes::bind(checkGumBleedingRoute));

    // GET /statistics/{user name}
    router.get("/statistics/:name", Routes::bind(getStatisticsRoute));

    // Configure server
    const std::string host = "localhost";
    const Port port = 9080;

    Address address(host, port);
    Endpoint endpoint(address);
    endpoint.init();
    endpoint.setHandler(router.handler());

    // Set up MQTT client
    mqttConnect();

    // Start server
    std::cout << "Server listening on http://" << host << ':' << port << std::endl;
    std::cout << "Press Ctrl + C to quit" << std::endl;
    endpoint.serve();

    mqttDisconnect();
}
