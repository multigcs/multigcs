
#include <libudev.h>
#include <stdint.h>
#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <math.h>
#include <userdata.h>
#include <serial.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <model.h>
#include <main.h>
#include <screen_cli.h>
#include <SDL/SDL_thread.h>
#include <screen_keyboard.h>
#include <screen_filesystem.h>
#include <screen_device.h>
#include <screen_baud.h>


uint8_t cli_startup = 0;
char cli_serial_device[1024];
int cli_serial_baud = 115200;
int cli_fd = 0;
uint8_t cli_mode = 0;

static SDL_Thread *sdl_thread_serial_cli = NULL;
static uint8_t cli_thread_running = 0;

#define CLI_MAX_BUFFER 100
#define CLI_MAX_LINES 100
char cli_buffer[CLI_MAX_LINES][CLI_MAX_BUFFER];
uint16_t cli_history = 0;


int thread_serial_cli (void *unused) {
	uint8_t n = 0;
	uint8_t nn = 0;
	uint8_t new = 0;
	uint8_t read_buffer[201];
	uint8_t read_num = 0;

	uint8_t read_y = 0;
	uint8_t read_x = 0;
	uint8_t n2 = 0;

	while (gui_running == 1 && cli_thread_running == 1) {
		while ((read_num = read(cli_fd, read_buffer, 200)) > 0) {
			for (nn = 0; nn < read_num; nn++) {
				new = read_buffer[nn];

				if (cli_mode == 1 && new == '\r') {
					read_x = 0;
				} else if (new == '\n' || new == '\r') {
					cli_buffer[CLI_MAX_LINES - 1][read_x] = ' ';
					if (cli_mode != 1) {
						read_x = 0;
					}
					for (n2 = 0; n2 < CLI_MAX_LINES; n2++) {
						strncpy(cli_buffer[n2 - 1], cli_buffer[n2], CLI_MAX_BUFFER);
//						printf("## %i: %s\n", n2, cli_buffer[n2]);
					}
					for (n2 = 0; n2 < CLI_MAX_BUFFER; n2++) {
						cli_buffer[CLI_MAX_LINES - 1][n2] = ' ';
					}
					cli_buffer[CLI_MAX_LINES - 1][CLI_MAX_BUFFER - 1] = 0;
				} else {
					if (read_x < CLI_MAX_BUFFER - 1) {
						cli_buffer[CLI_MAX_LINES - 1][read_x++] = new;
					}
				}

			}
		}
		usleep(100000);
	}
	printf("** exit thread cli\n");
	return 0;
}


static uint8_t cli_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

static void cli_init (void) {
	printf("init cli serial port...\n");
	cli_fd = serial_open(cli_serial_device, cli_serial_baud);
	if (cli_fd != -1) {
		cli_thread_running = 1;
		sdl_thread_serial_cli = SDL_CreateThread(thread_serial_cli, NULL);
		if ( sdl_thread_serial_cli == NULL ) {
			fprintf(stderr, "Unable to create thread_serial_cli: %s\n", SDL_GetError());
			return 1;
		}
	}
}

static void cli_exit (void) {
	if ( sdl_thread_serial_cli != NULL ) {
		SDL_WaitThread(sdl_thread_serial_cli, NULL);
		sdl_thread_serial_cli = NULL;
	}
	usleep(200000);
	serial_close(cli_fd);
}

static uint8_t cli_reconnect (char *name, float x, float y, int8_t button, float data) {
	cli_exit();
	cli_init();
	return 0;
}

static uint8_t cli_baud_set (char *name, float x, float y, int8_t button, float data) {
	printf("# %i #\n", atoi(name));
	return 0;
}

static uint8_t cli_baud_change (char *name, float x, float y, int8_t button, float data) {
	baud_set_callback(cli_baud_set);
	baud_set_mode(view_mode);
	return 0;
}

static uint8_t cli_device_set (char *name, float x, float y, int8_t button, float data) {
	printf("# %s #\n", name);
	return 0;
}

static uint8_t cli_device_change (char *name, float x, float y, int8_t button, float data) {
	device_set_callback(cli_device_set);
	device_reset_filter();
	device_add_filter("ttyUSB");
	device_add_filter("ttyACM");
	device_add_filter("ttyS");
	device_set_mode(view_mode);
	return 0;
}

static uint8_t cli_set_mode (char *name, float x, float y, int8_t button, float data) {
	cli_mode = 1 - cli_mode;
	return 0;
}

uint8_t cli_move (char *name, float x, float y, int8_t button, float data) {
	if (button == 4) {
		if (cli_history < CLI_MAX_LINES - 25) {
			cli_history++;
		}
	} else if (button == 5) {
		if (cli_history > 0) {
			cli_history--;
		}
	}
}

uint8_t cli_scroll (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	if ((int)data < 0) {
		if (cli_history < CLI_MAX_LINES - 25) {
			cli_history++;
		}
	} else {
		if (cli_history > 0) {
			cli_history--;
		}
	}
	return 0;
}


void screen_cli (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	draw_title(esContext, "CLI");

	if (cli_startup == 0) {
		cli_startup = 1;
		strcpy(cli_serial_device, "/dev/ttyS10");
		cli_init();
	}

	int n = 0;
	char tmp_str[100];
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif


	draw_text_f3(esContext, -1.1, -0.9 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "DEVICE:");
	sprintf(tmp_str, "%s [SELECT]", cli_serial_device);
	draw_button(esContext, "device_select", VIEW_MODE_CLI, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.9 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, cli_device_change, 0);

	draw_text_f3(esContext, 0.1, -0.9 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "BAUD:");
	sprintf(tmp_str, "%i [CHANGE]", ModelData.telebaud);
	draw_button(esContext, "rc_baud", VIEW_MODE_CLI, tmp_str, FONT_WHITE, 0.1 + 0.3, -0.9 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, cli_baud_change, n);

//	draw_button(esContext, "cli_reconnect", VIEW_MODE_CLI, "[RECONNECT]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, cli_reconnect, n);


	if (cli_mode == 0) {
		draw_button(esContext, "cli_reconnect", VIEW_MODE_CLI, "[\\n]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, cli_set_mode, 0);
	} else {
		draw_button(esContext, "cli_reconnect", VIEW_MODE_CLI, "[\\r]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, cli_set_mode, 0);
	}


	uint16_t nn = 0;
	uint16_t nn2 = 0;

	draw_box_f3(esContext, -1.3, -0.8, 0.002, 1.27, 0.87, 0.002, 90, 90, 90, 200);
	draw_rect_f3(esContext, -1.3, -0.8, 0.002, 1.27, 0.87, 0.002, 255, 255, 255, 255);
	set_button("cli", view_mode, -1.3, -0.8, 1.27, 0.87, cli_move, (float)0, 2);
	draw_scrollbar(esContext, CLI_MAX_LINES - 25 - cli_history, CLI_MAX_LINES - 25, cli_scroll);

	for (nn = CLI_MAX_LINES - 25 - cli_history; nn < CLI_MAX_LINES - cli_history && nn2 < 25; nn++) {
		cli_buffer[nn][70] = 0;
		draw_text_f3(esContext, -1.28, -0.78 + nn2 * 0.065, 0.002, 0.06, 0.06, FONT_WHITE, cli_buffer[nn]);
		nn2++;
	}


	if (keyboard_key[0] != 0 && strcmp(keyboard_key, "escape") != 0) {
		if (strcmp(keyboard_key, "return") == 0) {
			if (cli_mode == 1) {
				write(cli_fd, "\r", 1);
			} else {
				write(cli_fd, "\r\n", 2);
			}
			cli_history = 0;
		} else if (strcmp(keyboard_key, "backspace") == 0) {
		} else if (strcmp(keyboard_key, "delete") == 0) {
		} else if (strcmp(keyboard_key, "up") == 0) {
			if (cli_history < CLI_MAX_LINES - 25) {
				cli_history++;
			}
		} else if (strcmp(keyboard_key, "down") == 0) {
			if (cli_history > 0) {
				cli_history--;
			}
		} else if (strcmp(keyboard_key, "end") == 0) {
			cli_history = 0;
		} else if (strcmp(keyboard_key, "home") == 0) {
			cli_history = CLI_MAX_LINES - 25;
		} else if (strcmp(keyboard_key, "left") == 0) {
		} else if (strcmp(keyboard_key, "right") == 0) {
		} else if (strcmp(keyboard_key, "space") == 0) {
			write(cli_fd, " ", 1);
		} else if (keyboard_key[1] == 0) {
			write(cli_fd, keyboard_key, 1);
		}
		keyboard_key[0] = 0;
	}



	screen_device(esContext);
	screen_baud(esContext);
}

