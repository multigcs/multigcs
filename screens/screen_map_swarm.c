
#include <all.h>

Swarm SwarmSetup;

static uint8_t pd_open[MODELS_MAX];
static uint8_t pd_openm = 0;

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
	} else if (strncmp(name, "swarm_yawmode", 13) == 0) {
		SwarmSetup.yaw_mode = 1 - SwarmSetup.yaw_mode;
	} else if (strncmp(name, "swarm_rotate", 12) == 0) {
		SwarmSetup.rotate = 1 - SwarmSetup.rotate;
	} else if (strcmp(name, "swarm_setup_done") == 0) {
		map_show_swarm_setup = 0;
	} else if (strcmp(name, "swar_active") == 0) {
		SwarmSetup.active = 1 - SwarmSetup.active;
	} else if (strcmp(name, "SwarmSetup.options0") == 0) {
		SwarmSetup.options = 0;
	} else if (strcmp(name, "SwarmSetup.options1") == 0) {
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
		int n = atoi(name + 15);
		if (button == 5) {
			if (SwarmSetup.offset_x[n] > -50) {
				SwarmSetup.offset_x[n]--;
			}
		} else if (button == 4) {
			if (SwarmSetup.offset_x[n] < 50) {
				SwarmSetup.offset_x[n]++;
			}
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_INT16, &SwarmSetup.offset_x[n], -50.0, 50.0);
		}
	} else if (strncmp(name, "SwarmSetup.offy", 15) == 0) {
		int n = atoi(name + 15);
		if (button == 5) {
			if (SwarmSetup.offset_y[n] > -50) {
				SwarmSetup.offset_y[n]--;
			}
		} else if (button == 4) {
			if (SwarmSetup.offset_y[n] < 50) {
				SwarmSetup.offset_y[n]++;
			}
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_INT16, &SwarmSetup.offset_y[n], -50.0, 50.0);
		}
	} else if (strncmp(name, "SwarmSetup.offz", 15) == 0) {
		int n = atoi(name + 15);
		if (button == 5) {
			if (SwarmSetup.offset_z[n] > -10) {
				SwarmSetup.offset_z[n]--;
			}
		} else if (button == 4) {
			if (SwarmSetup.offset_z[n] < 10) {
				SwarmSetup.offset_z[n]++;
			}
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_INT16, &SwarmSetup.offset_z[n], -50.0, 50.0);
		}
	} else if (strncmp(name, "SwarmSetup.master", 17) == 0) {
		if (button == 4) {
			if (SwarmSetup.master > -1) {
				SwarmSetup.master--;
			} else {
				SwarmSetup.master = MODELS_MAX - 1;
			}
		} else if (button == 5) {
			if (SwarmSetup.master < MODELS_MAX - 1) {
				SwarmSetup.master++;
			} else {
				SwarmSetup.master = -1;
			}
		} else {
			if (pd_openm == 1) {
				if (data > 0.0) {
					SwarmSetup.master = (int8_t)data - 2;
				}
				pd_openm = 0;
			} else {
				pd_openm = 1;
			}
		}
	} else if (strncmp(name, "SwarmSetup.slave", 16) == 0) {
		n = atoi(name + 16);
		if (button == 4) {
			if (SwarmSetup.slave[n] > -1) {
				SwarmSetup.slave[n]--;
			} else {
				SwarmSetup.slave[n] = MODELS_MAX - 1;
			}
		} else if (button == 5) {
			if (SwarmSetup.slave[n] < MODELS_MAX - 1) {
				SwarmSetup.slave[n]++;
			} else {
				SwarmSetup.slave[n] = -1;
			}
		} else {
			if (pd_open[n] == 1) {
				if (data > 0.0) {
					SwarmSetup.slave[n] = (int8_t)data - 2;
				}
				pd_open[n] = 0;
			} else {
				pd_open[n] = 1;
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
	float px2 = 0.9;
	float py2 = 0.1;
	float sy = 0.08;
	reset_buttons();

	EntryList list[3];
	list[0].name = "ROLE";
	list[1].name = "OFFSET";
	list[2].name = NULL;
	draw_window(esContext, px1, py1, px2, py2, 0.002, "SwarmSetup.options", "Swarm-Setup", list, SwarmSetup.options, swarm_set);

	if (SwarmSetup.options == 0) {
		draw_text_button(esContext, "master_title", setup.view_mode, "Master:", FONT_WHITE, px1, py1 + (float)ny * sy, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		ny++;
		uint8_t n2 = 0;
		EntryList list[MODELS_MAX + 2];
		list[0].name = "GCS";
		for (n2 = 0; n2 < MODELS_MAX; n2++) {
			list[n2 + 1].name = ModelData[n2].name;
		}
		list[n2 + 1].name = NULL;
		draw_pulldown(esContext, px1 + 0.1, py1 + (float)ny * sy, 0.45, 0.01, "SwarmSetup.master", list, pd_openm, SwarmSetup.master + 1, swarm_set);
		ny++;
		draw_text_button(esContext, "sclave_title", setup.view_mode, "Slaves:", FONT_WHITE, px1, py1 + (float)ny * sy, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		ny++;
		for (n = 0; n < 4; n++) {
			sprintf(tmp_str2, "SwarmSetup.slave%i", n);
			draw_pulldown(esContext, px1 + 0.1, py1 + (float)ny * sy, 0.44, 0.01, tmp_str2, list, pd_open[n], SwarmSetup.slave[n] + 1, swarm_set);

			sprintf(tmp_str, "X=%im", SwarmSetup.offset_x[n]);
			sprintf(tmp_str2, "SwarmSetup.offx%i", n);
			draw_spinbox(esContext, px1 + 0.55, py1 + (float)ny * sy, 0.34, 0.01, tmp_str2, "X=%0.0fm", SwarmSetup.offset_x[n], swarm_set);

			sprintf(tmp_str, "Y=%im", SwarmSetup.offset_y[n]);
			sprintf(tmp_str2, "SwarmSetup.offy%i", n);
			draw_spinbox(esContext, px1 + 0.9, py1 + (float)ny * sy, 0.34, 0.01, tmp_str2, "Y=%0.0fm", SwarmSetup.offset_y[n], swarm_set);

			sprintf(tmp_str, "Z=%im", SwarmSetup.offset_z[n]);
			sprintf(tmp_str2, "SwarmSetup.offz%i", n);
			draw_spinbox(esContext, px1 + 1.25, py1 + (float)ny * sy, 0.34, 0.01, tmp_str2, "Z=%0.0fm", SwarmSetup.offset_z[n], swarm_set);

			ny++;
		}
		ny++;
		draw_text_button(esContext, "swarm_yawmode_", setup.view_mode, "Yaw-Rotate", FONT_GREEN, px1 + 0.1, py1 + (float)ny * sy, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		draw_checkbox(esContext, px1 + 0.7, py1 + (float)ny * sy, 0.005, "swarm_yawmode", SwarmSetup.yaw_mode, swarm_set);
		ny++;
		draw_text_button(esContext, "swarm_rotate_", setup.view_mode, "Pattern-Rotate", FONT_GREEN, px1 + 0.1, py1 + (float)ny * sy, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		draw_checkbox(esContext, px1 + 0.7, py1 + (float)ny * sy, 0.005, "swarm_rotate", SwarmSetup.rotate, swarm_set);
		ny++;
	} else {
		float gx1 = px1 + 0.5;
		float gx2 = px2 - 0.1;
		float gy1 = py1 + 0.15;
		float gy2 = py2 - 0.15;
		int gxn = 80;
		int gyn = 40;
		ny++;
		ny++;
		sprintf(tmp_str, "SLAVE=%i", SwarmSetup.selected);
		draw_text_button(esContext, "SwarmSetup.selected", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * sy, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, 0.0);
		ny++;
		sprintf(tmp_str, "%s", ModelData[SwarmSetup.slave[SwarmSetup.selected]].name);
		draw_text_button(esContext, "SwarmSetup.offn", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * sy, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)SwarmSetup.selected);
		ny++;
		sprintf(tmp_str, "X=%im", SwarmSetup.offset_x[SwarmSetup.selected]);
		draw_text_button(esContext, "SwarmSetup.offx", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * sy, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)SwarmSetup.selected);
		ny++;
		sprintf(tmp_str, "Y=%im", SwarmSetup.offset_y[SwarmSetup.selected]);
		draw_text_button(esContext, "SwarmSetup.offy", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * sy, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)SwarmSetup.selected);
		ny++;
		sprintf(tmp_str, "Z=%im", SwarmSetup.offset_z[SwarmSetup.selected]);
		draw_text_button(esContext, "SwarmSetup.offz", setup.view_mode, tmp_str, FONT_GREEN, px1 + 0.01, py1 + (float)ny * sy, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, swarm_set, (float)SwarmSetup.selected);
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

	draw_buttonbox(esContext, "swarm_setup_done", setup.view_mode, "CLOSE", px2 - 0.33, py2 - 0.1, 0.3, 0.005, swarm_set, 0.0);

}
