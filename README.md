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
- [Behaviour driven testing](#behaviour-driven-testing)
- [Fuzzing](#fuzzing)

## Repo Navigation

    .
    ├── apps                     # Source code for the smart appliances apps. 
    ├── hub                      # Source code for the hub app.
    ├── docker-compose.yml       # Docker script to start up the entire network.
    ├── mosquitto.conf           # Configs for the mosquitto server.
    ├── requirements.txt         # Packages dependencies
    ├── test-network.sh          # Script to test the network.
    └── README.md

## Prerequisites

To generate new app-api-clients you will need to follow [the instalation instructions](https://github.com/OpenAPITools/openapi-generator) for openapi-generator.

## Installation Notes

First, you need to install the requirements for our command line tool.
```
pip install -r requirements.txt
```

Now, you can use `./dev` or `python3 ./dev` CLI tool to manage the project. To install the dependencies
and build docker imges, use:
```
./dev init
```

**Local environment**: If you want to build the applications on your local machine instead
of using docker containers, you should do the following:

1. install the dependencies (only for Ubuntu at the moment): `./dev deps-ubuntu-local`
2. build your apps: `./dev build-local-all`

## Usage

To start the dataset, use:
```
./dev start-all
```

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

## Behaviour driven testing

After starting the dataset, use the following command to run the tests:
```
./dev run-functional-tests
```

## Fuzzing

After setting up the environment described above, you can bring the RESTler
fuzzer into the network to test the applications.

### Individual fuzzing

Individual fuzzers can be configured using `docker-composer` and the image provided
in `restler/Dockerfile`. For example, take a look at the configuration used to
test the `windwow` application (in `docker-compose.fuzzing.yaml`):
```
  windwow_restler:
    privileged: true
    build:
      context: ./restler
    networks:
      - iot_dataset # use the same netowrk where our apps are running
    volumes:
      # the target directory must contain an openapi.yaml specification
      - ./apps/windwow:/target
      # output logs of restler will be copied to this directory
      - ./restler/results/windwow:/results
```

Before running the fuzzer(s), be sure that you already started the target 
application(s) using the provided environment (see [Installation Notes](#installation-notes)). Then you can use the following command:
```
docker-compose -f docker-compose.fuzzing.yaml up
```

You should see the output from RESTler in your terminal and the logs
inside the volume you mounted.