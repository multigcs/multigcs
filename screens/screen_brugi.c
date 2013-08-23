
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


static uint8_t brugi_setval (char *name, float x, float y, int8_t button, float data) {
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


	sprintf(tmp_str, "%20s %i", "vers", brugi_setup.vers);
	draw_button(esContext, "vers", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "gyroPitchKp", brugi_setup.gyroPitchKp);
	draw_button(esContext, "gyroPitchKp", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "gyroPitchKi", brugi_setup.gyroPitchKi);
	draw_button(esContext, "gyroPitchKi", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "gyroPitchKd", brugi_setup.gyroPitchKd);
	draw_button(esContext, "gyroPitchKd", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "gyroRollKp", brugi_setup.gyroRollKp);
	draw_button(esContext, "gyroRollKp", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "gyroRollKi", brugi_setup.gyroRollKi);
	draw_button(esContext, "gyroRollKi", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "gyroRollKd", brugi_setup.gyroRollKd);
	draw_button(esContext, "gyroRollKd", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "accTimeConstant", brugi_setup.accTimeConstant);
	draw_button(esContext, "accTimeConstant", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "mpuLPF", brugi_setup.mpuLPF);
	draw_button(esContext, "mpuLPF", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "angleOffsetPitch", brugi_setup.angleOffsetPitch);
	draw_button(esContext, "angleOffsetPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "angleOffsetRoll", brugi_setup.angleOffsetRoll);
	draw_button(esContext, "angleOffsetRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "dirMotorPitch", brugi_setup.dirMotorPitch);
	draw_button(esContext, "dirMotorPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "dirMotorRoll", brugi_setup.dirMotorRoll);
	draw_button(esContext, "dirMotorRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "motorNumberPitch", brugi_setup.motorNumberPitch);
	draw_button(esContext, "motorNumberPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "motorNumberRoll", brugi_setup.motorNumberRoll);
	draw_button(esContext, "motorNumberRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "maxPWMmotorPitch", brugi_setup.maxPWMmotorPitch);
	draw_button(esContext, "maxPWMmotorPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	n = 0;
	sprintf(tmp_str, "%20s %i", "maxPWMmotorRoll", brugi_setup.maxPWMmotorRoll);
	draw_button(esContext, "maxPWMmotorRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "minRCPitch", brugi_setup.minRCPitch);
	draw_button(esContext, "minRCPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "maxRCPitch", brugi_setup.maxRCPitch);
	draw_button(esContext, "maxRCPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "minRCRoll", brugi_setup.minRCRoll);
	draw_button(esContext, "minRCRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "maxRCRoll", brugi_setup.maxRCRoll);
	draw_button(esContext, "maxRCRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "rcGain", brugi_setup.rcGain);
	draw_button(esContext, "rcGain", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "rcLPF", brugi_setup.rcLPF);
	draw_button(esContext, "rcLPF", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "rcModePPM", brugi_setup.rcModePPM);
	draw_button(esContext, "rcModePPM", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "rcChannelPitch", brugi_setup.rcChannelPitch);
	draw_button(esContext, "rcChannelPitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "rcChannelRoll", brugi_setup.rcChannelRoll);
	draw_button(esContext, "rcChannelRoll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "rcMid", brugi_setup.rcMid);
	draw_button(esContext, "rcMid", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "rcAbsolute", brugi_setup.rcAbsolute);
	draw_button(esContext, "rcAbsolute", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "accOutput", brugi_setup.accOutput);
	draw_button(esContext, "accOutput", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "enableGyro", brugi_setup.enableGyro);
	draw_button(esContext, "enableGyro", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "enableACC", brugi_setup.enableACC);
	draw_button(esContext, "enableACC", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "axisReverseZ", brugi_setup.axisReverseZ);
	draw_button(esContext, "axisReverseZ", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);
	sprintf(tmp_str, "%20s %i", "axisSwapXY", brugi_setup.axisSwapXY);
	draw_button(esContext, "axisSwapXY", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.2, -0.8 + n++ * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, brugi_setval, 0.0);


}

