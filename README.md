# IoT Dataset - Hub App
Hub App for the IoT Dataset

This is the repository contains a dataset to test IoT Smart Home networks for security vulnerabilities.

The main components are:
 - a central hub application `app.py` located in `hub`.
 - a Smart Home application dataset located in `apps`.

## Contents
- [Repo Navigation](#repo-navigation)
- [First Notes](#first-notes)
- [Installation Notes](#installation-notes)
- [How to add new apps](#how-to-add-new-apps)
- [IoT Applications References](#iot-applications-references)
- [Notes](#notes)
- [Artificially introduced bugs](#artificially-introduced-bugs)
- [Behaviour driven testing](#behaviour-driven-testing)
- [Fuzzing](#fuzzing)

## Repo Navigation

    .
    ├── apps                     # Source code for the smart appliances apps.
    ├── hub                      # Source code for the hub app.
    ├── restler                  # Fuzzer
    ├── docker-compose.dev.yml   # Docker script to start up the entire network.
    ├── docker-compose.prod.yml  # Docker script to start up the entire network.
    ├── docker-compose.prod.yml  # Docker script to start up the entire network.
    ├── dev                      # Helper script to build, run, start functional tests etc.
    ├── bug_unpatches            # Patches that are injected IoT/Smart Home bugs.
    ├── mosquitto.conf           # Configs for the mosquitto server.
    ├── requirements.txt         # Packages dependencies
    ├── test-network.sh          # Script to test the network.
    └── README.md

## First Notes

For each IoT app in the Dataset, `openapi-generator` will be run to generate the corresponding app-api-client.

To generate new app-api-clients you will need to follow [the instalation instructions](https://github.com/OpenAPITools/openapi-generator) for openapi-generator.

For now we are provinding a script at `/client-builders/generate_clients.py`. A command that will build a custom app list is the following:

```bash
python3 generate_clients.py -i ../apps/ -o ../hub/clients --apps smartkettle flowerpower smarttv windwow
```

`app.py` is the hub app, that will import all the generated app-api-clients, and orchestrate different information flows between them.

## Installation Notes

First, you need to install the requirements for our command line tool.
```
pip install -r requirements.txt
```

### Docker Deployment

You can use `./dev` or `python3 ./dev` CLI tool to manage the project.

To install the dependencies and build docker images, use:
```bash
./dev init
```

To start the dataset, use:
```bash
./dev start-all
```

### Local Deployment (x86)
If you want to build the applications on your local machine instead of using docker containers, you should do the following:

1. Install the dependencies and build the apps:
```bash
./dev deps-ubuntu-local
./dev build-local-all
```

2. Manually start each app on a different port. Example below:
```bash
./apps/flowerpower/build/run.sh 9081
./apps/smarttv/build/run.sh 9082
./apps/smartkettle/build/run.sh 9083
./apps/windwow/build/run.sh 9084
```

3. Generate API clients for the hub app:
```bash
cd client-builders/

mkdir -p /opt/openapi-generator/modules/openapi-generator-cli/target/
wget https://repo1.maven.org/maven2/org/openapitools/openapi-generator-cli/5.3.1/openapi-generator-cli-5.3.1.jar \
	-O /opt/openapi-generator/modules/openapi-generator-cli/target/openapi-generator-cli.jar

# Generate all clients
./generate_clients.py -i ../apps/ -o ../hub/clients

# Generate custom list of clients
./generate_clients.py -i ../apps/ -o ../hub/clients --apps smartkettle flowerpower smarttv windwow
```

4. Modify `clients/mergedclients/mergedclients/all.py` to reflect each client hostname and port. We are providing a useful script `hub/change_ports.sh` to do that. Modify it accordingly.
```bash
# Before running `hub/change_ports.sh` modify it to reflect your use case
cd hub && ./change_port.sh
```

5. Run the hub app:
```bash
cd hub
python3 -m pip install -r requirements.txt
python3 -m pip install -r src/requirements.txt
python3 -u src/app.py
```

6. Run functional tests:
```bash
cd hub/src && behave
```

### Local Deployment (ARM | RaspberryPi)

The deployment on RPi is more detailed in `docs/dataset_raspberry.md`.

The main difference is that `pistache` must be installed from sources.

To fire up the whole dataset, you must:

1. Install dependencies, `pistache`.
2. Build the apps, the hub.
3. Generate clients API with openapi-generator (e.g. `python generate_clients.py -i ../apps/ -o ../hub/clients --apps smartkettle flowerpower smarttv windwow`).
4. Start the apps using `./run.sh <port>` located in each app base folder.
5. Edit the script `hub/change_ports.sh` to match the hostname and the port for each app and execute the script `./change_ports.sh`.
6. Start the hub by executing `python -u src/app.py`.
7. To run the functional tests run `cd hub/src && behave`.

***Notes***

1. In the docker deployment, all applications start with a delay of 1 second.
2. There is a single MQTT server runing on the network (hostname `mqtt_server`). All applications connect to it.
3. Check if everything started correctly by running `./test-network.sh`.

## How to add new apps
To add new apps, copy the folder `apps/app_template`, add the sources to it and modify each helper script accordingly.

This template is used to easily/consistently integrate your app into the dataset:
It contains:
 - `Dockerfile`
 - `build.sh` script -  instructions to build the app on differen arches.
 - `run` script - instruction to run the app. It must expose the port.
 - `deps.sh` script - dependencies.
 - `openapi.yaml` - generate API client.

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
