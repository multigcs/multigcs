#!/bin/sh
#
#

if ! test -e APM_SITL/ardupilot
then
	mkdir -p APM_SITL
	cd APM_SITL
	git clone https://github.com/diydrones/ardupilot.git

	cd ardupilot/ArduCopter
	make configure
	make sitl
fi




