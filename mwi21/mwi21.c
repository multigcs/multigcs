
#include <all.h>

extern uint8_t redraw_flag;

int mwi21_serial_fd = -1;
uint8_t mwi21_serial_buf[255];
uint8_t serial_buffer[1024];
uint8_t mwi21_serial_n = 0;
uint8_t mwi21_frame_start = 0;
uint8_t mwi21_frame_len = 0;
uint8_t mwi21_cn = 5;
uint8_t mwi21_rn = 1;
int32_t mwi_status = 0;
uint8_t mwi_pid[16][3];
uint8_t mwi_set_pid[16][3];
uint8_t mwi_set_pid_flag = 0;
volatile int16_t mwi_box[16];
volatile int16_t mwi_set_box[16];
int8_t mwi_set_box_flag = 0;
int8_t mwi_get_pid_flag = 0;
int8_t mwi_get_box_flag = 0;
int8_t mwi_req = 0;
int16_t mwi_i2cErrors = 0;
int16_t mwi_sensors = 0;
int16_t mwi_mag_x = 0;
int16_t mwi_mag_y = 0;
int16_t mwi_mag_z = 0;
int16_t cycleTime = 0;
static uint32_t last_connection = 1;
static int8_t GPS_found = 0;
static int8_t mwi_startup = 0;
char mwi_box_names[16][12];
char mwi_pid_names[16][12];
int8_t mwi_get_boxnames_flag = 0;
int8_t mwi_get_pidnames_flag = 0;

uint8_t mwi21_connection_status (void) {
	if (mwi21_serial_fd == -1) {
		return 0;
	}
	return last_connection;
}

void mwi21_init (char *port, uint32_t baud) {
	uint8_t n = 0;
	mwi21_rn = 1;
	mwi21_serial_n = 0;
	for (n = 0; n < 16; n++) {
		mwi_box_names[n][0] = 0;
		mwi_pid_names[n][0] = 0;
	}
	SDL_Log("init multiwii serial port...\n");
	mwi21_serial_fd = serial_open(port, baud);
}

void mwi21_exit (void) {
	if (mwi21_serial_fd >= 0) {
		serial_close(mwi21_serial_fd);
		mwi21_serial_fd = -1;
	}
}

int8_t mwi21_read8 (void) {
	int8_t t = mwi21_serial_buf[mwi21_cn++] & 0xff;
	return t;
}

int16_t mwi21_read16 (void) {
	int16_t t = mwi21_serial_buf[mwi21_cn++] & 0xff;
	t += mwi21_serial_buf[mwi21_cn++] << 8;
	return t;
}

int32_t mwi21_read32 (void) {
	int32_t t = mwi21_serial_buf[mwi21_cn++] & 0xff;
	t += (mwi21_serial_buf[mwi21_cn++] & 0xff) << 8;
	t += (mwi21_serial_buf[mwi21_cn++] & 0xff) << 16;
	t += (mwi21_serial_buf[mwi21_cn++] & 0xff) << 24;
	return t;
}

void mwi21_get_req (uint8_t id) {
	uint8_t send_buffer[20];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 0;
	send_buffer[4] = id;
	send_buffer[5] = id;
	if (mwi21_serial_fd >= 0) {
		serial_write(mwi21_serial_fd, send_buffer, 6);
	}
}

void mwi21_get_req8 (uint8_t id, int8_t data) {
	uint8_t send_buffer[20];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 1;
	send_buffer[4] = id;
	send_buffer[5] = data;
	send_buffer[6] = 1 ^ id ^ data;
	if (mwi21_serial_fd >= 0) {
		serial_write(mwi21_serial_fd, send_buffer, 7);
	}
}

uint8_t write32 (uint32_t a, uint8_t *send_buffer, uint8_t pos, uint8_t csum) {
    uint8_t t;
    t = a;
    send_buffer[pos] = t;
    csum ^= t;
	pos++;
    t = a >> 8;
    send_buffer[pos] = t;
    csum ^= t;
	pos++;
    t = a >> 16;
    send_buffer[pos] = t;
    csum ^= t;
	pos++;
    t = a >> 24;
    send_buffer[pos] = t;
    csum ^= t;
	pos++;
	return csum;
}

uint8_t write16 (uint16_t a, uint8_t *send_buffer, uint8_t pos, uint8_t csum) {
    uint8_t t;
    t = a;
    send_buffer[pos] = t;
    csum ^= t;
	pos++;
    t = a >> 8;
    send_buffer[pos] = t;
    csum ^= t;
	pos++;
	return csum;
}

void mwi21_send_wp (uint8_t wpnum, float p_lat, float p_long, float p_alt) {
	uint8_t send_buffer[50];
	uint32_t mwi_wp_lat = (uint32_t)(p_lat * 10000000.0);
	uint32_t mwi_wp_lon = (uint32_t)(p_long * 10000000.0);
	uint32_t mwi_wp_alt = (uint32_t)(p_alt);
	int len = 18;
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = len;
	send_buffer[4] = MSP_WP_SET;
	send_buffer[5 + len] = len ^ MSP_WP_SET;
	send_buffer[5] = wpnum; // wp num
	send_buffer[5 + len] ^= wpnum;
	send_buffer[5 + len] = write32(mwi_wp_lat, send_buffer, 6, send_buffer[5 + len]);
	send_buffer[5 + len] = write32(mwi_wp_lon, send_buffer, 10, send_buffer[5 + len]);
	send_buffer[5 + len] = write32(mwi_wp_alt, send_buffer, 14, send_buffer[5 + len]);
	send_buffer[18] = 0; // 16bit
	send_buffer[5 + len] ^= 0;
	send_buffer[19] = 0;
	send_buffer[5 + len] ^= 0;
	send_buffer[20] = 0; // 16bit
	send_buffer[5 + len] ^= 0;
	send_buffer[21] = 0;
	send_buffer[5 + len] ^= 0;
	send_buffer[22] = 0; // 8bit
	send_buffer[5 + len] ^= 0;
	if (mwi21_serial_fd >= 0) {
		serial_write(mwi21_serial_fd, send_buffer, 6 + 32);
	}
}

void mwi21_send_box (void) {
	uint8_t send_buffer[50];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 32;
	send_buffer[4] = MSP_SET_BOX;
	send_buffer[5 + 32] = 32 ^ MSP_SET_BOX;
	uint8_t nn = 0;
	for (nn = 0; nn < 16; nn++) {
		int8_t d1 = (mwi_set_box[nn]>>8);
		int8_t d2 = mwi_set_box[nn];
		send_buffer[5 + nn * 2] = d2;
		send_buffer[5 + nn * 2 + 1] = d1;
		send_buffer[5 + 32] ^= d1;
		send_buffer[5 + 32] ^= d2;
	}
	if (mwi21_serial_fd >= 0) {
		serial_write(mwi21_serial_fd, send_buffer, 6 + 32);
	}
}

void mwi21_send_pid (void) {
	uint8_t send_buffer[50];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 30;
	send_buffer[4] = MSP_SET_PID;
	send_buffer[5 + 30] = 30 ^ MSP_SET_PID;
	uint8_t nn = 0;
	for (nn = 0; nn < 10; nn++) {
		send_buffer[5 + nn * 3] = mwi_set_pid[nn][0];
		send_buffer[5 + nn * 3 + 1] = mwi_set_pid[nn][1];
		send_buffer[5 + nn * 3 + 2] = mwi_set_pid[nn][2];
		send_buffer[5 + 30] ^= mwi_set_pid[nn][0];
		send_buffer[5 + 30] ^= mwi_set_pid[nn][1];
		send_buffer[5 + 30] ^= mwi_set_pid[nn][2];
	}
	if (mwi21_serial_fd >= 0) {
		serial_write(mwi21_serial_fd, send_buffer, 6 + 30);
	}
}

void mwi21_cal_acc (void) {
	mwi_req = MSP_ACC_CALIBRATION;
}

void mwi21_cal_mac (void) {
	mwi_req = MSP_MAG_CALIBRATION;
}

void mwi21_write_rom (void) {
	mwi_req = MSP_EEPROM_WRITE;
}

void mwi21_get_values (void) {
	mwi_get_pid_flag = 1;
	mwi_get_box_flag = 1;
	mwi_get_boxnames_flag = 1;
	mwi_get_pidnames_flag = 1;
}

void mwi21_get_new (void) {
	static uint8_t flag = 0;
	flag = 1 - flag;
	if (flag == 0) {
		if (mwi_get_pid_flag != 0) {
			mwi21_get_req(MSP_PID);
			mwi_get_pid_flag = 0;
		} else if (mwi_get_box_flag != 0) {
			mwi21_get_req8(MSP_BOX, 1);
			mwi_get_box_flag = 0;
		} else if (mwi_get_boxnames_flag != 0) {
			mwi21_get_req(MSP_BOXNAMES);
			mwi_get_boxnames_flag = 0;
		} else if (mwi_get_pidnames_flag != 0) {
			mwi21_get_req(MSP_PIDNAMES);
			mwi_get_pidnames_flag = 0;
		} else if (mwi_set_pid_flag == 1) {
			mwi21_send_pid();
			mwi_set_pid_flag = 0;
			mwi_get_pid_flag = 1;
		} else if (mwi_set_box_flag == 1) {
			mwi21_send_box();
			mwi_set_box_flag = 0;
			mwi_get_box_flag = 1;
		} else if (mwi_req != 0) {
			mwi21_get_req(mwi_req);
			mwi_req = 0;
		} else {
			mwi21_get_req(MSP_ATTITUDE);
		}
	} else if (mwi21_rn == 1) {
		mwi21_get_req(MSP_RC);
		mwi21_rn++;
	} else if (mwi21_rn == 2) {
		mwi21_get_req(MSP_ALTITUDE);
		mwi21_rn++;
	} else if (mwi21_rn == 3) {
		mwi21_get_req(MSP_BAT);
		mwi21_rn++;
	} else if (mwi21_rn == 4) {
		mwi21_get_req(MSP_RAW_GPS);
		mwi21_rn++;
	} else if (mwi21_rn == 5) {
		mwi21_get_req(MSP_STATUS);
		mwi21_rn++;
	} else if (mwi21_rn == 6) {
		mwi21_get_req(MSP_RAW_IMU);
		mwi21_rn++;
	} else if (mwi21_rn == 7) {
		mwi21_get_req8(MSP_WP, 0); // Home
		mwi21_rn++;
	} else if (mwi21_rn == 8) {
		mwi21_get_req8(MSP_WP, 16); // Hold
		mwi21_rn++;
	} else if (mwi21_rn == 9) {
		mwi21_send_wp(0, WayPoints[0].p_lat, WayPoints[0].p_long, WayPoints[0].p_alt);
		mwi21_rn++;
	} else if (mwi21_rn == 10) {
		mwi21_send_wp(16, WayPoints[1].p_lat, WayPoints[1].p_long, WayPoints[1].p_alt);
		mwi21_rn++;
	} else {
		mwi21_rn = 1;
	}
}

void mwi21_update (void) {
	uint8_t nn2 = 0;
	uint8_t cp = 0;
	uint8_t bn = 0;
	uint8_t c = 0;
	uint8_t res = 0;
	static uint8_t last = 0;
	static uint16_t tout = 0;
//	uint8_t n = 0;
	if (mwi21_serial_fd < 0) {
		return;
	}
	if (tout++ > 20) {
		tout = 0;
		mwi21_serial_n = 0;
		mwi21_get_new();
//		SDL_Log("mwi21: timeout\n");
	}
	while ((res = serial_read(mwi21_serial_fd, serial_buffer, 1023)) > 0) {
	    int i = 0;
	    for (i = 0; i < res; i++) {
		mwi21_serial_buf[0] = serial_buffer[i];
		last_connection = time(0);
		c = mwi21_serial_buf[0];
//		SDL_Log("%i: %i (%c)\n", mwi21_serial_n, c, c);
		if (mwi21_serial_n < 250) {
			mwi21_serial_buf[mwi21_serial_n++] = c;
		} else {
			mwi21_serial_n = 0;
		}
		if (c == 'M' && last == '$') {
			mwi21_frame_start = mwi21_serial_n - 2;
			mwi21_frame_len = 0;
//			SDL_Log("mwi21_frame_start: %i\n", mwi21_frame_start);
			tout = 0;
		}
		if (mwi21_serial_n - mwi21_frame_start == 4) {
			mwi21_frame_len = c;
//			SDL_Log("frame_parse: %i - %i\n", mwi21_serial_n - mwi21_frame_start, mwi21_frame_len);
		}
		if (mwi21_serial_buf[2] == '!' && mwi21_serial_n - mwi21_frame_start > 5) {
			if (mwi21_serial_buf[4] != 106) {
//				SDL_Log("## MWI CMD_Error: %i\n", mwi21_serial_buf[4]);
			}
			mwi21_serial_buf[0] = 0;
			mwi21_serial_buf[1] = 0;
			mwi21_serial_buf[2] = 0;
			mwi21_serial_buf[3] = 0;
			mwi21_serial_buf[4] = 0;
			mwi21_serial_n = 0;
			mwi21_frame_start = 0;
			mwi21_frame_len = 0;
		}
		if (mwi21_frame_len > 0 && mwi21_frame_len + 6 == mwi21_serial_n - mwi21_frame_start) {
			uint8_t cmd = mwi21_serial_buf[4 + mwi21_frame_start];
//			SDL_Log("--------------- CMD: %i\n", cmd);

			uint16_t nn = 0;
			uint8_t chksum = 0;
			for (nn = 3; nn < mwi21_frame_len + 5; nn++) {
				chksum ^= mwi21_serial_buf[nn + mwi21_frame_start];
			}

			if (mwi21_serial_buf[mwi21_frame_len + 5 + mwi21_frame_start] != chksum) {
				SDL_Log("mwi21: CSUM-Error (cmd:%i/len:%i):  %i %i %i\n", cmd, mwi21_frame_len, mwi21_serial_buf[mwi21_frame_len + 5 + mwi21_frame_start], chksum, mwi21_frame_start);
				mwi21_serial_n = 0;
				cmd = 0;
				continue;
			} else {
//				SDL_Log("mwi21: CSUM-OK (cmd:%i/len:%i):  %i %i %i\n", cmd, mwi21_frame_len, mwi21_serial_buf[mwi21_frame_len + 5 + mwi21_frame_start], chksum, mwi21_frame_start);
				mwi21_serial_n = 0;
			}
//			SDL_Log("CSUM %i(%i):  %i %i\n", cmd, mwi21_frame_len, mwi21_serial_buf[mwi21_frame_len + 5 + mwi21_frame_start], chksum);
			mwi21_get_new();

			switch (cmd) {
				case MSP_BOXNAMES:
					mwi21_cn = 5 + mwi21_frame_start;
					for (nn2 = 0; nn2 < mwi21_frame_len; nn2++) {
						char c = mwi21_read8();

						if (c == ';') {
							bn++;
							cp = 0;
						} else if (bn < 16 && cp < 11) {
							mwi_box_names[bn][cp + 1] = 0;
							mwi_box_names[bn][cp++] = c;
						}
					}
					redraw_flag = 1;
					mwi_get_boxnames_flag = 0;
					mwi_get_pidnames_flag = 1;
				break;
				case MSP_PIDNAMES:
					mwi21_cn = 5 + mwi21_frame_start;
					for (nn2 = 0; nn2 < mwi21_frame_len; nn2++) {
						char c = mwi21_read8();
						if (c == ';') {
							bn++;
							cp = 0;
						} else if (bn < 16 && cp < 11) {
							mwi_pid_names[bn][cp + 1] = 0;
							mwi_pid_names[bn][cp++] = c;
						}
					}
					redraw_flag = 1;
					mwi_get_pidnames_flag = 0;
				break;
				case MSP_ATTITUDE:
					mwi21_cn = 5 + mwi21_frame_start;
					ModelData.roll = (float)mwi21_read16() / 10.0;
					ModelData.pitch = (float)mwi21_read16() / -10.0;
					ModelData.yaw = (float)mwi21_read16();
					ModelData.heartbeat = 100;
					if (mwi_startup == 0) {
						mwi21_get_values();
					}
					redraw_flag = 1;
				break;
				case MSP_RC:
					mwi21_cn = 5 + mwi21_frame_start;
					ModelData.radio[0] = (mwi21_read16() - 1500) / 5;
					ModelData.radio[1] = (mwi21_read16() - 1500) / 5;
					ModelData.radio[2] = (mwi21_read16() - 1500) / 5;
					ModelData.radio[3] = (mwi21_read16() - 1500) / 5;
					ModelData.radio[4] = (mwi21_read16() - 1500) / 5;
					ModelData.radio[5] = (mwi21_read16() - 1500) / 5;
					ModelData.radio[6] = (mwi21_read16() - 1500) / 5;
					ModelData.radio[7] = (mwi21_read16() - 1500) / 5;
					ModelData.chancount = 8;
					redraw_flag = 1;
				break;
				case MSP_BAT:
					mwi21_cn = 5 + mwi21_frame_start;
					ModelData.voltage = (float)mwi21_read8() / 10.0;
					redraw_flag = 1;
				break;
				case MSP_ALTITUDE:
					mwi21_cn = 5 + mwi21_frame_start;
					ModelData.baro = (float)mwi21_read32() / 100.0;
					ModelData.heartbeat = 100;
					if (GPS_found == 0) {
						ModelData.p_alt = (float)mwi21_read32() / 100.0;
						if (ModelData.p_alt > 8000.0) {
							ModelData.p_alt = ModelData.baro;
						}
					}
					redraw_flag = 1;
				break;
				case MSP_PID:
					mwi_startup = 1;
					mwi21_cn = 5 + mwi21_frame_start;
					uint8_t len1 = mwi21_serial_buf[3 + mwi21_frame_start];
					uint8_t nn1 = 0;
					for (nn1 = 0; nn1 < len1 / 3; nn1++) {
						mwi_pid[nn1][0] = mwi21_read8();
						mwi_pid[nn1][1] = mwi21_read8();
						mwi_pid[nn1][2] = mwi21_read8();
					}
					mwi_get_pid_flag = 0;
					mwi_get_box_flag = 1;
				break;
				case MSP_STATUS:
					mwi21_cn = 5 + mwi21_frame_start;
					cycleTime = mwi21_read16();
					mwi_i2cErrors = mwi21_read16();
					mwi_sensors = mwi21_read16();
					mwi_status = mwi21_read32();
					if (mwi_status & (1<<BOXARM)) {
						ModelData.armed = MODEL_ARMED;
					} else {
						ModelData.armed = MODEL_DISARMED;
					}
					if (mwi_status & (1<<BOXGPSHOLD)) {
						ModelData.mode = MODEL_MODE_POSHOLD;
					} else if (mwi_status & (1<<BOXGPSHOME)) {
						ModelData.mode = MODEL_MODE_RTL;
					} else {
						ModelData.mode = MODEL_MODE_MANUAL;
					}
					redraw_flag = 1;
				break;
				case MSP_BOX:
					mwi21_cn = 5 + mwi21_frame_start;
					uint8_t len = mwi21_serial_buf[3 + mwi21_frame_start];
					uint8_t nn = 0;
					for (nn = 0; nn < len; nn++) {
//						mwi_box[nn] = mwi21_read16();
						mwi_set_box[nn] = mwi21_read16();
					}
					mwi_get_box_flag = 0;
					mwi_get_boxnames_flag = 1;
				break;
				case MSP_RAW_IMU:
					mwi21_cn = 5 + mwi21_frame_start;
					ModelData.acc_x = mwi21_read16();
					ModelData.acc_y = mwi21_read16();
					ModelData.acc_z = mwi21_read16();
					ModelData.gyro_x = mwi21_read16();
					ModelData.gyro_y = mwi21_read16();
					ModelData.gyro_z = mwi21_read16();
					mwi_mag_x = mwi21_read16();
					mwi_mag_y = mwi21_read16();
					mwi_mag_z = mwi21_read16();
					redraw_flag = 1;
				break;
				case MSP_RAW_GPS:
					mwi21_cn = 5 + mwi21_frame_start;
					int8_t GPS_fix = 0;
					int8_t GPS_numSat = 0;
					float GPS_speed = 0;
					static float new_lat = 0.0;
					static float new_lon = 0.0;
					static float new_alt = 0.0;
					GPS_fix = mwi21_read8();
					GPS_numSat = mwi21_read8();
					new_lat = (float)mwi21_read32() / 10000000.0;
					new_lon = (float)mwi21_read32() / 10000000.0;
					new_alt = (float)mwi21_read16();
					GPS_speed = (float)mwi21_read16();
					ModelData.speed = GPS_speed;
					ModelData.gpsfix = GPS_fix;
					ModelData.numSat = GPS_numSat;
					if (new_lat > 0.0 && new_lon > 0.0) {
						ModelData.p_lat = new_lat;
						ModelData.p_long = new_lon;
						ModelData.p_alt = new_alt;
						GPS_found = 1;
						redraw_flag = 1;
					}
				break;
				case MSP_WP:
					mwi21_cn = 5 + mwi21_frame_start;
					int8_t mwi_wp_num = mwi21_read8();
					float mwi_wp_lat = (float)mwi21_read32() / 10000000.0;
					float mwi_wp_lon = (float)mwi21_read32() / 10000000.0;
					int16_t mwi_wp_alt = mwi21_read16();
					int8_t mwi_wp_flag = mwi21_read8();
					if (mwi_wp_num == 0) {
						SDL_Log("# home # %i %f %f %i %i ###\n", mwi_wp_num, mwi_wp_lat, mwi_wp_lon, mwi_wp_alt, mwi_wp_flag);
						if (mwi_wp_lat != 0.0 || mwi_wp_lon != 0.0) {
							WayPoints[0].p_lat = mwi_wp_lat;
							WayPoints[0].p_long = mwi_wp_lon;
							WayPoints[0].p_alt = mwi_wp_alt;
							WayPoints[0].frametype = MAV_FRAME_GLOBAL;
						}
					} else {
						SDL_Log("# hold # %i %f %f %i %i ###\n", mwi_wp_num, mwi_wp_lat, mwi_wp_lon, mwi_wp_alt, mwi_wp_flag);
						if (mwi_wp_lat != 0.0 || mwi_wp_lon != 0.0) {
							strcpy(WayPoints[1].name, "HOLD");
							strcpy(WayPoints[1].command, "WAYPOINT");
							WayPoints[1].p_lat = mwi_wp_lat;
							WayPoints[1].p_long = mwi_wp_lon;
							WayPoints[1].p_alt = mwi_wp_alt;
							WayPoints[1].frametype = MAV_FRAME_GLOBAL;
							WayPoints[2].name[0] = 0;
							WayPoints[2].p_lat = 0.0;
							WayPoints[2].p_long = 0.0;
							WayPoints[2].p_alt = 0.0;
							WayPoints[2].frametype = MAV_FRAME_GLOBAL;
						}
					}
				break;
			}
			mwi21_serial_n = 0;
		}
		last = c;
	    }
	}
}


static void model_parseMWI21Pid (xmlDocPtr doc, xmlNodePtr cur, uint16_t pid) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"p"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_pid[pid][0] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"i"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_pid[pid][1] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"d"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_pid[pid][2] = atoi((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void model_parseMWI21Box (xmlDocPtr doc, xmlNodePtr cur, uint16_t box) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"value"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_box[box] = atoi((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

void mwi21_xml_load (xmlDocPtr doc, xmlNodePtr cur) { 
	uint16_t pid = 0;
	uint16_t box = 0;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"pid"))) {
			model_parseMWI21Pid (doc, cur, pid++);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"box"))) {
			model_parseMWI21Box (doc, cur, box++);
		}
		cur = cur->next;
	}
	return;
}

void mwi21_xml_save (FILE *fr) {
	int16_t n = 0;
	fprintf(fr, " <mwi21>\n");
	for (n = 0; n < 16; n++) {
		fprintf(fr, "  <pid><id>%i</id><p>%i</p><i>%i</i><d>%i</d></pid>\n", n, mwi_pid[n][0], mwi_pid[n][1], mwi_pid[n][2]);
	}
	for (n = 0; n < 16; n++) {
		fprintf(fr, "  <box><id>%i</id><value>%i</value></box>\n", n, mwi_box[n]);
	}
	fprintf(fr, " </mwi21>\n");
}

static void mwi21_html_page (char *content, uint8_t mode) {
	char tmp_str[512];
	int n3 = 0;
	int lc = 0;
	uint16_t n = 0;
	uint16_t n2 = 0;
	content[0] = 0;
	webserv_html_head(content, "MWII");
	strcat(content, "<SCRIPT>\n");
	strcat(content, "function check_value(row, col) {\n");
	strcat(content, "	var value = document.getElementById(row + \"-\" + col).value;\n");
	strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
	strcat(content, "	xmlHttp.open(\"GET\", \"/mwii_pid.html?\" + row + \",\" + col + \"=\" + value, true);\n");
	strcat(content, "	xmlHttp.send(null);\n");
	strcat(content, "}\n");
	strcat(content, "</SCRIPT>\n");
	webserv_html_start(content, 0);
	strcat(content, "<TABLE class=\"main\">\n");
	strcat(content, "<TR class=\"main\"><TD width=\"160px\" valign=\"top\">\n");
	strcat(content, "<TABLE width=\"100%\">\n");
	strcat(content, "<TR class=\"thead\"><TH>MODE</TH></TR>\n");
	strcat(content, "<TR class=\"first\"><TD><A href=\"/mwii.html\">PID's</A></TD></TR>");
	strcat(content, "<TR class=\"first\"><TD><A href=\"/mwii_box.html\">BOX's</A></TD></TR>");
	strcat(content, "</TABLE>\n");
	strcat(content, "</TD><TD valign=\"top\" width=\"20px\">&nbsp;</TD><TD valign=\"top\">\n");
	if (mode == 1) {
		strcat(content, "<TABLE width=\"100%\">\n");
		strcat(content, "<TR class=\"thead\"><TH>NAME</TH><TH colspan=\"3\">AUX1</TH><TH colspan=\"3\">AUX2</TH><TH colspan=\"3\">AUX3</TH><TH colspan=\"3\">AUX4</TH></TR>\n");
		strcat(content, "<TR class=\"thead\"><TH>&nbsp;</TH><TH>MIN</TH><TH>MID</TH><TH>MAX</TH><TH>MIN</TH><TH>MID</TH><TH>MAX</TH><TH>MIN</TH><TH>MID</TH><TH>MAX</TH><TH>MIN</TH><TH>MID</TH><TH>MAX</TH></TR>\n");
		lc = 0;
		for (n = 0; n < 16; n++) {
			if (mwi_box_names[n][0] != 0) {
				lc = 1 - lc;
				if (lc == 0) {
					strcat(content, "<TR class=\"first\">");
				} else {
					strcat(content, "<TR class=\"sec\">");
				}
				sprintf(tmp_str, "<TD>%s</TD>", mwi_box_names[n]);
				strcat(content, tmp_str);
				for (n2 = 0; n2 < 12; n2++) {
					if (mwi_set_box[n] & (1<<n2)) {
						sprintf(tmp_str, "<TD class=\"mboxsel\" onClick=\"document.location.href='/mwii_set.html?%i';\">&nbsp;</TD>\n", n3);
					} else {
						sprintf(tmp_str, "<TD class=\"mbox\" onClick=\"document.location.href='/mwii_set.html?%i';\">&nbsp;</TD>\n", n3);
					}
					strcat(content, tmp_str);
					n3++;
				}
				strcat(content, "</TR>\n");
			}
		}
		strcat(content, "</TABLE>\n");
	} else {
		strcat(content, "<TABLE width=\"100%\">\n");
		strcat(content, "<TR class=\"thead\"><TH>NAME</TH><TH>P</TH><TH>I</TH><TH>D</TH></TR>\n");
		n3 = 0;
		lc = 0;
		for (n = 0; n < 14; n++) {
			if (mwi_pid_names[n][0] != 0) {
				lc = 1 - lc;
				if (lc == 0) {
					strcat(content, "<TR class=\"first\">");
				} else {
					strcat(content, "<TR class=\"sec\">");
				}
				sprintf(tmp_str, "<TD>%s</TD>", mwi_pid_names[n]);
				strcat(content, tmp_str);
				sprintf(tmp_str, "<TD align=\"center\"><INPUT class=\"form-input\" onchange=\"check_value(%i,%i);\" id=\"%i-%i\" value=\"%0.1f\" type=\"text\"></TD>", n, 0, n, 0, (float)mwi_pid[n][0] / 10.0);
				strcat(content, tmp_str);
				sprintf(tmp_str, "<TD align=\"center\"><INPUT class=\"form-input\" onchange=\"check_value(%i,%i);\" id=\"%i-%i\" value=\"%0.3f\" type=\"text\"></TD>", n, 1, n, 1, (float)mwi_pid[n][1] / 1000.0);
				strcat(content, tmp_str);
				sprintf(tmp_str, "<TD align=\"center\"><INPUT class=\"form-input\" onchange=\"check_value(%i,%i);\" id=\"%i-%i\" value=\"%i\" type=\"text\"></TD>", n, 2, n, 2, mwi_pid[n][2]);
				strcat(content, tmp_str);
				strcat(content, "</TR>\n");
			}
		}
		strcat(content, "</TABLE>\n");
	}
	strcat(content, "</TD></TR></TABLE>\n");
	webserv_html_stop(content);
}

void mwi21_web_get (char *url, char *content, char *type) {
	if (strncmp(url, "/mwii.html", 10) == 0) {
		mwi21_html_page(content, 0);
		strcpy(type, "text/html");
	} else if (strncmp(url, "/mwii_box.html", 14) == 0) {
		mwi21_html_page(content, 1);
		strcpy(type, "text/html");
	} else if (strncmp(url, "/mwii_pid.html?", 14) == 0) {
		int n = 0;
		int row = 0;
		int col = 0;
		float val = 0.0;
		sscanf(url + 15, "%i,%i=%f", &row, &col, &val);
		for (n = 0; n < 16; n++) {
			mwi_set_pid[n][0] = mwi_pid[n][0];
			mwi_set_pid[n][1] = mwi_pid[n][1];
			mwi_set_pid[n][2] = mwi_pid[n][2];
		}
		if (col == 0) {
			mwi_set_pid[row][col] = (int)(val * 10.0);
		} else if (col == 1) {
			mwi_set_pid[row][col] = (int)(val * 1000.0);
		} else if (col == 2) {
			mwi_set_pid[row][col] = (int)(val);
		}
		mwi_set_pid_flag = 1;
		strcpy(content, " ");
		strcpy(type, "text/html");
	} else if (strncmp(url,"/mwii_set.html?", 14) == 0) {
		int n = 0;
		int n2 = 0;
		int n3 = 0;
		int nn = 0;
		sscanf(url + 15, "%i", &nn);
		for (n2 = 0; n2 < 16; n2++) {
			for (n3 = 0; n3 < 12; n3++) {
				if (mwi_set_box[n2] & (1<<n3)) {
					if (n == nn) {
						mwi_set_box[n2] &= ~(1<<n3);
					}
				} else {
					if (n == nn) {
						mwi_set_box[n2] |= (1<<n3);
					}
				}
				n++;
			}
		}
		mwi_set_box_flag = 1;
		strcpy(content, "<meta http-equiv=\"Refresh\" content=\"0; URL=/mwii.html\">");
		strcpy(type, "text/html");
	}
}





