
ARCH = `dpkg --print-architecture`
DEB_VERSION = 0.9-`date +%s`
BASE_DIR = /usr/share/multigcs


INCDIR += -I./ -ICommon -Iscreens -Imavlink -Igps -Imwi21 -Isimplebgc -Ibrugi -Ijeti -Iopenpilot -Ifrsky
INCDIR += -I/usr/include/tcl8.5
INCDIR += $(shell pkg-config --cflags libcurl) $(shell pkg-config --cflags libxml-2.0) $(shell pkg-config --cflags x11) $(shell pkg-config --cflags libpng)

LIBS += -lm -ltcl8.5
LIBS += $(shell pkg-config --libs libcurl) $(shell pkg-config --libs libxml-2.0) $(shell pkg-config --libs x11) $(shell pkg-config --libs libpng)



GCS = $(EXTRA_OBJECTS) main.o serial.o draw.o video.o geomag70.o \
	screens/screen_rcflow.o screens/screen_keyboard.o screens/screen_filesystem.o screens/screen_device.o screens/screen_baud.o screens/screen_model.o screens/screen_cli.o screens/screen_baseflightcli.o screens/screen_background.o screens/screen_wpedit.o screens/screen_hud.o screens/screen_map.o screens/screen_calibration.o screens/screen_fms.o screens/screen_system.o screens/screen_tcl.o screens/screen_mavlink_menu.o screens/screen_brugi.o screens/screen_mwi_menu.o screens/screen_openpilot_menu.o screens/screen_videolist.o screens/screen_graph.o screens/screen_telemetry.o \
	mavlink/my_mavlink.o gps/my_gps.o mwi21/mwi21.o jeti/jeti.o openpilot/openpilot.o frsky/frsky.o simplebgc/simplebgc.o brugi/brugi.o webserv.o webclient.o logging.o

default: all

all: gcs

clean:
	rm -f gcs *.o Common/*.o screens/*.o mavlink/*.o gps/*.o mwi21/*.o jeti/*.o openpilot/*.o frsky/*.o

install:
	cp -a gcs /usr/bin/gl-gcs
	cp -a gcs.sh /usr/bin/gcs

	mkdir -p $(BASE_DIR)
	cp -a WMM2010.COF $(BASE_DIR)/
	cp -a map-services.xml $(BASE_DIR)/
	cp -a clean-badmaps.sh $(BASE_DIR)/clean-badmaps.sh

	mkdir -p $(BASE_DIR)/obj3d

	mkdir -p $(BASE_DIR)/textures
	cp -a textures/* $(BASE_DIR)/textures/

	mkdir -p $(BASE_DIR)/fonts
	cp -a fonts/* $(BASE_DIR)/fonts/

	mkdir -p $(BASE_DIR)/rcflow_presets
	cp -a rcflow_presets/* $(BASE_DIR)/rcflow_presets/

	mkdir -p $(BASE_DIR)/scripts
	cp -a screens/screen_tcl.tcl $(BASE_DIR)/scripts/screen_tcl.tcl

	mkdir -p $(BASE_DIR)/mavlink
	cp -a mavlink/ParameterMetaData*.xml $(BASE_DIR)/mavlink/

	mkdir -p $(BASE_DIR)/webserv
	cp -a textures/marker.png $(BASE_DIR)/webserv/marker.png
	cp -a map.js $(BASE_DIR)/webserv/map.js
	cp -a webserv-index.html $(BASE_DIR)/webserv/index.html
	cp -a blender-export.py $(BASE_DIR)/webserv/blender-export.py
	cp -a plane.dae $(BASE_DIR)/webserv/plane.dae
	cp -a simple.dae $(BASE_DIR)/webserv/simple.dae

	chmod 0755 /usr/bin/gl-gcs
	chmod 0755 /usr/bin/gcs
	chmod 0755 $(BASE_DIR)/clean-badmaps.sh

deb: gcs
	rm -rf package/
	echo "....."
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
	chmod -R -s package/ -R
	chmod 0755 package/DEBIAN/ -R
	dpkg-deb --build package
	mv package.deb multigcs-$(DEB_VERSION_NAME)_$(DEB_VERSION)_$(ARCH).deb

%.o: %.c
	@echo "$< -> $@"
	@gcc -DBASE_DIR="\"$(BASE_DIR)\"" -c $(CFLAGS) $< -o $@ ${INCDIR}

gcs: ${COMMONSRC} ${COMMONHDR} ${GCS}
	@echo "linking $@"
	@gcc -DBASE_DIR="\"$(BASE_DIR)\"" $(CFLAGS) ${COMMONSRC} ${GCS} -o $@ ${INCDIR} ${LIBS}

font-generator: font-generator.c
	gcc -DBASE_DIR="\"$(BASE_DIR)\"" -o font-generator font-generator.c -Wall -O -I/usr/include/SDL -lSDL_ttf -lpng


