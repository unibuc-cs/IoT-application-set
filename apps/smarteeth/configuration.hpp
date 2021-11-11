#pragma once

#include <string>
#include <vector>

enum class ProgramType
{
    Full_Clean = 1,
    Only_Upper,
    Only_Lower,
    Warning_Safe_Teeths_Full_Clean
};

struct Configuration
{
    std::string name;
    int age;
    ProgramType program;
    /*
    Teeth schema
    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
    32 31 30 29 28 27 26 25 24 23 22 21 20 19 18  17
    Source: https://ibb.co/KhfB2Kp
    */
    std::vector<int> teeth;
};

void setConfiguration(const std::string &name, Configuration config);
const Configuration &getConfiguration(const std::string &name);
std::string getProgramName(ProgramType program);

void loadConfigurations();
void saveConfigurations();
