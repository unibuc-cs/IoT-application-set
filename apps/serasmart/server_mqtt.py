import json
import time
import status
from threading import Thread
from collections import deque
from flask_mqtt import Mqtt
from common import root_topic
import server_http

# Queue used for storing mqtt messages and sent them
# Format: [ (<sub_topic>,<command>),(<topic>,<command>) ]
# Subtopic means that the root topic must not be specified
mqqt_commands_queue = deque([])

mqtt = Mqtt(server_http.get_app())
mqtt_message_callbacks = []


@mqtt.on_connect()
def mqtt_on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")

        # Subscribe only on succesfull connect
        subscribe_to_topics()
    else:
        print("Failed to connect, return code %d\n", rc)


@mqtt.on_message()
def mqtt_on_message(client, userdata, msg):
    # Needed in order for the database to be registered and be usable withing the components
    server_http.get_app().app_context().push()

    # print(f"Received {msg.payload.decode()} from {msg.topic} topic")

    for callback in mqtt_message_callbacks:
        callback(client, userdata, msg)


def subscribe_to_topics():
    mqtt.subscribe(root_topic + "window/update")
    mqtt.subscribe(root_topic + "door/update")
    mqtt.subscribe(root_topic + "temperature")
    mqtt.subscribe(root_topic + "luminosity")
    mqtt.subscribe(root_topic + "humidity")
    mqtt.subscribe(root_topic + "motion")


def register_endpoints():
    from Endpoints import fereastra, usa, temperatura, lumina, umiditate,motion
    mqtt_message_callbacks.append(fereastra.mqtt_on_message)
    mqtt_message_callbacks.append(usa.mqtt_on_message)
    mqtt_message_callbacks.append(temperatura.mqtt_on_message)
    mqtt_message_callbacks.append(lumina.mqtt_on_message)
    mqtt_message_callbacks.append(umiditate.mqtt_on_message)
    mqtt_message_callbacks.append(motion.mqtt_on_message)


def mqtt_message_pump():
    global mqqt_commands_queue
    while True:
        # Using app context is required because the get_status() functions
        # requires access to the db.
        with server_http.get_app().app_context():
            message = json.dumps(status.get_status(), default=str)
        get_mqtt_client().publish(root_topic+"status", message)

        if len(get_mqtt_queue()) == 0:
            time.sleep(1)
            continue
        next_message = get_mqtt_queue().popleft()
        get_mqtt_client().publish(root_topic + next_message[0], next_message[1])


def run_mqtt_server():
    thread = Thread(target=mqtt_message_pump)
    thread.daemon = True
    thread.start()


def init_mqtt():
    register_endpoints()


def get_mqtt_client():
    return mqtt


def get_mqtt_queue():
    return mqqt_commands_queue

