#!/bin/bash

# [ $# -eq 0 ] && { echo "Usage: $0 port"; exit 1; }

if [ $(uname -m) = "x86_64" ]; then
	python app.py
elif [ $(uname -m) = "armv7l" ]; then
	# TODO
	echo ""
else
	echo "Unknown architecture"
	exit 1
fi
exit 0
