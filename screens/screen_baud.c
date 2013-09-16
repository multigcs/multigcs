
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
#include <screen_baud.h>

static uint8_t show_baud = 0;
static uint8_t baud_page = 0;
static uint8_t (*save_callback) (char *, float, float, int8_t, float);

void baud_set_callback (uint8_t (*callback) (char *, float, float, int8_t, float)) {
	save_callback = callback;
}

uint8_t baud_page_move (char *name, float x, float y, int8_t button, float data) {
	if (data < 0.0) {
		if (baud_page > 0) {
			baud_page += (int8_t)data;
		}
	} else {
		baud_page += (int8_t)data;
	}
	return 0;
}

void baud_set_mode (uint8_t mode) {
	show_baud = mode;
	baud_page = 0;
}

uint8_t baud_get_mode (void) {
	return show_baud;
}

uint8_t baud_name_cancel (char *name, float x, float y, int8_t button, float data) {
	show_baud = 0;
	return 0;
}

uint8_t baud_name_save (char *name, float x, float y, int8_t button, float data) {
	show_baud = 0;
	(*save_callback)(name, x, y, button, 1.0);
	return 0;
}

void screen_baud (ESContext *esContext) {
	if (show_baud != setup.view_mode) {
		return;
	}

	reset_buttons();
	draw_box_f3(esContext, -1.5, -1.0, 0.002, 1.5, 1.0, 0.002, 0, 0, 0, 200);

	char directory[200];
	uint8_t n = 0;
	sprintf(directory, "%s", "/dev");
	// Device-File's
	draw_button(esContext, "1200", setup.view_mode, "1200", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, baud_name_save, 0.0);
	n++;
	draw_button(esContext, "2400", setup.view_mode, "2400", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, baud_name_save, 0.0);
	n++;
	draw_button(esContext, "4800", setup.view_mode, "4800", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, baud_name_save, 0.0);
	n++;
	draw_button(esContext, "9600", setup.view_mode, "9600", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, baud_name_save, 0.0);
	n++;
	draw_button(esContext, "19200", setup.view_mode, "19200", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, baud_name_save, 0.0);
	n++;
	draw_button(esContext, "38400", setup.view_mode, "38400", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, baud_name_save, 0.0);
	n++;
	draw_button(esContext, "57600", setup.view_mode, "57600", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, baud_name_save, 0.0);
	n++;
	draw_button(esContext, "115200", setup.view_mode, "115200", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, baud_name_save, 0.0);
	n++;

	draw_button(esContext, "show", setup.view_mode, "[CANCEL]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, 1, 0, baud_name_cancel, 0.0);
}

