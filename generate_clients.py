#!/usr/bin/env python3

from os import system

apps = [
    "flowerpower",
    "smarteeth",
    "smarttv",
    "windwow",
    "smartkettle",
]

generator = "java -jar /opt/openapi-generator/modules/openapi-generator-cli/target/openapi-generator-cli.jar"
for app in apps:
    system(f"{generator} generate -i {app}-openapi.yaml -g python -o ./clients/{app} -c ./configs/{app}.json")