
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <serial.h>
#include <model.h>
#include <mwi21.h>
#include <my_mavlink.h>

void LogAppend(char *line);
void LogSave(char *file);

extern uint8_t redraw_flag;

int mwi21_serial_fd = -1;
uint8_t mwi21_serial_buf[255];
uint8_t mwi21_serial_n = 0;
uint8_t mwi21_frame_start = 0;
uint8_t mwi21_frame_len = 0;
uint8_t mwi21_cn = 5;
uint8_t mwi21_rn = 0;
int32_t mwi_status = 0;
int8_t mwi_pid[16][3];
int8_t mwi_set_pid[16][3];
int8_t mwi_set_pid_flag = 0;
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


uint8_t mwi21_connection_status (void) {
	if (mwi21_serial_fd == -1) {
		return 0;
	}
	return last_connection;
}

void mwi21_init (char *port, uint32_t baud) {
	mwi21_rn = 0;
	mwi21_serial_n = 0;
	printf("init multiwii serial port...\n");
	mwi21_serial_fd = serial_open(port, baud);
}

void mwi21_exit (void) {
	if (mwi21_serial_fd >= 0) {
		close(mwi21_serial_fd);
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
	char send_buffer[20];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 0;
	send_buffer[4] = id;
	send_buffer[5] = id;
	if (mwi21_serial_fd >= 0) {
		write(mwi21_serial_fd, send_buffer, 6);
	}
}

void mwi21_get_req8 (uint8_t id, int8_t data) {
	char send_buffer[20];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 1;
	send_buffer[4] = id;
	send_buffer[5] = data;
	send_buffer[6] = 1 ^ id ^ data;
	if (mwi21_serial_fd >= 0) {
		write(mwi21_serial_fd, send_buffer, 7);
	}
}

void mwi21_send_box (void) {
	char send_buffer[50];
	send_buffer[0] = '$';
	send_buffer[1] = 'M';
	send_buffer[2] = '<';
	send_buffer[3] = 28;
	send_buffer[4] = MSP_SET_BOX;
	send_buffer[5 + 28] = 28 ^ MSP_SET_BOX;
	uint8_t nn = 0;
	for (nn = 0; nn < 14; nn++) {
		int8_t d1 = (mwi_set_box[nn]>>8);
		int8_t d2 = mwi_set_box[nn];
		send_buffer[5 + nn * 2] = d2;
		send_buffer[5 + nn * 2 + 1] = d1;
		send_buffer[5 + 28] ^= d1;
		send_buffer[5 + 28] ^= d2;
	}
	if (mwi21_serial_fd >= 0) {
		write(mwi21_serial_fd, send_buffer, 6 + 28);
	}
}

void mwi21_send_pid (void) {
	char send_buffer[50];
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
		write(mwi21_serial_fd, send_buffer, 6 + 30);
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
}

void mwi21_update (void) {
	uint8_t c = 0;
	uint8_t res = 0;
	static uint8_t last = 0;
	static uint16_t tout = 0;
//	uint8_t n = 0;
	if (mwi21_serial_fd < 0) {
		return;
	}
	if (mwi21_serial_n == 0) {
		if (mwi21_rn == 0) {
			mwi21_get_req(MSP_ATTITUDE);
			mwi21_rn++;
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
			if (mwi_get_pid_flag != 0) {
				mwi21_get_req(MSP_PID);
				mwi_get_pid_flag = 0;
			} else if (mwi_get_box_flag != 0) {
				mwi21_get_req8(MSP_BOX, 1);
				mwi_get_box_flag = 0;
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
				mwi21_get_req(MSP_STATUS);
			}
			mwi21_rn++;
		} else if (mwi21_rn == 6) {
			mwi21_get_req(MSP_RAW_IMU);
//			mwi21_rn++;
//		} else if (mwi21_rn == 7) {
//			mwi21_get_req8(MSP_WP, 1);
			mwi21_rn = 0;
		}
	}
	if (tout++ > 300) {
		tout = 0;
		mwi21_serial_n = 0;
//		printf("mwi21: timeout\n");
	}
	while ((res = read(mwi21_serial_fd, mwi21_serial_buf, 1)) > 0) {
		last_connection = time(0);
		c = mwi21_serial_buf[0];
//		printf("%i: %i (%c)\n", mwi21_serial_n, c, c);
		if (mwi21_serial_n < 250) {
			mwi21_serial_buf[mwi21_serial_n++] = c;
		} else {
			mwi21_serial_n = 0;
		}
		if (c == 'M' && last == '$') {
			mwi21_frame_start = mwi21_serial_n - 2;
			mwi21_frame_len = 0;
//			printf("mwi21_frame_start: %i\n", mwi21_frame_start);
			tout = 0;
		}
		if (mwi21_serial_n - mwi21_frame_start == 4) {
			mwi21_frame_len = c;
//			printf("frame_parse: %i - %i\n", mwi21_serial_n - mwi21_frame_start, mwi21_frame_len);
		}
		if (mwi21_serial_buf[2] == '!' && mwi21_serial_n - mwi21_frame_start > 5) {
			printf("## MWI CMD_Error: %i\n", mwi21_serial_buf[4]);
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
//			printf("--------------- CMD: %i\n", cmd);

			uint16_t nn = 0;
			uint8_t chksum = 0;
			for (nn = 3; nn < mwi21_frame_len + 5; nn++) {
				chksum ^= mwi21_serial_buf[nn + mwi21_frame_start];
			}

			if (mwi21_serial_buf[mwi21_frame_len + 5 + mwi21_frame_start] != chksum) {
//				printf("mwi21: CSUM-Error (cmd:%i/len:%i):  %i %i %i\n", cmd, mwi21_frame_len, mwi21_serial_buf[mwi21_frame_len + 5 + mwi21_frame_start], chksum, mwi21_frame_start);
				mwi21_serial_n = 0;
				cmd = 0;
				continue;
			}
//			printf("CSUM %i(%i):  %i %i\n", cmd, mwi21_frame_len, mwi21_serial_buf[mwi21_frame_len + 5 + mwi21_frame_start], chksum);

			switch (cmd) {
				case MSP_ATTITUDE:
					mwi21_cn = 5 + mwi21_frame_start;
					ModelData.roll = (float)mwi21_read16() / 10.0;
					ModelData.pitch = (float)mwi21_read16() / -10.0;
					ModelData.yaw = (float)mwi21_read16();
					ModelData.heartbeat = 100;
					if (mwi_startup == 0) {
						mwi_get_pid_flag = 1;
						mwi_get_box_flag = 1;
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
					redraw_flag = 1;
				break;
				case MSP_BAT:
					mwi21_cn = 5 + mwi21_frame_start;
					ModelData.voltage = (float)mwi21_read8() / 10.0;
					redraw_flag = 1;
				break;
				case MSP_ALTITUDE:
					mwi21_cn = 5 + mwi21_frame_start;
					ModelData.baro = (float)mwi21_read32() / 100;
					if (GPS_found == 0) {
						ModelData.p_alt = (float)mwi21_read32() / 100;
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
					if (new_lat > 0.0 && new_lon > 0.0) {
						ModelData.p_lat = new_lat;
						ModelData.p_long = new_lon;
						ModelData.p_alt = new_alt;
						ModelData.speed = GPS_speed;
						ModelData.gpsfix = GPS_fix;
						ModelData.numSat = GPS_numSat;
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
					printf("### %i %f %f %i %i ###\n", mwi_wp_num, mwi_wp_lat, mwi_wp_lon, mwi_wp_alt, mwi_wp_flag);
				break;
			}
			mwi21_serial_n = 0;
		}
		last = c;
	}
}


