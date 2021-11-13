#pragma once
#include <algorithm>
#include <stdio.h>
#include <chrono>

#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
#include <signal.h>
#include <fstream>
#include <set>
#include <map>
#include <time.h>

using namespace std;
using namespace Pistache;
using namespace chrono;

namespace SmartTvN
{
    class Channel{
        private:
            string nume;
            string gen;
            int varstaMinima;
            int varstaMaxima;
        
        public:
            Channel(string nume, string gen, int varstaMinima, int varstaMaxima){
                this->nume = nume;
                this->gen = gen;
                this->varstaMinima = varstaMinima;
                this->varstaMaxima = varstaMaxima;
            }
            string getNume(){
                return this->nume;
            }

            string getGen(){
                return this->gen;
            }

            int getVarstaMinima(){
                return this->varstaMinima;
            }

            int getVarstaMaxima(){
                return this->varstaMaxima;
            }

            void setNume(string nume){
                this->nume = nume;
            }

            void setGen(string gen){
                this->gen = gen;
            }

            void setVarstaMinima(int varstaMinima){
                this->varstaMinima = varstaMinima;
            }

            void setVarstaMaxima(int varstaMaxima){
                this->varstaMaxima = varstaMaxima;
            }
    };

    class User{
        private:
            string username;
            int varsta;
            vector<Channel*> listaCanale;
        
        public:
            User(string nume, int varsta){
                this->username = nume;
                this->varsta = varsta;
                this->listaCanale = vector<Channel*>();
            }

            string getUsername(){
                return this->username;
            }

            int getVarsta(){
                return this->varsta;
            }

            vector<Channel*> getListaCanale(){
                return this->listaCanale;
            }

            void setUsername(string username){
                this->username = username;
            }

            void setVarsta(int varsta){
                this->varsta = varsta;
            }

            void setListaCanale(vector<Channel*> canale){
                this->listaCanale = canale;
            }

            void addChannel(Channel* canal){
                this->listaCanale.push_back(canal);
            }
    };

    class Recommandation{
    private:
        string username;
        string canal;
        string gen;
        int minute;
    public:
        Recommandation(string username, string canal, string gen, int minute){
            this->username = username;
            this->canal = canal;
            this->gen = gen;
            this->minute = minute;
        }

        string getGen(){
            return this->gen;
        }
        string getUsername(){
            return this->username;
        }

        int getMinute(){
            return this->minute;
        }
    };

    class SmartTv
    {

    private:
        time_point<high_resolution_clock> start_time;
        time_point<high_resolution_clock> last_time;
        int idle_duration = 10000;
        int threshold_recommandation = 200;
        vector<Channel*> all_channels;
        vector<User*> users;
        vector<Recommandation*> rec;
        int brightness = 100;

    public:
        SmartTv();
        ~SmartTv();
        int getTimeFromStart();
        int getTimeFromLast();
        int getIdleDuration();
        void restartTimeFromLast();
        void setIdleDuration(int idle_duration);
        void add_channels();
        void add_users();
        vector<string> getSuggestions(string gen, int varsta);
        void add_user(string nume, int varsta);
        vector<User*> getUsers();
        vector<Channel*>getChannels();
        void add_channel_to_user(string nume, string canal);
        Channel* getChannel(string nume);
        void add_rec();
        map<std::string, int> getGenres(string nume);
        vector<std::pair<std::string, std::string>> getGenRec(string nume);
        int getBrightness();
        void setBrightness(int outside_brighness);
        string notifyUserDistance(int size, float current_distance);
        void write_users();


    };


    vector<Channel*> SmartTv::getChannels(){
        return this->all_channels;
    }

    void SmartTv::write_users(){
        std::ofstream file("data_files/accounts.csv");
        for(int i = 0; i < users.size(); i++){
            file << users[i]->getUsername() << "," << users[i]->getVarsta();
            if(users[i]->getListaCanale().size()){
                file << ",";
                string output = "";
                for(int j = 0; j < users[i]->getListaCanale().size(); j++){
                    output = output + users[i]->getListaCanale()[j]->getNume() + ";";
                }

                output.pop_back();
                file << output << "\n";
            }
        }

        file.close();
    }

    SmartTv::~SmartTv(){
        this->write_users();
    }
    
    map<std::string, int> SmartTv::getGenres(string nume){

        map<std::string, int> genre_hist;
        for(int i = 0; i < rec.size(); i++){
            if (rec[i]->getUsername() == nume){
                std::string genre = rec[i]->getGen();
                int minute = rec[i]->getMinute();
                if (genre_hist.find(genre) != genre_hist.end()){
                    genre_hist[genre] += minute;
                }
                else{
                    genre_hist[genre] = minute;
                }
            }
        }

        return genre_hist;
    }

    vector<std::pair<std::string, std::string>> SmartTv::getGenRec(string nume){
        map<std::string, int> genre_hist = this->getGenres(nume);
        vector<string>genre_vec;

        map<string, int>::iterator it;
        for(it = genre_hist.begin(); it != genre_hist.end(); it++){
            auto genre = it->first;
            auto time = it->second;

            if (time > this->threshold_recommandation){
                genre_vec.push_back(genre);

            }
        }

        vector<std::pair<std::string, std::string>> new_rec;


        for(int i = 0; i < genre_vec.size(); i++){
            for(int j = 0; j < all_channels.size(); j++){
                if (genre_vec[i] == all_channels[j]->getGen()){
                    new_rec.push_back(make_pair(all_channels[j]->getGen(), all_channels[j]->getNume()));
                }
            }
        }


        return new_rec;

    }

    void SmartTv::add_rec(){
        std::ifstream file("data_files/dateIstoricVizionari.csv");
        std::string str;

        vector<Recommandation*> rec_array;
        while(std::getline(file, str)){
            stringstream s_stream(str);
            vector<string> result;
            while(s_stream.good()){
                string substr;
                getline(s_stream, substr, ',');
                result.push_back(substr);
            }

            std::string user = result[0];
            std::string canal = result[1];
            std::string gen = result[2];
            int minute = std::stoi(result[3]);

            Recommandation* new_rec = new Recommandation(user, canal, gen, minute);
            rec_array.push_back(new_rec);
            
        }

        this->rec = rec_array;
        file.close();
    }

    Channel* SmartTv::getChannel(string nume){
        for (int i = 0; i < all_channels.size(); i++){
            if (all_channels[i]->getNume() == nume){
                return all_channels[i];
            }
        }
    }

    void SmartTv::add_channel_to_user(string nume, string canal){
        for(int i = 0; i < users.size(); i++){
            if (users[i]->getUsername() == nume){
                users[i]->addChannel(this->getChannel(canal));
            }
        }
    }

    vector<User*> SmartTv::getUsers(){
        return this->users;
    }

    void SmartTv::add_user(string nume, int varsta){
        User* new_user = new User(nume, varsta);
        users.push_back(new_user);
    }

    void SmartTv::add_channels(){
        std::ifstream file("data_files/dateTV.csv");
        std::string str;

        vector<Channel*> channels;
        while(std::getline(file, str)){
            stringstream s_stream(str);
            vector<string> result;
            while(s_stream.good()){
                string substr;
                getline(s_stream, substr, ',');
                result.push_back(substr);
            }

            std::string nume = result[0];
            std::string gen = result[1];

            std::string interval = result[2];
            std::string delimiter = "-";
            std::string first_number = interval.substr(0, interval.find(delimiter));
            interval.erase(0, interval.find(delimiter) + delimiter.length());
            int varstaMinima = std::stoi(first_number);
            int varstaMaxima = std::stoi(interval);

            Channel* new_channel = new Channel(nume, gen, varstaMinima, varstaMaxima);
            channels.push_back(new_channel);
            
        }


        this->all_channels = channels;
        file.close();
    }

    void SmartTv::add_users(){
        std::ifstream file("data_files/accounts.csv");
        std::string str;

        vector<User*> new_users;
        while(std::getline(file, str)){
            stringstream s_stream(str);
            vector<string> result;
            while(s_stream.good()){
                string substr;
                getline(s_stream, substr, ',');
                result.push_back(substr);
            }

            std::string nume = result[0];
            int varsta = std::stoi(result[1]);

            User *new_user = new User(nume, varsta);

            if(result.size() == 3){

                std::string listChannelsstring = result[2];
                stringstream s_stream1(listChannelsstring);
                while(s_stream1.good()){
                    string canal;
                    getline(s_stream1, canal, ';');


                    new_user->addChannel(this->getChannel(canal));


                }
            }
            this->users.push_back(new_user);
            
        }

        file.close();
    }


    vector<string> SmartTv::getSuggestions(string gen, int varsta){
        vector<string> suggestions;
        for(int i = 0; i < all_channels.size(); i++){
            if (all_channels[i]->getGen() == gen && all_channels[i]->getVarstaMinima() <= varsta && all_channels[i]->getVarstaMaxima() >= varsta){
                suggestions.push_back(all_channels[i]->getNume());
            }
        }

        return suggestions;
    }

    // get the time (in seconds) since the TV has started
    int SmartTv::getTimeFromStart()
    {
        return duration_cast<seconds>(high_resolution_clock::now() - start_time).count();
    }

    // get the time (in seconds) since the last action on the TV
    int SmartTv::getTimeFromLast()
    {
        return duration_cast<seconds>(high_resolution_clock::now() - last_time).count();
    }

    void SmartTv::restartTimeFromLast()
    {
        last_time = high_resolution_clock::now();
    }

    void SmartTv::setIdleDuration(int idle_duration)
    {
        this->idle_duration = idle_duration;
    }
    
    int SmartTv::getIdleDuration()
    {
        return idle_duration;
    }
    
    void SmartTv::setBrightness(int outside_brightness){

        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);

        int hour=aTime->tm_hour;
        if(hour > 8 && hour < 17){
            if(outside_brightness < 25){
                this->brightness = 25;
            }
            else if(outside_brightness >=25  && outside_brightness < 50){
                this->brightness = 50;
            }
            else if(outside_brightness >=50  && outside_brightness < 75){
                this->brightness = 75;
            
            }
            else if(outside_brightness >=75  && outside_brightness < 100){
                this->brightness = 100;
            }
        }
        else{
            if(outside_brightness < 25){
                this->brightness = 5;
            }
            else if(outside_brightness >=25  && outside_brightness < 50){
                this->brightness = 30;
            }
            else if(outside_brightness >=50  && outside_brightness < 75){
                this->brightness = 55;
            }
            else if(outside_brightness >=75  && outside_brightness < 100){
                this->brightness = 80;
            }
        }
      
       
    }
    
    int SmartTv::getBrightness(){
        return brightness;
    }

    string SmartTv::notifyUserDistance(int size, float current_distance){
        string message = "You are ok.";

        if(size <=80){
            if(current_distance < 1.5){
                message = "You are too close. You need to between 1.5 and 2.5 m away from the tv for your given tv size.";
            }
        }
        else if(size > 80 && size <= 107){
            if(current_distance < 2.5){
                message = "You are too close. You need to be between 2.5 and 3.5 m away from the tv for your given tv size.";
            }
        }
        else if( size > 107 && size <= 120){
            if(current_distance < 3.5){
                message = "You are too close. You need to be between 3.5 and 4.5 m away from the tv for your given tv size.";
            }
        }
         else if( size > 120){
            if(current_distance < 5){
                message = "You are too close. You need to beat least 5 m away from the tv for your given tv size.";
            }
        }
        return message;
    }

    SmartTv::SmartTv()
    {
        start_time = high_resolution_clock::now();
        last_time = high_resolution_clock::now();
        this->add_channels();
        this->add_rec();
        this->add_users();
    }
}