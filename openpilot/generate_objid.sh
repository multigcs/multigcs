#!/bin/sh
#
#

XML_FILES="/usr/src/CleanFlight/OpenPilot/shared/uavobjectdefinition"
XML_FILES="/usr/src/CleanFlight/TauLabs/shared/uavobjectdefinition"

gcc -o openpilot/generate_objid openpilot/generate_objid.c -I/usr/include/libxml2 -lxml2 || exit 1

rm -rf openpilot/uavobjects.h
rm -rf openpilot/uavobjects_encode.c
rm -rf openpilot/uavobjects_decode.c
rm -rf openpilot/uavobjects_store.c

rm -rf screens/screen_openpilot_guihelper.c
rm -rf screens/screen_openpilot_guimain.c
rm -rf screens/screen_openpilot_gui.c

echo "" > openpilot/uavobjects_decode.c
echo "#include <all.h>" >> openpilot/uavobjects_decode.c
echo "" >> openpilot/uavobjects_decode.c
echo "void uavtalk_decode (uint32_t obj_id, uint8_t *buf) {" >> openpilot/uavobjects_decode.c
echo "	switch (obj_id) {" >> openpilot/uavobjects_decode.c

echo "" > openpilot/uavobjects_encode.c
echo "#include <all.h>" >> openpilot/uavobjects_encode.c
echo "" >> openpilot/uavobjects_encode.c

echo "" > openpilot/uavobjects_store.c
echo "#include <all.h>" >> openpilot/uavobjects_store.c
echo "" >> openpilot/uavobjects_store.c


echo "" > screens/screen_openpilot_guimain.c
#echo "#include <all.h>" >> screens/screen_openpilot_guimain.c
echo "" >> screens/screen_openpilot_guimain.c
echo "uint16_t show_num = 0;" >> screens/screen_openpilot_guimain.c
echo "uint16_t msy = 0;" >> screens/screen_openpilot_guimain.c
echo "" >> screens/screen_openpilot_guimain.c
echo "uint8_t UAVT_gui_show_num_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {" >> screens/screen_openpilot_guimain.c
echo "		show_num = (uint16_t)data;" >> screens/screen_openpilot_guimain.c
echo "		reset_buttons();" >> screens/screen_openpilot_guimain.c
echo "		sy = 0;" >> screens/screen_openpilot_guimain.c
echo "		return 0;" >> screens/screen_openpilot_guimain.c
echo "}" >> screens/screen_openpilot_guimain.c
echo "" >> screens/screen_openpilot_guimain.c
echo "uint8_t UAVT_gui_main_scroll (char *name, float x, float y, int8_t button, float data, uint8_t action) {" >> screens/screen_openpilot_guimain.c
echo "	if (button == 4) {" >> screens/screen_openpilot_guimain.c
echo "		if (msy > 0) {" >> screens/screen_openpilot_guimain.c
echo "			msy--;" >> screens/screen_openpilot_guimain.c
echo "		}" >> screens/screen_openpilot_guimain.c
echo "	} else if (button == 5) {" >> screens/screen_openpilot_guimain.c
echo "		msy++;" >> screens/screen_openpilot_guimain.c
echo "	}" >> screens/screen_openpilot_guimain.c
echo "	reset_buttons();" >> screens/screen_openpilot_guimain.c
echo "	return 0;" >> screens/screen_openpilot_guimain.c
echo "}" >> screens/screen_openpilot_guimain.c
echo "" >> screens/screen_openpilot_guimain.c
echo "void UAVT_gui_show(ESContext *esContext) {" >> screens/screen_openpilot_guimain.c
echo "	uint16_t ny = 0;" >> screens/screen_openpilot_guimain.c
echo "	uint16_t nn = 0;" >> screens/screen_openpilot_guimain.c

SHOW_NUM=1

for XML_FILE in `ls $XML_FILES/*.xml | sort`
do
	openpilot/generate_objid $XML_FILE

	echo "" >> openpilot/uavobjects.h
	echo "/*************************************************************************************************" >> openpilot/uavobjects.h
	basename $XML_FILE | sed "s|^| Filename: |g" >> openpilot/uavobjects.h
	cat openpilot/uavobject_comment.h >> openpilot/uavobjects.h
	echo "*************************************************************************************************/" >> openpilot/uavobjects.h
	echo "" >> openpilot/uavobjects.h

	cat openpilot/uavobject_options.h | grep -v "^extern " >> openpilot/uavobjects_store.c
	cat openpilot/uavobject_save.h | grep -v "^extern " >> openpilot/uavobjects_store.c
	cat openpilot/uavobject_examples.h | sed "s|//memcpy|memcpy|g" | sed "s|^|		|g" >> openpilot/uavobjects_decode.c
	cat openpilot/uavobject_examplessend.h >> openpilot/uavobjects_encode.c

	cat openpilot/uavobject_guihelper.h >> screens/screen_openpilot_guihelper.c
	cat openpilot/uavobject_gui.h >> screens/screen_openpilot_gui.c

	if grep -s -q ".." openpilot/uavobject_guimain.h
	then
		cat openpilot/uavobject_guimain.h | sed "s|SNUM|$SHOW_NUM|g" >> screens/screen_openpilot_guimain.c
		SHOW_NUM=`expr $SHOW_NUM + 1`
	fi

	cat openpilot/uavobject_ids.h >> openpilot/uavobjects.h
	echo "" >> openpilot/uavobjects.h
	cat openpilot/uavobject_defs.h >> openpilot/uavobjects.h
	cat openpilot/uavobject_options.h | grep "^extern " >> openpilot/uavobjects.h
	cat openpilot/uavobject_otypes.h >> openpilot/uavobjects.h
	cat openpilot/uavobject_struct.h >> openpilot/uavobjects.h
	echo "" >> openpilot/uavobjects.h
	cat openpilot/uavobject_save.h | grep "^extern " >> openpilot/uavobjects.h
	echo "" >> openpilot/uavobjects.h

done

echo "	}" >> openpilot/uavobjects_decode.c
echo "}" >> openpilot/uavobjects_decode.c
echo "" >> openpilot/uavobjects_decode.c
echo "" >> openpilot/uavobjects_store.c
echo "	if (msy > nn - 14) {" >> screens/screen_openpilot_guimain.c
echo "		msy = nn - 14;" >> screens/screen_openpilot_guimain.c
echo "	}" >> screens/screen_openpilot_guimain.c
echo "	if (sy > nn - 14) {" >> screens/screen_openpilot_guimain.c
echo "		sy = nn - 14;" >> screens/screen_openpilot_guimain.c
echo "	}" >> screens/screen_openpilot_guimain.c
echo "" >> screens/screen_openpilot_guimain.c
echo "	if (show_num != 0) {" >> screens/screen_openpilot_guimain.c
echo "		draw_text_button(esContext, \"gui_scroll\", VIEW_MODE_FCMENU, \"[SCROLL]\", FONT_WHITE, 0.9, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, UAVT_gui_scroll, 0.0);" >> screens/screen_openpilot_guimain.c
echo "	}" >> screens/screen_openpilot_guimain.c
echo "	if (show_num == 0) {" >> screens/screen_openpilot_guimain.c
echo "		draw_text_button(esContext, \"gui_main_scroll\", VIEW_MODE_FCMENU, \"[SCROLL]\", FONT_WHITE, 0.9, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, UAVT_gui_main_scroll, 0.0);" >> screens/screen_openpilot_guimain.c
echo "	} else {" >> screens/screen_openpilot_guimain.c
echo "		draw_text_button(esContext, \"gui_show_num_change\", VIEW_MODE_FCMENU, \"[BACK]\", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, UAVT_gui_show_num_change, 0.0);" >> screens/screen_openpilot_guimain.c
echo "	}" >> screens/screen_openpilot_guimain.c
echo "}" >> screens/screen_openpilot_guimain.c
echo "" >> screens/screen_openpilot_guimain.c

rm -rf openpilot/uavobject_guihelper.h
rm -rf openpilot/uavobject_guimain.h
rm -rf openpilot/uavobject_gui.h
rm -rf openpilot/uavobject_examplessend.h
rm -rf openpilot/uavobject_examples.h
rm -rf openpilot/uavobject_save.h
rm -rf openpilot/uavobject_comment.h
rm -rf openpilot/uavobject_defs.h
rm -rf openpilot/uavobject_ids.h
rm -rf openpilot/uavobject_otypes.h
rm -rf openpilot/uavobject_options.h
rm -rf openpilot/uavobject_struct.h


