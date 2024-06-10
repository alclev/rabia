FROM ubuntu:latest

RUN apt-get update -y
RUN apt-get upgrade -y

COPY requirements.txt .

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y $(cat requirements.txt)
CMD ["sh", "-c", "git clone https://github.com/sss-lehigh/remus.git && ./remus/tools/install.sh"]

WORKDIR "/root"