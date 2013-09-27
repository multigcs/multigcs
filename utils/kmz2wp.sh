#!/bin/sh
#
#


NAME="WP"
for LINE in `zcat $1 | xml2 | grep "/Placemark/" | sed "s| |#|g"`
do
	if echo "$LINE" | grep -s -q "/Placemark/name="
	then
		NAME="`echo $LINE | cut -d"=" -f2-`"
	elif echo "$LINE" | grep -s -q "/Placemark/Point/coordinates="
	then
		CORDS="`echo $LINE | cut -d"=" -f2-`"
		LONG="`echo $CORDS | cut -d"," -f1`"
		LAT="`echo $CORDS | cut -d"," -f2`"
		ALT="`echo $CORDS | cut -d"," -f3`"

		echo "name       $NAME"
		echo "command    WAYPOINT"
		echo "lat        $LAT"
		echo "lon        $LONG"
		echo "alt        $ALT"
		echo "yaw        0.000000"
		echo "wait       500.000000"
		echo "radius     2.000000"
		echo "orbit      0.000000"
		echo "type       0"
		echo ""

	fi
done
