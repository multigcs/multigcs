
#include <all.h>


void UAVT_Accels_Send (UAVT_AccelsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	len = openpilot_add_4byte(buf, len, data->temperature);
	uavtalk_send(buf, ACCELS_OBJID, 0x22, len);
}


void UAVT_AccessoryDesired_Send (UAVT_AccessoryDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->AccessoryVal);
	uavtalk_send(buf, ACCESSORYDESIRED_OBJID, 0x22, len);
}


void UAVT_ActuatorCommand_Send (UAVT_ActuatorCommandData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->Channel[0]);
	len = openpilot_add_2byte(buf, len, data->Channel[1]);
	len = openpilot_add_2byte(buf, len, data->Channel[2]);
	len = openpilot_add_2byte(buf, len, data->Channel[3]);
	len = openpilot_add_2byte(buf, len, data->Channel[4]);
	len = openpilot_add_2byte(buf, len, data->Channel[5]);
	len = openpilot_add_2byte(buf, len, data->Channel[6]);
	len = openpilot_add_2byte(buf, len, data->Channel[7]);
	len = openpilot_add_2byte(buf, len, data->Channel[8]);
	len = openpilot_add_2byte(buf, len, data->Channel[9]);
	len = openpilot_add_2byte(buf, len, data->MaxUpdateTime);
	len = openpilot_add_1byte(buf, len, data->UpdateTime);
	len = openpilot_add_1byte(buf, len, data->NumFailedUpdates);
	uavtalk_send(buf, ACTUATORCOMMAND_OBJID, 0x22, len);
}


void UAVT_ActuatorDesired_Send (UAVT_ActuatorDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	len = openpilot_add_4byte(buf, len, data->Throttle);
	len = openpilot_add_4byte(buf, len, data->UpdateTime);
	len = openpilot_add_4byte(buf, len, data->NumLongUpdates);
	uavtalk_send(buf, ACTUATORDESIRED_OBJID, 0x22, len);
}


void UAVT_ActuatorSettings_Send (UAVT_ActuatorSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[0]);
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[1]);
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[2]);
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[3]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[0]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[1]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[2]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[3]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[4]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[5]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[6]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[7]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[8]);
	len = openpilot_add_2byte(buf, len, data->ChannelMax[9]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[0]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[1]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[2]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[3]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[4]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[5]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[6]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[7]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[8]);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral[9]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[0]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[1]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[2]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[3]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[4]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[5]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[6]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[7]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[8]);
	len = openpilot_add_2byte(buf, len, data->ChannelMin[9]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[0]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[1]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[2]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[3]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[4]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[5]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[6]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[7]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[8]);
	len = openpilot_add_1byte(buf, len, data->ChannelType[9]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[0]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[1]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[2]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[3]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[4]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[5]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[6]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[7]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[8]);
	len = openpilot_add_1byte(buf, len, data->ChannelAddr[9]);
	len = openpilot_add_1byte(buf, len, data->MotorsSpinWhileArmed);
	uavtalk_send(buf, ACTUATORSETTINGS_OBJID, 0x22, len);
}


void UAVT_AltHoldSmoothed_Send (UAVT_AltHoldSmoothedData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Altitude);
	len = openpilot_add_4byte(buf, len, data->Velocity);
	len = openpilot_add_4byte(buf, len, data->Accel);
	uavtalk_send(buf, ALTHOLDSMOOTHED_OBJID, 0x22, len);
}


void UAVT_AltitudeHoldDesired_Send (UAVT_AltitudeHoldDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Altitude);
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	uavtalk_send(buf, ALTITUDEHOLDDESIRED_OBJID, 0x22, len);
}


void UAVT_AltitudeHoldSettings_Send (UAVT_AltitudeHoldSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Kp);
	len = openpilot_add_4byte(buf, len, data->Ki);
	len = openpilot_add_4byte(buf, len, data->Kd);
	len = openpilot_add_4byte(buf, len, data->Ka);
	len = openpilot_add_4byte(buf, len, data->PressureNoise);
	len = openpilot_add_4byte(buf, len, data->AccelNoise);
	len = openpilot_add_4byte(buf, len, data->AccelDrift);
	uavtalk_send(buf, ALTITUDEHOLDSETTINGS_OBJID, 0x22, len);
}


void UAVT_AttitudeActual_Send (UAVT_AttitudeActualData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->q1);
	len = openpilot_add_4byte(buf, len, data->q2);
	len = openpilot_add_4byte(buf, len, data->q3);
	len = openpilot_add_4byte(buf, len, data->q4);
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	uavtalk_send(buf, ATTITUDEACTUAL_OBJID, 0x22, len);
}


void UAVT_AttitudeSettings_Send (UAVT_AttitudeSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->GyroGain);
	len = openpilot_add_4byte(buf, len, data->AccelKp);
	len = openpilot_add_4byte(buf, len, data->AccelKi);
	len = openpilot_add_4byte(buf, len, data->AccelTau);
	len = openpilot_add_4byte(buf, len, data->YawBiasRate);
	len = openpilot_add_2byte(buf, len, data->AccelBias.X);
	len = openpilot_add_2byte(buf, len, data->AccelBias.Y);
	len = openpilot_add_2byte(buf, len, data->AccelBias.Z);
	len = openpilot_add_2byte(buf, len, data->GyroBias.X);
	len = openpilot_add_2byte(buf, len, data->GyroBias.Y);
	len = openpilot_add_2byte(buf, len, data->GyroBias.Z);
	len = openpilot_add_2byte(buf, len, data->BoardRotation.Roll);
	len = openpilot_add_2byte(buf, len, data->BoardRotation.Pitch);
	len = openpilot_add_2byte(buf, len, data->BoardRotation.Yaw);
	len = openpilot_add_1byte(buf, len, data->ZeroDuringArming);
	len = openpilot_add_1byte(buf, len, data->BiasCorrectGyro);
	len = openpilot_add_1byte(buf, len, data->TrimFlight);
	uavtalk_send(buf, ATTITUDESETTINGS_OBJID, 0x22, len);
}


void UAVT_BaroAltitude_Send (UAVT_BaroAltitudeData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Altitude);
	len = openpilot_add_4byte(buf, len, data->Temperature);
	len = openpilot_add_4byte(buf, len, data->Pressure);
	uavtalk_send(buf, BAROALTITUDE_OBJID, 0x22, len);
}


void UAVT_CameraDesired_Send (UAVT_CameraDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	uavtalk_send(buf, CAMERADESIRED_OBJID, 0x22, len);
}


void UAVT_CameraStabSettings_Send (UAVT_CameraStabSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->MaxAxisLockRate);
	len = openpilot_add_2byte(buf, len, data->ResponseTime.Roll);
	len = openpilot_add_2byte(buf, len, data->ResponseTime.Pitch);
	len = openpilot_add_2byte(buf, len, data->ResponseTime.Yaw);
	len = openpilot_add_1byte(buf, len, data->Input.Roll);
	len = openpilot_add_1byte(buf, len, data->Input.Pitch);
	len = openpilot_add_1byte(buf, len, data->Input.Yaw);
	len = openpilot_add_1byte(buf, len, data->InputRange.Roll);
	len = openpilot_add_1byte(buf, len, data->InputRange.Pitch);
	len = openpilot_add_1byte(buf, len, data->InputRange.Yaw);
	len = openpilot_add_1byte(buf, len, data->InputRate.Roll);
	len = openpilot_add_1byte(buf, len, data->InputRate.Pitch);
	len = openpilot_add_1byte(buf, len, data->InputRate.Yaw);
	len = openpilot_add_1byte(buf, len, data->StabilizationMode.Roll);
	len = openpilot_add_1byte(buf, len, data->StabilizationMode.Pitch);
	len = openpilot_add_1byte(buf, len, data->StabilizationMode.Yaw);
	len = openpilot_add_1byte(buf, len, data->OutputRange.Roll);
	len = openpilot_add_1byte(buf, len, data->OutputRange.Pitch);
	len = openpilot_add_1byte(buf, len, data->OutputRange.Yaw);
	uavtalk_send(buf, CAMERASTABSETTINGS_OBJID, 0x22, len);
}


void UAVT_FaultSettings_Send (UAVT_FaultSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->ActivateFault);
	uavtalk_send(buf, FAULTSETTINGS_OBJID, 0x22, len);
}


void UAVT_FirmwareIAPObj_Send (UAVT_FirmwareIAPObjData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->crc);
	len = openpilot_add_2byte(buf, len, data->Command);
	len = openpilot_add_2byte(buf, len, data->BoardRevision);
	len = openpilot_add_1byte(buf, len, data->Description[0]);
	len = openpilot_add_1byte(buf, len, data->Description[1]);
	len = openpilot_add_1byte(buf, len, data->Description[2]);
	len = openpilot_add_1byte(buf, len, data->Description[3]);
	len = openpilot_add_1byte(buf, len, data->Description[4]);
	len = openpilot_add_1byte(buf, len, data->Description[5]);
	len = openpilot_add_1byte(buf, len, data->Description[6]);
	len = openpilot_add_1byte(buf, len, data->Description[7]);
	len = openpilot_add_1byte(buf, len, data->Description[8]);
	len = openpilot_add_1byte(buf, len, data->Description[9]);
	len = openpilot_add_1byte(buf, len, data->Description[10]);
	len = openpilot_add_1byte(buf, len, data->Description[11]);
	len = openpilot_add_1byte(buf, len, data->Description[12]);
	len = openpilot_add_1byte(buf, len, data->Description[13]);
	len = openpilot_add_1byte(buf, len, data->Description[14]);
	len = openpilot_add_1byte(buf, len, data->Description[15]);
	len = openpilot_add_1byte(buf, len, data->Description[16]);
	len = openpilot_add_1byte(buf, len, data->Description[17]);
	len = openpilot_add_1byte(buf, len, data->Description[18]);
	len = openpilot_add_1byte(buf, len, data->Description[19]);
	len = openpilot_add_1byte(buf, len, data->Description[20]);
	len = openpilot_add_1byte(buf, len, data->Description[21]);
	len = openpilot_add_1byte(buf, len, data->Description[22]);
	len = openpilot_add_1byte(buf, len, data->Description[23]);
	len = openpilot_add_1byte(buf, len, data->Description[24]);
	len = openpilot_add_1byte(buf, len, data->Description[25]);
	len = openpilot_add_1byte(buf, len, data->Description[26]);
	len = openpilot_add_1byte(buf, len, data->Description[27]);
	len = openpilot_add_1byte(buf, len, data->Description[28]);
	len = openpilot_add_1byte(buf, len, data->Description[29]);
	len = openpilot_add_1byte(buf, len, data->Description[30]);
	len = openpilot_add_1byte(buf, len, data->Description[31]);
	len = openpilot_add_1byte(buf, len, data->Description[32]);
	len = openpilot_add_1byte(buf, len, data->Description[33]);
	len = openpilot_add_1byte(buf, len, data->Description[34]);
	len = openpilot_add_1byte(buf, len, data->Description[35]);
	len = openpilot_add_1byte(buf, len, data->Description[36]);
	len = openpilot_add_1byte(buf, len, data->Description[37]);
	len = openpilot_add_1byte(buf, len, data->Description[38]);
	len = openpilot_add_1byte(buf, len, data->Description[39]);
	len = openpilot_add_1byte(buf, len, data->Description[40]);
	len = openpilot_add_1byte(buf, len, data->Description[41]);
	len = openpilot_add_1byte(buf, len, data->Description[42]);
	len = openpilot_add_1byte(buf, len, data->Description[43]);
	len = openpilot_add_1byte(buf, len, data->Description[44]);
	len = openpilot_add_1byte(buf, len, data->Description[45]);
	len = openpilot_add_1byte(buf, len, data->Description[46]);
	len = openpilot_add_1byte(buf, len, data->Description[47]);
	len = openpilot_add_1byte(buf, len, data->Description[48]);
	len = openpilot_add_1byte(buf, len, data->Description[49]);
	len = openpilot_add_1byte(buf, len, data->Description[50]);
	len = openpilot_add_1byte(buf, len, data->Description[51]);
	len = openpilot_add_1byte(buf, len, data->Description[52]);
	len = openpilot_add_1byte(buf, len, data->Description[53]);
	len = openpilot_add_1byte(buf, len, data->Description[54]);
	len = openpilot_add_1byte(buf, len, data->Description[55]);
	len = openpilot_add_1byte(buf, len, data->Description[56]);
	len = openpilot_add_1byte(buf, len, data->Description[57]);
	len = openpilot_add_1byte(buf, len, data->Description[58]);
	len = openpilot_add_1byte(buf, len, data->Description[59]);
	len = openpilot_add_1byte(buf, len, data->Description[60]);
	len = openpilot_add_1byte(buf, len, data->Description[61]);
	len = openpilot_add_1byte(buf, len, data->Description[62]);
	len = openpilot_add_1byte(buf, len, data->Description[63]);
	len = openpilot_add_1byte(buf, len, data->Description[64]);
	len = openpilot_add_1byte(buf, len, data->Description[65]);
	len = openpilot_add_1byte(buf, len, data->Description[66]);
	len = openpilot_add_1byte(buf, len, data->Description[67]);
	len = openpilot_add_1byte(buf, len, data->Description[68]);
	len = openpilot_add_1byte(buf, len, data->Description[69]);
	len = openpilot_add_1byte(buf, len, data->Description[70]);
	len = openpilot_add_1byte(buf, len, data->Description[71]);
	len = openpilot_add_1byte(buf, len, data->Description[72]);
	len = openpilot_add_1byte(buf, len, data->Description[73]);
	len = openpilot_add_1byte(buf, len, data->Description[74]);
	len = openpilot_add_1byte(buf, len, data->Description[75]);
	len = openpilot_add_1byte(buf, len, data->Description[76]);
	len = openpilot_add_1byte(buf, len, data->Description[77]);
	len = openpilot_add_1byte(buf, len, data->Description[78]);
	len = openpilot_add_1byte(buf, len, data->Description[79]);
	len = openpilot_add_1byte(buf, len, data->Description[80]);
	len = openpilot_add_1byte(buf, len, data->Description[81]);
	len = openpilot_add_1byte(buf, len, data->Description[82]);
	len = openpilot_add_1byte(buf, len, data->Description[83]);
	len = openpilot_add_1byte(buf, len, data->Description[84]);
	len = openpilot_add_1byte(buf, len, data->Description[85]);
	len = openpilot_add_1byte(buf, len, data->Description[86]);
	len = openpilot_add_1byte(buf, len, data->Description[87]);
	len = openpilot_add_1byte(buf, len, data->Description[88]);
	len = openpilot_add_1byte(buf, len, data->Description[89]);
	len = openpilot_add_1byte(buf, len, data->Description[90]);
	len = openpilot_add_1byte(buf, len, data->Description[91]);
	len = openpilot_add_1byte(buf, len, data->Description[92]);
	len = openpilot_add_1byte(buf, len, data->Description[93]);
	len = openpilot_add_1byte(buf, len, data->Description[94]);
	len = openpilot_add_1byte(buf, len, data->Description[95]);
	len = openpilot_add_1byte(buf, len, data->Description[96]);
	len = openpilot_add_1byte(buf, len, data->Description[97]);
	len = openpilot_add_1byte(buf, len, data->Description[98]);
	len = openpilot_add_1byte(buf, len, data->Description[99]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[0]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[1]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[2]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[3]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[4]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[5]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[6]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[7]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[8]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[9]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[10]);
	len = openpilot_add_1byte(buf, len, data->CPUSerial[11]);
	len = openpilot_add_1byte(buf, len, data->BoardType);
	len = openpilot_add_1byte(buf, len, data->ArmReset);
	uavtalk_send(buf, FIRMWAREIAPOBJ_OBJID, 0x22, len);
}


void UAVT_FlightBatterySettings_Send (UAVT_FlightBatterySettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Capacity);
	len = openpilot_add_4byte(buf, len, data->VoltageThresholds.Warning);
	len = openpilot_add_4byte(buf, len, data->VoltageThresholds.Alarm);
	len = openpilot_add_4byte(buf, len, data->SensorCalibrations.VoltageFactor);
	len = openpilot_add_4byte(buf, len, data->SensorCalibrations.CurrentFactor);
	len = openpilot_add_1byte(buf, len, data->Type);
	len = openpilot_add_1byte(buf, len, data->NbCells);
	len = openpilot_add_1byte(buf, len, data->SensorType);
	uavtalk_send(buf, FLIGHTBATTERYSETTINGS_OBJID, 0x22, len);
}


void UAVT_FlightPlanControl_Send (UAVT_FlightPlanControlData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->Command);
	uavtalk_send(buf, FLIGHTPLANCONTROL_OBJID, 0x22, len);
}


void UAVT_FlightPlanSettings_Send (UAVT_FlightPlanSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Test);
	uavtalk_send(buf, FLIGHTPLANSETTINGS_OBJID, 0x22, len);
}


void UAVT_FlightPlanStatus_Send (UAVT_FlightPlanStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->ErrorFileID);
	len = openpilot_add_4byte(buf, len, data->ErrorLineNum);
	len = openpilot_add_4byte(buf, len, data->Debug[0]);
	len = openpilot_add_4byte(buf, len, data->Debug[1]);
	len = openpilot_add_1byte(buf, len, data->Status);
	len = openpilot_add_1byte(buf, len, data->ErrorType);
	uavtalk_send(buf, FLIGHTPLANSTATUS_OBJID, 0x22, len);
}


void UAVT_FlightStatus_Send (UAVT_FlightStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->Armed);
	len = openpilot_add_1byte(buf, len, data->FlightMode);
	uavtalk_send(buf, FLIGHTSTATUS_OBJID, 0x22, len);
}


void UAVT_FlightTelemetryStats_Send (UAVT_FlightTelemetryStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->TxDataRate);
	len = openpilot_add_4byte(buf, len, data->RxDataRate);
	len = openpilot_add_4byte(buf, len, data->TxFailures);
	len = openpilot_add_4byte(buf, len, data->RxFailures);
	len = openpilot_add_4byte(buf, len, data->TxRetries);
	len = openpilot_add_1byte(buf, len, data->Status);
	uavtalk_send(buf, FLIGHTTELEMETRYSTATS_OBJID, 0x22, len);
}


void UAVT_GCSReceiver_Send (UAVT_GCSReceiverData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->Channel[0]);
	len = openpilot_add_2byte(buf, len, data->Channel[1]);
	len = openpilot_add_2byte(buf, len, data->Channel[2]);
	len = openpilot_add_2byte(buf, len, data->Channel[3]);
	len = openpilot_add_2byte(buf, len, data->Channel[4]);
	len = openpilot_add_2byte(buf, len, data->Channel[5]);
	len = openpilot_add_2byte(buf, len, data->Channel[6]);
	len = openpilot_add_2byte(buf, len, data->Channel[7]);
	uavtalk_send(buf, GCSRECEIVER_OBJID, 0x22, len);
}


void UAVT_GCSTelemetryStats_Send (UAVT_GCSTelemetryStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->TxDataRate);
	len = openpilot_add_4byte(buf, len, data->RxDataRate);
	len = openpilot_add_4byte(buf, len, data->TxFailures);
	len = openpilot_add_4byte(buf, len, data->RxFailures);
	len = openpilot_add_4byte(buf, len, data->TxRetries);
	len = openpilot_add_1byte(buf, len, data->Status);
	uavtalk_send(buf, GCSTELEMETRYSTATS_OBJID, 0x22, len);
}


void UAVT_GPSPosition_Send (UAVT_GPSPositionData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Latitude);
	len = openpilot_add_4byte(buf, len, data->Longitude);
	len = openpilot_add_4byte(buf, len, data->Altitude);
	len = openpilot_add_4byte(buf, len, data->GeoidSeparation);
	len = openpilot_add_4byte(buf, len, data->Heading);
	len = openpilot_add_4byte(buf, len, data->Groundspeed);
	len = openpilot_add_4byte(buf, len, data->PDOP);
	len = openpilot_add_4byte(buf, len, data->HDOP);
	len = openpilot_add_4byte(buf, len, data->VDOP);
	len = openpilot_add_1byte(buf, len, data->Status);
	len = openpilot_add_1byte(buf, len, data->Satellites);
	uavtalk_send(buf, GPSPOSITION_OBJID, 0x22, len);
}


void UAVT_GPSSatellites_Send (UAVT_GPSSatellitesData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Elevation[0]);
	len = openpilot_add_4byte(buf, len, data->Elevation[1]);
	len = openpilot_add_4byte(buf, len, data->Elevation[2]);
	len = openpilot_add_4byte(buf, len, data->Elevation[3]);
	len = openpilot_add_4byte(buf, len, data->Elevation[4]);
	len = openpilot_add_4byte(buf, len, data->Elevation[5]);
	len = openpilot_add_4byte(buf, len, data->Elevation[6]);
	len = openpilot_add_4byte(buf, len, data->Elevation[7]);
	len = openpilot_add_4byte(buf, len, data->Elevation[8]);
	len = openpilot_add_4byte(buf, len, data->Elevation[9]);
	len = openpilot_add_4byte(buf, len, data->Elevation[10]);
	len = openpilot_add_4byte(buf, len, data->Elevation[11]);
	len = openpilot_add_4byte(buf, len, data->Elevation[12]);
	len = openpilot_add_4byte(buf, len, data->Elevation[13]);
	len = openpilot_add_4byte(buf, len, data->Elevation[14]);
	len = openpilot_add_4byte(buf, len, data->Elevation[15]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[0]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[1]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[2]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[3]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[4]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[5]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[6]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[7]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[8]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[9]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[10]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[11]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[12]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[13]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[14]);
	len = openpilot_add_4byte(buf, len, data->Azimuth[15]);
	len = openpilot_add_1byte(buf, len, data->SatsInView);
	len = openpilot_add_1byte(buf, len, data->PRN[0]);
	len = openpilot_add_1byte(buf, len, data->PRN[1]);
	len = openpilot_add_1byte(buf, len, data->PRN[2]);
	len = openpilot_add_1byte(buf, len, data->PRN[3]);
	len = openpilot_add_1byte(buf, len, data->PRN[4]);
	len = openpilot_add_1byte(buf, len, data->PRN[5]);
	len = openpilot_add_1byte(buf, len, data->PRN[6]);
	len = openpilot_add_1byte(buf, len, data->PRN[7]);
	len = openpilot_add_1byte(buf, len, data->PRN[8]);
	len = openpilot_add_1byte(buf, len, data->PRN[9]);
	len = openpilot_add_1byte(buf, len, data->PRN[10]);
	len = openpilot_add_1byte(buf, len, data->PRN[11]);
	len = openpilot_add_1byte(buf, len, data->PRN[12]);
	len = openpilot_add_1byte(buf, len, data->PRN[13]);
	len = openpilot_add_1byte(buf, len, data->PRN[14]);
	len = openpilot_add_1byte(buf, len, data->PRN[15]);
	len = openpilot_add_1byte(buf, len, data->SNR[0]);
	len = openpilot_add_1byte(buf, len, data->SNR[1]);
	len = openpilot_add_1byte(buf, len, data->SNR[2]);
	len = openpilot_add_1byte(buf, len, data->SNR[3]);
	len = openpilot_add_1byte(buf, len, data->SNR[4]);
	len = openpilot_add_1byte(buf, len, data->SNR[5]);
	len = openpilot_add_1byte(buf, len, data->SNR[6]);
	len = openpilot_add_1byte(buf, len, data->SNR[7]);
	len = openpilot_add_1byte(buf, len, data->SNR[8]);
	len = openpilot_add_1byte(buf, len, data->SNR[9]);
	len = openpilot_add_1byte(buf, len, data->SNR[10]);
	len = openpilot_add_1byte(buf, len, data->SNR[11]);
	len = openpilot_add_1byte(buf, len, data->SNR[12]);
	len = openpilot_add_1byte(buf, len, data->SNR[13]);
	len = openpilot_add_1byte(buf, len, data->SNR[14]);
	len = openpilot_add_1byte(buf, len, data->SNR[15]);
	uavtalk_send(buf, GPSSATELLITES_OBJID, 0x22, len);
}


void UAVT_GPSSettings_Send (UAVT_GPSSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->DataProtocol);
	uavtalk_send(buf, GPSSETTINGS_OBJID, 0x22, len);
}


void UAVT_GPSTime_Send (UAVT_GPSTimeData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->Year);
	len = openpilot_add_1byte(buf, len, data->Month);
	len = openpilot_add_1byte(buf, len, data->Day);
	len = openpilot_add_1byte(buf, len, data->Hour);
	len = openpilot_add_1byte(buf, len, data->Minute);
	len = openpilot_add_1byte(buf, len, data->Second);
	uavtalk_send(buf, GPSTIME_OBJID, 0x22, len);
}


void UAVT_GPSVelocity_Send (UAVT_GPSVelocityData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(buf, GPSVELOCITY_OBJID, 0x22, len);
}


void UAVT_GuidanceSettings_Send (UAVT_GuidanceSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->HorizontalPosPI.Kp);
	len = openpilot_add_4byte(buf, len, data->HorizontalPosPI.Ki);
	len = openpilot_add_4byte(buf, len, data->HorizontalPosPI.ILimit);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.Kp);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.Ki);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.Kd);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.ILimit);
	len = openpilot_add_4byte(buf, len, data->VerticalPosPI.Kp);
	len = openpilot_add_4byte(buf, len, data->VerticalPosPI.Ki);
	len = openpilot_add_4byte(buf, len, data->VerticalPosPI.ILimit);
	len = openpilot_add_4byte(buf, len, data->VerticalVelPID.Kp);
	len = openpilot_add_4byte(buf, len, data->VerticalVelPID.Ki);
	len = openpilot_add_4byte(buf, len, data->VerticalVelPID.Kd);
	len = openpilot_add_4byte(buf, len, data->VerticalVelPID.ILimit);
	len = openpilot_add_4byte(buf, len, data->MaxRollPitch);
	len = openpilot_add_4byte(buf, len, data->UpdatePeriod);
	len = openpilot_add_2byte(buf, len, data->HorizontalVelMax);
	len = openpilot_add_2byte(buf, len, data->VerticalVelMax);
	len = openpilot_add_1byte(buf, len, data->GuidanceMode);
	len = openpilot_add_1byte(buf, len, data->ThrottleControl);
	uavtalk_send(buf, GUIDANCESETTINGS_OBJID, 0x22, len);
}


void UAVT_GyrosBias_Send (UAVT_GyrosBiasData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	uavtalk_send(buf, GYROSBIAS_OBJID, 0x22, len);
}


void UAVT_Gyros_Send (UAVT_GyrosData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	len = openpilot_add_4byte(buf, len, data->temperature);
	uavtalk_send(buf, GYROS_OBJID, 0x22, len);
}


void UAVT_HomeLocation_Send (UAVT_HomeLocationData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Latitude);
	len = openpilot_add_4byte(buf, len, data->Longitude);
	len = openpilot_add_4byte(buf, len, data->Altitude);
	len = openpilot_add_4byte(buf, len, data->ECEF[0]);
	len = openpilot_add_4byte(buf, len, data->ECEF[1]);
	len = openpilot_add_4byte(buf, len, data->ECEF[2]);
	len = openpilot_add_4byte(buf, len, data->RNE[0]);
	len = openpilot_add_4byte(buf, len, data->RNE[1]);
	len = openpilot_add_4byte(buf, len, data->RNE[2]);
	len = openpilot_add_4byte(buf, len, data->RNE[3]);
	len = openpilot_add_4byte(buf, len, data->RNE[4]);
	len = openpilot_add_4byte(buf, len, data->RNE[5]);
	len = openpilot_add_4byte(buf, len, data->RNE[6]);
	len = openpilot_add_4byte(buf, len, data->RNE[7]);
	len = openpilot_add_4byte(buf, len, data->RNE[8]);
	len = openpilot_add_4byte(buf, len, data->Be[0]);
	len = openpilot_add_4byte(buf, len, data->Be[1]);
	len = openpilot_add_4byte(buf, len, data->Be[2]);
	len = openpilot_add_4byte(buf, len, data->g_e);
	len = openpilot_add_1byte(buf, len, data->Set);
	uavtalk_send(buf, HOMELOCATION_OBJID, 0x22, len);
}


void UAVT_HwSettings_Send (UAVT_HwSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->CC_RcvrPort);
	len = openpilot_add_1byte(buf, len, data->CC_MainPort);
	len = openpilot_add_1byte(buf, len, data->CC_FlexiPort);
	len = openpilot_add_1byte(buf, len, data->RV_RcvrPort);
	len = openpilot_add_1byte(buf, len, data->RV_AuxPort);
	len = openpilot_add_1byte(buf, len, data->RV_AuxSBusPort);
	len = openpilot_add_1byte(buf, len, data->RV_FlexiPort);
	len = openpilot_add_1byte(buf, len, data->RV_TelemetryPort);
	len = openpilot_add_1byte(buf, len, data->RV_GPSPort);
	len = openpilot_add_1byte(buf, len, data->TelemetrySpeed);
	len = openpilot_add_1byte(buf, len, data->GPSSpeed);
	len = openpilot_add_1byte(buf, len, data->ComUsbBridgeSpeed);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->OptionalModules.CameraStab);
	len = openpilot_add_1byte(buf, len, data->OptionalModules.GPS);
	len = openpilot_add_1byte(buf, len, data->OptionalModules.ComUsbBridge);
	len = openpilot_add_1byte(buf, len, data->OptionalModules.Fault);
	len = openpilot_add_1byte(buf, len, data->OptionalModules.Altitude);
	len = openpilot_add_1byte(buf, len, data->OptionalModules.TxPID);
	len = openpilot_add_1byte(buf, len, data->OptionalModules.Autotune);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	uavtalk_send(buf, HWSETTINGS_OBJID, 0x22, len);
}


void UAVT_I2CStats_Send (UAVT_I2CStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->evirq_log[0]);
	len = openpilot_add_4byte(buf, len, data->evirq_log[1]);
	len = openpilot_add_4byte(buf, len, data->evirq_log[2]);
	len = openpilot_add_4byte(buf, len, data->evirq_log[3]);
	len = openpilot_add_4byte(buf, len, data->evirq_log[4]);
	len = openpilot_add_4byte(buf, len, data->erirq_log[0]);
	len = openpilot_add_4byte(buf, len, data->erirq_log[1]);
	len = openpilot_add_4byte(buf, len, data->erirq_log[2]);
	len = openpilot_add_4byte(buf, len, data->erirq_log[3]);
	len = openpilot_add_4byte(buf, len, data->erirq_log[4]);
	len = openpilot_add_1byte(buf, len, data->event_errors);
	len = openpilot_add_1byte(buf, len, data->fsm_errors);
	len = openpilot_add_1byte(buf, len, data->irq_errors);
	len = openpilot_add_1byte(buf, len, data->nacks);
	len = openpilot_add_1byte(buf, len, data->timeouts);
	len = openpilot_add_1byte(buf, len, data->last_error_type);
	len = openpilot_add_1byte(buf, len, data->event_log[0]);
	len = openpilot_add_1byte(buf, len, data->event_log[1]);
	len = openpilot_add_1byte(buf, len, data->event_log[2]);
	len = openpilot_add_1byte(buf, len, data->event_log[3]);
	len = openpilot_add_1byte(buf, len, data->event_log[4]);
	len = openpilot_add_1byte(buf, len, data->state_log[0]);
	len = openpilot_add_1byte(buf, len, data->state_log[1]);
	len = openpilot_add_1byte(buf, len, data->state_log[2]);
	len = openpilot_add_1byte(buf, len, data->state_log[3]);
	len = openpilot_add_1byte(buf, len, data->state_log[4]);
	uavtalk_send(buf, I2CSTATS_OBJID, 0x22, len);
}


void UAVT_Magnetometer_Send (UAVT_MagnetometerData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	uavtalk_send(buf, MAGNETOMETER_OBJID, 0x22, len);
}


void UAVT_ManualControlCommand_Send (UAVT_ManualControlCommandData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Throttle);
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	len = openpilot_add_4byte(buf, len, data->Collective);
	len = openpilot_add_2byte(buf, len, data->Channel[0]);
	len = openpilot_add_2byte(buf, len, data->Channel[1]);
	len = openpilot_add_2byte(buf, len, data->Channel[2]);
	len = openpilot_add_2byte(buf, len, data->Channel[3]);
	len = openpilot_add_2byte(buf, len, data->Channel[4]);
	len = openpilot_add_2byte(buf, len, data->Channel[5]);
	len = openpilot_add_2byte(buf, len, data->Channel[6]);
	len = openpilot_add_2byte(buf, len, data->Channel[7]);
	len = openpilot_add_2byte(buf, len, data->Channel[8]);
	len = openpilot_add_1byte(buf, len, data->Connected);
	uavtalk_send(buf, MANUALCONTROLCOMMAND_OBJID, 0x22, len);
}


void UAVT_ManualControlSettings_Send (UAVT_ManualControlSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Deadband);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Throttle);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Roll);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Pitch);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Yaw);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.FlightMode);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Collective);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Accessory0);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Accessory1);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Accessory2);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Throttle);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Roll);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Pitch);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Yaw);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.FlightMode);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Collective);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Accessory0);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Accessory1);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Accessory2);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Throttle);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Roll);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Pitch);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Yaw);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.FlightMode);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Collective);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Accessory0);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Accessory1);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Accessory2);
	len = openpilot_add_2byte(buf, len, data->ArmedTimeout);
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.Throttle);
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.Roll);
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.Pitch);
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.Yaw);
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.FlightMode);
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.Collective);
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.Accessory0);
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.Accessory1);
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.Accessory2);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Throttle);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Roll);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Pitch);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Yaw);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.FlightMode);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Collective);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Accessory0);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Accessory1);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Accessory2);
	len = openpilot_add_1byte(buf, len, data->Arming);
	len = openpilot_add_1byte(buf, len, data->Stabilization1Settings.Roll);
	len = openpilot_add_1byte(buf, len, data->Stabilization1Settings.Pitch);
	len = openpilot_add_1byte(buf, len, data->Stabilization1Settings.Yaw);
	len = openpilot_add_1byte(buf, len, data->Stabilization2Settings.Roll);
	len = openpilot_add_1byte(buf, len, data->Stabilization2Settings.Pitch);
	len = openpilot_add_1byte(buf, len, data->Stabilization2Settings.Yaw);
	len = openpilot_add_1byte(buf, len, data->Stabilization3Settings.Roll);
	len = openpilot_add_1byte(buf, len, data->Stabilization3Settings.Pitch);
	len = openpilot_add_1byte(buf, len, data->Stabilization3Settings.Yaw);
	len = openpilot_add_1byte(buf, len, data->FlightModeNumber);
	len = openpilot_add_1byte(buf, len, data->FlightModePosition[0]);
	len = openpilot_add_1byte(buf, len, data->FlightModePosition[1]);
	len = openpilot_add_1byte(buf, len, data->FlightModePosition[2]);
	len = openpilot_add_1byte(buf, len, data->FlightModePosition[3]);
	len = openpilot_add_1byte(buf, len, data->FlightModePosition[4]);
	len = openpilot_add_1byte(buf, len, data->FlightModePosition[5]);
	uavtalk_send(buf, MANUALCONTROLSETTINGS_OBJID, 0x22, len);
}


void UAVT_MixerSettings_Send (UAVT_MixerSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->MaxAccel);
	len = openpilot_add_4byte(buf, len, data->FeedForward);
	len = openpilot_add_4byte(buf, len, data->AccelTime);
	len = openpilot_add_4byte(buf, len, data->DecelTime);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve1.n);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve1.n2);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve1.n5);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve1.n7);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve1.n1);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve2.n);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve2.n2);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve2.n5);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve2.n7);
	len = openpilot_add_4byte(buf, len, data->ThrottleCurve2.n1);
	len = openpilot_add_1byte(buf, len, data->Curve2Source);
	len = openpilot_add_1byte(buf, len, data->Mixer1Type);
	uavtalk_send(buf, MIXERSETTINGS_OBJID, 0x22, len);
}


void UAVT_MixerStatus_Send (UAVT_MixerStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Mixer1);
	len = openpilot_add_4byte(buf, len, data->Mixer2);
	len = openpilot_add_4byte(buf, len, data->Mixer3);
	len = openpilot_add_4byte(buf, len, data->Mixer4);
	len = openpilot_add_4byte(buf, len, data->Mixer5);
	len = openpilot_add_4byte(buf, len, data->Mixer6);
	len = openpilot_add_4byte(buf, len, data->Mixer7);
	len = openpilot_add_4byte(buf, len, data->Mixer8);
	len = openpilot_add_4byte(buf, len, data->Mixer9);
	len = openpilot_add_4byte(buf, len, data->Mixer10);
	uavtalk_send(buf, MIXERSTATUS_OBJID, 0x22, len);
}


void UAVT_NedAccel_Send (UAVT_NedAccelData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(buf, NEDACCEL_OBJID, 0x22, len);
}


void UAVT_ObjectPersistence_Send (UAVT_ObjectPersistenceData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->ObjectID);
	len = openpilot_add_4byte(buf, len, data->InstanceID);
	len = openpilot_add_1byte(buf, len, data->Operation);
	len = openpilot_add_1byte(buf, len, data->Selection);
	uavtalk_send(buf, OBJECTPERSISTENCE_OBJID, 0x22, len);
}


void UAVT_OveroSyncStats_Send (UAVT_OveroSyncStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Send);
	len = openpilot_add_4byte(buf, len, data->Received);
	len = openpilot_add_4byte(buf, len, data->DroppedUpdates);
	len = openpilot_add_1byte(buf, len, data->Connected);
	uavtalk_send(buf, OVEROSYNCSTATS_OBJID, 0x22, len);
}


void UAVT_PathAction_Send (UAVT_PathActionData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->ModeParameters[0]);
	len = openpilot_add_4byte(buf, len, data->ModeParameters[1]);
	len = openpilot_add_4byte(buf, len, data->ModeParameters[2]);
	len = openpilot_add_4byte(buf, len, data->ModeParameters[3]);
	len = openpilot_add_4byte(buf, len, data->ConditionParameters[0]);
	len = openpilot_add_4byte(buf, len, data->ConditionParameters[1]);
	len = openpilot_add_4byte(buf, len, data->ConditionParameters[2]);
	len = openpilot_add_4byte(buf, len, data->ConditionParameters[3]);
	len = openpilot_add_1byte(buf, len, data->Mode);
	len = openpilot_add_1byte(buf, len, data->EndCondition);
	len = openpilot_add_1byte(buf, len, data->Command);
	len = openpilot_add_1byte(buf, len, data->JumpDestination);
	len = openpilot_add_1byte(buf, len, data->ErrorDestination);
	uavtalk_send(buf, PATHACTION_OBJID, 0x22, len);
}


void UAVT_PipXSettings_Send (UAVT_PipXSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->PairID);
	len = openpilot_add_4byte(buf, len, data->Frequency);
	len = openpilot_add_2byte(buf, len, data->SendTimeout);
	len = openpilot_add_1byte(buf, len, data->TelemetryConfig);
	len = openpilot_add_1byte(buf, len, data->TelemetrySpeed);
	len = openpilot_add_1byte(buf, len, data->FlexiConfig);
	len = openpilot_add_1byte(buf, len, data->FlexiSpeed);
	len = openpilot_add_1byte(buf, len, data->VCPConfig);
	len = openpilot_add_1byte(buf, len, data->VCPSpeed);
	len = openpilot_add_1byte(buf, len, data->RFSpeed);
	len = openpilot_add_1byte(buf, len, data->MaxRFPower);
	len = openpilot_add_1byte(buf, len, data->MinPacketSize);
	len = openpilot_add_1byte(buf, len, data->FrequencyCalibration);
	len = openpilot_add_1byte(buf, len, data->AESKey[0]);
	len = openpilot_add_1byte(buf, len, data->AESKey[1]);
	len = openpilot_add_1byte(buf, len, data->AESKey[2]);
	len = openpilot_add_1byte(buf, len, data->AESKey[3]);
	len = openpilot_add_1byte(buf, len, data->AESKey[4]);
	len = openpilot_add_1byte(buf, len, data->AESKey[5]);
	len = openpilot_add_1byte(buf, len, data->AESKey[6]);
	len = openpilot_add_1byte(buf, len, data->AESKey[7]);
	len = openpilot_add_1byte(buf, len, data->AESKey[8]);
	len = openpilot_add_1byte(buf, len, data->AESKey[9]);
	len = openpilot_add_1byte(buf, len, data->AESKey[10]);
	len = openpilot_add_1byte(buf, len, data->AESKey[11]);
	len = openpilot_add_1byte(buf, len, data->AESKey[12]);
	len = openpilot_add_1byte(buf, len, data->AESKey[13]);
	len = openpilot_add_1byte(buf, len, data->AESKey[14]);
	len = openpilot_add_1byte(buf, len, data->AESKey[15]);
	len = openpilot_add_1byte(buf, len, data->AESKey[16]);
	len = openpilot_add_1byte(buf, len, data->AESKey[17]);
	len = openpilot_add_1byte(buf, len, data->AESKey[18]);
	len = openpilot_add_1byte(buf, len, data->AESKey[19]);
	len = openpilot_add_1byte(buf, len, data->AESKey[20]);
	len = openpilot_add_1byte(buf, len, data->AESKey[21]);
	len = openpilot_add_1byte(buf, len, data->AESKey[22]);
	len = openpilot_add_1byte(buf, len, data->AESKey[23]);
	len = openpilot_add_1byte(buf, len, data->AESKey[24]);
	len = openpilot_add_1byte(buf, len, data->AESKey[25]);
	len = openpilot_add_1byte(buf, len, data->AESKey[26]);
	len = openpilot_add_1byte(buf, len, data->AESKey[27]);
	len = openpilot_add_1byte(buf, len, data->AESKey[28]);
	len = openpilot_add_1byte(buf, len, data->AESKey[29]);
	len = openpilot_add_1byte(buf, len, data->AESKey[30]);
	len = openpilot_add_1byte(buf, len, data->AESKey[31]);
	uavtalk_send(buf, PIPXSETTINGS_OBJID, 0x22, len);
}


void UAVT_PositionActual_Send (UAVT_PositionActualData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(buf, POSITIONACTUAL_OBJID, 0x22, len);
}


void UAVT_PositionDesired_Send (UAVT_PositionDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(buf, POSITIONDESIRED_OBJID, 0x22, len);
}


void UAVT_RateDesired_Send (UAVT_RateDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	uavtalk_send(buf, RATEDESIRED_OBJID, 0x22, len);
}


void UAVT_RelayTuningSettings_Send (UAVT_RelayTuningSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->RateGain);
	len = openpilot_add_4byte(buf, len, data->AttitudeGain);
	len = openpilot_add_4byte(buf, len, data->Amplitude);
	len = openpilot_add_1byte(buf, len, data->HysteresisThresh);
	len = openpilot_add_1byte(buf, len, data->Mode);
	len = openpilot_add_1byte(buf, len, data->Behavior);
	uavtalk_send(buf, RELAYTUNINGSETTINGS_OBJID, 0x22, len);
}


void UAVT_RevoCalibration_Send (UAVT_RevoCalibrationData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->accel_bias.X);
	len = openpilot_add_4byte(buf, len, data->accel_bias.Y);
	len = openpilot_add_4byte(buf, len, data->accel_bias.Z);
	len = openpilot_add_4byte(buf, len, data->accel_scale.X);
	len = openpilot_add_4byte(buf, len, data->accel_scale.Y);
	len = openpilot_add_4byte(buf, len, data->accel_scale.Z);
	len = openpilot_add_4byte(buf, len, data->accel_var.X);
	len = openpilot_add_4byte(buf, len, data->accel_var.Y);
	len = openpilot_add_4byte(buf, len, data->accel_var.Z);
	len = openpilot_add_4byte(buf, len, data->gyro_bias.X);
	len = openpilot_add_4byte(buf, len, data->gyro_bias.Y);
	len = openpilot_add_4byte(buf, len, data->gyro_bias.Z);
	len = openpilot_add_4byte(buf, len, data->gyro_scale.X);
	len = openpilot_add_4byte(buf, len, data->gyro_scale.Y);
	len = openpilot_add_4byte(buf, len, data->gyro_scale.Z);
	len = openpilot_add_4byte(buf, len, data->gyro_var.X);
	len = openpilot_add_4byte(buf, len, data->gyro_var.Y);
	len = openpilot_add_4byte(buf, len, data->gyro_var.Z);
	len = openpilot_add_4byte(buf, len, data->gyro_tempcoeff.X);
	len = openpilot_add_4byte(buf, len, data->gyro_tempcoeff.Y);
	len = openpilot_add_4byte(buf, len, data->gyro_tempcoeff.Z);
	len = openpilot_add_4byte(buf, len, data->mag_bias.X);
	len = openpilot_add_4byte(buf, len, data->mag_bias.Y);
	len = openpilot_add_4byte(buf, len, data->mag_bias.Z);
	len = openpilot_add_4byte(buf, len, data->mag_scale.X);
	len = openpilot_add_4byte(buf, len, data->mag_scale.Y);
	len = openpilot_add_4byte(buf, len, data->mag_scale.Z);
	len = openpilot_add_4byte(buf, len, data->mag_var.X);
	len = openpilot_add_4byte(buf, len, data->mag_var.Y);
	len = openpilot_add_4byte(buf, len, data->mag_var.Z);
	len = openpilot_add_1byte(buf, len, data->BiasCorrectedRaw);
	uavtalk_send(buf, REVOCALIBRATION_OBJID, 0x22, len);
}


void UAVT_SonarAltitude_Send (UAVT_SonarAltitudeData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Altitude);
	uavtalk_send(buf, SONARALTITUDE_OBJID, 0x22, len);
}


void UAVT_StabilizationDesired_Send (UAVT_StabilizationDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	len = openpilot_add_4byte(buf, len, data->Throttle);
	len = openpilot_add_1byte(buf, len, data->StabilizationMode.Roll);
	len = openpilot_add_1byte(buf, len, data->StabilizationMode.Pitch);
	len = openpilot_add_1byte(buf, len, data->StabilizationMode.Yaw);
	uavtalk_send(buf, STABILIZATIONDESIRED_OBJID, 0x22, len);
}


void UAVT_StabilizationSettings_Send (UAVT_StabilizationSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->ManualRate.Roll);
	len = openpilot_add_4byte(buf, len, data->ManualRate.Pitch);
	len = openpilot_add_4byte(buf, len, data->ManualRate.Yaw);
	len = openpilot_add_4byte(buf, len, data->MaximumRate.Roll);
	len = openpilot_add_4byte(buf, len, data->MaximumRate.Pitch);
	len = openpilot_add_4byte(buf, len, data->MaximumRate.Yaw);
	len = openpilot_add_4byte(buf, len, data->RollRatePID.Kp);
	len = openpilot_add_4byte(buf, len, data->RollRatePID.Ki);
	len = openpilot_add_4byte(buf, len, data->RollRatePID.Kd);
	len = openpilot_add_4byte(buf, len, data->RollRatePID.ILimit);
	len = openpilot_add_4byte(buf, len, data->PitchRatePID.Kp);
	len = openpilot_add_4byte(buf, len, data->PitchRatePID.Ki);
	len = openpilot_add_4byte(buf, len, data->PitchRatePID.Kd);
	len = openpilot_add_4byte(buf, len, data->PitchRatePID.ILimit);
	len = openpilot_add_4byte(buf, len, data->YawRatePID.Kp);
	len = openpilot_add_4byte(buf, len, data->YawRatePID.Ki);
	len = openpilot_add_4byte(buf, len, data->YawRatePID.Kd);
	len = openpilot_add_4byte(buf, len, data->YawRatePID.ILimit);
	len = openpilot_add_4byte(buf, len, data->RollPI.Kp);
	len = openpilot_add_4byte(buf, len, data->RollPI.Ki);
	len = openpilot_add_4byte(buf, len, data->RollPI.ILimit);
	len = openpilot_add_4byte(buf, len, data->PitchPI.Kp);
	len = openpilot_add_4byte(buf, len, data->PitchPI.Ki);
	len = openpilot_add_4byte(buf, len, data->PitchPI.ILimit);
	len = openpilot_add_4byte(buf, len, data->YawPI.Kp);
	len = openpilot_add_4byte(buf, len, data->YawPI.Ki);
	len = openpilot_add_4byte(buf, len, data->YawPI.ILimit);
	len = openpilot_add_4byte(buf, len, data->VbarSensitivity.Roll);
	len = openpilot_add_4byte(buf, len, data->VbarSensitivity.Pitch);
	len = openpilot_add_4byte(buf, len, data->VbarSensitivity.Yaw);
	len = openpilot_add_4byte(buf, len, data->VbarRollPI.Kp);
	len = openpilot_add_4byte(buf, len, data->VbarRollPI.Ki);
	len = openpilot_add_4byte(buf, len, data->VbarPitchPI.Kp);
	len = openpilot_add_4byte(buf, len, data->VbarPitchPI.Ki);
	len = openpilot_add_4byte(buf, len, data->VbarYawPI.Kp);
	len = openpilot_add_4byte(buf, len, data->VbarYawPI.Ki);
	len = openpilot_add_4byte(buf, len, data->VbarTau);
	len = openpilot_add_4byte(buf, len, data->GyroTau);
	len = openpilot_add_4byte(buf, len, data->DerivativeGamma);
	len = openpilot_add_4byte(buf, len, data->WeakLevelingKp);
	len = openpilot_add_1byte(buf, len, data->RollMax);
	len = openpilot_add_1byte(buf, len, data->PitchMax);
	len = openpilot_add_1byte(buf, len, data->YawMax);
	len = openpilot_add_1byte(buf, len, data->VbarGyroSuppress);
	len = openpilot_add_1byte(buf, len, data->VbarPiroComp);
	len = openpilot_add_1byte(buf, len, data->VbarMaxAngle);
	len = openpilot_add_1byte(buf, len, data->DerivativeCutoff);
	len = openpilot_add_1byte(buf, len, data->MaxAxisLock);
	len = openpilot_add_1byte(buf, len, data->MaxAxisLockRate);
	len = openpilot_add_1byte(buf, len, data->MaxWeakLevelingRate);
	len = openpilot_add_1byte(buf, len, data->LowThrottleZeroIntegral);
	len = openpilot_add_1byte(buf, len, data->LowThrottleZeroAxis.Roll);
	len = openpilot_add_1byte(buf, len, data->LowThrottleZeroAxis.Pitch);
	len = openpilot_add_1byte(buf, len, data->LowThrottleZeroAxis.Yaw);
	uavtalk_send(buf, STABILIZATIONSETTINGS_OBJID, 0x22, len);
}


void UAVT_SystemAlarms_Send (UAVT_SystemAlarmsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->Alarm.OutOfMemory);
	len = openpilot_add_1byte(buf, len, data->Alarm.StackOverflow);
	len = openpilot_add_1byte(buf, len, data->Alarm.CPUOverload);
	len = openpilot_add_1byte(buf, len, data->Alarm.EventSystem);
	len = openpilot_add_1byte(buf, len, data->Alarm.Telemetry);
	len = openpilot_add_1byte(buf, len, data->Alarm.ManualControl);
	len = openpilot_add_1byte(buf, len, data->Alarm.Actuator);
	len = openpilot_add_1byte(buf, len, data->Alarm.Attitude);
	len = openpilot_add_1byte(buf, len, data->Alarm.Sensors);
	len = openpilot_add_1byte(buf, len, data->Alarm.Stabilization);
	len = openpilot_add_1byte(buf, len, data->Alarm.Guidance);
	len = openpilot_add_1byte(buf, len, data->Alarm.Battery);
	len = openpilot_add_1byte(buf, len, data->Alarm.FlightTime);
	len = openpilot_add_1byte(buf, len, data->Alarm.I2C);
	len = openpilot_add_1byte(buf, len, data->Alarm.GPS);
	len = openpilot_add_1byte(buf, len, data->Alarm.BootFault);
	uavtalk_send(buf, SYSTEMALARMS_OBJID, 0x22, len);
}


void UAVT_SystemSettings_Send (UAVT_SystemSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->GUIConfigData[0]);
	len = openpilot_add_4byte(buf, len, data->GUIConfigData[1]);
	len = openpilot_add_4byte(buf, len, data->GUIConfigData[2]);
	len = openpilot_add_4byte(buf, len, data->GUIConfigData[3]);
	len = openpilot_add_1byte(buf, len, data->AirframeType);
	uavtalk_send(buf, SYSTEMSETTINGS_OBJID, 0x22, len);
}


void UAVT_SystemStats_Send (UAVT_SystemStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->FlightTime);
	len = openpilot_add_4byte(buf, len, data->EventSystemWarningID);
	len = openpilot_add_4byte(buf, len, data->ObjectManagerCallbackID);
	len = openpilot_add_4byte(buf, len, data->ObjectManagerQueueID);
	len = openpilot_add_2byte(buf, len, data->HeapRemaining);
	len = openpilot_add_2byte(buf, len, data->IRQStackRemaining);
	len = openpilot_add_1byte(buf, len, data->CPULoad);
	len = openpilot_add_1byte(buf, len, data->CPUTemp);
	uavtalk_send(buf, SYSTEMSTATS_OBJID, 0x22, len);
}


void UAVT_TaskInfo_Send (UAVT_TaskInfoData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	uavtalk_send(buf, TASKINFO_OBJID, 0x22, len);
}


void UAVT_TxPIDSettings_Send (UAVT_TxPIDSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->ThrottleRange[0]);
	len = openpilot_add_4byte(buf, len, data->ThrottleRange[1]);
	len = openpilot_add_4byte(buf, len, data->MinPID.Instance1);
	len = openpilot_add_4byte(buf, len, data->MinPID.Instance2);
	len = openpilot_add_4byte(buf, len, data->MinPID.Instance3);
	len = openpilot_add_4byte(buf, len, data->MaxPID.Instance1);
	len = openpilot_add_4byte(buf, len, data->MaxPID.Instance2);
	len = openpilot_add_4byte(buf, len, data->MaxPID.Instance3);
	len = openpilot_add_1byte(buf, len, data->UpdateMode);
	len = openpilot_add_1byte(buf, len, data->Inputs.Instance1);
	len = openpilot_add_1byte(buf, len, data->Inputs.Instance2);
	len = openpilot_add_1byte(buf, len, data->Inputs.Instance3);
	len = openpilot_add_1byte(buf, len, data->PIDs.Instance1);
	len = openpilot_add_1byte(buf, len, data->PIDs.Instance2);
	len = openpilot_add_1byte(buf, len, data->PIDs.Instance3);
	uavtalk_send(buf, TXPIDSETTINGS_OBJID, 0x22, len);
}


void UAVT_VelocityActual_Send (UAVT_VelocityActualData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(buf, VELOCITYACTUAL_OBJID, 0x22, len);
}


void UAVT_VelocityDesired_Send (UAVT_VelocityDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(buf, VELOCITYDESIRED_OBJID, 0x22, len);
}


void UAVT_WatchdogStatus_Send (UAVT_WatchdogStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->BootupFlags);
	len = openpilot_add_2byte(buf, len, data->ActiveFlags);
	uavtalk_send(buf, WATCHDOGSTATUS_OBJID, 0x22, len);
}


void UAVT_WaypointActive_Send (UAVT_WaypointActiveData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->Index);
	uavtalk_send(buf, WAYPOINTACTIVE_OBJID, 0x22, len);
}


void UAVT_Waypoint_Send (UAVT_WaypointData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Position.North);
	len = openpilot_add_4byte(buf, len, data->Position.East);
	len = openpilot_add_4byte(buf, len, data->Position.Down);
	len = openpilot_add_4byte(buf, len, data->Velocity);
	len = openpilot_add_1byte(buf, len, data->Action);
	uavtalk_send(buf, WAYPOINT_OBJID, 0x22, len);
}

