#!/bin/bash
cd /mnt
path=$(find . -iname SmartWindow 2>/dev/null -print -quit)
cd $path
g++ Server.cpp -o server -lpistache -lcrypto -lssl -lpthread && ./server
