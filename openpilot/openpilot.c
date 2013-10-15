
#include <all.h>

/* http://wiki.openpilot.org/display/Doc/UAVTalk */

//#define DEBUG

static uint32_t last_connection = 1;
uint8_t openpilot_get = 1;
uint8_t openpilot_set = 0;
uint8_t openpilot_save = 0;

StabilizationSettingsData OpenpilotStabilizationSettings;
HwSettingsData OpenpilotHwSettings;
SystemSettingsData OpenpilotSystemSettings;


static const uint8_t crc_table[256] = {
	0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
	0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65, 0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
	0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
	0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
	0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2, 0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
	0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
	0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
	0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42, 0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
	0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
	0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
	0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c, 0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
	0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
	0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
	0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b, 0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
	0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
	0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3
};

uint8_t PIOS_CRC_updateByte(uint8_t crc, const uint8_t data) {
	return crc_table[crc ^ data];
}

uint8_t PIOS_CRC_updateCRC(uint8_t crc, const uint8_t* data, int32_t length) {
	// use registers for speed
	register int32_t len = length;
	register uint8_t crc8 = crc;
	register const uint8_t *p = data;
	while (len--) {
		crc8 = crc_table[crc8 ^ *p++];
	}
	return crc8;
}


int serial_fd_openpilot = -1;
uint8_t msg_obj_id1 = 0;
uint8_t msg_obj_id2 = 0;
uint8_t msg_obj_id3 = 0;
uint8_t msg_obj_id4 = 0;

uint8_t openpilot_connection_status (void) {
	if (serial_fd_openpilot == -1) {
		return 0;
	}
	return last_connection;
}

void openpilot_send_ack (void) {
#ifdef DEBUG
	printf(">> SEND_ACK\n");
#endif
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x23;	// Command
	openpilot_write_buf[n++] = 0x08;	// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = msg_obj_id1;	// ObjID1
	openpilot_write_buf[n++] = msg_obj_id2;	// ObjID2
	openpilot_write_buf[n++] = msg_obj_id3;	// ObjID3
	openpilot_write_buf[n++] = msg_obj_id4;	// ObjID4
	len = n;
	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
//		printf("%i: %x (%x)\n", n2, openpilot_write_buf[n2], crc);
	}
	openpilot_write_buf[n++] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, n);
}

void openpilot_save_to_flash (void) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
	ObjectPersistenceData data;

	data.ObjectID = STABILIZATIONSETTINGS_OBJID;
	data.InstanceID = 0;
	data.Operation = 2;
	data.Selection = 1;

	len = 18;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x22;	// Command (20, 22)
	openpilot_write_buf[n++] = len;		// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = 0x92;	// ObjID4
	openpilot_write_buf[n++] = 0x32;	// ObjID3
	openpilot_write_buf[n++] = 0xC6;	// ObjID2
	openpilot_write_buf[n++] = 0x99;	// ObjID1

	memcpy(&openpilot_write_buf[8], &data, sizeof(ObjectPersistenceData));

	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, len + 1);
}

void openpilot_send_req (uint8_t status) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
#ifdef DEBUG
	printf(">> SEND_REQ_GCSTELEMETRYSTATS: %i (0x%x)\n", status, status);
#endif
	FlightTelemetryStatsData data;
	data.TxDataRate = 0.0;
	data.RxDataRate = 0.0;
	data.TxFailures = 0;
	data.TxFailures = 0;
	data.TxRetries = 0;
	data.TeleStatus = status;
	len = 29;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x22;	// Command
	openpilot_write_buf[n++] = len;		// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = 0x44;	// ObjID1
	openpilot_write_buf[n++] = 0x27;	// ObjID2
	openpilot_write_buf[n++] = 0xC7;	// ObjID3
	openpilot_write_buf[n++] = 0xAB;	// ObjID4
	memcpy(&openpilot_write_buf[8], &data, sizeof(FlightTelemetryStatsData));
	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
//		printf("%i: %x (%x)\n", n2, openpilot_write_buf[n2], crc);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, len + 1);
}

void openpilot_send_setting_req (void) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
//#ifdef DEBUG
	printf(">> SEND_REQ_OBJECTPERSISTENCE\n");
//#endif
	ObjectPersistenceData data;
	data.ObjectID = 0x3d03de86;
	data.InstanceID = 0;
	data.Operation = 1;
	data.Selection = 0;

	len = 18;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x22;	// Command (20, 22)
	openpilot_write_buf[n++] = len;		// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = 0x92;	// ObjID4
	openpilot_write_buf[n++] = 0x32;	// ObjID3
	openpilot_write_buf[n++] = 0xC6;	// ObjID2
	openpilot_write_buf[n++] = 0x99;	// ObjID1
	memcpy(&openpilot_write_buf[8], &data, sizeof(ObjectPersistenceData));

	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
//		printf("%i: %x (%x)\n", n2, openpilot_write_buf[n2], crc);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, len + 1);
}

void openpilot_request_StabilizationSettings (void) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
	len = 8;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x21;	// Command
	openpilot_write_buf[n++] = len;		// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = 0x86;	// ObjID4
	openpilot_write_buf[n++] = 0xDE;	// ObjID3
	openpilot_write_buf[n++] = 0x03;	// ObjID2
	openpilot_write_buf[n++] = 0x3D;	// ObjID1
	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, len + 1);
}

void openpilot_defaults_StabilizationSettings (StabilizationSettingsData *data) {
	data->ManualRate[0] = 150;
	data->ManualRate[1] = 150;
	data->ManualRate[2] = 150;
	data->MaximumRate[0] = 300;
	data->MaximumRate[1] = 300;
	data->MaximumRate[2] = 300;
	data->RollRatePID[0] = 0.002;
	data->RollRatePID[1] = 0;
	data->RollRatePID[2] = 0;
	data->RollRatePID[3] = 0.3;
	data->PitchRatePID[0] = 0.002;
	data->PitchRatePID[1] = 0;
	data->PitchRatePID[2] = 0;
	data->PitchRatePID[3] = 0.3;
	data->YawRatePID[0] = 0.0035;
	data->YawRatePID[1] = 0.0035;
	data->YawRatePID[2] = 0;
	data->YawRatePID[3] = 0.3;
	data->RollPI[0] = 2;
	data->RollPI[1] = 0;
	data->RollPI[2] = 50;
	data->PitchPI[0] = 2;
	data->PitchPI[1] = 0;
	data->PitchPI[2] = 50;
	data->YawPI[0] = 2;
	data->YawPI[1] = 0;
	data->YawPI[2] = 50;
	data->VbarSensitivity[0] = 0.5;
	data->VbarSensitivity[1] = 0.5;
	data->VbarSensitivity[2] = 0.5;
	data->VbarRollPI[0] = 0.005;
	data->VbarRollPI[1] = 0.002;
	data->VbarPitchPI[0] = 0.005;
	data->VbarPitchPI[1] = 0.002;
	data->VbarYawPI[0] = 0.005;
	data->VbarYawPI[1] = 0.002;
	data->VbarTau = 0.5;
	data->GyroTau = 0.005;
	data->DerivativeGamma = 1;
	data->WeakLevelingKp = 0.1;
	data->RollMax = 55;
	data->PitchMax = 55;
	data->YawMax = 35;
	data->VbarGyroSuppress = 30;
	data->VbarMaxAngle = 10;
	data->DerivativeCutoff = 20;
	data->MaxAxisLock = 15;
	data->MaxAxisLockRate = 2;
	data->MaxWeakLevelingRate = 5;
	data->VbarPiroComp = 0;
	data->LowThrottleZeroIntegral = 1;
}

void openpilot_send_StabilizationSettings (StabilizationSettingsData *data) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
	len = 179;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x22;	// Command (20, 22)
	openpilot_write_buf[n++] = len;		// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = 0x86;	// ObjID4
	openpilot_write_buf[n++] = 0xDE;	// ObjID3
	openpilot_write_buf[n++] = 0x03;	// ObjID2
	openpilot_write_buf[n++] = 0x3D;	// ObjID1
	memcpy(&openpilot_write_buf[8], data, sizeof(StabilizationSettingsData));
	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, len + 1);
}

void openpilot_defaults_HwSettings (HwSettingsData *data) {
	data->DSMxBind = 0;
	data->CC_RcvrPort = 1; // PWM
	data->CC_MainPort = 1; // Telemetry
	data->CC_FlexiPort = 0; // Disabled
	data->RV_RcvrPort = 1; // PWM
	data->RV_AuxPort = 0; // Disabled
	data->RV_AuxSBusPort = 0; // Disabled
	data->RV_FlexiPort = 0; // Disabled
	data->RV_TelemetryPort = 1; // Telemetry
	data->RV_GPSPort = 2; // GPS
	data->TelemetrySpeed = 5; // 57600
	data->GPSSpeed = 5; // 57600
	data->ComUsbBridgeSpeed = 5; // 57600
	data->USB_HIDPort = 0; // USBTelemetry
	data->USB_VCPPort = 2; // Disabled
	data->OptionalModules[0] = 0; // Disabled
	data->OptionalModules[1] = 0; // Disabled
	data->OptionalModules[2] = 0; // Disabled
	data->OptionalModules[3] = 0; // Disabled
	data->OptionalModules[4] = 0; // Disabled
	data->OptionalModules[5] = 0; // Disabled
	data->OptionalModules[6] = 0; // Disabled
}

void openpilot_send_HwSettings (HwSettingsData *data) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
	len = 22;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x22;	// Command (20, 22)
	openpilot_write_buf[n++] = len;		// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = 0x46;	// ObjID4
	openpilot_write_buf[n++] = 0xB5;	// ObjID3
	openpilot_write_buf[n++] = 0xA9;	// ObjID2
	openpilot_write_buf[n++] = 0xA1;	// ObjID1

	memcpy(&openpilot_write_buf[8], &data, sizeof(HwSettingsData));

	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, len + 1);
}

void openpilot_request_HwSettings (void) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
	len = 8;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x21;	// Command
	openpilot_write_buf[n++] = len;		// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = 0x46;	// ObjID4
	openpilot_write_buf[n++] = 0xB5;	// ObjID3
	openpilot_write_buf[n++] = 0xA9;	// ObjID2
	openpilot_write_buf[n++] = 0xA1;	// ObjID1
	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, len + 1);
}

void openpilot_defaults_SystemSettings (SystemSettingsData *data) {
	data->GUIConfigData = 0;
	data->AirframeType = 5; // QuadX
}

void openpilot_send_SystemSettings (SystemSettingsData *data) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
	len = 18;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x22;	// Command (20, 22)
	openpilot_write_buf[n++] = len;		// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = 0x6E;	// ObjID4
	openpilot_write_buf[n++] = 0x32;	// ObjID3
	openpilot_write_buf[n++] = 0x2A;	// ObjID2
	openpilot_write_buf[n++] = 0xC7;	// ObjID1

	memcpy(&openpilot_write_buf[8], &data, sizeof(SystemSettingsData));

	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, len + 1);
}

void openpilot_request_SystemSettings (void) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
	len = 8;
	openpilot_write_buf[n++] = 0x3c;	// Start
	openpilot_write_buf[n++] = 0x21;	// Command
	openpilot_write_buf[n++] = len;		// Len1
	openpilot_write_buf[n++] = 0x00;	// Len2
	openpilot_write_buf[n++] = 0x6E;	// ObjID4
	openpilot_write_buf[n++] = 0x32;	// ObjID3
	openpilot_write_buf[n++] = 0x2A;	// ObjID2
	openpilot_write_buf[n++] = 0xC7;	// ObjID1
	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	serial_write(serial_fd_openpilot, openpilot_write_buf, len + 1);
}

void openpilot_update (void) {
	static uint8_t openpilot_read_buf[256];
	static uint8_t crc = 0;
	static uint8_t res = 0;
	static uint8_t n = 0;
	static uint8_t n2 = 0;
//	static uint8_t n3 = 0;
	static uint8_t data_num = 0;
	static uint8_t data_start = 0;
	static uint8_t data_len = 0;
	if (serial_fd_openpilot >= 0) {
		if (data_start == 0) {
		//	printf("-\n");
			if (serial_read(serial_fd_openpilot, &openpilot_read_buf[0], 1) > 0 && openpilot_read_buf[0] == 0x3c) {
		//		printf("FRAME_START\n");
				data_start = 1;
				data_num = 1;
				data_len = 0;
			}
		} else {
			if ((res = serial_read(serial_fd_openpilot, &openpilot_read_buf[data_num], 1)) > 0) {
		//		printf("+ %i\n", res);
				data_num += res;
				if (data_num > 200) {
					printf("BUFFER FULL\n");
					data_start = 0;
					data_num = 0;
					data_len = 0;
				} if (data_len != 0 && data_num > data_len) {
		//			printf("FRAME_COMPLETE\n");
					for (n = 0; n < data_len; n++) {
		//				printf("## %i/%i, %x (%i)\n", n, data_len, openpilot_read_buf[n], openpilot_read_buf[n]);
						if (openpilot_read_buf[n] == 0x3c) {
							crc = PIOS_CRC_updateByte(0, openpilot_read_buf[n]);
							n++;
							crc = PIOS_CRC_updateByte(crc, openpilot_read_buf[n]);
							uint8_t msg_type = openpilot_read_buf[n++];
							crc = PIOS_CRC_updateByte(crc, openpilot_read_buf[n]);
							uint8_t msg_len = openpilot_read_buf[n++];
							crc = PIOS_CRC_updateByte(crc, openpilot_read_buf[n]);
							uint8_t msg_len2 = openpilot_read_buf[n++];
							crc = PIOS_CRC_updateByte(crc, openpilot_read_buf[n]);
							msg_obj_id1 = openpilot_read_buf[n++];
							crc = PIOS_CRC_updateByte(crc, openpilot_read_buf[n]);
							msg_obj_id2 = openpilot_read_buf[n++];
							crc = PIOS_CRC_updateByte(crc, openpilot_read_buf[n]);
							msg_obj_id3 = openpilot_read_buf[n++];
							crc = PIOS_CRC_updateByte(crc, openpilot_read_buf[n]);
							msg_obj_id4 = openpilot_read_buf[n++];
							uint32_t obj_id = msg_obj_id1 & 0xff;
							obj_id |= msg_obj_id2<<8;
							obj_id |= msg_obj_id3<<16;
							obj_id |= msg_obj_id4<<24;
							if (msg_len2 > 0) {
		//						printf("####### msg-len: %i (type:%i)\n", msg_len, msg_type);
							}
		//					printf("########################### Start msg (type: %x, len: %x/%i) ###########################\n", msg_type, msg_len, msg_len);
		//					printf("########################### Object_ID (%x %x %x %x) ###########################\n", msg_obj_id1, msg_obj_id2, msg_obj_id3, msg_obj_id4);
							for (n2 = 0; n2 < msg_len - 8; n2++) {
		//						printf("####### msg (%i): %x\n", n2, openpilot_read_buf[n]);
								crc = PIOS_CRC_updateByte(crc, openpilot_read_buf[n++]);
							}
		//					printf("crc_test: %x - %x\n", openpilot_read_buf[n], crc);
							if (openpilot_read_buf[n] == crc) {
		//						printf("crc ok (cmd: %x) !\n", obj_id);
		//						printf("################ msg_type (msg_type: %x) !\n", msg_type);
								if (msg_type == 0x23) {
									switch (obj_id) {
										case GCSTELEMETRYSTATS_OBJID: {
//#ifdef DEBUG
											printf("<< GET_ACK GCSTELEMETRYSTATS: %i (0x%x)\n", msg_type, msg_type);
//#endif
											break;
										}
										default: {
//#ifdef DEBUG
											printf("<< GET_ACK UNKNOWN: %i (0x%x)\n", obj_id, obj_id);
//#endif
											break;
										}
									}
									break;
								} else if (msg_type == 0x24) {
									switch (obj_id) {
										default: {
											printf("<< GET_NACK UNKNOWN: %i (0x%x)\n", obj_id, obj_id);
											break;
										}
									}
									break;
								} else if (msg_type == 0x22) {
								} else if (msg_type == 0x20 || msg_type == 0x21) {
								} else {
									printf("################ msg_type (msg_type: %x) !\n", msg_type);
									//Object (OBJ): 0x20, Object request (OBJ_REQ): 0x21, Object with acknowledge request (OBJ_ACK): 0x22, Acknowledge (ACK): 0x23, Negative-Acknowledge (NACK) : 0x24. Note: The most significant 4 bits indicate the protocol version (v2 currently)
								}
								if (msg_type == 0x22) {
									openpilot_send_ack();
								}
								switch (obj_id) {
									case SYSTEMSETTINGS_OBJID: {
										SystemSettingsData *data = (SystemSettingsData *)&openpilot_read_buf[8];
										printf("<< SYSTEMSETTINGS:\\n");
										printf("	GUIConfigData: %i\\n", data->GUIConfigData);
										printf("	AirframeType: %i\\n", data->AirframeType);
										break;
									}
									case OBJECTPERSISTENCE_OBJID: {
										ObjectPersistenceData *data = (ObjectPersistenceData *)&openpilot_read_buf[8];
										printf("<< OBJECTPERSISTENCE: (len=%i; type:0x%x)\n", msg_len, msg_type);
										printf("	ObjectID: %i (0x%x)\n", data->ObjectID, data->ObjectID);
										printf("	InstanceID: %i\n", data->InstanceID);
										printf("	Operation: %i\n", data->Operation);
										printf("	Selection: %i\n", data->Selection);
										break;
									}
									case HWSETTINGS_OBJID: {
										HwSettingsData *data = (HwSettingsData *)&openpilot_read_buf[8];
										memcpy(&OpenpilotHwSettings, data, sizeof(HwSettingsData));
										printf("<< HWSETTINGS:\\n");
										printf("	DSMxBind: %i\n", data->DSMxBind);
										printf("	CC_RcvrPort: %i\n", data->CC_RcvrPort);
										printf("	CC_MainPort: %i\n", data->CC_MainPort);
										printf("	CC_FlexiPort: %i\n", data->CC_FlexiPort);
										printf("	RV_RcvrPort: %i\n", data->RV_RcvrPort);
										printf("	RV_AuxPort: %i\n", data->RV_AuxPort);
										printf("	RV_AuxSBusPort: %i\n", data->RV_AuxSBusPort);
										printf("	RV_FlexiPort: %i\n", data->RV_FlexiPort);
										printf("	RV_TelemetryPort: %i\n", data->RV_TelemetryPort);
										printf("	RV_GPSPort: %i\n", data->RV_GPSPort);
										printf("	TelemetrySpeed: %i\n", data->TelemetrySpeed);
										printf("	GPSSpeed: %i\n", data->GPSSpeed);
										printf("	ComUsbBridgeSpeed: %i\n", data->ComUsbBridgeSpeed);
										printf("	USB_HIDPort: %i\n", data->USB_HIDPort);
										printf("	USB_VCPPort: %i\n", data->USB_VCPPort);
										printf("	OptionalModules(CameraStab): %i\n", data->OptionalModules[0]);
										printf("	OptionalModules(GPS): %i\n", data->OptionalModules[1]);
										printf("	OptionalModules(ComUsbBridge): %i\n", data->OptionalModules[2]);
										printf("	OptionalModules(Fault): %i\n", data->OptionalModules[3]);
										printf("	OptionalModules(Altitude): %i\n", data->OptionalModules[4]);
										printf("	OptionalModules(TxPID): %i\n", data->OptionalModules[5]);
										printf("	OptionalModules(Autotune): %i\n", data->OptionalModules[6]);
										break;
									}
									case STABILIZATIONSETTINGS_OBJID: {
										StabilizationSettingsData *data = (StabilizationSettingsData *)&openpilot_read_buf[8];
										memcpy(&OpenpilotStabilizationSettings, data, sizeof(StabilizationSettingsData));
										printf("<< STABILIZATIONSETTINGS: (len=%i %i; type:0x%x)\n", msg_len, msg_len2, msg_type);
										printf("	ManualRate(Roll): %f\n", data->ManualRate[0]);
										printf("	ManualRate(Pitch): %f\n", data->ManualRate[1]);
										printf("	ManualRate(Yaw): %f\n", data->ManualRate[2]);
										printf("	MaximumRate(Roll): %f\n", data->MaximumRate[0]);
										printf("	MaximumRate(Pitch): %f\n", data->MaximumRate[1]);
										printf("	MaximumRate(Yaw): %f\n", data->MaximumRate[2]);
										printf("	RollRatePID(Kp): %f\n", data->RollRatePID[0]);
										printf("	RollRatePID(Ki): %f\n", data->RollRatePID[1]);
										printf("	RollRatePID(Kd): %f\n", data->RollRatePID[2]);
										printf("	RollRatePID(ILimit): %f\n", data->RollRatePID[3]);
										printf("	PitchRatePID(Kp): %f\n", data->PitchRatePID[0]);
										printf("	PitchRatePID(Ki): %f\n", data->PitchRatePID[1]);
										printf("	PitchRatePID(Kd): %f\n", data->PitchRatePID[2]);
										printf("	PitchRatePID(ILimit): %f\n", data->PitchRatePID[3]);
										printf("	YawRatePID(Kp): %f\n", data->YawRatePID[0]);
										printf("	YawRatePID(Ki): %f\n", data->YawRatePID[1]);
										printf("	YawRatePID(Kd): %f\n", data->YawRatePID[2]);
										printf("	YawRatePID(ILimit): %f\n", data->YawRatePID[3]);
										printf("	RollPI(Kp): %f\n", data->RollPI[0]);
										printf("	RollPI(Ki): %f\n", data->RollPI[1]);
										printf("	RollPI(ILimit): %f\n", data->RollPI[2]);
										printf("	PitchPI(Kp): %f\n", data->PitchPI[0]);
										printf("	PitchPI(Ki): %f\n", data->PitchPI[1]);
										printf("	PitchPI(ILimit): %f\n", data->PitchPI[2]);
										printf("	YawPI(Kp): %f\n", data->YawPI[0]);
										printf("	YawPI(Ki): %f\n", data->YawPI[1]);
										printf("	YawPI(ILimit): %f\n", data->YawPI[2]);
										printf("	VbarSensitivity(Roll): %f\n", data->VbarSensitivity[0]);
										printf("	VbarSensitivity(Pitch): %f\n", data->VbarSensitivity[1]);
										printf("	VbarSensitivity(Yaw): %f\n", data->VbarSensitivity[2]);
										printf("	VbarRollPI(Kp): %f\n", data->VbarRollPI[0]);
										printf("	VbarRollPI(Ki): %f\n", data->VbarRollPI[1]);
										printf("	VbarPitchPI(Kp): %f\n", data->VbarPitchPI[0]);
										printf("	VbarPitchPI(Ki): %f\n", data->VbarPitchPI[1]);
										printf("	VbarYawPI(Kp): %f\n", data->VbarYawPI[0]);
										printf("	VbarYawPI(Ki): %f\n", data->VbarYawPI[1]);
										printf("	VbarTau: %f\n", data->VbarTau);
										printf("	GyroTau: %f\n", data->GyroTau);
										printf("	DerivativeGamma: %f\n", data->DerivativeGamma);
										printf("	WeakLevelingKp: %f\n", data->WeakLevelingKp);
										printf("	RollMax: %i\n", data->RollMax);
										printf("	PitchMax: %i\n", data->PitchMax);
										printf("	YawMax: %i\n", data->YawMax);
										printf("	VbarGyroSuppress: %i\n", data->VbarGyroSuppress);
										printf("	VbarMaxAngle: %i\n", data->VbarMaxAngle);
										printf("	DerivativeCutoff: %i\n", data->DerivativeCutoff);
										printf("	MaxAxisLock: %i\n", data->MaxAxisLock);
										printf("	MaxAxisLockRate: %i\n", data->MaxAxisLockRate);
										printf("	MaxWeakLevelingRate: %i\n", data->MaxWeakLevelingRate);
										printf("	VbarPiroComp: %i\n", data->VbarPiroComp);
										printf("	LowThrottleZeroIntegral: %i\n", data->LowThrottleZeroIntegral);
										break;
									}
									case ATTITUDEACTUAL_OBJID: {
										AttitudeActualData *data = (AttitudeActualData *)&openpilot_read_buf[8];
#ifdef DEBUG
										printf("<< Attitude: %f %f %f\n", data->Roll, data->Pitch, data->Yaw);
#endif
										ModelData.roll = data->Roll;
										ModelData.pitch = data->Pitch;
										ModelData.yaw = data->Yaw;
										redraw_flag = 1;
										break;
									}
									case ACCELS_OBJID: {
										AccelsData *data = (AccelsData *)&openpilot_read_buf[8];
#ifdef DEBUG
										printf("<< Accel: %f %f %f  %f\n", data->x, data->y, data->z, data->temperature);
#endif
										ModelData.acc_x = data->x / 10.0;
										ModelData.acc_y = data->y / 10.0;
										ModelData.acc_z = data->z / 10.0;
										redraw_flag = 1;
										break;
									}
									case GYROS_OBJID: {
										GyrosData *data = (GyrosData *)&openpilot_read_buf[8];
#ifdef DEBUG
										printf("<< Gyro: %f %f %f\n", data->x, data->y, data->z, data->temperature);
#endif
										ModelData.gyro_x = data->x;
										ModelData.gyro_y = data->y;
										ModelData.gyro_z = data->z;
										redraw_flag = 1;
										break;
									}
									case STABILIZATIONDESIRED_OBJID: {
		//								StabilizationDesiredData *data = (StabilizationDesiredData *)&openpilot_read_buf[8];
		//								printf("<< StabilizationDesired: %f %f %f %f\n", data->Roll, data->Pitch, data->Yaw, data->Throttle);
		//								char names[3][30];
		//								char msg[8][30];
		//								strcpy(names[0], "ROLL");
		//								strcpy(names[1], "PITCH");
		//								strcpy(names[2], "YAW");
		//								strcpy(msg[0], "NONE");
		//								strcpy(msg[1], "RATE");
		//								strcpy(msg[2], "ATTITUDE");
		//								strcpy(msg[3], "AXISLOCK");
		//								strcpy(msg[4], "WEAKLEVELING");
		//								strcpy(msg[5], "VIRTUALBAR");
		//								strcpy(msg[6], "RELAYRATE");
		//								strcpy(msg[7], "RELAYATTITUDE");
		//								for (n2 = 0; n2 < 3; n2++) {
		//									printf("	%s: %s\n", names[n2], msg[data->StabilizationMode[n2]]);
		//								}
										break;
									}
									case SYSTEMSTATS_OBJID: {
										SystemStatsData *data = (SystemStatsData *)&openpilot_read_buf[8];
#ifdef DEBUG
										printf("<< System: %i %i %i\n", data->CPULoad, data->CPUTemp, data->FlightTime);
#endif
										ModelData.load = data->CPULoad;
										ModelData.heartbeat = 100;
		
										if (openpilot_get == 1) {
											openpilot_request_StabilizationSettings();
											openpilot_get = 2;
										} else if (openpilot_get == 2) {
											openpilot_request_HwSettings();
											openpilot_get = 0;
										} else if (openpilot_set == 1) {
											openpilot_send_StabilizationSettings(&OpenpilotStabilizationSettings);
											openpilot_set = 2;
										} else if (openpilot_set == 2) {
											openpilot_send_HwSettings(&OpenpilotHwSettings);
											openpilot_set = 0;
										} else if (openpilot_save == 1) {
											openpilot_save_to_flash();
											openpilot_save = 0;
										}
										redraw_flag = 1;
										break;
									}
									case SYSTEMALARMS_OBJID: {
										SystemAlarmsData *data = (SystemAlarmsData *)&openpilot_read_buf[8];
										printf("<< Alarm: \n");
										char names[16][30];
										char msg[5][30];
										strcpy(names[0], "OUTOFMEMORY");
										strcpy(names[1], "STACKOVERFLOW");
										strcpy(names[2], "CPUOVERLOAD");
										strcpy(names[3], "EVENTSYSTEM");
										strcpy(names[4], "TELEMETRY");
										strcpy(names[5], "MANUALCONTROL");
										strcpy(names[6], "ACTUATOR");
										strcpy(names[7], "ATTITUDE");
										strcpy(names[8], "SENSORS");
										strcpy(names[9], "STABILIZATION");
										strcpy(names[10], "GUIDANC");
										strcpy(names[11], "BATTERY");
										strcpy(names[12], "FLIGHTTIME");
										strcpy(names[13], "I2C");
										strcpy(names[14], "GPS");
										strcpy(names[15], "BOOTFAULT");
										strcpy(msg[0], "UNINITIALISED");
										strcpy(msg[1], "OK");
										strcpy(msg[2], "WARNING");
										strcpy(msg[3], "ERROR");
										strcpy(msg[4], "CRITICAL");
										for (n2 = 0; n2 < 16; n2++) {
											if (data->Alarm[n2] != 0 && data->Alarm[n2] != 1) {
												printf("	%s: %s\n", names[n2], msg[data->Alarm[n2]]);
											}
										}
										break;
									}
									case RELAYTUNING_OBJID: {
		//								RelayTuningData *data = (RelayTuningData *)&openpilot_read_buf[8];
		//								printf("<< RELAYTUNING:\n");
		//								char names[16][30];
		//								strcpy(names[0], "ROLL");
		//								strcpy(names[1], "PITCH");
		//								strcpy(names[2], "YAW");
		//								for (n2 = 0; n2 < 3; n2++) {
		//									printf("	Period: %s: %f\n", names[n2], data->Period[n2]);
		//								}
		//								for (n2 = 0; n2 < 3; n2++) {
		//									printf("	Gain: %s: %f\n", names[n2], data->Gain[n2]);
		//								}
										break;
									}
									case RECEIVERACTIVITYDATA_OBJID: {
		//								ReceiverActivityData *data = (ReceiverActivityData *)&openpilot_read_buf[8];
/*
										printf("<< RECEIVERACTIVITYDATA:\n");
										char names[8][30];
										strcpy(names[0], "PWM");
										strcpy(names[1], "PPM");
										strcpy(names[2], "DSM-MAINPORT");
										strcpy(names[3], "DSM-FLEXIPORT");
										strcpy(names[4], "SBUS");
										strcpy(names[5], "GCS");
										strcpy(names[6], "NONE");
										printf("	Active (%s): %i\n", names[data->ActiveGroup], data->ActiveChannel);
*/
										break;
									}
									case ACTUATORDESIRED_OBJID: {
		//								ActuatorDesiredData *data = (ActuatorDesiredData *)&openpilot_read_buf[8];
		//								printf("<< ACTUATORDESIRED\n");
		//								printf("	Roll: %f\n", data->Roll);
		//								printf("	Pitch: %f\n", data->Pitch);
		//								printf("	Yaw: %f\n", data->Yaw);
		//								printf("	Throttle: %f\n", data->Throttle);
		//								ModelData.radio[0] = (int16_t)(data->Roll * 100);
		//								ModelData.radio[1] = (int16_t)(data->Pitch * 100);
		//								ModelData.radio[2] = (int16_t)(data->Yaw * 100);
		//								ModelData.radio[3] = (int16_t)(data->Throttle * 100);
										//data->UpdateTime;
										//data->NumLongUpdates;
										redraw_flag = 1;
										break;
									}
									case ACCESSORYDESIRED_OBJID: {
		//								AccessoryDesiredData *data = (AccessoryDesiredData *)&openpilot_read_buf[8];
		//								printf("<< ACCESSORYDESIRED:\n");
		//								printf("	AccessoryVal: %f\n", data->AccessoryVal);
										break;
									}
									case MANUALCONTROLCOMMAND_OBJID: {
										ManualControlCommandData *data = (ManualControlCommandData *)&openpilot_read_buf[8];
//											printf("<< MANUALCONTROLCOMMAND:\n");
//											printf("	Connected: %i\n", data->Connected);
//											printf("	Roll: %f\n", data->Roll);
//											printf("	Pitch: %f\n", data->Pitch);
//											printf("	Yaw: %f\n", data->Yaw);
//											printf("	Throttle: %f\n", data->Throttle);
//											printf("	Collective: %f\n", data->Collective);
										for (n2 = 0; n2 < 8; n2++) {
//												printf("	Channel: %i: %i %i\n", n2, data->Channel[n2], ((int16_t)data->Channel[n2] - 1500) / 5);
											ModelData.radio[n2] = (int16_t)(data->Channel[n2] - 1500) / 5;
										}
										ModelData.radio[0] = (int16_t)(data->Roll * 100);
										ModelData.radio[1] = (int16_t)(data->Pitch * 100);
										ModelData.radio[2] = (int16_t)(data->Yaw * 100);
										ModelData.radio[3] = (int16_t)(data->Throttle * 100);
										ModelData.radio[4] = (int16_t)(data->Collective * 100);
										redraw_flag = 1;
										break;
									}
									case ACTUATORCOMMAND_OBJID: {
//											ActuatorCommandData *data = (ActuatorCommandData *)&openpilot_read_buf[8];
//											printf("<< ACTUATORCOMMAND:\n");
//											for (n2 = 0; n2 < 8; n2++) {
//												printf("	Channel: %i: %i\n", n2, data->Channel[n2]);
//											}
										//MaxUpdateTime
										//UpdateTime
										//NumFailedUpdates
										break;
									}
									case FLIGHTTELEMETRYSTATS_OBJID: {
										FlightTelemetryStatsData *data = (FlightTelemetryStatsData *)&openpilot_read_buf[8];
										if (data->TeleStatus == 0) {
											printf("<< FlightTelemetryStats: DISCONNECTED\n");
											openpilot_send_req(1);
										} else if (data->TeleStatus == 2) {
											printf("<< FlightTelemetryStats: HANDSHAKEACK\n");
											ModelData.armed = MODEL_DISARMED;
											ModelData.mode = MODEL_MODE_MANUAL;
											openpilot_send_req(3);
											openpilot_get = 1;
											redraw_flag = 1;
										} else if (data->TeleStatus == 3) {
//												printf("<< FlightTelemetryStats: CONNECTED\n");
//												printf("	TxDataRate: %f\n", data->TxDataRate);
//												printf("	RxDataRate: %f\n", data->RxDataRate);
//												printf("	TxFailures: %i\n", data->TxFailures);
//												printf("	RxFailures: %i\n", data->RxFailures);
//												printf("	TxRetries: %i\n", data->TxRetries);
										} else {
											printf("<< FlightTelemetryStats: %i\n", data->TeleStatus);
										}
										break;
									}
									case FLIGHTSTATUSDATA_OBJID: {
										FlightStatusData *data = (FlightStatusData *)&openpilot_read_buf[8];
										char names[8][30];
										printf("<< FLIGHTSTATUSDATA\n");
										strcpy(names[0], "DISARMED");
										strcpy(names[1], "ARMING");
										strcpy(names[2], "ARMED");
										printf("	Armed: %s\n", names[data->Armed]);
										if (data->Armed == 0) {
											ModelData.armed = MODEL_DISARMED;
										} else if (data->Armed == 1) {
											ModelData.armed = MODEL_ARMING;
										} else {
											ModelData.armed = MODEL_ARMED;
										}
										strcpy(names[0], "MANUAL");
										strcpy(names[1], "STABILIZED");
										strcpy(names[2], "STABILIZED2");
										strcpy(names[3], "STABILIZED3");
										strcpy(names[4], "AUTOTUNE");
										strcpy(names[5], "ALTITUDEHOLD");
										strcpy(names[6], "VELOCITYCONTROL");
										strcpy(names[7], "POSITIONHOLD");
										printf("	FlightMode: %s\n", names[data->FlightMode]);
										if (data->FlightMode == 0) {
											ModelData.mode = MODEL_MODE_MANUAL;
										} else {
											ModelData.mode = MODEL_MODE_POSHOLD;
										}
										redraw_flag = 1;
										break;
									}
									case GPSVELOCITYDATA_OBJID: {
//											GPSVelocityData *data = (GPSVelocityData *)&openpilot_read_buf[8];
//											printf("<< GPSVELOCITYDATA:\n");
//											printf("	North: %f\n", data->North);
//											printf("	East: %f\n", data->East);
//											printf("	Down: %f\n", data->Down);
										break;
									}
									case GPSPOSITION_OBJID: {
										GPSPositionData *data = (GPSPositionData *)&openpilot_read_buf[8];
										if (data->Latitude != 0.0) {
											ModelData.p_lat = (float)data->Latitude / 10000000.0;
											ModelData.p_long = (float)data->Longitude / 10000000.0;
											ModelData.p_alt = data->Altitude;
											ModelData.speed = data->Groundspeed;
											ModelData.numSat = data->Satellites;
											ModelData.gpsfix = data->GpsStatus;
											redraw_flag = 1;
										}
										break;
									}
									default: {
										printf("<< Unkown: %x\n", obj_id);
										openpilot_send_ack();
										break;
									}
								}
							}
						}
					}
					data_start = 0;
					data_num = 0;
					data_len = 0;
				} else if (data_num > 2) {
					data_len = openpilot_read_buf[2];
		//			printf("LEN %i\n", data_len);
				}
			}
		}
	}
}

uint8_t openpilot_init (char *port, uint32_t baud) {
	openpilot_defaults_StabilizationSettings(&OpenpilotStabilizationSettings);
	openpilot_defaults_HwSettings(&OpenpilotHwSettings);
	openpilot_defaults_SystemSettings(&OpenpilotSystemSettings);
	openpilot_get = 1;
	printf("init openpilot serial port...\n");
	serial_fd_openpilot = serial_open(port, baud);
	return 0;
}

void openpilot_exit (void) {
	if (serial_fd_openpilot >= 0) {
		serial_close(serial_fd_openpilot);
		serial_fd_openpilot = -1;
	}
}

void openpilot_xml_load (xmlDocPtr doc, xmlNodePtr cur) { 
	model_parseOpenPilot(doc, cur);
}

void openpilot_xml_save (FILE *fr) {
	model_save_xml_OpenPilot(fr);
}

