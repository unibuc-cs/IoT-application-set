FROM ubuntu:latest

# Dependencies
COPY ./deps_ubuntu.sh .
RUN apt update -y && apt upgrade -y && \
    echo 'tzdata tzdata/Areas select Europe' | debconf-set-selections && \
    echo 'tzdata tzdata/Zones/Europe select Paris' | debconf-set-selections && \
    DEBIAN_FRONTEND="noninteractive" apt install -y tzdata && \
    ./deps_ubuntu.sh && \
    add-apt-repository ppa:pistache+team/unstable && apt update -y && apt install -y libpistache-dev && \
    apt install -y curl wget nmap vim

# Compile
COPY . /app
WORKDIR /app
RUN mkdir build && cd build && ../build.sh
RUN chmod 755 ./build/main

# Run
RUN chmod 755 ./delay.sh
EXPOSE 9080
RUN useradd -m mock_user
USER mock_user
CMD ["./delay.sh", "1", "./run.sh"]
