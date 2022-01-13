# flowerpower.DefaultApi

All URIs are relative to *http://localhost:9080*

Method | HTTP request | Description
------------- | ------------- | -------------
[**activate_solar_lamp_get**](DefaultApi.md#activate_solar_lamp_get) | **GET** /activateSolarLamp | 
[**inject_minerals_get**](DefaultApi.md#inject_minerals_get) | **GET** /injectMinerals | 
[**irrigate_soil_get**](DefaultApi.md#irrigate_soil_get) | **GET** /irrigateSoil | 
[**plant_info_put**](DefaultApi.md#plant_info_put) | **PUT** /plantInfo | Updates plant settings.
[**settings_put**](DefaultApi.md#settings_put) | **PUT** /settings | Updates all settings by the specified JSON.
[**settings_setting_name_get**](DefaultApi.md#settings_setting_name_get) | **GET** /settings/{settingName} | Gets the value of the specified setting.
[**settings_setting_name_setting_value_put**](DefaultApi.md#settings_setting_name_setting_value_put) | **PUT** /settings/{settingName}/{settingValue} | Sets a value to a setting specified by name.
[**shovel_get**](DefaultApi.md#shovel_get) | **GET** /shovel | Shovels the soil.
[**soil_status_get**](DefaultApi.md#soil_status_get) | **GET** /soilStatus | 
[**status_get**](DefaultApi.md#status_get) | **GET** /status | Return plant status from local file.


# **activate_solar_lamp_get**
> str activate_solar_lamp_get()



### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_response = api_instance.activate_solar_lamp_get()
        pprint(api_response)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->activate_solar_lamp_get: %s\n" % e)
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

# **inject_minerals_get**
> str inject_minerals_get()



### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_response = api_instance.inject_minerals_get()
        pprint(api_response)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->inject_minerals_get: %s\n" % e)
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

# **irrigate_soil_get**
> str irrigate_soil_get()



### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_response = api_instance.irrigate_soil_get()
        pprint(api_response)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->irrigate_soil_get: %s\n" % e)
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

# **plant_info_put**
> plant_info_put()

Updates plant settings.

### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from flowerpower.model.plant_object import PlantObject
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    plant_object = PlantObject(
        height=3.14,
        species="species_example",
        color="color_example",
        suitable_soil_type="suitable_soil_type_example",
        type="type_example",
    ) # PlantObject |  (optional)

    # example passing only required values which don't have defaults set
    # and optional values
    try:
        # Updates plant settings.
        api_instance.plant_info_put(plant_object=plant_object)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->plant_info_put: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **plant_object** | [**PlantObject**](PlantObject.md)|  | [optional]

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
**200** | Success message. |  -  |
**422** | Invalid fields. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **settings_put**
> settings_put()

Updates all settings by the specified JSON.

### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from flowerpower.model.settings_object import SettingsObject
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    settings_object = SettingsObject(
        sensor_type=1,
        min=3.14,
        max=3.14,
        nutrient_type="nutrient_type_example",
    ) # SettingsObject |  (optional)

    # example passing only required values which don't have defaults set
    # and optional values
    try:
        # Updates all settings by the specified JSON.
        api_instance.settings_put(settings_object=settings_object)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->settings_put: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **settings_object** | [**SettingsObject**](SettingsObject.md)|  | [optional]

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
**200** | Success message. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **settings_setting_name_get**
> bool, date, datetime, dict, float, int, list, str, none_type settings_setting_name_get(setting_name)

Gets the value of the specified setting.

### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from flowerpower.model.setting_name import SettingName
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    setting_name = SettingName("soilHumidity") # SettingName | 

    # example passing only required values which don't have defaults set
    try:
        # Gets the value of the specified setting.
        api_response = api_instance.settings_setting_name_get(setting_name)
        pprint(api_response)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->settings_setting_name_get: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **setting_name** | **SettingName**|  |

### Return type

**bool, date, datetime, dict, float, int, list, str, none_type**

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: text/plain


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | The value of the requested setting. |  -  |
**404** | If the setting does not exist. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **settings_setting_name_setting_value_put**
> bool, date, datetime, dict, float, int, list, str, none_type settings_setting_name_setting_value_put(setting_name, setting_value)

Sets a value to a setting specified by name.

### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from flowerpower.model.setting_name import SettingName
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)
    setting_name = SettingName("soilHumidity") # SettingName | 
    setting_value = "settingValue_example" # str | 

    # example passing only required values which don't have defaults set
    try:
        # Sets a value to a setting specified by name.
        api_response = api_instance.settings_setting_name_setting_value_put(setting_name, setting_value)
        pprint(api_response)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->settings_setting_name_setting_value_put: %s\n" % e)
```


### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **setting_name** | **SettingName**|  |
 **setting_value** | **str**|  |

### Return type

**bool, date, datetime, dict, float, int, list, str, none_type**

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: text/plain


### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | The newly set value. |  -  |
**404** | If the setting does not exist. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **shovel_get**
> str shovel_get()

Shovels the soil.

### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        # Shovels the soil.
        api_response = api_instance.shovel_get()
        pprint(api_response)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->shovel_get: %s\n" % e)
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

# **soil_status_get**
> str soil_status_get()



### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        api_response = api_instance.soil_status_get()
        pprint(api_response)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->soil_status_get: %s\n" % e)
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
**200** | Soil status. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **status_get**
> str status_get()

Return plant status from local file.

### Example


```python
import time
import flowerpower
from flowerpower.api import default_api
from pprint import pprint
# Defining the host is optional and defaults to http://localhost:9080
# See configuration.py for a list of all supported configuration parameters.
configuration = flowerpower.Configuration(
    host = "http://localhost:9080"
)


# Enter a context with an instance of the API client
with flowerpower.ApiClient() as api_client:
    # Create an instance of the API class
    api_instance = default_api.DefaultApi(api_client)

    # example, this endpoint has no required or optional parameters
    try:
        # Return plant status from local file.
        api_response = api_instance.status_get()
        pprint(api_response)
    except flowerpower.ApiException as e:
        print("Exception when calling DefaultApi->status_get: %s\n" % e)
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
**200** | Plant status. |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

