from paho.mqtt import client as mqtt_client
import random
import json
import time

# Client for simulating all sensors: temperature, luminosity, humidity

sensor_topics = ["temperature", "luminosity", "humidity", "motion"]
client = None
broker = 'broker.emqx.io'
port = 1883
root_topic = "/greenhouse/"
client_id = f'python-mqtt-{random.randint(0, 1000)}'
username = 'emqx'
password = 'public'


def publish(topic, msg):
    global client
    result = client.publish(topic, msg)
    if result[0] == 0:
        print(f"Sent `{msg}` to topic `{topic}`")
    else:
        print(f"Failed to send message to topic {topic}")


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)


def connect_mqtt():
    new_mqtt_client = mqtt_client.Client(client_id)
    new_mqtt_client.username_pw_set(username, password)
    new_mqtt_client.on_connect = on_connect

    new_mqtt_client.connect(broker, port)
    return new_mqtt_client


# Method which impersonates the gadget and send values form its side
def run_sensors():
    global client

    # Wait for a connection
    time.sleep(2)

    while True:
        for sensor in sensor_topics:
            topic = root_topic + sensor

            if "motion" in sensor:
                msg = motion_generator()
            else:
                msg = default_generator()
            publish(topic, msg)

        time.sleep(5)


def default_generator():
    sensor_value = random.randint(0, 50)
    msg = json.dumps({"value": sensor_value})
    return msg


def motion_generator():
    sensor_area = random.randint(0, 5)
    sensor_duration = random.randint(1, 50)
    sensor_value = random.randint(0, 10) / 10

    msg = json.dumps({"area": sensor_area, "duration": sensor_duration, "value": sensor_value})
    return msg


def run():
    global client

    client = connect_mqtt()
    if client is None:
        print("Sensors failed")
        return

    client.loop_start()
    run_sensors()


if __name__ == '__main__':
    run()
