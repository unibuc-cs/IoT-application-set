#!/bin/bash

[ $# -eq 0 ] && { echo "Usage: $0 port"; exit 1; }

if [ $(uname -m) = "x86_64" ]; then
	./build/main --port $1
elif [ $(uname -m) = "armv7l" ]; then
	LD_LIBRARY_PATH=../../../pistache/build/src ./build/main --port $1
else
	echo "Unknown architecture"
	exit 1
fi
exit 0
