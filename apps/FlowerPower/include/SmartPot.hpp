///
/// @file SmartPot.hpp
///
/// @brief Class which represents the SmartPot actual functionalities
/// and methods.
///
#ifndef SMART_POT_HPP
#define SMART_POT_HPP

#include "Plant.hpp"
#include "Sensor.hpp"

#include <map>
#include <vector>
#include <string>


using namespace std;

namespace pot
{
class SmartPot
{
    Plant plant;
    map<int, map<string, Sensor>> sensors;

public:
    SmartPot()
    {

    }

    SmartPot(Plant _plant, const map<int, map<string, Sensor>> &_sensors)
    {
        plant = _plant;
        sensors = _sensors;
    }

    bool Find(string nameToFind)
    {
        for(auto it = sensors.begin(); it != sensors.end(); ++it)
        {
            map<string, Sensor> m = it->second;
            for(auto it2 = m.begin(); it2 != m.end(); ++it2)
            {
                if(it2->first == nameToFind)
                    return true;
            }
        }
        return false;
    }
    Sensor GetSensor(string nameToFind)
    {
        for(auto it = sensors.begin(); it != sensors.end(); ++it)
        {
            map<string, Sensor> m = it->second;
            for(auto it2 = m.begin(); it2 != m.end(); ++it2)
            {
                if(it2->first == nameToFind)
                    return it2->second;
            }
        }
        return Sensor();
    }


    int Get(const string& name, Sensor& returnedValue)
    {
        // If the setting does not exist.
        if(!Find(name))
        {
            returnedValue = Sensor();
            return 1;
        }
        else
        {
            returnedValue = GetSensor(name);
        }
        return 0;
    }

    int Get(const string& name, string& returnedValue)
    {
        // If the setting does not exist.
        if(!Find(name))
        {
            returnedValue = "";
            return 1;
        }
        else
        {
            Sensor aux = GetSensor(name);
            if(aux.GetStringValue().compare("") == 0)
            {
                returnedValue = to_string(aux.GetDoubleValue());
            }
            else
            {
                returnedValue = aux.GetStringValue();
            }
        }
        return 0;
    }

    int Set(const string& name, const Sensor& value)
    {
        // If the setting does not exist.
        if(!Find(name))
        {
            return 1;
        }
        else
        {
            for(auto it = sensors.begin(); it != sensors.end(); ++it)
            {
                for(auto it2 = (it->second).begin(); it2 != (it->second).end(); ++it2)
                {
                    if(it2->first == name)
                    {
                        it2->second = value;
                        return 0;
                    }
                }

            }
        }

        return 0;
    }

    int SetPlant(const Plant& _plant)
    {
        plant = _plant;
        return 0;
    }

    string Shovel()
    {
        return("0%Soil has been shovelled!");
    }
    string IrrigateSoil()
    {
        if(!Find("soilHumidity"))
            return "-1%No soilHumidity sensor found!";
        Sensor soilHumidity = GetSensor("soilHumidity");
        if(soilHumidity.GetDoubleValue() < soilHumidity.GetMinValue())
        {
            soilHumidity.SetValue(soilHumidity.GetMaxValue());
            return ("0%Soil has been moistened, current soil humidity: " + to_string(soilHumidity.GetDoubleValue()));
        }
        return "0%";
    }
    string NutrientsInjector()
    {
        string returnMessage = "0%";
        string nutrientsInjected = "";
        map <string, Sensor> groundSensor = sensors[1];
        if(groundSensor.find("phosphorus") == groundSensor.end())
            return "-1%No phosphorus found!";
        if(groundSensor.find("nitrogen") == groundSensor.end())
            return "-1%No nitrogen found!";
        if(groundSensor.find("potassium") == groundSensor.end())
            return "-1%No potassium found!";
        Sensor ph = groundSensor["phosphorus"];
        Sensor n = groundSensor["nitrogen"];
        Sensor p = groundSensor["potassium"];
        if(ph.GetDoubleValue() < ph.GetMinValue())
        {
            ph.SetValue(ph.GetMaxValue());
            nutrientsInjected += "phosphorus, ";
        }
        if(n.GetDoubleValue() < n.GetMinValue())
        {
            n.SetValue(n.GetMaxValue());
            nutrientsInjected += "nitrogen, ";
        }
        if(p.GetDoubleValue() < p.GetMinValue())
        {
            p.SetValue(p.GetMaxValue());
            nutrientsInjected += "potassium, ";
        }
        if(nutrientsInjected.compare("") == 0)
        {
            return returnMessage;
        }
        nutrientsInjected = nutrientsInjected.substr(0, nutrientsInjected.size() - 2);
        returnMessage += "Nutrients injected: " + nutrientsInjected;
        return returnMessage;
    }
    string SolarLamp()
    {
        string returnMessage = "0%";
        if(!Find("luminosity"))
            return "-1%No luminosity sensor found!";
        Sensor luminosity = GetSensor("luminosity");
        if(luminosity.GetDoubleValue() < luminosity.GetMinValue())
        {
            luminosity.SetValue((luminosity.GetMinValue() + luminosity.GetMaxValue())/2);
            returnMessage += "Luminosity has been increased to: " + to_string(luminosity.GetDoubleValue());
        }
        else if(luminosity.GetDoubleValue() > luminosity.GetMaxValue())
        {
            luminosity.SetValue((luminosity.GetMinValue() + luminosity.GetMaxValue())/2);
            returnMessage += "Luminosity has been increased to: " + to_string(luminosity.GetDoubleValue());
        }
        return returnMessage;
    }

    string DisplayPlantData()
    {
        Plant p;
        if(plant == p)
            return "-1%No plant found!";
        string returnMessage = "0%";
        returnMessage += "Plant species: " + plant.GetName() + "\nPlant color: " + plant.GetColor() + "\nPlant height: " + to_string(plant.GetHeight()) + "\nPlant type: " + plant.GetType();

        return returnMessage;
    }
    string DisplayEnvironmentData()
    {
        string returnMessage = "0%";
        /*if(settings.find("airHumidity") == settings.end())
            return "-1%No airHumidity sensor found!";
        returnMessage += "Air humidity: " + to_string(settings["airHumidity"].GetDoubleValue());
        if(settings.find("airTemperature") == settings.end())
            return "-1%No airTemperature sensor found!";
        returnMessage += "Air temperature: " + to_string(settings["airTemperature"].GetDoubleValue());
        if(settings.find("luminosity") == settings.end())
            return "-1%No luminosity sensor found!";
        returnMessage += "Luminosity: " + to_string(settings["luminosity"].GetDoubleValue());
        if(settings.find("soilHumidity") == settings.end())
            return "-1%No soilHumidity sensor found!";
        returnMessage += "Soil humidity: " + to_string(settings["soilHumidity"].GetDoubleValue());
        if(settings.find("soilType") == settings.end())
            return "-1%No soilType sensor found!";
        returnMessage += "Soil type: " + settings["airHumidity"].GetStringValue();
        if(settings.find("soilPh") == settings.end())
            return "-1%No soilPh sensor found!";
        returnMessage += "soilPh: " + to_string(settings["soilPh"].GetDoubleValue());*/
        for (auto it = sensors.begin(); it != sensors.end(); ++it)
        {
            for (auto it2 = (it->second).begin(); it2 != (it->second).end(); ++it2)
            {
                Sensor s = it2->second;
                if(s.GetStringValue().compare("") != 0)
                    returnMessage += "\n" + s.GetName() + ": " + s.GetStringValue();
                else
                    returnMessage += "\n" + s.GetName() + ": " + to_string(s.GetDoubleValue());
            }
        }
        return returnMessage;
    }
    string SoilCompatibility()
    {
        Plant p;
        if(plant == p)
            return "-1%No plant found!";
        if(!Find("soilType"))
            return "-1%No soilType sensor found!";
        if(plant.GetSoil().compare(GetSensor("soilType").GetStringValue()) != 0)
            return "1%Soil Type not suitable for plant!";
        else
            return "0%";
    }
    string SoilStatus()
    {
        bool alert = false;
        string alertMessages = "";
        if(!Find("soilPh"))
            return "-1%No soilPh sensor found!";
        if(!Find("soilHumidity"))
            return "-1%No soilHumidity sensor found!";
        Sensor soilPh = GetSensor("soilPh");
        Sensor soilHumidity = GetSensor("soilHumidity");
        if(soilPh.GetDoubleValue() < soilPh.GetMinValue())
        {
            alert = true;
            alertMessages += "Soil ph under critical levels!";
        }
        else if(soilPh.GetDoubleValue() > soilPh.GetMaxValue())
        {
            alert = true;
            alertMessages += "Soil ph above critical levels!";
        }
        if(soilHumidity.GetDoubleValue() < soilHumidity.GetMinValue())
        {
            alert = true;
            alertMessages += "Soil humidity under critical levels!";
        }
        else if(soilHumidity.GetDoubleValue() > soilHumidity.GetMaxValue())
        {
            alert = true;
            alertMessages += "Soil humidity above critical levels!";
        }
        if(alert)
            return "1%" + alertMessages;
        else
            return "0%";
    }
    string InadequateEnvironment()
    {
        bool alert = false;
        string alertMessages = "";
        if(!Find("temperature"))
            return "-1%No temperature sensor found!";
        if(!Find("humidity"))
            return "-1%No humidity sensor found!";
        Sensor temperature = GetSensor("temperature");
        Sensor humidity = GetSensor("humidity");
        if(temperature.GetDoubleValue() < temperature.GetMinValue())
        {
            alert = true;
            alertMessages += "Temperature under critical levels!";
        }
        else if(temperature.GetDoubleValue() > temperature.GetMaxValue())
        {
            alert = true;
            alertMessages += "Temperature above critical levels!";
        }
        if(humidity.GetDoubleValue() < humidity.GetMinValue())
        {
            alert = true;
            alertMessages += "Humidity under critical levels!";
        }
        else if(humidity.GetDoubleValue() > humidity.GetMaxValue())
        {
            alert = true;
            alertMessages += "Humidity above critical levels!";
        }
        if(alert)
            return "1%" + alertMessages;
        else
            return "0%";
    }
};
}

#endif
