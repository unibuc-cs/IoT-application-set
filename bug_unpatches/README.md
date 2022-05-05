(new) Bugs
===

| Id                     | Level       | Where       | Type                                  | Description                                                            |
|------------------------|-------------|-------------|---------------------------------------|------------------------------------------------------------------------|
| b1_invalid_sensor_type | Application | flowerpower | **Real**, CWE-457: Use of Uninitialized Variable | sensorNameMap[sensorTypeID] is accessed without checking for existence |
|                        |             |             |                                       |                                                                        |
|                        |             |             |                                       |                                                                        |

(old) Bugs
===

| Id                                          | Level       | Where                               | Type                                                                   | Description                                                                                                                                                         |
|---------------------------------------------|-------------|-------------------------------------|------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| a1_activatesolarlamp_luminosity_not_changed | Application | flowerpower                         | **Real**, programming error                                            | activateSolarLamp does not change luminosity                                                                                                                        |
| a2_dont_call_abs_on_temperature_diff        | Rule        | Rule 5, smartkettle, windwow        | **Real**, CWE-1284: Improper Validation of Specified Quantity in Input | SmartKettle’s temperature decreases for WindWow’s temperatures under 0 degrees celsius instead of increasing                                                        |
| a3_dont_call_min_for_brightness             | Rule        | Rule 4, smarttv                     | **Real**, CWE-1284: Improper Validation of Specified Quantity in Input | TV brightness should be set to a maximum of 10, but the value is not validated by the app                                                                           |
| a4_dont_check_temperature                   | Persistence | Rules 2 and 3, flowerpower, windwow | **Real**, business logic error                                         | Rule 2 will reduce the window’s luminosity if the temperature is over 30 degrees, then Rule 3 will unnecessarily turn on the lamp because the luminosity is too low |
| a5_json_key_not_checked                     | Application | flowerpower                         | **Real**, CWE-476: NULL Pointer Dereference                            | Does not check for optional key existence in JSON object on PUT /settings                                                                                           |
| a6_listen_to_localhost                      | Application | smarteeth                           | **Real**, misconfiguration                                             | Smarteeth: “localhost” set as the hostname of the listening server thus refusing outside connections                                                                |
| a7_windwow_set_setting_crash                | Application | windwow                             | **Injected**, CWE-824: Access of Uninitialized Pointer                 | Windwow crashes when trying to set luminosity to 25 and curtains are closed on GET /settings/{settingName}/{settingValue}                                           |