#include "brushing.hpp"

#include <chrono>
#include <stdexcept>

#include "configuration.hpp"
#include "mqtt.hpp"
#include "statistics.hpp"

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

static Conditions conditions;
static const Configuration *currentConfig;
static TimePoint startTime;
static bool brushingInProgress = false;
static BrushingData currentBrushingData;
// Aici tinem minte cat am periat fiecare zona.
static std::vector<int> timeSpentOnArea;

void setConditions(const std::string &name, int value)
{
    if (name == "toothpasteWeight")
    {
        conditions.toothpasteWeight = value;
    }
    else if (name == "temperature")
    {
        conditions.temperature = value;
    }
    else if (name == "humidty")
    {
        conditions.humidity = value;
    }
    else
    {
        throw std::runtime_error("Unknown condition parameter");
    }
}

void checkConditions()
{
    if (conditions.toothpasteWeight < 1)
        throw std::runtime_error("Cantitate insuficienta de pasta de dinti");
    if (conditions.toothpasteWeight > 5)
        throw std::runtime_error("Cantitate exagerata de pasta de dinti");
    if (conditions.temperature < 10)
        throw std::runtime_error("Temperatura prea scazuta");
    if (conditions.temperature > 45)
        throw std::runtime_error("Temperatura prea ridicata");
    if (conditions.humidity < 20)
        throw std::runtime_error("Umeziti periuta de dinti");

    // Conditii optime pentru periaj.
}

void startBrushing(const Configuration *configuration)
{
    if (brushingInProgress)
    {
        throw std::runtime_error("Brushing already started");
    }

    checkConditions();

    timeSpentOnArea = std::vector<int>();

    currentConfig = configuration;
    brushingInProgress = true;
    currentBrushingData = BrushingData{};

    startTime = Clock::now();

    mqttPublishMessage("brushing", "started");
}

void stopBrushing()
{
    if (!brushingInProgress)
    {
        throw std::runtime_error("Brushing hasn't started yet");
    }

    // Compute total brushing time
    int totalTime = 0;
    for (int areaTime : timeSpentOnArea)
    {
        totalTime += areaTime;
    }
    currentBrushingData.time = totalTime;

    // Save brushing data
    addBrushingData(currentConfig->name, currentBrushingData);

    brushingInProgress = false;
    currentConfig = nullptr;

    mqttPublishMessage("brushing", "stopped");
}

const Configuration *getCurrentConfiguration()
{
    return currentConfig;
}

int getCurrentTooth()
{
    if (!brushingInProgress)
    {
        throw std::runtime_error("No brushing currently in progress");
    }

    return timeSpentOnArea.size() + 1;
}

void signalTartrum()
{
    currentBrushingData.teethWithTartrum.push_back(getCurrentTooth());
}

void signalBleeding()
{
    currentBrushingData.bleeding = true;
}

bool isBleeding()
{
    return currentBrushingData.bleeding;
}

void moveBrush()
{
    if (!brushingInProgress)
    {
        throw std::runtime_error("Brushing hasn't started yet");
    }

    // ok stiu ca asta arata putin dubios dar face ce trebuie ca trebuie sa faca
    auto previousStartTime = startTime;
    startTime = Clock::now();
    auto timeSpan = std::chrono::duration_cast<std::chrono::seconds>(startTime - previousStartTime);
    timeSpentOnArea.push_back(timeSpan.count());
}

bool checkBrushing()
{
    if (!brushingInProgress)
    {
        throw std::runtime_error("Brushing hasn't started yet");
    }

    auto endTime = Clock::now();
    auto timeSpan = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

    // Aici 30 parea idealul, a mea dupa 30 bazaie (cred).
    if (timeSpan.count() < 30)
    {
        // Mai trebuie periat
        return false;
    }
    else
    {
        // Zona este gata
        return true;
    }
}

std::vector<BrushingTimeReport> checkBrushingTime()
{
    std::vector<BrushingTimeReport> v;
    int count = 0;

    for (auto &it : timeSpentOnArea)
    {
        count++;

        BrushingTimeReport report;
        report.area = count;
        report.time = it;

        if (it < 30)
        {
            // timp insuficient
            report.sufficientTime = false;
        }
        else
        {
            // timp suficient
            report.sufficientTime = true;
        }

        v.push_back(report);
    }

    return v;
}
