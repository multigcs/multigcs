#!/bin/sh
#
#

apt-get install binutils-mingw-w64-i686 gcc-mingw-w64-i686 gcc-mingw32 mingw-w64-x86-64-dev mingw-w64-i686-dev mingw32-runtime wine libwine-gl

mkdir -p winlibs
cd winlibs

test -e SDL2_image-devel-2.0.0-mingw.tar.gz || wget http://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.0-mingw.tar.gz
tar xzvpf SDL2_image-devel-2.0.0-mingw.tar.gz

test -e SDL2_net-devel-2.0.0-mingw.tar.gz || wget http://www.libsdl.org/projects/SDL_net/release/SDL2_net-devel-2.0.0-mingw.tar.gz
tar xzvpf SDL2_net-devel-2.0.0-mingw.tar.gz

test -e SDL2-devel-2.0.0-mingw.tar.gz || wget http://www.libsdl.org/release/SDL2-devel-2.0.0-mingw.tar.gz
tar xzvpf SDL2-devel-2.0.0-mingw.tar.gz

test -e iconv-1.9.2.win32.zip || wget ftp://ftp.zlatkovic.com/libxml/iconv-1.9.2.win32.zip
unzip -o -x iconv-1.9.2.win32.zip

test -e libxml2-2.7.8.win32.zip || wget ftp://ftp.zlatkovic.com/libxml/libxml2-2.7.8.win32.zip
unzip -o -x libxml2-2.7.8.win32.zip
rm -rf libxml2-2.7.8.win32/readme.txt

test -e libpng-1.2.37-lib.zip || wget http://downloads.sourceforge.net/project/gnuwin32/libpng/1.2.37/libpng-1.2.37-lib.zip
mkdir -p libpng-1.2.37
(cd libpng-1.2.37 ; unzip -o -x ../libpng-1.2.37-lib.zip)
rm -rf libpng-1.2.37/manifest

test -e libpng3.zip || wget -O libpng3.zip "http://gimpchat.com/download/file.php?id=107&sid=17dcd85386865b258538f5268be6b12e"
mkdir -p libpng3
(cd libpng3 ; unzip -o -x ../libpng3.zip)

test -e zlib-1.2.3-lib.zip || wget http://downloads.sourceforge.net/project/gnuwin32/zlib/1.2.3/zlib-1.2.3-lib.zip
mkdir -p zlib-1.2.3
(cd zlib-1.2.3 ; unzip -o -x ../zlib-1.2.3-lib.zip)
rm -rf zlib-1.2.3/manifest

test -e tcl8515-src.zip || wget http://prdownloads.sourceforge.net/tcl/tcl8515-src.zip
unzip -o -x tcl8515-src.zip
(cd tcl8.5.15/win/ ; ./configure --enable-gcc --host=i386-mingw32 ; make)

mkdir -p /usr/i686-w64-mingw32/bin/
mkdir -p /usr/i686-w64-mingw32/lib/
mkdir -p /usr/i686-w64-mingw32/include/
mkdir -p /usr/i686-w64-mingw32/include/tcl/

cp -av SDL2_image-2.0.0/i686-w64-mingw32/* /usr/i686-w64-mingw32/
cp -av SDL2_net-2.0.0/i686-w64-mingw32/* /usr/i686-w64-mingw32/
cp -av SDL2-2.0.0/i686-w64-mingw32/* /usr/i686-w64-mingw32/
cp -av iconv-1.9.2.win32/* /usr/i686-w64-mingw32/
cp -av libxml2-2.7.8.win32/* /usr/i686-w64-mingw32/
cp -av libpng-1.2.37/* /usr/i686-w64-mingw32/
cp -av libpng3/* /usr/i686-w64-mingw32/bin/
cp -av zlib-1.2.3/* /usr/i686-w64-mingw32/
cp -av tcl8.5.15/generic/*.h  /usr/i686-w64-mingw32/include/tcl/
cp -a tcl8.5.15/win/*dll /usr/i686-w64-mingw32/bin/


