#pragma once

struct ToothHealthInfo
{
    int intensity;
    bool overThreshold;
};

void updateToothColor(int data);

ToothHealthInfo checkTartrum();

ToothHealthInfo checkGumBleeding();
