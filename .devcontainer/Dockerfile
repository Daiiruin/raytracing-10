FROM ubuntu:20.04

ENV TZ=Europe/Paris
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    cmake \
    libssl-dev \
    wget \
    locales \
    nlohmann-json3-dev && \
    locale-gen en_US.UTF-8

ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

WORKDIR /app

RUN mkdir -p /app/stb && \
    wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h -O /app/stb/stb_image_write.h

CMD ["/bin/bash"]
