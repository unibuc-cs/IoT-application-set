FROM alpine:latest

RUN apk update && apk add python3 wget openjdk11-jre

RUN mkdir -p /opt/openapi-generator/modules/openapi-generator-cli/target/
RUN wget https://repo1.maven.org/maven2/org/openapitools/openapi-generator-cli/5.3.1/openapi-generator-cli-5.3.1.jar \
	-O /opt/openapi-generator/modules/openapi-generator-cli/target/openapi-generator-cli.jar

COPY ./generate_clients.py /usr/bin/generate_clients
RUN chmod +x /usr/bin/generate_clients

VOLUME [ "/apps" ]
VOLUME [ "/clients" ]

CMD [ "generate_clients", "/apps", "/clients" ]
