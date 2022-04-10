#!/bin/bash

echo "Install dependencies"
sudo apt install -y software-properties-common cmake g++ libboost-dev \
	libboost-program-options-dev nlohmann-json3-dev \
	libmosquitto-dev mosquitto mosquitto-clients \
	meson pkg-config libcurl4-openssl-dev rapidjson-dev \
	rapidjson-dev libomp-dev


echo "Init pistache"
git submodule update --init

echo "Build pistache"
cd pistache && \
	meson setup build --buildtype=release\
		-DPISTACHE_USE_SSL=false \
		-DPISTACHE_BUILD_EXAMPLES=false \
		-DPISTACHE_BUILD_TESTS=false \
		-DPISTACHE_BUILD_DOCS=false \
		-DPISTACHE_ENABLE_NETWORK_TESTS=false \
		--prefix="$PWD/prefix" && \
	meson install -C build && \
	cd -

echo "Start building apps..."
cd apps/flowerpower && mkdir build; cd build; ../build.sh && cd -
cd apps/windwow && mkdir build; cd build; ../build.sh && cd -
cd apps/smartkettle && mkdir build; cd build; ../build.sh && cd -
cd apps/smarttv && mkdir build; cd build; ../build.sh && cd -
echo "Apps built succesfully"

echo "Generate clients"
rm -rf hub/clients

cd client_builder && \
	./generate_clients.py -i ../apps/ -o ../hub/clients \
	--apps smartkettle flowerpower smarttv windwow && \
	cd -

cd hub
# ./changed_port.sh
python3 -m pip install -r requirements.txt
python3 -m pip install -r src/requirements.txt
python3 -u ./src/app.py
cd src && behave
