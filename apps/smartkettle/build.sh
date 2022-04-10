#!/bin/sh
if [ $(uname -m) = "x86_64" ]; then
	g++ ../smart_kettle.cpp -o main -lpistache -lboost_program_options -lmosquitto -lcrypto -lssl -lpthread  -std=c++17 && chmod 755 ./main
elif [ $(uname -m) = "armv7l" ]; then
	g++ ../smart_kettle.cpp -o main -I ../../../pistache/include -L ../../../pistache/build/src -lpistache -lboost_program_options -lmosquitto -lcrypto -lssl -lpthread  -std=c++17 && chmod 755 ./main
else
	echo "Unknown architecture"
	exit 1
fi
exit 0
