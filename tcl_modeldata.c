
static int ModelData_Cmd (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	Tcl_Obj *res;
	char tmp_str[1024];
	char data[10000];
	data[0] = 0;

	sprintf(tmp_str, "{{name} {%s}} ", ModelData.name); strcat(data, tmp_str);
	sprintf(tmp_str, "{{image} {%s}} ", ModelData.image); strcat(data, tmp_str);
	sprintf(tmp_str, "{{modeltype} {%i}} ", ModelData.modeltype); strcat(data, tmp_str);
	sprintf(tmp_str, "{{teletype} {%i}} ", ModelData.teletype); strcat(data, tmp_str);
	sprintf(tmp_str, "{{teledevice} {%s}} ", ModelData.teledevice); strcat(data, tmp_str);
	sprintf(tmp_str, "{{telebaud} {%i}} ", ModelData.telebaud); strcat(data, tmp_str);
	sprintf(tmp_str, "{{telebtaddr} {%s}} ", ModelData.telebtaddr); strcat(data, tmp_str);
	sprintf(tmp_str, "{{telebtpin} {%s}} ", ModelData.telebtpin); strcat(data, tmp_str);
	sprintf(tmp_str, "{{mode} {%i}} ", ModelData.mode); strcat(data, tmp_str);
	sprintf(tmp_str, "{{status} {%i}} ", ModelData.status); strcat(data, tmp_str);
	sprintf(tmp_str, "{{armed} {%i}} ", ModelData.armed); strcat(data, tmp_str);
	sprintf(tmp_str, "{{heartbeat} {%i}} ", ModelData.heartbeat); strcat(data, tmp_str);
	sprintf(tmp_str, "{{heartbeat_rc} {%i}} ", ModelData.heartbeat_rc); strcat(data, tmp_str);
	sprintf(tmp_str, "{{found_rc} {%i}} ", ModelData.found_rc); strcat(data, tmp_str);
	sprintf(tmp_str, "{{p_lat} {%f}} ", ModelData.p_lat); strcat(data, tmp_str);
	sprintf(tmp_str, "{{p_long} {%f}} ", ModelData.p_long); strcat(data, tmp_str);
	sprintf(tmp_str, "{{p_alt} {%f}} ", ModelData.p_alt); strcat(data, tmp_str);
	sprintf(tmp_str, "{{alt_offset} {%f}} ", ModelData.alt_offset); strcat(data, tmp_str);
	sprintf(tmp_str, "{{baro} {%f}} ", ModelData.baro); strcat(data, tmp_str);
	sprintf(tmp_str, "{{pitch} {%f}} ", ModelData.pitch); strcat(data, tmp_str);
	sprintf(tmp_str, "{{roll} {%f}} ", ModelData.roll); strcat(data, tmp_str);
	sprintf(tmp_str, "{{yaw} {%f}} ", ModelData.yaw); strcat(data, tmp_str);
	sprintf(tmp_str, "{{speed} {%f}} ", ModelData.speed); strcat(data, tmp_str);
	sprintf(tmp_str, "{{voltage} {%f}} ", ModelData.voltage); strcat(data, tmp_str);
	sprintf(tmp_str, "{{load} {%f}} ", ModelData.load); strcat(data, tmp_str);
	sprintf(tmp_str, "{{gpsfix} {%i}} ", ModelData.gpsfix); strcat(data, tmp_str);
	sprintf(tmp_str, "{{numSat} {%i}} ", ModelData.numSat); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(0)} {%i}} ", ModelData.radio[0]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(1)} {%i}} ", ModelData.radio[1]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(2)} {%i}} ", ModelData.radio[2]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(3)} {%i}} ", ModelData.radio[3]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(4)} {%i}} ", ModelData.radio[4]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(5)} {%i}} ", ModelData.radio[5]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(6)} {%i}} ", ModelData.radio[6]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(7)} {%i}} ", ModelData.radio[7]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(8)} {%i}} ", ModelData.radio[8]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(9)} {%i}} ", ModelData.radio[9]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(10)} {%i}} ", ModelData.radio[10]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(11)} {%i}} ", ModelData.radio[11]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(12)} {%i}} ", ModelData.radio[12]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(13)} {%i}} ", ModelData.radio[13]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(14)} {%i}} ", ModelData.radio[14]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{radio(15)} {%i}} ", ModelData.radio[15]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{acc_x} {%f}} ", ModelData.acc_x); strcat(data, tmp_str);
	sprintf(tmp_str, "{{acc_y} {%f}} ", ModelData.acc_y); strcat(data, tmp_str);
	sprintf(tmp_str, "{{acc_z} {%f}} ", ModelData.acc_z); strcat(data, tmp_str);
	sprintf(tmp_str, "{{gyro_x} {%f}} ", ModelData.gyro_x); strcat(data, tmp_str);
	sprintf(tmp_str, "{{gyro_y} {%f}} ", ModelData.gyro_y); strcat(data, tmp_str);
	sprintf(tmp_str, "{{gyro_z} {%f}} ", ModelData.gyro_z); strcat(data, tmp_str);
	sprintf(tmp_str, "{{rssi_rx} {%i}} ", ModelData.rssi_rx); strcat(data, tmp_str);
	sprintf(tmp_str, "{{rssi_tx} {%i}} ", ModelData.rssi_tx); strcat(data, tmp_str);
	sprintf(tmp_str, "{{voltage_rx} {%f}} ", ModelData.voltage_rx); strcat(data, tmp_str);
	sprintf(tmp_str, "{{voltage_zell(0)} {%f}} ", ModelData.voltage_zell[0]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{voltage_zell(1)} {%f}} ", ModelData.voltage_zell[1]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{voltage_zell(2)} {%f}} ", ModelData.voltage_zell[2]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{voltage_zell(3)} {%f}} ", ModelData.voltage_zell[3]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{voltage_zell(4)} {%f}} ", ModelData.voltage_zell[4]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{voltage_zell(5)} {%f}} ", ModelData.voltage_zell[5]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{temperature(0)} {%i}} ", ModelData.temperature[0]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{temperature(1)} {%i}} ", ModelData.temperature[1]); strcat(data, tmp_str);
	sprintf(tmp_str, "{{ampere} {%f}} ", ModelData.ampere); strcat(data, tmp_str);

	res = Tcl_NewStringObj(data, -1);
	Tcl_SetObjResult (interp, res);
	return TCL_OK;
}


