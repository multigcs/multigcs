
#include <all.h>


extern void get_dir (float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to, float *angle, float *dist1, float *angle_up, float *dist2);

static SDL_Thread *sdl_thread_serial_tracker = NULL;
//static uint8_t last = 0;
//static uint8_t new = 0;
static uint8_t mode = 0;
static int serial_fd_tracker = -1;
static uint8_t tracker_thread_running = 0;
static uint32_t last_connection = 1;
char trackername[TRACKER_TYPE_LAST][16] = {"Arduino", "PoloLux"};
uint8_t trackertype = TRACKER_TYPE_ARDUINO;
float tracker_lat = 0.0;
float tracker_long = 0.0;
float tracker_alt = 0.0;
float tracker_pan_dir = 0.0;
float tracker_pan_dir_trimmed = 0.0;
float tracker_pitch_dir = 0.0;
float tracker_pitch_dir_trimmed = 0.0;

Tracker TrackerData[TRACKER_MAX];

void tracker_setup_defaults (void) {
	TrackerData[TRACKER_PAN_ANGLE_MIN].min = -180.0;
	TrackerData[TRACKER_PAN_ANGLE_MIN].max = 180.0;
	TrackerData[TRACKER_PAN_ANGLE_MIN].value = -90.0;
	strcpy(TrackerData[TRACKER_PAN_ANGLE_MIN].name, "PAN_ANGLE_MIN");
	TrackerData[TRACKER_PAN_ANGLE_MAX].min = -180.0;
	TrackerData[TRACKER_PAN_ANGLE_MAX].max = 180.0;
	TrackerData[TRACKER_PAN_ANGLE_MAX].value = 90.0;
	strcpy(TrackerData[TRACKER_PAN_ANGLE_MAX].name, "PAN_ANGLE_MAX");
	TrackerData[TRACKER_PAN_PULSE_MIN].min = 900.0;
	TrackerData[TRACKER_PAN_PULSE_MIN].max = 2100.0;
	TrackerData[TRACKER_PAN_PULSE_MIN].value = 1000.0;
	strcpy(TrackerData[TRACKER_PAN_PULSE_MIN].name, "PAN_PULSE_MIN");
	TrackerData[TRACKER_PAN_PULSE_MAX].min = 900.0;
	TrackerData[TRACKER_PAN_PULSE_MAX].max = 2100.0;
	TrackerData[TRACKER_PAN_PULSE_MAX].value = 2000.0;
	strcpy(TrackerData[TRACKER_PAN_PULSE_MAX].name, "PAN_PULSE_MAX");
	TrackerData[TRACKER_PAN_TRIM].min = -180.0;
	TrackerData[TRACKER_PAN_TRIM].max = 180.0;
	TrackerData[TRACKER_PAN_TRIM].value = 0.0;
	strcpy(TrackerData[TRACKER_PAN_TRIM].name, "PAN_TRIM");
	TrackerData[TRACKER_PITCH_ANGLE_MIN].min = -180.0;
	TrackerData[TRACKER_PITCH_ANGLE_MIN].max = 180.0;
	TrackerData[TRACKER_PITCH_ANGLE_MIN].value = -90.0;
	strcpy(TrackerData[TRACKER_PITCH_ANGLE_MIN].name, "PITCH_ANGLE_MIN");
	TrackerData[TRACKER_PITCH_ANGLE_MAX].min = -180.0;
	TrackerData[TRACKER_PITCH_ANGLE_MAX].max = 180.0;
	TrackerData[TRACKER_PITCH_ANGLE_MAX].value = 90.0;
	strcpy(TrackerData[TRACKER_PITCH_ANGLE_MAX].name, "PITCH_ANGLE_MAX");
	TrackerData[TRACKER_PITCH_PULSE_MIN].min = 900.0;
	TrackerData[TRACKER_PITCH_PULSE_MIN].max = 2100.0;
	TrackerData[TRACKER_PITCH_PULSE_MIN].value = 1000.0;
	strcpy(TrackerData[TRACKER_PITCH_PULSE_MIN].name, "PITCH_PULSE_MIN");
	TrackerData[TRACKER_PITCH_PULSE_MAX].min = 900.0;
	TrackerData[TRACKER_PITCH_PULSE_MAX].max = 2100.0;
	TrackerData[TRACKER_PITCH_PULSE_MAX].value = 2000.0;
	strcpy(TrackerData[TRACKER_PITCH_PULSE_MAX].name, "PITCH_PULSE_MAX");
	TrackerData[TRACKER_PITCH_TRIM].min = -180.0;
	TrackerData[TRACKER_PITCH_TRIM].max = 180.0;
	TrackerData[TRACKER_PITCH_TRIM].value = 0.0;
	strcpy(TrackerData[TRACKER_PITCH_TRIM].name, "PITCH_TRIM");
}

void tracker_setup_save (void) {
        FILE *fr;
	int n = 0;
	char filename[1024];
	sprintf(filename, "%s/tracker.cfg", get_datadirectory());
        fr = fopen(filename, "wb");
	if (fr != 0) {
		fprintf(fr, "TYPE %i\n", trackertype);
		for (n = 0; n < TRACKER_MAX; n++) {
			fprintf(fr, "%s %f %f %f\n", TrackerData[n].name, TrackerData[n].min, TrackerData[n].max, TrackerData[n].value);
		}
	        fclose(fr);
	} else {
		SDL_Log("Can not save setup-file: %s\n", filename);
	}
}

void tracker_setup_load (void) {
        FILE *fr;
	int n = 0;
	char filename[1024];
	char name[101];
        char line[101];
	float min = 0.0;
	float max = 0.0;
	float value = 0.0;
	tracker_setup_defaults();
	sprintf(filename, "%s/tracker.cfg", get_datadirectory());
        fr = fopen(filename, "r");
	if (fr != 0) {
	        while(fgets(line, 100, fr) != NULL) {
			if (strncmp(line, "TYPE ", 5) == 0) {
				if (atoi(line + 5) < TRACKER_TYPE_LAST) {
					trackertype = atoi(line + 5);
				} else {
					SDL_Log("tracker: unknown type (%i)\n", atoi(line + 5));
				}
			} else {
			        sscanf(line, "%s %f %f %f\n", name, &min, &max, &value);
				for (n = 0; n < TRACKER_MAX; n++) {
					if (strcmp(TrackerData[n].name, name) == 0) {
						TrackerData[n].min = min;
						TrackerData[n].max = max;
						TrackerData[n].value = value;
					}
				}
			}
		}
	        fclose(fr);
	} else {
		SDL_Log("Can not load setup-file: %s\n", filename);
	}
}

uint8_t tracker_connection_status (void) {
	if (serial_fd_tracker == -1) {
		return 0;
	}
	return last_connection;
}

void tracker_set_home (void) {
	tracker_lat = ModelData.p_lat;
	tracker_long = ModelData.p_long;
	tracker_alt = ModelData.p_alt;
}

int thread_serial_tracker (void *unused) {
//	uint8_t nn = 0;
//	uint8_t read_buffer[201];
//	uint8_t read_num = 0;
	while (gui_running == 1 && tracker_thread_running == 1) {
/*		if (serial_fd_tracker != -1) {
			while ((read_num = serial_read(serial_fd_tracker, read_buffer, 200)) > 0) {
				for (nn = 0; nn < read_num; nn++) {
					new = read_buffer[nn];
					SDL_Log("##: %i (0x%x)\n", new, new);
					last = new;
				}
			}
		}
*/
		if (tracker_lat != 0.0 && tracker_long != 0.0) {
			float angle = 0.0;
			float dist1 = 0.0;
			float angle_up = 0.0;
			float dist2 = 0.0;
			get_dir(tracker_lat, tracker_long, tracker_alt, ModelData.p_lat, ModelData.p_long, ModelData.p_alt, &angle, &dist1, &angle_up, &dist2);
			float direction = angle - TrackerData[TRACKER_PAN_TRIM].value;
			if (direction >= 180.0) {
				direction -= 360.0;
			} else if (direction <= -180.0) {
				direction += 360.0;
			}
			tracker_pan_dir = angle;
			if (tracker_pan_dir >= 180.0) {
				tracker_pan_dir -= 360.0;
			} else if (tracker_pan_dir <= -180.0) {
				tracker_pan_dir += 360.0;
			}
			float direction_up = angle_up - TrackerData[TRACKER_PITCH_TRIM].value;
			if (direction_up >= 180.0) {
				direction_up -= 360.0;
			} else if (direction_up <= -180.0) {
				direction_up += 360.0;
			}
			tracker_pitch_dir = angle_up;
			if (tracker_pitch_dir >= 180.0) {
				tracker_pitch_dir -= 360.0;
			} else if (tracker_pitch_dir <= -180.0) {
				tracker_pitch_dir += 360.0;
			}
			if (direction > TrackerData[TRACKER_PAN_ANGLE_MAX].value) {
				direction = TrackerData[TRACKER_PAN_ANGLE_MAX].value;
			} else if (direction < TrackerData[TRACKER_PAN_ANGLE_MIN].value) {
				direction = TrackerData[TRACKER_PAN_ANGLE_MIN].value;
			}
			tracker_pan_dir_trimmed = direction;
			if (direction_up > TrackerData[TRACKER_PITCH_ANGLE_MAX].value) {
				direction_up = TrackerData[TRACKER_PITCH_ANGLE_MAX].value;
			} else if (direction_up < TrackerData[TRACKER_PITCH_ANGLE_MIN].value) {
				direction_up = TrackerData[TRACKER_PITCH_ANGLE_MIN].value;
			}
			tracker_pitch_dir_trimmed = direction_up;

//			float pulse_pan = (tracker_pan_dir_trimmed - TrackerData[TRACKER_PAN_ANGLE_MIN].value) * (TrackerData[TRACKER_PAN_PULSE_MAX].value - TrackerData[TRACKER_PAN_PULSE_MIN].value) / (TrackerData[TRACKER_PAN_ANGLE_MAX].value - TrackerData[TRACKER_PAN_ANGLE_MIN].value) + TrackerData[TRACKER_PAN_PULSE_MIN].value;
//			float pulse_pitch = (tracker_pitch_dir_trimmed - TrackerData[TRACKER_PITCH_ANGLE_MIN].value) * (TrackerData[TRACKER_PITCH_PULSE_MAX].value - TrackerData[TRACKER_PITCH_PULSE_MIN].value) / (TrackerData[TRACKER_PITCH_ANGLE_MAX].value - TrackerData[TRACKER_PITCH_ANGLE_MIN].value) + TrackerData[TRACKER_PITCH_PULSE_MIN].value;
//			SDL_Log("%fGrad %fGrad - %0.3fkm %0.0fm - %i %i\n", direction, direction_up, dist1, dist2, (int)pulse_pan, (int)pulse_pitch);


			if (serial_fd_tracker != -1) {
				char tmp_str[1024];
//				sprintf(tmp_str, "A%f %f\n", direction, direction_up * -1.0 + 90.0);
//				SDL_Log("#%s#", tmp_str);
//				serial_write(serial_fd_tracker, tmp_str, strlen(tmp_str));

				sprintf(tmp_str, "P%f %f %f\n", ModelData.p_lat, ModelData.p_long, ModelData.p_alt);
//				SDL_Log("#%s#", tmp_str);
				serial_write(serial_fd_tracker, tmp_str, strlen(tmp_str));

			}

		} else {
			tracker_set_home();
		}


		usleep(50000);
	}
	SDL_Log("tracker: exit thread\n");
	return 0;
}

uint8_t tracker_mode_get (void) {
	return mode;
}

uint8_t tracker_init (char *port, uint32_t baud) {
	SDL_Log("tracker: init\n");
	tracker_thread_running = 1;
	tracker_setup_load();
	SDL_Log("tracker: init serial port...\n");
	serial_fd_tracker = serial_open(port, baud);
	if (serial_fd_tracker != -1) {
#ifdef SDL2
		sdl_thread_serial_tracker = SDL_CreateThread(thread_serial_tracker, NULL, NULL);
#else
		sdl_thread_serial_tracker = SDL_CreateThread(thread_serial_tracker, NULL);
#endif
		if ( sdl_thread_serial_tracker == NULL ) {
			fprintf(stderr, "* Unable to create thread_serial_tracker: %s\n", SDL_GetError());
			return 1;
		}
	}
	return 0;
}

void tracker_exit (void) {
	if ( sdl_thread_serial_tracker != NULL ) {
		SDL_Log("tracker: wait thread\n");
		SDL_WaitThread(sdl_thread_serial_tracker, NULL);
		sdl_thread_serial_tracker = NULL;
	}
	serial_close(serial_fd_tracker);
	tracker_setup_save();
}



