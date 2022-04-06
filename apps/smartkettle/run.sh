#!/bin/bash

[ $# -eq 0 ] && { echo "Usage: $0 port"; exit 1; }

LD_LIBRARY_PATH=../../../pistache/build/src ./build/main --port $1
