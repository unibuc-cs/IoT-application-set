import sys
import threading
from datetime import datetime
import flask

# Import all the apps
# import app_smarttv
from clients import windwow

# app_smarttv.smarttv_api_instance.add_channel_username_canal_post(app_smarttv.username, app_smarttv.canal)

class general_environment:
    now = 0

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

# app = flask.Flask(__name__)

# windwow.api_instance.settings_setting_name_get("luminosity")

# @app.route("/")
# def print_env():
#     return env.print_env_values()

