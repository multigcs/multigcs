#!/usr/bin/tclsh
#
#


set fp [open "[lindex $argv 0]" r]
set file_data [read $fp]
close $fp

set TSTAMP 0
set data [split $file_data "\n"]
foreach line $data {
	set data [split $line ","]
	if {[string match "ATT,*" $line]} {
		set PITCH [string trim [lindex $data 1]]
		set ROLL [string trim [lindex $data 2]]
		set YAW [string trim [lindex $data 3]]
		if {$TSTAMP != 0} {
			puts "ATT;[expr $TSTAMP / 1000.0];$PITCH;$ROLL;$YAW"
		}
	} elseif {[string match "GPS,*" $line]} {
		set FIX [string trim [lindex $data 1]]
		set TSTAMP [string trim [lindex $data 2]]
		set NUMSAT [string trim [lindex $data 4]]
		set LAT [string trim [lindex $data 5]]
		set LONG [string trim [lindex $data 6]]
		set ALT [string trim [lindex $data 8]]
		set SPEED [string trim [lindex $data 9]]
		if {$LONG != 0 && $LAT != 0} {
			puts "GPS;[expr $TSTAMP / 1000.0];$LAT;$LONG;$ALT;$SPEED;$FIX;$NUMSAT"
		}
	}
}





