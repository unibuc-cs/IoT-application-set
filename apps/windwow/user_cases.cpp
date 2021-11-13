#include <algorithm>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <random>


using namespace std;
using json = nlohmann::json;


int main (int argc, char** argv){
  std::ifstream input_json("window_settings_original.json");
  json content_json;
  input_json >> content_json;
  auto& output = content_json["input_buffers"]["settings"]["buffer-tokens"];
  input_json.close();

  int arg, nr = std::rand(), min, max, med, med2;
  string str;

  arg = atoi (argv[1]);

  if (arg % 5 == 0)
  {
    // // luminosity case
    min = 0;
    med = 25;
    max = 100;

    // open curtains
    nr = med + (nr % (max - med + 1));

    // close curtains
    // nr = min + (nr % (med - min + 1));

    str = to_string (nr);
    output[4]["value"] = str;
  }

  if (arg % 5 == 1)
  {
      // // temperature case
      min = 0;
      med = 22;
      med2 = 30;
      max = 100;

      // open window
      nr = med2 + (nr % (max - med2 + 1));

      // semi-open window
      // nr = med + (nr % (med2 - med + 1));

      // close window
      // nr = nr % (med + 1);

      str = to_string (nr);
      output[3]["value"] = str;
  }

  if (arg % 5 == 2)
  {
      // // humidity case
      min = 0;
      med = 50;
      max = 100;

      // close window
      nr = med + (nr % (max - med + 1));

      // open window
      // nr = min + (nr % (med - min + 1));

      str = to_string (nr);
      output[2]["value"] = str;
  }

  if (arg % 5 == 3)
  {
    // // air_quality case
    min = 0;
    med = 50;
    max = 100;

    // open window
    nr = med + (nr % (max - med + 1));

    // close window
    // nr = min + (nr % (med - min + 1));

    str = to_string (nr);
    output[1]["value"] = str;
  }

  if (arg % 5 == 4)
  {
      // // impact case
      min = 0;
      med = 25;
      max = 100;

      // IMPACT
      nr = med + (nr % (max - med + 1));

      // SAFE
      // nr = min + (nr % (med - min + 1));

      str = to_string (nr);
      output[0]["value"] = str;
  }

  // write json output
  std::ofstream output_json ("window_settings.json");
  output_json << std::setw(4) << content_json << std::endl;
  output_json.close();

  return 0;
}
