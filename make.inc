
ARCH := `dpkg --print-architecture`
VERSION := 0.92
VERSION_BUILD := `date +%s`
BASE_DIR := /usr/share/multigcs

INCDIR += -I./ -ICommon -Iscreens -Inet -Itcl -Idraw -Imavlink -Igps -Imwi21 -Ijeti -Iopenpilot -Ifrsky -Iminizip -Itracker -Iutils
#INCDIR += -I/usr/include/tcl8.5
INCDIR += $(shell pkg-config --cflags libxml-2.0) $(shell pkg-config --cflags x11) $(shell pkg-config --cflags libpng) $(shell pkg-config --cflags zlib)

#LIBS += -lm -ltcl8.5
LIBS += -lm
LIBS += $(shell pkg-config --libs libxml-2.0) $(shell pkg-config --libs x11) $(shell pkg-config --libs libpng) $(shell pkg-config --libs zlib)

GCS += $(EXTRA_OBJECTS) main.c serial.c draw/draw.c draw/videocapture.c draw/map.c geomag70.c \
	minizip/ioapi.c minizip/unzip.c net/htmlget-wget.c \
	screens/screen_rcflow.c screens/screen_keyboard.c screens/screen_filesystem.c screens/screen_device.c screens/screen_baud.c screens/screen_number.c screens/screen_model.c screens/screen_background.c screens/screen_wpedit.c screens/screen_hud.c screens/screen_map.c screens/screen_map_survey.c screens/screen_map_swarm.c screens/screen_calibration.c screens/screen_fms.c screens/screen_system.c screens/screen_tcl.c screens/screen_mavlink_menu.c screens/screen_tracker.c screens/screen_mwi_menu.c screens/screen_openpilot_menu.c screens/screen_videolist.c screens/screen_graph.c screens/screen_telemetry.c \
	mavlink/my_mavlink.c mavlink/my_mavlink_rewrite.c gps/my_gps.c mwi21/mwi21.c jeti/jeti.c openpilot/openpilot.c openpilot/openpilot_xml.c frsky/frsky.c tracker/tracker.c net/savepng.c net/webserv.c net/webclient.c logging.c kml.c \
	openpilot/uavobjects_store.c openpilot/uavobjects_encode.c openpilot/uavobjects_decode.c \
	weather.c

OBJ = $(GCS:%.c=$(BUILDDIR)/%.o)
COMMONOBJ = $(COMMONSRC:%.c=$(BUILDDIR)/%.o)

default: all

all: $(BUILDDIR)/gcs

clean:
	rm -f $(BUILDDIR)/gcs $(OBJ)
	rm -rf $(BUILDDIR)/

install:
	cp -a $(BUILDDIR)/gcs /usr/bin/gl-gcs
	cp -a utils/gcs.sh /usr/bin/multigcs
	mkdir -p /usr/share/man/man1/
	cat data/man.1 | gzip -9 > /usr/share/man/man1/multigcs.1.gz
	mkdir -p /usr/share/doc/multigcs/
	cp -a README /usr/share/doc/multigcs/README
	cp -a copyright /usr/share/doc/multigcs/copyright
	cp -a GPLv2.txt /usr/share/doc/multigcs/GPLv2.txt
	cp -a multigcs.html /usr/share/doc/multigcs/multigcs.html
	test -e .git && git log | gzip -9 > /usr/share/doc/multigcs/changelog.gz || true
	test -e .git && git log | gzip -9 > /usr/share/doc/multigcs/changelog.Debian.gz || true 
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
	cp -a GPLv2.txt $(BASE_DIR)/webserv/GPLv2.txt
	chmod 0755 /usr/bin/gl-gcs
	chmod 0755 /usr/bin/multigcs
	chmod 0755 $(BASE_DIR)/clean-badmaps.sh

deb: $(BUILDDIR)/gcs
	rm -rf $(BUILDDIR)/package/
	mkdir -p $(BUILDDIR)/package/usr/bin
	cp -a $(BUILDDIR)/gcs $(BUILDDIR)/package/usr/bin/gl-gcs
	cp -a utils/gcs.sh $(BUILDDIR)/package/usr/bin/multigcs
	mkdir -p $(BUILDDIR)/package/usr/share/man/man1/
	cat data/man.1 | gzip -9 > $(BUILDDIR)/package/usr/share/man/man1/multigcs.1.gz
	mkdir -p $(BUILDDIR)/package/usr/share/doc/multigcs/
	cp -a README $(BUILDDIR)/package/usr/share/doc/multigcs/README
	cp -a copyright $(BUILDDIR)/package/usr/share/doc/multigcs/copyright
	cp -a GPLv2.txt $(BUILDDIR)/package/usr/share/doc/multigcs/GPLv2.txt
	cp -a multigcs.html $(BUILDDIR)/package/usr/share/doc/multigcs/multigcs.html
	git log | gzip -9 > $(BUILDDIR)/package/usr/share/doc/multigcs/changelog.gz
	git log | gzip -9 > $(BUILDDIR)/package/usr/share/doc/multigcs/changelog.Debian.gz
	mkdir -p $(BUILDDIR)/package$(BASE_DIR)
	cp -a data/WMM.COF $(BUILDDIR)/package$(BASE_DIR)/
	cp -a data/SRTM.list $(BUILDDIR)/package$(BASE_DIR)/
	cp -a data/map-services.xml $(BUILDDIR)/package$(BASE_DIR)/
	cp -a utils/clean-badmaps.sh $(BUILDDIR)/package$(BASE_DIR)/clean-badmaps.sh
	mkdir -p $(BUILDDIR)/package$(BASE_DIR)/obj3d
	mkdir -p $(BUILDDIR)/package$(BASE_DIR)/textures
	cp -a textures/* $(BUILDDIR)/package$(BASE_DIR)/textures/
	mkdir -p $(BUILDDIR)/package$(BASE_DIR)/fonts
	cp -a fonts/* $(BUILDDIR)/package$(BASE_DIR)/fonts/
	mkdir -p $(BUILDDIR)/package$$(BASE_DIR)/mixes
	cp -a data/mixes/* $(BUILDDIR)/package$$(BASE_DIR)/mixes/
	mkdir -p $(BUILDDIR)/package$(BASE_DIR)/rcflow_presets
	cp -a rcflow_presets/* $(BUILDDIR)/package$(BASE_DIR)/rcflow_presets/
	mkdir -p $(BUILDDIR)/package$(BASE_DIR)/scripts
	cp -a screens/screen_tcl.tcl $(BUILDDIR)/package$(BASE_DIR)/scripts/screen_tcl.tcl
	mkdir -p $(BUILDDIR)/package$(BASE_DIR)/mavlink
	cp -a mavlink/ParameterMetaData*.xml $(BUILDDIR)/package$(BASE_DIR)/mavlink/
	mkdir -p $(BUILDDIR)/package$(BASE_DIR)/webserv
	cp -a multigcs.html $(BUILDDIR)/package$(BASE_DIR)/webserv/multigcs.html
	cp -a textures/marker.png $(BUILDDIR)/package$(BASE_DIR)/webserv/marker.png
	cp -a textures/MULTICOPTER.png $(BUILDDIR)/package$(BASE_DIR)/webserv/model.png
	cp -a net/map.js $(BUILDDIR)/package$(BASE_DIR)/webserv/map.js
	cp -a net/webserv-index.html $(BUILDDIR)/package$(BASE_DIR)/webserv/index.html
	cp -a net/style.css $(BUILDDIR)/package$(BASE_DIR)/webserv/style.css
	cp -a net/favicon.ico $(BUILDDIR)/package$(BASE_DIR)/webserv/favicon.ico
	cp -a net/blender-export.py $(BUILDDIR)/package$(BASE_DIR)/webserv/blender-export.py
	cp -a net/plane.dae $(BUILDDIR)/package$(BASE_DIR)/webserv/plane.dae
	cp -a net/simple.dae $(BUILDDIR)/package$(BASE_DIR)/webserv/simple.dae
	cp -a copyright $(BUILDDIR)/package$(BASE_DIR)/webserv/copyright
	cp -a GPLv2.txt $(BUILDDIR)/package$(BASE_DIR)/webserv/GPLv2.txt
	chmod 0755 $(BUILDDIR)/package/usr/bin/gl-gcs
	chmod 0755 package/usr/bin/multigcs
	chmod 0755 $(BUILDDIR)/package$(BASE_DIR)/clean-badmaps.sh
	mkdir -p  $(BUILDDIR)/package/DEBIAN
	echo "Package: multigcs" >  $(BUILDDIR)/package/DEBIAN/control
	echo "Source: multigcs" >> $(BUILDDIR)/package/DEBIAN/control
	echo "Version: $(VERSION)" >> $(BUILDDIR)/package/DEBIAN/control
	echo "Architecture: $(ARCH)" >> $(BUILDDIR)/package/DEBIAN/control
	echo "Maintainer: Oliver Dippel <oliver@multixmedia.org>" >> $(BUILDDIR)/package/DEBIAN/control
	echo "Depends: $(DEB_DEPENDS)" >> $(BUILDDIR)/package/DEBIAN/control
	echo "Section: media" >> $(BUILDDIR)/package/DEBIAN/control
	echo "Priority: optional" >> $(BUILDDIR)/package/DEBIAN/control
	echo "Description: Ground-Control-Station based on OpenGL(-ES)" >> $(BUILDDIR)/package/DEBIAN/control
	echo " Ground-Control-Station based on OpenGL(-ES)" >> $(BUILDDIR)/package/DEBIAN/control
	chmod -R -s $(BUILDDIR)/package/ -R
	chmod 0755 $(BUILDDIR)/package/DEBIAN/ -R
	dpkg-deb --build $(BUILDDIR)/package
	mv $(BUILDDIR)/package.deb $(BUILDDIR)/multigcs-$(VERSION_NAME)_$(VERSION)-$(VERSION_BUILD)_$(ARCH).deb

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$< -> $@"
	@$(COMP) -c $(CFLAGS) $< -o $@ ${INCDIR}

$(BUILDDIR)/gcs: ${COMMONOBJ} ${COMMONHDR} ${OBJ}
	@echo "linking $@"
	@$(COMP) -DBASE_DIR="\"$(BASE_DIR)\"" $(CFLAGS) ${COMMONSRC} ${GCS} -o $@ ${INCDIR} ${LIBS}

font-generator: font-generator.c
	$(COMP) -DBASE_DIR="\"$(BASE_DIR)\"" -o font-generator font-generator.c -Wall -O -I/usr/include/SDL -lSDL_ttf -lpng

astyle:
	astyle --lineend=linux --mode=c --max-code-length=200 --break-after-logical --add-brackets --indent-switches --indent-cases --indent-col1-comments --indent=tab --indent=force-tab --unpad-paren --pad-oper --pad-header --delete-empty-lines --align-pointer=name --align-reference=name --remove-comment-prefix --style=google */*.c */*.h *.c *.h
	rm -rf */*.c.orig */*.h*.orig *.c.orig *.h.orig

