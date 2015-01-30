
#include <all.h>


uint16_t wpedit_pos = 0;
uint16_t wpedit_sel = 0;
uint8_t wpedit_last_mode = VIEW_MODE_MAP;

uint8_t read_wp (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	show_wp(name, x, y, button, 1, 0);
	mavlink_read_waypoints(ModelActive);
	return 0;
}

uint8_t write_wp (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_send_waypoints(ModelActive);
	return 0;
}

uint8_t wpedit_waypoint_number_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (strcmp(name, "param1") == 0) {
		if (button == 5) {
			WayPoints[ModelActive][waypoint_active].param1 -= 1.0;
		} else if (button == 4) {
			WayPoints[ModelActive][waypoint_active].param1 += 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &WayPoints[ModelActive][waypoint_active].param1, -999999.0, 999999.0);
		}
	} else if (strcmp(name, "param2") == 0) {
		if (button == 5) {
			WayPoints[ModelActive][waypoint_active].param2 -= 1.0;
		} else if (button == 4) {
			WayPoints[ModelActive][waypoint_active].param2 += 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &WayPoints[ModelActive][waypoint_active].param2, -999999.0, 999999.0);
		}
	} else if (strcmp(name, "param3") == 0) {
		if (button == 5) {
			WayPoints[ModelActive][waypoint_active].param3 -= 1.0;
		} else if (button == 4) {
			WayPoints[ModelActive][waypoint_active].param3 += 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &WayPoints[ModelActive][waypoint_active].param3, -999999.0, 999999.0);
		}
	} else if (strcmp(name, "param4") == 0) {
		if (button == 5) {
			WayPoints[ModelActive][waypoint_active].param4 -= 1.0;
		} else if (button == 4) {
			WayPoints[ModelActive][waypoint_active].param4 += 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &WayPoints[ModelActive][waypoint_active].param4, -999999.0, 999999.0);
		}
	} else if (strcmp(name, "lat") == 0) {
		if (button == 5) {
			WayPoints[ModelActive][waypoint_active].p_lat -= 1.0;
		} else if (button == 4) {
			WayPoints[ModelActive][waypoint_active].p_lat += 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &WayPoints[ModelActive][waypoint_active].p_lat, -999999.0, 999999.0);
		}
	} else if (strcmp(name, "long") == 0) {
		if (button == 5) {
			WayPoints[ModelActive][waypoint_active].p_long -= 1.0;
		} else if (button == 4) {
			WayPoints[ModelActive][waypoint_active].p_long += 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &WayPoints[ModelActive][waypoint_active].p_long, -999999.0, 999999.0);
		}
	} else if (strcmp(name, "alt") == 0) {
		if (button == 5) {
			WayPoints[ModelActive][waypoint_active].p_alt -= 1.0;
		} else if (button == 4) {
			WayPoints[ModelActive][waypoint_active].p_alt += 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &WayPoints[ModelActive][waypoint_active].p_alt, -999999.0, 999999.0);
		}
	} else if (strcmp(name, "frametype") == 0) {
		if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL) {
			WayPoints[ModelActive][waypoint_active].frametype = MAV_FRAME_GLOBAL_RELATIVE_ALT;
		} else {
			WayPoints[ModelActive][waypoint_active].frametype = MAV_FRAME_GLOBAL;
		}
	}
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
	WayPoints[ModelActive][waypoint_active].p_lat += data;
	return 0;
}

uint8_t wpedit_waypoint_lon_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[ModelActive][waypoint_active].p_long += data;
	return 0;
}

uint8_t wpedit_waypoint_alt_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		WayPoints[ModelActive][waypoint_active].p_alt += 1;
	} else if (button == 5) {
		WayPoints[ModelActive][waypoint_active].p_alt -= 1;
	} else if (data == 0.0) {
		if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL) {
			WayPoints[ModelActive][waypoint_active].p_alt = get_altitude(WayPoints[ModelActive][waypoint_active].p_lat, WayPoints[ModelActive][waypoint_active].p_long) + 2.0;
		} else {
			WayPoints[ModelActive][waypoint_active].p_alt = 2.0;
		}
	} else {
		WayPoints[ModelActive][waypoint_active].p_alt += data;
	}
	return 0;
}

uint8_t wpedit_waypoint_param4_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[ModelActive][waypoint_active].param4 += data;
	return 0;
}

uint8_t wpedit_waypoint_param2_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[ModelActive][waypoint_active].param2 += data;
	return 0;
}

uint8_t wpedit_waypoint_param3_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[ModelActive][waypoint_active].param3 += data;
	return 0;
}

uint8_t wpedit_waypoint_param1_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	WayPoints[ModelActive][waypoint_active].param1 += data;
	return 0;
}

uint8_t wpedit_waypoint_frametype_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL) {
		WayPoints[ModelActive][waypoint_active].frametype = MAV_FRAME_GLOBAL_RELATIVE_ALT;
	} else {
		WayPoints[ModelActive][waypoint_active].frametype = MAV_FRAME_GLOBAL;
	}
	return 0;
}

uint8_t wpedit_waypoint_type_select (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (strcmp(WayPoints[ModelActive][waypoint_active].command, "WAYPOINT") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "RTL");
	} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "RTL") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "TAKEOFF");
	} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "TAKEOFF") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "LAND");
	} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "LAND") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "SET_ROI");
	} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "SET_ROI") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "SHUTTER");
	} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "SHUTTER") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "SHUTTER_INT");
	} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "SHUTTER_INT") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "RELAY");
	} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "RELAY") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "RELAY_REP");
	} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "RELAY_REP") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "SERVO");
	} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "SERVO") == 0) {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "SERVO_REP");

	} else {
		strcpy(WayPoints[ModelActive][waypoint_active].command, "WAYPOINT");
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
		if (WayPoints[ModelActive][n].p_lat == 0.0) {
			break;
		}
	}
	num_waypoints = n - 1;
	sprintf(tmp_str, "Waypoint-Editor (total:%i)", num_waypoints);
	draw_title(esContext, tmp_str);


	if (waypoint_active >= 0) {

		sprintf(tmp_str, "EDIT: %s", WayPoints[ModelActive][waypoint_active].name);
		draw_text_f3(esContext, -1.2, -0.85 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
		draw_text_button(esContext, tmp_str, VIEW_MODE_WPEDIT, "[BACK]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_back, 0.0);
		n_y++;

		sprintf(tmp_str, "CMD   : %s", WayPoints[ModelActive][waypoint_active].command);
		draw_text_f3(esContext, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, 0.1, FONT_GREEN, tmp_str);
		draw_text_button(esContext, "wpedit_cmd", VIEW_MODE_WPEDIT, "[SELECT]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_type_select, 0.0);
		n_y++;

		if (strcmp(WayPoints[ModelActive][waypoint_active].command, "WAYPOINT") == 0) {
			sprintf(tmp_str, "LAT   : %f", WayPoints[ModelActive][waypoint_active].p_lat);
			draw_text_button(esContext, "lat", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			n_y++;
			sprintf(tmp_str, "LON   : %f", WayPoints[ModelActive][waypoint_active].p_long);
			draw_text_button(esContext, "long", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			n_y++;
			if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL) {
				sprintf(tmp_str, "Alt   : %0.1fm abs", WayPoints[ModelActive][waypoint_active].p_alt);
			} else if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT || WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT_INT) {
				sprintf(tmp_str, "Alt   : %0.1fm rel", WayPoints[ModelActive][waypoint_active].p_alt);
			} else {
				sprintf(tmp_str, "Alt   : %0.1fm ???", WayPoints[ModelActive][waypoint_active].p_alt);
			}
			draw_text_button(esContext, "alt", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_alt_", VIEW_MODE_WPEDIT, "[G]", FONT_GREEN, 0.6, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_alt_set, 0.0);
			draw_text_button(esContext, "wpedit_alt-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_alt_set, -1.0);
			draw_text_button(esContext, "wpedit_alt+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_alt_set, 1.0);
			n_y++;

			sprintf(tmp_str, "RADIUS: %0.1fm", WayPoints[ModelActive][waypoint_active].param1);
			draw_text_button(esContext, "param1", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_param1-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param1_set, -1.0);
			draw_text_button(esContext, "wpedit_param1+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param1_set, 1.0);
			n_y++;

			sprintf(tmp_str, "WAIT  : %0.0fms", WayPoints[ModelActive][waypoint_active].param2);
			draw_text_button(esContext, "param2", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_param2-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param2_set, -100.0);
			draw_text_button(esContext, "wpedit_param2+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param2_set, 100.0);
			n_y++;

			sprintf(tmp_str, "ORBIT : %0.1fm", WayPoints[ModelActive][waypoint_active].param3);
			draw_text_button(esContext, "param3", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_param3-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param3_set, -1.0);
			draw_text_button(esContext, "wpedit_param3+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param3_set, 1.0);
			n_y++;

			sprintf(tmp_str, "Yaw   : %f", WayPoints[ModelActive][waypoint_active].param4);
			draw_text_button(esContext, "param4", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_param4-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param4_set, -1.0);
			draw_text_button(esContext, "wpedit_param4+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param4_set, 1.0);
			n_y++;

			if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL) {
				sprintf(tmp_str, "FTYPE : GLOBAL");
			} else if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT || WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT_INT) {
				sprintf(tmp_str, "FTYPE : GLOBAL_RELATIVE_ALT");
			} else {
				sprintf(tmp_str, "FTYPE : ???");
			}
			draw_text_button(esContext, "frametype", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_frametype-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_frametype_set, -1.0);
			draw_text_button(esContext, "wpedit_frametype+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_frametype_set, 1.0);
			n_y++;
		} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "SET_ROI") == 0) {
			sprintf(tmp_str, "LAT   : %f", WayPoints[ModelActive][waypoint_active].p_lat);
			draw_text_button(esContext, "lat", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			n_y++;
			sprintf(tmp_str, "LON   : %f", WayPoints[ModelActive][waypoint_active].p_long);
			draw_text_button(esContext, "long", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			n_y++;

			if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL) {
				sprintf(tmp_str, "Alt   : %0.1fm abs", WayPoints[ModelActive][waypoint_active].p_alt);
			} else if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT || WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT_INT) {
				sprintf(tmp_str, "Alt   : %0.1fm rel", WayPoints[ModelActive][waypoint_active].p_alt);
			} else {
				sprintf(tmp_str, "Alt   : %0.1fm ???", WayPoints[ModelActive][waypoint_active].p_alt);
			}
			draw_text_button(esContext, "alt", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_alt_", VIEW_MODE_WPEDIT, "[G]", FONT_GREEN, 0.6, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_alt_set, 0.0);
			draw_text_button(esContext, "wpedit_alt-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_alt_set, -1.0);
			draw_text_button(esContext, "wpedit_alt+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_alt_set, 1.0);
			n_y++;
			if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL) {
				sprintf(tmp_str, "FTYPE : GLOBAL");
			} else if (WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT || WayPoints[ModelActive][waypoint_active].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT_INT) {
				sprintf(tmp_str, "FTYPE : GLOBAL_RELATIVE_ALT");
			} else {
				sprintf(tmp_str, "FTYPE : ???");
			}
			draw_text_button(esContext, "frametype", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_frametype-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_frametype_set, -1.0);
			draw_text_button(esContext, "wpedit_frametype+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_frametype_set, 1.0);
			n_y++;
		} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "TAKEOFF") == 0) {
			sprintf(tmp_str, "PITCH : %0.0f", WayPoints[ModelActive][waypoint_active].param2);
			draw_text_button(esContext, "param2", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_pitch-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param2_set, -1.0);
			draw_text_button(esContext, "wpedit_pitch+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param2_set, 1.0);
			n_y++;
		} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "SHUTTER_INT") == 0) {
			if (WayPoints[ModelActive][waypoint_active].param1 > 1000) {
				WayPoints[ModelActive][waypoint_active].param1 = 1000;
			}
			if (WayPoints[ModelActive][waypoint_active].param1 < 1) {
				WayPoints[ModelActive][waypoint_active].param1 = 1;
			}
			sprintf(tmp_str, "Dist : %0.0fm", WayPoints[ModelActive][waypoint_active].param1);
			draw_text_button(esContext, "param1", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_dist-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param1_set, -1.0);
			draw_text_button(esContext, "wpedit_dist+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param1_set, 1.0);
			n_y++;
		} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "RELAY") == 0) {
			if (WayPoints[ModelActive][waypoint_active].param1 > 1) {
				WayPoints[ModelActive][waypoint_active].param1 = 1;
			}
			if (WayPoints[ModelActive][waypoint_active].param1 < 0) {
				WayPoints[ModelActive][waypoint_active].param1 = 0;
			}
			if (WayPoints[ModelActive][waypoint_active].param2 > 1) {
				WayPoints[ModelActive][waypoint_active].param2 = 1;
			}
			if (WayPoints[ModelActive][waypoint_active].param2 < 0) {
				WayPoints[ModelActive][waypoint_active].param2 = 0;
			}
			sprintf(tmp_str, "RELAY-Num : %0.0f", WayPoints[ModelActive][waypoint_active].param1);
			draw_text_button(esContext, "param1", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_num-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param1_set, -1.0);
			draw_text_button(esContext, "wpedit_num+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param1_set, 1.0);
			n_y++;
			sprintf(tmp_str, "Set : %0.0f", WayPoints[ModelActive][waypoint_active].param2);
			draw_text_button(esContext, "param2", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_set-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param2_set, -1.0);
			draw_text_button(esContext, "wpedit_set+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param2_set, 1.0);
			n_y++;
		} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "RELAY_REP") == 0) {
			if (WayPoints[ModelActive][waypoint_active].param1 > 1) {
				WayPoints[ModelActive][waypoint_active].param1 = 1;
			}
			if (WayPoints[ModelActive][waypoint_active].param1 < 0) {
				WayPoints[ModelActive][waypoint_active].param1 = 0;
			}
			if (WayPoints[ModelActive][waypoint_active].param2 > 3600) {
				WayPoints[ModelActive][waypoint_active].param2 = 3600;
			}
			if (WayPoints[ModelActive][waypoint_active].param2 < 0) {
				WayPoints[ModelActive][waypoint_active].param2 = 0;
			}
			if (WayPoints[ModelActive][waypoint_active].param3 > 60) {
				WayPoints[ModelActive][waypoint_active].param3 = 60;
			}
			if (WayPoints[ModelActive][waypoint_active].param3 < 0) {
				WayPoints[ModelActive][waypoint_active].param3 = 0;
			}
			sprintf(tmp_str, "RELAY-Num : %0.0f", WayPoints[ModelActive][waypoint_active].param1);
			draw_text_button(esContext, "param1", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_num-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param1_set, -1.0);
			draw_text_button(esContext, "wpedit_num+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param1_set, 1.0);
			n_y++;
			sprintf(tmp_str, "Toggles : %0.0f", WayPoints[ModelActive][waypoint_active].param2);
			draw_text_button(esContext, "param2", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_tog-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param2_set, -1.0);
			draw_text_button(esContext, "wpedit_tog+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param2_set, 1.0);
			n_y++;
			sprintf(tmp_str, "Seconds : %0.0f", WayPoints[ModelActive][waypoint_active].param3);
			draw_text_button(esContext, "param3", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_sec-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param3_set, -1.0);
			draw_text_button(esContext, "wpedit_sec+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param3_set, 1.0);
			n_y++;
		} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "SERVO") == 0) {
			if (WayPoints[ModelActive][waypoint_active].param1 > 15) {
				WayPoints[ModelActive][waypoint_active].param1 = 15;
			}
			if (WayPoints[ModelActive][waypoint_active].param1 < 0) {
				WayPoints[ModelActive][waypoint_active].param1 = 0;
			}
			if (WayPoints[ModelActive][waypoint_active].param2 > 2200) {
				WayPoints[ModelActive][waypoint_active].param2 = 2200;
			}
			if (WayPoints[ModelActive][waypoint_active].param2 < 800) {
				WayPoints[ModelActive][waypoint_active].param2 = 800;
			}
			sprintf(tmp_str, "Servo-Num : %0.0f", WayPoints[ModelActive][waypoint_active].param1);
			draw_text_button(esContext, "param1", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_num-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param1_set, -1.0);
			draw_text_button(esContext, "wpedit_num+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param1_set, 1.0);
			n_y++;
			sprintf(tmp_str, "Position : %0.0f", WayPoints[ModelActive][waypoint_active].param2);
			draw_text_button(esContext, "param2", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_pos-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param2_set, -1.0);
			draw_text_button(esContext, "wpedit_pos+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param2_set, 1.0);
			n_y++;
		} else if (strcmp(WayPoints[ModelActive][waypoint_active].command, "SERVO_REP") == 0) {
			if (WayPoints[ModelActive][waypoint_active].param1 > 15) {
				WayPoints[ModelActive][waypoint_active].param1 = 15;
			}
			if (WayPoints[ModelActive][waypoint_active].param1 < 0) {
				WayPoints[ModelActive][waypoint_active].param1 = 0;
			}
			if (WayPoints[ModelActive][waypoint_active].param2 > 2200) {
				WayPoints[ModelActive][waypoint_active].param2 = 2200;
			}
			if (WayPoints[ModelActive][waypoint_active].param2 < 800) {
				WayPoints[ModelActive][waypoint_active].param2 = 800;
			}
			if (WayPoints[ModelActive][waypoint_active].param3 > 60) {
				WayPoints[ModelActive][waypoint_active].param3 = 60;
			}
			if (WayPoints[ModelActive][waypoint_active].param3 < 0) {
				WayPoints[ModelActive][waypoint_active].param3 = 0;
			}
			if (WayPoints[ModelActive][waypoint_active].param4 > 60) {
				WayPoints[ModelActive][waypoint_active].param4 = 60;
			}
			if (WayPoints[ModelActive][waypoint_active].param4 < 0) {
				WayPoints[ModelActive][waypoint_active].param4 = 0;
			}
			sprintf(tmp_str, "Servo-Num : %0.0f", WayPoints[ModelActive][waypoint_active].param1);
			draw_text_button(esContext, "param1", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_num-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param1_set, -1.0);
			draw_text_button(esContext, "wpedit_num+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param1_set, 1.0);
			n_y++;
			sprintf(tmp_str, "Position : %0.0f", WayPoints[ModelActive][waypoint_active].param2);
			draw_text_button(esContext, "param2", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_pos-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param2_set, -1.0);
			draw_text_button(esContext, "wpedit_pos+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param2_set, 1.0);
			n_y++;
			sprintf(tmp_str, "Toggles : %0.0f", WayPoints[ModelActive][waypoint_active].param3);
			draw_text_button(esContext, "param3", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_tog-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param3_set, -1.0);
			draw_text_button(esContext, "wpedit_tog+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param3_set, 1.0);
			n_y++;
			sprintf(tmp_str, "Seconds : %0.0f", WayPoints[ModelActive][waypoint_active].param4);
			draw_text_button(esContext, "param4", VIEW_MODE_WPEDIT, tmp_str, FONT_GREEN, -1.1, -0.85 + (n_y * step_y), 0.0025, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_number_set, 0.0);
			draw_text_button(esContext, "wpedit_sec-", VIEW_MODE_WPEDIT, "[-]", FONT_GREEN, 0.8, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_LEFT, ALIGN_TOP, wpedit_waypoint_param4_set, -1.0);
			draw_text_button(esContext, "wpedit_sec+", VIEW_MODE_WPEDIT, "[+]", FONT_GREEN, 1.2, -0.85 + (n_y * step_y), 0.002, 0.1, ALIGN_RIGHT, ALIGN_TOP, wpedit_waypoint_param4_set, 1.0);
			n_y++;
		}
	}
	draw_text_button(esContext, "map_read_wp", VIEW_MODE_WPEDIT, "READ_WP", FONT_GREEN_BG, -0.2, 0.9, 0.002, 0.06, 1, 0, read_wp, 0.0);
	draw_text_button(esContext, "map_write_wp", VIEW_MODE_WPEDIT, "WRITE_WP", FONT_GREEN_BG, 0.2, 0.9, 0.002, 0.06, 1, 0, write_wp, 0.0);
	screen_number(esContext);
}

