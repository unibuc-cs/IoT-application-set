from behave import *
import app
from flowerpower.model.setting_name import SettingName

@given('window luminosity is below threshold')
def step_impl(context):
    app.env.clients["flowerpower"]\
        .settings_setting_name_setting_value_put(
            SettingName("luminosity"), 
            str(1)
        )

    app.env.clients["windwow"]\
        .settings_setting_name_setting_value_post(
            "luminosity", 
            1,
        )

@when('plant is activated')
def step_impl(context):
    app.env.run_simple()

@then('plant luminosity is above the min value')
def step_impl(context):
    assert app.env.data["flowerpower"]["luminosity"] >= 1


@given('plant temperature is above 30 degrees')
def step_impl(context):
    app.env.clients["flowerpower"]\
        .settings_setting_name_setting_value_put(
            SettingName("luminosity"), 
            str(2)
        )

    app.env.clients["windwow"]\
        .settings_setting_name_setting_value_post(
            "luminosity", 
            10,
        )

    app.env.clients["windwow"]\
        .settings_setting_name_setting_value_post(
            "temperature", 
            40,
        )

    app.env.clients["flowerpower"]\
        .settings_setting_name_setting_value_put(
            SettingName("temperature"), 
            str(40)
        )

    # 10 / 2 = 5 < 6
    app.env.settings["plant_lamp_window_treshold"] = 6

@when('automation rules are ran for plant')
def step_impl(context):
    app.env.run_simple()

@then('plant luminosity is unchanged after halving')
def step_impl(context):
    app.gather_data(app.env)
    assert int(app.env.data["flowerpower"]["luminosity"]) == 5