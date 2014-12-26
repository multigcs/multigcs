#!/bin/sh
#
#


if echo "$1" | grep -s -q "^[1-9][0-9]*$"
then
	FILE="`grep "\<$1\>" -R  mavlink/GCS_MAVLink/include/mavlink/v1.0/ardupilotmega/*.h mavlink/GCS_MAVLink/include/mavlink/v1.0/common/*.h | grep "define MAVLINK_MSG" | grep -v "_LEN\|_CRC" | cut -d":" -f1 | head -n1`"
else
	FILE="$1"
fi



DEFINE=`grep "^#define MAVLINK_MSG_" $FILE | head -n1 | awk '{print $2}'`
DECODE=`grep "void mavlink_msg_.*_decode" $FILE | cut -d"(" -f1 | cut -d" " -f4`
PTYPE=`grep "packet;" $FILE | head -n1 | awk '{print $1}'`


echo ""
echo "		case $DEFINE: {"
echo "			$PTYPE packet;"
echo "			$DECODE(msg, &packet);"
grep MAVLINK_TYPE_ $FILE | cut -d"," -f1,3 | while read LINE
do

	OPTION="`echo $LINE | cut -d'\"' -f2`"
	TYPE="`echo $LINE | sed "s|.*MAVLINK_TYPE_||g"`"
	FTYPE="%i"

	if test "$TYPE" =  "FLOAT"
	then
		FTYPE="%f"
	elif echo "$TYPE" | grep -s -q "INT.*_T"
	then
		FTYPE="%i"
	else
		echo "## UNKNOWN_TYPE: $TYPE ##"
	fi

	echo "			SDL_Log(\"mavlink: ## $DEFINE $OPTION $FTYPE ##\\\n\", packet.$OPTION); //$TYPE"

done
echo "			break;"
echo "		}"
echo ""

