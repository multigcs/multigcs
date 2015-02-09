#!/bin/sh
#
#

if test "$1" = "-m"
then
	echo "## starting multiple SITL's in xterm's with docker ##"
	xterm -geometry 80x25+0+0 -e docker run -h copter1 -p 0.0.0.0:50001:5760 -p 0.0.0.0:51001:5501/udp --rm=true -i -t ardupilot-sitl-copter /bin/bash /usr/src/run_sitl-copter.sh &
	xterm -geometry 80x25+0+350 -e docker run -h copter2 -p 0.0.0.0:50002:5760 -p 0.0.0.0:51002:5501/udp --rm=true -i -t ardupilot-sitl-copter /bin/bash /usr/src/run_sitl-copter.sh &
	xterm -geometry 80x25+0+700 -e docker run -h copter3 -p 0.0.0.0:50003:5760 -p 0.0.0.0:51003:5501/udp --rm=true -i -t ardupilot-sitl-copter /bin/bash /usr/src/run_sitl-copter.sh &
else
	echo "## starting SITL in xterm's ##"
	xterm -geometry 80x25+0+0 -e ./APM_SITL/ardupilot/ArduCopter/ArduCopter.elf &
	xterm -geometry 80x25+0+350 -e ./APM_SITL/ardupilot/Tools/autotest/pysim/sim_multicopter.py --rate=400 --home 50.29395294,9.12301350,150,0 --wind=0,0,0 --frame X &
	xterm -geometry 80x25+0+700 -e ./mavlink/sitl-transmitter/joystick &
fi


