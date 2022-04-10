#!/bin/sh

apt install -y software-properties-common g++ libboost-dev \
	libboost-program-options-dev nlohmann-json3-dev libmosquitto-dev \
	cmake mosquitto mosquitto-clients pkg-config --fix-missing
