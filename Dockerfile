FROM ubuntu:latest

RUN apt-get update -y
RUN apt-get upgrade -y

COPY requirements.txt .

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y $(cat req.list)

WORKDIR "/root"