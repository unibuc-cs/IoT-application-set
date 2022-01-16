# windwow.DefaultApi

All URIs are relative to *http://windwow:9080*

Method | HTTP request | Description
------------- | ------------- | -------------
[**settings_setting_name_get**](DefaultApi.md#settings_setting_name_get) | **GET** /settings/{settingName} | 
[**settings_setting_name_setting_value_post**](DefaultApi.md#settings_setting_name_setting_value_post) | **POST** /settings/{settingName}/{settingValue} | 
[**user_settings_post**](DefaultApi.md#user_settings_post) | **POST** /userSettings | 


# **settings_setting_name_get**
> str settings_setting_name_get(setting_name)



Get value of a specific setting

### Example


```python
import time
import windwow
from windwow.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://windwow:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = windwow.Configuration(
    host = "http://windwow:9080"
)


# Enter a context with an instance of the API client
with windwow.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    setting_name = "luminosity" # str | 

    # example passing only required values which don't have defaults set
    try:
        api_response = api_instance.settings_setting_name_get(setting_name)
        pprint(api_response)
    except windwow.ApiException as e:
        print("Exception when calling DefaultApi->settings_setting_name_get: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **setting_name** | **str**|  |

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
**200** | The value of the requested setting. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **settings_setting_name_setting_value_post**
> str settings_setting_name_setting_value_post(setting_name, setting_value)



Set value of a specific setting

### Example


```python
import time
import windwow
from windwow.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://windwow:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = windwow.Configuration(
    host = "http://windwow:9080"
)


# Enter a context with an instance of the API client
with windwow.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    setting_name = "luminosity" # str | 
    setting_value = 5 # float | 

    # example passing only required values which don't have defaults set
    try:
        api_response = api_instance.settings_setting_name_setting_value_post(setting_name, setting_value)
        pprint(api_response)
    except windwow.ApiException as e:
        print("Exception when calling DefaultApi->settings_setting_name_setting_value_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **setting_name** | **str**|  |
 **setting_value** | **float**|  |

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
**200** | The value of the requested setting. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **user_settings_post**
> str user_settings_post()



### Example


```python
import time
import windwow
from windwow.api import default_api
from windwow.model.inline_object import InlineObject
from pprint import pprint
# Defining the host is optional and defaults to http://windwow:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = windwow.Configuration(
    host = "http://windwow:9080"
)


# Enter a context with an instance of the API client
with windwow.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    inline_object = InlineObject(
        username="cumparator",
        password="parolasigura",
        phonenumber=712345678,
    ) # InlineObject |  (optional)

    # example passing only required values which don't have defaults set
    # and optional values
    try:
        api_response = api_instance.user_settings_post(inline_object=inline_object)
        pprint(api_response)
    except windwow.ApiException as e:
        print("Exception when calling DefaultApi->user_settings_post: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **inline_object** | [**InlineObject**](InlineObject.md)|  | [optional]

### Return type

**str**

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: text/plain


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | The value of the requested setting. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

