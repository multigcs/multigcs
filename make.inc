
ARCH = `dpkg --print-architecture`
VERSION = 0.92
VERSION_BUILD := `date +%s`
BASE_DIR = /usr/share/multigcs


INCDIR += -I./ -ICommon -Iscreens -Inet -Itcl -Idraw -Imavlink -Igps -Imwi21 -Ijeti -Iopenpilot -Ifrsky -Iminizip -Itracker -Iutils
INCDIR += -I/usr/include/tcl8.5
INCDIR += $(shell pkg-config --cflags libxml-2.0) $(shell pkg-config --cflags x11) $(shell pkg-config --cflags libpng) $(shell pkg-config --cflags zlib)

LIBS += -lm -ltcl8.5
LIBS += $(shell pkg-config --libs libxml-2.0) $(shell pkg-config --libs x11) $(shell pkg-config --libs libpng) $(shell pkg-config --libs zlib)



GCS = $(EXTRA_OBJECTS) main.o serial.o draw/draw.o draw/videocapture.o draw/map.o geomag70.o \
	minizip/ioapi.o minizip/unzip.o net/htmlget-sdl.o \
	screens/screen_rcflow.o screens/screen_keyboard.o screens/screen_filesystem.o screens/screen_device.o screens/screen_baud.o screens/screen_number.o screens/screen_model.o screens/screen_background.o screens/screen_wpedit.o screens/screen_hud.o screens/screen_map.o screens/screen_map_survey.o screens/screen_map_swarm.o screens/screen_calibration.o screens/screen_fms.o screens/screen_system.o screens/screen_tcl.o screens/screen_mavlink_menu.o screens/screen_tracker.o screens/screen_mwi_menu.o screens/screen_openpilot_menu.o screens/screen_videolist.o screens/screen_graph.o screens/screen_telemetry.o \
	mavlink/my_mavlink.o mavlink/my_mavlink_rewrite.o gps/my_gps.o mwi21/mwi21.o jeti/jeti.o openpilot/openpilot.o openpilot/openpilot_xml.o frsky/frsky.o tracker/tracker.o net/savepng.o net/webserv.o net/webclient.o logging.o kml.o \
	openpilot/uavobjects_store.o openpilot/uavobjects_encode.o openpilot/uavobjects_decode.o \
	weather.o


default: all

all: gcs

clean:
	rm -f gcs *.o Common/*.o screens/*.o net/*.o draw/*.o tcl/*.o mavlink/*.o gps/*.o mwi21/*.o jeti/*.o openpilot/*.o frsky/*.o tracker/*.o minizip/*.o tracker/*.o quirc/*.o wifibc/*.o

install:
	cp -a gcs /usr/bin/gl-gcs
	cp -a utils/gcs.sh /usr/bin/multigcs
	mkdir -p /usr/share/man/man1/
	cat data/man.1 | gzip -9 > /usr/share/man/man1/multigcs.1.gz
	mkdir -p /usr/share/doc/multigcs/
	cp -a README /usr/share/doc/multigcs/README
	cp -a copyright /usr/share/doc/multigcs/copyright
	cp -a GPLv3.txt /usr/share/doc/multigcs/GPLv3.txt
	cp -a multigcs.html /usr/share/doc/multigcs/multigcs.html
	test -e .git && git log | gzip -9 > /usr/share/doc/multigcs/changelog.gz
	test -e .git && git log | gzip -9 > /usr/share/doc/multigcs/changelog.Debian.gz 
	mkdir -p $(BASE_DIR)
	cp -a data/WMM.COF $(BASE_DIR)/
	cp -a data/SRTM.list $(BASE_DIR)/
	cp -a data/map-services.xml $(BASE_DIR)/
	cp -a utils/clean-badmaps.sh $(BASE_DIR)/clean-badmaps.sh
	mkdir -p $(BASE_DIR)/obj3d
	cp -a models3d/*.obj $(BASE_DIR)/obj3d/
	cp -a models3d/*.txt $(BASE_DIR)/obj3d/
	mkdir -p $(BASE_DIR)/textures
	cp -a textures/* $(BASE_DIR)/textures/
	mkdir -p $(BASE_DIR)/fonts
	cp -a fonts/* $(BASE_DIR)/fonts/
	mkdir -p $(BASE_DIR)/mixes
	cp -a data/mixes/* $(BASE_DIR)/mixes/
	mkdir -p $(BASE_DIR)/rcflow_presets
	cp -a rcflow_presets/* $(BASE_DIR)/rcflow_presets/
	mkdir -p $(BASE_DIR)/scripts
	cp -a screens/screen_tcl.tcl $(BASE_DIR)/scripts/screen_tcl.tcl
	mkdir -p $(BASE_DIR)/mavlink
	cp -a mavlink/ParameterMetaData*.xml $(BASE_DIR)/mavlink/
	mkdir -p $(BASE_DIR)/webserv
	cp -a multigcs.html $(BASE_DIR)/webserv/multigcs.html
	cp -a textures/marker.png $(BASE_DIR)/webserv/marker.png
	cp -a textures/MULTICOPTER.png $(BASE_DIR)/webserv/model.png
	cp -a net/map.js $(BASE_DIR)/webserv/map.js
	cp -a net/webserv-index.html $(BASE_DIR)/webserv/index.html
	cp -a net/style.css $(BASE_DIR)/webserv/style.css
	cp -a net/favicon.ico $(BASE_DIR)/webserv/favicon.ico
	cp -a net/blender-export.py $(BASE_DIR)/webserv/blender-export.py
	cp -a net/plane.dae $(BASE_DIR)/webserv/plane.dae
	cp -a net/simple.dae $(BASE_DIR)/webserv/simple.dae
	cp -a copyright $(BASE_DIR)/webserv/copyright
	cp -a GPLv3.txt $(BASE_DIR)/webserv/GPLv3.txt
	chmod 0755 /usr/bin/gl-gcs
	chmod 0755 /usr/bin/multigcs
	chmod 0755 $(BASE_DIR)/clean-badmaps.sh

deb: gcs
	rm -rf package/
	mkdir -p package/usr/bin
	cp -a gcs package/usr/bin/gl-gcs
	cp -a utils/gcs.sh package/usr/bin/multigcs
	mkdir -p package/usr/share/man/man1/
	cat data/man.1 | gzip -9 > package/usr/share/man/man1/multigcs.1.gz
	mkdir -p package/usr/share/doc/multigcs/
	cp -a README package/usr/share/doc/multigcs/README
	cp -a copyright package/usr/share/doc/multigcs/copyright
	cp -a GPLv3.txt package/usr/share/doc/multigcs/GPLv3.txt
	cp -a multigcs.html package/usr/share/doc/multigcs/multigcs.html
	git log | gzip -9 > package/usr/share/doc/multigcs/changelog.gz
	git log | gzip -9 > package/usr/share/doc/multigcs/changelog.Debian.gz 
	mkdir -p package$(BASE_DIR)
	cp -a data/WMM.COF package$(BASE_DIR)/
	cp -a data/SRTM.list package$(BASE_DIR)/
	cp -a data/map-services.xml package$(BASE_DIR)/
	cp -a utils/clean-badmaps.sh package$(BASE_DIR)/clean-badmaps.sh
	mkdir -p package$(BASE_DIR)/obj3d
	mkdir -p package$(BASE_DIR)/textures
	cp -a textures/* package$(BASE_DIR)/textures/
	mkdir -p package$(BASE_DIR)/fonts
	cp -a fonts/* package$(BASE_DIR)/fonts/
	mkdir -p package$$(BASE_DIR)/mixes
	cp -a data/mixes/* package$$(BASE_DIR)/mixes/
	mkdir -p package$(BASE_DIR)/rcflow_presets
	cp -a rcflow_presets/* package$(BASE_DIR)/rcflow_presets/
	mkdir -p package$(BASE_DIR)/scripts
	cp -a screens/screen_tcl.tcl package$(BASE_DIR)/scripts/screen_tcl.tcl
	mkdir -p package$(BASE_DIR)/mavlink
	cp -a mavlink/ParameterMetaData*.xml package$(BASE_DIR)/mavlink/
	mkdir -p package$(BASE_DIR)/webserv
	cp -a multigcs.html package$(BASE_DIR)/webserv/multigcs.html
	cp -a textures/marker.png package$(BASE_DIR)/webserv/marker.png
	cp -a textures/MULTICOPTER.png package$(BASE_DIR)/webserv/model.png
	cp -a net/map.js package$(BASE_DIR)/webserv/map.js
	cp -a net/webserv-index.html package$(BASE_DIR)/webserv/index.html
	cp -a net/style.css package$(BASE_DIR)/webserv/style.css
	cp -a net/favicon.ico package$(BASE_DIR)/webserv/favicon.ico
	cp -a net/blender-export.py package$(BASE_DIR)/webserv/blender-export.py
	cp -a net/plane.dae package$(BASE_DIR)/webserv/plane.dae
	cp -a net/simple.dae package$(BASE_DIR)/webserv/simple.dae
	cp -a copyright package$(BASE_DIR)/webserv/copyright
	cp -a GPLv3.txt package$(BASE_DIR)/webserv/GPLv3.txt
	chmod 0755 package/usr/bin/gl-gcs
	chmod 0755 package/usr/bin/multigcs
	chmod 0755 package$(BASE_DIR)/clean-badmaps.sh
	mkdir -p package/DEBIAN/
	echo "Package: multigcs" > package/DEBIAN/control
	echo "Source: multigcs" >> package/DEBIAN/control
	echo "Version: $(VERSION)" >> package/DEBIAN/control
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
	mv package.deb multigcs-$(VERSION_NAME)_$(VERSION)-$(VERSION_BUILD)_$(ARCH).deb

%.o: %.c
	@echo "$< -> $@"
	@$(COMP) -c $(CFLAGS) $< -o $@ ${INCDIR}

gcs: ${COMMONSRC} ${COMMONHDR} ${GCS}
	@echo "linking $@"
	@$(COMP) -DBASE_DIR="\"$(BASE_DIR)\"" $(CFLAGS) ${COMMONSRC} ${GCS} -o $@ ${INCDIR} ${LIBS}

font-generator: font-generator.c
	$(COMP) -DBASE_DIR="\"$(BASE_DIR)\"" -o font-generator font-generator.c -Wall -O -I/usr/include/SDL -lSDL_ttf -lpng


