
FROM ubuntu:15.04

ENV HOME /root
CMD ["/usr/local/bin/build"]

RUN apt-get update

## basic depends ##
RUN apt-get install -y build-essential clang pkg-config libxml2-dev libpng12-dev libx11-dev zlib1g-dev libopencv-dev libglew-dev libglu1-mesa-dev libgl1-mesa-dev libsdl-net1.2-dev libsdl-image1.2-dev libsdl1.2-dev tk8.5-dev libgles2-mesa-dev dpkg-dev libvlc-dev libudev-dev vlc-nox

## wifibroadcast depends ## 
RUN apt-get install -y libpcap-dev iw

## build ##
RUN echo "#!/bin/sh" > /usr/local/bin/build && echo "(cd /usr/src/multigcs/ && make clean all deb)" >> /usr/local/bin/build && chmod 755 /usr/local/bin/build


