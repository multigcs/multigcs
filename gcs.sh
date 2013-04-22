#!/bin/sh
#
#


test -e /usr/share/gl-gcs/setup.cfg || echo "touchscreen_device" > /usr/share/gl-gcs/setup.cfg


if uname -a | grep -s -q raspberrypi
then
	killall -9 thd
	killall -9 rsyslogd
	killall -9 cron
	killall -9 ifplugd
	killall -9 ntpd
	killall -9 dbus-daemon

	TOUCH_DEV="`lsinput | grep TouchController -B 5 | grep "^/dev/input" | tail -n1`"
	if test "$TOUCH_DEV" != ""
	then
		unset DISPLAY
		export SDL_MOUSEDEV="/dev/input/event999"
		export SDL_NOMOUSE=1
		if grep -s -q "touchscreen_device" /usr/share/gl-gcs/setup.cfg
		then
			sed -i "s|touchscreen_device.*|touchscreen_device $TOUCH_DEV|g" /usr/share/gl-gcs/setup.cfg
		else
			sed -i "s|tile_y.*|touchscreen_device $TOUCH_DEV|g" /usr/share/gl-gcs/setup.cfg
		fi
	else
		sed -i "s|touchscreen_device.*||g" /usr/share/gl-gcs/setup.cfg
	fi

fi


rm -rf /tmp/gcs.playfile
rm -rf /tmp/gcs.execute
touch /tmp/gcs.run

while test -e /tmp/gcs.run
do
	gl-gcs
	if test -e /tmp/gcs.playfile
	then
		if test -x /usr/bin/omxplayer
		then
			omxplayer "`cat /tmp/gcs.playfile`"
		else
			mplayer "`cat /tmp/gcs.playfile`"
		fi
		rm -rf /tmp/gcs.playfile
		touch /tmp/gcs.run
	elif test -e /tmp/gcs.execute
	then
		sh /tmp/gcs.execute
		rm -rf /tmp/gcs.execute
		touch /tmp/gcs.run
	fi
done



