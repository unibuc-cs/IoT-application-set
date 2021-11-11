#pragma once

#include <string>
#include <vector>

struct Configuration;

// Conditiile verificate inaintea periajului. Temperatura maxima este cu 7
// grade mai mica decat temperatura la care se pot produce arsuri ale pielii.
// Cand umiditatea din aer scade sub 20%, gura se usuca, fiind necesar sa
// fie umezita periuta.
struct Conditions
{
    int toothpasteWeight;
    int temperature;
    int humidity;
};

struct BrushingTimeReport
{
    int area;
    int time;
    bool sufficientTime;
};

void setConditions(const std::string &name, int value);
// Verificarea conditiilor dinaintea periajului.
void checkConditions();

void startBrushing(const Configuration *configuration);
void stopBrushing();

const Configuration *getCurrentConfiguration();

// Intoarce indicele dintelui periat in acest moment.
int getCurrentTooth();

void signalTartrum();
void signalBleeding();

bool isBleeding();

// Cand periuta este mutata, retine ce durata a avut periajul
// pe zona precedenta.
void moveBrush();

// Functia este apelata impreuna cu moveBrush cand este detectata miscare.
// Din momentul in care periuta este mutata pe o zona anume, numara timpul
// de periaj si anunta utilizatorul cand poate muta periuta.
bool checkBrushing();

// Aici anunta utilizatorul pe care zone ar fi trebuit insistat dupa
// incetarea periajului.
std::vector<BrushingTimeReport> checkBrushingTime();
