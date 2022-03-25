"""
Weather API documentation can be found here: https://openweathermap.org/current
The api_key is from the account that I made (Staicu Bogdan), I don't think the key will change anytime soon.
"""

import requests, json
from flask import (
    Blueprint, request, jsonify
)
from Endpoints import weather_api
from common import root_topic

sensor_root_topic = "weather"
bp = Blueprint("vreme", __name__, url_prefix="/vreme")


@bp.route("", methods=["GET"])
def handler_get():
    return jsonify({
        "status": "API succesfully read",
        "temperature":weather_api.get_reference_temperature(),
        "humidity":weather_api.get_reference_humidity(),
        "pressure":weather_api.get_reference_pressure(),
        "description": weather_api.get_reference_description()
    })


"""
print(" Temperature (in celsius) = " +
      str(round(current_temperature - 273.15, 2)) +
      "\n atmospheric pressure (in hPa unit) = " +
      str(current_pressure) +
      "\n humidity (in percentage) = " +
      str(current_humidity) +
      "\n description = " +
      str(weather_description))
"""

