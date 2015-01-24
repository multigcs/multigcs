
#include <all.h>

void uavtalk_decode (uint32_t obj_id, uint8_t *buf) {
	switch (obj_id) {
		case ACCELS_OBJID: {
			UAVT_AccelsData *data = (UAVT_AccelsData *)buf;
			memcpy(&uavtalk_AccelsData, data, sizeof(UAVT_AccelsData));
			SDL_Log("uavtalk: <-Accels\n");
			SDL_Log("uavtalk: 	x: %f\n", data->x);
			SDL_Log("uavtalk: 	y: %f\n", data->y);
			SDL_Log("uavtalk: 	z: %f\n", data->z);
			SDL_Log("uavtalk: 	temperature: %f\n", data->temperature);
			break;
		}
		case ACCESSORYDESIRED_OBJID: {
			UAVT_AccessoryDesiredData *data = (UAVT_AccessoryDesiredData *)buf;
			memcpy(&uavtalk_AccessoryDesiredData, data, sizeof(UAVT_AccessoryDesiredData));
			SDL_Log("uavtalk: <-AccessoryDesired\n");
			SDL_Log("uavtalk: 	AccessoryVal: %f\n", data->AccessoryVal);
			break;
		}
		case ACTUATORCOMMAND_OBJID: {
			UAVT_ActuatorCommandData *data = (UAVT_ActuatorCommandData *)buf;
			memcpy(&uavtalk_ActuatorCommandData, data, sizeof(UAVT_ActuatorCommandData));
			SDL_Log("uavtalk: <-ActuatorCommand\n");
			SDL_Log("uavtalk: 	Channel[0]: %i\n", data->Channel[0]);
			SDL_Log("uavtalk: 	Channel[1]: %i\n", data->Channel[1]);
			SDL_Log("uavtalk: 	Channel[2]: %i\n", data->Channel[2]);
			SDL_Log("uavtalk: 	Channel[3]: %i\n", data->Channel[3]);
			SDL_Log("uavtalk: 	Channel[4]: %i\n", data->Channel[4]);
			SDL_Log("uavtalk: 	Channel[5]: %i\n", data->Channel[5]);
			SDL_Log("uavtalk: 	Channel[6]: %i\n", data->Channel[6]);
			SDL_Log("uavtalk: 	Channel[7]: %i\n", data->Channel[7]);
			SDL_Log("uavtalk: 	Channel[8]: %i\n", data->Channel[8]);
			SDL_Log("uavtalk: 	Channel[9]: %i\n", data->Channel[9]);
			SDL_Log("uavtalk: 	MaxUpdateTime: %i\n", data->MaxUpdateTime);
			SDL_Log("uavtalk: 	UpdateTime: %i\n", data->UpdateTime);
			SDL_Log("uavtalk: 	NumFailedUpdates: %i\n", data->NumFailedUpdates);
			break;
		}
		case ACTUATORDESIRED_OBJID: {
			UAVT_ActuatorDesiredData *data = (UAVT_ActuatorDesiredData *)buf;
			memcpy(&uavtalk_ActuatorDesiredData, data, sizeof(UAVT_ActuatorDesiredData));
			SDL_Log("uavtalk: <-ActuatorDesired\n");
			SDL_Log("uavtalk: 	Roll: %f\n", data->Roll);
			SDL_Log("uavtalk: 	Pitch: %f\n", data->Pitch);
			SDL_Log("uavtalk: 	Yaw: %f\n", data->Yaw);
			SDL_Log("uavtalk: 	Throttle: %f\n", data->Throttle);
			SDL_Log("uavtalk: 	UpdateTime: %f\n", data->UpdateTime);
			SDL_Log("uavtalk: 	NumLongUpdates: %f\n", data->NumLongUpdates);
			break;
		}
		case ACTUATORSETTINGS_OBJID: {
			UAVT_ActuatorSettingsData *data = (UAVT_ActuatorSettingsData *)buf;
			memcpy(&uavtalk_ActuatorSettingsData, data, sizeof(UAVT_ActuatorSettingsData));
			SDL_Log("uavtalk: <-ActuatorSettings\n");
			SDL_Log("uavtalk: 	ChannelUpdateFreq[0]: %i\n", data->ChannelUpdateFreq[0]);
			SDL_Log("uavtalk: 	ChannelUpdateFreq[1]: %i\n", data->ChannelUpdateFreq[1]);
			SDL_Log("uavtalk: 	ChannelUpdateFreq[2]: %i\n", data->ChannelUpdateFreq[2]);
			SDL_Log("uavtalk: 	ChannelUpdateFreq[3]: %i\n", data->ChannelUpdateFreq[3]);
			SDL_Log("uavtalk: 	ChannelMax[0]: %i\n", data->ChannelMax[0]);
			SDL_Log("uavtalk: 	ChannelMax[1]: %i\n", data->ChannelMax[1]);
			SDL_Log("uavtalk: 	ChannelMax[2]: %i\n", data->ChannelMax[2]);
			SDL_Log("uavtalk: 	ChannelMax[3]: %i\n", data->ChannelMax[3]);
			SDL_Log("uavtalk: 	ChannelMax[4]: %i\n", data->ChannelMax[4]);
			SDL_Log("uavtalk: 	ChannelMax[5]: %i\n", data->ChannelMax[5]);
			SDL_Log("uavtalk: 	ChannelMax[6]: %i\n", data->ChannelMax[6]);
			SDL_Log("uavtalk: 	ChannelMax[7]: %i\n", data->ChannelMax[7]);
			SDL_Log("uavtalk: 	ChannelMax[8]: %i\n", data->ChannelMax[8]);
			SDL_Log("uavtalk: 	ChannelMax[9]: %i\n", data->ChannelMax[9]);
			SDL_Log("uavtalk: 	ChannelNeutral[0]: %i\n", data->ChannelNeutral[0]);
			SDL_Log("uavtalk: 	ChannelNeutral[1]: %i\n", data->ChannelNeutral[1]);
			SDL_Log("uavtalk: 	ChannelNeutral[2]: %i\n", data->ChannelNeutral[2]);
			SDL_Log("uavtalk: 	ChannelNeutral[3]: %i\n", data->ChannelNeutral[3]);
			SDL_Log("uavtalk: 	ChannelNeutral[4]: %i\n", data->ChannelNeutral[4]);
			SDL_Log("uavtalk: 	ChannelNeutral[5]: %i\n", data->ChannelNeutral[5]);
			SDL_Log("uavtalk: 	ChannelNeutral[6]: %i\n", data->ChannelNeutral[6]);
			SDL_Log("uavtalk: 	ChannelNeutral[7]: %i\n", data->ChannelNeutral[7]);
			SDL_Log("uavtalk: 	ChannelNeutral[8]: %i\n", data->ChannelNeutral[8]);
			SDL_Log("uavtalk: 	ChannelNeutral[9]: %i\n", data->ChannelNeutral[9]);
			SDL_Log("uavtalk: 	ChannelMin[0]: %i\n", data->ChannelMin[0]);
			SDL_Log("uavtalk: 	ChannelMin[1]: %i\n", data->ChannelMin[1]);
			SDL_Log("uavtalk: 	ChannelMin[2]: %i\n", data->ChannelMin[2]);
			SDL_Log("uavtalk: 	ChannelMin[3]: %i\n", data->ChannelMin[3]);
			SDL_Log("uavtalk: 	ChannelMin[4]: %i\n", data->ChannelMin[4]);
			SDL_Log("uavtalk: 	ChannelMin[5]: %i\n", data->ChannelMin[5]);
			SDL_Log("uavtalk: 	ChannelMin[6]: %i\n", data->ChannelMin[6]);
			SDL_Log("uavtalk: 	ChannelMin[7]: %i\n", data->ChannelMin[7]);
			SDL_Log("uavtalk: 	ChannelMin[8]: %i\n", data->ChannelMin[8]);
			SDL_Log("uavtalk: 	ChannelMin[9]: %i\n", data->ChannelMin[9]);
			SDL_Log("uavtalk: 	ChannelType[0]: %i (%s)\n", data->ChannelType[0], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[0]]);
			SDL_Log("uavtalk: 	ChannelType[1]: %i (%s)\n", data->ChannelType[1], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[1]]);
			SDL_Log("uavtalk: 	ChannelType[2]: %i (%s)\n", data->ChannelType[2], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[2]]);
			SDL_Log("uavtalk: 	ChannelType[3]: %i (%s)\n", data->ChannelType[3], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[3]]);
			SDL_Log("uavtalk: 	ChannelType[4]: %i (%s)\n", data->ChannelType[4], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[4]]);
			SDL_Log("uavtalk: 	ChannelType[5]: %i (%s)\n", data->ChannelType[5], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[5]]);
			SDL_Log("uavtalk: 	ChannelType[6]: %i (%s)\n", data->ChannelType[6], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[6]]);
			SDL_Log("uavtalk: 	ChannelType[7]: %i (%s)\n", data->ChannelType[7], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[7]]);
			SDL_Log("uavtalk: 	ChannelType[8]: %i (%s)\n", data->ChannelType[8], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[8]]);
			SDL_Log("uavtalk: 	ChannelType[9]: %i (%s)\n", data->ChannelType[9], UAVT_ActuatorSettingsChannelTypeOption[data->ChannelType[9]]);
			SDL_Log("uavtalk: 	ChannelAddr[0]: %i\n", data->ChannelAddr[0]);
			SDL_Log("uavtalk: 	ChannelAddr[1]: %i\n", data->ChannelAddr[1]);
			SDL_Log("uavtalk: 	ChannelAddr[2]: %i\n", data->ChannelAddr[2]);
			SDL_Log("uavtalk: 	ChannelAddr[3]: %i\n", data->ChannelAddr[3]);
			SDL_Log("uavtalk: 	ChannelAddr[4]: %i\n", data->ChannelAddr[4]);
			SDL_Log("uavtalk: 	ChannelAddr[5]: %i\n", data->ChannelAddr[5]);
			SDL_Log("uavtalk: 	ChannelAddr[6]: %i\n", data->ChannelAddr[6]);
			SDL_Log("uavtalk: 	ChannelAddr[7]: %i\n", data->ChannelAddr[7]);
			SDL_Log("uavtalk: 	ChannelAddr[8]: %i\n", data->ChannelAddr[8]);
			SDL_Log("uavtalk: 	ChannelAddr[9]: %i\n", data->ChannelAddr[9]);
			SDL_Log("uavtalk: 	MotorsSpinWhileArmed: %i (%s)\n", data->MotorsSpinWhileArmed, UAVT_ActuatorSettingsMotorsSpinWhileArmedOption[data->MotorsSpinWhileArmed]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case ALTHOLDSMOOTHED_OBJID: {
			UAVT_AltHoldSmoothedData *data = (UAVT_AltHoldSmoothedData *)buf;
			memcpy(&uavtalk_AltHoldSmoothedData, data, sizeof(UAVT_AltHoldSmoothedData));
			SDL_Log("uavtalk: <-AltHoldSmoothed\n");
			SDL_Log("uavtalk: 	Altitude: %f\n", data->Altitude);
			SDL_Log("uavtalk: 	Velocity: %f\n", data->Velocity);
			SDL_Log("uavtalk: 	Accel: %f\n", data->Accel);
			break;
		}
		case ALTITUDEHOLDDESIRED_OBJID: {
			UAVT_AltitudeHoldDesiredData *data = (UAVT_AltitudeHoldDesiredData *)buf;
			memcpy(&uavtalk_AltitudeHoldDesiredData, data, sizeof(UAVT_AltitudeHoldDesiredData));
			SDL_Log("uavtalk: <-AltitudeHoldDesired\n");
			SDL_Log("uavtalk: 	Altitude: %f\n", data->Altitude);
			SDL_Log("uavtalk: 	Roll: %f\n", data->Roll);
			SDL_Log("uavtalk: 	Pitch: %f\n", data->Pitch);
			SDL_Log("uavtalk: 	Yaw: %f\n", data->Yaw);
			break;
		}
		case ALTITUDEHOLDSETTINGS_OBJID: {
			UAVT_AltitudeHoldSettingsData *data = (UAVT_AltitudeHoldSettingsData *)buf;
			memcpy(&uavtalk_AltitudeHoldSettingsData, data, sizeof(UAVT_AltitudeHoldSettingsData));
			SDL_Log("uavtalk: <-AltitudeHoldSettings\n");
			SDL_Log("uavtalk: 	Kp: %f\n", data->Kp);
			SDL_Log("uavtalk: 	Ki: %f\n", data->Ki);
			SDL_Log("uavtalk: 	Kd: %f\n", data->Kd);
			SDL_Log("uavtalk: 	Ka: %f\n", data->Ka);
			SDL_Log("uavtalk: 	PressureNoise: %f\n", data->PressureNoise);
			SDL_Log("uavtalk: 	AccelNoise: %f\n", data->AccelNoise);
			SDL_Log("uavtalk: 	AccelDrift: %f\n", data->AccelDrift);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case ATTITUDEACTUAL_OBJID: {
			UAVT_AttitudeActualData *data = (UAVT_AttitudeActualData *)buf;
			memcpy(&uavtalk_AttitudeActualData, data, sizeof(UAVT_AttitudeActualData));
			SDL_Log("uavtalk: <-AttitudeActual\n");
			SDL_Log("uavtalk: 	q1: %f\n", data->q1);
			SDL_Log("uavtalk: 	q2: %f\n", data->q2);
			SDL_Log("uavtalk: 	q3: %f\n", data->q3);
			SDL_Log("uavtalk: 	q4: %f\n", data->q4);
			SDL_Log("uavtalk: 	Roll: %f\n", data->Roll);
			SDL_Log("uavtalk: 	Pitch: %f\n", data->Pitch);
			SDL_Log("uavtalk: 	Yaw: %f\n", data->Yaw);
			break;
		}
		case ATTITUDESETTINGS_OBJID: {
			UAVT_AttitudeSettingsData *data = (UAVT_AttitudeSettingsData *)buf;
			memcpy(&uavtalk_AttitudeSettingsData, data, sizeof(UAVT_AttitudeSettingsData));
			SDL_Log("uavtalk: <-AttitudeSettings\n");
			SDL_Log("uavtalk: 	GyroGain: %f\n", data->GyroGain);
			SDL_Log("uavtalk: 	AccelKp: %f\n", data->AccelKp);
			SDL_Log("uavtalk: 	AccelKi: %f\n", data->AccelKi);
			SDL_Log("uavtalk: 	AccelTau: %f\n", data->AccelTau);
			SDL_Log("uavtalk: 	YawBiasRate: %f\n", data->YawBiasRate);
			SDL_Log("uavtalk: 	AccelBias.X: %i\n", data->AccelBias.X);
			SDL_Log("uavtalk: 	AccelBias.Y: %i\n", data->AccelBias.Y);
			SDL_Log("uavtalk: 	AccelBias.Z: %i\n", data->AccelBias.Z);
			SDL_Log("uavtalk: 	GyroBias.X: %i\n", data->GyroBias.X);
			SDL_Log("uavtalk: 	GyroBias.Y: %i\n", data->GyroBias.Y);
			SDL_Log("uavtalk: 	GyroBias.Z: %i\n", data->GyroBias.Z);
			SDL_Log("uavtalk: 	BoardRotation.Roll: %i\n", data->BoardRotation.Roll);
			SDL_Log("uavtalk: 	BoardRotation.Pitch: %i\n", data->BoardRotation.Pitch);
			SDL_Log("uavtalk: 	BoardRotation.Yaw: %i\n", data->BoardRotation.Yaw);
			SDL_Log("uavtalk: 	ZeroDuringArming: %i (%s)\n", data->ZeroDuringArming, UAVT_AttitudeSettingsZeroDuringArmingOption[data->ZeroDuringArming]);
			SDL_Log("uavtalk: 	BiasCorrectGyro: %i (%s)\n", data->BiasCorrectGyro, UAVT_AttitudeSettingsBiasCorrectGyroOption[data->BiasCorrectGyro]);
			SDL_Log("uavtalk: 	TrimFlight: %i (%s)\n", data->TrimFlight, UAVT_AttitudeSettingsTrimFlightOption[data->TrimFlight]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case BAROALTITUDE_OBJID: {
			UAVT_BaroAltitudeData *data = (UAVT_BaroAltitudeData *)buf;
			memcpy(&uavtalk_BaroAltitudeData, data, sizeof(UAVT_BaroAltitudeData));
			SDL_Log("uavtalk: <-BaroAltitude\n");
			SDL_Log("uavtalk: 	Altitude: %f\n", data->Altitude);
			SDL_Log("uavtalk: 	Temperature: %f\n", data->Temperature);
			SDL_Log("uavtalk: 	Pressure: %f\n", data->Pressure);
			break;
		}
		case CAMERADESIRED_OBJID: {
			UAVT_CameraDesiredData *data = (UAVT_CameraDesiredData *)buf;
			memcpy(&uavtalk_CameraDesiredData, data, sizeof(UAVT_CameraDesiredData));
			SDL_Log("uavtalk: <-CameraDesired\n");
			SDL_Log("uavtalk: 	Roll: %f\n", data->Roll);
			SDL_Log("uavtalk: 	Pitch: %f\n", data->Pitch);
			SDL_Log("uavtalk: 	Yaw: %f\n", data->Yaw);
			break;
		}
		case CAMERASTABSETTINGS_OBJID: {
			UAVT_CameraStabSettingsData *data = (UAVT_CameraStabSettingsData *)buf;
			memcpy(&uavtalk_CameraStabSettingsData, data, sizeof(UAVT_CameraStabSettingsData));
			SDL_Log("uavtalk: <-CameraStabSettings\n");
			SDL_Log("uavtalk: 	MaxAxisLockRate: %f\n", data->MaxAxisLockRate);
			SDL_Log("uavtalk: 	ResponseTime.Roll: %i\n", data->ResponseTime.Roll);
			SDL_Log("uavtalk: 	ResponseTime.Pitch: %i\n", data->ResponseTime.Pitch);
			SDL_Log("uavtalk: 	ResponseTime.Yaw: %i\n", data->ResponseTime.Yaw);
			SDL_Log("uavtalk: 	Input.Roll: %i\n", data->Input.Roll);
			SDL_Log("uavtalk: 	Input.Pitch: %i\n", data->Input.Pitch);
			SDL_Log("uavtalk: 	Input.Yaw: %i\n", data->Input.Yaw);
			SDL_Log("uavtalk: 	InputRange.Roll: %i\n", data->InputRange.Roll);
			SDL_Log("uavtalk: 	InputRange.Pitch: %i\n", data->InputRange.Pitch);
			SDL_Log("uavtalk: 	InputRange.Yaw: %i\n", data->InputRange.Yaw);
			SDL_Log("uavtalk: 	InputRate.Roll: %i\n", data->InputRate.Roll);
			SDL_Log("uavtalk: 	InputRate.Pitch: %i\n", data->InputRate.Pitch);
			SDL_Log("uavtalk: 	InputRate.Yaw: %i\n", data->InputRate.Yaw);
			SDL_Log("uavtalk: 	StabilizationMode.Roll: %i\n", data->StabilizationMode.Roll);
			SDL_Log("uavtalk: 	StabilizationMode.Pitch: %i\n", data->StabilizationMode.Pitch);
			SDL_Log("uavtalk: 	StabilizationMode.Yaw: %i\n", data->StabilizationMode.Yaw);
			SDL_Log("uavtalk: 	OutputRange.Roll: %i\n", data->OutputRange.Roll);
			SDL_Log("uavtalk: 	OutputRange.Pitch: %i\n", data->OutputRange.Pitch);
			SDL_Log("uavtalk: 	OutputRange.Yaw: %i\n", data->OutputRange.Yaw);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case FAULTSETTINGS_OBJID: {
			UAVT_FaultSettingsData *data = (UAVT_FaultSettingsData *)buf;
			memcpy(&uavtalk_FaultSettingsData, data, sizeof(UAVT_FaultSettingsData));
			SDL_Log("uavtalk: <-FaultSettings\n");
			SDL_Log("uavtalk: 	ActivateFault: %i (%s)\n", data->ActivateFault, UAVT_FaultSettingsActivateFaultOption[data->ActivateFault]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case FIRMWAREIAPOBJ_OBJID: {
			UAVT_FirmwareIAPObjData *data = (UAVT_FirmwareIAPObjData *)buf;
			memcpy(&uavtalk_FirmwareIAPObjData, data, sizeof(UAVT_FirmwareIAPObjData));
			SDL_Log("uavtalk: <-FirmwareIAPObj\n");
			SDL_Log("uavtalk: 	crc: %i\n", data->crc);
			SDL_Log("uavtalk: 	Command: %i\n", data->Command);
			SDL_Log("uavtalk: 	BoardRevision: %i\n", data->BoardRevision);
			SDL_Log("uavtalk: 	Description[0]: %i\n", data->Description[0]);
			SDL_Log("uavtalk: 	Description[1]: %i\n", data->Description[1]);
			SDL_Log("uavtalk: 	Description[2]: %i\n", data->Description[2]);
			SDL_Log("uavtalk: 	Description[3]: %i\n", data->Description[3]);
			SDL_Log("uavtalk: 	Description[4]: %i\n", data->Description[4]);
			SDL_Log("uavtalk: 	Description[5]: %i\n", data->Description[5]);
			SDL_Log("uavtalk: 	Description[6]: %i\n", data->Description[6]);
			SDL_Log("uavtalk: 	Description[7]: %i\n", data->Description[7]);
			SDL_Log("uavtalk: 	Description[8]: %i\n", data->Description[8]);
			SDL_Log("uavtalk: 	Description[9]: %i\n", data->Description[9]);
			SDL_Log("uavtalk: 	Description[10]: %i\n", data->Description[10]);
			SDL_Log("uavtalk: 	Description[11]: %i\n", data->Description[11]);
			SDL_Log("uavtalk: 	Description[12]: %i\n", data->Description[12]);
			SDL_Log("uavtalk: 	Description[13]: %i\n", data->Description[13]);
			SDL_Log("uavtalk: 	Description[14]: %i\n", data->Description[14]);
			SDL_Log("uavtalk: 	Description[15]: %i\n", data->Description[15]);
			SDL_Log("uavtalk: 	Description[16]: %i\n", data->Description[16]);
			SDL_Log("uavtalk: 	Description[17]: %i\n", data->Description[17]);
			SDL_Log("uavtalk: 	Description[18]: %i\n", data->Description[18]);
			SDL_Log("uavtalk: 	Description[19]: %i\n", data->Description[19]);
			SDL_Log("uavtalk: 	Description[20]: %i\n", data->Description[20]);
			SDL_Log("uavtalk: 	Description[21]: %i\n", data->Description[21]);
			SDL_Log("uavtalk: 	Description[22]: %i\n", data->Description[22]);
			SDL_Log("uavtalk: 	Description[23]: %i\n", data->Description[23]);
			SDL_Log("uavtalk: 	Description[24]: %i\n", data->Description[24]);
			SDL_Log("uavtalk: 	Description[25]: %i\n", data->Description[25]);
			SDL_Log("uavtalk: 	Description[26]: %i\n", data->Description[26]);
			SDL_Log("uavtalk: 	Description[27]: %i\n", data->Description[27]);
			SDL_Log("uavtalk: 	Description[28]: %i\n", data->Description[28]);
			SDL_Log("uavtalk: 	Description[29]: %i\n", data->Description[29]);
			SDL_Log("uavtalk: 	Description[30]: %i\n", data->Description[30]);
			SDL_Log("uavtalk: 	Description[31]: %i\n", data->Description[31]);
			SDL_Log("uavtalk: 	Description[32]: %i\n", data->Description[32]);
			SDL_Log("uavtalk: 	Description[33]: %i\n", data->Description[33]);
			SDL_Log("uavtalk: 	Description[34]: %i\n", data->Description[34]);
			SDL_Log("uavtalk: 	Description[35]: %i\n", data->Description[35]);
			SDL_Log("uavtalk: 	Description[36]: %i\n", data->Description[36]);
			SDL_Log("uavtalk: 	Description[37]: %i\n", data->Description[37]);
			SDL_Log("uavtalk: 	Description[38]: %i\n", data->Description[38]);
			SDL_Log("uavtalk: 	Description[39]: %i\n", data->Description[39]);
			SDL_Log("uavtalk: 	Description[40]: %i\n", data->Description[40]);
			SDL_Log("uavtalk: 	Description[41]: %i\n", data->Description[41]);
			SDL_Log("uavtalk: 	Description[42]: %i\n", data->Description[42]);
			SDL_Log("uavtalk: 	Description[43]: %i\n", data->Description[43]);
			SDL_Log("uavtalk: 	Description[44]: %i\n", data->Description[44]);
			SDL_Log("uavtalk: 	Description[45]: %i\n", data->Description[45]);
			SDL_Log("uavtalk: 	Description[46]: %i\n", data->Description[46]);
			SDL_Log("uavtalk: 	Description[47]: %i\n", data->Description[47]);
			SDL_Log("uavtalk: 	Description[48]: %i\n", data->Description[48]);
			SDL_Log("uavtalk: 	Description[49]: %i\n", data->Description[49]);
			SDL_Log("uavtalk: 	Description[50]: %i\n", data->Description[50]);
			SDL_Log("uavtalk: 	Description[51]: %i\n", data->Description[51]);
			SDL_Log("uavtalk: 	Description[52]: %i\n", data->Description[52]);
			SDL_Log("uavtalk: 	Description[53]: %i\n", data->Description[53]);
			SDL_Log("uavtalk: 	Description[54]: %i\n", data->Description[54]);
			SDL_Log("uavtalk: 	Description[55]: %i\n", data->Description[55]);
			SDL_Log("uavtalk: 	Description[56]: %i\n", data->Description[56]);
			SDL_Log("uavtalk: 	Description[57]: %i\n", data->Description[57]);
			SDL_Log("uavtalk: 	Description[58]: %i\n", data->Description[58]);
			SDL_Log("uavtalk: 	Description[59]: %i\n", data->Description[59]);
			SDL_Log("uavtalk: 	Description[60]: %i\n", data->Description[60]);
			SDL_Log("uavtalk: 	Description[61]: %i\n", data->Description[61]);
			SDL_Log("uavtalk: 	Description[62]: %i\n", data->Description[62]);
			SDL_Log("uavtalk: 	Description[63]: %i\n", data->Description[63]);
			SDL_Log("uavtalk: 	Description[64]: %i\n", data->Description[64]);
			SDL_Log("uavtalk: 	Description[65]: %i\n", data->Description[65]);
			SDL_Log("uavtalk: 	Description[66]: %i\n", data->Description[66]);
			SDL_Log("uavtalk: 	Description[67]: %i\n", data->Description[67]);
			SDL_Log("uavtalk: 	Description[68]: %i\n", data->Description[68]);
			SDL_Log("uavtalk: 	Description[69]: %i\n", data->Description[69]);
			SDL_Log("uavtalk: 	Description[70]: %i\n", data->Description[70]);
			SDL_Log("uavtalk: 	Description[71]: %i\n", data->Description[71]);
			SDL_Log("uavtalk: 	Description[72]: %i\n", data->Description[72]);
			SDL_Log("uavtalk: 	Description[73]: %i\n", data->Description[73]);
			SDL_Log("uavtalk: 	Description[74]: %i\n", data->Description[74]);
			SDL_Log("uavtalk: 	Description[75]: %i\n", data->Description[75]);
			SDL_Log("uavtalk: 	Description[76]: %i\n", data->Description[76]);
			SDL_Log("uavtalk: 	Description[77]: %i\n", data->Description[77]);
			SDL_Log("uavtalk: 	Description[78]: %i\n", data->Description[78]);
			SDL_Log("uavtalk: 	Description[79]: %i\n", data->Description[79]);
			SDL_Log("uavtalk: 	Description[80]: %i\n", data->Description[80]);
			SDL_Log("uavtalk: 	Description[81]: %i\n", data->Description[81]);
			SDL_Log("uavtalk: 	Description[82]: %i\n", data->Description[82]);
			SDL_Log("uavtalk: 	Description[83]: %i\n", data->Description[83]);
			SDL_Log("uavtalk: 	Description[84]: %i\n", data->Description[84]);
			SDL_Log("uavtalk: 	Description[85]: %i\n", data->Description[85]);
			SDL_Log("uavtalk: 	Description[86]: %i\n", data->Description[86]);
			SDL_Log("uavtalk: 	Description[87]: %i\n", data->Description[87]);
			SDL_Log("uavtalk: 	Description[88]: %i\n", data->Description[88]);
			SDL_Log("uavtalk: 	Description[89]: %i\n", data->Description[89]);
			SDL_Log("uavtalk: 	Description[90]: %i\n", data->Description[90]);
			SDL_Log("uavtalk: 	Description[91]: %i\n", data->Description[91]);
			SDL_Log("uavtalk: 	Description[92]: %i\n", data->Description[92]);
			SDL_Log("uavtalk: 	Description[93]: %i\n", data->Description[93]);
			SDL_Log("uavtalk: 	Description[94]: %i\n", data->Description[94]);
			SDL_Log("uavtalk: 	Description[95]: %i\n", data->Description[95]);
			SDL_Log("uavtalk: 	Description[96]: %i\n", data->Description[96]);
			SDL_Log("uavtalk: 	Description[97]: %i\n", data->Description[97]);
			SDL_Log("uavtalk: 	Description[98]: %i\n", data->Description[98]);
			SDL_Log("uavtalk: 	Description[99]: %i\n", data->Description[99]);
			SDL_Log("uavtalk: 	CPUSerial[0]: %i\n", data->CPUSerial[0]);
			SDL_Log("uavtalk: 	CPUSerial[1]: %i\n", data->CPUSerial[1]);
			SDL_Log("uavtalk: 	CPUSerial[2]: %i\n", data->CPUSerial[2]);
			SDL_Log("uavtalk: 	CPUSerial[3]: %i\n", data->CPUSerial[3]);
			SDL_Log("uavtalk: 	CPUSerial[4]: %i\n", data->CPUSerial[4]);
			SDL_Log("uavtalk: 	CPUSerial[5]: %i\n", data->CPUSerial[5]);
			SDL_Log("uavtalk: 	CPUSerial[6]: %i\n", data->CPUSerial[6]);
			SDL_Log("uavtalk: 	CPUSerial[7]: %i\n", data->CPUSerial[7]);
			SDL_Log("uavtalk: 	CPUSerial[8]: %i\n", data->CPUSerial[8]);
			SDL_Log("uavtalk: 	CPUSerial[9]: %i\n", data->CPUSerial[9]);
			SDL_Log("uavtalk: 	CPUSerial[10]: %i\n", data->CPUSerial[10]);
			SDL_Log("uavtalk: 	CPUSerial[11]: %i\n", data->CPUSerial[11]);
			SDL_Log("uavtalk: 	BoardType: %i\n", data->BoardType);
			SDL_Log("uavtalk: 	ArmReset: %i\n", data->ArmReset);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case FLIGHTBATTERYSETTINGS_OBJID: {
			UAVT_FlightBatterySettingsData *data = (UAVT_FlightBatterySettingsData *)buf;
			memcpy(&uavtalk_FlightBatterySettingsData, data, sizeof(UAVT_FlightBatterySettingsData));
			SDL_Log("uavtalk: <-FlightBatterySettings\n");
			SDL_Log("uavtalk: 	Capacity: %i\n", data->Capacity);
			SDL_Log("uavtalk: 	VoltageThresholds.Warning: %f\n", data->VoltageThresholds.Warning);
			SDL_Log("uavtalk: 	VoltageThresholds.Alarm: %f\n", data->VoltageThresholds.Alarm);
			SDL_Log("uavtalk: 	SensorCalibrations.VoltageFactor: %f\n", data->SensorCalibrations.VoltageFactor);
			SDL_Log("uavtalk: 	SensorCalibrations.CurrentFactor: %f\n", data->SensorCalibrations.CurrentFactor);
			SDL_Log("uavtalk: 	Type: %i (%s)\n", data->Type, UAVT_FlightBatterySettingsTypeOption[data->Type]);
			SDL_Log("uavtalk: 	NbCells: %i\n", data->NbCells);
			SDL_Log("uavtalk: 	SensorType: %i (%s)\n", data->SensorType, UAVT_FlightBatterySettingsSensorTypeOption[data->SensorType]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case FLIGHTBATTERYSTATE_OBJID: {
			UAVT_FlightBatteryStateData *data = (UAVT_FlightBatteryStateData *)buf;
			memcpy(&uavtalk_FlightBatteryStateData, data, sizeof(UAVT_FlightBatteryStateData));
			SDL_Log("uavtalk: <-FlightBatteryState\n");
			SDL_Log("uavtalk: 	Voltage: %f\n", data->Voltage);
			SDL_Log("uavtalk: 	Current: %f\n", data->Current);
			SDL_Log("uavtalk: 	PeakCurrent: %f\n", data->PeakCurrent);
			SDL_Log("uavtalk: 	AvgCurrent: %f\n", data->AvgCurrent);
			SDL_Log("uavtalk: 	ConsumedEnergy: %f\n", data->ConsumedEnergy);
			SDL_Log("uavtalk: 	EstimatedFlightTime: %f\n", data->EstimatedFlightTime);
			break;
		}
		case FLIGHTPLANCONTROL_OBJID: {
			UAVT_FlightPlanControlData *data = (UAVT_FlightPlanControlData *)buf;
			memcpy(&uavtalk_FlightPlanControlData, data, sizeof(UAVT_FlightPlanControlData));
			SDL_Log("uavtalk: <-FlightPlanControl\n");
			SDL_Log("uavtalk: 	Command: %i (%s)\n", data->Command, UAVT_FlightPlanControlCommandOption[data->Command]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case FLIGHTPLANSETTINGS_OBJID: {
			UAVT_FlightPlanSettingsData *data = (UAVT_FlightPlanSettingsData *)buf;
			memcpy(&uavtalk_FlightPlanSettingsData, data, sizeof(UAVT_FlightPlanSettingsData));
			SDL_Log("uavtalk: <-FlightPlanSettings\n");
			SDL_Log("uavtalk: 	Test: %f\n", data->Test);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case FLIGHTPLANSTATUS_OBJID: {
			UAVT_FlightPlanStatusData *data = (UAVT_FlightPlanStatusData *)buf;
			memcpy(&uavtalk_FlightPlanStatusData, data, sizeof(UAVT_FlightPlanStatusData));
			SDL_Log("uavtalk: <-FlightPlanStatus\n");
			SDL_Log("uavtalk: 	ErrorFileID: %i\n", data->ErrorFileID);
			SDL_Log("uavtalk: 	ErrorLineNum: %i\n", data->ErrorLineNum);
			SDL_Log("uavtalk: 	Debug[0]: %f\n", data->Debug[0]);
			SDL_Log("uavtalk: 	Debug[1]: %f\n", data->Debug[1]);
			SDL_Log("uavtalk: 	Status: %i (%s)\n", data->Status, UAVT_FlightPlanStatusStatusOption[data->Status]);
			SDL_Log("uavtalk: 	ErrorType: %i (%s)\n", data->ErrorType, UAVT_FlightPlanStatusErrorTypeOption[data->ErrorType]);
			break;
		}
		case FLIGHTSTATUS_OBJID: {
			UAVT_FlightStatusData *data = (UAVT_FlightStatusData *)buf;
			memcpy(&uavtalk_FlightStatusData, data, sizeof(UAVT_FlightStatusData));
			SDL_Log("uavtalk: <-FlightStatus\n");
			SDL_Log("uavtalk: 	Armed: %i (%s)\n", data->Armed, UAVT_FlightStatusArmedOption[data->Armed]);
			SDL_Log("uavtalk: 	FlightMode: %i (%s)\n", data->FlightMode, UAVT_FlightStatusFlightModeOption[data->FlightMode]);
			break;
		}
		case FLIGHTTELEMETRYSTATS_OBJID: {
			UAVT_FlightTelemetryStatsData *data = (UAVT_FlightTelemetryStatsData *)buf;
			memcpy(&uavtalk_FlightTelemetryStatsData, data, sizeof(UAVT_FlightTelemetryStatsData));
			SDL_Log("uavtalk: <-FlightTelemetryStats\n");
			SDL_Log("uavtalk: 	TxDataRate: %f\n", data->TxDataRate);
			SDL_Log("uavtalk: 	RxDataRate: %f\n", data->RxDataRate);
			SDL_Log("uavtalk: 	TxFailures: %i\n", data->TxFailures);
			SDL_Log("uavtalk: 	RxFailures: %i\n", data->RxFailures);
			SDL_Log("uavtalk: 	TxRetries: %i\n", data->TxRetries);
			SDL_Log("uavtalk: 	Status: %i (%s)\n", data->Status, UAVT_FlightTelemetryStatsStatusOption[data->Status]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case GCSRECEIVER_OBJID: {
			UAVT_GCSReceiverData *data = (UAVT_GCSReceiverData *)buf;
			memcpy(&uavtalk_GCSReceiverData, data, sizeof(UAVT_GCSReceiverData));
			SDL_Log("uavtalk: <-GCSReceiver\n");
			SDL_Log("uavtalk: 	Channel[0]: %i\n", data->Channel[0]);
			SDL_Log("uavtalk: 	Channel[1]: %i\n", data->Channel[1]);
			SDL_Log("uavtalk: 	Channel[2]: %i\n", data->Channel[2]);
			SDL_Log("uavtalk: 	Channel[3]: %i\n", data->Channel[3]);
			SDL_Log("uavtalk: 	Channel[4]: %i\n", data->Channel[4]);
			SDL_Log("uavtalk: 	Channel[5]: %i\n", data->Channel[5]);
			SDL_Log("uavtalk: 	Channel[6]: %i\n", data->Channel[6]);
			SDL_Log("uavtalk: 	Channel[7]: %i\n", data->Channel[7]);
			break;
		}
		case GCSTELEMETRYSTATS_OBJID: {
			UAVT_GCSTelemetryStatsData *data = (UAVT_GCSTelemetryStatsData *)buf;
			memcpy(&uavtalk_GCSTelemetryStatsData, data, sizeof(UAVT_GCSTelemetryStatsData));
			SDL_Log("uavtalk: <-GCSTelemetryStats\n");
			SDL_Log("uavtalk: 	TxDataRate: %f\n", data->TxDataRate);
			SDL_Log("uavtalk: 	RxDataRate: %f\n", data->RxDataRate);
			SDL_Log("uavtalk: 	TxFailures: %i\n", data->TxFailures);
			SDL_Log("uavtalk: 	RxFailures: %i\n", data->RxFailures);
			SDL_Log("uavtalk: 	TxRetries: %i\n", data->TxRetries);
			SDL_Log("uavtalk: 	Status: %i (%s)\n", data->Status, UAVT_GCSTelemetryStatsStatusOption[data->Status]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case GPSPOSITION_OBJID: {
			UAVT_GPSPositionData *data = (UAVT_GPSPositionData *)buf;
			memcpy(&uavtalk_GPSPositionData, data, sizeof(UAVT_GPSPositionData));
			SDL_Log("uavtalk: <-GPSPosition\n");
			SDL_Log("uavtalk: 	Latitude: %i\n", data->Latitude);
			SDL_Log("uavtalk: 	Longitude: %i\n", data->Longitude);
			SDL_Log("uavtalk: 	Altitude: %f\n", data->Altitude);
			SDL_Log("uavtalk: 	GeoidSeparation: %f\n", data->GeoidSeparation);
			SDL_Log("uavtalk: 	Heading: %f\n", data->Heading);
			SDL_Log("uavtalk: 	Groundspeed: %f\n", data->Groundspeed);
			SDL_Log("uavtalk: 	PDOP: %f\n", data->PDOP);
			SDL_Log("uavtalk: 	HDOP: %f\n", data->HDOP);
			SDL_Log("uavtalk: 	VDOP: %f\n", data->VDOP);
			SDL_Log("uavtalk: 	Status: %i (%s)\n", data->Status, UAVT_GPSPositionStatusOption[data->Status]);
			SDL_Log("uavtalk: 	Satellites: %i\n", data->Satellites);
			break;
		}
		case GPSSATELLITES_OBJID: {
			UAVT_GPSSatellitesData *data = (UAVT_GPSSatellitesData *)buf;
			memcpy(&uavtalk_GPSSatellitesData, data, sizeof(UAVT_GPSSatellitesData));
			SDL_Log("uavtalk: <-GPSSatellites\n");
			SDL_Log("uavtalk: 	Elevation[0]: %f\n", data->Elevation[0]);
			SDL_Log("uavtalk: 	Elevation[1]: %f\n", data->Elevation[1]);
			SDL_Log("uavtalk: 	Elevation[2]: %f\n", data->Elevation[2]);
			SDL_Log("uavtalk: 	Elevation[3]: %f\n", data->Elevation[3]);
			SDL_Log("uavtalk: 	Elevation[4]: %f\n", data->Elevation[4]);
			SDL_Log("uavtalk: 	Elevation[5]: %f\n", data->Elevation[5]);
			SDL_Log("uavtalk: 	Elevation[6]: %f\n", data->Elevation[6]);
			SDL_Log("uavtalk: 	Elevation[7]: %f\n", data->Elevation[7]);
			SDL_Log("uavtalk: 	Elevation[8]: %f\n", data->Elevation[8]);
			SDL_Log("uavtalk: 	Elevation[9]: %f\n", data->Elevation[9]);
			SDL_Log("uavtalk: 	Elevation[10]: %f\n", data->Elevation[10]);
			SDL_Log("uavtalk: 	Elevation[11]: %f\n", data->Elevation[11]);
			SDL_Log("uavtalk: 	Elevation[12]: %f\n", data->Elevation[12]);
			SDL_Log("uavtalk: 	Elevation[13]: %f\n", data->Elevation[13]);
			SDL_Log("uavtalk: 	Elevation[14]: %f\n", data->Elevation[14]);
			SDL_Log("uavtalk: 	Elevation[15]: %f\n", data->Elevation[15]);
			SDL_Log("uavtalk: 	Azimuth[0]: %f\n", data->Azimuth[0]);
			SDL_Log("uavtalk: 	Azimuth[1]: %f\n", data->Azimuth[1]);
			SDL_Log("uavtalk: 	Azimuth[2]: %f\n", data->Azimuth[2]);
			SDL_Log("uavtalk: 	Azimuth[3]: %f\n", data->Azimuth[3]);
			SDL_Log("uavtalk: 	Azimuth[4]: %f\n", data->Azimuth[4]);
			SDL_Log("uavtalk: 	Azimuth[5]: %f\n", data->Azimuth[5]);
			SDL_Log("uavtalk: 	Azimuth[6]: %f\n", data->Azimuth[6]);
			SDL_Log("uavtalk: 	Azimuth[7]: %f\n", data->Azimuth[7]);
			SDL_Log("uavtalk: 	Azimuth[8]: %f\n", data->Azimuth[8]);
			SDL_Log("uavtalk: 	Azimuth[9]: %f\n", data->Azimuth[9]);
			SDL_Log("uavtalk: 	Azimuth[10]: %f\n", data->Azimuth[10]);
			SDL_Log("uavtalk: 	Azimuth[11]: %f\n", data->Azimuth[11]);
			SDL_Log("uavtalk: 	Azimuth[12]: %f\n", data->Azimuth[12]);
			SDL_Log("uavtalk: 	Azimuth[13]: %f\n", data->Azimuth[13]);
			SDL_Log("uavtalk: 	Azimuth[14]: %f\n", data->Azimuth[14]);
			SDL_Log("uavtalk: 	Azimuth[15]: %f\n", data->Azimuth[15]);
			SDL_Log("uavtalk: 	SatsInView: %i\n", data->SatsInView);
			SDL_Log("uavtalk: 	PRN[0]: %i\n", data->PRN[0]);
			SDL_Log("uavtalk: 	PRN[1]: %i\n", data->PRN[1]);
			SDL_Log("uavtalk: 	PRN[2]: %i\n", data->PRN[2]);
			SDL_Log("uavtalk: 	PRN[3]: %i\n", data->PRN[3]);
			SDL_Log("uavtalk: 	PRN[4]: %i\n", data->PRN[4]);
			SDL_Log("uavtalk: 	PRN[5]: %i\n", data->PRN[5]);
			SDL_Log("uavtalk: 	PRN[6]: %i\n", data->PRN[6]);
			SDL_Log("uavtalk: 	PRN[7]: %i\n", data->PRN[7]);
			SDL_Log("uavtalk: 	PRN[8]: %i\n", data->PRN[8]);
			SDL_Log("uavtalk: 	PRN[9]: %i\n", data->PRN[9]);
			SDL_Log("uavtalk: 	PRN[10]: %i\n", data->PRN[10]);
			SDL_Log("uavtalk: 	PRN[11]: %i\n", data->PRN[11]);
			SDL_Log("uavtalk: 	PRN[12]: %i\n", data->PRN[12]);
			SDL_Log("uavtalk: 	PRN[13]: %i\n", data->PRN[13]);
			SDL_Log("uavtalk: 	PRN[14]: %i\n", data->PRN[14]);
			SDL_Log("uavtalk: 	PRN[15]: %i\n", data->PRN[15]);
			SDL_Log("uavtalk: 	SNR[0]: %i\n", data->SNR[0]);
			SDL_Log("uavtalk: 	SNR[1]: %i\n", data->SNR[1]);
			SDL_Log("uavtalk: 	SNR[2]: %i\n", data->SNR[2]);
			SDL_Log("uavtalk: 	SNR[3]: %i\n", data->SNR[3]);
			SDL_Log("uavtalk: 	SNR[4]: %i\n", data->SNR[4]);
			SDL_Log("uavtalk: 	SNR[5]: %i\n", data->SNR[5]);
			SDL_Log("uavtalk: 	SNR[6]: %i\n", data->SNR[6]);
			SDL_Log("uavtalk: 	SNR[7]: %i\n", data->SNR[7]);
			SDL_Log("uavtalk: 	SNR[8]: %i\n", data->SNR[8]);
			SDL_Log("uavtalk: 	SNR[9]: %i\n", data->SNR[9]);
			SDL_Log("uavtalk: 	SNR[10]: %i\n", data->SNR[10]);
			SDL_Log("uavtalk: 	SNR[11]: %i\n", data->SNR[11]);
			SDL_Log("uavtalk: 	SNR[12]: %i\n", data->SNR[12]);
			SDL_Log("uavtalk: 	SNR[13]: %i\n", data->SNR[13]);
			SDL_Log("uavtalk: 	SNR[14]: %i\n", data->SNR[14]);
			SDL_Log("uavtalk: 	SNR[15]: %i\n", data->SNR[15]);
			break;
		}
		case GPSSETTINGS_OBJID: {
			UAVT_GPSSettingsData *data = (UAVT_GPSSettingsData *)buf;
			memcpy(&uavtalk_GPSSettingsData, data, sizeof(UAVT_GPSSettingsData));
			SDL_Log("uavtalk: <-GPSSettings\n");
			SDL_Log("uavtalk: 	DataProtocol: %i (%s)\n", data->DataProtocol, UAVT_GPSSettingsDataProtocolOption[data->DataProtocol]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case GPSTIME_OBJID: {
			UAVT_GPSTimeData *data = (UAVT_GPSTimeData *)buf;
			memcpy(&uavtalk_GPSTimeData, data, sizeof(UAVT_GPSTimeData));
			SDL_Log("uavtalk: <-GPSTime\n");
			SDL_Log("uavtalk: 	Year: %i\n", data->Year);
			SDL_Log("uavtalk: 	Month: %i\n", data->Month);
			SDL_Log("uavtalk: 	Day: %i\n", data->Day);
			SDL_Log("uavtalk: 	Hour: %i\n", data->Hour);
			SDL_Log("uavtalk: 	Minute: %i\n", data->Minute);
			SDL_Log("uavtalk: 	Second: %i\n", data->Second);
			break;
		}
		case GPSVELOCITY_OBJID: {
			UAVT_GPSVelocityData *data = (UAVT_GPSVelocityData *)buf;
			memcpy(&uavtalk_GPSVelocityData, data, sizeof(UAVT_GPSVelocityData));
			SDL_Log("uavtalk: <-GPSVelocity\n");
			SDL_Log("uavtalk: 	North: %f\n", data->North);
			SDL_Log("uavtalk: 	East: %f\n", data->East);
			SDL_Log("uavtalk: 	Down: %f\n", data->Down);
			break;
		}
		case GUIDANCESETTINGS_OBJID: {
			UAVT_GuidanceSettingsData *data = (UAVT_GuidanceSettingsData *)buf;
			memcpy(&uavtalk_GuidanceSettingsData, data, sizeof(UAVT_GuidanceSettingsData));
			SDL_Log("uavtalk: <-GuidanceSettings\n");
			SDL_Log("uavtalk: 	HorizontalPosPI.Kp: %f\n", data->HorizontalPosPI.Kp);
			SDL_Log("uavtalk: 	HorizontalPosPI.Ki: %f\n", data->HorizontalPosPI.Ki);
			SDL_Log("uavtalk: 	HorizontalPosPI.ILimit: %f\n", data->HorizontalPosPI.ILimit);
			SDL_Log("uavtalk: 	HorizontalVelPID.Kp: %f\n", data->HorizontalVelPID.Kp);
			SDL_Log("uavtalk: 	HorizontalVelPID.Ki: %f\n", data->HorizontalVelPID.Ki);
			SDL_Log("uavtalk: 	HorizontalVelPID.Kd: %f\n", data->HorizontalVelPID.Kd);
			SDL_Log("uavtalk: 	HorizontalVelPID.ILimit: %f\n", data->HorizontalVelPID.ILimit);
			SDL_Log("uavtalk: 	VerticalPosPI.Kp: %f\n", data->VerticalPosPI.Kp);
			SDL_Log("uavtalk: 	VerticalPosPI.Ki: %f\n", data->VerticalPosPI.Ki);
			SDL_Log("uavtalk: 	VerticalPosPI.ILimit: %f\n", data->VerticalPosPI.ILimit);
			SDL_Log("uavtalk: 	VerticalVelPID.Kp: %f\n", data->VerticalVelPID.Kp);
			SDL_Log("uavtalk: 	VerticalVelPID.Ki: %f\n", data->VerticalVelPID.Ki);
			SDL_Log("uavtalk: 	VerticalVelPID.Kd: %f\n", data->VerticalVelPID.Kd);
			SDL_Log("uavtalk: 	VerticalVelPID.ILimit: %f\n", data->VerticalVelPID.ILimit);
			SDL_Log("uavtalk: 	MaxRollPitch: %f\n", data->MaxRollPitch);
			SDL_Log("uavtalk: 	UpdatePeriod: %i\n", data->UpdatePeriod);
			SDL_Log("uavtalk: 	HorizontalVelMax: %i\n", data->HorizontalVelMax);
			SDL_Log("uavtalk: 	VerticalVelMax: %i\n", data->VerticalVelMax);
			SDL_Log("uavtalk: 	GuidanceMode: %i (%s)\n", data->GuidanceMode, UAVT_GuidanceSettingsGuidanceModeOption[data->GuidanceMode]);
			SDL_Log("uavtalk: 	ThrottleControl: %i (%s)\n", data->ThrottleControl, UAVT_GuidanceSettingsThrottleControlOption[data->ThrottleControl]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case GYROSBIAS_OBJID: {
			UAVT_GyrosBiasData *data = (UAVT_GyrosBiasData *)buf;
			memcpy(&uavtalk_GyrosBiasData, data, sizeof(UAVT_GyrosBiasData));
			SDL_Log("uavtalk: <-GyrosBias\n");
			SDL_Log("uavtalk: 	x: %f\n", data->x);
			SDL_Log("uavtalk: 	y: %f\n", data->y);
			SDL_Log("uavtalk: 	z: %f\n", data->z);
			break;
		}
		case GYROS_OBJID: {
			UAVT_GyrosData *data = (UAVT_GyrosData *)buf;
			memcpy(&uavtalk_GyrosData, data, sizeof(UAVT_GyrosData));
			SDL_Log("uavtalk: <-Gyros\n");
			SDL_Log("uavtalk: 	x: %f\n", data->x);
			SDL_Log("uavtalk: 	y: %f\n", data->y);
			SDL_Log("uavtalk: 	z: %f\n", data->z);
			SDL_Log("uavtalk: 	temperature: %f\n", data->temperature);
			break;
		}
		case HOMELOCATION_OBJID: {
			UAVT_HomeLocationData *data = (UAVT_HomeLocationData *)buf;
			memcpy(&uavtalk_HomeLocationData, data, sizeof(UAVT_HomeLocationData));
			SDL_Log("uavtalk: <-HomeLocation\n");
			SDL_Log("uavtalk: 	Latitude: %i\n", data->Latitude);
			SDL_Log("uavtalk: 	Longitude: %i\n", data->Longitude);
			SDL_Log("uavtalk: 	Altitude: %f\n", data->Altitude);
			SDL_Log("uavtalk: 	ECEF[0]: %i\n", data->ECEF[0]);
			SDL_Log("uavtalk: 	ECEF[1]: %i\n", data->ECEF[1]);
			SDL_Log("uavtalk: 	ECEF[2]: %i\n", data->ECEF[2]);
			SDL_Log("uavtalk: 	RNE[0]: %f\n", data->RNE[0]);
			SDL_Log("uavtalk: 	RNE[1]: %f\n", data->RNE[1]);
			SDL_Log("uavtalk: 	RNE[2]: %f\n", data->RNE[2]);
			SDL_Log("uavtalk: 	RNE[3]: %f\n", data->RNE[3]);
			SDL_Log("uavtalk: 	RNE[4]: %f\n", data->RNE[4]);
			SDL_Log("uavtalk: 	RNE[5]: %f\n", data->RNE[5]);
			SDL_Log("uavtalk: 	RNE[6]: %f\n", data->RNE[6]);
			SDL_Log("uavtalk: 	RNE[7]: %f\n", data->RNE[7]);
			SDL_Log("uavtalk: 	RNE[8]: %f\n", data->RNE[8]);
			SDL_Log("uavtalk: 	Be[0]: %f\n", data->Be[0]);
			SDL_Log("uavtalk: 	Be[1]: %f\n", data->Be[1]);
			SDL_Log("uavtalk: 	Be[2]: %f\n", data->Be[2]);
			SDL_Log("uavtalk: 	g_e: %f\n", data->g_e);
			SDL_Log("uavtalk: 	Set: %i (%s)\n", data->Set, UAVT_HomeLocationSetOption[data->Set]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case HWSETTINGS_OBJID: {
			UAVT_HwSettingsData *data = (UAVT_HwSettingsData *)buf;
			memcpy(&uavtalk_HwSettingsData, data, sizeof(UAVT_HwSettingsData));
			SDL_Log("uavtalk: <-HwSettings\n");
			SDL_Log("uavtalk: 	CC_RcvrPort: %i (%s)\n", data->CC_RcvrPort, UAVT_HwSettingsCC_RcvrPortOption[data->CC_RcvrPort]);
			SDL_Log("uavtalk: 	CC_MainPort: %i (%s)\n", data->CC_MainPort, UAVT_HwSettingsCC_MainPortOption[data->CC_MainPort]);
			SDL_Log("uavtalk: 	CC_FlexiPort: %i (%s)\n", data->CC_FlexiPort, UAVT_HwSettingsCC_FlexiPortOption[data->CC_FlexiPort]);
			SDL_Log("uavtalk: 	RV_RcvrPort: %i (%s)\n", data->RV_RcvrPort, UAVT_HwSettingsRV_RcvrPortOption[data->RV_RcvrPort]);
			SDL_Log("uavtalk: 	RV_AuxPort: %i (%s)\n", data->RV_AuxPort, UAVT_HwSettingsRV_AuxPortOption[data->RV_AuxPort]);
			SDL_Log("uavtalk: 	RV_AuxSBusPort: %i (%s)\n", data->RV_AuxSBusPort, UAVT_HwSettingsRV_AuxSBusPortOption[data->RV_AuxSBusPort]);
			SDL_Log("uavtalk: 	RV_FlexiPort: %i (%s)\n", data->RV_FlexiPort, UAVT_HwSettingsRV_FlexiPortOption[data->RV_FlexiPort]);
			SDL_Log("uavtalk: 	RV_TelemetryPort: %i (%s)\n", data->RV_TelemetryPort, UAVT_HwSettingsRV_TelemetryPortOption[data->RV_TelemetryPort]);
			SDL_Log("uavtalk: 	RV_GPSPort: %i (%s)\n", data->RV_GPSPort, UAVT_HwSettingsRV_GPSPortOption[data->RV_GPSPort]);
			SDL_Log("uavtalk: 	TelemetrySpeed: %i (%s)\n", data->TelemetrySpeed, UAVT_HwSettingsTelemetrySpeedOption[data->TelemetrySpeed]);
			SDL_Log("uavtalk: 	GPSSpeed: %i (%s)\n", data->GPSSpeed, UAVT_HwSettingsGPSSpeedOption[data->GPSSpeed]);
			SDL_Log("uavtalk: 	ComUsbBridgeSpeed: %i (%s)\n", data->ComUsbBridgeSpeed, UAVT_HwSettingsComUsbBridgeSpeedOption[data->ComUsbBridgeSpeed]);
			SDL_Log("uavtalk: 	USB_HIDPort: %i (%s)\n", data->USB_HIDPort, UAVT_HwSettingsUSB_HIDPortOption[data->USB_HIDPort]);
			SDL_Log("uavtalk: 	USB_VCPPort: %i (%s)\n", data->USB_VCPPort, UAVT_HwSettingsUSB_VCPPortOption[data->USB_VCPPort]);
			SDL_Log("uavtalk: 	OptionalModules.CameraStab: %i\n", data->OptionalModules.CameraStab);
			SDL_Log("uavtalk: 	OptionalModules.GPS: %i\n", data->OptionalModules.GPS);
			SDL_Log("uavtalk: 	OptionalModules.ComUsbBridge: %i\n", data->OptionalModules.ComUsbBridge);
			SDL_Log("uavtalk: 	OptionalModules.Fault: %i\n", data->OptionalModules.Fault);
			SDL_Log("uavtalk: 	OptionalModules.Altitude: %i\n", data->OptionalModules.Altitude);
			SDL_Log("uavtalk: 	OptionalModules.TxPID: %i\n", data->OptionalModules.TxPID);
			SDL_Log("uavtalk: 	OptionalModules.Autotune: %i\n", data->OptionalModules.Autotune);
			SDL_Log("uavtalk: 	DSMxBind: %i\n", data->DSMxBind);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case I2CSTATS_OBJID: {
			UAVT_I2CStatsData *data = (UAVT_I2CStatsData *)buf;
			memcpy(&uavtalk_I2CStatsData, data, sizeof(UAVT_I2CStatsData));
			SDL_Log("uavtalk: <-I2CStats\n");
			SDL_Log("uavtalk: 	evirq_log[0]: %i\n", data->evirq_log[0]);
			SDL_Log("uavtalk: 	evirq_log[1]: %i\n", data->evirq_log[1]);
			SDL_Log("uavtalk: 	evirq_log[2]: %i\n", data->evirq_log[2]);
			SDL_Log("uavtalk: 	evirq_log[3]: %i\n", data->evirq_log[3]);
			SDL_Log("uavtalk: 	evirq_log[4]: %i\n", data->evirq_log[4]);
			SDL_Log("uavtalk: 	erirq_log[0]: %i\n", data->erirq_log[0]);
			SDL_Log("uavtalk: 	erirq_log[1]: %i\n", data->erirq_log[1]);
			SDL_Log("uavtalk: 	erirq_log[2]: %i\n", data->erirq_log[2]);
			SDL_Log("uavtalk: 	erirq_log[3]: %i\n", data->erirq_log[3]);
			SDL_Log("uavtalk: 	erirq_log[4]: %i\n", data->erirq_log[4]);
			SDL_Log("uavtalk: 	event_errors: %i\n", data->event_errors);
			SDL_Log("uavtalk: 	fsm_errors: %i\n", data->fsm_errors);
			SDL_Log("uavtalk: 	irq_errors: %i\n", data->irq_errors);
			SDL_Log("uavtalk: 	nacks: %i\n", data->nacks);
			SDL_Log("uavtalk: 	timeouts: %i\n", data->timeouts);
			SDL_Log("uavtalk: 	last_error_type: %i (%s)\n", data->last_error_type, UAVT_I2CStatslast_error_typeOption[data->last_error_type]);
			SDL_Log("uavtalk: 	event_log[0]: %i (%s)\n", data->event_log[0], UAVT_I2CStatsevent_logOption[data->event_log[0]]);
			SDL_Log("uavtalk: 	event_log[1]: %i (%s)\n", data->event_log[1], UAVT_I2CStatsevent_logOption[data->event_log[1]]);
			SDL_Log("uavtalk: 	event_log[2]: %i (%s)\n", data->event_log[2], UAVT_I2CStatsevent_logOption[data->event_log[2]]);
			SDL_Log("uavtalk: 	event_log[3]: %i (%s)\n", data->event_log[3], UAVT_I2CStatsevent_logOption[data->event_log[3]]);
			SDL_Log("uavtalk: 	event_log[4]: %i (%s)\n", data->event_log[4], UAVT_I2CStatsevent_logOption[data->event_log[4]]);
			SDL_Log("uavtalk: 	state_log[0]: %i (%s)\n", data->state_log[0], UAVT_I2CStatsstate_logOption[data->state_log[0]]);
			SDL_Log("uavtalk: 	state_log[1]: %i (%s)\n", data->state_log[1], UAVT_I2CStatsstate_logOption[data->state_log[1]]);
			SDL_Log("uavtalk: 	state_log[2]: %i (%s)\n", data->state_log[2], UAVT_I2CStatsstate_logOption[data->state_log[2]]);
			SDL_Log("uavtalk: 	state_log[3]: %i (%s)\n", data->state_log[3], UAVT_I2CStatsstate_logOption[data->state_log[3]]);
			SDL_Log("uavtalk: 	state_log[4]: %i (%s)\n", data->state_log[4], UAVT_I2CStatsstate_logOption[data->state_log[4]]);
			break;
		}
		case MAGNETOMETER_OBJID: {
			UAVT_MagnetometerData *data = (UAVT_MagnetometerData *)buf;
			memcpy(&uavtalk_MagnetometerData, data, sizeof(UAVT_MagnetometerData));
			SDL_Log("uavtalk: <-Magnetometer\n");
			SDL_Log("uavtalk: 	x: %f\n", data->x);
			SDL_Log("uavtalk: 	y: %f\n", data->y);
			SDL_Log("uavtalk: 	z: %f\n", data->z);
			break;
		}
		case MANUALCONTROLCOMMAND_OBJID: {
			UAVT_ManualControlCommandData *data = (UAVT_ManualControlCommandData *)buf;
			memcpy(&uavtalk_ManualControlCommandData, data, sizeof(UAVT_ManualControlCommandData));
			SDL_Log("uavtalk: <-ManualControlCommand\n");
			SDL_Log("uavtalk: 	Throttle: %f\n", data->Throttle);
			SDL_Log("uavtalk: 	Roll: %f\n", data->Roll);
			SDL_Log("uavtalk: 	Pitch: %f\n", data->Pitch);
			SDL_Log("uavtalk: 	Yaw: %f\n", data->Yaw);
			SDL_Log("uavtalk: 	Collective: %f\n", data->Collective);
			SDL_Log("uavtalk: 	Channel[0]: %i\n", data->Channel[0]);
			SDL_Log("uavtalk: 	Channel[1]: %i\n", data->Channel[1]);
			SDL_Log("uavtalk: 	Channel[2]: %i\n", data->Channel[2]);
			SDL_Log("uavtalk: 	Channel[3]: %i\n", data->Channel[3]);
			SDL_Log("uavtalk: 	Channel[4]: %i\n", data->Channel[4]);
			SDL_Log("uavtalk: 	Channel[5]: %i\n", data->Channel[5]);
			SDL_Log("uavtalk: 	Channel[6]: %i\n", data->Channel[6]);
			SDL_Log("uavtalk: 	Channel[7]: %i\n", data->Channel[7]);
			SDL_Log("uavtalk: 	Channel[8]: %i\n", data->Channel[8]);
			SDL_Log("uavtalk: 	Connected: %i (%s)\n", data->Connected, UAVT_ManualControlCommandConnectedOption[data->Connected]);
			break;
		}
		case MANUALCONTROLSETTINGS_OBJID: {
			UAVT_ManualControlSettingsData *data = (UAVT_ManualControlSettingsData *)buf;
			memcpy(&uavtalk_ManualControlSettingsData, data, sizeof(UAVT_ManualControlSettingsData));
			SDL_Log("uavtalk: <-ManualControlSettings\n");
			SDL_Log("uavtalk: 	Deadband: %f\n", data->Deadband);
			SDL_Log("uavtalk: 	ChannelMin.Throttle: %i\n", data->ChannelMin.Throttle);
			SDL_Log("uavtalk: 	ChannelMin.Roll: %i\n", data->ChannelMin.Roll);
			SDL_Log("uavtalk: 	ChannelMin.Pitch: %i\n", data->ChannelMin.Pitch);
			SDL_Log("uavtalk: 	ChannelMin.Yaw: %i\n", data->ChannelMin.Yaw);
			SDL_Log("uavtalk: 	ChannelMin.FlightMode: %i\n", data->ChannelMin.FlightMode);
			SDL_Log("uavtalk: 	ChannelMin.Collective: %i\n", data->ChannelMin.Collective);
			SDL_Log("uavtalk: 	ChannelMin.Accessory0: %i\n", data->ChannelMin.Accessory0);
			SDL_Log("uavtalk: 	ChannelMin.Accessory1: %i\n", data->ChannelMin.Accessory1);
			SDL_Log("uavtalk: 	ChannelMin.Accessory2: %i\n", data->ChannelMin.Accessory2);
			SDL_Log("uavtalk: 	ChannelNeutral.Throttle: %i\n", data->ChannelNeutral.Throttle);
			SDL_Log("uavtalk: 	ChannelNeutral.Roll: %i\n", data->ChannelNeutral.Roll);
			SDL_Log("uavtalk: 	ChannelNeutral.Pitch: %i\n", data->ChannelNeutral.Pitch);
			SDL_Log("uavtalk: 	ChannelNeutral.Yaw: %i\n", data->ChannelNeutral.Yaw);
			SDL_Log("uavtalk: 	ChannelNeutral.FlightMode: %i\n", data->ChannelNeutral.FlightMode);
			SDL_Log("uavtalk: 	ChannelNeutral.Collective: %i\n", data->ChannelNeutral.Collective);
			SDL_Log("uavtalk: 	ChannelNeutral.Accessory0: %i\n", data->ChannelNeutral.Accessory0);
			SDL_Log("uavtalk: 	ChannelNeutral.Accessory1: %i\n", data->ChannelNeutral.Accessory1);
			SDL_Log("uavtalk: 	ChannelNeutral.Accessory2: %i\n", data->ChannelNeutral.Accessory2);
			SDL_Log("uavtalk: 	ChannelMax.Throttle: %i\n", data->ChannelMax.Throttle);
			SDL_Log("uavtalk: 	ChannelMax.Roll: %i\n", data->ChannelMax.Roll);
			SDL_Log("uavtalk: 	ChannelMax.Pitch: %i\n", data->ChannelMax.Pitch);
			SDL_Log("uavtalk: 	ChannelMax.Yaw: %i\n", data->ChannelMax.Yaw);
			SDL_Log("uavtalk: 	ChannelMax.FlightMode: %i\n", data->ChannelMax.FlightMode);
			SDL_Log("uavtalk: 	ChannelMax.Collective: %i\n", data->ChannelMax.Collective);
			SDL_Log("uavtalk: 	ChannelMax.Accessory0: %i\n", data->ChannelMax.Accessory0);
			SDL_Log("uavtalk: 	ChannelMax.Accessory1: %i\n", data->ChannelMax.Accessory1);
			SDL_Log("uavtalk: 	ChannelMax.Accessory2: %i\n", data->ChannelMax.Accessory2);
			SDL_Log("uavtalk: 	ArmedTimeout: %i\n", data->ArmedTimeout);
			SDL_Log("uavtalk: 	ChannelGroups.Throttle: %i\n", data->ChannelGroups.Throttle);
			SDL_Log("uavtalk: 	ChannelGroups.Roll: %i\n", data->ChannelGroups.Roll);
			SDL_Log("uavtalk: 	ChannelGroups.Pitch: %i\n", data->ChannelGroups.Pitch);
			SDL_Log("uavtalk: 	ChannelGroups.Yaw: %i\n", data->ChannelGroups.Yaw);
			SDL_Log("uavtalk: 	ChannelGroups.FlightMode: %i\n", data->ChannelGroups.FlightMode);
			SDL_Log("uavtalk: 	ChannelGroups.Collective: %i\n", data->ChannelGroups.Collective);
			SDL_Log("uavtalk: 	ChannelGroups.Accessory0: %i\n", data->ChannelGroups.Accessory0);
			SDL_Log("uavtalk: 	ChannelGroups.Accessory1: %i\n", data->ChannelGroups.Accessory1);
			SDL_Log("uavtalk: 	ChannelGroups.Accessory2: %i\n", data->ChannelGroups.Accessory2);
			SDL_Log("uavtalk: 	ChannelNumber.Throttle: %i\n", data->ChannelNumber.Throttle);
			SDL_Log("uavtalk: 	ChannelNumber.Roll: %i\n", data->ChannelNumber.Roll);
			SDL_Log("uavtalk: 	ChannelNumber.Pitch: %i\n", data->ChannelNumber.Pitch);
			SDL_Log("uavtalk: 	ChannelNumber.Yaw: %i\n", data->ChannelNumber.Yaw);
			SDL_Log("uavtalk: 	ChannelNumber.FlightMode: %i\n", data->ChannelNumber.FlightMode);
			SDL_Log("uavtalk: 	ChannelNumber.Collective: %i\n", data->ChannelNumber.Collective);
			SDL_Log("uavtalk: 	ChannelNumber.Accessory0: %i\n", data->ChannelNumber.Accessory0);
			SDL_Log("uavtalk: 	ChannelNumber.Accessory1: %i\n", data->ChannelNumber.Accessory1);
			SDL_Log("uavtalk: 	ChannelNumber.Accessory2: %i\n", data->ChannelNumber.Accessory2);
			SDL_Log("uavtalk: 	Arming: %i (%s)\n", data->Arming, UAVT_ManualControlSettingsArmingOption[data->Arming]);
			SDL_Log("uavtalk: 	Stabilization1Settings.Roll: %i\n", data->Stabilization1Settings.Roll);
			SDL_Log("uavtalk: 	Stabilization1Settings.Pitch: %i\n", data->Stabilization1Settings.Pitch);
			SDL_Log("uavtalk: 	Stabilization1Settings.Yaw: %i\n", data->Stabilization1Settings.Yaw);
			SDL_Log("uavtalk: 	Stabilization2Settings.Roll: %i\n", data->Stabilization2Settings.Roll);
			SDL_Log("uavtalk: 	Stabilization2Settings.Pitch: %i\n", data->Stabilization2Settings.Pitch);
			SDL_Log("uavtalk: 	Stabilization2Settings.Yaw: %i\n", data->Stabilization2Settings.Yaw);
			SDL_Log("uavtalk: 	Stabilization3Settings.Roll: %i\n", data->Stabilization3Settings.Roll);
			SDL_Log("uavtalk: 	Stabilization3Settings.Pitch: %i\n", data->Stabilization3Settings.Pitch);
			SDL_Log("uavtalk: 	Stabilization3Settings.Yaw: %i\n", data->Stabilization3Settings.Yaw);
			SDL_Log("uavtalk: 	FlightModeNumber: %i\n", data->FlightModeNumber);
			SDL_Log("uavtalk: 	FlightModePosition[0]: %i (%s)\n", data->FlightModePosition[0], UAVT_ManualControlSettingsFlightModePositionOption[data->FlightModePosition[0]]);
			SDL_Log("uavtalk: 	FlightModePosition[1]: %i (%s)\n", data->FlightModePosition[1], UAVT_ManualControlSettingsFlightModePositionOption[data->FlightModePosition[1]]);
			SDL_Log("uavtalk: 	FlightModePosition[2]: %i (%s)\n", data->FlightModePosition[2], UAVT_ManualControlSettingsFlightModePositionOption[data->FlightModePosition[2]]);
			SDL_Log("uavtalk: 	FlightModePosition[3]: %i (%s)\n", data->FlightModePosition[3], UAVT_ManualControlSettingsFlightModePositionOption[data->FlightModePosition[3]]);
			SDL_Log("uavtalk: 	FlightModePosition[4]: %i (%s)\n", data->FlightModePosition[4], UAVT_ManualControlSettingsFlightModePositionOption[data->FlightModePosition[4]]);
			SDL_Log("uavtalk: 	FlightModePosition[5]: %i (%s)\n", data->FlightModePosition[5], UAVT_ManualControlSettingsFlightModePositionOption[data->FlightModePosition[5]]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case MIXERSETTINGS_OBJID: {
			UAVT_MixerSettingsData *data = (UAVT_MixerSettingsData *)buf;
			memcpy(&uavtalk_MixerSettingsData, data, sizeof(UAVT_MixerSettingsData));
			SDL_Log("uavtalk: <-MixerSettings\n");
			SDL_Log("uavtalk: 	MaxAccel: %f\n", data->MaxAccel);
			SDL_Log("uavtalk: 	FeedForward: %f\n", data->FeedForward);
			SDL_Log("uavtalk: 	AccelTime: %f\n", data->AccelTime);
			SDL_Log("uavtalk: 	DecelTime: %f\n", data->DecelTime);
			SDL_Log("uavtalk: 	ThrottleCurve1.n: %f\n", data->ThrottleCurve1.n);
			SDL_Log("uavtalk: 	ThrottleCurve1.n2: %f\n", data->ThrottleCurve1.n2);
			SDL_Log("uavtalk: 	ThrottleCurve1.n5: %f\n", data->ThrottleCurve1.n5);
			SDL_Log("uavtalk: 	ThrottleCurve1.n7: %f\n", data->ThrottleCurve1.n7);
			SDL_Log("uavtalk: 	ThrottleCurve1.n1: %f\n", data->ThrottleCurve1.n1);
			SDL_Log("uavtalk: 	ThrottleCurve2.n: %f\n", data->ThrottleCurve2.n);
			SDL_Log("uavtalk: 	ThrottleCurve2.n2: %f\n", data->ThrottleCurve2.n2);
			SDL_Log("uavtalk: 	ThrottleCurve2.n5: %f\n", data->ThrottleCurve2.n5);
			SDL_Log("uavtalk: 	ThrottleCurve2.n7: %f\n", data->ThrottleCurve2.n7);
			SDL_Log("uavtalk: 	ThrottleCurve2.n1: %f\n", data->ThrottleCurve2.n1);
			SDL_Log("uavtalk: 	Curve2Source: %i (%s)\n", data->Curve2Source, UAVT_MixerSettingsCurve2SourceOption[data->Curve2Source]);
			SDL_Log("uavtalk: 	Mixer1Type: %i (%s)\n", data->Mixer1Type, UAVT_MixerSettingsMixer1TypeOption[data->Mixer1Type]);
			SDL_Log("uavtalk: 	Mixer1Vector: %i\n", data->Mixer1Vector);
			SDL_Log("uavtalk: 	Mixer2Type: %i\n", data->Mixer2Type);
			SDL_Log("uavtalk: 	Mixer2Vector: %i\n", data->Mixer2Vector);
			SDL_Log("uavtalk: 	Mixer3Type: %i\n", data->Mixer3Type);
			SDL_Log("uavtalk: 	Mixer3Vector: %i\n", data->Mixer3Vector);
			SDL_Log("uavtalk: 	Mixer4Type: %i\n", data->Mixer4Type);
			SDL_Log("uavtalk: 	Mixer4Vector: %i\n", data->Mixer4Vector);
			SDL_Log("uavtalk: 	Mixer5Type: %i\n", data->Mixer5Type);
			SDL_Log("uavtalk: 	Mixer5Vector: %i\n", data->Mixer5Vector);
			SDL_Log("uavtalk: 	Mixer6Type: %i\n", data->Mixer6Type);
			SDL_Log("uavtalk: 	Mixer6Vector: %i\n", data->Mixer6Vector);
			SDL_Log("uavtalk: 	Mixer7Type: %i\n", data->Mixer7Type);
			SDL_Log("uavtalk: 	Mixer7Vector: %i\n", data->Mixer7Vector);
			SDL_Log("uavtalk: 	Mixer8Type: %i\n", data->Mixer8Type);
			SDL_Log("uavtalk: 	Mixer8Vector: %i\n", data->Mixer8Vector);
			SDL_Log("uavtalk: 	Mixer9Type: %i\n", data->Mixer9Type);
			SDL_Log("uavtalk: 	Mixer9Vector: %i\n", data->Mixer9Vector);
			SDL_Log("uavtalk: 	Mixer10Type: %i\n", data->Mixer10Type);
			SDL_Log("uavtalk: 	Mixer10Vector: %i\n", data->Mixer10Vector);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case MIXERSTATUS_OBJID: {
			UAVT_MixerStatusData *data = (UAVT_MixerStatusData *)buf;
			memcpy(&uavtalk_MixerStatusData, data, sizeof(UAVT_MixerStatusData));
			SDL_Log("uavtalk: <-MixerStatus\n");
			SDL_Log("uavtalk: 	Mixer1: %f\n", data->Mixer1);
			SDL_Log("uavtalk: 	Mixer2: %f\n", data->Mixer2);
			SDL_Log("uavtalk: 	Mixer3: %f\n", data->Mixer3);
			SDL_Log("uavtalk: 	Mixer4: %f\n", data->Mixer4);
			SDL_Log("uavtalk: 	Mixer5: %f\n", data->Mixer5);
			SDL_Log("uavtalk: 	Mixer6: %f\n", data->Mixer6);
			SDL_Log("uavtalk: 	Mixer7: %f\n", data->Mixer7);
			SDL_Log("uavtalk: 	Mixer8: %f\n", data->Mixer8);
			SDL_Log("uavtalk: 	Mixer9: %f\n", data->Mixer9);
			SDL_Log("uavtalk: 	Mixer10: %f\n", data->Mixer10);
			break;
		}
		case NEDACCEL_OBJID: {
			UAVT_NedAccelData *data = (UAVT_NedAccelData *)buf;
			memcpy(&uavtalk_NedAccelData, data, sizeof(UAVT_NedAccelData));
			SDL_Log("uavtalk: <-NedAccel\n");
			SDL_Log("uavtalk: 	North: %f\n", data->North);
			SDL_Log("uavtalk: 	East: %f\n", data->East);
			SDL_Log("uavtalk: 	Down: %f\n", data->Down);
			break;
		}
		case OBJECTPERSISTENCE_OBJID: {
			UAVT_ObjectPersistenceData *data = (UAVT_ObjectPersistenceData *)buf;
			memcpy(&uavtalk_ObjectPersistenceData, data, sizeof(UAVT_ObjectPersistenceData));
			SDL_Log("uavtalk: <-ObjectPersistence\n");
			SDL_Log("uavtalk: 	ObjectID: %i\n", data->ObjectID);
			SDL_Log("uavtalk: 	InstanceID: %i\n", data->InstanceID);
			SDL_Log("uavtalk: 	Operation: %i (%s)\n", data->Operation, UAVT_ObjectPersistenceOperationOption[data->Operation]);
			SDL_Log("uavtalk: 	Selection: %i (%s)\n", data->Selection, UAVT_ObjectPersistenceSelectionOption[data->Selection]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case OVEROSYNCSTATS_OBJID: {
			UAVT_OveroSyncStatsData *data = (UAVT_OveroSyncStatsData *)buf;
			memcpy(&uavtalk_OveroSyncStatsData, data, sizeof(UAVT_OveroSyncStatsData));
			SDL_Log("uavtalk: <-OveroSyncStats\n");
			SDL_Log("uavtalk: 	Send: %i\n", data->Send);
			SDL_Log("uavtalk: 	Received: %i\n", data->Received);
			SDL_Log("uavtalk: 	DroppedUpdates: %i\n", data->DroppedUpdates);
			SDL_Log("uavtalk: 	Connected: %i (%s)\n", data->Connected, UAVT_OveroSyncStatsConnectedOption[data->Connected]);
			break;
		}
		case PATHACTION_OBJID: {
			UAVT_PathActionData *data = (UAVT_PathActionData *)buf;
			memcpy(&uavtalk_PathActionData, data, sizeof(UAVT_PathActionData));
			SDL_Log("uavtalk: <-PathAction\n");
			SDL_Log("uavtalk: 	ModeParameters[0]: %f\n", data->ModeParameters[0]);
			SDL_Log("uavtalk: 	ModeParameters[1]: %f\n", data->ModeParameters[1]);
			SDL_Log("uavtalk: 	ModeParameters[2]: %f\n", data->ModeParameters[2]);
			SDL_Log("uavtalk: 	ModeParameters[3]: %f\n", data->ModeParameters[3]);
			SDL_Log("uavtalk: 	ConditionParameters[0]: %f\n", data->ConditionParameters[0]);
			SDL_Log("uavtalk: 	ConditionParameters[1]: %f\n", data->ConditionParameters[1]);
			SDL_Log("uavtalk: 	ConditionParameters[2]: %f\n", data->ConditionParameters[2]);
			SDL_Log("uavtalk: 	ConditionParameters[3]: %f\n", data->ConditionParameters[3]);
			SDL_Log("uavtalk: 	Mode: %i (%s)\n", data->Mode, UAVT_PathActionModeOption[data->Mode]);
			SDL_Log("uavtalk: 	EndCondition: %i (%s)\n", data->EndCondition, UAVT_PathActionEndConditionOption[data->EndCondition]);
			SDL_Log("uavtalk: 	Command: %i (%s)\n", data->Command, UAVT_PathActionCommandOption[data->Command]);
			SDL_Log("uavtalk: 	JumpDestination: %i\n", data->JumpDestination);
			SDL_Log("uavtalk: 	ErrorDestination: %i\n", data->ErrorDestination);
			break;
		}
		case PIPXSETTINGS_OBJID: {
			UAVT_PipXSettingsData *data = (UAVT_PipXSettingsData *)buf;
			memcpy(&uavtalk_PipXSettingsData, data, sizeof(UAVT_PipXSettingsData));
			SDL_Log("uavtalk: <-PipXSettings\n");
			SDL_Log("uavtalk: 	PairID: %i\n", data->PairID);
			SDL_Log("uavtalk: 	Frequency: %i\n", data->Frequency);
			SDL_Log("uavtalk: 	SendTimeout: %i\n", data->SendTimeout);
			SDL_Log("uavtalk: 	TelemetryConfig: %i (%s)\n", data->TelemetryConfig, UAVT_PipXSettingsTelemetryConfigOption[data->TelemetryConfig]);
			SDL_Log("uavtalk: 	TelemetrySpeed: %i (%s)\n", data->TelemetrySpeed, UAVT_PipXSettingsTelemetrySpeedOption[data->TelemetrySpeed]);
			SDL_Log("uavtalk: 	FlexiConfig: %i (%s)\n", data->FlexiConfig, UAVT_PipXSettingsFlexiConfigOption[data->FlexiConfig]);
			SDL_Log("uavtalk: 	FlexiSpeed: %i (%s)\n", data->FlexiSpeed, UAVT_PipXSettingsFlexiSpeedOption[data->FlexiSpeed]);
			SDL_Log("uavtalk: 	VCPConfig: %i (%s)\n", data->VCPConfig, UAVT_PipXSettingsVCPConfigOption[data->VCPConfig]);
			SDL_Log("uavtalk: 	VCPSpeed: %i (%s)\n", data->VCPSpeed, UAVT_PipXSettingsVCPSpeedOption[data->VCPSpeed]);
			SDL_Log("uavtalk: 	RFSpeed: %i (%s)\n", data->RFSpeed, UAVT_PipXSettingsRFSpeedOption[data->RFSpeed]);
			SDL_Log("uavtalk: 	MaxRFPower: %i (%s)\n", data->MaxRFPower, UAVT_PipXSettingsMaxRFPowerOption[data->MaxRFPower]);
			SDL_Log("uavtalk: 	MinPacketSize: %i\n", data->MinPacketSize);
			SDL_Log("uavtalk: 	FrequencyCalibration: %i\n", data->FrequencyCalibration);
			SDL_Log("uavtalk: 	AESKey[0]: %i\n", data->AESKey[0]);
			SDL_Log("uavtalk: 	AESKey[1]: %i\n", data->AESKey[1]);
			SDL_Log("uavtalk: 	AESKey[2]: %i\n", data->AESKey[2]);
			SDL_Log("uavtalk: 	AESKey[3]: %i\n", data->AESKey[3]);
			SDL_Log("uavtalk: 	AESKey[4]: %i\n", data->AESKey[4]);
			SDL_Log("uavtalk: 	AESKey[5]: %i\n", data->AESKey[5]);
			SDL_Log("uavtalk: 	AESKey[6]: %i\n", data->AESKey[6]);
			SDL_Log("uavtalk: 	AESKey[7]: %i\n", data->AESKey[7]);
			SDL_Log("uavtalk: 	AESKey[8]: %i\n", data->AESKey[8]);
			SDL_Log("uavtalk: 	AESKey[9]: %i\n", data->AESKey[9]);
			SDL_Log("uavtalk: 	AESKey[10]: %i\n", data->AESKey[10]);
			SDL_Log("uavtalk: 	AESKey[11]: %i\n", data->AESKey[11]);
			SDL_Log("uavtalk: 	AESKey[12]: %i\n", data->AESKey[12]);
			SDL_Log("uavtalk: 	AESKey[13]: %i\n", data->AESKey[13]);
			SDL_Log("uavtalk: 	AESKey[14]: %i\n", data->AESKey[14]);
			SDL_Log("uavtalk: 	AESKey[15]: %i\n", data->AESKey[15]);
			SDL_Log("uavtalk: 	AESKey[16]: %i\n", data->AESKey[16]);
			SDL_Log("uavtalk: 	AESKey[17]: %i\n", data->AESKey[17]);
			SDL_Log("uavtalk: 	AESKey[18]: %i\n", data->AESKey[18]);
			SDL_Log("uavtalk: 	AESKey[19]: %i\n", data->AESKey[19]);
			SDL_Log("uavtalk: 	AESKey[20]: %i\n", data->AESKey[20]);
			SDL_Log("uavtalk: 	AESKey[21]: %i\n", data->AESKey[21]);
			SDL_Log("uavtalk: 	AESKey[22]: %i\n", data->AESKey[22]);
			SDL_Log("uavtalk: 	AESKey[23]: %i\n", data->AESKey[23]);
			SDL_Log("uavtalk: 	AESKey[24]: %i\n", data->AESKey[24]);
			SDL_Log("uavtalk: 	AESKey[25]: %i\n", data->AESKey[25]);
			SDL_Log("uavtalk: 	AESKey[26]: %i\n", data->AESKey[26]);
			SDL_Log("uavtalk: 	AESKey[27]: %i\n", data->AESKey[27]);
			SDL_Log("uavtalk: 	AESKey[28]: %i\n", data->AESKey[28]);
			SDL_Log("uavtalk: 	AESKey[29]: %i\n", data->AESKey[29]);
			SDL_Log("uavtalk: 	AESKey[30]: %i\n", data->AESKey[30]);
			SDL_Log("uavtalk: 	AESKey[31]: %i\n", data->AESKey[31]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case PIPXSTATUS_OBJID: {
			UAVT_PipXStatusData *data = (UAVT_PipXStatusData *)buf;
			memcpy(&uavtalk_PipXStatusData, data, sizeof(UAVT_PipXStatusData));
			SDL_Log("uavtalk: <-PipXStatus\n");
			SDL_Log("uavtalk: 	MinFrequency: %i\n", data->MinFrequency);
			SDL_Log("uavtalk: 	MaxFrequency: %i\n", data->MaxFrequency);
			SDL_Log("uavtalk: 	FrequencyStepSize: %f\n", data->FrequencyStepSize);
			SDL_Log("uavtalk: 	DeviceID: %i\n", data->DeviceID);
			SDL_Log("uavtalk: 	AFC: %i\n", data->AFC);
			SDL_Log("uavtalk: 	PairIDs[0]: %i\n", data->PairIDs[0]);
			SDL_Log("uavtalk: 	PairIDs[1]: %i\n", data->PairIDs[1]);
			SDL_Log("uavtalk: 	PairIDs[2]: %i\n", data->PairIDs[2]);
			SDL_Log("uavtalk: 	PairIDs[3]: %i\n", data->PairIDs[3]);
			SDL_Log("uavtalk: 	BoardRevision: %i\n", data->BoardRevision);
			SDL_Log("uavtalk: 	Retries: %i\n", data->Retries);
			SDL_Log("uavtalk: 	Errors: %i\n", data->Errors);
			SDL_Log("uavtalk: 	UAVTalkErrors: %i\n", data->UAVTalkErrors);
			SDL_Log("uavtalk: 	Dropped: %i\n", data->Dropped);
			SDL_Log("uavtalk: 	Resets: %i\n", data->Resets);
			SDL_Log("uavtalk: 	TXRate: %i\n", data->TXRate);
			SDL_Log("uavtalk: 	RXRate: %i\n", data->RXRate);
			SDL_Log("uavtalk: 	Description[0]: %i\n", data->Description[0]);
			SDL_Log("uavtalk: 	Description[1]: %i\n", data->Description[1]);
			SDL_Log("uavtalk: 	Description[2]: %i\n", data->Description[2]);
			SDL_Log("uavtalk: 	Description[3]: %i\n", data->Description[3]);
			SDL_Log("uavtalk: 	Description[4]: %i\n", data->Description[4]);
			SDL_Log("uavtalk: 	Description[5]: %i\n", data->Description[5]);
			SDL_Log("uavtalk: 	Description[6]: %i\n", data->Description[6]);
			SDL_Log("uavtalk: 	Description[7]: %i\n", data->Description[7]);
			SDL_Log("uavtalk: 	Description[8]: %i\n", data->Description[8]);
			SDL_Log("uavtalk: 	Description[9]: %i\n", data->Description[9]);
			SDL_Log("uavtalk: 	Description[10]: %i\n", data->Description[10]);
			SDL_Log("uavtalk: 	Description[11]: %i\n", data->Description[11]);
			SDL_Log("uavtalk: 	Description[12]: %i\n", data->Description[12]);
			SDL_Log("uavtalk: 	Description[13]: %i\n", data->Description[13]);
			SDL_Log("uavtalk: 	Description[14]: %i\n", data->Description[14]);
			SDL_Log("uavtalk: 	Description[15]: %i\n", data->Description[15]);
			SDL_Log("uavtalk: 	Description[16]: %i\n", data->Description[16]);
			SDL_Log("uavtalk: 	Description[17]: %i\n", data->Description[17]);
			SDL_Log("uavtalk: 	Description[18]: %i\n", data->Description[18]);
			SDL_Log("uavtalk: 	Description[19]: %i\n", data->Description[19]);
			SDL_Log("uavtalk: 	Description[20]: %i\n", data->Description[20]);
			SDL_Log("uavtalk: 	Description[21]: %i\n", data->Description[21]);
			SDL_Log("uavtalk: 	Description[22]: %i\n", data->Description[22]);
			SDL_Log("uavtalk: 	Description[23]: %i\n", data->Description[23]);
			SDL_Log("uavtalk: 	Description[24]: %i\n", data->Description[24]);
			SDL_Log("uavtalk: 	Description[25]: %i\n", data->Description[25]);
			SDL_Log("uavtalk: 	Description[26]: %i\n", data->Description[26]);
			SDL_Log("uavtalk: 	Description[27]: %i\n", data->Description[27]);
			SDL_Log("uavtalk: 	Description[28]: %i\n", data->Description[28]);
			SDL_Log("uavtalk: 	Description[29]: %i\n", data->Description[29]);
			SDL_Log("uavtalk: 	Description[30]: %i\n", data->Description[30]);
			SDL_Log("uavtalk: 	Description[31]: %i\n", data->Description[31]);
			SDL_Log("uavtalk: 	Description[32]: %i\n", data->Description[32]);
			SDL_Log("uavtalk: 	Description[33]: %i\n", data->Description[33]);
			SDL_Log("uavtalk: 	Description[34]: %i\n", data->Description[34]);
			SDL_Log("uavtalk: 	Description[35]: %i\n", data->Description[35]);
			SDL_Log("uavtalk: 	Description[36]: %i\n", data->Description[36]);
			SDL_Log("uavtalk: 	Description[37]: %i\n", data->Description[37]);
			SDL_Log("uavtalk: 	Description[38]: %i\n", data->Description[38]);
			SDL_Log("uavtalk: 	Description[39]: %i\n", data->Description[39]);
			SDL_Log("uavtalk: 	CPUSerial[0]: %i\n", data->CPUSerial[0]);
			SDL_Log("uavtalk: 	CPUSerial[1]: %i\n", data->CPUSerial[1]);
			SDL_Log("uavtalk: 	CPUSerial[2]: %i\n", data->CPUSerial[2]);
			SDL_Log("uavtalk: 	CPUSerial[3]: %i\n", data->CPUSerial[3]);
			SDL_Log("uavtalk: 	CPUSerial[4]: %i\n", data->CPUSerial[4]);
			SDL_Log("uavtalk: 	CPUSerial[5]: %i\n", data->CPUSerial[5]);
			SDL_Log("uavtalk: 	CPUSerial[6]: %i\n", data->CPUSerial[6]);
			SDL_Log("uavtalk: 	CPUSerial[7]: %i\n", data->CPUSerial[7]);
			SDL_Log("uavtalk: 	CPUSerial[8]: %i\n", data->CPUSerial[8]);
			SDL_Log("uavtalk: 	CPUSerial[9]: %i\n", data->CPUSerial[9]);
			SDL_Log("uavtalk: 	CPUSerial[10]: %i\n", data->CPUSerial[10]);
			SDL_Log("uavtalk: 	CPUSerial[11]: %i\n", data->CPUSerial[11]);
			SDL_Log("uavtalk: 	BoardType: %i\n", data->BoardType);
			SDL_Log("uavtalk: 	FrequencyBand: %i\n", data->FrequencyBand);
			SDL_Log("uavtalk: 	RSSI: %i\n", data->RSSI);
			SDL_Log("uavtalk: 	LinkState: %i (%s)\n", data->LinkState, UAVT_PipXStatusLinkStateOption[data->LinkState]);
			SDL_Log("uavtalk: 	PairSignalStrengths[0]: %i\n", data->PairSignalStrengths[0]);
			SDL_Log("uavtalk: 	PairSignalStrengths[1]: %i\n", data->PairSignalStrengths[1]);
			SDL_Log("uavtalk: 	PairSignalStrengths[2]: %i\n", data->PairSignalStrengths[2]);
			SDL_Log("uavtalk: 	PairSignalStrengths[3]: %i\n", data->PairSignalStrengths[3]);
			break;
		}
		case POSITIONACTUAL_OBJID: {
			UAVT_PositionActualData *data = (UAVT_PositionActualData *)buf;
			memcpy(&uavtalk_PositionActualData, data, sizeof(UAVT_PositionActualData));
			SDL_Log("uavtalk: <-PositionActual\n");
			SDL_Log("uavtalk: 	North: %f\n", data->North);
			SDL_Log("uavtalk: 	East: %f\n", data->East);
			SDL_Log("uavtalk: 	Down: %f\n", data->Down);
			break;
		}
		case POSITIONDESIRED_OBJID: {
			UAVT_PositionDesiredData *data = (UAVT_PositionDesiredData *)buf;
			memcpy(&uavtalk_PositionDesiredData, data, sizeof(UAVT_PositionDesiredData));
			SDL_Log("uavtalk: <-PositionDesired\n");
			SDL_Log("uavtalk: 	North: %f\n", data->North);
			SDL_Log("uavtalk: 	East: %f\n", data->East);
			SDL_Log("uavtalk: 	Down: %f\n", data->Down);
			break;
		}
		case RATEDESIRED_OBJID: {
			UAVT_RateDesiredData *data = (UAVT_RateDesiredData *)buf;
			memcpy(&uavtalk_RateDesiredData, data, sizeof(UAVT_RateDesiredData));
			SDL_Log("uavtalk: <-RateDesired\n");
			SDL_Log("uavtalk: 	Roll: %f\n", data->Roll);
			SDL_Log("uavtalk: 	Pitch: %f\n", data->Pitch);
			SDL_Log("uavtalk: 	Yaw: %f\n", data->Yaw);
			break;
		}
		case RECEIVERACTIVITY_OBJID: {
			UAVT_ReceiverActivityData *data = (UAVT_ReceiverActivityData *)buf;
			memcpy(&uavtalk_ReceiverActivityData, data, sizeof(UAVT_ReceiverActivityData));
			SDL_Log("uavtalk: <-ReceiverActivity\n");
			SDL_Log("uavtalk: 	ActiveGroup: %i (%s)\n", data->ActiveGroup, UAVT_ReceiverActivityActiveGroupOption[data->ActiveGroup]);
			SDL_Log("uavtalk: 	ActiveChannel: %i\n", data->ActiveChannel);
			break;
		}
		case RELAYTUNINGSETTINGS_OBJID: {
			UAVT_RelayTuningSettingsData *data = (UAVT_RelayTuningSettingsData *)buf;
			memcpy(&uavtalk_RelayTuningSettingsData, data, sizeof(UAVT_RelayTuningSettingsData));
			SDL_Log("uavtalk: <-RelayTuningSettings\n");
			SDL_Log("uavtalk: 	RateGain: %f\n", data->RateGain);
			SDL_Log("uavtalk: 	AttitudeGain: %f\n", data->AttitudeGain);
			SDL_Log("uavtalk: 	Amplitude: %f\n", data->Amplitude);
			SDL_Log("uavtalk: 	HysteresisThresh: %i\n", data->HysteresisThresh);
			SDL_Log("uavtalk: 	Mode: %i (%s)\n", data->Mode, UAVT_RelayTuningSettingsModeOption[data->Mode]);
			SDL_Log("uavtalk: 	Behavior: %i (%s)\n", data->Behavior, UAVT_RelayTuningSettingsBehaviorOption[data->Behavior]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case RELAYTUNING_OBJID: {
			UAVT_RelayTuningData *data = (UAVT_RelayTuningData *)buf;
			memcpy(&uavtalk_RelayTuningData, data, sizeof(UAVT_RelayTuningData));
			SDL_Log("uavtalk: <-RelayTuning\n");
			SDL_Log("uavtalk: 	Period.Roll: %f\n", data->Period.Roll);
			SDL_Log("uavtalk: 	Period.Pitch: %f\n", data->Period.Pitch);
			SDL_Log("uavtalk: 	Period.Yaw: %f\n", data->Period.Yaw);
			SDL_Log("uavtalk: 	Gain.Roll: %f\n", data->Gain.Roll);
			SDL_Log("uavtalk: 	Gain.Pitch: %f\n", data->Gain.Pitch);
			SDL_Log("uavtalk: 	Gain.Yaw: %f\n", data->Gain.Yaw);
			break;
		}
		case REVOCALIBRATION_OBJID: {
			UAVT_RevoCalibrationData *data = (UAVT_RevoCalibrationData *)buf;
			memcpy(&uavtalk_RevoCalibrationData, data, sizeof(UAVT_RevoCalibrationData));
			SDL_Log("uavtalk: <-RevoCalibration\n");
			SDL_Log("uavtalk: 	accel_bias.X: %f\n", data->accel_bias.X);
			SDL_Log("uavtalk: 	accel_bias.Y: %f\n", data->accel_bias.Y);
			SDL_Log("uavtalk: 	accel_bias.Z: %f\n", data->accel_bias.Z);
			SDL_Log("uavtalk: 	accel_scale.X: %f\n", data->accel_scale.X);
			SDL_Log("uavtalk: 	accel_scale.Y: %f\n", data->accel_scale.Y);
			SDL_Log("uavtalk: 	accel_scale.Z: %f\n", data->accel_scale.Z);
			SDL_Log("uavtalk: 	accel_var.X: %f\n", data->accel_var.X);
			SDL_Log("uavtalk: 	accel_var.Y: %f\n", data->accel_var.Y);
			SDL_Log("uavtalk: 	accel_var.Z: %f\n", data->accel_var.Z);
			SDL_Log("uavtalk: 	gyro_bias.X: %f\n", data->gyro_bias.X);
			SDL_Log("uavtalk: 	gyro_bias.Y: %f\n", data->gyro_bias.Y);
			SDL_Log("uavtalk: 	gyro_bias.Z: %f\n", data->gyro_bias.Z);
			SDL_Log("uavtalk: 	gyro_scale.X: %f\n", data->gyro_scale.X);
			SDL_Log("uavtalk: 	gyro_scale.Y: %f\n", data->gyro_scale.Y);
			SDL_Log("uavtalk: 	gyro_scale.Z: %f\n", data->gyro_scale.Z);
			SDL_Log("uavtalk: 	gyro_var.X: %f\n", data->gyro_var.X);
			SDL_Log("uavtalk: 	gyro_var.Y: %f\n", data->gyro_var.Y);
			SDL_Log("uavtalk: 	gyro_var.Z: %f\n", data->gyro_var.Z);
			SDL_Log("uavtalk: 	gyro_tempcoeff.X: %f\n", data->gyro_tempcoeff.X);
			SDL_Log("uavtalk: 	gyro_tempcoeff.Y: %f\n", data->gyro_tempcoeff.Y);
			SDL_Log("uavtalk: 	gyro_tempcoeff.Z: %f\n", data->gyro_tempcoeff.Z);
			SDL_Log("uavtalk: 	mag_bias.X: %f\n", data->mag_bias.X);
			SDL_Log("uavtalk: 	mag_bias.Y: %f\n", data->mag_bias.Y);
			SDL_Log("uavtalk: 	mag_bias.Z: %f\n", data->mag_bias.Z);
			SDL_Log("uavtalk: 	mag_scale.X: %f\n", data->mag_scale.X);
			SDL_Log("uavtalk: 	mag_scale.Y: %f\n", data->mag_scale.Y);
			SDL_Log("uavtalk: 	mag_scale.Z: %f\n", data->mag_scale.Z);
			SDL_Log("uavtalk: 	mag_var.X: %f\n", data->mag_var.X);
			SDL_Log("uavtalk: 	mag_var.Y: %f\n", data->mag_var.Y);
			SDL_Log("uavtalk: 	mag_var.Z: %f\n", data->mag_var.Z);
			SDL_Log("uavtalk: 	BiasCorrectedRaw: %i (%s)\n", data->BiasCorrectedRaw, UAVT_RevoCalibrationBiasCorrectedRawOption[data->BiasCorrectedRaw]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case SONARALTITUDE_OBJID: {
			UAVT_SonarAltitudeData *data = (UAVT_SonarAltitudeData *)buf;
			memcpy(&uavtalk_SonarAltitudeData, data, sizeof(UAVT_SonarAltitudeData));
			SDL_Log("uavtalk: <-SonarAltitude\n");
			SDL_Log("uavtalk: 	Altitude: %f\n", data->Altitude);
			break;
		}
		case STABILIZATIONDESIRED_OBJID: {
			UAVT_StabilizationDesiredData *data = (UAVT_StabilizationDesiredData *)buf;
			memcpy(&uavtalk_StabilizationDesiredData, data, sizeof(UAVT_StabilizationDesiredData));
			SDL_Log("uavtalk: <-StabilizationDesired\n");
			SDL_Log("uavtalk: 	Roll: %f\n", data->Roll);
			SDL_Log("uavtalk: 	Pitch: %f\n", data->Pitch);
			SDL_Log("uavtalk: 	Yaw: %f\n", data->Yaw);
			SDL_Log("uavtalk: 	Throttle: %f\n", data->Throttle);
			SDL_Log("uavtalk: 	StabilizationMode.Roll: %i\n", data->StabilizationMode.Roll);
			SDL_Log("uavtalk: 	StabilizationMode.Pitch: %i\n", data->StabilizationMode.Pitch);
			SDL_Log("uavtalk: 	StabilizationMode.Yaw: %i\n", data->StabilizationMode.Yaw);
			break;
		}
		case STABILIZATIONSETTINGS_OBJID: {
			UAVT_StabilizationSettingsData *data = (UAVT_StabilizationSettingsData *)buf;
			memcpy(&uavtalk_StabilizationSettingsData, data, sizeof(UAVT_StabilizationSettingsData));
			SDL_Log("uavtalk: <-StabilizationSettings\n");
			SDL_Log("uavtalk: 	ManualRate.Roll: %f\n", data->ManualRate.Roll);
			SDL_Log("uavtalk: 	ManualRate.Pitch: %f\n", data->ManualRate.Pitch);
			SDL_Log("uavtalk: 	ManualRate.Yaw: %f\n", data->ManualRate.Yaw);
			SDL_Log("uavtalk: 	MaximumRate.Roll: %f\n", data->MaximumRate.Roll);
			SDL_Log("uavtalk: 	MaximumRate.Pitch: %f\n", data->MaximumRate.Pitch);
			SDL_Log("uavtalk: 	MaximumRate.Yaw: %f\n", data->MaximumRate.Yaw);
			SDL_Log("uavtalk: 	RollRatePID.Kp: %f\n", data->RollRatePID.Kp);
			SDL_Log("uavtalk: 	RollRatePID.Ki: %f\n", data->RollRatePID.Ki);
			SDL_Log("uavtalk: 	RollRatePID.Kd: %f\n", data->RollRatePID.Kd);
			SDL_Log("uavtalk: 	RollRatePID.ILimit: %f\n", data->RollRatePID.ILimit);
			SDL_Log("uavtalk: 	PitchRatePID.Kp: %f\n", data->PitchRatePID.Kp);
			SDL_Log("uavtalk: 	PitchRatePID.Ki: %f\n", data->PitchRatePID.Ki);
			SDL_Log("uavtalk: 	PitchRatePID.Kd: %f\n", data->PitchRatePID.Kd);
			SDL_Log("uavtalk: 	PitchRatePID.ILimit: %f\n", data->PitchRatePID.ILimit);
			SDL_Log("uavtalk: 	YawRatePID.Kp: %f\n", data->YawRatePID.Kp);
			SDL_Log("uavtalk: 	YawRatePID.Ki: %f\n", data->YawRatePID.Ki);
			SDL_Log("uavtalk: 	YawRatePID.Kd: %f\n", data->YawRatePID.Kd);
			SDL_Log("uavtalk: 	YawRatePID.ILimit: %f\n", data->YawRatePID.ILimit);
			SDL_Log("uavtalk: 	RollPI.Kp: %f\n", data->RollPI.Kp);
			SDL_Log("uavtalk: 	RollPI.Ki: %f\n", data->RollPI.Ki);
			SDL_Log("uavtalk: 	RollPI.ILimit: %f\n", data->RollPI.ILimit);
			SDL_Log("uavtalk: 	PitchPI.Kp: %f\n", data->PitchPI.Kp);
			SDL_Log("uavtalk: 	PitchPI.Ki: %f\n", data->PitchPI.Ki);
			SDL_Log("uavtalk: 	PitchPI.ILimit: %f\n", data->PitchPI.ILimit);
			SDL_Log("uavtalk: 	YawPI.Kp: %f\n", data->YawPI.Kp);
			SDL_Log("uavtalk: 	YawPI.Ki: %f\n", data->YawPI.Ki);
			SDL_Log("uavtalk: 	YawPI.ILimit: %f\n", data->YawPI.ILimit);
			SDL_Log("uavtalk: 	VbarSensitivity.Roll: %f\n", data->VbarSensitivity.Roll);
			SDL_Log("uavtalk: 	VbarSensitivity.Pitch: %f\n", data->VbarSensitivity.Pitch);
			SDL_Log("uavtalk: 	VbarSensitivity.Yaw: %f\n", data->VbarSensitivity.Yaw);
			SDL_Log("uavtalk: 	VbarRollPI.Kp: %f\n", data->VbarRollPI.Kp);
			SDL_Log("uavtalk: 	VbarRollPI.Ki: %f\n", data->VbarRollPI.Ki);
			SDL_Log("uavtalk: 	VbarPitchPI.Kp: %f\n", data->VbarPitchPI.Kp);
			SDL_Log("uavtalk: 	VbarPitchPI.Ki: %f\n", data->VbarPitchPI.Ki);
			SDL_Log("uavtalk: 	VbarYawPI.Kp: %f\n", data->VbarYawPI.Kp);
			SDL_Log("uavtalk: 	VbarYawPI.Ki: %f\n", data->VbarYawPI.Ki);
			SDL_Log("uavtalk: 	VbarTau: %f\n", data->VbarTau);
			SDL_Log("uavtalk: 	GyroTau: %f\n", data->GyroTau);
			SDL_Log("uavtalk: 	DerivativeGamma: %f\n", data->DerivativeGamma);
			SDL_Log("uavtalk: 	WeakLevelingKp: %f\n", data->WeakLevelingKp);
			SDL_Log("uavtalk: 	RollMax: %i\n", data->RollMax);
			SDL_Log("uavtalk: 	PitchMax: %i\n", data->PitchMax);
			SDL_Log("uavtalk: 	YawMax: %i\n", data->YawMax);
			SDL_Log("uavtalk: 	VbarGyroSuppress: %i\n", data->VbarGyroSuppress);
			SDL_Log("uavtalk: 	VbarPiroComp: %i (%s)\n", data->VbarPiroComp, UAVT_StabilizationSettingsVbarPiroCompOption[data->VbarPiroComp]);
			SDL_Log("uavtalk: 	VbarMaxAngle: %i\n", data->VbarMaxAngle);
			SDL_Log("uavtalk: 	DerivativeCutoff: %i\n", data->DerivativeCutoff);
			SDL_Log("uavtalk: 	MaxAxisLock: %i\n", data->MaxAxisLock);
			SDL_Log("uavtalk: 	MaxAxisLockRate: %i\n", data->MaxAxisLockRate);
			SDL_Log("uavtalk: 	MaxWeakLevelingRate: %i\n", data->MaxWeakLevelingRate);
			SDL_Log("uavtalk: 	LowThrottleZeroIntegral: %i (%s)\n", data->LowThrottleZeroIntegral, UAVT_StabilizationSettingsLowThrottleZeroIntegralOption[data->LowThrottleZeroIntegral]);
			SDL_Log("uavtalk: 	LowThrottleZeroAxis.Roll: %i\n", data->LowThrottleZeroAxis.Roll);
			SDL_Log("uavtalk: 	LowThrottleZeroAxis.Pitch: %i\n", data->LowThrottleZeroAxis.Pitch);
			SDL_Log("uavtalk: 	LowThrottleZeroAxis.Yaw: %i\n", data->LowThrottleZeroAxis.Yaw);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case SYSTEMALARMS_OBJID: {
			UAVT_SystemAlarmsData *data = (UAVT_SystemAlarmsData *)buf;
			memcpy(&uavtalk_SystemAlarmsData, data, sizeof(UAVT_SystemAlarmsData));
			SDL_Log("uavtalk: <-SystemAlarms\n");
			SDL_Log("uavtalk: 	Alarm.OutOfMemory: %i\n", data->Alarm.OutOfMemory);
			SDL_Log("uavtalk: 	Alarm.StackOverflow: %i\n", data->Alarm.StackOverflow);
			SDL_Log("uavtalk: 	Alarm.CPUOverload: %i\n", data->Alarm.CPUOverload);
			SDL_Log("uavtalk: 	Alarm.EventSystem: %i\n", data->Alarm.EventSystem);
			SDL_Log("uavtalk: 	Alarm.Telemetry: %i\n", data->Alarm.Telemetry);
			SDL_Log("uavtalk: 	Alarm.ManualControl: %i\n", data->Alarm.ManualControl);
			SDL_Log("uavtalk: 	Alarm.Actuator: %i\n", data->Alarm.Actuator);
			SDL_Log("uavtalk: 	Alarm.Attitude: %i\n", data->Alarm.Attitude);
			SDL_Log("uavtalk: 	Alarm.Sensors: %i\n", data->Alarm.Sensors);
			SDL_Log("uavtalk: 	Alarm.Stabilization: %i\n", data->Alarm.Stabilization);
			SDL_Log("uavtalk: 	Alarm.Guidance: %i\n", data->Alarm.Guidance);
			SDL_Log("uavtalk: 	Alarm.Battery: %i\n", data->Alarm.Battery);
			SDL_Log("uavtalk: 	Alarm.FlightTime: %i\n", data->Alarm.FlightTime);
			SDL_Log("uavtalk: 	Alarm.I2C: %i\n", data->Alarm.I2C);
			SDL_Log("uavtalk: 	Alarm.GPS: %i\n", data->Alarm.GPS);
			SDL_Log("uavtalk: 	Alarm.BootFault: %i\n", data->Alarm.BootFault);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case SYSTEMSETTINGS_OBJID: {
			UAVT_SystemSettingsData *data = (UAVT_SystemSettingsData *)buf;
			memcpy(&uavtalk_SystemSettingsData, data, sizeof(UAVT_SystemSettingsData));
			SDL_Log("uavtalk: <-SystemSettings\n");
			SDL_Log("uavtalk: 	GUIConfigData[0]: %i\n", data->GUIConfigData[0]);
			SDL_Log("uavtalk: 	GUIConfigData[1]: %i\n", data->GUIConfigData[1]);
			SDL_Log("uavtalk: 	GUIConfigData[2]: %i\n", data->GUIConfigData[2]);
			SDL_Log("uavtalk: 	GUIConfigData[3]: %i\n", data->GUIConfigData[3]);
			SDL_Log("uavtalk: 	AirframeType: %i (%s)\n", data->AirframeType, UAVT_SystemSettingsAirframeTypeOption[data->AirframeType]);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case SYSTEMSTATS_OBJID: {
			UAVT_SystemStatsData *data = (UAVT_SystemStatsData *)buf;
			memcpy(&uavtalk_SystemStatsData, data, sizeof(UAVT_SystemStatsData));
			SDL_Log("uavtalk: <-SystemStats\n");
			SDL_Log("uavtalk: 	FlightTime: %i\n", data->FlightTime);
			SDL_Log("uavtalk: 	EventSystemWarningID: %i\n", data->EventSystemWarningID);
			SDL_Log("uavtalk: 	ObjectManagerCallbackID: %i\n", data->ObjectManagerCallbackID);
			SDL_Log("uavtalk: 	ObjectManagerQueueID: %i\n", data->ObjectManagerQueueID);
			SDL_Log("uavtalk: 	HeapRemaining: %i\n", data->HeapRemaining);
			SDL_Log("uavtalk: 	IRQStackRemaining: %i\n", data->IRQStackRemaining);
			SDL_Log("uavtalk: 	CPULoad: %i\n", data->CPULoad);
			SDL_Log("uavtalk: 	CPUTemp: %i\n", data->CPUTemp);
			break;
		}
		case TASKINFO_OBJID: {
			UAVT_TaskInfoData *data = (UAVT_TaskInfoData *)buf;
			memcpy(&uavtalk_TaskInfoData, data, sizeof(UAVT_TaskInfoData));
			SDL_Log("uavtalk: <-TaskInfo\n");
			SDL_Log("uavtalk: 	StackRemaining: %i\n", data->StackRemaining);
			SDL_Log("uavtalk: 	Running: %i (%s)\n", data->Running, UAVT_TaskInfoRunningOption[data->Running]);
			SDL_Log("uavtalk: 	RunningTime: %i\n", data->RunningTime);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case TXPIDSETTINGS_OBJID: {
			UAVT_TxPIDSettingsData *data = (UAVT_TxPIDSettingsData *)buf;
			memcpy(&uavtalk_TxPIDSettingsData, data, sizeof(UAVT_TxPIDSettingsData));
			SDL_Log("uavtalk: <-TxPIDSettings\n");
			SDL_Log("uavtalk: 	ThrottleRange[0]: %f\n", data->ThrottleRange[0]);
			SDL_Log("uavtalk: 	ThrottleRange[1]: %f\n", data->ThrottleRange[1]);
			SDL_Log("uavtalk: 	MinPID.Instance1: %f\n", data->MinPID.Instance1);
			SDL_Log("uavtalk: 	MinPID.Instance2: %f\n", data->MinPID.Instance2);
			SDL_Log("uavtalk: 	MinPID.Instance3: %f\n", data->MinPID.Instance3);
			SDL_Log("uavtalk: 	MaxPID.Instance1: %f\n", data->MaxPID.Instance1);
			SDL_Log("uavtalk: 	MaxPID.Instance2: %f\n", data->MaxPID.Instance2);
			SDL_Log("uavtalk: 	MaxPID.Instance3: %f\n", data->MaxPID.Instance3);
			SDL_Log("uavtalk: 	UpdateMode: %i (%s)\n", data->UpdateMode, UAVT_TxPIDSettingsUpdateModeOption[data->UpdateMode]);
			SDL_Log("uavtalk: 	Inputs.Instance1: %i\n", data->Inputs.Instance1);
			SDL_Log("uavtalk: 	Inputs.Instance2: %i\n", data->Inputs.Instance2);
			SDL_Log("uavtalk: 	Inputs.Instance3: %i\n", data->Inputs.Instance3);
			SDL_Log("uavtalk: 	PIDs.Instance1: %i\n", data->PIDs.Instance1);
			SDL_Log("uavtalk: 	PIDs.Instance2: %i\n", data->PIDs.Instance2);
			SDL_Log("uavtalk: 	PIDs.Instance3: %i\n", data->PIDs.Instance3);
			SDL_Log("uavtalk: ->send_ack\n");
			break;
		}
		case VELOCITYACTUAL_OBJID: {
			UAVT_VelocityActualData *data = (UAVT_VelocityActualData *)buf;
			memcpy(&uavtalk_VelocityActualData, data, sizeof(UAVT_VelocityActualData));
			SDL_Log("uavtalk: <-VelocityActual\n");
			SDL_Log("uavtalk: 	North: %f\n", data->North);
			SDL_Log("uavtalk: 	East: %f\n", data->East);
			SDL_Log("uavtalk: 	Down: %f\n", data->Down);
			break;
		}
		case VELOCITYDESIRED_OBJID: {
			UAVT_VelocityDesiredData *data = (UAVT_VelocityDesiredData *)buf;
			memcpy(&uavtalk_VelocityDesiredData, data, sizeof(UAVT_VelocityDesiredData));
			SDL_Log("uavtalk: <-VelocityDesired\n");
			SDL_Log("uavtalk: 	North: %f\n", data->North);
			SDL_Log("uavtalk: 	East: %f\n", data->East);
			SDL_Log("uavtalk: 	Down: %f\n", data->Down);
			break;
		}
		case WATCHDOGSTATUS_OBJID: {
			UAVT_WatchdogStatusData *data = (UAVT_WatchdogStatusData *)buf;
			memcpy(&uavtalk_WatchdogStatusData, data, sizeof(UAVT_WatchdogStatusData));
			SDL_Log("uavtalk: <-WatchdogStatus\n");
			SDL_Log("uavtalk: 	BootupFlags: %i\n", data->BootupFlags);
			SDL_Log("uavtalk: 	ActiveFlags: %i\n", data->ActiveFlags);
			break;
		}
		case WAYPOINTACTIVE_OBJID: {
			UAVT_WaypointActiveData *data = (UAVT_WaypointActiveData *)buf;
			memcpy(&uavtalk_WaypointActiveData, data, sizeof(UAVT_WaypointActiveData));
			SDL_Log("uavtalk: <-WaypointActive\n");
			SDL_Log("uavtalk: 	Index: %i\n", data->Index);
			break;
		}
		case WAYPOINT_OBJID: {
			UAVT_WaypointData *data = (UAVT_WaypointData *)buf;
			memcpy(&uavtalk_WaypointData, data, sizeof(UAVT_WaypointData));
			SDL_Log("uavtalk: <-Waypoint\n");
			SDL_Log("uavtalk: 	Position.North: %f\n", data->Position.North);
			SDL_Log("uavtalk: 	Position.East: %f\n", data->Position.East);
			SDL_Log("uavtalk: 	Position.Down: %f\n", data->Position.Down);
			SDL_Log("uavtalk: 	Velocity: %f\n", data->Velocity);
			SDL_Log("uavtalk: 	Action: %i\n", data->Action);
			break;
		}
	}
}

