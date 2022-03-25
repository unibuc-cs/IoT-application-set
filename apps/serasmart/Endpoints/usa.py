from flask import (
    Blueprint, request, jsonify
)
from flask_mqtt import Mqtt
import json

from db import get_db
from common import root_topic
import server_mqtt
import server_http

bp = Blueprint("usa", __name__, url_prefix="/usa")
gadget_root_topic="door/"

@bp.route("",methods=["POST"])
def handler_post():
    state=int(request.form['state'])
    
    server_mqtt.get_mqtt_queue().append((gadget_root_topic+"set",json.dumps(
        {"state":state}
    )))
    
    return jsonify({
        "status":"Command was queued"
    })


@bp.route("",methods=["GET"])
def handler_get():
    db=get_db()
    
    last_event_id=int(request.args["last_id"])

    # Obviously! This is a major sql injection bug. Still researching how to fix it in python
    last_event=db.execute(
        f"SELECT * FROM events \
        WHERE event_location='DOOR' AND id>{last_event_id}\
        ORDER BY timestamp DESC"
    ).fetchone()

    # No new event was found so trigger a new one
    if last_event is None:
        # Signal the gadget to resend its state
        server_mqtt.get_mqtt_queue().append((gadget_root_topic+"sync",""))

        return jsonify({
            "status":"There are no new events registered"
        })

    return jsonify({
        "status":"Event succesfully retrieved",
        "data":{
            "id":last_event["id"],
            "timestamp":last_event["timestamp"],
            "state":"CLOSED" if last_event["state"]==0 else "OPENED" 
        }
    })


def mqtt_on_message(client,userdata,msg):    
    gadget_topic=root_topic+gadget_root_topic+"update"
    if not gadget_topic==msg.topic:
        return

    print(f"Door: received {msg.payload.decode()} from {msg.topic} topic")

    json_msg=json.loads(msg.payload.decode())

    # Save received state
    db=get_db()
    db.execute(f"INSERT INTO events(event_location,state) VALUES ('DOOR',{json_msg['state']})")
    db.commit()
