import time
import smartkettle
from pprint import pprint
from smartkettle.api import default_api
from smartkettle.model.inline_object import InlineObject
from smartkettle.model.inline_object1 import InlineObject1
from smartkettle.model.inline_response200 import InlineResponse200
from smartkettle.model.inline_response2001 import InlineResponse2001
from smartkettle.model.inline_response2002 import InlineResponse2002
from smartkettle.model.inline_response2003 import InlineResponse2003
from smartkettle.model.inline_response2004 import InlineResponse2004
# Defining the host is optional and defaults to http://141.85.232.40:9082
# See configuration.py for a list of all supported configuration parameters.
configuration = smartkettle.Configuration(
    host = "http://141.85.232.40:9082"
)

# Enter a context with an instance of the API client
with smartkettle.ApiClient(configuration) as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    
    # try:
    #     api_response = api_instance.boil_liquid_by_viscosity_get()
    #     pprint(api_response)
    # except smartkettle.ApiException as e:
    #     print("Exception when calling DefaultApi->boil_liquid_by_viscosity_get: %s\n" % e)