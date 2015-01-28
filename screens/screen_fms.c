
#include <all.h>

int16_t fms_pos = 0;
uint16_t fms_sel = 0;

uint8_t fms_null (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

uint8_t fms_add (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

uint8_t fms_rtl (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_send_cmd_rtl(ModelActive);
	return 0;
}

uint8_t fms_start_mission (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_send_cmd_mission(ModelActive);
	return 0;
}

uint8_t fms_del (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	reset_buttons();
	uint16_t n = 0;
	uint16_t n2 = waypoint_active + 1;
	for (n = waypoint_active; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[ModelActive][n].p_lat != 0.0) {
			WayPoints[ModelActive][n].p_lat = WayPoints[ModelActive][n2].p_lat;
			WayPoints[ModelActive][n].p_long = WayPoints[ModelActive][n2].p_long;
			WayPoints[ModelActive][n].p_alt = WayPoints[ModelActive][n2].p_alt;
			WayPoints[ModelActive][n].param1 = WayPoints[ModelActive][n2].param1;
			WayPoints[ModelActive][n].param2 = WayPoints[ModelActive][n2].param2;
			WayPoints[ModelActive][n].param3 = WayPoints[ModelActive][n2].param3;
			WayPoints[ModelActive][n].param4 = WayPoints[ModelActive][n2].param4;
			WayPoints[ModelActive][n].type = WayPoints[ModelActive][n2].type;
			WayPoints[ModelActive][n].frametype = WayPoints[ModelActive][n2].frametype;
			strncpy(WayPoints[ModelActive][n].name, WayPoints[ModelActive][n2].name, 127);
			strncpy(WayPoints[ModelActive][n].command, WayPoints[ModelActive][n2].command, 127);
			n2++;
		}
	}
	waypoint_active--;
	return 0;
}

uint8_t fms_scroll (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 5) {
		fms_pos += (int)1;
	} else if (button == 4) {
		fms_pos -= (int)1;
	} else if ((int)data < 0) {
		if (fms_pos > 0) {
			fms_pos -= (int)1;
		}
	} else {
		fms_pos += (int)1;
	}
	reset_buttons();
	return 0;
}

uint8_t fms_select (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	reset_buttons();
	waypoint_active = (int)data;
	return 0;
}

void screen_fms (ESContext *esContext) {
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
	char tmp_str2[100];
	int n = 0;
	int n2 = 0;
	float step_y = 0.22;
	float last_lat = 0.0;
	float last_lon = 0.0;
	float last_alt = 0.0;
	float alt = 0.0;
	float ss = -0.7;
	uint16_t num_waypoints = 0;
	for (n = 1; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[ModelActive][n].p_lat == 0.0) {
			break;
		}
	}
	num_waypoints = n - 1;
	sprintf(tmp_str, "Waypoint-Editors (total:%i)", num_waypoints);
	draw_title(esContext, tmp_str);
	for (n = fms_pos * 7; n < MAX_WAYPOINTS && n2 < 7; n++) {
		if (n == 0) {
			draw_box_f(esContext, -1.2, -0.55 + ((n2 - 1) * step_y), 1.3, -0.55 + (n2 * step_y), 127, 127, 127, 64);
		} else if (n == waypoint_active) {
			draw_box_f(esContext, -1.2, -0.55 + ((n2 - 1) * step_y), 1.3, -0.55 + (n2 * step_y), 255, 255, 255, 64);
			draw_line_f(esContext, ss - 0.01, -0.53 + ((n2 - 1) * step_y), ss, -0.51 + ((n2 - 1) * step_y), 0, 255, 0, 255);
			draw_line_f(esContext, ss + 0.01, -0.53 + ((n2 - 1) * step_y), ss, -0.51 + ((n2 - 1) * step_y), 0, 255, 0, 255);
		}
		if (WayPoints[ModelActive][n].p_lat != 0.0) {
			float distance1 = 0.0;
			float distance2 = 0.0;
			float winkel_up = 0.0;
			if (strcmp(WayPoints[ModelActive][n].command, "WAYPOINT") == 0) {
				if (last_lat != 0.0) {
					/* Distance - Ground-Level */
					distance1 = acos( 
						cos(toRad(last_lat))
						* cos(toRad(WayPoints[ModelActive][n].p_lat))
						* cos(toRad(last_lon) - toRad(WayPoints[ModelActive][n].p_long))
						+ sin(toRad(last_lat)) 
						* sin(toRad(WayPoints[ModelActive][n].p_lat))
					) * 6378.137 * 1000.0;
					alt = WayPoints[ModelActive][n].p_alt - last_alt;
					/* Distance - Sichtverbindung */
					distance2 = sqrt(((distance1) * (distance1)) + (alt * alt));
					/* Steigung */
					winkel_up = (asin(alt / distance2)) * 180 / PI;
					sprintf(tmp_str, "%0.1fm (%0.1fm / %0.1fGrad)", distance1, distance2, winkel_up);
					draw_text_f3(esContext, ss + 0.01, -0.62 + (n2 * step_y) - 0.125, 0.002, 0.05, 0.05, FONT_GREEN, tmp_str);
				}
				last_lat = WayPoints[ModelActive][n].p_lat;
				last_lon = WayPoints[ModelActive][n].p_long;
				last_alt = WayPoints[ModelActive][n].p_alt;
			}

			draw_line_f(esContext, ss, -0.55 + ((n2 - 1) * step_y), ss, -0.55 + (n2 * step_y), 0, 255, 0, 255);
			draw_circleFilled_f(esContext, ss, -0.55 + ((n2 - 1) * step_y), 0.01, 0, 255, 0, 128);
			draw_circleFilled_f(esContext, ss, -0.55 + (n2 * step_y), 0.01, 0, 255, 0, 128);


			sprintf(tmp_str, "%s", WayPoints[ModelActive][n].name);
			draw_text_button(esContext, "-", VIEW_MODE_FMS, tmp_str, FONT_GREEN, -1.2, -0.7 + (n2 * step_y), 0.002, 0.1, 0, 0, fms_select, (float)n);
			if (WayPoints[ModelActive][n].command[0] == 0) {
				strcpy(tmp_str, "---");
			} else {
				sprintf(tmp_str, "%s", WayPoints[ModelActive][n].command);
			}
			draw_text_f3(esContext, -1.2 + 0.01, -0.7 + (n2 * step_y) - 0.04, 0.002, 0.05, 0.05, FONT_GREEN, tmp_str);

			int nny = 0;
			int nny2 = 0;
			if (strcmp(WayPoints[ModelActive][n].command, "SHUTTER") == 0) {
			} else if (strcmp(WayPoints[ModelActive][n].command, "RTL") == 0) {
			} else if (strcmp(WayPoints[ModelActive][n].command, "LAND") == 0) {
			} else if (strcmp(WayPoints[ModelActive][n].command, "SHUTTER_INT") == 0) {
				sprintf(tmp_str, "Dist:%0.1fm", WayPoints[ModelActive][n].param1);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
			} else if (strcmp(WayPoints[ModelActive][n].command, "RELAY") == 0) {
				sprintf(tmp_str, "NUM:%0.0f", WayPoints[ModelActive][n].param1);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
				sprintf(tmp_str, "SET/UNSET:%0.0f", WayPoints[ModelActive][n].param2);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
			} else if (strcmp(WayPoints[ModelActive][n].command, "RELAY_REP") == 0) {
				sprintf(tmp_str, "NUM:%0.1f", WayPoints[ModelActive][n].param1);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
				sprintf(tmp_str, "TOGGLES:%0.0f", WayPoints[ModelActive][n].param2);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
				sprintf(tmp_str, "SECONDS:%0.0f", WayPoints[ModelActive][n].param3);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, 0.1, -0.75 + (nny2++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
			} else if (strcmp(WayPoints[ModelActive][n].command, "SERVO") == 0) {
				sprintf(tmp_str, "NUM:%0.1f", WayPoints[ModelActive][n].param1);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
				sprintf(tmp_str, "POS:%0.0f", WayPoints[ModelActive][n].param2);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
			} else if (strcmp(WayPoints[ModelActive][n].command, "SERVO_REP") == 0) {
				sprintf(tmp_str, "NUM:%0.1f", WayPoints[ModelActive][n].param1);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
				sprintf(tmp_str, "POS:%0.0f", WayPoints[ModelActive][n].param2);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
				sprintf(tmp_str, "TOGGLES:%0.0f", WayPoints[ModelActive][n].param3);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, 0.1, -0.75 + (nny2++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
				sprintf(tmp_str, "SECONDS:%0.0f", WayPoints[ModelActive][n].param4);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, 0.1, -0.75 + (nny2++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
			} else if (strcmp(WayPoints[ModelActive][n].command, "TAKEOFF") == 0) {
				sprintf(tmp_str, "PITCH:%0.0f", WayPoints[ModelActive][n].param2);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.75 + (nny++ * 0.1) + (n2 * step_y), 0.002, 0.08, 0, 0, fms_select, (float)n);
			} else {
				if (WayPoints[ModelActive][n].p_lat == 0.0) {
					strcpy(tmp_str, "---");
				} else {
					sprintf(tmp_str, "%0.6f", WayPoints[ModelActive][n].p_lat);
				}
				draw_text_button(esContext, "-", VIEW_MODE_FMS, tmp_str, FONT_GREEN, -0.5, -0.7 + (n2 * step_y), 0.002, 0.1, 0, 0, fms_select, (float)n);
				if (WayPoints[ModelActive][n].p_long == 0.0) {
					strcpy(tmp_str, "---");
				} else {
					sprintf(tmp_str, "%0.6f", WayPoints[ModelActive][n].p_long);
				}
				draw_text_button(esContext, "-", VIEW_MODE_FMS, tmp_str, FONT_GREEN, 0.1, -0.7 + (n2 * step_y), 0.002, 0.1, 0, 0, fms_select, (float)n);
				if (WayPoints[ModelActive][n].p_alt == 0.0) {
					strcpy(tmp_str, "---");
				} else {
					if (WayPoints[ModelActive][n].frametype == MAV_FRAME_GLOBAL) {
						sprintf(tmp_str, "%0.1fm abs", WayPoints[ModelActive][n].p_alt);
					} else if (WayPoints[ModelActive][n].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT || WayPoints[ModelActive][n].frametype == MAV_FRAME_GLOBAL_RELATIVE_ALT_INT) {
						sprintf(tmp_str, "%0.1fm rel", WayPoints[ModelActive][n].p_alt);
					} else {
						sprintf(tmp_str, "%0.1fm ???", WayPoints[ModelActive][n].p_alt);
					}
				}
				draw_text_button(esContext, "-", VIEW_MODE_FMS, tmp_str, FONT_GREEN, 1.25, -0.7 + (n2 * step_y), 0.002, 0.1, 2, 0, fms_select, (float)n);
			}

			sprintf(tmp_str2, "%s-%i-d", WayPoints[ModelActive][n].name, n);
			set_button(tmp_str2, VIEW_MODE_FMS, -1.2, -0.55 + ((n2 - 1) * step_y), 1.3, -0.55 + (n2 * step_y), fms_select, (float)n, 0);

			n2++;
		}
	}
	if ((num_waypoints + 1) > 7) {
		draw_scrollbar(esContext, fms_pos, (num_waypoints + 1) / 7, fms_scroll);
	}
	if (fms_pos < 0) {
		fms_pos = 0;
	} else if (fms_pos > (num_waypoints + 1) / 7) {
		fms_pos = (num_waypoints + 1) / 7;
	}

	draw_text_button(esContext, "fms_mission", VIEW_MODE_FMS, "START", FONT_GREEN_BG, -1.0, 0.9, 0.002, 0.06, 1, 0, fms_start_mission, 0.0);
	draw_text_button(esContext, "fms_edit", VIEW_MODE_FMS, "EDIT", FONT_GREEN_BG, -0.7, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, wpedit_waypoint_edit, (float)VIEW_MODE_FMS);
	draw_text_button(esContext, "fms_add", VIEW_MODE_FMS, "ADD", FONT_GREEN_BG, -0.5, 0.9, 0.002, 0.06, 1, 0, fms_add, 0.0);
	draw_text_button(esContext, "fms_del", VIEW_MODE_FMS, "DEL", FONT_GREEN_BG, 0.5, 0.9, 0.002, 0.06, 1, 0, fms_del, 0.0);
	draw_text_button(esContext, "fms_read_wp", VIEW_MODE_FMS, "READ_WP", FONT_GREEN_BG, -0.2, 0.9, 0.002, 0.06, 1, 0, read_wp, 0.0);
	draw_text_button(esContext, "fms_write_wp", VIEW_MODE_FMS, "WRITE_WP", FONT_GREEN_BG, 0.2, 0.9, 0.002, 0.06, 1, 0, write_wp, 0.0);
	draw_text_button(esContext, "fms_goto", VIEW_MODE_FMS, "GOTO", FONT_GREEN_BG, 0.7, 0.9, 0.002, 0.06, 1, 0, map_goto, (float)waypoint_active);

}

