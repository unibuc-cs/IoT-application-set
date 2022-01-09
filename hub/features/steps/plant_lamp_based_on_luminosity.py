from behave import *
import app

@given('Plant lamp is off and luminosity is 24')
def step_impl(context):
    # Get 
    app.gather_data(app.env)
    print(context.app.env.data["windwow"]["luminosity"])
    context.app = app
    pass

@when('Luminosity is 10')
def step_impl(context):
    app.env.clients["windwow"].settings_setting_name_setting_value_post("luminosity", int(temperature_value))
    # app.rule3(app.env, 24, 10)
    pass

@then('Turn on the plant lamp')
def step_impl(context):
    solar_lamp_status = app.env.clients["flowerpower"]
    assert context.app.env.data["smartkettle"]["rpm"] == context.app.env.data["windwow"]["temperature"]