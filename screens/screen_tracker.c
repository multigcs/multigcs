
#include <all.h>


#define SLIDER_START	-0.2
#define SLIDER_LEN	1.4

static uint8_t set_type = 0;

uint8_t tracker_cmd(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (strcmp(name + 1, "PAN_TRIM") == 0) {
		TrackerData[TRACKER_PAN_TRIM].value = tracker_pan_dir;
	} else if (strcmp(name + 1, "PITCH_TRIM") == 0) {
		TrackerData[TRACKER_PITCH_TRIM].value = tracker_pitch_dir;
	} else if (strcmp(name + 1, "SAVE") == 0) {
		tracker_setup_save();
	} else if (strcmp(name + 1, "LOAD") == 0) {
		tracker_setup_load();
	} else if (strcmp(name + 1, "DEFAULTS") == 0) {
		tracker_setup_defaults();
	} else if (strcmp(name + 1, "HOME") == 0) {
		tracker_set_home();
	} else if (strncmp(name + 1, "SETTYPE_", 8) == 0) {
		set_type = 0;
		trackertype = (uint8_t)data;
		reset_buttons();
	} else if (strcmp(name + 1, "TYPE") == 0) {
		set_type = 1 - set_type;
		reset_buttons();
	}
	return 0;
}

uint8_t tracker_move(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	float value = 0.0;
	float min = -100.0;
	float max = 100.0;
	min = TrackerData[(int)data].min;
	max = TrackerData[(int)data].max;
	value = TrackerData[(int)data].value;
	if (button == 4) {
	} else if (button == 5) {
	} else {
		float percent = (x - SLIDER_START) * 100.0 / SLIDER_LEN;
		if (percent > 100.0) {
			percent = 100.0;
		} else if (percent < 0.0) {
			percent = 0.0;
		}
		float diff = max - min;
		float new = percent * diff / 100.0 + min;
		//		SDL_Log("slider: %s %f %f %f %f\n", name + 1, x, percent, new, data);
		if (strstr(name, "baud") > 0) {
			float bauds[] = {1200.0, 2400.0, 9600.0, 38400.0, 57600.0, 115200.0, 200000.0};
			for (n = 0; n < 6; n++) {
				if (new <= bauds[n] + (bauds[n + 1] - bauds[n]) / 2) {
					new = bauds[n];
					break;
				}
			}
		}
		value = new;
	}
	if (value < min) {
		value = min;
	} else if (value > max) {
		value = max;
	}
	TrackerData[(int)data].value = value;
	return 0;
}


void screen_tracker(ESContext *esContext) {
	char tmp_str[1024];
	char tmp_str2[1024];
	uint8_t n = 0;
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	sprintf(tmp_str, "Antenna-Tracker (%s)", trackername[trackertype]);
	draw_title(esContext, tmp_str);
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	if (set_type == 1) {
		for (n = 0; n < TRACKER_TYPE_LAST; n++) {
			sprintf(tmp_str, "tSETTYPE_%s", trackername[n]);
			if (n == trackertype) {
				draw_text_button(esContext, tmp_str, setup.view_mode, trackername[n], FONT_GREEN, -0.8, -0.75 + n * 0.15, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, tracker_cmd, (float)n);
			} else {
				draw_text_button(esContext, tmp_str, setup.view_mode, trackername[n], FONT_WHITE, -0.8, -0.75 + n * 0.15, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, tracker_cmd, (float)n);
			}
		}
	} else {
		for (n = 0; n < TRACKER_MAX; n++) {
			if (trackertype == TRACKER_TYPE_ARDUINO && strstr(TrackerData[n].name, "PULSE") > 0) {
				continue;
			}
			draw_box_f3c2(esContext, SLIDER_START, -0.75 + n * 0.15, 0.002, SLIDER_START + SLIDER_LEN, -0.75 + n * 0.15 + 0.1, 0.002, 55, 55, 55, 220, 75, 45, 85, 100);
			if (strcmp(TrackerData[n].name, "PAN_TRIM") == 0 || strcmp(TrackerData[n].name, "PITCH_TRIM") == 0) {
				draw_box_f3c2(esContext, SLIDER_START + SLIDER_LEN / 2.0, -0.75 + n * 0.15, 0.002,
							  SLIDER_START + ((TrackerData[n].value - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1, 0.002, 55, 255, 155, 220, 81, 145, 185, 100);
			} else if (strcmp(TrackerData[n].name, "PAN_ANGLE_MIN") == 0 || strcmp(TrackerData[n].name, "PAN_ANGLE_MAX") == 0 || strcmp(TrackerData[n].name, "PITCH_ANGLE_MIN") == 0 ||
					   strcmp(TrackerData[n].name, "PITCH_ANGLE_MAX") == 0) {
				draw_box_f3c2(esContext, SLIDER_START + SLIDER_LEN / 2.0, -0.75 + n * 0.15, 0.002,
							  SLIDER_START + ((TrackerData[n].value - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1, 0.002, 55, 155, 155, 220, 81, 45, 185, 100);
			} else {
				draw_box_f3c2(esContext, SLIDER_START + SLIDER_LEN / 2.0, -0.75 + n * 0.15, 0.002,
							  SLIDER_START + ((TrackerData[n].value - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1, 0.002, 255, 255, 55, 220, 175, 145, 85, 100);
			}
			if (strcmp(TrackerData[n].name, "PAN_TRIM") == 0) {
				draw_line_f3(esContext, SLIDER_START + ((tracker_pan_dir - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 - 0.01, 0.002,
							 SLIDER_START + ((tracker_pan_dir - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1 + 0.01, 0.002, 255, 0, 0, 127);
				draw_line_f3(esContext, SLIDER_START + ((tracker_pan_dir_trimmed - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 - 0.01, 0.002,
							 SLIDER_START + ((tracker_pan_dir_trimmed - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1 + 0.01, 0.002, 0, 255, 0, 127);
			} else if (strcmp(TrackerData[n].name, "PITCH_TRIM") == 0) {
				draw_line_f3(esContext, SLIDER_START + ((tracker_pitch_dir - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 - 0.01, 0.002,
							 SLIDER_START + ((tracker_pitch_dir - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1 + 0.01, 0.002, 255, 0, 0, 127);
				draw_line_f3(esContext, SLIDER_START + ((tracker_pitch_dir_trimmed - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 - 0.01, 0.002,
							 SLIDER_START + ((tracker_pitch_dir_trimmed - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1 + 0.01, 0.002, 0, 255, 0, 127);
			} else if (strcmp(TrackerData[n].name, "PAN_ANGLE_MIN") == 0 || strcmp(TrackerData[n].name, "PAN_ANGLE_MAX") == 0) {
				draw_line_f3(esContext, SLIDER_START + ((tracker_pan_dir_trimmed - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 - 0.01, 0.002,
							 SLIDER_START + ((tracker_pan_dir_trimmed - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1 + 0.01, 0.002, 0, 0, 255, 127);
			} else if (strcmp(TrackerData[n].name, "PITCH_ANGLE_MIN") == 0 || strcmp(TrackerData[n].name, "PITCH_ANGLE_MAX") == 0) {
				draw_line_f3(esContext, SLIDER_START + ((tracker_pitch_dir_trimmed - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 - 0.01, 0.002,
							 SLIDER_START + ((tracker_pitch_dir_trimmed - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1 + 0.01, 0.002, 0, 0, 255, 127);
			} else if (strcmp(TrackerData[n].name, "PAN_PULSE_MIN") == 0 || strcmp(TrackerData[n].name, "PAN_PULSE_MAX") == 0) {
				float val = (tracker_pan_dir_trimmed - TrackerData[TRACKER_PAN_ANGLE_MIN].value) * (TrackerData[TRACKER_PAN_PULSE_MAX].value - TrackerData[TRACKER_PAN_PULSE_MIN].value) /
							(TrackerData[TRACKER_PAN_ANGLE_MAX].value - TrackerData[TRACKER_PAN_ANGLE_MIN].value) + TrackerData[TRACKER_PAN_PULSE_MIN].value;
				draw_line_f3(esContext, SLIDER_START + ((val - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 - 0.01, 0.002,
							 SLIDER_START + ((val - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1 + 0.01, 0.002, 0, 255, 255, 127);
			} else if (strcmp(TrackerData[n].name, "PITCH_PULSE_MIN") == 0 || strcmp(TrackerData[n].name, "PITCH_PULSE_MAX") == 0) {
				float val = (tracker_pitch_dir_trimmed - TrackerData[TRACKER_PITCH_ANGLE_MIN].value) * (TrackerData[TRACKER_PITCH_PULSE_MAX].value - TrackerData[TRACKER_PITCH_PULSE_MIN].value) /
							(TrackerData[TRACKER_PITCH_ANGLE_MAX].value - TrackerData[TRACKER_PITCH_ANGLE_MIN].value) + TrackerData[TRACKER_PITCH_PULSE_MIN].value;
				draw_line_f3(esContext, SLIDER_START + ((val - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 - 0.01, 0.002,
							 SLIDER_START + ((val - TrackerData[n].min) * SLIDER_LEN / (TrackerData[n].max - TrackerData[n].min)), -0.75 + n * 0.15 + 0.1 + 0.01, 0.002, 0, 255, 255, 127);
			}
			sprintf(tmp_str, "S%s", TrackerData[n].name);
			set_button(tmp_str, setup.view_mode, SLIDER_START, -0.75 + n * 0.15, SLIDER_START + SLIDER_LEN, -0.75 + n * 0.15 + 0.1, tracker_move, (float)n, 1);
			sprintf(tmp_str, "T%s", TrackerData[n].name);
			sprintf(tmp_str2, "%s: %0.1f", TrackerData[n].name, TrackerData[n].value);
			draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str2, FONT_WHITE, -1.2, -0.75 + n * 0.15 + 0.02, 0.003, 0.06, ALIGN_LEFT, ALIGN_TOP, tracker_cmd, 0.0);
		}
	}
	draw_text_button(esContext, "tLOAD", setup.view_mode, "LOAD", FONT_WHITE, -0.8, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, tracker_cmd, 0.0);
	draw_text_button(esContext, "tSAVE", setup.view_mode, "SAVE", FONT_WHITE, -0.4, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, tracker_cmd, 0.0);
	draw_text_button(esContext, "tTYPE", setup.view_mode, "TYPE", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, tracker_cmd, 0.0);
	draw_text_button(esContext, "tHOME", setup.view_mode, "SET_HOME", FONT_WHITE, 0.4, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, tracker_cmd, 0.0);
	draw_text_button(esContext, "tDEFAULTS", setup.view_mode, "DEFAULTS", FONT_WHITE, 0.8, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, tracker_cmd, 0.0);
}

