#pragma once

#include <string>
#include <vector>

#include "json.hpp"

//toate datele retinute in urma unui periaj
struct BrushingData
{
    //secunde
    int time;
    //vector cu dintii afectati (am presupus ca notam fiecare dinte cu un int)
    std::vector<int> teethWithTartrum;
    //true daca s-a identificat o sangerare in timpul periajului
    bool bleeding;
};

struct UserStats
{
    //vector de zile; o zi are mai multe periaje
    std::vector<std::vector<BrushingData>> oneYearHistory;
    //data ultimului periaj
    std::string lastBrushingDate;
    int minimBrushings;
    int maximBrushings;
    std::vector<int> tartrumHistory;
};

void addBrushingData(const std::string &name, BrushingData data);
json getStatistics(const std::string &name);
