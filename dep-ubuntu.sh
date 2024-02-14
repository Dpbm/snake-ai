#!/usr/bin/sh

sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential \
  make \
  cmake \
  clang \
  libsdl2-dev \
  libfreetype6-dev \
  libsdl2-ttf-dev \
  libsdl2-ttf-2.0-0
