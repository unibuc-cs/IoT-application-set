#include <algorithm>
#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
#include <signal.h>

using namespace std;
using namespace Pistache;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::map; using std::copy;


void printCookies(const Http::Request& req) {
    auto cookies = req.cookies();
    std::cout << "Cookies: [" << std::endl;
    const std::string indent(4, ' ');
    for (const auto& c: cookies) {
        std::cout << indent << c.name << " = " << c.value << std::endl;
    }
    std::cout << "]" << std::endl;
}

template<typename Map>
void PrintMap(Map& m)
{
    cout << "[ ";
    for (auto &item : m) {
        cout << item.first << ":" << item.second << " ";
    }
    cout << "]\n";
}

// Defining the class of the Window. It should model the entire configuration of the Window
class Window {
    public:
        explicit Window() {

            nr_settings = 5; nr_states = 5;

            settings[0].name = "luminosity";
            settings[1].name = "temperature";
            settings[2].name = "humidity";
            settings[3].name = "air_quality";
            settings[4].name = "impact";

            userSettings[0].name = "username";
            userSettings[1].name = "password";
            userSettings[2].name = "phonenumber";

            userSettings[0].value = "";
            userSettings[1].value = "";
            userSettings[2].value = "";
            

            for (int i = 0; i < nr_settings; i++){
                settings[i].value = 0;
            }

            states[0].name = "windows_open";
            states[1].name = "windows_semi_open";
            states[2].name = "windows_closed";
            states[3].name = "curtains_open";
            states[4].name = "alerted";

            for (int i = 0; i < nr_states; i++){
                states[i].value = false;
            }
         }

         int getStateValue(std::string name){
            for(int i = 0; i < nr_states; i++) {
                if(states[i].name == name) {
                    return states[i].value;
                }
            }
            return -1;
         }

         map<string, int> getActualizedStateDictWindow(){
            return actualized_state_dict;
         }

         void setActualizedStateDictWindow(map<string, int> my_dict){
            actualized_state_dict = my_dict;
         }

        int setUserSetting(std::string name, std::string value){
            bool pass = false;
            for(int i = 0; i < 3; i++){
                if(name == userSettings[i].name){
                    userSettings[i].value = value;
                    return 1;
                }
            }
            return 0;
        }

        // Setting the value for one settings
        int setSetting(std::string name, std::string value){
            bool pass = false;
            vector<int> changed_state_copy;
            for(int i = 0; i < changed_state.size(); i++){
                changed_state_copy.push_back(changed_state[i]);
            }

            for (int i = 0; i < nr_settings; i++) {
                if (name == settings[i].name) {
                    settings[i].value = std::stod(value);
                    if(settings[i].name == "luminosity") {
                        if(settings[i].value > 25.0) {
                            if(changed_state[3] % 2 == 0) {
                                // START FAKE BUG
                                volatile int *p = nullptr;
                                p[50] = 0xdeadbeef;
                                // END FAKE BUG

                                changed_state[3] += 1;
                                actualized_state_dict["curtains_open"] = 1;
                            }
                        } else {
                            if(changed_state[3] % 2 == 1){
                                changed_state[3] += 1;
                                actualized_state_dict["curtains_open"] = 0;
                            }
                        }
                    } else if (settings[i].name == "temperature") {
                        if(settings[i].value >= 30.0) {
                            if(changed_state[1] % 2 == 1) {
                                changed_state[1] += 1;
                                actualized_state_dict["windows_semi_open"] = 0;
                            }
                            if(changed_state[2] % 2 == 1) {
                                changed_state[2] += 1;
                                actualized_state_dict["windows_closed"] = 0;
                            }
                            if(changed_state[0] % 2 == 0 && changed_state[1] % 2 == 0 && changed_state[2] % 2 == 0) {
                                changed_state[0] += 1;
                                actualized_state_dict["windows_open"] = 1;
                            }
                        } else if (22.0 <= settings[i].value && settings[i].value < 30.0) {
                            if(changed_state[0] % 2 == 1) {
                                changed_state[0] += 1;
                                actualized_state_dict["windows_open"] = 0;
                            }
                            if(changed_state[2] % 2 == 1) {
                                changed_state[2] += 1;
                                actualized_state_dict["windows_closed"] = 0;
                            }
                            if(changed_state[1] % 2 == 0 && changed_state[0] % 2 == 0 && changed_state[2] % 2 == 0){
                                changed_state[1] += 1;
                                actualized_state_dict["windows_semi_open"] = 1;
                            }
                        } else {
                            if(changed_state[0] % 2 == 1) {
                                changed_state[0] += 1;
                                actualized_state_dict["windows_open"] = 0;
                            }
                            if(changed_state[1] % 2 == 1) {
                                changed_state[1] += 1;
                                actualized_state_dict["windows_semi_open"] = 0;
                            }
                            if(changed_state[2] % 2 == 0 && changed_state[0] % 2 == 0 && changed_state[1] % 2 == 0){
                                changed_state[2] += 1;
                                actualized_state_dict["windows_closed"] = 1;
                            }
                        }
                    } else if (settings[i].name == "humidity") {
                        if(settings[i].value >= 50.0) {
                            if(changed_state[0] % 2 == 1) {
                                changed_state[0] += 1;
                                actualized_state_dict["windows_open"] = 0;
                            }
                            if(changed_state[1] % 2 == 1) {
                                changed_state[1] += 1;
                                actualized_state_dict["windows_semi_open"] = 0;
                            }
                            if(changed_state[2] % 2 == 0) {
                                changed_state[2] += 1;
                                actualized_state_dict["windows_closed"] = 1;
                            }
                        } else {
                            if(changed_state[2] % 2 == 1) {
                                changed_state[2] += 1;
                                actualized_state_dict["windows_closed"] = 0;
                                if(changed_state[0] % 2 == 0) {
                                    changed_state[0] += 1;
                                    actualized_state_dict["windows_open"] = 1;
                                }
                                if(changed_state[1] % 2 == 1) {
                                    changed_state[1] += 1;
                                    actualized_state_dict["windows_semi_open"] = 0;
                                }
                            }
                        }
                    } else if (settings[i].name == "air_quality") {
                        if(settings[i].value <= 50.0) {
                            if(changed_state[0] % 2 == 1) {
                                changed_state[0] += 1;
                                actualized_state_dict["windows_open"] = 0;
                            }
                            if(changed_state[1] % 2 == 1) {
                                changed_state[1] += 1;
                                actualized_state_dict["windows_semi_open"] = 0;
                            }
                            if(changed_state[2] % 2 == 0) {
                                changed_state[2] += 1;
                                actualized_state_dict["windows_closed"] = 1;
                            }
                        } else {
                            if(changed_state[2] % 2 == 1) {
                                changed_state[2] += 1;
                                actualized_state_dict["windows_closed"] = 0;
                                if(changed_state[0] % 2 == 0) {
                                    changed_state[0] += 1;
                                    actualized_state_dict["windows_open"] = 1;
                                }
                                if(changed_state[1] % 2 == 1) {
                                    changed_state[1] += 1;
                                    actualized_state_dict["windows_semi_open"] = 0;
                                }
                            }
                        }
                    } else if (settings[i].name == "impact") {
                        if(settings[i].value > 25.0) {
                            if(changed_state[4] % 2 == 0) {
                                changed_state[4] += 1;
                                actualized_state_dict["alerted"] = 1;
                            }
                        } else {
                            if(changed_state[4] % 2 == 1) {
                                changed_state[4] += 1;
                                actualized_state_dict["alerted"] = 0;
                            }
                        }
                    }

                    for(int j = 0; j< changed_state.size(); j++){
                        if(changed_state[j] != changed_state_copy[j]){
                            return 2;
                        }
                    }
                    return 1; // no change made to any state
                }
            }
            return 0; // error
        }

        int setState(std::string name, std::string value){

            for (int i = 0; i < nr_states; i++) {
                if (name == states[i].name) {
                    if (value == "1" || value == "true")
                        states[i].value = true;
                    else
                        states[i].value = false;
                    return 1;
                }
            }
            return 0;
        }
        // Getter
        string get(std::string name){

            for (int i = 0; i < nr_settings; i++)
                if (name == settings[i].name){
                    string val = std::to_string(settings[i].value);
                    for (int j = 0; j < 4; j++)
                        val.pop_back();
                    return val;
                }
            return "";
        }

        vector<int> getChangedState(){
            return changed_state;
        }

    private:
        // Defining and instantiating settings.
        int nr_settings, nr_states;

        struct doubleSetting{
            std::string name;
            double value;

        } settings[5];

        struct stringSetting{
            std::string name;
            std::string value;
        } userSettings[3];

        struct boolState{
            std::string name;
            double value;

        } states[5];

        vector<int> changed_state {0, 0, 0, 0, 0};

        map<string, int> actualized_state_dict = {{"windows_open",0}, {"windows_semi_open",0}, {"windows_closed",0}, {"curtains_open",0}, {"alerted",0}};

        // actualized_state_dict["windows_open"] = 0;
        // actualized_state_dict["windows_semi_open"] = 0;
        // actualized_state_dict["windows_closed"] = 0;
        // actualized_state_dict["curtains_open"] = 0;
        // actualized_state_dict["alerted"] = 0;

};
