
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
#include <simplebgc.h>
#include <my_mavlink.h>

int simplebgc_serial_fd = -1;
uint8_t simplebgc_serial_buf[255];
static uint32_t last_connection = 1;
static uint8_t simplebgc_cmd = 0;

void simplebgc_send_cmd (uint8_t cmd) {
	simplebgc_cmd = cmd;
}

uint8_t simplebgc_connection_status (void) {
	if (simplebgc_serial_fd == -1) {
		return 0;
	}
	return last_connection;
}

void simplebgc_init (char *port, uint32_t baud) {
	uint8_t n = 0;
	printf("init simple-bgc serial port...\n");
	simplebgc_serial_fd = serial_open(port, baud);
}

void simplebgc_exit (void) {
	if (simplebgc_serial_fd >= 0) {
		close(simplebgc_serial_fd);
		simplebgc_serial_fd = -1;
	}
}

int16_t simplebgc_read16 (uint8_t *buffer, uint8_t pos) {
	int16_t t = buffer[pos] & 0xff;
	t += buffer[pos + 1] << 8;
	return t;
}

void simplebgc_update (void) {
	uint8_t c = 0;
	uint8_t res = 0;
	if (simplebgc_serial_fd < 0) {
		return;
	}
	static uint8_t info_num = 0;
	static uint8_t info_counter = 0;
	static uint8_t header_found = 0;
	static uint8_t data_cmd = 0;
	static uint8_t data_count = 0;
	static uint8_t data_len = 0;
	static uint8_t data_buffer[255];
	if (info_counter < 100) {
		info_counter++;
	} else {
		info_counter = 0;
		if (simplebgc_cmd == 'A' || simplebgc_cmd == 'G' || simplebgc_cmd == 'F' || simplebgc_cmd == 'O' || simplebgc_cmd == 'r') {
			char send_buffer[20];
			send_buffer[0] = '>';
			send_buffer[1] = simplebgc_cmd;
			send_buffer[2] = 0;
			send_buffer[3] = (send_buffer[1] + send_buffer[2])%255;
			send_buffer[4] = 0;
			if (simplebgc_serial_fd >= 0) {
				write(simplebgc_serial_fd, send_buffer, 5);
			}
			simplebgc_cmd = 0;
		} else if (info_num == 0) {
			char send_buffer[20];
			send_buffer[0] = '>';
			send_buffer[1] = 'V';
			send_buffer[2] = 0;
			send_buffer[3] = (send_buffer[1] + send_buffer[2])%255;
			send_buffer[4] = 0;
			if (simplebgc_serial_fd >= 0) {
				write(simplebgc_serial_fd, send_buffer, 5);
			}
		} else if (info_num == 1) {
			char send_buffer[20];
			send_buffer[0] = '>';
			send_buffer[1] = 'R';
			send_buffer[2] = 0;
			send_buffer[3] = (send_buffer[1] + send_buffer[2])%255;
			send_buffer[4] = 0;
			if (simplebgc_serial_fd >= 0) {
				write(simplebgc_serial_fd, send_buffer, 5);
			}
		} else if (info_num == 2) {
			char send_buffer[20];
			send_buffer[0] = '>';
			send_buffer[1] = 'D';
			send_buffer[2] = 0;
			send_buffer[3] = (send_buffer[1] + send_buffer[2])%255;
			send_buffer[4] = 0;
			if (simplebgc_serial_fd >= 0) {
				write(simplebgc_serial_fd, send_buffer, 5);
			}
		}
	}
	while ((res = read(simplebgc_serial_fd, simplebgc_serial_buf, 1)) > 0) {
		last_connection = time(0);
		c = simplebgc_serial_buf[0];
//		printf("	%i	<<<<<: %i (%c)\n", data_count - 3, c, c);
		if (header_found == 1) {
			if (data_count == 0) {
				data_cmd = c;
//				printf("data_cmd %i\n", data_cmd);
			} else if (data_count == 1) {
				data_len = c;
//				printf("data_len %i\n", data_len);
			} else if (data_count == 2) {
//				printf("csum %i (0x%x)\n", c, c);
			} else if (data_count < data_len + 2) {
				data_buffer[data_count - 3] = c;
			} else {
				data_buffer[data_count - 3] = c;
//				printf("%i: end_data %c (0x%x)\n", data_count - 3, c, c);
				if (data_cmd == 'V') {
					info_num = 1;
					printf("Simple-BGC:\n");
					printf("	board_version(1.0) %0.2f\n", (float)data_buffer[0] / 100.0);
					printf("	frw_version(2.0b3) %0.1fb%i\n", (float)data_buffer[1] / 10.0, data_buffer[2]);
					printf("	DEBUG %i\n", data_buffer[3]);
					printf("	AXIS %i\n", data_buffer[4]);
				} else if (data_cmd == 'D') {
					info_num = 2;
					ModelData.heartbeat = 100;
					ModelData.roll = (float)simplebgc_read16(data_buffer, 38) / 10.0;
					ModelData.pitch = (float)simplebgc_read16(data_buffer, 40) / 10.0;
					ModelData.yaw = (float)simplebgc_read16(data_buffer, 42) / 10.0;
/*

					printf("roll_acc %i\n", simplebgc_read16(data_buffer, 0));
					printf("roll_gyro %i\n", simplebgc_read16(data_buffer, 2));
					printf("roll_mag %i\n", simplebgc_read16(data_buffer, 4));

					printf("pitch_acc %i\n", simplebgc_read16(data_buffer, 6));
					printf("pitch_gyro %i\n", simplebgc_read16(data_buffer, 8));
					printf("pitch_mag %i\n", simplebgc_read16(data_buffer, 10));

					printf("yaw_acc %i\n", simplebgc_read16(data_buffer, 12));
					printf("yaw_gyro %i\n", simplebgc_read16(data_buffer, 14));
					printf("yaw_mag %i\n", simplebgc_read16(data_buffer, 16));

					printf("debug1 %i\n", simplebgc_read16(data_buffer, 18));
					printf("debug2 %i\n", simplebgc_read16(data_buffer, 20));
					printf("debug3 %i\n", simplebgc_read16(data_buffer, 22));
					printf("debug4 %i\n", simplebgc_read16(data_buffer, 24));

					printf("RC_ROLL %i\n", simplebgc_read16(data_buffer, 26));
					printf("RC_PITCH %i\n", simplebgc_read16(data_buffer, 28));
					printf("RC_YAW %i\n", simplebgc_read16(data_buffer, 30));
					printf("RC_CMD %i\n", simplebgc_read16(data_buffer, 32));

					printf("EXT_FC_ROLL %i\n", simplebgc_read16(data_buffer, 34));
					printf("EXT_FC_PITCH %i\n", simplebgc_read16(data_buffer, 36));

					printf("ANGLE_ROLL %i\n", simplebgc_read16(data_buffer, 38));
					printf("ANGLE_PITCH %i\n", simplebgc_read16(data_buffer, 40));
					printf("ANGLE_YAW %i\n", simplebgc_read16(data_buffer, 42));
*/
				} else if (data_cmd == 'R') {
					info_num = 2;

					printf("Profile parameters:\n");
					printf("	PROFILE %i\n", data_buffer[0]);
					printf("	ROLL_P %i\n", data_buffer[1]);
					printf("	ROLL_I %i\n", data_buffer[2]);
					printf("	ROLL_D %i\n", data_buffer[3]);
					printf("	ROLL_POWER %i\n", data_buffer[4]);
					printf("	ROLL_INVERT %i\n", data_buffer[5]);
					printf("	ROLL_POLES %i\n", data_buffer[6]);
					printf("	PITCH_P %i\n", data_buffer[7]);
					printf("	PITCH_I %i\n", data_buffer[8]);
					printf("	PITCH_D %i\n", data_buffer[9]);
					printf("	PITCH_POWER %i\n", data_buffer[10]);
					printf("	PITCH_INVERT %i\n", data_buffer[11]);
					printf("	PITCH_POLES %i\n", data_buffer[12]);
					printf("	YAW_P %i\n", data_buffer[13]);
					printf("	YAW_I %i\n", data_buffer[14]);
					printf("	YAW_D %i\n", data_buffer[15]);
					printf("	YAW_POWER %i\n", data_buffer[16]);
					printf("	YAW_INVERT %i\n", data_buffer[17]);
					printf("	YAW_POLES %i\n", data_buffer[18]);
					printf("	EXT_FC_GAIN_ROLL %i\n", data_buffer[19]);
					printf("	EXT_FC_GAIN_PITCH %i\n", data_buffer[20]);
					printf("	ROLL_RC_MIN_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 21));
					printf("	ROLL_RC_MAX_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 23));
					printf("	ROLL_RC_MODE %i\n", data_buffer[25]);
					printf("	ROLL_RC_LPF %i\n", data_buffer[26]);
					printf("	ROLL_RC_SPEED %i\n", data_buffer[27]);
					printf("	ROLL_RC_FOLLOW %i\n", data_buffer[28]);
					printf("	PITCH_RC_MIN_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 29));
					printf("	PITCH_RC_MAX_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 31));
					printf("	PITCH_RC_MODE %i\n", data_buffer[33]);
					printf("	PITCH_RC_LPF %i\n", data_buffer[34]);
					printf("	PITCH_RC_SPEED %i\n", data_buffer[35]);
					printf("	PITCH_RC_FOLLOW %i\n", data_buffer[36]);
					printf("	YAW_RC_MIN_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 37));
					printf("	YAW_RC_MAX_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 39));
					printf("	YAW_RC_MODE %i\n", data_buffer[41]);
					printf("	YAW_RC_LPF %i\n", data_buffer[42]);
					printf("	YAW_RC_SPEED %i\n", data_buffer[43]);
					printf("	YAW_RC_FOLLOW %i\n", data_buffer[44]);
					printf("	GYRO_TRUST %i\n", data_buffer[45]);
					printf("	USE_MODEL %i\n", data_buffer[46]);
					printf("	PWM_FREQ %i\n", data_buffer[47]);
					printf("	SERIAL_SPEED %i\n", data_buffer[48]);
					printf("	RC_TRIM_ROLL %i\n", data_buffer[49]);
					printf("	RC_TRIM_PITCH %i\n", data_buffer[50]);
					printf("	RC_TRIM_YAW %i\n", data_buffer[51]);
					printf("	RC_DEADBAND %i\n", data_buffer[52]);
					printf("	RC_EXPO_RATE %i\n", data_buffer[53]);
					printf("	RC_SOURCE %i\n", data_buffer[54]);
					printf("	RC_MAP_ROLL %i\n", data_buffer[55]);
					printf("	RC_MAP_PITCH %i\n", data_buffer[56]);
					printf("	RC_MAP_YAW %i\n", data_buffer[57]);
					printf("	RC_MAP_CMD %i\n", data_buffer[58]);
					printf("	FOLLOW_MODE %i\n", data_buffer[59]);
					printf("	FOLLOW_DEADBAND %i\n", data_buffer[60]);
					printf("	FOLLOW_EXPO_RATE %i\n", data_buffer[61]);
					printf("	FOLLOW_OFFSET_ROLL %i\n", data_buffer[62]);
					printf("	FOLLOW_OFFSET_PUTCH %i\n", data_buffer[63]);
					printf("	FOLLOW_OFFSET_YAW %i\n", data_buffer[64]);
					printf("\n");
					printf("General parameters:\n");
					printf("	AXIS_TOP %i\n", data_buffer[65]);
					printf("	AXIS_RIGHT %i\n", data_buffer[66]);
					printf("	GYRO_LPF %i\n", data_buffer[67]);
					printf("	I2C_INTERNAL_PULLUPS %i\n", data_buffer[68]);
					printf("	SKIP_GYRO_CALIB %i\n", data_buffer[69]);
					printf("	RC_CMD_LOW %i\n", data_buffer[70]);
					printf("	RC_CMD_MID %i\n", data_buffer[71]);
					printf("	RC_CMD_HIGH %i\n", data_buffer[72]);
					printf("	MENU_CMD_1 %i\n", data_buffer[73]);
					printf("	MENU_CMD_2 %i\n", data_buffer[74]);
					printf("	MENU_CMD_3 %i\n", data_buffer[75]);
					printf("	MENU_CMD_4 %i\n", data_buffer[76]);
					printf("	MENU_CMD_5 %i\n", data_buffer[77]);
					printf("	MENU_CMD_LONG %i\n", data_buffer[78]);
					printf("	OUTPUT_ROLL %i\n", data_buffer[79]);
					printf("	OUTPUT_PITCH­ %i\n", data_buffer[80]);
					printf("	OUTPUT_YAW %i\n", data_buffer[81]);
					// RESERVED_BYTES: data_buffer[82] (10u)
					printf("	CUR_PROFILE %i\n", data_buffer[92]);
				}
				header_found = 0;
				data_count = 0;
			}
			data_count++;
		} else if (c == '>') {
			header_found = 1;
			data_count = 0;
//			printf("header_found\n");
		}
	}
}


