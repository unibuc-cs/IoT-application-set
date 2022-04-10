#!/bin/sh

if [ $(uname -m) = "x86_64" ]; then
	cmake .. && cmake --build . && mv ./demo/main ./main && chmod 755 ./main
elif [ $(uname -m) = "armv7l" ]; then
	cp ../src/CMakeLists.txt ../src/CMakeLists_x86.txt
	mv ../src/CMakeLists_ARM.txt ../src/CMakeLists.txt
	cp ../demo/CMakeLists.txt ../demo/CMakeLists_x86.txt
	mv ../demo/CMakeLists_ARM.txt ../demo/CMakeLists.txt
	cmake .. && cmake --build . && mv ./demo/main ./main && chmod 755 ./main
else
	echo "Unknown architecture"
	exit 1
fi
exit 0
