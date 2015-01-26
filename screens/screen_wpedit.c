
#include <all.h>


uint16_t wpedit_pos = 0;
uint16_t wpedit_sel = 0;
uint8_t wpedit_last_mode = VIEW_MODE_MAP;

uint8_t read_wp (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	show_wp(name, x, y, button, 1, 0);
	mavlink_read_waypoints();
	return 0;
}

uint8_t write_wp (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_send_waypoints();
	return 0;
}

uint8_t wpedit_waypoint_edit (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	wpedit_last_mode = (uint8_t)data;
	setup.view_mode = VIEW_MODE_WPEDIT;
	view_mode_next = VIEW_MODE_WPEDIT;
	return 0;
}

uint8_t wpedit_back (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	setup.view_mode = wpedit_last_mode;
	view_mode_next = wpedit_last_mode;
	return 0;
}

uint8_t wpedit_waypoint_lat_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[waypoint_active].p_lat += data;
	return 0;
}

uint8_t wpedit_waypoint_lon_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[waypoint_active].p_long += data;
	return 0;
}

uint8_t wpedit_waypoint_alt_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		WayPoints[waypoint_active].p_alt += 1;
	} else if (button == 5) {
		WayPoints[waypoint_active].p_alt -= 1;
	} else if (data == 0.0) {
		if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL) {
			WayPoints[waypoint_active].p_alt = get_altitude(WayPoints[waypoint_active].p_lat, WayPoints[waypoint_active].p_long) + 2.0;
		} else {
			WayPoints[waypoint_active].p_alt = 2.0;
		}
	} else {
		WayPoints[waypoint_active].p_alt += data;
	}
	return 0;
}

uint8_t wpedit_waypoint_param4_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[waypoint_active].param4 += data;
	return 0;
}

uint8_t wpedit_waypoint_param2_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[waypoint_active].param2 += data;
	return 0;
}

uint8_t wpedit_waypoint_param3_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[waypoint_active].param3 += data;
	return 0;
}

uint8_t wpedit_waypoint_param1_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[waypoint_active].param1 += data;
	return 0;
}

uint8_t wpedit_waypoint_frametype_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL) {
		WayPoints[waypoint_active].frametype = MAV_FRAME_GLOBAL_RELATIVE_ALT;
	} else {
		WayPoints[waypoint_active].frametype = MAV_FRAME_GLOBAL;
	}
	return 0;
}

uint8_t wpedit_waypoint_type_select (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (strcmp(WayPoints[waypoint_active].command, "WAYPOINT") == 0) {
		strcpy(WayPoints[waypoint_active].command, "RTL");
	} else if (strcmp(WayPoints[waypoint_active].command, "RTL") == 0) {
		strcpy(WayPoints[waypoint_active].command, "TAKEOFF");
	} else if (strcmp(WayPoints[waypoint_active].command, "TAKEOFF") == 0) {
		strcpy(WayPoints[waypoint_active].command, "LAND");
	} else if (strcmp(WayPoints[waypoint_active].command, "LAND") == 0) {
		strcpy(WayPoints[waypoint_active].command, "SET_ROI");
	} else if (strcmp(WayPoints[waypoint_active].command, "SET_ROI") == 0) {
		strcpy(WayPoints[waypoint_active].command, "SHUTTER");
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
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	char tmp_str[100];
	uint8_t n_y = 0;
	float step_y = 0.16;
	uint16_t n = 0;
	uint16_t num_waypoints = 0;

	for (n = 1; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[n].p_lat == 0.0) {
			break;
		}
	}
	num_waypoints = n - 1;
	sprintf(tmp_str, "Waypoint-Editor (total:%i)", num_waypoints);
	draw_title(esContext, tmp_str);


	if (waypoint_active >= 0) {

		sprintf(tmp_str, "EDIT: %s", WayPoints[waypoint_active].name);
		draw_text_f3(esContext, -1.2, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
		draw_text_button(esContext, tmp_str, VIEW_MODE_WPEDIT, "[BACK]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_back, 0.0);
		n_y++;

		sprintf(tmp_str, "CMD   : %s", WayPoints[waypoint_active].command);
		draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
		draw_text_button(esContext, "wpedit_cmd", VIEW_MODE_WPEDIT, "[SELECT]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_type_select, 0.0);
		n_y++;

		if (strcmp(WayPoints[waypoint_active].command, "WAYPOINT") == 0) {
			sprintf(tmp_str, "LAT   : %f", WayPoints[waypoint_active].p_lat);
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			n_y++;

			sprintf(tmp_str, "LON   : %f", WayPoints[waypoint_active].p_long);
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			n_y++;

			if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL) {
				sprintf(tmp_str, "Alt   : %0.1fm abs", WayPoints[waypoint_active].p_alt);
			} else if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT || WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT_INT) {
				sprintf(tmp_str, "Alt   : %0.1fm rel", WayPoints[waypoint_active].p_alt);
			} else {
				sprintf(tmp_str, "Alt   : %0.1fm ???", WayPoints[waypoint_active].p_alt);
			}
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_text_button(esContext, "wpedit_alt_", VIEW_MODE_WPEDIT, "[G]", FONT_GREEN, 0.6, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_alt_set, 0.0);
			draw_text_button(esContext, "wpedit_alt-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_alt_set, -1.0);
			draw_text_button(esContext, "wpedit_alt+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_alt_set, 1.0);
			n_y++;

			sprintf(tmp_str, "RADIUS: %0.1fm", WayPoints[waypoint_active].param1);
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_text_button(esContext, "wpedit_param1-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param1_set, -1.0);
			draw_text_button(esContext, "wpedit_param1+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param1_set, 1.0);
			n_y++;

			sprintf(tmp_str, "WAIT  : %0.0fms", WayPoints[waypoint_active].param2);
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_text_button(esContext, "wpedit_param2-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param2_set, -100.0);
			draw_text_button(esContext, "wpedit_param2+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param2_set, 100.0);
			n_y++;

			sprintf(tmp_str, "ORBIT : %0.1fm", WayPoints[waypoint_active].param3);
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_text_button(esContext, "wpedit_param3-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param3_set, -1.0);
			draw_text_button(esContext, "wpedit_param3+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param3_set, 1.0);
			n_y++;

			sprintf(tmp_str, "Yaw   : %f", WayPoints[waypoint_active].param4);
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_text_button(esContext, "wpedit_param4-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param4_set, -1.0);
			draw_text_button(esContext, "wpedit_param4+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param4_set, 1.0);
			n_y++;

			if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL) {
				sprintf(tmp_str, "FTYPE : GLOBAL");
			} else if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT || WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT_INT) {
				sprintf(tmp_str, "FTYPE : GLOBAL_RELATIVE_ALT");
			} else {
				sprintf(tmp_str, "FTYPE : ???");
			}
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_text_button(esContext, "wpedit_frametype-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_frametype_set, -1.0);
			draw_text_button(esContext, "wpedit_frametype+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_frametype_set, 1.0);
			n_y++;
		} else if (strcmp(WayPoints[waypoint_active].command, "SET_ROI") == 0) {
			sprintf(tmp_str, "LAT   : %f", WayPoints[waypoint_active].p_lat);
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			n_y++;

			sprintf(tmp_str, "LON   : %f", WayPoints[waypoint_active].p_long);
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			n_y++;

			if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL) {
				sprintf(tmp_str, "Alt   : %0.1fm abs", WayPoints[waypoint_active].p_alt);
			} else if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT || WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT_INT) {
				sprintf(tmp_str, "Alt   : %0.1fm rel", WayPoints[waypoint_active].p_alt);
			} else {
				sprintf(tmp_str, "Alt   : %0.1fm ???", WayPoints[waypoint_active].p_alt);
			}
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_text_button(esContext, "wpedit_alt_", VIEW_MODE_WPEDIT, "[G]", FONT_GREEN, 0.6, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_alt_set, 0.0);
			draw_text_button(esContext, "wpedit_alt-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_alt_set, -1.0);
			draw_text_button(esContext, "wpedit_alt+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_alt_set, 1.0);
			n_y++;

			if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL) {
				sprintf(tmp_str, "FTYPE : GLOBAL");
			} else if (WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT || WayPoints[waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT_INT) {
				sprintf(tmp_str, "FTYPE : GLOBAL_RELATIVE_ALT");
			} else {
				sprintf(tmp_str, "FTYPE : ???");
			}
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_text_button(esContext, "wpedit_frametype-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_frametype_set, -1.0);
			draw_text_button(esContext, "wpedit_frametype+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_frametype_set, 1.0);
			n_y++;
		} else if (strcmp(WayPoints[waypoint_active].command, "TAKEOFF") == 0) {
			sprintf(tmp_str, "PITCH : %0.0f", WayPoints[waypoint_active].param2);
			draw_text_f3(esContext, -1.1, -0.9 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
			draw_text_button(esContext, "wpedit_pitch-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param2_set, -1.0);
			draw_text_button(esContext, "wpedit_pitch+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.9 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param2_set, 1.0);
			n_y++;
		}
	}

	draw_text_button(esContext, "map_read_wp", VIEW_MODE_WPEDIT, "READ_WP", FONT_GREEN_BG, -0.2, 0.9, 0.002, 0.06, 1, 0, read_wp, 0.0);
	draw_text_button(esContext, "map_write_wp", VIEW_MODE_WPEDIT, "WRITE_WP", FONT_GREEN_BG, 0.2, 0.9, 0.002, 0.06, 1, 0, write_wp, 0.0);
}

