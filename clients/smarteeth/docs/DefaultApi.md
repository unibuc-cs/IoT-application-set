# smarteeth.DefaultApi

All URIs are relative to *https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0*

Method | HTTP request | Description
------------- | ------------- | -------------
[**brushing_conditions_check_get**](DefaultApi.md#brushing_conditions_check_get) | **GET** /brushing/conditions/check | 
[**brushing_conditions_humidity_humidity_value_post**](DefaultApi.md#brushing_conditions_humidity_humidity_value_post) | **POST** /brushing/conditions/humidity/{humidityValue} | 
[**brushing_conditions_temperature_temperature_value_post**](DefaultApi.md#brushing_conditions_temperature_temperature_value_post) | **POST** /brushing/conditions/temperature/{temperatureValue} | 
[**brushing_conditions_toothpaste_weight_amount_post**](DefaultApi.md#brushing_conditions_toothpaste_weight_amount_post) | **POST** /brushing/conditions/toothpasteWeight/{amount} | 
[**brushing_direction_get**](DefaultApi.md#brushing_direction_get) | **GET** /brushing/direction | 
[**brushing_move_post**](DefaultApi.md#brushing_move_post) | **POST** /brushing/move | 
[**brushing_start_username_post**](DefaultApi.md#brushing_start_username_post) | **POST** /brushing/start/{username} | 
[**brushing_time_get**](DefaultApi.md#brushing_time_get) | **GET** /brushing/time | 
[**configuration_username_get**](DefaultApi.md#configuration_username_get) | **GET** /configuration/{username} | 
[**configuration_username_post**](DefaultApi.md#configuration_username_post) | **POST** /configuration/{username} | 
[**health_gum_bleeding_get**](DefaultApi.md#health_gum_bleeding_get) | **GET** /health/gumBleeding | 
[**health_tartrum_get**](DefaultApi.md#health_tartrum_get) | **GET** /health/tartrum | 
[**health_tooth_color_tooth_color_value_post**](DefaultApi.md#health_tooth_color_tooth_color_value_post) | **POST** /health/toothColor/{toothColorValue} | 
[**statistics_username_get**](DefaultApi.md#statistics_username_get) | **GET** /statistics/{username} | 


# **brushing_conditions_check_get**
> brushing_conditions_check_get()



Check status of brushing

### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_instance.brushing_conditions_check_get()
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->brushing_conditions_check_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **brushing_conditions_humidity_humidity_value_post**
> brushing_conditions_humidity_humidity_value_post(humidity_value)



### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    humidity_value = 25 # int | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.brushing_conditions_humidity_humidity_value_post(humidity_value)
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->brushing_conditions_humidity_humidity_value_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **humidity_value** | **int**|  |

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **brushing_conditions_temperature_temperature_value_post**
> brushing_conditions_temperature_temperature_value_post(temperature_value)



### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    temperature_value = 30 # int | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.brushing_conditions_temperature_temperature_value_post(temperature_value)
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->brushing_conditions_temperature_temperature_value_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **temperature_value** | **int**|  |

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **brushing_conditions_toothpaste_weight_amount_post**
> brushing_conditions_toothpaste_weight_amount_post(amount)



### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    amount = 1 # int | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.brushing_conditions_toothpaste_weight_amount_post(amount)
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->brushing_conditions_toothpaste_weight_amount_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **amount** | **int**|  |

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **brushing_direction_get**
> brushing_direction_get()



Get the direction of brushing

### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_instance.brushing_direction_get()
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->brushing_direction_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **brushing_move_post**
> brushing_move_post()



Start movement of brush

### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_instance.brushing_move_post()
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->brushing_move_post: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **brushing_start_username_post**
> brushing_start_username_post(username)



### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    username = "David" # str | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.brushing_start_username_post(username)
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->brushing_start_username_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **username** | **str**|  |

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **brushing_time_get**
> brushing_time_get()



Check brushing time

### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_instance.brushing_time_get()
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->brushing_time_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **configuration_username_get**
> configuration_username_get(username)



What temperature to warm the liquid at

### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    username = "David" # str | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.configuration_username_get(username)
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->configuration_username_get: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **username** | **str**|  |

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **configuration_username_post**
> configuration_username_post(username)



### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from smarteeth.model.inline_object import InlineObject
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    username = "David" # str | 
    inline_object = InlineObject(
        name="Adrian",
        age=27,
        program=3,
        teeth=[
            1,
        ],
    ) # InlineObject |  (optional)

    # example passing only required values which don't have defaults set
    try:
        api_instance.configuration_username_post(username)
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->configuration_username_post: %s\n" % e)

    # example passing only required values which don't have defaults set
    # and optional values
    try:
        api_instance.configuration_username_post(username, inline_object=inline_object)
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->configuration_username_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **username** | **str**|  |
 **inline_object** | [**InlineObject**](InlineObject.md)|  | [optional]

### Return type

void (empty response body)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: Not defined


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **health_gum_bleeding_get**
> health_gum_bleeding_get()



Check if user has gum bleeding

### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_instance.health_gum_bleeding_get()
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->health_gum_bleeding_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **health_tartrum_get**
> health_tartrum_get()



Check if user has tartrum

### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_instance.health_tartrum_get()
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->health_tartrum_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **health_tooth_color_tooth_color_value_post**
> health_tooth_color_tooth_color_value_post(tooth_color_value)



### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    tooth_color_value = 0 # int | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.health_tooth_color_tooth_color_value_post(tooth_color_value)
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->health_tooth_color_tooth_color_value_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **tooth_color_value** | **int**|  |

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **statistics_username_get**
> statistics_username_get(username)



### Example


```python
import time
import smarteeth
from smarteeth.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0
# See configuration.py for a list of all supported configuration parameters.
configuration = smarteeth.Configuration(
    host = "https://virtserver.swaggerhub.com/JustBeYou/smarteeth/1.0.0"
)


# Enter a context with an instance of the API client
with smarteeth.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    username = "David" # str | 

    # example passing only required values which don't have defaults set
    try:
        api_instance.statistics_username_get(username)
    except smarteeth.ApiException as e:
        print("Exception when calling DefaultApi->statistics_username_get: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **username** | **str**|  |

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
**200** | Ok |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

