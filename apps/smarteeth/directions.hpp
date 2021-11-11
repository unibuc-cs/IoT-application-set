#pragma once

#include <string>
#include <utility>

enum LedsColor //culorile pe care le ia ledul pentru a stabili in ce directie urmeaza sa mearga utilizatorul
{
    Grey = 1, //nu este aprins
    Blue,     //dreapta
    Purple,   //stanga
    Red       //stop - in cazul sangerarilor, se opreste pentru clatire
};

struct Directions
{
    bool ledValues[8][8];
};

// Intoarce directia care trebuie afisata pe leduri si culoarea lor.
std::pair<LedsColor, Directions> getLedsColorAndDirections();

// Transform culoarea intr-un string.
std::string getLedsColorAsString(LedsColor color);

// Transforma o matrice de pixeli intr-un string.
std::string getDirectionsAsString(Directions directions);
