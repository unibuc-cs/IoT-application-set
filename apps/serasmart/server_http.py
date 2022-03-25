from flask import Flask, render_template, request, send_from_directory
from flask_mqtt import Mqtt
from threading import Thread
import threading
import random
import time
import yaml
import json
import sys
import db

STATIC_FOLDER="APIDocumentation"
app=Flask(__name__,template_folder=STATIC_FOLDER)
app.config['MQTT_BROKER_URL'] = 'broker.emqx.io'  # use the free broker from HIVEMQ
app.config['MQTT_BROKER_PORT'] = 1883  # default port for non-tls connection
app.config['MQTT_USERNAME'] = 'emqx'  # set the username here if you need authentication for the broker
app.config['MQTT_PASSWORD'] = 'public'  # set the password here if the broker demands authentication
app.config['MQTT_KEEPALIVE'] = 5  # set the time interval for sending a ping to the broker to 5 seconds
app.config['MQTT_TLS_ENABLED'] = False  # set TLS to disabled for testing purposes
http_port="42178"

@app.route("/")
def main_route():
    return "SeraSmart IoT implementare. Citeste mai multe la <a href='https://github.com/iuliangal186/ProiectIS'>SeraSmart</a><br>\
        Acceseaza api-ul documentat aici: <br>\
            <a href='/openapi'>OpenAPI</a> cu <a href='/openapi.json'>json</a>\
            <br>\
            <a href='/asyncapi'>AsyncAPI</a> cu <a href='/asyncapi.json'>json</a>"

@app.route("/openapi")
def openapi_docs_route():
    return render_template("/OpenAPI/index.html", title = 'Main page')
@app.route("/openapi.json")
def openapi_route():
    with open(STATIC_FOLDER+"/OpenAPI/openapi.yaml", 'r') as yaml_in:
        yaml_object = yaml.safe_load(yaml_in) # yaml_object will be a list or a dict
        return json.dumps(yaml_object),200,{'Content-Type': 'application/json'}

@app.route("/asyncapi")
def asyncapi_docs_route():
    return render_template("/AsyncAPI/index.html", title = 'Main page')
@app.route("/css/global.min.css")
def asyncapi_globalcss_route():
    return render_template("/AsyncAPI/css/global.min.css", title = 'Main page'),200,{'Content-Type': 'text/css'}
@app.route("/css/asyncapi.min.css")
def asyncapi_asyncapicss_route():
    return render_template("/AsyncAPI/css/asyncapi.min.css", title = 'Main page'),200,{'Content-Type': 'text/css'}
@app.route("/js/asyncapi-ui.min.js")
def asyncapi_asyncapijs_route():
    return render_template("/AsyncAPI/js/asyncapi-ui.min.js", title = 'Main page'),200,{'Content-Type': 'text/javascript'}
@app.route("/asyncapi.json")
def asyncapi_route():
    with open(STATIC_FOLDER+"/AsyncAPI/asyncapi.yaml", 'r') as yaml_in:
        yaml_object = yaml.safe_load(yaml_in) # yaml_object will be a list or a dict
        return json.dumps(yaml_object),200,{'Content-Type': 'application/json'}



# Register extensions to the endpoints
def register_endpoints():
    # Python is completely crippled by the circular dependencies
    # Define dependecies here locally as we only need this single variable bp
    from Endpoints import fereastra,usa,temperatura,lumina,umiditate,motion,weather
    app.register_blueprint(fereastra.bp)
    app.register_blueprint(usa.bp)
    app.register_blueprint(temperatura.bp)
    app.register_blueprint(lumina.bp)
    app.register_blueprint(umiditate.bp)
    app.register_blueprint(motion.bp)
    app.register_blueprint(weather.bp)



def run_http_server():
    print(f"Running server on port {http_port}")

    db.init_app(app)

    # Unbelievable hack to run flask without setting an evironment variable and 
    # executing an external program to load the server
    # Overstep this incredible setup and just run the server
    app.run("localhost",http_port)


def init_http():
    register_endpoints()


def get_app():
    return app
