
#include <all.h>


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

uint8_t model_get_dronetype_by_name (char *name) {
	int16_t type = MAV_TYPE_ENUM_END - 1;
	while (type >= 0) {
		if (strcmp(name, dronetypes[type]) == 0) {
			return type;
		}
		type--;
	}
	return 0;
}

static uint8_t model_null (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

static uint8_t model_mavlink_sysid_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		ModelData[ModelActive].mavlink_sysid++;
	} else if (button == 5) {
		ModelData[ModelActive].mavlink_sysid--;
	}
	return 0;
}

//static uint8_t model_mavlink_compid_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
//	if (button == 4) {
//		ModelData[ModelActive].mavlink_compid++;
//	} else if (button == 5) {
//		ModelData[ModelActive].mavlink_compid--;
//	}
//	return 0;
//}

static uint8_t model_reconnect (char *name, float x, float y, int8_t button, float data, uint8_t action) {
//	set_telemetry(ModelActive, ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud);
	reset_telemetry(ModelActive);
	return 0;
}


uint8_t model_teletype_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if ((int)data < TELETYPE_LAST) {
		ModelData[ModelActive].teletype = (int)data;
	}
	select_teletype = 0;
	reset_telemetry(ModelActive);
	return 0;
}

static uint8_t model_use_deviceid_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	ModelData[ModelActive].use_deviceid = 1 - ModelData[ModelActive].use_deviceid;
	return 0;
}

static uint8_t model_dronetype_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (ModelData[ModelActive].dronetype < MAV_TYPE_ENUM_END - 1) {
		ModelData[ModelActive].dronetype++;
	} else {
		ModelData[ModelActive].dronetype = 0;
	}
	return 0;
}


static uint8_t model_teletype_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	select_teletype = 1;
	return 0;
}


static uint8_t model_baud_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	ModelData[ModelActive].telemetry_baud = atoi(name);
	return 0;
}

static uint8_t model_baud_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	baud_set_callback(model_baud_set);
	baud_set_mode(setup.view_mode);
	return 0;
}


static uint8_t model_device_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	strncpy(ModelData[ModelActive].telemetry_port, name, 199);
	serial_info_get(ModelData[ModelActive].telemetry_port, ModelData[ModelActive].deviceid);
	return 0;
}

static uint8_t model_device_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	device_set_callback(model_device_set);
	device_reset_filter();
	device_add_filter("ttyUSB");
	device_add_filter("ttyACM");
	device_add_filter("ttyS");
	device_add_filter("cu.");
	device_set_mode(setup.view_mode);
	return 0;
}

static uint8_t model_name_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	strncpy(ModelData[ModelActive].name, name, 199);
	return 0;
}

static uint8_t model_name_edit (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	keyboard_set_callback(model_name_set);
	keyboard_set_text(ModelData[ModelActive].name);
	keyboard_set_mode(setup.view_mode);
	return 0;
}

static uint8_t model_save_xml (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	reset_buttons();
	FILE *fr;
	char tmp_str[128];
	sprintf(tmp_str, "mkdir -p %s/models", get_datadirectory());
	system(tmp_str);
	sprintf(tmp_str, "%s/models/%s", get_datadirectory(), name);
	fr = fopen(tmp_str, "wb");
	if (fr != 0) {
		fprintf(fr, "<rcflow>\n");
		fprintf(fr, " <name>%s</name>\n", ModelData[ModelActive].name);
		fprintf(fr, " <image>%s</image>\n", ModelData[ModelActive].image);
		fprintf(fr, " <type>%s</type>\n", dronetypes[ModelData[ModelActive].dronetype]);
		fprintf(fr, " <telemetry>\n");
		fprintf(fr, "  <type>%s</type>\n", teletypes[ModelData[ModelActive].teletype]);
		fprintf(fr, "  <device>%s</device>\n", ModelData[ModelActive].telemetry_port);
		fprintf(fr, "  <baud>%i</baud>\n", ModelData[ModelActive].telemetry_baud);
		if (strstr(ModelData[ModelActive].telemetry_port, "rfcomm") > 0) {
			fprintf(fr, "  <bluetooth_addr>%s</bluetooth_addr>\n", ModelData[ModelActive].telebtaddr);
			fprintf(fr, "  <bluetooth_pin>%s</bluetooth_pin>\n", ModelData[ModelActive].telebtpin);
		}
		fprintf(fr, " </telemetry>\n");
		mavlink_xml_save(ModelActive, fr);
		mwi21_xml_save(ModelActive, fr);
		openpilot_xml_save(fr);
		fprintf(fr, "</rcflow>\n");
		fclose(fr);
	}
	return 0;
}

uint8_t model_save (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	char tmp_str[200];
	reset_buttons();
	keyboard_set_callback(model_save_xml);
	if (strstr(ModelData[ModelActive].name, ".xml\0") > 0) {
		strncpy(tmp_str, ModelData[ModelActive].name, 199);
	} else {
		sprintf(tmp_str, "%s.xml", ModelData[ModelActive].name);
	}
	keyboard_set_text(tmp_str);
	keyboard_set_mode(setup.view_mode);
	return 0;
}

static void die(char *msg) {
	SDL_Log("%s", msg);
	return;
}

static void model_parseTelemetry (xmlDocPtr doc, xmlNodePtr cur) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"type"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				ModelData[ModelActive].teletype = model_get_teletype_by_name((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"device"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData[ModelActive].telemetry_port, (char *)key, 199);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"baud"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				ModelData[ModelActive].telemetry_baud = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"bluetooth_addr"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData[ModelActive].telebtaddr, (char *)key, 199);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"bluetooth_pin"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData[ModelActive].telebtpin, (char *)key, 199);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void model_parseDoc (char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlChar *key;

	if (strncmp(docname, "./", 2) == 0) {
		docname += 2;
	}

	char *buffer = NULL;
	int len = 0;
	SDL_RWops *ops_file = SDL_RWFromFile(docname, "r");
	if (ops_file == NULL) {
		SDL_Log("map: Document open failed: %s\n", docname);
		return;
	}
	len = SDL_RWseek(ops_file, 0, SEEK_END);
	SDL_RWseek(ops_file, 0, SEEK_SET);
	buffer = malloc(len);
	SDL_RWread(ops_file, buffer, 1, len);
	doc = xmlParseMemory(buffer, len);
	SDL_RWclose(ops_file);
	free(buffer);

	if (doc == NULL) {
		SDL_Log("Document parsing failed: %s\n", docname);
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		die("Document is Empty!!!\n");
		return;
	}
	strncpy(ModelData[ModelActive].name, basename(docname), 199);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData[ModelActive].name, (char *)key, 199);
				if (strstr(ModelData[ModelActive].name, ".xml\0") <= 0) {
					strcat(ModelData[ModelActive].name, ".xml");
				}
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"image"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(ModelData[ModelActive].image, (char *)key, 511);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"type"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				ModelData[ModelActive].dronetype = model_get_dronetype_by_name((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"telemetry"))) {
			model_parseTelemetry(doc, cur);

		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"mavlink"))) {
			mavlink_xml_load(ModelActive, doc, cur);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"mwi21"))) {
			mwi21_xml_load(ModelActive, doc, cur);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"OpenPilot"))) {
			openpilot_xml_load(doc, cur);

		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}

static uint8_t model_load_xml (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	model_parseDoc(name);
	reset_buttons();
	return 0;
}

static uint8_t model_load (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	reset_buttons();
	char tmp_str[128];
	sprintf(tmp_str, "%s/models", get_datadirectory());
	filesystem_set_dir(tmp_str);
	filesystem_set_callback(model_load_xml);
	filesystem_reset_filter();
	filesystem_add_filter(".xml\0");
	filesystem_set_mode(setup.view_mode);
	return 0;
}

static uint8_t model_image_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	strncpy(ModelData[ModelActive].image, name, 511);
	reset_buttons();
	return 0;
}

static uint8_t model_image_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
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
Object3d obj3d_dronetype;
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
	if (ModelData[ModelActive].name[0] == 0) {
		strcpy(ModelData[ModelActive].name, "model1");
	}
	sprintf(tmp_str, "%s", ModelData[ModelActive].name);
	draw_text_button(esContext, "model_name_edit", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_name_edit, 0);
	n++;

	draw_text_button(esContext, "model_type", VIEW_MODE_MODEL, "TYPE:", FONT_WHITE, -1.1, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_dronetype_change, 0);
	draw_text_button(esContext, "dronetype_change", VIEW_MODE_MODEL, dronetypes[ModelData[ModelActive].dronetype], FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_dronetype_change, 0);


#ifdef SDLGL
//	get_background_model(ModelActive, tmp_str);
	sprintf(tmp_str, "%s/obj3d/%s.obj", BASE_DIR, dronetypes[ModelData[ModelActive].dronetype]);
	if (file_exists(tmp_str) != 0) {
		static uint8_t startup = 0;
		static float rotate = 0.0;
		rotate += 0.5;
		if (startup == 0 || strcmp(obj3d_dronetype.name, tmp_str) != 0) {
			startup = 1;
			if (obj3d_dronetype.faces_num != 0) {
				object3d_free(&obj3d_dronetype);
			}
			object3d_load(&obj3d_dronetype, tmp_str);
		}
		glPushMatrix();
		glTranslatef(0.5, (-0.8 + n * 0.12 + 0.2) * -1.0, -2.0);
		if (ModelData[ModelActive].heartbeat == 0) {
			glRotatef(rotate, 0.2, 1.0, 0.3);
		} else {
			glRotatef(-90.0, 1.0, 0.0, 0.0);
//			glRotatef(ModelData[ModelActive].yaw, 0.0, 0.0, -1.0);
			glRotatef(ModelData[ModelActive].pitch, 1.0, 0.0, 0.0);
			glRotatef(ModelData[ModelActive].roll, 0.0, 1.0, 0.0);
		}
		glScalef(0.25, 0.25, 0.25);
		object3d_draw(&obj3d_dronetype, 255, 255, 255, 100);
		glPopMatrix();
	} else {
		sprintf(tmp_str, "%s/textures/%s.png", BASE_DIR, dronetypes[ModelData[ModelActive].dronetype]);
		draw_image_f3(esContext, -1.1 + 1.0, -0.8 + n * 0.12 - 0.02, -1.1 + 1.0 + 0.1, -0.8 + n * 0.12 + 0.1 - 0.02, 0.002, tmp_str);
	}
#else
	sprintf(tmp_str, "%s/textures/%s.png", BASE_DIR, dronetypes[ModelData[ModelActive].dronetype]);
	draw_image_f3(esContext, -1.1 + 1.0, -0.8 + n * 0.12 - 0.02, -1.1 + 1.0 + 0.1, -0.8 + n * 0.12 + 0.1 - 0.02, 0.002, tmp_str);
#endif


	n++;

	draw_text_button(esContext, "model_image_change", VIEW_MODE_MODEL, "IMAGE:", FONT_WHITE, -1.1, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_image_change, 0);
	draw_image_f3(esContext, -1.1 + 0.3, -0.8 + n * 0.12 - 0.02, -1.2 + 0.3 + 0.4, -0.8 + n * 0.12 + 0.3 - 0.02, 0.002, ModelData[ModelActive].image);
	n++;

	n++;
	draw_text_button(esContext, "Telemetry", VIEW_MODE_MODEL, "Telemetry", FONT_WHITE, -1.25, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_null, (float)n);
	draw_line_f3(esContext, -1.3, -0.8 + n * 0.12 + 0.1, 0.002, 1.25, -0.8 + n * 0.12 + 0.1, 0.002, 255, 255, 0, 128);
	n++;

	draw_text_button(esContext, "model_load3", VIEW_MODE_MODEL, "TYPE:", FONT_WHITE, -1.1, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_teletype_change, 0);
	draw_text_button(esContext, "model_teletype_change", VIEW_MODE_MODEL, teletypes[ModelData[ModelActive].teletype], FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_teletype_change, 0);
	n++;


#ifdef SDLGL
	if (ModelData[ModelActive].pilottype == MAV_AUTOPILOT_PIXHAWK) {
		sprintf(tmp_str, "%s/obj3d/%s.obj", BASE_DIR, "PIXHAWK");
	} else {
		sprintf(tmp_str, "%s/obj3d/%s.obj", BASE_DIR, teletypes[ModelData[ModelActive].teletype]);
	}
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
		glTranslatef(0.5, -0.15, -2.0);
		glRotatef(rotate, -1.0, -1.0, 0.2);
		glScalef(0.25, 0.25, 0.25);
		object3d_draw(&obj3d_teletype, 255, 255, 255, 100);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
	}
#endif


	draw_text_f3(esContext, -1.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "DEVICE:");
	if (ModelData[ModelActive].telemetry_port[0] == 0) {
//		strcpy(ModelData[ModelActive].telemetry_port, "/dev/rfcomm0");
	}
	sprintf(tmp_str, "%s [SELECT]", ModelData[ModelActive].telemetry_port);
	draw_text_button(esContext, "device_select", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_device_change, 0);

	if (strcmp(ModelData[ModelActive].telemetry_port, "UDP") != 0 && strcmp(ModelData[ModelActive].telemetry_port, "TCP") != 0) {
		n++;
		draw_text_f3(esContext, -1.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "BAUD:");
		sprintf(tmp_str, "%i [CHANGE]", ModelData[ModelActive].telemetry_baud);
		draw_text_button(esContext, "rc_baud", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_baud_change, n);

		n++;
		draw_text_f3(esContext, -1.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "USEID:");
		sprintf(tmp_str, "%i [CHANGE]", ModelData[ModelActive].use_deviceid);
		if (ModelData[ModelActive].use_deviceid == 1) {
			draw_text_button(esContext, "rc_useid", VIEW_MODE_MODEL, tmp_str, FONT_GREEN, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_use_deviceid_change, n);
			n++;
			draw_text_f3(esContext, -1.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "ID:");
			draw_text_button(esContext, "rc_deviceid", VIEW_MODE_MODEL, ModelData[ModelActive].deviceid, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_null, n);
		} else {
			draw_text_button(esContext, "rc_useid", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_use_deviceid_change, n);
		}
	} else {
		if (ModelData[ModelActive].teletype == TELETYPE_ARDUPILOT) {
			n++;
			draw_text_f3(esContext, -1.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "USEID:");
			sprintf(tmp_str, "%i [CHANGE]", ModelData[ModelActive].use_deviceid);
			if (ModelData[ModelActive].use_deviceid == 1) {
				draw_text_button(esContext, "rc_useid", VIEW_MODE_MODEL, tmp_str, FONT_GREEN, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_use_deviceid_change, n);
				n++;
				draw_text_f3(esContext, -1.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "SysID:");
				sprintf(tmp_str, "%i [CHANGE]", ModelData[ModelActive].mavlink_sysid);
				draw_text_button(esContext, "rc_mavlink_sysid", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_mavlink_sysid_change, n);
			} else {
				draw_text_button(esContext, "rc_useid", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.3, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_use_deviceid_change, n);
			}
		}
	}



	if (strstr(ModelData[ModelActive].telemetry_port, "rfcomm") > 0) {
		n++;
		draw_text_f3(esContext, -1.1 + 0.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "BLUETOOTH_DEVICE:");
		if (ModelData[ModelActive].telebtaddr[0] == 0) {
			strcpy(ModelData[ModelActive].telebtaddr, "00:00:00:00:00:00");
		}
		sprintf(tmp_str, "%s [RESCAN]", ModelData[ModelActive].telebtaddr);
		draw_text_button(esContext, "bt_scan", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.8, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_null, n);

		n++;
		draw_text_f3(esContext, -1.1 + 0.1, -0.8 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "BLUETOOTH_PIN:");
		if (ModelData[ModelActive].telebtpin[0] == 0) {
			strcpy(ModelData[ModelActive].telebtpin, "1234");
		}
		sprintf(tmp_str, "%s [CHANGE]", ModelData[ModelActive].telebtpin);
		draw_text_button(esContext, "bt_pin", VIEW_MODE_MODEL, tmp_str, FONT_WHITE, -1.1 + 0.8, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, model_null, n);
	} else {
		n++;
		n++;
	}

	n = 13;
	draw_text_button(esContext, "model_reconnect", VIEW_MODE_MODEL, "[RECONNECT]", FONT_WHITE, 0.0, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, model_reconnect, n);
	n++;
	draw_text_button(esContext, "model_save", VIEW_MODE_MODEL, "[SAVE]", FONT_WHITE, 0.0, -0.8 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, model_save, n);

	screen_keyboard(esContext);
	screen_filesystem(esContext);
	screen_device(esContext);
	screen_baud(esContext);
}

