from flask import (
    Blueprint, request, jsonify
)
from flask_mqtt import Mqtt
import json

from db import get_db
from common import root_topic
from Endpoints import weather_api
import server_mqtt
import server_http

bp = Blueprint("temperatura", __name__, url_prefix="/temperatura")
sensor_root_topic="temperature"

# No POST handler because you can only read the temperature. Perhaps make it adjustable?

@bp.route("",methods=["GET"])
def handler_get():
    db=get_db()

    # Obviously! This is a major sql injection bug. Still researching how to fix it in python
    last_event=db.execute(
        f"SELECT * FROM temperature \
        ORDER BY timestamp DESC"
    ).fetchone()

    # No new event was found so trigger a new one
    if last_event is None:
        return jsonify({
            "status":"There are no new events registered"
        })

    return jsonify({
        "status":"Sensor succesfully read",
        "data":{
            "id":last_event["id"],
            "timestamp":last_event["timestamp"],
            "value":last_event["value"],
            "reference_value":last_event["reference_value"]
        }
    })

@bp.route("/statistics",methods=["GET"])
def handler_get_history():
    db=get_db()
    hours_time_period=float(request.args["time_period"])

    sample_points=db.execute(
        f"SELECT value,reference_value FROM temperature \
        WHERE (julianday('now')-julianday(timestamp))*24<{hours_time_period}\
        ORDER BY timestamp ASC"
    ).fetchall()
    average_point=db.execute(
        f"SELECT AVG(value) FROM temperature \
        WHERE (julianday('now')-julianday(timestamp))*24<{hours_time_period}"
    ).fetchone()
    average_reference_point=db.execute(
        f"SELECT AVG(reference_value) FROM temperature \
        WHERE (julianday('now')-julianday(timestamp))*24<{hours_time_period}"
    ).fetchone()

    if sample_points is None or average_point is None or average_reference_point is None:
        return jsonify({
            "status":"No data available"
        })

    result=[]
    for entry in sample_points:
        result.append({"value":entry["value"],"reference_value":entry["reference_value"]})
    return jsonify({
        "status":"Data succesfully retrieved",
        "data":{
            "average":average_point[0],
            "history":result
        }
    })

def mqtt_on_message(client,userdata,msg):
    reference_temperature=weather_api.get_reference_temperature()

    sensor_topic=root_topic+sensor_root_topic
    if not sensor_topic==msg.topic:
        return

    print(f"Temperature: received {msg.payload.decode()} from {msg.topic} topic")

    json_msg=json.loads(msg.payload.decode())

    # Save received state
    db=get_db()
    db.execute(f"INSERT INTO temperature(value,reference_value) VALUES ({json_msg['value']},{reference_temperature})")
    db.commit()
