FROM ubuntu:latest

ENV DEBIAN_FRONTEND="noninteractive"
RUN apt update && apt install python3 python3-pip wget openjdk-11-jdk -y

WORKDIR /project

COPY ./apps/flowerpower/openapi.yaml ./flowerpower-openapi.yaml 
COPY ./apps/smarteeth/openapi.yaml ./smarteeth-openapi.yaml 
COPY ./apps/smarttv/openapi.yaml ./smarttv-openapi.yaml 
COPY ./apps/windwow/openapi.yaml ./windwow-openapi.yaml 
COPY ./apps/smartkettle/swagger.yaml ./smartkettle-openapi.yaml 
COPY ./hub/configs ./configs
COPY ./hub/features ./features
COPY ./hub/generate_clients.py .

RUN mkdir -p mkdir -p /opt/openapi-generator/modules/openapi-generator-cli/target/
RUN wget https://repo1.maven.org/maven2/org/openapitools/openapi-generator-cli/5.3.1/openapi-generator-cli-5.3.1.jar \
	-O /opt/openapi-generator/modules/openapi-generator-cli/target/openapi-generator-cli.jar

RUN mkdir -p clients
RUN chmod +x ./generate_clients.py && ./generate_clients.py

COPY ./requirements.txt .
RUN python3 -m pip install -r requirements.txt

COPY ./hub/app.py .
CMD ["python3", "-u", "./app.py"]
