#!/bin/sh

java -jar openapi-generator-cli.jar generate -i ./WindWow/openapi.yaml -g python -o ./clients/windwow_api_client -c ./configs/windwow.json
pip3 install ./clients/windwow_api_client
