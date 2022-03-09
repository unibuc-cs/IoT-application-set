FROM jfloff/alpine-python:latest

WORKDIR /app
COPY . .

# Install packages
RUN apk add --update mosquitto mosquitto-clients
RUN pip install --upgrade pip && pip install -r ./requirements.txt

# Expose MQTT port
EXPOSE 1883
