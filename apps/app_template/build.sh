#!/bin/sh
if [ $(uname -m) = "x86_64" ]; then
	# TODO
elif [ $(uname -m) = "armv7l" ]; then
	# TODO
else
	echo "Unknown architecture"
	exit 1
fi
exit 0
