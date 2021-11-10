# IoT Dataset - Hub App
Hub App for the IoT Dataset
  
This is the repository for the hub app of the IoT Dataset project. 
  
For each IoT app in the Dataset, openapi-generator will be run, and the app-api-client will be generated. 
  
`app.py` is the hub app, that will import all the generated app-api-clients, and orchestrate different information flows between them. 

## Prerequisites

To generate new app-api-clients you will need to follow [the instalation instructions](https://github.com/OpenAPITools/openapi-generator) for openapi-generator.

## Installation notes
Clone this repo recursively to get the apps source code:

```
git clone --recursive https://github.com/unibuc-cs/iot-dataset-hub-app.git
```

## Run the Hub App

This setup has been tested with Python 3.8.10.

`python app.py` 

## Running the setup on Docker

We provide a `docker-compose` script that fetches, builds and starts the apps and the hub.

To start the whole network, run:
```
docker-compose up -d
``` 

If you want to interact with the applications, you can change the code of the [hub app](https://github.com/unibuc-cs/iot-dataset-hub-app), rebuild the image and restart the composer. If you want live updates, mount the directory of the hub app as a volume inside the docker container. (TODO add instructions for this)

### IoT applications
* https://github.com/unibuc-cs/iot-dataset-hub-app (the hub)
* https://github.com/unibuc-cs/FlowerPower
* https://github.com/unibuc-cs/smarteeth
* https://github.com/unibuc-cs/SmartKettle
* https://github.com/unibuc-cs/SmartTV-Alpha-X
* https://github.com/unibuc-cs/WindWow

***Notes***

1. All applications start with a delay of 1 second
2. There is a single MQTT server runing on the network (hostname `mqtt_server`). All applications connect to it.
3. Check if everything started correctly by running `./test.sh`

## To Do

- Create a python environment to containerize the libraries used by the project
- Build a tutorial, 
