#!/bin/bash

[ $# -eq 0 ] && { echo "Usage: $0 port"; exit 1; }

./build/demo/main --port $1

