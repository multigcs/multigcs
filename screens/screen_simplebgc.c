
#include <all.h>

#define SLIDER_START	-1.0
#define SLIDER_LEN	2.0
#define VALUES_MAX 76

typedef struct {
	void *var;
	char name[32];
	char title[32];
	uint8_t type;
	int32_t min;
	int32_t max;
} vDescription;

enum {
	TYPE_U8,
	TYPE_S8,
	TYPE_U16,
	TYPE_S16
};

static uint8_t mode = 0;
static char select_name[1024];
static uint32_t select_n = 0;
static int32_t select_value = 0;
static int32_t select_min = 0;
static int32_t select_max = 0;

static vDescription vdes[VALUES_MAX] = {
	{&simplebgc_setup.roll_p, "roll_p", "ROLL_P", TYPE_U8, 0, 255},
	{&simplebgc_setup.roll_i, "roll_i", "ROLL_I", TYPE_U8, 0, 255},
	{&simplebgc_setup.roll_d, "roll_d", "ROLL_D", TYPE_U8, 0, 255},
	{&simplebgc_setup.roll_power, "roll_power", "ROLL_POWER", TYPE_U8, 0, 255},
	{&simplebgc_setup.roll_invert, "roll_invert", "ROLL_INVERT", TYPE_U8, 0, 255},
	{&simplebgc_setup.roll_poles, "roll_poles", "ROLL_POLES", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_p, "pitch_p", "PITCH_P", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_i, "pitch_i", "PITCH_I", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_d, "pitch_d", "PITCH_D", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_power, "pitch_power", "PITCH_POWER", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_invert, "pitch_invert", "PITCH_INVERT", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_poles, "pitch_poles", "PITCH_POLES", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_p, "yaw_p", "YAW_P", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_i, "yaw_i", "YAW_I", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_d, "yaw_d", "YAW_D", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_power, "yaw_power", "YAW_POWER", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_invert, "yaw_invert", "YAW_INVERT", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_poles, "yaw_poles", "YAW_POLES", TYPE_U8, 0, 255},
	{&simplebgc_setup.ext_fc_gain_roll, "ext_fc_gain_roll", "EXT_FC_GAIN_ROLL", TYPE_S8, -127, 127},
	{&simplebgc_setup.ext_fc_gain_pitch, "ext_fc_gain_pitch", "EXT_FC_GAIN_PITCH", TYPE_S8, -127, 127},
	{&simplebgc_setup.roll_rc_min_angle, "roll_rc_min_angle", "ROLL_RC_MIN_ANGLE", TYPE_S16, -35535, 35535},
	{&simplebgc_setup.roll_rc_max_angle, "roll_rc_max_angle", "ROLL_RC_MAX_ANGLE", TYPE_S16, -35535, 35535},
	{&simplebgc_setup.roll_rc_mode, "roll_rc_mode", "ROLL_RC_MODE", TYPE_U8, 0, 255},
	{&simplebgc_setup.roll_rc_lpf, "roll_rc_lpf", "ROLL_RC_LPF", TYPE_U8, 0, 255},
	{&simplebgc_setup.roll_rc_speed, "roll_rc_speed", "ROLL_RC_SPEED", TYPE_U8, 0, 255},
	{&simplebgc_setup.roll_rc_follow, "roll_rc_follow", "ROLL_RC_FOLLOW", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_rc_min_angle, "pitch_rc_min_angle", "PITCH_RC_MIN_ANGLE", TYPE_S16, -35535, 35535},
	{&simplebgc_setup.pitch_rc_max_angle, "pitch_rc_max_angle", "PITCH_RC_MAX_ANGLE", TYPE_S16, -35535, 35535},
	{&simplebgc_setup.pitch_rc_mode, "pitch_rc_mode", "PITCH_RC_MODE", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_rc_lpf, "pitch_rc_lpf", "PITCH_RC_LPF", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_rc_speed, "pitch_rc_speed", "PITCH_RC_SPEED", TYPE_U8, 0, 255},
	{&simplebgc_setup.pitch_rc_follow, "pitch_rc_follow", "PITCH_RC_FOLLOW", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_rc_min_angle, "yaw_rc_min_angle", "YAW_RC_MIN_ANGLE", TYPE_S16, -35535, 35535},
	{&simplebgc_setup.yaw_rc_max_angle, "yaw_rc_max_angle", "YAW_RC_MAX_ANGLE", TYPE_S16, -35535, 35535},
	{&simplebgc_setup.yaw_rc_mode, "yaw_rc_mode", "YAW_RC_MODE", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_rc_lpf, "yaw_rc_lpf", "YAW_RC_LPF", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_rc_speed, "yaw_rc_speed", "YAW_RC_SPEED", TYPE_U8, 0, 255},
	{&simplebgc_setup.yaw_rc_follow, "yaw_rc_follow", "YAW_RC_FOLLOW", TYPE_U8, 0, 255},
	{&simplebgc_setup.gyro_trust, "gyro_trust", "GYRO_TRUST", TYPE_U8, 0, 255},
	{&simplebgc_setup.use_model, "use_model", "USE_MODEL", TYPE_U8, 0, 255},
	{&simplebgc_setup.pwm_freq, "pwm_freq", "PWM_FREQ", TYPE_U8, 0, 255},
	{&simplebgc_setup.serial_speed, "serial_speed", "SERIAL_SPEED", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_trim_roll, "rc_trim_roll", "RC_TRIM_ROLL", TYPE_S8, -127, 127},
	{&simplebgc_setup.rc_trim_pitch, "rc_trim_pitch", "RC_TRIM_PITCH", TYPE_S8, -127, 127},
	{&simplebgc_setup.rc_trim_yaw, "rc_trim_yaw", "RC_TRIM_YAW", TYPE_S8, -127, 127},
	{&simplebgc_setup.rc_deadband, "rc_deadband", "RC_DEADBAND", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_expo_rate, "rc_expo_rate", "RC_EXPO_RATE", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_source, "rc_source", "RC_SOURCE", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_map_roll, "rc_map_roll", "RC_MAP_ROLL", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_map_pitch, "rc_map_pitch", "RC_MAP_PITCH", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_map_yaw, "rc_map_yaw", "RC_MAP_YAW", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_map_cmd, "rc_map_cmd", "RC_MAP_CMD", TYPE_U8, 0, 255},
	{&simplebgc_setup.follow_mode, "follow_mode", "FOLLOW_MODE", TYPE_U8, 0, 255},
	{&simplebgc_setup.follow_deadband, "follow_deadband", "FOLLOW_DEADBAND", TYPE_U8, 0, 255},
	{&simplebgc_setup.follow_expo_rate, "follow_expo_rate", "FOLLOW_EXPO_RATE", TYPE_U8, 0, 255},
	{&simplebgc_setup.follow_offset_roll, "follow_offset_roll", "FOLLOW_OFFSET_ROLL", TYPE_U8, 0, 255},
	{&simplebgc_setup.follow_offset_pitch, "follow_offset_pitch", "FOLLOW_OFFSET_PITCH", TYPE_U8, 0, 255},
	{&simplebgc_setup.follow_offset_yaw, "follow_offset_yaw", "FOLLOW_OFFSET_YAW", TYPE_S8, -127, 127},
	{&simplebgc_setup.axis_top, "axis_top", "AXIS_TOP", TYPE_S8, -127, 127},
	{&simplebgc_setup.axis_right, "axis_right", "AXIS_RIGHT", TYPE_S8, -127, 127},
	{&simplebgc_setup.gyro_lpf, "gyro_lpf", "GYRO_LPF", TYPE_U8, 0, 255},
	{&simplebgc_setup.i2c_internal_pullups, "i2c_internal_pullups", "I2C_INTERNAL_PULLUPS", TYPE_U8, 0, 255},
	{&simplebgc_setup.skip_gyro_calib, "skip_gyro_calib", "SKIP_GYRO_CALIB", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_cmd_low, "rc_cmd_low", "RC_CMD_LOW", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_cmd_mid, "rc_cmd_mid", "RC_CMD_MID", TYPE_U8, 0, 255},
	{&simplebgc_setup.rc_cmd_high, "rc_cmd_high", "RC_CMD_HIGH", TYPE_U8, 0, 255},
	{&simplebgc_setup.menu_cmd_1, "menu_cmd_1", "MENU_CMD_1", TYPE_U8, 0, 255},
	{&simplebgc_setup.menu_cmd_2, "menu_cmd_2", "MENU_CMD_2", TYPE_U8, 0, 255},
	{&simplebgc_setup.menu_cmd_3, "menu_cmd_3", "MENU_CMD_3", TYPE_U8, 0, 255},
	{&simplebgc_setup.menu_cmd_4, "menu_cmd_4", "MENU_CMD_4", TYPE_U8, 0, 255},
	{&simplebgc_setup.menu_cmd_5, "menu_cmd_5", "MENU_CMD_5", TYPE_U8, 0, 255},
	{&simplebgc_setup.menu_cmd_long, "menu_cmd_long", "MENU_CMD_LONG", TYPE_U8, 0, 255},
	{&simplebgc_setup.output_roll, "output_roll", "OUTPUT_ROLL", TYPE_U8, 0, 255},
	{&simplebgc_setup.output_pitch, "output_pitch", "OUTPUT_PITCH", TYPE_U8, 0, 255},
	{&simplebgc_setup.output_yaw, "output_yaw", "OUTPUT_YAW", TYPE_U8, 0, 255},
	{&simplebgc_setup.cur_profile, "cur_profile", "CUR_PROFILE", TYPE_U8, 0, 255},
};

uint8_t simplebgc_select (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	strcpy(select_name, name + 1);
	int n = 0;
	if (select_name[0] == 0) {
		return 0;
	}
	printf("## %s ##\n", select_name);
	for (n = 0; n < VALUES_MAX; n++) {
		if (strcmp(select_name, vdes[n].name) == 0) {
			select_n = n;
			break;
		}
	}
	if (n == VALUES_MAX) {
		return 0;
	}
	if (vdes[select_n].type == TYPE_U8) {
		uint8_t *val = (uint8_t *)vdes[select_n].var;
		select_value = val[0];
	} else if (vdes[select_n].type == TYPE_S8) {
		int8_t *val = (int8_t *)vdes[select_n].var;
		select_value = val[0];
	} else if (vdes[select_n].type == TYPE_U16) {
		uint16_t *val = (uint16_t *)vdes[select_n].var;
		select_value = val[0];
	} else if (vdes[select_n].type == TYPE_S16) {
		int16_t *val = (int16_t *)vdes[select_n].var;
		select_value = val[0];
	}
	select_min = vdes[select_n].min;
	select_max = vdes[select_n].max;
	return 0;
}

uint8_t simplebgc_change (char *name, float x, float y, int8_t button, float data) {
	select_value += (int32_t)data;
	if (select_value > select_max) {
		select_value = select_max;
	} else if (select_value < select_min) {
		select_value = select_min;
	}
	if (vdes[select_n].type == TYPE_U8) {
		uint8_t *val = (uint8_t *)vdes[select_n].var;
		val[0] = select_value;
	} else if (vdes[select_n].type == TYPE_S8) {
		int8_t *val = (int8_t *)vdes[select_n].var;
		val[0] = select_value;
	} else if (vdes[select_n].type == TYPE_U16) {
		uint16_t *val = (uint16_t *)vdes[select_n].var;
		val[0] = select_value;
	} else if (vdes[select_n].type == TYPE_S16) {
		int16_t *val = (int16_t *)vdes[select_n].var;
		val[0] = select_value;
	}
	reset_buttons();
	return 0;
}

uint8_t simplebgc_reload (char *name, float x, float y, int8_t button, float data) {
	simplebgc_send_cmd('R');
	return 0;
}

uint8_t simplebgc_save (char *name, float x, float y, int8_t button, float data) {
	simplebgc_send_cmd('W');
	return 0;
}

uint8_t simplebgc_mode (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
printf("####\n");
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
	char tmp_str2[1024];
	if (select_name[0] != 0) {
		draw_text_button(esContext, "t", VIEW_MODE_FCMENU, vdes[select_n].title, FONT_GREEN, 0.0, -0.4, 0.002, 0.08, ALIGN_CENTER, ALIGN_TOP, simplebgc_select, 0.0);
		sprintf(tmp_str, "-%s", select_name);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -0.6, 0.0, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, simplebgc_change, -1.0);
		sprintf(tmp_str, "=%s", select_name);
		sprintf(tmp_str2, "%i", select_value);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.0, 0.0, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, simplebgc_select, 0.0);
		sprintf(tmp_str, "+%s", select_name);
		draw_text_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.6, 0.0, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, simplebgc_change, 1.0);
		draw_text_button(esContext, "b", VIEW_MODE_FCMENU, "BACK", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, simplebgc_select, 0.0);

	} else {
		if (mode == 0) {
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "AXIS", FONT_GREEN, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "P", FONT_GREEN, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "I", FONT_GREEN, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "D", FONT_GREEN, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "Pwr", FONT_GREEN, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "Inv", FONT_GREEN, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "Pol", FONT_GREEN, -1.3 + 6 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " ROLL", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_p);
			draw_text_button(esContext, "vroll_p", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_i);
			draw_text_button(esContext, "vroll_i", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_d);
			draw_text_button(esContext, "vroll_d", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_power);
			draw_text_button(esContext, "vroll_power", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_invert);
			draw_text_button(esContext, "vroll_invert", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_poles);
			draw_text_button(esContext, "vroll_poles", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " PITCH", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_p);
			draw_text_button(esContext, "vpitch_p", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_i);
			draw_text_button(esContext, "vpitch_i", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_d);
			draw_text_button(esContext, "vpitch_d", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_power);
			draw_text_button(esContext, "vpitch_power", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_invert);
			draw_text_button(esContext, "vpitch_invert", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_poles);
			draw_text_button(esContext, "vpitch_poles", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " YAW", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_p);
			draw_text_button(esContext, "vyaw_p", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_i);
			draw_text_button(esContext, "vyaw_i", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_d);
			draw_text_button(esContext, "vyaw_d", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_power);
			draw_text_button(esContext, "vyaw_power", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_invert);
			draw_text_button(esContext, "vyaw_invert", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_poles);
			draw_text_button(esContext, "vyaw_poles", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "AXIS", FONT_GREEN, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "MIN", FONT_GREEN, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "MAX", FONT_GREEN, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "MODE", FONT_GREEN, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "LPF", FONT_GREEN, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "SPEED", FONT_GREEN, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "FOLLOW", FONT_GREEN, -1.3 + 6 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " ROLL", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_min_angle);
			draw_text_button(esContext, "vroll_rc_min_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_max_angle);
			draw_text_button(esContext, "vroll_rc_max_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_mode);
			draw_text_button(esContext, "vroll_rc_mode", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_lpf);
			draw_text_button(esContext, "vroll_rc_lpf", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_speed);
			draw_text_button(esContext, "vroll_rc_speed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.roll_rc_follow);
			draw_text_button(esContext, "vroll_rc_follow", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " PITCH", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_min_angle);
			draw_text_button(esContext, "vpitch_rc_min_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_max_angle);
			draw_text_button(esContext, "vpitch_rc_max_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_mode);
			draw_text_button(esContext, "vpitch_rc_mode", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_lpf);
			draw_text_button(esContext, "vpitch_rc_lpf", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_speed);
			draw_text_button(esContext, "vpitch_rc_speed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.pitch_rc_follow);
			draw_text_button(esContext, "vpitch_rc_follow", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " YAW", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_min_angle);
			draw_text_button(esContext, "vyaw_rc_min_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_max_angle);
			draw_text_button(esContext, "vyaw_rc_max_angle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_mode);
			draw_text_button(esContext, "vyaw_rc_mode", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_lpf);
			draw_text_button(esContext, "vyaw_rc_lpf", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_speed);
			draw_text_button(esContext, "vyaw_rc_speed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.yaw_rc_follow);
			draw_text_button(esContext, "vyaw_rc_follow", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 6 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "AXIS", FONT_GREEN, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "TRIM", FONT_GREEN, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "MAP", FONT_GREEN, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "FOFF", FONT_GREEN, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "OUT", FONT_GREEN, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, "FCGAIN", FONT_GREEN, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " ROLL", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.rc_trim_roll);
			draw_text_button(esContext, "vrc_trim_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.rc_map_roll);
			draw_text_button(esContext, "vrc_map_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.follow_offset_roll);
			draw_text_button(esContext, "vfollow_offset_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.output_roll);
			draw_text_button(esContext, "voutput_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.ext_fc_gain_roll);
			draw_text_button(esContext, "vext_fc_gain_roll", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " PITCH", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.rc_trim_pitch);
			draw_text_button(esContext, "vrc_trim_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.rc_map_pitch);
			draw_text_button(esContext, "vrc_map_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.follow_offset_pitch);
			draw_text_button(esContext, "vfollow_offset_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.output_pitch);
			draw_text_button(esContext, "voutput_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.ext_fc_gain_pitch);
			draw_text_button(esContext, "vext_fc_gain_pitch", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 5 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			draw_text_button(esContext, "_", VIEW_MODE_FCMENU, " YAW", FONT_WHITE, -1.3 + 0 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.rc_trim_yaw);
			draw_text_button(esContext, "vrc_trim_yaw", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 1 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.rc_map_yaw);
			draw_text_button(esContext, "vrc_map_yaw", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 2 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.follow_offset_yaw);
			draw_text_button(esContext, "vfollow_offset_yaw", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 3 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			sprintf(tmp_str, "%i", simplebgc_setup.output_yaw);
			draw_text_button(esContext, "voutput_yaw", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + 4 * 0.4, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
		} else if (mode == 1) {
			sprintf(tmp_str, "%i", simplebgc_setup.rc_deadband);
			draw_text_button(esContext, "nrc_deadband", VIEW_MODE_FCMENU, "rc_deadband", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vrc_deadband", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.rc_expo_rate);
			draw_text_button(esContext, "nrc_expo_rate", VIEW_MODE_FCMENU, "rc_expo_rate", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vrc_expo_rate", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.rc_source);
			draw_text_button(esContext, "nrc_source", VIEW_MODE_FCMENU, "rc_source", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vrc_source", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.rc_map_cmd);
			draw_text_button(esContext, "nrc_map_cmd", VIEW_MODE_FCMENU, "rc_map_cmd", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vrc_map_cmd", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.rc_cmd_low);
			draw_text_button(esContext, "nrc_cmd_low", VIEW_MODE_FCMENU, "rc_cmd_low", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vrc_cmd_low", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.rc_cmd_mid);
			draw_text_button(esContext, "nrc_cmd_mid", VIEW_MODE_FCMENU, "rc_cmd_mid", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vrc_cmd_mid", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.rc_cmd_high);
			draw_text_button(esContext, "nrc_cmd_high", VIEW_MODE_FCMENU, "rc_cmd_high", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vrc_cmd_high", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_1);
			draw_text_button(esContext, "nmenu_cmd_1", VIEW_MODE_FCMENU, "menu_cmd_1", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vmenu_cmd_1", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_2);
			draw_text_button(esContext, "nmenu_cmd_2", VIEW_MODE_FCMENU, "menu_cmd_2", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vmenu_cmd_2", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_3);
			draw_text_button(esContext, "nmenu_cmd_3", VIEW_MODE_FCMENU, "menu_cmd_3", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vmenu_cmd_3", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_4);
			draw_text_button(esContext, "nmenu_cmd_4", VIEW_MODE_FCMENU, "menu_cmd_4", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vmenu_cmd_4", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_5);
			draw_text_button(esContext, "nmenu_cmd_5", VIEW_MODE_FCMENU, "menu_cmd_5", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vmenu_cmd_5", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.menu_cmd_long);
			draw_text_button(esContext, "nmenu_cmd_long", VIEW_MODE_FCMENU, "menu_cmd_long", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vmenu_cmd_long", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
		} else if (mode == 2) {
			sprintf(tmp_str, "%i", simplebgc_setup.gyro_trust);
			draw_text_button(esContext, "ngyro_trust", VIEW_MODE_FCMENU, "gyro_trust", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vgyro_trust", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.gyro_lpf);
			draw_text_button(esContext, "ngyro_lpf", VIEW_MODE_FCMENU, "gyro_lpf", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vgyro_lpf", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.skip_gyro_calib);
			draw_text_button(esContext, "nskip_gyro_calib", VIEW_MODE_FCMENU, "skip_gyro_calib", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vskip_gyro_calib", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.use_model);
			draw_text_button(esContext, "nuse_model", VIEW_MODE_FCMENU, "use_model", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vuse_model", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.pwm_freq);
			draw_text_button(esContext, "npwm_freq", VIEW_MODE_FCMENU, "pwm_freq", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vpwm_freq", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.serial_speed);
			draw_text_button(esContext, "nserial_speed", VIEW_MODE_FCMENU, "serial_speed", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vserial_speed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.follow_mode);
			draw_text_button(esContext, "nfollow_mode", VIEW_MODE_FCMENU, "follow_mode", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vfollow_mode", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.follow_deadband);
			draw_text_button(esContext, "nfollow_deadband", VIEW_MODE_FCMENU, "follow_deadband", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vfollow_deadband", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.follow_expo_rate);
			draw_text_button(esContext, "nfollow_expo_rate", VIEW_MODE_FCMENU, "follow_expo_rate", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vfollow_expo_rate", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.axis_top);
			draw_text_button(esContext, "naxis_top", VIEW_MODE_FCMENU, "axis_top", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vaxis_top", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.axis_right);
			draw_text_button(esContext, "naxis_right", VIEW_MODE_FCMENU, "axis_right", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vaxis_right", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
			sprintf(tmp_str, "%i", simplebgc_setup.i2c_internal_pullups);
			draw_text_button(esContext, "ni2c_internal_pullups", VIEW_MODE_FCMENU, "i2c_internal_pullups", FONT_WHITE, -1.3 + ny * 0.7, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			draw_text_button(esContext, "vi2c_internal_pullups", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.3 + ny * 0.7 + 0.8, -0.8 + nx * 0.1, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, simplebgc_select, 0.0);
			nx++;
		}
		sprintf(tmp_str, "MODE(%i)", mode);
		draw_text_button(esContext, "mode", VIEW_MODE_FCMENU, "MODE", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, simplebgc_mode, 0.0);
		draw_text_button(esContext, "save", VIEW_MODE_FCMENU, "SAVE", FONT_WHITE, 0.4, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, simplebgc_save, 0.0);
		draw_text_button(esContext, "reload", VIEW_MODE_FCMENU, "RELOAD", FONT_WHITE, 0.8, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, simplebgc_reload, 0.0);
	}
}

