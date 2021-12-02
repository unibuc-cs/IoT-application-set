FROM openapitools/openapi-generator-cli

RUN apt update && apt install python3 python3-pip -y

WORKDIR /project

COPY ./apps/flowerpower/openapi.yaml ./flowerpower-openapi.yaml 
COPY ./apps/smarteeth/openapi.yaml ./smarteeth-openapi.yaml 
COPY ./apps/smarttv/openapi.yaml ./smarttv-openapi.yaml 
COPY ./apps/windwow/openapi.yaml ./windwow-openapi.yaml 
COPY ./apps/smartkettle/swagger.yaml ./smartkettle-openapi.yaml 
COPY ./hub/configs ./configs
COPY ./hub/features ./features
COPY ./hub/generate_clients.py .

RUN mkdir -p clients
RUN chmod +x ./generate_clients.py && ./generate_clients.py

COPY ./requirements.txt .
RUN python3 -m pip install -r requirements.txt

COPY ./hub/app.py .
CMD ["python3", "-u", "./app.py"]
