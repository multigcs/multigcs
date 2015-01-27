
#include <all.h>

#define DEG_TO_RAD   ( PI / 180.0 )
#define RAD_TO_DEG   ( 180.0 / PI )

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
		if (strcmp(MavLinkVars[n].name, name) == 0) {
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
		if (strcmp(MavLinkVars[n].name, name) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return;
	}
//	MavLinkVars[selected].min = atof(MavLinkVars[selected].values);
	for (n2 = 0; n2 < strlen(MavLinkVars[selected].values); n2++) {
		if (MavLinkVars[selected].values[n2] == ',') {
			strncpy(tmp_str3, MavLinkVars[selected].values + n3, 1023);
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
	strncpy(tmp_str3, MavLinkVars[n].values + n3, 1023);
//	MavLinkVars[selected].max = atof(tmp_str3);
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
			strncpy(tmp_str3, MavLinkVars[n].bits + n3, 1023);
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
	strncpy(tmp_str3, MavLinkVars[n].bits + n3, 1023);
	MavLinkVars[n].max = (float)((1<<atoi(tmp_str3)) * (1<<atoi(tmp_str3)) - 1);
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
		if (strcmp(MavLinkVars[n].name, name + 1) == 0) {
			selected = n;
			break;
		}
	}
	MavLinkVars[selected].value = data;
	if (MavLinkVars[selected].value < MavLinkVars[selected].min) {
		MavLinkVars[selected].value = MavLinkVars[selected].min;
	} else if (MavLinkVars[selected].value > MavLinkVars[selected].max) {
		MavLinkVars[selected].value = MavLinkVars[selected].max;
	}
	mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
	return 0;
}

uint8_t mavlink_param_diff (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[n].name, name + 6) == 0) {
			selected = n;
			break;
		}
	}
	MavLinkVars[selected].value += data;
	if (MavLinkVars[selected].value < MavLinkVars[selected].min) {
		MavLinkVars[selected].value = MavLinkVars[selected].min;
	} else if (MavLinkVars[selected].value > MavLinkVars[selected].max) {
		MavLinkVars[selected].value = MavLinkVars[selected].max;
	}
	mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
	return 0;
}

uint8_t mavlink_slider_move (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[n].name, name + 1) == 0) {
			selected = n;
			break;
		}
	}
	if (button == 4) {
		if (MavLinkVars[selected].type != MAV_VAR_FLOAT) {
			MavLinkVars[selected].value += 1;
		} else {
			MavLinkVars[selected].value += 0.01;
		}
	} else if (button == 5) {
		if (MavLinkVars[selected].type != MAV_VAR_FLOAT) {
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
		if (MavLinkVars[selected].type != MAV_VAR_FLOAT) {
			int conv = (int)(new);
			new = (float)conv;
		}
//		SDL_Log("slider: %s %f %f %f %f\n", name + 1, x, percent, new, data);
		if (strstr(MavLinkVars[selected].name, "baud") > 0 || strstr(MavLinkVars[selected].name, "BAUD") > 0) {
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
	mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
	return 0;
}

uint8_t mavlink_slider2_move (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[n].name, name + 1) == 0) {
			selected = n;
			break;
		}
	}
	if (button == 4) {
		if (MavLinkVars[selected].type != MAV_VAR_FLOAT) {
			MavLinkVars[selected].value += 1;
		} else {
			MavLinkVars[selected].value += 0.01;
		}
	} else if (button == 5) {
		if (MavLinkVars[selected].type != MAV_VAR_FLOAT) {
			MavLinkVars[selected].value -= 1;
		} else {
			MavLinkVars[selected].value -= 0.01;
		}
	} else {
		float percent = (x - SLIDER2_START) * 100.0 / SLIDER2_LEN;
		if (percent > 100.0) {
			percent = 100.0;
		} else if (percent < 0.0) {
			percent = 0.0;
		}
		float diff = MavLinkVars[selected].max - MavLinkVars[selected].min;
		float new = percent * diff / 100.0 + MavLinkVars[selected].min;
		if (MavLinkVars[selected].type != MAV_VAR_FLOAT) {
			int conv = (int)(new);
			new = (float)conv;
		}
//		SDL_Log("slider2: %s %f %f %f %f\n", name + 1, x, percent, new, data);
		if (strstr(MavLinkVars[selected].name, "baud") > 0 || strstr(MavLinkVars[selected].name, "BAUD") > 0) {
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
	mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
	return 0;
}


uint8_t mavlink_set_magdecl (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[n].name, name + 1) == 0) {
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
	get_declination(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt, &ret_dd, &ret_dm);
	if (strcmp(name + 1, "COMPASS_DEC") == 0) {
		sprintf(tmp_str, "%i.%2.0i", ret_dd, ret_dm * 100 / 60);
		MavLinkVars[selected].value = atof(tmp_str) * DEG_TO_RAD;
	} else {
		sprintf(tmp_str, "%i%2.0i", ret_dd, ret_dm);
		MavLinkVars[selected].value = atof(tmp_str);
	}
	mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
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
		if (strcmp(MavLinkVars[n].name, name + 3) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return 0;
	}
	MavLinkVars[selected].value = data;
	mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
	option_menu = -1;
	return 0;
}

uint8_t mavlink_param_menu (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	reset_buttons();
	param_menu = (int)data;
	if (param_menu != -1) {
		param_last = MavLinkVars[param_menu].value;
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
		if (strcmp(MavLinkVars[n].name, name + 3) == 0) {
			selected = n;
			break;
		}
	}
	if (selected == -1) {
		return 0;
	}
	int new = (int)MavLinkVars[selected].value;
	if (new & (1<<(int)data)) {
		new &= ~(1<<(int)data);
	} else {
		new |= (1<<(int)data);
	}
	MavLinkVars[selected].value = (float)new;
	mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
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
			if (MavLinkVars[n].name[0] != 0) {
				fprintf(fr, "%i	%i	%s	%f\n", ModelData[ModelActive].sysid, ModelData[ModelActive].compid, MavLinkVars[n].name, MavLinkVars[n].value);
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
	mavlink_param_xml_meta_load();
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
	mavlink_send_value(ModelActive, MavLinkVars[n].name, MavLinkVars[n].value, MavLinkVars[n].type);
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
				MavLinkVars[selected].value = cal_min[pn];
				mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
				SDL_Delay(30);
				sprintf(tmp_str, "RC%i_MAX", pn + 1);
				selected = mavlink_get_id_by_name(tmp_str);
				MavLinkVars[selected].value = cal_max[pn];
				mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
				SDL_Delay(30);
			}
		}
		// double send
		for (pn = 0; pn < 8; pn++) {
			if (cal_min[pn] != cal_max[pn]) {
				sprintf(tmp_str, "RC%i_MIN", pn + 1);
				selected = mavlink_get_id_by_name(tmp_str);
				MavLinkVars[selected].value = cal_min[pn];
				mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
				SDL_Delay(30);
				sprintf(tmp_str, "RC%i_MAX", pn + 1);
				selected = mavlink_get_id_by_name(tmp_str);
				MavLinkVars[selected].value = cal_max[pn];
				mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
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
		if (MavLinkVars[n].name[0] != 0) {
			mavlink_send_value(ModelActive, MavLinkVars[n].name, MavLinkVars[n].value, MavLinkVars[n].type);
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
				sprintf(tmp_str, "mv_sel_%s_t", MavLinkVars[mav_id].name);
				sprintf(tmp_str2, "%s", plist[pn].name);
				if (MavLinkVars[mav_id].values[0] != 0) {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.8 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_options_menu, (float)(mav_id));
					sprintf(tmp_str, "mv_sel_%s_v", MavLinkVars[mav_id].name);
					mavlink_meta_get_option((int)MavLinkVars[mav_id].value, MavLinkVars[mav_id].name, tmp_str2);
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.8 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_options_menu, (float)(mav_id));
				} else if (MavLinkVars[mav_id].bits[0] != 0) {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.8 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)(mav_id));
					sprintf(tmp_str, "mv_sel_%s_v", MavLinkVars[mav_id].name);
					sprintf(tmp_str2, "%0.2f", MavLinkVars[mav_id].value);
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.8 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_bits_menu, (float)(mav_id));
				} else {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.8 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_param_menu, (float)(mav_id));
					sprintf(tmp_str, "mv_sel_%s_v", MavLinkVars[mav_id].name);
					sprintf(tmp_str2, "%0.2f", MavLinkVars[mav_id].value);
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.8 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_param_menu, (float)(mav_id));
				}
				if (MavLinkVars[mav_id].bits[0] == 0 && MavLinkVars[mav_id].values[0] == 0) {
					sprintf(tmp_str, "S%s", MavLinkVars[mav_id].name);
					draw_box_f3c2(esContext, SLIDER_START, -0.8 + row * 0.14, 0.001, SLIDER_START + SLIDER_LEN, -0.8 + row * 0.14 + 0.1, 0.001, 55, 55, 55, 220, 75, 45, 85, 100);
					draw_box_f3c2(esContext, SLIDER_START, -0.8 + row * 0.14, 0.001, SLIDER_START + ((MavLinkVars[mav_id].value - MavLinkVars[mav_id].min) * SLIDER_LEN / (MavLinkVars[mav_id].max - MavLinkVars[mav_id].min)), -0.8 + row * 0.14 + 0.1, 0.001, 255, 255, 55, 220, 175, 145, 85, 100);
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
		{"RATE_RLL_I", "Rate Roll-P"},
		{"RATE_RLL_D", "Rate Roll-P"},
		{"RATE_RLL_IMAX", "Rate Roll-P"},
		{"---", "---"},
		{"RATE_PIT_P", "Rate Roll-P"},
		{"RATE_PIT_I", "Rate Roll-P"},
		{"RATE_PIT_D", "Rate Roll-P"},
		{"RATE_PIT_IMAX", "Rate Roll-P"},
		{"---", "---"},
		{"RATE_YAW_P", "Rate Roll-P"},
		{"RATE_YAW_I", "Rate Roll-P"},
		{"RATE_YAW_D", "Rate Roll-P"},
		{"RATE_YAW_IMAX", "Rate Roll-P"},
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
				float minv = MavLinkVars[mavlink_get_id_by_name(tmp_str)].value;
				sprintf(tmp_str, "RC%i_MAX", pn + 1);
				float maxv = MavLinkVars[mavlink_get_id_by_name(tmp_str)].value;
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
					uint8_t map = MavLinkVars[mavlink_get_id_by_name(tmp_str)].value;
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
		MavLinkVars[selected].value = (float)mavlink_channel_select_num;
		mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
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
		{"COMPASS_LEARN", ""},
		{"COMPASS_EXTERNAL", ""},
	};
	draw_title(esContext, "Compass-Calibration");
	screen_mavlink_list(esContext, plist, sizeof(plist) / sizeof(paralist));
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
			if ((int)MavLinkVars[selected].value == 6) {
				pan = pn;
			} else if ((int)MavLinkVars[selected].value == 7) {
				tilt = pn;
			} else if ((int)MavLinkVars[selected].value == 8) {
				roll = pn;
			} else if ((int)MavLinkVars[selected].value == 10) {
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
						MavLinkVars[selected].value = (float)10;
						mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
					} else if ((int)MavLinkVars[selected].value == 10) {
						MavLinkVars[selected].value = (float)0;
						mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
					}
				} else if (mavlink_channel_select == 2) {
					if (pn == mavlink_channel_select_num - 1) {
						MavLinkVars[selected].value = (float)6;
						mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
					} else if ((int)MavLinkVars[selected].value == 6) {
						MavLinkVars[selected].value = (float)0;
						mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
					}
				} else if (mavlink_channel_select == 3) {
					if (pn == mavlink_channel_select_num - 1) {
						MavLinkVars[selected].value = (float)7;
						mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
					} else if ((int)MavLinkVars[selected].value == 7) {
						MavLinkVars[selected].value = (float)0;
						mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
					}
				} else if (mavlink_channel_select == 4) {
					if (pn == mavlink_channel_select_num - 1) {
						MavLinkVars[selected].value = (float)8;
						mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
					} else if ((int)MavLinkVars[selected].value == 8) {
						MavLinkVars[selected].value = (float)0;
						mavlink_send_value(ModelActive, MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
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
			screen_mavlink_rccal(esContext);
			return;
		} else if (mavlink_view_screen == 7) {
			screen_mavlink_magcal(esContext);
			return;
		} else if (mavlink_view_screen == 8) {
			screen_mavlink_acccal(esContext);
			return;
		} else if (mavlink_view_screen == 9) {
			screen_mavlink_camrelay(esContext);
			return;
		} else if (mavlink_view_screen == 10) {
			screen_mavlink_logfile(esContext);
			return;
		} else if (mavlink_view_screen == -1) {
			draw_title(esContext, "Mavlink");
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
			draw_text_button(esContext, "mlscreen7", VIEW_MODE_FCMENU, "Compass-Calibration", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(7));
			row++;
			draw_text_button(esContext, "mlscreen8", VIEW_MODE_FCMENU, "ACC-Calibration", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(8));
			row++;
			draw_text_button(esContext, "mlscreen9", VIEW_MODE_FCMENU, "Camera/Gimbal/Relay", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(9));
			row++;
			draw_text_button(esContext, "mlscreen10", VIEW_MODE_FCMENU, "Logfiles", FONT_WHITE, 0.0, -0.75 + row * 0.14, 0.005, 0.08, 1, 0, mavlink_view_screen_change, (float)(10));
			row++;
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
		if (strlen(MavLinkVars[row].name) > 3) {
			strncpy(tmp_str, MavLinkVars[row].name, 17);
			if (MavLinkVars[row].group[0] == 0) {
				for (n = 0; n < strlen(tmp_str) ; n++) {
					if (tmp_str[n] == '_') {
						tmp_str[n] = 0;
						break;
					}
				}
				strncpy(MavLinkVars[row].group, tmp_str, 17);
			}
			flag2 = 0;
			for (row2 = 0; row2 < MAVLINK_PARAMETER_MAX; row2++) {
				if (strcmp(main_groups[row2], MavLinkVars[row].group) == 0) {
					flag2 = 1;
					break;
				}
			}
			if (flag2 == 0) {
				for (row2 = 0; row2 < MAVLINK_PARAMETER_MAX; row2++) {
					if (main_groups[row2][0] == 0) {
						strncpy(main_groups[row2], MavLinkVars[row].group, 1023);
						break;
					}
				}
			}
			flag = 1;
		}
	}
	if (option_menu != -1) {
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[option_menu].name, FONT_GREEN, 0.0, -0.86, 0.002, 0.08, 1, 0, mavlink_options_menu, (float)-1);
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[option_menu].display, FONT_GREEN, 0.0, -0.79, 0.002, 0.04, 1, 0, mavlink_options_menu, (float)-1);
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[option_menu].desc, FONT_GREEN, 0.0, -0.75, 0.002, 0.04, 1, 0, mavlink_options_menu, (float)-1);
		int n3 = 0;
		for (n2 = (int)MavLinkVars[option_menu].min; n2 <= (int)MavLinkVars[option_menu].max; n2++) {
			tmp_str2[0] = 0;
			mavlink_meta_get_option(n2, MavLinkVars[option_menu].name, tmp_str2);
			if (tmp_str2[0] != 0) {
				sprintf(tmp_str, "%3.0i%s", n2, MavLinkVars[option_menu].name);
				if (n3 > 12) {
					if ((int)MavLinkVars[option_menu].value == n2) {
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, 0.0, -0.7 + (n3 - 13) * 0.1, 0.002, 0.08, 0, 0, mavlink_option_sel, n2);
					} else {
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.7 + (n3 - 13) * 0.1, 0.002, 0.08, 0, 0, mavlink_option_sel, n2);
					}
				} else {
					if ((int)MavLinkVars[option_menu].value == n2) {
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
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[bits_menu].name, FONT_GREEN, 0.0, -0.8, 0.002, 0.08, 1, 0, mavlink_options_menu, (float)-1);
		for (n2 = (int)0; n2 < 32; n2++) {
			tmp_str2[0] = 0;
			mavlink_meta_get_bits(n2, MavLinkVars[bits_menu].name, tmp_str2);
			if (tmp_str2[0] == 0) {
				break;
			}
			sprintf(tmp_str, "%3.0i%s", n2, MavLinkVars[bits_menu].name);
			if ((n2 - 0) > 12) {
				if ((int)MavLinkVars[bits_menu].value & (1<<n2)) {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, 0.0, -0.7 + (n2 - 13) * 0.1, 0.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				} else {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.7 + (n2 - 13) * 0.1, 0.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				}
			} else {
				if ((int)MavLinkVars[bits_menu].value & (1<<n2)) {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, -1.2, -0.7 + (n2) * 0.1, 0.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				} else {
					draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.7 + (n2) * 0.1, 0.002, 0.08, 0, 0, mavlink_bits_sel, n2);
				}
			}
		}
		draw_text_button(esContext, "back", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, -1.3, 0.8, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)-1);
	} else if (param_menu != -1) {
		draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[bits_menu].name, FONT_GREEN, 0.0, -0.8, 0.002, 0.08, 1, 0, mavlink_param_menu, (float)-1);
		row = 1;
		sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[param_menu].name, n);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[param_menu].name, FONT_WHITE, 0.0, -0.8, 0.002, 0.15, 1, 0, mavlink_param_menu, -1.0);
		if (strlen(MavLinkVars[param_menu].desc) > 60) {
			strncpy(tmp_str, MavLinkVars[param_menu].desc, 100);
			tmp_str[60] = 0;
			draw_text_button(esContext, "#1", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.7 + row * 0.14 + 0.07, 0.002, 0.06, 1, 0, mavlink_param_menu, -1.0);
			draw_text_button(esContext, "#2", VIEW_MODE_FCMENU, MavLinkVars[param_menu].desc + 60, FONT_WHITE, 0.0, -0.7 + row * 0.14 + 0.07 + 0.07, 0.002, 0.06, 1, 0, mavlink_param_menu, -1.0);
		} else {
			draw_text_button(esContext, "#1", VIEW_MODE_FCMENU, MavLinkVars[param_menu].desc, FONT_WHITE, 0.0, -0.7 + row * 0.14 + 0.07, 0.002, 0.06, 1, 0, mavlink_param_menu, -1.0);
		}
		if (MavLinkVars[param_menu].type == MAV_VAR_FLOAT) {
			sprintf(tmp_str, "diff1_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-1.0]", FONT_WHITE, -1.0, 0.3, 0.002, 0.08, 0, 0, mavlink_param_diff, -1.0);

			sprintf(tmp_str, "diff2_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-0.1]", FONT_WHITE, -1.2, 0.4, 0.002, 0.08, 0, 0, mavlink_param_diff, -0.1);

			sprintf(tmp_str, "diff3_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-0.01]", FONT_WHITE, -0.8, 0.4, 0.002, 0.08, 0, 0, mavlink_param_diff, -0.01);

			sprintf(tmp_str, "diff4_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-0.001]", FONT_WHITE, -0.4, 0.4, 0.002, 0.08, 0, 0, mavlink_param_diff, -0.001);

			sprintf(tmp_str, "diff5_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+0.001]", FONT_WHITE, 0.4, 0.4, 0.002, 0.08, 2, 0, mavlink_param_diff, 0.001);

			sprintf(tmp_str, "diff6_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+0.01]", FONT_WHITE, 0.8, 0.4, 0.002, 0.08, 2, 0, mavlink_param_diff, 0.01);

			sprintf(tmp_str, "diff7_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+0.1]", FONT_WHITE, 1.2, 0.4, 0.002, 0.08, 2, 0, mavlink_param_diff, 0.1);

			sprintf(tmp_str, "diff8_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+1.0]", FONT_WHITE, 1.0, 0.3, 0.002, 0.08, 2, 0, mavlink_param_diff, 1.0);
		} else {
			sprintf(tmp_str, "diff1_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-1]", FONT_WHITE, -1.0, 0.3, 0.002, 0.08, 0, 0, mavlink_param_diff, -1.0);

			sprintf(tmp_str, "diff8_%s", MavLinkVars[param_menu].name);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+1]", FONT_WHITE, 1.0, 0.3, 0.002, 0.08, 2, 0, mavlink_param_diff, 1.0);
		}
		sprintf(tmp_str, "min00_%s", MavLinkVars[param_menu].name);
		if (MavLinkVars[param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "%i", (int)MavLinkVars[param_menu].min);
		} else {
			sprintf(tmp_str2, "%0.4f", MavLinkVars[param_menu].min);
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.1, 0.002, 0.08, 0, 0, mavlink_param_diff, -1.0);

		sprintf(tmp_str, "val00_%s", MavLinkVars[param_menu].name);
		if (MavLinkVars[param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "%i", (int)MavLinkVars[param_menu].value);
		} else {
			if (strcmp(MavLinkVars[param_menu].name, "COMPASS_DEC") == 0) {
				float w = MavLinkVars[param_menu].value * RAD_TO_DEG;
				int d = (int)w;
				int m = (int)((w - (float)d) * 100.0) * 60 / 100;
				sprintf(tmp_str2, "%0.2f/%i.%i", MavLinkVars[param_menu].value, d, m);
			} else {
				sprintf(tmp_str2, "%0.4f", MavLinkVars[param_menu].value);
			}
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, -0.19, 0.002, 0.2, 1, 0, mavlink_param_diff, 0.0);

		sprintf(tmp_str, "max00_%s", MavLinkVars[param_menu].name);
		if (MavLinkVars[param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "%i", (int)MavLinkVars[param_menu].max);
		} else {
			sprintf(tmp_str2, "%0.4f", MavLinkVars[param_menu].max);
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 1.2, -0.1, 0.002, 0.08, 2, 0, mavlink_param_diff, 1.0);

		draw_box_f3c2(esContext, SLIDER2_START, 0.0, 0.002, SLIDER2_START + SLIDER2_LEN, 0.2, 0.002, 55, 55, 55, 220, 75, 45, 85, 100);
		draw_box_f3c2(esContext, SLIDER2_START, 0.0, 0.002, SLIDER2_START + ((MavLinkVars[param_menu].value - MavLinkVars[param_menu].min) * SLIDER2_LEN / (MavLinkVars[param_menu].max - MavLinkVars[param_menu].min)), 0.2, 0.002, 255, 255, 55, 220, 175, 145, 85, 100);

		if (MavLinkVars[param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "%i", (int)MavLinkVars[param_menu].value);
		} else {
			sprintf(tmp_str2, "%0.4f", MavLinkVars[param_menu].value);
		}
		sprintf(tmp_str, "value_%s", MavLinkVars[param_menu].name);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, 0.1, 2.005, 0.09, 1, 1, mavlink_param_diff, 0.0);

		sprintf(tmp_str, "S%s", MavLinkVars[param_menu].name);
		set_button(tmp_str, setup.view_mode, SLIDER2_START, 0.0, SLIDER2_START + SLIDER2_LEN, 0.2, mavlink_slider2_move, (float)param_menu, 1);
		if (strcmp(MavLinkVars[param_menu].name, "mag_declination") == 0 || strcmp(MavLinkVars[param_menu].name, "COMPASS_DEC") == 0) {
			int ret_dd = 0;
			int ret_dm = 0;
			get_declination(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt, &ret_dd, &ret_dm);
			sprintf(tmp_str, "M%s", MavLinkVars[param_menu].name);
			sprintf(tmp_str2, "[SET: %id%2.0im]", ret_dd, ret_dm);
			draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 1.2, 0.6, 0.002, 0.08, 2, 0, mavlink_set_magdecl, 0.0);
		}

		sprintf(tmp_str, "V%s", MavLinkVars[param_menu].name);
		if (MavLinkVars[param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "[RESET: %i]", (int)param_last);
		} else {
			sprintf(tmp_str2, "[RESET: %0.4f]", param_last);
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, 0.5, 0.002, 0.08, 1, 0, mavlink_param_set, param_last);

		if (MavLinkVars[param_menu].type != MAV_VAR_FLOAT) {
			sprintf(tmp_str2, "[ONLOAD: %i]", (int)MavLinkVars[param_menu].onload);
		} else {
			sprintf(tmp_str2, "[ONLOAD: %0.4f]", MavLinkVars[param_menu].onload);
		}
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, 0.6, 0.002, 0.08, 1, 0, mavlink_param_set, MavLinkVars[param_menu].onload);

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
			if (MavLinkVars[mav_id].name[0] == 0) {
				continue;
			}
			sprintf(tmp_str, "%s_", select_section);
			if (strcmp(MavLinkVars[mav_id].group, select_section) == 0) {
			} else if (strncmp(MavLinkVars[mav_id].name, tmp_str, strlen(tmp_str)) == 0 || strcmp(MavLinkVars[mav_id].name, select_section) == 0) {
			} else {
				continue;
			}
			mav_id_sect++;
			if (mav_id_sect < (int)set_sel + 1 || mav_id_sect - (int)set_sel > 10) {
				continue;
			}
			if (strlen(MavLinkVars[mav_id].desc) > 60) {
				strncpy(tmp_str, MavLinkVars[mav_id].desc, 100);
				tmp_str[60] = 0;
				draw_text_button(esContext, "#", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.19, -0.7 + row * 0.14 + 0.07, 0.002, 0.04, 0, 0, mavlink_select_sel, 0.0);
				draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[mav_id].desc + 60, FONT_WHITE, -1.18, -0.7 + row * 0.14 + 0.07 + 0.04, 0.002, 0.04, 0, 0, mavlink_select_sel, 0.0);
			} else {
				draw_text_button(esContext, "#", VIEW_MODE_FCMENU, MavLinkVars[mav_id].desc, FONT_WHITE, -1.19, -0.7 + row * 0.14 + 0.07, 0.002, 0.04, 0, 0, mavlink_select_sel, 0.0);
			}
			if (MavLinkVars[mav_id].type != MAV_VAR_FLOAT) {
				sprintf(tmp_str2, "%i", (int)MavLinkVars[mav_id].value);
			} else {
				sprintf(tmp_str2, "%0.4f", MavLinkVars[mav_id].value);
			}
			if (
				strcmp(MavLinkVars[mav_id].name, "aux_angle") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_horizon") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_baro") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_mag") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_camstab") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_camtrig") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_arm") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_gps_home") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_gps_hold") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_gps_log") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_passthru") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_headfree") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_beeper") == 0
				||
				strcmp(MavLinkVars[mav_id].name, "aux_headadj") == 0
			) {
				sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[mav_id].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_select_sel, 0.0);
				n3 = 0;
				for (n2 = 0; n2 < 12; n2++) {
					if ((int)MavLinkVars[mav_id].value & (1<<n2)) {
						sprintf(tmp_str, "R%2.0i%s", n2, MavLinkVars[mav_id].name);
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "X", FONT_WHITE, -0.3 + n3 * 0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_aux_toggle, (float)n2);
					} else {
						sprintf(tmp_str, "S%2.0i%s", n2, MavLinkVars[mav_id].name);
						draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "O", FONT_WHITE, -0.3 + n3 * 0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_aux_toggle, (float)n2);
					}
					if (n2 == 2 || n2 == 5 || n2 == 8) {
						n3++;
					}
					n3++;
				}
			} else if (MavLinkVars[mav_id].values[0] != 0) {
				sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[mav_id].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_options_menu, (float)(mav_id));
				mavlink_meta_get_option((int)MavLinkVars[mav_id].value, MavLinkVars[mav_id].name, tmp_str2);
				sprintf(tmp_str, "S%s", MavLinkVars[mav_id].name);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_options_menu, (float)(mav_id));
			} else if (MavLinkVars[mav_id].bits[0] != 0) {
				sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[mav_id].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)(mav_id));
				sprintf(tmp_str, "B%s", MavLinkVars[mav_id].name);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, ".....", FONT_WHITE, -0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_bits_menu, (float)(mav_id));
			} else {
				sprintf(tmp_str, "mv_sel_%s_%i_t", MavLinkVars[mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, MavLinkVars[mav_id].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_param_menu, (float)(mav_id));
				sprintf(tmp_str, "mv_sel_%s_%i_v", MavLinkVars[mav_id].name, n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.7 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_param_menu, (float)(mav_id));
				sprintf(tmp_str, "S%s", MavLinkVars[mav_id].name);
				draw_box_f3c2(esContext, SLIDER_START, -0.7 + row * 0.14, 0.003, SLIDER_START + SLIDER_LEN, -0.7 + row * 0.14 + 0.1, 0.003, 55, 55, 55, 220, 75, 45, 85, 100);
				draw_box_f3c2(esContext, SLIDER_START, -0.7 + row * 0.14, 0.003, SLIDER_START + ((MavLinkVars[mav_id].value - MavLinkVars[mav_id].min) * SLIDER_LEN / (MavLinkVars[mav_id].max - MavLinkVars[mav_id].min)), -0.7 + row * 0.14 + 0.1, 0.003, 255, 255, 55, 220, 175, 145, 85, 100);
				set_button(tmp_str, setup.view_mode, SLIDER_START, -0.7 + row * 0.14, SLIDER_START + SLIDER_LEN, -0.7 + row * 0.14 + 0.1, mavlink_slider_move, (float)row, 1);
				if (strcmp(MavLinkVars[mav_id].name, "mag_declination") == 0) {
					int ret_dd = 0;
					int ret_dm = 0;
					get_declination(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt, &ret_dd, &ret_dm);
					sprintf(tmp_str, "M%s", MavLinkVars[mav_id].name);
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

	draw_text_button(esContext, "load", VIEW_MODE_FCMENU, "[LOAD FILE]", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_param_load, 1.0);
	draw_text_button(esContext, "save", VIEW_MODE_FCMENU, "[SAVE FILE]", FONT_WHITE, -0.5, 0.9, 0.002, 0.06, 1, 0, mavlink_param_save, 1.0);
	draw_text_button(esContext, "upload", VIEW_MODE_FCMENU, "[UPLOAD ALL]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_param_upload_all, 1.0);


	if (ModelData[ModelActive].teletype != TELETYPE_ARDUPILOT && ModelData[ModelActive].teletype != TELETYPE_MEGAPIRATE_NG) {
		draw_text_button(esContext, "flash_r", VIEW_MODE_FCMENU, "[LOAD FLASH]", FONT_WHITE, 0.5, 0.9, 0.002, 0.06, 1, 0, mavlink_flashload, 0.0);
		draw_text_button(esContext, "flash_w", VIEW_MODE_FCMENU, "[WRITE FLASH]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_flash, 0.0);
	}

	if (flag == 0) {
		draw_text_f(esContext, -0.4, 0.0, 0.05, 0.05, FONT_BLACK_BG, "No Mavlink-Parameters found");
	}

	screen_keyboard(esContext);
	screen_filesystem(esContext);
}

