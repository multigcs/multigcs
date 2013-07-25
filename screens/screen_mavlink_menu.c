
#include <userdata.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <main.h>
#include <model.h>
#include <screen_mavlink_menu.h>
#include <screen_keyboard.h>
#include <screen_filesystem.h>
#include <my_mavlink.h>

float sel = 0.0;
float set_sel = 0.0;
float sel2 = 0.0;
float set_sel2 = 0.0;
uint8_t sel1_mode = 0;
uint8_t sel2_mode = 0;

static char select_section[100];
static int option_menu = -1;
static int bits_menu = -1;

#define SLIDER_START	0.35
#define SLIDER_LEN	0.7




void mavlink_meta_get_option (int id, char *name, char *entry) {
	char tmp_str3[1024];
	int n = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	int selected = -1;
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return;
	}
	MavLinkVars[n].min = atof(MavLinkVars[n].values);
	for (n2 = 0; n2 < strlen(MavLinkVars[n].values); n2++) {
		if (MavLinkVars[n].values[n2] == ',') {
			strcpy(tmp_str3, MavLinkVars[n].values + n3);
			for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
				if (tmp_str3[n4] == ',') {
					tmp_str3[n4] = 0;
					break;
				}
			}
			if (atoi(tmp_str3) == id) {
				strcpy(entry, tmp_str3);
//				break;
			}
			n3 = n2 + 1;
		}
	}
	strcpy(tmp_str3, MavLinkVars[n].values + n3);
	MavLinkVars[n].max = atof(tmp_str3);
	if (atoi(tmp_str3) == id) {
		strcpy(entry, tmp_str3);
	}
}

void mavlink_meta_get_bits (int id, char *name, char *entry) {
	char tmp_str3[1024];
	int n = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	int selected = -1;
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return;
	}
	MavLinkVars[n].min = atof(MavLinkVars[n].bits);
	for (n2 = 0; n2 < strlen(MavLinkVars[n].bits); n2++) {
		if (MavLinkVars[n].bits[n2] == ',') {
			strcpy(tmp_str3, MavLinkVars[n].bits + n3);
			for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
				if (tmp_str3[n4] == ',') {
					tmp_str3[n4] = 0;
					break;
				}
			}
			if (atoi(tmp_str3) == id) {
				strcpy(entry, tmp_str3);
//				break;
			}
			n3 = n2 + 1;
		}
	}
	strcpy(tmp_str3, MavLinkVars[n].bits + n3);
	MavLinkVars[n].max = atof(tmp_str3);
	if (atoi(tmp_str3) == id) {
		strcpy(entry, tmp_str3);
	}
}

uint8_t mavlink_slider_move (char *name, float x, float y, int8_t button, float data) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name + 1) == 0) {
			selected = n;
			break;
		}
	}
	if (button == 4) {
		if (MavLinkVars[selected].type != 0) {
			MavLinkVars[selected].value += 1;
		} else {
			MavLinkVars[selected].value += 0.01;
		}
	} else if (button == 5) {
		if (MavLinkVars[selected].type != 0) {
			MavLinkVars[selected].value -= 1;
		} else {
			MavLinkVars[selected].value -= 0.01;
		}
	} else {
		float percent = (x - SLIDER_START) * 100.0 / SLIDER_LEN;
		if (percent > 100.0) {
			percent = 100.0;
		} else if (percent < 0.0) {
			percent = 0.0;
		}
		float diff = MavLinkVars[selected].max - MavLinkVars[selected].min;
		float new = percent * diff / 100.0 + MavLinkVars[selected].min;
		if (MavLinkVars[selected].type != 0) {
			int conv = (int)(new);
			new = (float)conv;
		}
		printf("slider: %s %f %f %f %f\n", name + 1, x, percent, new, data);
		if (strstr(MavLinkVars[selected].name, "baud") > 0) {
			float bauds[] = {1200.0, 2400.0, 9600.0, 38400.0, 57600.0, 115200.0, 200000.0};
			for (n = 0; n < 6; n++) {
				if (new <= bauds[n] + (bauds[n + 1] - bauds[n]) / 2) {
					new = bauds[n];
					break;
				}
			}
		}
		MavLinkVars[selected].value = new;
	}
	if (MavLinkVars[selected].value < MavLinkVars[selected].min) {
		MavLinkVars[selected].value = MavLinkVars[selected].min;
	} else if (MavLinkVars[selected].value > MavLinkVars[selected].max) {
		MavLinkVars[selected].value = MavLinkVars[selected].max;
	}
	mavlink_send_value(MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
	return 0;
}

uint8_t mavlink_options_menu (char *name, float x, float y, int8_t button, float data) {
	option_menu = (int)data;
	return 0;
}

uint8_t mavlink_option_sel (char *name, float x, float y, int8_t button, float data) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name + 3) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return;
	}
	MavLinkVars[selected].value = data;
	mavlink_send_value(MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
	option_menu = -1;
	return 0;
}

uint8_t mavlink_bits_menu (char *name, float x, float y, int8_t button, float data) {
	bits_menu = (int)data;
	return 0;
}

uint8_t mavlink_bits_sel (char *name, float x, float y, int8_t button, float data) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name + 3) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return;
	}
	int new = (int)MavLinkVars[selected].value;
	if (new & (1<<(int)data)) {
		new &= ~(1<<(int)data);
	} else {
		new |= (1<<(int)data);
	}
	MavLinkVars[selected].value = (float)new;
	mavlink_send_value(MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
	return 0;
}

uint8_t mavlink_param_file_save (char *name, float x, float y, int8_t button, float data) {
	char filename[1024];
	FILE *fr;
	int n = 0;
	sprintf(filename, "%s/PARAMS/%s", BASE_DIR, name);
	if ((fr = fopen(filename, "w")) != 0) {
		fprintf(fr, "# Onboard parameters\n");
		fprintf(fr, "#\n");
		fprintf(fr, "# MAV ID  COMPONENT ID  PARAM NAME  VALUE (FLOAT)\n");
		for (n = 0; n < 500 - 1; n++) {
			if (MavLinkVars[n].name[0] != 0) {
				fprintf(fr, "%i	%i	%s	%f\n", ModelData.sysid, ModelData.compid, MavLinkVars[n].name, MavLinkVars[n].value);
			}
		}
		fprintf(fr, "\n");
		fclose(fr);
		printf("failed to save file: %s\n", filename);
	} else {
		printf("saved file: %s\n", filename);
	}
	return 0;
}

uint8_t mavlink_param_save (char *name, float x, float y, int8_t button, float data) {
	char filename[1024];
	sprintf(filename, "%s.txt", ModelData.name);
	keyboard_set_callback(mavlink_param_file_save);
	keyboard_set_text(filename);
	keyboard_set_mode(VIEW_MODE_FCMENU);
	return 0;
}

uint8_t mavlink_param_file_load (char *name, float x, float y, int8_t button, float data) {
	mavlink_param_read_file(name);
	return 0;
}

uint8_t mavlink_param_load (char *name, float x, float y, int8_t button, float data) {
	char directory[200];
	sprintf(directory, "%s/PARAMS", BASE_DIR);
	filesystem_set_callback(mavlink_param_file_load);
	filesystem_set_dir(directory);
	filesystem_reset_filter();
	filesystem_add_filter(".txt\0");
	filesystem_add_filter(".param\0");
	filesystem_set_mode(VIEW_MODE_FCMENU);
	return 0;
}

uint8_t mavlink_flash (char *name, float x, float y, int8_t button, float data) {
	save_to_flash();
	return 0;
}

uint8_t mavlink_flashload (char *name, float x, float y, int8_t button, float data) {
	load_from_flash();
	return 0;
}

uint8_t mavlink_aux_toggle (char *name, float x, float y, int8_t button, float data) {
	printf("aux: %s %f\n", name, data);
	int n = 0;
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name + 3) == 0) {
			break;
		}
	}
	int new = (int)MavLinkVars[n].value;
	if (name[0] == 'S') {
		new |= (1<<(int)data);
	} else if (name[0] == 'R') {
		new &= ~(1<<(int)data);
	}
	MavLinkVars[n].value = (float)new;
	mavlink_send_value(MavLinkVars[n].name, MavLinkVars[n].value, MavLinkVars[n].type);
	reset_buttons();
	return 0;
}

uint8_t mavlink_select_main (char *name, float x, float y, int8_t button, float data) {
	sel2 = (float)data;
	set_sel2 = (float)data;
	set_sel = 0;
	strcpy(select_section, name + 8);
	sel1_mode = 1;
	reset_buttons();
	return 0;
}

uint8_t mavlink_select_sel (char *name, float x, float y, int8_t button, float data) {
	uint16_t n = 0;
	printf("%s -- %0.2f\n", name + 1, data);
	if (data == 0.0) {
		sel1_mode = 0;
		reset_buttons();
		return 0;
	}
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name + 1) == 0) {
			MavLinkVars[n].value += data;
			mavlink_send_value(MavLinkVars[n].name, MavLinkVars[n].value, MavLinkVars[n].type);
			break;
		}
	}
	reset_buttons();
	return 0;
}

uint8_t mavlink_select_sel_scroll (char *name, float x, float y, int8_t button, float data) {
	if ((int)data > 0) {
		set_sel++;
	} else if (set_sel > 0) {
		set_sel--;
	}
	return 0;
}

void mavlink_param_read_file (char *param_file) {
        FILE *fr;
        char line[1024];
        int tmp_int1;
        int tmp_int2;
        char var1[101];
        char val[101];
        fr = fopen (param_file, "r");
        while(fgets(line, 100, fr) != NULL) {
                var1[0] = 0;
                val[0] = 0;
		if (line[0] != '#' && line[0] != '\n') {
	                sscanf (line, "%i %i %s %s", &tmp_int1, &tmp_int2, (char *)&var1, (char *)&val);
			float new_val = atof(val);
			uint16_t n = 0;
			uint8_t flag = 0;
			for (n = 0; n < 500; n++) {
				if (strcmp(MavLinkVars[n].name, var1) == 0) {
					float old_val = MavLinkVars[n].value;
					if (old_val != new_val) {
						printf ("CHANGED: %s = %f (OLD: %f)\n", var1, new_val, MavLinkVars[n].value);
						MavLinkVars[n].value = atof(val);
					}
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				for (n = 0; n < 500; n++) {
					if (MavLinkVars[n].name[0] == 0) {
						strcpy(MavLinkVars[n].name, var1);
						MavLinkVars[n].value = atof(val);
						MavLinkVars[n].id = -1;
				                printf ("NEW: %s = %f\n", var1, atof(val));
						break;
					}
				}
			}

		}
        }
        fclose(fr);
	reset_buttons();
}

uint8_t mavlink_param_upload_all (char *name, float x, float y, int8_t button, float data) {
	int n = 0;
	for (n = 0; n < 500 - 1; n++) {
		if (MavLinkVars[n].name[0] != 0) {
			mavlink_send_value(MavLinkVars[n].name, MavLinkVars[n].value, MavLinkVars[n].type);
			SDL_Delay(20);
		}
	}
	reset_buttons();
	return 0;
}

void screen_mavlink_menu (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	int16_t row = 0;
	int16_t col = 0;
	int16_t row2 = 0;
	int16_t n = 0;
	int16_t n2 = 0;
	int n3 = 0;
	int n4 = 0;
	char section[100];
	char tmp_str[1024];
	char tmp_str2[1024];
	char tmp_str3[1024];
	int8_t flag = 0;
	int8_t flag2 = 0;
	draw_title(esContext, "MavLink-Parameter");

	strcpy(section, mainMavLinkVars[(int)sel2].name);
	row2 = 0;
	for (row = 0; row < 500 - 1; row++) {
		if (strlen(MavLinkVars[row].name) > 3) {
			strcpy(tmp_str, MavLinkVars[row].name);
			for (n = 0; n < strlen(tmp_str) ; n++) {
				if (tmp_str[n] == '_') {
					tmp_str[n] = 0;
					break;
				}
			}
			flag2 = 0;
			for (row2 = 0; row2 < 500 - 1; row2++) {
				if (strcmp(mainMavLinkVars[row2].name, tmp_str) == 0) {
					flag2 = 1;
					break;
				}
			}
			if (flag2 == 0) {
				for (row2 = 0; row2 < 500 - 1; row2++) {
					if (mainMavLinkVars[row2].name[0] == 0) {
						strcpy(mainMavLinkVars[row2].name, tmp_str);
						break;
					}
				}
			}
			flag = 1;
		}
	}
	if (row2 > 0 && set_sel2 >= row2) {
		set_sel2 = row2 - 1;
	}
	row2 = 0;
	for (row = 0; row < 500 - 1; row++) {
		if (strncmp(MavLinkVars[row].name, section, strlen(section)) == 0) {
//			printf("%s - %s\n", section, MavLinkVars[row].name);
			strcpy(selMavLinkVars[row2].name, MavLinkVars[row].name);
			strcpy(selMavLinkVars[row2].desc, MavLinkVars[row].desc);
			strcpy(selMavLinkVars[row2].values, MavLinkVars[row].values);
			strcpy(selMavLinkVars[row2].bits, MavLinkVars[row].bits);
			selMavLinkVars[row2].value = MavLinkVars[row].value;
			selMavLinkVars[row2].min = MavLinkVars[row].min;
			selMavLinkVars[row2].max = MavLinkVars[row].max;
			selMavLinkVars[row2].type = MavLinkVars[row].type;
			selMavLinkVars[row2].id = row;
			selMavLinkVars[row2 + 1].name[0] = 0;
			selMavLinkVars[row2 + 1].value = 0.0;
			selMavLinkVars[row2 + 1].min = 0.0;
			selMavLinkVars[row2 + 1].max = 0.0;
			selMavLinkVars[row2 + 1].type = 0;
			selMavLinkVars[row2 + 1].id = 0;
			row2++;
		}
	}
	if (row2 > 0 && set_sel >= row2) {
		set_sel = row2 - 1;
	}

	if (sel1_mode != 1) {
		col = 0;
		row = 0;
		for (n = 0; n < 500; n++) {
			if (mainMavLinkVars[n].name[0] == 0) {
				break;
			}
			sprintf(tmp_str, "mv_main_%s", mainMavLinkVars[n].name);
			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, mainMavLinkVars[n].name, FONT_WHITE, -1.3 + col * 0.5, -0.8 + row * 0.12, 0.002, 0.08, 0, 0, mavlink_select_main, n);
			col++;
			if (col > 4) {
				col = 0;
				row++;
			}
		}
	}
	if (sel1_mode == 1) {
		col = 0;
		row = 0;
		if ((int)set_sel > 0) {
			sprintf(tmp_str, "-scroll_%s", selMavLinkVars[n].name);
			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[^]", FONT_WHITE, 0.0, -0.7 - 0.14, 0.002, 0.08, 1, 0, mavlink_select_sel_scroll, -1.0);
		}

		for (n = 0; n < 10 && n + (int)set_sel < 500; n++) {
			if (selMavLinkVars[n + (int)set_sel].name[0] == 0) {
				break;
			}

			if (strlen(selMavLinkVars[n + (int)set_sel].desc) > 60) {
				strncpy(tmp_str, selMavLinkVars[n + (int)set_sel].desc, 100);
				tmp_str[60] = 0;
				draw_button(esContext, "#", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.19, -0.7 + row * 0.14 + 0.07, 0.002, 0.04, 0, 0, mavlink_select_sel, n);
				draw_button(esContext, "#", VIEW_MODE_FCMENU, selMavLinkVars[n + (int)set_sel].desc + 60, FONT_WHITE, -1.18, -0.7 + row * 0.14 + 0.07 + 0.04, 0.002, 0.04, 0, 0, mavlink_select_sel, n);
			} else {
				draw_button(esContext, "#", VIEW_MODE_FCMENU, selMavLinkVars[n + (int)set_sel].desc, FONT_WHITE, -1.19, -0.7 + row * 0.14 + 0.07, 0.002, 0.04, 0, 0, mavlink_select_sel, n);
			}

			if (selMavLinkVars[n + (int)set_sel].type != 0) {
				sprintf(tmp_str2, "%i", (int)selMavLinkVars[n + (int)set_sel].value);
			} else {
				sprintf(tmp_str2, "%0.4f", selMavLinkVars[n + (int)set_sel].value);
			}

			if (
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_angle") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_horizon") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_baro") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_mag") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_camstab") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_camtrig") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_arm") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_gps_home") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_gps_hold") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_gps_log") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_passthru") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_headfree") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_beeper") == 0
				||
				strcmp(selMavLinkVars[n + (int)set_sel].name, "aux_headadj") == 0
			) {
				sprintf(tmp_str, "mv_sel_%s_%i_t", selMavLinkVars[n + (int)set_sel].name, n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, selMavLinkVars[n + (int)set_sel].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_select_sel, n);
				n3 = 0;
				for (n2 = 0; n2 < 12; n2++) {
					if ((int)selMavLinkVars[n + (int)set_sel].value & (1<<n2)) {
						sprintf(tmp_str, "R%2.0i%s", n2, selMavLinkVars[n + (int)set_sel].name);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "X", FONT_WHITE, -0.3 + n3 * 0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_aux_toggle, (float)n2);
					} else {
						sprintf(tmp_str, "S%2.0i%s", n2, selMavLinkVars[n + (int)set_sel].name);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "O", FONT_WHITE, -0.3 + n3 * 0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_aux_toggle, (float)n2);
					}
					if (n2 == 2 || n2 == 5 || n2 == 8) {
						n3++;
					}
					n3++;
				}
			} else if (selMavLinkVars[n + (int)set_sel].values[0] != 0) {
				sprintf(tmp_str, "mv_sel_%s_%i_t", selMavLinkVars[n + (int)set_sel].name, n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, selMavLinkVars[n + (int)set_sel].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_options_menu, (float)(n + (int)set_sel));
				mavlink_meta_get_option((int)selMavLinkVars[n + (int)set_sel].value, selMavLinkVars[n + (int)set_sel].name, tmp_str2);
				sprintf(tmp_str, "S%s", selMavLinkVars[n + (int)set_sel].name);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_options_menu, (float)(n + (int)set_sel));
			} else if (selMavLinkVars[n + (int)set_sel].bits[0] != 0) {
				sprintf(tmp_str, "mv_sel_%s_%i_t", selMavLinkVars[n + (int)set_sel].name, n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, selMavLinkVars[n + (int)set_sel].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)(n + (int)set_sel));
				sprintf(tmp_str, "B%s", selMavLinkVars[n + (int)set_sel].name);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, ".....", FONT_WHITE, -0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)(n + (int)set_sel));
			} else {
				sprintf(tmp_str, "mv_sel_%s_%i_t", selMavLinkVars[n + (int)set_sel].name, n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, selMavLinkVars[n + (int)set_sel].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_select_sel, n);
				sprintf(tmp_str, "mv_sel_%s_%i_v", selMavLinkVars[n + (int)set_sel].name, n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.7 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_select_sel, n);
				sprintf(tmp_str, "S%s", selMavLinkVars[n + (int)set_sel].name);
				draw_box_f3c2(esContext, SLIDER_START, -0.7 + row * 0.14, 0.001, SLIDER_START + SLIDER_LEN, -0.7 + row * 0.14 + 0.1, 0.001, 55, 55, 55, 220, 75, 45, 85, 100);
				draw_box_f3c2(esContext, SLIDER_START, -0.7 + row * 0.14, 0.001, SLIDER_START + ((selMavLinkVars[n + (int)set_sel].value - selMavLinkVars[n + (int)set_sel].min) * SLIDER_LEN / (selMavLinkVars[n + (int)set_sel].max - selMavLinkVars[n + (int)set_sel].min)), -0.7 + row * 0.14 + 0.1, 0.001, 255, 255, 55, 220, 175, 145, 85, 100);
				set_button(tmp_str, view_mode, SLIDER_START, -0.7 + row * 0.14, SLIDER_START + SLIDER_LEN, -0.7 + row * 0.14 + 0.1, mavlink_slider_move, (float)row, 1);
			}

			row++;
		}
		if (n >= 10) {
			sprintf(tmp_str, "+scroll_%s", selMavLinkVars[n + (int)set_sel].name);
			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[v]", FONT_WHITE, 0.0, 0.7, 0.002, 0.08, 1, 0, mavlink_select_sel_scroll, 1.0);
		}
		draw_button(esContext, "back", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, -1.3, 0.8, 0.002, 0.08, 0, 0, mavlink_select_sel, 0.0);
	}

	draw_button(esContext, "load", VIEW_MODE_FCMENU, "[LOAD FILE]", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_param_load, 1.0);
	draw_button(esContext, "save", VIEW_MODE_FCMENU, "[SAVE FILE]", FONT_WHITE, -0.5, 0.9, 0.002, 0.06, 1, 0, mavlink_param_save, 1.0);
	draw_button(esContext, "upload", VIEW_MODE_FCMENU, "[UPLOAD ALL]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, 1, 0, mavlink_param_upload_all, 1.0);
	draw_button(esContext, "flash_r", VIEW_MODE_FCMENU, "[LOAD FLASH]", FONT_WHITE, 0.5, 0.9, 0.002, 0.06, 1, 0, mavlink_flashload, 0.0);
	draw_button(esContext, "flash_w", VIEW_MODE_FCMENU, "[WRITE FLASH]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_flash, 0.0);

	if (option_menu != -1) {
		reset_buttons();
		draw_box_f3(esContext, -1.5, -1.0, 2.0, 1.5, 1.0, 2.0, 0, 0, 0, 200);
		draw_button(esContext, "#", VIEW_MODE_FCMENU, selMavLinkVars[option_menu].name, FONT_GREEN, 0.0, -0.8, 2.002, 0.08, 1, 0, mavlink_options_menu, (float)-1);
		for (n2 = (int)selMavLinkVars[option_menu].min; n2 <= (int)selMavLinkVars[option_menu].max; n2++) {
			tmp_str2[0] = 0;
			mavlink_meta_get_option(n2, selMavLinkVars[option_menu].name, tmp_str2);
			if (tmp_str2[0] == 0) {
				break;
			}
			sprintf(tmp_str, "%3.0i%s", n2, selMavLinkVars[option_menu].name);
			if ((n2 - (int)selMavLinkVars[option_menu].min) > 12) {
				if ((int)selMavLinkVars[option_menu].value == n2) {
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, 0.0, -0.7 + (n2 - (int)selMavLinkVars[option_menu].min - 13) * 0.1, 2.002, 0.08, 0, 0, mavlink_option_sel, n2);
				} else {
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.7 + (n2 - (int)selMavLinkVars[option_menu].min - 13) * 0.1, 2.002, 0.08, 0, 0, mavlink_option_sel, n2);
				}
			} else {
				if ((int)selMavLinkVars[option_menu].value == n2) {
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, -1.2, -0.7 + (n2 - (int)selMavLinkVars[option_menu].min) * 0.1, 2.002, 0.08, 0, 0, mavlink_option_sel, n2);
				} else {
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.7 + (n2 - (int)selMavLinkVars[option_menu].min) * 0.1, 2.002, 0.08, 0, 0, mavlink_option_sel, n2);
				}
			}
		}
		draw_button(esContext, "back", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, -1.3, 0.8, 2.002, 0.08, 0, 0, mavlink_options_menu, (float)-1);
	} else if (bits_menu != -1) {
		reset_buttons();
		draw_box_f3(esContext, -1.5, -1.0, 2.0, 1.5, 1.0, 2.0, 0, 0, 0, 200);
		draw_button(esContext, "#", VIEW_MODE_FCMENU, selMavLinkVars[bits_menu].name, FONT_GREEN, 0.0, -0.8, 2.002, 0.08, 1, 0, mavlink_options_menu, (float)-1);
		for (n2 = (int)0; n2 < 32; n2++) {
			tmp_str2[0] = 0;
			mavlink_meta_get_bits(n2, selMavLinkVars[bits_menu].name, tmp_str2);
			if (tmp_str2[0] == 0) {
				break;
			}
			sprintf(tmp_str, "%3.0i%s", n2, selMavLinkVars[bits_menu].name);
			if ((n2 - 0) > 12) {
				if ((int)selMavLinkVars[bits_menu].value & (1<<n2)) {
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, 0.0, -0.7 + (n2 - 13) * 0.1, 2.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				} else {
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.7 + (n2 - 13) * 0.1, 2.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				}
			} else {
				if ((int)selMavLinkVars[bits_menu].value & (1<<n2)) {
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, -1.2, -0.7 + (n2) * 0.1, 2.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				} else {
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.7 + (n2) * 0.1, 2.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				}
			}
		}
		draw_button(esContext, "back", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, -1.3, 0.8, 2.002, 0.08, 0, 0, mavlink_bits_menu, (float)-1);
	}

	if (flag == 0) {
		draw_text_f(esContext, -0.4, 0.0, 0.05, 0.05, FONT_BLACK_BG, "No Mavlink-Parameters found");
	}

	screen_keyboard(esContext);
	screen_filesystem(esContext);
}

