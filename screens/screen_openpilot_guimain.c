

uint16_t show_num = 0;
uint16_t msy = 0;

uint8_t UAVT_gui_show_num_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	show_num = (uint16_t)data;
	reset_buttons();
	sy = 0;
	return 0;
}

uint8_t UAVT_gui_main_scroll(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		if (msy > 0) {
			msy--;
		}
	} else if (button == 5) {
		msy++;
	}
	reset_buttons();
	return 0;
}

void UAVT_gui_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	if (show_num == 1) {
		UAVT_gui_ActuatorSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "ActuatorSettingsShow", VIEW_MODE_FCMENU, "ActuatorSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)1);
		}
	}
	nn++;
	if (show_num == 2) {
		UAVT_gui_AirspeedSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "AirspeedSettingsShow", VIEW_MODE_FCMENU, "AirspeedSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)2);
		}
	}
	nn++;
	if (show_num == 3) {
		UAVT_gui_AltitudeHoldSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "AltitudeHoldSettingsShow", VIEW_MODE_FCMENU, "AltitudeHoldSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)3);
		}
	}
	nn++;
	if (show_num == 4) {
		UAVT_gui_AttitudeSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "AttitudeSettingsShow", VIEW_MODE_FCMENU, "AttitudeSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)4);
		}
	}
	nn++;
	if (show_num == 5) {
		UAVT_gui_BrushlessGimbalSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "BrushlessGimbalSettingsShow", VIEW_MODE_FCMENU, "BrushlessGimbalSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)5);
		}
	}
	nn++;
	if (show_num == 6) {
		UAVT_gui_CameraStabSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "CameraStabSettingsShow", VIEW_MODE_FCMENU, "CameraStabSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)6);
		}
	}
	nn++;
	if (show_num == 7) {
		UAVT_gui_FaultSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "FaultSettingsShow", VIEW_MODE_FCMENU, "FaultSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)7);
		}
	}
	nn++;
	if (show_num == 8) {
		UAVT_gui_FixedWingAirspeeds_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "FixedWingAirspeedsShow", VIEW_MODE_FCMENU, "FixedWingAirspeeds ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)8);
		}
	}
	nn++;
	if (show_num == 9) {
		UAVT_gui_FixedWingPathFollowerSettingsCC_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "FixedWingPathFollowerSettingsCCShow", VIEW_MODE_FCMENU, "FixedWingPathFollowerSettingsCC ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)9);
		}
	}
	nn++;
	if (show_num == 10) {
		UAVT_gui_FixedWingPathFollowerSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "FixedWingPathFollowerSettingsShow", VIEW_MODE_FCMENU, "FixedWingPathFollowerSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)10);
		}
	}
	nn++;
	if (show_num == 11) {
		UAVT_gui_FlightBatterySettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "FlightBatterySettingsShow", VIEW_MODE_FCMENU, "FlightBatterySettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)11);
		}
	}
	nn++;
	if (show_num == 12) {
		UAVT_gui_FlightPlanSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "FlightPlanSettingsShow", VIEW_MODE_FCMENU, "FlightPlanSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)12);
		}
	}
	nn++;
	if (show_num == 13) {
		UAVT_gui_GeoFenceSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "GeoFenceSettingsShow", VIEW_MODE_FCMENU, "GeoFenceSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)13);
		}
	}
	nn++;
	if (show_num == 14) {
		UAVT_gui_GroundPathFollowerSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "GroundPathFollowerSettingsShow", VIEW_MODE_FCMENU, "GroundPathFollowerSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)14);
		}
	}
	nn++;
	if (show_num == 15) {
		UAVT_gui_HomeLocation_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HomeLocationShow", VIEW_MODE_FCMENU, "HomeLocation ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)15);
		}
	}
	nn++;
	if (show_num == 16) {
		UAVT_gui_HoTTSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HoTTSettingsShow", VIEW_MODE_FCMENU, "HoTTSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)16);
		}
	}
	nn++;
	if (show_num == 17) {
		UAVT_gui_HwColibri_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwColibriShow", VIEW_MODE_FCMENU, "HwColibri (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)17);
		}
	}
	nn++;
	if (show_num == 18) {
		UAVT_gui_HwCopterControl_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwCopterControlShow", VIEW_MODE_FCMENU, "HwCopterControl (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)18);
		}
	}
	nn++;
	if (show_num == 19) {
		UAVT_gui_HwDiscoveryF4_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwDiscoveryF4Show", VIEW_MODE_FCMENU, "HwDiscoveryF4 (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)19);
		}
	}
	nn++;
	if (show_num == 20) {
		UAVT_gui_HwFlyingF3_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwFlyingF3Show", VIEW_MODE_FCMENU, "HwFlyingF3 (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)20);
		}
	}
	nn++;
	if (show_num == 21) {
		UAVT_gui_HwFlyingF4_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwFlyingF4Show", VIEW_MODE_FCMENU, "HwFlyingF4 (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)21);
		}
	}
	nn++;
	if (show_num == 22) {
		UAVT_gui_HwFreedom_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwFreedomShow", VIEW_MODE_FCMENU, "HwFreedom (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)22);
		}
	}
	nn++;
	if (show_num == 23) {
		UAVT_gui_HwQuanton_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwQuantonShow", VIEW_MODE_FCMENU, "HwQuanton (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)23);
		}
	}
	nn++;
	if (show_num == 24) {
		UAVT_gui_HwRevolution_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwRevolutionShow", VIEW_MODE_FCMENU, "HwRevolution (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)24);
		}
	}
	nn++;
	if (show_num == 25) {
		UAVT_gui_HwRevoMini_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwRevoMiniShow", VIEW_MODE_FCMENU, "HwRevoMini (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)25);
		}
	}
	nn++;
	if (show_num == 26) {
		UAVT_gui_HwSparkyBGC_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwSparkyBGCShow", VIEW_MODE_FCMENU, "HwSparkyBGC (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)26);
		}
	}
	nn++;
	if (show_num == 27) {
		UAVT_gui_HwSparky_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "HwSparkyShow", VIEW_MODE_FCMENU, "HwSparky (HardwareSettings)", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)27);
		}
	}
	nn++;
	if (show_num == 28) {
		UAVT_gui_I2CVMUserProgram_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "I2CVMUserProgramShow", VIEW_MODE_FCMENU, "I2CVMUserProgram ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)28);
		}
	}
	nn++;
	if (show_num == 29) {
		UAVT_gui_INSSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "INSSettingsShow", VIEW_MODE_FCMENU, "INSSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)29);
		}
	}
	nn++;
	if (show_num == 30) {
		UAVT_gui_LoggingSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "LoggingSettingsShow", VIEW_MODE_FCMENU, "LoggingSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)30);
		}
	}
	nn++;
	if (show_num == 31) {
		UAVT_gui_ManualControlSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "ManualControlSettingsShow", VIEW_MODE_FCMENU, "ManualControlSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)31);
		}
	}
	nn++;
	if (show_num == 32) {
		UAVT_gui_MixerSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "MixerSettingsShow", VIEW_MODE_FCMENU, "MixerSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)32);
		}
	}
	nn++;
	if (show_num == 33) {
		UAVT_gui_ModuleSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "ModuleSettingsShow", VIEW_MODE_FCMENU, "ModuleSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)33);
		}
	}
	nn++;
	if (show_num == 34) {
		UAVT_gui_MWRateSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "MWRateSettingsShow", VIEW_MODE_FCMENU, "MWRateSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)34);
		}
	}
	nn++;
	if (show_num == 35) {
		UAVT_gui_OPLinkSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "OPLinkSettingsShow", VIEW_MODE_FCMENU, "OPLinkSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)35);
		}
	}
	nn++;
	if (show_num == 36) {
		UAVT_gui_OveroSyncSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "OveroSyncSettingsShow", VIEW_MODE_FCMENU, "OveroSyncSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)36);
		}
	}
	nn++;
	if (show_num == 37) {
		UAVT_gui_PathPlannerSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "PathPlannerSettingsShow", VIEW_MODE_FCMENU, "PathPlannerSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)37);
		}
	}
	nn++;
	if (show_num == 38) {
		UAVT_gui_PicoCSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "PicoCSettingsShow", VIEW_MODE_FCMENU, "PicoCSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)38);
		}
	}
	nn++;
	if (show_num == 39) {
		UAVT_gui_SensorSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "SensorSettingsShow", VIEW_MODE_FCMENU, "SensorSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)39);
		}
	}
	nn++;
	if (show_num == 40) {
		UAVT_gui_StabilizationSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "StabilizationSettingsShow", VIEW_MODE_FCMENU, "StabilizationSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)40);
		}
	}
	nn++;
	if (show_num == 41) {
		UAVT_gui_StateEstimation_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "StateEstimationShow", VIEW_MODE_FCMENU, "StateEstimation ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)41);
		}
	}
	nn++;
	if (show_num == 42) {
		UAVT_gui_SystemIdent_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "SystemIdentShow", VIEW_MODE_FCMENU, "SystemIdent ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)42);
		}
	}
	nn++;
	if (show_num == 43) {
		UAVT_gui_SystemSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "SystemSettingsShow", VIEW_MODE_FCMENU, "SystemSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)43);
		}
	}
	nn++;
	if (show_num == 44) {
		UAVT_gui_TrimAnglesSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "TrimAnglesSettingsShow", VIEW_MODE_FCMENU, "TrimAnglesSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change,
							 (float)44);
		}
	}
	nn++;
	if (show_num == 45) {
		UAVT_gui_TxPIDSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "TxPIDSettingsShow", VIEW_MODE_FCMENU, "TxPIDSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_show_num_change, (float)45);
		}
	}
	nn++;
	if (show_num == 46) {
		UAVT_gui_VibrationAnalysisSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "VibrationAnalysisSettingsShow", VIEW_MODE_FCMENU, "VibrationAnalysisSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)46);
		}
	}
	nn++;
	if (show_num == 47) {
		UAVT_gui_VtolPathFollowerSettings_show(esContext);
	} else if (show_num == 0) {
		if (nn >= msy && nn < msy + 14) {
			draw_text_button(esContext, "VtolPathFollowerSettingsShow", VIEW_MODE_FCMENU, "VtolPathFollowerSettings ()", FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
							 UAVT_gui_show_num_change, (float)47);
		}
	}
	nn++;
	if (msy > nn - 14) {
		msy = nn - 14;
	}
	if (sy > nn - 14) {
		sy = nn - 14;
	}
	if (show_num != 0) {
		draw_text_button(esContext, "gui_scroll", VIEW_MODE_FCMENU, "[SCROLL]", FONT_WHITE, 0.9, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, UAVT_gui_scroll, 0.0);
	}
	if (show_num == 0) {
		draw_text_button(esContext, "gui_main_scroll", VIEW_MODE_FCMENU, "[SCROLL]", FONT_WHITE, 0.9, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, UAVT_gui_main_scroll, 0.0);
	} else {
		draw_text_button(esContext, "gui_show_num_change", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, UAVT_gui_show_num_change, 0.0);
	}
}

