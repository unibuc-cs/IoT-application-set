(new) Bugs
===

| Id                     | Level       | Where       | Type                                  | Description                                                            |
|------------------------|-------------|-------------|---------------------------------------|------------------------------------------------------------------------|
| 1_sensor_type_oob_read | Application | flowerpower | **Real**, CWE-125: Out-of-bounds Read | sensorNameMap[sensorTypeID] is accessed without checking for existence |
|                        |             |             |                                       |                                                                        |
|                        |             |             |                                       |                                                                        |