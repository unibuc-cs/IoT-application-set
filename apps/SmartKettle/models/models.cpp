#include <nlohmann/json.hpp>

//
// Created by stalma on 20.05.2021.
//


using namespace std;


using json = nlohmann::json;

class Temperature {

private:
    string temperature;
    string scale;


public:

    void setTemperature(string temp) {
        this->temperature = temp;
    }

    void setScale(string scale) {
        this->scale = scale;
    }

    string getTemperature() const { return this->temperature; }

    string getScale() const { return this->scale; }


};


class TemperatureThreshold {
private:
    Temperature actualTemperature;
    Temperature setTemperature;
};

class KettleScheduler {
private:
    Temperature temperature;
    string hour;
    bool recurrent;

public:
    void setRecurrent(bool isrecurrent) {
        this->recurrent = isrecurrent;
    }

    void setHour(string hour) {
        this->hour = hour;
    }

    void setTemperature(const Temperature &t) {
        temperature.setTemperature(t.getTemperature());
        temperature.setScale(t.getScale());
    }

    Temperature getTempInfo() const {
        return this->temperature;
    }

    string getHour() const {
        return this->hour;
    }

    bool getIsRecurrent() const {
        return this->recurrent;
    }
};


class TeaInformation {
private:
    bool keepWarm;
    Temperature optimalTemperature;
    // time in minutes
    long time;

public:

    void setWarm(bool iswarm) {
        this->keepWarm = iswarm;
    }

    void setTime(long time) {
        this->time = time;
    }

    void setTemperature(const Temperature &t) {
        optimalTemperature.setTemperature(t.getTemperature());
        optimalTemperature.setScale(t.getScale());
    }

    Temperature getTempInfo() const {
        return this->optimalTemperature;
    }

    long getTime() const {
        return this->time;
    }

    bool getWarm() const {
        return this->keepWarm;
    }


};

class InfoMessage {

private:
    string message;
    string timestamp;


public:

    void setMessage(string msg) {
        this->message = msg;
    }

    void setTimeStamp(string tmp) {
        this->timestamp = tmp;
    }

    string getMessage() const {
        return this->message;
    }

    string getTimeStamp() const {

        return this->timestamp;
    }
};


class ViscosityInfo {
private:

    int lowerBound;
    string temperature;
public:
    void setLowerBound(int lb) {
        this->lowerBound = lb;
    }

    void setTemperature(string tmp) {
        this->temperature = tmp;
    }

    int getLowerBound() const {
        return this->lowerBound;
    }

    string getTemperature() const {

        return this->temperature;
    }


};

void to_json(json &j, const Temperature &temp) {
    j = json{{"temperature", temp.getTemperature()},
             {"scale",       temp.getScale()}};
}

void from_json(const json &j, Temperature &temp) {

    temp.setTemperature(j.at("temperature"));
    temp.setScale(j.at("scale"));
}

void to_json(json &j, const InfoMessage &temp) {
    j = json{{"message",   temp.getMessage()},
             {"timestamp", temp.getTimeStamp()}};
}

void from_json(const json &j, InfoMessage &temp) {

    temp.setMessage(j.at("message"));
    temp.setTimeStamp(j.at("timestamp"));
}

void to_json(json &j, const ViscosityInfo &viscosityInfo) {
    j = json{{"threshold",   viscosityInfo.getLowerBound()},
             {"temperature", viscosityInfo.getTemperature()}};
}

void from_json(const json &j, ViscosityInfo &viscosityInfo) {

    viscosityInfo.setLowerBound(j.at("threshold"));
    viscosityInfo.setTemperature(j.at("temperature"));
}


void to_json(json &j, const TeaInformation &tea) {
    j = json{{"keepWarm",    tea.getWarm()},
             {"temperature", json(tea.getTempInfo())},
             {"time",        tea.getTime()}};
}

void from_json(const json &j, TeaInformation &tea) {

    tea.setTemperature(j.at("temperature").get<Temperature>());
    tea.setTime(j.at("time"));
    tea.setWarm(j.at("keepWarm"));
}

void to_json(json &j, const KettleScheduler &scheduler) {
    j = json{{"recurrent",   scheduler.getIsRecurrent()},
             {"temperature", json(scheduler.getTempInfo())},
             {"hour",        scheduler.getHour()}};
}

void from_json(const json &j, KettleScheduler &scheduler) {

    scheduler.setTemperature(j.at("temperature").get<Temperature>());
    scheduler.setHour(j.at("hour"));
    scheduler.setRecurrent(j.at("recurrent"));
}

