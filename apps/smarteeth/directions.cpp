#include "directions.hpp"

#include "brushing.hpp"
#include "configuration.hpp"
#include "mqtt.hpp"

static void outputBraceletDirection(const std::string &direction)
{
    mqttPublishMessage("bracelet", direction);
}

std::pair<LedsColor, Directions> getLedsColorAndDirections()
{
    const Configuration &config = *getCurrentConfiguration();

    if (isBleeding())
    {
        //dintele sangereaza
        outputBraceletDirection("X");

        Directions stop{{{1, 0, 0, 0, 0, 0, 0, 1},
                         {0, 1, 0, 0, 0, 0, 1, 0},
                         {0, 0, 1, 0, 0, 1, 0, 0},
                         {0, 0, 0, 1, 1, 0, 0, 0},
                         {0, 0, 0, 1, 1, 0, 0, 0},
                         {0, 0, 1, 0, 0, 1, 0, 0},
                         {0, 1, 0, 0, 0, 0, 1, 0},
                         {1, 0, 0, 0, 0, 0, 0, 1}}};

        return std::make_pair(LedsColor::Red, stop);
    }

    int index = getCurrentTooth();

    if ((index == 1 || index == 32) || (index > 1 && index <= 8) || (index >= 25 && index < 32)) //ma aflu la primul dinte de sus sau la ultimul de jos deci trebuie sa merg spre stanga
    {
        Directions matrix{{{0, 0, 0, 0, 1, 0, 0, 0},
                           {0, 0, 0, 0, 0, 1, 0, 0},
                           {0, 0, 0, 0, 0, 0, 1, 0},
                           {1, 1, 1, 1, 1, 1, 1, 1},
                           {0, 0, 0, 0, 0, 0, 1, 0},
                           {0, 0, 0, 0, 0, 1, 0, 0},
                           {0, 0, 0, 0, 1, 0, 0, 0}}};
        outputBraceletDirection("==>");
        return std::make_pair(LedsColor::Purple, matrix);
    }

    if ((index == 16 || index == 17) || (index > 17 && index <= 24) || (index >= 9 && index <= 16)) //ma aflu la ultimul dinte de sus sau la primul de jos, deci dreapta
    {
        Directions matrix{{{0, 0, 0, 1, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 0, 0, 0, 0},
                           {1, 1, 1, 1, 1, 1, 1, 1},
                           {0, 1, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 0, 0},
                           {0, 0, 0, 1, 0, 0, 0, 0}}};
        outputBraceletDirection("<==");
        return std::make_pair(LedsColor::Blue, matrix);
    }

    return std::make_pair(LedsColor::Grey, Directions{});
}

std::string getLedsColorAsString(LedsColor color)
{
    switch (color)
    {
    case LedsColor::Blue:
        return "Blue";
    case LedsColor::Purple:
        return "Purple";
    case LedsColor::Red:
        return "Red";
    default:
        return "Grey";
    }
}

std::string getDirectionsAsString(Directions directions)
{
    std::string returnString;

    for (unsigned j = 0; j < 7; j++)
    {
        for (unsigned k = 0; k < 8; k++)
        {
            if (directions.ledValues[j][k])
                returnString += "*";
            else
                returnString += " ";
        }
        returnString += "\n";
    }

    return returnString;
}
