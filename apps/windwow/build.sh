#!/bin/sh
if [ $(uname -m) = "x86_64" ]; then
	g++ -std=c++17 ../Server.cpp -o main -lpistache -lcrypto -lssl -lpthread -lboost_program_options && chmod 755 ./main
elif [ $(uname -m) = "armv7" ]; then
	g++ -std=c++17 ../Server.cpp -o main -I ../../../pistache/include -L ../../../pistache/build/src -lpistache -lcrypto -lssl -lpthread -lboost_program_options && chmod 755 ./main
else
	echo "Unknown architecture"
	exit -1
fi
exit 0
