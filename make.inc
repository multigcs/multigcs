
ARCH = `dpkg --print-architecture`
DEB_VERSION = 0.9-`date +%s`

GCS = $(EXTRA_OBJECTS) main.o serial.o i2c.o draw.o video.o geomag70.o \
	screens/screen_rcflow.o screens/screen_keyboard.o screens/screen_filesystem.o screens/screen_device.o screens/screen_baud.o screens/screen_model.o screens/screen_background.o screens/screen_wpedit.o screens/screen_hud.o screens/screen_map.o screens/screen_calibration.o screens/screen_nd.o screens/screen_fms.o screens/screen_system.o screens/screen_tcl.o screens/screen_mavlink_menu.o screens/screen_mwi_menu.o screens/screen_openpilot_menu.o screens/screen_videolist.o screens/screen_graph.o \
	mavlink/my_mavlink.o gps/my_gps.o mwi21/mwi21.o jeti/jeti.o openpilot/openpilot.o frsky/frsky.o

default: all

all: gcs

clean:
	rm -f gcs *.o Common/*.o screens/*.o mavlink/*.o gps/*.o mwi21/*.o jeti/*.o openpilot/*.o frsky/*.o

install:
	mkdir -p /usr/share/gl-gcs/MAPS
	mkdir -p /usr/share/gl-gcs/textures
	mkdir -p /usr/share/gl-gcs/fonts
	mkdir -p /usr/share/gl-gcs/rcflow_presets
	mkdir -p /usr/share/gl-gcs/scripts
	mkdir -p /usr/bin
	cp -a textures/* /usr/share/gl-gcs/textures/
	cp -a fonts/* /usr/share/gl-gcs/fonts/
	cp -a rcflow_presets/* /usr/share/gl-gcs/rcflow_presets/
	cp -a gcs /usr/bin/gl-gcs
	cp -a gcs.sh /usr/bin/gcs
	cp -a clean-badmaps.sh /usr/share/gl-gcs/clean-badmaps.sh
	cp -a screens/screen_tcl.tcl /usr/share/gl-gcs/scripts/screen_tcl.tcl
	cp -a WMM2010.COF /usr/share/gl-gcs/MAPS
	touch /usr/share/gl-gcs/setup.cfg
	chmod 0755 /usr/bin/gl-gcs
	chmod 0755 /usr/bin/gcs
	chmod 0777 /usr/share/gl-gcs/setup.cfg
	chmod 0777 /usr/share/gl-gcs/clean-badmaps.sh

deb: gcs
	rm -rf package/
	mkdir -p package/usr/share/gl-gcs/MAPS
	mkdir -p package/usr/share/gl-gcs/textures
	mkdir -p package/usr/share/gl-gcs/fonts
	mkdir -p package/usr/share/gl-gcs/rcflow_presets
	mkdir -p package/usr/share/gl-gcs/scripts
	mkdir -p package/usr/bin
	mkdir -p package/DEBIAN
	cp -a textures/* package/usr/share/gl-gcs/textures/
	cp -a fonts/* package/usr/share/gl-gcs/fonts/
	cp -a rcflow_presets/* /usr/share/gl-gcs/rcflow_presets/
	cp -a gcs package/usr/bin/gl-gcs
	cp -a gcs.sh package/usr/bin/gcs
	cp -a clean-badmaps.sh package/usr/share/gl-gcs/clean-badmaps.sh
	cp -a screens/screen_tcl.tcl package/usr/share/gl-gcs/scripts/screens/screen_tcl.tcl
	cp -a WMM2010.COF package/usr/share/gl-gcs/MAPS
	touch package/usr/share/gl-gcs/setup.cfg
	chmod 0755 package/usr/bin/gl-gcs
	chmod 0755 package/usr/bin/gcs
	chmod 0777 package/usr/share/gl-gcs/setup.cfg
	chmod 0777 package/usr/share/gl-gcs/clean-badmaps.sh
	echo "Package: multigcs" > package/DEBIAN/control
	echo "Source: multigcs" >> package/DEBIAN/control
	echo "Version: $(DEB_VERSION)" >> package/DEBIAN/control
	echo "Architecture: $(ARCH)" >> package/DEBIAN/control
	echo "Maintainer: Oliver Dippel <oliver@multixmedia.org>" >> package/DEBIAN/control
	echo "Depends: $(DEB_DEPENDS)" >> package/DEBIAN/control
	echo "Section: media" >> package/DEBIAN/control
	echo "Priority: optional" >> package/DEBIAN/control
	echo "Description: Ground-Control-Station based on OpenGL(-ES)" >> package/DEBIAN/control
	echo " Ground-Control-Station based on OpenGL(-ES)" >> package/DEBIAN/control
	echo "/usr/share/gl-gcs/setup.cfg" > package/DEBIAN/conffiles
	chmod -R -s package/ -R
	chmod 0755 package/DEBIAN/ -R
	dpkg-deb --build package
	mv package.deb multigcs-$(DEB_VERSION_NAME)_$(DEB_VERSION)_$(ARCH).deb

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@ ${INCDIR}

gcs: ${COMMONSRC} ${COMMONHDR} ${GCS}
	gcc $(CFLAGS) ${COMMONSRC} ${GCS} -o $@ ${INCDIR} ${LIBS}

font-generator: font-generator.c
	gcc -o font-generator font-generator.c -Wall -O -I/usr/include/SDL -lSDL_ttf -lpng


