#!/bin/sh

apt install -y software-properties-common g++ nlohmann-json3-dev \
    mosquitto mosquitto-clients libmosquitto-dev cmake && \
    add-apt-repository ppa:pistache+team/unstable