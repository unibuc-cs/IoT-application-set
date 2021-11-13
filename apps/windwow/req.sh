#!/bin/bash
cd /mnt
path=$(find . -iname SmartWindow 2>/dev/null -print -quit)
cd $path
for var in `seq 0 11`
do
  echo "Input sent no. $var"
  g++ user_cases.cpp -o user_cases && ./user_cases $var
  curl -X POST -H "Content-Type: application/json" -d @window_settings.json http://localhost:9080/settings
  sleep 5
done
