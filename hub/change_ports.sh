#!/bin/bash

sed -i 's/smartkettle:[0-9][0-9][0-9][0-9]/localhost:9081/g' clients/mergedclients/mergedclients/all.py
sed -i 's/flowerpower:[0-9][0-9][0-9][0-9]/localhost:9082/g' clients/mergedclients/mergedclients/all.py
sed -i 's/smarttv:[0-9][0-9][0-9][0-9]/localhost:9083/g' clients/mergedclients/mergedclients/all.py
sed -i 's/windwow:[0-9][0-9][0-9][0-9]/localhost:9084/g' clients/mergedclients/mergedclients/all.py

