# SmartWindow
Windwow

## Raport de analiza:

### V1 : https://docs.google.com/document/d/1sND3OpOalYHy4aKE5gNf8ZgjmpYiduXQ/edit#

### V2 : https://docs.google.com/document/d/1GqnBhBT4BkBZZGLvEQcNeaEDXbutiNaM/edit#


## Trello :
### https://trello.com/b/OzGB4Jo6



## Cerinte de sistem :
- Linux -> de preferat ubuntu 18 / 20
- Windows -> WSL -> de preferat ubuntu 18 / 20



## Ce trebuie instalat :

- Windows -> WSL 2 -> de preferant ubuntu 20
- pistache 
- nlohmann
- mosquitto
- cmake
- gcc care suporta versiuni de c++ >= 17 



## Pistache start and test

### For Linux :

```
sudo add-apt-repository ppa:pistache+team/unstable
sudo apt update
sudo apt install libpistache-dev
sudo apt-get install -y nlohmann-json-dev.
```

### For WSL :

```
git clone --recurse-submodules https://github.com/pistacheio/pistache.git
cd pistache
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```


### Pistache server


#### From console run :

```
g++ Server.cpp -o server -lpistache -lcrypto -lssl -lpthread && ./server
or
g++ Server.cpp -std=c++17 -o server -lpistache -lcrypto -lssl -lpthread && ./server
```

#### In another console and run:
```
curl -X GET http://localhost:9080/settings/air_quality
curl -X POST http://localhost:9080/settings/air_quality/25
```

#### Send in-place or out-of-place header

```
curl -X POST -H "Content-Type: application/json" -d '{"date":"2021-03-23","luminosity":"100", "temperature":"50", "humidity": "120"}' localhost:9080/settings
curl -X POST -H "Content-Type: application/json" -d @window_settings.json http://localhost:9080/settings
curl -X POST -H "Content-Type: application/json" -d @user_settings.json http://localhost:9080/userSettings
mosquitto_pub -t test/t1 -m "impact: 10"
```


### Mosquitto server 


#### From console run :

```
mosquitto -v
```

#### In another console and run :

```
g++ ServerMQTT.cpp -o server -lmosquitto -lpistache -lcrypto -lssl -lpthread && ./server
```

#### In another console and run :

```
mosquitto_pub -t test/t1 -m "MESAJ"
```

 
