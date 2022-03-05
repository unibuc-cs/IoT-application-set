from behave import *
import app

@given('setting up window to temperature: {temperature_value}')
def step_impl(context, temperature_value):
    # Initialize environment fields
    app.gather_data(app.env)
    app.env.clients["windwow"].settings_setting_name_setting_value_post("temperature", int(temperature_value))
    context.app = app

@when('we set smartkettle rpm to windwow temperature')
def step_impl(context):
    stir_liquid_response = context.app.env.clients["smartkettle"].stir_liquid_rpm_get(int(context.app.env.data["windwow"]["temperature"]))
    # Update environment data
    idx0 = stir_liquid_response['message'].index('kettle at ') + len('kettle at ')
    idx1 = stir_liquid_response['message'].index(' rmp')
    context.app.env.data["smartkettle"]["rpm"] = int(float(stir_liquid_response['message'][idx0:idx1]))

@then('check if change was set')
def step_impl(context):
    assert context.app.env.data["smartkettle"]["rpm"] == context.app.env.data["windwow"]["temperature"]