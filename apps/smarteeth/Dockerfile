FROM ubuntu:latest

# Dependencies
RUN apt update -y && apt upgrade -y
RUN apt install -y software-properties-common g++ nlohmann-json3-dev
RUN add-apt-repository ppa:pistache+team/unstable && apt update -y && apt install -y libpistache-dev

RUN apt install -y gcc make cmake cmake-gui cmake-curses-gui libssl-dev git

RUN git clone https://github.com/eclipse/paho.mqtt.c.git && \
    cd paho.mqtt.c && \
    git checkout v1.3.8 && \
    cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON && \
    cmake --build build/ --target install && \
    ldconfig

RUN apt install -y doxygen graphviz

RUN git clone https://github.com/eclipse/paho.mqtt.cpp && cd paho.mqtt.cpp && \ 
    cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE && \
    cmake --build build/ --target install && \
    ldconfig

# Debugging
RUN apt install -y curl wget nmap

# Compile
COPY . /app
WORKDIR /app
RUN make build && chmod 755 ./smarteeth

# Run
COPY ./delay.sh /delay.sh
RUN chmod 755 /delay.sh
EXPOSE 9080
RUN useradd -m dorel
USER dorel
CMD ["/delay.sh", "1", "./smarteeth"]
