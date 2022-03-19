#!/bin/sh

g++ -std=c++17 ../Server.cpp -o server -lpistache -lcrypto -lssl -lpthread && \
    chmod 755 ./server