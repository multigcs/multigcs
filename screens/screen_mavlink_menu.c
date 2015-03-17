
#include <all.h>

extern char message_txt[1024];
float sel = 0.0;
float set_sel = 0.0;
float sel2 = 0.0;
float set_sel2 = 0.0;

typedef struct {
	char name[20];
	char title[20];
} paralist;

int16_t cal_min[8];
int16_t cal_max[8];

int8_t mavlink_view_screen = -1;
uint8_t mavlink_view_rccal = 0;
uint8_t acccal_step = 0;
uint8_t mavlink_channel_select = 0;
uint8_t mavlink_channel_select_num = 0;
uint8_t mavlink_magcal = 0;
uint8_t mavlink_magcal_set = 0;

static char select_section[1024];
static int option_menu = -1;
static int bits_menu = -1;
static int param_menu = -1;
static float param_last = 0.0;

#define SLIDER_START	0.25
#define SLIDER_LEN	1.0

#define SLIDER2_START	-1.2
#define SLIDER2_LEN	2.4


int mavlink_get_id_by_name (char *name) {
	int16_t n = 0;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name) == 0) {
			return n;
		}
	}
	return -1;
}

void mavlink_meta_get_option (int id, char *name, char *entry) {
	char tmp_str3[1024];
	int n = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return;
	}
//	MavLinkVars[ModelActive][selected].min = atof(MavLinkVars[ModelActive][selected].values);
	for (n2 = 0; n2 < strlen(MavLinkVars[ModelActive][selected].values); n2++) {
		if (MavLinkVars[ModelActive][selected].values[n2] == ',') {
			strncpy(tmp_str3, MavLinkVars[ModelActive][selected].values + n3, 1023);
			for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
				if (tmp_str3[n4] == ',') {
					tmp_str3[n4] = 0;
					break;
				}
			}
			if (atoi(tmp_str3) == id) {
				if (tmp_str3[0] == ' ') {
					strncpy(entry, tmp_str3 + 1, 1023);
				} else {
					strncpy(entry, tmp_str3, 1023);
				}
//				break;
			}
			n3 = n2 + 1;
		}
	}
	strncpy(tmp_str3, MavLinkVars[ModelActive][n].values + n3, 1023);
//	MavLinkVars[ModelActive][selected].max = atof(tmp_str3);
	if (atoi(tmp_str3) == id) {
		if (tmp_str3[0] == ' ') {
			strncpy(entry, tmp_str3 + 1, 1023);
		} else {
			strncpy(entry, tmp_str3, 1023);
		}
	}
}

void mavlink_meta_get_bits (int id, char *name, char *entry) {
	char tmp_str3[1024];
	int n = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return;
	}
	MavLinkVars[ModelActive][n].min = atof(MavLinkVars[ModelActive][n].bits);
	for (n2 = 0; n2 < strlen(MavLinkVars[ModelActive][n].bits); n2++) {
		if (MavLinkVars[ModelActive][n].bits[n2] == ',') {
			strncpy(tmp_str3, MavLinkVars[ModelActive][n].bits + n3, 1023);
			for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
				if (tmp_str3[n4] == ',') {
					tmp_str3[n4] = 0;
					break;
				}
			}
			if (atoi(tmp_str3) == id) {
				if (tmp_str3[0] == ' ') {
					strncpy(entry, tmp_str3 + 1, 1023);
				} else {
					strncpy(entry, tmp_str3, 1023);
				}
				strncpy(entry, tmp_str3, 1023);
//				break;
			}
			n3 = n2 + 1;
		}
	}
	strncpy(tmp_str3, MavLinkVars[ModelActive][n].bits + n3, 1023);
	MavLinkVars[ModelActive][n].max = (float)((1<<atoi(tmp_str3)) * (1<<atoi(tmp_str3)) - 1);
	if (atoi(tmp_str3) == id) {
		if (tmp_str3[0] == ' ') {
			strncpy(entry, tmp_str3 + 1, 1023);
		} else {
			strncpy(entry, tmp_str3, 1023);
		}
		strncpy(entry, tmp_str3, 1023);
	}
}

uint8_t mavlink_read_loglist_get (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_read_loglist(ModelActive);
	return 0;
}

uint8_t mavlink_read_logfile_get (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int id = (int)data;
	if (id != -1) {
		mavlink_read_logfile(ModelActive, loglist[id].id, 0, loglist[id].size);
	}
	return 0;
}

uint8_t mavlink_param_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name + 1) == 0) {
			selected = n;
			break;
		}
	}
	MavLinkVars[ModelActive][selected].value = data;
	if (MavLinkVars[ModelActive][selected].value < MavLinkVars[ModelActive][selected].min) {
		MavLinkVars[ModelActive][selected].value = MavLinkVars[ModelActive][selected].min;
	} else if (MavLinkVars[ModelActive][selected].value > MavLinkVars[ModelActive][selected].max) {
		MavLinkVars[ModelActive][selected].value = MavLinkVars[ModelActive][selected].max;
	}
	mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
	return 0;
}

uint8_t mavlink_param_diff (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name + 6) == 0) {
			selected = n;
			break;
		}
	}
	MavLinkVars[ModelActive][selected].value += data;
	if (MavLinkVars[ModelActive][selected].value < MavLinkVars[ModelActive][selected].min) {
		MavLinkVars[ModelActive][selected].value = MavLinkVars[ModelActive][selected].min;
	} else if (MavLinkVars[ModelActive][selected].value > MavLinkVars[ModelActive][selected].max) {
		MavLinkVars[ModelActive][selected].value = MavLinkVars[ModelActive][selected].max;
	}
	mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
	return 0;
}

uint8_t mavlink_slider_move (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name + 1) == 0) {
			selected = n;
			break;
		}
	}
	if (button == 4) {
		if (MavLinkVars[ModelActive][selected].type != MAV_VAR_FLOAT) {
			MavLinkVars[ModelActive][selected].value += 1;
		} else {
			MavLinkVars[ModelActive][selected].value += 0.01;
		}
	} else if (button == 5) {
		if (MavLinkVars[ModelActive][selected].type != MAV_VAR_FLOAT) {
			MavLinkVars[ModelActive][selected].value -= 1;
		} else {
			MavLinkVars[ModelActive][selected].value -= 0.01;
		}
	} else {
		float percent = (x - SLIDER_START) * 100.0 / SLIDER_LEN;
		if (percent > 100.0) {
			percent = 100.0;
		} else if (percent < 0.0) {
			percent = 0.0;
		}
		float diff = MavLinkVars[ModelActive][selected].max - MavLinkVars[ModelActive][selected].min;
		float new = percent * diff / 100.0 + MavLinkVars[ModelActive][selected].min;
		if (MavLinkVars[ModelActive][selected].type != MAV_VAR_FLOAT) {
			int conv = (int)(new);
			new = (float)conv;
		}
//		SDL_Log("slider: %s %f %f %f %f\n", name + 1, x, percent, new, data);
		if (strstr(MavLinkVars[ModelActive][selected].name, "baud") > 0 || strstr(MavLinkVars[ModelActive][selected].name, "BAUD") > 0) {
			float bauds[] = {1200.0, 2400.0, 9600.0, 38400.0, 57600.0, 115200.0, 200000.0};
			for (n = 0; n < 6; n++) {
				if (new <= bauds[n] + (bauds[n + 1] - bauds[n]) / 2) {
					new = bauds[n];
					break;
				}
			}
		}
		MavLinkVars[ModelActive][selected].value = new;
	}
	if (MavLinkVars[ModelActive][selected].value < MavLinkVars[ModelActive][selected].min) {
		MavLinkVars[ModelActive][selected].value = MavLinkVars[ModelActive][selected].min;
	} else if (MavLinkVars[ModelActive][selected].value > MavLinkVars[ModelActive][selected].max) {
		MavLinkVars[ModelActive][selected].value = MavLinkVars[ModelActive][selected].max;
	}
	mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
	return 0;
}

uint8_t mavlink_slider2_move (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name + 1) == 0) {
			selected = n;
			break;
		}
	}
	if (button == 4) {
		if (MavLinkVars[ModelActive][selected].type != MAV_VAR_FLOAT) {
			MavLinkVars[ModelActive][selected].value += 1;
		} else {
			MavLinkVars[ModelActive][selected].value += 0.01;
		}
	} else if (button == 5) {
		if (MavLinkVars[ModelActive][selected].type != MAV_VAR_FLOAT) {
			MavLinkVars[ModelActive][selected].value -= 1;
		} else {
			MavLinkVars[ModelActive][selected].value -= 0.01;
		}
	} else {
		float percent = (x - SLIDER2_START) * 100.0 / SLIDER2_LEN;
		if (percent > 100.0) {
			percent = 100.0;
		} else if (percent < 0.0) {
			percent = 0.0;
		}
		float diff = MavLinkVars[ModelActive][selected].max - MavLinkVars[ModelActive][selected].min;
		float new = percent * diff / 100.0 + MavLinkVars[ModelActive][selected].min;
		if (MavLinkVars[ModelActive][selected].type != MAV_VAR_FLOAT) {
			int conv = (int)(new);
			new = (float)conv;
		}
//		SDL_Log("slider2: %s %f %f %f %f\n", name + 1, x, percent, new, data);
		if (strstr(MavLinkVars[ModelActive][selected].name, "baud") > 0 || strstr(MavLinkVars[ModelActive][selected].name, "BAUD") > 0) {
			float bauds[] = {1200.0, 2400.0, 9600.0, 38400.0, 57600.0, 115200.0, 200000.0};
			for (n = 0; n < 6; n++) {
				if (new <= bauds[n] + (bauds[n + 1] - bauds[n]) / 2) {
					new = bauds[n];
					break;
				}
			}
		}
		MavLinkVars[ModelActive][selected].value = new;
	}
	if (MavLinkVars[ModelActive][selected].value < MavLinkVars[ModelActive][selected].min) {
		MavLinkVars[ModelActive][selected].value = MavLinkVars[ModelActive][selected].min;
	} else if (MavLinkVars[ModelActive][selected].value > MavLinkVars[ModelActive][selected].max) {
		MavLinkVars[ModelActive][selected].value = MavLinkVars[ModelActive][selected].max;
	}
	mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
	return 0;
}


uint8_t mavlink_set_magdecl (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name + 1) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return 0;
	}
	char tmp_str[100];
	int ret_dd = 0;
	int ret_dm = 0;
	int ret_id = 0;
	int ret_im = 0;
	get_declination(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt, &ret_dd, &ret_dm, &ret_id, &ret_im);
	if (strcmp(name + 1, "COMPASS_DEC") == 0) {
		sprintf(tmp_str, "%i.%2.0i", ret_dd, ret_dm * 100 / 60);
		MavLinkVars[ModelActive][selected].value = atof(tmp_str) * DEG_TO_RAD;
	} else {
		sprintf(tmp_str, "%i%2.0i", ret_dd, ret_dm);
		MavLinkVars[ModelActive][selected].value = atof(tmp_str);
	}
	mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
	return 0;
}

uint8_t mavlink_options_menu (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	reset_buttons();
	option_menu = (int)data;
	return 0;
}

uint8_t mavlink_option_sel (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name + 3) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return 0;
	}
	MavLinkVars[ModelActive][selected].value = data;
	mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
	option_menu = -1;
	return 0;
}

uint8_t mavlink_param_menu (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	reset_buttons();
	param_menu = (int)data;
	if (param_menu != -1) {
		param_last = MavLinkVars[ModelActive][param_menu].value;
	}
	return 0;
}

uint8_t mavlink_bits_menu (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	reset_buttons();
	bits_menu = (int)data;
	return 0;
}

uint8_t mavlink_bits_sel (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name + 3) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return 0;
	}
	int new = (int)MavLinkVars[ModelActive][selected].value;
	if (new & (1<<(int)data)) {
		new &= ~(1<<(int)data);
	} else {
		new |= (1<<(int)data);
	}
	MavLinkVars[ModelActive][selected].value = (float)new;
	mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
	return 0;
}

uint8_t mavlink_param_file_save (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	char filename[1024];
	FILE *fr;
	int n = 0;
	sprintf(filename, "%s/PARAMS/%s", get_datadirectory(), name);
	if ((fr = fopen(filename, "wb")) != 0) {
		fprintf(fr, "# Onboard parameters\n");
		fprintf(fr, "#\n");
		fprintf(fr, "# MAV ID  COMPONENT ID  PARAM NAME  VALUE (FLOAT)\n");
		for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
			if (MavLinkVars[ModelActive][n].name[0] != 0) {
				fprintf(fr, "%i	%i	%s	%f\n", ModelData[ModelActive].sysid, ModelData[ModelActive].compid, MavLinkVars[ModelActive][n].name, MavLinkVars[ModelActive][n].value);
			}
		}
		fprintf(fr, "\n");
		fclose(fr);
		SDL_Log("failed to save file: %s\n", filename);
	} else {
		SDL_Log("saved file: %s\n", filename);
	}
	return 0;
}

uint8_t mavlink_param_save (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	char filename[1024];
	sprintf(filename, "%s.txt", ModelData[ModelActive].name);
	keyboard_set_callback(mavlink_param_file_save);
	keyboard_set_text(filename);
	keyboard_set_mode(VIEW_MODE_FCMENU);
	return 0;
}

uint8_t mavlink_param_file_load (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_param_read_file(name);
	mavlink_param_xml_meta_load(ModelActive);
	return 0;
}

uint8_t mavlink_param_load (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	char directory[200];
	sprintf(directory, "%s/PARAMS", get_datadirectory());
	filesystem_set_callback(mavlink_param_file_load);
	filesystem_set_dir(directory);
	filesystem_reset_filter();
	filesystem_add_filter(".txt\0");
	filesystem_add_filter(".param\0");
	filesystem_set_mode(VIEW_MODE_FCMENU);
	return 0;
}

uint8_t mavlink_flash (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_save_to_flash(ModelActive);
	return 0;
}

uint8_t mavlink_flashload (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_load_from_flash(ModelActive);
	return 0;
}

uint8_t mavlink_aux_toggle (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	SDL_Log("aux: %s %f\n", name, data);
	int n = 0;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[ModelActive][n].name, name + 3) == 0) {
			break;
		}
	}
	int new = (int)MavLinkVars[ModelActive][n].value;
	if (name[0] == 'S') {
		new |= (1<<(int)data);
	} else if (name[0] == 'R') {
		new &= ~(1<<(int)data);
	}
	MavLinkVars[ModelActive][n].value = (float)new;
	mavlink_send_value(ModelActive, MavLinkVars[ModelActive][n].name, MavLinkVars[ModelActive][n].value, MavLinkVars[ModelActive][n].type);
	reset_buttons();
	return 0;
}

uint8_t mavlink_view_rccal_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_view_rccal = 1 - mavlink_view_rccal;
	return 0;
}

uint8_t mavlink_view_acccal_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if ((int)data == 1) {
		mavlink_send_cmd_calibration_ack(ModelActive);
	} else if ((int)data == 2) {
		sys_message("acc cal");
	} else {
		mavlink_send_cmd_calibration(ModelActive);
	}
	return 0;
}

uint8_t mavlink_view_rccal_save (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	char tmp_str[1024];
	int selected = 0;
	mavlink_view_rccal = 0;
	if (mavlink_view_rccal == 0) {
		int16_t pn = 0;
		for (pn = 0; pn < 8; pn++) {
			if (cal_min[pn] != cal_max[pn]) {
				sprintf(tmp_str, "RC%i_MIN", pn + 1);
				selected = mavlink_get_id_by_name(tmp_str);
				MavLinkVars[ModelActive][selected].value = cal_min[pn];
				mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
				SDL_Delay(30);
				sprintf(tmp_str, "RC%i_MAX", pn + 1);
				selected = mavlink_get_id_by_name(tmp_str);
				MavLinkVars[ModelActive][selected].value = cal_max[pn];
				mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
				SDL_Delay(30);
			}
		}
		// double send
		for (pn = 0; pn < 8; pn++) {
			if (cal_min[pn] != cal_max[pn]) {
				sprintf(tmp_str, "RC%i_MIN", pn + 1);
				selected = mavlink_get_id_by_name(tmp_str);
				MavLinkVars[ModelActive][selected].value = cal_min[pn];
				mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
				SDL_Delay(30);
				sprintf(tmp_str, "RC%i_MAX", pn + 1);
				selected = mavlink_get_id_by_name(tmp_str);
				MavLinkVars[ModelActive][selected].value = cal_max[pn];
				mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
				SDL_Delay(30);
			}
		}
	}
	return 0;
}

uint8_t mavlink_view_screen_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		mavlink_view_screen++;
	} else if (button == 5) {
		mavlink_view_screen--;
	} else {
		mavlink_view_screen = (int8_t)data;
	}
	reset_buttons();
	return 0;
}

uint8_t mavlink_select_main (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	strncpy(select_section, name + 8, 1023);
	set_sel = 0;
	reset_buttons();
	return 0;
}

uint8_t mavlink_select_sel (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	select_section[0] = 0;
	set_sel = 0;
	reset_buttons();
	return 0;
}

uint8_t mavlink_select_sel_scroll (char *name, float x, float y, int8_t button, float data, uint8_t action) {
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
	char var[101];
	float val = 0.0;
	float min = 0.0;
	float max = 0.0;
	SDL_Log("mavlink: load params: %s\n", param_file);
	fr = fopen (param_file, "r");
	while(fgets(line, 100, fr) != NULL) {
		var[0] = 0;
		val = 0.0;
		if ((line[0] >= 'a' && line[0] <= 'z') || (line[0] >= 'A' && line[0] <= 'Z')) {
			if (sscanf (line, "%s %f %f %f", var, &val, &min, &max) == 4) {
				mavlink_set_value(ModelActive, var, val, -1, -1);
			} else if (sscanf (line, "%[0-9a-zA-Z_],%f", var, &val) == 2) {
				mavlink_set_value(ModelActive, var, val, -1, -1);
			}
		} else if (line[0] >= '0' && line[0] <= '9') {
			sscanf (line, "%i %i %s %f", &tmp_int1, &tmp_int2, var, &val);
			mavlink_set_value(ModelActive, var, val, -1, -1);
		}
	}
	fclose(fr);
	reset_buttons();
}

uint8_t mavlink_param_upload_all (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (MavLinkVars[ModelActive][n].name[0] != 0) {
			mavlink_send_value(ModelActive, MavLinkVars[ModelActive][n].name, MavLinkVars[ModelActive][n].value, MavLinkVars[ModelActive][n].type);
			SDL_Delay(20);
		}
	}
	reset_buttons();
	return 0;
}


void screen_mavlink_list (ESContext *esContext, paralist *plist, int len) {
	char tmp_str[1024];
	char tmp_str2[1024];
	int16_t row = 0;
	int16_t pn = 0;
	int mav_id = -1;
	for (pn = 0; pn < len; pn++) {
		if (plist[pn].name[0] == '-') {
			draw_line_f3(esContext, -1.2, -0.83 + row * 0.14, 0.002, 1.25, -0.83 + row * 0.14, 0.002, 255, 255, 0, 255);
		} else {
			mav_id = mavlink_get_id_by_name(plist[pn].name);
			if (mav_id != -1) {
				sprintf(tmp_str, "mv_sel_%s_t", MavLinkVars[ModelActive][mav_id].name);
				if (plist[pn].title[0] != 0) {
					sprintf(tmp_str2, "%s", plist[pn].title);
				} else {
					sprintf(tmp_str2, "%s", plist[pn].name);
				}
				if (MavLinkVars[ModelActive][mav_id].values[0] != 0) {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.8 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_options_menu, (float)(mav_id));
					sprintf(tmp_str, "mv_sel_%s_v", MavLinkVars[ModelActive][mav_id].name);
					mavlink_meta_get_option((int)MavLinkVars[ModelActive][mav_id].value, MavLinkVars[ModelActive][mav_id].name, tmp_str2);
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.8 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_options_menu, (float)(mav_id));
				} else if (MavLinkVars[ModelActive][mav_id].bits[0] != 0) {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.8 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)(mav_id));
					sprintf(tmp_str, "mv_sel_%s_v", MavLinkVars[ModelActive][mav_id].name);
					sprintf(tmp_str2, "%0.2f", MavLinkVars[ModelActive][mav_id].value);
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.8 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_bits_menu, (float)(mav_id));
				} else {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.8 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_param_menu, (float)(mav_id));
					sprintf(tmp_str, "mv_sel_%s_v", MavLinkVars[ModelActive][mav_id].name);
					sprintf(tmp_str2, "%0.2f", MavLinkVars[ModelActive][mav_id].value);
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.8 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_param_menu, (float)(mav_id));
				}
				if (MavLinkVars[ModelActive][mav_id].bits[0] == 0 && MavLinkVars[ModelActive][mav_id].values[0] == 0) {
					sprintf(tmp_str, "S%s", MavLinkVars[ModelActive][mav_id].name);
					draw_box_f3c2(esContext, SLIDER_START, -0.8 + row * 0.14, 0.001, SLIDER_START + SLIDER_LEN, -0.8 + row * 0.14 + 0.1, 0.001, 55, 55, 55, 220, 75, 45, 85, 100);
					draw_box_f3c2(esContext, SLIDER_START, -0.8 + row * 0.14, 0.001, SLIDER_START + ((MavLinkVars[ModelActive][mav_id].value - MavLinkVars[ModelActive][mav_id].min) * SLIDER_LEN / (MavLinkVars[ModelActive][mav_id].max - MavLinkVars[ModelActive][mav_id].min)), -0.8 + row * 0.14 + 0.1, 0.001, 255, 255, 55, 220, 175, 145, 85, 100);
					set_button(tmp_str, setup.view_mode, SLIDER_START, -0.8 + row * 0.14, SLIDER_START + SLIDER_LEN, -0.8 + row * 0.14 + 0.1, mavlink_slider_move, (float)row, 1);
				}
			} else {
				sprintf(tmp_str, "%s (wait while loading....)", plist[pn].name);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_param_menu, (float)(mav_id));
			}
			row++;
		}
	}
}

void screen_mavlink_rate (ESContext *esContext) {
	paralist plist[] = {
		{"RATE_RLL_P", "Rate Roll-P"},
		{"RATE_RLL_I", "Rate Roll-I"},
		{"RATE_RLL_D", "Rate Roll-D"},
		{"RATE_RLL_IMAX", "Rate Roll-IMAX"},
		{"---", "---"},
		{"RATE_PIT_P", "Rate Roll-P"},
		{"RATE_PIT_I", "Rate Roll-I"},
		{"RATE_PIT_D", "Rate Roll-D"},
		{"RATE_PIT_IMAX", "Rate Roll-IMAX"},
		{"---", "---"},
		{"RATE_YAW_P", "Rate Roll-P"},
		{"RATE_YAW_I", "Rate Roll-I"},
		{"RATE_YAW_D", "Rate Roll-D"},
		{"RATE_YAW_IMAX", "Rate Roll-IMAX"},
	};
	draw_title(esContext, "Rate");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
}

void screen_mavlink_stabilize (ESContext *esContext) {
	paralist plist[] = {
		{"STB_RLL_P", "Stabilize Roll-P"},
		{"---", "---"},
		{"STB_PIT_P", "Stabilize Pitch-P"},
		{"---", "---"},
		{"STB_YAW_P", "Stabilize Yaw-P"},
		{"---", "---"},
		{"THR_ALT_P", "Throttle Alt-P"},
	};
	draw_title(esContext, "Stabilize");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
}

void screen_mavlink_rate_aq (ESContext *esContext) {
	paralist plist[] = {
		{"CTRL_TLT_RTE_P", "Rate Tilt-P"},
		{"CTRL_TLT_RTE_I", "Rate Tilt-I"},
		{"CTRL_TLT_RTE_D", "Rate Tilt-D"},
		{"CTRL_TLT_RTE_F", "Rate Tilt-F"},
		{"---", "---"},
		{"CTRL_TLT_RTE_PM", "Rate Tilt-PM"},
		{"CTRL_TLT_RTE_IM", "Rate Tilt-IM"},
		{"CTRL_TLT_RTE_DM", "Rate Tilt-DM"},
		{"CTRL_TLT_RTE_OM", "Rate Tilt-OM"},
	};
	draw_title(esContext, "Tilt-Rate PID's");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
}

void screen_mavlink_rateyaw_aq (ESContext *esContext) {
	paralist plist[] = {
		{"CTRL_YAW_RTE_P", "Rate Yaw-P"},
		{"CTRL_YAW_RTE_I", "Rate Yaw-I"},
		{"CTRL_YAW_RTE_D", "Rate Yaw-D"},
		{"CTRL_YAW_RTE_F", "Rate Yaw-F"},
		{"---", "---"},
		{"CTRL_YAW_RTE_PM", "Rate Yaw-PM"},
		{"CTRL_YAW_RTE_IM", "Rate Yaw-IM"},
		{"CTRL_YAW_RTE_DM", "Rate Yaw-DM"},
		{"CTRL_YAW_RTE_OM", "Rate Yaw-OM"},
	};
	draw_title(esContext, "Yaw-Rate PID's");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
}

void screen_mavlink_stabilize_aq (ESContext *esContext) {
	paralist plist[] = {
		{"CTRL_TLT_ANG_P", "Angle Tilt-P"},
		{"CTRL_TLT_ANG_I", "Angle Tilt-I"},
		{"CTRL_TLT_ANG_D", "Angle Tilt-D"},
		{"CTRL_TLT_ANG_F", "Angle Tilt-F"},
		{"---", "---"},
		{"CTRL_TLT_ANG_PM", "Angle Tilt-PM"},
		{"CTRL_TLT_ANG_IM", "Angle Tilt-IM"},
		{"CTRL_TLT_ANG_DM", "Angle Tilt-DM"},
		{"CTRL_TLT_ANG_OM", "Angle Tilt-OM"},
	};
	draw_title(esContext, "Tilt-Angle PID's");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
}

void screen_mavlink_stabilizeyaw_aq (ESContext *esContext) {
	paralist plist[] = {
		{"CTRL_YAW_ANG_P", "Angle Yaw-P"},
		{"CTRL_YAW_ANG_I", "Angle Yaw-I"},
		{"CTRL_YAW_ANG_D", "Angle Yaw-D"},
		{"CTRL_YAW_ANG_F", "Angle Yaw-F"},
		{"---", "---"},
		{"CTRL_YAW_ANG_PM", "Angle Yaw-PM"},
		{"CTRL_YAW_ANG_IM", "Angle Yaw-IM"},
		{"CTRL_YAW_ANG_DM", "Angle Yaw-DM"},
		{"CTRL_YAW_ANG_OM", "Angle Yaw-OM"},
	};
	draw_title(esContext, "Yaw-Angle PID's");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
}

void screen_mavlink_loiter (ESContext *esContext) {
	paralist plist[] = {
		{"HLD_LAT_P", "Stab-P"},
		{"---", "---"},
		{"LOITER_LAT_P", "Rate Lat-P"},
		{"LOITER_LAT_I", "Rate Lat-I"},
		{"LOITER_LAT_D", "Rate Lat-D"},
		{"LOITER_LAT_IMAX", "Rate Lat-IMAX"},
		{"---", "---"},
		{"LOITER_LON_P", "Rate Long-P"},
		{"LOITER_LON_I", "Rate Long-I"},
		{"LOITER_LON_D", "Rate Long-D"},
		{"LOITER_LON_IMAX", "Rate Long-IMAX"},
	};
	draw_title(esContext, "Loiter");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
}

void screen_mavlink_throttle (ESContext *esContext) {
	paralist plist[] = {
		{"THR_RATE_P", "Rate-P"},
		{"---", "---"},
		{"THR_ACCEL_P", "Accel-P"},
		{"THR_ACCEL_I", "Accel-I"},
		{"THR_ACCEL_D", "Accel-D"},
		{"THR_ACCEL_IMAX", "Accel-IMAX"},
	};
	draw_title(esContext, "Throttle");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
}

void screen_mavlink_flightmodes (ESContext *esContext) {
	paralist plist[] = {
		{"FLTMODE1", "Flightmode1"},
		{"FLTMODE2", "Flightmode2"},
		{"FLTMODE3", "Flightmode3"},
		{"FLTMODE4", "Flightmode4"},
		{"FLTMODE5", "Flightmode5"},
		{"FLTMODE6", "Flightmode6"},
		{"---", "---"},
		{"CH7_OPT", "Channel7-Option"},
		{"CH8_OPT", "Channel8-Option"},
	};
	draw_title(esContext, "Flightmodes");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
}

uint8_t mavlink_channel_select_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_channel_select = (uint8_t)data;
	mavlink_channel_select_num = 0;
	reset_buttons();
	return 0;
}

uint8_t mavlink_channel_select_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_channel_select_num = (uint8_t)data;
	reset_buttons();
	return 0;
}

uint8_t mavlink_mot_quadx (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	char tmp_str[128];
	int16_t pn = 0;
	mavlink_send_value(ModelActive, "MOT_PWRD_01_T", 100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_01_P", 100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_01_R", 100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_01_Y", -100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_02_T", 100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_02_P", 100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_02_R", -100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_02_Y", 100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_03_T", 100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_03_P", -100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_03_R", -100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_03_Y", -100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_04_T", 100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_04_P", -100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_04_R", 100.000000, 9);
	SDL_Delay(10);
	mavlink_send_value(ModelActive, "MOT_PWRD_04_Y", 100.000000, 9);
	SDL_Delay(10);
	for (pn = 4; pn < 8; pn++) {
		sprintf(tmp_str, "MOT_PWRD_%02i_T", pn + 1);
		mavlink_send_value(ModelActive, tmp_str, 0.000000, 9);
		SDL_Delay(10);
		sprintf(tmp_str, "MOT_PWRD_%02i_P", pn + 1);
		mavlink_send_value(ModelActive, tmp_str, 0.000000, 9);
		SDL_Delay(10);
		sprintf(tmp_str, "MOT_PWRD_%02i_R", pn + 1);
		mavlink_send_value(ModelActive, tmp_str, 0.000000, 9);
		SDL_Delay(10);
		sprintf(tmp_str, "MOT_PWRD_%02i_Y", pn + 1);
		mavlink_send_value(ModelActive, tmp_str, 0.000000, 9);
		SDL_Delay(10);
	}
	return 0;
}

uint8_t mavlink_mot_null (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

uint8_t mavlink_mot_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int mav_id = -1;
	float value = 0.0;
	mav_id = mavlink_get_id_by_name(name);
	value = MavLinkVars[ModelActive][mav_id].value;
	if (button == 4) {
		value += 1.0;
	} else if (button == 5) {
		value -= 1.0;
	} else {
		return 0;
	}
	if (value > 100.0) {
		value = 100.0;
	}
	if (value < -100.0) {
		value = -100.0;
	}
	mavlink_send_value(ModelActive, name, value, 9);
	SDL_Delay(10);
	return 0;
}

void screen_mavlink_mot_aq (ESContext *esContext) {
	char tmp_str[128];
	char tmp_str2[128];
	int16_t pn = 0;
	int mav_id = -1;
	float value_t = 0.0;
	float value_p = 0.0;
	float value_r = 0.0;
	float value_y = 0.0;
	int16_t yn = 0;
	draw_title(esContext, "Motors");
	draw_text_button(esContext, "h", VIEW_MODE_FCMENU, "Num", FONT_GREEN, -0.9, -0.8, 0.005, 0.08, 1, 0, mavlink_mot_null, 0.0);
	draw_text_button(esContext, "h", VIEW_MODE_FCMENU, "Throttle", FONT_GREEN, -0.4, -0.8, 0.005, 0.08, 1, 0, mavlink_mot_null, 0.0);
	draw_text_button(esContext, "h", VIEW_MODE_FCMENU, "Pitch", FONT_GREEN, -0.0, -0.8, 0.005, 0.08, 1, 0, mavlink_mot_null, 0.0);
	draw_text_button(esContext, "h", VIEW_MODE_FCMENU, "Roll", FONT_GREEN, 0.4, -0.8, 0.005, 0.08, 1, 0, mavlink_mot_null, 0.0);
	draw_text_button(esContext, "h", VIEW_MODE_FCMENU, "Yaw", FONT_GREEN, 0.8, -0.8, 0.005, 0.08, 1, 0, mavlink_mot_null, 0.0);
	for (pn = 0; pn < 8; pn++) {
		sprintf(tmp_str, "MOT_%02i", pn + 1);
		sprintf(tmp_str2, "#%i", pn + 1);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_PINK, -0.9, -0.7 + yn * 0.1, 0.005, 0.08, 1, 0, mavlink_mot_null, 0.0);

		sprintf(tmp_str, "MOT_PWRD_%02i_T", pn + 1);
		mav_id = mavlink_get_id_by_name(tmp_str);
		value_t = MavLinkVars[ModelActive][mav_id].value;
		sprintf(tmp_str2, "%0.1f%%", value_t);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.4, -0.7 + yn * 0.1, 0.005, 0.08, 1, 0, mavlink_mot_change, 0.0);

		sprintf(tmp_str, "MOT_PWRD_%02i_P", pn + 1);
		mav_id = mavlink_get_id_by_name(tmp_str);
		value_p = MavLinkVars[ModelActive][mav_id].value;
		sprintf(tmp_str2, "%0.1f%%", value_p);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.7 + yn * 0.1, 0.005, 0.08, 1, 0, mavlink_mot_change, 0.0);

		sprintf(tmp_str, "MOT_PWRD_%02i_R", pn + 1);
		mav_id = mavlink_get_id_by_name(tmp_str);
		value_r = MavLinkVars[ModelActive][mav_id].value;
		sprintf(tmp_str2, "%0.1f%%", value_r);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.4, -0.7 + yn * 0.1, 0.005, 0.08, 1, 0, mavlink_mot_change, 0.0);

		sprintf(tmp_str, "MOT_PWRD_%02i_Y", pn + 1);
		mav_id = mavlink_get_id_by_name(tmp_str);
		value_y = MavLinkVars[ModelActive][mav_id].value;
		sprintf(tmp_str2, "%0.1f%%", value_y);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.8, -0.7 + yn * 0.1, 0.005, 0.08, 1, 0, mavlink_mot_change, 0.0);

		if (value_y < 0.0) {
			draw_text_button(esContext, "cwccw", VIEW_MODE_FCMENU, "CW", FONT_GREEN, 1.1, -0.7 + yn * 0.1, 0.005, 0.08, 1, 0, mavlink_mot_null, 0.0);
		} else if (value_y > 0.0) {
			draw_text_button(esContext, "cwccw", VIEW_MODE_FCMENU, "CCW", FONT_PINK, 1.1, -0.7 + yn * 0.1, 0.005, 0.08, 1, 0, mavlink_mot_null, 0.0);
		}

		yn++;

#ifdef SDLGL
#ifndef ANDROID
		if (value_r != 0.0 && value_p != 0.0) {
			glLineWidth(5);
			glBegin(GL_LINES);
			glColor4f(0.0, 1.0, 0.0, 0.3);
			glVertex3f(0.0, -0.45, 0.0);
			glVertex3f(0.0 - (value_r / 450.0), -0.45 + (value_p / 450.0), -2.00);
			glEnd();
			sprintf(tmp_str, "#%i", pn + 1);
			if (value_y < 0.0) {
				draw_text_button(esContext, "h", VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, 0.0 - (value_r / 400.0), 0.45 - 0.03 - (value_p / 400.0), 0.005, 0.06, 1, 0, mavlink_mot_null, 0.0);
			} else if (value_y > 0.0) {
				draw_text_button(esContext, "h", VIEW_MODE_FCMENU, tmp_str, FONT_PINK, 0.0 - (value_r / 400.0), 0.45 - 0.03 - (value_p / 400.0), 0.005, 0.06, 1, 0, mavlink_mot_null, 0.0);
			}
		}
#endif
#endif

	}
	draw_text_button(esContext, "set_mot_quad_x", VIEW_MODE_FCMENU, "[Quad-X]", FONT_WHITE, 0.0, 0.8, 0.005, 0.08, 1, 0, mavlink_mot_quadx, 0.0);
}

uint8_t mavlink_rcmap_futaba (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_send_value(ModelActive, "RADIO_ROLL_CH", 0, 9);
	SDL_Delay(100);
	mavlink_send_value(ModelActive, "RADIO_PITC_CH", 1, 9);
	SDL_Delay(100);
	mavlink_send_value(ModelActive, "RADIO_THRO_CH", 2, 9);
	SDL_Delay(100);
	mavlink_send_value(ModelActive, "RADIO_RUDD_CH", 3, 9);
	SDL_Delay(100);
	return 0;
}

uint8_t mavlink_rcmap_jr (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	mavlink_send_value(ModelActive, "RADIO_THRO_CH", 0, 9);
	SDL_Delay(100);
	mavlink_send_value(ModelActive, "RADIO_ROLL_CH", 1, 9);
	SDL_Delay(100);
	mavlink_send_value(ModelActive, "RADIO_PITC_CH", 2, 9);
	SDL_Delay(100);
	mavlink_send_value(ModelActive, "RADIO_RUDD_CH", 3, 9);
	SDL_Delay(100);
	return 0;
}

void screen_mavlink_rccal_aq (ESContext *esContext) {
	paralist plist[] = {
		{"RADIO_SETUP", "RADIO_SETUP"},
		{"RADIO_THRO_CH", "Throttle"},
		{"RADIO_ROLL_CH", "Roll"},
		{"RADIO_PITC_CH", "Pitch"},
		{"RADIO_RUDD_CH", "Yaw"},
		{"RADIO_GEAR_CH", "Mode"},
		{"RADIO_FLAP_CH", "Aux1"},
		{"RADIO_AUX2_CH", "Aux2"},
		{"RADIO_AUX3_CH", "Aux3"},
		{"RADIO_AUX4_CH", "Aux4"},
		{"RADIO_AUX5_CH", "Aux5"},
	};
	draw_title(esContext, "RC-Setup");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
	draw_text_button(esContext, "set_rcmap_jr", VIEW_MODE_FCMENU, "[JR-Mapping]", FONT_WHITE, 0.0, 0.7, 0.005, 0.08, 1, 0, mavlink_rcmap_jr, 0.0);
	draw_text_button(esContext, "set_rcmap_futaba", VIEW_MODE_FCMENU, "[Futaba-Mapping]", FONT_WHITE, 0.0, 0.8, 0.005, 0.08, 1, 0, mavlink_rcmap_futaba, 0.0);
}

void screen_mavlink_rccal (ESContext *esContext) {
	char tmp_str[128];
	char tmp_str2[128];
	int16_t row = 0;
	int16_t pn = 0;
	int mav_id = -1;
	draw_title(esContext, "RC-Calibration");
	for (pn = 0; pn < 8; pn++) {
			mav_id = mavlink_get_id_by_name("RC8_MIN");
			if (mav_id != -1) {
				float min = 800;
				float max = 2200;
				float value = ModelData[ModelActive].radio_raw[pn];
				sprintf(tmp_str, "RC%i_MIN", pn + 1);
				float minv = MavLinkVars[ModelActive][mavlink_get_id_by_name(tmp_str)].value;
				sprintf(tmp_str, "RC%i_MAX", pn + 1);
				float maxv = MavLinkVars[ModelActive][mavlink_get_id_by_name(tmp_str)].value;
				if (mavlink_view_rccal == 1) {
					if (cal_min[pn] > value) {
						cal_min[pn] = value;
					}
					if (cal_max[pn] < value) {
						cal_max[pn] = value;
					}
					minv = cal_min[pn];
					maxv = cal_max[pn];
				} else {
					cal_min[pn] = 1250;
					cal_max[pn] = 1750;
				}
				sprintf(tmp_str, "mv_sel_RC%iMIN_t", pn + 1);
				sprintf(tmp_str2, "Channel%i", pn + 1);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.8 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_param_menu, (float)(mav_id));
				sprintf(tmp_str, "mv_sel_RC%iMIN_v", pn + 1);
				sprintf(tmp_str2, "%0.2f", value);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.8 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_param_menu, (float)(mav_id));
				sprintf(tmp_str, "SRC%iMIN", pn + 1);
				draw_box_f3c2(esContext, SLIDER_START, -0.8 + row * 0.14, 0.001, SLIDER_START + SLIDER_LEN, -0.8 + row * 0.14 + 0.1, 0.001, 55, 55, 55, 220, 75, 45, 85, 100);
				draw_box_f3c2(esContext, SLIDER_START + ((value - min) * SLIDER_LEN / (max - min)) - 0.004, -0.8 + row * 0.14, 0.001, SLIDER_START + ((value - min) * SLIDER_LEN / (max - min)) + 0.004, -0.8 + row * 0.14 + 0.1, 0.001, 255, 255, 55, 255, 255, 255, 255, 255);
				draw_box_f3c2(esContext, SLIDER_START, -0.8 + row * 0.14, 0.001, SLIDER_START + ((minv - min) * SLIDER_LEN / (max - min)), -0.8 + row * 0.14 + 0.1, 0.001, 255, 255, 55, 220, 255, 85, 85, 100);
				draw_box_f3c2(esContext, SLIDER_START + ((maxv - min) * SLIDER_LEN / (max - min)), -0.8 + row * 0.14, 0.001, SLIDER_START + SLIDER_LEN, -0.8 + row * 0.14 + 0.1, 0.001, 255, 255, 55, 220, 255, 85, 85, 100);
				set_button(tmp_str, setup.view_mode, SLIDER_START, -0.8 + row * 0.14, SLIDER_START + SLIDER_LEN, -0.8 + row * 0.14 + 0.1, mavlink_slider_move, (float)row, 1);
				if (pn < 4) { 
					if (pn == 0) { 
						sprintf(tmp_str, "RCMAP_ROLL");
					} else if (pn == 1) { 
						sprintf(tmp_str, "RCMAP_PITCH");
					} else if (pn == 2) { 
						sprintf(tmp_str, "RCMAP_THROTTLE");
					} else if (pn == 3) { 
						sprintf(tmp_str, "RCMAP_YAW");
					}
					uint8_t map = MavLinkVars[ModelActive][mavlink_get_id_by_name(tmp_str)].value;
					sprintf(tmp_str, "SRC%iMAP", pn + 1);
					sprintf(tmp_str2, "IN%i", map);
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, SLIDER_START + SLIDER_LEN + 0.01, -0.8 + row * 0.14, 0.002, 0.06, 0, 0, mavlink_channel_select_change, (float)(pn + 1));
				}
			}
			row++;
	}
	if (mavlink_view_rccal == 1) {
		draw_text_button(esContext, "rccalchange", VIEW_MODE_FCMENU, "[CAL]", FONT_GREEN, -1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_view_rccal_change, 0.0);
		draw_text_button(esContext, "rccalsave", VIEW_MODE_FCMENU, "[SAVE]", FONT_GREEN, 0.0, 0.9, 0.002, 0.06, 1, 0, mavlink_view_rccal_save, 0.0);
	} else {
		draw_text_button(esContext, "rccalchange", VIEW_MODE_FCMENU, "[CAL]", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_view_rccal_change, 0.0);
	}
	if (mavlink_channel_select_num != 0) {
		if (mavlink_channel_select == 1) { 
			sprintf(tmp_str, "RCMAP_ROLL");
		} else if (mavlink_channel_select == 2) { 
			sprintf(tmp_str, "RCMAP_PITCH");
		} else if (mavlink_channel_select == 3) { 
			sprintf(tmp_str, "RCMAP_THROTTLE");
		} else if (mavlink_channel_select == 4) { 
			sprintf(tmp_str, "RCMAP_YAW");
		}
		int selected = mavlink_get_id_by_name(tmp_str);
		MavLinkVars[ModelActive][selected].value = (float)mavlink_channel_select_num;
		mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
		mavlink_channel_select = 0;
		mavlink_channel_select_num = 0;
	} else if (mavlink_channel_select != 0) {
		row = 0;
		reset_buttons();
		draw_box_f3(esContext, -0.8, -0.85 + 0 * 0.14, 0.004, 0.8, -0.85 + 4 * 0.14 + 0.1, 0.004, 128, 128, 200, 200);
		for (pn = 0; pn < 4; pn++) {
			sprintf(tmp_str, "Input %i", pn + 1);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_channel_select_set, (float)(pn + 1));
			row++;
		}
	}
}

uint8_t mavlink_magcal_start (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	// AQ-DIMU
	mavlink_send_cmd_calibration_mag_aq(ModelActive);
	return 0;
}

uint8_t mavlink_magcal_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (data < 0.0) {
		mavlink_magcal = 0;
		mavlink_magcal_set = 0;
	} else if (data > 0.0) {
		mavlink_magcal = (uint8_t)data;
		mavlink_magcal_set = 0;
		if (mavlink_magcal == 1) {
			SDL_Log("magcal: reset offesets\n");
			mavlink_send_value(ModelActive, "COMPASS_OFS_X", 0.0, 9);
			SDL_Delay(100);
			mavlink_send_value(ModelActive, "COMPASS_OFS_Y", 0.0, 9);
			SDL_Delay(100);
			mavlink_send_value(ModelActive, "COMPASS_OFS_Z", 0.0, 9);
			SDL_Delay(100);
			mavlink_send_value(ModelActive, "COMPASS_OFS2_X", 0.0, 9);
			SDL_Delay(100);
			mavlink_send_value(ModelActive, "COMPASS_OFS2_Y", 0.0, 9);
			SDL_Delay(100);
			mavlink_send_value(ModelActive, "COMPASS_OFS2_Z", 0.0, 9);
			SDL_Delay(100);
		}
	} else {
		mavlink_magcal_set = 1;
	}
	reset_buttons();
	return 0;
}

uint8_t mavlink_mag_dec_inc (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	char tmp_str[1024];
	int ret_dd = 0;
	int ret_dm = 0;
	int ret_id = 0;
	int ret_im = 0;
	get_declination(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt, &ret_dd, &ret_dm, &ret_id, &ret_im);
	sprintf(tmp_str, "%i.%2.0i", ret_dd, ret_dm * 100 / 60);
	mavlink_send_value(ModelActive, "IMU_MAG_DECL", atof(tmp_str), 9);
	SDL_Delay(100);
	sprintf(tmp_str, "%i.%2.0i", ret_id, ret_im * 100 / 60);
	mavlink_send_value(ModelActive, "IMU_MAG_INCL", -atof(tmp_str), 9);
	SDL_Delay(100);
	return 0;
}


void screen_mavlink_magcal_aq (ESContext *esContext) {
	paralist plist[] = {
		{"IMU_MAG_DECL", "Declination"},
		{"IMU_MAG_INCL", "Inclination"},
	};
	draw_title(esContext, "Compass-Calibration");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
	draw_text_button(esContext, "set_dec_inc", VIEW_MODE_FCMENU, "[Set Declination/Inclination]", FONT_WHITE, 0.0, 0.8, 0.005, 0.08, 1, 0, mavlink_mag_dec_inc, 0.0);
}

void screen_mavlink_magcal (ESContext *esContext) {
	paralist plist[] = {
		{"MAG_ENABLE", ""},
		{"---", "---"},
		{"COMPASS_ORIENT", "Orientation"},
		{"---", "---"},
		{"COMPASS_DEC", ""},
		{"COMPASS_AUTODEC", ""},
		{"---", "---"},
		{"COMPASS_OFS_X", "X-Axis"},
		{"COMPASS_OFS_Y", "Y-Axis"},
		{"COMPASS_OFS_Z", "Z-Axis"},
		{"---", "---"},
		{"COMPASS_OFS2_X", "X2-Axis"},
		{"COMPASS_OFS2_Y", "Y2-Axis"},
		{"COMPASS_OFS2_Z", "Z2-Axis"},
//		{"---", "---"},
//		{"COMPASS_LEARN", ""},
//		{"COMPASS_EXTERNAL", ""},
	};
	draw_title(esContext, "Compass-Calibration");

	static int mag_pos = 0;
	static float mag_data[500][3];
	static int mag2_pos = 0;
	static float mag2_data[500][3];
	if (mavlink_magcal > 0) {
		int n = 0;
		static float last_x = 0.0;
		static float last_y = 0.0;
		static float last_z = 0.0;
		float minX = 0.0;
		float minY = 0.0;
		float minZ = 0.0;
		float maxX = 0.0;
		float maxY = 0.0;
		float maxZ = 0.0;
		if (last_x != ModelData[ModelActive].mag_x || last_y != ModelData[ModelActive].mag_y || last_z != ModelData[ModelActive].mag_z) {
			if (mag_pos < 500) {
				mag_data[mag_pos][0] = ModelData[ModelActive].mag_x;
				mag_data[mag_pos][1] = ModelData[ModelActive].mag_y;
				mag_data[mag_pos][2] = ModelData[ModelActive].mag_z;
				mag_pos++;
			}
			last_x = ModelData[ModelActive].mag_x;
			last_y = ModelData[ModelActive].mag_y;
			last_z = ModelData[ModelActive].mag_z;
		}

		static float last2_x = 0.0;
		static float last2_y = 0.0;
		static float last2_z = 0.0;
		float min2X = 0.0;
		float min2Y = 0.0;
		float min2Z = 0.0;
		float max2X = 0.0;
		float max2Y = 0.0;
		float max2Z = 0.0;
		if (last2_x != ModelData[ModelActive].mag2_x || last2_y != ModelData[ModelActive].mag2_y || last2_z != ModelData[ModelActive].mag2_z) {
			if (mag2_pos < 500) {
				mag2_data[mag2_pos][0] = ModelData[ModelActive].mag2_x;
				mag2_data[mag2_pos][1] = ModelData[ModelActive].mag2_y;
				mag2_data[mag2_pos][2] = ModelData[ModelActive].mag2_z;
				mag2_pos++;
			}
			last2_x = ModelData[ModelActive].mag2_x;
			last2_y = ModelData[ModelActive].mag2_y;
			last2_z = ModelData[ModelActive].mag2_z;
		}

		static float rot_x = 20.0;
		static float rot_y = 20.0;
		static float rot_z = 20.0;
//		rot_x += 0.14;
		rot_y += 0.23;
//		rot_z += 0.11;
#ifdef SDLGL
#ifndef ANDROID
		glPushMatrix();
		glRotatef(rot_x, 1.0, 0.0, 0.0);
		glRotatef(rot_y, 0.0, 1.0, 0.0);
		glRotatef(rot_z, 0.0, 0.0, 1.0);
		glLineWidth(1);
		glBegin(GL_LINES);
#endif
#endif
		for (n = 0; n < mag_pos; n++) {
#ifdef SDLGL
#ifndef ANDROID
			glColor4f(1.0, 0.0, 0.0, 0.3);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(mag_data[n][0] / 500.0, mag_data[n][1] / 500.0, mag_data[n][2] / 500.0);
#endif
#endif
			if (minX > mag_data[n][0]) {
				minX = mag_data[n][0];
			}
			if (minY > mag_data[n][1]) {
				minY = mag_data[n][1];
			}
			if (minZ > mag_data[n][2]) {
				minZ = mag_data[n][2];
			}
			if (maxX < mag_data[n][0]) {
				maxX = mag_data[n][0];
			}
			if (maxY < mag_data[n][1]) {
				maxY = mag_data[n][1];
			}
			if (maxZ < mag_data[n][2]) {
				maxZ = mag_data[n][2];
			}
		}
		for (n = 0; n < mag2_pos; n++) {
#ifdef SDLGL
#ifndef ANDROID
			glColor4f(1.0, 0.0, 1.0, 0.3);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(mag2_data[n][0] / 500.0, mag2_data[n][1] / 500.0, mag2_data[n][2] / 500.0);
#endif
#endif
			if (min2X > mag2_data[n][0]) {
				min2X = mag2_data[n][0];
			}
			if (min2Y > mag2_data[n][1]) {
				min2Y = mag2_data[n][1];
			}
			if (min2Z > mag2_data[n][2]) {
				min2Z = mag2_data[n][2];
			}
			if (max2X < mag2_data[n][0]) {
				max2X = mag2_data[n][0];
			}
			if (max2Y < mag2_data[n][1]) {
				max2Y = mag2_data[n][1];
			}
			if (max2Z < mag2_data[n][2]) {
				max2Z = mag2_data[n][2];
			}
		}
#ifndef ANDROID
		glEnd();
#endif
		float offsetX = maxX - (maxX - minX) / 2.0;
		float offsetY = maxY - (maxY - minY) / 2.0;
		float offsetZ = maxZ - (maxZ - minZ) / 2.0;
		float scaleX = 600.0 / (maxX - minX);
		float scaleY = 600.0 / (maxY - minY);
		float scaleZ = 600.0 / (maxZ - minZ);
		if (mavlink_magcal == 2) {
			offsetX = 0.0;
			offsetY = 0.0;
			offsetZ = 0.0;
		}
		float offset2X = max2X - (max2X - min2X) / 2.0;
		float offset2Y = max2Y - (max2Y - min2Y) / 2.0;
		float offset2Z = max2Z - (max2Z - min2Z) / 2.0;
		float scale2X = 600.0 / (max2X - min2X);
		float scale2Y = 600.0 / (max2Y - min2Y);
		float scale2Z = 600.0 / (max2Z - min2Z);
		if (mavlink_magcal == 2) {
			offset2X = 0.0;
			offset2Y = 0.0;
			offset2Z = 0.0;
		}

#ifdef SDLGL
#ifndef ANDROID
		glLineWidth(5);
		glBegin(GL_LINES);
		for (n = 0; n < mag_pos; n++) {
			glColor4f(0.0, 1.0, 0.0, 0.3);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f((mag_data[n][0] - offsetX) / 500.0 * scaleX, (mag_data[n][1] - offsetY) / 500.0 * scaleY, (mag_data[n][2] - offsetZ) / 500.0 * scaleZ);
			glColor4f(0.0, 1.0, 0.0, 1.0);
			glVertex3f((mag_data[n][0] - offsetX) / 500.0 * scaleX - 0.01, (mag_data[n][1] - offsetY) / 500.0 * scaleY, (mag_data[n][2] - offsetZ) / 500.0 * scaleZ);
			glVertex3f((mag_data[n][0] - offsetX) / 500.0 * scaleX + 0.01, (mag_data[n][1] - offsetY) / 500.0 * scaleY, (mag_data[n][2] - offsetZ) / 500.0 * scaleZ);
			glVertex3f((mag_data[n][0] - offsetX) / 500.0 * scaleX, (mag_data[n][1] - offsetY) / 500.0 * scaleY - 0.01, (mag_data[n][2] - offsetZ) / 500.0 * scaleZ);
			glVertex3f((mag_data[n][0] - offsetX) / 500.0 * scaleX, (mag_data[n][1] - offsetY) / 500.0 * scaleY + 0.01, (mag_data[n][2] - offsetZ) / 500.0 * scaleZ);
			glVertex3f((mag_data[n][0] - offsetX) / 500.0 * scaleX, (mag_data[n][1] - offsetY) / 500.0 * scaleY, (mag_data[n][2] - offsetZ) / 500.0 * scaleZ - 0.01);
			glVertex3f((mag_data[n][0] - offsetX) / 500.0 * scaleX, (mag_data[n][1] - offsetY) / 500.0 * scaleY, (mag_data[n][2] - offsetZ) / 500.0 * scaleZ + 0.01);
		}
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f((last_x - offsetX) / 500.0 * scaleX, (last_y - offsetY) / 500.0 * scaleY, (last_z - offsetZ) / 500.0 * scaleZ);

		if (mag2_pos > 1) {
			for (n = 0; n < mag2_pos; n++) {
				glColor4f(0.0, 1.0, 1.0, 0.3);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f((mag2_data[n][0] - offset2X) / 500.0 * scale2X, (mag2_data[n][1] - offset2Y) / 500.0 * scale2Y, (mag2_data[n][2] - offset2Z) / 500.0 * scale2Z);
				glColor4f(0.0, 1.0, 1.0, 1.0);
				glVertex3f((mag2_data[n][0] - offset2X) / 500.0 * scale2X - 0.01, (mag2_data[n][1] - offset2Y) / 500.0 * scale2Y, (mag2_data[n][2] - offset2Z) / 500.0 * scale2Z);
				glVertex3f((mag2_data[n][0] - offset2X) / 500.0 * scale2X + 0.01, (mag2_data[n][1] - offset2Y) / 500.0 * scale2Y, (mag2_data[n][2] - offset2Z) / 500.0 * scale2Z);
				glVertex3f((mag2_data[n][0] - offset2X) / 500.0 * scale2X, (mag2_data[n][1] - offset2Y) / 500.0 * scale2Y - 0.01, (mag2_data[n][2] - offset2Z) / 500.0 * scale2Z);
				glVertex3f((mag2_data[n][0] - offset2X) / 500.0 * scale2X, (mag2_data[n][1] - offset2Y) / 500.0 * scale2Y + 0.01, (mag2_data[n][2] - offset2Z) / 500.0 * scale2Z);
				glVertex3f((mag2_data[n][0] - offset2X) / 500.0 * scale2X, (mag2_data[n][1] - offset2Y) / 500.0 * scale2Y, (mag2_data[n][2] - offset2Z) / 500.0 * scale2Z - 0.01);
				glVertex3f((mag2_data[n][0] - offset2X) / 500.0 * scale2X, (mag2_data[n][1] - offset2Y) / 500.0 * scale2Y, (mag2_data[n][2] - offset2Z) / 500.0 * scale2Z + 0.01);
			}
			glColor4f(0.5, 0.5, 0.5, 1.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f((last2_x - offset2X) / 500.0 * scale2X, (last2_y - offset2Y) / 500.0 * scale2Y, (last2_z - offset2Z) / 500.0 * scale2Z);
		}

		glEnd();
		glLineWidth(1);
		glColor4f(1.0, 1.0, 0.0, 0.7);
		float angleA = 0.0;
		float angleB = 0.0;
		float step = 9.0;
		float v[10000][3];
		glBegin(GL_LINE_STRIP);
		for (angleA = -90.0f; angleA <90.0f; angleA += step) {
			int	n = 0;
			float r1 = (float)cos(angleA * PI / 180.0);
			float r2 = (float)cos((angleA + step) * PI / 180.0);
			float h1 = (float)sin(angleA * PI / 180.0);
			float h2 = (float)sin((angleA + step) * PI / 180.0);
			for (angleB = 0.0f; angleB <= 360.0f; angleB += step) {
				float fcos = (float)cos(angleB * PI / 180.0);
				float fsin = -(float)sin(angleB * PI / 180.0);
				v[n][0] = (r2 * fcos) * 0.6;
				v[n][1] = (h2) * 0.6;
				v[n][2] = (r2 * fsin) * 0.6;
				v[n + 1][0] = (r1 * fcos) * 0.6;
				v[n + 1][1] = (h1) * 0.6;
				v[n + 1][2] = (r1 * fsin) * 0.6;
				glVertex3f(v[n][0], v[n][1], v[n][2]);
				glVertex3f(v[n + 1][0], v[n + 1][1], v[n + 1][2]);
				n += 2;  
				if (n>31){
					n = 0;
					angleB -= step;
				}
			}
		}
		glEnd();
		glPopMatrix();
		float diff_x = 1.0;
		float diff_y = 0.6;
		glBegin(GL_LINES);
		for (n = 0; n < mag_pos; n++) {
			glColor4f(0.0, 1.0, 0.0, 0.3);
			glVertex3f(-diff_x, -diff_y, 0.0);
			glVertex3f((mag_data[n][0] - offsetX) / 1000.0 * scaleX - diff_x, (mag_data[n][1] - offsetY) / 1000.0 * scaleY - diff_y, 0.0);
			glVertex3f(-diff_x, diff_y, 0.0);
			glVertex3f((mag_data[n][0] - offsetX) / 1000.0 * scaleX - diff_x, (mag_data[n][2] - offsetZ) / 1000.0 * scaleZ + diff_y, 0.0);
			glVertex3f(diff_x, -diff_y, 0.0);
			glVertex3f((mag_data[n][2] - offsetZ) / 1000.0 * scaleZ + diff_x, (mag_data[n][1] - offsetY) / 1000.0 * scaleY - diff_y, 0.0);
			glColor4f(1.0, 0.0, 0.0, 0.3);
			glVertex3f(-diff_x, -diff_y, 0.0);
			glVertex3f((mag_data[n][0]) / 1000.0 - diff_x, (mag_data[n][1]) / 1000.0 - diff_y, 0.0);
			glVertex3f(-diff_x, diff_y, 0.0);
			glVertex3f((mag_data[n][0]) / 1000.0 - diff_x, (mag_data[n][2]) / 1000.0 + diff_y, 0.0);
			glVertex3f(diff_x, -diff_y, 0.0);
			glVertex3f((mag_data[n][2]) / 1000.0 + diff_x, (mag_data[n][1]) / 1000.0 - diff_y, 0.0);
		}
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex3f(-diff_x, -diff_y, 0.0);
		glVertex3f((last_x - offsetX) / 1000.0 * scaleX - diff_x, (last_y - offsetY) / 1000.0 * scaleY - diff_y, 0.0);
		glVertex3f(-diff_x, diff_y, 0.0);
		glVertex3f((last_x - offsetX) / 1000.0 * scaleX - diff_x, (last_z - offsetZ) / 1000.0 * scaleZ + diff_y, 0.0);
		glVertex3f(diff_x, -diff_y, 0.0);
		glVertex3f((last_z - offsetZ) / 1000.0 * scaleZ + diff_x, (last_y - offsetY) / 1000.0 * scaleY - diff_y, 0.0);
		if (mag2_pos > 1) {
			for (n = 0; n < mag2_pos; n++) {
				glColor4f(0.0, 1.0, 1.0, 0.3);
				glVertex3f(-diff_x, -diff_y, 0.0);
				glVertex3f((mag2_data[n][0] - offset2X) / 1000.0 * scale2X - diff_x, (mag2_data[n][1] - offset2Y) / 1000.0 * scale2Y - diff_y, 0.0);
				glVertex3f(-diff_x, diff_y, 0.0);
				glVertex3f((mag2_data[n][0] - offset2X) / 1000.0 * scale2X - diff_x, (mag2_data[n][2] - offset2Z) / 1000.0 * scale2Z + diff_y, 0.0);
				glVertex3f(diff_x, -diff_y, 0.0);
				glVertex3f((mag2_data[n][2] - offset2Z) / 1000.0 * scale2Z + diff_x, (mag2_data[n][1] - offset2Y) / 1000.0 * scale2Y - diff_y, 0.0);
				glColor4f(1.0, 0.0, 1.0, 0.3);
				glVertex3f(-diff_x, -diff_y, 0.0);
				glVertex3f((mag2_data[n][0]) / 1000.0 - diff_x, (mag2_data[n][1]) / 1000.0 - diff_y, 0.0);
				glVertex3f(-diff_x, diff_y, 0.0);
				glVertex3f((mag2_data[n][0]) / 1000.0 - diff_x, (mag2_data[n][2]) / 1000.0 + diff_y, 0.0);
				glVertex3f(diff_x, -diff_y, 0.0);
				glVertex3f((mag2_data[n][2]) / 1000.0 + diff_x, (mag2_data[n][1]) / 1000.0 - diff_y, 0.0);
			}
			glColor4f(0.5, 0.5, 0.5, 1.0);
			glVertex3f(-diff_x, -diff_y, 0.0);
			glVertex3f((last2_x - offset2X) / 1000.0 * scale2X - diff_x, (last2_y - offset2Y) / 1000.0 * scale2Y - diff_y, 0.0);
			glVertex3f(-diff_x, diff_y, 0.0);
			glVertex3f((last2_x - offset2X) / 1000.0 * scale2X - diff_x, (last2_z - offset2Z) / 1000.0 * scale2Z + diff_y, 0.0);
			glVertex3f(diff_x, -diff_y, 0.0);
			glVertex3f((last2_z - offset2Z) / 1000.0 * scale2Z + diff_x, (last2_y - offset2Y) / 1000.0 * scale2Y - diff_y, 0.0);
		}
		glEnd();
		draw_circle_f3(esContext, -diff_x, -diff_y, 0.0002, 0.3, 255, 255, 255, 255);
		draw_circle_f3(esContext, -diff_x, diff_y, 0.0002, 0.3, 255, 255, 255, 255);
		draw_circle_f3(esContext, diff_x, diff_y, 0.0002, 0.3, 255, 255, 255, 255);

		if (mavlink_magcal == 1) {
			char tmp_str[1024];
			sprintf(tmp_str, "# %i", mag_pos);
			draw_text_f(esContext, diff_x - 0.2, -diff_y - 0.2, 0.08, 0.08, FONT_WHITE, tmp_str);
			sprintf(tmp_str, "X %0.2f", -offsetX);
			draw_text_f(esContext, diff_x - 0.2, -diff_y - 0.1, 0.08, 0.08, FONT_WHITE, tmp_str);
			sprintf(tmp_str, "Y %0.2f", -offsetY);
			draw_text_f(esContext, diff_x - 0.2, -diff_y, 0.08, 0.08, FONT_WHITE, tmp_str);
			sprintf(tmp_str, "Z %0.2f", -offsetZ);
			draw_text_f(esContext, diff_x - 0.2, -diff_y + 0.1, 0.08, 0.08, FONT_WHITE, tmp_str);
			if (mag2_pos > 1) {
				sprintf(tmp_str, "# %i", mag2_pos);
				draw_text_f(esContext, diff_x - 0.2, -diff_y + 0.3, 0.08, 0.08, FONT_WHITE, tmp_str);
				sprintf(tmp_str, "X2 %0.2f", -offset2X);
				draw_text_f(esContext, diff_x - 0.2, -diff_y + 0.4, 0.08, 0.08, FONT_WHITE, tmp_str);
				sprintf(tmp_str, "Y2 %0.2f", -offset2Y);
				draw_text_f(esContext, diff_x - 0.2, -diff_y + 0.5, 0.08, 0.08, FONT_WHITE, tmp_str);
				sprintf(tmp_str, "Z2 %0.2f", -offset2Z);
				draw_text_f(esContext, diff_x - 0.2, -diff_y + 0.6, 0.08, 0.08, FONT_WHITE, tmp_str);
			}
		}
#endif
#endif
		if (mavlink_magcal_set == 1) {
			if (mavlink_magcal == 1) {
				SDL_Log("magcal: save offesets\n");
/*
				if (ModelData[ModelActive].pilottype == MAV_AUTOPILOT_PIXHAWK) {
					mavlink_send_value(ModelActive, "COMPASS_OFS_X", -offsetX, 9);
					mavlink_send_value(ModelActive, "COMPASS_OFS_Y", offsetZ, 9);
					mavlink_send_value(ModelActive, "COMPASS_OFS_Z", offsetY, 9);
					mavlink_send_magcal(ModelActive, -offsetX, offsetZ, offsetY);
				} else {
					mavlink_send_value(ModelActive, "COMPASS_OFS_X", -offsetX, 9);
					mavlink_send_value(ModelActive, "COMPASS_OFS_Y", offsetZ, 9);
					mavlink_send_value(ModelActive, "COMPASS_OFS_Z", offsetY, 9);
					mavlink_send_magcal(ModelActive, -offsetX, offsetZ, offsetY);
				}
				if (mag2_pos > 1) {
					mavlink_send_value(ModelActive, "COMPASS_OFS2_X", -offset2X, 9);
					mavlink_send_value(ModelActive, "COMPASS_OFS2_Y", -offset2Y, 9);
					mavlink_send_value(ModelActive, "COMPASS_OFS2_Z", -offset2Z, 9);
					mavlink_send_magcal2(ModelActive, -offset2X, -offset2Y, -offset2Z);
				}
* */
			}
			mavlink_magcal_set = 0;
			mavlink_magcal = 0;
		}
		if (mavlink_magcal == 1 && mag_pos > 100) {
			draw_text_button(esContext, "save_cal", VIEW_MODE_FCMENU, "[SAVE]", FONT_GREEN, 0.0, 0.7, 0.005, 0.08, 1, 0, mavlink_magcal_change, 0.0);
		}
		draw_text_button(esContext, "cancle_cal", VIEW_MODE_FCMENU, "[CANCEL]", FONT_GREEN, 0.0, 0.8, 0.005, 0.08, 1, 0, mavlink_magcal_change, -1.0);
	} else {
		screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
		if (ModelData[ModelActive].pilottype == MAV_AUTOPILOT_AUTOQUAD) {
			draw_text_button(esContext, "start_cal", VIEW_MODE_FCMENU, "[DIMU-Calibration]", FONT_WHITE, 0.0, 0.8, 0.005, 0.08, 1, 0, mavlink_magcal_start, 0.0);
		} else {
			draw_text_button(esContext, "start_test", VIEW_MODE_FCMENU, "[TEST]", FONT_WHITE, 0.0, 0.7, 0.005, 0.08, 1, 0, mavlink_magcal_change, 2.0);
			draw_text_button(esContext, "start_cal", VIEW_MODE_FCMENU, "[Calibration]", FONT_WHITE, 0.0, 0.8, 0.005, 0.08, 1, 0, mavlink_magcal_change, 1.0);
		}
		mag_pos = 0;
	}
}

void screen_mavlink_camrelay (ESContext *esContext) {
	paralist plist[] = {
		{"MNT_MODE", "Gimbal Mode"},
		{"MNT_RC_IN_ROLL", "Gimbal RC-Roll"},
		{"MNT_RC_IN_TILT", "Gimbal RC-Tilt"},
		{"MNT_RC_IN_PAN", "Gimbal RC-Pan"},
		{"---", "---"},
		{"CAM_TRIGG_TYPE", "Cam Trigger-Type"},
		{"CAM_DURATION", "Cam Duration"},
		{"CAM_SERVO_ON", "Cam Trigger-On"},
		{"CAM_SERVO_OFF", "Cam Trigger-Off"},
		{"CAM_TRIGG_DIST", "Cam Trigger-Distance"},
		{"---", "---"},
		{"RELAY_PIN", "Relay-Pin"},
	};

	draw_title(esContext, "Gimbal/Cam/Relay");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));

	int row	 = 0;
	char tmp_str[1024];
	int pn = 0;
	int trigger = 0;
	int pan = -1;
	int tilt = -1;
	int roll = -1;
	for (pn = 0; pn < 11; pn++) {
			sprintf(tmp_str, "RC%i_FUNCTION", pn + 1);
			int selected = mavlink_get_id_by_name(tmp_str);
			if ((int)MavLinkVars[ModelActive][selected].value == 6) {
				pan = pn;
			} else if ((int)MavLinkVars[ModelActive][selected].value == 7) {
				tilt = pn;
			} else if ((int)MavLinkVars[ModelActive][selected].value == 8) {
				roll = pn;
			} else if ((int)MavLinkVars[ModelActive][selected].value == 10) {
				trigger = pn;
			}
	}
	sprintf(tmp_str, "TRIG OUT=%i", trigger + 1);
	if (mavlink_channel_select == 1) {
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, -0.9, 0.65, 0.005, 0.08, 1, 0, mavlink_channel_select_change, (float)(0));
	} else {
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -0.9, 0.65, 0.005, 0.08, 1, 0, mavlink_channel_select_change, (float)(1));
	}
	sprintf(tmp_str, "PAN OUT=%i", pan + 1);
	if (mavlink_channel_select == 2) {
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, -0.3, 0.65, 0.005, 0.08, 1, 0, mavlink_channel_select_change, (float)(0));
	} else {
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -0.3, 0.65, 0.005, 0.08, 1, 0, mavlink_channel_select_change, (float)(2));
	}
	sprintf(tmp_str, "TILT OUT=%i", tilt + 1);
	if (mavlink_channel_select == 3) {
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, 0.3, 0.65, 0.005, 0.08, 1, 0, mavlink_channel_select_change, (float)(0));
	} else {
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.3, 0.65, 0.005, 0.08, 1, 0, mavlink_channel_select_change, (float)(3));
	}
	sprintf(tmp_str, "ROLL OUT=%i", roll + 1);
	if (mavlink_channel_select == 4) {
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, 0.9, 0.65, 0.005, 0.08, 1, 0, mavlink_channel_select_change, (float)(0));
	} else {
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.9, 0.65, 0.005, 0.08, 1, 0, mavlink_channel_select_change, (float)(4));
	}
	if (mavlink_channel_select_num != 0) {
		printf("%i  %i\n", mavlink_channel_select, mavlink_channel_select_num);
		for (pn = 4; pn < 11; pn++) {
				sprintf(tmp_str, "RC%i_FUNCTION", pn + 1);
				int selected = mavlink_get_id_by_name(tmp_str);
				if (mavlink_channel_select == 1) {
					if (pn == mavlink_channel_select_num - 1) {
						MavLinkVars[ModelActive][selected].value = (float)10;
						mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
					} else if ((int)MavLinkVars[ModelActive][selected].value == 10) {
						MavLinkVars[ModelActive][selected].value = (float)0;
						mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
					}
				} else if (mavlink_channel_select == 2) {
					if (pn == mavlink_channel_select_num - 1) {
						MavLinkVars[ModelActive][selected].value = (float)6;
						mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
					} else if ((int)MavLinkVars[ModelActive][selected].value == 6) {
						MavLinkVars[ModelActive][selected].value = (float)0;
						mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
					}
				} else if (mavlink_channel_select == 3) {
					if (pn == mavlink_channel_select_num - 1) {
						MavLinkVars[ModelActive][selected].value = (float)7;
						mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
					} else if ((int)MavLinkVars[ModelActive][selected].value == 7) {
						MavLinkVars[ModelActive][selected].value = (float)0;
						mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
					}
				} else if (mavlink_channel_select == 4) {
					if (pn == mavlink_channel_select_num - 1) {
						MavLinkVars[ModelActive][selected].value = (float)8;
						mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
					} else if ((int)MavLinkVars[ModelActive][selected].value == 8) {
						MavLinkVars[ModelActive][selected].value = (float)0;
						mavlink_send_value(ModelActive, MavLinkVars[ModelActive][selected].name, MavLinkVars[ModelActive][selected].value, MavLinkVars[ModelActive][selected].type);
					}
				}
		}
		mavlink_channel_select = 0;
		mavlink_channel_select_num = 0;
	} else if (mavlink_channel_select != 0) {
		row = 0;
		draw_box_f3(esContext, -0.8, -0.85 + 0 * 0.14, 0.004, 0.8, -0.85 + 8 * 0.14 + 0.1, 0.004, 128, 128, 200, 200);
		draw_text_button(esContext, "DISABLE", VIEW_MODE_FCMENU, "DISABLE", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_channel_select_set, (float)(-1));
		row++;
		for (pn = 4; pn < 11; pn++) {
			sprintf(tmp_str, "RC%i_FUNCTION", pn + 1);
			int selected = mavlink_get_id_by_name(tmp_str);
			if (selected != -1) {
				sprintf(tmp_str, "Output %i", pn + 1);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_channel_select_set, (float)(pn + 1));
			}
			row++;
		}
	}
}

void screen_mavlink_acccal (ESContext *esContext) {
	draw_title(esContext, "ACC-Calibration");
	if (strncmp(message_txt, "Calibration", 11) == 0) {
		draw_text_button(esContext, "acccalmsg", VIEW_MODE_FCMENU, message_txt, FONT_WHITE, 0.0, 0.0, 0.002, 0.08, 1, 0, mavlink_view_acccal_change, 2.0);
	} else if (strncmp(message_txt, "Place vehicle", 13) == 0) {
		draw_text_button(esContext, "acccalmsg", VIEW_MODE_FCMENU, message_txt, FONT_WHITE, 0.0, 0.0, 0.002, 0.08, 1, 0, mavlink_view_acccal_change, 1.0);
	} else {
		draw_text_button(esContext, "acccalmsg", VIEW_MODE_FCMENU, "Click to start ACC-Calibration", FONT_WHITE, 0.0, 0.0, 0.002, 0.08, 1, 0, mavlink_view_acccal_change, 0.0);
	}
}

void screen_mavlink_logfile (ESContext *esContext) {
	char tmp_str[1024];
	char tmp_str2[1024];
	char filepath[1024];
	int row = 0;
	int n = 0;
	if (mavlink_loghbeat == 255) {
		mavlink_loghbeat = 0;
		draw_title(esContext, "Logfiles (Done)");
	} else if (mavlink_loghbeat > 0) {
		sprintf(tmp_str, "Logfiles (ID:%i %i%%)", mavlink_logid, mavlink_logstat);
		draw_title(esContext, tmp_str);
		sprintf(tmp_str, "downloading logfile ID:%i", mavlink_logid);
		draw_text_button(esContext, "logstat", VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, 0.0, -0.35, 0.005, 0.1, 1, 0, mavlink_read_logfile_get, (float)(-1));
		draw_box_f3c2(esContext, -1.0, -0.25, 0.002, 1.0, 0.05, 0.002, 55, 55, 55, 220, 75, 45, 85, 100);
		draw_box_f3c2(esContext, -1.0, -0.25, 0.002, -1.0 + ((float)mavlink_logstat * 2.0 / 100.0), 0.05, 0.002, 255, 255, 55, 220, 175, 145, 85, 100);
		sprintf(tmp_str, "%i%%", mavlink_logstat);
		draw_text_button(esContext, "logstat", VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, 0.0, -0.175, 0.005, 0.1, 1, 0, mavlink_read_logfile_get, (float)(-1));
		sprintf(tmp_str, "%i KB / %i KB", mavlink_loggetsize / 1024, mavlink_logreqsize / 1024);
		draw_text_button(esContext, "logsize", VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, 0.0, -0.075, 0.005, 0.1, 1, 0, mavlink_read_logfile_get, (float)(-1));
		uint32_t dtime = SDL_GetTicks() - mavlink_logstartstamp;
		if (dtime / 1000 > 0) {
			uint32_t bs = mavlink_loggetsize * 1000 / dtime;
			sprintf(tmp_str, "%is (%i Bytes/s)", dtime / 1000, bs);
			draw_text_button(esContext, "logsize", VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, 0.0, 0.15, 0.005, 0.1, 1, 0, mavlink_read_logfile_get, (float)(-1));
			uint32_t remaining_bytes = mavlink_logreqsize - mavlink_loggetsize;
			if (bs > 0) {
				sprintf(tmp_str, "%i KB to get (%is)", remaining_bytes / 1024, remaining_bytes / bs);
				draw_text_button(esContext, "logrem", VIEW_MODE_FCMENU, tmp_str, FONT_GREEN, 0.0, 0.3, 0.005, 0.1, 1, 0, mavlink_read_logfile_get, (float)(-1));
			}
		}
	} else if (mavlink_logs_total > 0) {
		draw_title(esContext, "Logfiles");
		for (n = 0; n < mavlink_logs_total; n++) {
			sprintf(tmp_str, "log_%i", loglist[n].id);
			sprintf(filepath, "/tmp/mavlink_%i_%i.log", loglist[n].id, loglist[n].size);
			if (file_exists(filepath) != 0) {
				sprintf(filepath, "mavlink_%i_%i.log", loglist[n].id, loglist[n].size);
				sprintf(tmp_str2, "logfile %i: %i KB (%s)", loglist[n].id, loglist[n].size / 1024, filepath);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_read_logfile_get, (float)(-1));
			} else {
				sprintf(tmp_str2, "logfile %i: %i KB", loglist[n].id, loglist[n].size / 1024);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_read_logfile_get, (float)(n));
			}
			row++;
		}
	} else {
		draw_text_button(esContext, "loglist_", VIEW_MODE_FCMENU, "[GET LOGFILE LIST]", FONT_WHITE, 0.0, 0.0, 0.002, 0.1, 1, 0, mavlink_read_loglist_get, 1.0);
	}
}


void screen_mavlink_menu (ESContext *esContext) {
	int16_t row = 0;
	int16_t col = 0;
	int16_t row2 = 0;
	int16_t n = 0;
	int16_t n2 = 0;
	int n3 = 0;
	char tmp_str[1024];
	char tmp_str2[1024];
	int8_t flag = 0;
	int8_t flag2 = 0;
	static char main_groups[MAVLINK_PARAMETER_MAX][1024];

	draw_text_button(esContext, "ml_screen", VIEW_MODE_FCMENU, "[MAIN]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, 1, 0, mavlink_view_screen_change, -1.0);

	draw_text_button(esContext, "load", VIEW_MODE_FCMENU, "[LOAD FILE]", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_param_load, 1.0);
	draw_text_button(esContext, "save", VIEW_MODE_FCMENU, "[SAVE FILE]", FONT_WHITE, -0.5, 0.9, 0.002, 0.06, 1, 0, mavlink_param_save, 1.0);
//	draw_text_button(esContext, "upload", VIEW_MODE_FCMENU, "[UPLOAD ALL]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_param_upload_all, 1.0);
	if (ModelData[ModelActive].teletype != TELETYPE_ARDUPILOT && ModelData[ModelActive].teletype != TELETYPE_MEGAPIRATE_NG) {
		draw_text_button(esContext, "flash_r", VIEW_MODE_FCMENU, "[LOAD FLASH]", FONT_WHITE, 0.5, 0.9, 0.002, 0.06, 1, 0, mavlink_flashload, 0.0);
		draw_text_button(esContext, "flash_w", VIEW_MODE_FCMENU, "[WRITE FLASH]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_flash, 0.0);
	}

	if (param_menu == -1 && bits_menu == -1 && option_menu == -1) {
		if (mavlink_view_screen == 1) {
			screen_mavlink_stabilize(esContext);
			return;
		} else if (mavlink_view_screen == 2) {
			screen_mavlink_rate(esContext);
			return;
		} else if (mavlink_view_screen == 3) {
			screen_mavlink_loiter(esContext);
			return;
		} else if (mavlink_view_screen == 4) {
			screen_mavlink_throttle(esContext);
			return;
		} else if (mavlink_view_screen == 5) {
			screen_mavlink_flightmodes(esContext);
			return;
		} else if (mavlink_view_screen == 6) {
			if (ModelData[ModelActive].pilottype == MAV_AUTOPILOT_AUTOQUAD) {
				screen_mavlink_rccal_aq(esContext);
			} else {
				screen_mavlink_rccal(esContext);
			}
			return;
		} else if (mavlink_view_screen == 7) {
			screen_mavlink_acccal(esContext);
			return;
		} else if (mavlink_view_screen == 8) {
			if (ModelData[ModelActive].pilottype == MAV_AUTOPILOT_AUTOQUAD) {
				screen_mavlink_magcal_aq(esContext);
			} else {
				screen_mavlink_magcal(esContext);
			}
			return;
		} else if (mavlink_view_screen == 9) {
			screen_mavlink_camrelay(esContext);
			return;
		} else if (mavlink_view_screen == 10) {
			screen_mavlink_logfile(esContext);
			return;
		} else if (mavlink_view_screen == 11) {
			screen_mavlink_mot_aq(esContext);
			return;
		} else if (mavlink_view_screen == 12) {
			screen_mavlink_rate_aq(esContext);
			return;
		} else if (mavlink_view_screen == 13) {
			screen_mavlink_rateyaw_aq(esContext);
			return;
		} else if (mavlink_view_screen == 14) {
			screen_mavlink_stabilize_aq(esContext);
			return;
		} else if (mavlink_view_screen == 15) {
			screen_mavlink_stabilizeyaw_aq(esContext);
			return;
		} else if (mavlink_view_screen == -1) {
			draw_title(esContext, "Mavlink");
			if (ModelData[ModelActive].pilottype == MAV_AUTOPILOT_AUTOQUAD) {
				draw_text_button(esContext, "mlscreen12", VIEW_MODE_FCMENU, "Tilt-Rate-PID", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(12));
				row++;
				draw_text_button(esContext, "mlscreen13", VIEW_MODE_FCMENU, "Yaw-Rate-PID", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(13));
				row++;
				draw_text_button(esContext, "mlscreen14", VIEW_MODE_FCMENU, "Tilt-Angle-PID", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(14));
				row++;
				draw_text_button(esContext, "mlscreen15", VIEW_MODE_FCMENU, "Yaw-Angle-PID", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(15));
				row++;
				draw_text_button(esContext, "mlscreen6", VIEW_MODE_FCMENU, "RC-Calibration", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(6));
				row++;
				draw_text_button(esContext, "mlscreen8", VIEW_MODE_FCMENU, "ACC-Calibration", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(7));
				row++;
				draw_text_button(esContext, "mlscreen7", VIEW_MODE_FCMENU, "Compass-Calibration", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(8));
				row++;
				draw_text_button(esContext, "mlscreen11", VIEW_MODE_FCMENU, "Motors", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(11));
				row++;
			} else {
				draw_text_button(esContext, "mlscreen1", VIEW_MODE_FCMENU, "Stabilize-P", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(1));
				row++;
				draw_text_button(esContext, "mlscreen2", VIEW_MODE_FCMENU, "Rate-PID", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(2));
				row++;
				draw_text_button(esContext, "mlscreen3", VIEW_MODE_FCMENU, "Loiter-PID", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(3));
				row++;
				draw_text_button(esContext, "mlscreen4", VIEW_MODE_FCMENU, "Trottle/Alt-PID", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(4));
				row++;
				draw_text_button(esContext, "mlscreen5", VIEW_MODE_FCMENU, "Flightmodes", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(5));
				row++;
				draw_text_button(esContext, "mlscreen6", VIEW_MODE_FCMENU, "RC-Calibration", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(6));
				row++;
				draw_text_button(esContext, "mlscreen8", VIEW_MODE_FCMENU, "ACC-Calibration", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(7));
				row++;
				draw_text_button(esContext, "mlscreen7", VIEW_MODE_FCMENU, "Compass-Calibration", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(8));
				row++;
				draw_text_button(esContext, "mlscreen9", VIEW_MODE_FCMENU, "Camera/Gimbal/Relay", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(9));
				row++;
				draw_text_button(esContext, "mlscreen10", VIEW_MODE_FCMENU, "Logfiles", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(10));
				row++;
			}
			draw_text_button(esContext, "mlscreen0", VIEW_MODE_FCMENU, "All-Parameters", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(0));
			row++;
			return;
		} else {
			mavlink_view_screen = 0;
		}
	}

	draw_title(esContext, "MavLink-Parameter");
	row2 = 0;
	for (row = 0; row < MAVLINK_PARAMETER_MAX; row++) {
		if (strlen(MavLinkVars[ModelActive][row].name) > 3) {
			strncpy(tmp_str, MavLinkVars[ModelActive][row].name, 17);
			if (MavLinkVars[ModelActive][row].group[0] == 0) {
				for (n = 0; n < strlen(tmp_str) ; n++) {
					if (tmp_str[n] == '_') {
						tmp_str[n] = 0;
						break;
					}
				}
				strncpy(MavLinkVars[ModelActive][row].group, tmp_str, 17);
			}
			flag2 = 0;
			for (row2 = 0; row2 < MAVLINK_PARAMETER_MAX; row2++) {
				if (strcmp(main_groups[row2], MavLinkVars[ModelActive][row].group) == 0) {
					flag2 = 1;
					break;
				}
			}
			if (flag2 == 0) {
				for (row2 = 0; row2 < MAVLINK_PARAMETER_MAX; row2++) {
					if (main_groups[row2][0] == 0) {
						strncpy(main_groups[row2], MavLinkVars[ModelActive][row].group, 1023);
						break;
					}
				}
			}
			flag = 1;
		}
	}
	if (option_menu != -1) {
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[ModelActive][option_menu].name, FONT_GREEN, 0.0, -0.86, 0.002, 0.08, 1, 0, mavlink_options_menu, (float)-1);
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[ModelActive][option_menu].display, FONT_GREEN, 0.0, -0.79, 0.002, 0.04, 1, 0, mavlink_options_menu, (float)-1);
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[ModelActive][option_menu].desc, FONT_GREEN, 0.0, -0.75, 0.002, 0.04, 1, 0, mavlink_options_menu, (float)-1);
		int n3 = 0;
		for (n2 = (int)MavLinkVars[ModelActive][option_menu].min; n2 <= (int)MavLinkVars[ModelActive][option_menu].max; n2++) {
			tmp_str2[0] = 0;
			mavlink_meta_get_option(n2, MavLinkVars[ModelActive][option_menu].name, tmp_str2);
			if (tmp_str2[0] != 0) {
				sprintf(tmp_str, "%3.0i%s", n2, MavLinkVars[ModelActive][option_menu].name);
				if (n3 > 12) {
					if ((int)MavLinkVars[ModelActive][option_menu].value == n2) {
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, 0.0, -0.7 + (n3 - 13) * 0.1, 0.002, 0.08, 0, 0, mavlink_option_sel, n2);
					} else {
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.7 + (n3 - 13) * 0.1, 0.002, 0.08, 0, 0, mavlink_option_sel, n2);
					}
				} else {
					if ((int)MavLinkVars[ModelActive][option_menu].value == n2) {
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, -1.2, -0.7 + (n3) * 0.1, 0.002, 0.08, 0, 0, mavlink_option_sel, n2);
					} else {
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.7 + (n3) * 0.1, 0.002, 0.08, 0, 0, mavlink_option_sel, n2);
					}
				}
				n3++;
			}
		}
		draw_text_button(esContext, "back", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, -1.3, 0.8, 0.002, 0.08, 0, 0, mavlink_options_menu, (float)-1);
	} else if (bits_menu != -1) {
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[ModelActive][bits_menu].name, FONT_GREEN, 0.0, -0.8, 0.002, 0.08, 1, 0, mavlink_options_menu, (float)-1);
		for (n2 = (int)0; n2 < 32; n2++) {
			tmp_str2[0] = 0;
			mavlink_meta_get_bits(n2, MavLinkVars[ModelActive][bits_menu].name, tmp_str2);
			if (tmp_str2[0] == 0) {
				break;
			}
			sprintf(tmp_str, "%3.0i%s", n2, MavLinkVars[ModelActive][bits_menu].name);
			if ((n2 - 0) > 12) {
				if ((int)MavLinkVars[ModelActive][bits_menu].value & (1<<n2)) {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, 0.0, -0.7 + (n2 - 13) * 0.1, 0.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				} else {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.7 + (n2 - 13) * 0.1, 0.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				}
			} else {
				if ((int)MavLinkVars[ModelActive][bits_menu].value & (1<<n2)) {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, -1.2, -0.7 + (n2) * 0.1, 0.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				} else {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.7 + (n2) * 0.1, 0.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				}
			}
		}
		draw_text_button(esContext, "back", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, -1.3, 0.8, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)-1);
	} else if (param_menu != -1) {
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[ModelActive][bits_menu].name, FONT_GREEN, 0.0, -0.8, 0.002, 0.08, 1, 0, mavlink_param_menu, (float)-1);
		row = 1;
		sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[ModelActive][param_menu].name, n);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[ModelActive][param_menu].name, FONT_WHITE, 0.0, -0.8, 0.002, 0.15, 1, 0, mavlink_param_menu, -1.0);
		if (strlen(MavLinkVars[ModelActive][param_menu].desc) > 60) {
			strncpy(tmp_str, MavLinkVars[ModelActive][param_menu].desc, 100);
			tmp_str[60] = 0;
			draw_text_button(esContext, "#1", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.7 + row * 0.14 + 0.07, 0.002, 0.06, 1, 0, mavlink_param_menu, -1.0);
			draw_text_button(esContext, "#2", VIEW_MODE_FCMENU, MavLinkVars[ModelActive][param_menu].desc + 60, FONT_WHITE, 0.0, -0.7 + row * 0.14 + 0.07 + 0.07, 0.002, 0.06, 1, 0, mavlink_param_menu, -1.0);
		} else {
			draw_text_button(esContext, "#1", VIEW_MODE_FCMENU, MavLinkVars[ModelActive][param_menu].desc, FONT_WHITE, 0.0, -0.7 + row * 0.14 + 0.07, 0.002, 0.06, 1, 0, mavlink_param_menu, -1.0);
		}
		if (MavLinkVars[ModelActive][param_menu].type == MAV_VAR_FLOAT) {
			sprintf(tmp_str, "diff1_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-1.0]", FONT_WHITE, -1.0, 0.3, 0.002, 0.08, 0, 0, mavlink_param_diff, -1.0);

			sprintf(tmp_str, "diff2_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-0.1]", FONT_WHITE, -1.2, 0.4, 0.002, 0.08, 0, 0, mavlink_param_diff, -0.1);

			sprintf(tmp_str, "diff3_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-0.01]", FONT_WHITE, -0.8, 0.4, 0.002, 0.08, 0, 0, mavlink_param_diff, -0.01);

			sprintf(tmp_str, "diff4_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-0.001]", FONT_WHITE, -0.4, 0.4, 0.002, 0.08, 0, 0, mavlink_param_diff, -0.001);

			sprintf(tmp_str, "diff5_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+0.001]", FONT_WHITE, 0.4, 0.4, 0.002, 0.08, 2, 0, mavlink_param_diff, 0.001);

			sprintf(tmp_str, "diff6_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+0.01]", FONT_WHITE, 0.8, 0.4, 0.002, 0.08, 2, 0, mavlink_param_diff, 0.01);

			sprintf(tmp_str, "diff7_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+0.1]", FONT_WHITE, 1.2, 0.4, 0.002, 0.08, 2, 0, mavlink_param_diff, 0.1);

			sprintf(tmp_str, "diff8_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+1.0]", FONT_WHITE, 1.0, 0.3, 0.002, 0.08, 2, 0, mavlink_param_diff, 1.0);
		} else {
			sprintf(tmp_str, "diff1_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-1]", FONT_WHITE, -1.0, 0.3, 0.002, 0.08, 0, 0, mavlink_param_diff, -1.0);

			sprintf(tmp_str, "diff8_%s", MavLinkVars[ModelActive][param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+1]", FONT_WHITE, 1.0, 0.3, 0.002, 0.08, 2, 0, mavlink_param_diff, 1.0);
		}
		sprintf(tmp_str, "min00_%s", MavLinkVars[ModelActive][param_menu].name);
		if (MavLinkVars[ModelActive][param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "%i", (int)MavLinkVars[ModelActive][param_menu].min);
		} else {
			sprintf(tmp_str2, "%0.4f", MavLinkVars[ModelActive][param_menu].min);
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.1, 0.002, 0.08, 0, 0, mavlink_param_diff, -1.0);

		sprintf(tmp_str, "val00_%s", MavLinkVars[ModelActive][param_menu].name);
		if (MavLinkVars[ModelActive][param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "%i", (int)MavLinkVars[ModelActive][param_menu].value);
		} else {
			if (strcmp(MavLinkVars[ModelActive][param_menu].name, "COMPASS_DEC") == 0) {
				float w = MavLinkVars[ModelActive][param_menu].value * RAD_TO_DEG;
				int d = (int)w;
				int m = (int)((w - (float)d) * 100.0) * 60 / 100;
				sprintf(tmp_str2, "%0.2f/%i.%i", MavLinkVars[ModelActive][param_menu].value, d, m);
			} else {
				sprintf(tmp_str2, "%0.4f", MavLinkVars[ModelActive][param_menu].value);
			}
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.19, 0.002, 0.2, 1, 0, mavlink_param_diff, 0.0);

		sprintf(tmp_str, "max00_%s", MavLinkVars[ModelActive][param_menu].name);
		if (MavLinkVars[ModelActive][param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "%i", (int)MavLinkVars[ModelActive][param_menu].max);
		} else {
			sprintf(tmp_str2, "%0.4f", MavLinkVars[ModelActive][param_menu].max);
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 1.2, -0.1, 0.002, 0.08, 2, 0, mavlink_param_diff, 1.0);

		draw_box_f3c2(esContext, SLIDER2_START, 0.0, 0.002, SLIDER2_START + SLIDER2_LEN, 0.2, 0.002, 55, 55, 55, 220, 75, 45, 85, 100);
		draw_box_f3c2(esContext, SLIDER2_START, 0.0, 0.002, SLIDER2_START + ((MavLinkVars[ModelActive][param_menu].value - MavLinkVars[ModelActive][param_menu].min) * SLIDER2_LEN / (MavLinkVars[ModelActive][param_menu].max - MavLinkVars[ModelActive][param_menu].min)), 0.2, 0.002, 255, 255, 55, 220, 175, 145, 85, 100);

		if (MavLinkVars[ModelActive][param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "%i", (int)MavLinkVars[ModelActive][param_menu].value);
		} else {
			sprintf(tmp_str2, "%0.4f", MavLinkVars[ModelActive][param_menu].value);
		}
		sprintf(tmp_str, "value_%s", MavLinkVars[ModelActive][param_menu].name);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, 0.1, 2.005, 0.09, 1, 1, mavlink_param_diff, 0.0);

		sprintf(tmp_str, "S%s", MavLinkVars[ModelActive][param_menu].name);
		set_button(tmp_str, setup.view_mode, SLIDER2_START, 0.0, SLIDER2_START + SLIDER2_LEN, 0.2, mavlink_slider2_move, (float)param_menu, 1);
		if (strcmp(MavLinkVars[ModelActive][param_menu].name, "mag_declination") == 0 || strcmp(MavLinkVars[ModelActive][param_menu].name, "COMPASS_DEC") == 0) {
			int ret_dd = 0;
			int ret_dm = 0;
			int ret_id = 0;
			int ret_im = 0;
			get_declination(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt, &ret_dd, &ret_dm, &ret_id, &ret_im);
			sprintf(tmp_str, "M%s", MavLinkVars[ModelActive][param_menu].name);
			sprintf(tmp_str2, "[SET: %id%2.0im]", ret_dd, ret_dm);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 1.2, 0.6, 0.002, 0.08, 2, 0, mavlink_set_magdecl, 0.0);
		}

		sprintf(tmp_str, "V%s", MavLinkVars[ModelActive][param_menu].name);
		if (MavLinkVars[ModelActive][param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "[RESET: %i]", (int)param_last);
		} else {
			sprintf(tmp_str2, "[RESET: %0.4f]", param_last);
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, 0.5, 0.002, 0.08, 1, 0, mavlink_param_set, param_last);

		if (MavLinkVars[ModelActive][param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "[ONLOAD: %i]", (int)MavLinkVars[ModelActive][param_menu].onload);
		} else {
			sprintf(tmp_str2, "[ONLOAD: %0.4f]", MavLinkVars[ModelActive][param_menu].onload);
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, 0.6, 0.002, 0.08, 1, 0, mavlink_param_set, MavLinkVars[ModelActive][param_menu].onload);

		draw_text_button(esContext, "back", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, -1.3, 0.8, 0.002, 0.08, 0, 0, mavlink_param_menu, (float)-1);
	} else if (select_section[0] == 0) {
		col = 0;
		row = 0;
		for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
			if (main_groups[n][0] == 0) {
				break;
			}
			sprintf(tmp_str, "mv_main_%s", main_groups[n]);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, main_groups[n], FONT_WHITE, -1.1 + col * 0.55, -0.8 + row * 0.1, 0.002, 0.06, 1, 0, mavlink_select_main, n);
			col++;
			if (col > 4) {
				col = 0;
				row++;
			}
		}
	} else if (select_section[0] != 0) {
		col = 0;
		row = 0;
		int mav_id_sect = 0;
		int mav_id = 0;
		if ((int)set_sel > 0) {
			draw_text_button(esContext, "scroll_up", VIEW_MODE_FCMENU, "[^]", FONT_WHITE, 0.0, -0.7 - 0.14, 0.002, 0.08, 1, 0, mavlink_select_sel_scroll, -1.0);
		}
		for (mav_id = 0; mav_id < MAVLINK_PARAMETER_MAX; mav_id++) {
			if (MavLinkVars[ModelActive][mav_id].name[0] == 0) {
				continue;
			}
			sprintf(tmp_str, "%s_", select_section);
			if (strcmp(MavLinkVars[ModelActive][mav_id].group, select_section) == 0) {
			} else if (strncmp(MavLinkVars[ModelActive][mav_id].name, tmp_str, strlen(tmp_str)) == 0 || strcmp(MavLinkVars[ModelActive][mav_id].name, select_section) == 0) {
			} else {
				continue;
			}
			mav_id_sect++;
			if (mav_id_sect < (int)set_sel + 1 || mav_id_sect - (int)set_sel > 10) {
				continue;
			}
			if (strlen(MavLinkVars[ModelActive][mav_id].desc) > 60) {
				strncpy(tmp_str, MavLinkVars[ModelActive][mav_id].desc, 100);
				tmp_str[60] = 0;
				draw_text_button(esContext, "#", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.19, -0.7 + row * 0.14 + 0.07, 0.002, 0.04, 0, 0, mavlink_select_sel, 0.0);
				draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[ModelActive][mav_id].desc + 60, FONT_WHITE, -1.18, -0.7 + row * 0.14 + 0.07 + 0.04, 0.002, 0.04, 0, 0, mavlink_select_sel, 0.0);
			} else {
				draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[ModelActive][mav_id].desc, FONT_WHITE, -1.19, -0.7 + row * 0.14 + 0.07, 0.002, 0.04, 0, 0, mavlink_select_sel, 0.0);
			}
			if (MavLinkVars[ModelActive][mav_id].type != MAV_VAR_FLOAT) {
				sprintf(tmp_str2, "%i", (int)MavLinkVars[ModelActive][mav_id].value);
			} else {
				sprintf(tmp_str2, "%0.4f", MavLinkVars[ModelActive][mav_id].value);
			}
			if (
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_angle") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_horizon") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_baro") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_mag") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_camstab") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_camtrig") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_arm") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_gps_home") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_gps_hold") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_gps_log") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_passthru") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_headfree") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_beeper") == 0
				||
				strcmp(MavLinkVars[ModelActive][mav_id].name, "aux_headadj") == 0
			) {
				sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[ModelActive][mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[ModelActive][mav_id].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_select_sel, 0.0);
				n3 = 0;
				for (n2 = 0; n2 < 12; n2++) {
					if ((int)MavLinkVars[ModelActive][mav_id].value & (1<<n2)) {
						sprintf(tmp_str, "R%2.0i%s", n2, MavLinkVars[ModelActive][mav_id].name);
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "X", FONT_WHITE, -0.3 + n3 * 0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_aux_toggle, (float)n2);
					} else {
						sprintf(tmp_str, "S%2.0i%s", n2, MavLinkVars[ModelActive][mav_id].name);
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "O", FONT_WHITE, -0.3 + n3 * 0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_aux_toggle, (float)n2);
					}
					if (n2 == 2 || n2 == 5 || n2 == 8) {
						n3++;
					}
					n3++;
				}
			} else if (MavLinkVars[ModelActive][mav_id].values[0] != 0) {
				sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[ModelActive][mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[ModelActive][mav_id].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_options_menu, (float)(mav_id));
				mavlink_meta_get_option((int)MavLinkVars[ModelActive][mav_id].value, MavLinkVars[ModelActive][mav_id].name, tmp_str2);
				sprintf(tmp_str, "S%s", MavLinkVars[ModelActive][mav_id].name);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_options_menu, (float)(mav_id));
			} else if (MavLinkVars[ModelActive][mav_id].bits[0] != 0) {
				sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[ModelActive][mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[ModelActive][mav_id].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)(mav_id));
				sprintf(tmp_str, "B%s", MavLinkVars[ModelActive][mav_id].name);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, ".....", FONT_WHITE, -0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)(mav_id));
			} else {
				sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[ModelActive][mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[ModelActive][mav_id].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_param_menu, (float)(mav_id));
				sprintf(tmp_str, "mv_sel_%s_%i_v", MavLinkVars[ModelActive][mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.7 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_param_menu, (float)(mav_id));
				sprintf(tmp_str, "S%s", MavLinkVars[ModelActive][mav_id].name);
				draw_box_f3c2(esContext, SLIDER_START, -0.7 + row * 0.14, 0.003, SLIDER_START + SLIDER_LEN, -0.7 + row * 0.14 + 0.1, 0.003, 55, 55, 55, 220, 75, 45, 85, 100);
				draw_box_f3c2(esContext, SLIDER_START, -0.7 + row * 0.14, 0.003, SLIDER_START + ((MavLinkVars[ModelActive][mav_id].value - MavLinkVars[ModelActive][mav_id].min) * SLIDER_LEN / (MavLinkVars[ModelActive][mav_id].max - MavLinkVars[ModelActive][mav_id].min)), -0.7 + row * 0.14 + 0.1, 0.003, 255, 255, 55, 220, 175, 145, 85, 100);
				set_button(tmp_str, setup.view_mode, SLIDER_START, -0.7 + row * 0.14, SLIDER_START + SLIDER_LEN, -0.7 + row * 0.14 + 0.1, mavlink_slider_move, (float)row, 1);
				if (strcmp(MavLinkVars[ModelActive][mav_id].name, "mag_declination") == 0) {
					int ret_dd = 0;
					int ret_dm = 0;
					int ret_id = 0;
					int ret_im = 0;
					get_declination(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt, &ret_dd, &ret_dm, &ret_id, &ret_im);
					sprintf(tmp_str, "M%s", MavLinkVars[ModelActive][mav_id].name);
					sprintf(tmp_str2, "%i%2.0i", ret_dd, ret_dm);
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_set_magdecl, 0.0);
				}
			}
			row++;
		}
		if (mav_id_sect >= 10 && row >= 10) {
			draw_text_button(esContext, "scroll_down", VIEW_MODE_FCMENU, "[v]", FONT_WHITE, 0.0, 0.7, 0.002, 0.08, 1, 0, mavlink_select_sel_scroll, 1.0);
		}
		draw_text_button(esContext, "back", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, -1.3, 0.8, 0.002, 0.08, 0, 0, mavlink_select_sel, 0.0);
	}

	if (flag == 0) {
		draw_text_f(esContext, -0.4, 0.0, 0.05, 0.05, FONT_BLACK_BG, "No Mavlink-Parameters found");
	}

	screen_keyboard(esContext);
	screen_filesystem(esContext);
}

