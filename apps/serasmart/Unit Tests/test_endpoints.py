import os
import random
from tempfile import tempdir
import tempfile
from threading import Thread
import threading
from time import sleep
import pytest
import json
import sys

# Hahahha what a stupid hack for importing a module from the parent folder
sys.path.append("./..")
import db


# Numai o echipa de idioti a putut crea un asemenea sistem. Ore pierdute incercand sa testez o pagina banala.
# Un destept ca sa rezolve problema si-a transformat intreaga aplicatie main.py intr-un test.... adica test_main.py
# Ce o sa faci atunci cand vei vrea sa testezi si mqtt-ul?

@pytest.fixture(scope="module", autouse=True)
def client():
    import server_http

    server_http.get_app().config["TESTING"] = True
    server_http.init_http()
    app = server_http.get_app()

    with app.test_client() as client:
        with app.app_context():
            db.init_app(app)
        yield client


@pytest.fixture(scope="module", autouse=True)
def mqtt_server(client):
    import server_mqtt

    server_mqtt.init_mqtt()
    server_mqtt.run_mqtt_server()

    yield server_mqtt.get_mqtt_client()


@pytest.fixture(scope="module")
def mqtt_window():
    import Sensors.gadget_window as gadget_window

    # This does not block
    mqtt_client = gadget_window.test_mqtt()
    yield mqtt_client
    mqtt_client.disconnect()


@pytest.fixture(scope="module")
def mqtt_door():
    import Sensors.gadget_door as gadget_door

    # This does not block
    mqtt_client = gadget_door.test_mqtt()
    yield mqtt_client
    mqtt_client.disconnect()


def test_root_endpoint(client):
    landing = client.get("/")
    assert landing.status_code == 200

    html = landing.data.decode()

    assert "SeraSmart IoT implementare. Citeste mai multe la <a href='https://github.com/iuliangal186/ProiectIS'>SeraSmart</a>" in html


def test_temperature_sensor_values(client):
    landing = client.get("/temperatura")
    assert landing.status_code == 200

    data = json.loads(landing.data.decode())

    assert "Sensor succesfully read" in data['status']
    assert data['data']['id'] != 0
    assert data['data']['value'] >= -100 and data['data']['value'] < 100, "Temperatura nu e valida"
    assert data['data']['reference_value'] >= -100 and data['data']['reference_value'] < 100, "Temperatura nu e valida"
    assert data['data']['timestamp']

    # Get a random sample between 0 hours and 24 hours
    rand_nr = random.randint(0, 24)
    landing = client.get("/temperatura/statistics?time_period=" + str(rand_nr))
    assert landing.status_code == 200

    data = json.loads(landing.data.decode())
    print(rand_nr, data)

    assert "Data succesfully retrieved" in data['status']
    if len(data['data']['history']) == 0:
        assert data['data']['average'] == None
    else:
        sum = 0
        for i in range(len(data['data']['history'])):
            entry = data['data']['history'][i]
            sum += entry["value"]

            assert entry["value"] > -100 and entry["value"] < 100
            assert entry["reference_value"] > -100 and entry["reference_value"] < 100

        assert data['data']['average'] == sum / len(data['data']['history'])


def test_temperature_sensor_noparam(client):
    # Get a random sample between 0 hours and 24 hours
    landing = client.get("/temperatura/statistics")

    assert landing.status_code == 400, "Page should return bad request"


def test_luminosity_sensor_values(client):
    landing = client.get("/lumina")
    assert landing.status_code == 200

    data = json.loads(landing.data.decode())

    assert "Sensor succesfully read" in data['status']
    assert data['data']['id'] != 0
    assert data['data']['value'] >= 0 and data['data']['value'] < 100

    # Get a random sample between 0 hours and 24 hours
    rand_nr = random.randint(0, 24)
    landing = client.get("/lumina/statistics?time_period=" + str(rand_nr))
    assert landing.status_code == 200

    data = json.loads(landing.data.decode())
    print(rand_nr, data)

    assert "Data succesfully retrieved" in data['status']
    if len(data['data']['history']) == 0:
        assert (data['data']['average'] == None)
    else:
        assert data['data']['average'] > 0 and data['data']['average'] < 100
        assert data['data']['average'] == sum(data['data']['history']) / len(data['data']['history'])


def test_luminosity_sensor_noparam(client):
    # Get a random sample between 0 hours and 24 hours
    landing = client.get("/lumina/statistics")

    assert landing.status_code == 400, "Page should return bad request"


def test_humidity_sensor_values(client):
    landing = client.get("/umiditate")
    assert landing.status_code == 200

    data = json.loads(landing.data.decode())

    assert "Sensor succesfully read" in data['status']
    assert data['data']['id'] != 0
    assert data['data']['value'] >= 0 and data['data']['value'] < 100

    # Get a random sample between 0 hours and 24 hours
    rand_nr = random.randint(0, 24)
    landing = client.get("/umiditate/statistics?time_period=" + str(rand_nr))
    assert landing.status_code == 200

    data = json.loads(landing.data.decode())
    print(rand_nr, data)

    assert "Data succesfully retrieved" in data['status']
    if len(data['data']['history']) == 0:
        assert (data['data']['average'] == None)
    else:
        assert data['data']['average'] > 0 and data['data']['average'] < 100
        assert data['data']['average'] == sum(data['data']['history']) / len(data['data']['history'])


def test_humidity_sensor_noparam(client):
    # Get a random sample between 0 hours and 24 hours
    landing = client.get("/umiditate/statistics")

    assert landing.status_code == 400, "Page should return bad request"


def test_motion_sensor_values(client):
    landing = client.get("/miscare")
    assert landing.status_code == 200

    data = json.loads(landing.data.decode())

    assert "Sensor succesfully read" in data['status']
    assert data['data']['id'] != 0
    assert data['data']['strength'] >= 0 and data['data']['strength'] <= 1
    assert data['data']['area'] >= 0 and data['data']['area'] <= 5
    assert data['data']['duration'] >= 1 and data['data']['duration'] <= 50

    rand_nr = random.randint(0, 24)
    landing = client.get("/miscare/statistics?time_period=" + str(rand_nr))
    assert landing.status_code == 200

    data = json.loads(landing.data.decode())
    print(rand_nr, data)

    assert "Data succesfully retrieved" in data['status']
    if len(data['data']['history']) != 0:
        for i in range(len(data['data']['history'])):
            entry = data["data"]["history"][i]
            assert entry['strength'] >= 0 and entry['strength'] <= 1
            assert entry['area'] >= 0 and entry['area'] <= 5
            assert entry['duration'] >= 1 and entry['duration'] <= 50


def test_motion_sensor_noparam(client):
    # Get a random sample between 0 hours and 24 hours
    landing = client.get("/miscare/statistics")

    assert landing.status_code == 400, "Page should return bad request"


def test_gadget_window_values(client):
    # Test if requesting a large id will result in error
    landing = client.get("/fereastra?last_id=1000")
    assert landing.status_code == 200, "Page should return success"

    data = json.loads(landing.data.decode())
    assert "There are no new events registered" in data["status"]

    # Test if the values are returned as supposed for a specific id
    last_event = db.get_db().execute(
        f"SELECT max(id) FROM events \
        WHERE event_location='WINDOW'"
    ).fetchone()

    assert last_event != None, "There should be some rows in the database"
    last_event_id = last_event[0]
    print(last_event_id)

    # Test if a request to the last id generates an no-new-events error
    landing = client.get(f"/fereastra?last_id={last_event_id}")
    assert landing.status_code == 200, "Page should return success"

    data = json.loads(landing.data.decode())
    assert "There are no new events registered" in data["status"]

def test_gadget_window_noparam(client):
    # Test if a missing param will result in error
    landing = client.get("/fereastra")
    assert landing.status_code == 400, "Page should return bad request"
def test_gadget_window_noparam(client):
    # Test if a missing param will result in error
    landing = client.post("/fereastra")
    assert landing.status_code == 400, "Page should return bad request"



def test_gadget_door_values(client):
    # Test if requesting a large id will result in error
    landing = client.get("/usa?last_id=1000")
    assert landing.status_code == 200, "Page should return success"

    data = json.loads(landing.data.decode())
    assert "There are no new events registered" in data["status"]

    # Test if the values are returned as supposed for a specific id
    last_event = db.get_db().execute(
        f"SELECT max(id) FROM events \
        WHERE event_location='DOOR'"
    ).fetchone()

    assert last_event != None, "There should be some rows in the database"
    last_event_id = last_event[0]
    print(last_event_id)

    # Test if a request to the last id generates an no-new-events error
    landing = client.get(f"/usa?last_id={last_event_id}")
    assert landing.status_code == 200, "Page should return success"

    data = json.loads(landing.data.decode())
    assert "There are no new events registered" in data["status"]


def test_gadget_door_noparam(client):
    # Test if a missing param will result in error
    landing = client.get("/fereastra")
    assert landing.status_code == 400, "Page should return bad request"
def test_gadget_door_noparam2(client):
    # Test if a missing param will result in error
    landing = client.post("/fereastra")
    assert landing.status_code == 400, "Page should return bad request"

def test_weather_values(client):
    # Test if returned values are normal
    landing = client.get("/vreme")
    assert landing.status_code == 200, "Page should return success"

    data = json.loads(landing.data.decode())
    assert "API succesfully read" in data["status"]
    assert 0 <= data["humidity"] < 100
    assert -100 < data["temperature"] < 100


def test_weather_values_2(client):
    landing = client.get("/vreme")
    response = json.loads(landing.data.decode())

    assert response is not None
    assert "API succesfully read" in response["status"]
    assert response["description"]
    assert response["pressure"]


def test_weather_average_pressure(client):
    # Normal pressure values should be i around 1013 mb
    landing = client.get("/vreme")
    response = json.loads(landing.data.decode())

    assert response is not None
    assert 1005 <= response["pressure"] <= 1020


""" ---- INTEGRATION TESTING ---- """


# Test if integration with mqtt works
def test_gadgetwindow_and_mqtt(client, mqtt_window, mqtt_server):
    # Test if the values are returned as supposed for a specific id
    sleep(2)  # Wait for the previous test to complete(and for the mqtt to respond)...yeah this is called testing
    last_event = db.get_db().execute(
        f"SELECT max(id) FROM events \
        WHERE event_location='WINDOW'"
    ).fetchone()

    assert last_event is not None, "There should be some rows in the database"
    last_event_id = last_event[0]
    print(last_event_id)

    # Try and trigger a state change in the gadget
    landing = client.get(f"/fereastra?last_id={last_event_id}")
    assert landing.status_code == 200, "Page should return success"

    data = json.loads(landing.data.decode())
    assert "There are no new events registered" in data["status"]
    sleep(2)

    # Test if the last request triggered a new event
    landing = client.get(f"/fereastra?last_id={last_event_id}")
    assert landing.status_code == 200, "Page should return success"

    data = json.loads(landing.data.decode())
    assert "Event succesfully retrieved" in data["status"]
    assert data["data"]["id"] > last_event_id
    assert data["data"]["state"] == "OPENED" or data["data"]["state"] == "CLOSED"

# Test if changing gadget state works in integration
def test_gadgetwindow_and_mqtt2(client, mqtt_window, mqtt_server):
    # Test if the values are returned as supposed for a specific id
    sleep(2)  # Wait for the previous test to complete(and for the mqtt to respond)...yeah this is called testing
    
    # Try and change gadget state to OPENED
    landing = client.post(f"/fereastra",data=dict(state=1))
    assert landing.status_code == 200, "Page should return success"
    data = json.loads(landing.data.decode())
    assert "Command was queued" in data["status"]
    
    # Wait for mqtt to respond
    sleep(2)

    # Observe the change in http client
    landing = client.get(f"/fereastra?last_id=0")
    assert landing.status_code == 200, "Page should return success"
    data = json.loads(landing.data.decode())
    assert "Event succesfully retrieved" in data["status"]
    assert data["data"]["state"]=="OPENED"

    # Try and change gadget state to CLOSED
    landing = client.post(f"/fereastra",data=dict(state=0))
    assert landing.status_code == 200, "Page should return success"
    data = json.loads(landing.data.decode())
    assert "Command was queued" in data["status"]
    
    # Wait for mqtt to respond
    sleep(2)

    # Observe the change in http client
    landing = client.get(f"/fereastra?last_id=0")
    assert landing.status_code == 200, "Page should return success"
    data = json.loads(landing.data.decode())
    assert "Event succesfully retrieved" in data["status"]
    assert data["data"]["state"]=="CLOSED"




# Test if integration with mqtt works
def test_gadgetdoor_and_mqtt(client, mqtt_door, mqtt_server):
    # Test if the values are returned as supposed for a specific id
    sleep(2)  # Wait for the previous test to complete(and for the mqtt to respond)...yeah this is called testing
    last_event = db.get_db().execute(
        f"SELECT max(id) FROM events \
        WHERE event_location='DOOR'"
    ).fetchone()

    assert last_event is not None, "There should be some rows in the database"
    last_event_id = last_event[0]
    print(last_event_id)

    # Try and trigger a state change in the gadget
    landing = client.get(f"/usa?last_id={last_event_id}")
    assert landing.status_code == 200, "Page should return success"

    data = json.loads(landing.data.decode())
    assert "There are no new events registered" in data["status"]
    sleep(2)

    # Test if the last request triggered a new event
    landing = client.get(f"/usa?last_id={last_event_id}")
    assert landing.status_code == 200, "Page should return success"

    data = json.loads(landing.data.decode())
    assert "Event succesfully retrieved" in data["status"]
    assert data["data"]["id"] > last_event_id
    assert data["data"]["state"] == "OPENED" or data["data"]["state"] == "CLOSED"

# Test if changing gadget state works in integration
def test_gadgetdoor_and_mqtt2(client, mqtt_window, mqtt_server):
    # Test if the values are returned as supposed for a specific id
    sleep(2)  # Wait for the previous test to complete(and for the mqtt to respond)...yeah this is called testing
    
    # Try and change gadget state to OPENED
    landing = client.post(f"/usa",data=dict(state=1))
    assert landing.status_code == 200, "Page should return success"
    data = json.loads(landing.data.decode())
    assert "Command was queued" in data["status"]
    
    # Wait for mqtt to respond
    sleep(2)

    # Observe the change in http client
    landing = client.get(f"/usa?last_id=0")
    assert landing.status_code == 200, "Page should return success"
    data = json.loads(landing.data.decode())
    assert "Event succesfully retrieved" in data["status"]
    assert data["data"]["state"]=="OPENED"

    # Try and change gadget state to CLOSED
    landing = client.post(f"/usa",data=dict(state=0))
    assert landing.status_code == 200, "Page should return success"
    data = json.loads(landing.data.decode())
    assert "Command was queued" in data["status"]
    
    # Wait for mqtt to respond
    sleep(2)

    # Observe the change in http client
    landing = client.get(f"/usa?last_id=0")
    assert landing.status_code == 200, "Page should return success"
    data = json.loads(landing.data.decode())
    assert "Event succesfully retrieved" in data["status"]
    assert data["data"]["state"]=="CLOSED"