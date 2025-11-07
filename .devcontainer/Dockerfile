FROM ubuntu:22.04

ENV TZ=Europe/Paris
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    cmake \
    libssl-dev \
    wget \
    nlohmann-json3-dev

WORKDIR /app

RUN mkdir -p /app/stb && \
    wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h -O /app/stb/stb_image_write.h

CMD ["/bin/bash"]