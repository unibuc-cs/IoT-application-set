#!/bin/sh

g++ ../smart_kettle.cpp -o main -lpistache -lmosquitto -lcrypto -lssl -lpthread  -lboost_program_options -std=c++17
