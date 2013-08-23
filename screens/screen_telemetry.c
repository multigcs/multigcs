
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

void screen_telemetry (ESContext *esContext) {
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


//	draw_button(esContext, "telemetry_test1", VIEW_MODE_TELEMETRY, "TELE", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 0, 0, telemetry_null, 0);


#ifdef SDLGL
	glPopMatrix();
#endif

	glEnable( GL_DEPTH_TEST );
}



