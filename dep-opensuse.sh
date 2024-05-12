#!/usr/bin/sh

sudo zypper refresh
sudo zypper ref
sudo zypper update
sudo zypper patch
sudo zypper install libSDL2-2_0-0 \
  libSDL2-devel \
  cmake \
  make \
  libSDL2_ttf-2_0-0 \
  libSDL2_ttf-devel \
  pattern \
  clang \
  clang-tools \
  libgtk-3-0 \
  libgtk-3-0-devel \
  libgtkmm-3_0-1
