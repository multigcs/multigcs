
#include <stdint.h>
#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <math.h>
#include <userdata.h>
#include <serial.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <main.h>
#include <model.h>
#include <my_mavlink.h>
#include <my_gps.h>
#include <frsky.h>
#include <openpilot.h>
#include <mwi21.h>
#include <jeti.h>
#include <openpilot_xml.h>
#include <screen_model.h>
#include <SDL_thread.h>
#include <screen_keyboard.h>
#include <screen_filesystem.h>
#include <screen_device.h>
#include <screen_baud.h>
#include <webclient.h>

extern int file_exists (char *fileName);
static uint8_t select_teletype = 0;


uint8_t model_get_teletype_by_name (char *name) {
	int16_t type = TELETYPE_LAST - 1;
	while (type >= 0) {
		if (strcmp(name, teletypes[type]) == 0) {
			return type;
		}
		type--;
	}
	return 0;
}

uint8_t model_get_modeltype_by_name (char *name) {
	int16_t type = MODELTYPE_LAST - 1;
	while (type >= 0) {
		if (strcmp(name, modeltypes[type]) == 0) {
			return type;
		}
		type--;
	}
	return 0;
}

static uint8_t model_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

static uint8_t model_reconnect (char *name, float x, float y, int8_t button, float data) {
	set_telemetry(ModelData.teledevice, ModelData.telebaud);
	return 0;
}


uint8_t model_teletype_set (char *name, float x, float y, int8_t button, float data) {
	if ((int)data < TELETYPE_LAST) {
		ModelData.teletype = (int)data;
	}
	select_teletype = 0;
	reset_telemetry();
	return 0;
}

static uint8_t model_modeltype_change (char *name, float x, float y, int8_t button, float data) {
	if (ModelData.modeltype < MODELTYPE_LAST - 1) {
		ModelData.modeltype++;
	} else {
		ModelData.modeltype = 0;
	}
	return 0;
}


static uint8_t model_teletype_change (char *name, float x, float y, int8_t button, float data) {
	select_teletype = 1;
	return 0;
}


static uint8_t model_baud_set (char *name, float x, float y, int8_t button, float data) {
	ModelData.telebaud = atoi(name);
	return 0;
}

static uint8_t model_baud_change (char *name, float x, float y, int8_t button, float data) {
	baud_set_callback(model_baud_set);
	baud_set_mode(setup.view_mode);
	return 0;
}


static uint8_t model_device_set (char *name, float x, float y, int8_t button, float data) {
	strncpy(ModelData.teledevice, name, 199);
	return 0;
}

static uint8_t model_device_change (char *name, float x, float y, int8_t button, float data) {
	device_set_callback(model_device_set);
	device_reset_filter();
	device_add_filter("ttyUSB");
	device_add_filter("ttyACM");
	device_add_filter("ttyS");
	device_add_filter("cu.");
	device_set_mode(setup.view_mode);
	return 0;
}


static uint8_t model_name_set (char *name, float x, float y, int8_t button, float data) {
	strncpy(ModelData.name, name, 199);
	return 0;
}

static uint8_t model_name_edit (char *name, float x, float y, int8_t button, float data) {
	keyboard_set_callback(model_name_set);
	keyboard_set_text(ModelData.name);
	keyboard_set_mode(setup.view_mode);
	return 0;
}



static uint8_t model_save_xml (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	int16_t n = 0;
        FILE *fr;
	char tmp_str[128];
	sprintf(tmp_str, "mkdir -p %s/.multigcs/models", getenv("HOME"));
	system(tmp_str);
	sprintf(tmp_str, "%s/.multigcs/models/%s", getenv("HOME"), name);
        fr = fopen(tmp_str, "w");
	if (fr != 0) {
		fprintf(fr, "<rcflow>\n");
		fprintf(fr, " <name>%s</name>\n", ModelData.name);
		fprintf(fr, " <image>%s</image>\n", ModelData.image);
		fprintf(fr, " <type>%s</type>\n", modeltypes[ModelData.modeltype]);
		fprintf(fr, " <telemetry>\n");
		fprintf(fr, "  <type>%s</type>\n", teletypes[ModelData.teletype]);
		fprintf(fr, "  <device>%s</device>\n", ModelData.teledevice);
		fprintf(fr, "  <baud>%i</baud>\n", ModelData.telebaud);
		if (strstr(ModelData.teledevice, "rfcomm") > 0) {
			fprintf(fr, "  <bluetooth_addr>%s</bluetooth_addr>\n", ModelData.telebtaddr);
			fprintf(fr, "  <bluetooth_pin>%s</bluetooth_pin>\n", ModelData.telebtpin);
		}
		fprintf(fr, " </telemetry>\n");
		fprintf(fr, " <mavlink>\n");
		for (n = 0; n < 500 - 1; n++) {
			if (MavLinkVars[n].name[0] != 0) {
				fprintf(fr, "  <param><name>%s</name><value>%f</value></param>\n", MavLinkVars[n].name, MavLinkVars[n].value);
			}
		}
		fprintf(fr, " </mavlink>\n");
		fprintf(fr, " <mwi21>\n");
		for (n = 0; n < 16; n++) {
			fprintf(fr, "  <pid><id>%i</id><p>%i</p><i>%i</i><d>%i</d></pid>\n", n, mwi_pid[n][0], mwi_pid[n][1], mwi_pid[n][2]);
		}
		for (n = 0; n < 16; n++) {
			fprintf(fr, "  <box><id>%i</id><value>%i</value></box>\n", n, mwi_box[n]);
		}
		fprintf(fr, " </mwi21>\n");

		model_save_xml_OpenPilot(fr);

		fprintf(fr, "</rcflow>\n");
	        fclose(fr);
	}
	return 0;
}

uint8_t model_save (char *name, float x, float y, int8_t button, float data) {
	char tmp_str[200];
	reset_buttons();
	keyboard_set_callback(model_save_xml);
	if (strstr(ModelData.name, ".xml\0") > 0) {
		strncpy(tmp_str, ModelData.name, 199);
	} else {
		sprintf(tmp_str, "%s.xml", ModelData.name);
	}
	keyboard_set_text(tmp_str);
	keyboard_set_mode(setup.view_mode);
	return 0;
}



static void die(char *msg) {
	printf("%s", msg);
	return;
}

static void model_parseTelemetry (xmlDocPtr doc, xmlNodePtr cur) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"type"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				ModelData.teletype = model_get_teletype_by_name((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"device"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData.teledevice, (char *)key, 199);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"baud"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				ModelData.telebaud = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"bluetooth_addr"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData.telebtaddr, (char *)key, 199);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"bluetooth_pin"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData.telebtpin, (char *)key, 199);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void model_parseMavlinkParam (xmlDocPtr doc, xmlNodePtr cur, uint16_t param) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(MavLinkVars[param].name, (char *)key, 199);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"value"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				MavLinkVars[param].value = atof((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void model_parseMavlink (xmlDocPtr doc, xmlNodePtr cur) { 
	uint16_t param = 0;
	for (param = 0; param < 500; param++) {
		MavLinkVars[param].name[0] = 0;
		MavLinkVars[param].value = 0.0;
	}
	param = 0;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"param"))) {
			model_parseMavlinkParam (doc, cur, param++);
		}
		cur = cur->next;
	}
	return;
}

static void model_parseMWI21Pid (xmlDocPtr doc, xmlNodePtr cur, uint16_t pid) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"p"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_pid[pid][0] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"i"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_pid[pid][1] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"d"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_pid[pid][2] = atoi((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void model_parseMWI21Box (xmlDocPtr doc, xmlNodePtr cur, uint16_t box) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"value"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				mwi_box[box] = atoi((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void model_parseMWI21 (xmlDocPtr doc, xmlNodePtr cur) { 
	uint16_t pid = 0;
	uint16_t box = 0;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"pid"))) {
			model_parseMWI21Pid (doc, cur, pid++);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"box"))) {
			model_parseMWI21Box (doc, cur, box++);
		}
		cur = cur->next;
	}
	return;
}

static void model_parseDoc (char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlChar *key;
	doc = xmlParseFile(docname);
	if (doc == NULL) {
		printf("Document parsing failed: %s\n", docname);
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		die("Document is Empty!!!\n");
		return;
	}
	strncpy(ModelData.name, basename(docname), 199);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData.name, (char *)key, 199);
				if (strstr(ModelData.name, ".xml\0") <= 0) {
					strcat(ModelData.name, ".xml");
				}
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"image"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData.image, (char *)key, 511);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"type"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				ModelData.modeltype = model_get_modeltype_by_name((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"telemetry"))) {
			model_parseTelemetry(doc, cur);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"mavlink"))) {
			model_parseMavlink(doc, cur);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"mwi21"))) {
			model_parseMWI21(doc, cur);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"OpenPilot"))) {
			model_parseOpenPilot(doc, cur);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}

static uint8_t model_load_xml (char *name, float x, float y, int8_t button, float data) {
	model_parseDoc(name);
	reset_buttons();
	return 0;
}

static uint8_t model_load (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	char tmp_str[128];
	sprintf(tmp_str, "%s/.multigcs/models", getenv("HOME"));
	filesystem_set_dir(tmp_str);
	filesystem_set_callback(model_load_xml);
	filesystem_reset_filter();
	filesystem_add_filter(".xml\0");
	filesystem_set_mode(setup.view_mode);
	return 0;
}


static uint8_t model_image_set (char *name, float x, float y, int8_t button, float data) {
	strncpy(ModelData.image, name, 511);
	reset_buttons();
	return 0;
}

static uint8_t model_image_change (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	char tmp_str[128];
	sprintf(tmp_str, "%s", BASE_DIR);
	filesystem_set_dir(tmp_str);
	filesystem_set_callback(model_image_set);
	filesystem_reset_filter();
	filesystem_add_filter(".png\0");
	filesystem_set_mode(setup.view_mode);
	return 0;
}

#ifdef SDLGL
Object3d obj3d_modeltype;
Object3d obj3d_teletype;
#endif

void screen_model (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	draw_title(esContext, "Model");

	char tmp_str[100];
	int n = 0;

#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	if (clientmode == 1) {

		draw_text_button(esContext, "clientmode", VIEW_MODE_MODEL, "Client-Mode / No Config", FONT_PINK, 0.0, 0.0, 0.002, 0.1, ALIGN_CENTER, ALIGN_TOP, model_null, (float)n);

		return;
	}

	if (select_teletype == 1) {
		for (n = 0; n < TELETYPE_LAST; n++) {
			draw_text_button(esContext, teletypes[n], VIEW_MODE_MODEL, teletypes[n], FONT_WHITE, -1.25, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_teletype_set, (float)n);
		}
		return;
	}

	draw_text_button(esContext, "Model", VIEW_MODE_MODEL, "Model", FONT_WHITE, -1.25, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_null, (float)n);
	draw_line_f3(esContext, -1.3, -0.8 + n * 0.12 + 0.1, 0.002, 1.25, -0.8 + n * 0.12 + 0.1, 0.002, 255, 255, 0, 128);
	n++;

	draw_text_button(esContext, "model_load", VIEW_MODE_MODEL, "[LOAD]", FONT_WHITE, 1.1, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_RIGHT, ALIGN_TOP, model_load, 0);

	draw_text_button(esContext, "model_load2", VIEW_MODE_MODEL, "NAME:", FONT_WHITE, -1.1, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_name_edit, 0);
	if (ModelData.name[0] == 0) {
		strcpy(ModelData.name, "model1");
	}
	sprintf(tmp_str, "%s", ModelData.name);
	draw_text_button(esContext, "model_name_edit", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_name_edit, 0);
	n++;

	draw_text_button(esContext, "model_type", VIEW_MODE_MODEL, "TYPE:", FONT_WHITE, -1.1, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_modeltype_change, 0);
	draw_text_button(esContext, "modeltype_change", VIEW_MODE_MODEL, modeltypes[ModelData.modeltype], FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_modeltype_change, 0);


#ifdef SDLGL
	sprintf(tmp_str, "%s/obj3d/%s.obj", BASE_DIR, modeltypes[ModelData.modeltype]);
	if (file_exists(tmp_str) != 0) {
		static uint8_t startup = 0;
		static float rotate = 0.0;
		rotate += 0.5;
		if (startup == 0 || strcmp(obj3d_modeltype.name, tmp_str) != 0) {
			startup = 1;
			if (obj3d_modeltype.faces_num != 0) {
				object3d_free(&obj3d_modeltype);
			}
			object3d_load(&obj3d_modeltype, tmp_str);
		}
		glTranslatef(0.5, (-0.8 + n * 0.12 + 0.2) * -1.0, -2.0);
		glRotatef(rotate, 0.2, 1.0, 0.3);
		glScalef(0.25, 0.25, 0.25);
		object3d_draw(&obj3d_modeltype, 255, 255, 255, 100);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
	} else {
		sprintf(tmp_str, "%s/textures/%s.png", BASE_DIR, modeltypes[ModelData.modeltype]);
		draw_image_f3(esContext, -1.1 + 1.0, -0.8 + n * 0.12 - 0.02, -1.1 + 1.0 + 0.1, -0.8 + n * 0.12 + 0.1 - 0.02, 0.002, tmp_str);
	}
#else
	sprintf(tmp_str, "%s/textures/%s.png", BASE_DIR, modeltypes[ModelData.modeltype]);
	draw_image_f3(esContext, -1.1 + 1.0, -0.8 + n * 0.12 - 0.02, -1.1 + 1.0 + 0.1, -0.8 + n * 0.12 + 0.1 - 0.02, 0.002, tmp_str);
#endif


	n++;

	draw_text_button(esContext, "model_image_change", VIEW_MODE_MODEL, "IMAGE:", FONT_WHITE, -1.1, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_image_change, 0);
	draw_image_f3(esContext, -1.1 + 0.3, -0.8 + n * 0.12 - 0.02, -1.2 + 0.3 + 0.4, -0.8 + n * 0.12 + 0.3 - 0.02, 0.002, ModelData.image);
	n++;

	n++;
	draw_text_button(esContext, "Telemetry", VIEW_MODE_MODEL, "Telemetry", FONT_WHITE, -1.25, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_null, (float)n);
	draw_line_f3(esContext, -1.3, -0.8 + n * 0.12 + 0.1, 0.002, 1.25, -0.8 + n * 0.12 + 0.1, 0.002, 255, 255, 0, 128);
	n++;

	draw_text_button(esContext, "model_load3", VIEW_MODE_MODEL, "TYPE:", FONT_WHITE, -1.1, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_teletype_change, 0);
	draw_text_button(esContext, "model_teletype_change", VIEW_MODE_MODEL, teletypes[ModelData.teletype], FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_teletype_change, 0);
	n++;


#ifdef SDLGL
	sprintf(tmp_str, "%s/obj3d/%s.obj", BASE_DIR, teletypes[ModelData.teletype]);
	if (file_exists(tmp_str) != 0) {
		static uint8_t startup = 0;
		static float rotate = 0.0;
		rotate += 0.4;
		if (startup == 0 || strcmp(obj3d_teletype.name, tmp_str) != 0) {
			startup = 1;
			if (obj3d_teletype.faces_num != 0) {
				object3d_free(&obj3d_teletype);
			}
			object3d_load(&obj3d_teletype, tmp_str);
		}
		glTranslatef(0.5, (-0.8 + n * 0.12 + 0.3) * -1.0, -2.0);
		glRotatef(rotate, -1.0, -1.0, 0.2);
		glScalef(0.25, 0.25, 0.25);
		object3d_draw(&obj3d_teletype, 255, 255, 255, 100);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
	}
#endif


	draw_text_f3(esContext, -1.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "DEVICE:");
	if (ModelData.teledevice[0] == 0) {
		strcpy(ModelData.teledevice, "/dev/rfcomm0");
	}
	sprintf(tmp_str, "%s [SELECT]", ModelData.teledevice);
	draw_text_button(esContext, "device_select", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_device_change, 0);

	n++;
	draw_text_f3(esContext, -1.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "BAUD:");
	sprintf(tmp_str, "%i [CHANGE]", ModelData.telebaud);
	draw_text_button(esContext, "rc_baud", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_baud_change, n);

	if (strstr(ModelData.teledevice, "rfcomm") > 0) {
		n++;
		draw_text_f3(esContext, -1.1 + 0.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "BLUETOOTH_DEVICE:");
		if (ModelData.telebtaddr[0] == 0) {
			strcpy(ModelData.telebtaddr, "00:00:00:00:00:00");
		}
		sprintf(tmp_str, "%s [RESCAN]", ModelData.telebtaddr);
		draw_text_button(esContext, "bt_scan", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.8, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_null, n);

		n++;
		draw_text_f3(esContext, -1.1 + 0.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "BLUETOOTH_PIN:");
		if (ModelData.telebtpin[0] == 0) {
			strcpy(ModelData.telebtpin, "1234");
		}
		sprintf(tmp_str, "%s [CHANGE]", ModelData.telebtpin);
		draw_text_button(esContext, "bt_pin", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.8, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_null, n);
	} else {
		n++;
		n++;
	}
	n++;
	n++;
	n++;
	draw_text_button(esContext, "model_reconnect", VIEW_MODE_MODEL, "[RECONNECT]", FONT_WHITE, 0.0, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, model_reconnect, n);
	n++;
	draw_text_button(esContext, "model_save", VIEW_MODE_MODEL, "[SAVE]", FONT_WHITE, 0.0, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, model_save, n);

	screen_keyboard(esContext);
	screen_filesystem(esContext);
	screen_device(esContext);
	screen_baud(esContext);
}

