# SmartTV Alpha X
 
## Setup ## 

After clone repo, need to install pistache and nlohmann.

### Install pistache
```
sudo add-apt-repository ppa:pistache+team/unstable
sudo apt update
sudo apt install libpistache-dev
```

### Install nlohmann
```
sudo apt-get install nlohmann-json3-dev
```

### Create CMakeFiles
```
cd <project>
cmake .
```

### Build
```
cmake --build .
```

### Run
```
./smart-tv
```

### If it doesn't work, try this:
```
https://github.com/facebook/Surround360/issues/3
```

## MQTT ##

### Install 
```
sudo apt-get update
sudo apt-get install mosquitto
sudo apt-get install mosquitto-clients
sudo apt-get update
sudo apt-get install libmosquitto-dev
```

### Initialize mosquitto
```
mosquitto -v
```

### Example publish subscription
```
mosquitto_pub -m "{\"id\":1,\"name\":\"test\"}" -t "test/t1"
```
