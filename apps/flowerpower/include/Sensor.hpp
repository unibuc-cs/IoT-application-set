
#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <map>
#include <vector>
#include <string>

using namespace std;


namespace pot
{
class Sensor
{
    string name;
    double doubleValue;
    string stringValue;
    double minValue;
    double maxValue;
public:
    Sensor()
    {

    }
    Sensor(string _name, double _value, double _minValue, double _maxValue)
    {
        name = _name;
        doubleValue = _value;
        minValue = _minValue;
        maxValue = _maxValue;
    }
    Sensor(string _name, string _value, double _minValue, double _maxValue)
    {
        name = _name;
        stringValue = _value;
        minValue = _minValue;
        maxValue = _maxValue;
    }
    ~Sensor()
    {

    }
    void SetName(string newName)
    {
        name = newName;
    }
    string GetName()
    {
        return name;
    }
    void SetValue(double newValue)
    {
        doubleValue = newValue;
    }
    double GetDoubleValue()
    {
        return doubleValue;
    }
    void SetValue(string newValue)
    {
        stringValue = newValue;
    }
    string GetStringValue()
    {
        return stringValue;
    }
    void SetMinValue(double newValue)
    {
        minValue = newValue;
    }
    double GetMinValue()
    {
        return minValue;
    }
    void SetMaxValue(double newValue)
    {
        maxValue = newValue;
    }
    double GetMaxValue()
    {
        return maxValue;
    }

};
}

#endif