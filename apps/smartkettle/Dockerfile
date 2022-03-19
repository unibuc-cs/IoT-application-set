FROM ubuntu:latest

# Dependencies
COPY ./deps_ubuntu.sh .
RUN apt update -y && apt upgrade -y && \
    ./deps_ubuntu.sh && \
    apt install -y curl wget nmap vim

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
