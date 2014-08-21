
#include <all.h>


uint8_t cli_startup = 0;
int cli_fd = -1;
uint8_t cli_mode = 0;

#define CLI_MAX_BUFFER 100
#define CLI_MAX_LINES 100
char cli_buffer[CLI_MAX_LINES][CLI_MAX_BUFFER];
uint16_t cli_history = 0;


void cli_update (void) {
	static uint8_t nn = 0;
	static uint8_t new = 0;
	static uint8_t read_buffer[201];
	static uint8_t read_num = 0;
	static uint8_t read_x = 0;
	static uint8_t n2 = 0;
	if (cli_fd < 0) {
		return;
	}
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
//					SDL_Log("## %i: %s\n", n2, cli_buffer[n2]);
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
}

uint8_t cli_init (char *port, uint32_t baud) {
	SDL_Log("init cli serial port...\n");
	cli_fd = serial_open(port, baud);
	return 0;
}

uint8_t cli_exit (void) {
	if (cli_fd < 0) {
		return 0;
	}
	serial_close(cli_fd);
	cli_fd = -1;
	return 0;
}

static uint8_t cli_set_mode (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	cli_mode = 1 - cli_mode;
	return 0;
}

uint8_t cli_move (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		if (cli_history < CLI_MAX_LINES - 25) {
			cli_history++;
		}
	} else if (button == 5) {
		if (cli_history > 0) {
			cli_history--;
		}
	}
	return 0;
}

uint8_t cli_scroll (char *name, float x, float y, int8_t button, float data, uint8_t action) {
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

#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif


	if (cli_mode == 0) {
		draw_text_button(esContext, "cli_mode", VIEW_MODE_FCMENU, "[\\n]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, cli_set_mode, 0);
	} else {
		draw_text_button(esContext, "cli_mode", VIEW_MODE_FCMENU, "[\\r]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, cli_set_mode, 0);
	}


	uint16_t nn = 0;
	uint16_t nn2 = 0;

	draw_box_f3(esContext, -1.3, -0.8, 0.002, 1.27, 0.87, 0.002, 90, 90, 90, 200);
	draw_rect_f3(esContext, -1.3, -0.8, 0.002, 1.27, 0.87, 0.002, 255, 255, 255, 255);
	set_button("cli", setup.view_mode, -1.3, -0.8, 1.27, 0.87, cli_move, (float)0, 2);
	draw_scrollbar(esContext, CLI_MAX_LINES - 25 - cli_history, CLI_MAX_LINES - 25, cli_scroll);

	for (nn = CLI_MAX_LINES - 25 - cli_history; nn < CLI_MAX_LINES - cli_history && nn2 < 25; nn++) {
		cli_buffer[nn][70] = 0;
		draw_text_f3(esContext, -1.28, -0.78 + nn2 * 0.065, 0.002, 0.06, 0.06, FONT_WHITE, cli_buffer[nn]);
		nn2++;
	}

	if (keyboard_key[0] != 0 && strcmp(keyboard_key, "escape") != 0 && strcmp(keyboard_key, "print screen") != 0) {
//		SDL_Log("%s\n", keyboard_key);
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

}

