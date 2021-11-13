#!/bin/sh
docker build -t thelittlewho/hub_app -f hub/Dockerfile . && docker push thelittlewho/hub_app:latest
