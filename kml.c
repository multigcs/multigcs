
#include <all.h>

static void map_kml_parsePoint (xmlDocPtr doc, xmlNodePtr cur, char *name) {
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"coordinates"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				float p_lat = 0.0;
				float p_lon = 0.0;
				float p_alt = 0.0;
				sscanf((char *)key, "%f,%f,%f", &p_lon, &p_lat, &p_alt);
				if (p_lat != 0.0 && p_lon != 0.0) {
					mark_point(GlobalesContext, p_lat, p_lon, p_alt, "text", "", 0, 0.0, 0.0, lat, lon, zoom);
				}
				int n = 0;
				for (n = 1; n < strlen((char *)key) - 1; n++) {
					if (key[n] == ' ' || key[n] == '\n') {
						p_lat = 0.0;
						p_lon = 0.0;
						p_alt = 0.0;
						sscanf((char *)key + n + 1, "%f,%f,%f", &p_lon, &p_lat, &p_alt);
						if (p_lat != 0.0 && p_lon != 0.0) {
							mark_point(GlobalesContext, p_lat, p_lon, p_alt, "text", "", 0, 0.0, 0.0, lat, lon, zoom);
						}
					}
				}
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void map_kml_parseLineString (xmlDocPtr doc, xmlNodePtr cur, char *name) {
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"coordinates"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				float p_lat = 0.0;
				float p_lon = 0.0;
				float p_alt = 0.0;
				sscanf((char *)key, "%f,%f,%f", &p_lon, &p_lat, &p_alt);
				mark_point(GlobalesContext, p_lat, p_lon, p_alt, "text", "", 0, 0.0, 0.0, lat, lon, zoom);
				float last_p_lat = p_lat;
				float last_p_lon = p_lon;
				float last_p_alt = p_alt;
				int n = 0;
				for (n = 1; n < strlen((char *)key) - 1; n++) {
					if (key[n] == ' ' || key[n] == '\n') {
						p_lat = 0.0;
						p_lon = 0.0;
						p_alt = 0.0;
						sscanf((char *)key + n + 1, "%f,%f,%f", &p_lon, &p_lat, &p_alt);
						if (p_lat != 0.0 && p_lon != 0.0) {
							mark_point(GlobalesContext, p_lat, p_lon, p_alt, "", "", 0, 0.0, 0.0, lat, lon, zoom);
							mark_route(GlobalesContext, last_p_lat, last_p_lon, last_p_alt, p_lat, p_lon, p_alt, 1, lat, lon, zoom);
							last_p_lat = p_lat;
							last_p_lon = p_lon;
							last_p_alt = p_alt;
						}
					}
				}
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void map_kml_parsePolygon (xmlDocPtr doc, xmlNodePtr cur, char *name) {
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"extrude"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				printf("#extrude# %s ##\n", (char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"altitudeMode"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				printf("#altitudeMode# %s ##\n", (char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"outerBoundaryIs"))) {
			xmlNodePtr cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if ((!xmlStrcasecmp(cur2->name, (const xmlChar *)"LinearRing"))) {
					xmlNodePtr cur3 = cur2->xmlChildrenNode;
					while (cur3 != NULL) {
						if ((!xmlStrcasecmp(cur3->name, (const xmlChar *)"coordinates"))) {
							key = xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);
							if (key != NULL) {
								float p_lat = 0.0;
								float p_lon = 0.0;
								float p_alt = 0.0;
								sscanf((char *)key, "%f,%f,%f", &p_lon, &p_lat, &p_alt);
								mark_point(GlobalesContext, p_lat, p_lon, p_alt, name, "", 0, 0.0, 0.0, lat, lon, zoom);
								float last_p_lat = p_lat;
								float last_p_lon = p_lon;
								float last_p_alt = p_alt;
								int n = 0;
								for (n = 1; n < strlen((char *)key) - 1; n++) {
									if (key[n] == ' ' || key[n] == '\n') {
										p_lat = 0.0;
										p_lon = 0.0;
										p_alt = 0.0;
										sscanf((char *)key + n + 1, "%f,%f,%f", &p_lon, &p_lat, &p_alt);
										if (p_lat != 0.0 && p_lon != 0.0) {
											mark_route(GlobalesContext, last_p_lat, last_p_lon, last_p_alt, p_lat, p_lon, p_alt, 1, lat, lon, zoom);
											last_p_lat = p_lat;
											last_p_lon = p_lon;
											last_p_alt = p_alt;
										}
									}
								}
							}
							xmlFree(key);
						}
						cur3 = cur3->next;
					}
				}
				cur2 = cur2->next;
			}
		}
		cur = cur->next;
	}
	return;
}

static void map_kml_parseMultiGeometry (xmlDocPtr doc, xmlNodePtr cur, char *name) {
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Polygon"))) {
			map_kml_parsePolygon(doc, cur, name);
		}
		cur = cur->next;
	}
	return;
}

static void map_kml_parsePlacemark (xmlDocPtr doc, xmlNodePtr cur) {
	char name[1024];
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(name, (char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"description"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Point"))) {
			map_kml_parsePoint(doc, cur, name);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"LineString"))) {
			map_kml_parseLineString(doc, cur, name);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Polygon"))) {
			map_kml_parsePolygon(doc, cur, name);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"MultiGeometry"))) {
			map_kml_parseMultiGeometry(doc, cur, name);
		}
		cur = cur->next;
	}
	return;
}

void map_kml_parseDoc (char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	if (strncmp(docname, "./", 2) == 0) {
		docname += 2;
	}
	char *buffer = NULL;
	int len = 0;
	SDL_RWops *ops_file = SDL_RWFromFile(docname, "r");
	if (ops_file == NULL) {
		SDL_Log("kml: Document open failed: %s\n", docname);
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
		SDL_Log("kml: Document parsing failed: %s\n", docname);
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		SDL_Log("Document is Empty!!!\n");
		return;
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Document"))) {
			xmlNodePtr cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if ((!xmlStrcasecmp(cur2->name, (const xmlChar *)"Placemark"))) {
					map_kml_parsePlacemark(doc, cur2);
				}
				cur2 = cur2->next;
			}
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}


