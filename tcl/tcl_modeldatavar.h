

void tcl_update_modeldata (void) {


	TclUpdateVarString("ModelData[ModelActive](name)", ModelData[ModelActive].name);
	TclUpdateVarString("ModelData[ModelActive](image)", ModelData[ModelActive].image);
	TclUpdateVarInt("ModelData[ModelActive](modeltype)", ModelData[ModelActive].modeltype);
	TclUpdateVarInt("ModelData[ModelActive](teletype)", ModelData[ModelActive].teletype);
	TclUpdateVarString("ModelData[ModelActive](teledevice)", ModelData[ModelActive].teledevice);
	TclUpdateVarInt("ModelData[ModelActive](telebaud)", ModelData[ModelActive].telebaud);
	TclUpdateVarString("ModelData[ModelActive](telebtaddr)", ModelData[ModelActive].telebtaddr);
	TclUpdateVarString("ModelData[ModelActive](telebtpin)", ModelData[ModelActive].telebtpin);
	TclUpdateVarInt("ModelData[ModelActive](mode)", ModelData[ModelActive].mode);
	TclUpdateVarInt("ModelData[ModelActive](status)", ModelData[ModelActive].status);
	TclUpdateVarInt("ModelData[ModelActive](armed)", ModelData[ModelActive].armed);
	TclUpdateVarInt("ModelData[ModelActive](heartbeat)", ModelData[ModelActive].heartbeat);
	TclUpdateVarInt("ModelData[ModelActive](heartbeat_rc)", ModelData[ModelActive].heartbeat_rc);
	TclUpdateVarInt("ModelData[ModelActive](found_rc)", ModelData[ModelActive].found_rc);
	TclUpdateVarFloat("ModelData[ModelActive](p_lat)", ModelData[ModelActive].p_lat);
	TclUpdateVarFloat("ModelData[ModelActive](p_long)", ModelData[ModelActive].p_long);
	TclUpdateVarFloat("ModelData[ModelActive](p_alt)", ModelData[ModelActive].p_alt);
	TclUpdateVarFloat("ModelData[ModelActive](alt_offset)", ModelData[ModelActive].alt_offset);
	TclUpdateVarFloat("ModelData[ModelActive](baro)", ModelData[ModelActive].baro);
	TclUpdateVarFloat("ModelData[ModelActive](pitch)", ModelData[ModelActive].pitch);
	TclUpdateVarFloat("ModelData[ModelActive](roll)", ModelData[ModelActive].roll);
	TclUpdateVarFloat("ModelData[ModelActive](yaw)", ModelData[ModelActive].yaw);
	TclUpdateVarFloat("ModelData[ModelActive](speed)", ModelData[ModelActive].speed);
	TclUpdateVarFloat("ModelData[ModelActive](voltage)", ModelData[ModelActive].voltage);
	TclUpdateVarFloat("ModelData[ModelActive](load)", ModelData[ModelActive].load);
	TclUpdateVarInt("ModelData[ModelActive](gpsfix)", ModelData[ModelActive].gpsfix);
	TclUpdateVarInt("ModelData[ModelActive](numSat)", ModelData[ModelActive].numSat);
	TclUpdateVarInt("ModelData[ModelActive](radio,0)", ModelData[ModelActive].radio[0]);
	TclUpdateVarInt("ModelData[ModelActive](radio,1)", ModelData[ModelActive].radio[1]);
	TclUpdateVarInt("ModelData[ModelActive](radio,2)", ModelData[ModelActive].radio[2]);
	TclUpdateVarInt("ModelData[ModelActive](radio,3)", ModelData[ModelActive].radio[3]);
	TclUpdateVarInt("ModelData[ModelActive](radio,4)", ModelData[ModelActive].radio[4]);
	TclUpdateVarInt("ModelData[ModelActive](radio,5)", ModelData[ModelActive].radio[5]);
	TclUpdateVarInt("ModelData[ModelActive](radio,6)", ModelData[ModelActive].radio[6]);
	TclUpdateVarInt("ModelData[ModelActive](radio,7)", ModelData[ModelActive].radio[7]);
	TclUpdateVarInt("ModelData[ModelActive](radio,8)", ModelData[ModelActive].radio[8]);
	TclUpdateVarInt("ModelData[ModelActive](radio,9)", ModelData[ModelActive].radio[9]);
	TclUpdateVarInt("ModelData[ModelActive](radio,10)", ModelData[ModelActive].radio[10]);
	TclUpdateVarInt("ModelData[ModelActive](radio,11)", ModelData[ModelActive].radio[11]);
	TclUpdateVarInt("ModelData[ModelActive](radio,12)", ModelData[ModelActive].radio[12]);
	TclUpdateVarInt("ModelData[ModelActive](radio,13)", ModelData[ModelActive].radio[13]);
	TclUpdateVarInt("ModelData[ModelActive](radio,14)", ModelData[ModelActive].radio[14]);
	TclUpdateVarInt("ModelData[ModelActive](radio,15)", ModelData[ModelActive].radio[15]);
	TclUpdateVarFloat("ModelData[ModelActive](acc_x)", ModelData[ModelActive].acc_x);
	TclUpdateVarFloat("ModelData[ModelActive](acc_y)", ModelData[ModelActive].acc_y);
	TclUpdateVarFloat("ModelData[ModelActive](acc_z)", ModelData[ModelActive].acc_z);
	TclUpdateVarFloat("ModelData[ModelActive](gyro_x)", ModelData[ModelActive].gyro_x);
	TclUpdateVarFloat("ModelData[ModelActive](gyro_y)", ModelData[ModelActive].gyro_y);
	TclUpdateVarFloat("ModelData[ModelActive](gyro_z)", ModelData[ModelActive].gyro_z);
	TclUpdateVarInt("ModelData[ModelActive](rssi_rx)", ModelData[ModelActive].rssi_rx);
	TclUpdateVarInt("ModelData[ModelActive](rssi_tx)", ModelData[ModelActive].rssi_tx);
	TclUpdateVarFloat("ModelData[ModelActive](voltage_rx)", ModelData[ModelActive].voltage_rx);
	TclUpdateVarFloat("ModelData[ModelActive](voltage_zell,0)", ModelData[ModelActive].voltage_zell[0]);
	TclUpdateVarFloat("ModelData[ModelActive](voltage_zell,1)", ModelData[ModelActive].voltage_zell[1]);
	TclUpdateVarFloat("ModelData[ModelActive](voltage_zell,2)", ModelData[ModelActive].voltage_zell[2]);
	TclUpdateVarFloat("ModelData[ModelActive](voltage_zell,3)", ModelData[ModelActive].voltage_zell[3]);
	TclUpdateVarFloat("ModelData[ModelActive](voltage_zell,4)", ModelData[ModelActive].voltage_zell[4]);
	TclUpdateVarFloat("ModelData[ModelActive](voltage_zell,5)", ModelData[ModelActive].voltage_zell[5]);
	TclUpdateVarInt("ModelData[ModelActive](temperature,0)", ModelData[ModelActive].temperature[0]);
	TclUpdateVarInt("ModelData[ModelActive](temperature,1)", ModelData[ModelActive].temperature[1]);
	TclUpdateVarFloat("ModelData[ModelActive](ampere)", ModelData[ModelActive].ampere);

}


