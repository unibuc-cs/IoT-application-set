FROM ubuntu:latest

ENV DEBIAN_FRONTEND="noninteractive"
RUN apt update && apt install python3 python3-pip -y

WORKDIR /project

COPY ./requirements.txt .
RUN python3 -m pip install -r requirements.txt

COPY ./ .

CMD ["python3", "-u", "./app.py"]
