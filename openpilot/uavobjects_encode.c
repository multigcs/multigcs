
#include <all.h>


void UAVT_AccelDesired_Send (UAVT_AccelDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(ModelActive, buf, ACCELDESIRED_OBJID, 0x22, len);
}


void UAVT_Accels_Send (UAVT_AccelsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	len = openpilot_add_4byte(buf, len, data->temperature);
	uavtalk_send(ModelActive, buf, ACCELS_OBJID, 0x22, len);
}


void UAVT_AccessoryDesired_Send (UAVT_AccessoryDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->AccessoryVal);
	uavtalk_send(ModelActive, buf, ACCESSORYDESIRED_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, ACTUATORCOMMAND_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, ACTUATORDESIRED_OBJID, 0x22, len);
}


void UAVT_ActuatorSettings_Send (UAVT_ActuatorSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[0]);
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[1]);
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[2]);
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[3]);
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[4]);
	len = openpilot_add_2byte(buf, len, data->ChannelUpdateFreq[5]);
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
	uavtalk_send(ModelActive, buf, ACTUATORSETTINGS_OBJID, 0x22, len);
}


void UAVT_AirspeedActual_Send (UAVT_AirspeedActualData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->TrueAirspeed);
	len = openpilot_add_4byte(buf, len, data->CalibratedAirspeed);
	len = openpilot_add_4byte(buf, len, data->alpha);
	len = openpilot_add_4byte(buf, len, data->beta);
	uavtalk_send(ModelActive, buf, AIRSPEEDACTUAL_OBJID, 0x22, len);
}


void UAVT_AirspeedSettings_Send (UAVT_AirspeedSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Scale);
	len = openpilot_add_2byte(buf, len, data->ZeroPoint);
	len = openpilot_add_1byte(buf, len, data->GPSSamplePeriod_ms);
	len = openpilot_add_1byte(buf, len, data->AirspeedSensorType);
	len = openpilot_add_1byte(buf, len, data->AnalogPin);
	uavtalk_send(ModelActive, buf, AIRSPEEDSETTINGS_OBJID, 0x22, len);
}


void UAVT_AltitudeHoldDesired_Send (UAVT_AltitudeHoldDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Altitude);
	len = openpilot_add_4byte(buf, len, data->ClimbRate);
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	len = openpilot_add_1byte(buf, len, data->Land);
	uavtalk_send(ModelActive, buf, ALTITUDEHOLDDESIRED_OBJID, 0x22, len);
}


void UAVT_AltitudeHoldSettings_Send (UAVT_AltitudeHoldSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->PositionKp);
	len = openpilot_add_4byte(buf, len, data->VelocityKp);
	len = openpilot_add_4byte(buf, len, data->VelocityKi);
	len = openpilot_add_2byte(buf, len, data->AttitudeComp);
	len = openpilot_add_1byte(buf, len, data->MaxRate);
	len = openpilot_add_1byte(buf, len, data->Expo);
	len = openpilot_add_1byte(buf, len, data->Deadband);
	uavtalk_send(ModelActive, buf, ALTITUDEHOLDSETTINGS_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, ATTITUDEACTUAL_OBJID, 0x22, len);
}


void UAVT_AttitudeSettings_Send (UAVT_AttitudeSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->MagKp);
	len = openpilot_add_4byte(buf, len, data->MagKi);
	len = openpilot_add_4byte(buf, len, data->AccelKp);
	len = openpilot_add_4byte(buf, len, data->AccelKi);
	len = openpilot_add_4byte(buf, len, data->AccelTau);
	len = openpilot_add_4byte(buf, len, data->VertPositionTau);
	len = openpilot_add_4byte(buf, len, data->YawBiasRate);
	len = openpilot_add_2byte(buf, len, data->BoardRotation.Roll);
	len = openpilot_add_2byte(buf, len, data->BoardRotation.Pitch);
	len = openpilot_add_2byte(buf, len, data->BoardRotation.Yaw);
	len = openpilot_add_1byte(buf, len, data->ZeroDuringArming);
	len = openpilot_add_1byte(buf, len, data->BiasCorrectGyro);
	len = openpilot_add_1byte(buf, len, data->FilterChoice);
	len = openpilot_add_1byte(buf, len, data->TrimFlight);
	uavtalk_send(ModelActive, buf, ATTITUDESETTINGS_OBJID, 0x22, len);
}


void UAVT_AttitudeSimulated_Send (UAVT_AttitudeSimulatedData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->q1);
	len = openpilot_add_4byte(buf, len, data->q2);
	len = openpilot_add_4byte(buf, len, data->q3);
	len = openpilot_add_4byte(buf, len, data->q4);
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	len = openpilot_add_4byte(buf, len, data->Velocity.North);
	len = openpilot_add_4byte(buf, len, data->Velocity.East);
	len = openpilot_add_4byte(buf, len, data->Velocity.Down);
	len = openpilot_add_4byte(buf, len, data->Position.North);
	len = openpilot_add_4byte(buf, len, data->Position.East);
	len = openpilot_add_4byte(buf, len, data->Position.Down);
	uavtalk_send(ModelActive, buf, ATTITUDESIMULATED_OBJID, 0x22, len);
}


void UAVT_BaroAirspeed_Send (UAVT_BaroAirspeedData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->CalibratedAirspeed);
	len = openpilot_add_4byte(buf, len, data->GPSAirspeed);
	len = openpilot_add_4byte(buf, len, data->TrueAirspeed);
	len = openpilot_add_2byte(buf, len, data->SensorValue);
	len = openpilot_add_1byte(buf, len, data->BaroConnected);
	uavtalk_send(ModelActive, buf, BAROAIRSPEED_OBJID, 0x22, len);
}


void UAVT_BaroAltitude_Send (UAVT_BaroAltitudeData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Altitude);
	len = openpilot_add_4byte(buf, len, data->Temperature);
	len = openpilot_add_4byte(buf, len, data->Pressure);
	uavtalk_send(ModelActive, buf, BAROALTITUDE_OBJID, 0x22, len);
}


void UAVT_BrushlessGimbalSettings_Send (UAVT_BrushlessGimbalSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Damping.Roll);
	len = openpilot_add_4byte(buf, len, data->Damping.Pitch);
	len = openpilot_add_4byte(buf, len, data->Damping.Yaw);
	len = openpilot_add_2byte(buf, len, data->MaxDPS.Roll);
	len = openpilot_add_2byte(buf, len, data->MaxDPS.Pitch);
	len = openpilot_add_2byte(buf, len, data->MaxDPS.Yaw);
	len = openpilot_add_2byte(buf, len, data->SlewLimit.Roll);
	len = openpilot_add_2byte(buf, len, data->SlewLimit.Pitch);
	len = openpilot_add_2byte(buf, len, data->SlewLimit.Yaw);
	len = openpilot_add_1byte(buf, len, data->PowerScale.Roll);
	len = openpilot_add_1byte(buf, len, data->PowerScale.Pitch);
	len = openpilot_add_1byte(buf, len, data->PowerScale.Yaw);
	len = openpilot_add_1byte(buf, len, data->MaxAngle.Roll);
	len = openpilot_add_1byte(buf, len, data->MaxAngle.Pitch);
	len = openpilot_add_1byte(buf, len, data->MaxAngle.Yaw);
	len = openpilot_add_1byte(buf, len, data->RollFraction);
	len = openpilot_add_1byte(buf, len, data->PowerupSequence);
	uavtalk_send(ModelActive, buf, BRUSHLESSGIMBALSETTINGS_OBJID, 0x22, len);
}


void UAVT_CameraDesired_Send (UAVT_CameraDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	len = openpilot_add_4byte(buf, len, data->Bearing);
	len = openpilot_add_4byte(buf, len, data->Declination);
	uavtalk_send(ModelActive, buf, CAMERADESIRED_OBJID, 0x22, len);
}


void UAVT_CameraStabSettings_Send (UAVT_CameraStabSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->MaxAxisLockRate);
	len = openpilot_add_4byte(buf, len, data->MaxAccel);
	len = openpilot_add_1byte(buf, len, data->Input.Roll);
	len = openpilot_add_1byte(buf, len, data->Input.Pitch);
	len = openpilot_add_1byte(buf, len, data->Input.Yaw);
	len = openpilot_add_1byte(buf, len, data->InputRange.Roll);
	len = openpilot_add_1byte(buf, len, data->InputRange.Pitch);
	len = openpilot_add_1byte(buf, len, data->InputRange.Yaw);
	len = openpilot_add_1byte(buf, len, data->InputRate.Roll);
	len = openpilot_add_1byte(buf, len, data->InputRate.Pitch);
	len = openpilot_add_1byte(buf, len, data->InputRate.Yaw);
	len = openpilot_add_1byte(buf, len, data->OutputRange.Roll);
	len = openpilot_add_1byte(buf, len, data->OutputRange.Pitch);
	len = openpilot_add_1byte(buf, len, data->OutputRange.Yaw);
	len = openpilot_add_1byte(buf, len, data->FeedForward.Roll);
	len = openpilot_add_1byte(buf, len, data->FeedForward.Pitch);
	len = openpilot_add_1byte(buf, len, data->FeedForward.Yaw);
	len = openpilot_add_1byte(buf, len, data->StabilizationMode.Roll);
	len = openpilot_add_1byte(buf, len, data->StabilizationMode.Pitch);
	len = openpilot_add_1byte(buf, len, data->StabilizationMode.Yaw);
	len = openpilot_add_1byte(buf, len, data->AttitudeFilter);
	len = openpilot_add_1byte(buf, len, data->InputFilter);
	len = openpilot_add_1byte(buf, len, data->FeedForwardTime);
	uavtalk_send(ModelActive, buf, CAMERASTABSETTINGS_OBJID, 0x22, len);
}


void UAVT_FaultSettings_Send (UAVT_FaultSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->ActivateFault);
	uavtalk_send(ModelActive, buf, FAULTSETTINGS_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, FIRMWAREIAPOBJ_OBJID, 0x22, len);
}


void UAVT_FixedWingAirspeeds_Send (UAVT_FixedWingAirspeedsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->AirSpeedMax);
	len = openpilot_add_4byte(buf, len, data->CruiseSpeed);
	len = openpilot_add_4byte(buf, len, data->BestClimbRateSpeed);
	len = openpilot_add_4byte(buf, len, data->StallSpeedClean);
	len = openpilot_add_4byte(buf, len, data->StallSpeedDirty);
	len = openpilot_add_4byte(buf, len, data->VerticalVelMax);
	uavtalk_send(ModelActive, buf, FIXEDWINGAIRSPEEDS_OBJID, 0x22, len);
}


void UAVT_FixedWingPathFollowerSettingsCC_Send (UAVT_FixedWingPathFollowerSettingsCCData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->VerticalVelMax);
	len = openpilot_add_4byte(buf, len, data->VectorFollowingGain);
	len = openpilot_add_4byte(buf, len, data->OrbitFollowingGain);
	len = openpilot_add_4byte(buf, len, data->FollowerIntegralGain);
	len = openpilot_add_4byte(buf, len, data->VerticalPosP);
	len = openpilot_add_4byte(buf, len, data->HeadingPI[0]);
	len = openpilot_add_4byte(buf, len, data->HeadingPI[1]);
	len = openpilot_add_4byte(buf, len, data->HeadingPI[2]);
	len = openpilot_add_4byte(buf, len, data->AirspeedPI[0]);
	len = openpilot_add_4byte(buf, len, data->AirspeedPI[1]);
	len = openpilot_add_4byte(buf, len, data->AirspeedPI[2]);
	len = openpilot_add_4byte(buf, len, data->VerticalToPitchCrossFeed.Kp);
	len = openpilot_add_4byte(buf, len, data->VerticalToPitchCrossFeed.Max);
	len = openpilot_add_4byte(buf, len, data->AirspeedToVerticalCrossFeed.Kp);
	len = openpilot_add_4byte(buf, len, data->AirspeedToVerticalCrossFeed.Max);
	len = openpilot_add_4byte(buf, len, data->ThrottlePI[0]);
	len = openpilot_add_4byte(buf, len, data->ThrottlePI[1]);
	len = openpilot_add_4byte(buf, len, data->ThrottlePI[2]);
	len = openpilot_add_4byte(buf, len, data->RollLimit[0]);
	len = openpilot_add_4byte(buf, len, data->RollLimit[1]);
	len = openpilot_add_4byte(buf, len, data->RollLimit[2]);
	len = openpilot_add_4byte(buf, len, data->PitchLimit[0]);
	len = openpilot_add_4byte(buf, len, data->PitchLimit[1]);
	len = openpilot_add_4byte(buf, len, data->PitchLimit[2]);
	len = openpilot_add_4byte(buf, len, data->ThrottleLimit[0]);
	len = openpilot_add_4byte(buf, len, data->ThrottleLimit[1]);
	len = openpilot_add_4byte(buf, len, data->ThrottleLimit[2]);
	len = openpilot_add_2byte(buf, len, data->UpdatePeriod);
	uavtalk_send(ModelActive, buf, FIXEDWINGPATHFOLLOWERSETTINGSCC_OBJID, 0x22, len);
}


void UAVT_FixedWingPathFollowerSettings_Send (UAVT_FixedWingPathFollowerSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->HorizontalPosP);
	len = openpilot_add_4byte(buf, len, data->VerticalPosP);
	len = openpilot_add_4byte(buf, len, data->BearingPI[0]);
	len = openpilot_add_4byte(buf, len, data->BearingPI[1]);
	len = openpilot_add_4byte(buf, len, data->BearingPI[2]);
	len = openpilot_add_4byte(buf, len, data->PowerPI[0]);
	len = openpilot_add_4byte(buf, len, data->PowerPI[1]);
	len = openpilot_add_4byte(buf, len, data->PowerPI[2]);
	len = openpilot_add_4byte(buf, len, data->VerticalToPitchCrossFeed.Kp);
	len = openpilot_add_4byte(buf, len, data->VerticalToPitchCrossFeed.Max);
	len = openpilot_add_4byte(buf, len, data->AirspeedToVerticalCrossFeed.Kp);
	len = openpilot_add_4byte(buf, len, data->AirspeedToVerticalCrossFeed.Max);
	len = openpilot_add_4byte(buf, len, data->SpeedPI[0]);
	len = openpilot_add_4byte(buf, len, data->SpeedPI[1]);
	len = openpilot_add_4byte(buf, len, data->SpeedPI[2]);
	len = openpilot_add_4byte(buf, len, data->RollLimit[0]);
	len = openpilot_add_4byte(buf, len, data->RollLimit[1]);
	len = openpilot_add_4byte(buf, len, data->RollLimit[2]);
	len = openpilot_add_4byte(buf, len, data->PitchLimit[0]);
	len = openpilot_add_4byte(buf, len, data->PitchLimit[1]);
	len = openpilot_add_4byte(buf, len, data->PitchLimit[2]);
	len = openpilot_add_4byte(buf, len, data->ThrottleLimit[0]);
	len = openpilot_add_4byte(buf, len, data->ThrottleLimit[1]);
	len = openpilot_add_4byte(buf, len, data->ThrottleLimit[2]);
	len = openpilot_add_4byte(buf, len, data->OrbitRadius);
	len = openpilot_add_2byte(buf, len, data->UpdatePeriod);
	uavtalk_send(ModelActive, buf, FIXEDWINGPATHFOLLOWERSETTINGS_OBJID, 0x22, len);
}


void UAVT_FixedWingPathFollowerStatus_Send (UAVT_FixedWingPathFollowerStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Error.Bearing);
	len = openpilot_add_4byte(buf, len, data->Error.Speed);
	len = openpilot_add_4byte(buf, len, data->Error.Accel);
	len = openpilot_add_4byte(buf, len, data->Error.Power);
	len = openpilot_add_4byte(buf, len, data->ErrorInt.Bearing);
	len = openpilot_add_4byte(buf, len, data->ErrorInt.Speed);
	len = openpilot_add_4byte(buf, len, data->ErrorInt.Accel);
	len = openpilot_add_4byte(buf, len, data->ErrorInt.Power);
	len = openpilot_add_4byte(buf, len, data->Command.Bearing);
	len = openpilot_add_4byte(buf, len, data->Command.Speed);
	len = openpilot_add_4byte(buf, len, data->Command.Accel);
	len = openpilot_add_4byte(buf, len, data->Command.Power);
	len = openpilot_add_1byte(buf, len, data->Errors.Wind);
	len = openpilot_add_1byte(buf, len, data->Errors.Stallspeed);
	len = openpilot_add_1byte(buf, len, data->Errors.Lowspeed);
	len = openpilot_add_1byte(buf, len, data->Errors.Highspeed);
	len = openpilot_add_1byte(buf, len, data->Errors.Overspeed);
	len = openpilot_add_1byte(buf, len, data->Errors.Lowpower);
	len = openpilot_add_1byte(buf, len, data->Errors.Highpower);
	len = openpilot_add_1byte(buf, len, data->Errors.Pitchcontrol);
	uavtalk_send(ModelActive, buf, FIXEDWINGPATHFOLLOWERSTATUS_OBJID, 0x22, len);
}


void UAVT_FlightBatterySettings_Send (UAVT_FlightBatterySettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Capacity);
	len = openpilot_add_4byte(buf, len, data->VoltageThresholds.Warning);
	len = openpilot_add_4byte(buf, len, data->VoltageThresholds.Alarm);
	len = openpilot_add_4byte(buf, len, data->SensorCalibrationFactor.Voltage);
	len = openpilot_add_4byte(buf, len, data->SensorCalibrationFactor.Current);
	len = openpilot_add_4byte(buf, len, data->SensorCalibrationOffset.Voltage);
	len = openpilot_add_4byte(buf, len, data->SensorCalibrationOffset.Current);
	len = openpilot_add_1byte(buf, len, data->CurrentPin);
	len = openpilot_add_1byte(buf, len, data->VoltagePin);
	len = openpilot_add_1byte(buf, len, data->Type);
	len = openpilot_add_1byte(buf, len, data->NbCells);
	len = openpilot_add_1byte(buf, len, data->SensorType.BatteryCurrent);
	len = openpilot_add_1byte(buf, len, data->SensorType.BatteryVoltage);
	uavtalk_send(ModelActive, buf, FLIGHTBATTERYSETTINGS_OBJID, 0x22, len);
}


void UAVT_FlightPlanControl_Send (UAVT_FlightPlanControlData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->Command);
	uavtalk_send(ModelActive, buf, FLIGHTPLANCONTROL_OBJID, 0x22, len);
}


void UAVT_FlightPlanSettings_Send (UAVT_FlightPlanSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Test);
	uavtalk_send(ModelActive, buf, FLIGHTPLANSETTINGS_OBJID, 0x22, len);
}


void UAVT_FlightPlanStatus_Send (UAVT_FlightPlanStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->ErrorFileID);
	len = openpilot_add_4byte(buf, len, data->ErrorLineNum);
	len = openpilot_add_4byte(buf, len, data->Debug[0]);
	len = openpilot_add_4byte(buf, len, data->Debug[1]);
	len = openpilot_add_1byte(buf, len, data->State);
	len = openpilot_add_1byte(buf, len, data->ErrorType);
	uavtalk_send(ModelActive, buf, FLIGHTPLANSTATUS_OBJID, 0x22, len);
}


void UAVT_FlightStatus_Send (UAVT_FlightStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->Armed);
	len = openpilot_add_1byte(buf, len, data->FlightMode);
	len = openpilot_add_1byte(buf, len, data->ControlSource);
	uavtalk_send(ModelActive, buf, FLIGHTSTATUS_OBJID, 0x22, len);
}


void UAVT_FlightTelemetryStats_Send (UAVT_FlightTelemetryStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->TxDataRate);
	len = openpilot_add_4byte(buf, len, data->RxDataRate);
	len = openpilot_add_4byte(buf, len, data->TxFailures);
	len = openpilot_add_4byte(buf, len, data->RxFailures);
	len = openpilot_add_4byte(buf, len, data->TxRetries);
	len = openpilot_add_1byte(buf, len, data->State);
	uavtalk_send(ModelActive, buf, FLIGHTTELEMETRYSTATS_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, GCSRECEIVER_OBJID, 0x22, len);
}


void UAVT_GCSTelemetryStats_Send (UAVT_GCSTelemetryStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->TxDataRate);
	len = openpilot_add_4byte(buf, len, data->RxDataRate);
	len = openpilot_add_4byte(buf, len, data->TxFailures);
	len = openpilot_add_4byte(buf, len, data->RxFailures);
	len = openpilot_add_4byte(buf, len, data->TxRetries);
	len = openpilot_add_1byte(buf, len, data->State);
	uavtalk_send(ModelActive, buf, GCSTELEMETRYSTATS_OBJID, 0x22, len);
}


void UAVT_GeoFenceSettings_Send (UAVT_GeoFenceSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->WarningRadius);
	len = openpilot_add_2byte(buf, len, data->ErrorRadius);
	uavtalk_send(ModelActive, buf, GEOFENCESETTINGS_OBJID, 0x22, len);
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
	len = openpilot_add_1byte(buf, len, data->State);
	len = openpilot_add_1byte(buf, len, data->Satellites);
	uavtalk_send(ModelActive, buf, GPSPOSITION_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, GPSSATELLITES_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, GPSTIME_OBJID, 0x22, len);
}


void UAVT_GPSVelocity_Send (UAVT_GPSVelocityData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(ModelActive, buf, GPSVELOCITY_OBJID, 0x22, len);
}


void UAVT_GroundPathFollowerSettings_Send (UAVT_GroundPathFollowerSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->HorizontalPosPI.Kp);
	len = openpilot_add_4byte(buf, len, data->HorizontalPosPI.Ki);
	len = openpilot_add_4byte(buf, len, data->HorizontalPosPI.ILimit);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.Kp);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.Ki);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.Kd);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.ILimit);
	len = openpilot_add_4byte(buf, len, data->VelocityFeedforward);
	len = openpilot_add_4byte(buf, len, data->MaxThrottle);
	len = openpilot_add_4byte(buf, len, data->UpdatePeriod);
	len = openpilot_add_2byte(buf, len, data->HorizontalVelMax);
	len = openpilot_add_1byte(buf, len, data->ManualOverride);
	len = openpilot_add_1byte(buf, len, data->ThrottleControl);
	len = openpilot_add_1byte(buf, len, data->VelocitySource);
	len = openpilot_add_1byte(buf, len, data->PositionSource);
	len = openpilot_add_1byte(buf, len, data->EndpointRadius);
	uavtalk_send(ModelActive, buf, GROUNDPATHFOLLOWERSETTINGS_OBJID, 0x22, len);
}


void UAVT_GroundTruth_Send (UAVT_GroundTruthData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->AccelerationXYZ[0]);
	len = openpilot_add_4byte(buf, len, data->AccelerationXYZ[1]);
	len = openpilot_add_4byte(buf, len, data->AccelerationXYZ[2]);
	len = openpilot_add_4byte(buf, len, data->PositionNED[0]);
	len = openpilot_add_4byte(buf, len, data->PositionNED[1]);
	len = openpilot_add_4byte(buf, len, data->PositionNED[2]);
	len = openpilot_add_4byte(buf, len, data->VelocityNED[0]);
	len = openpilot_add_4byte(buf, len, data->VelocityNED[1]);
	len = openpilot_add_4byte(buf, len, data->VelocityNED[2]);
	len = openpilot_add_4byte(buf, len, data->RPY[0]);
	len = openpilot_add_4byte(buf, len, data->RPY[1]);
	len = openpilot_add_4byte(buf, len, data->RPY[2]);
	len = openpilot_add_4byte(buf, len, data->AngularRates[0]);
	len = openpilot_add_4byte(buf, len, data->AngularRates[1]);
	len = openpilot_add_4byte(buf, len, data->AngularRates[2]);
	len = openpilot_add_4byte(buf, len, data->TrueAirspeed);
	len = openpilot_add_4byte(buf, len, data->CalibratedAirspeed);
	len = openpilot_add_4byte(buf, len, data->AngleOfAttack);
	len = openpilot_add_4byte(buf, len, data->AngleOfSlip);
	uavtalk_send(ModelActive, buf, GROUNDTRUTH_OBJID, 0x22, len);
}


void UAVT_GyrosBias_Send (UAVT_GyrosBiasData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	uavtalk_send(ModelActive, buf, GYROSBIAS_OBJID, 0x22, len);
}


void UAVT_Gyros_Send (UAVT_GyrosData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	len = openpilot_add_4byte(buf, len, data->temperature);
	uavtalk_send(ModelActive, buf, GYROS_OBJID, 0x22, len);
}


void UAVT_HomeLocation_Send (UAVT_HomeLocationData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Latitude);
	len = openpilot_add_4byte(buf, len, data->Longitude);
	len = openpilot_add_4byte(buf, len, data->Altitude);
	len = openpilot_add_4byte(buf, len, data->Be[0]);
	len = openpilot_add_4byte(buf, len, data->Be[1]);
	len = openpilot_add_4byte(buf, len, data->Be[2]);
	len = openpilot_add_2byte(buf, len, data->GroundTemperature);
	len = openpilot_add_2byte(buf, len, data->SeaLevelPressure);
	len = openpilot_add_1byte(buf, len, data->Set);
	uavtalk_send(ModelActive, buf, HOMELOCATION_OBJID, 0x22, len);
}


void UAVT_HoTTSettings_Send (UAVT_HoTTSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Limit.MinSpeed);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxSpeed);
	len = openpilot_add_4byte(buf, len, data->Limit.NegDifference1);
	len = openpilot_add_4byte(buf, len, data->Limit.PosDifference1);
	len = openpilot_add_4byte(buf, len, data->Limit.NegDifference2);
	len = openpilot_add_4byte(buf, len, data->Limit.PosDifference2);
	len = openpilot_add_4byte(buf, len, data->Limit.MinHeight);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxHeight);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxDistance);
	len = openpilot_add_4byte(buf, len, data->Limit.MinPowerVoltage);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxPowerVoltage);
	len = openpilot_add_4byte(buf, len, data->Limit.MinSensor1Voltage);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxSensor1Voltage);
	len = openpilot_add_4byte(buf, len, data->Limit.MinSensor2Voltage);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxSensor2Voltage);
	len = openpilot_add_4byte(buf, len, data->Limit.MinCellVoltage);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxCurrent);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxUsedCapacity);
	len = openpilot_add_4byte(buf, len, data->Limit.MinSensor1Temp);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxSensor1Temp);
	len = openpilot_add_4byte(buf, len, data->Limit.MinSensor2Temp);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxSensor2Temp);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxServoTemp);
	len = openpilot_add_4byte(buf, len, data->Limit.MinRPM);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxRPM);
	len = openpilot_add_4byte(buf, len, data->Limit.MinFuel);
	len = openpilot_add_4byte(buf, len, data->Limit.MaxServoDifference);
	len = openpilot_add_1byte(buf, len, data->Sensor.VARIO);
	len = openpilot_add_1byte(buf, len, data->Sensor.GPS);
	len = openpilot_add_1byte(buf, len, data->Sensor.EAM);
	len = openpilot_add_1byte(buf, len, data->Sensor.GAM);
	len = openpilot_add_1byte(buf, len, data->Sensor.ESC);
	len = openpilot_add_1byte(buf, len, data->Warning.AltitudeBeep);
	len = openpilot_add_1byte(buf, len, data->Warning.MinSpeed);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxSpeed);
	len = openpilot_add_1byte(buf, len, data->Warning.NegDifference1);
	len = openpilot_add_1byte(buf, len, data->Warning.PosDifference1);
	len = openpilot_add_1byte(buf, len, data->Warning.NegDifference2);
	len = openpilot_add_1byte(buf, len, data->Warning.PosDifference2);
	len = openpilot_add_1byte(buf, len, data->Warning.MinHeight);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxHeight);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxDistance);
	len = openpilot_add_1byte(buf, len, data->Warning.MinPowerVoltage);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxPowerVoltage);
	len = openpilot_add_1byte(buf, len, data->Warning.MinSensor1Voltage);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxSensor1Voltage);
	len = openpilot_add_1byte(buf, len, data->Warning.MinSensor2Voltage);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxSensor2Voltage);
	len = openpilot_add_1byte(buf, len, data->Warning.MinCellVoltage);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxCurrent);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxUsedCapacity);
	len = openpilot_add_1byte(buf, len, data->Warning.MinSensor1Temp);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxSensor1Temp);
	len = openpilot_add_1byte(buf, len, data->Warning.MinSensor2Temp);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxSensor2Temp);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxServoTemp);
	len = openpilot_add_1byte(buf, len, data->Warning.MinRPM);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxRPM);
	len = openpilot_add_1byte(buf, len, data->Warning.MinFuel);
	len = openpilot_add_1byte(buf, len, data->Warning.MaxServoDifference);
	uavtalk_send(ModelActive, buf, HOTTSETTINGS_OBJID, 0x22, len);
}


void UAVT_HwColibri_Send (UAVT_HwColibriData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->Frame);
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->Uart1);
	len = openpilot_add_1byte(buf, len, data->Uart2);
	len = openpilot_add_1byte(buf, len, data->Uart3);
	len = openpilot_add_1byte(buf, len, data->Uart4);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->MPU6000Rate);
	len = openpilot_add_1byte(buf, len, data->MPU6000DLPF);
	len = openpilot_add_1byte(buf, len, data->Magnetometer);
	len = openpilot_add_1byte(buf, len, data->ExtMagOrientation);
	uavtalk_send(ModelActive, buf, HWCOLIBRI_OBJID, 0x22, len);
}


void UAVT_HwCopterControl_Send (UAVT_HwCopterControlData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->MainPort);
	len = openpilot_add_1byte(buf, len, data->FlexiPort);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->MPU6000Rate);
	len = openpilot_add_1byte(buf, len, data->MPU6000DLPF);
	uavtalk_send(ModelActive, buf, HWCOPTERCONTROL_OBJID, 0x22, len);
}


void UAVT_HwDiscoveryF4_Send (UAVT_HwDiscoveryF4Data *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->MainPort);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	uavtalk_send(ModelActive, buf, HWDISCOVERYF4_OBJID, 0x22, len);
}


void UAVT_HwFlyingF3_Send (UAVT_HwFlyingF3Data *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->Uart1);
	len = openpilot_add_1byte(buf, len, data->Uart2);
	len = openpilot_add_1byte(buf, len, data->Uart3);
	len = openpilot_add_1byte(buf, len, data->Uart4);
	len = openpilot_add_1byte(buf, len, data->Uart5);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->L3GD20Rate);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->Shield);
	uavtalk_send(ModelActive, buf, HWFLYINGF3_OBJID, 0x22, len);
}


void UAVT_HwFlyingF4_Send (UAVT_HwFlyingF4Data *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->Uart1);
	len = openpilot_add_1byte(buf, len, data->Uart2);
	len = openpilot_add_1byte(buf, len, data->Uart3);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->MPU6050Rate);
	len = openpilot_add_1byte(buf, len, data->MPU6050DLPF);
	len = openpilot_add_1byte(buf, len, data->Magnetometer);
	len = openpilot_add_1byte(buf, len, data->ExtMagOrientation);
	uavtalk_send(ModelActive, buf, HWFLYINGF4_OBJID, 0x22, len);
}


void UAVT_HwFreedom_Send (UAVT_HwFreedomData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->Output);
	len = openpilot_add_1byte(buf, len, data->MainPort);
	len = openpilot_add_1byte(buf, len, data->FlexiPort);
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->RadioPort);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->MPU6000Rate);
	len = openpilot_add_1byte(buf, len, data->MPU6000DLPF);
	uavtalk_send(ModelActive, buf, HWFREEDOM_OBJID, 0x22, len);
}


void UAVT_HwQuanton_Send (UAVT_HwQuantonData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->Uart1);
	len = openpilot_add_1byte(buf, len, data->Uart2);
	len = openpilot_add_1byte(buf, len, data->Uart3);
	len = openpilot_add_1byte(buf, len, data->Uart4);
	len = openpilot_add_1byte(buf, len, data->Uart5);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->MPU6000Rate);
	len = openpilot_add_1byte(buf, len, data->MPU6000DLPF);
	len = openpilot_add_1byte(buf, len, data->Magnetometer);
	len = openpilot_add_1byte(buf, len, data->ExtMagOrientation);
	uavtalk_send(ModelActive, buf, HWQUANTON_OBJID, 0x22, len);
}


void UAVT_HwRevolution_Send (UAVT_HwRevolutionData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->AuxPort);
	len = openpilot_add_1byte(buf, len, data->AuxSBusPort);
	len = openpilot_add_1byte(buf, len, data->FlexiPort);
	len = openpilot_add_1byte(buf, len, data->TelemetryPort);
	len = openpilot_add_1byte(buf, len, data->GPSPort);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->MPU6000Rate);
	len = openpilot_add_1byte(buf, len, data->MPU6000DLPF);
	uavtalk_send(ModelActive, buf, HWREVOLUTION_OBJID, 0x22, len);
}


void UAVT_HwRevoMini_Send (UAVT_HwRevoMiniData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->MainPort);
	len = openpilot_add_1byte(buf, len, data->FlexiPort);
	len = openpilot_add_1byte(buf, len, data->RadioPort);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->MPU6000Rate);
	len = openpilot_add_1byte(buf, len, data->MPU6000DLPF);
	uavtalk_send(ModelActive, buf, HWREVOMINI_OBJID, 0x22, len);
}


void UAVT_HwSparkyBGC_Send (UAVT_HwSparkyBGCData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->FlexiPort);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->MPU9150DLPF);
	len = openpilot_add_1byte(buf, len, data->MPU9150Rate);
	uavtalk_send(ModelActive, buf, HWSPARKYBGC_OBJID, 0x22, len);
}


void UAVT_HwSparky_Send (UAVT_HwSparkyData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->RcvrPort);
	len = openpilot_add_1byte(buf, len, data->FlexiPort);
	len = openpilot_add_1byte(buf, len, data->MainPort);
	len = openpilot_add_1byte(buf, len, data->OutPort);
	len = openpilot_add_1byte(buf, len, data->USB_HIDPort);
	len = openpilot_add_1byte(buf, len, data->USB_VCPPort);
	len = openpilot_add_1byte(buf, len, data->DSMxBind);
	len = openpilot_add_1byte(buf, len, data->GyroRange);
	len = openpilot_add_1byte(buf, len, data->AccelRange);
	len = openpilot_add_1byte(buf, len, data->MPU9150DLPF);
	len = openpilot_add_1byte(buf, len, data->MPU9150Rate);
	uavtalk_send(ModelActive, buf, HWSPARKY_OBJID, 0x22, len);
}


void UAVT_I2CVMUserProgram_Send (UAVT_I2CVMUserProgramData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Program[0]);
	len = openpilot_add_4byte(buf, len, data->Program[1]);
	len = openpilot_add_4byte(buf, len, data->Program[2]);
	len = openpilot_add_4byte(buf, len, data->Program[3]);
	len = openpilot_add_4byte(buf, len, data->Program[4]);
	len = openpilot_add_4byte(buf, len, data->Program[5]);
	len = openpilot_add_4byte(buf, len, data->Program[6]);
	len = openpilot_add_4byte(buf, len, data->Program[7]);
	len = openpilot_add_4byte(buf, len, data->Program[8]);
	len = openpilot_add_4byte(buf, len, data->Program[9]);
	len = openpilot_add_4byte(buf, len, data->Program[10]);
	len = openpilot_add_4byte(buf, len, data->Program[11]);
	len = openpilot_add_4byte(buf, len, data->Program[12]);
	len = openpilot_add_4byte(buf, len, data->Program[13]);
	len = openpilot_add_4byte(buf, len, data->Program[14]);
	len = openpilot_add_4byte(buf, len, data->Program[15]);
	len = openpilot_add_4byte(buf, len, data->Program[16]);
	len = openpilot_add_4byte(buf, len, data->Program[17]);
	len = openpilot_add_4byte(buf, len, data->Program[18]);
	len = openpilot_add_4byte(buf, len, data->Program[19]);
	uavtalk_send(ModelActive, buf, I2CVMUSERPROGRAM_OBJID, 0x22, len);
}


void UAVT_INSSettings_Send (UAVT_INSSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->accel_var.X);
	len = openpilot_add_4byte(buf, len, data->accel_var.Y);
	len = openpilot_add_4byte(buf, len, data->accel_var.Z);
	len = openpilot_add_4byte(buf, len, data->gyro_var.X);
	len = openpilot_add_4byte(buf, len, data->gyro_var.Y);
	len = openpilot_add_4byte(buf, len, data->gyro_var.Z);
	len = openpilot_add_4byte(buf, len, data->mag_var.X);
	len = openpilot_add_4byte(buf, len, data->mag_var.Y);
	len = openpilot_add_4byte(buf, len, data->mag_var.Z);
	len = openpilot_add_4byte(buf, len, data->gps_var.Pos);
	len = openpilot_add_4byte(buf, len, data->gps_var.Vel);
	len = openpilot_add_4byte(buf, len, data->gps_var.VertPos);
	len = openpilot_add_4byte(buf, len, data->baro_var);
	len = openpilot_add_4byte(buf, len, data->MagBiasNullingRate);
	len = openpilot_add_1byte(buf, len, data->ComputeGyroBias);
	uavtalk_send(ModelActive, buf, INSSETTINGS_OBJID, 0x22, len);
}


void UAVT_INSState_Send (UAVT_INSStateData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->State[0]);
	len = openpilot_add_4byte(buf, len, data->State[1]);
	len = openpilot_add_4byte(buf, len, data->State[2]);
	len = openpilot_add_4byte(buf, len, data->State[3]);
	len = openpilot_add_4byte(buf, len, data->State[4]);
	len = openpilot_add_4byte(buf, len, data->State[5]);
	len = openpilot_add_4byte(buf, len, data->State[6]);
	len = openpilot_add_4byte(buf, len, data->State[7]);
	len = openpilot_add_4byte(buf, len, data->State[8]);
	len = openpilot_add_4byte(buf, len, data->State[9]);
	len = openpilot_add_4byte(buf, len, data->State[10]);
	len = openpilot_add_4byte(buf, len, data->State[11]);
	len = openpilot_add_4byte(buf, len, data->State[12]);
	len = openpilot_add_4byte(buf, len, data->Var[0]);
	len = openpilot_add_4byte(buf, len, data->Var[1]);
	len = openpilot_add_4byte(buf, len, data->Var[2]);
	len = openpilot_add_4byte(buf, len, data->Var[3]);
	len = openpilot_add_4byte(buf, len, data->Var[4]);
	len = openpilot_add_4byte(buf, len, data->Var[5]);
	len = openpilot_add_4byte(buf, len, data->Var[6]);
	len = openpilot_add_4byte(buf, len, data->Var[7]);
	len = openpilot_add_4byte(buf, len, data->Var[8]);
	len = openpilot_add_4byte(buf, len, data->Var[9]);
	len = openpilot_add_4byte(buf, len, data->Var[10]);
	len = openpilot_add_4byte(buf, len, data->Var[11]);
	len = openpilot_add_4byte(buf, len, data->Var[12]);
	uavtalk_send(ModelActive, buf, INSSTATE_OBJID, 0x22, len);
}


void UAVT_LoggingSettings_Send (UAVT_LoggingSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->LogBehavior);
	uavtalk_send(ModelActive, buf, LOGGINGSETTINGS_OBJID, 0x22, len);
}


void UAVT_LoggingStats_Send (UAVT_LoggingStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->BytesLogged);
	len = openpilot_add_2byte(buf, len, data->MinFileId);
	len = openpilot_add_2byte(buf, len, data->MaxFileId);
	len = openpilot_add_2byte(buf, len, data->FileRequest);
	len = openpilot_add_2byte(buf, len, data->FileSectorNum);
	len = openpilot_add_1byte(buf, len, data->Operation);
	len = openpilot_add_1byte(buf, len, data->FileSector[0]);
	len = openpilot_add_1byte(buf, len, data->FileSector[1]);
	len = openpilot_add_1byte(buf, len, data->FileSector[2]);
	len = openpilot_add_1byte(buf, len, data->FileSector[3]);
	len = openpilot_add_1byte(buf, len, data->FileSector[4]);
	len = openpilot_add_1byte(buf, len, data->FileSector[5]);
	len = openpilot_add_1byte(buf, len, data->FileSector[6]);
	len = openpilot_add_1byte(buf, len, data->FileSector[7]);
	len = openpilot_add_1byte(buf, len, data->FileSector[8]);
	len = openpilot_add_1byte(buf, len, data->FileSector[9]);
	len = openpilot_add_1byte(buf, len, data->FileSector[10]);
	len = openpilot_add_1byte(buf, len, data->FileSector[11]);
	len = openpilot_add_1byte(buf, len, data->FileSector[12]);
	len = openpilot_add_1byte(buf, len, data->FileSector[13]);
	len = openpilot_add_1byte(buf, len, data->FileSector[14]);
	len = openpilot_add_1byte(buf, len, data->FileSector[15]);
	len = openpilot_add_1byte(buf, len, data->FileSector[16]);
	len = openpilot_add_1byte(buf, len, data->FileSector[17]);
	len = openpilot_add_1byte(buf, len, data->FileSector[18]);
	len = openpilot_add_1byte(buf, len, data->FileSector[19]);
	len = openpilot_add_1byte(buf, len, data->FileSector[20]);
	len = openpilot_add_1byte(buf, len, data->FileSector[21]);
	len = openpilot_add_1byte(buf, len, data->FileSector[22]);
	len = openpilot_add_1byte(buf, len, data->FileSector[23]);
	len = openpilot_add_1byte(buf, len, data->FileSector[24]);
	len = openpilot_add_1byte(buf, len, data->FileSector[25]);
	len = openpilot_add_1byte(buf, len, data->FileSector[26]);
	len = openpilot_add_1byte(buf, len, data->FileSector[27]);
	len = openpilot_add_1byte(buf, len, data->FileSector[28]);
	len = openpilot_add_1byte(buf, len, data->FileSector[29]);
	len = openpilot_add_1byte(buf, len, data->FileSector[30]);
	len = openpilot_add_1byte(buf, len, data->FileSector[31]);
	len = openpilot_add_1byte(buf, len, data->FileSector[32]);
	len = openpilot_add_1byte(buf, len, data->FileSector[33]);
	len = openpilot_add_1byte(buf, len, data->FileSector[34]);
	len = openpilot_add_1byte(buf, len, data->FileSector[35]);
	len = openpilot_add_1byte(buf, len, data->FileSector[36]);
	len = openpilot_add_1byte(buf, len, data->FileSector[37]);
	len = openpilot_add_1byte(buf, len, data->FileSector[38]);
	len = openpilot_add_1byte(buf, len, data->FileSector[39]);
	len = openpilot_add_1byte(buf, len, data->FileSector[40]);
	len = openpilot_add_1byte(buf, len, data->FileSector[41]);
	len = openpilot_add_1byte(buf, len, data->FileSector[42]);
	len = openpilot_add_1byte(buf, len, data->FileSector[43]);
	len = openpilot_add_1byte(buf, len, data->FileSector[44]);
	len = openpilot_add_1byte(buf, len, data->FileSector[45]);
	len = openpilot_add_1byte(buf, len, data->FileSector[46]);
	len = openpilot_add_1byte(buf, len, data->FileSector[47]);
	len = openpilot_add_1byte(buf, len, data->FileSector[48]);
	len = openpilot_add_1byte(buf, len, data->FileSector[49]);
	len = openpilot_add_1byte(buf, len, data->FileSector[50]);
	len = openpilot_add_1byte(buf, len, data->FileSector[51]);
	len = openpilot_add_1byte(buf, len, data->FileSector[52]);
	len = openpilot_add_1byte(buf, len, data->FileSector[53]);
	len = openpilot_add_1byte(buf, len, data->FileSector[54]);
	len = openpilot_add_1byte(buf, len, data->FileSector[55]);
	len = openpilot_add_1byte(buf, len, data->FileSector[56]);
	len = openpilot_add_1byte(buf, len, data->FileSector[57]);
	len = openpilot_add_1byte(buf, len, data->FileSector[58]);
	len = openpilot_add_1byte(buf, len, data->FileSector[59]);
	len = openpilot_add_1byte(buf, len, data->FileSector[60]);
	len = openpilot_add_1byte(buf, len, data->FileSector[61]);
	len = openpilot_add_1byte(buf, len, data->FileSector[62]);
	len = openpilot_add_1byte(buf, len, data->FileSector[63]);
	len = openpilot_add_1byte(buf, len, data->FileSector[64]);
	len = openpilot_add_1byte(buf, len, data->FileSector[65]);
	len = openpilot_add_1byte(buf, len, data->FileSector[66]);
	len = openpilot_add_1byte(buf, len, data->FileSector[67]);
	len = openpilot_add_1byte(buf, len, data->FileSector[68]);
	len = openpilot_add_1byte(buf, len, data->FileSector[69]);
	len = openpilot_add_1byte(buf, len, data->FileSector[70]);
	len = openpilot_add_1byte(buf, len, data->FileSector[71]);
	len = openpilot_add_1byte(buf, len, data->FileSector[72]);
	len = openpilot_add_1byte(buf, len, data->FileSector[73]);
	len = openpilot_add_1byte(buf, len, data->FileSector[74]);
	len = openpilot_add_1byte(buf, len, data->FileSector[75]);
	len = openpilot_add_1byte(buf, len, data->FileSector[76]);
	len = openpilot_add_1byte(buf, len, data->FileSector[77]);
	len = openpilot_add_1byte(buf, len, data->FileSector[78]);
	len = openpilot_add_1byte(buf, len, data->FileSector[79]);
	len = openpilot_add_1byte(buf, len, data->FileSector[80]);
	len = openpilot_add_1byte(buf, len, data->FileSector[81]);
	len = openpilot_add_1byte(buf, len, data->FileSector[82]);
	len = openpilot_add_1byte(buf, len, data->FileSector[83]);
	len = openpilot_add_1byte(buf, len, data->FileSector[84]);
	len = openpilot_add_1byte(buf, len, data->FileSector[85]);
	len = openpilot_add_1byte(buf, len, data->FileSector[86]);
	len = openpilot_add_1byte(buf, len, data->FileSector[87]);
	len = openpilot_add_1byte(buf, len, data->FileSector[88]);
	len = openpilot_add_1byte(buf, len, data->FileSector[89]);
	len = openpilot_add_1byte(buf, len, data->FileSector[90]);
	len = openpilot_add_1byte(buf, len, data->FileSector[91]);
	len = openpilot_add_1byte(buf, len, data->FileSector[92]);
	len = openpilot_add_1byte(buf, len, data->FileSector[93]);
	len = openpilot_add_1byte(buf, len, data->FileSector[94]);
	len = openpilot_add_1byte(buf, len, data->FileSector[95]);
	len = openpilot_add_1byte(buf, len, data->FileSector[96]);
	len = openpilot_add_1byte(buf, len, data->FileSector[97]);
	len = openpilot_add_1byte(buf, len, data->FileSector[98]);
	len = openpilot_add_1byte(buf, len, data->FileSector[99]);
	len = openpilot_add_1byte(buf, len, data->FileSector[100]);
	len = openpilot_add_1byte(buf, len, data->FileSector[101]);
	len = openpilot_add_1byte(buf, len, data->FileSector[102]);
	len = openpilot_add_1byte(buf, len, data->FileSector[103]);
	len = openpilot_add_1byte(buf, len, data->FileSector[104]);
	len = openpilot_add_1byte(buf, len, data->FileSector[105]);
	len = openpilot_add_1byte(buf, len, data->FileSector[106]);
	len = openpilot_add_1byte(buf, len, data->FileSector[107]);
	len = openpilot_add_1byte(buf, len, data->FileSector[108]);
	len = openpilot_add_1byte(buf, len, data->FileSector[109]);
	len = openpilot_add_1byte(buf, len, data->FileSector[110]);
	len = openpilot_add_1byte(buf, len, data->FileSector[111]);
	len = openpilot_add_1byte(buf, len, data->FileSector[112]);
	len = openpilot_add_1byte(buf, len, data->FileSector[113]);
	len = openpilot_add_1byte(buf, len, data->FileSector[114]);
	len = openpilot_add_1byte(buf, len, data->FileSector[115]);
	len = openpilot_add_1byte(buf, len, data->FileSector[116]);
	len = openpilot_add_1byte(buf, len, data->FileSector[117]);
	len = openpilot_add_1byte(buf, len, data->FileSector[118]);
	len = openpilot_add_1byte(buf, len, data->FileSector[119]);
	len = openpilot_add_1byte(buf, len, data->FileSector[120]);
	len = openpilot_add_1byte(buf, len, data->FileSector[121]);
	len = openpilot_add_1byte(buf, len, data->FileSector[122]);
	len = openpilot_add_1byte(buf, len, data->FileSector[123]);
	len = openpilot_add_1byte(buf, len, data->FileSector[124]);
	len = openpilot_add_1byte(buf, len, data->FileSector[125]);
	len = openpilot_add_1byte(buf, len, data->FileSector[126]);
	len = openpilot_add_1byte(buf, len, data->FileSector[127]);
	uavtalk_send(ModelActive, buf, LOGGINGSTATS_OBJID, 0x22, len);
}


void UAVT_LoiterCommand_Send (UAVT_LoiterCommandData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Forward);
	len = openpilot_add_4byte(buf, len, data->Right);
	len = openpilot_add_4byte(buf, len, data->Upwards);
	len = openpilot_add_1byte(buf, len, data->Frame);
	uavtalk_send(ModelActive, buf, LOITERCOMMAND_OBJID, 0x22, len);
}


void UAVT_MagBias_Send (UAVT_MagBiasData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	uavtalk_send(ModelActive, buf, MAGBIAS_OBJID, 0x22, len);
}


void UAVT_Magnetometer_Send (UAVT_MagnetometerData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	uavtalk_send(ModelActive, buf, MAGNETOMETER_OBJID, 0x22, len);
}


void UAVT_ManualControlCommand_Send (UAVT_ManualControlCommandData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Throttle);
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	len = openpilot_add_4byte(buf, len, data->RawRssi);
	len = openpilot_add_4byte(buf, len, data->Collective);
	len = openpilot_add_2byte(buf, len, data->Rssi);
	len = openpilot_add_2byte(buf, len, data->Channel.Throttle);
	len = openpilot_add_2byte(buf, len, data->Channel.Roll);
	len = openpilot_add_2byte(buf, len, data->Channel.Pitch);
	len = openpilot_add_2byte(buf, len, data->Channel.Yaw);
	len = openpilot_add_2byte(buf, len, data->Channel.FlightMode);
	len = openpilot_add_2byte(buf, len, data->Channel.Collective);
	len = openpilot_add_2byte(buf, len, data->Channel.Accessory0);
	len = openpilot_add_2byte(buf, len, data->Channel.Accessory1);
	len = openpilot_add_2byte(buf, len, data->Channel.Accessory2);
	len = openpilot_add_2byte(buf, len, data->Channel.Arming);
	len = openpilot_add_1byte(buf, len, data->Connected);
	uavtalk_send(ModelActive, buf, MANUALCONTROLCOMMAND_OBJID, 0x22, len);
}


void UAVT_ManualControlSettings_Send (UAVT_ManualControlSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Deadband);
	len = openpilot_add_2byte(buf, len, data->RssiMax);
	len = openpilot_add_2byte(buf, len, data->RssiMin);
	len = openpilot_add_2byte(buf, len, data->RssiPwmPeriod);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Throttle);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Roll);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Pitch);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Yaw);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.FlightMode);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Collective);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Accessory0);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Accessory1);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Accessory2);
	len = openpilot_add_2byte(buf, len, data->ChannelMin.Arming);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Throttle);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Roll);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Pitch);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Yaw);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.FlightMode);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Collective);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Accessory0);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Accessory1);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Accessory2);
	len = openpilot_add_2byte(buf, len, data->ChannelNeutral.Arming);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Throttle);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Roll);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Pitch);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Yaw);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.FlightMode);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Collective);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Accessory0);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Accessory1);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Accessory2);
	len = openpilot_add_2byte(buf, len, data->ChannelMax.Arming);
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
	len = openpilot_add_1byte(buf, len, data->ChannelGroups.Arming);
	len = openpilot_add_1byte(buf, len, data->RssiType);
	len = openpilot_add_1byte(buf, len, data->RssiChannelNumber);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Throttle);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Roll);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Pitch);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Yaw);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.FlightMode);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Collective);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Accessory0);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Accessory1);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Accessory2);
	len = openpilot_add_1byte(buf, len, data->ChannelNumber.Arming);
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
	uavtalk_send(ModelActive, buf, MANUALCONTROLSETTINGS_OBJID, 0x22, len);
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
	len = openpilot_add_1byte(buf, len, data->Mixer1Vector.ThrottleCurve1);
	len = openpilot_add_1byte(buf, len, data->Mixer1Vector.ThrottleCurve2);
	len = openpilot_add_1byte(buf, len, data->Mixer1Vector.Roll);
	len = openpilot_add_1byte(buf, len, data->Mixer1Vector.Pitch);
	len = openpilot_add_1byte(buf, len, data->Mixer1Vector.Yaw);
	uavtalk_send(ModelActive, buf, MIXERSETTINGS_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, MIXERSTATUS_OBJID, 0x22, len);
}


void UAVT_ModuleSettings_Send (UAVT_ModuleSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->AdminState.Airspeed);
	len = openpilot_add_1byte(buf, len, data->AdminState.AltitudeHold);
	len = openpilot_add_1byte(buf, len, data->AdminState.Autotune);
	len = openpilot_add_1byte(buf, len, data->AdminState.Battery);
	len = openpilot_add_1byte(buf, len, data->AdminState.CameraStab);
	len = openpilot_add_1byte(buf, len, data->AdminState.ComUsbBridge);
	len = openpilot_add_1byte(buf, len, data->AdminState.FixedWingPathFollower);
	len = openpilot_add_1byte(buf, len, data->AdminState.Fault);
	len = openpilot_add_1byte(buf, len, data->AdminState.GPS);
	len = openpilot_add_1byte(buf, len, data->AdminState.OveroSync);
	len = openpilot_add_1byte(buf, len, data->AdminState.PathPlanner);
	len = openpilot_add_1byte(buf, len, data->AdminState.TxPID);
	len = openpilot_add_1byte(buf, len, data->AdminState.VtolPathFollower);
	len = openpilot_add_1byte(buf, len, data->AdminState.GroundPathFollower);
	len = openpilot_add_1byte(buf, len, data->AdminState.GenericI2CSensor);
	len = openpilot_add_1byte(buf, len, data->AdminState.UAVOMavlinkBridge);
	len = openpilot_add_1byte(buf, len, data->AdminState.UAVOLighttelemetryBridge);
	len = openpilot_add_1byte(buf, len, data->AdminState.VibrationAnalysis);
	len = openpilot_add_1byte(buf, len, data->AdminState.UAVOHoTTBridge);
	len = openpilot_add_1byte(buf, len, data->AdminState.UAVOFrSKYSensorHubBridge);
	len = openpilot_add_1byte(buf, len, data->AdminState.PicoC);
	len = openpilot_add_1byte(buf, len, data->AdminState.UAVOFrSkySPortBridge);
	len = openpilot_add_1byte(buf, len, data->AdminState.Geofence);
	len = openpilot_add_1byte(buf, len, data->AdminState.Logging);
	len = openpilot_add_1byte(buf, len, data->TelemetrySpeed);
	len = openpilot_add_1byte(buf, len, data->GPSSpeed);
	len = openpilot_add_1byte(buf, len, data->GPSDataProtocol);
	len = openpilot_add_1byte(buf, len, data->GPSAutoConfigure);
	len = openpilot_add_1byte(buf, len, data->ComUsbBridgeSpeed);
	len = openpilot_add_1byte(buf, len, data->I2CVMProgramSelect);
	len = openpilot_add_1byte(buf, len, data->MavlinkSpeed);
	len = openpilot_add_1byte(buf, len, data->LightTelemetrySpeed);
	uavtalk_send(ModelActive, buf, MODULESETTINGS_OBJID, 0x22, len);
}


void UAVT_MWRateSettings_Send (UAVT_MWRateSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
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
	len = openpilot_add_4byte(buf, len, data->DerivativeGamma);
	len = openpilot_add_1byte(buf, len, data->RollPitchRate);
	len = openpilot_add_1byte(buf, len, data->YawRate);
	uavtalk_send(ModelActive, buf, MWRATESETTINGS_OBJID, 0x22, len);
}


void UAVT_NedAccel_Send (UAVT_NedAccelData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(ModelActive, buf, NEDACCEL_OBJID, 0x22, len);
}


void UAVT_NEDPosition_Send (UAVT_NEDPositionData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(ModelActive, buf, NEDPOSITION_OBJID, 0x22, len);
}


void UAVT_ObjectPersistence_Send (UAVT_ObjectPersistenceData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->ObjectID);
	len = openpilot_add_4byte(buf, len, data->InstanceID);
	len = openpilot_add_1byte(buf, len, data->Operation);
	len = openpilot_add_1byte(buf, len, data->Selection);
	uavtalk_send(ModelActive, buf, OBJECTPERSISTENCE_OBJID, 0x22, len);
}


void UAVT_OPLinkSettings_Send (UAVT_OPLinkSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->PairID);
	len = openpilot_add_4byte(buf, len, data->MinFrequency);
	len = openpilot_add_4byte(buf, len, data->MaxFrequency);
	len = openpilot_add_2byte(buf, len, data->SendTimeout);
	len = openpilot_add_1byte(buf, len, data->Coordinator);
	len = openpilot_add_1byte(buf, len, data->PPM);
	len = openpilot_add_1byte(buf, len, data->UAVTalk);
	len = openpilot_add_1byte(buf, len, data->InputConnection);
	len = openpilot_add_1byte(buf, len, data->OutputConnection);
	len = openpilot_add_1byte(buf, len, data->ComSpeed);
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
	uavtalk_send(ModelActive, buf, OPLINKSETTINGS_OBJID, 0x22, len);
}


void UAVT_OveroSyncSettings_Send (UAVT_OveroSyncSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->LogOn);
	uavtalk_send(ModelActive, buf, OVEROSYNCSETTINGS_OBJID, 0x22, len);
}


void UAVT_OveroSyncStats_Send (UAVT_OveroSyncStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Send);
	len = openpilot_add_4byte(buf, len, data->Received);
	len = openpilot_add_4byte(buf, len, data->FramesyncErrors);
	len = openpilot_add_4byte(buf, len, data->UnderrunErrors);
	len = openpilot_add_4byte(buf, len, data->DroppedUpdates);
	len = openpilot_add_4byte(buf, len, data->Packets);
	len = openpilot_add_1byte(buf, len, data->Connected);
	uavtalk_send(ModelActive, buf, OVEROSYNCSTATS_OBJID, 0x22, len);
}


void UAVT_PathDesired_Send (UAVT_PathDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Start.North);
	len = openpilot_add_4byte(buf, len, data->Start.East);
	len = openpilot_add_4byte(buf, len, data->Start.Down);
	len = openpilot_add_4byte(buf, len, data->End.North);
	len = openpilot_add_4byte(buf, len, data->End.East);
	len = openpilot_add_4byte(buf, len, data->End.Down);
	len = openpilot_add_4byte(buf, len, data->StartingVelocity);
	len = openpilot_add_4byte(buf, len, data->EndingVelocity);
	len = openpilot_add_4byte(buf, len, data->ModeParameters);
	len = openpilot_add_1byte(buf, len, data->Mode);
	uavtalk_send(ModelActive, buf, PATHDESIRED_OBJID, 0x22, len);
}


void UAVT_PathPlannerSettings_Send (UAVT_PathPlannerSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->PreprogrammedPath);
	len = openpilot_add_1byte(buf, len, data->FlashOperation);
	uavtalk_send(ModelActive, buf, PATHPLANNERSETTINGS_OBJID, 0x22, len);
}


void UAVT_PathStatus_Send (UAVT_PathStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->fractional_progress);
	len = openpilot_add_4byte(buf, len, data->error);
	len = openpilot_add_1byte(buf, len, data->State);
	uavtalk_send(ModelActive, buf, PATHSTATUS_OBJID, 0x22, len);
}


void UAVT_PicoCSettings_Send (UAVT_PicoCSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->MaxFileSize);
	len = openpilot_add_4byte(buf, len, data->TaskStackSize);
	len = openpilot_add_4byte(buf, len, data->PicoCStackSize);
	len = openpilot_add_1byte(buf, len, data->BootFileID);
	len = openpilot_add_1byte(buf, len, data->Startup);
	len = openpilot_add_1byte(buf, len, data->Source);
	len = openpilot_add_1byte(buf, len, data->ComSpeed);
	uavtalk_send(ModelActive, buf, PICOCSETTINGS_OBJID, 0x22, len);
}


void UAVT_PicoCStatus_Send (UAVT_PicoCStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->ExitValue);
	len = openpilot_add_2byte(buf, len, data->TestValue);
	len = openpilot_add_2byte(buf, len, data->SectorID);
	len = openpilot_add_1byte(buf, len, data->FileID);
	len = openpilot_add_1byte(buf, len, data->Command);
	len = openpilot_add_1byte(buf, len, data->CommandError);
	len = openpilot_add_1byte(buf, len, data->Sector[0]);
	len = openpilot_add_1byte(buf, len, data->Sector[1]);
	len = openpilot_add_1byte(buf, len, data->Sector[2]);
	len = openpilot_add_1byte(buf, len, data->Sector[3]);
	len = openpilot_add_1byte(buf, len, data->Sector[4]);
	len = openpilot_add_1byte(buf, len, data->Sector[5]);
	len = openpilot_add_1byte(buf, len, data->Sector[6]);
	len = openpilot_add_1byte(buf, len, data->Sector[7]);
	len = openpilot_add_1byte(buf, len, data->Sector[8]);
	len = openpilot_add_1byte(buf, len, data->Sector[9]);
	len = openpilot_add_1byte(buf, len, data->Sector[10]);
	len = openpilot_add_1byte(buf, len, data->Sector[11]);
	len = openpilot_add_1byte(buf, len, data->Sector[12]);
	len = openpilot_add_1byte(buf, len, data->Sector[13]);
	len = openpilot_add_1byte(buf, len, data->Sector[14]);
	len = openpilot_add_1byte(buf, len, data->Sector[15]);
	len = openpilot_add_1byte(buf, len, data->Sector[16]);
	len = openpilot_add_1byte(buf, len, data->Sector[17]);
	len = openpilot_add_1byte(buf, len, data->Sector[18]);
	len = openpilot_add_1byte(buf, len, data->Sector[19]);
	len = openpilot_add_1byte(buf, len, data->Sector[20]);
	len = openpilot_add_1byte(buf, len, data->Sector[21]);
	len = openpilot_add_1byte(buf, len, data->Sector[22]);
	len = openpilot_add_1byte(buf, len, data->Sector[23]);
	len = openpilot_add_1byte(buf, len, data->Sector[24]);
	len = openpilot_add_1byte(buf, len, data->Sector[25]);
	len = openpilot_add_1byte(buf, len, data->Sector[26]);
	len = openpilot_add_1byte(buf, len, data->Sector[27]);
	len = openpilot_add_1byte(buf, len, data->Sector[28]);
	len = openpilot_add_1byte(buf, len, data->Sector[29]);
	len = openpilot_add_1byte(buf, len, data->Sector[30]);
	len = openpilot_add_1byte(buf, len, data->Sector[31]);
	uavtalk_send(ModelActive, buf, PICOCSTATUS_OBJID, 0x22, len);
}


void UAVT_PoiLocation_Send (UAVT_PoiLocationData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(ModelActive, buf, POILOCATION_OBJID, 0x22, len);
}


void UAVT_PositionActual_Send (UAVT_PositionActualData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(ModelActive, buf, POSITIONACTUAL_OBJID, 0x22, len);
}


void UAVT_RateDesired_Send (UAVT_RateDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	len = openpilot_add_4byte(buf, len, data->Yaw);
	uavtalk_send(ModelActive, buf, RATEDESIRED_OBJID, 0x22, len);
}


void UAVT_SensorSettings_Send (UAVT_SensorSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->AccelBias.X);
	len = openpilot_add_4byte(buf, len, data->AccelBias.Y);
	len = openpilot_add_4byte(buf, len, data->AccelBias.Z);
	len = openpilot_add_4byte(buf, len, data->AccelScale.X);
	len = openpilot_add_4byte(buf, len, data->AccelScale.Y);
	len = openpilot_add_4byte(buf, len, data->AccelScale.Z);
	len = openpilot_add_4byte(buf, len, data->GyroScale.X);
	len = openpilot_add_4byte(buf, len, data->GyroScale.Y);
	len = openpilot_add_4byte(buf, len, data->GyroScale.Z);
	len = openpilot_add_4byte(buf, len, data->XGyroTempCoeff.n);
	len = openpilot_add_4byte(buf, len, data->XGyroTempCoeff.T);
	len = openpilot_add_4byte(buf, len, data->XGyroTempCoeff.T2);
	len = openpilot_add_4byte(buf, len, data->XGyroTempCoeff.T3);
	len = openpilot_add_4byte(buf, len, data->YGyroTempCoeff.n);
	len = openpilot_add_4byte(buf, len, data->YGyroTempCoeff.T);
	len = openpilot_add_4byte(buf, len, data->YGyroTempCoeff.T2);
	len = openpilot_add_4byte(buf, len, data->YGyroTempCoeff.T3);
	len = openpilot_add_4byte(buf, len, data->ZGyroTempCoeff.n);
	len = openpilot_add_4byte(buf, len, data->ZGyroTempCoeff.T);
	len = openpilot_add_4byte(buf, len, data->ZGyroTempCoeff.T2);
	len = openpilot_add_4byte(buf, len, data->ZGyroTempCoeff.T3);
	len = openpilot_add_4byte(buf, len, data->MagBias.X);
	len = openpilot_add_4byte(buf, len, data->MagBias.Y);
	len = openpilot_add_4byte(buf, len, data->MagBias.Z);
	len = openpilot_add_4byte(buf, len, data->MagScale.X);
	len = openpilot_add_4byte(buf, len, data->MagScale.Y);
	len = openpilot_add_4byte(buf, len, data->MagScale.Z);
	len = openpilot_add_4byte(buf, len, data->ZAccelOffset);
	uavtalk_send(ModelActive, buf, SENSORSETTINGS_OBJID, 0x22, len);
}


void UAVT_SessionManaging_Send (UAVT_SessionManagingData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->ObjectID);
	len = openpilot_add_2byte(buf, len, data->SessionID);
	len = openpilot_add_1byte(buf, len, data->ObjectInstances);
	len = openpilot_add_1byte(buf, len, data->NumberOfObjects);
	len = openpilot_add_1byte(buf, len, data->ObjectOfInterestIndex);
	uavtalk_send(ModelActive, buf, SESSIONMANAGING_OBJID, 0x22, len);
}


void UAVT_SonarAltitude_Send (UAVT_SonarAltitudeData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Altitude);
	uavtalk_send(ModelActive, buf, SONARALTITUDE_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, STABILIZATIONDESIRED_OBJID, 0x22, len);
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
	len = openpilot_add_4byte(buf, len, data->PoiMaximumRate.Roll);
	len = openpilot_add_4byte(buf, len, data->PoiMaximumRate.Pitch);
	len = openpilot_add_4byte(buf, len, data->PoiMaximumRate.Yaw);
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
	len = openpilot_add_4byte(buf, len, data->VbarRollPID.Kp);
	len = openpilot_add_4byte(buf, len, data->VbarRollPID.Ki);
	len = openpilot_add_4byte(buf, len, data->VbarRollPID.Kd);
	len = openpilot_add_4byte(buf, len, data->VbarPitchPID.Kp);
	len = openpilot_add_4byte(buf, len, data->VbarPitchPID.Ki);
	len = openpilot_add_4byte(buf, len, data->VbarPitchPID.Kd);
	len = openpilot_add_4byte(buf, len, data->VbarYawPID.Kp);
	len = openpilot_add_4byte(buf, len, data->VbarYawPID.Ki);
	len = openpilot_add_4byte(buf, len, data->VbarYawPID.Kd);
	len = openpilot_add_4byte(buf, len, data->VbarTau);
	len = openpilot_add_4byte(buf, len, data->GyroTau);
	len = openpilot_add_4byte(buf, len, data->DerivativeGamma);
	len = openpilot_add_4byte(buf, len, data->WeakLevelingKp);
	len = openpilot_add_4byte(buf, len, data->CoordinatedFlightYawPI.Kp);
	len = openpilot_add_4byte(buf, len, data->CoordinatedFlightYawPI.Ki);
	len = openpilot_add_4byte(buf, len, data->CoordinatedFlightYawPI.ILimit);
	len = openpilot_add_1byte(buf, len, data->RollMax);
	len = openpilot_add_1byte(buf, len, data->PitchMax);
	len = openpilot_add_1byte(buf, len, data->YawMax);
	len = openpilot_add_1byte(buf, len, data->RateExpo.Roll);
	len = openpilot_add_1byte(buf, len, data->RateExpo.Pitch);
	len = openpilot_add_1byte(buf, len, data->RateExpo.Yaw);
	len = openpilot_add_1byte(buf, len, data->RollRateTPA.Threshold);
	len = openpilot_add_1byte(buf, len, data->RollRateTPA.Attenuation);
	len = openpilot_add_1byte(buf, len, data->PitchRateTPA.Threshold);
	len = openpilot_add_1byte(buf, len, data->PitchRateTPA.Attenuation);
	len = openpilot_add_1byte(buf, len, data->YawRateTPA.Threshold);
	len = openpilot_add_1byte(buf, len, data->YawRateTPA.Attenuation);
	len = openpilot_add_1byte(buf, len, data->VbarGyroSuppress);
	len = openpilot_add_1byte(buf, len, data->VbarPiroComp);
	len = openpilot_add_1byte(buf, len, data->VbarMaxAngle);
	len = openpilot_add_1byte(buf, len, data->DerivativeCutoff);
	len = openpilot_add_1byte(buf, len, data->MaxAxisLock);
	len = openpilot_add_1byte(buf, len, data->MaxAxisLockRate);
	len = openpilot_add_1byte(buf, len, data->MaxWeakLevelingRate);
	len = openpilot_add_1byte(buf, len, data->LowThrottleZeroIntegral);
	uavtalk_send(ModelActive, buf, STABILIZATIONSETTINGS_OBJID, 0x22, len);
}


void UAVT_StateEstimation_Send (UAVT_StateEstimationData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->AttitudeFilter);
	len = openpilot_add_1byte(buf, len, data->NavigationFilter);
	uavtalk_send(ModelActive, buf, STATEESTIMATION_OBJID, 0x22, len);
}


void UAVT_SystemAlarms_Send (UAVT_SystemAlarmsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->Alarm.OutOfMemory);
	len = openpilot_add_1byte(buf, len, data->Alarm.CPUOverload);
	len = openpilot_add_1byte(buf, len, data->Alarm.StackOverflow);
	len = openpilot_add_1byte(buf, len, data->Alarm.SystemConfiguration);
	len = openpilot_add_1byte(buf, len, data->Alarm.EventSystem);
	len = openpilot_add_1byte(buf, len, data->Alarm.Telemetry);
	len = openpilot_add_1byte(buf, len, data->Alarm.ManualControl);
	len = openpilot_add_1byte(buf, len, data->Alarm.Actuator);
	len = openpilot_add_1byte(buf, len, data->Alarm.Attitude);
	len = openpilot_add_1byte(buf, len, data->Alarm.Sensors);
	len = openpilot_add_1byte(buf, len, data->Alarm.Stabilization);
	len = openpilot_add_1byte(buf, len, data->Alarm.Geofence);
	len = openpilot_add_1byte(buf, len, data->Alarm.PathFollower);
	len = openpilot_add_1byte(buf, len, data->Alarm.PathPlanner);
	len = openpilot_add_1byte(buf, len, data->Alarm.Battery);
	len = openpilot_add_1byte(buf, len, data->Alarm.FlightTime);
	len = openpilot_add_1byte(buf, len, data->Alarm.I2C);
	len = openpilot_add_1byte(buf, len, data->Alarm.GPS);
	len = openpilot_add_1byte(buf, len, data->Alarm.AltitudeHold);
	len = openpilot_add_1byte(buf, len, data->Alarm.BootFault);
	len = openpilot_add_1byte(buf, len, data->ConfigError);
	len = openpilot_add_1byte(buf, len, data->ManualControl);
	len = openpilot_add_1byte(buf, len, data->StateEstimation);
	uavtalk_send(ModelActive, buf, SYSTEMALARMS_OBJID, 0x22, len);
}


void UAVT_SystemSettings_Send (UAVT_SystemSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->AirframeCategorySpecificConfiguration[0]);
	len = openpilot_add_4byte(buf, len, data->AirframeCategorySpecificConfiguration[1]);
	len = openpilot_add_4byte(buf, len, data->AirframeCategorySpecificConfiguration[2]);
	len = openpilot_add_4byte(buf, len, data->AirframeCategorySpecificConfiguration[3]);
	len = openpilot_add_1byte(buf, len, data->AirframeType);
	uavtalk_send(ModelActive, buf, SYSTEMSETTINGS_OBJID, 0x22, len);
}


void UAVT_SystemStats_Send (UAVT_SystemStatsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->FlightTime);
	len = openpilot_add_4byte(buf, len, data->HeapRemaining);
	len = openpilot_add_4byte(buf, len, data->EventSystemWarningID);
	len = openpilot_add_4byte(buf, len, data->ObjectManagerCallbackID);
	len = openpilot_add_4byte(buf, len, data->ObjectManagerQueueID);
	len = openpilot_add_2byte(buf, len, data->IRQStackRemaining);
	len = openpilot_add_1byte(buf, len, data->CPULoad);
	len = openpilot_add_1byte(buf, len, data->CPUTemp);
	uavtalk_send(ModelActive, buf, SYSTEMSTATS_OBJID, 0x22, len);
}


void UAVT_TabletInfo_Send (UAVT_TabletInfoData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Latitude);
	len = openpilot_add_4byte(buf, len, data->Longitude);
	len = openpilot_add_4byte(buf, len, data->Altitude);
	len = openpilot_add_1byte(buf, len, data->Connected);
	len = openpilot_add_1byte(buf, len, data->TabletModeDesired);
	len = openpilot_add_1byte(buf, len, data->POI);
	uavtalk_send(ModelActive, buf, TABLETINFO_OBJID, 0x22, len);
}


void UAVT_TaskInfo_Send (UAVT_TaskInfoData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->StackRemaining.System);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Actuator);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Attitude);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Sensors);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.TelemetryTx);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.TelemetryTxPri);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.TelemetryRx);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.GPS);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.ManualControl);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Altitude);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Airspeed);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Stabilization);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.AltitudeHold);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.PathPlanner);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.PathFollower);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.FlightPlan);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Com2UsbBridge);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Usb2ComBridge);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.OveroSync);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.ModemRx);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.ModemTx);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.ModemStat);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Autotune);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.EventDispatcher);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.GenericI2CSensor);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.UAVOMavlinkBridge);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.UAVOLighttelemetryBridge);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.UAVORelay);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.VibrationAnalysis);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Battery);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.UAVOHoTTBridge);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.UAVOFrSKYSensorHubBridge);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.PicoC);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.Logging);
	len = openpilot_add_2byte(buf, len, data->StackRemaining.UAVOFrSkySPortBridge);
	len = openpilot_add_1byte(buf, len, data->Running.System);
	len = openpilot_add_1byte(buf, len, data->Running.Actuator);
	len = openpilot_add_1byte(buf, len, data->Running.Attitude);
	len = openpilot_add_1byte(buf, len, data->Running.Sensors);
	len = openpilot_add_1byte(buf, len, data->Running.TelemetryTx);
	len = openpilot_add_1byte(buf, len, data->Running.TelemetryTxPri);
	len = openpilot_add_1byte(buf, len, data->Running.TelemetryRx);
	len = openpilot_add_1byte(buf, len, data->Running.GPS);
	len = openpilot_add_1byte(buf, len, data->Running.ManualControl);
	len = openpilot_add_1byte(buf, len, data->Running.Altitude);
	len = openpilot_add_1byte(buf, len, data->Running.Airspeed);
	len = openpilot_add_1byte(buf, len, data->Running.Stabilization);
	len = openpilot_add_1byte(buf, len, data->Running.AltitudeHold);
	len = openpilot_add_1byte(buf, len, data->Running.PathPlanner);
	len = openpilot_add_1byte(buf, len, data->Running.PathFollower);
	len = openpilot_add_1byte(buf, len, data->Running.FlightPlan);
	len = openpilot_add_1byte(buf, len, data->Running.Com2UsbBridge);
	len = openpilot_add_1byte(buf, len, data->Running.Usb2ComBridge);
	len = openpilot_add_1byte(buf, len, data->Running.OveroSync);
	len = openpilot_add_1byte(buf, len, data->Running.ModemRx);
	len = openpilot_add_1byte(buf, len, data->Running.ModemTx);
	len = openpilot_add_1byte(buf, len, data->Running.ModemStat);
	len = openpilot_add_1byte(buf, len, data->Running.Autotune);
	len = openpilot_add_1byte(buf, len, data->Running.EventDispatcher);
	len = openpilot_add_1byte(buf, len, data->Running.GenericI2CSensor);
	len = openpilot_add_1byte(buf, len, data->Running.UAVOMavlinkBridge);
	len = openpilot_add_1byte(buf, len, data->Running.UAVOLighttelemetryBridge);
	len = openpilot_add_1byte(buf, len, data->Running.UAVORelay);
	len = openpilot_add_1byte(buf, len, data->Running.VibrationAnalysis);
	len = openpilot_add_1byte(buf, len, data->Running.Battery);
	len = openpilot_add_1byte(buf, len, data->Running.UAVOHoTTBridge);
	len = openpilot_add_1byte(buf, len, data->Running.UAVOFrSKYSBridge);
	len = openpilot_add_1byte(buf, len, data->Running.PicoC);
	len = openpilot_add_1byte(buf, len, data->Running.Logging);
	len = openpilot_add_1byte(buf, len, data->Running.UAVOFrSkySPortBridge);
	len = openpilot_add_1byte(buf, len, data->RunningTime.System);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Actuator);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Attitude);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Sensors);
	len = openpilot_add_1byte(buf, len, data->RunningTime.TelemetryTx);
	len = openpilot_add_1byte(buf, len, data->RunningTime.TelemetryTxPri);
	len = openpilot_add_1byte(buf, len, data->RunningTime.TelemetryRx);
	len = openpilot_add_1byte(buf, len, data->RunningTime.GPS);
	len = openpilot_add_1byte(buf, len, data->RunningTime.ManualControl);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Altitude);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Airspeed);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Stabilization);
	len = openpilot_add_1byte(buf, len, data->RunningTime.AltitudeHold);
	len = openpilot_add_1byte(buf, len, data->RunningTime.PathPlanner);
	len = openpilot_add_1byte(buf, len, data->RunningTime.PathFollower);
	len = openpilot_add_1byte(buf, len, data->RunningTime.FlightPlan);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Com2UsbBridge);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Usb2ComBridge);
	len = openpilot_add_1byte(buf, len, data->RunningTime.OveroSync);
	len = openpilot_add_1byte(buf, len, data->RunningTime.ModemRx);
	len = openpilot_add_1byte(buf, len, data->RunningTime.ModemTx);
	len = openpilot_add_1byte(buf, len, data->RunningTime.ModemStat);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Autotune);
	len = openpilot_add_1byte(buf, len, data->RunningTime.EventDispatcher);
	len = openpilot_add_1byte(buf, len, data->RunningTime.GenericI2CSensor);
	len = openpilot_add_1byte(buf, len, data->RunningTime.UAVOMavlinkBridge);
	len = openpilot_add_1byte(buf, len, data->RunningTime.UAVOLighttelemetryBridge);
	len = openpilot_add_1byte(buf, len, data->RunningTime.UAVORelay);
	len = openpilot_add_1byte(buf, len, data->RunningTime.VibrationAnalysis);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Battery);
	len = openpilot_add_1byte(buf, len, data->RunningTime.UAVOHoTTBridge);
	len = openpilot_add_1byte(buf, len, data->RunningTime.UAVOFrSKYSensorHubBridge);
	len = openpilot_add_1byte(buf, len, data->RunningTime.PicoC);
	len = openpilot_add_1byte(buf, len, data->RunningTime.Logging);
	len = openpilot_add_1byte(buf, len, data->RunningTime.UAVOFrSkySPortBridge);
	uavtalk_send(ModelActive, buf, TASKINFO_OBJID, 0x22, len);
}


void UAVT_TrimAnglesSettings_Send (UAVT_TrimAnglesSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	uavtalk_send(ModelActive, buf, TRIMANGLESSETTINGS_OBJID, 0x22, len);
}


void UAVT_TrimAngles_Send (UAVT_TrimAnglesData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Roll);
	len = openpilot_add_4byte(buf, len, data->Pitch);
	uavtalk_send(ModelActive, buf, TRIMANGLES_OBJID, 0x22, len);
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
	uavtalk_send(ModelActive, buf, TXPIDSETTINGS_OBJID, 0x22, len);
}


void UAVT_UBloxInfo_Send (UAVT_UBloxInfoData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->swVersion);
	len = openpilot_add_4byte(buf, len, data->ParseErrors);
	len = openpilot_add_1byte(buf, len, data->hwVersion[0]);
	len = openpilot_add_1byte(buf, len, data->hwVersion[1]);
	len = openpilot_add_1byte(buf, len, data->hwVersion[2]);
	len = openpilot_add_1byte(buf, len, data->hwVersion[3]);
	len = openpilot_add_1byte(buf, len, data->hwVersion[4]);
	len = openpilot_add_1byte(buf, len, data->hwVersion[5]);
	len = openpilot_add_1byte(buf, len, data->hwVersion[6]);
	len = openpilot_add_1byte(buf, len, data->hwVersion[7]);
	uavtalk_send(ModelActive, buf, UBLOXINFO_OBJID, 0x22, len);
}


void UAVT_VelocityActual_Send (UAVT_VelocityActualData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(ModelActive, buf, VELOCITYACTUAL_OBJID, 0x22, len);
}


void UAVT_VelocityDesired_Send (UAVT_VelocityDesiredData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(ModelActive, buf, VELOCITYDESIRED_OBJID, 0x22, len);
}


void UAVT_VibrationAnalysisOutput_Send (UAVT_VibrationAnalysisOutputData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->x);
	len = openpilot_add_4byte(buf, len, data->y);
	len = openpilot_add_4byte(buf, len, data->z);
	uavtalk_send(ModelActive, buf, VIBRATIONANALYSISOUTPUT_OBJID, 0x22, len);
}


void UAVT_VibrationAnalysisSettings_Send (UAVT_VibrationAnalysisSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->SampleRate);
	len = openpilot_add_1byte(buf, len, data->FFTWindowSize);
	len = openpilot_add_1byte(buf, len, data->TestingStatus);
	uavtalk_send(ModelActive, buf, VIBRATIONANALYSISSETTINGS_OBJID, 0x22, len);
}


void UAVT_VtolPathFollowerSettings_Send (UAVT_VtolPathFollowerSettingsData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->HorizontalPosPI.Kp);
	len = openpilot_add_4byte(buf, len, data->HorizontalPosPI.Ki);
	len = openpilot_add_4byte(buf, len, data->HorizontalPosPI.ILimit);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.Kp);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.Ki);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.Kd);
	len = openpilot_add_4byte(buf, len, data->HorizontalVelPID.ILimit);
	len = openpilot_add_4byte(buf, len, data->VelocityFeedforward);
	len = openpilot_add_4byte(buf, len, data->MaxRollPitch);
	len = openpilot_add_4byte(buf, len, data->UpdatePeriod);
	len = openpilot_add_4byte(buf, len, data->LandingRate);
	len = openpilot_add_2byte(buf, len, data->HorizontalVelMax);
	len = openpilot_add_2byte(buf, len, data->VerticalVelMax);
	len = openpilot_add_1byte(buf, len, data->ThrottleControl);
	len = openpilot_add_1byte(buf, len, data->VelocityChangePrediction);
	len = openpilot_add_1byte(buf, len, data->EndpointRadius);
	len = openpilot_add_1byte(buf, len, data->YawMode);
	uavtalk_send(ModelActive, buf, VTOLPATHFOLLOWERSETTINGS_OBJID, 0x22, len);
}


void UAVT_VtolPathFollowerStatus_Send (UAVT_VtolPathFollowerStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_1byte(buf, len, data->FSM_State);
	uavtalk_send(ModelActive, buf, VTOLPATHFOLLOWERSTATUS_OBJID, 0x22, len);
}


void UAVT_WatchdogStatus_Send (UAVT_WatchdogStatusData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->BootupFlags);
	len = openpilot_add_2byte(buf, len, data->ActiveFlags);
	uavtalk_send(ModelActive, buf, WATCHDOGSTATUS_OBJID, 0x22, len);
}


void UAVT_WaypointActive_Send (UAVT_WaypointActiveData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_2byte(buf, len, data->Index);
	uavtalk_send(ModelActive, buf, WAYPOINTACTIVE_OBJID, 0x22, len);
}


void UAVT_Waypoint_Send (UAVT_WaypointData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->Position.North);
	len = openpilot_add_4byte(buf, len, data->Position.East);
	len = openpilot_add_4byte(buf, len, data->Position.Down);
	len = openpilot_add_4byte(buf, len, data->Velocity);
	len = openpilot_add_4byte(buf, len, data->ModeParameters);
	len = openpilot_add_1byte(buf, len, data->Mode);
	uavtalk_send(ModelActive, buf, WAYPOINT_OBJID, 0x22, len);
}


void UAVT_WindVelocityActual_Send (UAVT_WindVelocityActualData *data) {
	uint8_t buf[256];
	uint8_t len = 0;
	len = openpilot_add_4byte(buf, len, data->North);
	len = openpilot_add_4byte(buf, len, data->East);
	len = openpilot_add_4byte(buf, len, data->Down);
	uavtalk_send(ModelActive, buf, WINDVELOCITYACTUAL_OBJID, 0x22, len);
}

