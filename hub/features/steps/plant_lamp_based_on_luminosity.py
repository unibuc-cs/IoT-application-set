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
    print(app.env.data["flowerpower"]["luminosity"])
    assert app.env.data["flowerpower"]["luminosity"] >= 1