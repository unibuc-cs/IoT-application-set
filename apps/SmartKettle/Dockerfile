FROM ubuntu:latest

# Dependencies
RUN apt update -y && apt upgrade -y
RUN apt install -y software-properties-common g++ libboost-dev nlohmann-json3-dev libmosquitto-dev 
RUN add-apt-repository ppa:pistache+team/unstable && apt update -y && apt install -y libpistache-dev
RUN apt update -y && apt install -y mosquitto mosquitto-clients

# Debugging
RUN apt install -y curl wget nmap vim

# Compile
COPY . /app
WORKDIR /app
RUN g++ smart_kettle.cpp -o main -lpistache -lmosquitto -lcrypto -lssl -lpthread  -std=c++17
RUN chmod 755 ./main

# Run
COPY ./delay.sh /delay.sh
RUN chmod 755 /delay.sh
EXPOSE 9080
RUN useradd -m mock_user
USER mock_user
CMD ["/delay.sh", "1", "./main"]
