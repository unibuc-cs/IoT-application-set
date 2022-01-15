#!/bin/bash

USERNAME=andreiaoca 
TAG=amd64
PLATFORM=linux/amd64

docker buildx create --name sasha --platform $PLATFORM --use

docker buildx build -t $USERNAME/flowerpower:$TAG --push ../apps/flowerpower
docker buildx build -t $USERNAME/smartkettle:$TAG --push ../apps/smartkettle
docker buildx build -t $USERNAME/windwow:$TAG --push ../apps/windwow
docker buildx build -t $USERNAME/smarttv:$TAG --push ../apps/smarttv
docker buildx build -t $USERNAME/smarteeth:$TAG --push ../apps/smarteeth

docker buildx use default
docker buildx rm sasha
