
#include <all.h>


#define SLIDER_START	-1.0
#define SLIDER_LEN	2.0

static uint8_t mode = 0;

uint8_t simplebgc_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t simplebgc_mode (char *name, float x, float y, int8_t button, float data) {
	if (mode < 2) {
		mode++;
	} else {
		mode = 0;
	}
	return 0;
}

void screen_simplebgc (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	draw_title(esContext, "SimpleBGC (Brushless-Gimbal-Controller)");
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	uint16_t nx = 0;
	uint16_t ny = 0;
	char tmp_str[1024];

if (mode == 0) {

	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "AXIS", FONT_GREEN, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "P", FONT_GREEN, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "I", FONT_GREEN, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "D", FONT_GREEN, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "Pwr", FONT_GREEN, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "Inv", FONT_GREEN, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "Pol", FONT_GREEN, -1.3 + 6 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " ROLL", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);

	sprintf(tmp_str, "%i", simplebgc_setup.roll_p);
	draw_text_button(esContext, "vroll_p", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_i);
	draw_text_button(esContext, "vroll_i", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_d);
	draw_text_button(esContext, "vroll_d", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_power);
	draw_text_button(esContext, "vroll_power", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_invert);
	draw_text_button(esContext, "vroll_invert", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_poles);
	draw_text_button(esContext, "vroll_poles", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;


	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " PITCH", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);

	sprintf(tmp_str, "%i", simplebgc_setup.pitch_p);
	draw_text_button(esContext, "vpitch_p", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_i);
	draw_text_button(esContext, "vpitch_i", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_d);
	draw_text_button(esContext, "vpitch_d", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_power);
	draw_text_button(esContext, "vpitch_power", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_invert);
	draw_text_button(esContext, "vpitch_invert", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_poles);
	draw_text_button(esContext, "vpitch_poles", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;


	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " YAW", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);

	sprintf(tmp_str, "%i", simplebgc_setup.yaw_p);
	draw_text_button(esContext, "vyaw_p", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_i);
	draw_text_button(esContext, "vyaw_i", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_d);
	draw_text_button(esContext, "vyaw_d", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_power);
	draw_text_button(esContext, "vyaw_power", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_invert);
	draw_text_button(esContext, "vyaw_invert", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_poles);
	draw_text_button(esContext, "vyaw_poles", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;


	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "AXIS", FONT_GREEN, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "MIN", FONT_GREEN, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "MAX", FONT_GREEN, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "MODE", FONT_GREEN, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "LPF", FONT_GREEN, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "SPEED", FONT_GREEN, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "FOLLOW", FONT_GREEN, -1.3 + 6 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " ROLL", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);

	sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_min_angle);
	draw_text_button(esContext, "vroll_rc_min_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_max_angle);
	draw_text_button(esContext, "vroll_rc_max_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_mode);
	draw_text_button(esContext, "vroll_rc_mode", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_lpf);
	draw_text_button(esContext, "vroll_rc_lpf", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_speed);
	draw_text_button(esContext, "vroll_rc_speed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_follow);
	draw_text_button(esContext, "vroll_rc_follow", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " PITCH", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);

	sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_min_angle);
	draw_text_button(esContext, "vpitch_rc_min_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_max_angle);
	draw_text_button(esContext, "vpitch_rc_max_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_mode);
	draw_text_button(esContext, "vpitch_rc_mode", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_lpf);
	draw_text_button(esContext, "vpitch_rc_lpf", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_speed);
	draw_text_button(esContext, "vpitch_rc_speed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_follow);
	draw_text_button(esContext, "vpitch_rc_follow", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " YAW", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);

	sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_min_angle);
	draw_text_button(esContext, "vyaw_rc_min_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_max_angle);
	draw_text_button(esContext, "vyaw_rc_max_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_mode);
	draw_text_button(esContext, "vyaw_rc_mode", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_lpf);
	draw_text_button(esContext, "vyaw_rc_lpf", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_speed);
	draw_text_button(esContext, "vyaw_rc_speed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_follow);
	draw_text_button(esContext, "vyaw_rc_follow", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;


	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "AXIS", FONT_GREEN, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "TRIM", FONT_GREEN, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "MAP", FONT_GREEN, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "FOFF", FONT_GREEN, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "OUT", FONT_GREEN, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "FCGAIN", FONT_GREEN, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " ROLL", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);

	sprintf(tmp_str, "%i", simplebgc_setup.rc_trim_roll);
	draw_text_button(esContext, "vrc_trim_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.rc_map_roll);
	draw_text_button(esContext, "vrc_map_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.follow_offset_roll);
	draw_text_button(esContext, "vfollow_offset_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.output_roll);
	draw_text_button(esContext, "voutput_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.ext_fc_gain_roll);
	draw_text_button(esContext, "vext_fc_gain_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " PITCH", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);

	sprintf(tmp_str, "%i", simplebgc_setup.rc_trim_pitch);
	draw_text_button(esContext, "vrc_trim_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.rc_map_pitch);
	draw_text_button(esContext, "vrc_map_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.follow_offset_pitch);
	draw_text_button(esContext, "vfollow_offset_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.output_pitch);
	draw_text_button(esContext, "voutput_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.ext_fc_gain_pitch);
	draw_text_button(esContext, "vext_fc_gain_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " YAW", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);

	sprintf(tmp_str, "%i", simplebgc_setup.rc_trim_yaw);
	draw_text_button(esContext, "vrc_trim_yaw", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.rc_map_yaw);
	draw_text_button(esContext, "vrc_map_yaw", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.follow_offset_yaw);
	draw_text_button(esContext, "vfollow_offset_yaw", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	sprintf(tmp_str, "%i", simplebgc_setup.output_yaw);
	draw_text_button(esContext, "voutput_yaw", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;


} else if (mode == 1) {

	sprintf(tmp_str, "%i", simplebgc_setup.rc_deadband);
	draw_text_button(esContext, "nrc_deadband", VIEW_MODE_FCMENU, "rc_deadband", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vrc_deadband", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.rc_expo_rate);
	draw_text_button(esContext, "nrc_expo_rate", VIEW_MODE_FCMENU, "rc_expo_rate", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vrc_expo_rate", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.rc_source);
	draw_text_button(esContext, "nrc_source", VIEW_MODE_FCMENU, "rc_source", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vrc_source", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.rc_map_cmd);
	draw_text_button(esContext, "nrc_map_cmd", VIEW_MODE_FCMENU, "rc_map_cmd", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vrc_map_cmd", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.rc_cmd_low);
	draw_text_button(esContext, "nrc_cmd_low", VIEW_MODE_FCMENU, "rc_cmd_low", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vrc_cmd_low", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.rc_cmd_mid);
	draw_text_button(esContext, "nrc_cmd_mid", VIEW_MODE_FCMENU, "rc_cmd_mid", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vrc_cmd_mid", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.rc_cmd_high);
	draw_text_button(esContext, "nrc_cmd_high", VIEW_MODE_FCMENU, "rc_cmd_high", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vrc_cmd_high", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_1);
	draw_text_button(esContext, "nmenu_cmd_1", VIEW_MODE_FCMENU, "menu_cmd_1", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vmenu_cmd_1", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_2);
	draw_text_button(esContext, "nmenu_cmd_2", VIEW_MODE_FCMENU, "menu_cmd_2", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vmenu_cmd_2", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_3);
	draw_text_button(esContext, "nmenu_cmd_3", VIEW_MODE_FCMENU, "menu_cmd_3", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vmenu_cmd_3", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_4);
	draw_text_button(esContext, "nmenu_cmd_4", VIEW_MODE_FCMENU, "menu_cmd_4", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vmenu_cmd_4", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_5);
	draw_text_button(esContext, "nmenu_cmd_5", VIEW_MODE_FCMENU, "menu_cmd_5", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vmenu_cmd_5", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_long);
	draw_text_button(esContext, "nmenu_cmd_long", VIEW_MODE_FCMENU, "menu_cmd_long", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vmenu_cmd_long", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

} else if (mode == 2) {

	sprintf(tmp_str, "%i", simplebgc_setup.gyro_trust);
	draw_text_button(esContext, "ngyro_trust", VIEW_MODE_FCMENU, "gyro_trust", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vgyro_trust", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.gyro_lpf);
	draw_text_button(esContext, "ngyro_lpf", VIEW_MODE_FCMENU, "gyro_lpf", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vgyro_lpf", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.skip_gyro_calib);
	draw_text_button(esContext, "nskip_gyro_calib", VIEW_MODE_FCMENU, "skip_gyro_calib", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vskip_gyro_calib", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.use_model);
	draw_text_button(esContext, "nuse_model", VIEW_MODE_FCMENU, "use_model", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vuse_model", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.pwm_freq);
	draw_text_button(esContext, "npwm_freq", VIEW_MODE_FCMENU, "pwm_freq", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vpwm_freq", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.serial_speed);
	draw_text_button(esContext, "nserial_speed", VIEW_MODE_FCMENU, "serial_speed", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vserial_speed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.follow_mode);
	draw_text_button(esContext, "nfollow_mode", VIEW_MODE_FCMENU, "follow_mode", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vfollow_mode", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.follow_deadband);
	draw_text_button(esContext, "nfollow_deadband", VIEW_MODE_FCMENU, "follow_deadband", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vfollow_deadband", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.follow_expo_rate);
	draw_text_button(esContext, "nfollow_expo_rate", VIEW_MODE_FCMENU, "follow_expo_rate", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vfollow_expo_rate", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.axis_top);
	draw_text_button(esContext, "naxis_top", VIEW_MODE_FCMENU, "axis_top", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vaxis_top", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.axis_right);
	draw_text_button(esContext, "naxis_right", VIEW_MODE_FCMENU, "axis_right", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vaxis_right", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

	sprintf(tmp_str, "%i", simplebgc_setup.i2c_internal_pullups);
	draw_text_button(esContext, "ni2c_internal_pullups", VIEW_MODE_FCMENU, "i2c_internal_pullups", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	draw_text_button(esContext, "vi2c_internal_pullups", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.07, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_null, 0.0);
	nx++;

}

	sprintf(tmp_str, "MODE(%i)", mode);
	draw_text_button(esContext, "mode", VIEW_MODE_FCMENU, "MODE", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, simplebgc_mode, 0.0);

}

