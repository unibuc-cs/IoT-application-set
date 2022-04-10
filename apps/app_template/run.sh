#!/bin/bash

if [ $(uname -m) = "x86_64" ]; then
	./build/main
elif [ $(uname -m) = "armv7l" ]; then
	[ $# -eq 0 ] && { echo "Usage: $0 port"; exit 1; }
	LD_LIBRARY_PATH=../../../pistache/build/src ./build/main --port $1
else
	echo "Unknown architecture"
	exit 1
fi
exit 0
