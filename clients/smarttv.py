import time
import smarttv
from pprint import pprint
from smarttv.api import default_api
from smarttv.model.inline_response200 import InlineResponse200
from smarttv.model.inline_response2001 import InlineResponse2001
from smarttv.model.inline_response2002 import InlineResponse2002
from smarttv.model.inline_response2003 import InlineResponse2003
from smarttv.model.inline_response2004 import InlineResponse2004
from smarttv.model.user import User
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = smarttv.Configuration(
    host = "http://localhost:9081"
)

# Enter a context with an instance of the API client
with smarttv.ApiClient(configuration) as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    # username = "ionel" # str | 
    # canal = "nasultv" # str | 

    # try:
    #     api_instance.add_channel_username_canal_post(username, canal)
    # except smarttv.ApiException as e:
    #     print("Exception when calling DefaultApi->add_channel_username_canal_post: %s\n" % e)