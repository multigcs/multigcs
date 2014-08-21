#!/bin/sh
#
#

## Export GUI:
#
#  ./openpilot_convert_xml2header.sh "" 6
#
## Export XML read/write:
#
#  ./openpilot_convert_xml2header.sh "" 9
#

GUIXML="stabilizationsettings.xml hwsettings.xml systemsettings.xml"

XMLFILE="$1"
MODE="$2"

if test "$MODE" != "6" && test "$MODE" != "9"
then
	OBJ_NAME="`xml2 < $XMLFILE | grep "^/xml/object/@name=" | cut -d"=" -f2-`"
	OBJ_DESC="`xml2 < $XMLFILE | grep "^/xml/object/description=" | cut -d"=" -f2-`"
	OBJ_NAME_lc="`echo $OBJ_NAME | tr "A-Z" "a-z"`"
	OBJID="`grep OBJID /usr/src/OpenPilot/build/uavobject-synthetics/gcs/$OBJ_NAME_lc.h | sed "s|.* = ||g" | sed "s|;.*||g"`"
	OBJID1="`echo $OBJID | cut -b 3-4`"
	OBJID2="`echo $OBJID | cut -b 5-6`"
	OBJID3="`echo $OBJID | cut -b 7-8`"
	OBJID4="`echo $OBJID | cut -b 9-10`"
fi

if test "$MODE" = "" || test "$MODE" = "1"
then
echo ""
echo "/* $OBJ_DESC */"
echo "#define `echo "$OBJ_NAME" | tr "a-z" "A-Z"`_OBJID $OBJID"
echo "typedef struct {"
for GET_TYPE in float 32 16 8 enum
do
	(xml2 < $XMLFILE ; echo /xml/object/field) | while read LINE
	do
		VAR="`echo $LINE | cut -d"=" -f1`"
		VAL="`echo $LINE | cut -d"=" -f2-`"
		if test "$LINE" = "/xml/object/field"
		then
			if echo "$TYPE" | grep -s -q "$GET_TYPE"
			then
				if test "$TYPE" = "enum"
				then
					TYPE="uint8_t"
				elif test "$TYPE" != "float"
				then
					TYPE="${TYPE}_t"
				fi
				if test "$ELEMENTNAMES" != ""
				then
					NUM_ELEMENTNAMES="`echo $ELEMENTNAMES | tr "," " " | wc -w`"
					NAME="$NAME[$NUM_ELEMENTNAMES]"
				fi
				echo "	$TYPE $NAME;"
			fi
			NAME=""
			UNITS=""
			TYPE=""
			ELEMENTS=""
			ELEMENTNAMES=""
			OPTIONS=""
			DEFAULT=""
			LIMIT=""
		elif test "$VAR" = "/xml/object/field/@name"
		then
			NAME="$VAL"
		elif test "$VAR" = "/xml/object/field/@units"
		then
			UNITS="$VAL"
		elif test "$VAR" = "/xml/object/field/@type"
		then
			TYPE="$VAL"
		elif test "$VAR" = "/xml/object/field/@elements"
		then
			ELEMENTS="$VAL"
		elif test "$VAR" = "/xml/object/field/@elementnames"
		then
			ELEMENTNAMES="$VAL"
		elif test "$VAR" = "/xml/object/field/@options"
		then
			OPTIONS="$VAL"
		elif test "$VAR" = "/xml/object/field/@defaultvalue"
		then
			DEFAULT="$VAL"
		elif test "$VAR" = "/xml/object/field/@limits"
		then
			LIMIT="$VAL"
	#	else
	#		echo "### $LINE ###"
		fi
	done
done
echo "} ${OBJ_NAME}Data;"
echo ""
fi



if test "$MODE" = "" || test "$MODE" = "2"
then
echo ""
echo "/*"
echo "	case `echo "$OBJ_NAME" | tr "a-z" "A-Z"`_OBJID: {"
echo "		${OBJ_NAME}Data *data = (${OBJ_NAME}Data *)&openpilot_read_buf[8];"
echo "		printf(\"<< `echo "$OBJ_NAME" | tr "a-z" "A-Z"`:\\\n\");"

for GET_TYPE in float 32 16 8 enum
do
	(xml2 < $XMLFILE ; echo /xml/object/field) | while read LINE
	do
		VAR="`echo $LINE | cut -d"=" -f1`"
		VAL="`echo $LINE | cut -d"=" -f2-`"
		if test "$LINE" = "/xml/object/field"
		then
			if echo "$TYPE" | grep -s -q "$GET_TYPE"
			then

				RTYPE="$TYPE"
				if test "$TYPE" = "enum"
				then
					TYPE="i"
				elif test "$TYPE" != "float"
				then
					TYPE="i"
				else
					TYPE="f"
				fi
				if test "$ELEMENTNAMES" != ""
				then
					NUM_ELEMENTNAMES="`echo $ELEMENTNAMES | tr "," " " | wc -w`"
					NUM_ELEMENTNAMES="`expr $NUM_ELEMENTNAMES - 1`"

					for NUM in `seq 0 $NUM_ELEMENTNAMES`
					do
						NUM2="`expr $NUM + 1`"
						ENAME="`echo $ELEMENTNAMES | tr "," " " | cut -d" " -f$NUM2`"
						echo "		printf(\"	$NAME($ENAME): %$TYPE\\\n\", data->$NAME[$NUM]);"
					done

				else
					echo "		printf(\"	$NAME: %$TYPE\\\n\", data->$NAME);"
				fi
			fi
			NAME=""
			UNITS=""
			TYPE=""
			ELEMENTS=""
			ELEMENTNAMES=""
			OPTIONS=""
			DEFAULT=""
			LIMIT=""
		elif test "$VAR" = "/xml/object/field/@name"
		then
			NAME="$VAL"
		elif test "$VAR" = "/xml/object/field/@units"
		then
			UNITS="$VAL"
		elif test "$VAR" = "/xml/object/field/@type"
		then
			TYPE="$VAL"
		elif test "$VAR" = "/xml/object/field/@elements"
		then
			ELEMENTS="$VAL"
		elif test "$VAR" = "/xml/object/field/@elementnames"
		then
			ELEMENTNAMES="$VAL"
		elif test "$VAR" = "/xml/object/field/@options"
		then
			OPTIONS="$VAL"
		elif test "$VAR" = "/xml/object/field/@defaultvalue"
		then
			DEFAULT="$VAL"
		elif test "$VAR" = "/xml/object/field/@limits"
		then
			LIMIT="$VAL"
	#	else
	#		echo "### $LINE ###"
		fi
	done
done
echo "		break;"
echo "	}"
echo "*/"
echo ""
fi


if test "$MODE" = "" || test "$MODE" = "3"
then

echo ""
echo "void openpilot_defaults_$OBJ_NAME (${OBJ_NAME}Data *data) {"

for GET_TYPE in float 32 16 8 enum
do
	(xml2 < $XMLFILE ; echo /xml/object/field) | while read LINE
	do
		VAR="`echo $LINE | cut -d"=" -f1`"
		VAL="`echo $LINE | cut -d"=" -f2-`"
		if test "$LINE" = "/xml/object/field"
		then
			if echo "$TYPE" | grep -s -q "$GET_TYPE"
			then

				RTYPE="$TYPE"
				if test "$TYPE" = "enum"
				then
					TYPE="i"
				elif test "$TYPE" != "float"
				then
					TYPE="i"
				else
					TYPE="f"
				fi
				if test "$ELEMENTNAMES" != ""
				then
					NUM_ELEMENTNAMES="`echo $ELEMENTNAMES | tr "," " " | wc -w`"
					NUM_ELEMENTNAMES="`expr $NUM_ELEMENTNAMES - 1`"

					for NUM in `seq 0 $NUM_ELEMENTNAMES`
					do
						NUM2="`expr $NUM + 1`"
						ENAME="`echo $ELEMENTNAMES | tr "," " " | cut -d" " -f$NUM2`"
						EDEFAULT="`echo $DEFAULT | tr "," " " | cut -d" " -f$NUM2`"
						if test "$RTYPE" = "enum"
						then
							NUM2="0"
							for OPTION in `echo $OPTIONS | tr "," " "`
							do
								if test "$DEFAULT" = "$OPTION"
								then
									echo "	data->$NAME[$NUM] = $NUM2; // $DEFAULT"
								fi
								NUM2="`expr $NUM2 + 1`"
							done
						else
							echo "	data->$NAME[$NUM] = $EDEFAULT;"
						fi
					done
				else
					if test "$RTYPE" = "enum"
					then
						NUM2="0"
						for OPTION in `echo $OPTIONS | tr "," " "`
						do
							if test "$DEFAULT" = "$OPTION"
							then
								echo "	data->$NAME = $NUM2; // $DEFAULT"
							fi
							NUM2="`expr $NUM2 + 1`"
						done
					else
						echo "	data->$NAME = $DEFAULT;"
					fi
				fi

			fi
			NAME=""
			UNITS=""
			TYPE=""
			ELEMENTS=""
			ELEMENTNAMES=""
			OPTIONS=""
			DEFAULT=""
			LIMIT=""
		elif test "$VAR" = "/xml/object/field/@name"
		then
			NAME="$VAL"
		elif test "$VAR" = "/xml/object/field/@units"
		then
			UNITS="$VAL"
		elif test "$VAR" = "/xml/object/field/@type"
		then
			TYPE="$VAL"
		elif test "$VAR" = "/xml/object/field/@elements"
		then
			ELEMENTS="$VAL"
		elif test "$VAR" = "/xml/object/field/@elementnames"
		then
			ELEMENTNAMES="$VAL"
		elif test "$VAR" = "/xml/object/field/@options"
		then
			OPTIONS="$VAL"
		elif test "$VAR" = "/xml/object/field/@defaultvalue"
		then
			DEFAULT="$VAL"
		elif test "$VAR" = "/xml/object/field/@limits"
		then
			LIMIT="$VAL"
	#	else
	#		echo "### $LINE ###"
		fi
	done
done
echo "}"
echo ""
echo "void openpilot_send_$OBJ_NAME (${OBJ_NAME}Data *data) {"
echo "	uint8_t openpilot_write_buf[256];"
echo "	uint8_t crc = 0;"
echo "	uint8_t n = 0;"
echo "	uint8_t n2 = 0;"
echo "	uint8_t len = 0;"
echo "	len = 18;"
echo "	openpilot_write_buf[n++] = 0x3c;	// Start"
echo "	openpilot_write_buf[n++] = 0x22;	// Command (20, 22)"
echo "	openpilot_write_buf[n++] = len;		// Len1"
echo "	openpilot_write_buf[n++] = 0x00;	// Len2"
echo "	openpilot_write_buf[n++] = 0x$OBJID4;	// ObjID4"
echo "	openpilot_write_buf[n++] = 0x$OBJID3;	// ObjID3"
echo "	openpilot_write_buf[n++] = 0x$OBJID2;	// ObjID2"
echo "	openpilot_write_buf[n++] = 0x$OBJID1;	// ObjID1"
echo ""
echo "	memcpy(&openpilot_write_buf[8], &data, sizeof(${OBJ_NAME}Data));"
echo ""
echo "	crc = 0;"
echo "	for (n2 = 0; n2 < len; n2++) {"
echo "		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);"
echo "	}"
echo "	openpilot_write_buf[len] = crc; 	//Checksum"
echo "	write(serial_fd_openpilot, openpilot_write_buf, len + 1);"
echo "}"
echo ""
echo "void openpilot_request_$OBJ_NAME (void) {"
echo "	uint8_t openpilot_write_buf[256];"
echo "	uint8_t crc = 0;"
echo "	uint8_t n = 0;"
echo "	uint8_t n2 = 0;"
echo "	uint8_t len = 0;"
echo "	len = 8;"
echo "	openpilot_write_buf[n++] = 0x3c;	// Start"
echo "	openpilot_write_buf[n++] = 0x21;	// Command"
echo "	openpilot_write_buf[n++] = len;		// Len1"
echo "	openpilot_write_buf[n++] = 0x00;	// Len2"
echo "	openpilot_write_buf[n++] = 0x$OBJID4;	// ObjID4"
echo "	openpilot_write_buf[n++] = 0x$OBJID3;	// ObjID3"
echo "	openpilot_write_buf[n++] = 0x$OBJID2;	// ObjID2"
echo "	openpilot_write_buf[n++] = 0x$OBJID1;	// ObjID1"
echo "	crc = 0;"
echo "	for (n2 = 0; n2 < len; n2++) {"
echo "		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);"
echo "	}"
echo "	openpilot_write_buf[len] = crc; 	//Checksum"
echo "	write(serial_fd_openpilot, openpilot_write_buf, len + 1);"
echo "}"
echo ""
fi



if test "$MODE" = "" || test "$MODE" = "4"
then

echo ""
for GET_TYPE in float 32 16 8 enum
do
	(xml2 < $XMLFILE ; echo /xml/object/field) | while read LINE
	do
		VAR="`echo $LINE | cut -d"=" -f1`"
		VAL="`echo $LINE | cut -d"=" -f2-`"
		if test "$LINE" = "/xml/object/field"
		then
			if echo "$TYPE" | grep -s -q "$GET_TYPE"
			then
				RTYPE="$TYPE"
				if test "$TYPE" != "float"
				then
					TYPE="int8_t"
				fi
				if test "$ELEMENTNAMES" != ""
				then
					NUM_ELEMENTNAMES="`echo $ELEMENTNAMES | tr "," " " | wc -w`"
					NUM_ELEMENTNAMES="`expr $NUM_ELEMENTNAMES - 1`"
					for NUM in `seq 0 $NUM_ELEMENTNAMES`
					do
						NUM2="`expr $NUM + 1`"
						ENAME="`echo $ELEMENTNAMES | tr "," " " | cut -d" " -f$NUM2`"
						EDEFAULT="`echo $DEFAULT | tr "," " " | cut -d" " -f$NUM2`"

echo "uint8_t openpilot_change_Openpilot${OBJ_NAME}_${NAME}_${ENAME} (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
if test "$RTYPE" = "enum"
then
	ENUM_MAX="`echo $OPTIONS | tr "," " " | wc -w`"
	echo "	if ((${TYPE})data < 0 && Openpilot$OBJ_NAME.$NAME[$NUM] > 0) {"
	echo "		Openpilot$OBJ_NAME.$NAME[$NUM] += (${TYPE})data;"
	echo "	} else if ((${TYPE})data > 0 && Openpilot$OBJ_NAME.$NAME[$NUM] < $ENUM_MAX - 1) {"
	echo "		Openpilot$OBJ_NAME.$NAME[$NUM] += (${TYPE})data;"
	echo "	} else {"
	echo "		Openpilot$OBJ_NAME.$NAME[$NUM] = 0;"
	echo "	}"
else
	echo "	Openpilot$OBJ_NAME.$NAME[$NUM] += (${TYPE})data;"
fi
echo "	return 0;"
echo "}"
echo ""

					done
				else

echo "uint8_t openpilot_change_Openpilot${OBJ_NAME}_${NAME} (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
if test "$RTYPE" = "enum"
then
	ENUM_MAX="`echo $OPTIONS | tr "," " " | wc -w`"
	echo "	if ((${TYPE})data < 0 && Openpilot$OBJ_NAME.$NAME > 0) {"
	echo "		Openpilot$OBJ_NAME.$NAME += (${TYPE})data;"
	echo "	} else if ((${TYPE})data > 0 && Openpilot$OBJ_NAME.$NAME < $ENUM_MAX - 1) {"
	echo "		Openpilot$OBJ_NAME.$NAME += (${TYPE})data;"
	echo "	} else {"
	echo "		Openpilot$OBJ_NAME.$NAME = 0;"
	echo "	}"
else
	echo "	Openpilot$OBJ_NAME.$NAME += (${TYPE})data;"
fi
echo "	return 0;"
echo "}"
echo ""
				fi
			fi
			NAME=""
			UNITS=""
			TYPE=""
			ELEMENTS=""
			ELEMENTNAMES=""
			OPTIONS=""
			DEFAULT=""
			LIMIT=""
		elif test "$VAR" = "/xml/object/field/@name"
		then
			NAME="$VAL"
		elif test "$VAR" = "/xml/object/field/@units"
		then
			UNITS="$VAL"
		elif test "$VAR" = "/xml/object/field/@type"
		then
			TYPE="$VAL"
		elif test "$VAR" = "/xml/object/field/@elements"
		then
			ELEMENTS="$VAL"
		elif test "$VAR" = "/xml/object/field/@elementnames"
		then
			ELEMENTNAMES="$VAL"
		elif test "$VAR" = "/xml/object/field/@options"
		then
			OPTIONS="$VAL"
		elif test "$VAR" = "/xml/object/field/@defaultvalue"
		then
			DEFAULT="$VAL"
		elif test "$VAR" = "/xml/object/field/@limits"
		then
			LIMIT="$VAL"
	#	else
	#		echo "### $LINE ###"
		fi
	done
done
echo ""


echo "void openpilot_$OBJ_NAME (ESContext *esContext) {"
echo "	uint8_t i = 0;"
echo "	int16_t n = 0;"
echo "	int16_t n2 = 0;"
echo "	char tmp_str[100];"
echo ""
echo "	draw_button(esContext, \"title\", VIEW_MODE_FCMENU, \"$OBJ_NAME\", FONT_WHITE, 0.0, -0.95, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_null, n);"
echo ""
for GET_TYPE in float 32 16 8 enum
do
	(xml2 < $XMLFILE ; echo /xml/object/field) | while read LINE
	do
		VAR="`echo $LINE | cut -d"=" -f1`"
		VAL="`echo $LINE | cut -d"=" -f2-`"
		if test "$LINE" = "/xml/object/field"
		then
			if echo "$TYPE" | grep -s -q "$GET_TYPE"
			then
				RTYPE="$TYPE"
				if test "$TYPE" = "enum"
				then
					TYPE="i"
				elif test "$TYPE" != "float"
				then
					TYPE="i"
				else
					TYPE="f"
				fi
				if test "$ELEMENTNAMES" != ""
				then

					NUM_ELEMENTNAMES="`echo $ELEMENTNAMES | tr "," " " | wc -w`"
					NUM_ELEMENTNAMES="`expr $NUM_ELEMENTNAMES - 1`"

					echo "	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {"
					echo "		draw_button(esContext, \"name_$NAME\", VIEW_MODE_FCMENU, \"$NAME\", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);"
					echo "		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);"
					echo "	}"
					echo "	n++;"

					for NUM in `seq 0 $NUM_ELEMENTNAMES`
					do
						echo "	if (n2 >= 2) {"
						echo "		n++;"
						echo "		n2 = 0;"
						echo "	}"
						NUM2="`expr $NUM + 1`"
						ENAME="`echo $ELEMENTNAMES | tr "," " " | cut -d" " -f$NUM2`"
						EDEFAULT="`echo $DEFAULT | tr "," " " | cut -d" " -f$NUM2`"
						echo "	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {"
						echo "		draw_button(esContext, \"name_$NAME[$ENAME]\", VIEW_MODE_FCMENU, \"$ENAME\", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);"
						if test "$TYPE" = "f"
						then
							echo "		sprintf(tmp_str, \"%0.6f\", Openpilot$OBJ_NAME.$NAME[$NUM]);"
							echo "		for (i = 0; i < 5; i++) {"
							echo "			if (tmp_str[strlen(tmp_str) - 1] == '0') {"
							echo "				tmp_str[strlen(tmp_str) - 1] = 0;"
							echo "			}"
							echo "		}"
							STEP="0.01"
						elif test "$RTYPE" = "enum"
						then
							echo "		sprintf(tmp_str, \"%$TYPE\", Openpilot$OBJ_NAME.$NAME[$NUM]);"
							NN="0"
							for OPTION in `echo $OPTIONS | tr "," " "`
							do
								echo "		if (Openpilot$OBJ_NAME.$NAME[$NUM] == $NN) {"
								echo "			sprintf(tmp_str, \"$OPTION\");"
								echo "		}"
								NN="`expr $NN + 1`"
							done
							STEP="1"
						else
							echo "		sprintf(tmp_str, \"%$TYPE\", Openpilot$OBJ_NAME.$NAME[$NUM]);"
							STEP="1"
						fi
						echo "		draw_button(esContext, \"default_$NAME[$ENAME]\", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);"
						echo "		draw_button(esContext, \"dec_$NAME[$ENAME]\", VIEW_MODE_FCMENU, \"[-]\", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_Openpilot${OBJ_NAME}_${NAME}_${ENAME}, -$STEP);"
						echo "		draw_button(esContext, \"inc_$NAME[$ENAME]\", VIEW_MODE_FCMENU, \"[+]\", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_Openpilot${OBJ_NAME}_${NAME}_${ENAME}, +$STEP);"
						echo "	}"
						echo "	n2++;"
					done
					echo "	n++;"
					echo "	n2 = 0;"

				else
					echo "	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {"
					echo "		draw_button(esContext, \"name_$NAME\", VIEW_MODE_FCMENU, \"$NAME\", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);"

					if test "$TYPE" = "f"
					then
						echo "		sprintf(tmp_str, \"%0.6f\", Openpilot$OBJ_NAME.$NAME);"
						echo "		for (i = 0; i < 5; i++) {"
						echo "			if (tmp_str[strlen(tmp_str) - 1] == '0') {"
						echo "				tmp_str[strlen(tmp_str) - 1] = 0;"
						echo "			}"
						echo "		}"
						STEP="0.01"
					elif test "$RTYPE" = "enum"
					then
						echo "		sprintf(tmp_str, \"%$TYPE\", Openpilot$OBJ_NAME.$NAME);"
						NN="0"
						for OPTION in `echo $OPTIONS | tr "," " "`
						do
							echo "		if (Openpilot$OBJ_NAME.$NAME == $NN) {"
							echo "			sprintf(tmp_str, \"$OPTION\");"
							echo "		}"
							NN="`expr $NN + 1`"
						done
						STEP="1"
					else
						echo "		sprintf(tmp_str, \"%$TYPE\", Openpilot$OBJ_NAME.$NAME);"
						STEP="1"
					fi
					echo "		draw_button(esContext, \"val_$NAME\", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);"
					echo "		draw_button(esContext, \"dec_$NAME\", VIEW_MODE_FCMENU, \"[-]\", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_Openpilot${OBJ_NAME}_${NAME}, -$STEP);"
					echo "		draw_button(esContext, \"inc_$NAME\", VIEW_MODE_FCMENU, \"[+]\", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_Openpilot${OBJ_NAME}_${NAME}, +$STEP);"
					echo "	}"
					echo "	n++;"
				fi
			fi
			NAME=""
			UNITS=""
			TYPE=""
			ELEMENTS=""
			ELEMENTNAMES=""
			OPTIONS=""
			DEFAULT=""
			LIMIT=""
		elif test "$VAR" = "/xml/object/field/@name"
		then
			NAME="$VAL"
		elif test "$VAR" = "/xml/object/field/@units"
		then
			UNITS="$VAL"
		elif test "$VAR" = "/xml/object/field/@type"
		then
			TYPE="$VAL"
		elif test "$VAR" = "/xml/object/field/@elements"
		then
			ELEMENTS="$VAL"
		elif test "$VAR" = "/xml/object/field/@elementnames"
		then
			ELEMENTNAMES="$VAL"
		elif test "$VAR" = "/xml/object/field/@options"
		then
			OPTIONS="$VAL"
		elif test "$VAR" = "/xml/object/field/@defaultvalue"
		then
			DEFAULT="$VAL"
		elif test "$VAR" = "/xml/object/field/@limits"
		then
			LIMIT="$VAL"
	#	else
	#		echo "### $LINE ###"
		fi
	done
done
echo ""

echo "	if (n > 13) {"
echo "		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, 0.77, 0.002, 255, 255, 255, 128);"
echo "		if (page < 0) {"
echo "			set_button(\"down\", VIEW_MODE_FCMENU, 1.3, -0.77, 1.35, -0.67, openpilot_down, 1.0);"
echo "			set_button(\"down2\", VIEW_MODE_FCMENU, 1.3, -0.77, 1.35, 0.0, openpilot_down, 3.0);"
echo "		}"
echo "		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);"
echo "		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);"
echo "		draw_rect_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);"
echo "		if (n + page - 13 > 0) {"
echo "			set_button(\"up\", VIEW_MODE_FCMENU, 1.3, 0.67, 1.35, 0.77, openpilot_up, 1.0);"
echo "			set_button(\"up2\", VIEW_MODE_FCMENU, 1.3, 0.0, 1.35, 0.77, openpilot_up, 3.0);"
echo "		}"
echo "		if (page > 0) {"
echo "			page = 0;"
echo "		}"
echo "		if (page < (n - 13) * -1) {"
echo "			page = (n - 13) * -1;"
echo "		}"
echo "		draw_box_f3(esContext, 1.3, 0.67, 0.002, 1.35, 0.77, 0.002, 255, 255, 255, 128);"
echo "		draw_box_f3(esContext, 1.3, 0.77, 0.002, 1.35, 0.67, 0.002, 255, 255, 255, 128);"
echo "		draw_rect_f3(esContext, 1.3, 0.77, 0.002, 1.35, 0.67, 0.002, 255, 255, 255, 128);"
echo "		draw_box_f3(esContext, 1.3 - 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13) - 0.02, 0.002, 1.35 + 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13), 0.002, 255, 255, 255, 200);"
echo "		draw_rect_f3(esContext, 1.3 - 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13) - 0.02, 0.002, 1.35 + 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13), 0.002, 100, 100, 100, 128);"
echo "	}"
echo "	if (openpilot_get == 1) {"
echo "		draw_button(esContext, \"get\", VIEW_MODE_FCMENU, \"[GET]\", FONT_GREEN, -0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_get, 0.0);"
echo "	} else {"
echo "		draw_button(esContext, \"get\", VIEW_MODE_FCMENU, \"[GET]\", FONT_WHITE, -0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_get, 0.0);"
echo "	}"
echo "	if (openpilot_set == 1) {"
echo "		draw_button(esContext, \"set\", VIEW_MODE_FCMENU, \"[SET]\", FONT_GREEN, 0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_set, 0.0);"
echo "	} else {"
echo "		draw_button(esContext, \"set\", VIEW_MODE_FCMENU, \"[SET]\", FONT_WHITE, 0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_set, 0.0);"
echo "	}"
echo "	draw_button(esContext, \"defaults\", VIEW_MODE_FCMENU, \"[DEFAULTS]\", FONT_WHITE, -0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_defaults, 0.0);"
echo "	draw_button(esContext, \"flash\", VIEW_MODE_FCMENU, \"[FLASH]\", FONT_WHITE, 0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_flash, 0.0);"
echo "}"
echo ""

fi


if test "$MODE" = "5"
then
	echo "		openpilot_$OBJ_NAME(esContext);"
elif test "$MODE" = "5b"
then
	echo "	openpilot_defaults_${OBJ_NAME}(&Openpilot${OBJ_NAME});"
fi

if test "$MODE" = "6"
then
echo ""
echo "#include <stdint.h>"
echo "#include <model.h>"
echo "#include <userdata.h>"
echo "#include <main.h>"
echo "#include <screen_openpilot_menu.h>"
echo "#include <openpilot.h>"
echo ""
echo "#define MAX_PER_PAGE 12"
echo ""
echo "static int8_t page = 0;"
echo "static uint8_t mode = 0;"
echo ""
echo "uint8_t openpilot_null (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
echo "	return 0;"
echo "}"
echo ""
echo "uint8_t openpilot_defaults (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
NUM="0"
for XML in $GUIXML
do
	$0 /usr/src/OpenPilot/shared/uavobjectdefinition/$XML 5b
	NUM="`expr $NUM + 1`"
done
echo "	return 0;"
echo "}"
echo ""
echo "uint8_t openpilot_flash (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
echo "	openpilot_save_to_flash();"
echo "	return 0;"
echo "}"
echo ""
echo "uint8_t openpilot_mode (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
echo "	if (mode < 2) {"
echo "		mode++;"
echo "	} else {"
echo "		mode = 0;"
echo "	}"
echo "	page = 0;"
echo "	return 0;"
echo "}"
echo ""
echo "uint8_t openpilot_setup_get (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
echo "	openpilot_get = 1;"
echo "	return 0;"
echo "}"
echo ""
echo "uint8_t openpilot_setup_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
echo "	openpilot_set = 1;"
echo "	return 0;"
echo "}"
echo ""
echo "uint8_t openpilot_down (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
echo "	if (page < 0) {"
echo "		page += (int8_t)data;"
echo "	}"
echo "	return 0;"
echo "}"
echo ""
echo "uint8_t openpilot_up (char *name, float x, float y, int8_t button, float data, uint8_t action) {"
echo "	if (page > -50) {"
echo "		page -= (int8_t)data;"
echo "	}"
echo "	return 0;"
echo "}"
echo ""
for XML in $GUIXML
do
	$0 /usr/src/OpenPilot/shared/uavobjectdefinition/$XML 4
done
echo "void screen_openpilot (ESContext *esContext) {"
echo "	if (mode == -1) {"
NUM="0"
for XML in $GUIXML
do
	echo "	} else if (mode == $NUM) {"
	$0 /usr/src/OpenPilot/shared/uavobjectdefinition/$XML 5
	NUM="`expr $NUM + 1`"
done
echo "	}"
echo "	draw_button(esContext, \"mode\", VIEW_MODE_FCMENU, \"[MODE]\", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_mode, 0.0);"
echo "}"
echo ""
fi






if test "$MODE" = "7"
then

echo ""
echo "void openpilot_save_xml_$OBJ_NAME (FILE *fr, ${OBJ_NAME}Data *data) {"
echo "	fprintf(fr, \"  <$OBJ_NAME>\\n\");"
for GET_TYPE in float 32 16 8 enum
do
	(xml2 < $XMLFILE ; echo /xml/object/field) | while read LINE
	do
		VAR="`echo $LINE | cut -d"=" -f1`"
		VAL="`echo $LINE | cut -d"=" -f2-`"
		if test "$LINE" = "/xml/object/field"
		then
			if echo "$TYPE" | grep -s -q "$GET_TYPE"
			then
				RTYPE="$TYPE"
				if test "$TYPE" = "enum"
				then
					TYPE="i"
				elif test "$TYPE" != "float"
				then
					TYPE="i"
				else
					TYPE="f"
				fi
				if test "$ELEMENTNAMES" != ""
				then
					NUM_ELEMENTNAMES="`echo $ELEMENTNAMES | tr "," " " | wc -w`"
					NUM_ELEMENTNAMES="`expr $NUM_ELEMENTNAMES - 1`"
					for NUM in `seq 0 $NUM_ELEMENTNAMES`
					do
						NUM2="`expr $NUM + 1`"
						ENAME="`echo $ELEMENTNAMES | tr "," " " | cut -d" " -f$NUM2`"
						echo "	fprintf(fr, \"   <${NAME}_$ENAME>%$TYPE</${NAME}_$ENAME>\\n\", data->$NAME[$NUM]);"
					done
				else
					echo "	fprintf(fr, \"   <$NAME>%$TYPE</$NAME>\\n\", data->$NAME);"
				fi
			fi
			NAME=""
			UNITS=""
			TYPE=""
			ELEMENTS=""
			ELEMENTNAMES=""
			OPTIONS=""
			DEFAULT=""
			LIMIT=""
		elif test "$VAR" = "/xml/object/field/@name"
		then
			NAME="$VAL"
		elif test "$VAR" = "/xml/object/field/@units"
		then
			UNITS="$VAL"
		elif test "$VAR" = "/xml/object/field/@type"
		then
			TYPE="$VAL"
		elif test "$VAR" = "/xml/object/field/@elements"
		then
			ELEMENTS="$VAL"
		elif test "$VAR" = "/xml/object/field/@elementnames"
		then
			ELEMENTNAMES="$VAL"
		elif test "$VAR" = "/xml/object/field/@options"
		then
			OPTIONS="$VAL"
		elif test "$VAR" = "/xml/object/field/@defaultvalue"
		then
			DEFAULT="$VAL"
		elif test "$VAR" = "/xml/object/field/@limits"
		then
			LIMIT="$VAL"
	#	else
	#		echo "### $LINE ###"
		fi
	done
done
echo "	fprintf(fr, \"  </$OBJ_NAME>\\n\");"
echo "}"
echo ""
fi



if test "$MODE" = "8"
then
echo ""
echo "static void model_parseOpenPilot_$OBJ_NAME (xmlDocPtr doc, xmlNodePtr cur, ${OBJ_NAME}Data *data) {"
echo "	xmlChar *key;"
echo "	cur = cur->xmlChildrenNode;"
echo "	while (cur != NULL) {"
echo "		if (1 == 2) {"
for GET_TYPE in float 32 16 8 enum
do
	(xml2 < $XMLFILE ; echo /xml/object/field) | while read LINE
	do
		VAR="`echo $LINE | cut -d"=" -f1`"
		VAL="`echo $LINE | cut -d"=" -f2-`"
		if test "$LINE" = "/xml/object/field"
		then
			if echo "$TYPE" | grep -s -q "$GET_TYPE"
			then
				RTYPE="$TYPE"
				if test "$TYPE" = "enum"
				then
					TYPE="i"
				elif test "$TYPE" != "float"
				then
					TYPE="i"
				else
					TYPE="f"
				fi
				if test "$ELEMENTNAMES" != ""
				then
					NUM_ELEMENTNAMES="`echo $ELEMENTNAMES | tr "," " " | wc -w`"
					NUM_ELEMENTNAMES="`expr $NUM_ELEMENTNAMES - 1`"
					for NUM in `seq 0 $NUM_ELEMENTNAMES`
					do
						NUM2="`expr $NUM + 1`"
						ENAME="`echo $ELEMENTNAMES | tr "," " " | cut -d" " -f$NUM2`"
						echo "		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)\"${NAME}_$ENAME\"))) {"
						echo "			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);"
						echo "			if ((char *)key != NULL) {"
						echo "				data->$NAME[$NUM] = ato$TYPE((char *)key);"
						echo "			}"
						echo "			xmlFree(key);"
					done
				else
					echo "		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)\"$NAME\"))) {"
					echo "			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);"
					echo "			if ((char *)key != NULL) {"
					echo "				data->$NAME = ato$TYPE((char *)key);"
					echo "			}"
					echo "			xmlFree(key);"
				fi
			fi
			NAME=""
			UNITS=""
			TYPE=""
			ELEMENTS=""
			ELEMENTNAMES=""
			OPTIONS=""
			DEFAULT=""
			LIMIT=""
		elif test "$VAR" = "/xml/object/field/@name"
		then
			NAME="$VAL"
		elif test "$VAR" = "/xml/object/field/@units"
		then
			UNITS="$VAL"
		elif test "$VAR" = "/xml/object/field/@type"
		then
			TYPE="$VAL"
		elif test "$VAR" = "/xml/object/field/@elements"
		then
			ELEMENTS="$VAL"
		elif test "$VAR" = "/xml/object/field/@elementnames"
		then
			ELEMENTNAMES="$VAL"
		elif test "$VAR" = "/xml/object/field/@options"
		then
			OPTIONS="$VAL"
		elif test "$VAR" = "/xml/object/field/@defaultvalue"
		then
			DEFAULT="$VAL"
		elif test "$VAR" = "/xml/object/field/@limits"
		then
			LIMIT="$VAL"
	#	else
	#		echo "### $LINE ###"
		fi
	done
done
echo "		}"
echo "		cur = cur->next;"
echo "	}"
echo "	return;"
echo "}"
echo ""
fi


if test "$MODE" = "9"
then
echo ""
for XML in $GUIXML
do
	$0 /usr/src/OpenPilot/shared/uavobjectdefinition/$XML 7
done
echo ""
echo "static void model_save_xml_OpenPilot (FILE *fr) {"
echo "	fprintf(fr, \" <OpenPilot>\\n\");"
for XML in $GUIXML
do
	OBJ_NAME2="`xml2 < /usr/src/OpenPilot/shared/uavobjectdefinition/$XML | grep "^/xml/object/@name=" | cut -d"=" -f2-`"
	echo "	openpilot_save_xml_$OBJ_NAME2(fr, &Openpilot$OBJ_NAME2);"
done
echo "	fprintf(fr, \" </OpenPilot>\\n\");"
echo "	return;"
echo "}"
echo ""
echo ""
for XML in $GUIXML
do
	$0 /usr/src/OpenPilot/shared/uavobjectdefinition/$XML 8
done
echo ""
echo "static void model_parseOpenPilot (xmlDocPtr doc, xmlNodePtr cur) {"
echo "	cur = cur->xmlChildrenNode;"
for XML in $GUIXML
do
	OBJ_NAME2="`xml2 < /usr/src/OpenPilot/shared/uavobjectdefinition/$XML | grep "^/xml/object/@name=" | cut -d"=" -f2-`"
	echo "	openpilot_defaults_$OBJ_NAME2(&Openpilot$OBJ_NAME2);"
done
echo "	while (cur != NULL) {"
echo "		if (1 == 2) {"
for XML in $GUIXML
do
	OBJ_NAME2="`xml2 < /usr/src/OpenPilot/shared/uavobjectdefinition/$XML | grep "^/xml/object/@name=" | cut -d"=" -f2-`"
	OBJ_DESC2="`xml2 < /usr/src/OpenPilot/shared/uavobjectdefinition/$XML | grep "^/xml/object/description=" | cut -d"=" -f2-`"
	echo "		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)\"$OBJ_NAME2\"))) {"
	echo "			model_parseOpenPilot_$OBJ_NAME2(doc, cur, &Openpilot$OBJ_NAME2);"
done
echo "		}"
echo "		cur = cur->next;"
echo "	}"
echo "	return;"
echo "}"
echo ""
fi

