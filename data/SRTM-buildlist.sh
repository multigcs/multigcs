#!/bin/sh
#
#

BASE_URL="http://dds.cr.usgs.gov/srtm/version2_1/SRTM3"
echo -n > data/SRTM.list
for REGION in Africa Australia Eurasia Islands North_America South_America
do
	wget -O- $BASE_URL/$REGION | grep "\.hgt\.zip" | cut -d"\"" -f2 | sed "s|^|$BASE_URL/$REGION/|g" >> data/SRTM.list
done


