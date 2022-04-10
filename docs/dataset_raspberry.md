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
sudo apt install -y software-properties-common cmake g++ libboost-dev \
	libboost-program-options-dev nlohmann-json3-dev \
	libmosquitto-dev mosquitto mosquitto-clients \
	meson pkg-config libcurl4-openssl-dev rapidjson-dev \
	rapidjson-dev libomp-dev
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

## Build and run app

```bash
cd apps/<app> && mkdir build; cd build; ../build.sh
./main <port>
```

***Notes***
 - `flowerpower` and `smarttv` are built via CMake.
 - `smartkettle` and `windwow` are built via `build.sh` with `g++`.

## Hub

Generate clients:
```bash
# Clean before
rm -rf ../hub/clients

./generate_clients.py -i ../apps/ -o ../hub/clients --apps smartkettle flowerpower smarttv windwow

# Edit the script below accordingly
python3 -m pip install -r requirements.txt
python3 -m pip install -r src/requirements.txt
cd hub && ./changed_port.sh
python -u ./src/app.py
cd src && behave
```
