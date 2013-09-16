
#include <userdata.h>
#include <screen_wpedit.h>
#include <screen_map.h>
#include <main.h>
#include <my_mavlink.h>

uint16_t wpedit_pos = 0;
uint16_t wpedit_sel = 0;
uint8_t wpedit_last_mode = VIEW_MODE_MAP;

uint8_t read_wp (char *name, float x, float y, int8_t button, float data) {
	show_wp(name, x, y, button, 1);
	read_waypoints();
	return 0;
}

uint8_t write_wp (char *name, float x, float y, int8_t button, float data) {
	send_waypoints();
	return 0;
}

uint8_t wpedit_waypoint_edit (char *name, float x, float y, int8_t button, float data) {
	wpedit_last_mode = (uint8_t)data;
	setup.view_mode = VIEW_MODE_WPEDIT;
	view_mode_next = VIEW_MODE_WPEDIT;
	return 0;
}

uint8_t wpedit_back (char *name, float x, float y, int8_t button, float data) {
	setup.view_mode = wpedit_last_mode;
	view_mode_next = wpedit_last_mode;
	return 0;
}

uint8_t wpedit_waypoint_lat_set (char *name, float x, float y, int8_t button, float data) {
	WayPoints[waypoint_active].p_lat += data;
	return 0;
}

uint8_t wpedit_waypoint_lon_set (char *name, float x, float y, int8_t button, float data) {
	WayPoints[waypoint_active].p_long += data;
	return 0;
}

uint8_t wpedit_waypoint_alt_set (char *name, float x, float y, int8_t button, float data) {
	WayPoints[waypoint_active].p_alt += data;
	return 0;
}

uint8_t wpedit_waypoint_yaw_set (char *name, float x, float y, int8_t button, float data) {
	WayPoints[waypoint_active].yaw += data;
	return 0;
}

uint8_t wpedit_waypoint_wait_set (char *name, float x, float y, int8_t button, float data) {
	WayPoints[waypoint_active].wait += data;
	return 0;
}

uint8_t wpedit_waypoint_orbit_set (char *name, float x, float y, int8_t button, float data) {
	WayPoints[waypoint_active].orbit += data;
	return 0;
}

uint8_t wpedit_waypoint_radius_set (char *name, float x, float y, int8_t button, float data) {
	WayPoints[waypoint_active].radius += data;
	return 0;
}

uint8_t wpedit_waypoint_type_select (char *name, float x, float y, int8_t button, float data) {
	if (strcmp(WayPoints[waypoint_active].command, "WAYPOINT") == 0) {
		strcpy(WayPoints[waypoint_active].command, "RTL");
	} else if (strcmp(WayPoints[waypoint_active].command, "RTL") == 0) {
		strcpy(WayPoints[waypoint_active].command, "TAKEOFF");
	} else if (strcmp(WayPoints[waypoint_active].command, "TAKEOFF") == 0) {
		strcpy(WayPoints[waypoint_active].command, "LAND");
	} else {
		strcpy(WayPoints[waypoint_active].command, "WAYPOINT");
	}
	return 0;
}

void screen_wpedit (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	char tmp_str[100];

#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	draw_title(esContext, "Waypoint-Editor");

	if (waypoint_active >= 0) {

		sprintf(tmp_str, "EDIT: %s", WayPoints[waypoint_active].name);
		draw_text_f3(esContext, -1.2, -0.9 + (0 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
		draw_button(esContext, tmp_str, VIEW_MODE_WPEDIT, "[BACK]", FONT_GREEN, 1.2, -0.9 + (0 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_back, 0.0);

		sprintf(tmp_str, "LAT   : %f", WayPoints[waypoint_active].p_lat);
		draw_text_f3(esContext, -1.1, -0.9 + (1 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
//		draw_button(esContext, "wpedit_lat-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (1 * 0.2), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_lat_set, -0.01);
//		draw_button(esContext, "wpedit_lat+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (1 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_lat_set, 0.01);

		sprintf(tmp_str, "LON   : %f", WayPoints[waypoint_active].p_long);
		draw_text_f3(esContext, -1.1, -0.9 + (2 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
//		draw_button(esContext, "wpedit_lon-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (2 * 0.2), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_lon_set, -0.01);
//		draw_button(esContext, "wpedit_lon+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (2 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_lon_set, 0.01);

		sprintf(tmp_str, "Alt   : %0.1fm", WayPoints[waypoint_active].p_alt);
		draw_text_f3(esContext, -1.1, -0.9 + (3 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
		draw_button(esContext, "wpedit_alt-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (3 * 0.2), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_alt_set, -1.0);
		draw_button(esContext, "wpedit_alt+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (3 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_alt_set, 1.0);

		sprintf(tmp_str, "Yaw   : %f", WayPoints[waypoint_active].yaw);
		draw_text_f3(esContext, -1.1, -0.9 + (4 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
		draw_button(esContext, "wpedit_yaw-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (4 * 0.2), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_yaw_set, -1.0);
		draw_button(esContext, "wpedit_yaw+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (4 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_yaw_set, 1.0);

		sprintf(tmp_str, "CMD   : %s", WayPoints[waypoint_active].command);
		draw_text_f3(esContext, -1.1, -0.9 + (5 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
		draw_button(esContext, "wpedit_cmd", VIEW_MODE_WPEDIT, "[SELECT]", FONT_GREEN, 1.2, -0.9 + (5 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_type_select, 0.0);

		if (strcmp(WayPoints[waypoint_active].command, "WAYPOINT") == 0) {
			sprintf(tmp_str, "WAIT  : %0.0fms", WayPoints[waypoint_active].wait);
			draw_text_f3(esContext, -1.1, -0.9 + (6 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_button(esContext, "wpedit_wait-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (6 * 0.2), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_wait_set, -100.0);
			draw_button(esContext, "wpedit_wait+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (6 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_wait_set, 100.0);

			sprintf(tmp_str, "RADIUS: %0.1fm", WayPoints[waypoint_active].radius);
			draw_text_f3(esContext, -1.1, -0.9 + (7 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_button(esContext, "wpedit_radius-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (7 * 0.2), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_radius_set, -1.0);
			draw_button(esContext, "wpedit_radius+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (7 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_radius_set, 1.0);

			sprintf(tmp_str, "ORBIT : %0.1fm", WayPoints[waypoint_active].orbit);
			draw_text_f3(esContext, -1.1, -0.9 + (8 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_button(esContext, "wpedit_orbit-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (8 * 0.2), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_orbit_set, -1.0);
			draw_button(esContext, "wpedit_orbit+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (8 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_orbit_set, 1.0);
		} else if (strcmp(WayPoints[waypoint_active].command, "TAKEOFF") == 0) {
			sprintf(tmp_str, "PITCH : %0.0f", WayPoints[waypoint_active].wait);
			draw_text_f3(esContext, -1.1, -0.9 + (6 * 0.2), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_button(esContext, "wpedit_pitch-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (6 * 0.2), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_wait_set, -1.0);
			draw_button(esContext, "wpedit_pitch+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (6 * 0.2), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_wait_set, 1.0);
		}
	}

	draw_button(esContext, "map_read_wp", VIEW_MODE_WPEDIT, "READ_WP", FONT_GREEN_BG, -0.2, 0.9, 0.002, 0.06, 1, 0, read_wp, 0.0);
	draw_button(esContext, "map_write_wp", VIEW_MODE_WPEDIT, "WRITE_WP", FONT_GREEN_BG, 0.2, 0.9, 0.002, 0.06, 1, 0, write_wp, 0.0);
}

