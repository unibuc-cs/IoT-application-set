#!/bin/sh

apt install -y software-properties-common build-essential g++ \
        mosquitto mosquitto-clients libmosquitto-dev rapidjson-dev libomp-dev \
        cmake && \
    add-apt-repository ppa:pistache+team/unstable && apt update -y && apt install -y libpistache-dev