
#include <all.h>

extern GLuint RB_texture;
void draw_texture_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, GLuint texture);
float mapcamscale = 1.8;

#ifdef USE_VISTA2D

static int vdView;
static uint8_t ratio = 1;
static float z = 0.0;
static uint8_t hud_use_vista2d = 0;

#endif


static float gimbal_pitch = 0.0;
static float gimbal_roll = 0.0;
static float gimbal_yaw = 0.0;

uint8_t hud_null (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

#if defined USE_WIFIBC
uint8_t hud_wifibc_record (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	setup.wifibc_record = 1 - setup.wifibc_record;
	return 0;
}

uint8_t hud_wifibc_channel (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	char cmd_str[1024];
	if (button == 5) {
		setup.wifibc_channel--;
	} else if (button == 4) {
		setup.wifibc_channel++;
	} else {
		for (setup.wifibc_channel = 1; setup.wifibc_channel < 20; setup.wifibc_channel++) {
			sprintf(cmd_str, "iwconfig %s channel %i", setup.wifibc_device, setup.wifibc_channel);
			SDL_Log("wifibc: %s\n", cmd_str);
			system(cmd_str);
			SDL_Delay(10);
			GroundData.wifibc_rssi[0] = -64;
			SDL_Delay(100);
			SDL_Log("wifibc: RSSI: %idBm\n", GroundData.wifibc_rssi[0]);
			if (GroundData.wifibc_rssi[0] != -64) {
				break;
			}
		}
	}
	sprintf(cmd_str, "iwconfig %s channel %i", setup.wifibc_device, setup.wifibc_channel);
	system(cmd_str);
	return 0;
}
#endif

uint8_t gimbal_set_pitch (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		gimbal_pitch++;
	} else if (button == 5) {
		gimbal_pitch--;
	}
	mavlink_set_gimbal_pos(ModelActive, gimbal_pitch, gimbal_roll, gimbal_yaw);
	return 0;
}

uint8_t gimbal_set_roll (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		gimbal_roll++;
	} else if (button == 5) {
		gimbal_roll--;
	}
	mavlink_set_gimbal_pos(ModelActive, gimbal_pitch, gimbal_roll, gimbal_yaw);
	return 0;
}

uint8_t gimbal_set_yaw (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		gimbal_yaw++;
	} else if (button == 5) {
		gimbal_yaw--;
	}
	mavlink_set_gimbal_pos(ModelActive, gimbal_pitch, gimbal_roll, gimbal_yaw);
	return 0;
}


#ifdef USE_VISTA2D

uint8_t vista2d_cmd (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		z += 0.01;
		return 0;
	}
	if (button == 5) {
		z -= 0.01;
		return 0;
	}
	if (strcmp(name + 1, "RATIO") == 0) {
		ratio = 1 - ratio;
	} else if (strcmp(name + 1, "INTERNAL") == 0) {
		hud_use_vista2d = 1 - hud_use_vista2d;
	} else if (strcmp(name + 1, "VIEW1") == 0) {
		vdViewStopAnim(vdView);
		vdViewFree(vdView);
		vdView = vdViewLoad("./External/vista2d/views/view1.v");
		vdViewStartAnim(vdView);
	} else if (strcmp(name + 1, "VIEW2") == 0) {
		vdViewStopAnim(vdView);
		vdViewFree(vdView);
		vdView = vdViewLoad("./External/vista2d/views/view2.v");
		vdViewStartAnim(vdView);
	} else if (strcmp(name + 1, "VIEW3") == 0) {
		vdViewStopAnim(vdView);
		vdViewFree(vdView);
		vdView = vdViewLoad("./External/vista2d/views/view3.v");
		vdViewStartAnim(vdView);
	} else if (strcmp(name + 1, "VIEW4") == 0) {
		vdViewStopAnim(vdView);
		vdViewFree(vdView);
		vdView = vdViewLoad("./External/vista2d/views/view4.v");
		vdViewStartAnim(vdView);
	} else if (strcmp(name + 1, "VIEW5") == 0) {
		vdViewStopAnim(vdView);
		vdViewFree(vdView);
		vdView = vdViewLoad("./External/vista2d/views/instruments.v");
		vdViewStartAnim(vdView);
	}
	return 0;
}

void screen_hud_vista2d (ESContext *esContext) {
	static uint8_t startup = 0;
	if (startup == 0) {
		startup = 1;
		vdView = vdViewLoad ("External/vista2d/views/view1.v");
		vdViewStartAnim(vdView);
	}
	char tmp_str[128];
	vdVarSetStr(vdView, "NAME", ModelData[ModelActive].name);
	sprintf(tmp_str, "%f", ModelData[ModelActive].roll);
	vdVarSetStr(vdView, "BODY_ROLL_ANGLE", tmp_str);
	sprintf(tmp_str, "%f", ModelData[ModelActive].pitch);
	vdVarSetStr(vdView, "BODY_PITCH_ANGLE", tmp_str);
	sprintf(tmp_str, "%f", ModelData[ModelActive].yaw);
	vdVarSetStr(vdView, "BODY_HEADING_ANGLE", tmp_str);
	sprintf(tmp_str, "%f", ModelData[ModelActive].p_alt);
	vdVarSetStr(vdView, "BARO_CORRECTED_ALTITUDE", tmp_str);
	sprintf(tmp_str, "%f", ModelData[ModelActive].speed);
	vdVarSetStr(vdView, "INDICATED_AIRSPEED", tmp_str);
	sprintf(tmp_str, "%f", ModelData[ModelActive].p_lat);
	vdVarSetStr(vdView, "POS_LAT", tmp_str);
	sprintf(tmp_str, "%f", ModelData[ModelActive].p_long);
	vdVarSetStr(vdView, "POS_LON", tmp_str);

	int w = (int)vdViewWidth(vdView);
	int h = (int)vdViewHeight(vdView);
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	if (ratio == 1) {
		glPushMatrix();
		glScalef(2.0 / w, 2.0 / h, 1.0);
		glTranslatef(-(float)w / 2.0, -(float)h / 2.0, z);
	} else {
		float scale = 2.0 / w;
		if (scale > 2.0 / h) {
			scale = 2.0 / h;
		}
		glPushMatrix();
		glScalef(scale, scale, 1.0);
		glTranslatef(-(float)w / 2.0, -(float)h / 2.0, z);
	}
	vdViewDrawWindow(vdView);
	glPopMatrix();
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glEnable(GL_BLEND);

	glDisable( GL_DEPTH_TEST );
	draw_text_button(esContext, "tVIEW1", setup.view_mode, "VIEW1", FONT_WHITE, -0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, vista2d_cmd, 0.0);
	draw_text_button(esContext, "tVIEW2", setup.view_mode, "VIEW2", FONT_WHITE, -0.4, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, vista2d_cmd, 0.0);
	draw_text_button(esContext, "tVIEW3", setup.view_mode, "VIEW3", FONT_WHITE, -0.2, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, vista2d_cmd, 0.0);
	draw_text_button(esContext, "tVIEW4", setup.view_mode, "VIEW4", FONT_WHITE, -0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, vista2d_cmd, 0.0);
	draw_text_button(esContext, "tVIEW5", setup.view_mode, "VIEW5", FONT_WHITE, 0.2, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, vista2d_cmd, 0.0);
	draw_text_button(esContext, "tRATIO", setup.view_mode, "RATIO", FONT_WHITE, 0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, vista2d_cmd, 0.0);
	draw_text_button(esContext, "tINTERNAL", setup.view_mode, "INTERNAL", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, vista2d_cmd, 0.0);
	glEnable( GL_DEPTH_TEST );
}

#endif

uint8_t hud_goto_screen (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	setup.view_mode = (int)data;
	view_mode_next = (int)data;
	return 0;
}

uint8_t hud_altitude_null (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	float ground_alt = (float)get_altitude(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long);
	if (ModelData[ModelActive].alt_offset != 0.0) {
		ModelData[ModelActive].alt_offset = 0.0;
	} else {
		ModelData[ModelActive].alt_offset = ModelData[ModelActive].p_alt - ground_alt;
	}
	return 0;
}

uint8_t view_hud (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (setup.hud_view_screen == 0) {
		setup.hud_view_screen = 1;
	} else if (setup.hud_view_screen == 1) {
		setup.hud_view_screen = 2;
	} else {
		setup.hud_view_screen = 0;
	}
	return 0;
}


uint8_t view_hud_stab (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (setup.hud_view_stab < 2) {
		setup.hud_view_stab++;
	} else {
		setup.hud_view_stab = 0;
	}
	return 0;
}

uint8_t view_hud_bw (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	setup.contrast = 1 - setup.contrast;
	return 0;
}

uint8_t view_hud_mark (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	setup.hud_view_mark = 1;	
	return 0;
}

uint8_t view_hud_tunnel (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	setup.hud_view_tunnel = 1 - setup.hud_view_tunnel;
	return 0;
}

uint8_t view_hud_map (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		mapcamscale += 0.01;
		return 0;
	}
	if (button == 5) {
		mapcamscale -= 0.01;
		return 0;
	}
	if (setup.hud_view_map == 0) {
		setup.hud_view_map = 1;
	} else if (setup.hud_view_map == 1) {
		setup.hud_view_map = 2;
	} else {
		setup.hud_view_map = 0;
	}
	return 0;
}

uint8_t view_hud_video (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	setup.hud_view_video = 1 - setup.hud_view_video;
	return 0;
}

void draw_gcs (ESContext *esContext, float x1, float y1, float roll, float pitch, float yaw) {
	ESMatrix modelview;
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	UserData *userData = esContext->userData;
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate( &modelview, x1, -y1, -1.9 );
	esRotate( &modelview, roll, 0.0, 1.0, 0.0 );
	esRotate( &modelview, pitch, 1.0, 0.0, 0.0 );
	esTranslate( &modelview, -x1, y1, 1.9 );
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	// Transmitter
	float rc_roll = ModelData[ModelActive].radio[0];
	float rc_pitch = -ModelData[ModelActive].radio[1];
	float rc_yaw = ModelData[ModelActive].radio[2];
	float rc_throttle = ModelData[ModelActive].radio[3];
	draw_box_f3(esContext, x1 - 0.01, y1 - 0.08, 0.101, x1 + 0.01, y1 - 0.15, 0.101, 200, 200, 200, 255);
	draw_box_f3(esContext, x1 - 0.1, y1 - 0.08, 0.101, x1 + 0.1, y1 + 0.1, 0.101, 255, 255, 255, 255);
	draw_circle_f3(esContext, x1 - 0.05, y1, 0.1012, 0.03, 127, 127, 127, 255);
	draw_circle_f3(esContext, x1 + 0.05, y1, 0.1012, 0.03, 127, 127, 127, 255);
	draw_line_f3(esContext, x1 - 0.05, y1, 0.1012, x1 - 0.05 + (rc_yaw * 0.02 / 100.0), y1 + (rc_throttle * 0.02 / 100.0), 0.112, 255, 0, 0, 255);
	draw_circleFilled_f3(esContext, x1 - 0.05 + (rc_yaw * 0.02 / 100.0), y1 + (rc_throttle * 0.02 / 100.0), 0.112, 0.01, 255, 0, 0, 255);
	draw_line_f3(esContext, x1 + 0.05, y1, 0.1012, x1 + 0.05 + (rc_roll * 0.02 / 100.0), y1 + (rc_pitch * 0.02 / 100.0), 0.112, 255, 0, 0, 255);
	draw_circleFilled_f3(esContext, x1 + 0.05 + (rc_roll * 0.02 / 100.0), y1 + (rc_pitch * 0.02 / 100.0), 0.112, 0.01, 255, 0, 0, 255);

#ifdef SDLGL
	glPopMatrix();
#endif
}


void draw_turning_indicator (ESContext *esContext, float ti_x, float ti_y, float w, float h) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	float rate_yaw = (float)ModelData[ModelActive].gyro_z / 40.0;
	if (ModelData[ModelActive].teletype == TELETYPE_MULTIWII_21 || ModelData[ModelActive].teletype == TELETYPE_BASEFLIGHT) {
		rate_yaw = (float)ModelData[ModelActive].gyro_z / 40.0;
	}
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, ti_x, -ti_y, 0.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f3(esContext, 0.0 - (w / 2.2), 0.0 - 0.0025, 0.02, 0.0 - (w / 2.0), 0.0 + 0.0025, 0.01, 255, 255, 255, 255);
	draw_box_f3(esContext, 0.0 + (w / 2.2), 0.0 - 0.0025, 0.02, 0.0 + (w / 2.0), 0.0 + 0.0025, 0.01, 255, 255, 255, 255);
	esRotate(&modelview, 20, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f3(esContext, 0.0 + (w / 2.2), 0.0 - 0.0025, 0.005, 0.0 + (w / 2.0), 0.0 + 0.0025, 0.005, 255, 255, 255, 255);
	esRotate(&modelview, -20, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	esRotate(&modelview, -20, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f3(esContext, 0.0 - (w / 2.2), 0.0 - 0.0025, 0.005, 0.0 - (w / 2.0), 0.0 + 0.0025, 0.01, 255, 255, 255, 255);
	esRotate(&modelview, 20, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	esRotate(&modelview, rate_yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	// Rumpf
	draw_circleFilled_f3(esContext, 0.0, 0.0, 0.005, (w / 14.0), 255, 255, 255, 255);
	// Hoehe
	draw_box_f3(esContext, 0.0 - (w / 5.0), 0.0 - (w / 14.0), 0.005, 0.0 + (w / 5.0), 0.0 - (w / 14.0) + (w / 40.0), 0.005, 255, 255, 255, 255);
	// Seite
	draw_box_f3(esContext, 0.0 - (w / 70.0), 0.0, 0.005, 0.0 + (w / 70.0), 0.0 - 0.1, 0.005, 255, 255, 255, 255);
	// Flaechen
	draw_triaFilled_f3(esContext, 0.0, 0.0 + (w / 40.0), 0.005, 0.0 + (w / 2.2), 0.0, 0.005, 0.0, 0.0 - (w / 40.0), 0.005, 255, 255, 255, 255);
	draw_triaFilled_f3(esContext, 0.0, 0.0 - (w / 40.0), 0.005, 0.0 - (w / 2.2), 0.0, 0.005, 0.0, 0.0 + (w / 40.0), 0.005, 255, 255, 255, 255);
	esRotate(&modelview, -rate_yaw, 0.0, 0.0, 1.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	float accel = ModelData[ModelActive].acc_y * 50.0;
	if (ModelData[ModelActive].teletype == TELETYPE_MULTIWII_21 || ModelData[ModelActive].teletype == TELETYPE_BASEFLIGHT) {
		accel = (float)ModelData[ModelActive].acc_x / 256.0 * -50.0;
	}
	draw_circleFilled_f3_part(esContext, 0.0, 0.0 - (w / 4.0), 0.0005, (w / 2.0), (w / 2.2), 235.0, 300.0, 255, 255, 255, 255);
	draw_circleFilled_f3_part_end(esContext, 0.0, 0.0 - (w / 4.0), 0.001, (w / 2.0), (w / 2.2), 270.0 + accel, 25, 25, 25, 255);
#ifdef SDLGL
	glPopMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
}




void draw_altiude_rule (ESContext *esContext, float ti_x, float ti_y, float w, float h) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	char tmp_str[100];
	int n = 0;

	// Alt
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	float ax1 = ti_x;
	if (setup.hud_view_screen == 0 || setup.hud_view_screen == 1) {
		ax1 = 0.65;
	}
	float ax = ax1 + 0.04;

	if (setup.contrast == 1) {
		draw_box_f3(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 + 7 * 0.1, 0.001, 0, 0, 0, 255);
		draw_box_f3(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 - 7 * 0.1, 0.001, 0, 0, 0, 255);
	} else {
		draw_box_f3c2(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 + 7 * 0.1, 0.001, 50, 50, 50, 128, 50, 50, 50, 64);
		draw_box_f3c2(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 - 7 * 0.1, 0.001, 50, 50, 50, 128, 50, 50, 50, 64);
	}


#ifdef SDLGL
	float ground_alt = (float)get_altitude(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long);
	if (ground_alt - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) > -7.0) {
		float y1a = 0.0 - (ground_alt + 2.0 - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1;
		float y2a = 0.0 - (ground_alt - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1;
		float y1b = y2a;
		float y2b = 0.0 - (-7.0) * 0.1;
		if (y1b < -0.7) {
			y1b = -0.7;
			y2a = -0.7;
		}
		if (y1a < -0.7) {
			y1a = -0.7;
		}
		draw_box_f3c2(esContext
			, ax1, y1a, 0.0015
			, ax1 + 0.17, y2a, 0.0015
			, 0, 255, 0, 0
			, 255, 0, 0, 128
		);
		draw_box_f3c2(esContext
			, ax1, y1b, 0.0015
			, ax1 + 0.17, y2b, 0.0015
			, 255, 0, 0, 128
			, 255, 0, 0, 128
		);
		draw_line_f3(esContext, ax1 - 0.05, y2a, 0.0015, ax1 + 0.25, y2a, 0.002, 255, 255, 255, 255);
	} else if ((ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - ground_alt > 100.0 - 7.0) {
		float y1a = 0.0 - (ground_alt + 100.0 - 2.0 - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1;
		float y2a = 0.0 - (ground_alt + 100.0 - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1;
		float y1b = 0.0 - (ground_alt + 100.0 - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1;
		float y2b = 0.0 - (7.0) * 0.1;
		if (y1b > 0.7) {
			y1b = 0.7;
			y2a = 0.7;
		}
		if (y1a > 0.7) {
			y1a = 0.7;
		}
		draw_box_f3c2(esContext
			, ax1, y1a, 0.0015
			, ax1 + 0.17, y2a, 0.0015
			, 0, 255, 0, 0
			, 255, 0, 0, 128
		);
		draw_box_f3c2(esContext
			, ax1, y1b, 0.0015
			, ax1 + 0.17, y2b, 0.0015
			, 255, 0, 0, 128
			, 255, 0, 0, 128
		);
		draw_line_f3(esContext, ax1 - 0.05, y2a, 0.0015, ax1 + 0.25, y2a, 0.002, 255, 255, 255, 255);
	}

	if (ground_alt - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) > 0.0) {
		draw_text_f3(esContext, 0.0 - (float)strlen("GROUND CONTACT") * 0.07 * 0.6 / 2.0, -0.75, 0.002, 0.07, 0.07, FONT_GREEN, "GROUND CONTACT");
	} else if (ground_alt - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) > -2.0) {
		draw_text_f3(esContext, 0.0 - (float)strlen("LOW ALT") * 0.07 * 0.6 / 2.0, -0.75, 0.002, 0.07, 0.07, FONT_GREEN, "LOW ALT");
//	} else if ((ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - ground_alt > 100.0) {
//		draw_text_f3(esContext, 0.0 - (float)strlen("PUBLIC AIRSPACE") * 0.07 * 0.6 / 2.0, -0.75, 0.002, 0.07, 0.07, FONT_GREEN, "PUBLIC AIRSPACE");
	}

	sprintf(tmp_str, "%0.1f", (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - ground_alt);
	if (setup.contrast == 1) {
		draw_text_f3(esContext, ax + 0.15 - strlen(tmp_str) * 0.07 * 0.6 - 0.05, 0.7, 0.0025, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f3(esContext, ax + 0.15 - strlen(tmp_str) * 0.07 * 0.6 - 0.05, 0.7, 0.0025, 0.07, 0.07, FONT_PINK, tmp_str);
	}
#endif

	draw_rect_f3(esContext, ax1, 0.0 - 7 * 0.1, 0.002, ax1 + 0.17, 0.0 + 7 * 0.1, 0.002, 255, 255, 255, 127);
	for (n = (int)(ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - 5; n <= (int)(ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) + 6; n += 1) {
		float tsize = 0.05;
		sprintf(tmp_str, "%i", n);
		draw_text_f3(esContext, ax1 + 0.02, 0.0 - 0.025 - ((float)n - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1, 0.0015, tsize, tsize, FONT_WHITE, tmp_str);
		draw_line_f3(esContext, ax1, 0.0 - ((float)n - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1, 0.0015, ax1 + 0.02, 0.0 - ((float)n - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1, 0.0015, 255, 255, 255, 255);
	}
	for (n = (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) + 0.3 - 5; n <= (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - 0.3 + 7; n += 1) {
		draw_line_f3(esContext, ax1, 0.0 - ((float)n - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1 + 0.05, 0.0015, ax1 + 0.01, 0.0 - ((float)n - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset)) * 0.1 + 0.05, 0.0015, 255, 255, 255, 255);
	}
	draw_box_f3(esContext, ax, -0.05, 0.002, ax + 0.28, 0.05, 0.002, 0, 0, 0, 255);
	draw_triaFilled_f3(esContext, ax, -0.02, 0.002, ax - 0.02, 0.0, 0.002, ax, 0.02, 0.002, 0, 0, 0, 255);
	draw_line_f3(esContext, ax, -0.05, 0.002, ax + 0.28, -0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, 0.05, 0.002, ax + 0.28, 0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax + 0.28, -0.05, 0.002, ax + 0.28, 0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, -0.05, 0.002, ax, -0.019, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, 0.05, 0.002, ax, 0.019, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax - 0.02, 0.0, 0.002, ax, -0.02, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax - 0.02, 0.0, 0.002, ax, 0.02, 0.002, 255, 255, 255, 255);

	sprintf(tmp_str, "%0.1f", (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset));
	if (setup.contrast == 1) {
		draw_text_f3(esContext, ax + 0.15 - strlen(tmp_str) * 0.07 * 0.6 - 0.05, -0.77, 0.0025, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f3(esContext, ax + 0.15 - strlen(tmp_str) * 0.07 * 0.6 - 0.05, -0.77, 0.0025, 0.07, 0.07, FONT_PINK, tmp_str);
	}

	sprintf(tmp_str, "%0.1fm", (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset));
	draw_text_f3(esContext, ax + 0.28 - strlen(tmp_str) * 0.05 * 0.6 - 0.05, 0.0 - 0.025, 0.0025, 0.05, 0.05, FONT_WHITE, tmp_str);
	set_button("alt_null", VIEW_MODE_HUD, ax, -0.05, ax + 0.28, 0.05, hud_altitude_null, ModelData[ModelActive].p_alt, 0);

	sprintf(tmp_str, "%0.2f", ModelData[ModelActive].press_abs);
	draw_text_button(esContext, "hud_alt_press", VIEW_MODE_HUD, tmp_str, FONT_WHITE, ax + 0.27, 0.015, 0.05, 0.035, 2, 0, hud_null, 0);
}



void draw_speed_rule (ESContext *esContext, float ti_x, float ti_y, float w, float h) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	char tmp_str[100];
	int n = 0;

	float speed = ModelData[ModelActive].speed * 1000.0 / 60.0 / 60.0; // km/h -> m/s

	// Speed
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	float ax1 = ti_x;
	if (setup.hud_view_screen == 0 || setup.hud_view_screen == 1) {
		ax1 = -0.65;
	}
	float ax = ax1 - 0.04;
	ax1 -= 0.17;

	if (setup.contrast == 1) {
		draw_box_f3(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 + 7 * 0.1, 0.001, 0, 0, 0, 255);
		draw_box_f3(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 - 7 * 0.1, 0.001, 0, 0, 0, 255);
	} else {
		draw_box_f3c2(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 + 7 * 0.1, 0.001, 50, 50, 50, 128, 50, 50, 50, 64);
		draw_box_f3c2(esContext, ax1, 0.0, 0.001, ax1 + 0.17, 0.0 - 7 * 0.1, 0.001, 50, 50, 50, 128, 50, 50, 50, 64);
	}

	draw_rect_f3(esContext, ax1, 0.0 - 7 * 0.1, 0.002, ax1 + 0.17, 0.0 + 7 * 0.1, 0.002, 255, 255, 255, 127);
	for (n = (int)speed - 5; n <= (int)speed + 6; n += 1) {
		float tsize = 0.05;
		sprintf(tmp_str, "%i", n);
		draw_text_f3(esContext, ax1 + 0.02, 0.0 - 0.025 - ((float)n - speed) * 0.1, 0.0015, tsize, tsize, FONT_WHITE, tmp_str);
		draw_line_f3(esContext, ax1 + 0.17, 0.0 - ((float)n - speed) * 0.1, 0.0015, ax1 + 0.17 - 0.02, 0.0 - ((float)n - speed) * 0.1, 0.0015, 255, 255, 255, 255);
	}
	for (n = speed + 0.3 - 5; n <= speed - 0.3 + 7; n += 1) {
		draw_line_f3(esContext, ax1 + 0.17, 0.0 - ((float)n - speed) * 0.1 + 0.05, 0.0015, ax1 + 0.17 - 0.01, 0.0 - ((float)n - speed) * 0.1 + 0.05, 0.0015, 255, 255, 255, 255);
	}

	draw_box_f3(esContext, ax - 0.28, -0.05, 0.002, ax, 0.05, 0.002, 0, 0, 0, 255);
	draw_triaFilled_f3(esContext, ax + 0.02, 0.0, 0.002, ax, -0.02, 0.002, ax, 0.02, 0.002, 0, 0, 0, 255);
	draw_line_f3(esContext, ax, -0.05, 0.002, ax - 0.28, -0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, 0.05, 0.002, ax - 0.28, 0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax - 0.28, -0.05, 0.002, ax - 0.28, 0.05, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, -0.05, 0.002, ax, -0.019, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax, 0.05, 0.002, ax, 0.019, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax + 0.02, 0.0, 0.002, ax, -0.02, 0.002, 255, 255, 255, 255);
	draw_line_f3(esContext, ax + 0.02, 0.0, 0.002, ax, 0.02, 0.002, 255, 255, 255, 255);

	sprintf(tmp_str, "%0.1f", speed);
	if (setup.contrast == 1) {
		draw_text_f3(esContext, ax1, -0.77, 0.0025, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f3(esContext, ax1, -0.77, 0.0025, 0.07, 0.07, FONT_PINK, tmp_str);
	}

	sprintf(tmp_str, "%0.1fm/s", speed);
	draw_text_f3(esContext, ax - strlen(tmp_str) * 0.05 * 0.6 - 0.05, 0.0 - 0.025, 0.0025, 0.05, 0.05, FONT_WHITE, tmp_str);
}



uint8_t graph1_data[3][200];
int16_t graph1_pointer = 0;
int16_t graph1_size = 128;


void hud_draw_horizon (ESContext *esContext, uint8_t type) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	char tmp_str[400];
	int n = 0;

#ifdef SDLGL
	glDisable(GL_DEPTH_TEST);
	if (setup.hud_view_video == 1) {

#if defined USE_VLC
	if (vlc_is_playing() == 0) {
		vlc_exit();
		vlc_init(setup.videocapture_device);
	}
	draw_surface_f3(esContext, -1.42, -1.0, 1.42, 1.0, -2.0, 1.0, vlc_update());
#elif defined USE_WIFIBC
	SDL_Surface *vidsurf = wifibc_get();
	if (vidsurf != NULL) {
#ifdef _ANDROID
		SDL_Surface *imageSurface = convert_to_power_of_two(vidsurf);
		draw_surface_f3(esContext, -1.42, -1.0, 1.42, 1.0, -2.0, 1.0, imageSurface);
		SDL_FreeSurface(imageSurface);
#else
		draw_surface_f3(esContext, -1.42, -1.0, 1.42, 1.0, -2.0, 1.0, vidsurf);
#endif
	}
#elif defined USE_OPENCV
	SDL_Surface *vidsurf = openvc_get();
	if (vidsurf != NULL) {
#ifdef _ANDROID
		SDL_Surface *imageSurface = convert_to_power_of_two(vidsurf);
		draw_surface_f3(esContext, -1.42, -1.0, 1.42, 1.0, -2.0, 1.0, imageSurface);
		SDL_FreeSurface(imageSurface);
#else
		draw_surface_f3(esContext, -1.42, -1.0, 1.42, 1.0, -2.0, 1.0, vidsurf);
#endif
	}
#else
#ifndef OSX
#if defined USE_V4L
	draw_surface_f3(esContext, -1.42, -1.0, 1.42, 1.0, -2.0, 1.0, videodev_loop());
#endif
#endif
#endif
	}
#endif
#ifdef SDLGL

	if (setup.hud_view_map != 0) {
		glPushMatrix();
		glScalef(mapcamscale, mapcamscale, 1.0);
		if (setup.hud_view_map == 1) {
			if (setup.hud_view_video == 1) {
				display_map(esContext, lat, lon, zoom, 3, 1, 0.5, 0.05, 0.05, 0.5);
			} else {
				display_map(esContext, lat, lon, zoom, 3, 1, 1.0, 0.1, 0.1, 0.3);
			}
		} else if (setup.hud_view_map == 2) {
			if (setup.hud_view_video == 1) {
				display_map(esContext, lat, lon, zoom, 3, 0, 0.0, 0.35, 0.35, 0.3);
			} else {
				display_map(esContext, lat, lon, zoom, 3, 0, 0.0, 0.7, 0.7, 0.7);
			}
		}
		glPopMatrix();
	}
#endif
	// Background
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, 0.0, -3.0);
	esRotate(&modelview, -ModelData[ModelActive].roll, 0.0, 0.0, 1.0);
	esTranslate(&modelview, 0.0, -ModelData[ModelActive].pitch / 70.0, 0.0);
	esTranslate(&modelview, 0.0, 0.0, 3.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	if (setup.hud_view_map == 0 && setup.hud_view_video == 0) {
		if (setup.contrast == 1) {
			draw_box_f3(esContext, -2.5, -2.5, 0.001, 2.5, 0.0, 0.001, 127, 127, 127, 255);
			draw_box_f3(esContext, -2.5, 0.0, 0.001, 2.5, 2.5, 0.001, 255, 255, 255, 255);
		} else {
#ifdef SDLGL
			draw_box_f3c2(esContext, -2.5, -2.5, 0.001, 2.5, 0.0, 0.001, 0x01, 0x8e, 0xea, 255, 0x01, 0x8e, 0xea, 255); // blue
			draw_box_f3c2(esContext, -2.5, 0.0, 0.001, 2.5, 2.5, 0.001, 0xb1, 0x56, 0x1f, 255, 0xb1, 0x56, 0x1f, 255);  // brown
#else
			char tmp_str[128];
			sprintf(tmp_str, "%s/textures/blue.png", BASE_DIR);
			draw_image_f3(esContext, -2.5, -2.5, 2.5, 0.0, -0.001, tmp_str); // blue
			sprintf(tmp_str, "%s/textures/brown.png", BASE_DIR);
			draw_image_f3(esContext, -2.5, 0.0, 2.5, 2.5, -0.001, tmp_str); // brown
#endif
		}
		draw_line_f3(esContext, -2.5, 0.0, 0.001, 2.5, 0.0, 0.001, 255, 255, 255, 255);
	}
#ifdef SDLGL
	glPopMatrix();
#endif
if (type == 1) {
	// Pitch & Roll-Winkel
	for (n = -30 - ((int)(-ModelData[ModelActive].pitch / 10) % 10 * 10); n <= 20 - ((int)((-ModelData[ModelActive].pitch - 3) / 10) % 10 * 10); n += 10) {
		// Pitch
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, 0.0, -3.0);
		esRotate(&modelview, -ModelData[ModelActive].roll, 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, (float)(n + -ModelData[ModelActive].pitch) / 70.0, 0.0);
		esTranslate(&modelview, 0.0, 0.0, 3.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		if (n == 0) {
			draw_line_f3(esContext, -2.0, 0.0, -0.001, 2.0, 0.0, -0.001, 255, 255, 255, 255);
		} else {
			sprintf(tmp_str, "%i", n * -1);
			draw_text_f3(esContext, -0.2 - strlen(tmp_str) * 0.05 * 0.6, -0.025, 0.001, 0.05, 0.05, FONT_WHITE, tmp_str);
			draw_text_f3(esContext, 0.2, -0.025, 0.001, 0.05, 0.05, FONT_WHITE, tmp_str);

			uint8_t alpha = 255;
			if ((n + -ModelData[ModelActive].pitch) < 0) {
				alpha = 255 - -(n + -ModelData[ModelActive].pitch) * 255 / 45;
			} else {
				alpha = 255 - (n + -ModelData[ModelActive].pitch) * 255 / 45;
			}
			if ((n + -ModelData[ModelActive].pitch) > -45 && (n + -ModelData[ModelActive].pitch) < 45) {
				draw_line_f3(esContext, -0.15, 0.0, 0.001, 0.15, 0.0, 0.001, 255, 255, 255, alpha);
			}
		}
#ifdef SDLGL
		glPopMatrix();
#endif
	}
	for (n = -35 - ((int)(-ModelData[ModelActive].pitch / 10) % 10 * 10); n <= 25 - ((int)((-ModelData[ModelActive].pitch - 3) / 10) % 10 * 10); n += 10) {
		// Pitch
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, 0.0, -3.0);
		esRotate(&modelview, -ModelData[ModelActive].roll, 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, (float)(n + -ModelData[ModelActive].pitch) / 70.0, 0.0);
		esTranslate(&modelview, 0.0, 0.0, 3.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		uint8_t alpha = 255;
		if ((n + -ModelData[ModelActive].pitch) < 0) {
			alpha = 255 - -(n + -ModelData[ModelActive].pitch) * 255 / 45;
		} else {
			alpha = 255 - (n + -ModelData[ModelActive].pitch) * 255 / 45;
		}
		if ((n + -ModelData[ModelActive].pitch) > -45 && (n + -ModelData[ModelActive].pitch) < 45) {
			draw_line_f3(esContext, -0.1, 0.0, 0.001, 0.1, 0.0, 0.001, 255, 255, 255, alpha);
		}
#ifdef SDLGL
		glPopMatrix();
#endif
	}

	for (n = -45; n <= 45; n += 10) {
		// Roll
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esRotate(&modelview, -(float)n, 0.0, 0.0, 1.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		uint8_t alpha = 255;
/*
		if ((n) < 0) {
			alpha = 255 - -(n) * 255 / 45;
		} else {
			alpha = 255 - (n) * 255 / 45;
		}
*/
		if ((n) > -45 && (n) < 45) {
			draw_line_f(esContext, 0.0, -0.65, 0.0, -0.6, 255, 255, 255, alpha);
		}
#ifdef SDLGL
		glPopMatrix();
#endif
	}

	for (n = -45; n <= 45; n += 5) {
		// Roll
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esRotate(&modelview, -(float)n, 0.0, 0.0, 1.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		uint8_t alpha = 255;
/*		if ((n) < 0) {
			alpha = 255 - -(n) * 255 / 45;
		} else {
			alpha = 255 - (n) * 255 / 45;
		}
*/
		if ((n) > -45 && (n) < 45) {
			draw_line_f(esContext, 0.0, -0.63, 0.0, -0.6, 255, 255, 255, alpha);
		}
#ifdef SDLGL
		glPopMatrix();
#endif
	}

	// Roll-Zeiger
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif

	esRotate(&modelview, -ModelData[ModelActive].roll, 0.0, 0.0, 1.0);

#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_line_f(esContext, 0.0, -0.6, -0.04, -0.56, 255, 255, 255, 255);
	draw_line_f(esContext, 0.0, -0.6, 0.04, -0.56, 255, 255, 255, 255);
	draw_line_f(esContext, -0.04, -0.56, 0.04, -0.56, 255, 255, 255, 255);
	draw_line_f(esContext, -0.04, -0.54, 0.04, -0.54, 255, 255, 255, 255);
	draw_line_f(esContext, -0.04, -0.54, -0.04, -0.56, 255, 255, 255, 255);
	draw_line_f(esContext, 0.04, -0.54, 0.04, -0.56, 255, 255, 255, 255);

#ifdef SDLGL
	glPopMatrix();
#endif

	// Center-Cross
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f3(esContext, -0.45, -0.02, 0.001, -0.15, 0.02, 0.001, 255, 255, 255, 255);
	draw_box_f3(esContext, -0.15 - 0.04, -0.02, 0.001, -0.15, 0.08, 0.001, 255, 255, 255, 255);
	draw_box_f3(esContext, 0.15, -0.02, 0.001, 0.45, 0.02, 0.001, 255, 255, 255, 255);
	draw_box_f3(esContext, 0.15, -0.02, 0.001, 0.15 + 0.04, 0.08, 0.001, 255, 255, 255, 255);
#ifdef SDLGL
	glPopMatrix();
#endif
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, 0.0, +0.01);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_box_f(esContext, -0.45 + 0.005, -0.02 + 0.005, -0.15 - 0.005, 0.02 - 0.005, 0, 0, 0, 255);
	draw_box_f(esContext, -0.15 - 0.04 + 0.005, -0.02 + 0.005, -0.15 - 0.005, 0.08 - 0.005, 0, 0, 0, 255);
	draw_box_f(esContext, 0.15 + 0.005, -0.02 + 0.005, 0.45 - 0.005, 0.02 - 0.005, 0, 0, 0, 255);
	draw_box_f(esContext, 0.15 + 0.005, -0.02 + 0.005, 0.15 + 0.04 - 0.005, 0.08 - 0.005, 0, 0, 0, 255);
#ifdef SDLGL
	glPopMatrix();
#endif
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, 0.0, +0.01);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	if (setup.contrast == 1) {
		draw_box_f3(esContext, -0.005, -0.2, 0.001, 0.005, 0.2, 0.001, 0, 0, 0, 255);
		draw_box_f3(esContext, -0.2, -0.005, 0.001, 0.2, 0.005, 0.001, 0, 0, 0, 255);
	} else {
		draw_box_f3(esContext, -0.005, -0.2, 0.001, 0.005, 0.2, 0.001, 0xff, 0x33, 0xfc, 255); // pink
		draw_box_f3(esContext, -0.2, -0.005, 0.001, 0.2, 0.005, 0.001, 0xff, 0x33, 0xfc, 255); // pink
	}
#ifdef SDLGL
	glPopMatrix();
#endif

	} else {
		draw_box_f(esContext, -2.0, -0.01, 2.0, 0.01, 255, 255, 255, 255);
		if (setup.contrast == 1) {
			draw_box_f3(esContext, -0.01, -0.2, 0.001, 0.01, 0.2, 0.001, 0, 0, 0, 255);
			draw_box_f3(esContext, -0.2, -0.01, 0.001, 0.2, 0.01, 0.001, 0, 0, 0, 255);
		} else {
			draw_box_f3(esContext, -0.01, -0.2, 0.001, 0.01, 0.2, 0.001, 0xff, 0x33, 0xfc, 255); // pink
			draw_box_f3(esContext, -0.2, -0.01, 0.001, 0.2, 0.01, 0.001, 0xff, 0x33, 0xfc, 255); // pink
		}
	}
}

#ifdef CAR_MODE
void draw_circleMarker_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef SDLGL
	y1 = y1 * -1;
	float i = start;
	glBegin(GL_LINES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0 + z1);
	glVertex3f(x1 - cos(i * DEG2RAD) * radius, y1 + sin(i * DEG2RAD) * radius, -2.0 + z1);
	glVertex3f(x1 - cos(i * DEG2RAD) * radius_inner, y1 + sin(i * DEG2RAD) * radius_inner, -2.0 + z1);
	glEnd();
#endif
}
#endif

void draw_circleText_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, float start, float size, char *text, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	float i = start;
	x1 -= cos(i * DEG2RAD) * radius;
	y1 -= sin(i * DEG2RAD) * radius;
	draw_text_f3(esContext, x1 - strlen(text) * size * 0.6 / 2.0 - 0.015, y1 - size / 2.0, z1, size, size, FONT_WHITE, text);
}

void screen_hud_internal (ESContext *esContext) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#else
#ifndef WINDOWS
	if (draw_target() == 0 && setup.view_mode == VIEW_MODE_HUD) {
		draw_to_buffer();
		display_map(esContext, lat, lon, zoom, 0, 1, 1.0, 0.0, 0.0, 0.0);
		draw_to_screen();
		reset_buttons();
	}
#endif
#endif
	glDisable(GL_DEPTH_TEST);



#ifdef CAR_MODE
	static int pointer_pm = 0;
	static float pointer_val = 0.0;
	if (pointer_pm == 0) {
		if (pointer_val < 200.0) {
			pointer_val += 1.0;
		} else {
			pointer_pm = 1;
		}
	} else {
		if (pointer_val > -54.0) {
			pointer_val -= 3.0;
		} else {
			pointer_pm = 0;
		}
	}
	float upm = (pointer_val + 54.0) * 8000.0 / 288;

	if (setup.hud_view_screen != 2 && draw_target() == 0) {
		if (upm < 800.0) {
			draw_image_f3(esContext, 0.0 - 0.2, 0.0 - 0.3, 0.0 + 0.2, 0.0 + 0.1, 0.012, "car-door.png");
		} else if (upm < 1600.0) {
			draw_image_f3(esContext, 0.0 - 0.2, 0.0 - 0.3, 0.0 + 0.2, 0.0 + 0.1, 0.012, "car.png");
		} else {
			draw_buffer_to_screen(0.0 - 0.6, -0.1 - 0.4, 0.0 + 0.6, -0.1 + 0.4, 0.0, 1.0);
		}
		glLineWidth(7);
		draw_line_f3 (esContext, 0.0 - 0.6, -0.1 - 0.4, 0.001, 0.0 + 0.6, -0.1 - 0.4, 0.001, 75, 75, 75, 255);
		draw_line_f3 (esContext, 0.0 - 0.6, -0.1 + 0.4, 0.001, 0.0 + 0.6, -0.1 + 0.4, 0.001, 75, 75, 75, 255);
		glLineWidth(3);
		draw_line_f3 (esContext, 0.0 - 0.6, -0.1 - 0.4, 0.001, 0.0 + 0.6, -0.1 - 0.4, 0.001, 200, 200, 200, 255);
		draw_line_f3 (esContext, 0.0 - 0.6, -0.1 + 0.4, 0.001, 0.0 + 0.6, -0.1 + 0.4, 0.001, 200, 200, 200, 255);
	}

	float i1x = -0.8;
	float i2x = 0.8;

//	draw_image_f3(esContext, -1.2, -0.62, -0.19, 0.42, 0.012, "tacho.png");
//	draw_image_f3(esContext, 0.21, -0.62, 1.21, 0.42, 0.012, "tacho2.png");

	draw_circleFilled_f(esContext, i1x, -0.1, 0.5, 0, 0, 0, 255);
//	draw_circleFilled_f(esContext, i1x, -0.1, 0.5, 40, 40, 40, 255);
//	draw_circleFilled_f3_part(esContext, i1x, -0.1, 0.0005, 0.5, 0.5, 0.0, 360.0, 60, 60, 255, 255);

	draw_text_f3(esContext, -0.6, 0.05, 0.002, 0.04, 0.04, FONT_WHITE, "1/min*1000");
	draw_circleFilled_f(esContext, i2x, -0.1, 0.5, 0, 0, 0, 255);
//	draw_circleFilled_f(esContext, i2x, -0.1, 0.5, 40, 40, 40, 255);
//	draw_circleFilled_f3_part(esContext, i2x, -0.1, 0.0005, 0.5, 0.5, 0.0, 360.0, 60, 60, 255, 255);

	char tmp_str3[10];
	float a = 0.0;
	glLineWidth(3);
	for (a = -54.0; a <= 234.0; a += 7.2) {
		if (a < 180.0) {
			draw_circleMarker_f3(esContext, i1x, -0.1, 0.0002, 0.5, 0.45, a, 255, 255, 255, 255);
		} else {
			draw_circleMarker_f3(esContext, i1x, -0.1, 0.0002, 0.5, 0.45, a, 255, 0, 0, 255);
		}
	}
	glLineWidth(6);
	int nt = 0;
	for (a = -54.0; a <= 234.0; a += 36.0) {
		if (a < 180.0) {
			draw_circleMarker_f3(esContext, i1x, -0.1, 0.0002, 0.5, 0.4, a, 255, 255, 255, 255);
		} else {
			draw_circleMarker_f3(esContext, i1x, -0.1, 0.0002, 0.5, 0.4, a, 255, 0, 0, 255);
		}
		sprintf(tmp_str3, "%i", nt);
		draw_circleText_f3(esContext, i1x, -0.1, 0.0002, 0.365, a, 0.07, tmp_str3, 255, 255, 255, 255);
		nt += 1;
	}

	glLineWidth(3);
	for (a = -54.0; a <= 234.0; a += 9.0) {
		draw_circleMarker_f3(esContext, i2x, -0.1, 0.0002, 0.5, 0.45, a, 255, 255, 255, 255);
	}
	glLineWidth(6);
	nt = 0;
	for (a = -54.0; a <= 234.0; a += 18.0) {
		draw_circleMarker_f3(esContext, i2x, -0.1, 0.0002, 0.5, 0.43, a, 255, 255, 255, 255);
		sprintf(tmp_str3, "%i", nt);
		draw_circleText_f3(esContext, i2x, -0.1, 0.0002, 0.365, a, 0.07, tmp_str3, 255, 255, 255, 255);
		if (nt < 60) {
			nt += 10;
		} else {
			nt += 20;
		}
	}

//	draw_box_f3(esContext, i1x - 0.15, -0.1 + 0.3 - 0.09, 0.001, i1x + 0.15, -0.1 + 0.3 + 0.09, 0.001, 0, 0, 0, 255);
//	draw_text_f(esContext, i1x - 0.12, -0.1 + 0.33 - 0.1, 0.07, 0.07, FONT_GREEN, "09:47");
//	draw_text_f(esContext, i1x - 0.135, -0.1 + 0.4 - 0.1, 0.07, 0.07, FONT_GREEN, "001145");


//	draw_circleFilled_f(esContext, i1x + 0.005, -0.1 + 0.005, 0.075, 30, 30, 30, 255);
//	draw_circlePointer_f3(esContext, i1x, -0.1, 0.0001, 0.45, 0.02, pointer_val, 255, 255, 255, 255);
//	draw_circleFilled_f(esContext, i1x, -0.1, 0.07, 127, 127, 127, 255);
//	draw_circle_f3(esContext, i1x, -0.1, 0.002, 0.07, 155, 155, 155, 255);


//	draw_box_f3(esContext, i2x - 0.15, -0.1 + 0.3 - 0.09, 0.001, i2x + 0.15, -0.1 + 0.3 + 0.09, 0.001, 0, 0, 0, 255);
//	draw_text_f(esContext, i2x - 0.12, -0.1 + 0.33 - 0.1, 0.07, 0.07, FONT_GREEN, "02547");
//	draw_text_f(esContext, i2x - 0.135, -0.1 + 0.4 - 0.1, 0.07, 0.07, FONT_GREEN, "006287");


//	draw_circleFilled_f(esContext, i2x + 0.005, -0.1 + 0.005, 0.075, 30, 30, 30, 255);
//	draw_circlePointer_f3(esContext, i2x, -0.1, 0.0001, 0.45, 0.02, pointer_val, 255, 255, 255, 255);
//	draw_circleFilled_f(esContext, i2x, -0.1, 0.07, 127, 127, 127, 255);
//	draw_circle_f3(esContext, i2x, -0.1, 0.002, 0.07, 155, 155, 155, 255);


	glLineWidth(4);
	draw_circleMarker_f3(esContext, i1x, -0.1, 0.0002, 0.43, 0.3, pointer_val, 255, 55, 55, 255);
	draw_circleMarker_f3(esContext, i2x, -0.1, 0.0002, 0.43, 0.3, pointer_val, 255, 55, 55, 255);
	glLineWidth(1);

	if (upm > 6000.0) {
		draw_circleFilled_f3_part(esContext, i1x, -0.1, 0.0005, 0.3, 0.3, 0.0, 360.0, 160, 60, 60, 255);
	} else {
		draw_circleFilled_f3_part(esContext, i1x, -0.1, 0.0005, 0.3, 0.3, 0.0, 360.0, 60, 60, 160, 255);
	}
	draw_circleFilled_f3_part(esContext, i2x, -0.1, 0.0005, 0.3, 0.3, 0.0, 360.0, 60, 60, 160, 255);

	sprintf(tmp_str3, "%0.0fupm", upm);
	if (upm > 6000.0) {
		draw_text_f(esContext, i1x - strlen(tmp_str3) * 0.07 * 0.6 / 2.0 - 0.015, -0.1 - 0.05 - 0.035, 0.07, 0.07, FONT_PINK, tmp_str3);
	} else {
		draw_text_f(esContext, i1x - strlen(tmp_str3) * 0.07 * 0.6 / 2.0 - 0.015, -0.1 - 0.05 - 0.035, 0.07, 0.07, FONT_GREEN, tmp_str3);
	}
	sprintf(tmp_str3, "%0.0fl", 46.0);
	draw_text_f(esContext, i1x - strlen(tmp_str3) * 0.07 * 0.6 / 2.0 - 0.015, -0.1 - 0.05 - 0.035 + 0.1, 0.07, 0.07, FONT_GREEN, tmp_str3);

	sprintf(tmp_str3, "%0.0fkm/h", (pointer_val + 54.0) * 260.0 / 288);
	draw_text_f(esContext, i2x - strlen(tmp_str3) * 0.07 * 0.6 / 2.0 - 0.015, -0.1 - 0.05 - 0.035, 0.07, 0.07, FONT_GREEN, tmp_str3);
	sprintf(tmp_str3, "10.6l/100km");
	draw_text_f(esContext, i2x - strlen(tmp_str3) * 0.05 * 0.6 / 2.0 - 0.015, -0.1 - 0.05 - 0.035 + 0.1, 0.05, 0.05, FONT_GREEN, tmp_str3);

	glLineWidth(7);
	draw_circle_f3(esContext, i1x, -0.1, 0.001, 0.5, 75, 75, 75, 255);
	draw_circle_f3(esContext, i2x, -0.1, 0.001, 0.5, 75, 75, 75, 255);

	draw_circle_f3(esContext, i1x, -0.1, 0.001, 0.3, 75, 75, 75, 255);
	draw_circle_f3(esContext, i2x, -0.1, 0.001, 0.3, 75, 75, 75, 255);

	glLineWidth(3);
	draw_circle_f3(esContext, i1x, -0.1, 0.001, 0.5, 255, 255, 255, 255);
	draw_circle_f3(esContext, i2x, -0.1, 0.001, 0.5, 255, 255, 255, 255);

	draw_circle_f3(esContext, i1x, -0.1, 0.001, 0.3, 200, 200, 200, 255);
	draw_circle_f3(esContext, i2x, -0.1, 0.001, 0.3, 200, 200, 200, 255);

	glLineWidth(1);

	draw_image_f3(esContext, i1x - 0.1, 0.3 - 0.05, i1x + 0.1, 0.3 + 0.05, 0.012, "s6-logo.png");

	char icons[20][50];
	strcpy(icons[0], "textures/tacho-abs.png");
	strcpy(icons[1], "textures/tacho-bat.png");
	strcpy(icons[2], "textures/tacho-fern.png");
	strcpy(icons[3], "textures/tacho-nebel.png");
	strcpy(icons[4], "textures/tacho-oel.png");
	strcpy(icons[5], "textures/tacho-wasser.png");
	strcpy(icons[6], "textures/tacho-airbag.png");
	strcpy(icons[7], "textures/tacho-cat.png");
	strcpy(icons[8], "textures/tacho-hmm.png");
	strcpy(icons[9], "textures/tacho-motor.png");
	strcpy(icons[10], "textures/tacho-nebel2.png");
	strcpy(icons[11], "textures/tacho-tank.png");
	strcpy(icons[12], "");
	int nn1 = 0;
	for (nn1 = 0; nn1 < 20 && icons[nn1][0] != 0; nn1++) {
		draw_image_f3(esContext, (nn1 * 0.12 - 0.65) - 0.05, -0.65 - 0.05, (nn1 * 0.12 - 0.65) + 0.05, -0.65 + 0.05, 0.012, icons[nn1]);
		if ((int)upm / 500 != nn1 && (int)upm < 6000) {
			draw_box_f3(esContext, (nn1 * 0.12 - 0.65) - 0.05, -0.65 - 0.05, 0.012, (nn1 * 0.12 - 0.65) + 0.05, -0.65 + 0.05, 0.012, 0, 0, 0, 200);
		}
	}


#ifdef SDLGL
#ifndef WINDOWS
	if (setup.hud_view_screen != 2 && draw_target() == 0) {
//		draw_buffer_to_screen(0.9, 0.4, 1.4, 0.85, 0.0, 1.0);
//		draw_rect_f3(esContext, 0.9, 0.4, 0.002, 1.4, 0.85, 0.002, 0, 0, 0, 255);
//		draw_rect_f3(esContext, 0.9 - 0.005, 0.4 - 0.005, 0.002, 1.4 + 0.005, 0.85 + 0.005, 0.002, 255, 255, 255, 255);
//		set_button("goto_map", setup.view_mode, 0.9, 0.4, 1.4, 0.85, hud_goto_screen, (float)VIEW_MODE_MAP, 0);
	}
#endif
#endif
#ifdef SDLGL
	glPopMatrix();
#endif
	glEnable(GL_DEPTH_TEST);
	return;
#endif

	char tmp_str[400];
	char tmp_str2[400];
	int n = 0;
	uint8_t i = 0;
	float angle = 0.0;
	float angle_wp = 0.0;
	float dist1 = 0.0;
	float angle_up = 0.0;
	float dist2 = 0.0;
	float angle2 = 0.0;
	float angle_home = 0.0;

	get_dir(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt, WayPoints[ModelActive][waypoint_active].p_lat, WayPoints[ModelActive][waypoint_active].p_long, WayPoints[ModelActive][waypoint_active].p_alt, &angle_wp, &dist1, &angle_up, &dist2);
	angle2 = angle_wp - ModelData[ModelActive].yaw;
	if (angle2 > 180.0) {
		angle2 = angle2 - 360.0;
	}
	get_dir(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt, WayPoints[ModelActive][0].p_lat, WayPoints[ModelActive][0].p_long, WayPoints[ModelActive][0].p_alt, &angle, &dist1, &angle_up, &dist2);
	angle_home = angle - ModelData[ModelActive].yaw;
	if (angle_home > 180.0) {
		angle_home = angle_home - 360.0;
	}
	hud_draw_horizon(esContext, 1);
	glDisable(GL_DEPTH_TEST);

	// Rahmen
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	if (setup.hud_view_screen == 0) {
		draw_image(esContext, 0, 0, esContext->width, esContext->height, TEXTURE_HUD_FRAME);
	}

	// Alt
	draw_altiude_rule(esContext, 1.0, -0.6, 0.0, 0.0);

	// Speed
	draw_speed_rule(esContext, -1.0, -0.6, 0.0, 0.0);

	//SDL_Log("hud#6\n");

	// Status
//	draw_text_f3(esContext, -1.0 - strlen(statetypes[ModelData[ModelActive].armed]) * 0.07 * 0.6 / 2.0, -0.92, 0.002, 0.07, 0.07, FONT_GREEN, statetypes[ModelData[ModelActive].armed]);
//	draw_line_f3(esContext, -0.8, -0.94, 0.002, -0.8, -0.83, 0.002, 255, 255, 255, 255);

	if (ModelData[ModelActive].mode == 0) {
		sprintf(tmp_str, "MANUAL");
	} else if (ModelData[ModelActive].mode == 1) {
		sprintf(tmp_str, "ACRO");
	} else if (ModelData[ModelActive].mode == 2) {
		sprintf(tmp_str, "ALT_HOLD");
	} else if (ModelData[ModelActive].mode == 3) {
		sprintf(tmp_str, "AUTO");
	} else if (ModelData[ModelActive].mode == 4) {
		sprintf(tmp_str, "GUIDED");
	} else if (ModelData[ModelActive].mode == 5) {
		sprintf(tmp_str, "LOITER");
	} else if (ModelData[ModelActive].mode == 6) {
		sprintf(tmp_str, "RTL");
	} else if (ModelData[ModelActive].mode == 7) {
		sprintf(tmp_str, "CIRCLE");
	} else if (ModelData[ModelActive].mode == 8) {
		sprintf(tmp_str, "POSITION");
	} else if (ModelData[ModelActive].mode == 9) {
		sprintf(tmp_str, "LAND");
	} else if (ModelData[ModelActive].mode == 10) {
		sprintf(tmp_str, "OF_LOITER");
	} else if (ModelData[ModelActive].mode == 11) {
		sprintf(tmp_str, "DRIFT");
	} else if (ModelData[ModelActive].mode == 13) {
		sprintf(tmp_str, "SPORT");
	} else if (ModelData[ModelActive].mode == 16) {
		sprintf(tmp_str, "POSH");
	} else {
		sprintf(tmp_str, "UNKNOWN%i", ModelData[ModelActive].mode);
	}
//	draw_text_f3(esContext, -0.6 - strlen(tmp_str) * 0.07 * 0.6 / 2.0, -0.92, 0.002, 0.07, 0.07, FONT_GREEN, tmp_str);
//	draw_line_f3(esContext, -0.4, -0.94, 0.002, -0.4, -0.83, 0.002, 255, 255, 255, 255);

	// Yaw
	float compas_r = 0.9;
	float compas_y = 1.5;
	if (setup.hud_view_screen == 0) {
		draw_circleFilled_f(esContext, 0.0, compas_y, compas_r + 0.01, 0, 0, 0, 255);
	} else {
		draw_circleFilled_f(esContext, 0.0, compas_y, compas_r + 0.01, 0, 0, 0, 127);
	}
	draw_line_f(esContext, 0.0, compas_y - compas_r, 0.0, compas_y, 255, 255, 255, 255);
	sprintf(tmp_str, "%0.1f", ModelData[ModelActive].yaw);
	if (setup.contrast == 1) {
		draw_text_f(esContext, -0.2 - strlen(tmp_str) * 0.07 * 0.6 / 2.0 - 0.01, 0.9, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f(esContext, -0.2 - strlen(tmp_str) * 0.07 * 0.6 / 2.0 - 0.01, 0.9, 0.07, 0.07, FONT_PINK, tmp_str);
	}
	sprintf(tmp_str, "MAG");
	if (setup.contrast == 1) {
		draw_text_f(esContext, 0.2 - strlen(tmp_str) * 0.07 * 0.6 / 2.0 - 0.01, 0.9, 0.07, 0.07, FONT_WHITE, tmp_str);
	} else {
		draw_text_f(esContext, 0.2 - strlen(tmp_str) * 0.07 * 0.6 / 2.0 - 0.01, 0.9, 0.07, 0.07, FONT_GREEN, tmp_str);
	}

	//SDL_Log("hud#7\n");

	// Yaw-Arrow
	if (setup.contrast == 1) {
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r - 0.05 + 0.05, 0, 0, 0, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r - 0.05 + 0.05, 0, 0, 0, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.05, compas_y - compas_r - 0.05, 0, 0, 0, 255);
	} else {
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r - 0.05 + 0.05, 255, 255, 255, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r - 0.05 + 0.05, 255, 255, 255, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.05, compas_y - compas_r - 0.05, 255, 255, 255, 255);
	}

	for (n = (int)ModelData[ModelActive].yaw / 10 * 10 - 60; n <= (int)ModelData[ModelActive].yaw / 10 * 10 + 60; n += 10) {
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, -compas_y, -3.0);
		esRotate(&modelview, ((float)n - ModelData[ModelActive].yaw), 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, compas_y, 3.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		draw_line_f(esContext, 0.0, compas_y - compas_r, 0.0, compas_y - compas_r + 0.05, 255, 255, 255, 255);
		if (n >= 360) {
			sprintf(tmp_str, "%i", n - 360);
		} else if (n < 0) {
			sprintf(tmp_str, "%i", n + 360);
		} else {
			sprintf(tmp_str, "%i", n);
		}
		draw_text_f(esContext, 0.0 - strlen(tmp_str) * 0.05 * 0.6 / 2.0 - 0.01, compas_y - compas_r + 0.05, 0.05, 0.05, FONT_WHITE, tmp_str);
#ifdef SDLGL
		glPopMatrix();
#endif
	}
	for (n = (int)ModelData[ModelActive].yaw / 10 * 10 - 60; n <= (int)ModelData[ModelActive].yaw / 10 * 10 + 60; n += 1) {
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, -compas_y, -3.0);
		esRotate(&modelview, ((float)n - ModelData[ModelActive].yaw) + 5.0, 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, compas_y, 3.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		draw_line_f(esContext, 0.0, compas_y - compas_r, 0.0, compas_y - compas_r + 0.03, 255, 255, 255, 255);

#ifdef SDLGL
		glPopMatrix();
#endif
	}

	if (setup.weather_enable == 1) {
		double C = angle_wp - weather.wind_direction; // Wind/Plane-Angle-Diff
		if (C > 180.0) {
			C -= 360.0;
		}
		if (C < -180.0) {
			C += 360.0;
		}
		double a = weather.wind_speed * 3.6; // Wind-Speed
		double b = ModelData[ModelActive].speed; // Plane-Speed
		if (b < 1.0) {
			b = 1.0;
		}
		double c = sqrt((a * a) + (b * b) - (2.0 * a * b * cos(C * 3.14159 / 180.0)));
		double A = acos((a * a - b * b - c * c) / (-2 * b * c)) * 180.0 / 3.14159; // Correction-Angle
		if (C > 0.0) {
			A *= -1.0;
		}
		double NewDir = angle_wp - A;

		weather_draw_wind(esContext, -0.26, 0.76, 1);

	// Waypoint-Dir (Wind-Correction)
#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
#else
		esMatrixLoadIdentity(&modelview);
#endif
		esTranslate(&modelview, 0.0, -compas_y, -3.0);
		esRotate(&modelview, NewDir - ModelData[ModelActive].yaw, 0.0, 0.0, 1.0);
		esTranslate(&modelview, 0.0, compas_y, 3.0);
#ifndef SDLGL
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		// Next-Waypoint-Arrow (Wind-Correction)
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 255, 0, 0, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 255, 0, 0, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.05, compas_y - compas_r - 0.05, 255, 0, 0, 255);

		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 255, 0, 0, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 255, 0, 0, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.05, compas_y - compas_r + 0.05, 255, 0, 0, 255);
#ifdef SDLGL
		glPopMatrix();
#endif
	// Route-Dir Arrow (Waypoint) (Wind-Correction)
#ifndef SDLGL
		esMatrixLoadIdentity(&modelview);
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
		float diff_wpw = NewDir - ModelData[ModelActive].yaw;
		if (diff_wpw > 180.0) {
			diff_wpw -= 360.0;
		}
		if (diff_wpw < -180.0) {
			diff_wpw += 360.0;
		}
		sprintf(tmp_str, "%0.1f", diff_wpw);
		if (diff_wpw > 0.0) {
			draw_line_f(esContext, 0.0, 0.88, 0.1, 0.88, 255, 0, 0, 255);
			draw_line_f(esContext, 0.05, 0.88 - 0.01, 0.1, 0.88, 255, 0, 0, 255);
			draw_line_f(esContext, 0.05, 0.88 + 0.01, 0.1, 0.88, 255, 0, 0, 255);
			draw_text_f3(esContext, 0.11, 0.88 - 0.02, 0.002, 0.04, 0.04, FONT_GREEN, tmp_str);
		} else {
			draw_line_f(esContext, 0.0, 0.88, -0.1, 0.88, 255, 0, 0, 255);
			draw_line_f(esContext, -0.05, 0.88 - 0.01, -0.1, 0.88, 255, 0, 0, 255);
			draw_line_f(esContext, -0.05, 0.88 + 0.01, -0.1, 0.88, 255, 0, 0, 255);
			draw_text_f3(esContext, -0.11 - strlen(tmp_str) * 0.04 * 0.6 - 0.01, 0.88 - 0.02, 0.002, 0.04, 0.04, FONT_GREEN, tmp_str);
		}
	}


	// Home & Waypoint-Dir
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, -compas_y, -3.0);
	esRotate(&modelview, angle2, 0.0, 0.0, 1.0);
	esTranslate(&modelview, 0.0, compas_y, 3.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	// Next-Waypoint-Arrow
	if (setup.contrast == 1) {
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 255, 255, 255, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 255, 255, 255, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.05, compas_y - compas_r - 0.05, 255, 255, 255, 255);

		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 255, 255, 255, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 255, 255, 255, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.05, compas_y - compas_r + 0.05, 0, 255, 0, 255);
	} else {
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 0, 255, 0, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r - 0.05, 0.0, compas_y - compas_r, 0, 255, 0, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r - 0.05, 0.05, compas_y - compas_r - 0.05, 0, 255, 0, 255);

		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 0, 255, 0, 255);
		draw_line_f(esContext, 0.05, compas_y - compas_r + 0.05, 0.0, compas_y - compas_r + 0.05 - 0.05, 0, 255, 0, 255);
		draw_line_f(esContext, -0.05, compas_y - compas_r + 0.05, 0.05, compas_y - compas_r + 0.05, 0, 255, 0, 255);
	}
#ifdef SDLGL
	glPopMatrix();
#endif

	// Route-Dir Arrow (Waypoint)
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	float diff_wp = angle2;
	if (diff_wp > 180.0) {
		diff_wp -= 360.0;
	}
	if (diff_wp < -180.0) {
		diff_wp += 360.0;
	}
	sprintf(tmp_str, "%0.1f", diff_wp);
	if (diff_wp > 0.0) {
		if (setup.contrast == 1) {
			draw_line_f(esContext, 0.0, 0.85, 0.1, 0.85, 255, 255, 255, 255);
			draw_line_f(esContext, 0.05, 0.85 - 0.01, 0.1, 0.85, 255, 255, 255, 255);
			draw_line_f(esContext, 0.05, 0.85 + 0.01, 0.1, 0.85, 255, 255, 255, 255);
			draw_text_f3(esContext, 0.11, 0.85 - 0.02, 0.002, 0.04, 0.04, FONT_WHITE, tmp_str);
		} else {
			draw_line_f(esContext, 0.0, 0.85, 0.1, 0.85, 0, 255, 0, 255);
			draw_line_f(esContext, 0.05, 0.85 - 0.01, 0.1, 0.85, 0, 255, 0, 255);
			draw_line_f(esContext, 0.05, 0.85 + 0.01, 0.1, 0.85, 0, 255, 0, 255);
			draw_text_f3(esContext, 0.11, 0.85 - 0.02, 0.002, 0.04, 0.04, FONT_GREEN, tmp_str);
		}
	} else {
		if (setup.contrast == 1) {
			draw_line_f(esContext, 0.0, 0.85, -0.1, 0.85, 255, 255, 255, 255);
			draw_line_f(esContext, -0.05, 0.85 - 0.01, -0.1, 0.85, 255, 255, 255, 255);
			draw_line_f(esContext, -0.05, 0.85 + 0.01, -0.1, 0.85, 255, 255, 255, 255);
			draw_text_f3(esContext, -0.11 - strlen(tmp_str) * 0.04 * 0.6 - 0.01, 0.85 - 0.02, 0.002, 0.04, 0.04, FONT_WHITE, tmp_str);
		} else {
			draw_line_f(esContext, 0.0, 0.85, -0.1, 0.85, 0, 255, 0, 255);
			draw_line_f(esContext, -0.05, 0.85 - 0.01, -0.1, 0.85, 0, 255, 0, 255);
			draw_line_f(esContext, -0.05, 0.85 + 0.01, -0.1, 0.85, 0, 255, 0, 255);
			draw_text_f3(esContext, -0.11 - strlen(tmp_str) * 0.04 * 0.6 - 0.01, 0.85 - 0.02, 0.002, 0.04, 0.04, FONT_GREEN, tmp_str);
		}
	}



#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
#endif
	esTranslate(&modelview, 0.0, -compas_y, -3.0);
	esRotate(&modelview, angle_home, 0.0, 0.0, 1.0);
	esTranslate(&modelview, 0.0, compas_y, 3.0);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	// Home-Arrow
	float r = compas_y - compas_r + 0.1;
	draw_line_f(esContext, -0.03, r - 0.05, 0.0, r - 0.1, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, 0.03, r - 0.05, 0.0, r - 0.1, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, -0.03, r - 0.05, 0.03, r - 0.05, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, -0.03, r, 0.03, r, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, -0.03, r - 0.05, -0.03, r, 0xff, 0x33, 0xfc, 255);
	draw_line_f(esContext, 0.03, r - 0.05, 0.03, r, 0xff, 0x33, 0xfc, 255);
#ifdef SDLGL
	glPopMatrix();
#endif


	//SDL_Log("hud#9\n");

	// Route-Dir Arrow (Home)
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	if (angle_home > 0.0) {
		if (setup.contrast == 1) {
			draw_line_f(esContext, 0.0, 0.95, 0.05, 0.95, 255, 255, 255, 255);
			draw_line_f(esContext, 0.025, 0.95 - 0.01, 0.05, 0.95, 255, 255, 255, 255);
			draw_line_f(esContext, 0.025, 0.95 + 0.01, 0.05, 0.95, 255, 255, 255, 255);
		} else {
			draw_line_f(esContext, 0.0, 0.95, 0.05, 0.95, 0xff, 0x33, 0xfc, 255);
			draw_line_f(esContext, 0.025, 0.95 - 0.01, 0.05, 0.95, 0xff, 0x33, 0xfc, 255);
			draw_line_f(esContext, 0.025, 0.95 + 0.01, 0.05, 0.95, 0xff, 0x33, 0xfc, 255);
		}
	} else {
		if (setup.contrast == 1) {
			draw_line_f(esContext, 0.0, 0.95, -0.05, 0.95, 255, 255, 255, 255);
			draw_line_f(esContext, -0.025, 0.95 - 0.01, -0.05, 0.95, 255, 255, 255, 255);
			draw_line_f(esContext, -0.025, 0.95 + 0.01, -0.05, 0.95, 255, 255, 255, 255);
		} else {
			draw_line_f(esContext, 0.0, 0.95, -0.05, 0.95, 0xff, 0x33, 0xfc, 255);
			draw_line_f(esContext, -0.025, 0.95 - 0.01, -0.05, 0.95, 0xff, 0x33, 0xfc, 255);
			draw_line_f(esContext, -0.025, 0.95 + 0.01, -0.05, 0.95, 0xff, 0x33, 0xfc, 255);
		}
	}

	//SDL_Log("hud#9a\n");

#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	//SDL_Log("hud#9b\n");

	if (setup.hud_view_screen == 0 || setup.hud_view_screen == 1) {
		// Turn-Indicator
		draw_turning_indicator(esContext, 1.15, 0.25, 0.4, 0.1);

	//SDL_Log("hud#9c\n");

		// CPU, Voltage & Speed
		float volt_mind = 4.0;
		float volt_max = 6.0;
		float volt_diff = volt_max - volt_mind;
		float volt_diff2 = ModelData[ModelActive].voltage_rx - volt_mind;
		if (ModelData[ModelActive].found_rc != 1) {
			volt_mind = 10.0;
			volt_max = 12.6;
			volt_diff2 = ModelData[ModelActive].voltage - volt_mind;
		}
		float percent = 100.0 / volt_diff * volt_diff2;
		float voltage_all = 0.0;
		float voltage_real = 0.0;
		float voltage_max = 0.0;
		for (i = 0; i < 6; i++) {
			if (ModelData[ModelActive].voltage_zell[i] > 0.0) {
				voltage_real += ModelData[ModelActive].voltage_zell[i];
				voltage_all += ModelData[ModelActive].voltage_zell[i] - 3.0;
				voltage_max += 1.2;
			}
		}

		sprintf(tmp_str, "%0.0fkm/h", ModelData[ModelActive].speed);
		draw_circleMeter_f3(esContext, -1.05, -0.6, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, (ModelData[ModelActive].speed * 100.0 / 250.0), "Speed", tmp_str, 0);

		if (ModelData[ModelActive].found_rc == 1) {
			sprintf(tmp_str, "%0.1fV", ModelData[ModelActive].voltage_rx);
			draw_circleMeter_f3(esContext, -1.05, -0.3, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, percent, "Volt-RX", tmp_str, 0);
		} else {
			sprintf(tmp_str, "%0.1fV", ModelData[ModelActive].voltage);
			draw_circleMeter_f3(esContext, -1.05, -0.3, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, percent, "Volt", tmp_str, 0);
		}

		if (voltage_max != 0.0) {
			sprintf(tmp_str, "%0.1fV", voltage_real);
			draw_circleMeter_f3(esContext, -1.05, 0.3, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, voltage_all * 100.0 / voltage_max, "Volt", tmp_str, 0);
		}

		if (ModelData[ModelActive].found_rc == 1) {
			sprintf(tmp_str, "%0.1fA", ModelData[ModelActive].ampere);
			draw_circleMeter_f3(esContext, -1.05, 0.6, 0.001, 0.14, 0.0, 25.0, 50.0, 180.0, ModelData[ModelActive].ampere, "Strom", tmp_str, 0);
		}

	//SDL_Log("hud#9e\n");

		if (ModelData[ModelActive].teletype != TELETYPE_MULTIWII_21 && ModelData[ModelActive].teletype != TELETYPE_BASEFLIGHT) {
			sprintf(tmp_str, "CPU %0.0f%%", ModelData[ModelActive].load);
			draw_circleMeter_f3(esContext, -1.05, -0.1, 0.001, 0.06, 20.0, 33.0, 66.0, 160.0, ModelData[ModelActive].load, "", "", 3);
			draw_text_button(esContext, "hud_load", VIEW_MODE_HUD, tmp_str, FONT_WHITE, -1.05, -0.1, 0.003, 0.035, 1, 0, hud_null, 0);
		}

		sprintf(tmp_str, "PRESS %0.2f", ModelData[ModelActive].press_abs);
		draw_circleMeter_f3(esContext, -1.05, 0.1, 0.001, 0.06, 20.0, 33.0, 66.0, 160.0, ModelData[ModelActive].press_abs / 20.0, "", "", 3);
		draw_text_button(esContext, "hud_press", VIEW_MODE_HUD, tmp_str, FONT_WHITE, -1.05, 0.1, 0.003, 0.035, 1, 0, hud_null, 0);

		sprintf(tmp_str, "VARIO %0.2f", ModelData[ModelActive].press_diff);
		draw_circleMeter_f3(esContext, -1.05, 0.2, 0.001, 0.06, 20.0, 33.0, 66.0, 160.0, ModelData[ModelActive].press_diff + 50.0, "", "", 3);
		draw_text_button(esContext, "hud_press", VIEW_MODE_HUD, tmp_str, FONT_WHITE, -1.05, 0.2, 0.003, 0.035, 1, 0, hud_null, 0);

		sprintf(tmp_str, "TEMP %0.1f'C", ModelData[ModelActive].temperature[0]);
		draw_circleMeter_f3(esContext, -1.05, 0.3, 0.001, 0.06, 20.0, 33.0, 66.0, 160.0, ModelData[ModelActive].temperature[0], "", "", 3);
		draw_text_button(esContext, "hud_press", VIEW_MODE_HUD, tmp_str, FONT_WHITE, -1.05, 0.3, 0.003, 0.035, 1, 0, hud_null, 0);

#ifdef USE_WIFIBC
		sprintf(tmp_str, "Channel: %i", setup.wifibc_channel);
		draw_text_button(esContext, "wifibc_channel", VIEW_MODE_HUD, tmp_str, FONT_GREEN, -1.05, 0.7, 0.005, 0.035, 1, 0, hud_wifibc_channel, 0);
		sprintf(tmp_str, "%idBm", GroundData.wifibc_rssi[0]);
		draw_circleMeter_f3(esContext, -1.05, 0.6, 0.001, 0.14, 0.0, 10.0, 25.0, 180.0, 100.0 - (GroundData.wifibc_rssi[0] / -64.0 * 100.0), "WifiBC", tmp_str, 0);
		if (setup.wifibc_record == 1) {
			sprintf(tmp_str, "Record: %0.2fMB", (float)setup.wifibc_record_size / 1024 / 1024);
			draw_text_button(esContext, "wifibc_record", VIEW_MODE_HUD, tmp_str, FONT_PINK, -1.05, 0.73, 0.005, 0.035, 1, 0, hud_wifibc_record, 0);
		} else {
			draw_text_button(esContext, "wifibc_record", VIEW_MODE_HUD, "Record", FONT_GREEN, -1.05, 0.73, 0.005, 0.035, 1, 0, hud_wifibc_record, 0);
		}
#endif

	//SDL_Log("hud#9f\n");

		// RC-Values
		for (n = 0; n < ModelData[ModelActive].chancount && n < 16; n++) {
			float x1 = -1.3;
			float y1 = -0.55 + (float)n * 0.1;
			float val = (float)ModelData[ModelActive].radio[n] / 2.0 + 50.0;
			if (val > 100.0) {
				val = 100.0;
			} else if (val < -100.0) {
				val = -100.0;
			}
			if (ModelData[ModelActive].chancount > 8) {
				y1 -= 0.2;
			}
			if (n >= 4) {
				draw_circleMeter_f3(esContext, x1, y1, 0.001, 0.06, 20.0, 33.0, 66.0, 160.0, val, "", "", 1);
			} else {
				draw_circleMeter_f3(esContext, x1, y1, 0.001, 0.06, 20.0, 50.0, 50.0, 160.0, val, "", "", 1);
			}
			if (ModelData[ModelActive].teletype == TELETYPE_MULTIWII_21 || ModelData[ModelActive].teletype == TELETYPE_OPENPILOT || ModelData[ModelActive].teletype == TELETYPE_BASEFLIGHT) {
				if (n == 0) {
					draw_text_button(esContext, "hud_rd_1", VIEW_MODE_HUD, "ROLL", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 1) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "PITCH", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 2) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "YAW", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 3) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "THROTTLE", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 4) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX1", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 5) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX2", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 6) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX3", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 7) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX4", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else  {
					sprintf(tmp_str, "CH %i", n);
					draw_text_button(esContext, tmp_str, VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				}
			} else if (ModelData[ModelActive].teletype == TELETYPE_AUTOQUAD) {
				if (n == 0) {
					draw_text_button(esContext, "hud_rd_1", VIEW_MODE_HUD, "THROTTLE", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 1) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "ROLL", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 2) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "PITCH", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 3) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "YAW", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 4) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "GEAR", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 5) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "MAN/PH/W", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 6) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "RTL/SH", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 7) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX3", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else  {
					sprintf(tmp_str, "CH %i", n);
					draw_text_button(esContext, tmp_str, VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				}
			} else if (ModelData[ModelActive].teletype == TELETYPE_ARDUPILOT || ModelData[ModelActive].teletype == TELETYPE_MEGAPIRATE_NG) {
				if (n == 0) {
					draw_text_button(esContext, "hud_rd_1", VIEW_MODE_HUD, "ROLL", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 1) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "PITCH", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 2) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "THROTTLE", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 3) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "YAW", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 4) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "MODE", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 5) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "CH7", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 6) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "CH8", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else if (n == 7) {
					draw_text_button(esContext, "hud_rd_2", VIEW_MODE_HUD, "AUX", FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				} else  {
					sprintf(tmp_str, "CH %i", n);
					draw_text_button(esContext, tmp_str, VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
				}
			} else {
				sprintf(tmp_str, "CH %i", n);
				draw_text_button(esContext, tmp_str, VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1, 0.003, 0.035, 1, 0, hud_null, 0);
			}
		}
		static float min_g = 1.0;
		static float max_g = 0.0;

		if (setup.weather_enable == 1) {
			weather_draw(esContext, 1.0, -0.15);
		}


	//SDL_Log("hud#9g\n");

		float all_g = ModelData[ModelActive].acc_z * -1;
		if (ModelData[ModelActive].teletype == TELETYPE_MULTIWII_21 || ModelData[ModelActive].teletype == TELETYPE_BASEFLIGHT) {
			all_g = (float)ModelData[ModelActive].acc_z / 256.0;
		}
		if (min_g > all_g) {
			min_g = all_g;
		}
		if (max_g < all_g) {
			max_g = all_g;
		}
		sprintf(tmp_str, "Accel: %0.1fg", all_g);
		sprintf(tmp_str2, "%0.1fg %0.1fg", min_g, max_g);
		draw_circleMeter_f3(esContext, 1.15, -0.6, 0.001, 0.14, 0.0, 0.0, 50.0, 180.0, 50.0, tmp_str, tmp_str2, 0);
		draw_circleMeter_f3(esContext, 1.15, -0.3, 0.001, 0.14, 0.0, 50.0, 50.0, 180.0, 50.0, "Vario", "-1.2m/s", 0);


		if (ModelData[ModelActive].found_rc == 1) {
			// Lipo-Watch
			for (i = 0; i < 6; i++) {
				sprintf(tmp_str2, "hud_lv%i", i);
				if (ModelData[ModelActive].voltage_zell[i] != 0.0) {
					sprintf(tmp_str, "%0.2fV", ModelData[ModelActive].voltage_zell[i]);
					draw_circleMeter_f3(esContext, -1.3, 0.3 + (i * 0.1), 0.001, 0.06, 20.0, 20.0, 40.0, 160.0, ((ModelData[ModelActive].voltage_zell[i] - 3.0) * 100.0 / 1.2), "", "", 1);
					draw_text_button(esContext, tmp_str2, VIEW_MODE_HUD, tmp_str, FONT_WHITE, -1.3, 0.3 + (i * 0.1), 0.003, 0.035, 1, 0, hud_null, 0);
				}
			}

			// Temperature
			draw_circleMeter_f3(esContext, 1.07, 0.025, 0.001, 0.06, 20.0, 50.0, 50.0, 160.0, ((float)ModelData[ModelActive].temperature[0] + 30) * 100 / 280, "", "", 3);
			sprintf(tmp_str, "%0.1f°C", ModelData[ModelActive].temperature[0]);
			draw_text_button(esContext, "temp1", VIEW_MODE_HUD, tmp_str, FONT_WHITE, 1.07, 0.025, 0.003, 0.035, 1, 0, hud_null, 0);
			draw_circleMeter_f3(esContext, 1.23, 0.025, 0.001, 0.06, 20.0, 50.0, 50.0, 160.0, 50.0, "", "", 3);
			sprintf(tmp_str, "%0.1f°C", ModelData[ModelActive].temperature[1]);
			draw_text_button(esContext, "temp2", VIEW_MODE_HUD, tmp_str, FONT_WHITE, 1.23, 0.025, 0.003, 0.035, 1, 0, hud_null, 0);

			// Test-Graph
			graph1_data[0][graph1_pointer] = ModelData[ModelActive].rssi_rx;
			graph1_data[1][graph1_pointer] = ModelData[ModelActive].rssi_tx;
			if (graph1_pointer < graph1_size) {
				graph1_pointer++;
			} else {
				graph1_pointer = 0;
			}
			for (n = 0; n < 2; n++) {
				draw_box_f3(esContext, 0.95, 0.45 + (float)n * 0.1, 0.001, 1.35, 0.45 + (float)n * 0.1 + 0.08, 0.001, 200, 200, 200, 64);
				draw_line_f3(esContext, 0.95, 0.45 + (float)n * 0.1 + 0.04, 0.002, 1.35, 0.45 + (float)n * 0.1 + 0.04, 0.002, 255, 255, 255, 127);
				if (n == 0) {
					draw_text_button(esContext, "rssi_rx", VIEW_MODE_HUD, "RSSI RX", FONT_WHITE, 0.95, 0.45 + (float)n * 0.1 + 0.05, 0.002, 0.035, 0, 0, hud_null, 0);
				} else {
					draw_text_button(esContext, "rssi_tx", VIEW_MODE_HUD, "RSSI TX", FONT_WHITE, 0.95, 0.45 + (float)n * 0.1 + 0.05, 0.002, 0.035, 0, 0, hud_null, 0);
				}
				draw_graph_value(esContext, 0.95, 0.45 + (float)n * 0.1, 1.35, 0.45 + (float)n * 0.1 + 0.08, 0.001, graph1_data[n], graph1_size, graph1_pointer, 255 - n * 25, n * 25, n * 125, 255);
			}
			draw_image_f3(esContext, 0.8, 0.85, 1.0, 0.96, 0.002, ModelData[ModelActive].image);
		}
	}

	//SDL_Log("hud#10\n");

	// Draw Jeti-Telemetrie
	if (jeti_ok == 1) {
		float jetibox_x = -1.15;
		float jetibox_y = 0.65;
		draw_box_f3c2(esContext, jetibox_x - 0.01, jetibox_y - 0.025, 0.001, jetibox_x + 0.52, jetibox_y + 0.12, 0.001, 255, 255, 255, 127, 255, 255, 255, 64);
		draw_text_f3(esContext, jetibox_x, jetibox_y, 0.003, 0.05, 0.05, FONT_WHITE, jeti_line1);
		draw_text_f3(esContext, jetibox_x, jetibox_y + 0.05, 0.003, 0.05, 0.05, FONT_WHITE, jeti_line2);
		draw_text_button(esContext, "jeti_left", VIEW_MODE_HUD, "<", FONT_GREEN_BG, jetibox_x + 0.07	, jetibox_y + 0.15, 0.002, 0.05, 0, 0, jeti_left, 0);
		draw_text_button(esContext, "jeti_up", VIEW_MODE_HUD, "^", FONT_GREEN_BG, jetibox_x + 0.17, jetibox_y + 0.15, 0.002, 0.05, 0, 0, jeti_up, 0);
		draw_text_button(esContext, "jeti_down", VIEW_MODE_HUD, "v", FONT_GREEN_BG, jetibox_x + 0.27, jetibox_y + 0.15, 0.002, 0.05, 0, 0, jeti_down, 0);
		draw_text_button(esContext, "jeti_right", VIEW_MODE_HUD, ">", FONT_GREEN_BG, jetibox_x + 0.37, jetibox_y + 0.15, 0.002, 0.05, 0, 0, jeti_right, 0);
	}

	if (setup.hud_view_screen == 0) {
		draw_text_button(esContext, "view_hud", VIEW_MODE_HUD, "VIEW", FONT_WHITE, -1.35, 0.9, 0.002, 0.06, 0, 0, view_hud, 0);
	} else if (setup.hud_view_screen == 1) {
		draw_text_button(esContext, "view_hud", VIEW_MODE_HUD, "VIEW", FONT_PINK, -1.35, 0.9, 0.002, 0.06, 0, 0, view_hud, 0);
	} else {
		draw_text_button(esContext, "view_hud", VIEW_MODE_HUD, "VIEW", FONT_GREEN, -1.35, 0.9, 0.002, 0.06, 0, 0, view_hud, 0);
	}
#ifdef SDLGL
	if (setup.hud_view_map != 0) {
		draw_text_button(esContext, "view_hud_mark", VIEW_MODE_HUD, "MARK", FONT_GREEN, -1.35, 0.8, 0.002, 0.06, 0, 0, view_hud_mark, 0);
		if (setup.hud_view_map == 1) {
			draw_text_button(esContext, "view_hud_map", VIEW_MODE_HUD, "MAP", FONT_GREEN, -1.15, 0.9, 0.002, 0.06, 0, 0, view_hud_map, 0);
		} else if (setup.hud_view_map == 2) {
			draw_text_button(esContext, "view_hud_map", VIEW_MODE_HUD, "MAP", FONT_PINK, -1.15, 0.9, 0.002, 0.06, 0, 0, view_hud_map, 0);
		} else {
			draw_text_button(esContext, "view_hud_map", VIEW_MODE_HUD, "MAP", FONT_PINK, -1.15, 0.9, 0.002, 0.06, 0, 0, view_hud_map, 0);
		}
//		if (setup.hud_view_tunnel == 1) {
//			draw_text_button(esContext, "view_map_tunnel", VIEW_MODE_HUD, "TUNNEL", FONT_GREEN, -1.0, 0.9, 0.002, 0.06, 0, 0, view_hud_tunnel, 0);
//		} else {
//			draw_text_button(esContext, "view_map_tunnel", VIEW_MODE_HUD, "TUNNEL", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 0, 0, view_hud_tunnel, 0);
//		}
		setup.hud_view_tunnel = 0;
		if (setup.hud_view_stab == 1) {
			draw_text_button(esContext, "view_hud_stab", VIEW_MODE_HUD, "STAB", FONT_GREEN, -1.0, 0.8, 0.002, 0.06, 0, 0, view_hud_stab, 0);
		} else if (setup.hud_view_stab == 2) {
			draw_text_button(esContext, "view_hud_stab", VIEW_MODE_HUD, "STAB", FONT_PINK, -1.0, 0.8, 0.002, 0.06, 0, 0, view_hud_stab, 0);
		} else {
			draw_text_button(esContext, "view_hud_stab", VIEW_MODE_HUD, "STAB", FONT_WHITE, -1.0, 0.8, 0.002, 0.06, 0, 0, view_hud_stab, 0);
		}
	} else {
		draw_text_button(esContext, "view_hud_map", VIEW_MODE_HUD, "MAP", FONT_WHITE, -1.15, 0.9, 0.002, 0.06, 0, 0, view_hud_map, 0);
		draw_text_button(esContext, "view_map_bw", VIEW_MODE_HUD, "BW", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 0, 0, view_hud_bw, 0);
	}
	if (setup.hud_view_video == 1) {
		draw_text_button(esContext, "view_hud_video", VIEW_MODE_HUD, "VID", FONT_GREEN, -1.15, 0.8, 0.002, 0.06, 0, 0, view_hud_video, 0);
	} else {
		draw_text_button(esContext, "view_hud_video", VIEW_MODE_HUD, "VID", FONT_WHITE, -1.15, 0.8, 0.002, 0.06, 0, 0, view_hud_video, 0);
	}

	if (ModelData[ModelActive].dronetype == 26) {
		draw_text_button(esContext, "gimbal_pitch", VIEW_MODE_HUD, "PITCH", FONT_WHITE, -1.2, 0.5, 0.002, 0.06, 0, 0, gimbal_set_pitch, 0);
		draw_text_button(esContext, "gimbal_roll", VIEW_MODE_HUD, "ROLL", FONT_WHITE, -1.2, 0.6, 0.002, 0.06, 0, 0, gimbal_set_roll, 0);
		draw_text_button(esContext, "gimbal_yaw", VIEW_MODE_HUD, "YAW", FONT_WHITE, -1.2, 0.7, 0.002, 0.06, 0, 0, gimbal_set_yaw, 0);
	}

#else
	draw_text_button(esContext, "view_map_bw", VIEW_MODE_HUD, "BW", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 0, 0, view_hud_bw, 0);
#endif
	if (ModelData[ModelActive].dronetype == MAV_TYPE_GENERIC) {
		strcpy(tmp_str, "Generic air vehicle");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_FIXED_WING) {
		strcpy(tmp_str, "Fixed wing aircraft");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_QUADROTOR) {
		strcpy(tmp_str, "Quadrotor");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_COAXIAL) {
		strcpy(tmp_str, "Coaxial helicopter");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_HELICOPTER) {
		strcpy(tmp_str, "Helicopter");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_ANTENNA_TRACKER) {
		strcpy(tmp_str, "Antenna-Tracker");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_GCS) {
		strcpy(tmp_str, "ground control station");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_AIRSHIP) {
		strcpy(tmp_str, "Airship, controlled");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_FREE_BALLOON) {
		strcpy(tmp_str, "Free balloon, uncontrolled");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_ROCKET) {
		strcpy(tmp_str, "Rocket");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_GROUND_ROVER) {
		strcpy(tmp_str, "Ground rover");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_SURFACE_BOAT) {
		strcpy(tmp_str, "Boat");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_SUBMARINE) {
		strcpy(tmp_str, "Submarine");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_HEXAROTOR) {
		strcpy(tmp_str, "Hexarotor");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_OCTOROTOR) {
		strcpy(tmp_str, "Octorotor");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_TRICOPTER) {
		strcpy(tmp_str, "Tricopter");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_FLAPPING_WING) {
		strcpy(tmp_str, "Flapping wing");
	} else if (ModelData[ModelActive].dronetype == MAV_TYPE_KITE) {
		strcpy(tmp_str, "Flapping wing");
	} else if (ModelData[ModelActive].dronetype == 26) {
		sprintf(tmp_str, "BL-Gimabal");
	} else {
		sprintf(tmp_str, "UNKNOWN(%i)", ModelData[ModelActive].dronetype);
	}
	draw_text_button(esContext, "view_hud_v", VIEW_MODE_HUD, tmp_str, FONT_GREEN, 0.0, -0.99, 0.002, 0.06, 1, 0, hud_null, 0);

#ifdef SDLGL
#ifndef WINDOWS
	if (setup.hud_view_screen != 2 && draw_target() == 0) {
		draw_buffer_to_screen(0.9, 0.45, 1.4, 0.9, 0.0, 1.0);
		draw_rect_f3(esContext, 0.9, 0.45, 0.002, 1.4, 0.9, 0.002, 0, 0, 0, 255);
		draw_rect_f3(esContext, 0.9 - 0.005, 0.45 - 0.005, 0.002, 1.4 + 0.005, 0.9 + 0.005, 0.002, 255, 255, 255, 255);
		set_button("goto_map", setup.view_mode, 0.9, 0.45, 1.4, 0.9, hud_goto_screen, (float)VIEW_MODE_MAP, 0);
	}
#endif
#endif
#ifdef SDLGL
	glPopMatrix();
#endif
	glEnable(GL_DEPTH_TEST);
}

void screen_hud (ESContext *esContext) {
#ifdef USE_VISTA2D
	if (hud_use_vista2d == 1) {
		screen_hud_vista2d(esContext);
	} else {
		screen_hud_internal(esContext);
		draw_text_button(esContext, "tINTERNAL", setup.view_mode, "Vista2D", FONT_GREEN, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, vista2d_cmd, 0.0);
	}
#else
	screen_hud_internal(esContext);
#endif
}
