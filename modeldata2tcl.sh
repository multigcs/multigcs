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
" > tcl_modeldata.c

echo "

void tcl_update_modeldata (void) {
	char tmp_str[1024];

" > tcl_modeldatavar.c

echo "
	char name[200];
	char image[200];
	uint8_t modeltype;
	uint8_t teletype;
	char teledevice[20];
	uint32_t telebaud;
	char telebtaddr[20];
	char telebtpin[20];
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
	int16_t radio[16];
	float acc_x;
	float acc_y;
	float acc_z;
	float gyro_x;
	float gyro_y;
	float gyro_z;
	uint8_t rssi_rx;
	uint8_t rssi_tx;
	float voltage_rx;
	float voltage_zell[6];
	int16_t temperature[2];
	float ampere;
" | tr -d ";" | grep ".." | while read LINE
do
	TYPE="`echo $LINE | awk '{print $1}'`"
	NAME="`echo $LINE | awk '{print $2}' | cut -d"[" -f1`"
	ARRAY="`echo $LINE | grep "\[.*\]" | cut -d"[" -f2 | cut -d"]" -f1`"
	if test "$TYPE" = "float"
	then
		T="%f"
	elif echo "$TYPE" | grep -s -q "int"
	then
		T="%i"
	elif echo "$TYPE" | grep -s -q "char"
	then
		T="%s"
		echo "	sprintf(tmp_str, \"{{$NAME} {$T}} \", ModelData.$NAME); strcat(data, tmp_str);" >> tcl_modeldata.c
		echo "	sprintf(tmp_str, \"set ModelData($NAME) \\\"$T\\\"\", ModelData.$NAME); Tcl_Eval(tcl_interp, tmp_str);" >> tcl_modeldatavar.c
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
			echo "	sprintf(tmp_str, \"{{$NAME($N)} {$T}} \", ModelData.$NAME[$N]); strcat(data, tmp_str);" >> tcl_modeldata.c
			echo "	sprintf(tmp_str, \"set ModelData($NAME,$N) \\\"$T\\\"\", ModelData.$NAME[$N]); Tcl_Eval(tcl_interp, tmp_str);" >> tcl_modeldatavar.c
		done
	else
		echo "	sprintf(tmp_str, \"{{$NAME} {$T}} \", ModelData.$NAME); strcat(data, tmp_str);" >> tcl_modeldata.c
		echo "	sprintf(tmp_str, \"set ModelData($NAME) \\\"$T\\\"\", ModelData.$NAME); Tcl_Eval(tcl_interp, tmp_str);" >> tcl_modeldatavar.c
	fi
done


echo "
	res = Tcl_NewStringObj(data, -1);
	Tcl_SetObjResult (interp, res);
	return TCL_OK;
}

" >> tcl_modeldata.c

echo "
}

" >> tcl_modeldatavar.c




