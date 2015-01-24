
void openpilot_save_xml_StabilizationSettings (FILE *fr, UAVT_StabilizationSettingsData *data);
void openpilot_save_xml_HwSettings (FILE *fr, UAVT_HwSettingsData *data);
void openpilot_save_xml_SystemSettings (FILE *fr, UAVT_SystemSettingsData *data);
void model_save_xml_OpenPilot (FILE *fr);
void model_parseOpenPilot_StabilizationSettings (xmlDocPtr doc, xmlNodePtr cur, UAVT_StabilizationSettingsData *data);
void model_parseOpenPilot_HwSettings (xmlDocPtr doc, xmlNodePtr cur, UAVT_HwSettingsData *data);
void model_parseOpenPilot_SystemSettings (xmlDocPtr doc, xmlNodePtr cur, UAVT_SystemSettingsData *data);
void model_parseOpenPilot (xmlDocPtr doc, xmlNodePtr cur);

