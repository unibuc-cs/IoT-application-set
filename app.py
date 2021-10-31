import sys
import threading
from datetime import datetime
import flask
from pprint import pprint

# Import all the apps
# import app_smarttv
from clients import windwow
from clients import smarttv
from clients import smartkettle

class general_environment:
    now = 0
    luminosity = 30

    def __init__(self):
        # Var init
        self.now = datetime.now()

        # Proceses init
        self.set_time()

    def set_time(self):
        threading.Timer(1.0, self.set_time).start()
        self.now = datetime.now()

    def print_env_values(self):
        return "Current Time =" + self.now.strftime("%H:%M:%S")

env = general_environment();

# try:
#     insert_user_username_varsta_post_response = smarttv.api_instance.insert_user_username_varsta_post("ionel", 19)
#     pprint(insert_user_username_varsta_post_response)
# except smarttv.smarttv_object.ApiException as e:
#     print("Exception when calling DefaultApi->add_channel_username_canal_post: %s\n" % e)

#### 
## Test Case 1 - Get luminosity from WindWow and stir SmartKettle with the value of the luminosity

## Prerequisite environment values

# Set default environment luminosity value
set_luminosity = windwow.api_instance.settings_setting_name_setting_value_post("luminosity",env.luminosity)

##

## Test Scenario

# Get luminosity
get_luminosity = windwow.api_instance.settings_setting_name_get("luminosity")

# Parse luminosity and save it as a general environment value
env.luminosity = int(get_luminosity[14:16])

# Set the stir of SmartKettle
stir_liquid_rpm_get_response = smartkettle.api_instance.stir_liquid_rpm_get(env.luminosity)

####

pprint(get_luminosity)
pprint(stir_liquid_rpm_get_response)

# app = flask.Flask(__name__)

# @app.route("/")
# def print_env():
#     return env.print_env_values()

