
#include <all.h>

void openpilot_save_xml_StabilizationSettings (FILE *fr, UAVT_StabilizationSettingsData *data) {
	fprintf(fr, "  <StabilizationSettings>\n");
	fprintf(fr, "  </StabilizationSettings>\n");
}


void openpilot_save_xml_HwSettings (FILE *fr, UAVT_HwSettingsData *data) {
	fprintf(fr, "  <HwSettings>\n");
	fprintf(fr, "  </HwSettings>\n");
}


void openpilot_save_xml_SystemSettings (FILE *fr, UAVT_SystemSettingsData *data) {
	fprintf(fr, "  <SystemSettings>\n");
	fprintf(fr, "  </SystemSettings>\n");
}


void model_save_xml_OpenPilot (FILE *fr) {
	fprintf(fr, " <OpenPilot>\n");
	fprintf(fr, " </OpenPilot>\n");
	return;
}


#ifndef ANDROID

void model_parseOpenPilot_StabilizationSettings (xmlDocPtr doc, xmlNodePtr cur, UAVT_StabilizationSettingsData *data) {
/*
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if (1 == 2) {
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"ManualRate_Roll"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->ManualRate[0] = atof((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
*/
	return;
}


void model_parseOpenPilot_HwSettings (xmlDocPtr doc, xmlNodePtr cur, UAVT_HwSettingsData *data) {
	return;
}


void model_parseOpenPilot_SystemSettings (xmlDocPtr doc, xmlNodePtr cur, UAVT_SystemSettingsData *data) {
	return;
}


void model_parseOpenPilot (xmlDocPtr doc, xmlNodePtr cur) {
	return;
}

#else

void model_parseOpenPilot (xmlDocPtr doc, xmlNodePtr cur) {
	return;
}

#endif
