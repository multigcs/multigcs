

void tcl_update_modeldata (void) {


	TclUpdateVarString("ModelData(name)", ModelData.name);
	TclUpdateVarString("ModelData(image)", ModelData.image);
	TclUpdateVarInt("ModelData(modeltype)", ModelData.modeltype);
	TclUpdateVarInt("ModelData(teletype)", ModelData.teletype);
	TclUpdateVarString("ModelData(teledevice)", ModelData.teledevice);
	TclUpdateVarInt("ModelData(telebaud)", ModelData.telebaud);
	TclUpdateVarString("ModelData(telebtaddr)", ModelData.telebtaddr);
	TclUpdateVarString("ModelData(telebtpin)", ModelData.telebtpin);
	TclUpdateVarInt("ModelData(mode)", ModelData.mode);
	TclUpdateVarInt("ModelData(status)", ModelData.status);
	TclUpdateVarInt("ModelData(armed)", ModelData.armed);
	TclUpdateVarInt("ModelData(heartbeat)", ModelData.heartbeat);
	TclUpdateVarInt("ModelData(heartbeat_rc)", ModelData.heartbeat_rc);
	TclUpdateVarInt("ModelData(found_rc)", ModelData.found_rc);
	TclUpdateVarFloat("ModelData(p_lat)", ModelData.p_lat);
	TclUpdateVarFloat("ModelData(p_long)", ModelData.p_long);
	TclUpdateVarFloat("ModelData(p_alt)", ModelData.p_alt);
	TclUpdateVarFloat("ModelData(alt_offset)", ModelData.alt_offset);
	TclUpdateVarFloat("ModelData(baro)", ModelData.baro);
	TclUpdateVarFloat("ModelData(pitch)", ModelData.pitch);
	TclUpdateVarFloat("ModelData(roll)", ModelData.roll);
	TclUpdateVarFloat("ModelData(yaw)", ModelData.yaw);
	TclUpdateVarFloat("ModelData(speed)", ModelData.speed);
	TclUpdateVarFloat("ModelData(voltage)", ModelData.voltage);
	TclUpdateVarFloat("ModelData(load)", ModelData.load);
	TclUpdateVarInt("ModelData(gpsfix)", ModelData.gpsfix);
	TclUpdateVarInt("ModelData(numSat)", ModelData.numSat);
	TclUpdateVarInt("ModelData(radio,0)", ModelData.radio[0]);
	TclUpdateVarInt("ModelData(radio,1)", ModelData.radio[1]);
	TclUpdateVarInt("ModelData(radio,2)", ModelData.radio[2]);
	TclUpdateVarInt("ModelData(radio,3)", ModelData.radio[3]);
	TclUpdateVarInt("ModelData(radio,4)", ModelData.radio[4]);
	TclUpdateVarInt("ModelData(radio,5)", ModelData.radio[5]);
	TclUpdateVarInt("ModelData(radio,6)", ModelData.radio[6]);
	TclUpdateVarInt("ModelData(radio,7)", ModelData.radio[7]);
	TclUpdateVarInt("ModelData(radio,8)", ModelData.radio[8]);
	TclUpdateVarInt("ModelData(radio,9)", ModelData.radio[9]);
	TclUpdateVarInt("ModelData(radio,10)", ModelData.radio[10]);
	TclUpdateVarInt("ModelData(radio,11)", ModelData.radio[11]);
	TclUpdateVarInt("ModelData(radio,12)", ModelData.radio[12]);
	TclUpdateVarInt("ModelData(radio,13)", ModelData.radio[13]);
	TclUpdateVarInt("ModelData(radio,14)", ModelData.radio[14]);
	TclUpdateVarInt("ModelData(radio,15)", ModelData.radio[15]);
	TclUpdateVarFloat("ModelData(acc_x)", ModelData.acc_x);
	TclUpdateVarFloat("ModelData(acc_y)", ModelData.acc_y);
	TclUpdateVarFloat("ModelData(acc_z)", ModelData.acc_z);
	TclUpdateVarFloat("ModelData(gyro_x)", ModelData.gyro_x);
	TclUpdateVarFloat("ModelData(gyro_y)", ModelData.gyro_y);
	TclUpdateVarFloat("ModelData(gyro_z)", ModelData.gyro_z);
	TclUpdateVarInt("ModelData(rssi_rx)", ModelData.rssi_rx);
	TclUpdateVarInt("ModelData(rssi_tx)", ModelData.rssi_tx);
	TclUpdateVarFloat("ModelData(voltage_rx)", ModelData.voltage_rx);
	TclUpdateVarFloat("ModelData(voltage_zell,0)", ModelData.voltage_zell[0]);
	TclUpdateVarFloat("ModelData(voltage_zell,1)", ModelData.voltage_zell[1]);
	TclUpdateVarFloat("ModelData(voltage_zell,2)", ModelData.voltage_zell[2]);
	TclUpdateVarFloat("ModelData(voltage_zell,3)", ModelData.voltage_zell[3]);
	TclUpdateVarFloat("ModelData(voltage_zell,4)", ModelData.voltage_zell[4]);
	TclUpdateVarFloat("ModelData(voltage_zell,5)", ModelData.voltage_zell[5]);
	TclUpdateVarInt("ModelData(temperature,0)", ModelData.temperature[0]);
	TclUpdateVarInt("ModelData(temperature,1)", ModelData.temperature[1]);
	TclUpdateVarFloat("ModelData(ampere)", ModelData.ampere);

}


