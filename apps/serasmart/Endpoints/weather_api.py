import requests
from datetime import datetime

api_key = "1ef9677a0b162641ee1daa1988395188"
# url variable composed of multiple variables
base_url = "http://api.openweathermap.org/data/2.5/weather?"
# latitude and longitude of Bucharest
lat, lon = "44", "26"
complete_url = base_url + "lat=" + lat + "&lon=" + lon + "&appid=" + api_key

# Cache responses so that we don't saturate the API
cache_time = 0
cache_reset_timeout = 5  # seconds
cache_response = None


# Unbelievable. I have to write code to calculate something as simple and important as utc time
def UtcNow():
    now = datetime.utcnow()
    return (now - datetime(1970, 1, 1)).total_seconds()


def get_reference_temperature():
    global cache_time, cache_reset_timeout, cache_response
    x = None

    if UtcNow() - cache_time > cache_reset_timeout:
        cache_time = UtcNow()

        response = requests.get(complete_url)
        x = response.json()
        cache_response = x
    else:
        x = cache_response

    y = x["main"]
    current_temperature = round(y["temp"] - 273.15, 2)
    current_pressure = y["pressure"]
    current_humidity = y["humidity"]
    z = x["weather"]
    weather_description = z[0]["description"]

    return current_temperature


def get_reference_humidity():
    global cache_time, cache_reset_timeout, cache_response
    x = None

    if UtcNow() - cache_time > cache_reset_timeout:
        cache_time = UtcNow()

        response = requests.get(complete_url)
        x = response.json()
        cache_response = x
    else:
        x = cache_response

    y = x["main"]
    current_pressure = y["pressure"]
    current_humidity = y["humidity"]
    z = x["weather"]

    return current_humidity


def get_reference_description():
    global cache_time, cache_reset_timeout, cache_response

    if UtcNow() - cache_time > cache_reset_timeout:
        cache_time = UtcNow()
        response = requests.get(complete_url)
        x = response.json()
        cache_response = x
    else:
        x = cache_response

    return x["weather"][0]["description"]


def get_reference_pressure():
    global cache_time, cache_reset_timeout, cache_response

    if UtcNow() - cache_time > cache_reset_timeout:
        cache_time = UtcNow()
        response = requests.get(complete_url)
        x = response.json()
        cache_response = x
    else:
        x = cache_response

    return x["main"]["pressure"]
