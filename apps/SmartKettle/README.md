# Smart Kettle App

### Requirements

```bash
// boost
sudo apt-get install libboost-dev

// g++
sudo apt install g++


// nlohmann - json formatter
sudo apt-get install nlohmann-json3-dev

// Pistache
sudo add-apt-repository ppa:pistache+team/unstable
sudo apt update
sudo apt install libpistache-dev

// Mosquitto (MQTT)
sudo apt install mosquitto mosquitto-clients
```

### Compile and run

```bash
g++ smart_kettle.cpp -o main -lpistache -lmosquitto -lcrypto -lssl -lpthread  -std=c++17

./main
```

### Test with Docker
One can build and test the app using Docker. Inside the repo, you can find a `Dockerfile` and a `Makefile` for convenience.

To build the Docker image locally run:
```bash
$ make
```

View the available images with:
```bash
$ docker image ls
```

To run a container that has all the dependencies installed and the app compiled run:
```bash
$ make run
```

### HTTP

#### 1. Warm liquid at the specified temperature

GET /warmLiquid/temperature/scale

```bash
curl -X GET http://localhost:9080/warmLiquid/80/celsius
```

```json
{
  "message": "Kettle settings saved. The water is warming at 80 degrees celsius",
  "timestamp": "Tue Jul 13 10:08:29 2021"
}
```
#### 2. Find the viscosity of the containing liquid and set the recommended boiling temperature

GET /boilLiquidByViscosity

```bash
curl -X GET http://localhost:9080/boilLiquidByViscosity
```

The kettle uses the information from the viscosity sensor to find the optimal temperature of the containing liquid.

```json
{
  "message": "The temperature has been set to 90 degrees",
  "timestamp": "Tue May 25 09:27:18 2021"
}
```

#### 3. Make tea

POST /makeTea

```bash
curl -H "Content-Type: application/json" -X POST -d '{"keepWarm":'true', "temperature": {"temperature":"100", "scale":"C"}, "time":'5'}' http://localhost:9080/makeTea
```

The kettle boils the water to the specified temperature, inserts the tea infuser into the water for a certain amount of time and after the infusion it keeps your tea warm.

Input format:

```json
{
  "keepWarm": true,
  "temperature": {
    "temperature": "100",
    "scale": "C"
  },
  "time": 5
}
```

Output format:

```json
{
  "message": "Preparing your tea...The temperature has been set to 100 C degrees. Infusion time: 5 minutes. ",
  "timestamp": "Tue May 25 09:33:03 2021"
}
```

#### 4. Set a recurrent boiling schedule

POST /warmLiquidByDate

```bash
curl -H "Content-Type: application/json" -X POST -d '{"recurrent":'true', "temperature": {"temperature":"30", "scale":"F"}, "hour":"22:30"}' http://localhost:9080/warmLiquidByDate
```

Set a recurring event if you want to prepare your drink at a certain hour of the day.

Input format:

```json
{
  "recurrent": true,
  "temperature": {
    "temperature": "30",
    "scale": "F"
  },
  "hour": "22:30"
}
```

Output format:

```json

{
  "message": "Scheduler is set at 22:30. Temperature: 50 degrees F. ",
  "timestamp": "Tue May 25 09:41:48 2021"
}
```

#### 5. Stir the liquid at the specified rpm

GET /stirLiquid/rmp

```bash
curl -X GET http://localhost:9080/stirLiquid/1000
```

```json
{
  "message": "Started stirring the content of the kettle at 1000 rmp",
  "timestamp": "Tue Jul 13 11:25:08 2021"
}
```

### MQTT

1. Warm tea

```bash
mosquitto_sub -t kettle/temp/70/C -C 1
```

2. Get scheduler settings

```bash
mosquitto_sub -t kettle/scheduler -C 1
```

3. Get viscosity of the containing liquid and the recommended temperature

```bash
mosquitto_sub -t kettle/viscosity -C 1
```

### Team Members
<hr/>

- Busuioc Andrei
- Iamandii Ana-Maria
- Manea Cristina Larisa
- Nazare Daniela Andreea
- Rusu Iuliana
- Talmacel Sergiu-Victor
