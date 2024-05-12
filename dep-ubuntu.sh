#!/usr/bin/sh

sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential \
  make \
  git \
  cmake \
  clang \
  libsdl2-dev \
  libfreetype6-dev \
  libsdl2-ttf-dev \
  libsdl2-ttf-2.0-0 \
  libstdc++-12-dev \
  libgtk-3-dev \
  libgtkmm-3.0-dev
