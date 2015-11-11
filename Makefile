

## Linux-RaspberryPi GLES Version ##
DEB_DEPENDS = tcl8.5, espeak, coreutils, imagemagick, bluez, input-utils, gcc-4.6,libasound2,libasyncns0,libattr1,libc6,libcaca0,libcap2,libcomerr2,libcurl3,libdbus-1-3,libdirectfb-1.2-9,libflac8,libgcc1,libgcrypt11,libgnutls26,libgpg-error0,libgssapi-krb5-2,libice6,libidn11,libjson0,libk5crypto3,libkeyutils1,libkrb5-3,libkrb5support0,libldap-2.4-2,libncursesw5,libogg0,libp11-kit0,libpng12-0,libpulse0,librtmp0,libsasl2-2,libsdl1.2debian,libslang2,libsm6,libsndfile1,libssh2-1,libssl1.0.0,libtasn1-3,libtinfo5,libts-0.0-0,libuuid1,libvorbis0a,libvorbisenc2,libwrap0,libx11-6,libx11-xcb1,libxau6,libxcb1,libxdmcp6,libxext6,libxi6,libxtst6,raspi-copies-and-fills,zlib1g,libxml2
VERSION_NAME = rpi
EXTRA_OBJECTS = draw/gles_draw.o
BASE_DIR = /usr/share/multigcs
COMP = gcc

INCDIR = -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux
LIBS = -lbcm_host -L$(SDKSTAGE)/opt/vc/lib -ludev
CFLAGS += -DRPI_NO_X -Ofast -pipe -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -DBASE_DIR="\"$(BASE_DIR)\""
#CFLAGS += -flto -ffast-math -fno-math-errno -funsafe-math-optimizations -ffinite-math-only -fno-signed-zeros -fno-trapping-math -frounding-math

INCDIR += $(shell pkg-config --cflags sdl) $(shell pkg-config --cflags SDL_image) $(shell pkg-config --cflags SDL_net)
LIBS += $(shell pkg-config --libs sdl) $(shell pkg-config --libs SDL_image) $(shell pkg-config --libs SDL_net) -lEGL lGLESv2 -lglut -lGL

## ldd gcs  | grep -v /opt | awk '{print $1}' | xargs -r -l dpkg -S  | cut -d":" -f1 | sort -u | tr  "\n" "," ##

COMMONSRC=./Common/esShader.c ./Common/esTransform.c ./Common/esShapes.c ./Common/esUtil.c
COMMONHRD=esUtil.h

include make.inc

