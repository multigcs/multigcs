#!/bin/sh
#
#

XML_FILES="/usr/src/CleanFlight/OpenPilot/shared/uavobjectdefinition"

gcc -o openpilot/generate_objid openpilot/generate_objid.c -I/usr/include/libxml2 -lxml2 || exit 1

rm -rf openpilot/uavobjects.h
rm -rf openpilot/uavobjects_encode.c
rm -rf openpilot/uavobjects_decode.c
rm -rf openpilot/uavobjects_store.c


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

rm -rf openpilot/uavobject_examplessend.h
rm -rf openpilot/uavobject_examples.h
rm -rf openpilot/uavobject_save.h
rm -rf openpilot/uavobject_comment.h
rm -rf openpilot/uavobject_defs.h
rm -rf openpilot/uavobject_ids.h
rm -rf openpilot/uavobject_otypes.h
rm -rf openpilot/uavobject_options.h
rm -rf openpilot/uavobject_struct.h

#cat openpilot/uavobjects.h

