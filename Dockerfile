FROM openapitools/openapi-generator-cli

RUN apt update
RUN apt install python3 python3-pip -y

WORKDIR /project

COPY ./FlowerPower/openapi.yaml ./flowerpower-openapi.yaml 
COPY ./smarteeth/swagger.yaml ./smarteeth-openapi.yaml 
COPY ./SmartTV-Alpha-X/openapi.yaml ./smarttv-openapi.yaml 
COPY ./WindWow/openapi.yaml ./windwow-openapi.yaml 
COPY ./SmartKettle/swagger.yaml ./smartkettle-openapi.yaml 
COPY ./configs ./configs
COPY ./generate_clients.py .

RUN mkdir -p clients
RUN chmod +x ./generate_clients.py && ./generate_clients.py

COPY ./requirements.txt .
RUN python3 -m pip install -r requirements.txt

COPY app.py .
CMD ["bash"]
#CMD [ "python3", "./app.py" ]