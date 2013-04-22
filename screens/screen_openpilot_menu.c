
#include <stdint.h>
#include <model.h>
#include <userdata.h>
#include <main.h>
#include <screen_openpilot_menu.h>
#include <openpilot.h>

#define MAX_PER_PAGE 12

static int8_t page = 0;
static uint8_t mode = 0;

uint8_t openpilot_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t openpilot_defaults (char *name, float x, float y, int8_t button, float data) {
	openpilot_defaults_StabilizationSettings(&OpenpilotStabilizationSettings);
	openpilot_defaults_HwSettings(&OpenpilotHwSettings);
	openpilot_defaults_SystemSettings(&OpenpilotSystemSettings);
	return 0;
}

uint8_t openpilot_flash (char *name, float x, float y, int8_t button, float data) {
	openpilot_save_to_flash();
	return 0;
}

uint8_t openpilot_mode (char *name, float x, float y, int8_t button, float data) {
	if (mode < 2) {
		mode++;
	} else {
		mode = 0;
	}
	page = 0;
	return 0;
}

uint8_t openpilot_setup_get (char *name, float x, float y, int8_t button, float data) {
	openpilot_get = 1;
	return 0;
}

uint8_t openpilot_setup_set (char *name, float x, float y, int8_t button, float data) {
	openpilot_set = 1;
	return 0;
}

uint8_t openpilot_down (char *name, float x, float y, int8_t button, float data) {
	if (page < 0) {
		page += (int8_t)data;
	}
	return 0;
}

uint8_t openpilot_up (char *name, float x, float y, int8_t button, float data) {
	if (page > -50) {
		page -= (int8_t)data;
	}
	return 0;
}


uint8_t openpilot_change_OpenpilotStabilizationSettings_ManualRate_Roll (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.ManualRate[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_ManualRate_Pitch (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.ManualRate[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_ManualRate_Yaw (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.ManualRate[2] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_MaximumRate_Roll (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.MaximumRate[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_MaximumRate_Pitch (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.MaximumRate[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_MaximumRate_Yaw (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.MaximumRate[2] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_RollRatePID_Kp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.RollRatePID[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_RollRatePID_Ki (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.RollRatePID[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_RollRatePID_Kd (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.RollRatePID[2] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_RollRatePID_ILimit (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.RollRatePID[3] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_Kp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.PitchRatePID[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_Ki (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.PitchRatePID[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_Kd (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.PitchRatePID[2] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_ILimit (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.PitchRatePID[3] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_YawRatePID_Kp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.YawRatePID[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_YawRatePID_Ki (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.YawRatePID[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_YawRatePID_Kd (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.YawRatePID[2] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_YawRatePID_ILimit (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.YawRatePID[3] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_RollPI_Kp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.RollPI[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_RollPI_Ki (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.RollPI[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_RollPI_ILimit (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.RollPI[2] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_PitchPI_Kp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.PitchPI[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_PitchPI_Ki (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.PitchPI[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_PitchPI_ILimit (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.PitchPI[2] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_YawPI_Kp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.YawPI[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_YawPI_Ki (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.YawPI[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_YawPI_ILimit (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.YawPI[2] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarSensitivity_Roll (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarSensitivity[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarSensitivity_Pitch (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarSensitivity[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarSensitivity_Yaw (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarSensitivity[2] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarRollPI_Kp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarRollPI[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarRollPI_Ki (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarRollPI[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarPitchPI_Kp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarPitchPI[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarPitchPI_Ki (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarPitchPI[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarYawPI_Kp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarYawPI[0] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarYawPI_Ki (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarYawPI[1] += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarTau (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarTau += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_GyroTau (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.GyroTau += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_DerivativeGamma (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.DerivativeGamma += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_WeakLevelingKp (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.WeakLevelingKp += (float)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_RollMax (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.RollMax += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_PitchMax (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.PitchMax += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_YawMax (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.YawMax += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarGyroSuppress (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarGyroSuppress += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarMaxAngle (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.VbarMaxAngle += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_DerivativeCutoff (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.DerivativeCutoff += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_MaxAxisLock (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.MaxAxisLock += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_MaxAxisLockRate (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.MaxAxisLockRate += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_MaxWeakLevelingRate (char *name, float x, float y, int8_t button, float data) {
	OpenpilotStabilizationSettings.MaxWeakLevelingRate += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_VbarPiroComp (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotStabilizationSettings.VbarPiroComp > 0) {
		OpenpilotStabilizationSettings.VbarPiroComp += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotStabilizationSettings.VbarPiroComp < 2 - 1) {
		OpenpilotStabilizationSettings.VbarPiroComp += (int8_t)data;
	} else {
		OpenpilotStabilizationSettings.VbarPiroComp = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotStabilizationSettings_LowThrottleZeroIntegral (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotStabilizationSettings.LowThrottleZeroIntegral > 0) {
		OpenpilotStabilizationSettings.LowThrottleZeroIntegral += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotStabilizationSettings.LowThrottleZeroIntegral < 2 - 1) {
		OpenpilotStabilizationSettings.LowThrottleZeroIntegral += (int8_t)data;
	} else {
		OpenpilotStabilizationSettings.LowThrottleZeroIntegral = 0;
	}
	return 0;
}


void openpilot_StabilizationSettings (ESContext *esContext) {
	uint8_t i = 0;
	int16_t n = 0;
	int16_t n2 = 0;
	char tmp_str[100];

	draw_title(esContext, "StabilizationSettings");

	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_ManualRate", VIEW_MODE_FCMENU, "ManualRate", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_ManualRate[Roll]", VIEW_MODE_FCMENU, "Roll", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.ManualRate[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_ManualRate[Roll]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_ManualRate[Roll]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_ManualRate_Roll, -0.01);
		draw_button(esContext, "inc_ManualRate[Roll]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_ManualRate_Roll, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_ManualRate[Pitch]", VIEW_MODE_FCMENU, "Pitch", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.ManualRate[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_ManualRate[Pitch]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_ManualRate[Pitch]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_ManualRate_Pitch, -0.01);
		draw_button(esContext, "inc_ManualRate[Pitch]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_ManualRate_Pitch, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_ManualRate[Yaw]", VIEW_MODE_FCMENU, "Yaw", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.ManualRate[2]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_ManualRate[Yaw]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_ManualRate[Yaw]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_ManualRate_Yaw, -0.01);
		draw_button(esContext, "inc_ManualRate[Yaw]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_ManualRate_Yaw, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_MaximumRate", VIEW_MODE_FCMENU, "MaximumRate", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_MaximumRate[Roll]", VIEW_MODE_FCMENU, "Roll", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.MaximumRate[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_MaximumRate[Roll]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_MaximumRate[Roll]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaximumRate_Roll, -0.01);
		draw_button(esContext, "inc_MaximumRate[Roll]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaximumRate_Roll, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_MaximumRate[Pitch]", VIEW_MODE_FCMENU, "Pitch", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.MaximumRate[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_MaximumRate[Pitch]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_MaximumRate[Pitch]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaximumRate_Pitch, -0.01);
		draw_button(esContext, "inc_MaximumRate[Pitch]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaximumRate_Pitch, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_MaximumRate[Yaw]", VIEW_MODE_FCMENU, "Yaw", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.MaximumRate[2]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_MaximumRate[Yaw]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_MaximumRate[Yaw]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaximumRate_Yaw, -0.01);
		draw_button(esContext, "inc_MaximumRate[Yaw]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaximumRate_Yaw, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollRatePID", VIEW_MODE_FCMENU, "RollRatePID", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollRatePID[Kp]", VIEW_MODE_FCMENU, "Kp", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.RollRatePID[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_RollRatePID[Kp]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RollRatePID[Kp]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollRatePID_Kp, -0.01);
		draw_button(esContext, "inc_RollRatePID[Kp]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollRatePID_Kp, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollRatePID[Ki]", VIEW_MODE_FCMENU, "Ki", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.RollRatePID[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_RollRatePID[Ki]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RollRatePID[Ki]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollRatePID_Ki, -0.01);
		draw_button(esContext, "inc_RollRatePID[Ki]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollRatePID_Ki, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollRatePID[Kd]", VIEW_MODE_FCMENU, "Kd", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.RollRatePID[2]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_RollRatePID[Kd]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RollRatePID[Kd]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollRatePID_Kd, -0.01);
		draw_button(esContext, "inc_RollRatePID[Kd]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollRatePID_Kd, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollRatePID[ILimit]", VIEW_MODE_FCMENU, "ILimit", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.RollRatePID[3]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_RollRatePID[ILimit]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RollRatePID[ILimit]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollRatePID_ILimit, -0.01);
		draw_button(esContext, "inc_RollRatePID[ILimit]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollRatePID_ILimit, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchRatePID", VIEW_MODE_FCMENU, "PitchRatePID", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchRatePID[Kp]", VIEW_MODE_FCMENU, "Kp", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.PitchRatePID[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_PitchRatePID[Kp]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_PitchRatePID[Kp]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_Kp, -0.01);
		draw_button(esContext, "inc_PitchRatePID[Kp]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_Kp, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchRatePID[Ki]", VIEW_MODE_FCMENU, "Ki", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.PitchRatePID[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_PitchRatePID[Ki]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_PitchRatePID[Ki]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_Ki, -0.01);
		draw_button(esContext, "inc_PitchRatePID[Ki]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_Ki, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchRatePID[Kd]", VIEW_MODE_FCMENU, "Kd", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.PitchRatePID[2]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_PitchRatePID[Kd]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_PitchRatePID[Kd]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_Kd, -0.01);
		draw_button(esContext, "inc_PitchRatePID[Kd]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_Kd, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchRatePID[ILimit]", VIEW_MODE_FCMENU, "ILimit", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.PitchRatePID[3]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_PitchRatePID[ILimit]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_PitchRatePID[ILimit]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_ILimit, -0.01);
		draw_button(esContext, "inc_PitchRatePID[ILimit]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchRatePID_ILimit, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawRatePID", VIEW_MODE_FCMENU, "YawRatePID", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawRatePID[Kp]", VIEW_MODE_FCMENU, "Kp", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.YawRatePID[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_YawRatePID[Kp]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_YawRatePID[Kp]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawRatePID_Kp, -0.01);
		draw_button(esContext, "inc_YawRatePID[Kp]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawRatePID_Kp, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawRatePID[Ki]", VIEW_MODE_FCMENU, "Ki", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.YawRatePID[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_YawRatePID[Ki]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_YawRatePID[Ki]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawRatePID_Ki, -0.01);
		draw_button(esContext, "inc_YawRatePID[Ki]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawRatePID_Ki, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawRatePID[Kd]", VIEW_MODE_FCMENU, "Kd", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.YawRatePID[2]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_YawRatePID[Kd]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_YawRatePID[Kd]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawRatePID_Kd, -0.01);
		draw_button(esContext, "inc_YawRatePID[Kd]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawRatePID_Kd, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawRatePID[ILimit]", VIEW_MODE_FCMENU, "ILimit", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.YawRatePID[3]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_YawRatePID[ILimit]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_YawRatePID[ILimit]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawRatePID_ILimit, -0.01);
		draw_button(esContext, "inc_YawRatePID[ILimit]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawRatePID_ILimit, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollPI", VIEW_MODE_FCMENU, "RollPI", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollPI[Kp]", VIEW_MODE_FCMENU, "Kp", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.RollPI[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_RollPI[Kp]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RollPI[Kp]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollPI_Kp, -0.01);
		draw_button(esContext, "inc_RollPI[Kp]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollPI_Kp, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollPI[Ki]", VIEW_MODE_FCMENU, "Ki", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.RollPI[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_RollPI[Ki]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RollPI[Ki]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollPI_Ki, -0.01);
		draw_button(esContext, "inc_RollPI[Ki]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollPI_Ki, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollPI[ILimit]", VIEW_MODE_FCMENU, "ILimit", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.RollPI[2]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_RollPI[ILimit]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RollPI[ILimit]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollPI_ILimit, -0.01);
		draw_button(esContext, "inc_RollPI[ILimit]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollPI_ILimit, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchPI", VIEW_MODE_FCMENU, "PitchPI", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchPI[Kp]", VIEW_MODE_FCMENU, "Kp", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.PitchPI[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_PitchPI[Kp]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_PitchPI[Kp]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchPI_Kp, -0.01);
		draw_button(esContext, "inc_PitchPI[Kp]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchPI_Kp, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchPI[Ki]", VIEW_MODE_FCMENU, "Ki", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.PitchPI[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_PitchPI[Ki]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_PitchPI[Ki]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchPI_Ki, -0.01);
		draw_button(esContext, "inc_PitchPI[Ki]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchPI_Ki, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchPI[ILimit]", VIEW_MODE_FCMENU, "ILimit", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.PitchPI[2]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_PitchPI[ILimit]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_PitchPI[ILimit]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchPI_ILimit, -0.01);
		draw_button(esContext, "inc_PitchPI[ILimit]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchPI_ILimit, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawPI", VIEW_MODE_FCMENU, "YawPI", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawPI[Kp]", VIEW_MODE_FCMENU, "Kp", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.YawPI[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_YawPI[Kp]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_YawPI[Kp]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawPI_Kp, -0.01);
		draw_button(esContext, "inc_YawPI[Kp]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawPI_Kp, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawPI[Ki]", VIEW_MODE_FCMENU, "Ki", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.YawPI[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_YawPI[Ki]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_YawPI[Ki]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawPI_Ki, -0.01);
		draw_button(esContext, "inc_YawPI[Ki]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawPI_Ki, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawPI[ILimit]", VIEW_MODE_FCMENU, "ILimit", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.YawPI[2]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_YawPI[ILimit]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_YawPI[ILimit]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawPI_ILimit, -0.01);
		draw_button(esContext, "inc_YawPI[ILimit]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawPI_ILimit, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarSensitivity", VIEW_MODE_FCMENU, "VbarSensitivity", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarSensitivity[Roll]", VIEW_MODE_FCMENU, "Roll", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarSensitivity[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_VbarSensitivity[Roll]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarSensitivity[Roll]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarSensitivity_Roll, -0.01);
		draw_button(esContext, "inc_VbarSensitivity[Roll]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarSensitivity_Roll, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarSensitivity[Pitch]", VIEW_MODE_FCMENU, "Pitch", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarSensitivity[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_VbarSensitivity[Pitch]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarSensitivity[Pitch]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarSensitivity_Pitch, -0.01);
		draw_button(esContext, "inc_VbarSensitivity[Pitch]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarSensitivity_Pitch, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarSensitivity[Yaw]", VIEW_MODE_FCMENU, "Yaw", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarSensitivity[2]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_VbarSensitivity[Yaw]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarSensitivity[Yaw]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarSensitivity_Yaw, -0.01);
		draw_button(esContext, "inc_VbarSensitivity[Yaw]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarSensitivity_Yaw, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarRollPI", VIEW_MODE_FCMENU, "VbarRollPI", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarRollPI[Kp]", VIEW_MODE_FCMENU, "Kp", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarRollPI[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_VbarRollPI[Kp]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarRollPI[Kp]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarRollPI_Kp, -0.01);
		draw_button(esContext, "inc_VbarRollPI[Kp]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarRollPI_Kp, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarRollPI[Ki]", VIEW_MODE_FCMENU, "Ki", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarRollPI[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_VbarRollPI[Ki]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarRollPI[Ki]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarRollPI_Ki, -0.01);
		draw_button(esContext, "inc_VbarRollPI[Ki]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarRollPI_Ki, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarPitchPI", VIEW_MODE_FCMENU, "VbarPitchPI", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarPitchPI[Kp]", VIEW_MODE_FCMENU, "Kp", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarPitchPI[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_VbarPitchPI[Kp]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarPitchPI[Kp]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarPitchPI_Kp, -0.01);
		draw_button(esContext, "inc_VbarPitchPI[Kp]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarPitchPI_Kp, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarPitchPI[Ki]", VIEW_MODE_FCMENU, "Ki", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarPitchPI[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_VbarPitchPI[Ki]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarPitchPI[Ki]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarPitchPI_Ki, -0.01);
		draw_button(esContext, "inc_VbarPitchPI[Ki]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarPitchPI_Ki, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarYawPI", VIEW_MODE_FCMENU, "VbarYawPI", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarYawPI[Kp]", VIEW_MODE_FCMENU, "Kp", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarYawPI[0]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_VbarYawPI[Kp]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarYawPI[Kp]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarYawPI_Kp, -0.01);
		draw_button(esContext, "inc_VbarYawPI[Kp]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarYawPI_Kp, +0.01);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarYawPI[Ki]", VIEW_MODE_FCMENU, "Ki", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarYawPI[1]);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "default_VbarYawPI[Ki]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarYawPI[Ki]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarYawPI_Ki, -0.01);
		draw_button(esContext, "inc_VbarYawPI[Ki]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarYawPI_Ki, +0.01);
	}
	n2++;
	n++;
	n2 = 0;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarTau", VIEW_MODE_FCMENU, "VbarTau", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.VbarTau);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "val_VbarTau", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarTau", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarTau, -0.01);
		draw_button(esContext, "inc_VbarTau", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarTau, +0.01);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_GyroTau", VIEW_MODE_FCMENU, "GyroTau", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.GyroTau);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "val_GyroTau", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_GyroTau", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_GyroTau, -0.01);
		draw_button(esContext, "inc_GyroTau", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_GyroTau, +0.01);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_DerivativeGamma", VIEW_MODE_FCMENU, "DerivativeGamma", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.DerivativeGamma);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "val_DerivativeGamma", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_DerivativeGamma", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_DerivativeGamma, -0.01);
		draw_button(esContext, "inc_DerivativeGamma", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_DerivativeGamma, +0.01);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_WeakLevelingKp", VIEW_MODE_FCMENU, "WeakLevelingKp", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%0.6f", OpenpilotStabilizationSettings.WeakLevelingKp);
		for (i = 0; i < 5; i++) {
			if (tmp_str[strlen(tmp_str) - 1] == '0') {
				tmp_str[strlen(tmp_str) - 1] = 0;
			}
		}
		draw_button(esContext, "val_WeakLevelingKp", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_WeakLevelingKp", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_WeakLevelingKp, -0.01);
		draw_button(esContext, "inc_WeakLevelingKp", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_WeakLevelingKp, +0.01);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RollMax", VIEW_MODE_FCMENU, "RollMax", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.RollMax);
		draw_button(esContext, "val_RollMax", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RollMax", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollMax, -1);
		draw_button(esContext, "inc_RollMax", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_RollMax, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_PitchMax", VIEW_MODE_FCMENU, "PitchMax", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.PitchMax);
		draw_button(esContext, "val_PitchMax", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_PitchMax", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchMax, -1);
		draw_button(esContext, "inc_PitchMax", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_PitchMax, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_YawMax", VIEW_MODE_FCMENU, "YawMax", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.YawMax);
		draw_button(esContext, "val_YawMax", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_YawMax", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawMax, -1);
		draw_button(esContext, "inc_YawMax", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_YawMax, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarGyroSuppress", VIEW_MODE_FCMENU, "VbarGyroSuppress", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.VbarGyroSuppress);
		draw_button(esContext, "val_VbarGyroSuppress", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarGyroSuppress", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarGyroSuppress, -1);
		draw_button(esContext, "inc_VbarGyroSuppress", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarGyroSuppress, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarMaxAngle", VIEW_MODE_FCMENU, "VbarMaxAngle", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.VbarMaxAngle);
		draw_button(esContext, "val_VbarMaxAngle", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarMaxAngle", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarMaxAngle, -1);
		draw_button(esContext, "inc_VbarMaxAngle", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarMaxAngle, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_DerivativeCutoff", VIEW_MODE_FCMENU, "DerivativeCutoff", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.DerivativeCutoff);
		draw_button(esContext, "val_DerivativeCutoff", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_DerivativeCutoff", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_DerivativeCutoff, -1);
		draw_button(esContext, "inc_DerivativeCutoff", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_DerivativeCutoff, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_MaxAxisLock", VIEW_MODE_FCMENU, "MaxAxisLock", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.MaxAxisLock);
		draw_button(esContext, "val_MaxAxisLock", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_MaxAxisLock", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaxAxisLock, -1);
		draw_button(esContext, "inc_MaxAxisLock", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaxAxisLock, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_MaxAxisLockRate", VIEW_MODE_FCMENU, "MaxAxisLockRate", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.MaxAxisLockRate);
		draw_button(esContext, "val_MaxAxisLockRate", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_MaxAxisLockRate", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaxAxisLockRate, -1);
		draw_button(esContext, "inc_MaxAxisLockRate", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaxAxisLockRate, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_MaxWeakLevelingRate", VIEW_MODE_FCMENU, "MaxWeakLevelingRate", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.MaxWeakLevelingRate);
		draw_button(esContext, "val_MaxWeakLevelingRate", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_MaxWeakLevelingRate", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaxWeakLevelingRate, -1);
		draw_button(esContext, "inc_MaxWeakLevelingRate", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_MaxWeakLevelingRate, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_VbarPiroComp", VIEW_MODE_FCMENU, "VbarPiroComp", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.VbarPiroComp);
		if (OpenpilotStabilizationSettings.VbarPiroComp == 0) {
			sprintf(tmp_str, "FALSE");
		}
		if (OpenpilotStabilizationSettings.VbarPiroComp == 1) {
			sprintf(tmp_str, "TRUE");
		}
		draw_button(esContext, "val_VbarPiroComp", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_VbarPiroComp", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarPiroComp, -1);
		draw_button(esContext, "inc_VbarPiroComp", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_VbarPiroComp, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_LowThrottleZeroIntegral", VIEW_MODE_FCMENU, "LowThrottleZeroIntegral", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotStabilizationSettings.LowThrottleZeroIntegral);
		if (OpenpilotStabilizationSettings.LowThrottleZeroIntegral == 0) {
			sprintf(tmp_str, "FALSE");
		}
		if (OpenpilotStabilizationSettings.LowThrottleZeroIntegral == 1) {
			sprintf(tmp_str, "TRUE");
		}
		draw_button(esContext, "val_LowThrottleZeroIntegral", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_LowThrottleZeroIntegral", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_LowThrottleZeroIntegral, -1);
		draw_button(esContext, "inc_LowThrottleZeroIntegral", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotStabilizationSettings_LowThrottleZeroIntegral, +1);
	}
	n++;

	if (n > 13) {
		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, 0.77, 0.002, 255, 255, 255, 128);
		if (page < 0) {
			set_button("down", VIEW_MODE_FCMENU, 1.3, -0.77, 1.35, -0.67, openpilot_down, 1.0, 0);
			set_button("down2", VIEW_MODE_FCMENU, 1.3, -0.77, 1.35, 0.0, openpilot_down, 3.0, 0);
		}
		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);
		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);
		draw_rect_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);
		if (n + page - 13 > 0) {
			set_button("up", VIEW_MODE_FCMENU, 1.3, 0.67, 1.35, 0.77, openpilot_up, 1.0, 0);
			set_button("up2", VIEW_MODE_FCMENU, 1.3, 0.0, 1.35, 0.77, openpilot_up, 3.0, 0);
		}
		if (page > 0) {
			page = 0;
		}
		if (page < (n - 13) * -1) {
			page = (n - 13) * -1;
		}
		draw_box_f3(esContext, 1.3, 0.67, 0.002, 1.35, 0.77, 0.002, 255, 255, 255, 128);
		draw_box_f3(esContext, 1.3, 0.77, 0.002, 1.35, 0.67, 0.002, 255, 255, 255, 128);
		draw_rect_f3(esContext, 1.3, 0.77, 0.002, 1.35, 0.67, 0.002, 255, 255, 255, 128);
		draw_box_f3(esContext, 1.3 - 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13) - 0.02, 0.002, 1.35 + 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13), 0.002, 255, 255, 255, 200);
		draw_rect_f3(esContext, 1.3 - 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13) - 0.02, 0.002, 1.35 + 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13), 0.002, 100, 100, 100, 128);
	}
	if (openpilot_get == 1) {
		draw_button(esContext, "get", VIEW_MODE_FCMENU, "[GET]", FONT_GREEN, -0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_get, 0.0);
	} else {
		draw_button(esContext, "get", VIEW_MODE_FCMENU, "[GET]", FONT_WHITE, -0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_get, 0.0);
	}
	if (openpilot_set == 1) {
		draw_button(esContext, "set", VIEW_MODE_FCMENU, "[SET]", FONT_GREEN, 0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_set, 0.0);
	} else {
		draw_button(esContext, "set", VIEW_MODE_FCMENU, "[SET]", FONT_WHITE, 0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_set, 0.0);
	}
	draw_button(esContext, "defaults", VIEW_MODE_FCMENU, "[DEFAULTS]", FONT_WHITE, -0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_defaults, 0.0);
	draw_button(esContext, "flash", VIEW_MODE_FCMENU, "[FLASH]", FONT_WHITE, 0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_flash, 0.0);
}


uint8_t openpilot_change_OpenpilotHwSettings_DSMxBind (char *name, float x, float y, int8_t button, float data) {
	OpenpilotHwSettings.DSMxBind += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_CC_RcvrPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.CC_RcvrPort > 0) {
		OpenpilotHwSettings.CC_RcvrPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.CC_RcvrPort < 6 - 1) {
		OpenpilotHwSettings.CC_RcvrPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.CC_RcvrPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_CC_MainPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.CC_MainPort > 0) {
		OpenpilotHwSettings.CC_MainPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.CC_MainPort < 11 - 1) {
		OpenpilotHwSettings.CC_MainPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.CC_MainPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_CC_FlexiPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.CC_FlexiPort > 0) {
		OpenpilotHwSettings.CC_FlexiPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.CC_FlexiPort < 11 - 1) {
		OpenpilotHwSettings.CC_FlexiPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.CC_FlexiPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_RV_RcvrPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.RV_RcvrPort > 0) {
		OpenpilotHwSettings.RV_RcvrPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.RV_RcvrPort < 5 - 1) {
		OpenpilotHwSettings.RV_RcvrPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.RV_RcvrPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_RV_AuxPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.RV_AuxPort > 0) {
		OpenpilotHwSettings.RV_AuxPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.RV_AuxPort < 9 - 1) {
		OpenpilotHwSettings.RV_AuxPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.RV_AuxPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_RV_AuxSBusPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.RV_AuxSBusPort > 0) {
		OpenpilotHwSettings.RV_AuxSBusPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.RV_AuxSBusPort < 9 - 1) {
		OpenpilotHwSettings.RV_AuxSBusPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.RV_AuxSBusPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_RV_FlexiPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.RV_FlexiPort > 0) {
		OpenpilotHwSettings.RV_FlexiPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.RV_FlexiPort < 9 - 1) {
		OpenpilotHwSettings.RV_FlexiPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.RV_FlexiPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_RV_TelemetryPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.RV_TelemetryPort > 0) {
		OpenpilotHwSettings.RV_TelemetryPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.RV_TelemetryPort < 4 - 1) {
		OpenpilotHwSettings.RV_TelemetryPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.RV_TelemetryPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_RV_GPSPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.RV_GPSPort > 0) {
		OpenpilotHwSettings.RV_GPSPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.RV_GPSPort < 5 - 1) {
		OpenpilotHwSettings.RV_GPSPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.RV_GPSPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_TelemetrySpeed (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.TelemetrySpeed > 0) {
		OpenpilotHwSettings.TelemetrySpeed += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.TelemetrySpeed < 7 - 1) {
		OpenpilotHwSettings.TelemetrySpeed += (int8_t)data;
	} else {
		OpenpilotHwSettings.TelemetrySpeed = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_GPSSpeed (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.GPSSpeed > 0) {
		OpenpilotHwSettings.GPSSpeed += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.GPSSpeed < 7 - 1) {
		OpenpilotHwSettings.GPSSpeed += (int8_t)data;
	} else {
		OpenpilotHwSettings.GPSSpeed = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_ComUsbBridgeSpeed (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.ComUsbBridgeSpeed > 0) {
		OpenpilotHwSettings.ComUsbBridgeSpeed += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.ComUsbBridgeSpeed < 7 - 1) {
		OpenpilotHwSettings.ComUsbBridgeSpeed += (int8_t)data;
	} else {
		OpenpilotHwSettings.ComUsbBridgeSpeed = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_USB_HIDPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.USB_HIDPort > 0) {
		OpenpilotHwSettings.USB_HIDPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.USB_HIDPort < 3 - 1) {
		OpenpilotHwSettings.USB_HIDPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.USB_HIDPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_USB_VCPPort (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.USB_VCPPort > 0) {
		OpenpilotHwSettings.USB_VCPPort += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.USB_VCPPort < 3 - 1) {
		OpenpilotHwSettings.USB_VCPPort += (int8_t)data;
	} else {
		OpenpilotHwSettings.USB_VCPPort = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_OptionalModules_CameraStab (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.OptionalModules[0] > 0) {
		OpenpilotHwSettings.OptionalModules[0] += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.OptionalModules[0] < 2 - 1) {
		OpenpilotHwSettings.OptionalModules[0] += (int8_t)data;
	} else {
		OpenpilotHwSettings.OptionalModules[0] = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_OptionalModules_GPS (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.OptionalModules[1] > 0) {
		OpenpilotHwSettings.OptionalModules[1] += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.OptionalModules[1] < 2 - 1) {
		OpenpilotHwSettings.OptionalModules[1] += (int8_t)data;
	} else {
		OpenpilotHwSettings.OptionalModules[1] = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_OptionalModules_ComUsbBridge (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.OptionalModules[2] > 0) {
		OpenpilotHwSettings.OptionalModules[2] += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.OptionalModules[2] < 2 - 1) {
		OpenpilotHwSettings.OptionalModules[2] += (int8_t)data;
	} else {
		OpenpilotHwSettings.OptionalModules[2] = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_OptionalModules_Fault (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.OptionalModules[3] > 0) {
		OpenpilotHwSettings.OptionalModules[3] += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.OptionalModules[3] < 2 - 1) {
		OpenpilotHwSettings.OptionalModules[3] += (int8_t)data;
	} else {
		OpenpilotHwSettings.OptionalModules[3] = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_OptionalModules_Altitude (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.OptionalModules[4] > 0) {
		OpenpilotHwSettings.OptionalModules[4] += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.OptionalModules[4] < 2 - 1) {
		OpenpilotHwSettings.OptionalModules[4] += (int8_t)data;
	} else {
		OpenpilotHwSettings.OptionalModules[4] = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_OptionalModules_TxPID (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.OptionalModules[5] > 0) {
		OpenpilotHwSettings.OptionalModules[5] += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.OptionalModules[5] < 2 - 1) {
		OpenpilotHwSettings.OptionalModules[5] += (int8_t)data;
	} else {
		OpenpilotHwSettings.OptionalModules[5] = 0;
	}
	return 0;
}

uint8_t openpilot_change_OpenpilotHwSettings_OptionalModules_Autotune (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotHwSettings.OptionalModules[6] > 0) {
		OpenpilotHwSettings.OptionalModules[6] += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotHwSettings.OptionalModules[6] < 2 - 1) {
		OpenpilotHwSettings.OptionalModules[6] += (int8_t)data;
	} else {
		OpenpilotHwSettings.OptionalModules[6] = 0;
	}
	return 0;
}


void openpilot_HwSettings (ESContext *esContext) {
	int16_t n = 0;
	int16_t n2 = 0;
	char tmp_str[100];

	draw_title(esContext, "Hardware-Settings");

	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_DSMxBind", VIEW_MODE_FCMENU, "DSMxBind", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.DSMxBind);
		draw_button(esContext, "val_DSMxBind", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_DSMxBind", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_DSMxBind, -1);
		draw_button(esContext, "inc_DSMxBind", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_DSMxBind, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_CC_RcvrPort", VIEW_MODE_FCMENU, "CC_RcvrPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.CC_RcvrPort);
		if (OpenpilotHwSettings.CC_RcvrPort == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.CC_RcvrPort == 1) {
			sprintf(tmp_str, "PWM");
		}
		if (OpenpilotHwSettings.CC_RcvrPort == 2) {
			sprintf(tmp_str, "PPM");
		}
		if (OpenpilotHwSettings.CC_RcvrPort == 3) {
			sprintf(tmp_str, "PPM+PWM");
		}
		if (OpenpilotHwSettings.CC_RcvrPort == 4) {
			sprintf(tmp_str, "PPM+Outputs");
		}
		if (OpenpilotHwSettings.CC_RcvrPort == 5) {
			sprintf(tmp_str, "Outputs");
		}
		draw_button(esContext, "val_CC_RcvrPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_CC_RcvrPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_CC_RcvrPort, -1);
		draw_button(esContext, "inc_CC_RcvrPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_CC_RcvrPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_CC_MainPort", VIEW_MODE_FCMENU, "CC_MainPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.CC_MainPort);
		if (OpenpilotHwSettings.CC_MainPort == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.CC_MainPort == 1) {
			sprintf(tmp_str, "Telemetry");
		}
		if (OpenpilotHwSettings.CC_MainPort == 2) {
			sprintf(tmp_str, "GPS");
		}
		if (OpenpilotHwSettings.CC_MainPort == 3) {
			sprintf(tmp_str, "S.Bus");
		}
		if (OpenpilotHwSettings.CC_MainPort == 4) {
			sprintf(tmp_str, "DSM2");
		}
		if (OpenpilotHwSettings.CC_MainPort == 5) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.CC_MainPort == 6) {
			sprintf(tmp_str, "(10bit)");
		}
		if (OpenpilotHwSettings.CC_MainPort == 7) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.CC_MainPort == 8) {
			sprintf(tmp_str, "(11bit)");
		}
		if (OpenpilotHwSettings.CC_MainPort == 9) {
			sprintf(tmp_str, "ComAux");
		}
		if (OpenpilotHwSettings.CC_MainPort == 10) {
			sprintf(tmp_str, "ComBridge");
		}
		draw_button(esContext, "val_CC_MainPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_CC_MainPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_CC_MainPort, -1);
		draw_button(esContext, "inc_CC_MainPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_CC_MainPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_CC_FlexiPort", VIEW_MODE_FCMENU, "CC_FlexiPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.CC_FlexiPort);
		if (OpenpilotHwSettings.CC_FlexiPort == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 1) {
			sprintf(tmp_str, "Telemetry");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 2) {
			sprintf(tmp_str, "GPS");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 3) {
			sprintf(tmp_str, "I2C");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 4) {
			sprintf(tmp_str, "DSM2");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 5) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 6) {
			sprintf(tmp_str, "(10bit)");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 7) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 8) {
			sprintf(tmp_str, "(11bit)");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 9) {
			sprintf(tmp_str, "ComAux");
		}
		if (OpenpilotHwSettings.CC_FlexiPort == 10) {
			sprintf(tmp_str, "ComBridge");
		}
		draw_button(esContext, "val_CC_FlexiPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_CC_FlexiPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_CC_FlexiPort, -1);
		draw_button(esContext, "inc_CC_FlexiPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_CC_FlexiPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RV_RcvrPort", VIEW_MODE_FCMENU, "RV_RcvrPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.RV_RcvrPort);
		if (OpenpilotHwSettings.RV_RcvrPort == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.RV_RcvrPort == 1) {
			sprintf(tmp_str, "PWM");
		}
		if (OpenpilotHwSettings.RV_RcvrPort == 2) {
			sprintf(tmp_str, "PPM");
		}
		if (OpenpilotHwSettings.RV_RcvrPort == 3) {
			sprintf(tmp_str, "PPM+Outputs");
		}
		if (OpenpilotHwSettings.RV_RcvrPort == 4) {
			sprintf(tmp_str, "Outputs");
		}
		draw_button(esContext, "val_RV_RcvrPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RV_RcvrPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_RcvrPort, -1);
		draw_button(esContext, "inc_RV_RcvrPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_RcvrPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RV_AuxPort", VIEW_MODE_FCMENU, "RV_AuxPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.RV_AuxPort);
		if (OpenpilotHwSettings.RV_AuxPort == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.RV_AuxPort == 1) {
			sprintf(tmp_str, "Telemetry");
		}
		if (OpenpilotHwSettings.RV_AuxPort == 2) {
			sprintf(tmp_str, "DSM2");
		}
		if (OpenpilotHwSettings.RV_AuxPort == 3) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.RV_AuxPort == 4) {
			sprintf(tmp_str, "(10bit)");
		}
		if (OpenpilotHwSettings.RV_AuxPort == 5) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.RV_AuxPort == 6) {
			sprintf(tmp_str, "(11bit)");
		}
		if (OpenpilotHwSettings.RV_AuxPort == 7) {
			sprintf(tmp_str, "ComAux");
		}
		if (OpenpilotHwSettings.RV_AuxPort == 8) {
			sprintf(tmp_str, "ComBridge");
		}
		draw_button(esContext, "val_RV_AuxPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RV_AuxPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_AuxPort, -1);
		draw_button(esContext, "inc_RV_AuxPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_AuxPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RV_AuxSBusPort", VIEW_MODE_FCMENU, "RV_AuxSBusPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.RV_AuxSBusPort);
		if (OpenpilotHwSettings.RV_AuxSBusPort == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.RV_AuxSBusPort == 1) {
			sprintf(tmp_str, "S.Bus");
		}
		if (OpenpilotHwSettings.RV_AuxSBusPort == 2) {
			sprintf(tmp_str, "DSM2");
		}
		if (OpenpilotHwSettings.RV_AuxSBusPort == 3) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.RV_AuxSBusPort == 4) {
			sprintf(tmp_str, "(10bit)");
		}
		if (OpenpilotHwSettings.RV_AuxSBusPort == 5) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.RV_AuxSBusPort == 6) {
			sprintf(tmp_str, "(11bit)");
		}
		if (OpenpilotHwSettings.RV_AuxSBusPort == 7) {
			sprintf(tmp_str, "ComAux");
		}
		if (OpenpilotHwSettings.RV_AuxSBusPort == 8) {
			sprintf(tmp_str, "ComBridge");
		}
		draw_button(esContext, "val_RV_AuxSBusPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RV_AuxSBusPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_AuxSBusPort, -1);
		draw_button(esContext, "inc_RV_AuxSBusPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_AuxSBusPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RV_FlexiPort", VIEW_MODE_FCMENU, "RV_FlexiPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.RV_FlexiPort);
		if (OpenpilotHwSettings.RV_FlexiPort == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.RV_FlexiPort == 1) {
			sprintf(tmp_str, "I2C");
		}
		if (OpenpilotHwSettings.RV_FlexiPort == 2) {
			sprintf(tmp_str, "DSM2");
		}
		if (OpenpilotHwSettings.RV_FlexiPort == 3) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.RV_FlexiPort == 4) {
			sprintf(tmp_str, "(10bit)");
		}
		if (OpenpilotHwSettings.RV_FlexiPort == 5) {
			sprintf(tmp_str, "DSMX");
		}
		if (OpenpilotHwSettings.RV_FlexiPort == 6) {
			sprintf(tmp_str, "(11bit)");
		}
		if (OpenpilotHwSettings.RV_FlexiPort == 7) {
			sprintf(tmp_str, "ComAux");
		}
		if (OpenpilotHwSettings.RV_FlexiPort == 8) {
			sprintf(tmp_str, "ComBridge");
		}
		draw_button(esContext, "val_RV_FlexiPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RV_FlexiPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_FlexiPort, -1);
		draw_button(esContext, "inc_RV_FlexiPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_FlexiPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RV_TelemetryPort", VIEW_MODE_FCMENU, "RV_TelemetryPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.RV_TelemetryPort);
		if (OpenpilotHwSettings.RV_TelemetryPort == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.RV_TelemetryPort == 1) {
			sprintf(tmp_str, "Telemetry");
		}
		if (OpenpilotHwSettings.RV_TelemetryPort == 2) {
			sprintf(tmp_str, "ComAux");
		}
		if (OpenpilotHwSettings.RV_TelemetryPort == 3) {
			sprintf(tmp_str, "ComBridge");
		}
		draw_button(esContext, "val_RV_TelemetryPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RV_TelemetryPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_TelemetryPort, -1);
		draw_button(esContext, "inc_RV_TelemetryPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_TelemetryPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_RV_GPSPort", VIEW_MODE_FCMENU, "RV_GPSPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.RV_GPSPort);
		if (OpenpilotHwSettings.RV_GPSPort == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.RV_GPSPort == 1) {
			sprintf(tmp_str, "Telemetry");
		}
		if (OpenpilotHwSettings.RV_GPSPort == 2) {
			sprintf(tmp_str, "GPS");
		}
		if (OpenpilotHwSettings.RV_GPSPort == 3) {
			sprintf(tmp_str, "ComAux");
		}
		if (OpenpilotHwSettings.RV_GPSPort == 4) {
			sprintf(tmp_str, "ComBridge");
		}
		draw_button(esContext, "val_RV_GPSPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_RV_GPSPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_GPSPort, -1);
		draw_button(esContext, "inc_RV_GPSPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_RV_GPSPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_TelemetrySpeed", VIEW_MODE_FCMENU, "TelemetrySpeed", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.TelemetrySpeed);
		if (OpenpilotHwSettings.TelemetrySpeed == 0) {
			sprintf(tmp_str, "2400");
		}
		if (OpenpilotHwSettings.TelemetrySpeed == 1) {
			sprintf(tmp_str, "4800");
		}
		if (OpenpilotHwSettings.TelemetrySpeed == 2) {
			sprintf(tmp_str, "9600");
		}
		if (OpenpilotHwSettings.TelemetrySpeed == 3) {
			sprintf(tmp_str, "19200");
		}
		if (OpenpilotHwSettings.TelemetrySpeed == 4) {
			sprintf(tmp_str, "38400");
		}
		if (OpenpilotHwSettings.TelemetrySpeed == 5) {
			sprintf(tmp_str, "57600");
		}
		if (OpenpilotHwSettings.TelemetrySpeed == 6) {
			sprintf(tmp_str, "115200");
		}
		draw_button(esContext, "val_TelemetrySpeed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_TelemetrySpeed", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_TelemetrySpeed, -1);
		draw_button(esContext, "inc_TelemetrySpeed", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_TelemetrySpeed, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_GPSSpeed", VIEW_MODE_FCMENU, "GPSSpeed", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.GPSSpeed);
		if (OpenpilotHwSettings.GPSSpeed == 0) {
			sprintf(tmp_str, "2400");
		}
		if (OpenpilotHwSettings.GPSSpeed == 1) {
			sprintf(tmp_str, "4800");
		}
		if (OpenpilotHwSettings.GPSSpeed == 2) {
			sprintf(tmp_str, "9600");
		}
		if (OpenpilotHwSettings.GPSSpeed == 3) {
			sprintf(tmp_str, "19200");
		}
		if (OpenpilotHwSettings.GPSSpeed == 4) {
			sprintf(tmp_str, "38400");
		}
		if (OpenpilotHwSettings.GPSSpeed == 5) {
			sprintf(tmp_str, "57600");
		}
		if (OpenpilotHwSettings.GPSSpeed == 6) {
			sprintf(tmp_str, "115200");
		}
		draw_button(esContext, "val_GPSSpeed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_GPSSpeed", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_GPSSpeed, -1);
		draw_button(esContext, "inc_GPSSpeed", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_GPSSpeed, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_ComUsbBridgeSpeed", VIEW_MODE_FCMENU, "ComUsbBridgeSpeed", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.ComUsbBridgeSpeed);
		if (OpenpilotHwSettings.ComUsbBridgeSpeed == 0) {
			sprintf(tmp_str, "2400");
		}
		if (OpenpilotHwSettings.ComUsbBridgeSpeed == 1) {
			sprintf(tmp_str, "4800");
		}
		if (OpenpilotHwSettings.ComUsbBridgeSpeed == 2) {
			sprintf(tmp_str, "9600");
		}
		if (OpenpilotHwSettings.ComUsbBridgeSpeed == 3) {
			sprintf(tmp_str, "19200");
		}
		if (OpenpilotHwSettings.ComUsbBridgeSpeed == 4) {
			sprintf(tmp_str, "38400");
		}
		if (OpenpilotHwSettings.ComUsbBridgeSpeed == 5) {
			sprintf(tmp_str, "57600");
		}
		if (OpenpilotHwSettings.ComUsbBridgeSpeed == 6) {
			sprintf(tmp_str, "115200");
		}
		draw_button(esContext, "val_ComUsbBridgeSpeed", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_ComUsbBridgeSpeed", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_ComUsbBridgeSpeed, -1);
		draw_button(esContext, "inc_ComUsbBridgeSpeed", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_ComUsbBridgeSpeed, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_USB_HIDPort", VIEW_MODE_FCMENU, "USB_HIDPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.USB_HIDPort);
		if (OpenpilotHwSettings.USB_HIDPort == 0) {
			sprintf(tmp_str, "USBTelemetry");
		}
		if (OpenpilotHwSettings.USB_HIDPort == 1) {
			sprintf(tmp_str, "RCTransmitter");
		}
		if (OpenpilotHwSettings.USB_HIDPort == 2) {
			sprintf(tmp_str, "Disabled");
		}
		draw_button(esContext, "val_USB_HIDPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_USB_HIDPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_USB_HIDPort, -1);
		draw_button(esContext, "inc_USB_HIDPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_USB_HIDPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_USB_VCPPort", VIEW_MODE_FCMENU, "USB_VCPPort", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.USB_VCPPort);
		if (OpenpilotHwSettings.USB_VCPPort == 0) {
			sprintf(tmp_str, "USBTelemetry");
		}
		if (OpenpilotHwSettings.USB_VCPPort == 1) {
			sprintf(tmp_str, "ComBridge");
		}
		if (OpenpilotHwSettings.USB_VCPPort == 2) {
			sprintf(tmp_str, "Disabled");
		}
		draw_button(esContext, "val_USB_VCPPort", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_USB_VCPPort", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_USB_VCPPort, -1);
		draw_button(esContext, "inc_USB_VCPPort", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_USB_VCPPort, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_OptionalModules", VIEW_MODE_FCMENU, "OptionalModules", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		draw_line_f3(esContext, -1.3, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 1.25, -0.77 + (n + page) * 0.12 + 0.07, 0.002, 255, 255, 0, 128);
	}
	n++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_OptionalModules[CameraStab]", VIEW_MODE_FCMENU, "CameraStab", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.OptionalModules[0]);
		if (OpenpilotHwSettings.OptionalModules[0] == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.OptionalModules[0] == 1) {
			sprintf(tmp_str, "Enabled");
		}
		draw_button(esContext, "default_OptionalModules[CameraStab]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_OptionalModules[CameraStab]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_CameraStab, -1);
		draw_button(esContext, "inc_OptionalModules[CameraStab]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_CameraStab, +1);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_OptionalModules[GPS]", VIEW_MODE_FCMENU, "GPS", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.OptionalModules[1]);
		if (OpenpilotHwSettings.OptionalModules[1] == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.OptionalModules[1] == 1) {
			sprintf(tmp_str, "Enabled");
		}
		draw_button(esContext, "default_OptionalModules[GPS]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_OptionalModules[GPS]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_GPS, -1);
		draw_button(esContext, "inc_OptionalModules[GPS]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_GPS, +1);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_OptionalModules[ComUsbBridge]", VIEW_MODE_FCMENU, "ComUsbBridge", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.OptionalModules[2]);
		if (OpenpilotHwSettings.OptionalModules[2] == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.OptionalModules[2] == 1) {
			sprintf(tmp_str, "Enabled");
		}
		draw_button(esContext, "default_OptionalModules[ComUsbBridge]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_OptionalModules[ComUsbBridge]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_ComUsbBridge, -1);
		draw_button(esContext, "inc_OptionalModules[ComUsbBridge]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_ComUsbBridge, +1);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_OptionalModules[Fault]", VIEW_MODE_FCMENU, "Fault", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.OptionalModules[3]);
		if (OpenpilotHwSettings.OptionalModules[3] == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.OptionalModules[3] == 1) {
			sprintf(tmp_str, "Enabled");
		}
		draw_button(esContext, "default_OptionalModules[Fault]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_OptionalModules[Fault]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_Fault, -1);
		draw_button(esContext, "inc_OptionalModules[Fault]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_Fault, +1);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_OptionalModules[Altitude]", VIEW_MODE_FCMENU, "Altitude", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.OptionalModules[4]);
		if (OpenpilotHwSettings.OptionalModules[4] == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.OptionalModules[4] == 1) {
			sprintf(tmp_str, "Enabled");
		}
		draw_button(esContext, "default_OptionalModules[Altitude]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_OptionalModules[Altitude]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_Altitude, -1);
		draw_button(esContext, "inc_OptionalModules[Altitude]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_Altitude, +1);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_OptionalModules[TxPID]", VIEW_MODE_FCMENU, "TxPID", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.OptionalModules[5]);
		if (OpenpilotHwSettings.OptionalModules[5] == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.OptionalModules[5] == 1) {
			sprintf(tmp_str, "Enabled");
		}
		draw_button(esContext, "default_OptionalModules[TxPID]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_OptionalModules[TxPID]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_TxPID, -1);
		draw_button(esContext, "inc_OptionalModules[TxPID]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_TxPID, +1);
	}
	n2++;
	if (n2 >= 2) {
		n++;
		n2 = 0;
	}
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_OptionalModules[Autotune]", VIEW_MODE_FCMENU, "Autotune", FONT_WHITE, -1.25 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotHwSettings.OptionalModules[6]);
		if (OpenpilotHwSettings.OptionalModules[6] == 0) {
			sprintf(tmp_str, "Disabled");
		}
		if (OpenpilotHwSettings.OptionalModules[6] == 1) {
			sprintf(tmp_str, "Enabled");
		}
		draw_button(esContext, "default_OptionalModules[Autotune]", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.35 + 0.9 + n2 * 1.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 2, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_OptionalModules[Autotune]", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.22, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_Autotune, -1);
		draw_button(esContext, "inc_OptionalModules[Autotune]", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -1.35 + 0.7 + n2 * 1.2 + 0.35, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotHwSettings_OptionalModules_Autotune, +1);
	}
	n2++;
	n++;
	n2 = 0;

	if (n > 13) {
		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, 0.77, 0.002, 255, 255, 255, 128);
		if (page < 0) {
			set_button("down", VIEW_MODE_FCMENU, 1.3, -0.77, 1.35, -0.67, openpilot_down, 1.0, 0);
			set_button("down2", VIEW_MODE_FCMENU, 1.3, -0.77, 1.35, 0.0, openpilot_down, 3.0, 0);
		}
		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);
		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);
		draw_rect_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);
		if (n + page - 13 > 0) {
			set_button("up", VIEW_MODE_FCMENU, 1.3, 0.67, 1.35, 0.77, openpilot_up, 1.0, 0);
			set_button("up2", VIEW_MODE_FCMENU, 1.3, 0.0, 1.35, 0.77, openpilot_up, 3.0, 0);
		}
		if (page > 0) {
			page = 0;
		}
		if (page < (n - 13) * -1) {
			page = (n - 13) * -1;
		}
		draw_box_f3(esContext, 1.3, 0.67, 0.002, 1.35, 0.77, 0.002, 255, 255, 255, 128);
		draw_box_f3(esContext, 1.3, 0.77, 0.002, 1.35, 0.67, 0.002, 255, 255, 255, 128);
		draw_rect_f3(esContext, 1.3, 0.77, 0.002, 1.35, 0.67, 0.002, 255, 255, 255, 128);
		draw_box_f3(esContext, 1.3 - 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13) - 0.02, 0.002, 1.35 + 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13), 0.002, 255, 255, 255, 200);
		draw_rect_f3(esContext, 1.3 - 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13) - 0.02, 0.002, 1.35 + 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13), 0.002, 100, 100, 100, 128);
	}
	if (openpilot_get == 1) {
		draw_button(esContext, "get", VIEW_MODE_FCMENU, "[GET]", FONT_GREEN, -0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_get, 0.0);
	} else {
		draw_button(esContext, "get", VIEW_MODE_FCMENU, "[GET]", FONT_WHITE, -0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_get, 0.0);
	}
	if (openpilot_set == 1) {
		draw_button(esContext, "set", VIEW_MODE_FCMENU, "[SET]", FONT_GREEN, 0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_set, 0.0);
	} else {
		draw_button(esContext, "set", VIEW_MODE_FCMENU, "[SET]", FONT_WHITE, 0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_set, 0.0);
	}
	draw_button(esContext, "defaults", VIEW_MODE_FCMENU, "[DEFAULTS]", FONT_WHITE, -0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_defaults, 0.0);
	draw_button(esContext, "flash", VIEW_MODE_FCMENU, "[FLASH]", FONT_WHITE, 0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_flash, 0.0);
}


uint8_t openpilot_change_OpenpilotSystemSettings_GUIConfigData (char *name, float x, float y, int8_t button, float data) {
	OpenpilotSystemSettings.GUIConfigData += (int8_t)data;
	return 0;
}

uint8_t openpilot_change_OpenpilotSystemSettings_AirframeType (char *name, float x, float y, int8_t button, float data) {
	if ((int8_t)data < 0 && OpenpilotSystemSettings.AirframeType > 0) {
		OpenpilotSystemSettings.AirframeType += (int8_t)data;
	} else if ((int8_t)data > 0 && OpenpilotSystemSettings.AirframeType < 19 - 1) {
		OpenpilotSystemSettings.AirframeType += (int8_t)data;
	} else {
		OpenpilotSystemSettings.AirframeType = 0;
	}
	return 0;
}


void openpilot_SystemSettings (ESContext *esContext) {
	int16_t n = 0;
	char tmp_str[100];

	draw_title(esContext, "SystemSettings");

	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_GUIConfigData", VIEW_MODE_FCMENU, "GUIConfigData", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotSystemSettings.GUIConfigData);
		draw_button(esContext, "val_GUIConfigData", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_GUIConfigData", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotSystemSettings_GUIConfigData, -1);
		draw_button(esContext, "inc_GUIConfigData", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotSystemSettings_GUIConfigData, +1);
	}
	n++;
	if (-0.77 + (n + page) * 0.12 > -0.8 && -0.77 + (n + page) * 0.12 < 0.7) {
		draw_button(esContext, "name_AirframeType", VIEW_MODE_FCMENU, "AirframeType", FONT_WHITE, -1.3, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_null, (float)n);
		sprintf(tmp_str, "%i", OpenpilotSystemSettings.AirframeType);
		if (OpenpilotSystemSettings.AirframeType == 0) {
			sprintf(tmp_str, "FixedWing");
		}
		if (OpenpilotSystemSettings.AirframeType == 1) {
			sprintf(tmp_str, "FixedWingElevon");
		}
		if (OpenpilotSystemSettings.AirframeType == 2) {
			sprintf(tmp_str, "FixedWingVtail");
		}
		if (OpenpilotSystemSettings.AirframeType == 3) {
			sprintf(tmp_str, "VTOL");
		}
		if (OpenpilotSystemSettings.AirframeType == 4) {
			sprintf(tmp_str, "HeliCP");
		}
		if (OpenpilotSystemSettings.AirframeType == 5) {
			sprintf(tmp_str, "QuadX");
		}
		if (OpenpilotSystemSettings.AirframeType == 6) {
			sprintf(tmp_str, "QuadP");
		}
		if (OpenpilotSystemSettings.AirframeType == 7) {
			sprintf(tmp_str, "Hexa");
		}
		if (OpenpilotSystemSettings.AirframeType == 8) {
			sprintf(tmp_str, "Octo");
		}
		if (OpenpilotSystemSettings.AirframeType == 9) {
			sprintf(tmp_str, "Custom");
		}
		if (OpenpilotSystemSettings.AirframeType == 10) {
			sprintf(tmp_str, "HexaX");
		}
		if (OpenpilotSystemSettings.AirframeType == 11) {
			sprintf(tmp_str, "OctoV");
		}
		if (OpenpilotSystemSettings.AirframeType == 12) {
			sprintf(tmp_str, "OctoCoaxP");
		}
		if (OpenpilotSystemSettings.AirframeType == 13) {
			sprintf(tmp_str, "OctoCoaxX");
		}
		if (OpenpilotSystemSettings.AirframeType == 14) {
			sprintf(tmp_str, "HexaCoax");
		}
		if (OpenpilotSystemSettings.AirframeType == 15) {
			sprintf(tmp_str, "Tri");
		}
		if (OpenpilotSystemSettings.AirframeType == 16) {
			sprintf(tmp_str, "GroundVehicleCar");
		}
		if (OpenpilotSystemSettings.AirframeType == 17) {
			sprintf(tmp_str, "GroundVehicleDifferential");
		}
		if (OpenpilotSystemSettings.AirframeType == 18) {
			sprintf(tmp_str, "GroundVehicleMotorcycle");
		}
		draw_button(esContext, "val_AirframeType", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, 0.0, -0.77 + (n + page) * 0.12, 0.002, 0.05, 0, 0, openpilot_null, (float)n);
		draw_button(esContext, "dec_AirframeType", VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.25 + 0.2, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotSystemSettings_AirframeType, -1);
		draw_button(esContext, "inc_AirframeType", VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.25 + 0.4, -0.77 + (n + page) * 0.12, 0.002, 0.06, 0, 0, openpilot_change_OpenpilotSystemSettings_AirframeType, +1);
	}
	n++;

	if (n > 13) {
		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, 0.77, 0.002, 255, 255, 255, 128);
		if (page < 0) {
			set_button("down", VIEW_MODE_FCMENU, 1.3, -0.77, 1.35, -0.67, openpilot_down, 1.0, 0);
			set_button("down2", VIEW_MODE_FCMENU, 1.3, -0.77, 1.35, 0.0, openpilot_down, 3.0, 0);
		}
		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);
		draw_box_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);
		draw_rect_f3(esContext, 1.3, -0.77, 0.002, 1.35, -0.67, 0.002, 255, 255, 255, 128);
		if (n + page - 13 > 0) {
			set_button("up", VIEW_MODE_FCMENU, 1.3, 0.67, 1.35, 0.77, openpilot_up, 1.0, 0);
			set_button("up2", VIEW_MODE_FCMENU, 1.3, 0.0, 1.35, 0.77, openpilot_up, 3.0, 0);
		}
		if (page > 0) {
			page = 0;
		}
		if (page < (n - 13) * -1) {
			page = (n - 13) * -1;
		}
		draw_box_f3(esContext, 1.3, 0.67, 0.002, 1.35, 0.77, 0.002, 255, 255, 255, 128);
		draw_box_f3(esContext, 1.3, 0.77, 0.002, 1.35, 0.67, 0.002, 255, 255, 255, 128);
		draw_rect_f3(esContext, 1.3, 0.77, 0.002, 1.35, 0.67, 0.002, 255, 255, 255, 128);
		draw_box_f3(esContext, 1.3 - 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13) - 0.02, 0.002, 1.35 + 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13), 0.002, 255, 255, 255, 200);
		draw_rect_f3(esContext, 1.3 - 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13) - 0.02, 0.002, 1.35 + 0.01, 0.67 - (1.34 - 0.02) * (float)(n + page - 13) / (float)(n - 13), 0.002, 100, 100, 100, 128);
	}
	if (openpilot_get == 1) {
		draw_button(esContext, "get", VIEW_MODE_FCMENU, "[GET]", FONT_GREEN, -0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_get, 0.0);
	} else {
		draw_button(esContext, "get", VIEW_MODE_FCMENU, "[GET]", FONT_WHITE, -0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_get, 0.0);
	}
	if (openpilot_set == 1) {
		draw_button(esContext, "set", VIEW_MODE_FCMENU, "[SET]", FONT_GREEN, 0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_set, 0.0);
	} else {
		draw_button(esContext, "set", VIEW_MODE_FCMENU, "[SET]", FONT_WHITE, 0.6, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_setup_set, 0.0);
	}
	draw_button(esContext, "defaults", VIEW_MODE_FCMENU, "[DEFAULTS]", FONT_WHITE, -0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_defaults, 0.0);
	draw_button(esContext, "flash", VIEW_MODE_FCMENU, "[FLASH]", FONT_WHITE, 0.3, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_flash, 0.0);
}

void screen_openpilot (ESContext *esContext) {
	if (mode == -1) {
	} else if (mode == 0) {
		openpilot_StabilizationSettings(esContext);
	} else if (mode == 1) {
		openpilot_HwSettings(esContext);
	} else if (mode == 2) {
		openpilot_SystemSettings(esContext);
	}
	draw_button(esContext, "mode", VIEW_MODE_FCMENU, "[MODE]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, openpilot_mode, 0.0);
}

