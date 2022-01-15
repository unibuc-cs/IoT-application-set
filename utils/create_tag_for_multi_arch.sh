#!/bin/sh

# TODO - Create a TAG_LIST = (amd64 arm etc.) variable and use it to expand 
# a list to create the manifest

USERNAME=andreiaoca

docker manifest create $USERNAME/flowerpower:latest $USERNAME/flowerpower:amd64 \
	$USERNAME/flowerpower:arm
docker manifest push $USERNAME/flowerpower:latest

docker manifest create $USERNAME/smartkettle:latest $USERNAME/smartkettle:amd64 \
	$USERNAME/smartkettle:arm
docker manifest push $USERNAME/smartkettle:latest

docker manifest create $USERNAME/windwow:latest $USERNAME/windwow:amd64 \
	$USERNAME/windwow:arm
docker manifest push $USERNAME/windwow:latest

docker manifest create $USERNAME/smarttv:latest $USERNAME/smarttv:amd64 \
	$USERNAME/smarttv:arm
docker manifest push $USERNAME/smarttv:latest

docker manifest create $USERNAME/smarteeth:latest $USERNAME/smarteeth:amd64 \
	$USERNAME/smarteeth:arm
docker manifest push $USERNAME/smarteeth:latest
