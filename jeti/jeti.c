
#include <all.h>

static SDL_Thread *sdl_thread_serial_jeti = NULL;
static uint8_t jeti_thread_running = 0;
int jeti_serial_fd = -1;
char jeti_serial_buf[255];
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

uint8_t jeti_left (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

uint8_t jeti_up (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

uint8_t jeti_down (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

uint8_t jeti_right (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

void jeti_update (void) {
	uint8_t c = 0;
	uint8_t res = 0;
	if (jeti_serial_fd >= 0) {
		while ((res = serial_read(jeti_serial_fd, jeti_serial_buf, 1)) > 0) {
			last_connection = time(0);
			c = jeti_serial_buf[0];
//			SDL_Log("jeti: %i: %i (%c)\n", jeti_line_cn, c, c);
			if (c == 254) {
				jeti_line_cn = 0;
			} else if (c == 255) {
				if (jeti_line_cn == 32) {
					strncpy(jeti_line1, jeti_line, 16);
					strncpy(jeti_line2, jeti_line + 16, 16);
//					SDL_Log("jeti: | %s |\n", jeti_line1);
//					SDL_Log("jeti: | %s |\n", jeti_line2);
//					SDL_Log("jeti: --------------------\n");
					if (jeti_button > 0) {
						usleep(10000);
						SDL_Log("jeti: Button: %c\n", jeti_button);
//						serial_write(jeti_serial_fd, jeti_button, 1);
						jeti_button = 0;
					}
					jeti_ok = 1;
				}
			} else if (jeti_line_cn < 32) {
				jeti_line[jeti_line_cn++] = c;
			}
		}
	} else {
		strncpy(jeti_line2, "----------------", 16);
		strncpy(jeti_line2, " no connection  ", 16);
	}
}

int thread_serial_jeti (void *unused) {
	while (gui_running == 1 && jeti_thread_running == 1) {
		jeti_update();
		usleep(1000000);
	}
	SDL_Log("jeti: exit thread\n");
	return 0;
}

uint8_t jeti_init (char *mdevice, uint32_t baud) {
	strncpy(jeti_line1, "--- Jeti Box ---", 16);
	strncpy(jeti_line2, " wait for data  ", 16);
	SDL_Log("jeti: init\n");
	jeti_thread_running = 1;
	SDL_Log("jeti: init serial port...\n");
	jeti_serial_fd = serial_open9b(mdevice, baud);
	if (jeti_serial_fd != -1) {
#ifdef SDL2
		sdl_thread_serial_jeti = SDL_CreateThread(thread_serial_jeti, NULL, NULL);
#else
		sdl_thread_serial_jeti = SDL_CreateThread(thread_serial_jeti, NULL);
#endif
		if ( sdl_thread_serial_jeti == NULL ) {
			fprintf(stderr, "* Unable to create thread_serial_jeti: %s\n", SDL_GetError());
			return 1;
		}
	}
	return 0;
}

void jeti_exit (void) {
	if ( sdl_thread_serial_jeti != NULL ) {
		SDL_Log("jeti: wait thread\n");
		SDL_WaitThread(sdl_thread_serial_jeti, NULL);
		sdl_thread_serial_jeti = NULL;
	}
	if (jeti_serial_fd >= 0) {
		close(jeti_serial_fd);
		jeti_serial_fd = -1;
	}
}


