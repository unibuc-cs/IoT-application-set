#!/bin/sh

apt install -y software-properties-common g++ nlohmann-json3-dev \
    mosquitto mosquitto-clients libmosquitto-dev cmake pkg-config --fix-missing && \
    add-apt-repository ppa:pistache+team/unstable && apt update -y && apt install -y libpistache-dev