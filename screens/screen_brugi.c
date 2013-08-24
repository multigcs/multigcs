
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
#include <brugi.h>
#include <screen_brugi.h>


#define SLIDER_START	-1.0
#define SLIDER_LEN	2.0

static int16_t brugi_selected = -1;
static BrugiValue *slider_value = NULL;
static char *slider_name = NULL;
static float slider_lastvalue = 0.0;

uint8_t brugi_gyrocal (char *name, float x, float y, int8_t button, float data) {
	brugi_send_cmd("GC\n");
	return 0;
}

uint8_t brugi_defaults (char *name, float x, float y, int8_t button, float data) {
	brugi_send_cmd("SD\n");
	SDL_Delay(100);
	brugi_send_cmd("par\n");
	return 0;
}

uint8_t brugi_save_to_flash (char *name, float x, float y, int8_t button, float data) {
	brugi_send_cmd("WE\n");
	SDL_Delay(100);
	brugi_send_cmd("par\n");
	return 0;
}

uint8_t brugi_read_from_flash (char *name, float x, float y, int8_t button, float data) {
	brugi_send_cmd("RE\n");
	SDL_Delay(100);
	brugi_send_cmd("par\n");
	return 0;
}

uint8_t brugi_slider_move (char *name, float x, float y, int8_t button, float data) {
	float new = slider_value->value;
	if (button == 4) {
		new += slider_value->step;
	} else if (button == 5) {
		new -= slider_value->step;
	} else {
		float percent = (x - SLIDER_START) * 100.0 / SLIDER_LEN;
		if (percent > 100.0) {
			percent = 100.0;
		} else if (percent < 0.0) {
			percent = 0.0;
		} else {
		}
		float diff = slider_value->max - slider_value->min;
		new = percent * diff / 100.0 + slider_value->min;
//		printf("slider: %s %f %f %f %f\n", name + 1, x, percent, new, data);
	}
	if (slider_value->type == 0) {
		slider_value->value = (float)(int)new;
	} else {
		slider_value->value = new;
	}
	brugi_set_value(slider_name, slider_value->value * slider_value->scale - slider_value->offset);
	return 0;
}


static uint8_t brugi_select (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	brugi_selected = (int16_t)data;
	return 0;
}

static uint8_t edit_value (ESContext *esContext, char *name, uint8_t type, BrugiValue *value) {
	char tmp_str[1024];
	slider_value = value;
	slider_name = name;
	if (value->min > value->value) {
		value->value = value->min;
	}
	if (value->max < value->value) {
		value->value = value->max;
	}
	if (value->type == 0) {
		sprintf(tmp_str, "%s = %0.0f", name, value->value);
	} else {
		sprintf(tmp_str, "%s = %0.3f", name, value->value);
	}
	draw_button(esContext, name, VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, -1.0);
	draw_box_f3c2(esContext, SLIDER_START, -0.7 + 3 * 0.14, 0.001, SLIDER_START + SLIDER_LEN, -0.7 + 3 * 0.14 + 0.1, 0.001, 55, 55, 55, 220, 75, 45, 85, 100);
	draw_box_f3c2(esContext, SLIDER_START, -0.7 + 3 * 0.14, 0.001, SLIDER_START + ((value->value - value->min) * SLIDER_LEN / (value->max - value->min)), -0.7 + 3 * 0.14 + 0.1, 0.001, 255, 255, 55, 220, 175, 145, 85, 100);
	set_button(tmp_str, view_mode, SLIDER_START, -0.7 + 3 * 0.14, SLIDER_START + SLIDER_LEN, -0.7 + 3 * 0.14 + 0.1, brugi_slider_move, (float)3, 1);

	return 0;
}


void screen_brugi (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	draw_title(esContext, "Brugi (Brushless-Gimbal)");
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	uint16_t n = 0;
	char tmp_str[1024];

	if (1 == 0) {
	} else if (brugi_selected == 0) {
		edit_value(esContext, "vers", 0, &brugi_setup.vers);
	} else if (brugi_selected == 1) {
		edit_value(esContext, "gyroPitchKp", 0, &brugi_setup.gyroPitchKp);
	} else if (brugi_selected == 2) {
		edit_value(esContext, "gyroPitchKi", 0, &brugi_setup.gyroPitchKi);
	} else if (brugi_selected == 3) {
		edit_value(esContext, "gyroPitchKd", 0, &brugi_setup.gyroPitchKd);
	} else if (brugi_selected == 4) {
		edit_value(esContext, "gyroRollKp", 0, &brugi_setup.gyroRollKp);
	} else if (brugi_selected == 5) {
		edit_value(esContext, "gyroRollKi", 0, &brugi_setup.gyroRollKi);
	} else if (brugi_selected == 6) {
		edit_value(esContext, "gyroRollKd", 0, &brugi_setup.gyroRollKd);
	} else if (brugi_selected == 7) {
		edit_value(esContext, "accTimeConstant", 0, &brugi_setup.accTimeConstant);
	} else if (brugi_selected == 8) {
		edit_value(esContext, "mpuLPF", 0, &brugi_setup.mpuLPF);
	} else if (brugi_selected == 9) {
		edit_value(esContext, "angleOffsetPitch", 0, &brugi_setup.angleOffsetPitch);
	} else if (brugi_selected == 10) {
		edit_value(esContext, "angleOffsetRoll", 0, &brugi_setup.angleOffsetRoll);
	} else if (brugi_selected == 11) {
		brugi_selected = -1;
		brugi_setup.dirMotorPitch.value = 1.0 - brugi_setup.dirMotorPitch.value;
		brugi_set_value("dirMotorPitch", brugi_setup.dirMotorPitch.value * brugi_setup.dirMotorPitch.scale - brugi_setup.dirMotorPitch.offset);
	} else if (brugi_selected == 12) {
		brugi_selected = -1;
		brugi_setup.dirMotorRoll.value = 1.0 - brugi_setup.dirMotorRoll.value;
		brugi_set_value("dirMotorRoll", brugi_setup.dirMotorRoll.value * brugi_setup.dirMotorRoll.scale - brugi_setup.dirMotorRoll.offset);
	} else if (brugi_selected == 13) {
		edit_value(esContext, "motorNumberPitch", 0, &brugi_setup.motorNumberPitch);
	} else if (brugi_selected == 14) {
		edit_value(esContext, "motorNumberRoll", 0, &brugi_setup.motorNumberRoll);
	} else if (brugi_selected == 15) {
		edit_value(esContext, "maxPWMmotorPitch", 0, &brugi_setup.maxPWMmotorPitch);
	} else if (brugi_selected == 16) {
		edit_value(esContext, "maxPWMmotorRoll", 0, &brugi_setup.maxPWMmotorRoll);
	} else if (brugi_selected == 17) {
		edit_value(esContext, "minRCPitch", 0, &brugi_setup.minRCPitch);
	} else if (brugi_selected == 18) {
		edit_value(esContext, "maxRCPitch", 0, &brugi_setup.maxRCPitch);
	} else if (brugi_selected == 19) {
		edit_value(esContext, "minRCRoll", 0, &brugi_setup.minRCRoll);
	} else if (brugi_selected == 20) {
		edit_value(esContext, "maxRCRoll", 0, &brugi_setup.maxRCRoll);
	} else if (brugi_selected == 21) {
		edit_value(esContext, "rcGain", 0, &brugi_setup.rcGain);
	} else if (brugi_selected == 22) {
		edit_value(esContext, "rcLPF", 0, &brugi_setup.rcLPF);
	} else if (brugi_selected == 23) {
		brugi_selected = -1;
		brugi_setup.rcModePPM.value = 1.0 - brugi_setup.rcModePPM.value;
		brugi_set_value("rcModePPM", brugi_setup.rcModePPM.value * brugi_setup.rcModePPM.scale - brugi_setup.rcModePPM.offset);
	} else if (brugi_selected == 24) {
		edit_value(esContext, "rcChannelPitch", 0, &brugi_setup.rcChannelPitch);
	} else if (brugi_selected == 25) {
		edit_value(esContext, "rcChannelRoll", 0, &brugi_setup.rcChannelRoll);
	} else if (brugi_selected == 26) {
		edit_value(esContext, "rcMid", 0, &brugi_setup.rcMid);
	} else if (brugi_selected == 27) {
		brugi_selected = -1;
		brugi_setup.rcAbsolute.value = 1.0 - brugi_setup.rcAbsolute.value;
		brugi_set_value("rcAbsolute", brugi_setup.rcAbsolute.value * brugi_setup.rcAbsolute.scale - brugi_setup.rcAbsolute.offset);
	} else if (brugi_selected == 28) {
		edit_value(esContext, "accOutput", 0, &brugi_setup.accOutput);
	} else if (brugi_selected == 29) {
		brugi_selected = -1;
		brugi_setup.enableGyro.value = 1.0 - brugi_setup.enableGyro.value;
		brugi_set_value("enableGyro", brugi_setup.enableGyro.value * brugi_setup.enableGyro.scale - brugi_setup.enableGyro.offset);
	} else if (brugi_selected == 30) {
		brugi_selected = -1;
		brugi_setup.enableACC.value = 1.0 - brugi_setup.enableACC.value;
		brugi_set_value("enableACC", brugi_setup.enableACC.value * brugi_setup.enableACC.scale - brugi_setup.enableACC.offset);
	} else if (brugi_selected == 31) {
		brugi_selected = -1;
		brugi_setup.axisReverseZ.value = 1.0 - brugi_setup.axisReverseZ.value;
		brugi_set_value("axisReverseZ", brugi_setup.axisReverseZ.value * brugi_setup.axisReverseZ.scale - brugi_setup.axisReverseZ.offset);
	} else if (brugi_selected == 32) {
		brugi_selected = -1;
		brugi_setup.axisSwapXY.value = 1.0 - brugi_setup.axisSwapXY.value;
		brugi_set_value("axisSwapXY", brugi_setup.axisSwapXY.value * brugi_setup.axisSwapXY.scale - brugi_setup.axisSwapXY.offset);
	} else {
	
		sprintf(tmp_str, "%20s %0.3f", "vers", brugi_setup.vers.value);
		draw_button(esContext, "vers", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)0);
		sprintf(tmp_str, "%20s %0.3f", "gyroPitchKp", brugi_setup.gyroPitchKp.value);
		draw_button(esContext, "gyroPitchKp", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)1);
		sprintf(tmp_str, "%20s %0.3f", "gyroPitchKi", brugi_setup.gyroPitchKi.value);
		draw_button(esContext, "gyroPitchKi", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)2);
		sprintf(tmp_str, "%20s %0.3f", "gyroPitchKd", brugi_setup.gyroPitchKd.value);
		draw_button(esContext, "gyroPitchKd", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)3);
		sprintf(tmp_str, "%20s %0.3f", "gyroRollKp", brugi_setup.gyroRollKp.value);
		draw_button(esContext, "gyroRollKp", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)4);
		sprintf(tmp_str, "%20s %0.3f", "gyroRollKi", brugi_setup.gyroRollKi.value);
		draw_button(esContext, "gyroRollKi", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)5);
		sprintf(tmp_str, "%20s %0.3f", "gyroRollKd", brugi_setup.gyroRollKd.value);
		draw_button(esContext, "gyroRollKd", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)6);
		sprintf(tmp_str, "%20s %0.0f", "accTimeConstant", brugi_setup.accTimeConstant.value);
		draw_button(esContext, "accTimeConstant", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)7);
		sprintf(tmp_str, "%20s %0.0f", "mpuLPF", brugi_setup.mpuLPF.value);
		draw_button(esContext, "mpuLPF", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)8);
		sprintf(tmp_str, "%20s %0.3f", "angleOffsetPitch", brugi_setup.angleOffsetPitch.value);
		draw_button(esContext, "angleOffsetPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)9);
		sprintf(tmp_str, "%20s %0.3f", "angleOffsetRoll", brugi_setup.angleOffsetRoll.value);
		draw_button(esContext, "angleOffsetRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)10);
		sprintf(tmp_str, "%20s %0.0f", "dirMotorPitch", brugi_setup.dirMotorPitch.value);
		draw_button(esContext, "dirMotorPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)11);
		sprintf(tmp_str, "%20s %0.0f", "dirMotorRoll", brugi_setup.dirMotorRoll.value);
		draw_button(esContext, "dirMotorRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)12);
		sprintf(tmp_str, "%20s %0.0f", "motorNumberPitch", brugi_setup.motorNumberPitch.value);
		draw_button(esContext, "motorNumberPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)13);
		sprintf(tmp_str, "%20s %0.0f", "motorNumberRoll", brugi_setup.motorNumberRoll.value);
		draw_button(esContext, "motorNumberRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)14);
		sprintf(tmp_str, "%20s %0.3f", "maxPWMmotorPitch", brugi_setup.maxPWMmotorPitch.value);
		draw_button(esContext, "maxPWMmotorPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)15);
		n = 0;
		sprintf(tmp_str, "%20s %0.3f", "maxPWMmotorRoll", brugi_setup.maxPWMmotorRoll.value);
		draw_button(esContext, "maxPWMmotorRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)16);
		sprintf(tmp_str, "%20s %0.0f", "minRCPitch", brugi_setup.minRCPitch.value);
		draw_button(esContext, "minRCPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)17);
		sprintf(tmp_str, "%20s %0.0f", "maxRCPitch", brugi_setup.maxRCPitch.value);
		draw_button(esContext, "maxRCPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)18);
		sprintf(tmp_str, "%20s %0.0f", "minRCRoll", brugi_setup.minRCRoll.value);
		draw_button(esContext, "minRCRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)19);
		sprintf(tmp_str, "%20s %0.0f", "maxRCRoll", brugi_setup.maxRCRoll.value);
		draw_button(esContext, "maxRCRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)20);
		sprintf(tmp_str, "%20s %0.3f", "rcGain", brugi_setup.rcGain.value);
		draw_button(esContext, "rcGain", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)21);
		sprintf(tmp_str, "%20s %0.3f", "rcLPF", brugi_setup.rcLPF.value);
		draw_button(esContext, "rcLPF", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)22);
		sprintf(tmp_str, "%20s %0.0f", "rcModePPM", brugi_setup.rcModePPM.value);
		draw_button(esContext, "rcModePPM", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)23);
		sprintf(tmp_str, "%20s %0.0f", "rcChannelPitch", brugi_setup.rcChannelPitch.value);
		draw_button(esContext, "rcChannelPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)24);
		sprintf(tmp_str, "%20s %0.0f", "rcChannelRoll", brugi_setup.rcChannelRoll.value);
		draw_button(esContext, "rcChannelRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)25);
		sprintf(tmp_str, "%20s %0.0f", "rcMid", brugi_setup.rcMid.value);
		draw_button(esContext, "rcMid", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)26);
		sprintf(tmp_str, "%20s %0.0f", "rcAbsolute", brugi_setup.rcAbsolute.value);
		draw_button(esContext, "rcAbsolute", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)27);
		sprintf(tmp_str, "%20s %0.3f", "accOutput", brugi_setup.accOutput.value);
		draw_button(esContext, "accOutput", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)28);
		sprintf(tmp_str, "%20s %0.0f", "enableGyro", brugi_setup.enableGyro.value);
		draw_button(esContext, "enableGyro", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)29);
		sprintf(tmp_str, "%20s %0.0f", "enableACC", brugi_setup.enableACC.value);
		draw_button(esContext, "enableACC", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)30);
		sprintf(tmp_str, "%20s %0.0f", "axisReverseZ", brugi_setup.axisReverseZ.value);
		draw_button(esContext, "axisReverseZ", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)31);
		sprintf(tmp_str, "%20s %0.0f", "axisSwapXY", brugi_setup.axisSwapXY.value);
		draw_button(esContext, "axisSwapXY", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_select, (float)32);
	}

	draw_button(esContext, "gyrocal", VIEW_MODE_FCMENU, "Gyro-Calibration", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, brugi_gyrocal, 0.0);
	draw_button(esContext, "defaults", VIEW_MODE_FCMENU, "Defaults", FONT_WHITE, -0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, brugi_defaults, 0.0);
	draw_button(esContext, "fload", VIEW_MODE_FCMENU, "Flash-Load", FONT_WHITE, 0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, brugi_read_from_flash, 0.0);
	draw_button(esContext, "fsave", VIEW_MODE_FCMENU, "Flash-Save", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, brugi_save_to_flash, 0.0);

}

