#include "mqtt.hpp"

#include <mqtt/client.h>

mqtt::client *client = nullptr;

void mqttConnect()
{
    // Create a new client
    const std::string serverUri = "localhost";
    const std::string clientId = "smarteeth";
    client = new mqtt::client(serverUri, clientId);

    mqtt::connect_options options;
    options.set_keep_alive_interval(20);
    options.set_clean_session(true);

    try
    {
        // Connect to the MQTT broker
        client->connect(options);
    }
    catch (const mqtt::exception &exc)
    {
        std::cerr << exc.what() << " [" << exc.get_reason_code() << "]" << std::endl;

        delete client;
        client = nullptr;
    }
}

void mqttDisconnect()
{
    // Disconnect
    client->disconnect();

    // Cleanup resources
    delete client;

    client = nullptr;
}

void mqttPublishMessage(const std::string &topic, const std::string &payload)
{
    // Connection is closed, do nothing
    if (!client)
    {
        return;
    }

    // Create a message
    auto msg = mqtt::make_message(topic, payload);

    // Publish it to the server
    client->publish(msg);
}
