

static void tcl_update_modeldata (Tcl_Interp *tcl_interp) {
	char tmp_str[1024];

	sprintf(tmp_str, "set ModelData(name) \"%s\"", ModelData.name); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(image) \"%s\"", ModelData.image); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(modeltype) \"%i\"", ModelData.modeltype); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(teletype) \"%i\"", ModelData.teletype); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(teledevice) \"%s\"", ModelData.teledevice); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(telebaud) \"%i\"", ModelData.telebaud); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(telebtaddr) \"%s\"", ModelData.telebtaddr); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(telebtpin) \"%s\"", ModelData.telebtpin); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(mode) \"%i\"", ModelData.mode); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(status) \"%i\"", ModelData.status); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(armed) \"%i\"", ModelData.armed); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(heartbeat) \"%i\"", ModelData.heartbeat); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(heartbeat_rc) \"%i\"", ModelData.heartbeat_rc); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(found_rc) \"%i\"", ModelData.found_rc); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(p_lat) \"%f\"", ModelData.p_lat); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(p_long) \"%f\"", ModelData.p_long); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(p_alt) \"%f\"", ModelData.p_alt); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(alt_offset) \"%f\"", ModelData.alt_offset); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(baro) \"%f\"", ModelData.baro); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(pitch) \"%f\"", ModelData.pitch); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(roll) \"%f\"", ModelData.roll); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(yaw) \"%f\"", ModelData.yaw); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(speed) \"%f\"", ModelData.speed); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(voltage) \"%f\"", ModelData.voltage); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(load) \"%f\"", ModelData.load); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(gpsfix) \"%i\"", ModelData.gpsfix); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(numSat) \"%i\"", ModelData.numSat); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,0) \"%i\"", ModelData.radio[0]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,1) \"%i\"", ModelData.radio[1]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,2) \"%i\"", ModelData.radio[2]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,3) \"%i\"", ModelData.radio[3]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,4) \"%i\"", ModelData.radio[4]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,5) \"%i\"", ModelData.radio[5]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,6) \"%i\"", ModelData.radio[6]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,7) \"%i\"", ModelData.radio[7]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,8) \"%i\"", ModelData.radio[8]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,9) \"%i\"", ModelData.radio[9]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,10) \"%i\"", ModelData.radio[10]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,11) \"%i\"", ModelData.radio[11]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,12) \"%i\"", ModelData.radio[12]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,13) \"%i\"", ModelData.radio[13]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,14) \"%i\"", ModelData.radio[14]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(radio,15) \"%i\"", ModelData.radio[15]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(acc_x) \"%f\"", ModelData.acc_x); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(acc_y) \"%f\"", ModelData.acc_y); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(acc_z) \"%f\"", ModelData.acc_z); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(gyro_x) \"%f\"", ModelData.gyro_x); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(gyro_y) \"%f\"", ModelData.gyro_y); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(gyro_z) \"%f\"", ModelData.gyro_z); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(rssi_rx) \"%i\"", ModelData.rssi_rx); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(rssi_tx) \"%i\"", ModelData.rssi_tx); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(voltage_rx) \"%f\"", ModelData.voltage_rx); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(voltage_zell,0) \"%f\"", ModelData.voltage_zell[0]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(voltage_zell,1) \"%f\"", ModelData.voltage_zell[1]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(voltage_zell,2) \"%f\"", ModelData.voltage_zell[2]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(voltage_zell,3) \"%f\"", ModelData.voltage_zell[3]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(voltage_zell,4) \"%f\"", ModelData.voltage_zell[4]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(voltage_zell,5) \"%f\"", ModelData.voltage_zell[5]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(temperature,0) \"%i\"", ModelData.temperature[0]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(temperature,1) \"%i\"", ModelData.temperature[1]); Tcl_Eval(tcl_interp, tmp_str);
	sprintf(tmp_str, "set ModelData(ampere) \"%f\"", ModelData.ampere); Tcl_Eval(tcl_interp, tmp_str);

}


