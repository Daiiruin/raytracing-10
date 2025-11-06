FROM ubuntu:20.04

ENV TZ=Europe/Paris
RUN \   
  apt update && DEBIAN_FRONTEND=noninteractive apt install --assume-yes build-essential cmake libssl-dev 

WORKDIR /app
