#pragma once

#include <string>

void mqttConnect();
void mqttDisconnect();

void mqttPublishMessage(const std::string &topic, const std::string &payload);
