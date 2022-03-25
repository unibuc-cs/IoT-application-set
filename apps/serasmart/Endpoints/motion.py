from flask import (
    Blueprint, request, jsonify
)
from flask_mqtt import Mqtt
import json

from db import get_db
from common import root_topic
import server_mqtt
import server_http

bp = Blueprint("miscare", __name__, url_prefix="/miscare")
sensor_root_topic = "motion"


@bp.route("", methods=["GET"])
def handler_get():
    db = get_db()

    # Obviously! This is a major sql injection bug. Still researching how to fix it in python
    last_event = db.execute(
        f"SELECT * FROM motion \
        ORDER BY timestamp DESC"
    ).fetchone()

    # No new event was found so trigger a new one
    if last_event is None:
        return jsonify({
            "status": "There are no new events registered"
        })

    return jsonify({
        "status": "Sensor succesfully read",
        "data": {
            "id": last_event["id"],
            "timestamp": last_event["timestamp"],
            "area": last_event["area"],
            "duration": last_event["duration"],
            "strength": last_event["value"]
        }
    })


@bp.route("/statistics", methods=["GET"])
def handler_get_history():
    db = get_db()
    hours_time_period = float(request.args["time_period"])
    sample_points = db.execute(
        f"SELECT timestamp,area,duration,value FROM motion \
        WHERE (julianday('now')-julianday(timestamp))*24<{hours_time_period}\
        ORDER BY timestamp ASC"
    ).fetchall()

    if sample_points is None:
        return jsonify({
            "status": "No data available"
        })

    result = []
    for entry in sample_points:
        result.append({"timestamp": entry["timestamp"], "area": entry["area"], "duration": entry["duration"],
                       "strength": entry["value"]})

    return jsonify({
        "status": "Data succesfully retrieved",
        "data": {
            "history": result
        }
    })


def mqtt_on_message(client, userdata, msg):
    sensor_topic = root_topic + sensor_root_topic
    if not sensor_topic == msg.topic:
        return

    print(f"Motion: received {msg.payload.decode()} from {msg.topic} topic")

    json_msg = json.loads(msg.payload.decode())

    # Save received state
    db = get_db()
    db.execute(
        f"INSERT INTO motion(area,duration,value) VALUES ({json_msg['area']},{json_msg['duration']},{json_msg['value']})")
    db.commit()
