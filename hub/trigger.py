import app
from flowerpower.model.settings_object import SettingsObject
from flowerpower.model.setting_name import SettingName

#app.env.clients["windwow"].settings_setting_name_setting_value_post("luminosity", 70)

"""
luminosity_sensor_id = 3
threshold = 30

print(SettingsObject(luminosity_sensor_id, float(threshold), 100.0))

app.env.clients["flowerpower"].settings_put(
    settings_object=SettingsObject(luminosity_sensor_id, float(threshold), 100.0, nutrient_type=None, _check_type=False)
)
"""

app.env.clients["flowerpower"]\
    .settings_setting_name_setting_value_put(
        SettingName("luminosity"), 
        str(30)
    )

app.env.clients["windwow"].settings_setting_name_setting_value_post(
    "luminosity", 30, 
    _check_input_type=False, _host_index=0
    )


app.env.clients["flowerpower"]\
    .settings_setting_name_setting_value_put(
        SettingName("temperature"), 
        str(40)
    )
    
