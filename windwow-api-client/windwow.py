import time
import openapi_client
from pprint import pprint
from openapi_client.api import default_api
from openapi_client.model.inline_object import InlineObject
# Defining the host is optional and defaults to http://141.85.232.40:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://141.85.232.40:9080"
)

windwow_api_instance = ""

# Enter a context with an instance of the API client
with openapi_client.ApiClient(configuration) as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    setting_name = "luminosity" # str | 
    windwow_api_instance = api_instance

    try:
        api_response = api_instance.settings_setting_name_get(setting_name)
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->settings_setting_name_get: %s\n" % e)