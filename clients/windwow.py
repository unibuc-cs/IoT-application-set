import time
import windwow_api_client
from pprint import pprint
from windwow_api_client.api import default_api
from windwow_api_client.model.inline_object import InlineObject
# Defining the host is optional and defaults to http://141.85.232.40:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = windwow_api_client.Configuration(
    host = "http://141.85.232.40:9080"
)



# Enter a context with an instance of the API client
with windwow_api_client.ApiClient(configuration) as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    setting_name = "luminosity" # str |

    try:
        api_response = api_instance.settings_setting_name_get(setting_name)
        pprint(api_response)
    except windwow_api_client.ApiException as e:
        print("Exception when calling DefaultApi->settings_setting_name_get: %s\n" % e)
