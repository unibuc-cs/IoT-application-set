FROM ubuntu:latest

# Dependencies
COPY ./deps_ubuntu.sh .
RUN apt update -y && apt upgrade -y && \
    echo 'tzdata tzdata/Areas select Europe' | debconf-set-selections && \
    echo 'tzdata tzdata/Zones/Europe select Paris' | debconf-set-selections && \
    DEBIAN_FRONTEND="noninteractive" apt install -y tzdata && \
    ./deps_ubuntu.sh && \
    apt update -y && apt install -y libpistache-dev

# Compile
COPY . /app
WORKDIR /app
RUN g++ -std=c++17 Server.cpp -o server -lpistache -lcrypto -lssl -lpthread && \
    chmod 755 ./server

# Run
COPY ./delay.sh /delay.sh
RUN chmod 755 /delay.sh
EXPOSE 9080
RUN useradd -m dorel
USER dorel
CMD ["/delay.sh", "1", "./server"]
