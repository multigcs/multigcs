
#include <all.h>

Swarm SwarmSetup;


void latlong_offset (float *p_lat, float *p_long, float *p_alt, float lat_om, float long_om, float alt_om) {
	float R = 6378137.0 + *p_alt + alt_om;
	float dLat = -lat_om / R;
	float dLong = long_om / (R * cos(PI * lat / 180.0));
	*p_lat += dLat * 180.0 / PI;
	*p_long += dLong * 180.0 / PI;
	*p_alt += alt_om;
}

uint8_t swarm_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	if (strcmp(name, "swarm_setup") == 0) {
		map_show_swarm_setup = 1 - map_show_swarm_setup;
	} else if (strcmp(name, "swarm_yawmode") == 0) {
		SwarmSetup.yaw_mode = 1 - SwarmSetup.yaw_mode;
	} else if (strcmp(name, "swarm_rotate") == 0) {
		SwarmSetup.rotate = 1 - SwarmSetup.rotate;
	} else if (strcmp(name, "swarm_setup_done") == 0) {
		map_show_swarm_setup = 0;
	} else if (strcmp(name, "swar_active") == 0) {
		SwarmSetup.active = 1 - SwarmSetup.active;
	} else if (strcmp(name, "SwarmSetup.options1") == 0) {
		SwarmSetup.options = 0;
	} else if (strcmp(name, "SwarmSetup.options2") == 0) {
		SwarmSetup.options = 1;
	} else if (strcmp(name, "SwarmSetup.selected") == 0) {
		if (button == 5) {
			if (SwarmSetup.selected > 0) {
				SwarmSetup.selected--;
			} else {
				SwarmSetup.selected = 4 - 1;
			}
		} else {
			if (SwarmSetup.selected < 4 - 1) {
				SwarmSetup.selected++;
			} else {
				SwarmSetup.selected = 0;
			}
		}
	} else if (strncmp(name, "SwarmSetup.offx", 15) == 0) {
		int n = (int)data;
		if (data == -1.0) {
			n = SwarmSetup.selected;
		}
		if (button == 5) {
			if (SwarmSetup.offset_x[n] > -50) {
				SwarmSetup.offset_x[n]--;
			}
		} else {
			if (SwarmSetup.offset_x[n] < 50) {
				SwarmSetup.offset_x[n]++;
			}
		}
	} else if (strncmp(name, "SwarmSetup.offy", 15) == 0) {
		int n = (int)data;
		if (data == -1.0) {
			n = SwarmSetup.selected;
		}
		if (button == 5) {
			if (SwarmSetup.offset_y[n] > -50) {
				SwarmSetup.offset_y[n]--;
			}
		} else {
			if (SwarmSetup.offset_y[n] < 50) {
				SwarmSetup.offset_y[n]++;
			}
		}
	} else if (strncmp(name, "SwarmSetup.offz", 15) == 0) {
		int n = (int)data;
		if (data == -1.0) {
			n = SwarmSetup.selected;
		}
		if (button == 5) {
			if (SwarmSetup.offset_z[n] > -10) {
				SwarmSetup.offset_z[n]--;
			}
		} else {
			if (SwarmSetup.offset_z[n] < 10) {
				SwarmSetup.offset_z[n]++;
			}
		}
	} else if (strcmp(name, "SwarmSetup.master") == 0) {
		if (button == 5) {
			if (SwarmSetup.master > 0) {
				SwarmSetup.master--;
			} else {
				SwarmSetup.master = MODELS_MAX - 1;
			}
		} else {
			if (SwarmSetup.master < MODELS_MAX - 1) {
				SwarmSetup.master++;
			} else {
				SwarmSetup.master = 0;
			}
		}
	} else if (strncmp(name, "SwarmSetup.slave", 16) == 0) {
		n = atoi(name + 16);
		if (button == 5) {
			if (SwarmSetup.slave[n] > -1) {
				SwarmSetup.slave[n]--;
			} else {
				SwarmSetup.slave[n] = MODELS_MAX - 1;
			}
		} else {
			if (SwarmSetup.slave[n] < MODELS_MAX - 1) {
				SwarmSetup.slave[n]++;
			} else {
				SwarmSetup.slave[n] = -1;
			}
		}
	}
	return 0;
}

void swarm_draw_setup (ESContext *esContext) {
	int n = 0;
	int ny = 1;
	int gx = 0;
	int gy = 0;
	char tmp_str[128];
	char tmp_str2[128];
	float px1 = -0.8;
	float py1 = -0.9;
	float px2 = 0.8;
	float py2 = -0.0;
	reset_buttons();
	draw_box_f3(esContext, px1, py1, 0.002, px2, py2, 0.002, 0, 0, 0, 127);
	draw_box_f3(esContext, px1, py1, 0.005, px2, py1 + 0.06, 0.005, 255, 255, 255, 127);
	draw_rect_f3(esContext, px1, py1, 0.005, px2, py1 + 0.06, 0.005, 255, 255, 255, 255);
	draw_text_button(esContext, "swarm_setup_title", setup.view_mode, "Swarm-Setup", FONT_GREEN, px1, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
	if (SwarmSetup.options == 0) {
		draw_text_button(esContext, "SwarmSetup.options1", setup.view_mode, "[ROLE]", FONT_GREEN, px1 + 0.95, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		draw_text_button(esContext, "SwarmSetup.options2", setup.view_mode, "[OFFSET]", FONT_WHITE, px1 + 1.25, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 1.0);
	} else {
		draw_text_button(esContext, "SwarmSetup.options1", setup.view_mode, "[ROLE]", FONT_WHITE, px1 + 0.95, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		draw_text_button(esContext, "SwarmSetup.options2", setup.view_mode, "[OFFSET]", FONT_GREEN, px1 + 1.25, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 1.0);
	}
	if (SwarmSetup.options == 0) {
		draw_text_button(esContext, "master_title", setup.view_mode, "Master:", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		ny++;
		if (SwarmSetup.master == -1) {
			sprintf(tmp_str, "NONE");
		} else {
			sprintf(tmp_str, "%s", ModelData[SwarmSetup.master].name);
		}
		draw_text_button(esContext, "SwarmSetup.master", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		ny++;
		ny++;
		draw_text_button(esContext, "sclave_title", setup.view_mode, "Slaves:", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		ny++;
		for (n = 0; n < 4; n++) {
			if (SwarmSetup.slave[n] == -1) {
				sprintf(tmp_str, "NONE");
			} else {
				sprintf(tmp_str, "%s", ModelData[SwarmSetup.slave[n]].name);
			}
			sprintf(tmp_str2, "SwarmSetup.slave%i", n);
			draw_text_button(esContext, tmp_str2, setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
			sprintf(tmp_str, "X=%im", SwarmSetup.offset_x[n]);
			sprintf(tmp_str2, "SwarmSetup.offx%i", n);
			draw_text_button(esContext, tmp_str2, setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.6, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)n);
			sprintf(tmp_str, "Y=%im", SwarmSetup.offset_y[n]);
			sprintf(tmp_str2, "SwarmSetup.offy%i", n);
			draw_text_button(esContext, tmp_str2, setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.9, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)n);
			sprintf(tmp_str, "Z=%im", SwarmSetup.offset_z[n]);
			sprintf(tmp_str2, "SwarmSetup.offz%i", n);
			draw_text_button(esContext, tmp_str2, setup.view_mode, tmp_str, FONT_GREEN, px1 + 1.2, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)n);
			ny++;
		}
		ny++;
		ny++;
		if (SwarmSetup.yaw_mode == 1) {
			sprintf(tmp_str, "YawMode   ROTATE");
		} else {
			sprintf(tmp_str, "YawMode   FIX");
		}
		draw_text_button(esContext, "swarm_yawmode", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		ny++;
		if (SwarmSetup.rotate == 1) {
			sprintf(tmp_str, "Rotate    TRUE");
		} else {
			sprintf(tmp_str, "YawMode   FALSE");
		}
		draw_text_button(esContext, "swarm_rotate", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		ny++;
	} else {
		float gx1 = px1 + 0.5;
		float gx2 = px2 - 0.1;
		float gy1 = py1 + 0.1;
		float gy2 = py2 - 0.1;
		int gxn = 80;
		int gyn = 40;
		ny++;
		ny++;
		sprintf(tmp_str, "SLAVE=%i", SwarmSetup.selected);
		draw_text_button(esContext, "SwarmSetup.selected", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		ny++;
		sprintf(tmp_str, "%s", ModelData[SwarmSetup.slave[SwarmSetup.selected]].name);
		draw_text_button(esContext, "SwarmSetup.offn", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)SwarmSetup.selected);
		ny++;
		sprintf(tmp_str, "X=%im", SwarmSetup.offset_x[SwarmSetup.selected]);
		draw_text_button(esContext, "SwarmSetup.offx", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)SwarmSetup.selected);
		ny++;
		sprintf(tmp_str, "Y=%im", SwarmSetup.offset_y[SwarmSetup.selected]);
		draw_text_button(esContext, "SwarmSetup.offy", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)SwarmSetup.selected);
		ny++;
		sprintf(tmp_str, "Z=%im", SwarmSetup.offset_z[SwarmSetup.selected]);
		draw_text_button(esContext, "SwarmSetup.offz", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)SwarmSetup.selected);
		ny++;

		for (gx = 0; gx <= gxn; gx++) {
			draw_line_f3(esContext, gx1 + (float)gx * ((gx2 - gx1) / (float)gxn), gy1, 0.006, gx1 + (float)gx * ((gx2 - gx1) / (float)gxn), gy2, 0.006, 255, 255, 255, 90);
		}
		for (gy = 0; gy <= gyn; gy++) {
			draw_line_f3(esContext, gx1, gy1 + (float)gy * ((gy2 - gy1) / (float)gyn), 0.006, gx2, gy1 + (float)gy * ((gy2 - gy1) / (float)gyn), 0.006, 255, 255, 255, 90);
		}
		draw_circleFilled_f3(esContext, gx1 + (gx2 - gx1) / 2.0, gy1 + (gy2 - gy1) / 2.0, 0.007, 0.01, 255, 0, 0, 255);

		for (n = 0; n < 4; n++) {
			if (SwarmSetup.slave[n] == -1) {
				continue;
			}
			float offx = SwarmSetup.offset_x[n] / 50.0;
			float offy = SwarmSetup.offset_y[n] / 50.0;
			draw_circleFilled_f3(esContext, gx1 + (gx2 - gx1) / 2.0 + offx, gy1 + (gy2 - gy1) / 2.0 + offy, 0.007, 0.01, 255, 255, 0, 255);
			if (n == SwarmSetup.selected) {
				draw_circle_f3(esContext, gx1 + (gx2 - gx1) / 2.0 + offx, gy1 + (gy2 - gy1) / 2.0 + offy, 0.007, 0.02, 255, 0, 255, 255);
			}
		}
	}

	draw_text_button(esContext, "swarm_setup_done", setup.view_mode, "[CLOSE]", FONT_GREEN, px2 - 0.02, py2 - 0.075, 0.005, 0.07, ALIGN_RIGHT, ALIGN_TOP, swarm_set, 0.0);
	draw_rect_f3(esContext, px1, py1, 0.005, px2, py2, 0.005, 255, 255, 255, 255);
}
