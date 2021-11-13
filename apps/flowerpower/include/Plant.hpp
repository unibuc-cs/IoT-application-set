
#ifndef PLANT_HPP
#define PLANT_HPP

#include <map>
#include <vector>
#include <string>

using namespace std;

namespace pot {
    
class Plant
{
    string name;
    string color;
    double height;
    string plantType;
    string suitableSoilType;
public:
    Plant(string _name, string _color, double _height, string _plantType, string _suitableSoilType)
    {
        name = _name;
        color = _color;
        height = _height;
        plantType = _plantType;
        suitableSoilType = _suitableSoilType;
    }
    Plant()
    {

    }
    ~Plant()
    {

    }
    string GetName()
    {
        return name;
    }
    string GetColor()
    {
        return color;
    }
    double GetHeight()
    {
        return height;
    }
    string GetType()
    {
        return plantType;
    }
    string GetSoil()
    {
        return suitableSoilType;
    }

    bool operator==(Plant& p1)
    {
        return p1.GetName() == this->GetName();
    }
};




}

#endif