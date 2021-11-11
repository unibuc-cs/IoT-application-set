#include "configuration.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "json.hpp"

namespace fs = std::filesystem;

/// Maps names to configuration objects
static std::unordered_map<std::string, Configuration> configs;

static const std::string CONFIG_DIR = "configurations";

void setConfiguration(const std::string &name, Configuration config)
{
    //ATENTIE!! Numele este unic, daca se primesc alte setari cu acelasi nume se considera update.
    configs.insert_or_assign(name, config);
}

const Configuration &getConfiguration(const std::string &name)
{
    return configs.at(name);
}

void to_json(json &j, const Configuration &c)
{
    j = json{{"name", c.name}, {"age", c.age}, {"program", c.program}, {"teeth", c.teeth}};
}

void from_json(const json &j, Configuration &c)
{
    j.at("name").get_to(c.name);
    j.at("age").get_to(c.age);
    j.at("program").get_to(c.program);
    j.at("teeth").get_to(c.teeth);
}

std::string getProgramName(ProgramType program)
{
    switch (program)
    {
    case ProgramType::Full_Clean:
        return "Full_Clean";
    case ProgramType::Only_Upper:
        return "Only Upper";
    case ProgramType::Only_Lower:
        return "Only Lower";
    case ProgramType::Warning_Safe_Teeths_Full_Clean:
        return "Warning Safe Teeth Full Clean";
    default:
        return "Unknown Config";
    }
}

void loadConfigurations()
{
    std::string pathConfig = fs::current_path().generic_string() + "/" + CONFIG_DIR;

    for (const auto &fileName : fs::directory_iterator(pathConfig))
    {
        if (fileName.path().extension() != ".json")
        {
            continue;
        }

        std::ifstream fin(fileName.path());
        std::string buffer;
        std::getline(fin, buffer);
        const Configuration config = json::parse(buffer);
        setConfiguration(config.name, config);

        std::cout << "Loaded saved config with name '" << config.name << "'\n";

        fin.close();
        //aici e ca si cum ai primi
    }
}

void saveConfigurations()
{
    std::string pathConfigDir = fs::current_path().generic_string() + "/" + CONFIG_DIR + "/";
    for (const auto &element : configs)
    {
        std::string pathConfig = pathConfigDir + element.first + ".json";
        json configJson = element.second;

        std::ofstream fout(pathConfig);
        fout << configJson.dump();
        fout.close();
    }
}
