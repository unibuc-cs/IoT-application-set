import time
import openapi_client
from pprint import pprint
from openapi_client.api import default_api
from openapi_client.model.plant_object import PlantObject
from openapi_client.model.setting_name import SettingName
from openapi_client.model.settings_object import SettingsObject
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9080"
)



# Enter a context with an instance of the API client
with openapi_client.ApiClient(configuration) as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    
    try:
        api_response = api_instance.activate_solar_lamp_get()
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->activate_solar_lamp_get: %s\n" % e)