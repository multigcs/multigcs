
ARCH = `dpkg --print-architecture`
DEB_VERSION = 0.9-`date +%s`
BASE_DIR = /usr/share/multigcs

GCS = $(EXTRA_OBJECTS) main.o serial.o draw.o video.o geomag70.o \
	screens/screen_rcflow.o screens/screen_keyboard.o screens/screen_filesystem.o screens/screen_device.o screens/screen_baud.o screens/screen_model.o screens/screen_cli.o screens/screen_baseflightcli.o screens/screen_background.o screens/screen_wpedit.o screens/screen_hud.o screens/screen_map.o screens/screen_calibration.o screens/screen_fms.o screens/screen_system.o screens/screen_tcl.o screens/screen_mavlink_menu.o screens/screen_mwi_menu.o screens/screen_openpilot_menu.o screens/screen_videolist.o screens/screen_graph.o screens/screen_telemetry.o \
	mavlink/my_mavlink.o gps/my_gps.o mwi21/mwi21.o jeti/jeti.o openpilot/openpilot.o frsky/frsky.o webserv.o

default: all

all: gcs

clean:
	rm -f gcs *.o Common/*.o screens/*.o mavlink/*.o gps/*.o mwi21/*.o jeti/*.o openpilot/*.o frsky/*.o

install:
	test -e /usr/share/gl-gcs && (cp -a /usr/share/gl-gcs/* $(BASE_DIR) ; rm -rf /usr/share/gl-gcs/) || true
	mkdir -p $(BASE_DIR)/MAPS
	mkdir -p $(BASE_DIR)/textures
	mkdir -p $(BASE_DIR)/fonts
	mkdir -p $(BASE_DIR)/rcflow_presets
	mkdir -p $(BASE_DIR)/scripts
	mkdir -p $(BASE_DIR)/mavlink
	cp -a textures/* $(BASE_DIR)/textures/
	cp -a fonts/* $(BASE_DIR)/fonts/
	cp -a rcflow_presets/* $(BASE_DIR)/rcflow_presets/
	cp -a gcs /usr/bin/gl-gcs
	cp -a gcs.sh /usr/bin/gcs
	cp -a clean-badmaps.sh $(BASE_DIR)/clean-badmaps.sh
	cp -a screens/screen_tcl.tcl $(BASE_DIR)/scripts/screen_tcl.tcl
	cp -a map-services.xml $(BASE_DIR)/
	cp -a WMM2010.COF $(BASE_DIR)/MAPS/
	cp -a mavlink/ParameterMetaData*.xml $(BASE_DIR)/mavlink/
	touch $(BASE_DIR)/setup.cfg
	chmod 0755 /usr/bin/gl-gcs
	chmod 0755 /usr/bin/gcs
	chmod 0777 $(BASE_DIR)/setup.cfg
	chmod 0777 $(BASE_DIR)/clean-badmaps.sh

deb: gcs
	rm -rf package/
	mkdir -p package$(BASE_DIR)/MAPS
	mkdir -p package$(BASE_DIR)/textures
	mkdir -p package$(BASE_DIR)/fonts
	mkdir -p package$(BASE_DIR)/rcflow_presets
	mkdir -p package$(BASE_DIR)/scripts
	mkdir -p package/usr/bin
	mkdir -p package/DEBIAN
	cp -a textures/* package$(BASE_DIR)/textures/
	cp -a fonts/* package$(BASE_DIR)/fonts/
	cp -a rcflow_presets/* $(BASE_DIR)/rcflow_presets/
	cp -a gcs package/usr/bin/gl-gcs
	cp -a gcs.sh package/usr/bin/gcs
	cp -a clean-badmaps.sh package$(BASE_DIR)/clean-badmaps.sh
	cp -a screens/screen_tcl.tcl package$(BASE_DIR)/scripts/screen_tcl.tcl
	cp -a map-services.xml package$(BASE_DIR)/
	cp -a WMM2010.COF package$(BASE_DIR)/MAPS
	touch package$(BASE_DIR)/setup.cfg
	chmod 0755 package/usr/bin/gl-gcs
	chmod 0755 package/usr/bin/gcs
	chmod 0777 package$(BASE_DIR)/setup.cfg
	chmod 0777 package$(BASE_DIR)/clean-badmaps.sh
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
	echo "$(BASE_DIR)/setup.cfg" > package/DEBIAN/conffiles
	chmod -R -s package/ -R
	chmod 0755 package/DEBIAN/ -R
	dpkg-deb --build package
	mv package.deb multigcs-$(DEB_VERSION_NAME)_$(DEB_VERSION)_$(ARCH).deb

%.o: %.c
	gcc -DBASE_DIR="\"$(BASE_DIR)\"" -c $(CFLAGS) $< -o $@ ${INCDIR}

gcs: ${COMMONSRC} ${COMMONHDR} ${GCS}
	gcc -DBASE_DIR="\"$(BASE_DIR)\"" $(CFLAGS) ${COMMONSRC} ${GCS} -o $@ ${INCDIR} ${LIBS}

font-generator: font-generator.c
	gcc -DBASE_DIR="\"$(BASE_DIR)\"" -o font-generator font-generator.c -Wall -O -I/usr/include/SDL -lSDL_ttf -lpng


