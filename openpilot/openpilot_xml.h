
void openpilot_save_xml_StabilizationSettings (FILE *fr, StabilizationSettingsData *data);
void openpilot_save_xml_HwSettings (FILE *fr, HwSettingsData *data);
void openpilot_save_xml_SystemSettings (FILE *fr, SystemSettingsData *data);
void model_save_xml_OpenPilot (FILE *fr);
void model_parseOpenPilot_StabilizationSettings (xmlDocPtr doc, xmlNodePtr cur, StabilizationSettingsData *data);
void model_parseOpenPilot_HwSettings (xmlDocPtr doc, xmlNodePtr cur, HwSettingsData *data);
void model_parseOpenPilot_SystemSettings (xmlDocPtr doc, xmlNodePtr cur, SystemSettingsData *data);
void model_parseOpenPilot (xmlDocPtr doc, xmlNodePtr cur);

