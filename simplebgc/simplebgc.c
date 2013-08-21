
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
		if (info_num == 0) {
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
					info_num = 1;
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
	if (info_num == 2) {
		exit(0);
	}
}


