# Local deployment on Raspberry Pi

## Apps List
- hub - Python - ported on RPI

- smartkettle - CPP - ported on RPi - 9081
- flowerpower - CPP - ported on RPi - 9082
- smarttv - CPP - ported on RPi - 9083
- windwow - CPP - ported on RPi - 9084

- smarteeth - CPP

- phillips - Rust

- smartoven - Python
- serasmart - Python
- soundsystem - Go

- MQTT Broker

## Dependencies

```bash
sudo apt install -y libboost-program-options-dev
```

## Build `libpistache` from source

There is no install candidate for `pistache` for RPI OS.

Follow the [instructions](https://github.com/pistacheio/pistache#building-from-source)
to build it from sources.

```bash
cd pistache

# Pistache dependencies
sudo apt install meson pkg-config libcurl4-openssl-dev rapidjson-dev

# Install config for RPI
meson setup build --buildtype=release\
	-DPISTACHE_USE_SSL=false \
	-DPISTACHE_BUILD_EXAMPLES=false \
	-DPISTACHE_BUILD_TESTS=false \
	-DPISTACHE_BUILD_DOCS=false \
	-DPISTACHE_ENABLE_NETWORK_TESTS=false \
	--prefix="$PWD/prefix"

meson install -C build
```

## Flower Power

```bash
cd apps/flowerpower

sudo apt install software-properties-common build-essential g++ \
        mosquitto mosquitto-clients libmosquitto-dev rapidjson-dev libomp-dev \
        cmake

mkdir build; cd build; ../build.sh

./main
```

## Smart TV

Same notes as `flowerpower`.

## Smart Kettle

```bash
sudo apt install software-properties-common g++ libboost-dev nlohmann-json3-dev libmosquitto-dev

mkdir build; cd build; ../build.sh

export LD_LIBRARY_PATH=../../../pistache/build/src

./server
```

## Windwow

Same notes as `smartkettle`.

## Hub

Generate clients:
```python
# Clean before
rm -rf ../hub/clients

python generate_clients.py -i ../apps/ -o ../hub/clients --apps smartkettle flowerpower smarttv windwow

# Edit the script below accordingly
cd hub
./changed_port.sh
python -u ./src/app.py
```
