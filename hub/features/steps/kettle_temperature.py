from behave import *
import app

@given('window\'s temperature is {X}')
def step_impl(context, X):
    app.env.clients["windwow"].settings_setting_name_setting_value_post(
        "temperature", 
        int(X),
    )

@when('automation rules are triggered for kettle')
def step_impl(context):
    app.env.run_simple()

@then('kettle\'s temperature is set to {Y}')
def step_impl(context, Y):
    assert int(app.env.data["smartkettle"]["temperature"]) == int(Y)