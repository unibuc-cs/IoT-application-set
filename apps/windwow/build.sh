#!/bin/sh

g++ -std=c++17 ../Server.cpp -o server -I ../../../pistache/include -L ../../../pistache/build/src -lpistache -lcrypto -lssl -lpthread -lboost_program_options && \
    chmod 755 ./server
