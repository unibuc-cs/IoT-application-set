FROM ubuntu:20.04

# Dependencies
COPY ./deps_ubuntu.sh .
RUN apt update -y && apt upgrade -y && \
    echo 'tzdata tzdata/Areas select Europe' | debconf-set-selections && \
    echo 'tzdata tzdata/Zones/Europe select Paris' | debconf-set-selections && \
    DEBIAN_FRONTEND="noninteractive" apt install -y tzdata && \
    ./deps_ubuntu.sh && \
    apt install -y curl wget nmap

# Compile
COPY . /app
WORKDIR /app
RUN cmake . && cmake --build . && chmod 755 ./smart-tv

# Run
COPY ./delay.sh /delay.sh
RUN chmod 755 /delay.sh
EXPOSE 9080
RUN useradd -m dorel
USER dorel
CMD ["/delay.sh", "1", "./smart-tv"]
