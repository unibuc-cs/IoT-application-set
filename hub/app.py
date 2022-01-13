#!/usr/bin/python3

from datetime import datetime
from typing import List
from pprint import pprint
from time import sleep

# ------------------------------------------------------------------------------
# Import all the apps
# TODO: this code could be automatically generated
import windwow
from windwow.api import default_api as windwow_default_api
from windwow.api.default_api import DefaultApi as WindwowDefaultApi

def get_windwow_api() -> WindwowDefaultApi:
    print(f"Instanciate API client for windwow")
    configuration = windwow.Configuration(host = f"http://windwow:9080")
    api_client = windwow.ApiClient(configuration)
    return windwow_default_api.DefaultApi(api_client)

import smarttv
from smarttv.api import default_api as smarttv_default_api
from smarttv.api.default_api import DefaultApi as SmarttvDefaultApi

def get_smarttv_api() -> SmarttvDefaultApi:
    print(f"Instanciate API client for smarttv")
    configuration = smarttv.Configuration(host = f"http://smarttv:9080")
    api_client = smarttv.ApiClient(configuration)
    return smarttv_default_api.DefaultApi(api_client)

import smartkettle
from smartkettle.api import default_api as smartkettle_default_api
from smartkettle.api.default_api import DefaultApi as SmartkettleDefaultApi

def get_smartkettle_api() -> SmartkettleDefaultApi:
    print(f"Instanciate API client for smartkettle")
    configuration = smartkettle.Configuration(host = f"http://smartkettle:9080")
    api_client = smartkettle.ApiClient(configuration)
    return smartkettle_default_api.DefaultApi(api_client)

import flowerpower
from flowerpower.api import default_api as flowerpower_default_api
from flowerpower.api.default_api import DefaultApi as FlowerpowerDefaultApi
from flowerpower.model.setting_name import SettingName
from flowerpower.model.settings_object import SettingsObject

def get_flowerpower_api() -> FlowerpowerDefaultApi:
    print(f"Instanciate API client for flowerpower")
    configuration = flowerpower.Configuration(host = f"http://flowerpower:9080")
    api_client = flowerpower.ApiClient(configuration)
    return flowerpower_default_api.DefaultApi(api_client)

import smarteeth
from smarteeth.api import default_api as smarteeth_default_api
from smarteeth.api.default_api import DefaultApi as SmarteethDefaultApi

def get_smarteeth_api() -> SmarteethDefaultApi:
    print(f"Instanciate API client for smarteeth")
    configuration = smarteeth.Configuration(host = f"http://smarteeth:9080")
    api_client = smarteeth.ApiClient(configuration)
    return smarteeth_default_api.DefaultApi(api_client)
# ------------------------------------------------------------------------------


class Environment:
    def __init__(self, rules: List[callable], interval = 5):
        self.rules = rules
        self.now = datetime.now()
        self.interval = interval

        self.data = {
            "windwow": {},
            "smartkettle": {},
            "flowerpower": {},
            "smarteeth": {},
            "smarttv": {},
        }

        self.clients = {
            "windwow": get_windwow_api(),
            "smartkettle": get_smartkettle_api(),
            "flowerpower": get_flowerpower_api(),
            "smarteeth": get_smarteeth_api(),
            "smarttv": get_smarttv_api(),
        }

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
    
    # error here
    #env.data["smarteeth"]["gum_bleeding"] = env.clients["smarteeth"].health_gum_bleeding_get()
    #print ('gum', env.data["smarteeth"]["gum_bleeding"])

    # error here
    temperature_raw = env.clients["flowerpower"].settings_setting_name_get(SettingName('temperature'), _check_return_type=False)
    temperature = float(temperature_raw)
    env.data["flowerpower"]["temperature"] = temperature

    luminosity_raw = env.clients["flowerpower"].settings_setting_name_get(SettingName('luminosity'), _check_return_type=False)
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
    env.clients["windwow"].settings_setting_name_setting_value_post("luminosity", env.data["windwow"]["luminosity"])
    env.clients["flowerpower"].settings_setting_name_setting_value_put(SettingName("luminosity"), env.data["windwow"]["luminosity"])
    print(f"Luminosity changed from {old} to {env.data['windwow']['luminosity']}")

def rule3(env: Environment):
    print("Rule 3")
    luminosity_sensor_id = 3
    threshold = env.settings["plant_lamp_window_treshold"]

    if env.data["windwow"]["luminosity"] < threshold:
        print(f"If luminosity amount is less than the threshold = {threshold}, then turn on the lamp")
        print("Lamp turned on")
        env.clients["flowerpower"].activate_solar_lamp_get()

def rule4(env: Environment):
    print("Rule 4")

    brightness_base = env.settings["tv_base_brightness"]
    
    env.data["smarttv"]["brightness"] = max(
            10 - env.data["windwow"]["luminosity"]/10 + brightness_base,
            brightness_base 
        )
    env.data["smarttv"]["brightness"] = min(env.data["smarttv"]["brightness"], 10)
    env.clients["smarttv"].set_brightness_level_post(int(env.data["smarttv"]["brightness"]))

def rule5(env: Environment):
    print("Rule 5")

env = Environment([
        gather_data,
        rule1,
        rule2,
        rule3,
        rule4,
        rule5,
    ])

if __name__ == "__main__":
    env.run()

