
#include <libudev.h>
#include <stdint.h>
#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <math.h>
#include <userdata.h>
#include <model.h>
#include <serial.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <model.h>
#include <main.h>
#include <screen_baseflightcli.h>
#include <SDL/SDL_thread.h>
#include <screen_keyboard.h>


uint8_t baseflightcli_startup = 0;
int baseflightcli_fd = -1;
uint8_t baseflightcli_mode = 0;

#define BASEFLIGHTCLI_MAX_BUFFER 500
static char baseflightcli_buffer[BASEFLIGHTCLI_MAX_BUFFER + 1];

typedef struct {
	char name[200];
	char group[200];
	float value;
	float min;
	float max;
	uint8_t type;
} BfSetValues;
static BfSetValues bf_set_value[200];

typedef struct {
	char name[200];
	char filter[30];
} BfSetGroups;
static BfSetGroups bf_set_groups[200];

typedef struct {
	char name[200];
} BfMixer;
static BfMixer bf_mixer[30];

static char groupnames[200][200];

static int16_t baseflightcli_group = 0;


void baseflightcli_add_value (char *vname, uint8_t type, float vval, float vmin, float vmax) {
	uint16_t n3 = 0;
	uint8_t flag = 0;
	uint8_t flag2 = 0;
	flag = 0;
	flag2 = 0;
	for (n3 = 0; n3 < 199; n3++) {
		if (strcmp(bf_set_value[n3].name, vname) == 0) {
//			printf("found: %s = %f\n", vname, vval);
			bf_set_value[n3].value = vval;
			if (vmin != 0.0 || vmax != 0.0) {
				bf_set_value[n3].min = vmin;
				bf_set_value[n3].max = vmax;
			}
			flag = n3;
		} else if (flag2 == 0 && bf_set_value[n3].name[0] == 0) {
			flag2 = n3;
		}
	}
	if (flag == 0) {
//		printf("add(%i): %s = %f\n", flag2, vname, vval);
		strcpy(bf_set_value[flag2].name, vname);
		bf_set_value[flag2].value = vval;
		if (vmin != 0.0 || vmax != 0.0) {
			bf_set_value[flag2].min = vmin;
			bf_set_value[flag2].max = vmax;
		}
		bf_set_value[n3].type = type;
		strcpy(bf_set_value[flag2].group, "etc");
		for (n3 = 0; n3 < 100; n3++) {
			if (bf_set_groups[n3].filter[0] != 0 && strstr(bf_set_value[flag2].name, bf_set_groups[n3].filter) > 0) {
				strcpy(bf_set_value[flag2].group, bf_set_groups[n3].name);
				break;
			}
		}
		flag = 0;
		for (n3 = 0; n3 < 100; n3++) {
			if (strcmp(groupnames[n3], bf_set_value[flag2].group) == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			for (n3 = 0; n3 < 100; n3++) {
				if (groupnames[n3][0] == 0) {
					strcpy(groupnames[n3], bf_set_value[flag2].group);
					break;
				}
			}
		}
	}
}

void baseflightcli_update (void) {
	static uint8_t n = 0;
	static uint8_t nn = 0;
	static uint8_t new = 0;
	static uint8_t read_buffer[501];
	static uint8_t read_num = 0;
	static uint8_t read_y = 0;
	static uint8_t read_x = 0;
	static uint8_t n2 = 0;
	if (baseflightcli_fd < 0) {
		return;
	}
	read_buffer[0] = 0;
	while ((read_num = read(baseflightcli_fd, read_buffer, 1)) > 0) {
		for (nn = 0; nn < read_num; nn++) {
			new = read_buffer[nn];
			if (new == '\r') {
			} else if (new == '\n') {
				if (baseflightcli_buffer[0] == 0) {
				} else if (baseflightcli_buffer[0] == '#') {
					printf("## %s\n", baseflightcli_buffer);
				} else if (strncmp(baseflightcli_buffer, "Available mixers:", 2) == 0) {
					n2 = 0;
					nn = 0;
					char tmp_str[400];
					for (n = 18; n < strlen(baseflightcli_buffer) + 1; n++) {
						if (baseflightcli_buffer[n] == ' ' || baseflightcli_buffer[n] == '\n' || baseflightcli_buffer[n] == 0) {
							strcpy(bf_mixer[n2++].name, tmp_str);
							bf_mixer[n2].name[0] = 0;
							nn = 0;
							tmp_str[nn] = 0;
						} else {
							tmp_str[nn++] = baseflightcli_buffer[n];
							tmp_str[nn] = 0;
						}
					}
				} else if (strncmp(baseflightcli_buffer, "ERR:", 4) == 0) {
					printf("## %s\n", baseflightcli_buffer);
				} else if (strncmp(baseflightcli_buffer, "feature ", 8) == 0) {
					char tmp_var[100];
					float tmp_val = 0.0;
					if (baseflightcli_buffer[8] == '-') {
						strcpy(tmp_var, baseflightcli_buffer + 9);
						tmp_val = 0.0;
					} else {
						strcpy(tmp_var, baseflightcli_buffer + 8);
						tmp_val = 1.0;
					}
					char tmp_str[400];
					sprintf(tmp_str, "feature_%s", tmp_var);
					baseflightcli_add_value(tmp_str, 0, tmp_val, 0.0, 1.0);
				} else if (strncmp(baseflightcli_buffer, "aux ", 4) == 0) {
					char tmp_str[400];
					int vnum = 0;
					int vval = 0;
					sscanf(baseflightcli_buffer, "aux %i %i", &vnum, &vval);
					sprintf(tmp_str, "aux_%i", vnum);
					baseflightcli_add_value(tmp_str, 0, (float)vval, 0.0, 4096.0);
				} else if (strncmp(baseflightcli_buffer, "mixer ", 6) == 0) {
					float tmp_val = 0.0;
					int mn = 0;
					int mm = 0;
					for (n = 0; n < 30; n++) {
						if (bf_mixer[n].name[0] != 0) {
							mm++;
						}
						if (strcmp(bf_mixer[n].name, baseflightcli_buffer + 6) == 0) {
							tmp_val = (float)n;
						}
					}
					baseflightcli_add_value("mixer", 0, tmp_val, 0.0, (float)(mm));
				} else if (strstr(baseflightcli_buffer, "=") > 0) {
					if (strncmp(baseflightcli_buffer, "set ", 4) == 0) {
						char tmp_str[400];
						strcpy(tmp_str, baseflightcli_buffer + 4);
						strcpy(baseflightcli_buffer, tmp_str);
					}
					char vname[101];
					char vchar = ' ';
					float vval = 0.0;
					float vmin = 0.0;
					float vmax = 0.0;
					uint8_t type = 0;
					sscanf(baseflightcli_buffer, "%s %c %f %f %f", &vname, &vchar, &vval, &vmin, &vmax);
					if (strstr(baseflightcli_buffer, ".") > 0) {
						type = 1;
					}

					baseflightcli_add_value(vname, type, vval, vmin, vmax);

				} else {
					printf("#UNKNOWN# %s\n", baseflightcli_buffer);
				}
				baseflightcli_buffer[0] = 0;
				read_x = 0;
			} else {
				if (read_x < BASEFLIGHTCLI_MAX_BUFFER - 1) {
					baseflightcli_buffer[read_x++] = new;
					baseflightcli_buffer[read_x] = 0;
				}
			}
		}
	}
}

static uint8_t baseflightcli_null (char *name, float x, float y, int8_t button, float data) {
	printf("baseflightcli_null: %f\n", data);
	return 0;
}

static uint8_t baseflightcli_mixer_set (char *name, float x, float y, int8_t button, float data) {
	printf("baseflightcli_mixer_set: %s %f\n", name, data);
	int n = 0;
	int nn = (int)data;
	for (n = 0; n < (int)bf_set_value[nn].max; n++) {
		if (strcmp(bf_mixer[n].name, name) == 0) {
			bf_set_value[nn].value = (float)n;
			break;
		}
	}
	char tmp_str[400];
	sprintf(tmp_str, "mixer %s\n", bf_mixer[(int)bf_set_value[nn].value].name);
	write(baseflightcli_fd, tmp_str, strlen(tmp_str));
	printf(tmp_str);
	return 0;
}

static uint8_t baseflightcli_aux_toggle (char *name, float x, float y, int8_t button, float data) {
	int aux_n = atoi(name + 4);
	int n = atoi(name + 6);
	if (name[6] == '_') {
		n = atoi(name + 7);
	}
	int nn = (int)data;
	int new = (int)bf_set_value[nn].value;
	if (new & (1<<n)) {
		new &= ~(1<<n);
	} else {
		new |= (1<<n);
	}
	bf_set_value[nn].value = (float)new;

	char tmp_str[400];
	sprintf(tmp_str, "aux %i %i\n", aux_n, new);
	write(baseflightcli_fd, tmp_str, strlen(tmp_str));
	printf(tmp_str);

	return 0;
}

static uint8_t baseflightcli_defaults (char *name, float x, float y, int8_t button, float data) {
	printf("baseflightcli_defaults: %f\n", data);

	char tmp_str[400];
	sprintf(tmp_str, "defaults\n");
	write(baseflightcli_fd, tmp_str, strlen(tmp_str));
	printf(tmp_str);

	return 0;
}


static uint8_t baseflightcli_group_open (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	printf("baseflightcli_group_open: %f\n", data);
	baseflightcli_group = data;
	return 0;
}

static uint8_t baseflightcli_read (char *name, float x, float y, int8_t button, float data) {
	printf("reading baseflight cli...\n");
	write(baseflightcli_fd, "####\n", 5);
	write(baseflightcli_fd, "mixer list\n", 11);
	write(baseflightcli_fd, "set *\n", 6);
	write(baseflightcli_fd, "dump\n", 5);
	return 0;
}

static uint8_t baseflightcli_save (char *name, float x, float y, int8_t button, float data) {
	write(baseflightcli_fd, "save\n", 5);
	return 0;
}

uint8_t baseflightcli_init (char *port, uint32_t baud) {
	uint16_t group_n = 0;

	strcpy(bf_set_groups[group_n].name, "feature");
	strcpy(bf_set_groups[group_n++].filter, "feature");

	strcpy(bf_set_groups[group_n].name, "mixer");
	strcpy(bf_set_groups[group_n++].filter, "mixer");

	strcpy(bf_set_groups[group_n].name, "aux");
	strcpy(bf_set_groups[group_n++].filter, "aux");

	strcpy(bf_set_groups[group_n].name, "rc");
	strcpy(bf_set_groups[group_n++].filter, "rc");

	strcpy(bf_set_groups[group_n].name, "rc");
	strcpy(bf_set_groups[group_n++].filter, "failsafe");

	strcpy(bf_set_groups[group_n].name, "rc");
	strcpy(bf_set_groups[group_n++].filter, "trim");

	strcpy(bf_set_groups[group_n].name, "gimbal");
	strcpy(bf_set_groups[group_n++].filter, "gimbal");

	strcpy(bf_set_groups[group_n].name, "wing");
	strcpy(bf_set_groups[group_n++].filter, "wing");

	strcpy(bf_set_groups[group_n].name, "tri");
	strcpy(bf_set_groups[group_n++].filter, "tri");

	strcpy(bf_set_groups[group_n].name, "gyro");
	strcpy(bf_set_groups[group_n++].filter, "gyro");

	strcpy(bf_set_groups[group_n].name, "acc");
	strcpy(bf_set_groups[group_n++].filter, "acc");

	strcpy(bf_set_groups[group_n].name, "mag");
	strcpy(bf_set_groups[group_n++].filter, "mag");

	strcpy(bf_set_groups[group_n].name, "gps");
	strcpy(bf_set_groups[group_n++].filter, "gps");

	strcpy(bf_set_groups[group_n].name, "nav");
	strcpy(bf_set_groups[group_n++].filter, "nav");

	strcpy(bf_set_groups[group_n].name, "led");
	strcpy(bf_set_groups[group_n++].filter, "led");

	strcpy(bf_set_groups[group_n].name, "led");
	strcpy(bf_set_groups[group_n++].filter, "LED");

	strcpy(bf_set_groups[group_n].name, "led");
	strcpy(bf_set_groups[group_n++].filter, "MWCRGB");

	strcpy(bf_set_groups[group_n].name, "sonar");
	strcpy(bf_set_groups[group_n++].filter, "sonar");

	strcpy(bf_set_groups[group_n].name, "dir");
	strcpy(bf_set_groups[group_n++].filter, "dir");

	strcpy(bf_set_groups[group_n].name, "thr");
	strcpy(bf_set_groups[group_n++].filter, "thr");

	strcpy(bf_set_groups[group_n].name, "pid");
	strcpy(bf_set_groups[group_n++].filter, "p_");

	strcpy(bf_set_groups[group_n].name, "pid");
	strcpy(bf_set_groups[group_n++].filter, "i_");

	strcpy(bf_set_groups[group_n].name, "pid");
	strcpy(bf_set_groups[group_n++].filter, "d_");

	printf("init baseflightcli serial port...\n");
	baseflightcli_fd = serial_open(port, baud);

	baseflightcli_read("", 0.0, 0.0, 0, 0.0);

	return 0;
}

#define SLIDER_START	0.2
#define SLIDER_LEN	0.5

uint8_t baseflightcli_toggle (char *name, float x, float y, int8_t button, float data) {
	char tmp_str[400];
	int nn = (int)data;
	printf("toggle(%i): %s %f\n", nn, bf_set_value[nn].name, bf_set_value[nn].value);
	bf_set_value[nn].value = 1.0 - bf_set_value[nn].value;
	if (strncmp(bf_set_value[nn].name, "feature_", 8) == 0) {
		if (bf_set_value[nn].value == 0.0) {
			sprintf(tmp_str, "feature -%s\n", bf_set_value[nn].name + 8);
		} else {
			sprintf(tmp_str, "feature %s\n", bf_set_value[nn].name + 8);
		}
	} else {
		if (bf_set_value[nn].type == 0) {
			sprintf(tmp_str, "set %s=%i\n", bf_set_value[nn].name, (int)bf_set_value[nn].value);
		} else {
			sprintf(tmp_str, "set %s=%f\n", bf_set_value[nn].name, bf_set_value[nn].value);
		}
	}
	write(baseflightcli_fd, tmp_str, strlen(tmp_str));
	printf(tmp_str);
	return 0;
}

uint8_t baseflightcli_slider_move (char *name, float x, float y, int8_t button, float data) {
	int n = 0;
	int nn = (int)data;
	if (button == 4) {
		if (bf_set_value[nn].type == 0) {
			bf_set_value[nn].value += 1;
		} else {
			bf_set_value[nn].value += 0.01;
		}
	} else if (button == 5) {
		if (bf_set_value[nn].type == 0) {
			bf_set_value[nn].value -= 1;
		} else {
			bf_set_value[nn].value -= 0.01;
		}
	} else {
		float percent = (x - SLIDER_START) * 100.0 / SLIDER_LEN;
		if (percent > 100.0) {
			percent = 100.0;
		} else if (percent < 0.0) {
			percent = 0.0;
		}
		float diff = bf_set_value[nn].max - bf_set_value[nn].min;
		float new = percent * diff / 100.0 + bf_set_value[nn].min;
		if (bf_set_value[nn].type == 0) {
			int conv = (int)(new);
			new = (float)conv;
		}
		if (strstr(bf_set_value[nn].name, "baud") > 0) {
			float bauds[] = {1200.0, 2400.0, 9600.0, 38400.0, 57600.0, 115200.0, 200000.0};
			for (n = 0; n < 6; n++) {
				if (new <= bauds[n] + (bauds[n + 1] - bauds[n]) / 2) {
					new = bauds[n];
					break;
				}
			}
		}
		bf_set_value[nn].value = new;
	}
	if (bf_set_value[nn].value > bf_set_value[nn].max) {
		bf_set_value[nn].value = bf_set_value[nn].max;
	} else if (bf_set_value[nn].value < bf_set_value[nn].min) {
		bf_set_value[nn].value = bf_set_value[nn].min;
	}

	char tmp_str[400];
	if (strncmp(bf_set_value[nn].name, "mixer", 5) == 0) {
		sprintf(tmp_str, "mixer %s\n", bf_mixer[(int)bf_set_value[nn].value].name);
	} else if (bf_set_value[nn].type == 0) {
		sprintf(tmp_str, "set %s=%i\n", bf_set_value[nn].name, (int)bf_set_value[nn].value);
	} else {
		sprintf(tmp_str, "set %s=%f\n", bf_set_value[nn].name, bf_set_value[nn].value);
	}
	write(baseflightcli_fd, tmp_str, strlen(tmp_str));
	printf(tmp_str);
	return 0;
}


uint8_t baseflightcli_exit (void) {
	if (baseflightcli_fd < 0) {
		return;
	}
	serial_close(baseflightcli_fd);
	baseflightcli_fd = -1;
	return 0;
}

void screen_baseflightcli (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	draw_title(esContext, "BASEFLIGHTCLI");

	int n = 0;
	int n2 = 0;
	char tmp_str[200];
	char tmp_str2[100];
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif



	uint16_t nn = 0;
	uint16_t nn2 = 0;
	for (nn = 0; nn < 100; nn++) {
		if (groupnames[nn][0] != 0) {
			if (baseflightcli_group == nn) {
				draw_button(esContext, groupnames[nn], VIEW_MODE_FCMENU, groupnames[nn], FONT_GREEN, -1.3, -0.8 + nn * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, baseflightcli_group_open, (float)nn);
			} else {
				draw_button(esContext, groupnames[nn], VIEW_MODE_FCMENU, groupnames[nn], FONT_WHITE, -1.3, -0.8 + nn * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, baseflightcli_group_open, (float)nn);
			}
		}
	}
	uint8_t aux_flag = 0;
	if (baseflightcli_group != -1) {
		nn2 = 0;
		for (nn = 0; nn < 1000; nn++) {
			if (strcmp(bf_set_value[nn].group, groupnames[baseflightcli_group]) == 0) {
				if (strncmp(bf_set_value[nn].name, "aux_", 4) == 0) {
					if (aux_flag == 0) {
						aux_flag = 1;
						nn2++;
						n = 0;
						n++;
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "AUX1", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						n++;
						n++;
						n++;
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "AUX2", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						n++;
						n++;
						n++;
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "AUX3", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						n++;
						n++;
						n++;
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "AUX4", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						n++;
						nn2++;
						n = 0;
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "L", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "M", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "H", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						n++;
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "L", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "M", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "H", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						n++;
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "L", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "M", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "H", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						n++;
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "L", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "M", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "H", FONT_GREEN, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						nn2++;
					}
					draw_button(esContext, "name", VIEW_MODE_FCMENU, bf_set_value[nn].name, FONT_WHITE, -0.9, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, baseflightcli_null, (float)nn);
					tmp_str[0] = 0;
					n = 0;
					for (n2 = 0; n2 < 12; n2++) {
						sprintf(tmp_str, "%s_%i", bf_set_value[nn].name, n2);
						if ((int)bf_set_value[nn].value & (1<<n2)) {
							draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "1", FONT_WHITE, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						} else {
							draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "0", FONT_WHITE, -0.3 + n++ * 0.1, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_aux_toggle, (float)nn);
						}
						if (n2 == 2 || n2 == 5 || n2 == 8) {
							n++;
						}
					}
				} else if (strncmp(bf_set_value[nn].name, "mixer", 5) == 0) {
					draw_button(esContext, "name", VIEW_MODE_FCMENU, bf_set_value[nn].name, FONT_WHITE, -0.9, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, baseflightcli_null, (float)nn);
					for (n2 = 0; n2 < (int)bf_set_value[nn].max; n2++) {
						if (n2 == (int)bf_set_value[nn].value) {
							draw_button(esContext, bf_mixer[n2].name, VIEW_MODE_FCMENU, bf_mixer[n2].name, FONT_GREEN, 0.0, -0.8 + nn2++ * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, baseflightcli_mixer_set, (float)nn);
						} else {
							draw_button(esContext, bf_mixer[n2].name, VIEW_MODE_FCMENU, bf_mixer[n2].name, FONT_WHITE, 0.0, -0.8 + nn2++ * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, baseflightcli_mixer_set, (float)nn);
						}
					}
				} else {
					draw_button(esContext, "name", VIEW_MODE_FCMENU, bf_set_value[nn].name, FONT_WHITE, -0.9, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, baseflightcli_null, (float)nn);
					if (strncmp(bf_set_value[nn].name, "mixer", 5) == 0) {
						sprintf(tmp_str, "%s", bf_mixer[(int)bf_set_value[nn].value].name);
					} else if (bf_set_value[nn].type == 1) {
						sprintf(tmp_str, "%f", bf_set_value[nn].value);
					} else {
						sprintf(tmp_str, "%i", (int)bf_set_value[nn].value);
					}
					draw_button(esContext, "value", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, baseflightcli_null, (float)nn);
					if (bf_set_value[nn].type == 1) {
						sprintf(tmp_str, "%f -> %f", bf_set_value[nn].min, bf_set_value[nn].max);
					} else {
						sprintf(tmp_str, "%i -> %i", (int)bf_set_value[nn].min, (int)bf_set_value[nn].max);
					}
					draw_button(esContext, "minmax", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.7, -0.8 + nn2 * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, baseflightcli_null, (float)nn);
					sprintf(tmp_str, "slider_%s", bf_set_value[nn].name);
					draw_box_f3c2(esContext, SLIDER_START, -0.8 + nn2 * 0.07, 0.001, SLIDER_START + SLIDER_LEN, -0.8 + nn2 * 0.07 + 0.07, 0.001, 55, 55, 55, 220, 75, 45, 85, 100);
					if (bf_set_value[nn].min == 0.0 && bf_set_value[nn].max == 1.0) {
						if (bf_set_value[nn].value == 1.0) {
							draw_box_f3c2(esContext, SLIDER_START, -0.8 + nn2 * 0.07, 0.001, SLIDER_START + SLIDER_LEN, -0.8 + nn2 * 0.07 + 0.07, 0.001, 255, 255, 55, 220, 175, 145, 85, 100);
						}
						set_button(tmp_str, view_mode, SLIDER_START, -0.8 + nn2 * 0.07, SLIDER_START + SLIDER_LEN, -0.8 + nn2 * 0.07 + 0.07, baseflightcli_toggle, (float)nn, 0);
					} else {
						draw_box_f3c2(esContext, SLIDER_START, -0.8 + nn2 * 0.07, 0.001, SLIDER_START + ((bf_set_value[nn].value - bf_set_value[nn].min) * SLIDER_LEN / (bf_set_value[nn].max - bf_set_value[nn].min)), -0.8 + nn2 * 0.07 + 0.07, 0.001, 255, 255, 55, 220, 175, 145, 85, 100);
						set_button(tmp_str, view_mode, SLIDER_START, -0.8 + nn2 * 0.07, SLIDER_START + SLIDER_LEN, -0.8 + nn2 * 0.07 + 0.07, baseflightcli_slider_move, (float)nn, 1);
					}
				}
				nn2++;
			}
		}
	}

	draw_button(esContext, "defaults", VIEW_MODE_FCMENU, "[DEFAULT]", FONT_WHITE, -1.2, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_defaults, 0.0);
	draw_button(esContext, "read", VIEW_MODE_FCMENU, "[READ]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_read, 0.0);
	draw_button(esContext, "save", VIEW_MODE_FCMENU, "[SAVE]", FONT_WHITE, 1.2, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, baseflightcli_save, 0.0);

}

