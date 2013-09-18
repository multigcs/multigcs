
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <math.h>
#include <userdata.h>
#include <serial.h>
#include <main.h>
#include <screen_keyboard.h>

static uint8_t show_keyboard = 0;
static char new_name[200];
static uint8_t new_name_cnt = 0;
static uint8_t (*save_callback) (char *, float, float, int8_t, float);

void keyboard_set_callback (uint8_t (*callback) (char *, float, float, int8_t, float)) {
	save_callback = callback;
}

void keyboard_set_mode (uint8_t mode) {
	show_keyboard = mode;
}

uint8_t keyboard_get_mode (void) {
	return show_keyboard;
}

void keyboard_set_text (char *text) {
	strcpy(new_name, text);
	new_name_cnt = 0;
}

char *keyboard_get_text (void) {
	return new_name;
}

uint8_t keyboard_name_cancel (char *name, float x, float y, int8_t button, float data) {
	show_keyboard = 0;
	return 0;
}

uint8_t keyboard_name_save (char *name, float x, float y, int8_t button, float data) {
	show_keyboard = 0;
	(*save_callback)(new_name, x, y, button, 1.0);
	return 0;
}

uint8_t keyboard_pos_char (char *name, float x, float y, int8_t button, float data) {
	new_name_cnt = (int)data;
	return 0;
}

uint8_t keyboard_add_char (char *name, float x, float y, int8_t button, float data) {
	if (data == 0) {
		new_name[new_name_cnt] = data;
		new_name_cnt--;
	} else if (new_name[new_name_cnt] == 0) {
		new_name[new_name_cnt + 1] = 0;
		new_name[new_name_cnt] = data;
		new_name_cnt++;
	} else {
		new_name[new_name_cnt] = data;
		new_name_cnt++;
	}
	return 0;
}

void screen_keyboard (ESContext *esContext) {
#ifdef SDLGL
	if (draw_target() != 0) {
		return;
	}
#endif
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif

	if (show_keyboard != setup.view_mode) {
		return;
	}


	reset_buttons();
	draw_box_f3(esContext, -1.5, -1.0, 0.002, 1.5, 1.0, 0.002, 0, 0, 0, 200);

	draw_title(esContext, "Keyboard");

	char tmp_str[100];
	char tmp_str2[100];
	int n = 0;

#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	for (n = 0; n < strlen(new_name) + 1; n++) {
		if (new_name[n] != 0) {
			sprintf(tmp_str2, "%c", new_name[n]);
		} else {
			sprintf(tmp_str2, "[END]");
		}
		sprintf(tmp_str, "set_char_%i", n);
		draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str2, FONT_WHITE, -0.9 + n * 0.08, -0.6, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, keyboard_pos_char, n);
		if (n == new_name_cnt) {
			draw_text_button(esContext, "mark", setup.view_mode, "^", FONT_WHITE, -0.9 + n * 0.08, -0.5, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, keyboard_pos_char, n);
		}
	}
	draw_text_button(esContext, "rcname_save", setup.view_mode, "[OK]", FONT_WHITE, 0.4, -0.6, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, keyboard_name_save, 0);
	draw_text_button(esContext, "rcname_cancel", setup.view_mode, "[CANCEL]", FONT_WHITE, 0.6, -0.6, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, keyboard_name_cancel, 0);
	uint8_t x = 0;
	uint8_t y = 0;
	for (n = 33; n < 150; n++) {
		sprintf(tmp_str2, "%c", n);
		sprintf(tmp_str, "add_char_%i", n);
		draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str2, FONT_WHITE, -1.1 + x * 0.14, -0.3 + y * 0.14, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, keyboard_add_char, n);
		if (x > 14) {
			y++;
			x = 0;
		} else {
			x++;
		}
	}
	sprintf(tmp_str2, "[END]");
	sprintf(tmp_str, "add_char_%i", 0);
	draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str2, FONT_WHITE, -1.1 + x * 0.14, -0.3 + y * 0.14, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, keyboard_add_char, 0);


	if (keyboard_key[0] != 0) {
		if (strcmp(keyboard_key, "return") == 0) {
			keyboard_name_save("", 0.0, 0.0, 0, 0.0);
		} else if (strcmp(keyboard_key, "backspace") == 0) {
			new_name_cnt--;
		} else if (strcmp(keyboard_key, "delete") == 0) {
			keyboard_add_char("", 0.0, 0.0, 0, 0.0);
		} else if (strcmp(keyboard_key, "up") == 0) {
		} else if (strcmp(keyboard_key, "down") == 0) {
		} else if (strcmp(keyboard_key, "end") == 0) {
		} else if (strcmp(keyboard_key, "home") == 0) {
			new_name_cnt = 0;
		} else if (strcmp(keyboard_key, "escape") == 0) {
			keyboard_name_cancel("", 0.0, 0.0, 0, 0.0);
		} else if (strcmp(keyboard_key, "left") == 0) {
			new_name_cnt--;
		} else if (strcmp(keyboard_key, "right") == 0) {
			new_name_cnt++;
		} else if (strcmp(keyboard_key, "space") == 0) {
			keyboard_add_char("", 0.0, 0.0, 0, ' ');
		} else if (keyboard_key[1] == 0) {
			keyboard_add_char("", 0.0, 0.0, 0, keyboard_key[0]);
		}
		keyboard_key[0] = 0;
	}

}

