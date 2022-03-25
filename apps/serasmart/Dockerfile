FROM ubuntu:latest

ENV DEBIAN_FRONTEND="noninteractive"
RUN apt update && apt install python3 python3-pip -y

WORKDIR /project

RUN python3 -m pip install flask flask-mqtt pyyaml

COPY ./ .

CMD ["python3", "-u", "./app.py"]