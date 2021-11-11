version=latest

build:
	docker image build -t smart_kettle_img:latest .

# `-p` exposes the port outside the Docker container 
run: build
	docker run -it -p 9080:9080 --name smart_kettle smart_kettle_img:${version} /bin/bash

test:
	curl -X GET http://localhost:9080/boilLiquidByViscosity

clean:
	docker rm -f smart_kettle

clean_all:
	docker rm -f smart_kettle
	docker image rm smart_kettle_img:${version}
