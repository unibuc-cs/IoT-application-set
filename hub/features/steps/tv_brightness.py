from behave import *
import app

@given('TV brightness is set to {X}, window luminosity to {Y} and base luminosity to {Z}')
def step_impl(context, X, Y, Z):
    print(X)
    app.env.clients["smarttv"].set_brightness_level_post(int(X))
    
    app.env.clients["windwow"]\
        .settings_setting_name_setting_value_post(
            "luminosity", 
            int(Y),
        )

    app.env.settings["tv_base_brightness"] = int(Z)

@when('automation rules are triggered')
def step_impl(context):
    app.env.run_simple()

@then('TV brightness is set to max(10 - {Y}/10 + {Z}, {Z}) <= 10')
def step_impl(context, Y, Z):
    Y = float(Y)
    Z = float(Z)
    assert app.env.data["smarttv"]["brightness"] == int(
        min(max(10 - Y/10 + Z, Z), 10)
    )