#!/bin/sh
#
#



identify /usr/share/gl-gcs/MAPS/*.png /usr/share/gl-gcs/MAPS/*.jpg 2>/dev/null | grep 100x100 | cut -d"[" -f1 | while read FILE
do
	if test -e "$FILE"
	then
		echo $FILE
		rm "$FILE"
	fi
done

identify /usr/share/gl-gcs/MAPS/*.png /usr/share/gl-gcs/MAPS/*.jpg 2>&1 | grep "improper image header\|Empty input file" | cut -d"\`" -f2 | cut -d\' -f1 | while read FILE
do
	if test -e "$FILE"
	then
		echo $FILE
		rm "$FILE"
	fi
done
