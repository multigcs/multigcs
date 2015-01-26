
#include <all.h>

#ifndef WINDOWS
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>
#include <libudev.h>
#endif

/* http://wiki.openpilot.org/display/Doc/UAVTalk */

//#define DEBUG

static uint32_t last_connection = 1;
uint8_t openpilot_get = 1;
uint8_t openpilot_set = 0;
uint8_t openpilot_save = 0;
uint8_t msg_obj_id1 = 0;
uint8_t msg_obj_id2 = 0;
uint8_t msg_obj_id3 = 0;
uint8_t msg_obj_id4 = 0;
int serial_fd_openpilot = -1;
int hidraw_fd_openpilot = -1;

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

uint8_t openpilot_connection_status (void) {
	if (serial_fd_openpilot == -1) {
		return 0;
	}
	return last_connection;
}

#ifndef WINDOWS
int openpilot_hidraw_find (void) {
	char device[1024];
	int fd = -1;
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;
	struct udev_device *dev;
	udev = udev_new();
	if (!udev) {
		SDL_Log("uavtalk: Can't create udev\n");
		return -1;
	}
	enumerate = udev_enumerate_new(udev);
	udev_enumerate_add_match_subsystem(enumerate, "hidraw");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);
	udev_list_entry_foreach(dev_list_entry, devices) {
		dev = udev_device_get_parent_with_subsystem_devtype(udev_device_new_from_syspath(udev, udev_list_entry_get_name(dev_list_entry)), "usb", "usb_device");
		if (!dev) {
			return -1;
		}
		if (strcmp("openpilot.org", udev_device_get_sysattr_value(dev,"manufacturer")) == 0 || strcmp("TauLabs.org", udev_device_get_sysattr_value(dev,"manufacturer")) == 0) {
			SDL_Log("uavtalk: VID/PID: %s %s\n", udev_device_get_sysattr_value(dev,"idVendor"), udev_device_get_sysattr_value(dev, "idProduct"));
			SDL_Log("uavtalk: %s\n", udev_device_get_sysattr_value(dev,"manufacturer"));
			SDL_Log("uavtalk: %s\n", udev_device_get_sysattr_value(dev,"product"));
			SDL_Log("uavtalk: serial: %s\n", udev_device_get_sysattr_value(dev, "serial"));
			strcpy(device, udev_device_get_devnode(udev_device_new_from_syspath(udev, udev_list_entry_get_name(dev_list_entry))));
			SDL_Log("uavtalk: device: %s\n", device);
			fd = open(device, O_RDWR|O_NONBLOCK);
			udev_device_unref(dev);
			break;
		}
		udev_device_unref(dev);
	}
	udev_enumerate_unref(enumerate);
	udev_unref(udev);
	return fd;
}

void openpilot_hidraw_write (int fd, uint8_t *data, int len) {
	uint8_t buf[512];
	if (fd >= 0) {
		buf[0] = 2;
		buf[1] = len;
		memcpy(&buf[2], data, len);
		write(fd, buf, len + 2);
	}
}
#endif

void openpilot_write (uint8_t *data, int len) {
	if (serial_fd_openpilot >= 0) {
		serial_write(serial_fd_openpilot, data, len);
	}
#ifndef WINDOWS
	if (hidraw_fd_openpilot >= 0) {
		openpilot_hidraw_write(hidraw_fd_openpilot, data, len);
	}
#endif
}

void uavtalk_send (uint8_t *buf, uint32_t obj_id, uint8_t command, uint16_t len) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t oid4 = ((obj_id) & 0x000000FF);
	uint8_t oid3 = ((obj_id>>8) & 0x000000FF);
	uint8_t oid2 = ((obj_id>>16) & 0x000000FF);
	uint8_t oid1 = ((obj_id>>24) & 0x000000FF);
	len += 8;
	uint8_t len2 = ((len) & 0x000000FF);
	uint8_t len1 = ((len>>8) & 0x000000FF);
	openpilot_write_buf[0] = 0x3c;	// Start
	openpilot_write_buf[1] = command;
	openpilot_write_buf[2] = len2;
	openpilot_write_buf[3] = len1;
	openpilot_write_buf[4] = oid4;
	openpilot_write_buf[5] = oid3;
	openpilot_write_buf[6] = oid2;
	openpilot_write_buf[7] = oid1;
	memcpy(&openpilot_write_buf[8], buf, len);
	for (n = 0; n < len; n++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n]);
	}
	openpilot_write_buf[len] = crc;
	openpilot_write(openpilot_write_buf, len + 1);
}

uint16_t openpilot_add_4byte (uint8_t *buf, uint16_t pos, uint32_t value) {
	uint8_t value4 = ((value) & 0x000000FF);
	uint8_t value3 = ((value>>8) & 0x000000FF);
	uint8_t value2 = ((value>>16) & 0x000000FF);
	uint8_t value1 = ((value>>24) & 0x000000FF);
	buf[pos++] = value4;
	buf[pos++] = value3;
	buf[pos++] = value2;
	buf[pos++] = value1;
	return pos;
}

uint16_t openpilot_add_2byte (uint8_t *buf, uint16_t pos, uint16_t value) {
	uint8_t value2 = ((value) & 0x000000FF);
	uint8_t value1 = ((value>>8) & 0x000000FF);
	buf[pos++] = value2;
	buf[pos++] = value1;
	return pos;
}

uint16_t openpilot_add_1byte (uint8_t *buf, uint16_t pos, uint8_t value) {
	buf[pos++] = value;
	return pos;
}


void uavtalk_request (uint32_t obj_id) {
	uint8_t openpilot_write_buf[256];
#ifdef DEBUG
	SDL_Log("uavtalk: >> SEND_REQ\n");
#endif
	uavtalk_send(openpilot_write_buf, obj_id, 0x21, 0);
}

void uavtalk_send_ack (uint32_t obj_id) {
	uint8_t openpilot_write_buf[256];
#ifdef DEBUG
	SDL_Log("uavtalk: >> SEND_ACK\n");
#endif
	uavtalk_send(openpilot_write_buf, obj_id, 0x3c, 0);
}

void openpilot_send_ack (void) {
#ifdef DEBUG
	SDL_Log("uavtalk: >> SEND_ACK\n");
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
//		SDL_Log("uavtalk: %i: %x (%x)\n", n2, openpilot_write_buf[n2], crc);
	}
	openpilot_write_buf[n++] = crc; 	//Checksum
	openpilot_write(openpilot_write_buf, n);
}

void openpilot_save_to_flash (void) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
	UAVT_ObjectPersistenceData data;

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

	memcpy(&openpilot_write_buf[8], &data, sizeof(UAVT_ObjectPersistenceData));

	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	openpilot_write(openpilot_write_buf, len + 1);

}

void openpilot_send_req (uint8_t status) {
	uint8_t openpilot_write_buf[256];
	uint8_t len = 0;

	UAVT_GCSTelemetryStatsData data;
	data.TxDataRate = 1.0;
	data.RxDataRate = 2.0;
	data.TxFailures = 3;
	data.RxFailures = 4;
	data.TxRetries = 5;
	data.State = status;

	len = openpilot_add_4byte(openpilot_write_buf, len, data.TxDataRate);
	len = openpilot_add_4byte(openpilot_write_buf, len, data.RxDataRate);
	len = openpilot_add_4byte(openpilot_write_buf, len, data.TxFailures);
	len = openpilot_add_4byte(openpilot_write_buf, len, data.RxFailures);
	len = openpilot_add_4byte(openpilot_write_buf, len, data.TxRetries);
	len = openpilot_add_1byte(openpilot_write_buf, len, data.State);

	uavtalk_send(openpilot_write_buf, GCSTELEMETRYSTATS_OBJID, 0x22, len);
}


void openpilot_send_setting_req (void) {
	uint8_t openpilot_write_buf[256];
	uint8_t crc = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t len = 0;
#ifdef DEBUG
	SDL_Log("uavtalk: >> SEND_REQ_OBJECTPERSISTENCE\n");
#endif
	UAVT_ObjectPersistenceData data;
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
	memcpy(&openpilot_write_buf[8], &data, sizeof(UAVT_ObjectPersistenceData));

	crc = 0;
	for (n2 = 0; n2 < len; n2++) {
		crc = PIOS_CRC_updateByte(crc, openpilot_write_buf[n2]);
//		SDL_Log("uavtalk: %i: %x (%x)\n", n2, openpilot_write_buf[n2], crc);
	}
	openpilot_write_buf[len] = crc; 	//Checksum
	openpilot_write(openpilot_write_buf, len + 1);

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
	openpilot_write(openpilot_write_buf, len + 1);

}

void openpilot_decode (char c) {
	static uint8_t openpilot_read_buf[1024];
	static uint8_t crc = 0;
	static uint16_t n = 0;
	static uint16_t n2 = 0;
	static uint16_t n3 = 0;
	static uint16_t data_num = 0;
	static uint16_t data_start = 0;
	static uint16_t data_len = 0;
	if (data_start == 0) {
		if (c == 0x3c) {
//			SDL_Log("uavtalk: FRAME_START\n");
			openpilot_read_buf[data_num] = c;
			data_start = 1;
			data_num = 1;
			data_len = 0;
		}
	} else {
		openpilot_read_buf[data_num] = c;
		data_num += 1;
		if (data_num > 1000) {
			SDL_Log("uavtalk: BUFFER FULL\n");
			data_start = 0;
			data_num = 0;
			data_len = 0;
		} if (data_len != 0 && data_num > data_len) {
//			SDL_Log("uavtalk: FRAME_COMPLETE\n");
			for (n = 0; n < data_len; n++) {
//				SDL_Log("uavtalk: ## %i/%i, 0x%x (%i)\n", n, data_len, openpilot_read_buf[n], openpilot_read_buf[n]);
				if (openpilot_read_buf[n] == 0x3c) {
					n2 = n + 1;
					uint8_t msg_type = openpilot_read_buf[n2++];
					uint16_t msg_len1 = openpilot_read_buf[n2++];
					uint16_t msg_len2 = openpilot_read_buf[n2++];
					msg_obj_id1 = openpilot_read_buf[n2++];
					msg_obj_id2 = openpilot_read_buf[n2++];
					msg_obj_id3 = openpilot_read_buf[n2++];
					msg_obj_id4 = openpilot_read_buf[n2++];
					uint16_t msg_len = msg_len1 & 0xff;
					msg_len |= msg_len2<<8;
					uint32_t obj_id = msg_obj_id1 & 0xff;
					obj_id |= msg_obj_id2<<8;
					obj_id |= msg_obj_id3<<16;
					obj_id |= msg_obj_id4<<24;
					uint8_t org_crc = openpilot_read_buf[n2 + msg_len - 8];
					crc = 0;
					for (n3 = 0; n3 < msg_len; n3++) {
						crc = PIOS_CRC_updateByte(crc, openpilot_read_buf[n + n3]);
					}
					if (org_crc != crc) {
//						printf("#### wrong crc: %i != %i ####\n", org_crc, crc);
					} else {
						if (msg_type == 0x23) {
							switch (obj_id) {
								case GCSTELEMETRYSTATS_OBJID: {
#ifdef DEBUG
									SDL_Log("uavtalk: << GET_ACK GCSTELEMETRYSTATS: %i (0x%x)\n", msg_type, msg_type);
#endif
									break;
								}
								case FLIGHTTELEMETRYSTATS_OBJID: {
#ifdef DEBUG
									SDL_Log("uavtalk: << GET_ACK FLIGHTTELEMETRYSTATS: %i (0x%x)\n", msg_type, msg_type);
#endif
									break;
								}
								default: {
#ifdef DEBUG
									SDL_Log("uavtalk: << GET_ACK UNKNOWN: %i (0x%x)\n", obj_id, obj_id);
#endif
									break;
								}
							}
							break;
						} else if (msg_type == 0x24) {
							switch (obj_id) {
								default: {
									SDL_Log("uavtalk: << GET_NACK UNKNOWN: %i (0x%x)\n", obj_id, obj_id);
									break;
								}
							}
							break;
						} else if (msg_type == 0x22) {
							break;
						} else if (msg_type == 0x21) {
							break;
						} else if (msg_type == 0x20) {
						} else {
							SDL_Log("uavtalk: ################ msg_type (msg_type: %x) !\n", msg_type);
							//Object (OBJ): 0x20, Object request (OBJ_REQ): 0x21, Object with acknowledge request (OBJ_ACK): 0x22, Acknowledge (ACK): 0x23, Negative-Acknowledge (NACK) : 0x24. Note: The most significant 4 bits indicate the protocol version (v2 currently)
						}
						if (msg_type == 0x22) {
							openpilot_send_ack();
						}

						// update modeldata

	uavtalk_decode(obj_id, &openpilot_read_buf[n + 8]);

/*
if (obj_id == HWFLYINGF3_OBJID) {
		for (n3 = 0; n3 < msg_len; n3++) {
			printf("## 0x%x %i ##\n", openpilot_read_buf[n + n3], openpilot_read_buf[n + n3]);
	}
}
*/
						ModelData.roll = uavtalk_AttitudeActualData.Roll;
						ModelData.pitch = uavtalk_AttitudeActualData.Pitch;
						ModelData.yaw = uavtalk_AttitudeActualData.Yaw;
						ModelData.acc_x = uavtalk_AccelsData.x / 10.0;
						ModelData.acc_y = uavtalk_AccelsData.y / 10.0;
						ModelData.acc_z = uavtalk_AccelsData.z / 10.0;
						ModelData.gyro_x = uavtalk_GyrosData.x;
						ModelData.gyro_y = uavtalk_GyrosData.y;
						ModelData.gyro_z = uavtalk_GyrosData.z;
						ModelData.load = uavtalk_SystemStatsData.CPULoad;
/*
 * 						for (n2 = 0; n2 < 8; n2++) {
							ModelData.radio[n2] = (int16_t)(uavtalk_ManualControlCommandData.Channel[n2] - 1500) / 5;
						}
						ModelData.radio[0] = (int16_t)(uavtalk_ManualControlCommandData.Roll * 100);
						ModelData.radio[1] = (int16_t)(uavtalk_ManualControlCommandData.Pitch * 100);
						ModelData.radio[2] = (int16_t)(uavtalk_ManualControlCommandData.Yaw * 100);
						ModelData.radio[3] = (int16_t)(uavtalk_ManualControlCommandData.Throttle * 100);
						ModelData.radio[4] = (int16_t)(uavtalk_ManualControlCommandData.Collective * 100);
						ModelData.chancount = 8;

						if (uavtalk_GPSPositionData.Latitude != 0.0) {
							ModelData.p_lat = (float)uavtalk_GPSPositionData.Latitude / 10000000.0;
							ModelData.p_long = (float)uavtalk_GPSPositionData.Longitude / 10000000.0;
							ModelData.p_alt = uavtalk_GPSPositionData.Altitude;
							ModelData.speed = uavtalk_GPSPositionData.Groundspeed;
							ModelData.numSat = uavtalk_GPSPositionData.Satellites;
							ModelData.gpsfix = uavtalk_GPSPositionData.State;
							ModelData.hdop = uavtalk_GPSPositionData.HDOP;
							ModelData.vdop = uavtalk_GPSPositionData.VDOP;
						}
						if (uavtalk_FlightStatusData.Armed == 0) {
							ModelData.armed = MODEL_DISARMED;
						} else if (uavtalk_FlightStatusData.Armed == 1) {
							ModelData.armed = MODEL_ARMING;
						} else {
							ModelData.armed = MODEL_ARMED;
						}
*/
						if (uavtalk_FlightStatusData.FlightMode == 0) {
							ModelData.mode = MODEL_MODE_MANUAL;
						} else {
							ModelData.mode = MODEL_MODE_POSHOLD;
						}
						ModelData.heartbeat = 100;


//uavtalk_request(MIXERSETTINGS_OBJID);


						if (openpilot_get == 1) {
//							uavtalk_request(STABILIZATIONSETTINGS_OBJID);
							openpilot_get = 2;
						} else if (openpilot_get == 2) {
//							uavtalk_request(HWSETTINGS_OBJID);
							openpilot_get = 0;
						} else if (openpilot_set == 1) {
//							openpilot_send_StabilizationSettings(&OpenpilotStabilizationSettings);
							openpilot_set = 2;
						} else if (openpilot_set == 2) {
//							openpilot_send_HwSettings(&OpenpilotHwSettings);
							openpilot_set = 0;
						} else if (openpilot_save == 1) {
//							openpilot_save_to_flash();
							openpilot_save = 0;
						}

						// connection handshake
						switch (obj_id) {
							case FLIGHTTELEMETRYSTATS_OBJID: {
								UAVT_FlightTelemetryStatsData *data = (UAVT_FlightTelemetryStatsData *)&openpilot_read_buf[n + 8];
								if (data->State == 0) { // -> FLIGHTTELEMETRYSTATS_STATUS_DISCONNECTED
									SDL_Log("uavtalk: << FlightTelemetryStats: DISCONNECTED\n");
									openpilot_send_req(1); // <- GCSTELEMETRYSTATS_STATUS_HANDSHAKEREQ
								} else if (data->State == 2) { // -> FLIGHTTELEMETRYSTATS_STATUS_HANDSHAKEACK
									SDL_Log("uavtalk: << FlightTelemetryStats: HANDSHAKEACK\n");
									openpilot_send_req(3); // <- GCSTELEMETRYSTATS_STATUS_CONNECTED
									redraw_flag = 1;
								} else if (data->State == 3) {
									SDL_Log("uavtalk: << FlightTelemetryStats: CONNECTED\n");

uavtalk_request(HWFLYINGF3_OBJID);

//uavtalk_request(MANUALCONTROLSETTINGS_OBJID);

									openpilot_get = 1;
								} else {
									SDL_Log("uavtalk: << FlightTelemetryStats: %i\n", data->State);
								}
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
//			SDL_Log("uavtalk: LEN %i\n", data_len);
		}
	}
}

void openpilot_update (void) {
	uint8_t buf[1024];
	int res = 0;
	int n = 0;
	if (serial_fd_openpilot >= 0) {
		if (serial_read(serial_fd_openpilot, buf, 1000) > 0) {
			for (n = 0; n < res; n++) {
				openpilot_decode(buf[n]);
			}
		}
	}
#ifndef WINDOWS
	if (hidraw_fd_openpilot >= 0) {
		while ((res = read(hidraw_fd_openpilot, buf, 1000)) > 0) {
			for (n = 0; n < res; n++) {
				openpilot_decode(buf[n]);
			}
		}
	}
#endif
}

uint8_t openpilot_init (char *port, uint32_t baud) {
	openpilot_get = 1;
	SDL_Log("uavtalk: init openpilot serial port...\n");
	serial_fd_openpilot = serial_open(port, baud);
#ifndef WINDOWS
	if (serial_fd_openpilot < 0) {
		hidraw_fd_openpilot = openpilot_hidraw_find();
	}
#endif
	return 0;
}

void openpilot_exit (void) {
	if (serial_fd_openpilot >= 0) {
		serial_close(serial_fd_openpilot);
		serial_fd_openpilot = -1;
	}
#ifndef WINDOWS
	if (hidraw_fd_openpilot >= 0) {
		close(hidraw_fd_openpilot);
		hidraw_fd_openpilot = -1;
	}
#endif
}

void openpilot_xml_load (xmlDocPtr doc, xmlNodePtr cur) { 
//	model_parseOpenPilot(doc, cur);
}

void openpilot_xml_save (FILE *fr) {
}

