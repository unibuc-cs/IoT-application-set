#!/bin/sh

java -jar openapi-generator-cli.jar generate -i ../SmartKettle/openapi.yaml -g python -o ./clients/smartkettle -c ./configs/smartkettle.json
pip3 install ./clients/smartkettle
