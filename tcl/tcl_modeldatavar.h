

void tcl_update_modeldata (void) {


	TclUpdateVarString("ModelData(name)", ModelData[ModelActive].name);
	TclUpdateVarString("ModelData(sysstr)", ModelData[ModelActive].sysstr);
	TclUpdateVarString("ModelData(image)", ModelData[ModelActive].image);
	TclUpdateVarInt("ModelData(dronetype)", ModelData[ModelActive].dronetype);
	TclUpdateVarInt("ModelData(teletype)", ModelData[ModelActive].teletype);
	TclUpdateVarInt("ModelData(dronetype)", ModelData[ModelActive].dronetype);
	TclUpdateVarInt("ModelData(pilottype)", ModelData[ModelActive].pilottype);
	TclUpdateVarString("ModelData(telebtaddr)", ModelData[ModelActive].telebtaddr);
	TclUpdateVarString("ModelData(telebtpin)", ModelData[ModelActive].telebtpin);
	TclUpdateVarInt("ModelData(mode)", ModelData[ModelActive].mode);
	TclUpdateVarInt("ModelData(status)", ModelData[ModelActive].status);
	TclUpdateVarInt("ModelData(armed)", ModelData[ModelActive].armed);
	TclUpdateVarInt("ModelData(heartbeat)", ModelData[ModelActive].heartbeat);
	TclUpdateVarInt("ModelData(heartbeat_rc)", ModelData[ModelActive].heartbeat_rc);
	TclUpdateVarInt("ModelData(found_rc)", ModelData[ModelActive].found_rc);
	TclUpdateVarFloat("ModelData(p_lat)", ModelData[ModelActive].p_lat);
	TclUpdateVarFloat("ModelData(p_long)", ModelData[ModelActive].p_long);
	TclUpdateVarFloat("ModelData(p_alt)", ModelData[ModelActive].p_alt);
	TclUpdateVarFloat("ModelData(alt_offset)", ModelData[ModelActive].alt_offset);
	TclUpdateVarFloat("ModelData(baro)", ModelData[ModelActive].baro);
	TclUpdateVarFloat("ModelData(pitch)", ModelData[ModelActive].pitch);
	TclUpdateVarFloat("ModelData(roll)", ModelData[ModelActive].roll);
	TclUpdateVarFloat("ModelData(yaw)", ModelData[ModelActive].yaw);
	TclUpdateVarFloat("ModelData(speed)", ModelData[ModelActive].speed);
	TclUpdateVarFloat("ModelData(voltage)", ModelData[ModelActive].voltage);
	TclUpdateVarFloat("ModelData(load)", ModelData[ModelActive].load);
	TclUpdateVarInt("ModelData(gpsfix)", ModelData[ModelActive].gpsfix);
	TclUpdateVarInt("ModelData(numSat)", ModelData[ModelActive].numSat);
	TclUpdateVarInt("ModelData(radio,0)", ModelData[ModelActive].radio[0]);
	TclUpdateVarInt("ModelData(radio,1)", ModelData[ModelActive].radio[1]);
	TclUpdateVarInt("ModelData(radio,2)", ModelData[ModelActive].radio[2]);
	TclUpdateVarInt("ModelData(radio,3)", ModelData[ModelActive].radio[3]);
	TclUpdateVarInt("ModelData(radio,4)", ModelData[ModelActive].radio[4]);
	TclUpdateVarInt("ModelData(radio,5)", ModelData[ModelActive].radio[5]);
	TclUpdateVarInt("ModelData(radio,6)", ModelData[ModelActive].radio[6]);
	TclUpdateVarInt("ModelData(radio,7)", ModelData[ModelActive].radio[7]);
	TclUpdateVarInt("ModelData(radio,8)", ModelData[ModelActive].radio[8]);
	TclUpdateVarInt("ModelData(radio,9)", ModelData[ModelActive].radio[9]);
	TclUpdateVarInt("ModelData(radio,10)", ModelData[ModelActive].radio[10]);
	TclUpdateVarInt("ModelData(radio,11)", ModelData[ModelActive].radio[11]);
	TclUpdateVarInt("ModelData(radio,12)", ModelData[ModelActive].radio[12]);
	TclUpdateVarInt("ModelData(radio,13)", ModelData[ModelActive].radio[13]);
	TclUpdateVarInt("ModelData(radio,14)", ModelData[ModelActive].radio[14]);
	TclUpdateVarInt("ModelData(radio,15)", ModelData[ModelActive].radio[15]);
	TclUpdateVarInt("ModelData(radio_raw,0)", ModelData[ModelActive].radio_raw[0]);
	TclUpdateVarInt("ModelData(radio_raw,1)", ModelData[ModelActive].radio_raw[1]);
	TclUpdateVarInt("ModelData(radio_raw,2)", ModelData[ModelActive].radio_raw[2]);
	TclUpdateVarInt("ModelData(radio_raw,3)", ModelData[ModelActive].radio_raw[3]);
	TclUpdateVarInt("ModelData(radio_raw,4)", ModelData[ModelActive].radio_raw[4]);
	TclUpdateVarInt("ModelData(radio_raw,5)", ModelData[ModelActive].radio_raw[5]);
	TclUpdateVarInt("ModelData(radio_raw,6)", ModelData[ModelActive].radio_raw[6]);
	TclUpdateVarInt("ModelData(radio_raw,7)", ModelData[ModelActive].radio_raw[7]);
	TclUpdateVarFloat("ModelData(acc_x)", ModelData[ModelActive].acc_x);
	TclUpdateVarFloat("ModelData(acc_y)", ModelData[ModelActive].acc_y);
	TclUpdateVarFloat("ModelData(acc_z)", ModelData[ModelActive].acc_z);
	TclUpdateVarFloat("ModelData(gyro_x)", ModelData[ModelActive].gyro_x);
	TclUpdateVarFloat("ModelData(gyro_y)", ModelData[ModelActive].gyro_y);
	TclUpdateVarFloat("ModelData(gyro_z)", ModelData[ModelActive].gyro_z);
	TclUpdateVarFloat("ModelData(mnt_pitch)", ModelData[ModelActive].mnt_pitch);
	TclUpdateVarFloat("ModelData(mnt_roll)", ModelData[ModelActive].mnt_roll);
	TclUpdateVarFloat("ModelData(mnt_yaw)", ModelData[ModelActive].mnt_yaw);
	TclUpdateVarInt("ModelData(rssi_rx)", ModelData[ModelActive].rssi_rx);
	TclUpdateVarInt("ModelData(rssi_tx)", ModelData[ModelActive].rssi_tx);
	TclUpdateVarInt("ModelData(rssi_rc_rx)", ModelData[ModelActive].rssi_rc_rx);
	TclUpdateVarInt("ModelData(rssi_rc_tx)", ModelData[ModelActive].rssi_rc_tx);
	TclUpdateVarFloat("ModelData(voltage_rx)", ModelData[ModelActive].voltage_rx);
	TclUpdateVarFloat("ModelData(voltage_zell,0)", ModelData[ModelActive].voltage_zell[0]);
	TclUpdateVarFloat("ModelData(voltage_zell,1)", ModelData[ModelActive].voltage_zell[1]);
	TclUpdateVarFloat("ModelData(voltage_zell,2)", ModelData[ModelActive].voltage_zell[2]);
	TclUpdateVarFloat("ModelData(voltage_zell,3)", ModelData[ModelActive].voltage_zell[3]);
	TclUpdateVarFloat("ModelData(voltage_zell,4)", ModelData[ModelActive].voltage_zell[4]);
	TclUpdateVarFloat("ModelData(voltage_zell,5)", ModelData[ModelActive].voltage_zell[5]);
	TclUpdateVarInt("ModelData(temperature,0)", ModelData[ModelActive].temperature[0]);
	TclUpdateVarInt("ModelData(temperature,1)", ModelData[ModelActive].temperature[1]);
	TclUpdateVarFloat("ModelData(ampere)", ModelData[ModelActive].ampere);
	TclUpdateVarFloat("ModelData(fc_voltage1)", ModelData[ModelActive].fc_voltage1);
	TclUpdateVarFloat("ModelData(fc_voltage2)", ModelData[ModelActive].fc_voltage2);
	TclUpdateVarInt("ModelData(fc_i2c_errors)", ModelData[ModelActive].fc_i2c_errors);
	TclUpdateVarInt("ModelData(fc_status)", ModelData[ModelActive].fc_status);
	TclUpdateVarInt("ModelData(chancount)", ModelData[ModelActive].chancount);
	TclUpdateVarInt("ModelData(sysid)", ModelData[ModelActive].sysid);
	TclUpdateVarInt("ModelData(compid)", ModelData[ModelActive].compid);
	TclUpdateVarInt("ModelData(mavlink_update)", ModelData[ModelActive].mavlink_update);
	TclUpdateVarString("ModelData(telemetry_port)", ModelData[ModelActive].telemetry_port);
	TclUpdateVarInt("ModelData(telemetry_baud)", ModelData[ModelActive].telemetry_baud);
	TclUpdateVarInt("ModelData(serial_fd)", ModelData[ModelActive].serial_fd);

}


