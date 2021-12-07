# IoT Dataset - Hub App
Hub App for the IoT Dataset

This is the repository for the hub app of the IoT Dataset project. 
  
For each IoT app in the Dataset, openapi-generator will be run, and the app-api-client will be generated. 
  
`app.py` is the hub app, that will import all the generated app-api-clients, and orchestrate different information flows between them. 

## Contents
- [Repo Navigation](#repo-navigation)
- [Prerequisites](#prerequisites)
- [Installation Notes](#installation-notes)
- [Development environment](#development-environment)
- [IoT Applications References](#iot-applications-references)
- [Notes](#notes)
- [Artificially introduced bugs](#artificially-introduced-bugs)

## Repo Navigation

    .
    ├── apps                     # Source code for the smart appliances apps. 
    ├── hub                      # Source code for the hub app.
    ├── docker-compose.yml       # Docker script to start up the entire network.
    ├── mosquitto.conf           # Configs for the mosquitto server.
    ├── requirements.txt         # Packages dependencies
    ├── test-network.sh     # Script to test the network.
    └── README.md

## Prerequisites

To generate new app-api-clients you will need to follow [the instalation instructions](https://github.com/OpenAPITools/openapi-generator) for openapi-generator.

## Installation Notes

We provide a `docker-compose` script that builds and starts the apps and the hub.

To start the whole network, run:
```
docker-compose up -d
``` 

To sent packages to one of the apps, one can attach to the hub container:
```
docker exec -it <hub_container_name> /bin/bash
# curl -I -X GET http://<app_container_hostname>:9080/warmLiquid/80/celsius
curl -X GET http://iot-dataset-hub-app-smartkettle-1:9080/warmLiquid/80/celsius
```

To sent requests from the local machine without attaching to the containers, run:
```
# curl -X GET http://localhost:<app_container_port>/warmLiquid/80/celsius
curl -X GET http://localhost:9082/warmLiquid/80/celsius
```

To stop the containers, run:
```
docker-compose stop
```

To clean the containers created, run:
```
docker-compose down
```

To clean everything (containers, images, network), run:
```
docker-compose down --rmi all
```

## Development environment

If you want to develop any of the applications or the hub, there are two smoother ways than
using the default `docker-compose.yml` file. 

* use `docker-compose.dev.yml` - it will build images from the local directory instead of pulling
them from the remote repository. Unfortunately, after rebuilding an image you will have to
restart the entire composer session or to manually recreate the container of the service you are
targeting. (eg. `docker-compose -f docker-compose.dev.yml up --build --force-recreate <service>` in a
different terminal)

* use `dev.py` - it manages individual docker containers. See `./dev.py -h` for more information.

***Notes***

1. All applications start with a delay of 1 second.
2. There is a single MQTT server runing on the network (hostname `mqtt_server`). All applications connect to it.
3. Check if everything started correctly by running `./test-network.sh`.

## IoT Applications References

* https://github.com/unibuc-cs/iot-dataset-hub-app (the hub)
* https://github.com/unibuc-cs/FlowerPower
* https://github.com/unibuc-cs/smarteeth
* https://github.com/unibuc-cs/SmartKettle
* https://github.com/unibuc-cs/SmartTV-Alpha-X
* https://github.com/unibuc-cs/WindWow

## Artificially introduced bugs

Bugs introduced in the applications for testing reasons:
* invalid memory access (segmentation fault) in windwow. Trigger:
```
curl -X 'POST' \
  'http://localhost:9084/settings/luminosity/9999' \
  -H 'accept: text/plain' \
  -d ''
```
* no response from server in windwow. Trigger:
```
curl -X 'GET' \
  'http://localhost:9084/settings/invalid' \
  -H 'accept: text/plain'
```
