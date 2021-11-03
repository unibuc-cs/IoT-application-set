import sys
import threading
from datetime import datetime
import flask
from pprint import pprint
from time import sleep

# Import all the apps
import windwow
from windwow.api import default_api as windwow_default_api
import smarttv
from smarttv.api import default_api as smarttv_default_api
import smartkettle
from smartkettle.api import default_api as smartkettle_default_api
import flowerpower
from flowerpower.api import default_api as flowerpower_default_api
 
# Hostnames (inside docker) are the same as client libs names
def get_api_instance(lib, api):
    print(f"Instanciate API client for {lib.__name__}")
    configuration = lib.Configuration(host = f"http://{lib.__name__}:9080")
    api_client = lib.ApiClient(configuration)
    return api.DefaultApi(api_client)

windwow_api_instance = get_api_instance(windwow, windwow_default_api)
smartkettle_api_instance = get_api_instance(smartkettle, smartkettle_default_api)

class general_environment:
    now = 0
    luminosity = 30

    def __init__(self):
        # Var init
        self.now = datetime.now()

        # Proceses init
        self.set_time()

    def set_time(self):
        self.now = datetime.now()

    def print_env_values(self):
        return "Current Time =" + self.now.strftime("%H:%M:%S")

env = general_environment();

print("Wait 5 seconds before starting (so we are sure that all apps started)")
sleep(5)

#### 
## Test Case 1 - Get luminosity from WindWow and stir SmartKettle with the value of the luminosity
print ("Test case 1")

## Prerequisite environment values

# Set default environment luminosity value
set_luminosity = windwow_api_instance.settings_setting_name_setting_value_post("luminosity",env.luminosity)
print(f"settings_setting_name_setting_value_post: {set_luminosity}")

##

## Test Scenario

# Get luminosity
get_luminosity = windwow_api_instance.settings_setting_name_get("luminosity")
print(f"settings_setting_name_get: {get_luminosity}")

# Parse luminosity and save it as a general environment value
env.luminosity = int(get_luminosity[14:16])

# Set the stir of SmartKettle
stir_liquid_rpm_get_response = smartkettle_api_instance.stir_liquid_rpm_get(env.luminosity)
print(f"stir_liquid_rpm_get_response: {stir_liquid_rpm_get_response}")

####

pprint(get_luminosity)
pprint(stir_liquid_rpm_get_response)

# app = flask.Flask(__name__)

# @app.route("/")
# def print_env():
#     return env.print_env_values()

