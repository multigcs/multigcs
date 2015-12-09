/***********************************************
    Object: ActuatorSettings
***********************************************/

void UAVT_gui_ActuatorSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "ActuatorSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelUpdateFreq0 = %i", uavtalk_ActuatorSettingsData.ChannelUpdateFreq[0]);
		draw_text_button(esContext, "ActuatorSettingsChannelUpdateFreq0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelUpdateFreq_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelUpdateFreq1 = %i", uavtalk_ActuatorSettingsData.ChannelUpdateFreq[1]);
		draw_text_button(esContext, "ActuatorSettingsChannelUpdateFreq1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelUpdateFreq_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelUpdateFreq2 = %i", uavtalk_ActuatorSettingsData.ChannelUpdateFreq[2]);
		draw_text_button(esContext, "ActuatorSettingsChannelUpdateFreq2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelUpdateFreq_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelUpdateFreq3 = %i", uavtalk_ActuatorSettingsData.ChannelUpdateFreq[3]);
		draw_text_button(esContext, "ActuatorSettingsChannelUpdateFreq3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelUpdateFreq_3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelUpdateFreq4 = %i", uavtalk_ActuatorSettingsData.ChannelUpdateFreq[4]);
		draw_text_button(esContext, "ActuatorSettingsChannelUpdateFreq4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelUpdateFreq_4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelUpdateFreq5 = %i", uavtalk_ActuatorSettingsData.ChannelUpdateFreq[5]);
		draw_text_button(esContext, "ActuatorSettingsChannelUpdateFreq5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelUpdateFreq_5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax0 = %i", uavtalk_ActuatorSettingsData.ChannelMax[0]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax1 = %i", uavtalk_ActuatorSettingsData.ChannelMax[1]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax2 = %i", uavtalk_ActuatorSettingsData.ChannelMax[2]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax3 = %i", uavtalk_ActuatorSettingsData.ChannelMax[3]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax4 = %i", uavtalk_ActuatorSettingsData.ChannelMax[4]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax5 = %i", uavtalk_ActuatorSettingsData.ChannelMax[5]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax6 = %i", uavtalk_ActuatorSettingsData.ChannelMax[6]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax6Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_6_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax7 = %i", uavtalk_ActuatorSettingsData.ChannelMax[7]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax7Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_7_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax8 = %i", uavtalk_ActuatorSettingsData.ChannelMax[8]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax8Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_8_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax9 = %i", uavtalk_ActuatorSettingsData.ChannelMax[9]);
		draw_text_button(esContext, "ActuatorSettingsChannelMax9Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMax_9_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral0 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[0]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral1 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[1]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral2 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[2]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral3 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[3]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral4 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[4]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral5 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[5]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral6 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[6]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral6Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_6_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral7 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[7]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral7Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_7_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral8 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[8]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral8Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_8_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral9 = %i", uavtalk_ActuatorSettingsData.ChannelNeutral[9]);
		draw_text_button(esContext, "ActuatorSettingsChannelNeutral9Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelNeutral_9_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin0 = %i", uavtalk_ActuatorSettingsData.ChannelMin[0]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin1 = %i", uavtalk_ActuatorSettingsData.ChannelMin[1]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin2 = %i", uavtalk_ActuatorSettingsData.ChannelMin[2]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin3 = %i", uavtalk_ActuatorSettingsData.ChannelMin[3]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin4 = %i", uavtalk_ActuatorSettingsData.ChannelMin[4]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin5 = %i", uavtalk_ActuatorSettingsData.ChannelMin[5]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin6 = %i", uavtalk_ActuatorSettingsData.ChannelMin[6]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin6Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_6_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin7 = %i", uavtalk_ActuatorSettingsData.ChannelMin[7]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin7Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_7_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin8 = %i", uavtalk_ActuatorSettingsData.ChannelMin[8]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin8Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_8_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin9 = %i", uavtalk_ActuatorSettingsData.ChannelMin[9]);
		draw_text_button(esContext, "ActuatorSettingsChannelMin9Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelMin_9_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType0 = %i", uavtalk_ActuatorSettingsData.ChannelType[0]);
		draw_text_button(esContext, "ActuatorSettingsChannelType0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType1 = %i", uavtalk_ActuatorSettingsData.ChannelType[1]);
		draw_text_button(esContext, "ActuatorSettingsChannelType1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType2 = %i", uavtalk_ActuatorSettingsData.ChannelType[2]);
		draw_text_button(esContext, "ActuatorSettingsChannelType2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType3 = %i", uavtalk_ActuatorSettingsData.ChannelType[3]);
		draw_text_button(esContext, "ActuatorSettingsChannelType3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType4 = %i", uavtalk_ActuatorSettingsData.ChannelType[4]);
		draw_text_button(esContext, "ActuatorSettingsChannelType4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType5 = %i", uavtalk_ActuatorSettingsData.ChannelType[5]);
		draw_text_button(esContext, "ActuatorSettingsChannelType5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType6 = %i", uavtalk_ActuatorSettingsData.ChannelType[6]);
		draw_text_button(esContext, "ActuatorSettingsChannelType6Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_6_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType7 = %i", uavtalk_ActuatorSettingsData.ChannelType[7]);
		draw_text_button(esContext, "ActuatorSettingsChannelType7Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_7_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType8 = %i", uavtalk_ActuatorSettingsData.ChannelType[8]);
		draw_text_button(esContext, "ActuatorSettingsChannelType8Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_8_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelType9 = %i", uavtalk_ActuatorSettingsData.ChannelType[9]);
		draw_text_button(esContext, "ActuatorSettingsChannelType9Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelType_9_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr0 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[0]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr1 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[1]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr2 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[2]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr3 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[3]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr4 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[4]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr5 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[5]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr6 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[6]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr6Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_6_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr7 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[7]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr7Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_7_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr8 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[8]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr8Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_8_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelAddr9 = %i", uavtalk_ActuatorSettingsData.ChannelAddr[9]);
		draw_text_button(esContext, "ActuatorSettingsChannelAddr9Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsChannelAddr_9_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MotorsSpinWhileArmed = %i (%s)", uavtalk_ActuatorSettingsData.MotorsSpinWhileArmed,
				UAVT_ActuatorSettingsMotorsSpinWhileArmedOption[uavtalk_ActuatorSettingsData.MotorsSpinWhileArmed]);
		draw_text_button(esContext, "ActuatorSettingsMotorsSpinWhileArmedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ActuatorSettingsMotorsSpinWhileArmed_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: AirspeedSettings
***********************************************/

void UAVT_gui_AirspeedSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "AirspeedSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Scale = %f", uavtalk_AirspeedSettingsData.Scale);
		draw_text_button(esContext, "AirspeedSettingsScaleChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_AirspeedSettingsScale_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ZeroPoint = %i", uavtalk_AirspeedSettingsData.ZeroPoint);
		draw_text_button(esContext, "AirspeedSettingsZeroPointChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AirspeedSettingsZeroPoint_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GPSSamplePeriod_ms = %i", uavtalk_AirspeedSettingsData.GPSSamplePeriod_ms);
		draw_text_button(esContext, "AirspeedSettingsGPSSamplePeriod_msChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AirspeedSettingsGPSSamplePeriod_ms_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirspeedSensorType = %i (%s)", uavtalk_AirspeedSettingsData.AirspeedSensorType, UAVT_AirspeedSettingsAirspeedSensorTypeOption[uavtalk_AirspeedSettingsData.AirspeedSensorType]);
		draw_text_button(esContext, "AirspeedSettingsAirspeedSensorTypeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AirspeedSettingsAirspeedSensorType_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AnalogPin = %i (%s)", uavtalk_AirspeedSettingsData.AnalogPin, UAVT_AirspeedSettingsAnalogPinOption[uavtalk_AirspeedSettingsData.AnalogPin]);
		draw_text_button(esContext, "AirspeedSettingsAnalogPinChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AirspeedSettingsAnalogPin_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: AltitudeHoldSettings
***********************************************/

void UAVT_gui_AltitudeHoldSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "AltitudeHoldSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PositionKp = %f", uavtalk_AltitudeHoldSettingsData.PositionKp);
		draw_text_button(esContext, "AltitudeHoldSettingsPositionKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AltitudeHoldSettingsPositionKp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VelocityKp = %f", uavtalk_AltitudeHoldSettingsData.VelocityKp);
		draw_text_button(esContext, "AltitudeHoldSettingsVelocityKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AltitudeHoldSettingsVelocityKp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VelocityKi = %f", uavtalk_AltitudeHoldSettingsData.VelocityKi);
		draw_text_button(esContext, "AltitudeHoldSettingsVelocityKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AltitudeHoldSettingsVelocityKi_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AttitudeComp = %i", uavtalk_AltitudeHoldSettingsData.AttitudeComp);
		draw_text_button(esContext, "AltitudeHoldSettingsAttitudeCompChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AltitudeHoldSettingsAttitudeComp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxRate = %i", uavtalk_AltitudeHoldSettingsData.MaxRate);
		draw_text_button(esContext, "AltitudeHoldSettingsMaxRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AltitudeHoldSettingsMaxRate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Expo = %i", uavtalk_AltitudeHoldSettingsData.Expo);
		draw_text_button(esContext, "AltitudeHoldSettingsExpoChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AltitudeHoldSettingsExpo_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Deadband = %i", uavtalk_AltitudeHoldSettingsData.Deadband);
		draw_text_button(esContext, "AltitudeHoldSettingsDeadbandChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AltitudeHoldSettingsDeadband_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: AttitudeSettings
***********************************************/

void UAVT_gui_AttitudeSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "AttitudeSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MagKp = %f", uavtalk_AttitudeSettingsData.MagKp);
		draw_text_button(esContext, "AttitudeSettingsMagKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_AttitudeSettingsMagKp_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MagKi = %f", uavtalk_AttitudeSettingsData.MagKi);
		draw_text_button(esContext, "AttitudeSettingsMagKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_AttitudeSettingsMagKi_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelKp = %f", uavtalk_AttitudeSettingsData.AccelKp);
		draw_text_button(esContext, "AttitudeSettingsAccelKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsAccelKp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelKi = %f", uavtalk_AttitudeSettingsData.AccelKi);
		draw_text_button(esContext, "AttitudeSettingsAccelKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsAccelKi_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelTau = %f", uavtalk_AttitudeSettingsData.AccelTau);
		draw_text_button(esContext, "AttitudeSettingsAccelTauChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsAccelTau_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VertPositionTau = %f", uavtalk_AttitudeSettingsData.VertPositionTau);
		draw_text_button(esContext, "AttitudeSettingsVertPositionTauChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsVertPositionTau_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawBiasRate = %f", uavtalk_AttitudeSettingsData.YawBiasRate);
		draw_text_button(esContext, "AttitudeSettingsYawBiasRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsYawBiasRate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "BoardRotation.Roll = %i", uavtalk_AttitudeSettingsData.BoardRotation.Roll);
		draw_text_button(esContext, "AttitudeSettingsBoardRotationRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsBoardRotation_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "BoardRotation.Pitch = %i", uavtalk_AttitudeSettingsData.BoardRotation.Pitch);
		draw_text_button(esContext, "AttitudeSettingsBoardRotationPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsBoardRotation_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "BoardRotation.Yaw = %i", uavtalk_AttitudeSettingsData.BoardRotation.Yaw);
		draw_text_button(esContext, "AttitudeSettingsBoardRotationYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsBoardRotation_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ZeroDuringArming = %i (%s)", uavtalk_AttitudeSettingsData.ZeroDuringArming, UAVT_AttitudeSettingsZeroDuringArmingOption[uavtalk_AttitudeSettingsData.ZeroDuringArming]);
		draw_text_button(esContext, "AttitudeSettingsZeroDuringArmingChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsZeroDuringArming_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "BiasCorrectGyro = %i (%s)", uavtalk_AttitudeSettingsData.BiasCorrectGyro, UAVT_AttitudeSettingsBiasCorrectGyroOption[uavtalk_AttitudeSettingsData.BiasCorrectGyro]);
		draw_text_button(esContext, "AttitudeSettingsBiasCorrectGyroChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsBiasCorrectGyro_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FilterChoice = %i (%s)", uavtalk_AttitudeSettingsData.FilterChoice, UAVT_AttitudeSettingsFilterChoiceOption[uavtalk_AttitudeSettingsData.FilterChoice]);
		draw_text_button(esContext, "AttitudeSettingsFilterChoiceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsFilterChoice_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "TrimFlight = %i (%s)", uavtalk_AttitudeSettingsData.TrimFlight, UAVT_AttitudeSettingsTrimFlightOption[uavtalk_AttitudeSettingsData.TrimFlight]);
		draw_text_button(esContext, "AttitudeSettingsTrimFlightChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_AttitudeSettingsTrimFlight_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: BrushlessGimbalSettings
***********************************************/

void UAVT_gui_BrushlessGimbalSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "BrushlessGimbalSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Damping.Roll = %f", uavtalk_BrushlessGimbalSettingsData.Damping.Roll);
		draw_text_button(esContext, "BrushlessGimbalSettingsDampingRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsDamping_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Damping.Pitch = %f", uavtalk_BrushlessGimbalSettingsData.Damping.Pitch);
		draw_text_button(esContext, "BrushlessGimbalSettingsDampingPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsDamping_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Damping.Yaw = %f", uavtalk_BrushlessGimbalSettingsData.Damping.Yaw);
		draw_text_button(esContext, "BrushlessGimbalSettingsDampingYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsDamping_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxDPS.Roll = %i", uavtalk_BrushlessGimbalSettingsData.MaxDPS.Roll);
		draw_text_button(esContext, "BrushlessGimbalSettingsMaxDPSRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsMaxDPS_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxDPS.Pitch = %i", uavtalk_BrushlessGimbalSettingsData.MaxDPS.Pitch);
		draw_text_button(esContext, "BrushlessGimbalSettingsMaxDPSPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsMaxDPS_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxDPS.Yaw = %i", uavtalk_BrushlessGimbalSettingsData.MaxDPS.Yaw);
		draw_text_button(esContext, "BrushlessGimbalSettingsMaxDPSYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsMaxDPS_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SlewLimit.Roll = %i", uavtalk_BrushlessGimbalSettingsData.SlewLimit.Roll);
		draw_text_button(esContext, "BrushlessGimbalSettingsSlewLimitRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsSlewLimit_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SlewLimit.Pitch = %i", uavtalk_BrushlessGimbalSettingsData.SlewLimit.Pitch);
		draw_text_button(esContext, "BrushlessGimbalSettingsSlewLimitPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsSlewLimit_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SlewLimit.Yaw = %i", uavtalk_BrushlessGimbalSettingsData.SlewLimit.Yaw);
		draw_text_button(esContext, "BrushlessGimbalSettingsSlewLimitYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsSlewLimit_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PowerScale.Roll = %i", uavtalk_BrushlessGimbalSettingsData.PowerScale.Roll);
		draw_text_button(esContext, "BrushlessGimbalSettingsPowerScaleRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsPowerScale_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PowerScale.Pitch = %i", uavtalk_BrushlessGimbalSettingsData.PowerScale.Pitch);
		draw_text_button(esContext, "BrushlessGimbalSettingsPowerScalePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsPowerScale_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PowerScale.Yaw = %i", uavtalk_BrushlessGimbalSettingsData.PowerScale.Yaw);
		draw_text_button(esContext, "BrushlessGimbalSettingsPowerScaleYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsPowerScale_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxAngle.Roll = %i", uavtalk_BrushlessGimbalSettingsData.MaxAngle.Roll);
		draw_text_button(esContext, "BrushlessGimbalSettingsMaxAngleRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsMaxAngle_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxAngle.Pitch = %i", uavtalk_BrushlessGimbalSettingsData.MaxAngle.Pitch);
		draw_text_button(esContext, "BrushlessGimbalSettingsMaxAnglePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsMaxAngle_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxAngle.Yaw = %i", uavtalk_BrushlessGimbalSettingsData.MaxAngle.Yaw);
		draw_text_button(esContext, "BrushlessGimbalSettingsMaxAngleYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsMaxAngle_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollFraction = %i", uavtalk_BrushlessGimbalSettingsData.RollFraction);
		draw_text_button(esContext, "BrushlessGimbalSettingsRollFractionChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsRollFraction_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PowerupSequence = %i (%s)", uavtalk_BrushlessGimbalSettingsData.PowerupSequence,
				UAVT_BrushlessGimbalSettingsPowerupSequenceOption[uavtalk_BrushlessGimbalSettingsData.PowerupSequence]);
		draw_text_button(esContext, "BrushlessGimbalSettingsPowerupSequenceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_BrushlessGimbalSettingsPowerupSequence_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: CameraStabSettings
***********************************************/

void UAVT_gui_CameraStabSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "CameraStabSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxAxisLockRate = %f", uavtalk_CameraStabSettingsData.MaxAxisLockRate);
		draw_text_button(esContext, "CameraStabSettingsMaxAxisLockRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsMaxAxisLockRate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxAccel = %f", uavtalk_CameraStabSettingsData.MaxAccel);
		draw_text_button(esContext, "CameraStabSettingsMaxAccelChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsMaxAccel_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Input.Roll = %i", uavtalk_CameraStabSettingsData.Input.Roll);
		draw_text_button(esContext, "CameraStabSettingsInputRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInput_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Input.Pitch = %i", uavtalk_CameraStabSettingsData.Input.Pitch);
		draw_text_button(esContext, "CameraStabSettingsInputPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInput_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Input.Yaw = %i", uavtalk_CameraStabSettingsData.Input.Yaw);
		draw_text_button(esContext, "CameraStabSettingsInputYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInput_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "InputRange.Roll = %i", uavtalk_CameraStabSettingsData.InputRange.Roll);
		draw_text_button(esContext, "CameraStabSettingsInputRangeRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInputRange_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "InputRange.Pitch = %i", uavtalk_CameraStabSettingsData.InputRange.Pitch);
		draw_text_button(esContext, "CameraStabSettingsInputRangePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInputRange_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "InputRange.Yaw = %i", uavtalk_CameraStabSettingsData.InputRange.Yaw);
		draw_text_button(esContext, "CameraStabSettingsInputRangeYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInputRange_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "InputRate.Roll = %i", uavtalk_CameraStabSettingsData.InputRate.Roll);
		draw_text_button(esContext, "CameraStabSettingsInputRateRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInputRate_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "InputRate.Pitch = %i", uavtalk_CameraStabSettingsData.InputRate.Pitch);
		draw_text_button(esContext, "CameraStabSettingsInputRatePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInputRate_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "InputRate.Yaw = %i", uavtalk_CameraStabSettingsData.InputRate.Yaw);
		draw_text_button(esContext, "CameraStabSettingsInputRateYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInputRate_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "OutputRange.Roll = %i", uavtalk_CameraStabSettingsData.OutputRange.Roll);
		draw_text_button(esContext, "CameraStabSettingsOutputRangeRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsOutputRange_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "OutputRange.Pitch = %i", uavtalk_CameraStabSettingsData.OutputRange.Pitch);
		draw_text_button(esContext, "CameraStabSettingsOutputRangePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsOutputRange_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "OutputRange.Yaw = %i", uavtalk_CameraStabSettingsData.OutputRange.Yaw);
		draw_text_button(esContext, "CameraStabSettingsOutputRangeYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsOutputRange_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FeedForward.Roll = %i", uavtalk_CameraStabSettingsData.FeedForward.Roll);
		draw_text_button(esContext, "CameraStabSettingsFeedForwardRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsFeedForward_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FeedForward.Pitch = %i", uavtalk_CameraStabSettingsData.FeedForward.Pitch);
		draw_text_button(esContext, "CameraStabSettingsFeedForwardPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsFeedForward_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FeedForward.Yaw = %i", uavtalk_CameraStabSettingsData.FeedForward.Yaw);
		draw_text_button(esContext, "CameraStabSettingsFeedForwardYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsFeedForward_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "StabilizationMode.Roll = %i", uavtalk_CameraStabSettingsData.StabilizationMode.Roll);
		draw_text_button(esContext, "CameraStabSettingsStabilizationModeRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsStabilizationMode_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "StabilizationMode.Pitch = %i", uavtalk_CameraStabSettingsData.StabilizationMode.Pitch);
		draw_text_button(esContext, "CameraStabSettingsStabilizationModePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsStabilizationMode_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "StabilizationMode.Yaw = %i", uavtalk_CameraStabSettingsData.StabilizationMode.Yaw);
		draw_text_button(esContext, "CameraStabSettingsStabilizationModeYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsStabilizationMode_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AttitudeFilter = %i", uavtalk_CameraStabSettingsData.AttitudeFilter);
		draw_text_button(esContext, "CameraStabSettingsAttitudeFilterChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsAttitudeFilter_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "InputFilter = %i", uavtalk_CameraStabSettingsData.InputFilter);
		draw_text_button(esContext, "CameraStabSettingsInputFilterChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsInputFilter_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FeedForwardTime = %i", uavtalk_CameraStabSettingsData.FeedForwardTime);
		draw_text_button(esContext, "CameraStabSettingsFeedForwardTimeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_CameraStabSettingsFeedForwardTime_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: FaultSettings
***********************************************/

void UAVT_gui_FaultSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "FaultSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ActivateFault = %i (%s)", uavtalk_FaultSettingsData.ActivateFault, UAVT_FaultSettingsActivateFaultOption[uavtalk_FaultSettingsData.ActivateFault]);
		draw_text_button(esContext, "FaultSettingsActivateFaultChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FaultSettingsActivateFault_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: FixedWingAirspeeds
***********************************************/

void UAVT_gui_FixedWingAirspeeds_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "FixedWingAirspeeds ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirSpeedMax = %f", uavtalk_FixedWingAirspeedsData.AirSpeedMax);
		draw_text_button(esContext, "FixedWingAirspeedsAirSpeedMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingAirspeedsAirSpeedMax_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "CruiseSpeed = %f", uavtalk_FixedWingAirspeedsData.CruiseSpeed);
		draw_text_button(esContext, "FixedWingAirspeedsCruiseSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingAirspeedsCruiseSpeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "BestClimbRateSpeed = %f", uavtalk_FixedWingAirspeedsData.BestClimbRateSpeed);
		draw_text_button(esContext, "FixedWingAirspeedsBestClimbRateSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingAirspeedsBestClimbRateSpeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "StallSpeedClean = %f", uavtalk_FixedWingAirspeedsData.StallSpeedClean);
		draw_text_button(esContext, "FixedWingAirspeedsStallSpeedCleanChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingAirspeedsStallSpeedClean_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "StallSpeedDirty = %f", uavtalk_FixedWingAirspeedsData.StallSpeedDirty);
		draw_text_button(esContext, "FixedWingAirspeedsStallSpeedDirtyChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingAirspeedsStallSpeedDirty_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VerticalVelMax = %f", uavtalk_FixedWingAirspeedsData.VerticalVelMax);
		draw_text_button(esContext, "FixedWingAirspeedsVerticalVelMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingAirspeedsVerticalVelMax_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: FixedWingPathFollowerSettingsCC
***********************************************/

void UAVT_gui_FixedWingPathFollowerSettingsCC_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "FixedWingPathFollowerSettingsCC ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VerticalVelMax = %f", uavtalk_FixedWingPathFollowerSettingsCCData.VerticalVelMax);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCVerticalVelMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCVerticalVelMax_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VectorFollowingGain = %f", uavtalk_FixedWingPathFollowerSettingsCCData.VectorFollowingGain);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCVectorFollowingGainChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCVectorFollowingGain_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "OrbitFollowingGain = %f", uavtalk_FixedWingPathFollowerSettingsCCData.OrbitFollowingGain);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCOrbitFollowingGainChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCOrbitFollowingGain_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FollowerIntegralGain = %f", uavtalk_FixedWingPathFollowerSettingsCCData.FollowerIntegralGain);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCFollowerIntegralGainChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCFollowerIntegralGain_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VerticalPosP = %f", uavtalk_FixedWingPathFollowerSettingsCCData.VerticalPosP);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCVerticalPosPChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCVerticalPosP_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HeadingPI0 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCHeadingPI0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCHeadingPI_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HeadingPI1 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCHeadingPI1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCHeadingPI_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HeadingPI2 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.HeadingPI[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCHeadingPI2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCHeadingPI_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirspeedPI0 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCAirspeedPI0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedPI_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirspeedPI1 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCAirspeedPI1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedPI_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirspeedPI2 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedPI[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCAirspeedPI2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedPI_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VerticalToPitchCrossFeed.Kp = %f", uavtalk_FixedWingPathFollowerSettingsCCData.VerticalToPitchCrossFeed.Kp);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCVerticalToPitchCrossFeedKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCVerticalToPitchCrossFeed_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VerticalToPitchCrossFeed.Max = %f", uavtalk_FixedWingPathFollowerSettingsCCData.VerticalToPitchCrossFeed.Max);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCVerticalToPitchCrossFeedMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCVerticalToPitchCrossFeed_Max_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirspeedToVerticalCrossFeed.Kp = %f", uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedToVerticalCrossFeed.Kp);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCAirspeedToVerticalCrossFeedKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedToVerticalCrossFeed_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirspeedToVerticalCrossFeed.Max = %f", uavtalk_FixedWingPathFollowerSettingsCCData.AirspeedToVerticalCrossFeed.Max);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCAirspeedToVerticalCrossFeedMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCAirspeedToVerticalCrossFeed_Max_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottlePI0 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCThrottlePI0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCThrottlePI_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottlePI1 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCThrottlePI1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCThrottlePI_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottlePI2 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.ThrottlePI[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCThrottlePI2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCThrottlePI_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollLimit0 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCRollLimit0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCRollLimit_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollLimit1 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCRollLimit1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCRollLimit_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollLimit2 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.RollLimit[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCRollLimit2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCRollLimit_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchLimit0 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCPitchLimit0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCPitchLimit_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchLimit1 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCPitchLimit1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCPitchLimit_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchLimit2 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.PitchLimit[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCPitchLimit2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCPitchLimit_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleLimit0 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCThrottleLimit0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCThrottleLimit_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleLimit1 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCThrottleLimit1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCThrottleLimit_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleLimit2 = %f", uavtalk_FixedWingPathFollowerSettingsCCData.ThrottleLimit[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCThrottleLimit2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCThrottleLimit_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "UpdatePeriod = %i", uavtalk_FixedWingPathFollowerSettingsCCData.UpdatePeriod);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsCCUpdatePeriodChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsCCUpdatePeriod_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: FixedWingPathFollowerSettings
***********************************************/

void UAVT_gui_FixedWingPathFollowerSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "FixedWingPathFollowerSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalPosP = %f", uavtalk_FixedWingPathFollowerSettingsData.HorizontalPosP);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsHorizontalPosPChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsHorizontalPosP_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VerticalPosP = %f", uavtalk_FixedWingPathFollowerSettingsData.VerticalPosP);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsVerticalPosPChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsVerticalPosP_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "BearingPI0 = %f", uavtalk_FixedWingPathFollowerSettingsData.BearingPI[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsBearingPI0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsBearingPI_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "BearingPI1 = %f", uavtalk_FixedWingPathFollowerSettingsData.BearingPI[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsBearingPI1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsBearingPI_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "BearingPI2 = %f", uavtalk_FixedWingPathFollowerSettingsData.BearingPI[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsBearingPI2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsBearingPI_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PowerPI0 = %f", uavtalk_FixedWingPathFollowerSettingsData.PowerPI[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsPowerPI0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsPowerPI_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PowerPI1 = %f", uavtalk_FixedWingPathFollowerSettingsData.PowerPI[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsPowerPI1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsPowerPI_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PowerPI2 = %f", uavtalk_FixedWingPathFollowerSettingsData.PowerPI[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsPowerPI2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsPowerPI_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VerticalToPitchCrossFeed.Kp = %f", uavtalk_FixedWingPathFollowerSettingsData.VerticalToPitchCrossFeed.Kp);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsVerticalToPitchCrossFeedKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsVerticalToPitchCrossFeed_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VerticalToPitchCrossFeed.Max = %f", uavtalk_FixedWingPathFollowerSettingsData.VerticalToPitchCrossFeed.Max);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsVerticalToPitchCrossFeedMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsVerticalToPitchCrossFeed_Max_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirspeedToVerticalCrossFeed.Kp = %f", uavtalk_FixedWingPathFollowerSettingsData.AirspeedToVerticalCrossFeed.Kp);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsAirspeedToVerticalCrossFeedKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsAirspeedToVerticalCrossFeed_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirspeedToVerticalCrossFeed.Max = %f", uavtalk_FixedWingPathFollowerSettingsData.AirspeedToVerticalCrossFeed.Max);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsAirspeedToVerticalCrossFeedMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsAirspeedToVerticalCrossFeed_Max_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SpeedPI0 = %f", uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsSpeedPI0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsSpeedPI_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SpeedPI1 = %f", uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsSpeedPI1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsSpeedPI_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SpeedPI2 = %f", uavtalk_FixedWingPathFollowerSettingsData.SpeedPI[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsSpeedPI2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsSpeedPI_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollLimit0 = %f", uavtalk_FixedWingPathFollowerSettingsData.RollLimit[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsRollLimit0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsRollLimit_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollLimit1 = %f", uavtalk_FixedWingPathFollowerSettingsData.RollLimit[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsRollLimit1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsRollLimit_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollLimit2 = %f", uavtalk_FixedWingPathFollowerSettingsData.RollLimit[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsRollLimit2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsRollLimit_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchLimit0 = %f", uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsPitchLimit0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsPitchLimit_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchLimit1 = %f", uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsPitchLimit1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsPitchLimit_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchLimit2 = %f", uavtalk_FixedWingPathFollowerSettingsData.PitchLimit[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsPitchLimit2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsPitchLimit_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleLimit0 = %f", uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[0]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsThrottleLimit0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsThrottleLimit_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleLimit1 = %f", uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[1]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsThrottleLimit1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsThrottleLimit_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleLimit2 = %f", uavtalk_FixedWingPathFollowerSettingsData.ThrottleLimit[2]);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsThrottleLimit2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsThrottleLimit_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "OrbitRadius = %f", uavtalk_FixedWingPathFollowerSettingsData.OrbitRadius);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsOrbitRadiusChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsOrbitRadius_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "UpdatePeriod = %i", uavtalk_FixedWingPathFollowerSettingsData.UpdatePeriod);
		draw_text_button(esContext, "FixedWingPathFollowerSettingsUpdatePeriodChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FixedWingPathFollowerSettingsUpdatePeriod_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: FlightBatterySettings
***********************************************/

void UAVT_gui_FlightBatterySettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "FlightBatterySettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Capacity = %i", uavtalk_FlightBatterySettingsData.Capacity);
		draw_text_button(esContext, "FlightBatterySettingsCapacityChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsCapacity_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VoltageThresholds.Warning = %f", uavtalk_FlightBatterySettingsData.VoltageThresholds.Warning);
		draw_text_button(esContext, "FlightBatterySettingsVoltageThresholdsWarningChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsVoltageThresholds_Warning_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VoltageThresholds.Alarm = %f", uavtalk_FlightBatterySettingsData.VoltageThresholds.Alarm);
		draw_text_button(esContext, "FlightBatterySettingsVoltageThresholdsAlarmChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsVoltageThresholds_Alarm_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SensorCalibrationFactor.Voltage = %f", uavtalk_FlightBatterySettingsData.SensorCalibrationFactor.Voltage);
		draw_text_button(esContext, "FlightBatterySettingsSensorCalibrationFactorVoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsSensorCalibrationFactor_Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SensorCalibrationFactor.Current = %f", uavtalk_FlightBatterySettingsData.SensorCalibrationFactor.Current);
		draw_text_button(esContext, "FlightBatterySettingsSensorCalibrationFactorCurrentChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsSensorCalibrationFactor_Current_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SensorCalibrationOffset.Voltage = %f", uavtalk_FlightBatterySettingsData.SensorCalibrationOffset.Voltage);
		draw_text_button(esContext, "FlightBatterySettingsSensorCalibrationOffsetVoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsSensorCalibrationOffset_Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SensorCalibrationOffset.Current = %f", uavtalk_FlightBatterySettingsData.SensorCalibrationOffset.Current);
		draw_text_button(esContext, "FlightBatterySettingsSensorCalibrationOffsetCurrentChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsSensorCalibrationOffset_Current_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "CurrentPin = %i (%s)", uavtalk_FlightBatterySettingsData.CurrentPin, UAVT_FlightBatterySettingsCurrentPinOption[uavtalk_FlightBatterySettingsData.CurrentPin]);
		draw_text_button(esContext, "FlightBatterySettingsCurrentPinChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsCurrentPin_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VoltagePin = %i (%s)", uavtalk_FlightBatterySettingsData.VoltagePin, UAVT_FlightBatterySettingsVoltagePinOption[uavtalk_FlightBatterySettingsData.VoltagePin]);
		draw_text_button(esContext, "FlightBatterySettingsVoltagePinChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsVoltagePin_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Type = %i (%s)", uavtalk_FlightBatterySettingsData.Type, UAVT_FlightBatterySettingsTypeOption[uavtalk_FlightBatterySettingsData.Type]);
		draw_text_button(esContext, "FlightBatterySettingsTypeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsType_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "NbCells = %i", uavtalk_FlightBatterySettingsData.NbCells);
		draw_text_button(esContext, "FlightBatterySettingsNbCellsChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsNbCells_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SensorType.BatteryCurrent = %i", uavtalk_FlightBatterySettingsData.SensorType.BatteryCurrent);
		draw_text_button(esContext, "FlightBatterySettingsSensorTypeBatteryCurrentChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsSensorType_BatteryCurrent_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SensorType.BatteryVoltage = %i", uavtalk_FlightBatterySettingsData.SensorType.BatteryVoltage);
		draw_text_button(esContext, "FlightBatterySettingsSensorTypeBatteryVoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_FlightBatterySettingsSensorType_BatteryVoltage_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: FlightPlanSettings
***********************************************/

void UAVT_gui_FlightPlanSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "FlightPlanSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Test = %f", uavtalk_FlightPlanSettingsData.Test);
		draw_text_button(esContext, "FlightPlanSettingsTestChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_FlightPlanSettingsTest_change,
						 0.0);
	}
	nn++;
}

/***********************************************
    Object: GeoFenceSettings
***********************************************/

void UAVT_gui_GeoFenceSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "GeoFenceSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "WarningRadius = %i", uavtalk_GeoFenceSettingsData.WarningRadius);
		draw_text_button(esContext, "GeoFenceSettingsWarningRadiusChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GeoFenceSettingsWarningRadius_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ErrorRadius = %i", uavtalk_GeoFenceSettingsData.ErrorRadius);
		draw_text_button(esContext, "GeoFenceSettingsErrorRadiusChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GeoFenceSettingsErrorRadius_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: GroundPathFollowerSettings
***********************************************/

void UAVT_gui_GroundPathFollowerSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "GroundPathFollowerSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalPosPI.Kp = %f", uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.Kp);
		draw_text_button(esContext, "GroundPathFollowerSettingsHorizontalPosPIKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsHorizontalPosPI_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalPosPI.Ki = %f", uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.Ki);
		draw_text_button(esContext, "GroundPathFollowerSettingsHorizontalPosPIKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsHorizontalPosPI_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalPosPI.ILimit = %f", uavtalk_GroundPathFollowerSettingsData.HorizontalPosPI.ILimit);
		draw_text_button(esContext, "GroundPathFollowerSettingsHorizontalPosPIILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsHorizontalPosPI_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelPID.Kp = %f", uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Kp);
		draw_text_button(esContext, "GroundPathFollowerSettingsHorizontalVelPIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsHorizontalVelPID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelPID.Ki = %f", uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Ki);
		draw_text_button(esContext, "GroundPathFollowerSettingsHorizontalVelPIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsHorizontalVelPID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelPID.Kd = %f", uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.Kd);
		draw_text_button(esContext, "GroundPathFollowerSettingsHorizontalVelPIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsHorizontalVelPID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelPID.ILimit = %f", uavtalk_GroundPathFollowerSettingsData.HorizontalVelPID.ILimit);
		draw_text_button(esContext, "GroundPathFollowerSettingsHorizontalVelPIDILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsHorizontalVelPID_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VelocityFeedforward = %f", uavtalk_GroundPathFollowerSettingsData.VelocityFeedforward);
		draw_text_button(esContext, "GroundPathFollowerSettingsVelocityFeedforwardChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsVelocityFeedforward_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxThrottle = %f", uavtalk_GroundPathFollowerSettingsData.MaxThrottle);
		draw_text_button(esContext, "GroundPathFollowerSettingsMaxThrottleChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsMaxThrottle_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "UpdatePeriod = %i", uavtalk_GroundPathFollowerSettingsData.UpdatePeriod);
		draw_text_button(esContext, "GroundPathFollowerSettingsUpdatePeriodChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsUpdatePeriod_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelMax = %i", uavtalk_GroundPathFollowerSettingsData.HorizontalVelMax);
		draw_text_button(esContext, "GroundPathFollowerSettingsHorizontalVelMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsHorizontalVelMax_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ManualOverride = %i (%s)", uavtalk_GroundPathFollowerSettingsData.ManualOverride,
				UAVT_GroundPathFollowerSettingsManualOverrideOption[uavtalk_GroundPathFollowerSettingsData.ManualOverride]);
		draw_text_button(esContext, "GroundPathFollowerSettingsManualOverrideChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsManualOverride_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleControl = %i (%s)", uavtalk_GroundPathFollowerSettingsData.ThrottleControl,
				UAVT_GroundPathFollowerSettingsThrottleControlOption[uavtalk_GroundPathFollowerSettingsData.ThrottleControl]);
		draw_text_button(esContext, "GroundPathFollowerSettingsThrottleControlChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsThrottleControl_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VelocitySource = %i (%s)", uavtalk_GroundPathFollowerSettingsData.VelocitySource,
				UAVT_GroundPathFollowerSettingsVelocitySourceOption[uavtalk_GroundPathFollowerSettingsData.VelocitySource]);
		draw_text_button(esContext, "GroundPathFollowerSettingsVelocitySourceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsVelocitySource_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PositionSource = %i (%s)", uavtalk_GroundPathFollowerSettingsData.PositionSource,
				UAVT_GroundPathFollowerSettingsPositionSourceOption[uavtalk_GroundPathFollowerSettingsData.PositionSource]);
		draw_text_button(esContext, "GroundPathFollowerSettingsPositionSourceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsPositionSource_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "EndpointRadius = %i", uavtalk_GroundPathFollowerSettingsData.EndpointRadius);
		draw_text_button(esContext, "GroundPathFollowerSettingsEndpointRadiusChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_GroundPathFollowerSettingsEndpointRadius_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HomeLocation
***********************************************/

void UAVT_gui_HomeLocation_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HomeLocation ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Latitude = %i", uavtalk_HomeLocationData.Latitude);
		draw_text_button(esContext, "HomeLocationLatitudeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HomeLocationLatitude_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Longitude = %i", uavtalk_HomeLocationData.Longitude);
		draw_text_button(esContext, "HomeLocationLongitudeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HomeLocationLongitude_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Altitude = %f", uavtalk_HomeLocationData.Altitude);
		draw_text_button(esContext, "HomeLocationAltitudeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HomeLocationAltitude_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Be0 = %f", uavtalk_HomeLocationData.Be[0]);
		draw_text_button(esContext, "HomeLocationBe0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HomeLocationBe_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Be1 = %f", uavtalk_HomeLocationData.Be[1]);
		draw_text_button(esContext, "HomeLocationBe1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HomeLocationBe_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Be2 = %f", uavtalk_HomeLocationData.Be[2]);
		draw_text_button(esContext, "HomeLocationBe2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HomeLocationBe_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GroundTemperature = %i", uavtalk_HomeLocationData.GroundTemperature);
		draw_text_button(esContext, "HomeLocationGroundTemperatureChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HomeLocationGroundTemperature_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SeaLevelPressure = %i", uavtalk_HomeLocationData.SeaLevelPressure);
		draw_text_button(esContext, "HomeLocationSeaLevelPressureChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HomeLocationSeaLevelPressure_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Set = %i (%s)", uavtalk_HomeLocationData.Set, UAVT_HomeLocationSetOption[uavtalk_HomeLocationData.Set]);
		draw_text_button(esContext, "HomeLocationSetChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HomeLocationSet_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HoTTSettings
***********************************************/

void UAVT_gui_HoTTSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HoTTSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinSpeed = %f", uavtalk_HoTTSettingsData.Limit.MinSpeed);
		draw_text_button(esContext, "HoTTSettingsLimitMinSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinSpeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxSpeed = %f", uavtalk_HoTTSettingsData.Limit.MaxSpeed);
		draw_text_button(esContext, "HoTTSettingsLimitMaxSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxSpeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.NegDifference1 = %f", uavtalk_HoTTSettingsData.Limit.NegDifference1);
		draw_text_button(esContext, "HoTTSettingsLimitNegDifference1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_NegDifference1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.PosDifference1 = %f", uavtalk_HoTTSettingsData.Limit.PosDifference1);
		draw_text_button(esContext, "HoTTSettingsLimitPosDifference1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_PosDifference1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.NegDifference2 = %f", uavtalk_HoTTSettingsData.Limit.NegDifference2);
		draw_text_button(esContext, "HoTTSettingsLimitNegDifference2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_NegDifference2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.PosDifference2 = %f", uavtalk_HoTTSettingsData.Limit.PosDifference2);
		draw_text_button(esContext, "HoTTSettingsLimitPosDifference2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_PosDifference2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinHeight = %f", uavtalk_HoTTSettingsData.Limit.MinHeight);
		draw_text_button(esContext, "HoTTSettingsLimitMinHeightChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinHeight_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxHeight = %f", uavtalk_HoTTSettingsData.Limit.MaxHeight);
		draw_text_button(esContext, "HoTTSettingsLimitMaxHeightChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxHeight_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxDistance = %f", uavtalk_HoTTSettingsData.Limit.MaxDistance);
		draw_text_button(esContext, "HoTTSettingsLimitMaxDistanceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxDistance_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinPowerVoltage = %f", uavtalk_HoTTSettingsData.Limit.MinPowerVoltage);
		draw_text_button(esContext, "HoTTSettingsLimitMinPowerVoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinPowerVoltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxPowerVoltage = %f", uavtalk_HoTTSettingsData.Limit.MaxPowerVoltage);
		draw_text_button(esContext, "HoTTSettingsLimitMaxPowerVoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxPowerVoltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinSensor1Voltage = %f", uavtalk_HoTTSettingsData.Limit.MinSensor1Voltage);
		draw_text_button(esContext, "HoTTSettingsLimitMinSensor1VoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinSensor1Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxSensor1Voltage = %f", uavtalk_HoTTSettingsData.Limit.MaxSensor1Voltage);
		draw_text_button(esContext, "HoTTSettingsLimitMaxSensor1VoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxSensor1Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinSensor2Voltage = %f", uavtalk_HoTTSettingsData.Limit.MinSensor2Voltage);
		draw_text_button(esContext, "HoTTSettingsLimitMinSensor2VoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinSensor2Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxSensor2Voltage = %f", uavtalk_HoTTSettingsData.Limit.MaxSensor2Voltage);
		draw_text_button(esContext, "HoTTSettingsLimitMaxSensor2VoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxSensor2Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinCellVoltage = %f", uavtalk_HoTTSettingsData.Limit.MinCellVoltage);
		draw_text_button(esContext, "HoTTSettingsLimitMinCellVoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinCellVoltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxCurrent = %f", uavtalk_HoTTSettingsData.Limit.MaxCurrent);
		draw_text_button(esContext, "HoTTSettingsLimitMaxCurrentChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxCurrent_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxUsedCapacity = %f", uavtalk_HoTTSettingsData.Limit.MaxUsedCapacity);
		draw_text_button(esContext, "HoTTSettingsLimitMaxUsedCapacityChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxUsedCapacity_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinSensor1Temp = %f", uavtalk_HoTTSettingsData.Limit.MinSensor1Temp);
		draw_text_button(esContext, "HoTTSettingsLimitMinSensor1TempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinSensor1Temp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxSensor1Temp = %f", uavtalk_HoTTSettingsData.Limit.MaxSensor1Temp);
		draw_text_button(esContext, "HoTTSettingsLimitMaxSensor1TempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxSensor1Temp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinSensor2Temp = %f", uavtalk_HoTTSettingsData.Limit.MinSensor2Temp);
		draw_text_button(esContext, "HoTTSettingsLimitMinSensor2TempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinSensor2Temp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxSensor2Temp = %f", uavtalk_HoTTSettingsData.Limit.MaxSensor2Temp);
		draw_text_button(esContext, "HoTTSettingsLimitMaxSensor2TempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxSensor2Temp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxServoTemp = %f", uavtalk_HoTTSettingsData.Limit.MaxServoTemp);
		draw_text_button(esContext, "HoTTSettingsLimitMaxServoTempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxServoTemp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinRPM = %f", uavtalk_HoTTSettingsData.Limit.MinRPM);
		draw_text_button(esContext, "HoTTSettingsLimitMinRPMChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinRPM_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxRPM = %f", uavtalk_HoTTSettingsData.Limit.MaxRPM);
		draw_text_button(esContext, "HoTTSettingsLimitMaxRPMChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxRPM_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MinFuel = %f", uavtalk_HoTTSettingsData.Limit.MinFuel);
		draw_text_button(esContext, "HoTTSettingsLimitMinFuelChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MinFuel_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Limit.MaxServoDifference = %f", uavtalk_HoTTSettingsData.Limit.MaxServoDifference);
		draw_text_button(esContext, "HoTTSettingsLimitMaxServoDifferenceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsLimit_MaxServoDifference_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Sensor.VARIO = %i", uavtalk_HoTTSettingsData.Sensor.VARIO);
		draw_text_button(esContext, "HoTTSettingsSensorVARIOChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsSensor_VARIO_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Sensor.GPS = %i", uavtalk_HoTTSettingsData.Sensor.GPS);
		draw_text_button(esContext, "HoTTSettingsSensorGPSChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HoTTSettingsSensor_GPS_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Sensor.EAM = %i", uavtalk_HoTTSettingsData.Sensor.EAM);
		draw_text_button(esContext, "HoTTSettingsSensorEAMChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HoTTSettingsSensor_EAM_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Sensor.GAM = %i", uavtalk_HoTTSettingsData.Sensor.GAM);
		draw_text_button(esContext, "HoTTSettingsSensorGAMChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HoTTSettingsSensor_GAM_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Sensor.ESC = %i", uavtalk_HoTTSettingsData.Sensor.ESC);
		draw_text_button(esContext, "HoTTSettingsSensorESCChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HoTTSettingsSensor_ESC_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.AltitudeBeep = %i", uavtalk_HoTTSettingsData.Warning.AltitudeBeep);
		draw_text_button(esContext, "HoTTSettingsWarningAltitudeBeepChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_AltitudeBeep_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinSpeed = %i", uavtalk_HoTTSettingsData.Warning.MinSpeed);
		draw_text_button(esContext, "HoTTSettingsWarningMinSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinSpeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxSpeed = %i", uavtalk_HoTTSettingsData.Warning.MaxSpeed);
		draw_text_button(esContext, "HoTTSettingsWarningMaxSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxSpeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.NegDifference1 = %i", uavtalk_HoTTSettingsData.Warning.NegDifference1);
		draw_text_button(esContext, "HoTTSettingsWarningNegDifference1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_NegDifference1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.PosDifference1 = %i", uavtalk_HoTTSettingsData.Warning.PosDifference1);
		draw_text_button(esContext, "HoTTSettingsWarningPosDifference1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_PosDifference1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.NegDifference2 = %i", uavtalk_HoTTSettingsData.Warning.NegDifference2);
		draw_text_button(esContext, "HoTTSettingsWarningNegDifference2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_NegDifference2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.PosDifference2 = %i", uavtalk_HoTTSettingsData.Warning.PosDifference2);
		draw_text_button(esContext, "HoTTSettingsWarningPosDifference2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_PosDifference2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinHeight = %i", uavtalk_HoTTSettingsData.Warning.MinHeight);
		draw_text_button(esContext, "HoTTSettingsWarningMinHeightChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinHeight_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxHeight = %i", uavtalk_HoTTSettingsData.Warning.MaxHeight);
		draw_text_button(esContext, "HoTTSettingsWarningMaxHeightChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxHeight_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxDistance = %i", uavtalk_HoTTSettingsData.Warning.MaxDistance);
		draw_text_button(esContext, "HoTTSettingsWarningMaxDistanceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxDistance_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinPowerVoltage = %i", uavtalk_HoTTSettingsData.Warning.MinPowerVoltage);
		draw_text_button(esContext, "HoTTSettingsWarningMinPowerVoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinPowerVoltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxPowerVoltage = %i", uavtalk_HoTTSettingsData.Warning.MaxPowerVoltage);
		draw_text_button(esContext, "HoTTSettingsWarningMaxPowerVoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxPowerVoltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinSensor1Voltage = %i", uavtalk_HoTTSettingsData.Warning.MinSensor1Voltage);
		draw_text_button(esContext, "HoTTSettingsWarningMinSensor1VoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinSensor1Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxSensor1Voltage = %i", uavtalk_HoTTSettingsData.Warning.MaxSensor1Voltage);
		draw_text_button(esContext, "HoTTSettingsWarningMaxSensor1VoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxSensor1Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinSensor2Voltage = %i", uavtalk_HoTTSettingsData.Warning.MinSensor2Voltage);
		draw_text_button(esContext, "HoTTSettingsWarningMinSensor2VoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinSensor2Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxSensor2Voltage = %i", uavtalk_HoTTSettingsData.Warning.MaxSensor2Voltage);
		draw_text_button(esContext, "HoTTSettingsWarningMaxSensor2VoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxSensor2Voltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinCellVoltage = %i", uavtalk_HoTTSettingsData.Warning.MinCellVoltage);
		draw_text_button(esContext, "HoTTSettingsWarningMinCellVoltageChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinCellVoltage_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxCurrent = %i", uavtalk_HoTTSettingsData.Warning.MaxCurrent);
		draw_text_button(esContext, "HoTTSettingsWarningMaxCurrentChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxCurrent_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxUsedCapacity = %i", uavtalk_HoTTSettingsData.Warning.MaxUsedCapacity);
		draw_text_button(esContext, "HoTTSettingsWarningMaxUsedCapacityChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxUsedCapacity_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinSensor1Temp = %i", uavtalk_HoTTSettingsData.Warning.MinSensor1Temp);
		draw_text_button(esContext, "HoTTSettingsWarningMinSensor1TempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinSensor1Temp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxSensor1Temp = %i", uavtalk_HoTTSettingsData.Warning.MaxSensor1Temp);
		draw_text_button(esContext, "HoTTSettingsWarningMaxSensor1TempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxSensor1Temp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinSensor2Temp = %i", uavtalk_HoTTSettingsData.Warning.MinSensor2Temp);
		draw_text_button(esContext, "HoTTSettingsWarningMinSensor2TempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinSensor2Temp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxSensor2Temp = %i", uavtalk_HoTTSettingsData.Warning.MaxSensor2Temp);
		draw_text_button(esContext, "HoTTSettingsWarningMaxSensor2TempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxSensor2Temp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxServoTemp = %i", uavtalk_HoTTSettingsData.Warning.MaxServoTemp);
		draw_text_button(esContext, "HoTTSettingsWarningMaxServoTempChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxServoTemp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinRPM = %i", uavtalk_HoTTSettingsData.Warning.MinRPM);
		draw_text_button(esContext, "HoTTSettingsWarningMinRPMChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinRPM_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxRPM = %i", uavtalk_HoTTSettingsData.Warning.MaxRPM);
		draw_text_button(esContext, "HoTTSettingsWarningMaxRPMChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxRPM_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MinFuel = %i", uavtalk_HoTTSettingsData.Warning.MinFuel);
		draw_text_button(esContext, "HoTTSettingsWarningMinFuelChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MinFuel_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Warning.MaxServoDifference = %i", uavtalk_HoTTSettingsData.Warning.MaxServoDifference);
		draw_text_button(esContext, "HoTTSettingsWarningMaxServoDifferenceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HoTTSettingsWarning_MaxServoDifference_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwColibri
***********************************************/

void UAVT_gui_HwColibri_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwColibri (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Frame = %i (%s)", uavtalk_HwColibriData.Frame, UAVT_HwColibriFrameOption[uavtalk_HwColibriData.Frame]);
		draw_text_button(esContext, "HwColibriFrameChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriFrame_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwColibriData.RcvrPort, UAVT_HwColibriRcvrPortOption[uavtalk_HwColibriData.RcvrPort]);
		draw_text_button(esContext, "HwColibriRcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriRcvrPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart1 = %i (%s)", uavtalk_HwColibriData.Uart1, UAVT_HwColibriUart1Option[uavtalk_HwColibriData.Uart1]);
		draw_text_button(esContext, "HwColibriUart1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriUart1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart2 = %i (%s)", uavtalk_HwColibriData.Uart2, UAVT_HwColibriUart2Option[uavtalk_HwColibriData.Uart2]);
		draw_text_button(esContext, "HwColibriUart2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriUart2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart3 = %i (%s)", uavtalk_HwColibriData.Uart3, UAVT_HwColibriUart3Option[uavtalk_HwColibriData.Uart3]);
		draw_text_button(esContext, "HwColibriUart3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriUart3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart4 = %i (%s)", uavtalk_HwColibriData.Uart4, UAVT_HwColibriUart4Option[uavtalk_HwColibriData.Uart4]);
		draw_text_button(esContext, "HwColibriUart4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriUart4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwColibriData.USB_HIDPort, UAVT_HwColibriUSB_HIDPortOption[uavtalk_HwColibriData.USB_HIDPort]);
		draw_text_button(esContext, "HwColibriUSB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriUSB_HIDPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwColibriData.USB_VCPPort, UAVT_HwColibriUSB_VCPPortOption[uavtalk_HwColibriData.USB_VCPPort]);
		draw_text_button(esContext, "HwColibriUSB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriUSB_VCPPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwColibriData.DSMxBind);
		draw_text_button(esContext, "HwColibriDSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriDSMxBind_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwColibriData.GyroRange, UAVT_HwColibriGyroRangeOption[uavtalk_HwColibriData.GyroRange]);
		draw_text_button(esContext, "HwColibriGyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriGyroRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwColibriData.AccelRange, UAVT_HwColibriAccelRangeOption[uavtalk_HwColibriData.AccelRange]);
		draw_text_button(esContext, "HwColibriAccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriAccelRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000Rate = %i (%s)", uavtalk_HwColibriData.MPU6000Rate, UAVT_HwColibriMPU6000RateOption[uavtalk_HwColibriData.MPU6000Rate]);
		draw_text_button(esContext, "HwColibriMPU6000RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriMPU6000Rate_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000DLPF = %i (%s)", uavtalk_HwColibriData.MPU6000DLPF, UAVT_HwColibriMPU6000DLPFOption[uavtalk_HwColibriData.MPU6000DLPF]);
		draw_text_button(esContext, "HwColibriMPU6000DLPFChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriMPU6000DLPF_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Magnetometer = %i (%s)", uavtalk_HwColibriData.Magnetometer, UAVT_HwColibriMagnetometerOption[uavtalk_HwColibriData.Magnetometer]);
		draw_text_button(esContext, "HwColibriMagnetometerChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwColibriMagnetometer_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ExtMagOrientation = %i (%s)", uavtalk_HwColibriData.ExtMagOrientation, UAVT_HwColibriExtMagOrientationOption[uavtalk_HwColibriData.ExtMagOrientation]);
		draw_text_button(esContext, "HwColibriExtMagOrientationChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwColibriExtMagOrientation_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwCopterControl
***********************************************/

void UAVT_gui_HwCopterControl_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwCopterControl (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwCopterControlData.RcvrPort, UAVT_HwCopterControlRcvrPortOption[uavtalk_HwCopterControlData.RcvrPort]);
		draw_text_button(esContext, "HwCopterControlRcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlRcvrPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MainPort = %i (%s)", uavtalk_HwCopterControlData.MainPort, UAVT_HwCopterControlMainPortOption[uavtalk_HwCopterControlData.MainPort]);
		draw_text_button(esContext, "HwCopterControlMainPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlMainPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlexiPort = %i (%s)", uavtalk_HwCopterControlData.FlexiPort, UAVT_HwCopterControlFlexiPortOption[uavtalk_HwCopterControlData.FlexiPort]);
		draw_text_button(esContext, "HwCopterControlFlexiPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlFlexiPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwCopterControlData.USB_HIDPort, UAVT_HwCopterControlUSB_HIDPortOption[uavtalk_HwCopterControlData.USB_HIDPort]);
		draw_text_button(esContext, "HwCopterControlUSB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlUSB_HIDPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwCopterControlData.USB_VCPPort, UAVT_HwCopterControlUSB_VCPPortOption[uavtalk_HwCopterControlData.USB_VCPPort]);
		draw_text_button(esContext, "HwCopterControlUSB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlUSB_VCPPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwCopterControlData.DSMxBind);
		draw_text_button(esContext, "HwCopterControlDSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlDSMxBind_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwCopterControlData.GyroRange, UAVT_HwCopterControlGyroRangeOption[uavtalk_HwCopterControlData.GyroRange]);
		draw_text_button(esContext, "HwCopterControlGyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlGyroRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwCopterControlData.AccelRange, UAVT_HwCopterControlAccelRangeOption[uavtalk_HwCopterControlData.AccelRange]);
		draw_text_button(esContext, "HwCopterControlAccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlAccelRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000Rate = %i (%s)", uavtalk_HwCopterControlData.MPU6000Rate, UAVT_HwCopterControlMPU6000RateOption[uavtalk_HwCopterControlData.MPU6000Rate]);
		draw_text_button(esContext, "HwCopterControlMPU6000RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlMPU6000Rate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000DLPF = %i (%s)", uavtalk_HwCopterControlData.MPU6000DLPF, UAVT_HwCopterControlMPU6000DLPFOption[uavtalk_HwCopterControlData.MPU6000DLPF]);
		draw_text_button(esContext, "HwCopterControlMPU6000DLPFChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwCopterControlMPU6000DLPF_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwDiscoveryF4
***********************************************/

void UAVT_gui_HwDiscoveryF4_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwDiscoveryF4 (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MainPort = %i (%s)", uavtalk_HwDiscoveryF4Data.MainPort, UAVT_HwDiscoveryF4MainPortOption[uavtalk_HwDiscoveryF4Data.MainPort]);
		draw_text_button(esContext, "HwDiscoveryF4MainPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwDiscoveryF4MainPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwDiscoveryF4Data.USB_HIDPort, UAVT_HwDiscoveryF4USB_HIDPortOption[uavtalk_HwDiscoveryF4Data.USB_HIDPort]);
		draw_text_button(esContext, "HwDiscoveryF4USB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwDiscoveryF4USB_HIDPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwDiscoveryF4Data.USB_VCPPort, UAVT_HwDiscoveryF4USB_VCPPortOption[uavtalk_HwDiscoveryF4Data.USB_VCPPort]);
		draw_text_button(esContext, "HwDiscoveryF4USB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwDiscoveryF4USB_VCPPort_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwFlyingF3
***********************************************/

void UAVT_gui_HwFlyingF3_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwFlyingF3 (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwFlyingF3Data.RcvrPort, UAVT_HwFlyingF3RcvrPortOption[uavtalk_HwFlyingF3Data.RcvrPort]);
		draw_text_button(esContext, "HwFlyingF3RcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3RcvrPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart1 = %i (%s)", uavtalk_HwFlyingF3Data.Uart1, UAVT_HwFlyingF3Uart1Option[uavtalk_HwFlyingF3Data.Uart1]);
		draw_text_button(esContext, "HwFlyingF3Uart1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3Uart1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart2 = %i (%s)", uavtalk_HwFlyingF3Data.Uart2, UAVT_HwFlyingF3Uart2Option[uavtalk_HwFlyingF3Data.Uart2]);
		draw_text_button(esContext, "HwFlyingF3Uart2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3Uart2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart3 = %i (%s)", uavtalk_HwFlyingF3Data.Uart3, UAVT_HwFlyingF3Uart3Option[uavtalk_HwFlyingF3Data.Uart3]);
		draw_text_button(esContext, "HwFlyingF3Uart3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3Uart3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart4 = %i (%s)", uavtalk_HwFlyingF3Data.Uart4, UAVT_HwFlyingF3Uart4Option[uavtalk_HwFlyingF3Data.Uart4]);
		draw_text_button(esContext, "HwFlyingF3Uart4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3Uart4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart5 = %i (%s)", uavtalk_HwFlyingF3Data.Uart5, UAVT_HwFlyingF3Uart5Option[uavtalk_HwFlyingF3Data.Uart5]);
		draw_text_button(esContext, "HwFlyingF3Uart5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3Uart5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwFlyingF3Data.USB_HIDPort, UAVT_HwFlyingF3USB_HIDPortOption[uavtalk_HwFlyingF3Data.USB_HIDPort]);
		draw_text_button(esContext, "HwFlyingF3USB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3USB_HIDPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwFlyingF3Data.USB_VCPPort, UAVT_HwFlyingF3USB_VCPPortOption[uavtalk_HwFlyingF3Data.USB_VCPPort]);
		draw_text_button(esContext, "HwFlyingF3USB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3USB_VCPPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwFlyingF3Data.DSMxBind);
		draw_text_button(esContext, "HwFlyingF3DSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3DSMxBind_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwFlyingF3Data.GyroRange, UAVT_HwFlyingF3GyroRangeOption[uavtalk_HwFlyingF3Data.GyroRange]);
		draw_text_button(esContext, "HwFlyingF3GyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3GyroRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "L3GD20Rate = %i (%s)", uavtalk_HwFlyingF3Data.L3GD20Rate, UAVT_HwFlyingF3L3GD20RateOption[uavtalk_HwFlyingF3Data.L3GD20Rate]);
		draw_text_button(esContext, "HwFlyingF3L3GD20RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3L3GD20Rate_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwFlyingF3Data.AccelRange, UAVT_HwFlyingF3AccelRangeOption[uavtalk_HwFlyingF3Data.AccelRange]);
		draw_text_button(esContext, "HwFlyingF3AccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3AccelRange_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Shield = %i (%s)", uavtalk_HwFlyingF3Data.Shield, UAVT_HwFlyingF3ShieldOption[uavtalk_HwFlyingF3Data.Shield]);
		draw_text_button(esContext, "HwFlyingF3ShieldChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF3Shield_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwFlyingF4
***********************************************/

void UAVT_gui_HwFlyingF4_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwFlyingF4 (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwFlyingF4Data.RcvrPort, UAVT_HwFlyingF4RcvrPortOption[uavtalk_HwFlyingF4Data.RcvrPort]);
		draw_text_button(esContext, "HwFlyingF4RcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4RcvrPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart1 = %i (%s)", uavtalk_HwFlyingF4Data.Uart1, UAVT_HwFlyingF4Uart1Option[uavtalk_HwFlyingF4Data.Uart1]);
		draw_text_button(esContext, "HwFlyingF4Uart1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4Uart1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart2 = %i (%s)", uavtalk_HwFlyingF4Data.Uart2, UAVT_HwFlyingF4Uart2Option[uavtalk_HwFlyingF4Data.Uart2]);
		draw_text_button(esContext, "HwFlyingF4Uart2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4Uart2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart3 = %i (%s)", uavtalk_HwFlyingF4Data.Uart3, UAVT_HwFlyingF4Uart3Option[uavtalk_HwFlyingF4Data.Uart3]);
		draw_text_button(esContext, "HwFlyingF4Uart3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4Uart3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwFlyingF4Data.USB_HIDPort, UAVT_HwFlyingF4USB_HIDPortOption[uavtalk_HwFlyingF4Data.USB_HIDPort]);
		draw_text_button(esContext, "HwFlyingF4USB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4USB_HIDPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwFlyingF4Data.USB_VCPPort, UAVT_HwFlyingF4USB_VCPPortOption[uavtalk_HwFlyingF4Data.USB_VCPPort]);
		draw_text_button(esContext, "HwFlyingF4USB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4USB_VCPPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwFlyingF4Data.DSMxBind);
		draw_text_button(esContext, "HwFlyingF4DSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4DSMxBind_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwFlyingF4Data.GyroRange, UAVT_HwFlyingF4GyroRangeOption[uavtalk_HwFlyingF4Data.GyroRange]);
		draw_text_button(esContext, "HwFlyingF4GyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4GyroRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwFlyingF4Data.AccelRange, UAVT_HwFlyingF4AccelRangeOption[uavtalk_HwFlyingF4Data.AccelRange]);
		draw_text_button(esContext, "HwFlyingF4AccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4AccelRange_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6050Rate = %i (%s)", uavtalk_HwFlyingF4Data.MPU6050Rate, UAVT_HwFlyingF4MPU6050RateOption[uavtalk_HwFlyingF4Data.MPU6050Rate]);
		draw_text_button(esContext, "HwFlyingF4MPU6050RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4MPU6050Rate_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6050DLPF = %i (%s)", uavtalk_HwFlyingF4Data.MPU6050DLPF, UAVT_HwFlyingF4MPU6050DLPFOption[uavtalk_HwFlyingF4Data.MPU6050DLPF]);
		draw_text_button(esContext, "HwFlyingF4MPU6050DLPFChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4MPU6050DLPF_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Magnetometer = %i (%s)", uavtalk_HwFlyingF4Data.Magnetometer, UAVT_HwFlyingF4MagnetometerOption[uavtalk_HwFlyingF4Data.Magnetometer]);
		draw_text_button(esContext, "HwFlyingF4MagnetometerChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFlyingF4Magnetometer_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ExtMagOrientation = %i (%s)", uavtalk_HwFlyingF4Data.ExtMagOrientation, UAVT_HwFlyingF4ExtMagOrientationOption[uavtalk_HwFlyingF4Data.ExtMagOrientation]);
		draw_text_button(esContext, "HwFlyingF4ExtMagOrientationChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwFlyingF4ExtMagOrientation_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwFreedom
***********************************************/

void UAVT_gui_HwFreedom_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwFreedom (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Output = %i (%s)", uavtalk_HwFreedomData.Output, UAVT_HwFreedomOutputOption[uavtalk_HwFreedomData.Output]);
		draw_text_button(esContext, "HwFreedomOutputChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomOutput_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MainPort = %i (%s)", uavtalk_HwFreedomData.MainPort, UAVT_HwFreedomMainPortOption[uavtalk_HwFreedomData.MainPort]);
		draw_text_button(esContext, "HwFreedomMainPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomMainPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlexiPort = %i (%s)", uavtalk_HwFreedomData.FlexiPort, UAVT_HwFreedomFlexiPortOption[uavtalk_HwFreedomData.FlexiPort]);
		draw_text_button(esContext, "HwFreedomFlexiPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomFlexiPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwFreedomData.RcvrPort, UAVT_HwFreedomRcvrPortOption[uavtalk_HwFreedomData.RcvrPort]);
		draw_text_button(esContext, "HwFreedomRcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomRcvrPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RadioPort = %i (%s)", uavtalk_HwFreedomData.RadioPort, UAVT_HwFreedomRadioPortOption[uavtalk_HwFreedomData.RadioPort]);
		draw_text_button(esContext, "HwFreedomRadioPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomRadioPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwFreedomData.USB_HIDPort, UAVT_HwFreedomUSB_HIDPortOption[uavtalk_HwFreedomData.USB_HIDPort]);
		draw_text_button(esContext, "HwFreedomUSB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomUSB_HIDPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwFreedomData.USB_VCPPort, UAVT_HwFreedomUSB_VCPPortOption[uavtalk_HwFreedomData.USB_VCPPort]);
		draw_text_button(esContext, "HwFreedomUSB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomUSB_VCPPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwFreedomData.DSMxBind);
		draw_text_button(esContext, "HwFreedomDSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomDSMxBind_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwFreedomData.GyroRange, UAVT_HwFreedomGyroRangeOption[uavtalk_HwFreedomData.GyroRange]);
		draw_text_button(esContext, "HwFreedomGyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomGyroRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwFreedomData.AccelRange, UAVT_HwFreedomAccelRangeOption[uavtalk_HwFreedomData.AccelRange]);
		draw_text_button(esContext, "HwFreedomAccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomAccelRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000Rate = %i (%s)", uavtalk_HwFreedomData.MPU6000Rate, UAVT_HwFreedomMPU6000RateOption[uavtalk_HwFreedomData.MPU6000Rate]);
		draw_text_button(esContext, "HwFreedomMPU6000RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomMPU6000Rate_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000DLPF = %i (%s)", uavtalk_HwFreedomData.MPU6000DLPF, UAVT_HwFreedomMPU6000DLPFOption[uavtalk_HwFreedomData.MPU6000DLPF]);
		draw_text_button(esContext, "HwFreedomMPU6000DLPFChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwFreedomMPU6000DLPF_change,
						 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwQuanton
***********************************************/

void UAVT_gui_HwQuanton_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwQuanton (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwQuantonData.RcvrPort, UAVT_HwQuantonRcvrPortOption[uavtalk_HwQuantonData.RcvrPort]);
		draw_text_button(esContext, "HwQuantonRcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonRcvrPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart1 = %i (%s)", uavtalk_HwQuantonData.Uart1, UAVT_HwQuantonUart1Option[uavtalk_HwQuantonData.Uart1]);
		draw_text_button(esContext, "HwQuantonUart1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonUart1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart2 = %i (%s)", uavtalk_HwQuantonData.Uart2, UAVT_HwQuantonUart2Option[uavtalk_HwQuantonData.Uart2]);
		draw_text_button(esContext, "HwQuantonUart2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonUart2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart3 = %i (%s)", uavtalk_HwQuantonData.Uart3, UAVT_HwQuantonUart3Option[uavtalk_HwQuantonData.Uart3]);
		draw_text_button(esContext, "HwQuantonUart3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonUart3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart4 = %i (%s)", uavtalk_HwQuantonData.Uart4, UAVT_HwQuantonUart4Option[uavtalk_HwQuantonData.Uart4]);
		draw_text_button(esContext, "HwQuantonUart4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonUart4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Uart5 = %i (%s)", uavtalk_HwQuantonData.Uart5, UAVT_HwQuantonUart5Option[uavtalk_HwQuantonData.Uart5]);
		draw_text_button(esContext, "HwQuantonUart5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonUart5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwQuantonData.USB_HIDPort, UAVT_HwQuantonUSB_HIDPortOption[uavtalk_HwQuantonData.USB_HIDPort]);
		draw_text_button(esContext, "HwQuantonUSB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonUSB_HIDPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwQuantonData.USB_VCPPort, UAVT_HwQuantonUSB_VCPPortOption[uavtalk_HwQuantonData.USB_VCPPort]);
		draw_text_button(esContext, "HwQuantonUSB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonUSB_VCPPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwQuantonData.DSMxBind);
		draw_text_button(esContext, "HwQuantonDSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonDSMxBind_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwQuantonData.GyroRange, UAVT_HwQuantonGyroRangeOption[uavtalk_HwQuantonData.GyroRange]);
		draw_text_button(esContext, "HwQuantonGyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonGyroRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwQuantonData.AccelRange, UAVT_HwQuantonAccelRangeOption[uavtalk_HwQuantonData.AccelRange]);
		draw_text_button(esContext, "HwQuantonAccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonAccelRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000Rate = %i (%s)", uavtalk_HwQuantonData.MPU6000Rate, UAVT_HwQuantonMPU6000RateOption[uavtalk_HwQuantonData.MPU6000Rate]);
		draw_text_button(esContext, "HwQuantonMPU6000RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonMPU6000Rate_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000DLPF = %i (%s)", uavtalk_HwQuantonData.MPU6000DLPF, UAVT_HwQuantonMPU6000DLPFOption[uavtalk_HwQuantonData.MPU6000DLPF]);
		draw_text_button(esContext, "HwQuantonMPU6000DLPFChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonMPU6000DLPF_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Magnetometer = %i (%s)", uavtalk_HwQuantonData.Magnetometer, UAVT_HwQuantonMagnetometerOption[uavtalk_HwQuantonData.Magnetometer]);
		draw_text_button(esContext, "HwQuantonMagnetometerChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwQuantonMagnetometer_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ExtMagOrientation = %i (%s)", uavtalk_HwQuantonData.ExtMagOrientation, UAVT_HwQuantonExtMagOrientationOption[uavtalk_HwQuantonData.ExtMagOrientation]);
		draw_text_button(esContext, "HwQuantonExtMagOrientationChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwQuantonExtMagOrientation_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwRevolution
***********************************************/

void UAVT_gui_HwRevolution_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwRevolution (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwRevolutionData.RcvrPort, UAVT_HwRevolutionRcvrPortOption[uavtalk_HwRevolutionData.RcvrPort]);
		draw_text_button(esContext, "HwRevolutionRcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevolutionRcvrPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AuxPort = %i (%s)", uavtalk_HwRevolutionData.AuxPort, UAVT_HwRevolutionAuxPortOption[uavtalk_HwRevolutionData.AuxPort]);
		draw_text_button(esContext, "HwRevolutionAuxPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevolutionAuxPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AuxSBusPort = %i (%s)", uavtalk_HwRevolutionData.AuxSBusPort, UAVT_HwRevolutionAuxSBusPortOption[uavtalk_HwRevolutionData.AuxSBusPort]);
		draw_text_button(esContext, "HwRevolutionAuxSBusPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwRevolutionAuxSBusPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlexiPort = %i (%s)", uavtalk_HwRevolutionData.FlexiPort, UAVT_HwRevolutionFlexiPortOption[uavtalk_HwRevolutionData.FlexiPort]);
		draw_text_button(esContext, "HwRevolutionFlexiPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevolutionFlexiPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "TelemetryPort = %i (%s)", uavtalk_HwRevolutionData.TelemetryPort, UAVT_HwRevolutionTelemetryPortOption[uavtalk_HwRevolutionData.TelemetryPort]);
		draw_text_button(esContext, "HwRevolutionTelemetryPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwRevolutionTelemetryPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GPSPort = %i (%s)", uavtalk_HwRevolutionData.GPSPort, UAVT_HwRevolutionGPSPortOption[uavtalk_HwRevolutionData.GPSPort]);
		draw_text_button(esContext, "HwRevolutionGPSPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevolutionGPSPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwRevolutionData.USB_HIDPort, UAVT_HwRevolutionUSB_HIDPortOption[uavtalk_HwRevolutionData.USB_HIDPort]);
		draw_text_button(esContext, "HwRevolutionUSB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwRevolutionUSB_HIDPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwRevolutionData.USB_VCPPort, UAVT_HwRevolutionUSB_VCPPortOption[uavtalk_HwRevolutionData.USB_VCPPort]);
		draw_text_button(esContext, "HwRevolutionUSB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwRevolutionUSB_VCPPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwRevolutionData.DSMxBind);
		draw_text_button(esContext, "HwRevolutionDSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevolutionDSMxBind_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwRevolutionData.GyroRange, UAVT_HwRevolutionGyroRangeOption[uavtalk_HwRevolutionData.GyroRange]);
		draw_text_button(esContext, "HwRevolutionGyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevolutionGyroRange_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwRevolutionData.AccelRange, UAVT_HwRevolutionAccelRangeOption[uavtalk_HwRevolutionData.AccelRange]);
		draw_text_button(esContext, "HwRevolutionAccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevolutionAccelRange_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000Rate = %i (%s)", uavtalk_HwRevolutionData.MPU6000Rate, UAVT_HwRevolutionMPU6000RateOption[uavtalk_HwRevolutionData.MPU6000Rate]);
		draw_text_button(esContext, "HwRevolutionMPU6000RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwRevolutionMPU6000Rate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000DLPF = %i (%s)", uavtalk_HwRevolutionData.MPU6000DLPF, UAVT_HwRevolutionMPU6000DLPFOption[uavtalk_HwRevolutionData.MPU6000DLPF]);
		draw_text_button(esContext, "HwRevolutionMPU6000DLPFChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_HwRevolutionMPU6000DLPF_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwRevoMini
***********************************************/

void UAVT_gui_HwRevoMini_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwRevoMini (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwRevoMiniData.RcvrPort, UAVT_HwRevoMiniRcvrPortOption[uavtalk_HwRevoMiniData.RcvrPort]);
		draw_text_button(esContext, "HwRevoMiniRcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniRcvrPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MainPort = %i (%s)", uavtalk_HwRevoMiniData.MainPort, UAVT_HwRevoMiniMainPortOption[uavtalk_HwRevoMiniData.MainPort]);
		draw_text_button(esContext, "HwRevoMiniMainPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniMainPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlexiPort = %i (%s)", uavtalk_HwRevoMiniData.FlexiPort, UAVT_HwRevoMiniFlexiPortOption[uavtalk_HwRevoMiniData.FlexiPort]);
		draw_text_button(esContext, "HwRevoMiniFlexiPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniFlexiPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RadioPort = %i (%s)", uavtalk_HwRevoMiniData.RadioPort, UAVT_HwRevoMiniRadioPortOption[uavtalk_HwRevoMiniData.RadioPort]);
		draw_text_button(esContext, "HwRevoMiniRadioPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniRadioPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwRevoMiniData.USB_HIDPort, UAVT_HwRevoMiniUSB_HIDPortOption[uavtalk_HwRevoMiniData.USB_HIDPort]);
		draw_text_button(esContext, "HwRevoMiniUSB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniUSB_HIDPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwRevoMiniData.USB_VCPPort, UAVT_HwRevoMiniUSB_VCPPortOption[uavtalk_HwRevoMiniData.USB_VCPPort]);
		draw_text_button(esContext, "HwRevoMiniUSB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniUSB_VCPPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwRevoMiniData.DSMxBind);
		draw_text_button(esContext, "HwRevoMiniDSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniDSMxBind_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwRevoMiniData.GyroRange, UAVT_HwRevoMiniGyroRangeOption[uavtalk_HwRevoMiniData.GyroRange]);
		draw_text_button(esContext, "HwRevoMiniGyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniGyroRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwRevoMiniData.AccelRange, UAVT_HwRevoMiniAccelRangeOption[uavtalk_HwRevoMiniData.AccelRange]);
		draw_text_button(esContext, "HwRevoMiniAccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniAccelRange_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000Rate = %i (%s)", uavtalk_HwRevoMiniData.MPU6000Rate, UAVT_HwRevoMiniMPU6000RateOption[uavtalk_HwRevoMiniData.MPU6000Rate]);
		draw_text_button(esContext, "HwRevoMiniMPU6000RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniMPU6000Rate_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU6000DLPF = %i (%s)", uavtalk_HwRevoMiniData.MPU6000DLPF, UAVT_HwRevoMiniMPU6000DLPFOption[uavtalk_HwRevoMiniData.MPU6000DLPF]);
		draw_text_button(esContext, "HwRevoMiniMPU6000DLPFChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwRevoMiniMPU6000DLPF_change,
						 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwSparkyBGC
***********************************************/

void UAVT_gui_HwSparkyBGC_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwSparkyBGC (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwSparkyBGCData.RcvrPort, UAVT_HwSparkyBGCRcvrPortOption[uavtalk_HwSparkyBGCData.RcvrPort]);
		draw_text_button(esContext, "HwSparkyBGCRcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyBGCRcvrPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlexiPort = %i (%s)", uavtalk_HwSparkyBGCData.FlexiPort, UAVT_HwSparkyBGCFlexiPortOption[uavtalk_HwSparkyBGCData.FlexiPort]);
		draw_text_button(esContext, "HwSparkyBGCFlexiPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyBGCFlexiPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwSparkyBGCData.USB_HIDPort, UAVT_HwSparkyBGCUSB_HIDPortOption[uavtalk_HwSparkyBGCData.USB_HIDPort]);
		draw_text_button(esContext, "HwSparkyBGCUSB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyBGCUSB_HIDPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwSparkyBGCData.USB_VCPPort, UAVT_HwSparkyBGCUSB_VCPPortOption[uavtalk_HwSparkyBGCData.USB_VCPPort]);
		draw_text_button(esContext, "HwSparkyBGCUSB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyBGCUSB_VCPPort_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwSparkyBGCData.DSMxBind);
		draw_text_button(esContext, "HwSparkyBGCDSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyBGCDSMxBind_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwSparkyBGCData.GyroRange, UAVT_HwSparkyBGCGyroRangeOption[uavtalk_HwSparkyBGCData.GyroRange]);
		draw_text_button(esContext, "HwSparkyBGCGyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyBGCGyroRange_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwSparkyBGCData.AccelRange, UAVT_HwSparkyBGCAccelRangeOption[uavtalk_HwSparkyBGCData.AccelRange]);
		draw_text_button(esContext, "HwSparkyBGCAccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyBGCAccelRange_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU9150DLPF = %i (%s)", uavtalk_HwSparkyBGCData.MPU9150DLPF, UAVT_HwSparkyBGCMPU9150DLPFOption[uavtalk_HwSparkyBGCData.MPU9150DLPF]);
		draw_text_button(esContext, "HwSparkyBGCMPU9150DLPFChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyBGCMPU9150DLPF_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU9150Rate = %i (%s)", uavtalk_HwSparkyBGCData.MPU9150Rate, UAVT_HwSparkyBGCMPU9150RateOption[uavtalk_HwSparkyBGCData.MPU9150Rate]);
		draw_text_button(esContext, "HwSparkyBGCMPU9150RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyBGCMPU9150Rate_change,
						 0.0);
	}
	nn++;
}

/***********************************************
    Object: HwSparky
***********************************************/

void UAVT_gui_HwSparky_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "HwSparky (HardwareSettings)");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RcvrPort = %i (%s)", uavtalk_HwSparkyData.RcvrPort, UAVT_HwSparkyRcvrPortOption[uavtalk_HwSparkyData.RcvrPort]);
		draw_text_button(esContext, "HwSparkyRcvrPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyRcvrPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlexiPort = %i (%s)", uavtalk_HwSparkyData.FlexiPort, UAVT_HwSparkyFlexiPortOption[uavtalk_HwSparkyData.FlexiPort]);
		draw_text_button(esContext, "HwSparkyFlexiPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyFlexiPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MainPort = %i (%s)", uavtalk_HwSparkyData.MainPort, UAVT_HwSparkyMainPortOption[uavtalk_HwSparkyData.MainPort]);
		draw_text_button(esContext, "HwSparkyMainPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyMainPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "OutPort = %i (%s)", uavtalk_HwSparkyData.OutPort, UAVT_HwSparkyOutPortOption[uavtalk_HwSparkyData.OutPort]);
		draw_text_button(esContext, "HwSparkyOutPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyOutPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_HIDPort = %i (%s)", uavtalk_HwSparkyData.USB_HIDPort, UAVT_HwSparkyUSB_HIDPortOption[uavtalk_HwSparkyData.USB_HIDPort]);
		draw_text_button(esContext, "HwSparkyUSB_HIDPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyUSB_HIDPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "USB_VCPPort = %i (%s)", uavtalk_HwSparkyData.USB_VCPPort, UAVT_HwSparkyUSB_VCPPortOption[uavtalk_HwSparkyData.USB_VCPPort]);
		draw_text_button(esContext, "HwSparkyUSB_VCPPortChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyUSB_VCPPort_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DSMxBind = %i", uavtalk_HwSparkyData.DSMxBind);
		draw_text_button(esContext, "HwSparkyDSMxBindChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyDSMxBind_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroRange = %i (%s)", uavtalk_HwSparkyData.GyroRange, UAVT_HwSparkyGyroRangeOption[uavtalk_HwSparkyData.GyroRange]);
		draw_text_button(esContext, "HwSparkyGyroRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyGyroRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelRange = %i (%s)", uavtalk_HwSparkyData.AccelRange, UAVT_HwSparkyAccelRangeOption[uavtalk_HwSparkyData.AccelRange]);
		draw_text_button(esContext, "HwSparkyAccelRangeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyAccelRange_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU9150DLPF = %i (%s)", uavtalk_HwSparkyData.MPU9150DLPF, UAVT_HwSparkyMPU9150DLPFOption[uavtalk_HwSparkyData.MPU9150DLPF]);
		draw_text_button(esContext, "HwSparkyMPU9150DLPFChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyMPU9150DLPF_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MPU9150Rate = %i (%s)", uavtalk_HwSparkyData.MPU9150Rate, UAVT_HwSparkyMPU9150RateOption[uavtalk_HwSparkyData.MPU9150Rate]);
		draw_text_button(esContext, "HwSparkyMPU9150RateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_HwSparkyMPU9150Rate_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: I2CVMUserProgram
***********************************************/

void UAVT_gui_I2CVMUserProgram_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "I2CVMUserProgram ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program0 = %i", uavtalk_I2CVMUserProgramData.Program[0]);
		draw_text_button(esContext, "I2CVMUserProgramProgram0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program1 = %i", uavtalk_I2CVMUserProgramData.Program[1]);
		draw_text_button(esContext, "I2CVMUserProgramProgram1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program2 = %i", uavtalk_I2CVMUserProgramData.Program[2]);
		draw_text_button(esContext, "I2CVMUserProgramProgram2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program3 = %i", uavtalk_I2CVMUserProgramData.Program[3]);
		draw_text_button(esContext, "I2CVMUserProgramProgram3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program4 = %i", uavtalk_I2CVMUserProgramData.Program[4]);
		draw_text_button(esContext, "I2CVMUserProgramProgram4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program5 = %i", uavtalk_I2CVMUserProgramData.Program[5]);
		draw_text_button(esContext, "I2CVMUserProgramProgram5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program6 = %i", uavtalk_I2CVMUserProgramData.Program[6]);
		draw_text_button(esContext, "I2CVMUserProgramProgram6Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_6_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program7 = %i", uavtalk_I2CVMUserProgramData.Program[7]);
		draw_text_button(esContext, "I2CVMUserProgramProgram7Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_7_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program8 = %i", uavtalk_I2CVMUserProgramData.Program[8]);
		draw_text_button(esContext, "I2CVMUserProgramProgram8Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_8_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program9 = %i", uavtalk_I2CVMUserProgramData.Program[9]);
		draw_text_button(esContext, "I2CVMUserProgramProgram9Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_9_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program10 = %i", uavtalk_I2CVMUserProgramData.Program[10]);
		draw_text_button(esContext, "I2CVMUserProgramProgram10Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_10_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program11 = %i", uavtalk_I2CVMUserProgramData.Program[11]);
		draw_text_button(esContext, "I2CVMUserProgramProgram11Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_11_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program12 = %i", uavtalk_I2CVMUserProgramData.Program[12]);
		draw_text_button(esContext, "I2CVMUserProgramProgram12Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_12_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program13 = %i", uavtalk_I2CVMUserProgramData.Program[13]);
		draw_text_button(esContext, "I2CVMUserProgramProgram13Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_13_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program14 = %i", uavtalk_I2CVMUserProgramData.Program[14]);
		draw_text_button(esContext, "I2CVMUserProgramProgram14Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_14_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program15 = %i", uavtalk_I2CVMUserProgramData.Program[15]);
		draw_text_button(esContext, "I2CVMUserProgramProgram15Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_15_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program16 = %i", uavtalk_I2CVMUserProgramData.Program[16]);
		draw_text_button(esContext, "I2CVMUserProgramProgram16Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_16_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program17 = %i", uavtalk_I2CVMUserProgramData.Program[17]);
		draw_text_button(esContext, "I2CVMUserProgramProgram17Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_17_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program18 = %i", uavtalk_I2CVMUserProgramData.Program[18]);
		draw_text_button(esContext, "I2CVMUserProgramProgram18Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_18_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Program19 = %i", uavtalk_I2CVMUserProgramData.Program[19]);
		draw_text_button(esContext, "I2CVMUserProgramProgram19Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_I2CVMUserProgramProgram_19_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: INSSettings
***********************************************/

void UAVT_gui_INSSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "INSSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "accel_var.X = %f", uavtalk_INSSettingsData.accel_var.X);
		draw_text_button(esContext, "INSSettingsaccel_varXChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsaccel_var_X_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "accel_var.Y = %f", uavtalk_INSSettingsData.accel_var.Y);
		draw_text_button(esContext, "INSSettingsaccel_varYChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsaccel_var_Y_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "accel_var.Z = %f", uavtalk_INSSettingsData.accel_var.Z);
		draw_text_button(esContext, "INSSettingsaccel_varZChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsaccel_var_Z_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "gyro_var.X = %f", uavtalk_INSSettingsData.gyro_var.X);
		draw_text_button(esContext, "INSSettingsgyro_varXChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsgyro_var_X_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "gyro_var.Y = %f", uavtalk_INSSettingsData.gyro_var.Y);
		draw_text_button(esContext, "INSSettingsgyro_varYChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsgyro_var_Y_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "gyro_var.Z = %f", uavtalk_INSSettingsData.gyro_var.Z);
		draw_text_button(esContext, "INSSettingsgyro_varZChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsgyro_var_Z_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "mag_var.X = %f", uavtalk_INSSettingsData.mag_var.X);
		draw_text_button(esContext, "INSSettingsmag_varXChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsmag_var_X_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "mag_var.Y = %f", uavtalk_INSSettingsData.mag_var.Y);
		draw_text_button(esContext, "INSSettingsmag_varYChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsmag_var_Y_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "mag_var.Z = %f", uavtalk_INSSettingsData.mag_var.Z);
		draw_text_button(esContext, "INSSettingsmag_varZChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsmag_var_Z_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "gps_var.Pos = %f", uavtalk_INSSettingsData.gps_var.Pos);
		draw_text_button(esContext, "INSSettingsgps_varPosChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsgps_var_Pos_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "gps_var.Vel = %f", uavtalk_INSSettingsData.gps_var.Vel);
		draw_text_button(esContext, "INSSettingsgps_varVelChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsgps_var_Vel_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "gps_var.VertPos = %f", uavtalk_INSSettingsData.gps_var.VertPos);
		draw_text_button(esContext, "INSSettingsgps_varVertPosChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_INSSettingsgps_var_VertPos_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "baro_var = %f", uavtalk_INSSettingsData.baro_var);
		draw_text_button(esContext, "INSSettingsbaro_varChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_INSSettingsbaro_var_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MagBiasNullingRate = %f", uavtalk_INSSettingsData.MagBiasNullingRate);
		draw_text_button(esContext, "INSSettingsMagBiasNullingRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_INSSettingsMagBiasNullingRate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ComputeGyroBias = %i (%s)", uavtalk_INSSettingsData.ComputeGyroBias, UAVT_INSSettingsComputeGyroBiasOption[uavtalk_INSSettingsData.ComputeGyroBias]);
		draw_text_button(esContext, "INSSettingsComputeGyroBiasChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_INSSettingsComputeGyroBias_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: LoggingSettings
***********************************************/

void UAVT_gui_LoggingSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "LoggingSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "LogBehavior = %i (%s)", uavtalk_LoggingSettingsData.LogBehavior, UAVT_LoggingSettingsLogBehaviorOption[uavtalk_LoggingSettingsData.LogBehavior]);
		draw_text_button(esContext, "LoggingSettingsLogBehaviorChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_LoggingSettingsLogBehavior_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: ManualControlSettings
***********************************************/

void UAVT_gui_ManualControlSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "ManualControlSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Deadband = %f", uavtalk_ManualControlSettingsData.Deadband);
		draw_text_button(esContext, "ManualControlSettingsDeadbandChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsDeadband_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RssiMax = %i", uavtalk_ManualControlSettingsData.RssiMax);
		draw_text_button(esContext, "ManualControlSettingsRssiMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsRssiMax_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RssiMin = %i", uavtalk_ManualControlSettingsData.RssiMin);
		draw_text_button(esContext, "ManualControlSettingsRssiMinChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsRssiMin_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RssiPwmPeriod = %i", uavtalk_ManualControlSettingsData.RssiPwmPeriod);
		draw_text_button(esContext, "ManualControlSettingsRssiPwmPeriodChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsRssiPwmPeriod_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.Throttle = %i", uavtalk_ManualControlSettingsData.ChannelMin.Throttle);
		draw_text_button(esContext, "ManualControlSettingsChannelMinThrottleChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_Throttle_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.Roll = %i", uavtalk_ManualControlSettingsData.ChannelMin.Roll);
		draw_text_button(esContext, "ManualControlSettingsChannelMinRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.Pitch = %i", uavtalk_ManualControlSettingsData.ChannelMin.Pitch);
		draw_text_button(esContext, "ManualControlSettingsChannelMinPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.Yaw = %i", uavtalk_ManualControlSettingsData.ChannelMin.Yaw);
		draw_text_button(esContext, "ManualControlSettingsChannelMinYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.FlightMode = %i", uavtalk_ManualControlSettingsData.ChannelMin.FlightMode);
		draw_text_button(esContext, "ManualControlSettingsChannelMinFlightModeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_FlightMode_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.Collective = %i", uavtalk_ManualControlSettingsData.ChannelMin.Collective);
		draw_text_button(esContext, "ManualControlSettingsChannelMinCollectiveChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_Collective_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.Accessory0 = %i", uavtalk_ManualControlSettingsData.ChannelMin.Accessory0);
		draw_text_button(esContext, "ManualControlSettingsChannelMinAccessory0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_Accessory0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.Accessory1 = %i", uavtalk_ManualControlSettingsData.ChannelMin.Accessory1);
		draw_text_button(esContext, "ManualControlSettingsChannelMinAccessory1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_Accessory1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.Accessory2 = %i", uavtalk_ManualControlSettingsData.ChannelMin.Accessory2);
		draw_text_button(esContext, "ManualControlSettingsChannelMinAccessory2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_Accessory2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMin.Arming = %i", uavtalk_ManualControlSettingsData.ChannelMin.Arming);
		draw_text_button(esContext, "ManualControlSettingsChannelMinArmingChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMin_Arming_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.Throttle = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.Throttle);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralThrottleChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_Throttle_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.Roll = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.Roll);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.Pitch = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.Pitch);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.Yaw = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.Yaw);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.FlightMode = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.FlightMode);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralFlightModeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_FlightMode_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.Collective = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.Collective);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralCollectiveChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_Collective_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.Accessory0 = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory0);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralAccessory0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_Accessory0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.Accessory1 = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory1);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralAccessory1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_Accessory1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.Accessory2 = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.Accessory2);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralAccessory2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_Accessory2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNeutral.Arming = %i", uavtalk_ManualControlSettingsData.ChannelNeutral.Arming);
		draw_text_button(esContext, "ManualControlSettingsChannelNeutralArmingChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNeutral_Arming_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.Throttle = %i", uavtalk_ManualControlSettingsData.ChannelMax.Throttle);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxThrottleChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_Throttle_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.Roll = %i", uavtalk_ManualControlSettingsData.ChannelMax.Roll);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.Pitch = %i", uavtalk_ManualControlSettingsData.ChannelMax.Pitch);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.Yaw = %i", uavtalk_ManualControlSettingsData.ChannelMax.Yaw);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.FlightMode = %i", uavtalk_ManualControlSettingsData.ChannelMax.FlightMode);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxFlightModeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_FlightMode_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.Collective = %i", uavtalk_ManualControlSettingsData.ChannelMax.Collective);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxCollectiveChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_Collective_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.Accessory0 = %i", uavtalk_ManualControlSettingsData.ChannelMax.Accessory0);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxAccessory0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_Accessory0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.Accessory1 = %i", uavtalk_ManualControlSettingsData.ChannelMax.Accessory1);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxAccessory1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_Accessory1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.Accessory2 = %i", uavtalk_ManualControlSettingsData.ChannelMax.Accessory2);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxAccessory2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_Accessory2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelMax.Arming = %i", uavtalk_ManualControlSettingsData.ChannelMax.Arming);
		draw_text_button(esContext, "ManualControlSettingsChannelMaxArmingChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelMax_Arming_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ArmedTimeout = %i", uavtalk_ManualControlSettingsData.ArmedTimeout);
		draw_text_button(esContext, "ManualControlSettingsArmedTimeoutChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsArmedTimeout_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.Throttle = %i", uavtalk_ManualControlSettingsData.ChannelGroups.Throttle);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsThrottleChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_Throttle_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.Roll = %i", uavtalk_ManualControlSettingsData.ChannelGroups.Roll);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.Pitch = %i", uavtalk_ManualControlSettingsData.ChannelGroups.Pitch);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.Yaw = %i", uavtalk_ManualControlSettingsData.ChannelGroups.Yaw);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.FlightMode = %i", uavtalk_ManualControlSettingsData.ChannelGroups.FlightMode);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsFlightModeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_FlightMode_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.Collective = %i", uavtalk_ManualControlSettingsData.ChannelGroups.Collective);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsCollectiveChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_Collective_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.Accessory0 = %i", uavtalk_ManualControlSettingsData.ChannelGroups.Accessory0);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsAccessory0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_Accessory0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.Accessory1 = %i", uavtalk_ManualControlSettingsData.ChannelGroups.Accessory1);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsAccessory1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_Accessory1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.Accessory2 = %i", uavtalk_ManualControlSettingsData.ChannelGroups.Accessory2);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsAccessory2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_Accessory2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelGroups.Arming = %i", uavtalk_ManualControlSettingsData.ChannelGroups.Arming);
		draw_text_button(esContext, "ManualControlSettingsChannelGroupsArmingChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelGroups_Arming_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RssiType = %i (%s)", uavtalk_ManualControlSettingsData.RssiType, UAVT_ManualControlSettingsRssiTypeOption[uavtalk_ManualControlSettingsData.RssiType]);
		draw_text_button(esContext, "ManualControlSettingsRssiTypeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsRssiType_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RssiChannelNumber = %i", uavtalk_ManualControlSettingsData.RssiChannelNumber);
		draw_text_button(esContext, "ManualControlSettingsRssiChannelNumberChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsRssiChannelNumber_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.Throttle = %i", uavtalk_ManualControlSettingsData.ChannelNumber.Throttle);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberThrottleChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_Throttle_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.Roll = %i", uavtalk_ManualControlSettingsData.ChannelNumber.Roll);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.Pitch = %i", uavtalk_ManualControlSettingsData.ChannelNumber.Pitch);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.Yaw = %i", uavtalk_ManualControlSettingsData.ChannelNumber.Yaw);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.FlightMode = %i", uavtalk_ManualControlSettingsData.ChannelNumber.FlightMode);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberFlightModeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_FlightMode_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.Collective = %i", uavtalk_ManualControlSettingsData.ChannelNumber.Collective);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberCollectiveChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_Collective_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.Accessory0 = %i", uavtalk_ManualControlSettingsData.ChannelNumber.Accessory0);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberAccessory0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_Accessory0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.Accessory1 = %i", uavtalk_ManualControlSettingsData.ChannelNumber.Accessory1);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberAccessory1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_Accessory1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.Accessory2 = %i", uavtalk_ManualControlSettingsData.ChannelNumber.Accessory2);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberAccessory2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_Accessory2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ChannelNumber.Arming = %i", uavtalk_ManualControlSettingsData.ChannelNumber.Arming);
		draw_text_button(esContext, "ManualControlSettingsChannelNumberArmingChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsChannelNumber_Arming_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Arming = %i (%s)", uavtalk_ManualControlSettingsData.Arming, UAVT_ManualControlSettingsArmingOption[uavtalk_ManualControlSettingsData.Arming]);
		draw_text_button(esContext, "ManualControlSettingsArmingChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsArming_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Stabilization1Settings.Roll = %i", uavtalk_ManualControlSettingsData.Stabilization1Settings.Roll);
		draw_text_button(esContext, "ManualControlSettingsStabilization1SettingsRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsStabilization1Settings_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Stabilization1Settings.Pitch = %i", uavtalk_ManualControlSettingsData.Stabilization1Settings.Pitch);
		draw_text_button(esContext, "ManualControlSettingsStabilization1SettingsPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsStabilization1Settings_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Stabilization1Settings.Yaw = %i", uavtalk_ManualControlSettingsData.Stabilization1Settings.Yaw);
		draw_text_button(esContext, "ManualControlSettingsStabilization1SettingsYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsStabilization1Settings_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Stabilization2Settings.Roll = %i", uavtalk_ManualControlSettingsData.Stabilization2Settings.Roll);
		draw_text_button(esContext, "ManualControlSettingsStabilization2SettingsRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsStabilization2Settings_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Stabilization2Settings.Pitch = %i", uavtalk_ManualControlSettingsData.Stabilization2Settings.Pitch);
		draw_text_button(esContext, "ManualControlSettingsStabilization2SettingsPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsStabilization2Settings_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Stabilization2Settings.Yaw = %i", uavtalk_ManualControlSettingsData.Stabilization2Settings.Yaw);
		draw_text_button(esContext, "ManualControlSettingsStabilization2SettingsYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsStabilization2Settings_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Stabilization3Settings.Roll = %i", uavtalk_ManualControlSettingsData.Stabilization3Settings.Roll);
		draw_text_button(esContext, "ManualControlSettingsStabilization3SettingsRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsStabilization3Settings_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Stabilization3Settings.Pitch = %i", uavtalk_ManualControlSettingsData.Stabilization3Settings.Pitch);
		draw_text_button(esContext, "ManualControlSettingsStabilization3SettingsPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsStabilization3Settings_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Stabilization3Settings.Yaw = %i", uavtalk_ManualControlSettingsData.Stabilization3Settings.Yaw);
		draw_text_button(esContext, "ManualControlSettingsStabilization3SettingsYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsStabilization3Settings_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlightModeNumber = %i", uavtalk_ManualControlSettingsData.FlightModeNumber);
		draw_text_button(esContext, "ManualControlSettingsFlightModeNumberChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsFlightModeNumber_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlightModePosition0 = %i", uavtalk_ManualControlSettingsData.FlightModePosition[0]);
		draw_text_button(esContext, "ManualControlSettingsFlightModePosition0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsFlightModePosition_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlightModePosition1 = %i", uavtalk_ManualControlSettingsData.FlightModePosition[1]);
		draw_text_button(esContext, "ManualControlSettingsFlightModePosition1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsFlightModePosition_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlightModePosition2 = %i", uavtalk_ManualControlSettingsData.FlightModePosition[2]);
		draw_text_button(esContext, "ManualControlSettingsFlightModePosition2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsFlightModePosition_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlightModePosition3 = %i", uavtalk_ManualControlSettingsData.FlightModePosition[3]);
		draw_text_button(esContext, "ManualControlSettingsFlightModePosition3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsFlightModePosition_3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlightModePosition4 = %i", uavtalk_ManualControlSettingsData.FlightModePosition[4]);
		draw_text_button(esContext, "ManualControlSettingsFlightModePosition4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsFlightModePosition_4_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlightModePosition5 = %i", uavtalk_ManualControlSettingsData.FlightModePosition[5]);
		draw_text_button(esContext, "ManualControlSettingsFlightModePosition5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ManualControlSettingsFlightModePosition_5_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: MixerSettings
***********************************************/

void UAVT_gui_MixerSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "MixerSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxAccel = %f", uavtalk_MixerSettingsData.MaxAccel);
		draw_text_button(esContext, "MixerSettingsMaxAccelChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_MixerSettingsMaxAccel_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FeedForward = %f", uavtalk_MixerSettingsData.FeedForward);
		draw_text_button(esContext, "MixerSettingsFeedForwardChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsFeedForward_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelTime = %f", uavtalk_MixerSettingsData.AccelTime);
		draw_text_button(esContext, "MixerSettingsAccelTimeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_MixerSettingsAccelTime_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DecelTime = %f", uavtalk_MixerSettingsData.DecelTime);
		draw_text_button(esContext, "MixerSettingsDecelTimeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_MixerSettingsDecelTime_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve1.n = %f", uavtalk_MixerSettingsData.ThrottleCurve1.n);
		draw_text_button(esContext, "MixerSettingsThrottleCurve1nChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve1_n_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve1.n2 = %f", uavtalk_MixerSettingsData.ThrottleCurve1.n2);
		draw_text_button(esContext, "MixerSettingsThrottleCurve1n2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve1_n2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve1.n5 = %f", uavtalk_MixerSettingsData.ThrottleCurve1.n5);
		draw_text_button(esContext, "MixerSettingsThrottleCurve1n5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve1_n5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve1.n7 = %f", uavtalk_MixerSettingsData.ThrottleCurve1.n7);
		draw_text_button(esContext, "MixerSettingsThrottleCurve1n7Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve1_n7_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve1.n1 = %f", uavtalk_MixerSettingsData.ThrottleCurve1.n1);
		draw_text_button(esContext, "MixerSettingsThrottleCurve1n1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve1_n1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve2.n = %f", uavtalk_MixerSettingsData.ThrottleCurve2.n);
		draw_text_button(esContext, "MixerSettingsThrottleCurve2nChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve2_n_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve2.n2 = %f", uavtalk_MixerSettingsData.ThrottleCurve2.n2);
		draw_text_button(esContext, "MixerSettingsThrottleCurve2n2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve2_n2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve2.n5 = %f", uavtalk_MixerSettingsData.ThrottleCurve2.n5);
		draw_text_button(esContext, "MixerSettingsThrottleCurve2n5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve2_n5_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve2.n7 = %f", uavtalk_MixerSettingsData.ThrottleCurve2.n7);
		draw_text_button(esContext, "MixerSettingsThrottleCurve2n7Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve2_n7_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleCurve2.n1 = %f", uavtalk_MixerSettingsData.ThrottleCurve2.n1);
		draw_text_button(esContext, "MixerSettingsThrottleCurve2n1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsThrottleCurve2_n1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Curve2Source = %i (%s)", uavtalk_MixerSettingsData.Curve2Source, UAVT_MixerSettingsCurve2SourceOption[uavtalk_MixerSettingsData.Curve2Source]);
		draw_text_button(esContext, "MixerSettingsCurve2SourceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsCurve2Source_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Mixer1Type = %i (%s)", uavtalk_MixerSettingsData.Mixer1Type, UAVT_MixerSettingsMixer1TypeOption[uavtalk_MixerSettingsData.Mixer1Type]);
		draw_text_button(esContext, "MixerSettingsMixer1TypeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsMixer1Type_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Mixer1Vector.ThrottleCurve1 = %i", uavtalk_MixerSettingsData.Mixer1Vector.ThrottleCurve1);
		draw_text_button(esContext, "MixerSettingsMixer1VectorThrottleCurve1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsMixer1Vector_ThrottleCurve1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Mixer1Vector.ThrottleCurve2 = %i", uavtalk_MixerSettingsData.Mixer1Vector.ThrottleCurve2);
		draw_text_button(esContext, "MixerSettingsMixer1VectorThrottleCurve2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsMixer1Vector_ThrottleCurve2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Mixer1Vector.Roll = %i", uavtalk_MixerSettingsData.Mixer1Vector.Roll);
		draw_text_button(esContext, "MixerSettingsMixer1VectorRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsMixer1Vector_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Mixer1Vector.Pitch = %i", uavtalk_MixerSettingsData.Mixer1Vector.Pitch);
		draw_text_button(esContext, "MixerSettingsMixer1VectorPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsMixer1Vector_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Mixer1Vector.Yaw = %i", uavtalk_MixerSettingsData.Mixer1Vector.Yaw);
		draw_text_button(esContext, "MixerSettingsMixer1VectorYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MixerSettingsMixer1Vector_Yaw_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: ModuleSettings
***********************************************/

void UAVT_gui_ModuleSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "ModuleSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.Airspeed = %i", uavtalk_ModuleSettingsData.AdminState.Airspeed);
		draw_text_button(esContext, "ModuleSettingsAdminStateAirspeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_Airspeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.AltitudeHold = %i", uavtalk_ModuleSettingsData.AdminState.AltitudeHold);
		draw_text_button(esContext, "ModuleSettingsAdminStateAltitudeHoldChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_AltitudeHold_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.Autotune = %i", uavtalk_ModuleSettingsData.AdminState.Autotune);
		draw_text_button(esContext, "ModuleSettingsAdminStateAutotuneChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_Autotune_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.Battery = %i", uavtalk_ModuleSettingsData.AdminState.Battery);
		draw_text_button(esContext, "ModuleSettingsAdminStateBatteryChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_Battery_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.CameraStab = %i", uavtalk_ModuleSettingsData.AdminState.CameraStab);
		draw_text_button(esContext, "ModuleSettingsAdminStateCameraStabChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_CameraStab_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.ComUsbBridge = %i", uavtalk_ModuleSettingsData.AdminState.ComUsbBridge);
		draw_text_button(esContext, "ModuleSettingsAdminStateComUsbBridgeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_ComUsbBridge_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.FixedWingPathFollower = %i", uavtalk_ModuleSettingsData.AdminState.FixedWingPathFollower);
		draw_text_button(esContext, "ModuleSettingsAdminStateFixedWingPathFollowerChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_FixedWingPathFollower_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.Fault = %i", uavtalk_ModuleSettingsData.AdminState.Fault);
		draw_text_button(esContext, "ModuleSettingsAdminStateFaultChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_Fault_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.GPS = %i", uavtalk_ModuleSettingsData.AdminState.GPS);
		draw_text_button(esContext, "ModuleSettingsAdminStateGPSChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_GPS_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.OveroSync = %i", uavtalk_ModuleSettingsData.AdminState.OveroSync);
		draw_text_button(esContext, "ModuleSettingsAdminStateOveroSyncChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_OveroSync_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.PathPlanner = %i", uavtalk_ModuleSettingsData.AdminState.PathPlanner);
		draw_text_button(esContext, "ModuleSettingsAdminStatePathPlannerChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_PathPlanner_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.TxPID = %i", uavtalk_ModuleSettingsData.AdminState.TxPID);
		draw_text_button(esContext, "ModuleSettingsAdminStateTxPIDChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_TxPID_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.VtolPathFollower = %i", uavtalk_ModuleSettingsData.AdminState.VtolPathFollower);
		draw_text_button(esContext, "ModuleSettingsAdminStateVtolPathFollowerChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_VtolPathFollower_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.GroundPathFollower = %i", uavtalk_ModuleSettingsData.AdminState.GroundPathFollower);
		draw_text_button(esContext, "ModuleSettingsAdminStateGroundPathFollowerChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_GroundPathFollower_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.GenericI2CSensor = %i", uavtalk_ModuleSettingsData.AdminState.GenericI2CSensor);
		draw_text_button(esContext, "ModuleSettingsAdminStateGenericI2CSensorChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_GenericI2CSensor_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.UAVOMavlinkBridge = %i", uavtalk_ModuleSettingsData.AdminState.UAVOMavlinkBridge);
		draw_text_button(esContext, "ModuleSettingsAdminStateUAVOMavlinkBridgeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_UAVOMavlinkBridge_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.UAVOLighttelemetryBridge = %i", uavtalk_ModuleSettingsData.AdminState.UAVOLighttelemetryBridge);
		draw_text_button(esContext, "ModuleSettingsAdminStateUAVOLighttelemetryBridgeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_UAVOLighttelemetryBridge_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.VibrationAnalysis = %i", uavtalk_ModuleSettingsData.AdminState.VibrationAnalysis);
		draw_text_button(esContext, "ModuleSettingsAdminStateVibrationAnalysisChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_VibrationAnalysis_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.UAVOHoTTBridge = %i", uavtalk_ModuleSettingsData.AdminState.UAVOHoTTBridge);
		draw_text_button(esContext, "ModuleSettingsAdminStateUAVOHoTTBridgeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_UAVOHoTTBridge_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.UAVOFrSKYSensorHubBridge = %i", uavtalk_ModuleSettingsData.AdminState.UAVOFrSKYSensorHubBridge);
		draw_text_button(esContext, "ModuleSettingsAdminStateUAVOFrSKYSensorHubBridgeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_UAVOFrSKYSensorHubBridge_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.PicoC = %i", uavtalk_ModuleSettingsData.AdminState.PicoC);
		draw_text_button(esContext, "ModuleSettingsAdminStatePicoCChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_PicoC_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.UAVOFrSkySPortBridge = %i", uavtalk_ModuleSettingsData.AdminState.UAVOFrSkySPortBridge);
		draw_text_button(esContext, "ModuleSettingsAdminStateUAVOFrSkySPortBridgeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_UAVOFrSkySPortBridge_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.Geofence = %i", uavtalk_ModuleSettingsData.AdminState.Geofence);
		draw_text_button(esContext, "ModuleSettingsAdminStateGeofenceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_Geofence_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AdminState.Logging = %i", uavtalk_ModuleSettingsData.AdminState.Logging);
		draw_text_button(esContext, "ModuleSettingsAdminStateLoggingChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsAdminState_Logging_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "TelemetrySpeed = %i (%s)", uavtalk_ModuleSettingsData.TelemetrySpeed, UAVT_ModuleSettingsTelemetrySpeedOption[uavtalk_ModuleSettingsData.TelemetrySpeed]);
		draw_text_button(esContext, "ModuleSettingsTelemetrySpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsTelemetrySpeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GPSSpeed = %i (%s)", uavtalk_ModuleSettingsData.GPSSpeed, UAVT_ModuleSettingsGPSSpeedOption[uavtalk_ModuleSettingsData.GPSSpeed]);
		draw_text_button(esContext, "ModuleSettingsGPSSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_ModuleSettingsGPSSpeed_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GPSDataProtocol = %i (%s)", uavtalk_ModuleSettingsData.GPSDataProtocol, UAVT_ModuleSettingsGPSDataProtocolOption[uavtalk_ModuleSettingsData.GPSDataProtocol]);
		draw_text_button(esContext, "ModuleSettingsGPSDataProtocolChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsGPSDataProtocol_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GPSAutoConfigure = %i (%s)", uavtalk_ModuleSettingsData.GPSAutoConfigure, UAVT_ModuleSettingsGPSAutoConfigureOption[uavtalk_ModuleSettingsData.GPSAutoConfigure]);
		draw_text_button(esContext, "ModuleSettingsGPSAutoConfigureChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsGPSAutoConfigure_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ComUsbBridgeSpeed = %i (%s)", uavtalk_ModuleSettingsData.ComUsbBridgeSpeed, UAVT_ModuleSettingsComUsbBridgeSpeedOption[uavtalk_ModuleSettingsData.ComUsbBridgeSpeed]);
		draw_text_button(esContext, "ModuleSettingsComUsbBridgeSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsComUsbBridgeSpeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "I2CVMProgramSelect = %i (%s)", uavtalk_ModuleSettingsData.I2CVMProgramSelect, UAVT_ModuleSettingsI2CVMProgramSelectOption[uavtalk_ModuleSettingsData.I2CVMProgramSelect]);
		draw_text_button(esContext, "ModuleSettingsI2CVMProgramSelectChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsI2CVMProgramSelect_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MavlinkSpeed = %i (%s)", uavtalk_ModuleSettingsData.MavlinkSpeed, UAVT_ModuleSettingsMavlinkSpeedOption[uavtalk_ModuleSettingsData.MavlinkSpeed]);
		draw_text_button(esContext, "ModuleSettingsMavlinkSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsMavlinkSpeed_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "LightTelemetrySpeed = %i (%s)", uavtalk_ModuleSettingsData.LightTelemetrySpeed, UAVT_ModuleSettingsLightTelemetrySpeedOption[uavtalk_ModuleSettingsData.LightTelemetrySpeed]);
		draw_text_button(esContext, "ModuleSettingsLightTelemetrySpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_ModuleSettingsLightTelemetrySpeed_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: MWRateSettings
***********************************************/

void UAVT_gui_MWRateSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "MWRateSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRatePID.Kp = %f", uavtalk_MWRateSettingsData.RollRatePID.Kp);
		draw_text_button(esContext, "MWRateSettingsRollRatePIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsRollRatePID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRatePID.Ki = %f", uavtalk_MWRateSettingsData.RollRatePID.Ki);
		draw_text_button(esContext, "MWRateSettingsRollRatePIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsRollRatePID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRatePID.Kd = %f", uavtalk_MWRateSettingsData.RollRatePID.Kd);
		draw_text_button(esContext, "MWRateSettingsRollRatePIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsRollRatePID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRatePID.ILimit = %f", uavtalk_MWRateSettingsData.RollRatePID.ILimit);
		draw_text_button(esContext, "MWRateSettingsRollRatePIDILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsRollRatePID_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRatePID.Kp = %f", uavtalk_MWRateSettingsData.PitchRatePID.Kp);
		draw_text_button(esContext, "MWRateSettingsPitchRatePIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsPitchRatePID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRatePID.Ki = %f", uavtalk_MWRateSettingsData.PitchRatePID.Ki);
		draw_text_button(esContext, "MWRateSettingsPitchRatePIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsPitchRatePID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRatePID.Kd = %f", uavtalk_MWRateSettingsData.PitchRatePID.Kd);
		draw_text_button(esContext, "MWRateSettingsPitchRatePIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsPitchRatePID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRatePID.ILimit = %f", uavtalk_MWRateSettingsData.PitchRatePID.ILimit);
		draw_text_button(esContext, "MWRateSettingsPitchRatePIDILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsPitchRatePID_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRatePID.Kp = %f", uavtalk_MWRateSettingsData.YawRatePID.Kp);
		draw_text_button(esContext, "MWRateSettingsYawRatePIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsYawRatePID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRatePID.Ki = %f", uavtalk_MWRateSettingsData.YawRatePID.Ki);
		draw_text_button(esContext, "MWRateSettingsYawRatePIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsYawRatePID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRatePID.Kd = %f", uavtalk_MWRateSettingsData.YawRatePID.Kd);
		draw_text_button(esContext, "MWRateSettingsYawRatePIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsYawRatePID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRatePID.ILimit = %f", uavtalk_MWRateSettingsData.YawRatePID.ILimit);
		draw_text_button(esContext, "MWRateSettingsYawRatePIDILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsYawRatePID_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DerivativeGamma = %f", uavtalk_MWRateSettingsData.DerivativeGamma);
		draw_text_button(esContext, "MWRateSettingsDerivativeGammaChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsDerivativeGamma_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollPitchRate = %i", uavtalk_MWRateSettingsData.RollPitchRate);
		draw_text_button(esContext, "MWRateSettingsRollPitchRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_MWRateSettingsRollPitchRate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRate = %i", uavtalk_MWRateSettingsData.YawRate);
		draw_text_button(esContext, "MWRateSettingsYawRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_MWRateSettingsYawRate_change,
						 0.0);
	}
	nn++;
}

/***********************************************
    Object: OPLinkSettings
***********************************************/

void UAVT_gui_OPLinkSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "OPLinkSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PairID = %i", uavtalk_OPLinkSettingsData.PairID);
		draw_text_button(esContext, "OPLinkSettingsPairIDChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsPairID_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MinFrequency = %i", uavtalk_OPLinkSettingsData.MinFrequency);
		draw_text_button(esContext, "OPLinkSettingsMinFrequencyChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsMinFrequency_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxFrequency = %i", uavtalk_OPLinkSettingsData.MaxFrequency);
		draw_text_button(esContext, "OPLinkSettingsMaxFrequencyChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsMaxFrequency_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SendTimeout = %i", uavtalk_OPLinkSettingsData.SendTimeout);
		draw_text_button(esContext, "OPLinkSettingsSendTimeoutChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsSendTimeout_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Coordinator = %i (%s)", uavtalk_OPLinkSettingsData.Coordinator, UAVT_OPLinkSettingsCoordinatorOption[uavtalk_OPLinkSettingsData.Coordinator]);
		draw_text_button(esContext, "OPLinkSettingsCoordinatorChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsCoordinator_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PPM = %i (%s)", uavtalk_OPLinkSettingsData.PPM, UAVT_OPLinkSettingsPPMOption[uavtalk_OPLinkSettingsData.PPM]);
		draw_text_button(esContext, "OPLinkSettingsPPMChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsPPM_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "UAVTalk = %i (%s)", uavtalk_OPLinkSettingsData.UAVTalk, UAVT_OPLinkSettingsUAVTalkOption[uavtalk_OPLinkSettingsData.UAVTalk]);
		draw_text_button(esContext, "OPLinkSettingsUAVTalkChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsUAVTalk_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "InputConnection = %i (%s)", uavtalk_OPLinkSettingsData.InputConnection, UAVT_OPLinkSettingsInputConnectionOption[uavtalk_OPLinkSettingsData.InputConnection]);
		draw_text_button(esContext, "OPLinkSettingsInputConnectionChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsInputConnection_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "OutputConnection = %i (%s)", uavtalk_OPLinkSettingsData.OutputConnection, UAVT_OPLinkSettingsOutputConnectionOption[uavtalk_OPLinkSettingsData.OutputConnection]);
		draw_text_button(esContext, "OPLinkSettingsOutputConnectionChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsOutputConnection_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ComSpeed = %i (%s)", uavtalk_OPLinkSettingsData.ComSpeed, UAVT_OPLinkSettingsComSpeedOption[uavtalk_OPLinkSettingsData.ComSpeed]);
		draw_text_button(esContext, "OPLinkSettingsComSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsComSpeed_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxRFPower = %i (%s)", uavtalk_OPLinkSettingsData.MaxRFPower, UAVT_OPLinkSettingsMaxRFPowerOption[uavtalk_OPLinkSettingsData.MaxRFPower]);
		draw_text_button(esContext, "OPLinkSettingsMaxRFPowerChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsMaxRFPower_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MinPacketSize = %i", uavtalk_OPLinkSettingsData.MinPacketSize);
		draw_text_button(esContext, "OPLinkSettingsMinPacketSizeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsMinPacketSize_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FrequencyCalibration = %i", uavtalk_OPLinkSettingsData.FrequencyCalibration);
		draw_text_button(esContext, "OPLinkSettingsFrequencyCalibrationChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsFrequencyCalibration_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey0 = %i", uavtalk_OPLinkSettingsData.AESKey[0]);
		draw_text_button(esContext, "OPLinkSettingsAESKey0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_0_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey1 = %i", uavtalk_OPLinkSettingsData.AESKey[1]);
		draw_text_button(esContext, "OPLinkSettingsAESKey1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_1_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey2 = %i", uavtalk_OPLinkSettingsData.AESKey[2]);
		draw_text_button(esContext, "OPLinkSettingsAESKey2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_2_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey3 = %i", uavtalk_OPLinkSettingsData.AESKey[3]);
		draw_text_button(esContext, "OPLinkSettingsAESKey3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_3_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey4 = %i", uavtalk_OPLinkSettingsData.AESKey[4]);
		draw_text_button(esContext, "OPLinkSettingsAESKey4Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_4_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey5 = %i", uavtalk_OPLinkSettingsData.AESKey[5]);
		draw_text_button(esContext, "OPLinkSettingsAESKey5Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_5_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey6 = %i", uavtalk_OPLinkSettingsData.AESKey[6]);
		draw_text_button(esContext, "OPLinkSettingsAESKey6Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_6_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey7 = %i", uavtalk_OPLinkSettingsData.AESKey[7]);
		draw_text_button(esContext, "OPLinkSettingsAESKey7Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_7_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey8 = %i", uavtalk_OPLinkSettingsData.AESKey[8]);
		draw_text_button(esContext, "OPLinkSettingsAESKey8Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_8_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey9 = %i", uavtalk_OPLinkSettingsData.AESKey[9]);
		draw_text_button(esContext, "OPLinkSettingsAESKey9Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OPLinkSettingsAESKey_9_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey10 = %i", uavtalk_OPLinkSettingsData.AESKey[10]);
		draw_text_button(esContext, "OPLinkSettingsAESKey10Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_10_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey11 = %i", uavtalk_OPLinkSettingsData.AESKey[11]);
		draw_text_button(esContext, "OPLinkSettingsAESKey11Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_11_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey12 = %i", uavtalk_OPLinkSettingsData.AESKey[12]);
		draw_text_button(esContext, "OPLinkSettingsAESKey12Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_12_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey13 = %i", uavtalk_OPLinkSettingsData.AESKey[13]);
		draw_text_button(esContext, "OPLinkSettingsAESKey13Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_13_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey14 = %i", uavtalk_OPLinkSettingsData.AESKey[14]);
		draw_text_button(esContext, "OPLinkSettingsAESKey14Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_14_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey15 = %i", uavtalk_OPLinkSettingsData.AESKey[15]);
		draw_text_button(esContext, "OPLinkSettingsAESKey15Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_15_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey16 = %i", uavtalk_OPLinkSettingsData.AESKey[16]);
		draw_text_button(esContext, "OPLinkSettingsAESKey16Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_16_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey17 = %i", uavtalk_OPLinkSettingsData.AESKey[17]);
		draw_text_button(esContext, "OPLinkSettingsAESKey17Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_17_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey18 = %i", uavtalk_OPLinkSettingsData.AESKey[18]);
		draw_text_button(esContext, "OPLinkSettingsAESKey18Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_18_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey19 = %i", uavtalk_OPLinkSettingsData.AESKey[19]);
		draw_text_button(esContext, "OPLinkSettingsAESKey19Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_19_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey20 = %i", uavtalk_OPLinkSettingsData.AESKey[20]);
		draw_text_button(esContext, "OPLinkSettingsAESKey20Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_20_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey21 = %i", uavtalk_OPLinkSettingsData.AESKey[21]);
		draw_text_button(esContext, "OPLinkSettingsAESKey21Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_21_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey22 = %i", uavtalk_OPLinkSettingsData.AESKey[22]);
		draw_text_button(esContext, "OPLinkSettingsAESKey22Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_22_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey23 = %i", uavtalk_OPLinkSettingsData.AESKey[23]);
		draw_text_button(esContext, "OPLinkSettingsAESKey23Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_23_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey24 = %i", uavtalk_OPLinkSettingsData.AESKey[24]);
		draw_text_button(esContext, "OPLinkSettingsAESKey24Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_24_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey25 = %i", uavtalk_OPLinkSettingsData.AESKey[25]);
		draw_text_button(esContext, "OPLinkSettingsAESKey25Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_25_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey26 = %i", uavtalk_OPLinkSettingsData.AESKey[26]);
		draw_text_button(esContext, "OPLinkSettingsAESKey26Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_26_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey27 = %i", uavtalk_OPLinkSettingsData.AESKey[27]);
		draw_text_button(esContext, "OPLinkSettingsAESKey27Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_27_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey28 = %i", uavtalk_OPLinkSettingsData.AESKey[28]);
		draw_text_button(esContext, "OPLinkSettingsAESKey28Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_28_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey29 = %i", uavtalk_OPLinkSettingsData.AESKey[29]);
		draw_text_button(esContext, "OPLinkSettingsAESKey29Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_29_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey30 = %i", uavtalk_OPLinkSettingsData.AESKey[30]);
		draw_text_button(esContext, "OPLinkSettingsAESKey30Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_30_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AESKey31 = %i", uavtalk_OPLinkSettingsData.AESKey[31]);
		draw_text_button(esContext, "OPLinkSettingsAESKey31Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_OPLinkSettingsAESKey_31_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: OveroSyncSettings
***********************************************/

void UAVT_gui_OveroSyncSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "OveroSyncSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "LogOn = %i (%s)", uavtalk_OveroSyncSettingsData.LogOn, UAVT_OveroSyncSettingsLogOnOption[uavtalk_OveroSyncSettingsData.LogOn]);
		draw_text_button(esContext, "OveroSyncSettingsLogOnChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_OveroSyncSettingsLogOn_change,
						 0.0);
	}
	nn++;
}

/***********************************************
    Object: PathPlannerSettings
***********************************************/

void UAVT_gui_PathPlannerSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "PathPlannerSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PreprogrammedPath = %i (%s)", uavtalk_PathPlannerSettingsData.PreprogrammedPath, UAVT_PathPlannerSettingsPreprogrammedPathOption[uavtalk_PathPlannerSettingsData.PreprogrammedPath]);
		draw_text_button(esContext, "PathPlannerSettingsPreprogrammedPathChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_PathPlannerSettingsPreprogrammedPath_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FlashOperation = %i (%s)", uavtalk_PathPlannerSettingsData.FlashOperation, UAVT_PathPlannerSettingsFlashOperationOption[uavtalk_PathPlannerSettingsData.FlashOperation]);
		draw_text_button(esContext, "PathPlannerSettingsFlashOperationChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_PathPlannerSettingsFlashOperation_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: PicoCSettings
***********************************************/

void UAVT_gui_PicoCSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "PicoCSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxFileSize = %i", uavtalk_PicoCSettingsData.MaxFileSize);
		draw_text_button(esContext, "PicoCSettingsMaxFileSizeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_PicoCSettingsMaxFileSize_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "TaskStackSize = %i", uavtalk_PicoCSettingsData.TaskStackSize);
		draw_text_button(esContext, "PicoCSettingsTaskStackSizeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_PicoCSettingsTaskStackSize_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PicoCStackSize = %i", uavtalk_PicoCSettingsData.PicoCStackSize);
		draw_text_button(esContext, "PicoCSettingsPicoCStackSizeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_PicoCSettingsPicoCStackSize_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "BootFileID = %i", uavtalk_PicoCSettingsData.BootFileID);
		draw_text_button(esContext, "PicoCSettingsBootFileIDChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_PicoCSettingsBootFileID_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Startup = %i (%s)", uavtalk_PicoCSettingsData.Startup, UAVT_PicoCSettingsStartupOption[uavtalk_PicoCSettingsData.Startup]);
		draw_text_button(esContext, "PicoCSettingsStartupChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_PicoCSettingsStartup_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Source = %i (%s)", uavtalk_PicoCSettingsData.Source, UAVT_PicoCSettingsSourceOption[uavtalk_PicoCSettingsData.Source]);
		draw_text_button(esContext, "PicoCSettingsSourceChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_PicoCSettingsSource_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ComSpeed = %i (%s)", uavtalk_PicoCSettingsData.ComSpeed, UAVT_PicoCSettingsComSpeedOption[uavtalk_PicoCSettingsData.ComSpeed]);
		draw_text_button(esContext, "PicoCSettingsComSpeedChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_PicoCSettingsComSpeed_change,
						 0.0);
	}
	nn++;
}

/***********************************************
    Object: SensorSettings
***********************************************/

void UAVT_gui_SensorSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "SensorSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelBias.X = %f", uavtalk_SensorSettingsData.AccelBias.X);
		draw_text_button(esContext, "SensorSettingsAccelBiasXChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsAccelBias_X_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelBias.Y = %f", uavtalk_SensorSettingsData.AccelBias.Y);
		draw_text_button(esContext, "SensorSettingsAccelBiasYChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsAccelBias_Y_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelBias.Z = %f", uavtalk_SensorSettingsData.AccelBias.Z);
		draw_text_button(esContext, "SensorSettingsAccelBiasZChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsAccelBias_Z_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelScale.X = %f", uavtalk_SensorSettingsData.AccelScale.X);
		draw_text_button(esContext, "SensorSettingsAccelScaleXChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsAccelScale_X_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelScale.Y = %f", uavtalk_SensorSettingsData.AccelScale.Y);
		draw_text_button(esContext, "SensorSettingsAccelScaleYChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsAccelScale_Y_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AccelScale.Z = %f", uavtalk_SensorSettingsData.AccelScale.Z);
		draw_text_button(esContext, "SensorSettingsAccelScaleZChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsAccelScale_Z_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroScale.X = %f", uavtalk_SensorSettingsData.GyroScale.X);
		draw_text_button(esContext, "SensorSettingsGyroScaleXChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsGyroScale_X_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroScale.Y = %f", uavtalk_SensorSettingsData.GyroScale.Y);
		draw_text_button(esContext, "SensorSettingsGyroScaleYChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsGyroScale_Y_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroScale.Z = %f", uavtalk_SensorSettingsData.GyroScale.Z);
		draw_text_button(esContext, "SensorSettingsGyroScaleZChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsGyroScale_Z_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "XGyroTempCoeff.n = %f", uavtalk_SensorSettingsData.XGyroTempCoeff.n);
		draw_text_button(esContext, "SensorSettingsXGyroTempCoeffnChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsXGyroTempCoeff_n_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "XGyroTempCoeff.T = %f", uavtalk_SensorSettingsData.XGyroTempCoeff.T);
		draw_text_button(esContext, "SensorSettingsXGyroTempCoeffTChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsXGyroTempCoeff_T_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "XGyroTempCoeff.T2 = %f", uavtalk_SensorSettingsData.XGyroTempCoeff.T2);
		draw_text_button(esContext, "SensorSettingsXGyroTempCoeffT2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsXGyroTempCoeff_T2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "XGyroTempCoeff.T3 = %f", uavtalk_SensorSettingsData.XGyroTempCoeff.T3);
		draw_text_button(esContext, "SensorSettingsXGyroTempCoeffT3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsXGyroTempCoeff_T3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YGyroTempCoeff.n = %f", uavtalk_SensorSettingsData.YGyroTempCoeff.n);
		draw_text_button(esContext, "SensorSettingsYGyroTempCoeffnChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsYGyroTempCoeff_n_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YGyroTempCoeff.T = %f", uavtalk_SensorSettingsData.YGyroTempCoeff.T);
		draw_text_button(esContext, "SensorSettingsYGyroTempCoeffTChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsYGyroTempCoeff_T_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YGyroTempCoeff.T2 = %f", uavtalk_SensorSettingsData.YGyroTempCoeff.T2);
		draw_text_button(esContext, "SensorSettingsYGyroTempCoeffT2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsYGyroTempCoeff_T2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YGyroTempCoeff.T3 = %f", uavtalk_SensorSettingsData.YGyroTempCoeff.T3);
		draw_text_button(esContext, "SensorSettingsYGyroTempCoeffT3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsYGyroTempCoeff_T3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ZGyroTempCoeff.n = %f", uavtalk_SensorSettingsData.ZGyroTempCoeff.n);
		draw_text_button(esContext, "SensorSettingsZGyroTempCoeffnChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsZGyroTempCoeff_n_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ZGyroTempCoeff.T = %f", uavtalk_SensorSettingsData.ZGyroTempCoeff.T);
		draw_text_button(esContext, "SensorSettingsZGyroTempCoeffTChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsZGyroTempCoeff_T_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ZGyroTempCoeff.T2 = %f", uavtalk_SensorSettingsData.ZGyroTempCoeff.T2);
		draw_text_button(esContext, "SensorSettingsZGyroTempCoeffT2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsZGyroTempCoeff_T2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ZGyroTempCoeff.T3 = %f", uavtalk_SensorSettingsData.ZGyroTempCoeff.T3);
		draw_text_button(esContext, "SensorSettingsZGyroTempCoeffT3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsZGyroTempCoeff_T3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MagBias.X = %f", uavtalk_SensorSettingsData.MagBias.X);
		draw_text_button(esContext, "SensorSettingsMagBiasXChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsMagBias_X_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MagBias.Y = %f", uavtalk_SensorSettingsData.MagBias.Y);
		draw_text_button(esContext, "SensorSettingsMagBiasYChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsMagBias_Y_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MagBias.Z = %f", uavtalk_SensorSettingsData.MagBias.Z);
		draw_text_button(esContext, "SensorSettingsMagBiasZChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsMagBias_Z_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MagScale.X = %f", uavtalk_SensorSettingsData.MagScale.X);
		draw_text_button(esContext, "SensorSettingsMagScaleXChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsMagScale_X_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MagScale.Y = %f", uavtalk_SensorSettingsData.MagScale.Y);
		draw_text_button(esContext, "SensorSettingsMagScaleYChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsMagScale_Y_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MagScale.Z = %f", uavtalk_SensorSettingsData.MagScale.Z);
		draw_text_button(esContext, "SensorSettingsMagScaleZChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsMagScale_Z_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ZAccelOffset = %f", uavtalk_SensorSettingsData.ZAccelOffset);
		draw_text_button(esContext, "SensorSettingsZAccelOffsetChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SensorSettingsZAccelOffset_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: StabilizationSettings
***********************************************/

void UAVT_gui_StabilizationSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "StabilizationSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ManualRate.Roll = %f", uavtalk_StabilizationSettingsData.ManualRate.Roll);
		draw_text_button(esContext, "StabilizationSettingsManualRateRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsManualRate_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ManualRate.Pitch = %f", uavtalk_StabilizationSettingsData.ManualRate.Pitch);
		draw_text_button(esContext, "StabilizationSettingsManualRatePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsManualRate_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ManualRate.Yaw = %f", uavtalk_StabilizationSettingsData.ManualRate.Yaw);
		draw_text_button(esContext, "StabilizationSettingsManualRateYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsManualRate_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaximumRate.Roll = %f", uavtalk_StabilizationSettingsData.MaximumRate.Roll);
		draw_text_button(esContext, "StabilizationSettingsMaximumRateRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsMaximumRate_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaximumRate.Pitch = %f", uavtalk_StabilizationSettingsData.MaximumRate.Pitch);
		draw_text_button(esContext, "StabilizationSettingsMaximumRatePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsMaximumRate_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaximumRate.Yaw = %f", uavtalk_StabilizationSettingsData.MaximumRate.Yaw);
		draw_text_button(esContext, "StabilizationSettingsMaximumRateYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsMaximumRate_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PoiMaximumRate.Roll = %f", uavtalk_StabilizationSettingsData.PoiMaximumRate.Roll);
		draw_text_button(esContext, "StabilizationSettingsPoiMaximumRateRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPoiMaximumRate_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PoiMaximumRate.Pitch = %f", uavtalk_StabilizationSettingsData.PoiMaximumRate.Pitch);
		draw_text_button(esContext, "StabilizationSettingsPoiMaximumRatePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPoiMaximumRate_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PoiMaximumRate.Yaw = %f", uavtalk_StabilizationSettingsData.PoiMaximumRate.Yaw);
		draw_text_button(esContext, "StabilizationSettingsPoiMaximumRateYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPoiMaximumRate_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRatePID.Kp = %f", uavtalk_StabilizationSettingsData.RollRatePID.Kp);
		draw_text_button(esContext, "StabilizationSettingsRollRatePIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollRatePID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRatePID.Ki = %f", uavtalk_StabilizationSettingsData.RollRatePID.Ki);
		draw_text_button(esContext, "StabilizationSettingsRollRatePIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollRatePID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRatePID.Kd = %f", uavtalk_StabilizationSettingsData.RollRatePID.Kd);
		draw_text_button(esContext, "StabilizationSettingsRollRatePIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollRatePID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRatePID.ILimit = %f", uavtalk_StabilizationSettingsData.RollRatePID.ILimit);
		draw_text_button(esContext, "StabilizationSettingsRollRatePIDILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollRatePID_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRatePID.Kp = %f", uavtalk_StabilizationSettingsData.PitchRatePID.Kp);
		draw_text_button(esContext, "StabilizationSettingsPitchRatePIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchRatePID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRatePID.Ki = %f", uavtalk_StabilizationSettingsData.PitchRatePID.Ki);
		draw_text_button(esContext, "StabilizationSettingsPitchRatePIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchRatePID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRatePID.Kd = %f", uavtalk_StabilizationSettingsData.PitchRatePID.Kd);
		draw_text_button(esContext, "StabilizationSettingsPitchRatePIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchRatePID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRatePID.ILimit = %f", uavtalk_StabilizationSettingsData.PitchRatePID.ILimit);
		draw_text_button(esContext, "StabilizationSettingsPitchRatePIDILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchRatePID_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRatePID.Kp = %f", uavtalk_StabilizationSettingsData.YawRatePID.Kp);
		draw_text_button(esContext, "StabilizationSettingsYawRatePIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawRatePID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRatePID.Ki = %f", uavtalk_StabilizationSettingsData.YawRatePID.Ki);
		draw_text_button(esContext, "StabilizationSettingsYawRatePIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawRatePID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRatePID.Kd = %f", uavtalk_StabilizationSettingsData.YawRatePID.Kd);
		draw_text_button(esContext, "StabilizationSettingsYawRatePIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawRatePID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRatePID.ILimit = %f", uavtalk_StabilizationSettingsData.YawRatePID.ILimit);
		draw_text_button(esContext, "StabilizationSettingsYawRatePIDILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawRatePID_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollPI.Kp = %f", uavtalk_StabilizationSettingsData.RollPI.Kp);
		draw_text_button(esContext, "StabilizationSettingsRollPIKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollPI_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollPI.Ki = %f", uavtalk_StabilizationSettingsData.RollPI.Ki);
		draw_text_button(esContext, "StabilizationSettingsRollPIKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollPI_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollPI.ILimit = %f", uavtalk_StabilizationSettingsData.RollPI.ILimit);
		draw_text_button(esContext, "StabilizationSettingsRollPIILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollPI_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchPI.Kp = %f", uavtalk_StabilizationSettingsData.PitchPI.Kp);
		draw_text_button(esContext, "StabilizationSettingsPitchPIKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchPI_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchPI.Ki = %f", uavtalk_StabilizationSettingsData.PitchPI.Ki);
		draw_text_button(esContext, "StabilizationSettingsPitchPIKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchPI_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchPI.ILimit = %f", uavtalk_StabilizationSettingsData.PitchPI.ILimit);
		draw_text_button(esContext, "StabilizationSettingsPitchPIILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchPI_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawPI.Kp = %f", uavtalk_StabilizationSettingsData.YawPI.Kp);
		draw_text_button(esContext, "StabilizationSettingsYawPIKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawPI_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawPI.Ki = %f", uavtalk_StabilizationSettingsData.YawPI.Ki);
		draw_text_button(esContext, "StabilizationSettingsYawPIKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawPI_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawPI.ILimit = %f", uavtalk_StabilizationSettingsData.YawPI.ILimit);
		draw_text_button(esContext, "StabilizationSettingsYawPIILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawPI_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarSensitivity.Roll = %f", uavtalk_StabilizationSettingsData.VbarSensitivity.Roll);
		draw_text_button(esContext, "StabilizationSettingsVbarSensitivityRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarSensitivity_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarSensitivity.Pitch = %f", uavtalk_StabilizationSettingsData.VbarSensitivity.Pitch);
		draw_text_button(esContext, "StabilizationSettingsVbarSensitivityPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarSensitivity_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarSensitivity.Yaw = %f", uavtalk_StabilizationSettingsData.VbarSensitivity.Yaw);
		draw_text_button(esContext, "StabilizationSettingsVbarSensitivityYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarSensitivity_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarRollPID.Kp = %f", uavtalk_StabilizationSettingsData.VbarRollPID.Kp);
		draw_text_button(esContext, "StabilizationSettingsVbarRollPIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarRollPID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarRollPID.Ki = %f", uavtalk_StabilizationSettingsData.VbarRollPID.Ki);
		draw_text_button(esContext, "StabilizationSettingsVbarRollPIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarRollPID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarRollPID.Kd = %f", uavtalk_StabilizationSettingsData.VbarRollPID.Kd);
		draw_text_button(esContext, "StabilizationSettingsVbarRollPIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarRollPID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarPitchPID.Kp = %f", uavtalk_StabilizationSettingsData.VbarPitchPID.Kp);
		draw_text_button(esContext, "StabilizationSettingsVbarPitchPIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarPitchPID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarPitchPID.Ki = %f", uavtalk_StabilizationSettingsData.VbarPitchPID.Ki);
		draw_text_button(esContext, "StabilizationSettingsVbarPitchPIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarPitchPID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarPitchPID.Kd = %f", uavtalk_StabilizationSettingsData.VbarPitchPID.Kd);
		draw_text_button(esContext, "StabilizationSettingsVbarPitchPIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarPitchPID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarYawPID.Kp = %f", uavtalk_StabilizationSettingsData.VbarYawPID.Kp);
		draw_text_button(esContext, "StabilizationSettingsVbarYawPIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarYawPID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarYawPID.Ki = %f", uavtalk_StabilizationSettingsData.VbarYawPID.Ki);
		draw_text_button(esContext, "StabilizationSettingsVbarYawPIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarYawPID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarYawPID.Kd = %f", uavtalk_StabilizationSettingsData.VbarYawPID.Kd);
		draw_text_button(esContext, "StabilizationSettingsVbarYawPIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarYawPID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarTau = %f", uavtalk_StabilizationSettingsData.VbarTau);
		draw_text_button(esContext, "StabilizationSettingsVbarTauChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarTau_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "GyroTau = %f", uavtalk_StabilizationSettingsData.GyroTau);
		draw_text_button(esContext, "StabilizationSettingsGyroTauChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsGyroTau_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DerivativeGamma = %f", uavtalk_StabilizationSettingsData.DerivativeGamma);
		draw_text_button(esContext, "StabilizationSettingsDerivativeGammaChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsDerivativeGamma_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "WeakLevelingKp = %f", uavtalk_StabilizationSettingsData.WeakLevelingKp);
		draw_text_button(esContext, "StabilizationSettingsWeakLevelingKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsWeakLevelingKp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "CoordinatedFlightYawPI.Kp = %f", uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.Kp);
		draw_text_button(esContext, "StabilizationSettingsCoordinatedFlightYawPIKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsCoordinatedFlightYawPI_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "CoordinatedFlightYawPI.Ki = %f", uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.Ki);
		draw_text_button(esContext, "StabilizationSettingsCoordinatedFlightYawPIKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsCoordinatedFlightYawPI_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "CoordinatedFlightYawPI.ILimit = %f", uavtalk_StabilizationSettingsData.CoordinatedFlightYawPI.ILimit);
		draw_text_button(esContext, "StabilizationSettingsCoordinatedFlightYawPIILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsCoordinatedFlightYawPI_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollMax = %i", uavtalk_StabilizationSettingsData.RollMax);
		draw_text_button(esContext, "StabilizationSettingsRollMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollMax_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchMax = %i", uavtalk_StabilizationSettingsData.PitchMax);
		draw_text_button(esContext, "StabilizationSettingsPitchMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchMax_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawMax = %i", uavtalk_StabilizationSettingsData.YawMax);
		draw_text_button(esContext, "StabilizationSettingsYawMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawMax_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RateExpo.Roll = %i", uavtalk_StabilizationSettingsData.RateExpo.Roll);
		draw_text_button(esContext, "StabilizationSettingsRateExpoRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRateExpo_Roll_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RateExpo.Pitch = %i", uavtalk_StabilizationSettingsData.RateExpo.Pitch);
		draw_text_button(esContext, "StabilizationSettingsRateExpoPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRateExpo_Pitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RateExpo.Yaw = %i", uavtalk_StabilizationSettingsData.RateExpo.Yaw);
		draw_text_button(esContext, "StabilizationSettingsRateExpoYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRateExpo_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRateTPA.Threshold = %i", uavtalk_StabilizationSettingsData.RollRateTPA.Threshold);
		draw_text_button(esContext, "StabilizationSettingsRollRateTPAThresholdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollRateTPA_Threshold_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "RollRateTPA.Attenuation = %i", uavtalk_StabilizationSettingsData.RollRateTPA.Attenuation);
		draw_text_button(esContext, "StabilizationSettingsRollRateTPAAttenuationChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsRollRateTPA_Attenuation_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRateTPA.Threshold = %i", uavtalk_StabilizationSettingsData.PitchRateTPA.Threshold);
		draw_text_button(esContext, "StabilizationSettingsPitchRateTPAThresholdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchRateTPA_Threshold_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PitchRateTPA.Attenuation = %i", uavtalk_StabilizationSettingsData.PitchRateTPA.Attenuation);
		draw_text_button(esContext, "StabilizationSettingsPitchRateTPAAttenuationChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsPitchRateTPA_Attenuation_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRateTPA.Threshold = %i", uavtalk_StabilizationSettingsData.YawRateTPA.Threshold);
		draw_text_button(esContext, "StabilizationSettingsYawRateTPAThresholdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawRateTPA_Threshold_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawRateTPA.Attenuation = %i", uavtalk_StabilizationSettingsData.YawRateTPA.Attenuation);
		draw_text_button(esContext, "StabilizationSettingsYawRateTPAAttenuationChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsYawRateTPA_Attenuation_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarGyroSuppress = %i", uavtalk_StabilizationSettingsData.VbarGyroSuppress);
		draw_text_button(esContext, "StabilizationSettingsVbarGyroSuppressChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarGyroSuppress_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarPiroComp = %i (%s)", uavtalk_StabilizationSettingsData.VbarPiroComp, UAVT_StabilizationSettingsVbarPiroCompOption[uavtalk_StabilizationSettingsData.VbarPiroComp]);
		draw_text_button(esContext, "StabilizationSettingsVbarPiroCompChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarPiroComp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VbarMaxAngle = %i", uavtalk_StabilizationSettingsData.VbarMaxAngle);
		draw_text_button(esContext, "StabilizationSettingsVbarMaxAngleChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsVbarMaxAngle_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "DerivativeCutoff = %i", uavtalk_StabilizationSettingsData.DerivativeCutoff);
		draw_text_button(esContext, "StabilizationSettingsDerivativeCutoffChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsDerivativeCutoff_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxAxisLock = %i", uavtalk_StabilizationSettingsData.MaxAxisLock);
		draw_text_button(esContext, "StabilizationSettingsMaxAxisLockChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsMaxAxisLock_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxAxisLockRate = %i", uavtalk_StabilizationSettingsData.MaxAxisLockRate);
		draw_text_button(esContext, "StabilizationSettingsMaxAxisLockRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsMaxAxisLockRate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxWeakLevelingRate = %i", uavtalk_StabilizationSettingsData.MaxWeakLevelingRate);
		draw_text_button(esContext, "StabilizationSettingsMaxWeakLevelingRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsMaxWeakLevelingRate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "LowThrottleZeroIntegral = %i (%s)", uavtalk_StabilizationSettingsData.LowThrottleZeroIntegral,
				UAVT_StabilizationSettingsLowThrottleZeroIntegralOption[uavtalk_StabilizationSettingsData.LowThrottleZeroIntegral]);
		draw_text_button(esContext, "StabilizationSettingsLowThrottleZeroIntegralChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StabilizationSettingsLowThrottleZeroIntegral_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: StateEstimation
***********************************************/

void UAVT_gui_StateEstimation_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "StateEstimation ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AttitudeFilter = %i (%s)", uavtalk_StateEstimationData.AttitudeFilter, UAVT_StateEstimationAttitudeFilterOption[uavtalk_StateEstimationData.AttitudeFilter]);
		draw_text_button(esContext, "StateEstimationAttitudeFilterChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StateEstimationAttitudeFilter_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "NavigationFilter = %i (%s)", uavtalk_StateEstimationData.NavigationFilter, UAVT_StateEstimationNavigationFilterOption[uavtalk_StateEstimationData.NavigationFilter]);
		draw_text_button(esContext, "StateEstimationNavigationFilterChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_StateEstimationNavigationFilter_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: SystemIdent
***********************************************/

void UAVT_gui_SystemIdent_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "SystemIdent ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Beta.Roll = %f", uavtalk_SystemIdentData.Beta.Roll);
		draw_text_button(esContext, "SystemIdentBetaRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_SystemIdentBeta_Roll_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Beta.Pitch = %f", uavtalk_SystemIdentData.Beta.Pitch);
		draw_text_button(esContext, "SystemIdentBetaPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_SystemIdentBeta_Pitch_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Beta.Yaw = %f", uavtalk_SystemIdentData.Beta.Yaw);
		draw_text_button(esContext, "SystemIdentBetaYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_SystemIdentBeta_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Bias.Roll = %f", uavtalk_SystemIdentData.Bias.Roll);
		draw_text_button(esContext, "SystemIdentBiasRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_SystemIdentBias_Roll_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Bias.Pitch = %f", uavtalk_SystemIdentData.Bias.Pitch);
		draw_text_button(esContext, "SystemIdentBiasPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_SystemIdentBias_Pitch_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Bias.Yaw = %f", uavtalk_SystemIdentData.Bias.Yaw);
		draw_text_button(esContext, "SystemIdentBiasYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_SystemIdentBias_Yaw_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Noise.Roll = %f", uavtalk_SystemIdentData.Noise.Roll);
		draw_text_button(esContext, "SystemIdentNoiseRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_SystemIdentNoise_Roll_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Noise.Pitch = %f", uavtalk_SystemIdentData.Noise.Pitch);
		draw_text_button(esContext, "SystemIdentNoisePitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_SystemIdentNoise_Pitch_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Noise.Yaw = %f", uavtalk_SystemIdentData.Noise.Yaw);
		draw_text_button(esContext, "SystemIdentNoiseYawChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_SystemIdentNoise_Yaw_change,
						 0.0);
	}
	nn++;
}

/***********************************************
    Object: SystemSettings
***********************************************/

void UAVT_gui_SystemSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "SystemSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirframeCategorySpecificConfiguration0 = %i", uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[0]);
		draw_text_button(esContext, "SystemSettingsAirframeCategorySpecificConfiguration0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SystemSettingsAirframeCategorySpecificConfiguration_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirframeCategorySpecificConfiguration1 = %i", uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[1]);
		draw_text_button(esContext, "SystemSettingsAirframeCategorySpecificConfiguration1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SystemSettingsAirframeCategorySpecificConfiguration_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirframeCategorySpecificConfiguration2 = %i", uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[2]);
		draw_text_button(esContext, "SystemSettingsAirframeCategorySpecificConfiguration2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SystemSettingsAirframeCategorySpecificConfiguration_2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirframeCategorySpecificConfiguration3 = %i", uavtalk_SystemSettingsData.AirframeCategorySpecificConfiguration[3]);
		draw_text_button(esContext, "SystemSettingsAirframeCategorySpecificConfiguration3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SystemSettingsAirframeCategorySpecificConfiguration_3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "AirframeType = %i (%s)", uavtalk_SystemSettingsData.AirframeType, UAVT_SystemSettingsAirframeTypeOption[uavtalk_SystemSettingsData.AirframeType]);
		draw_text_button(esContext, "SystemSettingsAirframeTypeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_SystemSettingsAirframeType_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: TrimAnglesSettings
***********************************************/

void UAVT_gui_TrimAnglesSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "TrimAnglesSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Roll = %f", uavtalk_TrimAnglesSettingsData.Roll);
		draw_text_button(esContext, "TrimAnglesSettingsRollChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, UAVT_gui_TrimAnglesSettingsRoll_change,
						 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Pitch = %f", uavtalk_TrimAnglesSettingsData.Pitch);
		draw_text_button(esContext, "TrimAnglesSettingsPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TrimAnglesSettingsPitch_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: TxPIDSettings
***********************************************/

void UAVT_gui_TxPIDSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "TxPIDSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleRange0 = %f", uavtalk_TxPIDSettingsData.ThrottleRange[0]);
		draw_text_button(esContext, "TxPIDSettingsThrottleRange0Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsThrottleRange_0_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleRange1 = %f", uavtalk_TxPIDSettingsData.ThrottleRange[1]);
		draw_text_button(esContext, "TxPIDSettingsThrottleRange1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsThrottleRange_1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MinPID.Instance1 = %f", uavtalk_TxPIDSettingsData.MinPID.Instance1);
		draw_text_button(esContext, "TxPIDSettingsMinPIDInstance1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsMinPID_Instance1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MinPID.Instance2 = %f", uavtalk_TxPIDSettingsData.MinPID.Instance2);
		draw_text_button(esContext, "TxPIDSettingsMinPIDInstance2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsMinPID_Instance2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MinPID.Instance3 = %f", uavtalk_TxPIDSettingsData.MinPID.Instance3);
		draw_text_button(esContext, "TxPIDSettingsMinPIDInstance3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsMinPID_Instance3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxPID.Instance1 = %f", uavtalk_TxPIDSettingsData.MaxPID.Instance1);
		draw_text_button(esContext, "TxPIDSettingsMaxPIDInstance1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsMaxPID_Instance1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxPID.Instance2 = %f", uavtalk_TxPIDSettingsData.MaxPID.Instance2);
		draw_text_button(esContext, "TxPIDSettingsMaxPIDInstance2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsMaxPID_Instance2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxPID.Instance3 = %f", uavtalk_TxPIDSettingsData.MaxPID.Instance3);
		draw_text_button(esContext, "TxPIDSettingsMaxPIDInstance3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsMaxPID_Instance3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "UpdateMode = %i (%s)", uavtalk_TxPIDSettingsData.UpdateMode, UAVT_TxPIDSettingsUpdateModeOption[uavtalk_TxPIDSettingsData.UpdateMode]);
		draw_text_button(esContext, "TxPIDSettingsUpdateModeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsUpdateMode_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Inputs.Instance1 = %i", uavtalk_TxPIDSettingsData.Inputs.Instance1);
		draw_text_button(esContext, "TxPIDSettingsInputsInstance1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsInputs_Instance1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Inputs.Instance2 = %i", uavtalk_TxPIDSettingsData.Inputs.Instance2);
		draw_text_button(esContext, "TxPIDSettingsInputsInstance2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsInputs_Instance2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "Inputs.Instance3 = %i", uavtalk_TxPIDSettingsData.Inputs.Instance3);
		draw_text_button(esContext, "TxPIDSettingsInputsInstance3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsInputs_Instance3_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PIDs.Instance1 = %i", uavtalk_TxPIDSettingsData.PIDs.Instance1);
		draw_text_button(esContext, "TxPIDSettingsPIDsInstance1Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsPIDs_Instance1_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PIDs.Instance2 = %i", uavtalk_TxPIDSettingsData.PIDs.Instance2);
		draw_text_button(esContext, "TxPIDSettingsPIDsInstance2Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsPIDs_Instance2_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "PIDs.Instance3 = %i", uavtalk_TxPIDSettingsData.PIDs.Instance3);
		draw_text_button(esContext, "TxPIDSettingsPIDsInstance3Change", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_TxPIDSettingsPIDs_Instance3_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: VibrationAnalysisSettings
***********************************************/

void UAVT_gui_VibrationAnalysisSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "VibrationAnalysisSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "SampleRate = %i", uavtalk_VibrationAnalysisSettingsData.SampleRate);
		draw_text_button(esContext, "VibrationAnalysisSettingsSampleRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VibrationAnalysisSettingsSampleRate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "FFTWindowSize = %i (%s)", uavtalk_VibrationAnalysisSettingsData.FFTWindowSize,
				UAVT_VibrationAnalysisSettingsFFTWindowSizeOption[uavtalk_VibrationAnalysisSettingsData.FFTWindowSize]);
		draw_text_button(esContext, "VibrationAnalysisSettingsFFTWindowSizeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VibrationAnalysisSettingsFFTWindowSize_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "TestingStatus = %i (%s)", uavtalk_VibrationAnalysisSettingsData.TestingStatus,
				UAVT_VibrationAnalysisSettingsTestingStatusOption[uavtalk_VibrationAnalysisSettingsData.TestingStatus]);
		draw_text_button(esContext, "VibrationAnalysisSettingsTestingStatusChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VibrationAnalysisSettingsTestingStatus_change, 0.0);
	}
	nn++;
}

/***********************************************
    Object: VtolPathFollowerSettings
***********************************************/

void UAVT_gui_VtolPathFollowerSettings_show(ESContext *esContext) {
	uint16_t ny = 0;
	uint16_t nn = 0;
	char tmp_str[1024];
	draw_title(esContext, "VtolPathFollowerSettings ()");
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalPosPI.Kp = %f", uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.Kp);
		draw_text_button(esContext, "VtolPathFollowerSettingsHorizontalPosPIKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsHorizontalPosPI_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalPosPI.Ki = %f", uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.Ki);
		draw_text_button(esContext, "VtolPathFollowerSettingsHorizontalPosPIKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsHorizontalPosPI_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalPosPI.ILimit = %f", uavtalk_VtolPathFollowerSettingsData.HorizontalPosPI.ILimit);
		draw_text_button(esContext, "VtolPathFollowerSettingsHorizontalPosPIILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsHorizontalPosPI_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelPID.Kp = %f", uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Kp);
		draw_text_button(esContext, "VtolPathFollowerSettingsHorizontalVelPIDKpChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsHorizontalVelPID_Kp_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelPID.Ki = %f", uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Ki);
		draw_text_button(esContext, "VtolPathFollowerSettingsHorizontalVelPIDKiChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsHorizontalVelPID_Ki_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelPID.Kd = %f", uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.Kd);
		draw_text_button(esContext, "VtolPathFollowerSettingsHorizontalVelPIDKdChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsHorizontalVelPID_Kd_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelPID.ILimit = %f", uavtalk_VtolPathFollowerSettingsData.HorizontalVelPID.ILimit);
		draw_text_button(esContext, "VtolPathFollowerSettingsHorizontalVelPIDILimitChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsHorizontalVelPID_ILimit_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VelocityFeedforward = %f", uavtalk_VtolPathFollowerSettingsData.VelocityFeedforward);
		draw_text_button(esContext, "VtolPathFollowerSettingsVelocityFeedforwardChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsVelocityFeedforward_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "MaxRollPitch = %f", uavtalk_VtolPathFollowerSettingsData.MaxRollPitch);
		draw_text_button(esContext, "VtolPathFollowerSettingsMaxRollPitchChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsMaxRollPitch_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "UpdatePeriod = %i", uavtalk_VtolPathFollowerSettingsData.UpdatePeriod);
		draw_text_button(esContext, "VtolPathFollowerSettingsUpdatePeriodChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsUpdatePeriod_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "LandingRate = %f", uavtalk_VtolPathFollowerSettingsData.LandingRate);
		draw_text_button(esContext, "VtolPathFollowerSettingsLandingRateChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsLandingRate_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "HorizontalVelMax = %i", uavtalk_VtolPathFollowerSettingsData.HorizontalVelMax);
		draw_text_button(esContext, "VtolPathFollowerSettingsHorizontalVelMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsHorizontalVelMax_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VerticalVelMax = %i", uavtalk_VtolPathFollowerSettingsData.VerticalVelMax);
		draw_text_button(esContext, "VtolPathFollowerSettingsVerticalVelMaxChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsVerticalVelMax_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "ThrottleControl = %i (%s)", uavtalk_VtolPathFollowerSettingsData.ThrottleControl,
				UAVT_VtolPathFollowerSettingsThrottleControlOption[uavtalk_VtolPathFollowerSettingsData.ThrottleControl]);
		draw_text_button(esContext, "VtolPathFollowerSettingsThrottleControlChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsThrottleControl_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "VelocityChangePrediction = %i (%s)", uavtalk_VtolPathFollowerSettingsData.VelocityChangePrediction,
				UAVT_VtolPathFollowerSettingsVelocityChangePredictionOption[uavtalk_VtolPathFollowerSettingsData.VelocityChangePrediction]);
		draw_text_button(esContext, "VtolPathFollowerSettingsVelocityChangePredictionChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsVelocityChangePrediction_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "EndpointRadius = %i", uavtalk_VtolPathFollowerSettingsData.EndpointRadius);
		draw_text_button(esContext, "VtolPathFollowerSettingsEndpointRadiusChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsEndpointRadius_change, 0.0);
	}
	nn++;
	if (nn >= sy && nn < sy + 14) {
		sprintf(tmp_str, "YawMode = %i (%s)", uavtalk_VtolPathFollowerSettingsData.YawMode, UAVT_VtolPathFollowerSettingsYawModeOption[uavtalk_VtolPathFollowerSettingsData.YawMode]);
		draw_text_button(esContext, "VtolPathFollowerSettingsYawModeChange", VIEW_MODE_FCMENU, tmp_str, FONT_WHITE, -1.2, -0.9 + ny++ * 0.12, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP,
						 UAVT_gui_VtolPathFollowerSettingsYawMode_change, 0.0);
	}
	nn++;
}

