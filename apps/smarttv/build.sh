#!/bin/sh

if [ $(uname -m) = "x86_64" ]; then
	cmake .. && cmake --build . && chmod 755 ./main
elif [ $(uname -m) = "armv7l" ]; then
	cp CMakeLists.txt CMakeLists_x86.txt
	mv CMakeLists_ARM.txt CMakeLists.txt
	cmake .. && cmake --build . && chmod 755 ./main
else
	echo "Unknown architecture"
	exit 1
fi
exit 0

