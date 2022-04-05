#!/bin/sh

g++ -std=c++17 ../Server.cpp -o server -lpistache -lcrypto -lssl -lpthread -lboost_program_options && \
    chmod 755 ./server
