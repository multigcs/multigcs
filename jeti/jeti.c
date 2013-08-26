

#include <stdint.h>
#include <stdio.h>
#include <string.h>
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
#include <jeti.h>

int jeti_serial_fd = -1;
char jeti_serial_buf[255];
struct termios newtio;
char jeti_line[33];
char jeti_line1[17];
char jeti_line2[17];
uint8_t jeti_line_cn = 0;
uint8_t jeti_button = 0;
uint8_t jeti_ok = 0;
static uint32_t last_connection = 1;

uint8_t jeti_connection_status (void) {
	if (jeti_serial_fd == -1) {
		return 0;
	}
	return last_connection;
}

uint8_t jeti_left (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t jeti_up (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t jeti_down (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t jeti_right (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

void jeti_init (char *mdevice, uint32_t baud) {
	strcpy(jeti_line1, "--- Jeti Box ---");
	strcpy(jeti_line2, " wait for data  ");
	printf("jeti: init serial port...\n");
	jeti_serial_fd = serial_open9b(mdevice, baud);
}

void jeti_exit (void) {
	if (jeti_serial_fd >= 0) {
		close(jeti_serial_fd);
	}
}

void jeti_update (void) {
	uint8_t c = 0;
	uint8_t res = 0;
	if (jeti_serial_fd >= 0) {
		while ((res = read(jeti_serial_fd, jeti_serial_buf, 1)) > 0) {
			last_connection = time(0);
			c = jeti_serial_buf[0];
//			printf("jeti: %i: %i (%c)\n", jeti_line_cn, c, c);
			if (c == 254) {
				jeti_line_cn = 0;
			} else if (c == 255) {
				if (jeti_line_cn == 32) {
					strncpy(jeti_line1, jeti_line, 16);
					strncpy(jeti_line2, jeti_line + 16, 16);
//					printf("jeti: | %s |\n", jeti_line1);
//					printf("jeti: | %s |\n", jeti_line2);
//					printf("jeti: --------------------\n");
					if (jeti_button > 0) {
						usleep(10000);
						printf("jeti: Button: %c\n", jeti_button);
//						write(jeti_serial_fd, jeti_button, 1);
						jeti_button = 0;
					}
					jeti_ok = 1;
				}
			} else if (jeti_line_cn < 32) {
				jeti_line[jeti_line_cn++] = c;
			}
		}
	} else {
		strcpy(jeti_line2, "----------------");
		strcpy(jeti_line2, " no connection  ");
	}
}



