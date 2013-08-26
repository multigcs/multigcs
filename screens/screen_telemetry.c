
#include <stdint.h>
#include <termios.h>
#include <userdata.h>
#include <model.h>
#include <main.h>
#include <screen_hud.h>
#include <screen_map.h>
#include <my_mavlink.h>
#include <jeti.h>
#include <mwi21.h>


uint8_t telemetry_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

void draw_value_display (ESContext *esContext, float x1, float y1, float fsize, uint16_t len, uint8_t align, char *title, char *format, float value) {
	float x2 = x1 + fsize * (len + 1) * 0.6;
	float y2 = y1 + fsize + 0.04 + (fsize / 3);
	char text[100];
	sprintf(text, format, value);
	draw_box_f(esContext, x1, y1, x2, y2, 10, 10, 10, 200);
	draw_rect_f(esContext, x1, y1, x2, y2, 100, 100, 100, 255);
	draw_rect_f(esContext, x1 + 0.01, y1 + 0.01, x2 - 0.01, y2 - 0.01, 200, 200, 200, 255);
	draw_text_f(esContext, x1 + 0.01, y1 + 0.02, fsize / 3, fsize / 3, FONT_PINK, title);
	if (align == 0) {
		draw_text_f(esContext, x1 + 0.02, y1 + 0.02 + (fsize / 3), fsize, fsize, FONT_GREEN, text);
	} else {
		draw_text_f(esContext, x1 + 0.02 + (fsize * (len - strlen(text)) * 0.6), y1 + 0.02 + (fsize / 3), fsize, fsize, FONT_GREEN, text);
	}
}

void draw_value_bar (ESContext *esContext, float x1, float y1, float x2, float y2, uint8_t type, float min, float max, float warning, float critical, float value) {
	char tmp_str[1024];
//	draw_box_f(esContext, x1, y1, x2, y2, 100, 100, 100, 125);

	float x_diff = x2 - x1;
	float y_diff = y2 - y1;
	float v_diff = max - min;

	float y_warning = y2 - (y_diff / v_diff * (warning - min));
	float y_critical = y2 - (y_diff / v_diff * (critical - min));
	float y_max = y2 - (y_diff / v_diff * (max - min));
	float y_value = y2 - (y_diff / v_diff * (value - min));

	draw_box_f(esContext, x1 + x_diff / 6.0 * 3.0, y_max, x1 + x_diff / 6.0 * 4.0, y_warning, 0, 255, 0, 255);
	draw_box_f(esContext, x1 + x_diff / 6.0 * 3.0, y_warning, x1 + x_diff / 6.0 * 4.0, y_critical, 255, 255, 0, 255);
	draw_box_f(esContext, x1 + x_diff / 6.0 * 3.0, y_critical, x1 + x_diff / 6.0 * 4.0, y2, 255, 0, 0, 255);

	draw_line_f(esContext, x1 + x_diff / 6.0 * 3.0, y_warning, x1 + x_diff / 6.0 * 4.0 + x_diff / 10.0, y_warning, 255, 255, 0, 255);
	sprintf(tmp_str, "%0.1f", warning);
	draw_text_f(esContext, x1 + x_diff / 6.0 * 4.0 + x_diff / 10.0, y_warning - 0.02, 0.04, 0.04, FONT_PINK, tmp_str);

	draw_line_f(esContext, x1 + x_diff / 6.0 * 3.0, y_critical, x1 + x_diff / 6.0 * 4.0 + x_diff / 10.0, y_critical, 255, 0, 0, 255);
	sprintf(tmp_str, "%0.1f", critical);
	draw_text_f(esContext, x1 + x_diff / 6.0 * 4.0 + x_diff / 10.0, y_critical - 0.02, 0.04, 0.04, FONT_PINK, tmp_str);


	uint16_t steps = (uint16_t)(y_diff / 0.06);
	uint16_t step = 0.0;
	steps = 10;
	for (step = 0; step <= steps; step++) {
		draw_line_f(esContext, x1 + x_diff / 6.0 * 3.0, y2 - (y_diff * (float)step / steps), x1 + x_diff / 6.0 * 3.0 - x_diff / 10.0, y2 - (y_diff * (float)step / steps), 255, 255, 255, 255);
		sprintf(tmp_str, "%0.1f", min + (v_diff * (float)step / steps));
		draw_text_f(esContext, x1, y2 - (y_diff * (float)step / steps) - 0.02, 0.04, 0.04, FONT_WHITE, tmp_str);
	}

	steps = 50;
	for (step = 0; step <= steps; step++) {
		draw_line_f(esContext, x1 + x_diff / 6.0 * 3.0, y2 - (y_diff * (float)step / steps), x1 + x_diff / 6.0 * 3.0 - x_diff / 20.0, y2 - (y_diff * (float)step / steps), 200, 200, 200, 255);
	}

	sprintf(tmp_str, "%0.1f", value);

	draw_tria_f(esContext, x1 + x_diff / 6.0 * 3.0, y_value, x1 + x_diff / 6.0 * 4.0 + x_diff / 10.0, y_value - x_diff / 10.0, x1 + x_diff / 6.0 * 4.0 + x_diff / 10.0, y_value + x_diff / 10.0, 255, 255, 255, 255);
//	draw_text_f(esContext, x1 + x_diff / 6.0 * 4.0 + x_diff / 10.0, y_value - 0.02, 0.04, 0.04, FONT_PINK, tmp_str);

}


void draw_value_bar2 (ESContext *esContext, float x1, float y1, float x2, float y2, char *title, char *unit, uint8_t type, float min, float max, float warning, float critical, float value) {
	char tmp_str[1024];
	sprintf(tmp_str, title);
//	draw_text_f(esContext, (x1 + (x2 - x1) / 2) - strlen(tmp_str) * 0.1 / 2.0 * 0.6, y1, 0.1, 0.1, FONT_WHITE, tmp_str);
	draw_text_f(esContext, x1, y1, 0.1, 0.1, FONT_WHITE, tmp_str);
	draw_value_bar(esContext, x1, y1 + 0.11, x2, y2 - 0.16, 0, min, max, warning, critical, value);
	sprintf(tmp_str, "%0.1f%s", value, unit);
	draw_text_f(esContext, (x1 + (x2 - x1) / 2) - strlen(tmp_str) * 0.1 / 2.0 * 0.6, y2 - 0.13, 0.1, 0.1, FONT_WHITE, tmp_str);
}


void screen_telemetry (ESContext *esContext) {
	char tmp_str[1024];
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif

	glDisable( GL_DEPTH_TEST );

#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	ESMatrix modelview;
	esMatrixLoadIdentity(&modelview);
#endif


	draw_title(esContext, "Telemtry");
/*
	uint8_t y = 0;
	draw_value_display(esContext, -1.2, -0.7 + y++ * 0.28, 0.15, 10, 1, "Speed", "%0.1f km/h", ModelData.speed);
	draw_value_display(esContext, -1.2, -0.7 + y++ * 0.28, 0.15, 10, 1, "Altitude", "%0.1f m", ModelData.p_alt);
	draw_value_display(esContext, -1.2, -0.7 + y++ * 0.28, 0.15, 10, 1, "Voltage (RX)", "%0.1f V", ModelData.voltage_rx);
	draw_value_display(esContext, -1.2, -0.7 + y++ * 0.28, 0.15, 10, 1, "Curent", "%0.1f A", ModelData.ampere);

	y = 0;
	draw_value_display(esContext, 0.2, -0.7 + y++ * 0.28, 0.15, 10, 1, "RSSI to Air", "%0.1f %", ModelData.rssi_tx);
	draw_value_display(esContext, 0.2, -0.7 + y++ * 0.28, 0.15, 10, 1, "RSSI to Ground", "%0.1f %", ModelData.rssi_rx);
	y++;
//	draw_value_display(esContext, -1.2, -0.7 + y++ * 0.28, 0.15, 10, 1, "Voltage (TX)", "%0.1f V", ModelData.voltage_tx);
	draw_value_display(esContext, 0.2, -0.7 + y++ * 0.28, 0.15, 10, 1, "Direction", "%0.1f Grad", ModelData.yaw);
*/

//	draw_button(esContext, "telemetry_test1", VIEW_MODE_TELEMETRY, "TELE", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 0, 0, telemetry_null, 0);


	draw_value_bar2(esContext, -1.2, -0.7, -0.9, 0.0, "SPEED", "km/h", 0, 0.0, 200.0, 0.0, 0.0, ModelData.speed);
	draw_value_bar2(esContext, -0.7, -0.7, -0.4, 0.0, "ALT", "m", 0, -10.0, 999.0, 0.0, 0.0, ModelData.p_alt);
	draw_value_bar2(esContext, -0.2, -0.7, 0.1, 0.0, "VOLTS", "V", 0, 0.0, 14.0, 11.0, 10.0, ModelData.voltage_rx);



#ifdef SDLGL
	glPopMatrix();
#endif

	glEnable( GL_DEPTH_TEST );
}



