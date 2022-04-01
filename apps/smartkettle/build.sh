#!/bin/sh

g++ ../smart_kettle.cpp -o main -I ../../../pistache/include -L ../../../pistache/build/src -lpistache --lboost_program_options -lmosquitto -lcrypto -lssl -lpthread  -std=c++17

