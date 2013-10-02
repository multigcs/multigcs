
#include <all.h>

SDL_Thread *gcs_sdl_thread_serial_gps = NULL;
int gcs_serial_fd_gps = -1;
int serial_fd_gps = -1;
static uint32_t last_connection = 1;
static uint32_t gcs_last_connection = 1;

uint8_t gcsgps_connection_status (void) {
	if (gcs_serial_fd_gps == -1) {
		return 0;
	}
	return gcs_last_connection;
}

uint8_t gps_connection_status (void) {
	if (serial_fd_gps == -1) {
		return 0;
	}
	return last_connection;
}

void gps_update (void) {
	static uint8_t n = 0;
	static int res;
	static char serial_buf[2];
	static char line[1024];
	if (serial_fd_gps >= 0 && (res = read(serial_fd_gps, serial_buf, 1)) > 0) {
		last_connection = time(0);
		if (serial_buf[0] == '\r') {
		} else if (serial_buf[0] != '\n') {
			line[n++] = serial_buf[0];
			line[n] = 0;
		} else {
//				printf("gps: %s\n", line);
			if (strncmp(line, "$GPVTG", 6) == 0) {
				float track;
				char ch_T;
				char null1;
				char null2;
				float speed_knots;
				char knots;
				float speed;
				char ch_K;
				sscanf( line, "$GPVTG,%f,%c,%c,%c,%f,%c,%f,%c,", &track, &ch_T, &null1, &null2, &speed_knots, &knots, &speed, &ch_K);
//					printf("gps: %s\n", line);
				ModelData.speed = speed;
				redraw_flag = 1;
			} else if (strncmp(line, "$GPRMC", 6) == 0) {
				float time;
				char ch_A;
				float lat1;
				char ch_N;
				float lon1;
				char ch_W;
				float speed_knots;
				float curse;
				float date;
				float mag_var;
				char ch_E;
				sscanf( line, "$GPRMC,%f,%c,%f,%c,%f,%c,%f,%f,%f,%f,%c", &time, &ch_A, &lat1, &ch_N, &lon1, &ch_W, &speed_knots, &curse, &date, &mag_var, &ch_E);
//					printf("gps: %s %f\n", line, curse);
				ModelData.yaw = curse;
				redraw_flag = 1;
			} else if (strncmp(line, "$GPGGA", 6) == 0) {
				float time;
				float lat1;
				char latdir;
				float lon1;
				char londir;
				int quality;
				int num_sat;
				float hdilution;
				float alt2;
				char alt2_unit;
				float alt1;
				char alt1_unit;
				sscanf( line, "$GPGGA,%f,%f,%c,%f,%c,%d,%d,%f,%f,%c,%f,%c", &time, &lat1, &latdir, &lon1, &londir, &quality, &num_sat, &hdilution, &alt2, &alt2_unit, &alt1, &alt1_unit);
//					printf("gps: %s\n", line);
//					printf("gps: ###################### %f, %f, %c, %f, %c, %d, %d, %f, %f, %c, %f, %c ##\n", time, lat1, latdir, lon1, londir, quality, num_sat, hdilution, alt2, alt2_unit, alt1, alt1_unit);
				char tmp_str[20];
				sprintf(tmp_str, "%2.0f", lat1);
				float hlat = atof(tmp_str + 2) / 60.0;
				tmp_str[2] = 0;
				hlat += atof(tmp_str);
				sprintf(tmp_str, "%5.0f", lon1);
				float hlon = atof(tmp_str + 3) / 60.0;
				tmp_str[3] = 0;
				hlon += atof(tmp_str);
				ModelData.heartbeat = 100;
				if (hlat != 0.0 && hlon != 0.0) {
					ModelData.p_lat = hlat;
					ModelData.p_long = hlon;
					ModelData.p_alt = alt2;
					ModelData.numSat = num_sat;
					ModelData.gpsfix = quality;
					redraw_flag = 1;
				}
/*
				printf("#%f - %f (%0.1fm)#\n", hlat, hlon, alt1);
				printf("Lat:  %f\n", WayPoints[0].p_lat);
				printf("Lon:  %f\n", hlon);
				printf("Alt:  %0.1fm (%0.1fm)\n", alt1, alt2);
				printf("Sats: %i\n", num_sat);
				if (quality == 0) {
					printf("GPS:  Invalid\n");
				} else if (quality == 1) {
					printf("GPS:  2D Fix\n");
				} else if (quality == 2) {
					printf("GPS:  3D Fix\n");
				}
*/
			} else if (strncmp(line, "$IMU", 4) == 0) {
				float imuX;
				float imuY;
				float imuZ;
				sscanf( line, "$IMU,%f,%f,%f", &imuX, &imuY, &imuZ);
				ModelData.pitch = imuX;
				ModelData.roll = imuY;
				ModelData.yaw = imuZ;
				redraw_flag = 1;
			} else if (strncmp(line, "$ACC", 4) == 0) {
				float accX;
				float accY;
				sscanf( line, "$ACC,%f,%f", &accX, &accY);
				ModelData.acc_x = accX / 90.0;
				ModelData.acc_y = accY / 90.0;
				redraw_flag = 1;
			} else if (strncmp(line, "$GYRO", 5) == 0) {
				float gyroX;
				float gyroY;
				float gyroZ;
				sscanf( line, "$GYRO,%f,%f,%f", &gyroX, &gyroY, &gyroZ);
				ModelData.gyro_x = gyroX;
				ModelData.gyro_y = gyroY;
				ModelData.gyro_z = gyroZ;
				redraw_flag = 1;
			}
			n = 0;
		}
	}
}


int gcs_thread_serial_gps (void *unused) {
	uint8_t n = 0;
	int res;
	char serial_buf[2];
	char line[1024];
	while (gui_running == 1) {
		while ((res = read(gcs_serial_fd_gps, serial_buf, 1)) > 0 && gui_running == 1) {
			gcs_last_connection = time(0);
			if (serial_buf[0] == '\r') {
			} else if (serial_buf[0] != '\n') {
				line[n++] = serial_buf[0];
				line[n] = 0;
			} else {
				if (strncmp(line, "$GPGGA", 6) == 0) {
					float time;
					float lat1;
					char latdir;
					float lon1;
					char londir;
					int quality;
					int num_sat;
					float hdilution;
					float alt2;
					char alt2_unit;
					float alt1;
					char alt1_unit;
					sscanf( line, "$GPGGA,%f,%f,%c,%f,%c,%d,%d,%f,%f,%c,%f,%c", &time, &lat1, &latdir, &lon1, &londir, &quality, &num_sat, &hdilution, &alt2, &alt2_unit, &alt1, &alt1_unit);
//					printf("%s\n", line);
//					printf("###################### %f, %f, %c, %f, %c, %d, %d, %f, %f, %c, %f, %c ##\n", time, lat1, latdir, lon1, londir, quality, num_sat, hdilution, alt2, alt2_unit, alt1, alt1_unit);
					char tmp_str[20];
					sprintf(tmp_str, "%2.0f", lat1);
					float hlat = atof(tmp_str + 2) / 60.0;
					tmp_str[2] = 0;
					hlat += atof(tmp_str);
					sprintf(tmp_str, "%5.0f", lon1);
					float hlon = atof(tmp_str + 3) / 60.0;
					tmp_str[3] = 0;
					hlon += atof(tmp_str);

					if (hlat != 0.0 && hlon != 0.0) {
						WayPoints[0].p_lat = hlat;
						WayPoints[0].p_long = hlon;
						WayPoints[0].p_alt = alt2;
						redraw_flag = 1;
					}
/*
					printf("#%f - %f (%0.1fm)#\n", hlat, hlon, alt1);
					printf("Lat:  %f\n", WayPoints[0].p_lat);
					printf("Lon:  %f\n", hlon);
					printf("Alt:  %0.1fm (%0.1fm)\n", alt1, alt2);
					printf("Sats: %i\n", num_sat);
					if (quality == 0) {
						printf("GPS:  Invalid\n");
					} else if (quality == 1) {
						printf("GPS:  2D Fix\n");
					} else if (quality == 2) {
						printf("GPS:  3D Fix\n");
					}
*/
				}
				n = 0;
			}
		}
		usleep(100000);
	}
	printf("gcs-gps: exit gps\n");
	return 0;
}


uint8_t gcs_gps_init (char *port, uint32_t baud) {
	printf("gcs-gps: init serial port...\n");
	gcs_serial_fd_gps = serial_open(port, baud);
	if (gcs_serial_fd_gps != -1) {
#ifdef SDL2
		gcs_sdl_thread_serial_gps = SDL_CreateThread(gcs_thread_serial_gps, NULL, NULL);
#else
		gcs_sdl_thread_serial_gps = SDL_CreateThread(gcs_thread_serial_gps, NULL);
#endif
		if ( gcs_sdl_thread_serial_gps == NULL ) {
			fprintf(stderr, "gcs-gps: Unable to create gcs_thread_serial_gps: %s\n", SDL_GetError());
			return 1;
		}
	}
	return 0;
}

uint8_t gps_init (char *port, uint32_t baud) {
	printf("gps: init serial port...\n");
	serial_fd_gps = serial_open(port, baud);
	return 0;
}

void gcs_gps_exit (void) {
	if ( gcs_sdl_thread_serial_gps != NULL ) {
		printf("gcs-gps: wait thread\n");
		SDL_WaitThread(gcs_sdl_thread_serial_gps, NULL);
		gcs_sdl_thread_serial_gps = NULL;
	}
	serial_close(gcs_serial_fd_gps);
	gcs_serial_fd_gps = -1;
}

void gps_exit (void) {
	if (serial_fd_gps >= 0) {
		serial_close(serial_fd_gps);
		serial_fd_gps = -1;
	}
}



