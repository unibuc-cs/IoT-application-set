# smartkettle.DefaultApi

All URIs are relative to *http://141.85.232.40:9082*

Method | HTTP request | Description
------------- | ------------- | -------------
[**boil_liquid_by_viscosity_get**](DefaultApi.md#boil_liquid_by_viscosity_get) | **GET** /boilLiquidByViscosity | 
[**make_tea_post**](DefaultApi.md#make_tea_post) | **POST** /makeTea | 
[**stir_liquid_rpm_get**](DefaultApi.md#stir_liquid_rpm_get) | **GET** /stirLiquid/{rpm} | 
[**warm_liquid_by_date_post**](DefaultApi.md#warm_liquid_by_date_post) | **POST** /warmLiquidByDate | 
[**warm_liquid_temperature_scale_get**](DefaultApi.md#warm_liquid_temperature_scale_get) | **GET** /warmLiquid/{temperature}/{scale} | 


# **boil_liquid_by_viscosity_get**
> InlineResponse2001 boil_liquid_by_viscosity_get()



### Example


```python
import time
import smartkettle
from smartkettle.api import default_api
from smartkettle.model.inline_response2001 import InlineResponse2001
from pprint import pprint
# Defining the host is optional and defaults to http://141.85.232.40:9082
# See configuration.py for a list of all supported configuration parameters.
configuration = smartkettle.Configuration(
    host = "http://141.85.232.40:9082"
)


# Enter a context with an instance of the API client
with smartkettle.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_response = api_instance.boil_liquid_by_viscosity_get()
        pprint(api_response)
    except smartkettle.ApiException as e:
        print("Exception when calling DefaultApi->boil_liquid_by_viscosity_get: %s\n" % e)
```


### Parameters
This endpoint does not need any parameter.

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
**200** | Success Response |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **make_tea_post**
> InlineResponse2002 make_tea_post()



### Example


```python
import time
import smartkettle
from smartkettle.api import default_api
from smartkettle.model.inline_object import InlineObject
from smartkettle.model.inline_response2002 import InlineResponse2002
from pprint import pprint
# Defining the host is optional and defaults to http://141.85.232.40:9082
# See configuration.py for a list of all supported configuration parameters.
configuration = smartkettle.Configuration(
    host = "http://141.85.232.40:9082"
)


# Enter a context with an instance of the API client
with smartkettle.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    inline_object = InlineObject(
        keep_warm=True,
        temperature=MakeTeaTemperature(
            temperature="100",
            scale="C",
        ),
        time=5,
    ) # InlineObject |  (optional)

    # example passing only required values which don't have defaults set
    # and optional values
    try:
        api_response = api_instance.make_tea_post(inline_object=inline_object)
        pprint(api_response)
    except smartkettle.ApiException as e:
        print("Exception when calling DefaultApi->make_tea_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **inline_object** | [**InlineObject**](InlineObject.md)|  | [optional]

### Return type

[**InlineResponse2002**](InlineResponse2002.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Success Response |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **stir_liquid_rpm_get**
> InlineResponse2004 stir_liquid_rpm_get(rpm)



### Example


```python
import time
import smartkettle
from smartkettle.api import default_api
from smartkettle.model.inline_response2004 import InlineResponse2004
from pprint import pprint
# Defining the host is optional and defaults to http://141.85.232.40:9082
# See configuration.py for a list of all supported configuration parameters.
configuration = smartkettle.Configuration(
    host = "http://141.85.232.40:9082"
)


# Enter a context with an instance of the API client
with smartkettle.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    rpm = 50 # float | 

    # example passing only required values which don't have defaults set
    try:
        api_response = api_instance.stir_liquid_rpm_get(rpm)
        pprint(api_response)
    except smartkettle.ApiException as e:
        print("Exception when calling DefaultApi->stir_liquid_rpm_get: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **rpm** | **float**|  |

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
**200** | Success Response |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **warm_liquid_by_date_post**
> InlineResponse2003 warm_liquid_by_date_post()



### Example


```python
import time
import smartkettle
from smartkettle.api import default_api
from smartkettle.model.inline_response2003 import InlineResponse2003
from smartkettle.model.inline_object1 import InlineObject1
from pprint import pprint
# Defining the host is optional and defaults to http://141.85.232.40:9082
# See configuration.py for a list of all supported configuration parameters.
configuration = smartkettle.Configuration(
    host = "http://141.85.232.40:9082"
)


# Enter a context with an instance of the API client
with smartkettle.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    inline_object1 = InlineObject1(
        recurrent=True,
        temperature=MakeTeaTemperature(
            temperature="100",
            scale="C",
        ),
        hour="22:30",
    ) # InlineObject1 |  (optional)

    # example passing only required values which don't have defaults set
    # and optional values
    try:
        api_response = api_instance.warm_liquid_by_date_post(inline_object1=inline_object1)
        pprint(api_response)
    except smartkettle.ApiException as e:
        print("Exception when calling DefaultApi->warm_liquid_by_date_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **inline_object1** | [**InlineObject1**](InlineObject1.md)|  | [optional]

### Return type

[**InlineResponse2003**](InlineResponse2003.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Success Response |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **warm_liquid_temperature_scale_get**
> InlineResponse200 warm_liquid_temperature_scale_get(temperature, scale)



What temperature to warm the liquid at

### Example


```python
import time
import smartkettle
from smartkettle.api import default_api
from smartkettle.model.inline_response200 import InlineResponse200
from pprint import pprint
# Defining the host is optional and defaults to http://141.85.232.40:9082
# See configuration.py for a list of all supported configuration parameters.
configuration = smartkettle.Configuration(
    host = "http://141.85.232.40:9082"
)


# Enter a context with an instance of the API client
with smartkettle.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    temperature = 50 # float | 
    scale = "celsius" # str | 

    # example passing only required values which don't have defaults set
    try:
        api_response = api_instance.warm_liquid_temperature_scale_get(temperature, scale)
        pprint(api_response)
    except smartkettle.ApiException as e:
        print("Exception when calling DefaultApi->warm_liquid_temperature_scale_get: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **temperature** | **float**|  |
 **scale** | **str**|  |

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
**200** | Success Response |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

