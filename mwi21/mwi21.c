
#include <all.h>

extern uint8_t redraw_flag;

uint8_t last[MODELS_MAX];
uint16_t tout[MODELS_MAX];
uint8_t flag[MODELS_MAX];
uint8_t mwi21_serial_buf[MODELS_MAX][255];
uint8_t serial_buffer[MODELS_MAX][1024];
uint8_t mwi21_serial_n[MODELS_MAX];
uint8_t mwi21_frame_start[MODELS_MAX];
uint8_t mwi21_frame_len[MODELS_MAX];
uint8_t mwi21_cn[MODELS_MAX];
uint8_t mwi21_rn[MODELS_MAX];
int32_t mwi_status[MODELS_MAX];
uint8_t mwi_pid[MODELS_MAX][16][3];
uint8_t mwi_set_pid[MODELS_MAX][16][3];
uint8_t mwi_set_pid_flag[MODELS_MAX];
volatile int16_t mwi_box[MODELS_MAX][16];
volatile int16_t mwi_set_box[MODELS_MAX][16];
int8_t mwi_set_box_flag[MODELS_MAX];
int8_t mwi_get_pid_flag[MODELS_MAX];
int8_t mwi_get_box_flag[MODELS_MAX];
int8_t mwi_req[MODELS_MAX];
int16_t mwi_i2cErrors[MODELS_MAX];
int16_t mwi_sensors[MODELS_MAX];
int16_t mwi_mag_x;
int16_t mwi_mag_y;
int16_t mwi_mag_z;
int16_t cycleTime[MODELS_MAX];
static uint32_t last_connection[MODELS_MAX];
static int8_t GPS_found[MODELS_MAX];
static int8_t mwi_startup[MODELS_MAX];
char mwi_box_names[MODELS_MAX][16][12];
char mwi_pid_names[MODELS_MAX][16][12];
int8_t mwi_get_boxnames_flag[MODELS_MAX];
int8_t mwi_get_pidnames_flag[MODELS_MAX];

uint8_t mwi21_connection_status (uint8_t modelid) {
	if (ModelData[modelid].serial_fd == -1) {
		return 0;
	}
	return last_connection[modelid];
}

void mwi21_init (uint8_t modelid, char *port, uint32_t baud) {
	uint8_t n = 0;
#ifndef WINDOWS
	if (port[0] != '/') {
		return;
	}
#endif
	last[modelid] = 0;
	tout[modelid] = 0;
	flag[modelid] = 0;
	mwi21_rn[modelid] = 1;
	mwi21_serial_n[modelid] = 0;
	for (n = 0; n < 16; n++) {
		mwi_box_names[modelid][n][0] = 0;
		mwi_pid_names[modelid][n][0] = 0;
	}
	SDL_Log("init multiwii serial(%i) port...\n", modelid);
	ModelData[modelid].serial_fd = serial_open(port, baud);
}

void mwi21_exit (uint8_t modelid) {
	if (ModelData[modelid].serial_fd >= 0) {
		serial_close(ModelData[modelid].serial_fd);
		ModelData[modelid].serial_fd = -1;
	}
}

int8_t mwi21_read8 (uint8_t modelid) {
	int8_t t = mwi21_serial_buf[modelid][mwi21_cn[modelid]++] & 0xff;
	return t;
}

int16_t mwi21_read16 (uint8_t modelid) {
	int16_t t = mwi21_serial_buf[modelid][mwi21_cn[modelid]++] & 0xff;
	t += mwi21_serial_buf[modelid][mwi21_cn[modelid]++] << 8;
	return t;
}

int32_t mwi21_read32 (uint8_t modelid) {
	int32_t t = mwi21_serial_buf[modelid][mwi21_cn[modelid]++] & 0xff;
	t += (mwi21_serial_buf[modelid][mwi21_cn[modelid]++] & 0xff) << 8;
	t += (mwi21_serial_buf[modelid][mwi21_cn[modelid]++] & 0xff) << 16;
	t += (mwi21_serial_buf[modelid][mwi21_cn[modelid]++] & 0xff) << 24;
	return t;
}

void mwi21_get_req (uint8_t modelid, uint8_t id) {
	uint8_t send_buffer[20];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 0;
	send_buffer[4] = id;
	send_buffer[5] = id;
	if (ModelData[modelid].serial_fd >= 0) {
		serial_write(ModelData[modelid].serial_fd, send_buffer, 6);
	}
}

void mwi21_get_req8 (uint8_t modelid, uint8_t id, int8_t data) {
	uint8_t send_buffer[20];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 1;
	send_buffer[4] = id;
	send_buffer[5] = data;
	send_buffer[6] = 1 ^ id ^ data;
	if (ModelData[modelid].serial_fd >= 0) {
		serial_write(ModelData[modelid].serial_fd, send_buffer, 7);
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

void mwi21_send_wp (uint8_t modelid, uint8_t wpnum, float p_lat, float p_long, float p_alt) {
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
	if (ModelData[modelid].serial_fd >= 0) {
		serial_write(ModelData[modelid].serial_fd, send_buffer, 6 + 32);
	}
}

void mwi21_send_box (uint8_t modelid) {
	uint8_t send_buffer[50];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 32;
	send_buffer[4] = MSP_SET_BOX;
	send_buffer[5 + 32] = 32 ^ MSP_SET_BOX;
	uint8_t nn = 0;
	for (nn = 0; nn < 16; nn++) {
		int8_t d1 = (mwi_set_box[modelid][nn]>>8);
		int8_t d2 = mwi_set_box[modelid][nn];
		send_buffer[5 + nn * 2] = d2;
		send_buffer[5 + nn * 2 + 1] = d1;
		send_buffer[5 + 32] ^= d1;
		send_buffer[5 + 32] ^= d2;
	}
	if (ModelData[modelid].serial_fd >= 0) {
		serial_write(ModelData[modelid].serial_fd, send_buffer, 6 + 32);
	}
}

void mwi21_send_pid (uint8_t modelid) {
	uint8_t send_buffer[50];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 30;
	send_buffer[4] = MSP_SET_PID;
	send_buffer[5 + 30] = 30 ^ MSP_SET_PID;
	uint8_t nn = 0;
	for (nn = 0; nn < 10; nn++) {
		send_buffer[5 + nn * 3] = mwi_set_pid[modelid][nn][0];
		send_buffer[5 + nn * 3 + 1] = mwi_set_pid[modelid][nn][1];
		send_buffer[5 + nn * 3 + 2] = mwi_set_pid[modelid][nn][2];
		send_buffer[5 + 30] ^= mwi_set_pid[modelid][nn][0];
		send_buffer[5 + 30] ^= mwi_set_pid[modelid][nn][1];
		send_buffer[5 + 30] ^= mwi_set_pid[modelid][nn][2];
	}
	if (ModelData[modelid].serial_fd >= 0) {
		serial_write(ModelData[modelid].serial_fd, send_buffer, 6 + 30);
	}
}

void mwi21_cal_acc (uint8_t modelid) {
	mwi_req[modelid] = MSP_ACC_CALIBRATION;
}

void mwi21_cal_mac (uint8_t modelid) {
	mwi_req[modelid] = MSP_MAG_CALIBRATION;
}

void mwi21_write_rom (uint8_t modelid) {
	mwi_req[modelid] = MSP_EEPROM_WRITE;
}

void mwi21_get_values (uint8_t modelid) {
	mwi_get_pid_flag[modelid] = 1;
	mwi_get_box_flag[modelid] = 1;
	mwi_get_boxnames_flag[modelid] = 1;
	mwi_get_pidnames_flag[modelid] = 1;
}

void mwi21_get_new (uint8_t modelid) {
	flag[modelid] = 1 - flag[modelid];
	if (flag[modelid] == 0) {
		if (mwi_get_pid_flag[modelid] != 0) {
			mwi21_get_req(modelid, MSP_PID);
			mwi_get_pid_flag[modelid] = 0;
		} else if (mwi_get_box_flag[modelid] != 0) {
			mwi21_get_req8(modelid, MSP_BOX, 1);
			mwi_get_box_flag[modelid] = 0;
		} else if (mwi_get_boxnames_flag[modelid] != 0) {
			mwi21_get_req(modelid, MSP_BOXNAMES);
			mwi_get_boxnames_flag[modelid] = 0;
		} else if (mwi_get_pidnames_flag[modelid] != 0) {
			mwi21_get_req(modelid, MSP_PIDNAMES);
			mwi_get_pidnames_flag[modelid] = 0;
		} else if (mwi_set_pid_flag[modelid] == 1) {
			mwi21_send_pid(modelid);
			mwi_set_pid_flag[modelid] = 0;
			mwi_get_pid_flag[modelid] = 1;
		} else if (mwi_set_box_flag[modelid] == 1) {
			mwi21_send_box(modelid);
			mwi_set_box_flag[modelid] = 0;
			mwi_get_box_flag[modelid] = 1;
		} else if (mwi_req[modelid] != 0) {
			mwi21_get_req(modelid, mwi_req[modelid]);
			mwi_req[modelid] = 0;
		} else {
			mwi21_get_req(modelid, MSP_ATTITUDE);
		}
	} else if (mwi21_rn[modelid] == 1) {
		mwi21_get_req(modelid, MSP_RC);
		mwi21_rn[modelid]++;
	} else if (mwi21_rn[modelid] == 2) {
		mwi21_get_req(modelid, MSP_ALTITUDE);
		mwi21_rn[modelid]++;
	} else if (mwi21_rn[modelid] == 3) {
		mwi21_get_req(modelid, MSP_BAT);
		mwi21_rn[modelid]++;
	} else if (mwi21_rn[modelid] == 4) {
		mwi21_get_req(modelid, MSP_RAW_GPS);
		mwi21_rn[modelid]++;
	} else if (mwi21_rn[modelid] == 5) {
		mwi21_get_req(modelid, MSP_STATUS);
		mwi21_rn[modelid]++;
	} else if (mwi21_rn[modelid] == 6) {
		mwi21_get_req(modelid, MSP_RAW_IMU);
		mwi21_rn[modelid]++;
	} else if (mwi21_rn[modelid] == 7) {
		mwi21_get_req8(modelid, MSP_WP, 0); // Home
		mwi21_rn[modelid]++;
	} else if (mwi21_rn[modelid] == 8) {
		mwi21_get_req8(modelid, MSP_WP, 16); // Hold
		mwi21_rn[modelid]++;
	} else if (mwi21_rn[modelid] == 9) {
		mwi21_send_wp(modelid, 0, WayPoints[modelid][0].p_lat, WayPoints[modelid][0].p_long, WayPoints[modelid][0].p_alt);
		mwi21_rn[modelid]++;
	} else if (mwi21_rn[modelid] == 10) {
		mwi21_send_wp(modelid, 16, WayPoints[modelid][1].p_lat, WayPoints[modelid][1].p_long, WayPoints[modelid][1].p_alt);
		mwi21_rn[modelid]++;
	} else {
		mwi21_rn[modelid] = 1;
	}
}

void mwi21_update (uint8_t modelid) {
	uint8_t nn2 = 0;
	uint8_t cp = 0;
	uint8_t bn = 0;
	uint8_t c = 0;
	uint8_t res = 0;
//	uint8_t n = 0;
	ModelData[modelid].serial_fd = serial_check(ModelData[modelid].serial_fd);
	if (ModelData[modelid].serial_fd < 0) {
		return;
	}
	if (tout[modelid]++ > 20) {
		tout[modelid] = 0;
		mwi21_serial_n[modelid] = 0;
		mwi21_get_new(modelid);
//		SDL_Log("mwi21: timeout\n");
	}
	while ((res = serial_read(ModelData[modelid].serial_fd, serial_buffer[modelid], 1023)) > 0) {
	    int i = 0;
	    for (i = 0; i < res; i++) {
		mwi21_serial_buf[modelid][0] = serial_buffer[modelid][i];
		last_connection[modelid] = time(0);
		c = mwi21_serial_buf[modelid][0];
//		SDL_Log("model%i: %i: %i (%c)\n", modelid, mwi21_serial_n[modelid], c, c);
		if (mwi21_serial_n[modelid] < 250) {
			mwi21_serial_buf[modelid][mwi21_serial_n[modelid]++] = c;
		} else {
			mwi21_serial_n[modelid] = 0;
		}
		if (c == 'M' && last[modelid] == '$') {
			mwi21_frame_start[modelid] = mwi21_serial_n[modelid] - 2;
			mwi21_frame_len[modelid] = 0;
//			SDL_Log("mwi21_frame_start(%i): %i\n", modelid, mwi21_frame_start[modelid]);
			tout[modelid] = 0;
		}
		if (mwi21_serial_n[modelid] - mwi21_frame_start[modelid] == 4) {
			mwi21_frame_len[modelid] = c;
//			SDL_Log("frame_parse: %i - %i\n", mwi21_serial_n[modelid] - mwi21_frame_start[modelid], mwi21_frame_len[modelid]);
		}
		if (mwi21_serial_buf[modelid][2] == '!' && mwi21_serial_n[modelid] - mwi21_frame_start[modelid] > 5) {
			if (mwi21_serial_buf[modelid][4] != 106) {
//				SDL_Log("## MWI CMD_Error: %i\n", mwi21_serial_buf[modelid][4]);
			}
			mwi21_serial_buf[modelid][0] = 0;
			mwi21_serial_buf[modelid][1] = 0;
			mwi21_serial_buf[modelid][2] = 0;
			mwi21_serial_buf[modelid][3] = 0;
			mwi21_serial_buf[modelid][4] = 0;
			mwi21_serial_n[modelid] = 0;
			mwi21_frame_start[modelid] = 0;
			mwi21_frame_len[modelid] = 0;
		}
		if (mwi21_frame_len[modelid] > 0 && mwi21_frame_len[modelid] + 6 == mwi21_serial_n[modelid] - mwi21_frame_start[modelid]) {
			uint8_t cmd = mwi21_serial_buf[modelid][4 + mwi21_frame_start[modelid]];
//			SDL_Log("--------------- CMD: %i\n", cmd);

			uint16_t nn = 0;
			uint8_t chksum = 0;
			for (nn = 3; nn < mwi21_frame_len[modelid] + 5; nn++) {
				chksum ^= mwi21_serial_buf[modelid][nn + mwi21_frame_start[modelid]];
			}

			if (mwi21_serial_buf[modelid][mwi21_frame_len[modelid] + 5 + mwi21_frame_start[modelid]] != chksum) {
				SDL_Log("mwi21: CSUM-Error (cmd:%i/len:%i):  %i %i %i\n", cmd, mwi21_frame_len[modelid], mwi21_serial_buf[modelid][mwi21_frame_len[modelid] + 5 + mwi21_frame_start[modelid]], chksum, mwi21_frame_start[modelid]);
				mwi21_serial_n[modelid] = 0;
				cmd = 0;
				continue;
			} else {
//				SDL_Log("mwi21: CSUM-OK (cmd:%i/len:%i):  %i %i %i\n", cmd, mwi21_frame_len[modelid], mwi21_serial_buf[modelid][mwi21_frame_len[modelid] + 5 + mwi21_frame_start[modelid]], chksum, mwi21_frame_start[modelid]);
				mwi21_serial_n[modelid] = 0;
			}
//			SDL_Log("CSUM %i(%i):  %i %i\n", cmd, mwi21_frame_len[modelid], mwi21_serial_buf[modelid][mwi21_frame_len[modelid] + 5 + mwi21_frame_start[modelid]], chksum);
			mwi21_get_new(modelid);

			switch (cmd) {
				case MSP_BOXNAMES:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					for (nn2 = 0; nn2 < mwi21_frame_len[modelid]; nn2++) {
						char c = mwi21_read8(modelid);

						if (c == ';') {
							bn++;
							cp = 0;
						} else if (bn < 16 && cp < 11) {
							mwi_box_names[modelid][bn][cp + 1] = 0;
							mwi_box_names[modelid][bn][cp++] = c;
						}
					}
					redraw_flag = 1;
					mwi_get_boxnames_flag[modelid] = 0;
					mwi_get_pidnames_flag[modelid] = 1;
				break;
				case MSP_PIDNAMES:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					for (nn2 = 0; nn2 < mwi21_frame_len[modelid]; nn2++) {
						char c = mwi21_read8(modelid);
						if (c == ';') {
							bn++;
							cp = 0;
						} else if (bn < 16 && cp < 11) {
							mwi_pid_names[modelid][bn][cp + 1] = 0;
							mwi_pid_names[modelid][bn][cp++] = c;
						}
					}
					redraw_flag = 1;
					mwi_get_pidnames_flag[modelid] = 0;
				break;
				case MSP_ATTITUDE:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					ModelData[modelid].roll = (float)mwi21_read16(modelid) / 10.0;
					ModelData[modelid].pitch = (float)mwi21_read16(modelid) / -10.0;
					ModelData[modelid].yaw = (float)mwi21_read16(modelid);
					ModelData[modelid].heartbeat = 100;
					ModelData[modelid].dronetype = MAV_TYPE_GENERIC;
					strcpy(ModelData[modelid].sysstr, "Multiwii");
					if (mwi_startup[modelid] == 0) {
						mwi21_get_values(modelid);
					}
					redraw_flag = 1;
				break;
				case MSP_RC:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					ModelData[modelid].radio[0] = (mwi21_read16(modelid) - 1500) / 5;
					ModelData[modelid].radio[1] = (mwi21_read16(modelid) - 1500) / 5;
					ModelData[modelid].radio[2] = (mwi21_read16(modelid) - 1500) / 5;
					ModelData[modelid].radio[3] = (mwi21_read16(modelid) - 1500) / 5;
					ModelData[modelid].radio[4] = (mwi21_read16(modelid) - 1500) / 5;
					ModelData[modelid].radio[5] = (mwi21_read16(modelid) - 1500) / 5;
					ModelData[modelid].radio[6] = (mwi21_read16(modelid) - 1500) / 5;
					ModelData[modelid].radio[7] = (mwi21_read16(modelid) - 1500) / 5;
					ModelData[modelid].chancount = 8;
					redraw_flag = 1;
				break;
				case MSP_BAT:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					ModelData[modelid].voltage = (float)mwi21_read8(modelid) / 10.0;
					redraw_flag = 1;
				break;
				case MSP_ALTITUDE:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					ModelData[modelid].baro = (float)mwi21_read32(modelid) / 100.0;
					ModelData[modelid].heartbeat = 100;
					if (GPS_found[modelid] == 0) {
						ModelData[modelid].p_alt = (float)mwi21_read32(modelid) / 100.0;
						if (ModelData[modelid].p_alt > 8000.0) {
							ModelData[modelid].p_alt = ModelData[modelid].baro;
						}
					}
					redraw_flag = 1;
				break;
				case MSP_PID:
					mwi_startup[modelid] = 1;
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					uint8_t len1 = mwi21_serial_buf[modelid][3 + mwi21_frame_start[modelid]];
					uint8_t nn1 = 0;
					for (nn1 = 0; nn1 < len1 / 3; nn1++) {
						mwi_pid[modelid][nn1][0] = mwi21_read8(modelid);
						mwi_pid[modelid][nn1][1] = mwi21_read8(modelid);
						mwi_pid[modelid][nn1][2] = mwi21_read8(modelid);
					}
					mwi_get_pid_flag[modelid] = 0;
					mwi_get_box_flag[modelid] = 1;
				break;
				case MSP_STATUS:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					cycleTime[modelid] = mwi21_read16(modelid);
					mwi_i2cErrors[modelid] = mwi21_read16(modelid);
					mwi_sensors[modelid] = mwi21_read16(modelid);
					mwi_status[modelid] = mwi21_read32(modelid);
					if (mwi_status[modelid] & (1<<BOXARM)) {
						ModelData[modelid].armed = MODEL_ARMED;
					} else {
						ModelData[modelid].armed = MODEL_DISARMED;
					}
					if (mwi_status[modelid] & (1<<BOXGPSHOLD)) {
						ModelData[modelid].mode = MODEL_MODE_POSHOLD;
					} else if (mwi_status[modelid] & (1<<BOXGPSHOME)) {
						ModelData[modelid].mode = MODEL_MODE_RTL;
					} else {
						ModelData[modelid].mode = MODEL_MODE_MANUAL;
					}
					redraw_flag = 1;
				break;
				case MSP_BOX:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					uint8_t len = mwi21_serial_buf[modelid][3 + mwi21_frame_start[modelid]];
					uint8_t nn = 0;
					for (nn = 0; nn < len; nn++) {
//						mwi_box[modelid][nn] = mwi21_read16(modelid);
						mwi_set_box[modelid][nn] = mwi21_read16(modelid);
					}
					mwi_get_box_flag[modelid] = 0;
					mwi_get_boxnames_flag[modelid] = 1;
				break;
				case MSP_RAW_IMU:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					ModelData[modelid].acc_x = mwi21_read16(modelid);
					ModelData[modelid].acc_y = mwi21_read16(modelid);
					ModelData[modelid].acc_z = mwi21_read16(modelid);
					ModelData[modelid].gyro_x = mwi21_read16(modelid);
					ModelData[modelid].gyro_y = mwi21_read16(modelid);
					ModelData[modelid].gyro_z = mwi21_read16(modelid);
					mwi_mag_x = mwi21_read16(modelid);
					mwi_mag_y = mwi21_read16(modelid);
					mwi_mag_z = mwi21_read16(modelid);
					redraw_flag = 1;
				break;
				case MSP_RAW_GPS:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					int8_t GPS_fix = 0;
					int8_t GPS_numSat = 0;
					float GPS_speed = 0;
					float new_lat = 0.0;
					float new_lon = 0.0;
					float new_alt = 0.0;
					GPS_fix = mwi21_read8(modelid);
					GPS_numSat = mwi21_read8(modelid);
					new_lat = (float)mwi21_read32(modelid) / 10000000.0;
					new_lon = (float)mwi21_read32(modelid) / 10000000.0;
					new_alt = (float)mwi21_read16(modelid);
					GPS_speed = (float)mwi21_read16(modelid);
					ModelData[modelid].speed = GPS_speed;
					ModelData[modelid].gpsfix = GPS_fix;
					ModelData[modelid].numSat = GPS_numSat;
					if (new_lat > 0.0 && new_lon > 0.0) {
						ModelData[modelid].p_lat = new_lat;
						ModelData[modelid].p_long = new_lon;
						ModelData[modelid].p_alt = new_alt;
						GPS_found[modelid] = 1;
						redraw_flag = 1;
					}
				break;
				case MSP_WP:
					mwi21_cn[modelid] = 5 + mwi21_frame_start[modelid];
					int8_t mwi_wp_num = mwi21_read8(modelid);
					float mwi_wp_lat = (float)mwi21_read32(modelid) / 10000000.0;
					float mwi_wp_lon = (float)mwi21_read32(modelid) / 10000000.0;
					int16_t mwi_wp_alt = mwi21_read16(modelid);
					//int8_t mwi_wp_flag = mwi21_read8(modelid);
					mwi21_read8(modelid);
					if (mwi_wp_num == 0) {
//						SDL_Log("# home # %i %f %f %i %i ###\n", mwi_wp_num, mwi_wp_lat, mwi_wp_lon, mwi_wp_alt, mwi_wp_flag);
						if (mwi_wp_lat != 0.0 || mwi_wp_lon != 0.0) {
							WayPoints[modelid][0].p_lat = mwi_wp_lat;
							WayPoints[modelid][0].p_long = mwi_wp_lon;
							WayPoints[modelid][0].p_alt = mwi_wp_alt;
							WayPoints[modelid][0].frametype = MAV_FRAME_GLOBAL;
						}
					} else {
//						SDL_Log("# hold # %i %f %f %i %i ###\n", mwi_wp_num, mwi_wp_lat, mwi_wp_lon, mwi_wp_alt, mwi_wp_flag);
						if (mwi_wp_lat != 0.0 || mwi_wp_lon != 0.0) {
							strcpy(WayPoints[modelid][1].name, "HOLD");
							strcpy(WayPoints[modelid][1].command, "WAYPOINT");
							WayPoints[modelid][1].p_lat = mwi_wp_lat;
							WayPoints[modelid][1].p_long = mwi_wp_lon;
							WayPoints[modelid][1].p_alt = mwi_wp_alt;
							WayPoints[modelid][1].frametype = MAV_FRAME_GLOBAL;
							WayPoints[modelid][2].name[0] = 0;
							WayPoints[modelid][2].p_lat = 0.0;
							WayPoints[modelid][2].p_long = 0.0;
							WayPoints[modelid][2].p_alt = 0.0;
							WayPoints[modelid][2].frametype = MAV_FRAME_GLOBAL;
						}
					}
				break;
			}
			mwi21_serial_n[modelid] = 0;
		}
		last[modelid] = c;
	    }
	}
}


static void model_parseMWI21Pid (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur, uint16_t pid) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"p"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_pid[modelid][pid][0] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"i"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_pid[modelid][pid][1] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"d"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_pid[modelid][pid][2] = atoi((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void model_parseMWI21Box (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur, uint16_t box) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"value"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_box[modelid][box] = atoi((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

void mwi21_xml_load (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur) { 
	uint16_t pid = 0;
	uint16_t box = 0;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"pid"))) {
			model_parseMWI21Pid (modelid, doc, cur, pid++);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"box"))) {
			model_parseMWI21Box (modelid, doc, cur, box++);
		}
		cur = cur->next;
	}
	return;
}

void mwi21_xml_save (uint8_t modelid, FILE *fr) {
	int16_t n = 0;
	fprintf(fr, " <mwi21>\n");
	for (n = 0; n < 16; n++) {
		fprintf(fr, "  <pid><id>%i</id><p>%i</p><i>%i</i><d>%i</d></pid>\n", n, mwi_pid[modelid][n][0], mwi_pid[modelid][n][1], mwi_pid[modelid][n][2]);
	}
	for (n = 0; n < 16; n++) {
		fprintf(fr, "  <box><id>%i</id><value>%i</value></box>\n", n, mwi_box[modelid][n]);
	}
	fprintf(fr, " </mwi21>\n");
}

static void mwi21_html_page (uint8_t modelid, char *content, uint8_t mode) {
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
			if (mwi_box_names[modelid][n][0] != 0) {
				lc = 1 - lc;
				if (lc == 0) {
					strcat(content, "<TR class=\"first\">");
				} else {
					strcat(content, "<TR class=\"sec\">");
				}
				sprintf(tmp_str, "<TD>%s</TD>", mwi_box_names[modelid][n]);
				strcat(content, tmp_str);
				for (n2 = 0; n2 < 12; n2++) {
					if (mwi_set_box[modelid][n] & (1<<n2)) {
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
			if (mwi_pid_names[modelid][n][0] != 0) {
				lc = 1 - lc;
				if (lc == 0) {
					strcat(content, "<TR class=\"first\">");
				} else {
					strcat(content, "<TR class=\"sec\">");
				}
				sprintf(tmp_str, "<TD>%s</TD>", mwi_pid_names[modelid][n]);
				strcat(content, tmp_str);
				sprintf(tmp_str, "<TD align=\"center\"><INPUT class=\"form-input\" onchange=\"check_value(%i,%i);\" id=\"%i-%i\" value=\"%0.1f\" type=\"text\"></TD>", n, 0, n, 0, (float)mwi_pid[modelid][n][0] / 10.0);
				strcat(content, tmp_str);
				sprintf(tmp_str, "<TD align=\"center\"><INPUT class=\"form-input\" onchange=\"check_value(%i,%i);\" id=\"%i-%i\" value=\"%0.3f\" type=\"text\"></TD>", n, 1, n, 1, (float)mwi_pid[modelid][n][1] / 1000.0);
				strcat(content, tmp_str);
				sprintf(tmp_str, "<TD align=\"center\"><INPUT class=\"form-input\" onchange=\"check_value(%i,%i);\" id=\"%i-%i\" value=\"%i\" type=\"text\"></TD>", n, 2, n, 2, mwi_pid[modelid][n][2]);
				strcat(content, tmp_str);
				strcat(content, "</TR>\n");
			}
		}
		strcat(content, "</TABLE>\n");
	}
	strcat(content, "</TD></TR></TABLE>\n");
	webserv_html_stop(content);
}

void mwi21_web_get (uint8_t modelid, char *url, char *content, char *type) {
	if (strncmp(url, "/mwii.html", 10) == 0) {
		mwi21_html_page(modelid, content, 0);
		strcpy(type, "text/html");
	} else if (strncmp(url, "/mwii_box.html", 14) == 0) {
		mwi21_html_page(modelid, content, 1);
		strcpy(type, "text/html");
	} else if (strncmp(url, "/mwii_pid.html?", 14) == 0) {
		int n = 0;
		int row = 0;
		int col = 0;
		float val = 0.0;
		sscanf(url + 15, "%i,%i=%f", &row, &col, &val);
		for (n = 0; n < 16; n++) {
			mwi_set_pid[modelid][n][0] = mwi_pid[modelid][n][0];
			mwi_set_pid[modelid][n][1] = mwi_pid[modelid][n][1];
			mwi_set_pid[modelid][n][2] = mwi_pid[modelid][n][2];
		}
		if (col == 0) {
			mwi_set_pid[modelid][row][col] = (int)(val * 10.0);
		} else if (col == 1) {
			mwi_set_pid[modelid][row][col] = (int)(val * 1000.0);
		} else if (col == 2) {
			mwi_set_pid[modelid][row][col] = (int)(val);
		}
		mwi_set_pid_flag[modelid] = 1;
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
				if (mwi_set_box[modelid][n2] & (1<<n3)) {
					if (n == nn) {
						mwi_set_box[modelid][n2] &= ~(1<<n3);
					}
				} else {
					if (n == nn) {
						mwi_set_box[modelid][n2] |= (1<<n3);
					}
				}
				n++;
			}
		}
		mwi_set_box_flag[modelid] = 1;
		strcpy(content, "<meta http-equiv=\"Refresh\" content=\"0; URL=/mwii.html\">");
		strcpy(type, "text/html");
	}
}


