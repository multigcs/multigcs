
uint8_t UAVT_gui_ActuatorSettingsChannelUpdateFreq_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[0] += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[0] -= (uint16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[0] += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelUpdateFreq_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[1] += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[1] -= (uint16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[1] += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelUpdateFreq_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[2] += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[2] -= (uint16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[2] += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelUpdateFreq_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[3] += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[3] -= (uint16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[3] += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelUpdateFreq_4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[4] += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[4] -= (uint16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[4] += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelUpdateFreq_5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[5] += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[5] -= (uint16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelUpdateFreq[5] += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[0] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[0] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[0] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[1] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[1] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[1] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[2] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[2] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[2] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[3] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[3] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[3] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[4] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[4] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[4] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[5] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[5] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[5] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_6_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[6] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[6] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[6] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_7_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[7] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[7] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[7] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_8_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[8] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[8] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[8] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMax_9_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMax[9] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMax[9] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMax[9] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[0] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[0] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[0] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[1] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[1] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[1] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[2] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[2] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[2] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[3] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[3] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[3] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[4] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[4] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[4] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[5] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[5] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[5] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_6_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[6] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[6] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[6] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_7_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[7] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[7] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[7] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_8_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[8] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[8] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[8] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelNeutral_9_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[9] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelNeutral[9] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelNeutral[9] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[0] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[0] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[0] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[1] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[1] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[1] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[2] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[2] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[2] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[3] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[3] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[3] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[4] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[4] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[4] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[5] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[5] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[5] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_6_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[6] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[6] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[6] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_7_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[7] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[7] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[7] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_8_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[8] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[8] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[8] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelMin_9_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelMin[9] += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelMin[9] -= (int16_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelMin[9] += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[0] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[0] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[0] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[0] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[0] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[1] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[1] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[1] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[1] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[1] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[2] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[2] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[2] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[2] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[2] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[3] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[3] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[3] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[3] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[3] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[4] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[4] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[4] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[4] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[4] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[5] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[5] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[5] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[5] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[5] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_6_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[6] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[6] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[6] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[6] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[6] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_7_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[7] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[7] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[7] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[7] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[7] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_8_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[8] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[8] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[8] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[8] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[8] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelType_9_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelType[9] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelType[9] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelType[9] += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.ChannelType[9] >= ACTUATORSETTINGS_CHANNELTYPE_LASTITEM) {
		uavtalk_ActuatorSettingsData.ChannelType[9] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[0] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[0] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[0] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[1] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[1] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[1] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[2] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[2] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[2] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[3] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[3] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[3] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[4] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[4] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[4] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[5] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[5] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[5] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_6_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[6] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[6] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[6] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_7_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[7] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[7] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[7] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_8_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[8] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[8] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[8] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsChannelAddr_9_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.ChannelAddr[9] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.ChannelAddr[9] -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.ChannelAddr[9] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ActuatorSettingsMotorsSpinWhileArmed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ActuatorSettingsData.MotorsSpinWhileArmed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ActuatorSettingsData.MotorsSpinWhileArmed -= (uint8_t)1.0;
	} else {
		uavtalk_ActuatorSettingsData.MotorsSpinWhileArmed += (uint8_t)data;
	}
	if (uavtalk_ActuatorSettingsData.MotorsSpinWhileArmed >= ACTUATORSETTINGS_MOTORSSPINWHILEARMED_LASTITEM) {
		uavtalk_ActuatorSettingsData.MotorsSpinWhileArmed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_AirspeedSettingsScale_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AirspeedSettingsData.Scale += (float)1.0;
	} else if (button == 5) {
		uavtalk_AirspeedSettingsData.Scale -= (float)1.0;
	} else {
		uavtalk_AirspeedSettingsData.Scale += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AirspeedSettingsZeroPoint_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AirspeedSettingsData.ZeroPoint += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_AirspeedSettingsData.ZeroPoint -= (uint16_t)1.0;
	} else {
		uavtalk_AirspeedSettingsData.ZeroPoint += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_AirspeedSettingsGPSSamplePeriod_ms_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AirspeedSettingsData.GPSSamplePeriod_ms += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AirspeedSettingsData.GPSSamplePeriod_ms -= (uint8_t)1.0;
	} else {
		uavtalk_AirspeedSettingsData.GPSSamplePeriod_ms += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_AirspeedSettingsAirspeedSensorType_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AirspeedSettingsData.AirspeedSensorType += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AirspeedSettingsData.AirspeedSensorType -= (uint8_t)1.0;
	} else {
		uavtalk_AirspeedSettingsData.AirspeedSensorType += (uint8_t)data;
	}
	if (uavtalk_AirspeedSettingsData.AirspeedSensorType >= AIRSPEEDSETTINGS_AIRSPEEDSENSORTYPE_LASTITEM) {
		uavtalk_AirspeedSettingsData.AirspeedSensorType = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_AirspeedSettingsAnalogPin_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AirspeedSettingsData.AnalogPin += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AirspeedSettingsData.AnalogPin -= (uint8_t)1.0;
	} else {
		uavtalk_AirspeedSettingsData.AnalogPin += (uint8_t)data;
	}
	if (uavtalk_AirspeedSettingsData.AnalogPin >= AIRSPEEDSETTINGS_ANALOGPIN_LASTITEM) {
		uavtalk_AirspeedSettingsData.AnalogPin = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_AltitudeHoldSettingsPositionKp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AltitudeHoldSettingsData.PositionKp += (float)1.0;
	} else if (button == 5) {
		uavtalk_AltitudeHoldSettingsData.PositionKp -= (float)1.0;
	} else {
		uavtalk_AltitudeHoldSettingsData.PositionKp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AltitudeHoldSettingsVelocityKp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AltitudeHoldSettingsData.VelocityKp += (float)1.0;
	} else if (button == 5) {
		uavtalk_AltitudeHoldSettingsData.VelocityKp -= (float)1.0;
	} else {
		uavtalk_AltitudeHoldSettingsData.VelocityKp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AltitudeHoldSettingsVelocityKi_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AltitudeHoldSettingsData.VelocityKi += (float)1.0;
	} else if (button == 5) {
		uavtalk_AltitudeHoldSettingsData.VelocityKi -= (float)1.0;
	} else {
		uavtalk_AltitudeHoldSettingsData.VelocityKi += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AltitudeHoldSettingsAttitudeComp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AltitudeHoldSettingsData.AttitudeComp += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_AltitudeHoldSettingsData.AttitudeComp -= (uint16_t)1.0;
	} else {
		uavtalk_AltitudeHoldSettingsData.AttitudeComp += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_AltitudeHoldSettingsMaxRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AltitudeHoldSettingsData.MaxRate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AltitudeHoldSettingsData.MaxRate -= (uint8_t)1.0;
	} else {
		uavtalk_AltitudeHoldSettingsData.MaxRate += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_AltitudeHoldSettingsExpo_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AltitudeHoldSettingsData.Expo += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AltitudeHoldSettingsData.Expo -= (uint8_t)1.0;
	} else {
		uavtalk_AltitudeHoldSettingsData.Expo += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_AltitudeHoldSettingsDeadband_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AltitudeHoldSettingsData.Deadband += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AltitudeHoldSettingsData.Deadband -= (uint8_t)1.0;
	} else {
		uavtalk_AltitudeHoldSettingsData.Deadband += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsMagKp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.MagKp += (float)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.MagKp -= (float)1.0;
	} else {
		uavtalk_AttitudeSettingsData.MagKp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsMagKi_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.MagKi += (float)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.MagKi -= (float)1.0;
	} else {
		uavtalk_AttitudeSettingsData.MagKi += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsAccelKp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.AccelKp += (float)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.AccelKp -= (float)1.0;
	} else {
		uavtalk_AttitudeSettingsData.AccelKp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsAccelKi_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.AccelKi += (float)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.AccelKi -= (float)1.0;
	} else {
		uavtalk_AttitudeSettingsData.AccelKi += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsAccelTau_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.AccelTau += (float)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.AccelTau -= (float)1.0;
	} else {
		uavtalk_AttitudeSettingsData.AccelTau += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsVertPositionTau_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.VertPositionTau += (float)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.VertPositionTau -= (float)1.0;
	} else {
		uavtalk_AttitudeSettingsData.VertPositionTau += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsYawBiasRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.YawBiasRate += (float)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.YawBiasRate -= (float)1.0;
	} else {
		uavtalk_AttitudeSettingsData.YawBiasRate += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsBoardRotation_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.BoardRotation.Roll += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.BoardRotation.Roll -= (int16_t)1.0;
	} else {
		uavtalk_AttitudeSettingsData.BoardRotation.Roll += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsBoardRotation_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.BoardRotation.Pitch += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.BoardRotation.Pitch -= (int16_t)1.0;
	} else {
		uavtalk_AttitudeSettingsData.BoardRotation.Pitch += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsBoardRotation_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.BoardRotation.Yaw += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.BoardRotation.Yaw -= (int16_t)1.0;
	} else {
		uavtalk_AttitudeSettingsData.BoardRotation.Yaw += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsZeroDuringArming_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.ZeroDuringArming += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.ZeroDuringArming -= (uint8_t)1.0;
	} else {
		uavtalk_AttitudeSettingsData.ZeroDuringArming += (uint8_t)data;
	}
	if (uavtalk_AttitudeSettingsData.ZeroDuringArming >= ATTITUDESETTINGS_ZERODURINGARMING_LASTITEM) {
		uavtalk_AttitudeSettingsData.ZeroDuringArming = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsBiasCorrectGyro_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.BiasCorrectGyro += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.BiasCorrectGyro -= (uint8_t)1.0;
	} else {
		uavtalk_AttitudeSettingsData.BiasCorrectGyro += (uint8_t)data;
	}
	if (uavtalk_AttitudeSettingsData.BiasCorrectGyro >= ATTITUDESETTINGS_BIASCORRECTGYRO_LASTITEM) {
		uavtalk_AttitudeSettingsData.BiasCorrectGyro = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsFilterChoice_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.FilterChoice += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.FilterChoice -= (uint8_t)1.0;
	} else {
		uavtalk_AttitudeSettingsData.FilterChoice += (uint8_t)data;
	}
	if (uavtalk_AttitudeSettingsData.FilterChoice >= ATTITUDESETTINGS_FILTERCHOICE_LASTITEM) {
		uavtalk_AttitudeSettingsData.FilterChoice = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_AttitudeSettingsTrimFlight_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_AttitudeSettingsData.TrimFlight += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_AttitudeSettingsData.TrimFlight -= (uint8_t)1.0;
	} else {
		uavtalk_AttitudeSettingsData.TrimFlight += (uint8_t)data;
	}
	if (uavtalk_AttitudeSettingsData.TrimFlight >= ATTITUDESETTINGS_TRIMFLIGHT_LASTITEM) {
		uavtalk_AttitudeSettingsData.TrimFlight = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsDamping_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.Damping.Roll += (float)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.Damping.Roll -= (float)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.Damping.Roll += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsDamping_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.Damping.Pitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.Damping.Pitch -= (float)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.Damping.Pitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsDamping_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.Damping.Yaw += (float)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.Damping.Yaw -= (float)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.Damping.Yaw += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsMaxDPS_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.MaxDPS.Roll += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.MaxDPS.Roll -= (uint16_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.MaxDPS.Roll += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsMaxDPS_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.MaxDPS.Pitch += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.MaxDPS.Pitch -= (uint16_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.MaxDPS.Pitch += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsMaxDPS_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.MaxDPS.Yaw += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.MaxDPS.Yaw -= (uint16_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.MaxDPS.Yaw += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsSlewLimit_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.SlewLimit.Roll += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.SlewLimit.Roll -= (uint16_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.SlewLimit.Roll += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsSlewLimit_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.SlewLimit.Pitch += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.SlewLimit.Pitch -= (uint16_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.SlewLimit.Pitch += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsSlewLimit_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.SlewLimit.Yaw += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.SlewLimit.Yaw -= (uint16_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.SlewLimit.Yaw += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsPowerScale_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.PowerScale.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.PowerScale.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.PowerScale.Roll += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsPowerScale_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.PowerScale.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.PowerScale.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.PowerScale.Pitch += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsPowerScale_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.PowerScale.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.PowerScale.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.PowerScale.Yaw += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsMaxAngle_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.MaxAngle.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.MaxAngle.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.MaxAngle.Roll += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsMaxAngle_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.MaxAngle.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.MaxAngle.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.MaxAngle.Pitch += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsMaxAngle_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.MaxAngle.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.MaxAngle.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.MaxAngle.Yaw += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsRollFraction_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.RollFraction += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.RollFraction -= (uint8_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.RollFraction += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_BrushlessGimbalSettingsPowerupSequence_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_BrushlessGimbalSettingsData.PowerupSequence += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_BrushlessGimbalSettingsData.PowerupSequence -= (uint8_t)1.0;
	} else {
		uavtalk_BrushlessGimbalSettingsData.PowerupSequence += (uint8_t)data;
	}
	if (uavtalk_BrushlessGimbalSettingsData.PowerupSequence >= BRUSHLESSGIMBALSETTINGS_POWERUPSEQUENCE_LASTITEM) {
		uavtalk_BrushlessGimbalSettingsData.PowerupSequence = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsMaxAxisLockRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.MaxAxisLockRate += (float)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.MaxAxisLockRate -= (float)1.0;
	} else {
		uavtalk_CameraStabSettingsData.MaxAxisLockRate += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsMaxAccel_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.MaxAccel += (float)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.MaxAccel -= (float)1.0;
	} else {
		uavtalk_CameraStabSettingsData.MaxAccel += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInput_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.Input.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.Input.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.Input.Roll += (uint8_t)data;
	}
	if (uavtalk_CameraStabSettingsData.Input.Roll >= CAMERASTABSETTINGS_INPUT_LASTITEM) {
		uavtalk_CameraStabSettingsData.Input.Roll = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInput_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.Input.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.Input.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.Input.Pitch += (uint8_t)data;
	}
	if (uavtalk_CameraStabSettingsData.Input.Pitch >= CAMERASTABSETTINGS_INPUT_LASTITEM) {
		uavtalk_CameraStabSettingsData.Input.Pitch = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInput_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.Input.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.Input.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.Input.Yaw += (uint8_t)data;
	}
	if (uavtalk_CameraStabSettingsData.Input.Yaw >= CAMERASTABSETTINGS_INPUT_LASTITEM) {
		uavtalk_CameraStabSettingsData.Input.Yaw = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInputRange_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.InputRange.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.InputRange.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.InputRange.Roll += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInputRange_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.InputRange.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.InputRange.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.InputRange.Pitch += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInputRange_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.InputRange.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.InputRange.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.InputRange.Yaw += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInputRate_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.InputRate.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.InputRate.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.InputRate.Roll += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInputRate_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.InputRate.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.InputRate.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.InputRate.Pitch += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInputRate_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.InputRate.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.InputRate.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.InputRate.Yaw += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsOutputRange_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.OutputRange.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.OutputRange.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.OutputRange.Roll += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsOutputRange_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.OutputRange.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.OutputRange.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.OutputRange.Pitch += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsOutputRange_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.OutputRange.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.OutputRange.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.OutputRange.Yaw += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsFeedForward_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.FeedForward.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.FeedForward.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.FeedForward.Roll += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsFeedForward_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.FeedForward.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.FeedForward.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.FeedForward.Pitch += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsFeedForward_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.FeedForward.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.FeedForward.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.FeedForward.Yaw += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsStabilizationMode_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.StabilizationMode.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.StabilizationMode.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.StabilizationMode.Roll += (uint8_t)data;
	}
	if (uavtalk_CameraStabSettingsData.StabilizationMode.Roll >= CAMERASTABSETTINGS_STABILIZATIONMODE_LASTITEM) {
		uavtalk_CameraStabSettingsData.StabilizationMode.Roll = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsStabilizationMode_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.StabilizationMode.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.StabilizationMode.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.StabilizationMode.Pitch += (uint8_t)data;
	}
	if (uavtalk_CameraStabSettingsData.StabilizationMode.Pitch >= CAMERASTABSETTINGS_STABILIZATIONMODE_LASTITEM) {
		uavtalk_CameraStabSettingsData.StabilizationMode.Pitch = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsStabilizationMode_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.StabilizationMode.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.StabilizationMode.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.StabilizationMode.Yaw += (uint8_t)data;
	}
	if (uavtalk_CameraStabSettingsData.StabilizationMode.Yaw >= CAMERASTABSETTINGS_STABILIZATIONMODE_LASTITEM) {
		uavtalk_CameraStabSettingsData.StabilizationMode.Yaw = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsAttitudeFilter_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.AttitudeFilter += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.AttitudeFilter -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.AttitudeFilter += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsInputFilter_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.InputFilter += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.InputFilter -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.InputFilter += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_CameraStabSettingsFeedForwardTime_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_CameraStabSettingsData.FeedForwardTime += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_CameraStabSettingsData.FeedForwardTime -= (uint8_t)1.0;
	} else {
		uavtalk_CameraStabSettingsData.FeedForwardTime += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_FaultSettingsActivateFault_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FaultSettingsData.ActivateFault += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_FaultSettingsData.ActivateFault -= (uint8_t)1.0;
	} else {
		uavtalk_FaultSettingsData.ActivateFault += (uint8_t)data;
	}
	if (uavtalk_FaultSettingsData.ActivateFault >= FAULTSETTINGS_ACTIVATEFAULT_LASTITEM) {
		uavtalk_FaultSettingsData.ActivateFault = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingAirspeedsAirSpeedMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingAirspeedsData.AirSpeedMax += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingAirspeedsData.AirSpeedMax -= (float)1.0;
	} else {
		uavtalk_FixedWingAirspeedsData.AirSpeedMax += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingAirspeedsCruiseSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingAirspeedsData.CruiseSpeed += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingAirspeedsData.CruiseSpeed -= (float)1.0;
	} else {
		uavtalk_FixedWingAirspeedsData.CruiseSpeed += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingAirspeedsBestClimbRateSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingAirspeedsData.BestClimbRateSpeed += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingAirspeedsData.BestClimbRateSpeed -= (float)1.0;
	} else {
		uavtalk_FixedWingAirspeedsData.BestClimbRateSpeed += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingAirspeedsStallSpeedClean_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingAirspeedsData.StallSpeedClean += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingAirspeedsData.StallSpeedClean -= (float)1.0;
	} else {
		uavtalk_FixedWingAirspeedsData.StallSpeedClean += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingAirspeedsStallSpeedDirty_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingAirspeedsData.StallSpeedDirty += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingAirspeedsData.StallSpeedDirty -= (float)1.0;
	} else {
		uavtalk_FixedWingAirspeedsData.StallSpeedDirty += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingAirspeedsVerticalVelMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingAirspeedsData.VerticalVelMax += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingAirspeedsData.VerticalVelMax -= (float)1.0;
	} else {
		uavtalk_FixedWingAirspeedsData.VerticalVelMax += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCVerticalVelMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalVelMax += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalVelMax -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalVelMax += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCVectorFollowingGain_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VectorFollowingGain += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VectorFollowingGain -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.VectorFollowingGain += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCOrbitFollowingGain_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.OrbitFollowingGain += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.OrbitFollowingGain -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.OrbitFollowingGain += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCFollowerIntegralGain_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.FollowerIntegralGain += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.FollowerIntegralGain -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.FollowerIntegralGain += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCVerticalPosP_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalPosP += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalPosP -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalPosP += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCHeadingPI_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCHeadingPI_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCHeadingPI_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedPI_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedPI_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedPI_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCVerticalToPitchCrossFeed_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalToPitchCrossFeed.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalToPitchCrossFeed.Kp -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalToPitchCrossFeed.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCVerticalToPitchCrossFeed_Max_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalToPitchCrossFeed.Max += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalToPitchCrossFeed.Max -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.VerticalToPitchCrossFeed.Max += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedToVerticalCrossFeed_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedToVerticalCrossFeed.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedToVerticalCrossFeed.Kp -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedToVerticalCrossFeed.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedToVerticalCrossFeed_Max_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedToVerticalCrossFeed.Max += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedToVerticalCrossFeed.Max -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedToVerticalCrossFeed.Max += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCThrottlePI_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCThrottlePI_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCThrottlePI_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCRollLimit_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCRollLimit_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCRollLimit_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCPitchLimit_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCPitchLimit_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCPitchLimit_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCThrottleLimit_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCThrottleLimit_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCThrottleLimit_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsCCUpdatePeriod_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsCCData.UpdatePeriod += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsCCData.UpdatePeriod -= (int16_t)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsCCData.UpdatePeriod += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsHorizontalPosP_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.HorizontalPosP += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.HorizontalPosP -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.HorizontalPosP += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsVerticalPosP_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.VerticalPosP += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.VerticalPosP -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.VerticalPosP += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsBearingPI_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.BearingPI[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.BearingPI[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.BearingPI[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsBearingPI_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.BearingPI[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.BearingPI[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.BearingPI[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsBearingPI_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.BearingPI[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.BearingPI[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.BearingPI[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsPowerPI_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.PowerPI[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.PowerPI[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.PowerPI[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsPowerPI_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.PowerPI[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.PowerPI[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.PowerPI[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsPowerPI_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.PowerPI[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.PowerPI[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.PowerPI[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsVerticalToPitchCrossFeed_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.VerticalToPitchCrossFeed.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.VerticalToPitchCrossFeed.Kp -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.VerticalToPitchCrossFeed.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsVerticalToPitchCrossFeed_Max_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.VerticalToPitchCrossFeed.Max += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.VerticalToPitchCrossFeed.Max -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.VerticalToPitchCrossFeed.Max += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsAirspeedToVerticalCrossFeed_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.AirspeedToVerticalCrossFeed.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.AirspeedToVerticalCrossFeed.Kp -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.AirspeedToVerticalCrossFeed.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsAirspeedToVerticalCrossFeed_Max_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.AirspeedToVerticalCrossFeed.Max += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.AirspeedToVerticalCrossFeed.Max -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.AirspeedToVerticalCrossFeed.Max += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsSpeedPI_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsSpeedPI_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsSpeedPI_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsRollLimit_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.RollLimit[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.RollLimit[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.RollLimit[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsRollLimit_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.RollLimit[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.RollLimit[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.RollLimit[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsRollLimit_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.RollLimit[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.RollLimit[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.RollLimit[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsPitchLimit_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsPitchLimit_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsPitchLimit_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsThrottleLimit_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[0] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsThrottleLimit_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[1] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsThrottleLimit_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[2] -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsOrbitRadius_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.OrbitRadius += (float)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.OrbitRadius -= (float)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.OrbitRadius += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FixedWingPathFollowerSettingsUpdatePeriod_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FixedWingPathFollowerSettingsData.UpdatePeriod += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_FixedWingPathFollowerSettingsData.UpdatePeriod -= (int16_t)1.0;
	} else {
		uavtalk_FixedWingPathFollowerSettingsData.UpdatePeriod += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsCapacity_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.Capacity += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.Capacity -= (uint32_t)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.Capacity += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsVoltageThresholds_Warning_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.VoltageThresholds.Warning += (float)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.VoltageThresholds.Warning -= (float)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.VoltageThresholds.Warning += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsVoltageThresholds_Alarm_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.VoltageThresholds.Alarm += (float)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.VoltageThresholds.Alarm -= (float)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.VoltageThresholds.Alarm += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsSensorCalibrationFactor_Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.SensorCalibrationFactor.Voltage += (float)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.SensorCalibrationFactor.Voltage -= (float)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.SensorCalibrationFactor.Voltage += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsSensorCalibrationFactor_Current_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.SensorCalibrationFactor.Current += (float)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.SensorCalibrationFactor.Current -= (float)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.SensorCalibrationFactor.Current += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsSensorCalibrationOffset_Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.SensorCalibrationOffset.Voltage += (float)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.SensorCalibrationOffset.Voltage -= (float)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.SensorCalibrationOffset.Voltage += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsSensorCalibrationOffset_Current_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.SensorCalibrationOffset.Current += (float)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.SensorCalibrationOffset.Current -= (float)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.SensorCalibrationOffset.Current += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsCurrentPin_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.CurrentPin += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.CurrentPin -= (uint8_t)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.CurrentPin += (uint8_t)data;
	}
	if (uavtalk_FlightBatterySettingsData.CurrentPin >= FLIGHTBATTERYSETTINGS_CURRENTPIN_LASTITEM) {
		uavtalk_FlightBatterySettingsData.CurrentPin = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsVoltagePin_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.VoltagePin += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.VoltagePin -= (uint8_t)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.VoltagePin += (uint8_t)data;
	}
	if (uavtalk_FlightBatterySettingsData.VoltagePin >= FLIGHTBATTERYSETTINGS_VOLTAGEPIN_LASTITEM) {
		uavtalk_FlightBatterySettingsData.VoltagePin = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsType_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.Type += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.Type -= (uint8_t)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.Type += (uint8_t)data;
	}
	if (uavtalk_FlightBatterySettingsData.Type >= FLIGHTBATTERYSETTINGS_TYPE_LASTITEM) {
		uavtalk_FlightBatterySettingsData.Type = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsNbCells_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.NbCells += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.NbCells -= (uint8_t)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.NbCells += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsSensorType_BatteryCurrent_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.SensorType.BatteryCurrent += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.SensorType.BatteryCurrent -= (uint8_t)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.SensorType.BatteryCurrent += (uint8_t)data;
	}
	if (uavtalk_FlightBatterySettingsData.SensorType.BatteryCurrent >= FLIGHTBATTERYSETTINGS_SENSORTYPE_LASTITEM) {
		uavtalk_FlightBatterySettingsData.SensorType.BatteryCurrent = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_FlightBatterySettingsSensorType_BatteryVoltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightBatterySettingsData.SensorType.BatteryVoltage += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_FlightBatterySettingsData.SensorType.BatteryVoltage -= (uint8_t)1.0;
	} else {
		uavtalk_FlightBatterySettingsData.SensorType.BatteryVoltage += (uint8_t)data;
	}
	if (uavtalk_FlightBatterySettingsData.SensorType.BatteryVoltage >= FLIGHTBATTERYSETTINGS_SENSORTYPE_LASTITEM) {
		uavtalk_FlightBatterySettingsData.SensorType.BatteryVoltage = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_FlightPlanSettingsTest_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_FlightPlanSettingsData.Test += (float)1.0;
	} else if (button == 5) {
		uavtalk_FlightPlanSettingsData.Test -= (float)1.0;
	} else {
		uavtalk_FlightPlanSettingsData.Test += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GeoFenceSettingsWarningRadius_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GeoFenceSettingsData.WarningRadius += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_GeoFenceSettingsData.WarningRadius -= (uint16_t)1.0;
	} else {
		uavtalk_GeoFenceSettingsData.WarningRadius += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_GeoFenceSettingsErrorRadius_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GeoFenceSettingsData.ErrorRadius += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_GeoFenceSettingsData.ErrorRadius -= (uint16_t)1.0;
	} else {
		uavtalk_GeoFenceSettingsData.ErrorRadius += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsHorizontalPosPI_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.Kp -= (float)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsHorizontalPosPI_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.Ki -= (float)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsHorizontalPosPI_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.ILimit -= (float)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsHorizontalVelPID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Kp -= (float)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsHorizontalVelPID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Ki -= (float)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsHorizontalVelPID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Kd -= (float)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsHorizontalVelPID_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.ILimit -= (float)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsVelocityFeedforward_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.VelocityFeedforward += (float)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.VelocityFeedforward -= (float)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.VelocityFeedforward += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsMaxThrottle_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.MaxThrottle += (float)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.MaxThrottle -= (float)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.MaxThrottle += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsUpdatePeriod_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.UpdatePeriod += (int32_t)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.UpdatePeriod -= (int32_t)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.UpdatePeriod += (int32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsHorizontalVelMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelMax += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelMax -= (uint16_t)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.HorizontalVelMax += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsManualOverride_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.ManualOverride += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.ManualOverride -= (uint8_t)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.ManualOverride += (uint8_t)data;
	}
	if (uavtalk_GroundPathFollowerSettingsData.ManualOverride >= GROUNDPATHFOLLOWERSETTINGS_MANUALOVERRIDE_LASTITEM) {
		uavtalk_GroundPathFollowerSettingsData.ManualOverride = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsThrottleControl_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.ThrottleControl += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.ThrottleControl -= (uint8_t)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.ThrottleControl += (uint8_t)data;
	}
	if (uavtalk_GroundPathFollowerSettingsData.ThrottleControl >= GROUNDPATHFOLLOWERSETTINGS_THROTTLECONTROL_LASTITEM) {
		uavtalk_GroundPathFollowerSettingsData.ThrottleControl = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsVelocitySource_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.VelocitySource += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.VelocitySource -= (uint8_t)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.VelocitySource += (uint8_t)data;
	}
	if (uavtalk_GroundPathFollowerSettingsData.VelocitySource >= GROUNDPATHFOLLOWERSETTINGS_VELOCITYSOURCE_LASTITEM) {
		uavtalk_GroundPathFollowerSettingsData.VelocitySource = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsPositionSource_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.PositionSource += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.PositionSource -= (uint8_t)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.PositionSource += (uint8_t)data;
	}
	if (uavtalk_GroundPathFollowerSettingsData.PositionSource >= GROUNDPATHFOLLOWERSETTINGS_POSITIONSOURCE_LASTITEM) {
		uavtalk_GroundPathFollowerSettingsData.PositionSource = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_GroundPathFollowerSettingsEndpointRadius_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_GroundPathFollowerSettingsData.EndpointRadius += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_GroundPathFollowerSettingsData.EndpointRadius -= (uint8_t)1.0;
	} else {
		uavtalk_GroundPathFollowerSettingsData.EndpointRadius += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HomeLocationLatitude_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HomeLocationData.Latitude += (int32_t)1.0;
	} else if (button == 5) {
		uavtalk_HomeLocationData.Latitude -= (int32_t)1.0;
	} else {
		uavtalk_HomeLocationData.Latitude += (int32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HomeLocationLongitude_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HomeLocationData.Longitude += (int32_t)1.0;
	} else if (button == 5) {
		uavtalk_HomeLocationData.Longitude -= (int32_t)1.0;
	} else {
		uavtalk_HomeLocationData.Longitude += (int32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HomeLocationAltitude_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HomeLocationData.Altitude += (float)1.0;
	} else if (button == 5) {
		uavtalk_HomeLocationData.Altitude -= (float)1.0;
	} else {
		uavtalk_HomeLocationData.Altitude += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HomeLocationBe_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HomeLocationData.Be[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_HomeLocationData.Be[0] -= (float)1.0;
	} else {
		uavtalk_HomeLocationData.Be[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HomeLocationBe_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HomeLocationData.Be[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_HomeLocationData.Be[1] -= (float)1.0;
	} else {
		uavtalk_HomeLocationData.Be[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HomeLocationBe_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HomeLocationData.Be[2] += (float)1.0;
	} else if (button == 5) {
		uavtalk_HomeLocationData.Be[2] -= (float)1.0;
	} else {
		uavtalk_HomeLocationData.Be[2] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HomeLocationGroundTemperature_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HomeLocationData.GroundTemperature += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_HomeLocationData.GroundTemperature -= (int16_t)1.0;
	} else {
		uavtalk_HomeLocationData.GroundTemperature += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HomeLocationSeaLevelPressure_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HomeLocationData.SeaLevelPressure += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_HomeLocationData.SeaLevelPressure -= (uint16_t)1.0;
	} else {
		uavtalk_HomeLocationData.SeaLevelPressure += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HomeLocationSet_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HomeLocationData.Set += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HomeLocationData.Set -= (uint8_t)1.0;
	} else {
		uavtalk_HomeLocationData.Set += (uint8_t)data;
	}
	if (uavtalk_HomeLocationData.Set >= HOMELOCATION_SET_LASTITEM) {
		uavtalk_HomeLocationData.Set = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinSpeed += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinSpeed -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinSpeed += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxSpeed += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxSpeed -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxSpeed += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_NegDifference1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.NegDifference1 += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.NegDifference1 -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.NegDifference1 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_PosDifference1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.PosDifference1 += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.PosDifference1 -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.PosDifference1 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_NegDifference2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.NegDifference2 += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.NegDifference2 -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.NegDifference2 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_PosDifference2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.PosDifference2 += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.PosDifference2 -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.PosDifference2 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinHeight_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinHeight += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinHeight -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinHeight += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxHeight_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxHeight += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxHeight -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxHeight += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxDistance_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxDistance += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxDistance -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxDistance += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinPowerVoltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinPowerVoltage += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinPowerVoltage -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinPowerVoltage += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxPowerVoltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxPowerVoltage += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxPowerVoltage -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxPowerVoltage += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinSensor1Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinSensor1Voltage += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinSensor1Voltage -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinSensor1Voltage += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxSensor1Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxSensor1Voltage += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxSensor1Voltage -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxSensor1Voltage += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinSensor2Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinSensor2Voltage += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinSensor2Voltage -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinSensor2Voltage += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxSensor2Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxSensor2Voltage += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxSensor2Voltage -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxSensor2Voltage += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinCellVoltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinCellVoltage += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinCellVoltage -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinCellVoltage += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxCurrent_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxCurrent += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxCurrent -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxCurrent += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxUsedCapacity_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxUsedCapacity += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxUsedCapacity -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxUsedCapacity += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinSensor1Temp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinSensor1Temp += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinSensor1Temp -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinSensor1Temp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxSensor1Temp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxSensor1Temp += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxSensor1Temp -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxSensor1Temp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinSensor2Temp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinSensor2Temp += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinSensor2Temp -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinSensor2Temp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxSensor2Temp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxSensor2Temp += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxSensor2Temp -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxSensor2Temp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxServoTemp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxServoTemp += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxServoTemp -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxServoTemp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinRPM_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinRPM += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinRPM -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinRPM += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxRPM_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxRPM += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxRPM -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxRPM += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MinFuel_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MinFuel += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MinFuel -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MinFuel += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsLimit_MaxServoDifference_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Limit.MaxServoDifference += (float)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Limit.MaxServoDifference -= (float)1.0;
	} else {
		uavtalk_HoTTSettingsData.Limit.MaxServoDifference += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsSensor_VARIO_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Sensor.VARIO += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Sensor.VARIO -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Sensor.VARIO += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Sensor.VARIO >= HOTTSETTINGS_SENSOR_LASTITEM) {
		uavtalk_HoTTSettingsData.Sensor.VARIO = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsSensor_GPS_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Sensor.GPS += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Sensor.GPS -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Sensor.GPS += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Sensor.GPS >= HOTTSETTINGS_SENSOR_LASTITEM) {
		uavtalk_HoTTSettingsData.Sensor.GPS = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsSensor_EAM_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Sensor.EAM += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Sensor.EAM -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Sensor.EAM += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Sensor.EAM >= HOTTSETTINGS_SENSOR_LASTITEM) {
		uavtalk_HoTTSettingsData.Sensor.EAM = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsSensor_GAM_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Sensor.GAM += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Sensor.GAM -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Sensor.GAM += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Sensor.GAM >= HOTTSETTINGS_SENSOR_LASTITEM) {
		uavtalk_HoTTSettingsData.Sensor.GAM = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsSensor_ESC_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Sensor.ESC += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Sensor.ESC -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Sensor.ESC += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Sensor.ESC >= HOTTSETTINGS_SENSOR_LASTITEM) {
		uavtalk_HoTTSettingsData.Sensor.ESC = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_AltitudeBeep_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.AltitudeBeep += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.AltitudeBeep -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.AltitudeBeep += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.AltitudeBeep >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.AltitudeBeep = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinSpeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinSpeed -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinSpeed += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinSpeed >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinSpeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxSpeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxSpeed -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxSpeed += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxSpeed >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxSpeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_NegDifference1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.NegDifference1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.NegDifference1 -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.NegDifference1 += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.NegDifference1 >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.NegDifference1 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_PosDifference1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.PosDifference1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.PosDifference1 -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.PosDifference1 += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.PosDifference1 >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.PosDifference1 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_NegDifference2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.NegDifference2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.NegDifference2 -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.NegDifference2 += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.NegDifference2 >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.NegDifference2 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_PosDifference2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.PosDifference2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.PosDifference2 -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.PosDifference2 += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.PosDifference2 >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.PosDifference2 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinHeight_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinHeight += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinHeight -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinHeight += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinHeight >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinHeight = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxHeight_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxHeight += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxHeight -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxHeight += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxHeight >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxHeight = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxDistance_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxDistance += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxDistance -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxDistance += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxDistance >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxDistance = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinPowerVoltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinPowerVoltage += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinPowerVoltage -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinPowerVoltage += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinPowerVoltage >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinPowerVoltage = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxPowerVoltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxPowerVoltage += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxPowerVoltage -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxPowerVoltage += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxPowerVoltage >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxPowerVoltage = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinSensor1Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinSensor1Voltage += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinSensor1Voltage -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinSensor1Voltage += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinSensor1Voltage >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinSensor1Voltage = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxSensor1Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor1Voltage += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor1Voltage -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxSensor1Voltage += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxSensor1Voltage >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor1Voltage = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinSensor2Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinSensor2Voltage += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinSensor2Voltage -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinSensor2Voltage += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinSensor2Voltage >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinSensor2Voltage = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxSensor2Voltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor2Voltage += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor2Voltage -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxSensor2Voltage += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxSensor2Voltage >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor2Voltage = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinCellVoltage_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinCellVoltage += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinCellVoltage -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinCellVoltage += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinCellVoltage >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinCellVoltage = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxCurrent_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxCurrent += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxCurrent -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxCurrent += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxCurrent >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxCurrent = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxUsedCapacity_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxUsedCapacity += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxUsedCapacity -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxUsedCapacity += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxUsedCapacity >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxUsedCapacity = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinSensor1Temp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinSensor1Temp += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinSensor1Temp -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinSensor1Temp += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinSensor1Temp >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinSensor1Temp = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxSensor1Temp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor1Temp += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor1Temp -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxSensor1Temp += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxSensor1Temp >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor1Temp = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinSensor2Temp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinSensor2Temp += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinSensor2Temp -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinSensor2Temp += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinSensor2Temp >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinSensor2Temp = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxSensor2Temp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor2Temp += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor2Temp -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxSensor2Temp += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxSensor2Temp >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxSensor2Temp = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxServoTemp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxServoTemp += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxServoTemp -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxServoTemp += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxServoTemp >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxServoTemp = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinRPM_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinRPM += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinRPM -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinRPM += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinRPM >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinRPM = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxRPM_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxRPM += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxRPM -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxRPM += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxRPM >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxRPM = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MinFuel_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MinFuel += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MinFuel -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MinFuel += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MinFuel >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MinFuel = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HoTTSettingsWarning_MaxServoDifference_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HoTTSettingsData.Warning.MaxServoDifference += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HoTTSettingsData.Warning.MaxServoDifference -= (uint8_t)1.0;
	} else {
		uavtalk_HoTTSettingsData.Warning.MaxServoDifference += (uint8_t)data;
	}
	if (uavtalk_HoTTSettingsData.Warning.MaxServoDifference >= HOTTSETTINGS_WARNING_LASTITEM) {
		uavtalk_HoTTSettingsData.Warning.MaxServoDifference = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriFrame_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.Frame += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.Frame -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.Frame += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.Frame >= HWCOLIBRI_FRAME_LASTITEM) {
		uavtalk_HwColibriData.Frame = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriRcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.RcvrPort >= HWCOLIBRI_RCVRPORT_LASTITEM) {
		uavtalk_HwColibriData.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriUart1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.Uart1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.Uart1 -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.Uart1 += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.Uart1 >= HWCOLIBRI_UART1_LASTITEM) {
		uavtalk_HwColibriData.Uart1 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriUart2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.Uart2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.Uart2 -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.Uart2 += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.Uart2 >= HWCOLIBRI_UART2_LASTITEM) {
		uavtalk_HwColibriData.Uart2 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriUart3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.Uart3 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.Uart3 -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.Uart3 += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.Uart3 >= HWCOLIBRI_UART3_LASTITEM) {
		uavtalk_HwColibriData.Uart3 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriUart4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.Uart4 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.Uart4 -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.Uart4 += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.Uart4 >= HWCOLIBRI_UART4_LASTITEM) {
		uavtalk_HwColibriData.Uart4 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriUSB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.USB_HIDPort >= HWCOLIBRI_USB_HIDPORT_LASTITEM) {
		uavtalk_HwColibriData.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriUSB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.USB_VCPPort >= HWCOLIBRI_USB_VCPPORT_LASTITEM) {
		uavtalk_HwColibriData.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriDSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriGyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.GyroRange >= HWCOLIBRI_GYRORANGE_LASTITEM) {
		uavtalk_HwColibriData.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriAccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.AccelRange >= HWCOLIBRI_ACCELRANGE_LASTITEM) {
		uavtalk_HwColibriData.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriMPU6000Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.MPU6000Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.MPU6000Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.MPU6000Rate += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.MPU6000Rate >= HWCOLIBRI_MPU6000RATE_LASTITEM) {
		uavtalk_HwColibriData.MPU6000Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriMPU6000DLPF_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.MPU6000DLPF += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.MPU6000DLPF -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.MPU6000DLPF += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.MPU6000DLPF >= HWCOLIBRI_MPU6000DLPF_LASTITEM) {
		uavtalk_HwColibriData.MPU6000DLPF = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriMagnetometer_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.Magnetometer += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.Magnetometer -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.Magnetometer += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.Magnetometer >= HWCOLIBRI_MAGNETOMETER_LASTITEM) {
		uavtalk_HwColibriData.Magnetometer = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwColibriExtMagOrientation_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwColibriData.ExtMagOrientation += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwColibriData.ExtMagOrientation -= (uint8_t)1.0;
	} else {
		uavtalk_HwColibriData.ExtMagOrientation += (uint8_t)data;
	}
	if (uavtalk_HwColibriData.ExtMagOrientation >= HWCOLIBRI_EXTMAGORIENTATION_LASTITEM) {
		uavtalk_HwColibriData.ExtMagOrientation = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlRcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwCopterControlData.RcvrPort >= HWCOPTERCONTROL_RCVRPORT_LASTITEM) {
		uavtalk_HwCopterControlData.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlMainPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.MainPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.MainPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.MainPort += (uint8_t)data;
	}
	if (uavtalk_HwCopterControlData.MainPort >= HWCOPTERCONTROL_MAINPORT_LASTITEM) {
		uavtalk_HwCopterControlData.MainPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlFlexiPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.FlexiPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.FlexiPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.FlexiPort += (uint8_t)data;
	}
	if (uavtalk_HwCopterControlData.FlexiPort >= HWCOPTERCONTROL_FLEXIPORT_LASTITEM) {
		uavtalk_HwCopterControlData.FlexiPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlUSB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwCopterControlData.USB_HIDPort >= HWCOPTERCONTROL_USB_HIDPORT_LASTITEM) {
		uavtalk_HwCopterControlData.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlUSB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwCopterControlData.USB_VCPPort >= HWCOPTERCONTROL_USB_VCPPORT_LASTITEM) {
		uavtalk_HwCopterControlData.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlDSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlGyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwCopterControlData.GyroRange >= HWCOPTERCONTROL_GYRORANGE_LASTITEM) {
		uavtalk_HwCopterControlData.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlAccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwCopterControlData.AccelRange >= HWCOPTERCONTROL_ACCELRANGE_LASTITEM) {
		uavtalk_HwCopterControlData.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlMPU6000Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.MPU6000Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.MPU6000Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.MPU6000Rate += (uint8_t)data;
	}
	if (uavtalk_HwCopterControlData.MPU6000Rate >= HWCOPTERCONTROL_MPU6000RATE_LASTITEM) {
		uavtalk_HwCopterControlData.MPU6000Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwCopterControlMPU6000DLPF_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwCopterControlData.MPU6000DLPF += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwCopterControlData.MPU6000DLPF -= (uint8_t)1.0;
	} else {
		uavtalk_HwCopterControlData.MPU6000DLPF += (uint8_t)data;
	}
	if (uavtalk_HwCopterControlData.MPU6000DLPF >= HWCOPTERCONTROL_MPU6000DLPF_LASTITEM) {
		uavtalk_HwCopterControlData.MPU6000DLPF = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwDiscoveryF4MainPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwDiscoveryF4Data.MainPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwDiscoveryF4Data.MainPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwDiscoveryF4Data.MainPort += (uint8_t)data;
	}
	if (uavtalk_HwDiscoveryF4Data.MainPort >= HWDISCOVERYF4_MAINPORT_LASTITEM) {
		uavtalk_HwDiscoveryF4Data.MainPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwDiscoveryF4USB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwDiscoveryF4Data.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwDiscoveryF4Data.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwDiscoveryF4Data.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwDiscoveryF4Data.USB_HIDPort >= HWDISCOVERYF4_USB_HIDPORT_LASTITEM) {
		uavtalk_HwDiscoveryF4Data.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwDiscoveryF4USB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwDiscoveryF4Data.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwDiscoveryF4Data.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwDiscoveryF4Data.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwDiscoveryF4Data.USB_VCPPort >= HWDISCOVERYF4_USB_VCPPORT_LASTITEM) {
		uavtalk_HwDiscoveryF4Data.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3RcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.RcvrPort >= HWFLYINGF3_RCVRPORT_LASTITEM) {
		uavtalk_HwFlyingF3Data.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3Uart1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.Uart1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.Uart1 -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.Uart1 += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.Uart1 >= HWFLYINGF3_UART1_LASTITEM) {
		uavtalk_HwFlyingF3Data.Uart1 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3Uart2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.Uart2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.Uart2 -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.Uart2 += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.Uart2 >= HWFLYINGF3_UART2_LASTITEM) {
		uavtalk_HwFlyingF3Data.Uart2 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3Uart3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.Uart3 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.Uart3 -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.Uart3 += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.Uart3 >= HWFLYINGF3_UART3_LASTITEM) {
		uavtalk_HwFlyingF3Data.Uart3 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3Uart4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.Uart4 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.Uart4 -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.Uart4 += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.Uart4 >= HWFLYINGF3_UART4_LASTITEM) {
		uavtalk_HwFlyingF3Data.Uart4 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3Uart5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.Uart5 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.Uart5 -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.Uart5 += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.Uart5 >= HWFLYINGF3_UART5_LASTITEM) {
		uavtalk_HwFlyingF3Data.Uart5 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3USB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.USB_HIDPort >= HWFLYINGF3_USB_HIDPORT_LASTITEM) {
		uavtalk_HwFlyingF3Data.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3USB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.USB_VCPPort >= HWFLYINGF3_USB_VCPPORT_LASTITEM) {
		uavtalk_HwFlyingF3Data.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3DSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3GyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.GyroRange >= HWFLYINGF3_GYRORANGE_LASTITEM) {
		uavtalk_HwFlyingF3Data.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3L3GD20Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.L3GD20Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.L3GD20Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.L3GD20Rate += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.L3GD20Rate >= HWFLYINGF3_L3GD20RATE_LASTITEM) {
		uavtalk_HwFlyingF3Data.L3GD20Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3AccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.AccelRange >= HWFLYINGF3_ACCELRANGE_LASTITEM) {
		uavtalk_HwFlyingF3Data.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF3Shield_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF3Data.Shield += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF3Data.Shield -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF3Data.Shield += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF3Data.Shield >= HWFLYINGF3_SHIELD_LASTITEM) {
		uavtalk_HwFlyingF3Data.Shield = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4RcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.RcvrPort >= HWFLYINGF4_RCVRPORT_LASTITEM) {
		uavtalk_HwFlyingF4Data.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4Uart1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.Uart1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.Uart1 -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.Uart1 += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.Uart1 >= HWFLYINGF4_UART1_LASTITEM) {
		uavtalk_HwFlyingF4Data.Uart1 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4Uart2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.Uart2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.Uart2 -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.Uart2 += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.Uart2 >= HWFLYINGF4_UART2_LASTITEM) {
		uavtalk_HwFlyingF4Data.Uart2 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4Uart3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.Uart3 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.Uart3 -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.Uart3 += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.Uart3 >= HWFLYINGF4_UART3_LASTITEM) {
		uavtalk_HwFlyingF4Data.Uart3 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4USB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.USB_HIDPort >= HWFLYINGF4_USB_HIDPORT_LASTITEM) {
		uavtalk_HwFlyingF4Data.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4USB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.USB_VCPPort >= HWFLYINGF4_USB_VCPPORT_LASTITEM) {
		uavtalk_HwFlyingF4Data.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4DSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4GyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.GyroRange >= HWFLYINGF4_GYRORANGE_LASTITEM) {
		uavtalk_HwFlyingF4Data.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4AccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.AccelRange >= HWFLYINGF4_ACCELRANGE_LASTITEM) {
		uavtalk_HwFlyingF4Data.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4MPU6050Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.MPU6050Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.MPU6050Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.MPU6050Rate += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.MPU6050Rate >= HWFLYINGF4_MPU6050RATE_LASTITEM) {
		uavtalk_HwFlyingF4Data.MPU6050Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4MPU6050DLPF_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.MPU6050DLPF += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.MPU6050DLPF -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.MPU6050DLPF += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.MPU6050DLPF >= HWFLYINGF4_MPU6050DLPF_LASTITEM) {
		uavtalk_HwFlyingF4Data.MPU6050DLPF = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4Magnetometer_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.Magnetometer += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.Magnetometer -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.Magnetometer += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.Magnetometer >= HWFLYINGF4_MAGNETOMETER_LASTITEM) {
		uavtalk_HwFlyingF4Data.Magnetometer = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFlyingF4ExtMagOrientation_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFlyingF4Data.ExtMagOrientation += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFlyingF4Data.ExtMagOrientation -= (uint8_t)1.0;
	} else {
		uavtalk_HwFlyingF4Data.ExtMagOrientation += (uint8_t)data;
	}
	if (uavtalk_HwFlyingF4Data.ExtMagOrientation >= HWFLYINGF4_EXTMAGORIENTATION_LASTITEM) {
		uavtalk_HwFlyingF4Data.ExtMagOrientation = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomOutput_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.Output += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.Output -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.Output += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.Output >= HWFREEDOM_OUTPUT_LASTITEM) {
		uavtalk_HwFreedomData.Output = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomMainPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.MainPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.MainPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.MainPort += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.MainPort >= HWFREEDOM_MAINPORT_LASTITEM) {
		uavtalk_HwFreedomData.MainPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomFlexiPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.FlexiPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.FlexiPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.FlexiPort += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.FlexiPort >= HWFREEDOM_FLEXIPORT_LASTITEM) {
		uavtalk_HwFreedomData.FlexiPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomRcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.RcvrPort >= HWFREEDOM_RCVRPORT_LASTITEM) {
		uavtalk_HwFreedomData.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomRadioPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.RadioPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.RadioPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.RadioPort += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.RadioPort >= HWFREEDOM_RADIOPORT_LASTITEM) {
		uavtalk_HwFreedomData.RadioPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomUSB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.USB_HIDPort >= HWFREEDOM_USB_HIDPORT_LASTITEM) {
		uavtalk_HwFreedomData.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomUSB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.USB_VCPPort >= HWFREEDOM_USB_VCPPORT_LASTITEM) {
		uavtalk_HwFreedomData.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomDSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomGyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.GyroRange >= HWFREEDOM_GYRORANGE_LASTITEM) {
		uavtalk_HwFreedomData.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomAccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.AccelRange >= HWFREEDOM_ACCELRANGE_LASTITEM) {
		uavtalk_HwFreedomData.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomMPU6000Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.MPU6000Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.MPU6000Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.MPU6000Rate += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.MPU6000Rate >= HWFREEDOM_MPU6000RATE_LASTITEM) {
		uavtalk_HwFreedomData.MPU6000Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwFreedomMPU6000DLPF_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwFreedomData.MPU6000DLPF += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwFreedomData.MPU6000DLPF -= (uint8_t)1.0;
	} else {
		uavtalk_HwFreedomData.MPU6000DLPF += (uint8_t)data;
	}
	if (uavtalk_HwFreedomData.MPU6000DLPF >= HWFREEDOM_MPU6000DLPF_LASTITEM) {
		uavtalk_HwFreedomData.MPU6000DLPF = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonRcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.RcvrPort >= HWQUANTON_RCVRPORT_LASTITEM) {
		uavtalk_HwQuantonData.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonUart1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.Uart1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.Uart1 -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.Uart1 += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.Uart1 >= HWQUANTON_UART1_LASTITEM) {
		uavtalk_HwQuantonData.Uart1 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonUart2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.Uart2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.Uart2 -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.Uart2 += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.Uart2 >= HWQUANTON_UART2_LASTITEM) {
		uavtalk_HwQuantonData.Uart2 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonUart3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.Uart3 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.Uart3 -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.Uart3 += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.Uart3 >= HWQUANTON_UART3_LASTITEM) {
		uavtalk_HwQuantonData.Uart3 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonUart4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.Uart4 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.Uart4 -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.Uart4 += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.Uart4 >= HWQUANTON_UART4_LASTITEM) {
		uavtalk_HwQuantonData.Uart4 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonUart5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.Uart5 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.Uart5 -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.Uart5 += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.Uart5 >= HWQUANTON_UART5_LASTITEM) {
		uavtalk_HwQuantonData.Uart5 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonUSB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.USB_HIDPort >= HWQUANTON_USB_HIDPORT_LASTITEM) {
		uavtalk_HwQuantonData.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonUSB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.USB_VCPPort >= HWQUANTON_USB_VCPPORT_LASTITEM) {
		uavtalk_HwQuantonData.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonDSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonGyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.GyroRange >= HWQUANTON_GYRORANGE_LASTITEM) {
		uavtalk_HwQuantonData.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonAccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.AccelRange >= HWQUANTON_ACCELRANGE_LASTITEM) {
		uavtalk_HwQuantonData.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonMPU6000Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.MPU6000Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.MPU6000Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.MPU6000Rate += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.MPU6000Rate >= HWQUANTON_MPU6000RATE_LASTITEM) {
		uavtalk_HwQuantonData.MPU6000Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonMPU6000DLPF_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.MPU6000DLPF += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.MPU6000DLPF -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.MPU6000DLPF += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.MPU6000DLPF >= HWQUANTON_MPU6000DLPF_LASTITEM) {
		uavtalk_HwQuantonData.MPU6000DLPF = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonMagnetometer_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.Magnetometer += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.Magnetometer -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.Magnetometer += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.Magnetometer >= HWQUANTON_MAGNETOMETER_LASTITEM) {
		uavtalk_HwQuantonData.Magnetometer = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwQuantonExtMagOrientation_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwQuantonData.ExtMagOrientation += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwQuantonData.ExtMagOrientation -= (uint8_t)1.0;
	} else {
		uavtalk_HwQuantonData.ExtMagOrientation += (uint8_t)data;
	}
	if (uavtalk_HwQuantonData.ExtMagOrientation >= HWQUANTON_EXTMAGORIENTATION_LASTITEM) {
		uavtalk_HwQuantonData.ExtMagOrientation = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionRcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.RcvrPort >= HWREVOLUTION_RCVRPORT_LASTITEM) {
		uavtalk_HwRevolutionData.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionAuxPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.AuxPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.AuxPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.AuxPort += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.AuxPort >= HWREVOLUTION_AUXPORT_LASTITEM) {
		uavtalk_HwRevolutionData.AuxPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionAuxSBusPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.AuxSBusPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.AuxSBusPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.AuxSBusPort += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.AuxSBusPort >= HWREVOLUTION_AUXSBUSPORT_LASTITEM) {
		uavtalk_HwRevolutionData.AuxSBusPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionFlexiPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.FlexiPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.FlexiPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.FlexiPort += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.FlexiPort >= HWREVOLUTION_FLEXIPORT_LASTITEM) {
		uavtalk_HwRevolutionData.FlexiPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionTelemetryPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.TelemetryPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.TelemetryPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.TelemetryPort += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.TelemetryPort >= HWREVOLUTION_TELEMETRYPORT_LASTITEM) {
		uavtalk_HwRevolutionData.TelemetryPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionGPSPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.GPSPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.GPSPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.GPSPort += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.GPSPort >= HWREVOLUTION_GPSPORT_LASTITEM) {
		uavtalk_HwRevolutionData.GPSPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionUSB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.USB_HIDPort >= HWREVOLUTION_USB_HIDPORT_LASTITEM) {
		uavtalk_HwRevolutionData.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionUSB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.USB_VCPPort >= HWREVOLUTION_USB_VCPPORT_LASTITEM) {
		uavtalk_HwRevolutionData.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionDSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionGyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.GyroRange >= HWREVOLUTION_GYRORANGE_LASTITEM) {
		uavtalk_HwRevolutionData.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionAccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.AccelRange >= HWREVOLUTION_ACCELRANGE_LASTITEM) {
		uavtalk_HwRevolutionData.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionMPU6000Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.MPU6000Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.MPU6000Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.MPU6000Rate += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.MPU6000Rate >= HWREVOLUTION_MPU6000RATE_LASTITEM) {
		uavtalk_HwRevolutionData.MPU6000Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevolutionMPU6000DLPF_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevolutionData.MPU6000DLPF += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevolutionData.MPU6000DLPF -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevolutionData.MPU6000DLPF += (uint8_t)data;
	}
	if (uavtalk_HwRevolutionData.MPU6000DLPF >= HWREVOLUTION_MPU6000DLPF_LASTITEM) {
		uavtalk_HwRevolutionData.MPU6000DLPF = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniRcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.RcvrPort >= HWREVOMINI_RCVRPORT_LASTITEM) {
		uavtalk_HwRevoMiniData.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniMainPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.MainPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.MainPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.MainPort += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.MainPort >= HWREVOMINI_MAINPORT_LASTITEM) {
		uavtalk_HwRevoMiniData.MainPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniFlexiPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.FlexiPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.FlexiPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.FlexiPort += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.FlexiPort >= HWREVOMINI_FLEXIPORT_LASTITEM) {
		uavtalk_HwRevoMiniData.FlexiPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniRadioPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.RadioPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.RadioPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.RadioPort += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.RadioPort >= HWREVOMINI_RADIOPORT_LASTITEM) {
		uavtalk_HwRevoMiniData.RadioPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniUSB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.USB_HIDPort >= HWREVOMINI_USB_HIDPORT_LASTITEM) {
		uavtalk_HwRevoMiniData.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniUSB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.USB_VCPPort >= HWREVOMINI_USB_VCPPORT_LASTITEM) {
		uavtalk_HwRevoMiniData.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniDSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniGyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.GyroRange >= HWREVOMINI_GYRORANGE_LASTITEM) {
		uavtalk_HwRevoMiniData.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniAccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.AccelRange >= HWREVOMINI_ACCELRANGE_LASTITEM) {
		uavtalk_HwRevoMiniData.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniMPU6000Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.MPU6000Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.MPU6000Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.MPU6000Rate += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.MPU6000Rate >= HWREVOMINI_MPU6000RATE_LASTITEM) {
		uavtalk_HwRevoMiniData.MPU6000Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwRevoMiniMPU6000DLPF_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwRevoMiniData.MPU6000DLPF += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwRevoMiniData.MPU6000DLPF -= (uint8_t)1.0;
	} else {
		uavtalk_HwRevoMiniData.MPU6000DLPF += (uint8_t)data;
	}
	if (uavtalk_HwRevoMiniData.MPU6000DLPF >= HWREVOMINI_MPU6000DLPF_LASTITEM) {
		uavtalk_HwRevoMiniData.MPU6000DLPF = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyBGCRcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyBGCData.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyBGCData.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyBGCData.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyBGCData.RcvrPort >= HWSPARKYBGC_RCVRPORT_LASTITEM) {
		uavtalk_HwSparkyBGCData.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyBGCFlexiPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyBGCData.FlexiPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyBGCData.FlexiPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyBGCData.FlexiPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyBGCData.FlexiPort >= HWSPARKYBGC_FLEXIPORT_LASTITEM) {
		uavtalk_HwSparkyBGCData.FlexiPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyBGCUSB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyBGCData.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyBGCData.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyBGCData.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyBGCData.USB_HIDPort >= HWSPARKYBGC_USB_HIDPORT_LASTITEM) {
		uavtalk_HwSparkyBGCData.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyBGCUSB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyBGCData.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyBGCData.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyBGCData.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyBGCData.USB_VCPPort >= HWSPARKYBGC_USB_VCPPORT_LASTITEM) {
		uavtalk_HwSparkyBGCData.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyBGCDSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyBGCData.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyBGCData.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyBGCData.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyBGCGyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyBGCData.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyBGCData.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyBGCData.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwSparkyBGCData.GyroRange >= HWSPARKYBGC_GYRORANGE_LASTITEM) {
		uavtalk_HwSparkyBGCData.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyBGCAccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyBGCData.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyBGCData.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyBGCData.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwSparkyBGCData.AccelRange >= HWSPARKYBGC_ACCELRANGE_LASTITEM) {
		uavtalk_HwSparkyBGCData.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyBGCMPU9150DLPF_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyBGCData.MPU9150DLPF += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyBGCData.MPU9150DLPF -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyBGCData.MPU9150DLPF += (uint8_t)data;
	}
	if (uavtalk_HwSparkyBGCData.MPU9150DLPF >= HWSPARKYBGC_MPU9150DLPF_LASTITEM) {
		uavtalk_HwSparkyBGCData.MPU9150DLPF = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyBGCMPU9150Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyBGCData.MPU9150Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyBGCData.MPU9150Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyBGCData.MPU9150Rate += (uint8_t)data;
	}
	if (uavtalk_HwSparkyBGCData.MPU9150Rate >= HWSPARKYBGC_MPU9150RATE_LASTITEM) {
		uavtalk_HwSparkyBGCData.MPU9150Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyRcvrPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.RcvrPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.RcvrPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.RcvrPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.RcvrPort >= HWSPARKY_RCVRPORT_LASTITEM) {
		uavtalk_HwSparkyData.RcvrPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyFlexiPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.FlexiPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.FlexiPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.FlexiPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.FlexiPort >= HWSPARKY_FLEXIPORT_LASTITEM) {
		uavtalk_HwSparkyData.FlexiPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyMainPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.MainPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.MainPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.MainPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.MainPort >= HWSPARKY_MAINPORT_LASTITEM) {
		uavtalk_HwSparkyData.MainPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyOutPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.OutPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.OutPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.OutPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.OutPort >= HWSPARKY_OUTPORT_LASTITEM) {
		uavtalk_HwSparkyData.OutPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyUSB_HIDPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.USB_HIDPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.USB_HIDPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.USB_HIDPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.USB_HIDPort >= HWSPARKY_USB_HIDPORT_LASTITEM) {
		uavtalk_HwSparkyData.USB_HIDPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyUSB_VCPPort_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.USB_VCPPort += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.USB_VCPPort -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.USB_VCPPort += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.USB_VCPPort >= HWSPARKY_USB_VCPPORT_LASTITEM) {
		uavtalk_HwSparkyData.USB_VCPPort = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyDSMxBind_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.DSMxBind += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.DSMxBind -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.DSMxBind += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyGyroRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.GyroRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.GyroRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.GyroRange += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.GyroRange >= HWSPARKY_GYRORANGE_LASTITEM) {
		uavtalk_HwSparkyData.GyroRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyAccelRange_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.AccelRange += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.AccelRange -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.AccelRange += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.AccelRange >= HWSPARKY_ACCELRANGE_LASTITEM) {
		uavtalk_HwSparkyData.AccelRange = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyMPU9150DLPF_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.MPU9150DLPF += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.MPU9150DLPF -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.MPU9150DLPF += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.MPU9150DLPF >= HWSPARKY_MPU9150DLPF_LASTITEM) {
		uavtalk_HwSparkyData.MPU9150DLPF = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_HwSparkyMPU9150Rate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_HwSparkyData.MPU9150Rate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_HwSparkyData.MPU9150Rate -= (uint8_t)1.0;
	} else {
		uavtalk_HwSparkyData.MPU9150Rate += (uint8_t)data;
	}
	if (uavtalk_HwSparkyData.MPU9150Rate >= HWSPARKY_MPU9150RATE_LASTITEM) {
		uavtalk_HwSparkyData.MPU9150Rate = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[0] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[0] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[0] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[1] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[1] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[1] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[2] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[2] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[2] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[3] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[3] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[3] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[4] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[4] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[4] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[5] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[5] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[5] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_6_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[6] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[6] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[6] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_7_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[7] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[7] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[7] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_8_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[8] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[8] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[8] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_9_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[9] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[9] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[9] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_10_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[10] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[10] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[10] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_11_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[11] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[11] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[11] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_12_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[12] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[12] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[12] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_13_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[13] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[13] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[13] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_14_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[14] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[14] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[14] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_15_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[15] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[15] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[15] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_16_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[16] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[16] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[16] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_17_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[17] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[17] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[17] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_18_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[18] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[18] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[18] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_I2CVMUserProgramProgram_19_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_I2CVMUserProgramData.Program[19] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_I2CVMUserProgramData.Program[19] -= (uint32_t)1.0;
	} else {
		uavtalk_I2CVMUserProgramData.Program[19] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsaccel_var_X_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.accel_var.X += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.accel_var.X -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.accel_var.X += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsaccel_var_Y_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.accel_var.Y += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.accel_var.Y -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.accel_var.Y += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsaccel_var_Z_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.accel_var.Z += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.accel_var.Z -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.accel_var.Z += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsgyro_var_X_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.gyro_var.X += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.gyro_var.X -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.gyro_var.X += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsgyro_var_Y_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.gyro_var.Y += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.gyro_var.Y -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.gyro_var.Y += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsgyro_var_Z_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.gyro_var.Z += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.gyro_var.Z -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.gyro_var.Z += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsmag_var_X_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.mag_var.X += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.mag_var.X -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.mag_var.X += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsmag_var_Y_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.mag_var.Y += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.mag_var.Y -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.mag_var.Y += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsmag_var_Z_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.mag_var.Z += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.mag_var.Z -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.mag_var.Z += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsgps_var_Pos_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.gps_var.Pos += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.gps_var.Pos -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.gps_var.Pos += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsgps_var_Vel_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.gps_var.Vel += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.gps_var.Vel -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.gps_var.Vel += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsgps_var_VertPos_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.gps_var.VertPos += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.gps_var.VertPos -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.gps_var.VertPos += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsbaro_var_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.baro_var += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.baro_var -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.baro_var += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsMagBiasNullingRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.MagBiasNullingRate += (float)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.MagBiasNullingRate -= (float)1.0;
	} else {
		uavtalk_INSSettingsData.MagBiasNullingRate += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_INSSettingsComputeGyroBias_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_INSSettingsData.ComputeGyroBias += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_INSSettingsData.ComputeGyroBias -= (uint8_t)1.0;
	} else {
		uavtalk_INSSettingsData.ComputeGyroBias += (uint8_t)data;
	}
	if (uavtalk_INSSettingsData.ComputeGyroBias >= INSSETTINGS_COMPUTEGYROBIAS_LASTITEM) {
		uavtalk_INSSettingsData.ComputeGyroBias = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_LoggingSettingsLogBehavior_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_LoggingSettingsData.LogBehavior += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_LoggingSettingsData.LogBehavior -= (uint8_t)1.0;
	} else {
		uavtalk_LoggingSettingsData.LogBehavior += (uint8_t)data;
	}
	if (uavtalk_LoggingSettingsData.LogBehavior >= LOGGINGSETTINGS_LOGBEHAVIOR_LASTITEM) {
		uavtalk_LoggingSettingsData.LogBehavior = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsDeadband_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Deadband += (float)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Deadband -= (float)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Deadband += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsRssiMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.RssiMax += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.RssiMax -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.RssiMax += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsRssiMin_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.RssiMin += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.RssiMin -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.RssiMin += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsRssiPwmPeriod_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.RssiPwmPeriod += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.RssiPwmPeriod -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.RssiPwmPeriod += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_Throttle_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.Throttle += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.Throttle -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.Throttle += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.Roll += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.Roll -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.Roll += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.Pitch += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.Pitch -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.Pitch += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.Yaw += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.Yaw -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.Yaw += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_FlightMode_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.FlightMode += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.FlightMode -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.FlightMode += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_Collective_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.Collective += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.Collective -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.Collective += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_Accessory0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.Accessory0 += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.Accessory0 -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.Accessory0 += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_Accessory1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.Accessory1 += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.Accessory1 -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.Accessory1 += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_Accessory2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.Accessory2 += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.Accessory2 -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.Accessory2 += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMin_Arming_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMin.Arming += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMin.Arming -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMin.Arming += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_Throttle_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Throttle += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Throttle -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Throttle += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Roll += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Roll -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Roll += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Pitch += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Pitch -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Pitch += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Yaw += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Yaw -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Yaw += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_FlightMode_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.FlightMode += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.FlightMode -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.FlightMode += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_Collective_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Collective += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Collective -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Collective += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_Accessory0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory0 += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory0 -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory0 += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_Accessory1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory1 += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory1 -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory1 += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_Accessory2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory2 += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory2 -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory2 += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNeutral_Arming_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Arming += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Arming -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNeutral.Arming += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_Throttle_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.Throttle += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.Throttle -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.Throttle += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.Roll += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.Roll -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.Roll += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.Pitch += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.Pitch -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.Pitch += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.Yaw += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.Yaw -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.Yaw += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_FlightMode_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.FlightMode += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.FlightMode -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.FlightMode += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_Collective_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.Collective += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.Collective -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.Collective += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_Accessory0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.Accessory0 += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.Accessory0 -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.Accessory0 += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_Accessory1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.Accessory1 += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.Accessory1 -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.Accessory1 += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_Accessory2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.Accessory2 += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.Accessory2 -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.Accessory2 += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelMax_Arming_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelMax.Arming += (int16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelMax.Arming -= (int16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelMax.Arming += (int16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsArmedTimeout_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ArmedTimeout += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ArmedTimeout -= (uint16_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ArmedTimeout += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_Throttle_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Throttle += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Throttle -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.Throttle += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.Throttle >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Throttle = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.Roll += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.Roll >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Roll = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.Pitch += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.Pitch >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Pitch = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.Yaw += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.Yaw >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Yaw = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_FlightMode_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.FlightMode += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.FlightMode -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.FlightMode += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.FlightMode >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.FlightMode = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_Collective_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Collective += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Collective -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.Collective += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.Collective >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Collective = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_Accessory0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory0 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory0 -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory0 += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.Accessory0 >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory0 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_Accessory1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory1 -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory1 += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.Accessory1 >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory1 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_Accessory2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory2 -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory2 += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.Accessory2 >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Accessory2 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelGroups_Arming_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Arming += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Arming -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelGroups.Arming += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.ChannelGroups.Arming >= MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM) {
		uavtalk_ManualControlSettingsData.ChannelGroups.Arming = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsRssiType_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.RssiType += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.RssiType -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.RssiType += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.RssiType >= MANUALCONTROLSETTINGS_RSSITYPE_LASTITEM) {
		uavtalk_ManualControlSettingsData.RssiType = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsRssiChannelNumber_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.RssiChannelNumber += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.RssiChannelNumber -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.RssiChannelNumber += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_Throttle_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Throttle += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Throttle -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.Throttle += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.Roll += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.Pitch += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.Yaw += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_FlightMode_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.FlightMode += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.FlightMode -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.FlightMode += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_Collective_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Collective += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Collective -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.Collective += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_Accessory0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Accessory0 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Accessory0 -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.Accessory0 += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_Accessory1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Accessory1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Accessory1 -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.Accessory1 += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_Accessory2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Accessory2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Accessory2 -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.Accessory2 += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsChannelNumber_Arming_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Arming += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.ChannelNumber.Arming -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.ChannelNumber.Arming += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsArming_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Arming += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Arming -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Arming += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Arming >= MANUALCONTROLSETTINGS_ARMING_LASTITEM) {
		uavtalk_ManualControlSettingsData.Arming = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsStabilization1Settings_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Roll += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Stabilization1Settings.Roll >= MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_LASTITEM) {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Roll = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsStabilization1Settings_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Pitch += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Stabilization1Settings.Pitch >= MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_LASTITEM) {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Pitch = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsStabilization1Settings_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Yaw += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Stabilization1Settings.Yaw >= MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_LASTITEM) {
		uavtalk_ManualControlSettingsData.Stabilization1Settings.Yaw = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsStabilization2Settings_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Roll += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Stabilization2Settings.Roll >= MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_LASTITEM) {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Roll = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsStabilization2Settings_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Pitch += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Stabilization2Settings.Pitch >= MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_LASTITEM) {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Pitch = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsStabilization2Settings_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Yaw += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Stabilization2Settings.Yaw >= MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_LASTITEM) {
		uavtalk_ManualControlSettingsData.Stabilization2Settings.Yaw = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsStabilization3Settings_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Roll += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Stabilization3Settings.Roll >= MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_LASTITEM) {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Roll = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsStabilization3Settings_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Pitch += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Stabilization3Settings.Pitch >= MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_LASTITEM) {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Pitch = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsStabilization3Settings_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Yaw += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.Stabilization3Settings.Yaw >= MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_LASTITEM) {
		uavtalk_ManualControlSettingsData.Stabilization3Settings.Yaw = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsFlightModeNumber_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.FlightModeNumber += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.FlightModeNumber -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.FlightModeNumber += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsFlightModePosition_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.FlightModePosition[0] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.FlightModePosition[0] -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.FlightModePosition[0] += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.FlightModePosition[0] >= MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_LASTITEM) {
		uavtalk_ManualControlSettingsData.FlightModePosition[0] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsFlightModePosition_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.FlightModePosition[1] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.FlightModePosition[1] -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.FlightModePosition[1] += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.FlightModePosition[1] >= MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_LASTITEM) {
		uavtalk_ManualControlSettingsData.FlightModePosition[1] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsFlightModePosition_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.FlightModePosition[2] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.FlightModePosition[2] -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.FlightModePosition[2] += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.FlightModePosition[2] >= MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_LASTITEM) {
		uavtalk_ManualControlSettingsData.FlightModePosition[2] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsFlightModePosition_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.FlightModePosition[3] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.FlightModePosition[3] -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.FlightModePosition[3] += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.FlightModePosition[3] >= MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_LASTITEM) {
		uavtalk_ManualControlSettingsData.FlightModePosition[3] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsFlightModePosition_4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.FlightModePosition[4] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.FlightModePosition[4] -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.FlightModePosition[4] += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.FlightModePosition[4] >= MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_LASTITEM) {
		uavtalk_ManualControlSettingsData.FlightModePosition[4] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ManualControlSettingsFlightModePosition_5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ManualControlSettingsData.FlightModePosition[5] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ManualControlSettingsData.FlightModePosition[5] -= (uint8_t)1.0;
	} else {
		uavtalk_ManualControlSettingsData.FlightModePosition[5] += (uint8_t)data;
	}
	if (uavtalk_ManualControlSettingsData.FlightModePosition[5] >= MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_LASTITEM) {
		uavtalk_ManualControlSettingsData.FlightModePosition[5] = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsMaxAccel_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.MaxAccel += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.MaxAccel -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.MaxAccel += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsFeedForward_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.FeedForward += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.FeedForward -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.FeedForward += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsAccelTime_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.AccelTime += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.AccelTime -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.AccelTime += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsDecelTime_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.DecelTime += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.DecelTime -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.DecelTime += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve1_n_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve1.n += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve1_n2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n2 += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n2 -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve1.n2 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve1_n5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n5 += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n5 -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve1.n5 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve1_n7_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n7 += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n7 -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve1.n7 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve1_n1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n1 += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve1.n1 -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve1.n1 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve2_n_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve2.n += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve2_n2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n2 += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n2 -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve2.n2 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve2_n5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n5 += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n5 -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve2.n5 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve2_n7_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n7 += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n7 -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve2.n7 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsThrottleCurve2_n1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n1 += (float)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.ThrottleCurve2.n1 -= (float)1.0;
	} else {
		uavtalk_MixerSettingsData.ThrottleCurve2.n1 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsCurve2Source_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.Curve2Source += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.Curve2Source -= (uint8_t)1.0;
	} else {
		uavtalk_MixerSettingsData.Curve2Source += (uint8_t)data;
	}
	if (uavtalk_MixerSettingsData.Curve2Source >= MIXERSETTINGS_CURVE2SOURCE_LASTITEM) {
		uavtalk_MixerSettingsData.Curve2Source = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsMixer1Type_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.Mixer1Type += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.Mixer1Type -= (uint8_t)1.0;
	} else {
		uavtalk_MixerSettingsData.Mixer1Type += (uint8_t)data;
	}
	if (uavtalk_MixerSettingsData.Mixer1Type >= MIXERSETTINGS_MIXER1TYPE_LASTITEM) {
		uavtalk_MixerSettingsData.Mixer1Type = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsMixer1Vector_ThrottleCurve1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.Mixer1Vector.ThrottleCurve1 += (int8_t)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.Mixer1Vector.ThrottleCurve1 -= (int8_t)1.0;
	} else {
		uavtalk_MixerSettingsData.Mixer1Vector.ThrottleCurve1 += (int8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsMixer1Vector_ThrottleCurve2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.Mixer1Vector.ThrottleCurve2 += (int8_t)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.Mixer1Vector.ThrottleCurve2 -= (int8_t)1.0;
	} else {
		uavtalk_MixerSettingsData.Mixer1Vector.ThrottleCurve2 += (int8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsMixer1Vector_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.Mixer1Vector.Roll += (int8_t)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.Mixer1Vector.Roll -= (int8_t)1.0;
	} else {
		uavtalk_MixerSettingsData.Mixer1Vector.Roll += (int8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsMixer1Vector_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.Mixer1Vector.Pitch += (int8_t)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.Mixer1Vector.Pitch -= (int8_t)1.0;
	} else {
		uavtalk_MixerSettingsData.Mixer1Vector.Pitch += (int8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_MixerSettingsMixer1Vector_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MixerSettingsData.Mixer1Vector.Yaw += (int8_t)1.0;
	} else if (button == 5) {
		uavtalk_MixerSettingsData.Mixer1Vector.Yaw -= (int8_t)1.0;
	} else {
		uavtalk_MixerSettingsData.Mixer1Vector.Yaw += (int8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_Airspeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.Airspeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.Airspeed -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.Airspeed += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.Airspeed >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.Airspeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_AltitudeHold_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.AltitudeHold += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.AltitudeHold -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.AltitudeHold += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.AltitudeHold >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.AltitudeHold = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_Autotune_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.Autotune += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.Autotune -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.Autotune += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.Autotune >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.Autotune = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_Battery_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.Battery += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.Battery -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.Battery += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.Battery >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.Battery = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_CameraStab_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.CameraStab += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.CameraStab -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.CameraStab += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.CameraStab >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.CameraStab = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_ComUsbBridge_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.ComUsbBridge += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.ComUsbBridge -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.ComUsbBridge += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.ComUsbBridge >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.ComUsbBridge = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_FixedWingPathFollower_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.FixedWingPathFollower += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.FixedWingPathFollower -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.FixedWingPathFollower += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.FixedWingPathFollower >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.FixedWingPathFollower = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_Fault_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.Fault += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.Fault -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.Fault += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.Fault >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.Fault = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_GPS_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.GPS += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.GPS -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.GPS += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.GPS >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.GPS = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_OveroSync_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.OveroSync += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.OveroSync -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.OveroSync += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.OveroSync >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.OveroSync = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_PathPlanner_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.PathPlanner += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.PathPlanner -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.PathPlanner += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.PathPlanner >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.PathPlanner = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_TxPID_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.TxPID += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.TxPID -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.TxPID += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.TxPID >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.TxPID = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_VtolPathFollower_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.VtolPathFollower += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.VtolPathFollower -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.VtolPathFollower += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.VtolPathFollower >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.VtolPathFollower = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_GroundPathFollower_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.GroundPathFollower += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.GroundPathFollower -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.GroundPathFollower += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.GroundPathFollower >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.GroundPathFollower = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_GenericI2CSensor_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.GenericI2CSensor += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.GenericI2CSensor -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.GenericI2CSensor += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.GenericI2CSensor >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.GenericI2CSensor = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_UAVOMavlinkBridge_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.UAVOMavlinkBridge += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.UAVOMavlinkBridge -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.UAVOMavlinkBridge += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.UAVOMavlinkBridge >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.UAVOMavlinkBridge = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_UAVOLighttelemetryBridge_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.UAVOLighttelemetryBridge += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.UAVOLighttelemetryBridge -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.UAVOLighttelemetryBridge += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.UAVOLighttelemetryBridge >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.UAVOLighttelemetryBridge = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_VibrationAnalysis_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.VibrationAnalysis += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.VibrationAnalysis -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.VibrationAnalysis += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.VibrationAnalysis >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.VibrationAnalysis = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_UAVOHoTTBridge_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.UAVOHoTTBridge += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.UAVOHoTTBridge -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.UAVOHoTTBridge += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.UAVOHoTTBridge >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.UAVOHoTTBridge = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_UAVOFrSKYSensorHubBridge_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.UAVOFrSKYSensorHubBridge += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.UAVOFrSKYSensorHubBridge -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.UAVOFrSKYSensorHubBridge += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.UAVOFrSKYSensorHubBridge >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.UAVOFrSKYSensorHubBridge = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_PicoC_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.PicoC += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.PicoC -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.PicoC += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.PicoC >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.PicoC = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_UAVOFrSkySPortBridge_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.UAVOFrSkySPortBridge += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.UAVOFrSkySPortBridge -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.UAVOFrSkySPortBridge += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.UAVOFrSkySPortBridge >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.UAVOFrSkySPortBridge = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_Geofence_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.Geofence += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.Geofence -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.Geofence += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.Geofence >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.Geofence = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsAdminState_Logging_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.AdminState.Logging += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.AdminState.Logging -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.AdminState.Logging += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.AdminState.Logging >= MODULESETTINGS_ADMINSTATE_LASTITEM) {
		uavtalk_ModuleSettingsData.AdminState.Logging = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsTelemetrySpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.TelemetrySpeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.TelemetrySpeed -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.TelemetrySpeed += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.TelemetrySpeed >= MODULESETTINGS_TELEMETRYSPEED_LASTITEM) {
		uavtalk_ModuleSettingsData.TelemetrySpeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsGPSSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.GPSSpeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.GPSSpeed -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.GPSSpeed += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.GPSSpeed >= MODULESETTINGS_GPSSPEED_LASTITEM) {
		uavtalk_ModuleSettingsData.GPSSpeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsGPSDataProtocol_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.GPSDataProtocol += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.GPSDataProtocol -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.GPSDataProtocol += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.GPSDataProtocol >= MODULESETTINGS_GPSDATAPROTOCOL_LASTITEM) {
		uavtalk_ModuleSettingsData.GPSDataProtocol = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsGPSAutoConfigure_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.GPSAutoConfigure += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.GPSAutoConfigure -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.GPSAutoConfigure += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.GPSAutoConfigure >= MODULESETTINGS_GPSAUTOCONFIGURE_LASTITEM) {
		uavtalk_ModuleSettingsData.GPSAutoConfigure = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsComUsbBridgeSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.ComUsbBridgeSpeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.ComUsbBridgeSpeed -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.ComUsbBridgeSpeed += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.ComUsbBridgeSpeed >= MODULESETTINGS_COMUSBBRIDGESPEED_LASTITEM) {
		uavtalk_ModuleSettingsData.ComUsbBridgeSpeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsI2CVMProgramSelect_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.I2CVMProgramSelect += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.I2CVMProgramSelect -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.I2CVMProgramSelect += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.I2CVMProgramSelect >= MODULESETTINGS_I2CVMPROGRAMSELECT_LASTITEM) {
		uavtalk_ModuleSettingsData.I2CVMProgramSelect = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsMavlinkSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.MavlinkSpeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.MavlinkSpeed -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.MavlinkSpeed += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.MavlinkSpeed >= MODULESETTINGS_MAVLINKSPEED_LASTITEM) {
		uavtalk_ModuleSettingsData.MavlinkSpeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_ModuleSettingsLightTelemetrySpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_ModuleSettingsData.LightTelemetrySpeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_ModuleSettingsData.LightTelemetrySpeed -= (uint8_t)1.0;
	} else {
		uavtalk_ModuleSettingsData.LightTelemetrySpeed += (uint8_t)data;
	}
	if (uavtalk_ModuleSettingsData.LightTelemetrySpeed >= MODULESETTINGS_LIGHTTELEMETRYSPEED_LASTITEM) {
		uavtalk_ModuleSettingsData.LightTelemetrySpeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsRollRatePID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.RollRatePID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.RollRatePID.Kp -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.RollRatePID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsRollRatePID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.RollRatePID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.RollRatePID.Ki -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.RollRatePID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsRollRatePID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.RollRatePID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.RollRatePID.Kd -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.RollRatePID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsRollRatePID_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.RollRatePID.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.RollRatePID.ILimit -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.RollRatePID.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsPitchRatePID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.PitchRatePID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.PitchRatePID.Kp -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.PitchRatePID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsPitchRatePID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.PitchRatePID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.PitchRatePID.Ki -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.PitchRatePID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsPitchRatePID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.PitchRatePID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.PitchRatePID.Kd -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.PitchRatePID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsPitchRatePID_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.PitchRatePID.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.PitchRatePID.ILimit -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.PitchRatePID.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsYawRatePID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.YawRatePID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.YawRatePID.Kp -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.YawRatePID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsYawRatePID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.YawRatePID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.YawRatePID.Ki -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.YawRatePID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsYawRatePID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.YawRatePID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.YawRatePID.Kd -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.YawRatePID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsYawRatePID_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.YawRatePID.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.YawRatePID.ILimit -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.YawRatePID.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsDerivativeGamma_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.DerivativeGamma += (float)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.DerivativeGamma -= (float)1.0;
	} else {
		uavtalk_MWRateSettingsData.DerivativeGamma += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsRollPitchRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.RollPitchRate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.RollPitchRate -= (uint8_t)1.0;
	} else {
		uavtalk_MWRateSettingsData.RollPitchRate += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_MWRateSettingsYawRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_MWRateSettingsData.YawRate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_MWRateSettingsData.YawRate -= (uint8_t)1.0;
	} else {
		uavtalk_MWRateSettingsData.YawRate += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsPairID_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.PairID += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.PairID -= (uint32_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.PairID += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsMinFrequency_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.MinFrequency += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.MinFrequency -= (uint32_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.MinFrequency += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsMaxFrequency_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.MaxFrequency += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.MaxFrequency -= (uint32_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.MaxFrequency += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsSendTimeout_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.SendTimeout += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.SendTimeout -= (uint16_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.SendTimeout += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsCoordinator_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.Coordinator += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.Coordinator -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.Coordinator += (uint8_t)data;
	}
	if (uavtalk_OPLinkSettingsData.Coordinator >= OPLINKSETTINGS_COORDINATOR_LASTITEM) {
		uavtalk_OPLinkSettingsData.Coordinator = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsPPM_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.PPM += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.PPM -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.PPM += (uint8_t)data;
	}
	if (uavtalk_OPLinkSettingsData.PPM >= OPLINKSETTINGS_PPM_LASTITEM) {
		uavtalk_OPLinkSettingsData.PPM = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsUAVTalk_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.UAVTalk += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.UAVTalk -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.UAVTalk += (uint8_t)data;
	}
	if (uavtalk_OPLinkSettingsData.UAVTalk >= OPLINKSETTINGS_UAVTALK_LASTITEM) {
		uavtalk_OPLinkSettingsData.UAVTalk = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsInputConnection_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.InputConnection += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.InputConnection -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.InputConnection += (uint8_t)data;
	}
	if (uavtalk_OPLinkSettingsData.InputConnection >= OPLINKSETTINGS_INPUTCONNECTION_LASTITEM) {
		uavtalk_OPLinkSettingsData.InputConnection = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsOutputConnection_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.OutputConnection += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.OutputConnection -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.OutputConnection += (uint8_t)data;
	}
	if (uavtalk_OPLinkSettingsData.OutputConnection >= OPLINKSETTINGS_OUTPUTCONNECTION_LASTITEM) {
		uavtalk_OPLinkSettingsData.OutputConnection = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsComSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.ComSpeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.ComSpeed -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.ComSpeed += (uint8_t)data;
	}
	if (uavtalk_OPLinkSettingsData.ComSpeed >= OPLINKSETTINGS_COMSPEED_LASTITEM) {
		uavtalk_OPLinkSettingsData.ComSpeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsMaxRFPower_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.MaxRFPower += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.MaxRFPower -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.MaxRFPower += (uint8_t)data;
	}
	if (uavtalk_OPLinkSettingsData.MaxRFPower >= OPLINKSETTINGS_MAXRFPOWER_LASTITEM) {
		uavtalk_OPLinkSettingsData.MaxRFPower = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsMinPacketSize_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.MinPacketSize += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.MinPacketSize -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.MinPacketSize += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsFrequencyCalibration_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.FrequencyCalibration += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.FrequencyCalibration -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.FrequencyCalibration += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[0] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[0] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[0] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[1] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[1] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[1] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[2] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[2] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[2] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[3] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[3] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[3] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_4_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[4] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[4] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[4] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_5_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[5] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[5] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[5] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_6_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[6] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[6] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[6] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_7_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[7] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[7] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[7] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_8_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[8] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[8] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[8] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_9_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[9] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[9] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[9] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_10_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[10] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[10] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[10] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_11_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[11] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[11] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[11] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_12_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[12] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[12] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[12] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_13_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[13] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[13] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[13] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_14_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[14] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[14] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[14] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_15_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[15] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[15] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[15] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_16_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[16] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[16] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[16] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_17_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[17] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[17] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[17] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_18_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[18] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[18] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[18] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_19_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[19] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[19] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[19] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_20_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[20] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[20] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[20] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_21_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[21] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[21] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[21] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_22_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[22] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[22] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[22] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_23_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[23] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[23] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[23] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_24_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[24] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[24] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[24] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_25_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[25] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[25] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[25] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_26_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[26] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[26] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[26] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_27_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[27] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[27] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[27] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_28_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[28] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[28] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[28] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_29_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[29] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[29] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[29] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_30_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[30] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[30] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[30] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OPLinkSettingsAESKey_31_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OPLinkSettingsData.AESKey[31] += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OPLinkSettingsData.AESKey[31] -= (uint8_t)1.0;
	} else {
		uavtalk_OPLinkSettingsData.AESKey[31] += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_OveroSyncSettingsLogOn_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_OveroSyncSettingsData.LogOn += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_OveroSyncSettingsData.LogOn -= (uint8_t)1.0;
	} else {
		uavtalk_OveroSyncSettingsData.LogOn += (uint8_t)data;
	}
	if (uavtalk_OveroSyncSettingsData.LogOn >= OVEROSYNCSETTINGS_LOGON_LASTITEM) {
		uavtalk_OveroSyncSettingsData.LogOn = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_PathPlannerSettingsPreprogrammedPath_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_PathPlannerSettingsData.PreprogrammedPath += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_PathPlannerSettingsData.PreprogrammedPath -= (uint8_t)1.0;
	} else {
		uavtalk_PathPlannerSettingsData.PreprogrammedPath += (uint8_t)data;
	}
	if (uavtalk_PathPlannerSettingsData.PreprogrammedPath >= PATHPLANNERSETTINGS_PREPROGRAMMEDPATH_LASTITEM) {
		uavtalk_PathPlannerSettingsData.PreprogrammedPath = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_PathPlannerSettingsFlashOperation_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_PathPlannerSettingsData.FlashOperation += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_PathPlannerSettingsData.FlashOperation -= (uint8_t)1.0;
	} else {
		uavtalk_PathPlannerSettingsData.FlashOperation += (uint8_t)data;
	}
	if (uavtalk_PathPlannerSettingsData.FlashOperation >= PATHPLANNERSETTINGS_FLASHOPERATION_LASTITEM) {
		uavtalk_PathPlannerSettingsData.FlashOperation = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_PicoCSettingsMaxFileSize_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_PicoCSettingsData.MaxFileSize += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_PicoCSettingsData.MaxFileSize -= (uint32_t)1.0;
	} else {
		uavtalk_PicoCSettingsData.MaxFileSize += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_PicoCSettingsTaskStackSize_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_PicoCSettingsData.TaskStackSize += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_PicoCSettingsData.TaskStackSize -= (uint32_t)1.0;
	} else {
		uavtalk_PicoCSettingsData.TaskStackSize += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_PicoCSettingsPicoCStackSize_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_PicoCSettingsData.PicoCStackSize += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_PicoCSettingsData.PicoCStackSize -= (uint32_t)1.0;
	} else {
		uavtalk_PicoCSettingsData.PicoCStackSize += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_PicoCSettingsBootFileID_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_PicoCSettingsData.BootFileID += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_PicoCSettingsData.BootFileID -= (uint8_t)1.0;
	} else {
		uavtalk_PicoCSettingsData.BootFileID += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_PicoCSettingsStartup_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_PicoCSettingsData.Startup += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_PicoCSettingsData.Startup -= (uint8_t)1.0;
	} else {
		uavtalk_PicoCSettingsData.Startup += (uint8_t)data;
	}
	if (uavtalk_PicoCSettingsData.Startup >= PICOCSETTINGS_STARTUP_LASTITEM) {
		uavtalk_PicoCSettingsData.Startup = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_PicoCSettingsSource_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_PicoCSettingsData.Source += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_PicoCSettingsData.Source -= (uint8_t)1.0;
	} else {
		uavtalk_PicoCSettingsData.Source += (uint8_t)data;
	}
	if (uavtalk_PicoCSettingsData.Source >= PICOCSETTINGS_SOURCE_LASTITEM) {
		uavtalk_PicoCSettingsData.Source = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_PicoCSettingsComSpeed_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_PicoCSettingsData.ComSpeed += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_PicoCSettingsData.ComSpeed -= (uint8_t)1.0;
	} else {
		uavtalk_PicoCSettingsData.ComSpeed += (uint8_t)data;
	}
	if (uavtalk_PicoCSettingsData.ComSpeed >= PICOCSETTINGS_COMSPEED_LASTITEM) {
		uavtalk_PicoCSettingsData.ComSpeed = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsAccelBias_X_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.AccelBias.X += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.AccelBias.X -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.AccelBias.X += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsAccelBias_Y_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.AccelBias.Y += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.AccelBias.Y -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.AccelBias.Y += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsAccelBias_Z_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.AccelBias.Z += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.AccelBias.Z -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.AccelBias.Z += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsAccelScale_X_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.AccelScale.X += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.AccelScale.X -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.AccelScale.X += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsAccelScale_Y_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.AccelScale.Y += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.AccelScale.Y -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.AccelScale.Y += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsAccelScale_Z_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.AccelScale.Z += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.AccelScale.Z -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.AccelScale.Z += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsGyroScale_X_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.GyroScale.X += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.GyroScale.X -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.GyroScale.X += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsGyroScale_Y_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.GyroScale.Y += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.GyroScale.Y -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.GyroScale.Y += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsGyroScale_Z_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.GyroScale.Z += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.GyroScale.Z -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.GyroScale.Z += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsXGyroTempCoeff_n_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.XGyroTempCoeff.n += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.XGyroTempCoeff.n -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.XGyroTempCoeff.n += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsXGyroTempCoeff_T_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.XGyroTempCoeff.T += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.XGyroTempCoeff.T -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.XGyroTempCoeff.T += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsXGyroTempCoeff_T2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.XGyroTempCoeff.T2 += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.XGyroTempCoeff.T2 -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.XGyroTempCoeff.T2 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsXGyroTempCoeff_T3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.XGyroTempCoeff.T3 += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.XGyroTempCoeff.T3 -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.XGyroTempCoeff.T3 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsYGyroTempCoeff_n_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.YGyroTempCoeff.n += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.YGyroTempCoeff.n -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.YGyroTempCoeff.n += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsYGyroTempCoeff_T_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.YGyroTempCoeff.T += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.YGyroTempCoeff.T -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.YGyroTempCoeff.T += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsYGyroTempCoeff_T2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.YGyroTempCoeff.T2 += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.YGyroTempCoeff.T2 -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.YGyroTempCoeff.T2 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsYGyroTempCoeff_T3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.YGyroTempCoeff.T3 += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.YGyroTempCoeff.T3 -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.YGyroTempCoeff.T3 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsZGyroTempCoeff_n_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.n += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.n -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.n += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsZGyroTempCoeff_T_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.T += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.T -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.T += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsZGyroTempCoeff_T2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.T2 += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.T2 -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.T2 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsZGyroTempCoeff_T3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.T3 += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.T3 -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.ZGyroTempCoeff.T3 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsMagBias_X_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.MagBias.X += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.MagBias.X -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.MagBias.X += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsMagBias_Y_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.MagBias.Y += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.MagBias.Y -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.MagBias.Y += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsMagBias_Z_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.MagBias.Z += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.MagBias.Z -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.MagBias.Z += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsMagScale_X_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.MagScale.X += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.MagScale.X -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.MagScale.X += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsMagScale_Y_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.MagScale.Y += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.MagScale.Y -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.MagScale.Y += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsMagScale_Z_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.MagScale.Z += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.MagScale.Z -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.MagScale.Z += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SensorSettingsZAccelOffset_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SensorSettingsData.ZAccelOffset += (float)1.0;
	} else if (button == 5) {
		uavtalk_SensorSettingsData.ZAccelOffset -= (float)1.0;
	} else {
		uavtalk_SensorSettingsData.ZAccelOffset += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsManualRate_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.ManualRate.Roll += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.ManualRate.Roll -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.ManualRate.Roll += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsManualRate_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.ManualRate.Pitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.ManualRate.Pitch -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.ManualRate.Pitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsManualRate_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.ManualRate.Yaw += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.ManualRate.Yaw -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.ManualRate.Yaw += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsMaximumRate_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.MaximumRate.Roll += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.MaximumRate.Roll -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.MaximumRate.Roll += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsMaximumRate_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.MaximumRate.Pitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.MaximumRate.Pitch -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.MaximumRate.Pitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsMaximumRate_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.MaximumRate.Yaw += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.MaximumRate.Yaw -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.MaximumRate.Yaw += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPoiMaximumRate_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PoiMaximumRate.Roll += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PoiMaximumRate.Roll -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PoiMaximumRate.Roll += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPoiMaximumRate_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PoiMaximumRate.Pitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PoiMaximumRate.Pitch -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PoiMaximumRate.Pitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPoiMaximumRate_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PoiMaximumRate.Yaw += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PoiMaximumRate.Yaw -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PoiMaximumRate.Yaw += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollRatePID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollRatePID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollRatePID.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollRatePID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollRatePID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollRatePID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollRatePID.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollRatePID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollRatePID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollRatePID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollRatePID.Kd -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollRatePID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollRatePID_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollRatePID.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollRatePID.ILimit -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollRatePID.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchRatePID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchRatePID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchRatePID.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchRatePID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchRatePID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchRatePID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchRatePID.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchRatePID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchRatePID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchRatePID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchRatePID.Kd -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchRatePID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchRatePID_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchRatePID.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchRatePID.ILimit -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchRatePID.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawRatePID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawRatePID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawRatePID.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawRatePID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawRatePID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawRatePID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawRatePID.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawRatePID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawRatePID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawRatePID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawRatePID.Kd -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawRatePID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawRatePID_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawRatePID.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawRatePID.ILimit -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawRatePID.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollPI_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollPI.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollPI.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollPI.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollPI_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollPI.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollPI.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollPI.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollPI_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollPI.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollPI.ILimit -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollPI.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchPI_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchPI.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchPI.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchPI.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchPI_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchPI.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchPI.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchPI.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchPI_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchPI.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchPI.ILimit -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchPI.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawPI_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawPI.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawPI.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawPI.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawPI_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawPI.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawPI.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawPI.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawPI_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawPI.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawPI.ILimit -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawPI.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarSensitivity_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarSensitivity.Roll += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarSensitivity.Roll -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarSensitivity.Roll += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarSensitivity_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarSensitivity.Pitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarSensitivity.Pitch -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarSensitivity.Pitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarSensitivity_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarSensitivity.Yaw += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarSensitivity.Yaw -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarSensitivity.Yaw += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarRollPID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarRollPID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarRollPID.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarRollPID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarRollPID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarRollPID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarRollPID.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarRollPID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarRollPID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarRollPID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarRollPID.Kd -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarRollPID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarPitchPID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarPitchPID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarPitchPID.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarPitchPID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarPitchPID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarPitchPID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarPitchPID.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarPitchPID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarPitchPID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarPitchPID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarPitchPID.Kd -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarPitchPID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarYawPID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarYawPID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarYawPID.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarYawPID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarYawPID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarYawPID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarYawPID.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarYawPID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarYawPID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarYawPID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarYawPID.Kd -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarYawPID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarTau_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarTau += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarTau -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarTau += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsGyroTau_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.GyroTau += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.GyroTau -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.GyroTau += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsDerivativeGamma_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.DerivativeGamma += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.DerivativeGamma -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.DerivativeGamma += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsWeakLevelingKp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.WeakLevelingKp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.WeakLevelingKp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.WeakLevelingKp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsCoordinatedFlightYawPI_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.Kp -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsCoordinatedFlightYawPI_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.Ki -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsCoordinatedFlightYawPI_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.ILimit -= (float)1.0;
	} else {
		uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollMax += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollMax -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollMax += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchMax += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchMax -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchMax += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawMax += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawMax -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawMax += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRateExpo_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RateExpo.Roll += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RateExpo.Roll -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RateExpo.Roll += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRateExpo_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RateExpo.Pitch += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RateExpo.Pitch -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RateExpo.Pitch += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRateExpo_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RateExpo.Yaw += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RateExpo.Yaw -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RateExpo.Yaw += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollRateTPA_Threshold_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollRateTPA.Threshold += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollRateTPA.Threshold -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollRateTPA.Threshold += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsRollRateTPA_Attenuation_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.RollRateTPA.Attenuation += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.RollRateTPA.Attenuation -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.RollRateTPA.Attenuation += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchRateTPA_Threshold_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchRateTPA.Threshold += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchRateTPA.Threshold -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchRateTPA.Threshold += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsPitchRateTPA_Attenuation_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.PitchRateTPA.Attenuation += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.PitchRateTPA.Attenuation -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.PitchRateTPA.Attenuation += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawRateTPA_Threshold_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawRateTPA.Threshold += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawRateTPA.Threshold -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawRateTPA.Threshold += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsYawRateTPA_Attenuation_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.YawRateTPA.Attenuation += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.YawRateTPA.Attenuation -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.YawRateTPA.Attenuation += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarGyroSuppress_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarGyroSuppress += (int8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarGyroSuppress -= (int8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarGyroSuppress += (int8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarPiroComp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarPiroComp += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarPiroComp -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarPiroComp += (uint8_t)data;
	}
	if (uavtalk_StabilizationSettingsData.VbarPiroComp >= STABILIZATIONSETTINGS_VBARPIROCOMP_LASTITEM) {
		uavtalk_StabilizationSettingsData.VbarPiroComp = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsVbarMaxAngle_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.VbarMaxAngle += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.VbarMaxAngle -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.VbarMaxAngle += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsDerivativeCutoff_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.DerivativeCutoff += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.DerivativeCutoff -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.DerivativeCutoff += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsMaxAxisLock_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.MaxAxisLock += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.MaxAxisLock -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.MaxAxisLock += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsMaxAxisLockRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.MaxAxisLockRate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.MaxAxisLockRate -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.MaxAxisLockRate += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsMaxWeakLevelingRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.MaxWeakLevelingRate += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.MaxWeakLevelingRate -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.MaxWeakLevelingRate += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_StabilizationSettingsLowThrottleZeroIntegral_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StabilizationSettingsData.LowThrottleZeroIntegral += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StabilizationSettingsData.LowThrottleZeroIntegral -= (uint8_t)1.0;
	} else {
		uavtalk_StabilizationSettingsData.LowThrottleZeroIntegral += (uint8_t)data;
	}
	if (uavtalk_StabilizationSettingsData.LowThrottleZeroIntegral >= STABILIZATIONSETTINGS_LOWTHROTTLEZEROINTEGRAL_LASTITEM) {
		uavtalk_StabilizationSettingsData.LowThrottleZeroIntegral = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_StateEstimationAttitudeFilter_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StateEstimationData.AttitudeFilter += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StateEstimationData.AttitudeFilter -= (uint8_t)1.0;
	} else {
		uavtalk_StateEstimationData.AttitudeFilter += (uint8_t)data;
	}
	if (uavtalk_StateEstimationData.AttitudeFilter >= STATEESTIMATION_ATTITUDEFILTER_LASTITEM) {
		uavtalk_StateEstimationData.AttitudeFilter = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_StateEstimationNavigationFilter_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_StateEstimationData.NavigationFilter += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_StateEstimationData.NavigationFilter -= (uint8_t)1.0;
	} else {
		uavtalk_StateEstimationData.NavigationFilter += (uint8_t)data;
	}
	if (uavtalk_StateEstimationData.NavigationFilter >= STATEESTIMATION_NAVIGATIONFILTER_LASTITEM) {
		uavtalk_StateEstimationData.NavigationFilter = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_SystemIdentBeta_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemIdentData.Beta.Roll += (float)1.0;
	} else if (button == 5) {
		uavtalk_SystemIdentData.Beta.Roll -= (float)1.0;
	} else {
		uavtalk_SystemIdentData.Beta.Roll += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemIdentBeta_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemIdentData.Beta.Pitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_SystemIdentData.Beta.Pitch -= (float)1.0;
	} else {
		uavtalk_SystemIdentData.Beta.Pitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemIdentBeta_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemIdentData.Beta.Yaw += (float)1.0;
	} else if (button == 5) {
		uavtalk_SystemIdentData.Beta.Yaw -= (float)1.0;
	} else {
		uavtalk_SystemIdentData.Beta.Yaw += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemIdentBias_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemIdentData.Bias.Roll += (float)1.0;
	} else if (button == 5) {
		uavtalk_SystemIdentData.Bias.Roll -= (float)1.0;
	} else {
		uavtalk_SystemIdentData.Bias.Roll += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemIdentBias_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemIdentData.Bias.Pitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_SystemIdentData.Bias.Pitch -= (float)1.0;
	} else {
		uavtalk_SystemIdentData.Bias.Pitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemIdentBias_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemIdentData.Bias.Yaw += (float)1.0;
	} else if (button == 5) {
		uavtalk_SystemIdentData.Bias.Yaw -= (float)1.0;
	} else {
		uavtalk_SystemIdentData.Bias.Yaw += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemIdentNoise_Roll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemIdentData.Noise.Roll += (float)1.0;
	} else if (button == 5) {
		uavtalk_SystemIdentData.Noise.Roll -= (float)1.0;
	} else {
		uavtalk_SystemIdentData.Noise.Roll += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemIdentNoise_Pitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemIdentData.Noise.Pitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_SystemIdentData.Noise.Pitch -= (float)1.0;
	} else {
		uavtalk_SystemIdentData.Noise.Pitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemIdentNoise_Yaw_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemIdentData.Noise.Yaw += (float)1.0;
	} else if (button == 5) {
		uavtalk_SystemIdentData.Noise.Yaw -= (float)1.0;
	} else {
		uavtalk_SystemIdentData.Noise.Yaw += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemSettingsAirframeCategorySpecificConfiguration_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[0] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[0] -= (uint32_t)1.0;
	} else {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[0] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemSettingsAirframeCategorySpecificConfiguration_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[1] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[1] -= (uint32_t)1.0;
	} else {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[1] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemSettingsAirframeCategorySpecificConfiguration_2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[2] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[2] -= (uint32_t)1.0;
	} else {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[2] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemSettingsAirframeCategorySpecificConfiguration_3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[3] += (uint32_t)1.0;
	} else if (button == 5) {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[3] -= (uint32_t)1.0;
	} else {
		uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[3] += (uint32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_SystemSettingsAirframeType_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_SystemSettingsData.AirframeType += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_SystemSettingsData.AirframeType -= (uint8_t)1.0;
	} else {
		uavtalk_SystemSettingsData.AirframeType += (uint8_t)data;
	}
	if (uavtalk_SystemSettingsData.AirframeType >= SYSTEMSETTINGS_AIRFRAMETYPE_LASTITEM) {
		uavtalk_SystemSettingsData.AirframeType = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_TrimAnglesSettingsRoll_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TrimAnglesSettingsData.Roll += (float)1.0;
	} else if (button == 5) {
		uavtalk_TrimAnglesSettingsData.Roll -= (float)1.0;
	} else {
		uavtalk_TrimAnglesSettingsData.Roll += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TrimAnglesSettingsPitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TrimAnglesSettingsData.Pitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_TrimAnglesSettingsData.Pitch -= (float)1.0;
	} else {
		uavtalk_TrimAnglesSettingsData.Pitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsThrottleRange_0_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.ThrottleRange[0] += (float)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.ThrottleRange[0] -= (float)1.0;
	} else {
		uavtalk_TxPIDSettingsData.ThrottleRange[0] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsThrottleRange_1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.ThrottleRange[1] += (float)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.ThrottleRange[1] -= (float)1.0;
	} else {
		uavtalk_TxPIDSettingsData.ThrottleRange[1] += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsMinPID_Instance1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.MinPID.Instance1 += (float)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.MinPID.Instance1 -= (float)1.0;
	} else {
		uavtalk_TxPIDSettingsData.MinPID.Instance1 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsMinPID_Instance2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.MinPID.Instance2 += (float)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.MinPID.Instance2 -= (float)1.0;
	} else {
		uavtalk_TxPIDSettingsData.MinPID.Instance2 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsMinPID_Instance3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.MinPID.Instance3 += (float)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.MinPID.Instance3 -= (float)1.0;
	} else {
		uavtalk_TxPIDSettingsData.MinPID.Instance3 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsMaxPID_Instance1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.MaxPID.Instance1 += (float)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.MaxPID.Instance1 -= (float)1.0;
	} else {
		uavtalk_TxPIDSettingsData.MaxPID.Instance1 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsMaxPID_Instance2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.MaxPID.Instance2 += (float)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.MaxPID.Instance2 -= (float)1.0;
	} else {
		uavtalk_TxPIDSettingsData.MaxPID.Instance2 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsMaxPID_Instance3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.MaxPID.Instance3 += (float)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.MaxPID.Instance3 -= (float)1.0;
	} else {
		uavtalk_TxPIDSettingsData.MaxPID.Instance3 += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsUpdateMode_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.UpdateMode += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.UpdateMode -= (uint8_t)1.0;
	} else {
		uavtalk_TxPIDSettingsData.UpdateMode += (uint8_t)data;
	}
	if (uavtalk_TxPIDSettingsData.UpdateMode >= TXPIDSETTINGS_UPDATEMODE_LASTITEM) {
		uavtalk_TxPIDSettingsData.UpdateMode = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsInputs_Instance1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.Inputs.Instance1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.Inputs.Instance1 -= (uint8_t)1.0;
	} else {
		uavtalk_TxPIDSettingsData.Inputs.Instance1 += (uint8_t)data;
	}
	if (uavtalk_TxPIDSettingsData.Inputs.Instance1 >= TXPIDSETTINGS_INPUTS_LASTITEM) {
		uavtalk_TxPIDSettingsData.Inputs.Instance1 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsInputs_Instance2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.Inputs.Instance2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.Inputs.Instance2 -= (uint8_t)1.0;
	} else {
		uavtalk_TxPIDSettingsData.Inputs.Instance2 += (uint8_t)data;
	}
	if (uavtalk_TxPIDSettingsData.Inputs.Instance2 >= TXPIDSETTINGS_INPUTS_LASTITEM) {
		uavtalk_TxPIDSettingsData.Inputs.Instance2 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsInputs_Instance3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.Inputs.Instance3 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.Inputs.Instance3 -= (uint8_t)1.0;
	} else {
		uavtalk_TxPIDSettingsData.Inputs.Instance3 += (uint8_t)data;
	}
	if (uavtalk_TxPIDSettingsData.Inputs.Instance3 >= TXPIDSETTINGS_INPUTS_LASTITEM) {
		uavtalk_TxPIDSettingsData.Inputs.Instance3 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsPIDs_Instance1_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.PIDs.Instance1 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.PIDs.Instance1 -= (uint8_t)1.0;
	} else {
		uavtalk_TxPIDSettingsData.PIDs.Instance1 += (uint8_t)data;
	}
	if (uavtalk_TxPIDSettingsData.PIDs.Instance1 >= TXPIDSETTINGS_PIDS_LASTITEM) {
		uavtalk_TxPIDSettingsData.PIDs.Instance1 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsPIDs_Instance2_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.PIDs.Instance2 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.PIDs.Instance2 -= (uint8_t)1.0;
	} else {
		uavtalk_TxPIDSettingsData.PIDs.Instance2 += (uint8_t)data;
	}
	if (uavtalk_TxPIDSettingsData.PIDs.Instance2 >= TXPIDSETTINGS_PIDS_LASTITEM) {
		uavtalk_TxPIDSettingsData.PIDs.Instance2 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_TxPIDSettingsPIDs_Instance3_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_TxPIDSettingsData.PIDs.Instance3 += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_TxPIDSettingsData.PIDs.Instance3 -= (uint8_t)1.0;
	} else {
		uavtalk_TxPIDSettingsData.PIDs.Instance3 += (uint8_t)data;
	}
	if (uavtalk_TxPIDSettingsData.PIDs.Instance3 >= TXPIDSETTINGS_PIDS_LASTITEM) {
		uavtalk_TxPIDSettingsData.PIDs.Instance3 = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_VibrationAnalysisSettingsSampleRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VibrationAnalysisSettingsData.SampleRate += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_VibrationAnalysisSettingsData.SampleRate -= (uint16_t)1.0;
	} else {
		uavtalk_VibrationAnalysisSettingsData.SampleRate += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_VibrationAnalysisSettingsFFTWindowSize_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VibrationAnalysisSettingsData.FFTWindowSize += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_VibrationAnalysisSettingsData.FFTWindowSize -= (uint8_t)1.0;
	} else {
		uavtalk_VibrationAnalysisSettingsData.FFTWindowSize += (uint8_t)data;
	}
	if (uavtalk_VibrationAnalysisSettingsData.FFTWindowSize >= VIBRATIONANALYSISSETTINGS_FFTWINDOWSIZE_LASTITEM) {
		uavtalk_VibrationAnalysisSettingsData.FFTWindowSize = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_VibrationAnalysisSettingsTestingStatus_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VibrationAnalysisSettingsData.TestingStatus += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_VibrationAnalysisSettingsData.TestingStatus -= (uint8_t)1.0;
	} else {
		uavtalk_VibrationAnalysisSettingsData.TestingStatus += (uint8_t)data;
	}
	if (uavtalk_VibrationAnalysisSettingsData.TestingStatus >= VIBRATIONANALYSISSETTINGS_TESTINGSTATUS_LASTITEM) {
		uavtalk_VibrationAnalysisSettingsData.TestingStatus = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsHorizontalPosPI_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.Kp -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsHorizontalPosPI_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.Ki -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsHorizontalPosPI_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.ILimit -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsHorizontalVelPID_Kp_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Kp += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Kp -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Kp += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsHorizontalVelPID_Ki_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Ki += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Ki -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Ki += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsHorizontalVelPID_Kd_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Kd += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Kd -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Kd += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsHorizontalVelPID_ILimit_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.ILimit += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.ILimit -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.ILimit += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsVelocityFeedforward_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.VelocityFeedforward += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.VelocityFeedforward -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.VelocityFeedforward += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsMaxRollPitch_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.MaxRollPitch += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.MaxRollPitch -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.MaxRollPitch += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsUpdatePeriod_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.UpdatePeriod += (int32_t)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.UpdatePeriod -= (int32_t)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.UpdatePeriod += (int32_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsLandingRate_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.LandingRate += (float)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.LandingRate -= (float)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.LandingRate += (float)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsHorizontalVelMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelMax += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelMax -= (uint16_t)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.HorizontalVelMax += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsVerticalVelMax_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.VerticalVelMax += (uint16_t)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.VerticalVelMax -= (uint16_t)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.VerticalVelMax += (uint16_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsThrottleControl_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.ThrottleControl += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.ThrottleControl -= (uint8_t)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.ThrottleControl += (uint8_t)data;
	}
	if (uavtalk_VtolPathFollowerSettingsData.ThrottleControl >= VTOLPATHFOLLOWERSETTINGS_THROTTLECONTROL_LASTITEM) {
		uavtalk_VtolPathFollowerSettingsData.ThrottleControl = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsVelocityChangePrediction_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.VelocityChangePrediction += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.VelocityChangePrediction -= (uint8_t)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.VelocityChangePrediction += (uint8_t)data;
	}
	if (uavtalk_VtolPathFollowerSettingsData.VelocityChangePrediction >= VTOLPATHFOLLOWERSETTINGS_VELOCITYCHANGEPREDICTION_LASTITEM) {
		uavtalk_VtolPathFollowerSettingsData.VelocityChangePrediction = (uint8_t)0.0;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsEndpointRadius_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.EndpointRadius += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.EndpointRadius -= (uint8_t)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.EndpointRadius += (uint8_t)data;
	}
	return 0;
}

uint8_t UAVT_gui_VtolPathFollowerSettingsYawMode_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		uavtalk_VtolPathFollowerSettingsData.YawMode += (uint8_t)1.0;
	} else if (button == 5) {
		uavtalk_VtolPathFollowerSettingsData.YawMode -= (uint8_t)1.0;
	} else {
		uavtalk_VtolPathFollowerSettingsData.YawMode += (uint8_t)data;
	}
	if (uavtalk_VtolPathFollowerSettingsData.YawMode >= VTOLPATHFOLLOWERSETTINGS_YAWMODE_LASTITEM) {
		uavtalk_VtolPathFollowerSettingsData.YawMode = (uint8_t)0.0;
	}
	return 0;
}
