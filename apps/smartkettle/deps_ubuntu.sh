#!/bin/sh

apt install -y software-properties-common g++ libboost-dev nlohmann-json3-dev libmosquitto-dev && \ 
    add-apt-repository ppa:pistache+team/unstable && apt update -y && apt install -y libpistache-dev && \
    apt update -y && apt install -y mosquitto mosquitto-clients