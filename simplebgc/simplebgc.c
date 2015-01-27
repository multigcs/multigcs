
#include <all.h>


int simplebgc_serial_fd = -1;
uint8_t simplebgc_serial_buf[255];
static uint32_t last_connection = 1;
static uint8_t simplebgc_cmd = 0;
static uint8_t info_num = 0;

SimpleBgcSetup simplebgc_setup;


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
	SDL_Log("init simple-bgc serial port...\n");
	info_num = 0;
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
	static uint8_t info_counter = 0;
	static uint8_t header_found = 0;
	static uint8_t data_cmd = 0;
	static uint8_t data_csum = 0;
	static uint8_t data_count = 0;
	static uint8_t data_len = 0;
	static uint8_t data_buffer[255];
	if (info_counter < 100) {
		info_counter++;
	} else {
		info_counter = 0;
		if (simplebgc_cmd == 'V' || simplebgc_cmd == 'D' || simplebgc_cmd == 'R' || simplebgc_cmd == 'A' || simplebgc_cmd == 'G' || simplebgc_cmd == 'F' || simplebgc_cmd == 'O' || simplebgc_cmd == 'r') {
			char send_buffer[20];
			send_buffer[0] = '>';
			send_buffer[1] = simplebgc_cmd;
			send_buffer[2] = 0;
			send_buffer[3] = (send_buffer[1] + send_buffer[2])%255;
			send_buffer[4] = 0;
			if (simplebgc_serial_fd >= 0) {
				serial_write(simplebgc_serial_fd, send_buffer, 5);
			}
			simplebgc_cmd = 0;
		} else if (simplebgc_cmd == 'W') {
			uint8_t send_buffer[100];
			send_buffer[0] = '>';
			send_buffer[1] = simplebgc_cmd;
			send_buffer[2] = 78;
			send_buffer[3] = (send_buffer[1] + send_buffer[2])%255;
			memcpy(&data_buffer[1], &simplebgc_setup, sizeof(SimpleBgcSetup));
			data_buffer[0] = 0;
			data_csum = 0;
			int nn = 0;
			for (nn = 0; nn < 78; nn++) {
				data_csum += data_buffer[nn];
			}
			data_buffer[78] = (data_csum % 255);
			if (simplebgc_serial_fd >= 0) {
				serial_write(simplebgc_serial_fd, send_buffer, 4);
				serial_write(simplebgc_serial_fd, data_buffer, 79);
			}
			SDL_Log("NEW_CSUM: 0x%x\n", data_buffer[78]);
			simplebgc_cmd = 0;
			info_num = 0;
		} else if (info_num == 0) {
			char send_buffer[20];
			send_buffer[0] = '>';
			send_buffer[1] = 'V';
			send_buffer[2] = 0;
			send_buffer[3] = (send_buffer[1] + send_buffer[2])%255;
			send_buffer[4] = 0;
			if (simplebgc_serial_fd >= 0) {
				serial_write(simplebgc_serial_fd, send_buffer, 5);
			}
		} else if (info_num == 1) {
			char send_buffer[20];
			send_buffer[0] = '>';
			send_buffer[1] = 'R';
			send_buffer[2] = 0;
			send_buffer[3] = (send_buffer[1] + send_buffer[2])%255;
			send_buffer[4] = 0;
			if (simplebgc_serial_fd >= 0) {
				serial_write(simplebgc_serial_fd, send_buffer, 5);
			}
		} else if (info_num == 2) {
			char send_buffer[20];
			send_buffer[0] = '>';
			send_buffer[1] = 'D';
			send_buffer[2] = 0;
			send_buffer[3] = (send_buffer[1] + send_buffer[2])%255;
			send_buffer[4] = 0;
			if (simplebgc_serial_fd >= 0) {
				serial_write(simplebgc_serial_fd, send_buffer, 5);
			}
		}
	}
	while ((res = serial_read(simplebgc_serial_fd, simplebgc_serial_buf, 200)) > 0) {
		last_connection = time(0);
		int gn = 0;
		for (gn = 0; gn < res; gn++) {
			c = simplebgc_serial_buf[gn];
			if (header_found == 1) {
				if (data_count == 0) {
					data_cmd = c;
					data_csum = 0;
				} else if (data_count == 1) {
					data_len = c;
				} else if (data_count == 2) {
				} else if (data_count < data_len + 3 && data_count < 200) {
					data_buffer[data_count - 3] = c;
					data_csum += c;
				} else {
					if (c != (data_csum % 255)) {
						SDL_Log("CSUM: FAILED (0x%x != 0x%x) len:%i\n", c, (data_csum % 255), data_len);
					} else if (data_cmd == 'V') {
						info_num = 1;
						SDL_Log("Simple-BGC:\n");
						SDL_Log("	board_version(1.0) %0.2f\n", (float)data_buffer[0] / 100.0);
						SDL_Log("	frw_version(2.0b3) %0.1fb%i\n", (float)data_buffer[1] / 10.0, data_buffer[2]);
						SDL_Log("	DEBUG %i\n", data_buffer[3]);
						SDL_Log("	AXIS %i\n", data_buffer[4]);
					} else if (data_cmd == 'D') {
						info_num = 2;
						ModelData[ModelActive].heartbeat = 100;
						ModelData[ModelActive].roll = (float)simplebgc_read16(data_buffer, 38) / 10.0;
						ModelData[ModelActive].pitch = (float)simplebgc_read16(data_buffer, 40) / 10.0;
						ModelData[ModelActive].yaw = (float)simplebgc_read16(data_buffer, 42) / 10.0;
					} else if (data_cmd == 'R') {
						info_num = 2;
						memcpy(&simplebgc_setup, &data_buffer[1], sizeof(SimpleBgcSetup));
						SDL_Log("Profile parameters:\n");
						SDL_Log("	PROFILE %i\n", data_buffer[0]);
						SDL_Log("	ROLL_P %i\n", data_buffer[1]);
						SDL_Log("	ROLL_I %i\n", data_buffer[2]);
						SDL_Log("	ROLL_D %i\n", data_buffer[3]);
						SDL_Log("	ROLL_POWER %i\n", data_buffer[4]);
						SDL_Log("	ROLL_INVERT %i\n", data_buffer[5]);
						SDL_Log("	ROLL_POLES %i\n", data_buffer[6]);
						SDL_Log("	PITCH_P %i\n", data_buffer[7]);
						SDL_Log("	PITCH_I %i\n", data_buffer[8]);
						SDL_Log("	PITCH_D %i\n", data_buffer[9]);
						SDL_Log("	PITCH_POWER %i\n", data_buffer[10]);
						SDL_Log("	PITCH_INVERT %i\n", data_buffer[11]);
						SDL_Log("	PITCH_POLES %i\n", data_buffer[12]);
						SDL_Log("	YAW_P %i\n", data_buffer[13]);
						SDL_Log("	YAW_I %i\n", data_buffer[14]);
						SDL_Log("	YAW_D %i\n", data_buffer[15]);
						SDL_Log("	YAW_POWER %i\n", data_buffer[16]);
						SDL_Log("	YAW_INVERT %i\n", data_buffer[17]);
						SDL_Log("	YAW_POLES %i\n", data_buffer[18]);
						SDL_Log("	EXT_FC_GAIN_ROLL %i\n", data_buffer[19]);
						SDL_Log("	EXT_FC_GAIN_PITCH %i\n", data_buffer[20]);
						SDL_Log("	ROLL_RC_MIN_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 21));
						SDL_Log("	ROLL_RC_MAX_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 23));
						SDL_Log("	ROLL_RC_MODE %i\n", data_buffer[25]);
						SDL_Log("	ROLL_RC_LPF %i\n", data_buffer[26]);
						SDL_Log("	ROLL_RC_SPEED %i\n", data_buffer[27]);
						SDL_Log("	ROLL_RC_FOLLOW %i\n", data_buffer[28]);
						SDL_Log("	PITCH_RC_MIN_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 29));
						SDL_Log("	PITCH_RC_MAX_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 31));
						SDL_Log("	PITCH_RC_MODE %i\n", data_buffer[33]);
						SDL_Log("	PITCH_RC_LPF %i\n", data_buffer[34]);
						SDL_Log("	PITCH_RC_SPEED %i\n", data_buffer[35]);
						SDL_Log("	PITCH_RC_FOLLOW %i\n", data_buffer[36]);
						SDL_Log("	YAW_RC_MIN_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 37));
						SDL_Log("	YAW_RC_MAX_ANGLE %i\n", (int16_t)simplebgc_read16(data_buffer, 39));
						SDL_Log("	YAW_RC_MODE %i\n", data_buffer[41]);
						SDL_Log("	YAW_RC_LPF %i\n", data_buffer[42]);
						SDL_Log("	YAW_RC_SPEED %i\n", data_buffer[43]);
						SDL_Log("	YAW_RC_FOLLOW %i\n", data_buffer[44]);
						SDL_Log("	GYRO_TRUST %i\n", data_buffer[45]);
						SDL_Log("	USE_MODEL %i\n", data_buffer[46]);
						SDL_Log("	PWM_FREQ %i\n", data_buffer[47]);
						SDL_Log("	SERIAL_SPEED %i\n", data_buffer[48]);
						SDL_Log("	RC_TRIM_ROLL %i\n", data_buffer[49]);
						SDL_Log("	RC_TRIM_PITCH %i\n", data_buffer[50]);
						SDL_Log("	RC_TRIM_YAW %i\n", data_buffer[51]);
						SDL_Log("	RC_DEADBAND %i\n", data_buffer[52]);
						SDL_Log("	RC_EXPO_RATE %i\n", data_buffer[53]);
						SDL_Log("	RC_SOURCE %i\n", data_buffer[54]);
						SDL_Log("	RC_MAP_ROLL %i\n", data_buffer[55]);
						SDL_Log("	RC_MAP_PITCH %i\n", data_buffer[56]);
						SDL_Log("	RC_MAP_YAW %i\n", data_buffer[57]);
						SDL_Log("	RC_MAP_CMD %i\n", data_buffer[58]);
						SDL_Log("	FOLLOW_MODE %i\n", data_buffer[59]);
						SDL_Log("	FOLLOW_DEADBAND %i\n", data_buffer[60]);
						SDL_Log("	FOLLOW_EXPO_RATE %i\n", data_buffer[61]);
						SDL_Log("	FOLLOW_OFFSET_ROLL %i\n", data_buffer[62]);
						SDL_Log("	FOLLOW_OFFSET_PITCH %i\n", data_buffer[63]);
						SDL_Log("	FOLLOW_OFFSET_YAW %i\n", data_buffer[64]);
						SDL_Log("\n");
						SDL_Log("General parameters:\n");
						SDL_Log("	AXIS_TOP %i\n", data_buffer[65]);
						SDL_Log("	AXIS_RIGHT %i\n", data_buffer[66]);
						SDL_Log("	GYRO_LPF %i\n", data_buffer[67]);
						SDL_Log("	I2C_INTERNAL_PULLUPS %i\n", data_buffer[68]);
						SDL_Log("	SKIP_GYRO_CALIB %i\n", data_buffer[69]);
						SDL_Log("	RC_CMD_LOW %i\n", data_buffer[70]);
						SDL_Log("	RC_CMD_MID %i\n", data_buffer[71]);
						SDL_Log("	RC_CMD_HIGH %i\n", data_buffer[72]);
						SDL_Log("	MENU_CMD_1 %i\n", data_buffer[73]);
						SDL_Log("	MENU_CMD_2 %i\n", data_buffer[74]);
						SDL_Log("	MENU_CMD_3 %i\n", data_buffer[75]);
						SDL_Log("	MENU_CMD_4 %i\n", data_buffer[76]);
						SDL_Log("	MENU_CMD_5 %i\n", data_buffer[77]);
						SDL_Log("	MENU_CMD_LONG %i\n", data_buffer[78]);
						SDL_Log("	OUTPUT_ROLL %i\n", data_buffer[79]);
						SDL_Log("	OUTPUT_PITCH %i\n", data_buffer[80]);
						SDL_Log("	OUTPUT_YAW %i\n", data_buffer[81]);
						// RESERVED_BYTES: data_buffer[82] (10u)
						SDL_Log("	CUR_PROFILE %i\n", data_buffer[92]);
						SDL_Log("CSUM: 0x%x\n", c);
					}
					header_found = 0;
					data_count = 0;
				}
				data_count++;
			} else if (c == '>') {
				header_found = 1;
				data_count = 0;
			}
		}
	}
}


