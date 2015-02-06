#!/bin/sh
#
#


echo "## starting SITL in xterm's ##"
#xterm -e ./APM_SITL/ardupilot/ArduCopter/ArduCopter.elf &
#xterm -e ./APM_SITL/ardupilot/Tools/autotest/pysim/sim_multicopter.py --home 50.29395294,9.12301350,150,0 --wind=0,0,0 --frame X &
#xterm -e ./mavlink/sitl-transmitter/joystick &


xterm -e docker run -h copter1 -p 0.0.0.0:50001:5760 --rm=true -i -t ardupilot-sitl-copter /bin/bash /usr/src/run_sitl-copter.sh &
xterm -e docker run -h copter2 -p 0.0.0.0:50002:5760 --rm=true -i -t ardupilot-sitl-copter /bin/bash /usr/src/run_sitl-copter.sh &
xterm -e docker run -h copter3 -p 0.0.0.0:50003:5760 --rm=true -i -t ardupilot-sitl-copter /bin/bash /usr/src/run_sitl-copter.sh &


