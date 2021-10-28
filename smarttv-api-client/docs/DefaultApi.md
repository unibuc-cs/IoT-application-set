# openapi_client.DefaultApi

All URIs are relative to *http://localhost:9081*

Method | HTTP request | Description
------------- | ------------- | -------------
[**add_channel_username_canal_post**](DefaultApi.md#add_channel_username_canal_post) | **POST** /addChannel/{username}/{canal} | 
[**get_history_and_recommandations_nume_get**](DefaultApi.md#get_history_and_recommandations_nume_get) | **GET** /getHistoryAndRecommandations/{nume} | 
[**get_suggested_channels_gen_varsta_get**](DefaultApi.md#get_suggested_channels_gen_varsta_get) | **GET** /getSuggestedChannels/{gen}/{varsta} | 
[**get_users_get**](DefaultApi.md#get_users_get) | **GET** /getUsers | 
[**get_users_json_get**](DefaultApi.md#get_users_json_get) | **GET** /getUsersJSON | Loads users into output_users.json file.
[**insert_user_username_varsta_post**](DefaultApi.md#insert_user_username_varsta_post) | **POST** /insertUser/{username}/{varsta} | 
[**notification_distance_size_current_distance_get**](DefaultApi.md#notification_distance_size_current_distance_get) | **GET** /notificationDistance/{size}/{current_distance} | 
[**set_brightness_level_post**](DefaultApi.md#set_brightness_level_post) | **POST** /setBrightness/{level} | 
[**set_brightness_our_sensor_post**](DefaultApi.md#set_brightness_our_sensor_post) | **POST** /setBrightnessOurSensor | Loads brightness from (another) file.
[**set_brightness_sensor_post**](DefaultApi.md#set_brightness_sensor_post) | **POST** /setBrightnessSensor | Loads brightness from file.
[**timp_idle_time_post**](DefaultApi.md#timp_idle_time_post) | **POST** /timp-idle/{time} | 
[**timp_last_get**](DefaultApi.md#timp_last_get) | **GET** /timp-last | 
[**timp_start_get**](DefaultApi.md#timp_start_get) | **GET** /timp-start | 


# **add_channel_username_canal_post**
> add_channel_username_canal_post(username, canal)



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    username = "ionel" # str | 
    canal = "nasultv" # str | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.add_channel_username_canal_post(username, canal)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->add_channel_username_canal_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **username** | **str**|  |
 **canal** | **str**|  |

### Return type

void (empty response body)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: Not defined


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Success message. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **get_history_and_recommandations_nume_get**
> InlineResponse2002 get_history_and_recommandations_nume_get(nume)



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from openapi_client.model.inline_response2002 import InlineResponse2002
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    nume = "film_bun" # str | 

    # example passing only required values which don't have defaults set
    try:
        api_response = api_instance.get_history_and_recommandations_nume_get(nume)
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->get_history_and_recommandations_nume_get: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **nume** | **str**|  |

### Return type

[**InlineResponse2002**](InlineResponse2002.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Object containing the history and suggested channels. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **get_suggested_channels_gen_varsta_get**
> InlineResponse2001 get_suggested_channels_gen_varsta_get(gen, varsta)



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from openapi_client.model.inline_response2001 import InlineResponse2001
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    gen = "actiune" # str | 
    varsta = 19 # int | 

    # example passing only required values which don't have defaults set
    try:
        api_response = api_instance.get_suggested_channels_gen_varsta_get(gen, varsta)
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->get_suggested_channels_gen_varsta_get: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **gen** | **str**|  |
 **varsta** | **int**|  |

### Return type

[**InlineResponse2001**](InlineResponse2001.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | List of suggested channels. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **get_users_get**
> [User] get_users_get()



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from openapi_client.model.user import User
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_response = api_instance.get_users_get()
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->get_users_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

### Return type

[**[User]**](User.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Array of users. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **get_users_json_get**
> str get_users_json_get()

Loads users into output_users.json file.

### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        # Loads users into output_users.json file.
        api_response = api_instance.get_users_json_get()
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->get_users_json_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

### Return type

**str**

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: text/plain


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Success message. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **insert_user_username_varsta_post**
> insert_user_username_varsta_post(username, varsta)



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    username = "ionel" # str | 
    varsta = 19 # int | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.insert_user_username_varsta_post(username, varsta)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->insert_user_username_varsta_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **username** | **str**|  |
 **varsta** | **int**|  |

### Return type

void (empty response body)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Success message |  -  |
**400** | User already exists. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **notification_distance_size_current_distance_get**
> InlineResponse2004 notification_distance_size_current_distance_get(size, current_distance)



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from openapi_client.model.inline_response2004 import InlineResponse2004
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    size = 7 # int | 
    current_distance = 2.5 # float | 

    # example passing only required values which don't have defaults set
    try:
        api_response = api_instance.notification_distance_size_current_distance_get(size, current_distance)
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->notification_distance_size_current_distance_get: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **size** | **int**|  |
 **current_distance** | **float**|  |

### Return type

[**InlineResponse2004**](InlineResponse2004.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | New notification distance. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **set_brightness_level_post**
> InlineResponse2003 set_brightness_level_post(level)



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from openapi_client.model.inline_response2003 import InlineResponse2003
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    level = 3 # int | 

    # example passing only required values which don't have defaults set
    try:
        api_response = api_instance.set_brightness_level_post(level)
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->set_brightness_level_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **level** | **int**|  |

### Return type

[**InlineResponse2003**](InlineResponse2003.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | The new level. |  -  |
**400** | Invalid brightness level. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **set_brightness_our_sensor_post**
> InlineResponse2003 set_brightness_our_sensor_post()

Loads brightness from (another) file.

### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from openapi_client.model.inline_response2003 import InlineResponse2003
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        # Loads brightness from (another) file.
        api_response = api_instance.set_brightness_our_sensor_post()
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->set_brightness_our_sensor_post: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

### Return type

[**InlineResponse2003**](InlineResponse2003.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | The new level. |  -  |
**400** | Invalid brightness level. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **set_brightness_sensor_post**
> InlineResponse2003 set_brightness_sensor_post()

Loads brightness from file.

### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from openapi_client.model.inline_response2003 import InlineResponse2003
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        # Loads brightness from file.
        api_response = api_instance.set_brightness_sensor_post()
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->set_brightness_sensor_post: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

### Return type

[**InlineResponse2003**](InlineResponse2003.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | The new level. |  -  |
**400** | Invalid brightness level. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **timp_idle_time_post**
> timp_idle_time_post(time)



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    time = 5 # int | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.timp_idle_time_post(time)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->timp_idle_time_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **time** | **int**|  |

### Return type

void (empty response body)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: Not defined


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Set idle time duration. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **timp_last_get**
> InlineResponse200 timp_last_get()



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from openapi_client.model.inline_response200 import InlineResponse200
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_response = api_instance.timp_last_get()
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->timp_last_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

### Return type

[**InlineResponse200**](InlineResponse200.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Time from last. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **timp_start_get**
> InlineResponse200 timp_start_get()



### Example


```python
import time
import openapi_client
from openapi_client.api import default_api
from openapi_client.model.inline_response200 import InlineResponse200
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9081
# See configuration.py for a list of all supported configuration parameters.
configuration = openapi_client.Configuration(
    host = "http://localhost:9081"
)


# Enter a context with an instance of the API client
with openapi_client.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_response = api_instance.timp_start_get()
        pprint(api_response)
    except openapi_client.ApiException as e:
        print("Exception when calling DefaultApi->timp_start_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

### Return type

[**InlineResponse200**](InlineResponse200.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Time from start. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

