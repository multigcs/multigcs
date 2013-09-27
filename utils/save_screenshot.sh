#!/bin/sh
#
#



DUMP="$1"
NAME="$2"

mkdir -p screenshots_new

if test "$NAME" = "dump"
then
	convert $DUMP /tmp/dump.png
else
	NUM=`ls screenshots_new/$NAME[0-9].png | sed "s|.*$NAME||g" | sed "s|\.png||g" | tail -n1 | xargs -r -l expr 1 +`
	test "$NUM" = "" && NUM="1"
	convert $DUMP screenshots_new/$NAME$NUM.png
fi



