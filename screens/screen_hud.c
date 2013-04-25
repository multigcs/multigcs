
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


SDL_Surface *videodev_loop (void);
void draw_surface_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, SDL_Surface *screen);


uint8_t hud_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t hud_altitude_null (char *name, float x, float y, int8_t button, float data) {
	float ground_alt = (float)get_altitude(ModelData.p_lat, ModelData.p_long);
	ModelData.alt_offset = ModelData.p_alt - ground_alt;
	return 0;
}

uint8_t view_hud (char *name, float x, float y, int8_t button, float data) {
	hud_view = 1 - hud_view;
	return 0;
}

uint8_t view_hud_bw (char *name, float x, float y, int8_t button, float data) {
	contrast = 1 - contrast;
	return 0;
}

uint8_t view_hud_mark (char *name, float x, float y, int8_t button, float data) {
	hud_view_mark = 1;	
	return 0;
}

uint8_t view_hud_tunnel (char *name, float x, float y, int8_t button, float data) {
	hud_view_tunnel = 1 - hud_view_tunnel;
	return 0;
}

uint8_t view_hud_map (char *name, float x, float y, int8_t button, float data) {
	hud_view_map = 1 - hud_view_map;
	return 0;
}

uint8_t view_hud_video (char *name, float x, float y, int8_t button, float data) {
	hud_view_video = 1 - hud_view_video;
	return 0;
}

void draw_gcs (ESContext *esContext, float x1, float y1, float roll, float pitch, float yaw) {
	ESMatrix modelview;
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	UserData *userData = esContext->userData;
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate( &modelview, x1, -y1, -1.9 );
	esRotate( &modelview, roll, 0.0, 1.0, 0.0 );
	esRotate( &modelview, pitch, 1.0, 0.0, 0.0 );
	esTranslate( &modelview, -x1, y1, 1.9 );
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	// Transmitter
	float rc_roll = ModelData.radio[0];
	float rc_pitch = -ModelData.radio[1];
	float rc_yaw = ModelData.radio[2];
	float rc_throttle = ModelData.radio[3];
	draw_box_f3(esContext, x1 - 0.01, y1 - 0.08, 0.101, x1 + 0.01, y1 - 0.15, 0.101, 200, 200, 200, 255);
	draw_box_f3(esContext, x1 - 0.1, y1 - 0.08, 0.101, x1 + 0.1, y1 + 0.1, 0.101, 255, 255, 255, 255);
	draw_circle_f3(esContext, x1 - 0.05, y1, 0.1012, 0.03, 127, 127, 127, 255);
	draw_circle_f3(esContext, x1 + 0.05, y1, 0.1012, 0.03, 127, 127, 127, 255);
	draw_line_f3(esContext, x1 - 0.05, y1, 0.1012, x1 - 0.05 + (rc_yaw * 0.02 / 100.0), y1 + (rc_throttle * 0.02 / 100.0), 0.112, 255, 0, 0, 255);
	draw_circleFilled_f3(esContext, x1 - 0.05 + (rc_yaw * 0.02 / 100.0), y1 + (rc_throttle * 0.02 / 100.0), 0.112, 0.01, 255, 0, 0, 255);
	draw_line_f3(esContext, x1 + 0.05, y1, 0.1012, x1 + 0.05 + (rc_roll * 0.02 / 100.0), y1 + (rc_pitch * 0.02 / 100.0), 0.112, 255, 0, 0, 255);
	draw_circleFilled_f3(esContext, x1 + 0.05 + (rc_roll * 0.02 / 100.0), y1 + (rc_pitch * 0.02 / 100.0), 0.112, 0.01, 255, 0, 0, 255);

#ifdef SDLGL
	glPopMatrix();
#endif
}


void draw_turning_indicator (ESContext *esContext, float ti_x, float ti_y, float w, float h) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	float rate_yaw = (float)ModelData.gyro_z / 40.0;
	if (ModelData.teletype == TELETYPE_MULTIWII_21 || ModelData.teletype == TELETYPE_BASEFLIGHT) {
		rate_yaw = (float)ModelData.gyro_z / 40.0;
	}
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, ti_x, -ti_y, 0.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f3(esContext, 0.0 - (w / 2.2), 0.0 - 0.0025, 0.02, 0.0 - (w / 2.0), 0.0 + 0.0025, 0.01, 255, 255, 255, 255);
	draw_box_f3(esContext, 0.0 + (w / 2.2), 0.0 - 0.0025, 0.02, 0.0 + (w / 2.0), 0.0 + 0.0025, 0.01, 255, 255, 255, 255);
	esRotate(&modelview, 20, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f3(esContext, 0.0 + (w / 2.2), 0.0 - 0.0025, 0.005, 0.0 + (w / 2.0), 0.0 + 0.0025, 0.005, 255, 255, 255, 255);
	esRotate(&modelview, -20, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	esRotate(&modelview, -20, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f3(esContext, 0.0 - (w / 2.2), 0.0 - 0.0025, 0.005, 0.0 - (w / 2.0), 0.0 + 0.0025, 0.01, 255, 255, 255, 255);
	esRotate(&modelview, 20, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	esRotate(&modelview, rate_yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	// Rumpf
	draw_circleFilled_f3(esContext, 0.0, 0.0, 0.005, (w / 14.0), 255, 255, 255, 255);
	// Hoehe
	draw_box_f3(esContext, 0.0 - (w / 5.0), 0.0 - (w / 14.0), 0.005, 0.0 + (w / 5.0), 0.0 - (w / 14.0) + (w / 40.0), 0.005, 255, 255, 255, 255);
	// Seite
	draw_box_f3(esContext, 0.0 - (w / 40.0), 0.0, 0.005, 0.0 + (w / 140.0), 0.0 - 0.1, 0.005, 255, 255, 255, 255);
	// Flaechen
	draw_tria_f3(esContext, 0.0, 0.0 - (w / 40.0), 0.005, 0.0 + (w / 2.2), 0.0, (w / 40.0), 0.0, 0.0 + (w / 40.0), 0.005, 255, 255, 255, 255);
	draw_tria_f3(esContext, 0.0, 0.0 - (w / 40.0), 0.005, 0.0 - (w / 2.2), 0.0, (w / 40.0), 0.0, 0.0 + (w / 40.0), 0.005, 255, 255, 255, 255);
	esRotate(&modelview, -rate_yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	float accel = ModelData.acc_y * 50.0;
	if (ModelData.teletype == TELETYPE_MULTIWII_21 || ModelData.teletype == TELETYPE_BASEFLIGHT) {
		accel = (float)ModelData.acc_x / 256.0 * -50.0;
	}
	draw_circleFilled_f3_part(esContext, 0.0, 0.0 - (w / 4.0), 0.0005, (w / 2.0), (w / 2.2), 240.0, 300.0, 255, 255, 255, 255);
	draw_circleFilled_f3_part_end(esContext, 0.0, 0.0 - (w / 4.0), 0.001, (w / 2.0), (w / 2.2), 270.0 + accel, 25, 25, 25, 255);
#ifdef SDLGL
	glPopMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
}




void draw_altiude_rule (ESContext *esContext, float ti_x, float ti_y, float w, float h) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	char tmp_str[100];
	int n = 0;

	// Alt
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	float ax1 = ti_x;
	if (hud_view == 0) {
		ax1 = 0.65;
	}
	float ax = ax1 + 0.04;

	if (contrast == 1) {
		draw_box_f3(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 + 7 * 0.1, 0.001, 0, 0, 0, 255);
		draw_box_f3(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 - 7 * 0.1, 0.001, 0, 0, 0, 255);
	} else {
		draw_box_f3c2(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 + 7 * 0.1, 0.001, 50, 50, 50, 128, 50, 50, 50, 64);
		draw_box_f3c2(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 - 7 * 0.1, 0.001, 50, 50, 50, 128, 50, 50, 50, 64);
	}


#ifdef SDLGL
	float ground_alt = (float)get_altitude(ModelData.p_lat, ModelData.p_long);
	if (ground_alt - (ModelData.p_alt - ModelData.alt_offset) > -7.0) {
		float y1a = 0.0 - (ground_alt + 2.0 - (ModelData.p_alt - ModelData.alt_offset)) * 0.1;
		float y2a = 0.0 - (ground_alt - (ModelData.p_alt - ModelData.alt_offset)) * 0.1;
		float y1b = y2a;
		float y2b = 0.0 - (-7.0) * 0.1;
		if (y1b < -0.7) {
			y1b = -0.7;
			y2a = -0.7;
		}
		if (y1a < -0.7) {
			y1a = -0.7;
		}
		draw_box_f3c2(esContext
			, ax1, y1a, 0.0015
			, ax1 + 0.17, y2a, 0.0015
			, 0, 255, 0, 0
			, 255, 0, 0, 128
		);
		draw_box_f3c2(esContext
			, ax1, y1b, 0.0015
			, ax1 + 0.17, y2b, 0.0015
			, 255, 0, 0, 128
			, 255, 0, 0, 128
		);
		draw_line_f3(esContext, ax1 - 0.05, y2a, 0.0015, ax1 + 0.25, y2a, 0.002, 255, 255, 255, 255);
	} else if ((ModelData.p_alt - ModelData.alt_offset) - ground_alt > 100.0 - 7.0) {
		float y1a = 0.0 - (ground_alt + 100.0 - 2.0 - (ModelData.p_alt - ModelData.alt_offset)) * 0.1;
		float y2a = 0.0 - (ground_alt + 100.0 - (ModelData.p_alt - ModelData.alt_offset)) * 0.1;
		float y1b = 0.0 - (ground_alt + 100.0 - (ModelData.p_alt - ModelData.alt_offset)) * 0.1;
		float y2b = 0.0 - (7.0) * 0.1;
		if (y1b > 0.7) {
			y1b = 0.7;
			y2a = 0.7;
		}
		if (y1a > 0.7) {
			y1a = 0.7;
		}
		draw_box_f3c2(esContext
			, ax1, y1a, 0.0015
			, ax1 + 0.17, y2a, 0.0015
			, 0, 255, 0, 0
			, 255, 0, 0, 128
		);
		draw_box_f3c2(esContext
			, ax1, y1b, 0.0015
			, ax1 + 0.17, y2b, 0.0015
			, 255, 0, 0, 128
			, 255, 0, 0, 128
		);
		draw_line_f3(esContext, ax1 - 0.05, y2a, 0.0015, ax1 + 0.25, y2a, 0.002, 255, 255, 255, 255);
	}

	if (ground_alt - (ModelData.p_alt - ModelData.alt_offset) > 0.0) {
		draw_text_f3(esContext, 0.0 - (float)strlen("GROUND CONTACT") * 0.07 * 0.6 / 2.0, -0.75, 0.002, 0.07, 0.07, FONT_GREEN, "GROUND CONTACT");
	} else if (ground_alt - (ModelData.p_alt - ModelData.alt_offset) > -2.0) {
		draw_text_f3(esContext, 0.0 - (float)strlen("LOW ALT") * 0.07 * 0.6 / 2.0, -0.75, 0.002, 0.07, 0.07, FONT_GREEN, "LOW ALT");
	} else if ((ModelData.p_alt - ModelData.alt_offset) - ground_alt > 100.0) {
		draw_text_f3(esContext, 0.0 - (float)strlen("PUBLIC AIRSPACE") * 0.07 * 0.6 / 2.0, -0.75, 0.002, 0.07, 0.07, FONT_GREEN, "PUBLIC AIRSPACE");
	}

	sprintf(tmp_str, "%0.1f", (ModelData.p_alt - ModelData.alt_offset) - ground_alt);
	if (contrast == 1) {
		draw_text_f3(esContext, ax + 0.15 - strlen(tmp_str) * 0.07 * 0.6 - 0.05, 0.7, 0.0025, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f3(esContext, ax + 0.15 - strlen(tmp_str) * 0.07 * 0.6 - 0.05, 0.7, 0.0025, 0.07, 0.07, FONT_PINK, tmp_str);
	}
#endif

	draw_rect_f3(esContext, ax1, 0.0 - 7 * 0.1, 0.002, ax1 + 0.17, 0.0 + 7 * 0.1, 0.002, 255, 255, 255, 127);
	for (n = (int)(ModelData.p_alt - ModelData.alt_offset) - 5; n <= (int)(ModelData.p_alt - ModelData.alt_offset) + 6; n += 1) {
		float tsize = 0.05;
		sprintf(tmp_str, "%i", n);
		draw_text_f3(esContext, ax1 + 0.02, 0.0 - 0.025 - ((float)n - (ModelData.p_alt - ModelData.alt_offset)) * 0.1, 0.0015, tsize, tsize, FONT_WHITE, tmp_str);
		draw_line_f3(esContext, ax1, 0.0 - ((float)n - (ModelData.p_alt - ModelData.alt_offset)) * 0.1, 0.0015, ax1 + 0.02, 0.0 - ((float)n - (ModelData.p_alt - ModelData.alt_offset)) * 0.1, 0.0015, 255, 255, 255, 255);
	}
	for (n = (ModelData.p_alt - ModelData.alt_offset) + 0.3 - 5; n <= (ModelData.p_alt - ModelData.alt_offset) - 0.3 + 7; n += 1) {
		draw_line_f3(esContext, ax1, 0.0 - ((float)n - (ModelData.p_alt - ModelData.alt_offset)) * 0.1 + 0.05, 0.0015, ax1 + 0.01, 0.0 - ((float)n - (ModelData.p_alt - ModelData.alt_offset)) * 0.1 + 0.05, 0.0015, 255, 255, 255, 255);
	}
	draw_box_f3(esContext, ax, -0.05, 0.002, ax + 0.28, 0.05, 0.002, 0, 0, 0, 255);
	draw_tria_f3(esContext, ax - 0.02, 0.0, 0.002, ax, -0.02, 0.002, ax, 0.02, 0.002, 0, 0, 0, 255);
	draw_line_f3(esContext, ax, -0.05, 0.002, ax + 0.28, -0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, 0.05, 0.002, ax + 0.28, 0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax + 0.28, -0.05, 0.002, ax + 0.28, 0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, -0.05, 0.002, ax, -0.019, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, 0.05, 0.002, ax, 0.019, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax - 0.02, 0.0, 0.002, ax, -0.02, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax - 0.02, 0.0, 0.002, ax, 0.02, 0.002, 255, 255, 255, 255);

	sprintf(tmp_str, "%0.1f", (ModelData.p_alt - ModelData.alt_offset));
	if (contrast == 1) {
		draw_text_f3(esContext, ax + 0.15 - strlen(tmp_str) * 0.07 * 0.6 - 0.05, -0.77, 0.0025, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f3(esContext, ax + 0.15 - strlen(tmp_str) * 0.07 * 0.6 - 0.05, -0.77, 0.0025, 0.07, 0.07, FONT_PINK, tmp_str);
	}

	sprintf(tmp_str, "%0.1fm", (ModelData.p_alt - ModelData.alt_offset));
	draw_text_f3(esContext, ax + 0.28 - strlen(tmp_str) * 0.05 * 0.6 - 0.05, 0.0 - 0.025, 0.0025, 0.05, 0.05, FONT_WHITE, tmp_str);
	set_button("alt_null", VIEW_MODE_HUD, ax, -0.05, ax + 0.28, 0.05, hud_altitude_null, ModelData.p_alt, 0);

}



void draw_speed_rule (ESContext *esContext, float ti_x, float ti_y, float w, float h) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	char tmp_str[100];
	int n = 0;

	float speed = ModelData.speed * 1000.0 / 60.0 / 60.0; // km/h -> m/s

	// Speed
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	float ax1 = ti_x;
	if (hud_view == 0) {
		ax1 = -0.65;
	}
	float ax = ax1 - 0.04;
	ax1 -= 0.17;

	if (contrast == 1) {
		draw_box_f3(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 + 7 * 0.1, 0.001, 0, 0, 0, 255);
		draw_box_f3(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 - 7 * 0.1, 0.001, 0, 0, 0, 255);
	} else {
		draw_box_f3c2(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 + 7 * 0.1, 0.001, 50, 50, 50, 128, 50, 50, 50, 64);
		draw_box_f3c2(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 - 7 * 0.1, 0.001, 50, 50, 50, 128, 50, 50, 50, 64);
	}

	draw_rect_f3(esContext, ax1, 0.0 - 7 * 0.1, 0.002, ax1 + 0.17, 0.0 + 7 * 0.1, 0.002, 255, 255, 255, 127);
	for (n = (int)speed - 5; n <= (int)speed + 6; n += 1) {
		float tsize = 0.05;
		sprintf(tmp_str, "%i", n);
		draw_text_f3(esContext, ax1 + 0.02, 0.0 - 0.025 - ((float)n - speed) * 0.1, 0.0015, tsize, tsize, FONT_WHITE, tmp_str);
		draw_line_f3(esContext, ax1 + 0.17, 0.0 - ((float)n - speed) * 0.1, 0.0015, ax1 + 0.17 - 0.02, 0.0 - ((float)n - speed) * 0.1, 0.0015, 255, 255, 255, 255);
	}
	for (n = speed + 0.3 - 5; n <= speed - 0.3 + 7; n += 1) {
		draw_line_f3(esContext, ax1 + 0.17, 0.0 - ((float)n - speed) * 0.1 + 0.05, 0.0015, ax1 + 0.17 - 0.01, 0.0 - ((float)n - speed) * 0.1 + 0.05, 0.0015, 255, 255, 255, 255);
	}

	draw_box_f3(esContext, ax, -0.05, 0.002, ax - 0.28, 0.05, 0.002, 0, 0, 0, 255);
	draw_tria_f3(esContext, ax + 0.02, 0.0, 0.002, ax, -0.02, 0.002, ax, 0.02, 0.002, 0, 0, 0, 255);
	draw_line_f3(esContext, ax, -0.05, 0.002, ax - 0.28, -0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, 0.05, 0.002, ax - 0.28, 0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax - 0.28, -0.05, 0.002, ax - 0.28, 0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, -0.05, 0.002, ax, -0.019, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, 0.05, 0.002, ax, 0.019, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax + 0.02, 0.0, 0.002, ax, -0.02, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax + 0.02, 0.0, 0.002, ax, 0.02, 0.002, 255, 255, 255, 255);

	sprintf(tmp_str, "%0.1f", speed);
	if (contrast == 1) {
		draw_text_f3(esContext, ax1, -0.77, 0.0025, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f3(esContext, ax1, -0.77, 0.0025, 0.07, 0.07, FONT_PINK, tmp_str);
	}

	sprintf(tmp_str, "%0.1fm/s", speed);
	draw_text_f3(esContext, ax - strlen(tmp_str) * 0.05 * 0.6 - 0.05, 0.0 - 0.025, 0.0025, 0.05, 0.05, FONT_WHITE, tmp_str);
}



uint8_t graph1_data[3][200];
int16_t graph1_pointer = 0;
int16_t graph1_size = 128;


void screen_hud (ESContext *esContext) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	char tmp_str[400];
	char tmp_str2[400];
	int n = 0;
	uint8_t i = 0;
	float angle = 0.0;
	float dist1 = 0.0;
	float angle_up = 0.0;
	float dist2 = 0.0;
	float angle2 = 0.0;
	float angle_home = 0.0;

	//printf("hud#1\n");

#ifdef SDLGL
	if (hud_view_video == 1) {
		draw_surface_f3(esContext, -1.4, -1.0, 1.4, 1.0, -0.001, videodev_loop());
	}
	if (hud_view_map == 1) {
		if (hud_view_video == 1) {
			display_map(esContext, lat, lon, zoom, 4);
		} else {
			display_map(esContext, lat, lon, zoom, 3);
		}
	}
#endif
	glDisable( GL_DEPTH_TEST );


	get_dir(ModelData.p_lat, ModelData.p_long, ModelData.p_alt, WayPoints[waypoint_active].p_lat, WayPoints[waypoint_active].p_long, WayPoints[waypoint_active].p_alt, &angle, &dist1, &angle_up, &dist2);
	angle2 = angle - ModelData.yaw;
	if (angle2 > 180.0) {
		angle2 = angle2 - 360.0;
	}
	get_dir(ModelData.p_lat, ModelData.p_long, ModelData.p_alt, WayPoints[0].p_lat, WayPoints[0].p_long, WayPoints[0].p_alt, &angle, &dist1, &angle_up, &dist2);
	angle_home = angle - ModelData.yaw;
	if (angle_home > 180.0) {
		angle_home = angle_home - 360.0;
	}

	// Horizont / Background
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, 0.0, -3.0);
	esRotate(&modelview, -ModelData.roll, 0.0, 0.0, 1.0);
	esTranslate(&modelview, 0.0, -ModelData.pitch / 70.0, 0.0);
	esTranslate(&modelview, 0.0, 0.0, 3.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	//printf("hud#2\n");

	if (hud_view_map != 1 && hud_view_video != 1) {
		if (contrast == 1) {
			draw_box_f3(esContext, -2.5f, -2.5f, -0.001, 2.5f, 0.0f, -0.001, 127, 127, 127, 255);
			draw_box_f3(esContext, -2.5f, 0.0f, -0.001, 2.5f, 2.5f, -0.001, 255, 255, 255, 255);
		} else {
#ifdef SDLGL
			draw_box_f3c2(esContext, -2.5f, -2.5f, -0.001, 2.5f, 0.0f, -0.001, 0x01, 0x8e, 0xea, 100, 0x01, 0x8e, 0xea, 255); // blue
			draw_box_f3c2(esContext, -2.5f, 0.0f, -0.001, 2.5f, 2.5f, -0.001, 0xb1, 0x56, 0x1f, 255, 0xb1, 0x56, 0x1f, 100);  // brown
#else
			char tmp_str[128];
			sprintf(tmp_str, "%s/textures/blue.png", BASE_DIR);
			draw_image_f3(esContext, -2.5f, -2.5f, 2.5f, 0.0f, -0.001, tmp_str); // blue
			sprintf(tmp_str, "%s/textures/brown.png", BASE_DIR);
			draw_image_f3(esContext, -2.5f, 0.0f, 2.5f, 2.5f, -0.001, tmp_str); // brown
#endif
		}
	}



#ifdef SDLGL
	glPopMatrix();
#endif


	// Pitch & Roll-Winkel
	for (n = -30 - ((int)(-ModelData.pitch / 10) % 10 * 10); n <= 20 - ((int)((-ModelData.pitch - 3) / 10) % 10 * 10); n += 10) {
		// Pitch
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, 0.0, -3.0);
		esRotate(&modelview, -ModelData.roll, 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, (float)(n + -ModelData.pitch) / 70.0, 0.0);
		esTranslate(&modelview, 0.0, 0.0, 3.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		if (n == 0) {
			draw_line_f3(esContext, -2.0, 0.0, -0.001, 2.0, 0.0, -0.001, 255, 255, 255, 255);
		} else {
			sprintf(tmp_str, "%i", n * -1);
			draw_text_f3(esContext, -0.2 - strlen(tmp_str) * 0.05 * 0.6, -0.025, 0.001, 0.05, 0.05, FONT_WHITE, tmp_str);
			draw_text_f3(esContext, 0.2, -0.025, 0.001, 0.05, 0.05, FONT_WHITE, tmp_str);

			uint8_t alpha = 255;
			if ((n + -ModelData.pitch) < 0) {
				alpha = 255 - -(n + -ModelData.pitch) * 255 / 45;
			} else {
				alpha = 255 - (n + -ModelData.pitch) * 255 / 45;
			}
			if ((n + -ModelData.pitch) > -45 && (n + -ModelData.pitch) < 45) {
				draw_line_f3(esContext, -0.15, 0.0, 0.001, 0.15, 0.0, 0.001, 255, 255, 255, alpha);
			}
		}
#ifdef SDLGL
		glPopMatrix();
#endif
	}


	//printf("hud#3\n");


//	for (n = -40 - ((int)(-ModelData.pitch / 5) % 10 * 5); n <= 30 - ((int)(-ModelData.pitch / 5) % 10 * 5); n += 5) {
	for (n = -35 - ((int)(-ModelData.pitch / 10) % 10 * 10); n <= 25 - ((int)((-ModelData.pitch - 3) / 10) % 10 * 10); n += 10) {
		// Pitch
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, 0.0, -3.0);
		esRotate(&modelview, -ModelData.roll, 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, (float)(n + -ModelData.pitch) / 70.0, 0.0);
		esTranslate(&modelview, 0.0, 0.0, 3.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		uint8_t alpha = 255;
		if ((n + -ModelData.pitch) < 0) {
			alpha = 255 - -(n + -ModelData.pitch) * 255 / 45;
		} else {
			alpha = 255 - (n + -ModelData.pitch) * 255 / 45;
		}
		if ((n + -ModelData.pitch) > -45 && (n + -ModelData.pitch) < 45) {
			draw_line_f3(esContext, -0.1, 0.0, 0.001, 0.1, 0.0, 0.001, 255, 255, 255, alpha);
		}
#ifdef SDLGL
		glPopMatrix();
#endif
	}

	for (n = -45; n <= 45; n += 10) {
		// Roll
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esRotate(&modelview, -(float)n, 0.0, 0.0, 1.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		uint8_t alpha = 255;
/*
		if ((n) < 0) {
			alpha = 255 - -(n) * 255 / 45;
		} else {
			alpha = 255 - (n) * 255 / 45;
		}
*/
		if ((n) > -45 && (n) < 45) {
			draw_line_f(esContext, 0.0, -0.65, 0.0, -0.6, 255, 255, 255, alpha);
		}
#ifdef SDLGL
		glPopMatrix();
#endif
	}

	for (n = -45; n <= 45; n += 5) {
		// Roll
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esRotate(&modelview, -(float)n, 0.0, 0.0, 1.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		uint8_t alpha = 255;
/*		if ((n) < 0) {
			alpha = 255 - -(n) * 255 / 45;
		} else {
			alpha = 255 - (n) * 255 / 45;
		}
*/
		if ((n) > -45 && (n) < 45) {
			draw_line_f(esContext, 0.0, -0.63, 0.0, -0.6, 255, 255, 255, alpha);
		}
#ifdef SDLGL
		glPopMatrix();
#endif
	}

	//printf("hud#4\n");


	// Roll-Zeiger
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif

	esRotate(&modelview, -ModelData.roll, 0.0, 0.0, 1.0);

#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_line_f(esContext, 0.0, -0.6, -0.04, -0.56, 255, 255, 255, 255);
	draw_line_f(esContext, 0.0, -0.6, 0.04, -0.56, 255, 255, 255, 255);
	draw_line_f(esContext, -0.04, -0.56, 0.04, -0.56, 255, 255, 255, 255);
	draw_line_f(esContext, -0.04, -0.54, 0.04, -0.54, 255, 255, 255, 255);
	draw_line_f(esContext, -0.04, -0.54, -0.04, -0.56, 255, 255, 255, 255);
	draw_line_f(esContext, 0.04, -0.54, 0.04, -0.56, 255, 255, 255, 255);

#ifdef SDLGL
	glPopMatrix();
#endif

	// Center-Cross
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f3(esContext, -0.45, -0.02, 0.001, -0.15, 0.02, 0.001, 255, 255, 255, 255);
	draw_box_f3(esContext, -0.15 - 0.04, -0.02, 0.001, -0.15, 0.08, 0.001, 255, 255, 255, 255);
	draw_box_f3(esContext, 0.15, -0.02, 0.001, 0.45, 0.02, 0.001, 255, 255, 255, 255);
	draw_box_f3(esContext, 0.15, -0.02, 0.001, 0.15 + 0.04, 0.08, 0.001, 255, 255, 255, 255);
#ifdef SDLGL
	glPopMatrix();
#endif
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, 0.0, +0.01);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f(esContext, -0.45 + 0.005, -0.02 + 0.005, -0.15 - 0.005, 0.02 - 0.005, 0, 0, 0, 255);
	draw_box_f(esContext, -0.15 - 0.04 + 0.005, -0.02 + 0.005, -0.15 - 0.005, 0.08 - 0.005, 0, 0, 0, 255);
	draw_box_f(esContext, 0.15 + 0.005, -0.02 + 0.005, 0.45 - 0.005, 0.02 - 0.005, 0, 0, 0, 255);
	draw_box_f(esContext, 0.15 + 0.005, -0.02 + 0.005, 0.15 + 0.04 - 0.005, 0.08 - 0.005, 0, 0, 0, 255);
#ifdef SDLGL
	glPopMatrix();
#endif
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, 0.0, +0.01);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	//printf("hud#5\n");


	if (contrast == 1) {
		draw_box_f3(esContext, -0.005, -0.2, 0.001, 0.005, 0.2, 0.001, 0, 0, 0, 255);
		draw_box_f3(esContext, -0.2, -0.005, 0.001, 0.2, 0.005, 0.001, 0, 0, 0, 255);
	} else {
		draw_box_f3(esContext, -0.005, -0.2, 0.001, 0.005, 0.2, 0.001, 0xff, 0x33, 0xfc, 255); // pink
		draw_box_f3(esContext, -0.2, -0.005, 0.001, 0.2, 0.005, 0.001, 0xff, 0x33, 0xfc, 255); // pink
	}
#ifdef SDLGL
	glPopMatrix();
#endif


	// Rahmen
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	if (hud_view == 0) {
		draw_image(esContext, 0, 0, esContext->width, esContext->height, TEXTURE_HUD_FRAME);
	}


	// Alt
	draw_altiude_rule(esContext, 1.0, -0.6, 0.0, 0.0);

	// Speed
	draw_speed_rule(esContext, -1.0, -0.6, 0.0, 0.0);

	//printf("hud#6\n");

	// Status
	draw_text_f3(esContext, -1.0 - strlen("ARMED") * 0.07 * 0.6 / 2.0, -0.92, 0.002, 0.07, 0.07, FONT_TRANS, "ARMED");
	draw_line_f3(esContext, -0.8, -0.94, 0.002, -0.8, -0.83, 0.002, 255, 255, 255, 255);
	draw_text_f3(esContext, -0.6 - strlen("MANUAL") * 0.07 * 0.6 / 2.0, -0.92, 0.002, 0.07, 0.07, FONT_TRANS, "MANUAL");
	draw_line_f3(esContext, -0.4, -0.94, 0.002, -0.4, -0.83, 0.002, 255, 255, 255, 255);
	draw_text_f3(esContext, -0.2 - strlen("RTL") * 0.07 * 0.6 / 2.0, -0.92, 0.002, 0.07, 0.07, FONT_TRANS, "RTL");
	draw_line_f3(esContext, 0.0, -0.94, 0.002, 0.0, -0.83, 0.002, 255, 255, 255, 255);
	draw_text_f3(esContext, 0.2 - strlen("POS_HOLD") * 0.07 * 0.6 / 2.0, -0.92, 0.002, 0.07, 0.07, FONT_TRANS, "POS_HOLD");
	draw_line_f3(esContext, 0.4, -0.94, 0.002, 0.4, -0.83, 0.002, 255, 255, 255, 255);
	draw_text_f3(esContext, 0.6 - strlen("MISSION") * 0.07 * 0.6 / 2.0, -0.92, 0.002, 0.07, 0.07, FONT_TRANS, "MISSION");
	draw_line_f3(esContext, 0.8, -0.94, 0.002, 0.8, -0.83, 0.002, 255, 255, 255, 255);
	draw_text_f3(esContext, 1.0 - strlen("FAILSAVE") * 0.07 * 0.6 / 2.0, -0.92, 0.002, 0.07, 0.07, FONT_TRANS, "FAILSAVE");

	static uint8_t last_armed = MODEL_ARMED;
	static uint8_t last_mode = MODEL_MODE_MANUAL;
	if (ModelData.mode == MODEL_MODE_MANUAL) {
		if (last_mode != ModelData.mode) {
			system("#espeak -v en \"manual\" > /dev/null 2> /dev/null &");
		}
		draw_text_f(esContext, -0.6 - strlen("MANUAL") * 0.07 * 0.6 / 2.0, -0.92, 0.07, 0.07, FONT_GREEN, "MANUAL");
	} else if (ModelData.mode == MODEL_MODE_RTL) {
		if (last_mode != ModelData.mode) {
			system("#espeak -v en \"rtl\" > /dev/null 2> /dev/null &");
		}
		draw_text_f(esContext, -0.2 - strlen("RTL") * 0.07 * 0.6 / 2.0, -0.92, 0.07, 0.07, FONT_GREEN, "RTL");
	} else if (ModelData.mode == MODEL_MODE_POSHOLD) {
		if (last_mode != ModelData.mode) {
			system("#espeak -v en \"Position hold\" > /dev/null 2> /dev/null &");
		}
		draw_text_f(esContext, 0.2 - strlen("POS_HOLD") * 0.07 * 0.6 / 2.0, -0.92, 0.07, 0.07, FONT_GREEN, "POS_HOLD");
	} else if (ModelData.mode == MODEL_MODE_MISSION) {
		if (last_mode != ModelData.mode) {
			system("#espeak -v en \"mission\" > /dev/null 2> /dev/null &");
		}
		draw_text_f(esContext, 0.6 - strlen("MISSION") * 0.07 * 0.6 / 2.0, -0.92, 0.07, 0.07, FONT_GREEN, "MISSION");
	}
	if (ModelData.armed == MODEL_ARMED) {
		if (last_armed != ModelData.armed) {
			system("#espeak -v en \"armed\" > /dev/null 2> /dev/null &");
		}
		if (contrast == 1) {
			draw_text_f(esContext, -1.0 - strlen("ARMED") * 0.07 * 0.6 / 2.0, -0.92, 0.07, 0.07, FONT_WHITE, "ARMED");
		} else {
			draw_text_f(esContext, -1.0 - strlen("ARMED") * 0.07 * 0.6 / 2.0, -0.92, 0.07, 0.07, FONT_GREEN, "ARMED");
		}
	} else if (ModelData.armed == MODEL_ARMING) {
		draw_text_f(esContext, -1.0 - strlen("ARMED") * 0.07 * 0.6 / 2.0, -0.92, 0.07, 0.07, FONT_GREEN_BG, "ARMED");
	} else {
		if (last_armed != ModelData.armed) {
			system("#espeak -v en \"disarmed\" > /dev/null 2> /dev/null &");
		}
	}
//	if (ModelData.status == MAV_STATE_CRITICAL) {
//		if (last_status != ModelData.status) {
//			system("#espeak -v en \"failsave\" > /dev/null 2> /dev/null &");
//		}
//		draw_text_f(esContext, 1.0 - strlen("FAILSAVE") * 0.07 * 0.6 / 2.0, -0.92, 0.07, 0.07, FONT_GREEN, "FAILSAVE");
//	}
	last_armed = ModelData.armed;
	last_mode = ModelData.mode;

	// Yaw
	float compas_r = 0.9;
	float compas_y = 1.5;
	if (hud_view == 1) {
		draw_circleFilled_f(esContext, 0.0, compas_y, compas_r + 0.01, 0, 0, 0, 127);
	} else {
		draw_circleFilled_f(esContext, 0.0, compas_y, compas_r + 0.01, 0, 0, 0, 255);
	}
	draw_line_f(esContext, 0.0, compas_y - compas_r, 0.0, compas_y, 255, 255, 255, 255);
	sprintf(tmp_str, "%0.1f", ModelData.yaw);
	if (contrast == 1) {
		draw_text_f(esContext, -0.2 - strlen(tmp_str) * 0.07 * 0.6 / 2.0 - 0.01, 0.9, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f(esContext, -0.2 - strlen(tmp_str) * 0.07 * 0.6 / 2.0 - 0.01, 0.9, 0.07, 0.07, FONT_PINK, tmp_str);
	}
	sprintf(tmp_str, "MAG");
	if (contrast == 1) {
		draw_text_f(esContext, 0.2 - strlen(tmp_str) * 0.07 * 0.6 / 2.0 - 0.01, 0.9, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f(esContext, 0.2 - strlen(tmp_str) * 0.07 * 0.6 / 2.0 - 0.01, 0.9, 0.07, 0.07, FONT_GREEN, tmp_str);
	}

	//printf("hud#7\n");

	// Yaw-Arrow
	if (contrast == 1) {
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r - 0.05 + 0.05, 0, 0, 0, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r - 0.05 + 0.05, 0, 0, 0, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.05, compas_y - compas_r - 0.05, 0, 0, 0, 255);
	} else {
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r - 0.05 + 0.05, 255, 255, 255, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r - 0.05 + 0.05, 255, 255, 255, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.05, compas_y - compas_r - 0.05, 255, 255, 255, 255);
	}

	for (n = (int)ModelData.yaw / 10 * 10 - 60; n <= (int)ModelData.yaw / 10 * 10 + 60; n += 10) {
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, -compas_y, -3.0);
		esRotate(&modelview, ((float)n - ModelData.yaw), 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, compas_y, 3.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		draw_line_f(esContext, 0.0, compas_y - compas_r, 0.0, compas_y - compas_r + 0.05, 255, 255, 255, 255);
		if (n >= 360) {
			sprintf(tmp_str, "%i", n - 360);
		} else if (n < 0) {
			sprintf(tmp_str, "%i", n + 360);
		} else {
			sprintf(tmp_str, "%i", n);
		}
		draw_text_f(esContext, 0.0 - strlen(tmp_str) * 0.05 * 0.6 / 2.0 - 0.01, compas_y - compas_r + 0.05, 0.05, 0.05, FONT_WHITE, tmp_str);
#ifdef SDLGL
		glPopMatrix();
#endif
	}
	for (n = (int)ModelData.yaw / 10 * 10 - 60; n <= (int)ModelData.yaw / 10 * 10 + 60; n += 1) {
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, -compas_y, -3.0);
		esRotate(&modelview, ((float)n - ModelData.yaw) + 5.0, 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, compas_y, 3.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		draw_line_f(esContext, 0.0, compas_y - compas_r, 0.0, compas_y - compas_r + 0.03, 255, 255, 255, 255);

#ifdef SDLGL
		glPopMatrix();
#endif
	}

	//printf("hud#8\n");

	// Home & Waypoint-Dir
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, -compas_y, -3.0);
	esRotate(&modelview, angle2, 0.0, 0.0, 1.0);
	esTranslate(&modelview, 0.0, compas_y, 3.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	// Next-Waypoint-Arrow
	if (contrast == 1) {
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 255, 255, 255, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 255, 255, 255, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.05, compas_y - compas_r - 0.05, 255, 255, 255, 255);

		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 255, 255, 255, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 255, 255, 255, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.05, compas_y - compas_r + 0.05, 0, 255, 0, 255);
	} else {
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 0, 255, 0, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 0, 255, 0, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.05, compas_y - compas_r - 0.05, 0, 255, 0, 255);

		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 0, 255, 0, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 0, 255, 0, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.05, compas_y - compas_r + 0.05, 0, 255, 0, 255);
	}
#ifdef SDLGL
	glPopMatrix();
#endif

	// Route-Dir Arrow (Waypoint)
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	sprintf(tmp_str, "%0.1f", (angle2));
	if (angle2 > 0.0) {
		if (contrast == 1) {
			draw_line_f(esContext, 0.0, 0.85, 0.1, 0.85, 255, 255, 255, 255);
			draw_line_f(esContext, 0.05, 0.85 - 0.01, 0.1, 0.85, 255, 255, 255, 255);
			draw_line_f(esContext, 0.05, 0.85 + 0.01, 0.1, 0.85, 255, 255, 255, 255);
			draw_text_f3(esContext, 0.11, 0.85 - 0.02, 0.002, 0.04, 0.04, FONT_WHITE, tmp_str);
		} else {
			draw_line_f(esContext, 0.0, 0.85, 0.1, 0.85, 0, 255, 0, 255);
			draw_line_f(esContext, 0.05, 0.85 - 0.01, 0.1, 0.85, 0, 255, 0, 255);
			draw_line_f(esContext, 0.05, 0.85 + 0.01, 0.1, 0.85, 0, 255, 0, 255);
			draw_text_f3(esContext, 0.11, 0.85 - 0.02, 0.002, 0.04, 0.04, FONT_GREEN, tmp_str);
		}
	} else {
		if (contrast == 1) {
			draw_line_f(esContext, 0.0, 0.85, -0.1, 0.85, 255, 255, 255, 255);
			draw_line_f(esContext, -0.05, 0.85 - 0.01, -0.1, 0.85, 255, 255, 255, 255);
			draw_line_f(esContext, -0.05, 0.85 + 0.01, -0.1, 0.85, 255, 255, 255, 255);
			draw_text_f3(esContext, -0.11 - strlen(tmp_str) * 0.04 * 0.6 - 0.01, 0.85 - 0.02, 0.002, 0.04, 0.04, FONT_WHITE, tmp_str);
		} else {
			draw_line_f(esContext, 0.0, 0.85, -0.1, 0.85, 0, 255, 0, 255);
			draw_line_f(esContext, -0.05, 0.85 - 0.01, -0.1, 0.85, 0, 255, 0, 255);
			draw_line_f(esContext, -0.05, 0.85 + 0.01, -0.1, 0.85, 0, 255, 0, 255);
			draw_text_f3(esContext, -0.11 - strlen(tmp_str) * 0.04 * 0.6 - 0.01, 0.85 - 0.02, 0.002, 0.04, 0.04, FONT_GREEN, tmp_str);
		}
	}



#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, -compas_y, -3.0);
	esRotate(&modelview, angle_home, 0.0, 0.0, 1.0);
	esTranslate(&modelview, 0.0, compas_y, 3.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	// Home-Arrow
	float r = compas_y - compas_r + 0.1;
	draw_line_f(esContext, -0.03, r - 0.05, 0.0, r - 0.1, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, 0.03, r - 0.05, 0.0, r - 0.1, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, -0.03, r - 0.05, 0.03, r - 0.05, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, -0.03, r, 0.03, r, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, -0.03, r - 0.05, -0.03, r, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, 0.03, r - 0.05, 0.03, r, 0xff, 0x33, 0xfc, 255);
#ifdef SDLGL
	glPopMatrix();
#endif


	//printf("hud#9\n");

	// Route-Dir Arrow (Home)
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	if (angle_home > 0.0) {
		if (contrast == 1) {
			draw_line_f(esContext, 0.0, 0.9, 0.05, 0.9, 255, 255, 255, 255);
			draw_line_f(esContext, 0.025, 0.9 - 0.01, 0.05, 0.9, 255, 255, 255, 255);
			draw_line_f(esContext, 0.025, 0.9 + 0.01, 0.05, 0.9, 255, 255, 255, 255);
		} else {
			draw_line_f(esContext, 0.0, 0.9, 0.05, 0.9, 0xff, 0x33, 0xfc, 255);
			draw_line_f(esContext, 0.025, 0.9 - 0.01, 0.05, 0.9, 0xff, 0x33, 0xfc, 255);
			draw_line_f(esContext, 0.025, 0.9 + 0.01, 0.05, 0.9, 0xff, 0x33, 0xfc, 255);
		}
	} else {
		if (contrast == 1) {
			draw_line_f(esContext, 0.0, 0.9, -0.05, 0.9, 255, 255, 255, 255);
			draw_line_f(esContext, -0.025, 0.9 - 0.01, -0.05, 0.9, 255, 255, 255, 255);
			draw_line_f(esContext, -0.025, 0.9 + 0.01, -0.05, 0.9, 255, 255, 255, 255);
		} else {
			draw_line_f(esContext, 0.0, 0.9, -0.05, 0.9, 0xff, 0x33, 0xfc, 255);
			draw_line_f(esContext, -0.025, 0.9 - 0.01, -0.05, 0.9, 0xff, 0x33, 0xfc, 255);
			draw_line_f(esContext, -0.025, 0.9 + 0.01, -0.05, 0.9, 0xff, 0x33, 0xfc, 255);
		}
	}

	//printf("hud#9a\n");

#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	//printf("hud#9b\n");

	if (hud_view == 0) {
		// Turn-Indicator
		draw_turning_indicator(esContext, 1.15, 0.25, 0.4, 0.1);

	//printf("hud#9c\n");


		// CPU, Voltage & Speed
		float volt_mind = 4.0;
		float volt_max = 6.0;
		float volt_diff = volt_max - volt_mind;
		float volt_diff2 = ModelData.voltage_rx - volt_mind;
		if (ModelData.found_rc != 1) {
			volt_mind = 10.0;
			volt_max = 12.6;
			volt_diff2 = ModelData.voltage - volt_mind;
		}
		float percent = 100.0 / volt_diff * volt_diff2;
		float voltage_all = 0.0;
		float voltage_real = 0.0;
		float voltage_max = 0.0;
		for (i = 0; i < 6; i++) {
			if (ModelData.voltage_zell[i] > 0.0) {
				voltage_real += ModelData.voltage_zell[i];
				voltage_all += ModelData.voltage_zell[i] - 3.0;
				voltage_max += 1.2;
			}
		}

	//printf("hud#9d\n");

		sprintf(tmp_str, "%0.0fkm/h", ModelData.speed);
		draw_circleMeter_f3(esContext, -1.05, -0.5, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, (ModelData.speed * 100.0 / 250.0), "Speed", tmp_str, 0);

		if (ModelData.found_rc == 1) {
			sprintf(tmp_str, "%0.1fV", ModelData.voltage_rx);
			draw_circleMeter_f3(esContext, -1.05, -0.2, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, percent, "Volt-RX", tmp_str, 0);
		} else {
			sprintf(tmp_str, "%0.1fV", ModelData.voltage);
			draw_circleMeter_f3(esContext, -1.05, -0.2, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, percent, "Volt", tmp_str, 0);
		}

		if (voltage_max != 0.0) {
			sprintf(tmp_str, "%0.1fV", voltage_real);
			draw_circleMeter_f3(esContext, -1.05, 0.3, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, voltage_all * 100.0 / voltage_max, "Volt", tmp_str, 0);
		}

		if (ModelData.found_rc == 1) {
			sprintf(tmp_str, "%0.1fA", ModelData.ampere);
			draw_circleMeter_f3(esContext, -1.05, 0.6, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, ModelData.ampere, "Strom", tmp_str, 0);
		}

	//printf("hud#9e\n");

		if (ModelData.teletype != TELETYPE_MULTIWII_21 && ModelData.teletype != TELETYPE_BASEFLIGHT) {
			sprintf(tmp_str, "CPU %0.0f%%", ModelData.load);
			draw_circleMeter_f3(esContext, -1.05, 0.025, 0.001, 0.06, 20.0, 33.0, 66.0, 160.0, 50, "", "", 3);
			draw_button(esContext, "hud_load", VIEW_MODE_HUD, tmp_str, FONT_WHITE, -1.05, 0.025, 0.003, 0.035, 1, 0, hud_null, 0);
		}

	//printf("hud#9f\n");

		// RC-Values
		for (n = 0; n < 8; n++) {
			float x1 = -1.3;
			float y1 = -0.55 + (float)n * 0.1;
			float val = (float)ModelData.radio[n] / 2.0 + 50.0;
			if (val > 100.0) {
				val = 100.0;
			} else if (val < -100.0) {
				val = -100.0;
			}
			if (n >= 4) {
				draw_circleMeter_f3(esContext, x1, y1, 0.001, 0.06, 20.0, 33.0, 66.0, 160.0, val, "", "", 1);
			} else {
				draw_circleMeter_f3(esContext, x1, y1, 0.001, 0.06, 20.0, 50.0, 50.0, 160.0, val, "", "", 1);
			}
			if (ModelData.teletype == TELETYPE_MULTIWII_21 || ModelData.teletype == TELETYPE_OPENPILOT || ModelData.teletype == TELETYPE_BASEFLIGHT) {
				if (n == 0) {
					draw_button(esContext, "hud_rd_1", VIEW_MODE_HUD, "ROLL", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 1) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "PITCH", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 2) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "YAW", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 3) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "THROTTLE", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 4) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX1", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 5) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX2", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 6) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX3", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 7) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX4", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				}
			} else if (ModelData.teletype == TELETYPE_AUTOQUAD) {
				if (n == 0) {
					draw_button(esContext, "hud_rd_1", VIEW_MODE_HUD, "THROTTLE", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 1) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "ROLL", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 2) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "PITCH", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 3) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "YAW", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 4) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "GEAR", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 5) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "MAN/PH/W", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 6) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "RTL/SH", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 7) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX3", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				}
			} else if (ModelData.teletype == TELETYPE_ARDUPILOT || ModelData.teletype == TELETYPE_MEGAPIRATE_NG) {
				if (n == 0) {
					draw_button(esContext, "hud_rd_1", VIEW_MODE_HUD, "ROLL", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 1) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "PITCH", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 2) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "THROTTLE", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 3) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "YAW", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 4) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX1", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 5) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX2", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 6) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX3", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 7) {
					draw_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX4", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				}
			} else {
				sprintf(tmp_str, "CH %i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
			}
		}
		static float min_g = 1.0;
		static float max_g = 0.0;

	//printf("hud#9g\n");

		float all_g = ModelData.acc_z * -1;
		if (ModelData.teletype == TELETYPE_MULTIWII_21 || ModelData.teletype == TELETYPE_BASEFLIGHT) {
			all_g = (float)ModelData.acc_z / 256.0;
		}
		if (min_g > all_g) {
			min_g = all_g;
		}
		if (max_g < all_g) {
			max_g = all_g;
		}
		sprintf(tmp_str, "Accel: %0.1fg", all_g);
		sprintf(tmp_str2, "%0.1fg %0.1fg", min_g, max_g);
		draw_circleMeter_f3(esContext, 1.15, -0.5, 0.001, 0.14, 0.0, 0.0, 50.0, 180.0, 50.0, tmp_str, tmp_str2, 0);
		draw_circleMeter_f3(esContext, 1.15, -0.2, 0.001, 0.14, 0.0, 50.0, 50.0, 180.0, 50.0, "Vario", "-1.2m/s", 0);


		if (ModelData.found_rc == 1) {
			// Lipo-Watch
			for (i = 0; i < 6; i++) {
				sprintf(tmp_str2, "hud_lv%i", i);
				if (ModelData.voltage_zell[i] != 0.0) {
					sprintf(tmp_str, "%0.2fV", ModelData.voltage_zell[i]);
					draw_circleMeter_f3(esContext, -1.3, 0.3 + (i * 0.1), 0.001, 0.06, 20.0, 20.0, 40.0, 160.0, ((ModelData.voltage_zell[i] - 3.0) * 100.0 / 1.2), "", "", 1);
					draw_button(esContext, tmp_str2, VIEW_MODE_HUD, tmp_str, FONT_WHITE, -1.3, 0.3 + (i * 0.1), 0.003, 0.035, 1, 0, hud_null, 0);
				}
			}

			// Temperature
			draw_circleMeter_f3(esContext, 1.07, 0.025, 0.001, 0.06, 20.0, 50.0, 50.0, 160.0, ((float)ModelData.temperature[0] + 30) * 100 / 280, "", "", 3);
			sprintf(tmp_str, "%i°C", ModelData.temperature[0]);
			draw_button(esContext, "temp1", VIEW_MODE_HUD, tmp_str, FONT_WHITE, 1.07, 0.025, 0.003, 0.035, 1, 0, hud_null, 0);
			draw_circleMeter_f3(esContext, 1.23, 0.025, 0.001, 0.06, 20.0, 50.0, 50.0, 160.0, 50.0, "", "", 3);
			sprintf(tmp_str, "%i°C", ModelData.temperature[1]);
			draw_button(esContext, "temp2", VIEW_MODE_HUD, tmp_str, FONT_WHITE, 1.23, 0.025, 0.003, 0.035, 1, 0, hud_null, 0);

			// Test-Graph
			graph1_data[0][graph1_pointer] = ModelData.rssi_rx;
			graph1_data[1][graph1_pointer] = ModelData.rssi_tx;
			if (graph1_pointer < graph1_size) {
				graph1_pointer++;
			} else {
				graph1_pointer = 0;
			}
			for (n = 0; n < 2; n++) {
				draw_box_f3(esContext, 0.95, 0.45 + (float)n * 0.1, 0.001, 1.35, 0.45 + (float)n * 0.1 + 0.08, 0.001, 200, 200, 200, 64);
				draw_line_f3(esContext, 0.95, 0.45 + (float)n * 0.1 + 0.04, 0.002, 1.35, 0.45 + (float)n * 0.1 + 0.04, 0.002, 255, 255, 255, 127);
				if (n == 0) {
					draw_button(esContext, "rssi_rx", VIEW_MODE_HUD, "RSSI RX", FONT_WHITE, 0.95, 0.45 + (float)n * 0.1 + 0.05, 0.002, 0.035, 0, 0, hud_null, 0);
				} else {
					draw_button(esContext, "rssi_tx", VIEW_MODE_HUD, "RSSI TX", FONT_WHITE, 0.95, 0.45 + (float)n * 0.1 + 0.05, 0.002, 0.035, 0, 0, hud_null, 0);
				}
				draw_graph_value(esContext, 0.95, 0.45 + (float)n * 0.1, 1.35, 0.45 + (float)n * 0.1 + 0.08, 0.001, graph1_data[n], graph1_size, graph1_pointer, 255 - n * 25, n * 25, n * 125, 255);
			}
			draw_image_f3(esContext, 0.8, 0.85, 1.0, 0.96, 0.002, ModelData.image);
		}
	}

	//printf("hud#10\n");

	// Draw Jeti-Telemetrie
	if (jeti_ok == 1) {
		float jetibox_x = -1.15;
		float jetibox_y = 0.65;
		draw_box_f3c2(esContext, jetibox_x - 0.01, jetibox_y - 0.025, 0.001, jetibox_x + 0.52, jetibox_y + 0.12, 0.001, 255, 255, 255, 127, 255, 255, 255, 64);
		draw_text_f3(esContext, jetibox_x, jetibox_y, 0.003, 0.05, 0.05, FONT_WHITE, jeti_line1);
		draw_text_f3(esContext, jetibox_x, jetibox_y + 0.05, 0.003, 0.05, 0.05, FONT_WHITE, jeti_line2);
		draw_button(esContext, "jeti_left", VIEW_MODE_HUD, "<", FONT_GREEN_BG, jetibox_x + 0.07	, jetibox_y + 0.15, 0.002, 0.05, 0, 0, jeti_left, 0);
		draw_button(esContext, "jeti_up", VIEW_MODE_HUD, "^", FONT_GREEN_BG, jetibox_x + 0.17, jetibox_y + 0.15, 0.002, 0.05, 0, 0, jeti_up, 0);
		draw_button(esContext, "jeti_down", VIEW_MODE_HUD, "v", FONT_GREEN_BG, jetibox_x + 0.27, jetibox_y + 0.15, 0.002, 0.05, 0, 0, jeti_down, 0);
		draw_button(esContext, "jeti_right", VIEW_MODE_HUD, ">", FONT_GREEN_BG, jetibox_x + 0.37, jetibox_y + 0.15, 0.002, 0.05, 0, 0, jeti_right, 0);
	}

	if (hud_view == 1) {
		draw_button(esContext, "view_hud", VIEW_MODE_HUD, "VIEW", FONT_GREEN, -1.35, 0.9, 0.002, 0.06, 0, 0, view_hud, 0);
	} else {
		draw_button(esContext, "view_hud", VIEW_MODE_HUD, "VIEW", FONT_WHITE, -1.35, 0.9, 0.002, 0.06, 0, 0, view_hud, 0);
	}
#ifdef SDLGL
	if (hud_view_map == 1) {
		draw_button(esContext, "view_hud_mark", VIEW_MODE_HUD, "MARK", FONT_GREEN, -1.35, 0.8, 0.002, 0.06, 0, 0, view_hud_mark, 0);
		draw_button(esContext, "view_hud_map", VIEW_MODE_HUD, "MAP", FONT_GREEN, -1.15, 0.9, 0.002, 0.06, 0, 0, view_hud_map, 0);
//		if (hud_view_tunnel == 1) {
//			draw_button(esContext, "view_map_tunnel", VIEW_MODE_HUD, "TUNNEL", FONT_GREEN, -1.0, 0.9, 0.002, 0.06, 0, 0, view_hud_tunnel, 0);
//		} else {
//			draw_button(esContext, "view_map_tunnel", VIEW_MODE_HUD, "TUNNEL", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 0, 0, view_hud_tunnel, 0);
//		}
		hud_view_tunnel = 0;
	} else {
		draw_button(esContext, "view_hud_map", VIEW_MODE_HUD, "MAP", FONT_WHITE, -1.15, 0.9, 0.002, 0.06, 0, 0, view_hud_map, 0);
		draw_button(esContext, "view_map_bw", VIEW_MODE_HUD, "BW", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 0, 0, view_hud_bw, 0);
	}
	if (hud_view_video == 1) {
		draw_button(esContext, "view_hud_video", VIEW_MODE_HUD, "VID", FONT_GREEN, -1.15, 0.8, 0.002, 0.06, 0, 0, view_hud_video, 0);
	} else {
		draw_button(esContext, "view_hud_video", VIEW_MODE_HUD, "VID", FONT_WHITE, -1.15, 0.8, 0.002, 0.06, 0, 0, view_hud_video, 0);
	}
#else
	draw_button(esContext, "view_map_bw", VIEW_MODE_HUD, "BW", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 0, 0, view_hud_bw, 0);
#endif

	//printf("hud#11\n");

#ifdef SDLGL
	glPopMatrix();
#endif

	glEnable( GL_DEPTH_TEST );

	//printf("hud#12end\n");

}



