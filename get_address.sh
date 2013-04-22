#!/bin/sh
#
#

ADDRESS="$1"

POSTITION="`wget -q -O - "http://maps.googleapis.com/maps/api/geocode/xml?sensor=true&address=$ADDRESS" | xml2 | grep "^/GeocodeResponse/result/formatted_address=\|^/GeocodeResponse/result/geometry/location/lat=\|^/GeocodeResponse/result/geometry/location/lng=" | sed "s|.*=||g" | tr "\n" ";"`"

echo $POSTITION

