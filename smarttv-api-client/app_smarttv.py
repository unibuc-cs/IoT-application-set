import time
import openapi_client
from pprint import pprint
from openapi_client.api import default_api
from openapi_client.model.inline_response200 import InlineResponse200
from openapi_client.model.inline_response2001 import InlineResponse2001
from openapi_client.model.inline_response2002 import InlineResponse2002
from openapi_client.model.inline_response2003 import InlineResponse2003
from openapi_client.model.inline_response2004 import InlineResponse2004
from openapi_client.model.user import User
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)

username = "ionel" # str | 
canal = "nasultv" # str | 

smarttv_api_instance = ""

# Enter a context with an instance of the API client
with openapi_client.ApiClient(configuration) as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    
    # Set global variable
    smarttv_api_instance = api_instance;
    
    try:
        # x = api_instance.add_channel_username_canal_post(username, canal)
        print("Add Channel Username canal post called")
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->add_channel_username_canal_post: %s\n" % e)