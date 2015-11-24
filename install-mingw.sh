#!/bin/sh
#
#

MINGW_DIR="`grep "MINGW_DIR = " Makefile.win32-cross  | awk '{print $3}'`"

apt-get install mingw32 wine dos2unix nsis nsis-common wget build-essential pkg-config zip unzip tofrodos tclsh

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

test -e winglut.zip || wget http://web.cs.wpi.edu/~gogo/courses/mingw/winglut.zip
mkdir -p winglut
(cd winglut ; unzip -o -x ../winglut.zip)

test -e glew-1.13.0.tgz || wget http://kent.dl.sourceforge.net/project/glew/glew/1.13.0/glew-1.13.0.tgz
tar xzvpf glew-1.13.0.tgz
(
cd glew-1.13.0
rm -rf lib/
rm -rf bin/
mkdir -p lib/
mkdir -p bin/
i686-w64-mingw32-gcc -DGLEW_NO_GLU -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.o -c src/glew.c
i686-w64-mingw32-gcc -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib/libglew32.dll.a  -o bin/glew32.dll src/glew.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
ar cr lib/libglew32.a src/glew.o
sed -e "s|@prefix@|/usr|g" -e "s|@libdir@|/usr/lib|g" -e "s|@exec_prefix@|/usr/bin|g" -e "s|@includedir@|/usr/include/GL|g" -e "s|@version@|1.6.0|g" -e "s|@cflags@||g" -e "s|@libname@|GLEW|g" < glew.pc.in > glew.pc
i686-w64-mingw32-gcc -DGLEW_NO_GLU -DGLEW_MX -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.mx.o -c src/glew.c
i686-w64-mingw32-gcc -shared -Wl,-soname,libglew32mx.dll -Wl,--out-implib,lib/libglew32mx.dll.a -o bin/glew32mx.dll src/glew.mx.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
ar cr lib/libglew32mx.a src/glew.mx.o
sed -e "s|@prefix@|/usr|g" -e "s|@libdir@|/usr/lib|g" -e "s|@exec_prefix@|/usr/bin|g" -e "s|@includedir@|/usr/include/GL|g" -e "s|@version@|1.6.0|g" -e "s|@cflags@|-DGLEW_MX|g" -e "s|@libname@|GLEWmx|g" < glew.pc.in > glewmx.pc
i686-w64-mingw32-gcc -c -O2 -Wall -W -Iinclude  -o src/glewinfo.o src/glewinfo.c
i686-w64-mingw32-gcc -O2 -Wall -W -Iinclude  -o bin/glewinfo.exe src/glewinfo.o -Llib  -lglew32 -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
i686-w64-mingw32-gcc -c -O2 -Wall -W -Iinclude  -o src/visualinfo.o src/visualinfo.c
i686-w64-mingw32-gcc -O2 -Wall -W -Iinclude  -o bin/visualinfo.exe src/visualinfo.o -Llib  -lglew32 -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
)

test -e libjpeg/ || mkdir -p libjpeg
test -e libjpeg/libjpeg-9.dll || wget -O libjpeg/libjpeg-9.dll https://raw.github.com/OctaForge/OF-Windows/master/bin_win64/libjpeg-9.dll


test -e OpenCV-2.4.5VC.zip || wget http://www.multixmedia.org/test/OpenCV-2.4.5VC.zip
unzip -o -x OpenCV-2.4.5VC.zip

mkdir -p $MINGW_DIR/bin/
mkdir -p $MINGW_DIR/lib/
mkdir -p $MINGW_DIR/include/
mkdir -p $MINGW_DIR/include/tcl/

cp -av SDL2_image-2.0.0/i686-w64-mingw32/* $MINGW_DIR/
cp -av SDL2_net-2.0.0/i686-w64-mingw32/* $MINGW_DIR/
cp -av SDL2-2.0.0/i686-w64-mingw32/* $MINGW_DIR/
cp -av iconv-1.9.2.win32/* $MINGW_DIR/
cp -av libxml2-2.7.8.win32/* $MINGW_DIR/
cp -av libpng-1.2.37/* $MINGW_DIR/
cp -av libpng3/* $MINGW_DIR/bin/
cp -av zlib-1.2.3/* $MINGW_DIR/
cp -av tcl8.5.15/generic/*.h  $MINGW_DIR/include/tcl/
cp -av tcl8.5.15/win/*dll $MINGW_DIR/bin/
cp -av winglut/glut32.dll $MINGW_DIR/bin/
cp -av winglut/winlib/* $MINGW_DIR/lib/
cp -av winglut/GL/* $MINGW_DIR/include/GL/
cp -av glew-1.13.0/lib/* $MINGW_DIR/lib/
cp -av glew-1.13.0/bin/* $MINGW_DIR/bin/
cp -av glew-1.13.0/include/* $MINGW_DIR/include/
cp -av libjpeg/libjpeg-9.dll $MINGW_DIR/bin/
cp -av OpenCV-2.4.5VC/install/bin/* $MINGW_DIR/bin/
cp -av OpenCV-2.4.5VC/install/lib/* $MINGW_DIR/lib/
cp -av OpenCV-2.4.5VC/install/include/* $MINGW_DIR/include/

(cd /usr/share/nsis/ ; test -e UltraModernUI_1.00_2010-11-11.zip || wget -O UltraModernUI_1.00_2010-11-11.zip http://freefr.dl.sourceforge.net/project/ultramodernui/UltraModernUI/UltraModernUI%201.00b2-dev/UltraModernUI_1.00_2010-11-11.zip)
(cd /usr/share/nsis/ ; test -e /usr/share/nsis/Contrib/Graphics/UltraModernUI/Complete.bmp || unzip -x UltraModernUI_1.00_2010-11-11.zip)




