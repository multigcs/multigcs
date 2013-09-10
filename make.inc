
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
	mkdir -p package/usr/bin
	cp -a gcs package/usr/bin/gl-gcs
	cp -a gcs.sh package/usr/bin/gcs
	mkdir -p package$(BASE_DIR)
	cp -a WMM2010.COF package$(BASE_DIR)/
	cp -a map-services.xml package$(BASE_DIR)/
	cp -a clean-badmaps.sh package$(BASE_DIR)/clean-badmaps.sh
	mkdir -p package$(BASE_DIR)/obj3d
	mkdir -p package$(BASE_DIR)/textures
	cp -a textures/* package$(BASE_DIR)/textures/
	mkdir -p package$(BASE_DIR)/fonts
	cp -a fonts/* package$(BASE_DIR)/fonts/
	mkdir -p package$(BASE_DIR)/rcflow_presets
	cp -a rcflow_presets/* package$(BASE_DIR)/rcflow_presets/
	mkdir -p package$(BASE_DIR)/scripts
	cp -a screens/screen_tcl.tcl package$(BASE_DIR)/scripts/screen_tcl.tcl
	mkdir -p package$(BASE_DIR)/mavlink
	cp -a mavlink/ParameterMetaData*.xml package$(BASE_DIR)/mavlink/
	mkdir -p package$(BASE_DIR)/webserv
	cp -a textures/marker.png package$(BASE_DIR)/webserv/marker.png
	cp -a map.js package$(BASE_DIR)/webserv/map.js
	cp -a webserv-index.html package$(BASE_DIR)/webserv/index.html
	cp -a blender-export.py package$(BASE_DIR)/webserv/blender-export.py
	cp -a plane.dae package$(BASE_DIR)/webserv/plane.dae
	cp -a simple.dae package$(BASE_DIR)/webserv/simple.dae
	chmod 0755 package/usr/bin/gl-gcs
	chmod 0755 package/usr/bin/gcs
	chmod 0755 package$(BASE_DIR)/clean-badmaps.sh
	mkdir -p package/DEBIAN/
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

app: gcs
	rm -rf multigcs.app/Contents/MacOS/
	mkdir -p multigcs.app/Contents/MacOS/bin
	mkdir -p multigcs.app/Contents/Resources
	cp -a gcs.sh multigcs.app/Contents/MacOS/bin/gcs.sh
	mkdir -p multigcs.app/Contents/MacOS/share
	cp -a WMM2010.COF multigcs.app/Contents/MacOS/share/
	cp -a map-services.xml multigcs.app/Contents/MacOS/share/
	cp -a clean-badmaps.sh multigcs.app/Contents/MacOS/share/clean-badmaps.sh
	mkdir -p multigcs.app/Contents/MacOS/share/obj3d
	mkdir -p multigcs.app/Contents/MacOS/share/textures
	cp -a textures/* multigcs.app/Contents/MacOS/share/textures/
	mkdir -p multigcs.app/Contents/MacOS/share/fonts
	cp -a fonts/* multigcs.app/Contents/MacOS/share/fonts/
	mkdir -p multigcs.app/Contents/MacOS/share/rcflow_presets
	cp -a rcflow_presets/* multigcs.app/Contents/MacOS/share/rcflow_presets/
	mkdir -p multigcs.app/Contents/MacOS/share/scripts
	cp -a screens/screen_tcl.tcl multigcs.app/Contents/MacOS/share/scripts/screen_tcl.tcl
	mkdir -p multigcs.app/Contents/MacOS/share/mavlink
	cp -a mavlink/ParameterMetaData*.xml multigcs.app/Contents/MacOS/share/mavlink/
	mkdir -p multigcs.app/Contents/MacOS/share/webserv
	cp -a textures/marker.png multigcs.app/Contents/MacOS/share/webserv/marker.png
	cp -a map.js multigcs.app/Contents/MacOS/share/webserv/map.js
	cp -a webserv-index.html multigcs.app/Contents/MacOS/share/webserv/index.html
	cp -a blender-export.py multigcs.app/Contents/MacOS/share/webserv/blender-export.py
	cp -a plane.dae multigcs.app/Contents/MacOS/share/webserv/plane.dae
	cp -a simple.dae multigcs.app/Contents/MacOS/share/webserv/simple.dae

	sh osx-app.sh

	echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" > multigcs.app/Contents/Info.plist
	echo "<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" >> multigcs.app/Contents/Info.plist
	echo "<plist version=\"1.0\">" >> multigcs.app/Contents/Info.plist
	echo "<dict>" >> multigcs.app/Contents/Info.plist
	echo "  <key>CFBundleGetInfoString</key>" >> multigcs.app/Contents/Info.plist
	echo "  <string>multigcs</string>" >> multigcs.app/Contents/Info.plist
	echo "  <key>CFBundleExecutable</key>" >> multigcs.app/Contents/Info.plist
	echo "  <string>multigcs</string>" >> multigcs.app/Contents/Info.plist
	echo "  <key>CFBundleIdentifier</key>" >> multigcs.app/Contents/Info.plist
	echo "  <string>org.multixmedia.www</string>" >> multigcs.app/Contents/Info.plist
	echo "  <key>CFBundleName</key>" >> multigcs.app/Contents/Info.plist
	echo "  <string>multigcs</string>" >> multigcs.app/Contents/Info.plist
	echo "  <key>CFBundleIconFile</key>" >> multigcs.app/Contents/Info.plist
	echo "  <string>multigcs.icns</string>" >> multigcs.app/Contents/Info.plist
	echo "  <key>CFBundleShortVersionString</key>" >> multigcs.app/Contents/Info.plist
	echo "  <string>0.1</string>" >> multigcs.app/Contents/Info.plist
	echo "  <key>CFBundleInfoDictionaryVersion</key>" >> multigcs.app/Contents/Info.plist
	echo "  <string>6.0</string>" >> multigcs.app/Contents/Info.plist
	echo "  <key>CFBundlePackageType</key>" >> multigcs.app/Contents/Info.plist
	echo "  <string>APPL</string>" >> multigcs.app/Contents/Info.plist
	echo "  <key>IFMajorVersion</key>" >> multigcs.app/Contents/Info.plist
	echo "  <integer>0</integer>" >> multigcs.app/Contents/Info.plist
	echo "  <key>IFMinorVersion</key>" >> multigcs.app/Contents/Info.plist
	echo "  <integer>1</integer>" >> multigcs.app/Contents/Info.plist
	echo "</dict>" >> multigcs.app/Contents/Info.plist
	echo "</plist>" >> multigcs.app/Contents/Info.plist





%.o: %.c
	@echo "$< -> $@"
	@gcc -c $(CFLAGS) $< -o $@ ${INCDIR}

gcs: ${COMMONSRC} ${COMMONHDR} ${GCS}
	@echo "linking $@"
	@gcc -DBASE_DIR="\"$(BASE_DIR)\"" $(CFLAGS) ${COMMONSRC} ${GCS} -o $@ ${INCDIR} ${LIBS}

font-generator: font-generator.c
	gcc -DBASE_DIR="\"$(BASE_DIR)\"" -o font-generator font-generator.c -Wall -O -I/usr/include/SDL -lSDL_ttf -lpng


