# syntax=docker/dockerfile:1
FROM ubuntu:22.04
LABEL org.opencontainers.image.source=https://github.com/Dpbm/snake-ai

ENV TZ "America/New_York"
ENV DEBIAN_FRONTEND noninteractive

WORKDIR /snake

# prepare ubuntu
COPY compile.sh dep-ubuntu.sh setup-nfd.sh ./
RUN apt update && \
    apt upgrade -y && \
    apt install sudo locales locales-all -y

ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8
ENV LC_NUMERIC "C"

RUN chmod +x ./dep-ubuntu.sh && \
    chmod +x ./setup-nfd.sh
RUN ./dep-ubuntu.sh && \
    ./setup-nfd.sh


COPY CMakeLists.txt main.cpp ./
COPY game ./game
COPY assets ./assets
COPY genetic ./genetic
COPY helpers ./helpers
COPY machine ./machine
COPY matrix ./matrix
COPY qubo ./qubo

# fake files
RUN echo "int main(){ return 0; }" >> ./manual_tests.cpp 
RUN mkdir -p ./tests
RUN touch ./tests/fake_test.cc

# build executable
RUN chmod +x ./compile.sh && \
    ./compile.sh

CMD ./build/snake
