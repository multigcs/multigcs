
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
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"outerBoundaryIs")) || (!xmlStrcasecmp(cur->name, (const xmlChar *)"innerBoundaryIs"))) {
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





void map_overlay (ESContext *esContext, float north, float west, float south, float east, float rotate, char *file, float lat, float lon, uint8_t zoom) {
	int mark_x1 = long2x(west, lon, zoom);
	int mark_y1 = lat2y(north, lat, zoom);
	int mark_x2 = long2x(east, lon, zoom);
	int mark_y2 = lat2y(south, lat, zoom);
	float x1 = (float)mark_x1 / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)mark_y1 / (float)esContext->height * 2.0 - 1.0;
	float x2 = (float)mark_x2 / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y2 = (float)mark_y2 / (float)esContext->height * 2.0 - 1.0;

	float diff_x = (x2 - x1) / 2.0;
	float diff_y = (y2 - y1) / 2.0;
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(x1 + diff_x, -(y1 + diff_y), 0.0);
	glRotatef(rotate, 0.0, 0.0, 1.0);
	glTranslatef(-(x1 + diff_x), y1 + diff_y, 0.0);
	draw_image_f3(esContext, x1, y1, x2, y2, 1.0, file);

	glPopMatrix();
#endif
}


static void map_kml_parseGroundOverlay (xmlDocPtr doc, xmlNodePtr cur) {
	float north = 0.0;
	float south = 0.0;
	float east = 0.0;
	float west = 0.0;
	char name[1024];
	char href[1024];
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(name, (char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Icon"))) {
			xmlNodePtr cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if ((!xmlStrcasecmp(cur2->name, (const xmlChar *)"href"))) {
					key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
					if (key != NULL) {
						strcpy(href, (char *)key);
					}
					xmlFree(key);
				}
				cur2 = cur2->next;
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"LatLonQuad")) || (!xmlStrcasecmp(cur->name, (const xmlChar *)"gx:LatLonQuad"))) {
			xmlNodePtr cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if ((!xmlStrcasecmp(cur2->name, (const xmlChar *)"coordinates"))) {
					key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
					if (key != NULL) {
						float px1 = 0.0;
						float py1 = 0.0;
						float pz1 = 0.0;
						float px2 = 0.0;
						float py2 = 0.0;
						float pz2 = 0.0;
						float px3 = 0.0;
						float py3 = 0.0;
						float pz3 = 0.0;
						float px4 = 0.0;
						float py4 = 0.0;
						float pz4 = 0.0;
						sscanf((char *)key, "%f,%f,%f %f,%f,%f %f,%f,%f %f,%f,%f", &px1, &py1, &pz1, &px2, &py2, &pz2, &px3, &py3, &pz3, &px4, &py4, &pz4);
						int mx1 = long2x(px1, lon, zoom);
						int my1 = lat2y(py1, lat, zoom);
						int mx2 = long2x(px2, lon, zoom);
						int my2 = lat2y(py2, lat, zoom);
						int mx3 = long2x(px3, lon, zoom);
						int my3 = lat2y(py3, lat, zoom);
						int mx4 = long2x(px4, lon, zoom);
						int my4 = lat2y(py4, lat, zoom);
						float x1 = (float)mx1 / (float)GlobalesContext->width * 2.0 * aspect - 1.0 * aspect;
						float y1 = (float)my1 / (float)GlobalesContext->height * 2.0 - 1.0;
						float x2 = (float)mx2 / (float)GlobalesContext->width * 2.0 * aspect - 1.0 * aspect;
						float y2 = (float)my2 / (float)GlobalesContext->height * 2.0 - 1.0;
						float x3 = (float)mx3 / (float)GlobalesContext->width * 2.0 * aspect - 1.0 * aspect;
						float y3 = (float)my3 / (float)GlobalesContext->height * 2.0 - 1.0;
						float x4 = (float)mx4 / (float)GlobalesContext->width * 2.0 * aspect - 1.0 * aspect;
						float y4 = (float)my4 / (float)GlobalesContext->height * 2.0 - 1.0;
						float z1 = (float)get_altitude(py1, px1) / alt_zoom;
						float z2 = (float)get_altitude(py2, px2) / alt_zoom;
						float z3 = (float)get_altitude(py3, px3) / alt_zoom;
						float z4 = (float)get_altitude(py4, px4) / alt_zoom;
#ifdef SDLGL
						draw_image_f12(GlobalesContext, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, href);
#endif
					}
					xmlFree(key);
				}
				cur2 = cur2->next;
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"LatLonBox"))) {
			xmlNodePtr cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if ((!xmlStrcasecmp(cur2->name, (const xmlChar *)"north"))) {
					key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
					if (key != NULL) {
						north = atof((char *)key);
					}
					xmlFree(key);
				} else if ((!xmlStrcasecmp(cur2->name, (const xmlChar *)"south"))) {
					key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
					if (key != NULL) {
						south = atof((char *)key);
					}
					xmlFree(key);
				} else if ((!xmlStrcasecmp(cur2->name, (const xmlChar *)"east"))) {
					key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
					if (key != NULL) {
						east = atof((char *)key);
					}
					xmlFree(key);
				} else if ((!xmlStrcasecmp(cur2->name, (const xmlChar *)"west"))) {
					key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
					if (key != NULL) {
						west = atof((char *)key);
					}
					xmlFree(key);
				}
				cur2 = cur2->next;
			}
			map_overlay(GlobalesContext, north, west, south, east, 0.0, href, lat, lon, zoom);
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
				} else if ((!xmlStrcasecmp(cur2->name, (const xmlChar *)"GroundOverlay"))) {
					map_kml_parseGroundOverlay(doc, cur2);
				}
				cur2 = cur2->next;
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"GroundOverlay"))) {
			map_kml_parseGroundOverlay(doc, cur);

		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}


