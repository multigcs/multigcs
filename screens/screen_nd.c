
#include <stdint.h>
#include <math.h>
#include <userdata.h>
#include <model.h>
#include <main.h>
#include <screen_nd.h>
#include <my_mavlink.h>
#include <screen_wpedit.h>
#include <screen_map.h>

uint8_t nd_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

void screen_nd (ESContext *esContext) {
	ESMatrix modelview;
	char tmp_str[100];
	char tmp_str2[100];
	int16_t n = 0;

	draw_title(esContext, "Navigation");

	// Yaw
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	UserData *userData = esContext->userData;
	esMatrixLoadIdentity(&modelview);
#endif
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_line_f(esContext, 0.0, -0.8, 0.0, 0.0, 255, 255, 255, 127);
	draw_image_f(esContext, 0.0 - 0.05, 0.0 - 0.05, 0.0 + 0.05, 0.0 + 0.05, TEXTURE_QUAD);
	draw_line_f(esContext, 0.0, 0.0 - 0.1, 0.0, 0.0, 0, 255, 0, 255);
	draw_line_f(esContext, 0.0, 0.0 - 0.1, 0.0 - 0.02, 0.0 - 0.1 + 0.02, 0, 255, 0, 255);
	draw_line_f(esContext, 0.0, 0.0 - 0.1, 0.0 + 0.02, 0.0 - 0.1 + 0.02, 0, 255, 0, 255);
#ifdef SDLGL
	glPopMatrix();
#endif

	sprintf(tmp_str2, "%0.1f", ModelData.yaw);
	draw_text_f(esContext, 0.0 - strlen(tmp_str2) * 0.07 * 0.6 / 2.0 - 0.02, -0.88, 0.07, 0.07, FONT_WHITE, tmp_str2);

	for (n = 0; n < 360; n += 10) {
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, 0.0, -2.0);
		esRotate(&modelview, ((float)n - ModelData.yaw), 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, 0.0, 2.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		draw_line_f(esContext, 0.0, 0.7, 0.0, 0.75, 255, 255, 255, 255);
		sprintf(tmp_str, "%i", n);
		draw_text_f(esContext, 0.0 - strlen(tmp_str) * 0.05 * 0.6 / 2.0 - 0.01, -0.7, 0.05, 0.05, FONT_WHITE, tmp_str);
#ifdef SDLGL
		glPopMatrix();
#endif

#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, 0.0, -2.0);
		esRotate(&modelview, ((float)n - ModelData.yaw) + 5.0, 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, 0.0, 2.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		draw_line_f(esContext, 0.0, 0.7, 0.0, 0.73, 255, 255, 255, 255);
#ifdef SDLGL
		glPopMatrix();
#endif
	}


	float home_nx = 0.0;
	float home_ny = 0.0;

	float nx1 = 0.0;
	float ny1 = 0.0;
	float home_dist = 0.0;
	float dist1 = 0.0;
	float dist2 = 0.0;
	float max_dist = 0.0;
	static float nd_zoom = 1.0;
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esRotate(&modelview, -ModelData.yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	show_dir_f(esContext, 0.0, 0.0, nd_zoom, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), WayPoints[0].p_lat, WayPoints[0].p_long, WayPoints[0].p_alt, 255, 255, 255, 32, &home_nx, &home_ny, &home_dist);

	esTranslate(&modelview, home_nx, -home_ny, 0.0);
	esRotate(&modelview, ModelData.yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	draw_line_f(esContext, -0.03, -0.05, 0.0, -0.1, 255, 255, 255, 32);
	draw_line_f(esContext, 0.03, -0.05, 0.0, -0.1, 255, 255, 255, 32);
	draw_line_f(esContext, -0.03, -0.05, 0.03, -0.05, 255, 255, 255, 32);
	draw_line_f(esContext, -0.03, 0.0, 0.03, 0.0, 255, 255, 255, 32);
	draw_line_f(esContext, -0.03, -0.05, -0.03, 0.0, 255, 255, 255, 32);
	draw_line_f(esContext, 0.03, -0.05, 0.03, 0.0, 255, 255, 255, 32);

	draw_circleFilled_f(esContext, 0.0, 0.0, 0.01, 255, 255, 255, 128);
	strcpy(tmp_str, "HOME");
	draw_text_f(esContext, 0.0, 0.0, 0.05, 0.05, FONT_TRANS, tmp_str);
#ifdef SDLGL
	glPopMatrix();
#endif


#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	float last_lat = ModelData.p_lat;
	float last_lon = ModelData.p_long;
	float last_alt = (ModelData.p_alt - ModelData.alt_offset);
	for (n = waypoint_active; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[n].p_lat != 0.0) {
			strcpy(tmp_str, WayPoints[n].name);

			esRotate(&modelview, -ModelData.yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
			esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
			esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
			if (n == waypoint_active) {
				show_dir_f(esContext, 0.0, 0.0, nd_zoom, last_lat, last_lon, last_alt, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, 0xff, 0x33, 0xfc, 255, &nx1, &ny1, &dist1);
			} else {
				show_dir_f(esContext, 0.0, 0.0, nd_zoom, last_lat, last_lon, last_alt, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, 0, 255, 0, 127, &nx1, &ny1, &dist2);
			}

			esTranslate(&modelview, nx1, -ny1, 0.0);
			esRotate(&modelview, ModelData.yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
			esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
			esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

			if (n == waypoint_active) {
				draw_circleFilled_f(esContext, 0.0, 0.0, 0.01, 0xff, 0x33, 0xfc, 255);
				draw_text_f(esContext, 0.0, 0.0, 0.05, 0.05, FONT_PINK, tmp_str);
			} else {
				draw_circleFilled_f(esContext, 0.0, 0.0, 0.01, 0, 255, 0, 127);
				draw_text_f(esContext, 0.0, 0.0, 0.05, 0.05, FONT_GREEN, tmp_str);
			}

			last_lat = WayPoints[n].p_lat;
			last_lon = WayPoints[n].p_long;
			last_alt = WayPoints[n].p_alt;

			if (max_dist < dist1 * 1000.0) {
				max_dist = dist1 * 1000.0;
			}
			if (max_dist < dist2 * 1000.0) {
				max_dist = dist2 * 1000.0;
			}
		}
	}
	nd_zoom = max_dist / 500.0;
#ifdef SDLGL
	glPopMatrix();
#endif



#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	last_lat = ModelData.p_lat;
	last_lon = ModelData.p_long;
	last_alt = (ModelData.p_alt - ModelData.alt_offset);
	for (n = waypoint_active - 1; n > 1; n--) {
		if (WayPoints[n].p_lat != 0.0) {
			strcpy(tmp_str, WayPoints[n].name);

			esRotate(&modelview, -ModelData.yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
			esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
			esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
			show_dir_f(esContext, 0.0, 0.0, nd_zoom, last_lat, last_lon, last_alt, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, 127, 127, 127, 127, &nx1, &ny1, &dist2);

			esTranslate(&modelview, nx1, -ny1, 0.0);
			esRotate(&modelview, ModelData.yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
			esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
			esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
			draw_circleFilled_f(esContext, 0.0, 0.0, 0.01, 127, 127, 127, 127);
			draw_text_f(esContext, 0.0, 0.0, 0.05, 0.05, FONT_TRANS, tmp_str);

			last_lat = WayPoints[n].p_lat;
			last_lon = WayPoints[n].p_long;
			last_alt = WayPoints[n].p_alt;

			if (max_dist < dist1 * 1000.0) {
				max_dist = dist1 * 1000.0;
			}
			if (max_dist < dist2 * 1000.0) {
				max_dist = dist2 * 1000.0;
			}
		}
	}
	nd_zoom = max_dist / 500.0;
#ifdef SDLGL
	glPopMatrix();
#endif



	// Alt Frame
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, 0.0, 0.01);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	int d_start = 100;
	int d_steps = 100;
	if (nd_zoom < 0.5) {
		d_start = 20;
		d_steps = 10;
	}

	if (max_dist < 1000.0 && max_dist >= 0.0) {
		for (n = d_start; n < max_dist; n += d_steps) {
			sprintf(tmp_str, "%im", n);
			draw_text_f(esContext, 0.02, -(float)n / 1000.0 / nd_zoom - 0.015, 0.04, 0.04, FONT_TRANS, tmp_str);
			draw_line_f(esContext, 0.0 - 0.02, -(float)n / 1000.0 / nd_zoom, 0.0 + 0.02, -(float)n / 1000.0 / nd_zoom, 255, 255, 255, 127);
		}
	}

	draw_box_f(esContext, -0.8, 0.2, 0.8, 0.8, 0, 0, 0, 200);
	draw_line_f(esContext, -0.8, 0.2, 0.8, 0.2, 255, 255, 255, 255);
	draw_line_f(esContext, -0.8, 0.8, 0.8, 0.8, 255, 255, 255, 255);
	draw_line_f(esContext, -0.8, 0.2, -0.8, 0.8, 255, 255, 255, 255);
	draw_line_f(esContext, 0.8, 0.2, 0.8, 0.8, 255, 255, 255, 255);

	float nf = 0.0;
	for (nf = 0.3; nf < 0.8; nf += 0.05) {
		draw_line_f(esContext, 0.4, nf, 0.4, nf + 0.025, 0xff, 0x33, 0xfc, 255);
	}

	/* Distance - Ground-Level */
	float distance1 = acos( 
		cos(toRad(ModelData.p_lat))
		* cos(toRad(WayPoints[waypoint_active].p_lat))
		* cos(toRad(ModelData.p_long) - toRad(WayPoints[waypoint_active].p_long))
		+ sin(toRad(ModelData.p_lat)) 
		* sin(toRad(WayPoints[waypoint_active].p_lat))
	) * 6378.137 * 1000.0;
	float alt1 = WayPoints[waypoint_active].p_alt - (ModelData.p_alt - ModelData.alt_offset);
	/* Distance - Sichtverbindung */
	float distance2 = sqrt(((distance1) * (distance1)) + (alt1 * alt1));
	/* Steigung */
	float winkel_up = (asin(alt1 / distance2)) * 180 / PI;


	float alt_zoom = (WayPoints[waypoint_active].p_alt - (ModelData.p_alt - ModelData.alt_offset)) / 0.2;
	if (alt_zoom < 0.0) {
		alt_zoom *= -1;
	}

	float alt_diff = (WayPoints[waypoint_active].p_alt - (ModelData.p_alt - ModelData.alt_offset)) / alt_zoom;

	strcpy(tmp_str2, WayPoints[waypoint_active].name);
	draw_text_f(esContext, 0.4 - strlen(tmp_str2) * 0.05 * 0.6 / 2.0 - 0.02, 0.22, 0.05, 0.05, FONT_PINK, tmp_str2);

	draw_line_f(esContext, -0.4, 0.5, 0.4, 0.5 - alt_diff, 0xff, 0x33, 0xfc, 255);

	sprintf(tmp_str2, "%0.1fm", (ModelData.p_alt - ModelData.alt_offset));
	draw_text_f(esContext, -0.4 - strlen(tmp_str2) * 0.05 * 0.6 - 0.02, 0.5 - 0.025, 0.05, 0.05, FONT_PINK, tmp_str2);

	sprintf(tmp_str2, "%0.1fm", WayPoints[waypoint_active].p_alt);
	draw_text_f(esContext, 0.4, 0.5 - alt_diff - 0.025, 0.05, 0.05, FONT_PINK, tmp_str2);

	sprintf(tmp_str2, "%0.1fGrad", winkel_up);
	draw_text_f(esContext, 0.0 - strlen(tmp_str2) * 0.05 * 0.6 / 2.0 - 0.02, 0.6, 0.05, 0.05, FONT_PINK, tmp_str2);

	sprintf(tmp_str2, "%0.1fm", dist1 * 1000.0);
	draw_text_f(esContext, 0.0 - strlen(tmp_str2) * 0.05 * 0.6 / 2.0 - 0.02, 0.75, 0.05, 0.05, FONT_PINK, tmp_str2);

	draw_line_f(esContext, -0.3, 0.77, -0.15, 0.77, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, -0.3, 0.77, -0.3 + 0.02, 0.77 + 0.02, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, -0.3, 0.77, -0.3 + 0.02, 0.77 - 0.02, 0xff, 0x33, 0xfc, 255);

	draw_line_f(esContext, 0.3, 0.77, 0.15, 0.77, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, 0.3, 0.77, 0.3 - 0.02, 0.77 + 0.02, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, 0.3, 0.77, 0.3 - 0.02, 0.77 - 0.02, 0xff, 0x33, 0xfc, 255);

	float ax1 = -0.8;
	draw_box_f(esContext, ax1, 0.5 - 6 * 0.05, ax1 + 0.17, 0.5 + 6 * 0.05, 255, 255, 255, 128);
	for (n = (ModelData.p_alt - ModelData.alt_offset) - 4; n <= (ModelData.p_alt - ModelData.alt_offset) + 5; n += 1) {
		float tsize = 0.05;
		sprintf(tmp_str, "%i", n);
		draw_text_f(esContext, ax1 + 0.02, 0.5 - 0.025 - ((float)n - (ModelData.p_alt - ModelData.alt_offset)) * 0.05, tsize, tsize, FONT_WHITE, tmp_str);
		draw_line_f(esContext, ax1, 0.5 - ((float)n - (ModelData.p_alt - ModelData.alt_offset)) * 0.05, ax1 + 0.02, 0.5 - ((float)n - (ModelData.p_alt - ModelData.alt_offset)) * 0.05, 255, 255, 255, 255);
	}

	if (home_dist * 1000.0 > 1000) {
		sprintf(tmp_str2, "Home-Distance: %0.2fkm", home_dist * 1000.0 / 1000.0);
	} else {
		sprintf(tmp_str2, "Home-Distance: %0.1fm", home_dist * 1000.0);
	}
	draw_text_f(esContext, -1.25, 0.9, 0.05, 0.05, FONT_GREEN, tmp_str2);

#ifdef SDLGL
	glPopMatrix();
#endif


	draw_button(esContext, "map_read_wp", VIEW_MODE_ND, "READ_WP", FONT_GREEN_BG, -0.2, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, read_wp, 0.0);
	draw_button(esContext, "map_write_wp", VIEW_MODE_ND, "WRITE_WP", FONT_GREEN_BG, 0.2, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, write_wp, 0.0);
}

