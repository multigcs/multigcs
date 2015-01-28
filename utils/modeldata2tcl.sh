#!/bin/sh
#
#
#


echo "
static int ModelData_Cmd (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	Tcl_Obj *res;
	char tmp_str[1024];
	char data[10000];
	data[0] = 0;
" > tcl/tcl_ModelData\[ModelActive\].h

echo "

void tcl_update_modeldata (void) {

" > tcl/tcl_modeldatavar.h

echo "
	char name[200];
	char sysstr[200];
	char image[512];
	uint8_t modeltype;
	uint8_t teletype;
	uint8_t dronetype;
	uint8_t pilottype;
	char telebtaddr[200];
	char telebtpin[200];
	uint8_t mode;
	uint8_t status;
	uint8_t armed;
	uint8_t heartbeat;
	uint8_t heartbeat_rc;
	uint8_t found_rc;
	float p_lat;
	float p_long;
	float p_alt;
	float alt_offset;
	float baro;
	float pitch;
	float roll;
	float yaw;
	float speed;
	float voltage;
	float load;
	int8_t gpsfix;
	int8_t numSat;
	float_t hdop;
	float_t vdop;
	int16_t radio[16];
	int16_t radio_raw[8];
	float acc_x;
	float acc_y;
	float acc_z;
	float gyro_x;
	float gyro_y;
	float gyro_z;
	float mnt_pitch;
	float mnt_roll;
	float mnt_yaw;
	uint8_t rssi_rx;
	uint8_t rssi_tx;
	uint8_t rssi_rc_rx;
	uint8_t rssi_rc_tx;
	float voltage_rx;
	float voltage_zell[6];
	int16_t temperature[2];
	float ampere;
	float fc_voltage1;
	float fc_voltage2;
	uint8_t fc_i2c_errors;
	uint16_t fc_status;
	uint8_t chancount;
	uint8_t sysid;
	uint8_t compid;
	uint32_t mavlink_update;
	char telemetry_port[1024];
	uint32_t telemetry_baud;
	int serial_fd;
" | tr -d ";" | grep ".." | while read LINE
do
	TYPE="`echo $LINE | awk '{print $1}'`"
	NAME="`echo $LINE | awk '{print $2}' | cut -d"[" -f1`"
	ARRAY="`echo $LINE | grep "\[.*\]" | cut -d"[" -f2 | cut -d"]" -f1`"
	if test "$TYPE" = "float"
	then
		T="%f"
		T2="Float"
	elif echo "$TYPE" | grep -s -q "int"
	then
		T="%i"
		T2="Int"
	elif echo "$TYPE" | grep -s -q "char"
	then
		T="%s"
		T2="String"
		echo "	sprintf(tmp_str, \"{{$NAME} {$T}} \", ModelData\[ModelActive\].$NAME); strcat(data, tmp_str);" >> tcl/tcl_ModelData\[ModelActive\].h
#		echo "	sprintf(tmp_str, \"set ModelData($NAME) \\\"$T\\\"\", ModelData\[ModelActive\].$NAME); Tcl_Eval(tcl_interp, tmp_str);" >> tcl/tcl_modeldatavar.h
		echo "	TclUpdateVar$T2(\"ModelData($NAME)\", ModelData\[ModelActive\].$NAME);" >> tcl/tcl_modeldatavar.h
		continue
	else
		echo "ERROR: $TYPE ($NAME)"
		continue
	fi
	if test "$ARRAY" != ""
	then
		ARRAY="`expr $ARRAY - 1`"
		for N in `seq 0 $ARRAY`
		do
			echo "	sprintf(tmp_str, \"{{$NAME($N)} {$T}} \", ModelData\[ModelActive\].$NAME[$N]); strcat(data, tmp_str);" >> tcl/tcl_ModelData\[ModelActive\].h
#			echo "	sprintf(tmp_str, \"set ModelData($NAME,$N) \\\"$T\\\"\", ModelData\[ModelActive\].$NAME[$N]); Tcl_Eval(tcl_interp, tmp_str);" >> tcl/tcl_modeldatavar.h
			echo "	TclUpdateVar$T2(\"ModelData($NAME,$N)\", ModelData\[ModelActive\].$NAME[$N]);" >> tcl/tcl_modeldatavar.h
		done
	else
		echo "	sprintf(tmp_str, \"{{$NAME} {$T}} \", ModelData\[ModelActive\].$NAME); strcat(data, tmp_str);" >> tcl/tcl_ModelData\[ModelActive\].h
#		echo "	sprintf(tmp_str, \"set ModelData($NAME) \\\"$T\\\"\", ModelData\[ModelActive\].$NAME); Tcl_Eval(tcl_interp, tmp_str);" >> tcl/tcl_modeldatavar.h
		echo "	TclUpdateVar$T2(\"ModelData($NAME)\", ModelData\[ModelActive\].$NAME);" >> tcl/tcl_modeldatavar.h
	fi
done


echo "
	res = Tcl_NewStringObj(data, -1);
	Tcl_SetObjResult (interp, res);
	return TCL_OK;
}

" >> tcl/tcl_ModelData\[ModelActive\].h

echo "
}

" >> tcl/tcl_modeldatavar.h




