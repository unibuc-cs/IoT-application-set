#!/usr/bin/python3

from datetime import datetime
from typing import List
from pprint import pprint
from time import sleep

# Import all default things
from mergedclients.all import *

# Additional imports
from flowerpower.model.setting_name import SettingName
from flowerpower.model.settings_object import SettingsObject

class Environment:
    def __init__(self, rules: List[callable], interval = 5):
        self.rules = rules
        self.now = datetime.now()
        self.interval = interval

        self.data = {k: {} for k in ALL_APPS}
        self.data["windwow"]["hot_day"] = False

        self.clients = get_all_clients_apis()

        self.settings = {
            "plant_lamp_window_treshold": 10,
            "tv_base_brightness": 1,
        }

    def run(self):
        print("Hub app started.")
        sleep(3)
        while True:
            self.now = datetime.now()

            for rule in self.rules:
                rule(self)

            self.print_env()
            sleep(self.interval)

    def run_simple(self):
        for rule in self.rules:
            rule(self)

    def print_env(self):
        print(f"New environment at: f{self.now}")
        pprint(self.data)
        print()

# Collect data from sensors
def gather_data(env: Environment):
    print("Gather data")
    temperature_raw = env.clients["windwow"].settings_setting_name_get("temperature", _check_return_type=False)
    env.data["windwow"]["temperature"] = float(temperature_raw[14:])

    luminosity_raw = env.clients["windwow"].settings_setting_name_get("luminosity", _check_return_type=False)
    env.data["windwow"]["luminosity"] = float(luminosity_raw[14:])

    temperature_raw = env.clients["flowerpower"].settings_setting_name_get(SettingName('temperature'), _check_return_type=False)
    temperature = float(temperature_raw)
    env.data["flowerpower"]["temperature"] = temperature

    luminosity_raw = env.clients["flowerpower"].settings_setting_name_get(SettingName('luminosity'), _check_return_type=False)
    print("got", luminosity_raw)
    luminosity = float(luminosity_raw)
    env.data["flowerpower"]["luminosity"] = luminosity

# If window temperature is X, then set Kettle RPM to X.
def rule1(env: Environment):
    print("Rule 1")
    print(f"Window temperature is f{env.data['windwow']['temperature']}")
    env.clients["smartkettle"].stir_liquid_rpm_get(int(env.data["windwow"]["temperature"]))
    env.data["smartkettle"]["rpm"] = int(env.data["windwow"]["temperature"])
    print(f"Kettle RPM was set to {int(env.data['windwow']['temperature'])}")

# If plant temperature is above 30 degrees, reduce the luminosity of the window to half
def rule2(env: Environment):
    print("Rule 2")

    if env.data["flowerpower"]["temperature"] < 30:
        print("Nothing to do")
        return

    old = env.data["windwow"]["luminosity"]
    env.data["windwow"]["luminosity"] /= 2
    env.data["flowerpower"]["luminosity"] = env.data["windwow"]["luminosity"]
    old2 = env.data["flowerpower"]["temperature"]
    env.data["flowerpower"]["temperature"] *= 0.70
    env.data["flowerpower"]["temperature"] = env.data["flowerpower"]["temperature"]

    env.clients["windwow"].settings_setting_name_setting_value_post("luminosity", str(int(env.data["windwow"]["luminosity"])), _check_input_type=False, _host_index=0)
    env.clients["flowerpower"].settings_setting_name_setting_value_put(SettingName("luminosity"), str(env.data["windwow"]["luminosity"]))
    env.clients["flowerpower"].settings_setting_name_setting_value_put(SettingName("temperature"), str(env.data["flowerpower"]["temperature"]))
    print(f"Luminosity changed from {old} to {env.data['windwow']['luminosity']}")
    print(f"Temperature changed from {old2} to {env.data['flowerpower']['temperature']}")

# If the window's luminosity is less than X, turn on the lamp
def rule3(env: Environment):
    print("Rule 3")
    luminosity_sensor_id = 3
    threshold = env.settings["plant_lamp_window_treshold"]

    # // BUG TO UNPATCH don't check window temperature
    if env.data["windwow"]["luminosity"] < threshold and env.data["windwow"]["temperature"] < 30:
        print(f"If luminosity amount is less than the threshold = {threshold}, then turn on the lamp")
        print("Lamp turned on")
        env.clients["flowerpower"].activate_solar_lamp_get()

# Set the brightness of the TV based on the luminosity level of the window
def rule4(env: Environment):
    print("Rule 4")

    brightness_base = env.settings["tv_base_brightness"]
    
    env.data["smarttv"]["brightness"] = max(
            10 - env.data["windwow"]["luminosity"]/10 + brightness_base,
            brightness_base 
        )
    # // BUG TO UNPATCH forget to call min
    env.data["smarttv"]["brightness"] = min(env.data["smarttv"]["brightness"], 10)
    env.clients["smarttv"].set_brightness_level_post(int(env.data["smarttv"]["brightness"]))

# If it's cold outside, increase the temperature in the kettle by 3 degrees for every degree under 10 at window's thermometer
def rule5(env: Environment):
    print("Rule 5")

    target_temp = 40
    # // BUG TO UNPATCH forgot to add abs
    dif = abs(env.data["windwow"]["temperature"] - 10)
    if env.data["windwow"]["temperature"] < 10:
        target_temp = dif * 3 + target_temp

    resp = env.clients["smartkettle"].warm_liquid_temperature_scale_get(
        target_temp,
        'celsius',
    )
    
    msg1 = 'The water is warming at '
    msg2 = ' degrees'
    m = resp['message']
    idx1 = m.index(msg1) + len(msg1)
    idx2 = m.index(msg2)
    env.data["smartkettle"]["temperature"] = float(m[idx1:idx2])

env = Environment([
        gather_data,
        rule1,
        #rule2, # This is broken too
        rule3,
        #rule4, # There is some bug
        rule5,
    ])

if __name__ == "__main__":
    env.run()

