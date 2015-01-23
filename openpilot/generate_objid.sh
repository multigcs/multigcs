#!/bin/sh
#
#

XML_FILES="/usr/src/CleanFlight/OpenPilot/shared/uavobjectdefinition"

gcc -o openpilot/generate_objid openpilot/generate_objid.c -I/usr/include/libxml2 -lxml2 || exit 1

rm -rf openpilot/uavobjects.h
rm -rf openpilot/uavobjects_samples_send.c
rm -rf openpilot/uavobjects_samples_rec.c


echo "" > openpilot/uavobjects_samples_rec.c
echo "void uavtalk_decode (uint32_t obj_id, uint8_t *buf) {" >> openpilot/uavobjects_samples_rec.c
echo "	switch (obj_id) {" >> openpilot/uavobjects_samples_rec.c

for XML_FILE in `ls $XML_FILES/*.xml | sort`
do
	openpilot/generate_objid $XML_FILE

	echo "" >> openpilot/uavobjects.h
	echo "/*************************************************************************************************" >> openpilot/uavobjects.h
	basename $XML_FILE | sed "s|^| Filename: |g" >> openpilot/uavobjects.h
	cat openpilot/uavobject_comment.h >> openpilot/uavobjects.h
	echo "*************************************************************************************************/" >> openpilot/uavobjects.h
	echo "" >> openpilot/uavobjects.h
	echo "/*" >> openpilot/uavobjects.h
	echo "" >> openpilot/uavobjects.h
	cat openpilot/uavobject_examples.h >> openpilot/uavobjects.h

	cat openpilot/uavobject_examples.h | sed "s|^|		|g" >> openpilot/uavobjects_samples_rec.c

	echo "" >> openpilot/uavobjects.h
	cat openpilot/uavobject_examplessend.h >> openpilot/uavobjects.h
	cat openpilot/uavobject_examplessend.h >> openpilot/uavobjects_samples_send.c
	echo "*/" >> openpilot/uavobjects.h
	echo "" >> openpilot/uavobjects.h
	cat openpilot/uavobject_ids.h >> openpilot/uavobjects.h
	echo "" >> openpilot/uavobjects.h
	cat openpilot/uavobject_defs.h >> openpilot/uavobjects.h
	cat openpilot/uavobject_options.h >> openpilot/uavobjects.h
	cat openpilot/uavobject_otypes.h >> openpilot/uavobjects.h
	cat openpilot/uavobject_struct.h >> openpilot/uavobjects.h
	echo "" >> openpilot/uavobjects.h

done

echo "	}" >> openpilot/uavobjects_samples_rec.c
echo "}" >> openpilot/uavobjects_samples_rec.c
echo "" >> openpilot/uavobjects_samples_rec.c

rm -rf openpilot/uavobject_examplessend.h
rm -rf openpilot/uavobject_examples.h
rm -rf openpilot/uavobject_comment.h
rm -rf openpilot/uavobject_defs.h
rm -rf openpilot/uavobject_ids.h
rm -rf openpilot/uavobject_otypes.h
rm -rf openpilot/uavobject_options.h
rm -rf openpilot/uavobject_struct.h

cat openpilot/uavobjects.h

