#!/bin/sh

g++ ../smart_kettle.cpp -o main -lpistache -lmosquitto -lcrypto -lssl -lpthread  -std=c++17