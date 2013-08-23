
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
#include <brugi.h>
#include <my_mavlink.h>

int brugi_serial_fd = -1;
uint8_t brugi_serial_buf[255];
static uint32_t last_connection = 1;
static uint8_t info_num = 0;
BrugiSetup brugi_setup;


void brugi_send_cmd (char *cmd) {
	if (brugi_serial_fd >= 0) {
		write(brugi_serial_fd, cmd, strlen(cmd));
	}
}

void brugi_set_value (char *var, int16_t val) {
	char cmd[100];
	sprintf(cmd, "par %s %i\n", var, val);
	brugi_send_cmd(cmd);
}

uint8_t brugi_connection_status (void) {
	if (brugi_serial_fd == -1) {
		return 0;
	}
	return last_connection;
}

void brugi_init (char *port, uint32_t baud) {
	uint8_t n = 0;
	printf("init simple-bgc serial port...\n");
	brugi_serial_fd = serial_open(port, baud);
}

void brugi_exit (void) {
	if (brugi_serial_fd >= 0) {
		brugi_send_cmd("OAC 0\n");
		tcflush(brugi_serial_fd, TCIFLUSH);
		close(brugi_serial_fd);
		brugi_serial_fd = -1;
		info_num = 0;
	}
}

void brugi_update (void) {
	uint8_t c = 0;
	uint8_t res = 0;
	if (brugi_serial_fd < 0) {
		return;
	}
	static uint8_t info_counter = 0;
	static uint8_t header_found = 0;
	static uint8_t data_cmd = 0;
	static uint8_t data_count = 0;
	static uint8_t data_len = 0;
	static uint8_t data_buffer[255];
	if (info_counter < 250) {
		info_counter++;
	} else {
		info_counter = 0;
		if (info_num == 0) {
			brugi_send_cmd("par\n");
		} else if (info_num == 1) {
			brugi_send_cmd("OAC 1\n");
		}
	}
	while ((res = read(brugi_serial_fd, brugi_serial_buf, 1)) > 0) {
		last_connection = time(0);
		c = brugi_serial_buf[0];

		if (c == '\n') {
			data_count = 0;
			if (strstr(data_buffer, "done.") > 0) {
				info_num = 1;
			} else if (strstr(data_buffer, "vers ") > 0) {
				brugi_setup.vers = atoi(data_buffer + 4 + 1);
			} else if (strstr(data_buffer, "gyroPitchKp ") > 0) {
				brugi_setup.gyroPitchKp = atoi(data_buffer + 11 + 1);
			} else if (strstr(data_buffer, "gyroPitchKi ") > 0) {
				brugi_setup.gyroPitchKi = atoi(data_buffer + 11 + 1);
			} else if (strstr(data_buffer, "gyroPitchKd ") > 0) {
				brugi_setup.gyroPitchKd = atoi(data_buffer + 11 + 1);
			} else if (strstr(data_buffer, "gyroRollKp ") > 0) {
				brugi_setup.gyroRollKp = atoi(data_buffer + 10 + 1);
			} else if (strstr(data_buffer, "gyroRollKi ") > 0) {
				brugi_setup.gyroRollKi = atoi(data_buffer + 10 + 1);
			} else if (strstr(data_buffer, "gyroRollKd ") > 0) {
				brugi_setup.gyroRollKd = atoi(data_buffer + 10 + 1);
			} else if (strstr(data_buffer, "accTimeConstant ") > 0) {
				brugi_setup.accTimeConstant = atoi(data_buffer + 15 + 1);
			} else if (strstr(data_buffer, "mpuLPF ") > 0) {
				brugi_setup.mpuLPF = atoi(data_buffer + 6 + 1);
			} else if (strstr(data_buffer, "angleOffsetPitch ") > 0) {
				brugi_setup.angleOffsetPitch = atoi(data_buffer + 16 + 1);
			} else if (strstr(data_buffer, "angleOffsetRoll ") > 0) {
				brugi_setup.angleOffsetRoll = atoi(data_buffer + 15 + 1);
			} else if (strstr(data_buffer, "dirMotorPitch ") > 0) {
				brugi_setup.dirMotorPitch = atoi(data_buffer + 13 + 1);
			} else if (strstr(data_buffer, "dirMotorRoll ") > 0) {
				brugi_setup.dirMotorRoll = atoi(data_buffer + 12 + 1);
			} else if (strstr(data_buffer, "motorNumberPitch ") > 0) {
				brugi_setup.motorNumberPitch = atoi(data_buffer + 16 + 1);
			} else if (strstr(data_buffer, "motorNumberRoll ") > 0) {
				brugi_setup.motorNumberRoll = atoi(data_buffer + 15 + 1);
			} else if (strstr(data_buffer, "maxPWMmotorPitch ") > 0) {
				brugi_setup.maxPWMmotorPitch = atoi(data_buffer + 16 + 1);
			} else if (strstr(data_buffer, "maxPWMmotorRoll ") > 0) {
				brugi_setup.maxPWMmotorRoll = atoi(data_buffer + 15 + 1);
			} else if (strstr(data_buffer, "minRCPitch ") > 0) {
				brugi_setup.minRCPitch = atoi(data_buffer + 10 + 1);
			} else if (strstr(data_buffer, "maxRCPitch ") > 0) {
				brugi_setup.maxRCPitch = atoi(data_buffer + 10 + 1);
			} else if (strstr(data_buffer, "minRCRoll ") > 0) {
				brugi_setup.minRCRoll = atoi(data_buffer + 9 + 1);
			} else if (strstr(data_buffer, "maxRCRoll ") > 0) {
				brugi_setup.maxRCRoll = atoi(data_buffer + 9 + 1);
			} else if (strstr(data_buffer, "rcGain ") > 0) {
				brugi_setup.rcGain = atoi(data_buffer + 6 + 1);
			} else if (strstr(data_buffer, "rcLPF ") > 0) {
				brugi_setup.rcLPF = atoi(data_buffer + 5 + 1);
			} else if (strstr(data_buffer, "rcModePPM ") > 0) {
				brugi_setup.rcModePPM = atoi(data_buffer + 9 + 1);
			} else if (strstr(data_buffer, "rcChannelPitch ") > 0) {
				brugi_setup.rcChannelPitch = atoi(data_buffer + 14 + 1);
			} else if (strstr(data_buffer, "rcChannelRoll ") > 0) {
				brugi_setup.rcChannelRoll = atoi(data_buffer + 13 + 1);
			} else if (strstr(data_buffer, "rcMid ") > 0) {
				brugi_setup.rcMid = atoi(data_buffer + 5 + 1);
			} else if (strstr(data_buffer, "rcAbsolute ") > 0) {
				brugi_setup.rcAbsolute = atoi(data_buffer + 10 + 1);
			} else if (strstr(data_buffer, "accOutput ") > 0) {
				brugi_setup.accOutput = atoi(data_buffer + 9 + 1);
			} else if (strstr(data_buffer, "enableGyro ") > 0) {
				brugi_setup.enableGyro = atoi(data_buffer + 10 + 1);
			} else if (strstr(data_buffer, "enableACC ") > 0) {
				brugi_setup.enableACC = atoi(data_buffer + 9 + 1);
			} else if (strstr(data_buffer, "axisReverseZ ") > 0) {
				brugi_setup.axisReverseZ = atoi(data_buffer + 12 + 1);
			} else if (strstr(data_buffer, "axisSwapXY ") > 0) {
				brugi_setup.axisSwapXY = atoi(data_buffer + 10 + 1);
			} else if (strstr(data_buffer, " ACC ") > 0) {
				int acc_x = 0;
				int acc_y = 0;
				sscanf(data_buffer, "%i ACC %i", &acc_y, &acc_x);
				ModelData.roll = (float)acc_x / 1000.0;
				ModelData.pitch = (float)acc_y / 1000.0;
//				printf("#### %f,%f -- %s\n", (float)acc_x / 1000.0, (float)acc_y / 1000.0,  data_buffer);
				info_num = 2;
			}

		} else if (c == '\r') {
		} else if (data_count < 200) {
			data_buffer[data_count++] = c;
			data_buffer[data_count] = 0;
		}
	}
}


