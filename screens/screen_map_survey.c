
#include <all.h>

Survey SurveySetup;
alist list[PMAX + 2];

float f_max (float a, float b) {
	if (a > b) {
		return a;
	}
	return b;
}

float f_min (float a, float b) {
	if (a < b) {
		return a;
	}
	return b;
}

uint8_t onSegment (float px, float py, float qx, float qy, float rx, float ry) {
	if (qx <= f_max(px, rx) && qx >= f_min(px, rx) && qy <= f_max(py, ry) && qy >= f_min(py, ry)) {
		return 1;
	}
	return 0;
}

int orientation (float px, float py, float qx, float qy, float rx, float ry) {
	float val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
    if (val == 0.0) {
		return 0;
	}
    return (val > 0.0) ? 1: 2;
}
 
uint8_t intersect_check (float p1x, float p1y, float q1x, float q1y, float p2x, float p2y, float q2x, float q2y) {
    int o1 = orientation(p1x, p1y, q1x, q1y, p2x, p2y);
    int o2 = orientation(p1x, p1y, q1x, q1y, q2x, q2y);
    int o3 = orientation(p2x, p2y, q2x, q2y, p1x, p1y);
    int o4 = orientation(p2x, p2y, q2x, q2y, q1x, q1y);
    if (o1 != o2 && o3 != o4) {
        return 1;
	}
    if (o1 == 0 && onSegment(p1x, p1y, p2x, p2y, q1x, q1y))  {
		return 1;
	}
    if (o2 == 0 && onSegment(p1x, p1y, q2x, q2y, q1x, q1y)) {
		return 1;
	}
    if (o3 == 0 && onSegment(p2x, p2y, p1x, p1y, q2x, q2y)) {
		return 1;
	}
    if (o4 == 0 && onSegment(p2x, p2y, q1x, q1y, q2x, q2y)) {
		return 1;
	}
    return 0;
}

int8_t survey_check_intersect_nofly (ESContext *esContext, float lastn_x, float lastn_y, float px1, float py1) {
	int nfn = 0;
	for (nfn = 0; nfn < 255; nfn++) {
		int num = 0;
		float pmark_x = 0.0;
		float pmark_y = 0.0;
		float last_x = 0.0;
		float last_y = 0.0;
		for (num = 1; num < MAX_POLYPOINTS; num++) {
			if (PolyPointsNoFly[num].num == nfn && PolyPointsNoFly[num].p_lat != 0.0) {
				pmark_x = long2x(PolyPointsNoFly[num].p_long, lon, zoom);
				pmark_y = lat2y(PolyPointsNoFly[num].p_lat, lat, zoom);
				float px2 = (float)(pmark_x) / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
				float py2 = (float)(pmark_y) / (float)esContext->height * 2.0 - 1.0;
				if (last_x != 0.0 && last_y != 0.0) {
					if (intersect_check(lastn_x, lastn_y, px1, py1, last_x, last_y, px2, py2) == 1) {
						return nfn;
					}
				}
				last_x = px2;
				last_y = py2;
			}
		}
	}
	return -1;
}

int8_t survey_check_intersect_nofly2point (ESContext *esContext, int nfn, float px, float py, float px2, float py2) {
	int num = 0;
	float pmark_x = 0.0;
	float pmark_y = 0.0;
	float last_x = 0.0;
	float last_y = 0.0;
	for (num = 1; num < MAX_POLYPOINTS; num++) {
		if (PolyPointsNoFly[num].num == nfn && PolyPointsNoFly[num].p_lat != 0.0) {
			pmark_x = long2x(PolyPointsNoFly[num].p_long, lon, zoom);
			pmark_y = lat2y(PolyPointsNoFly[num].p_lat, lat, zoom);
			float px1 = (float)(pmark_x) / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
			float py1 = (float)(pmark_y) / (float)esContext->height * 2.0 - 1.0;
			last_x = px1;
			last_y = py1;
		}
	}
	for (num = 1; num < MAX_POLYPOINTS; num++) {
		if (PolyPointsNoFly[num].num == nfn && PolyPointsNoFly[num].p_lat != 0.0) {
			pmark_x = long2x(PolyPointsNoFly[num].p_long, lon, zoom);
			pmark_y = lat2y(PolyPointsNoFly[num].p_lat, lat, zoom);
			float px1 = (float)(pmark_x) / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
			float py1 = (float)(pmark_y) / (float)esContext->height * 2.0 - 1.0;
			if (last_x != 0.0 && last_y != 0.0) {
				if (px2 == px1 && py2 == py1) {
				} else if (px2 == last_x && py2 == last_y) {
				} else if (intersect_check(px, py, px2, py2, last_x, last_y, px1, py1) == 1) {
					return 1;
				}
			}
			last_x = px1;
			last_y = py1;
		}
	}
	return 0;
}

float dist (Point2D p1, Point2D p2) {
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;
	if (dx < 0.0) {
		dx *= -1;
	}
	if (dy < 0.0) {
		dy *= -1;
	}
	return sqrt((dx * dx) + (dy * dy));
}

void olist_add (Point2D p, Point2D from, int f) {
	int n = 0;
	for (n = 0; n < 100; n++) {
		if (list[n].p.x == p.x && list[n].p.y == p.y) {
			if (list[n].t == IN_OPEN && list[n].f > f) {
				list[n].from.x = from.x;
				list[n].from.y = from.y;
				list[n].f = f;
			}
			break;
		} else if (list[n].t == UNSET) {
			list[n].p.x = p.x;
			list[n].p.y = p.y;
			list[n].from.x = from.x;
			list[n].from.y = from.y;
			list[n].f = f;
			list[n].t = IN_OPEN;
			break;
		}
	}
}

void olist_mv2close (Point2D p, Point2D from, int f) {
	int n = 0;
	for (n = 0; n < 100; n++) {
		if (list[n].p.x == p.x && list[n].p.y == p.y && list[n].t != IN_CLOSE) {
			list[n].from.x = from.x;
			list[n].from.y = from.y;
			list[n].f = f;
			list[n].t = IN_CLOSE;
			break;
		}
	}
}

void survey_reroute (ESContext *esContext, float x1, float y1, float x2, float y2, float alt, int nfzone) {
	Point2D active;
	Point2D mypoly[PMAX];
	Point2D start;
	Point2D stop;
	float active_dist = 0;
	int num = 0;
	int n = 0;
	start.x = x1;
	start.y = y1;
	stop.x = x2;
	stop.y = y2;
	int polypoints = 0;
	for (num = 1; num < MAX_POLYPOINTS; num++) {
		if (PolyPointsNoFly[num].num == nfzone && PolyPointsNoFly[num].p_lat != 0.0) {
			float pmark_x = long2x(PolyPointsNoFly[num].p_long, lon, zoom);
			float pmark_y = lat2y(PolyPointsNoFly[num].p_lat, lat, zoom);
			float px2 = (float)(pmark_x) / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
			float py2 = (float)(pmark_y) / (float)esContext->height * 2.0 - 1.0;
			mypoly[polypoints].x = px2;
			mypoly[polypoints].y = py2;
			mypoly[polypoints].type = 0;
			if (survey_check_intersect_nofly2point(esContext, nfzone, x1, y1, px2, py2) == 0) {
				mypoly[polypoints].type |= 1;
				draw_circleFilled_f3(esContext, px2, py2, 0.0, 0.02, 255, 0, 0, 127);
			}
			if (survey_check_intersect_nofly2point(esContext, nfzone, x2, y2, px2, py2) == 0) {
				mypoly[polypoints].type |= 2;
				draw_circleFilled_f3(esContext, px2, py2, 0.0, 0.015, 0, 255, 0, 127);
			}
			polypoints++;
		}
	}
	for (n = 0; n < 100; n++) {
		list[n].p.x = -1;
		list[n].p.y = -1;
		list[n].from.x = -1;
		list[n].from.y = -1;
		list[n].f = -1;
		list[n].t = UNSET;
	}
	olist_add(start, start, 0);
	olist_mv2close(start, start, 0);
	active = start;
	for (n = 0; n < polypoints; n++) {
		if (mypoly[n].type & 1) {
			olist_add(mypoly[n], start, dist(mypoly[n], stop));
		}
	}
	while (1) {
		int min_n = -1;
		float min_dist = 9999;
		for (n = 0; n < 100; n++) {
			if (list[n].t == IN_OPEN) {
				float ndist = dist(active, list[n].p) + dist(list[n].p, stop);
				if (min_dist > ndist) {
					min_dist = ndist;
					min_n = n;
				}
			}
		}
		if (min_n != -1) {
			active_dist += min_dist;
			olist_mv2close(list[min_n].p, active, active_dist);
			active = list[min_n].p;
			for (n = 0; n < polypoints; n++) {
				if (active.x == mypoly[n].x && active.y == mypoly[n].y) {
					if (n > 0) {
						olist_add(mypoly[n - 1], active, dist(active, mypoly[n - 1]) + dist(mypoly[n - 1], stop));
					} else {
						olist_add(mypoly[polypoints - 1], active, dist(active, mypoly[polypoints - 1]) + dist(mypoly[polypoints - 1], stop));
					}
					if (n < polypoints - 1) {
						olist_add(mypoly[n + 1], active, dist(active, mypoly[n + 1]) + dist(mypoly[n + 1], stop));
					} else {
						olist_add(mypoly[0], active, dist(active, mypoly[0]) + dist(mypoly[0], stop));
					}
					if (mypoly[n].type & 2) {
						olist_add(stop, active, dist(active, stop));
					}
				}
			}
		} else {
			break;
		}
	}
	active = stop;
	while (1) {
		int flag = 0;
		for (n = 0; n < 100; n++) {
			if (active.x == list[n].p.x && active.y == list[n].p.y) {

				draw_line_f3(esContext, list[n].p.x, list[n].p.y, 0.0, list[n].from.x, list[n].from.y, 0.0, 255, 255, 255, 255);

				active = list[n].from;
				if (list[n].from.x == start.x && list[n].from.y == start.y) {
				} else {
					flag = 1;
				}
				break;
			}
		}
		if (flag == 0) {
			break;
		}
	}
}

int point_in_poly (float testx, float testy) {
	int result = 0;
	int num = 0;
	float pmark_x = 0.0;
	float pmark_y = 0.0;
	float last_x = 0.0;
	float last_y = 0.0;
	for (num = 1; num < MAX_POLYPOINTS; num++) {
		if (PolyPoints[num].p_lat != 0.0) {
			pmark_x = long2x(PolyPoints[num].p_long, lon, zoom);
			pmark_y = lat2y(PolyPoints[num].p_lat, lat, zoom);
			last_x = pmark_x;
			last_y = pmark_y;
		}
	}
	for (num = 1; num < MAX_POLYPOINTS; num++) {
		if (PolyPoints[num].p_lat != 0.0) {
			pmark_x = long2x(PolyPoints[num].p_long, lon, zoom);
			pmark_y = lat2y(PolyPoints[num].p_lat, lat, zoom);
			float x1 = last_x;
			float y1 = last_y;
			float x2 = pmark_x;
			float y2 = pmark_y;
			if (y2 == testy) {
				if ((x2 == testx) || (y1 == testy && ((x2 > testx) == (x1 < testx)))) {
//					fprintf(stderr, "Point on line\n");
					return 1;
				}
			}
			if ((y1 < testy) != (y2 < testy)) {
				if (x1 >= testx) {
					if (x2 > testx) {
						result = 1 - result;
					} else {
						float d = (float)(x1 - testx) * (y2 - testy) - (float)(x2 - testx) * (y1 - testy);
						if (!d) {
							return 1;
						}
						if ((d > 0) == (y2 > y1)) {
							result = 1 - result;
						}
					}
				} else {
					if (x2 > testx) {
						float d = (float)(x1 - testx) * (y2 - testy) - (float)(x2 - testx) * (y1 - testy);
						if (!d) {
							return 1;
						}
						if ((d > 0) == (y2 > y1)) {
							result = 1 - result;
						}
					}
				}
			}
		}
		last_x = pmark_x;
		last_y = pmark_y;
	}
	return result;
}

int point_in_polynf (float testx, float testy) {
	int result = 0;
	int num = 0;
	float pmark_x = 0.0;
	float pmark_y = 0.0;
	float last_x = 0.0;
	float last_y = 0.0;
	int nfn = 0;
	for (nfn = 0; nfn < 255; nfn++) {
		for (num = 1; num < MAX_POLYPOINTS; num++) {
			if (PolyPointsNoFly[num].num == nfn && PolyPointsNoFly[num].p_lat != 0.0) {
				pmark_x = long2x(PolyPointsNoFly[num].p_long, lon, zoom);
				pmark_y = lat2y(PolyPointsNoFly[num].p_lat, lat, zoom);
				last_x = pmark_x;
				last_y = pmark_y;
			}
		}
		for (num = 1; num < MAX_POLYPOINTS; num++) {
			if (PolyPointsNoFly[num].num == nfn && PolyPointsNoFly[num].p_lat != 0.0) {
				pmark_x = long2x(PolyPointsNoFly[num].p_long, lon, zoom);
				pmark_y = lat2y(PolyPointsNoFly[num].p_lat, lat, zoom);
				float x1 = last_x;
				float y1 = last_y;
				float x2 = pmark_x;
				float y2 = pmark_y;
				if (y2 == testy) {
					if ((x2 == testx) || (y1 == testy && ((x2 > testx) == (x1 < testx)))) {
//						fprintf(stderr, "Point on line\n");
						return 1;
					}
				}
				if ((y1 < testy) != (y2 < testy)) {
					if (x1 >= testx) {
						if (x2 > testx) {
							result = 1 - result;
						} else {
							float d = (float)(x1 - testx) * (y2 - testy) - (float)(x2 - testx) * (y1 - testy);
							if (!d) {
								return 1;
							}
							if ((d > 0) == (y2 > y1)) {
								result = 1 - result;
							}
						}
					} else {
						if (x2 > testx) {
							float d = (float)(x1 - testx) * (y2 - testy) - (float)(x2 - testx) * (y1 - testy);
							if (!d) {
								return 1;
							}
							if ((d > 0) == (y2 > y1)) {
								result = 1 - result;
							}
						}
					}
				}
			}
			last_x = pmark_x;
			last_y = pmark_y;
		}
	}
	return result;
}

void survey_parsePolypoint (xmlDocPtr doc, xmlNodePtr cur, int n) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"lat"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				PolyPoints[n].p_lat = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"lon"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				PolyPoints[n].p_long = atof((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

void survey_parsePolypointNoFly (xmlDocPtr doc, xmlNodePtr cur, int n) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"lat"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				PolyPointsNoFly[n].p_lat = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"lon"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				PolyPointsNoFly[n].p_long = atof((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

void survey_parseDoc (char *docname) {
	int n = 0;
	int nnf = 0;
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
		SDL_Log("Document is Empty!!!\n");
		return;
	}
	for (n = 0; n < MAX_POLYPOINTS; n++) {
		PolyPoints[n].p_lat = 0.0;
		PolyPoints[n].p_long = 0.0;
	}
	n = 1;
	nnf = 1;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(SurveySetup.name, (char *)key, 1000);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"interval"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.interval = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"pos"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.pos = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"type"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.type = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"num"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.num = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"triggermode"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.triggermode = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"options"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.options = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"mode"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.mode = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"alt_abs"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.alt_abs = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"angle"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.angle = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"grid_x"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.grid_x = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"grid_y"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.grid_y = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"film_width"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.film_width = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"film_height"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.film_height = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"sensor_mult"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.sensor_mult = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"lense"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.lense = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"overlap"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.overlap = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"alt"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.alt = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"angle"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				SurveySetup.angle = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"polypoint"))) {
			survey_parsePolypoint(doc, cur, n);
			n++;
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"polypoint_nf"))) {
			survey_parsePolypoint(doc, cur, n);
			nnf++;
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}

uint8_t survey_load_xml (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	survey_parseDoc(name);
	reset_buttons();
	return 0;
}

uint8_t survey_load (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	reset_buttons();
	char tmp_str[128];
	sprintf(tmp_str, "%s/survey", get_datadirectory());
	filesystem_set_dir(tmp_str);
	filesystem_set_callback(survey_load_xml);
	filesystem_reset_filter();
	filesystem_add_filter(".xml\0");
	filesystem_set_mode(setup.view_mode);
	return 0;
}

uint8_t survey_save_xml (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	FILE *fr;
	int n = 0;
	char tmp_str[128];
	reset_buttons();
	sprintf(tmp_str, "mkdir -p %s/survey", get_datadirectory());
	system(tmp_str);
	sprintf(tmp_str, "%s/survey/%s", get_datadirectory(), name);
	fr = fopen(tmp_str, "wb");
	if (fr != 0) {
		fprintf(fr, "<survey>\n");
		fprintf(fr, " <name>%s</name>\n", SurveySetup.name);
		fprintf(fr, " <interval>%i</interval>\n", SurveySetup.interval);
		fprintf(fr, " <pos>%i</pos>\n", SurveySetup.pos);
		fprintf(fr, " <type>%i</type>\n", SurveySetup.type);
		fprintf(fr, " <num>%i</num>\n", SurveySetup.num);
		fprintf(fr, " <triggermode>%i</triggermode>\n", SurveySetup.triggermode);
		fprintf(fr, " <options>%i</options>\n", SurveySetup.options);
		fprintf(fr, " <mode>%i</mode>\n", SurveySetup.mode);
		fprintf(fr, " <angle>%f</angle>\n", SurveySetup.angle);
		fprintf(fr, " <grid_x>%f</grid_x>\n", SurveySetup.grid_x);
		fprintf(fr, " <grid_y>%f</grid_y>\n", SurveySetup.grid_y);
		fprintf(fr, " <film_width>%f</film_width>\n", SurveySetup.film_width);
		fprintf(fr, " <film_height>%f</film_height>\n", SurveySetup.film_height);
		fprintf(fr, " <sensor_mult>%f</sensor_mult>\n", SurveySetup.sensor_mult);
		fprintf(fr, " <lense>%f</lense>\n", SurveySetup.lense);
		fprintf(fr, " <overlap>%f</overlap>\n", SurveySetup.overlap);
		fprintf(fr, " <alt>%f</alt>\n", SurveySetup.alt);
		fprintf(fr, " <alt_abs>%i</alt_abs>\n", SurveySetup.alt_abs);
		for (n = 0; n < MAX_POLYPOINTS; n++) {
			if (PolyPoints[n].p_lat != 0.0) {
				fprintf(fr, " <polypoint>\n");
				fprintf(fr, "  <lat>%0.8f</lat>\n", PolyPoints[n].p_lat);
				fprintf(fr, "  <lon>%0.8f</lon>\n", PolyPoints[n].p_long);
				fprintf(fr, " </polypoint>\n");
			}
		}
		for (n = 0; n < MAX_POLYPOINTS; n++) {
			if (PolyPointsNoFly[n].p_lat != 0.0) {
				fprintf(fr, " <polypoint_nf>\n");
				fprintf(fr, "  <lat>%0.8f</lat>\n", PolyPointsNoFly[n].p_lat);
				fprintf(fr, "  <lon>%0.8f</lon>\n", PolyPointsNoFly[n].p_long);
				fprintf(fr, " </polypoint_nf>\n");
			}
		}
		fprintf(fr, "</survey>\n");
		fclose(fr);
	}
	return 0;
}

uint8_t survey_save (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	char tmp_str[200];
	reset_buttons();
	keyboard_set_callback(survey_save_xml);
	if (strstr(SurveySetup.name, ".xml\0") > 0) {
		strncpy(tmp_str, SurveySetup.name, 199);
	} else {
		sprintf(tmp_str, "%s.xml", SurveySetup.name);
	}
	keyboard_set_text(tmp_str);
	keyboard_set_mode(setup.view_mode);
	return 0;
}

uint8_t survey_name_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	strncpy(SurveySetup.name, name, 1000);
	return 0;
}

uint8_t survey_name_edit (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	keyboard_set_callback(survey_name_set);
	keyboard_set_text(SurveySetup.name);
	keyboard_set_mode(setup.view_mode);
	return 0;
}

void draw_fov (ESContext *esContext, float p_lat, float p_long, float p_alt, float angle) {
#ifdef SDLGL
	float mpp = get_m_per_pixel(lat, zoom);
	float pos_alt = get_altitude(p_lat, p_long);
	float dist = p_alt - pos_alt; // Abstand in Metern
	float h = 0.0;
	float w = 0.0;
	calc_fov(SurveySetup.film_width, SurveySetup.film_height, SurveySetup.sensor_mult, SurveySetup.lense, dist, &w, &h);
	int mp_x = long2x(p_long, lon, zoom);
	int mp_y = lat2y(p_lat, lat, zoom);
	float mx = ((float)mp_x) / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float my = ((float)mp_y) / (float)esContext->height * 2.0 - 1.0;
	float mx1 = ((float)(w / mpp) / 2.0) / (float)esContext->width * 2.0 * aspect;
	float my1 = ((float)(h / mpp) / 2.0) / (float)esContext->height * 2.0;
	float z = pos_alt / alt_zoom;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(mx, -my, 0.0);
	glRotatef(-angle, 0.0, 0.0, 1.0);
	draw_box_f3(esContext, -mx1, -my1, z, mx1, my1, z, 255, 0, 0, 64);
	glPopMatrix();
#endif
}

uint8_t survey_export_kml (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	int n = 0;
	int pmark_x = long2x(PolyPoints[1].p_long, lon, zoom);
	int pmark_y = lat2y(PolyPoints[1].p_lat, lat, zoom);
	float min_x = pmark_x;
	float min_y = pmark_y;
	float max_x = pmark_x;
	float max_y = pmark_y;
	float pos_alt_max = -999999.0;
	char filename[1024];
	char ge_command[1024];
	sprintf(filename, "%s/survey/%s.kml", get_datadirectory(), SurveySetup.name);
	FILE *kmlout = fopen(filename, "w");
	fprintf(kmlout, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(kmlout, "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
	fprintf(kmlout, "  <Document>\n");
	fprintf(kmlout, "    <name>Mission: %s</name>\n", SurveySetup.name);
	fprintf(kmlout, "    <description>MultiGCS - Survey-Mission\n");
	if (SurveySetup.mode == 1) {
		fprintf(kmlout, "    grid_x: %0.0f m\n", SurveySetup.grid_x);
		fprintf(kmlout, "    grid_y: %0.0f m\n", SurveySetup.grid_y);
		if (SurveySetup.alt_abs == 1) {
			fprintf(kmlout, "    Alt: %0.2fm ABS\n", SurveySetup.alt);
		} else {
			fprintf(kmlout, "    Alt: %0.2fm REL\n", SurveySetup.alt);
		}
	} else {
		fprintf(kmlout, "    focal length: %0.0f mm\n", SurveySetup.lense);
		fprintf(kmlout, "    Film-Width: %0.0f mm\n", SurveySetup.film_width);
		fprintf(kmlout, "    Film-Height: %0.0f mm\n", SurveySetup.film_height);
		fprintf(kmlout, "    Sensor-Mult.: %0.2fx\n", SurveySetup.sensor_mult);
		fprintf(kmlout, "    Overlap: %0.2f\n", SurveySetup.overlap);
		if (SurveySetup.alt_abs == 1) {
			fprintf(kmlout, "    Alt: %0.2fm ABS\n", SurveySetup.alt);
		} else {
			fprintf(kmlout, "    Alt: %0.2fm REL\n", SurveySetup.alt);
		}
	}
	fprintf(kmlout, "    Angle: %0.1f\n", SurveySetup.angle);
	fprintf(kmlout, "    </description>\n");
	fprintf(kmlout, "    <Style id=\"yellowLineGreenPoly\">\n");
	fprintf(kmlout, "      <LineStyle>\n");
	fprintf(kmlout, "        <color>7f00ffff</color>\n");
	fprintf(kmlout, "        <width>4</width>\n");
	fprintf(kmlout, "      </LineStyle>\n");
	fprintf(kmlout, "      <PolyStyle>\n");
	fprintf(kmlout, "        <color>7f00ff00</color>\n");
	fprintf(kmlout, "      </PolyStyle>\n");
	fprintf(kmlout, "    </Style>\n");
	fprintf(kmlout, "    <Style id=\"redLineGreenPoly\">\n");
	fprintf(kmlout, "      <LineStyle>\n");
	fprintf(kmlout, "        <color>7f0000ff</color>\n");
	fprintf(kmlout, "        <width>2</width>\n");
	fprintf(kmlout, "      </LineStyle>\n");
	fprintf(kmlout, "      <PolyStyle>\n");
	fprintf(kmlout, "        <color>7f00ff00</color>\n");
	fprintf(kmlout, "      </PolyStyle>\n");
	fprintf(kmlout, "    </Style>\n");
	fprintf(kmlout, "    <Placemark>\n");
	fprintf(kmlout, "      <name>Outline</name>\n");
	fprintf(kmlout, "    <ExtendedData>\n");
	if (SurveySetup.mode == 1) {
		fprintf(kmlout, "    <Data name=\"grid_x\"><value>%0.0f m</value></Data>\n", SurveySetup.grid_x);
		fprintf(kmlout, "    <Data name=\"grid_y\"><value>%0.0f m</value></Data>\n", SurveySetup.grid_y);
		if (SurveySetup.alt_abs == 1) {
			fprintf(kmlout, "    <Data name=\"Alt\"><value>%0.2fm ABS</value></Data>\n", SurveySetup.alt);
		} else {
			fprintf(kmlout, "    <Data name=\"Alt\"><value>%0.2fm REL</value></Data>\n", SurveySetup.alt);
		}
	} else {
		fprintf(kmlout, "    <Data name=\"focal length\"><value>%0.0f mm</value></Data>\n", SurveySetup.lense);
		fprintf(kmlout, "    <Data name=\"Film-Width\"><value>%0.0f mm</value></Data>\n", SurveySetup.film_width);
		fprintf(kmlout, "    <Data name=\"Film-Height\"><value>%0.0f mm</value></Data>\n", SurveySetup.film_height);
		fprintf(kmlout, "    <Data name=\"Sensor-Mult.\"><value>%0.2fx</value></Data>\n", SurveySetup.sensor_mult);
		fprintf(kmlout, "    <Data name=\"Overlap\"><value>%0.2f</value></Data>\n", SurveySetup.overlap);
		if (SurveySetup.alt_abs == 1) {
			fprintf(kmlout, "    <Data name=\"Alt\"><value>%0.2fm ABS</value></Data>\n", SurveySetup.alt);
		} else {
			fprintf(kmlout, "    <Data name=\"Alt\"><value>%0.2fm REL</value></Data>\n", SurveySetup.alt);
		}
	}
	fprintf(kmlout, "    <Data name=\"Angle\"><value>%0.1f</value></Data>\n", SurveySetup.angle);
	fprintf(kmlout, "    </ExtendedData>\n");
	fprintf(kmlout, "      <styleUrl>#redLineGreenPoly</styleUrl>\n");
	fprintf(kmlout, "      <LineString>\n");
	fprintf(kmlout, "        <extrude>0</extrude>\n");
	fprintf(kmlout, "        <tessellate>1</tessellate>\n");
	fprintf(kmlout, "        <coordinates>\n");
	for (n = 1; n < MAX_WAYPOINTS; n++) {
		if (PolyPoints[n].p_lat != 0.0) {
			pmark_x = long2x(PolyPoints[n].p_long, lon, zoom);
			pmark_y = lat2y(PolyPoints[n].p_lat, lat, zoom);
			if (min_x > pmark_x) {
				min_x = pmark_x;
			}
			if (min_y > pmark_y) {
				min_y = pmark_y;
			}
			if (max_x < pmark_x) {
				max_x = pmark_x;
			}
			if (max_y < pmark_y) {
				max_y = pmark_y;
			}
			float pos_alt = get_altitude(PolyPoints[n].p_lat, PolyPoints[n].p_long);
			if (pos_alt_max < pos_alt) {
				pos_alt_max = pos_alt;
			}
			fprintf(kmlout, "          %f,%f\n", PolyPoints[n].p_long, PolyPoints[n].p_lat);
		}
	}
	fprintf(kmlout, "          %f,%f\n", PolyPoints[1].p_long, PolyPoints[1].p_lat);
	fprintf(kmlout, "        </coordinates>\n");
	fprintf(kmlout, "      </LineString>\n");
	fprintf(kmlout, "    </Placemark>\n");

	// drawing Grid
	float h = 0.0;
	float w = 0.0;
	float mpp = get_m_per_pixel(lat, zoom);
	float dist = 0.0;
	float grid_x = 0.0;
	float grid_y = 0.0;
	if (SurveySetup.alt_abs == 1) {
		dist = SurveySetup.alt - pos_alt_max;
	} else {
		dist = SurveySetup.alt;
	}
	if (dist < 1.0) {
		dist = 1.0;
	}
	if (SurveySetup.mode == 1) {
		grid_x = SurveySetup.grid_x / mpp;
		grid_y = SurveySetup.grid_y / mpp;
	} else {
		calc_fov(SurveySetup.film_width, SurveySetup.film_height, SurveySetup.sensor_mult, SurveySetup.lense, dist, &w, &h);
		grid_x = w / mpp / SurveySetup.overlap;
		grid_y = h / mpp / SurveySetup.overlap;
	}
	fprintf(kmlout, "    <Placemark>\n");
	fprintf(kmlout, "      <name>Route</name>\n");
	fprintf(kmlout, "    <ExtendedData>\n");
	if (SurveySetup.mode == 1) {
		fprintf(kmlout, "    <Data name=\"grid_x\"><value>%0.0f m</value></Data>\n", SurveySetup.grid_x);
		fprintf(kmlout, "    <Data name=\"grid_y\"><value>%0.0f m</value></Data>\n", SurveySetup.grid_y);
		if (SurveySetup.alt_abs == 1) {
			fprintf(kmlout, "    <Data name=\"Alt\"><value>%0.2fm ABS</value></Data>\n", SurveySetup.alt);
		} else {
			fprintf(kmlout, "    <Data name=\"Alt\"><value>%0.2fm REL</value></Data>\n", SurveySetup.alt);
		}
	} else {
		fprintf(kmlout, "    <Data name=\"focal length\"><value>%0.0f mm</value></Data>\n", SurveySetup.lense);
		fprintf(kmlout, "    <Data name=\"Film-Width\"><value>%0.0f mm</value></Data>\n", SurveySetup.film_width);
		fprintf(kmlout, "    <Data name=\"Film-Height\"><value>%0.0f mm</value></Data>\n", SurveySetup.film_height);
		fprintf(kmlout, "    <Data name=\"Sensor-Mult.\"><value>%0.2fx</value></Data>\n", SurveySetup.sensor_mult);
		fprintf(kmlout, "    <Data name=\"Overlap\"><value>%0.2f</value></Data>\n", SurveySetup.overlap);
		if (SurveySetup.alt_abs == 1) {
			fprintf(kmlout, "    <Data name=\"Alt\"><value>%0.2fm ABS</value></Data>\n", SurveySetup.alt);
		} else {
			fprintf(kmlout, "    <Data name=\"Alt\"><value>%0.2fm REL</value></Data>\n", SurveySetup.alt);
		}
	}
	fprintf(kmlout, "    <Data name=\"Angle\"><value>%0.1f</value></Data>\n", SurveySetup.angle);
	fprintf(kmlout, "    </ExtendedData>\n");
	fprintf(kmlout, "      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
	fprintf(kmlout, "      <LineString>\n");
	fprintf(kmlout, "        <extrude>1</extrude>\n");
	fprintf(kmlout, "        <tessellate>1</tessellate>\n");
	fprintf(kmlout, "        <altitudeMode>absolute</altitudeMode>\n");
	fprintf(kmlout, "        <coordinates>\n");
	float n_x = 0.0;
	float n_y = 0.0;
	float center_x = min_x + (max_x - min_x) / 2.0;
	float center_y = min_y + (max_y - min_y) / 2.0;
	float max_w = max_y - min_y;
	if (max_w < max_x - min_x) {
		max_w = max_x - min_x;
	}
	float ltx = center_x + cos((45.0 + 180.0 + SurveySetup.angle) * DEG2RAD) * max_w;
	float lty = center_y + sin((45.0 + 180.0 + SurveySetup.angle) * DEG2RAD) * max_w;
	for (n_y = 0.0; n_y <= max_w * 1.5; n_y += grid_y) {
		float lnx = ltx + cos((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
		float lny = lty + sin((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
		for (n_x = 0; n_x < max_w * 1.5; n_x += grid_x) {
			float nx = lnx + cos((SurveySetup.angle) * DEG2RAD) * n_x;
			float ny = lny + sin((SurveySetup.angle) * DEG2RAD) * n_x;
			if (point_in_poly(nx, ny) == 0) {
				continue;
			}
			if (point_in_polynf(nx, ny) != 0) {
				continue;
			}
			float np_long = x2long(nx, lon, mapdata->zoom);
			float np_lat = y2lat(ny, lat, mapdata->zoom);
			float pos_alt = get_altitude(np_lat, np_long);
			float alt = SurveySetup.alt + pos_alt;
			if (SurveySetup.alt_abs == 1) {
				if (SurveySetup.alt < pos_alt + 1.0) {
					SurveySetup.alt = pos_alt + 1.0;
				}
				alt = SurveySetup.alt;
			}
			fprintf(kmlout, "          %f,%f,%f\n", np_long, np_lat, alt);
		}
		n_y += grid_y;
		lnx = ltx + cos((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
		lny = lty + sin((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
		for (n_x = n_x - grid_x; n_x > -grid_x; n_x -= grid_x) {
			float nx = lnx + cos((SurveySetup.angle) * DEG2RAD) * n_x;
			float ny = lny + sin((SurveySetup.angle) * DEG2RAD) * n_x;
			if (point_in_poly(nx, ny) == 0) {
				continue;
			}
			if (point_in_polynf(nx, ny) != 0) {
				continue;
			}
			float np_long = x2long(nx, lon, mapdata->zoom);
			float np_lat = y2lat(ny, lat, mapdata->zoom);
			float pos_alt = get_altitude(np_lat, np_long);
			float alt = SurveySetup.alt + pos_alt;
			if (SurveySetup.alt_abs == 1) {
				if (SurveySetup.alt < pos_alt + 1.0) {
					SurveySetup.alt = pos_alt + 1.0;
				}
				alt = SurveySetup.alt;
			}
			fprintf(kmlout, "          %f,%f,%f\n", np_long, np_lat, alt);
		}
	}
	fprintf(kmlout, "        </coordinates>\n");
	fprintf(kmlout, "      </LineString>\n");
	fprintf(kmlout, "    </Placemark>\n");
	int mark_n = 0;
	for (n_y = 0.0; n_y <= max_w * 1.5; n_y += grid_y) {
		float lnx = ltx + cos((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
		float lny = lty + sin((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
		for (n_x = 0; n_x < max_w * 1.5; n_x += grid_x) {
			float nx = lnx + cos((SurveySetup.angle) * DEG2RAD) * n_x;
			float ny = lny + sin((SurveySetup.angle) * DEG2RAD) * n_x;
			if (point_in_poly(nx, ny) == 0) {
				continue;
			}
			if (point_in_polynf(nx, ny) != 0) {
				continue;
			}
			float np_long = x2long(nx, lon, mapdata->zoom);
			float np_lat = y2lat(ny, lat, mapdata->zoom);
			float pos_alt = get_altitude(np_lat, np_long);
			float alt = SurveySetup.alt + pos_alt;
			if (SurveySetup.alt_abs == 1) {
				if (SurveySetup.alt < pos_alt + 1.0) {
					SurveySetup.alt = pos_alt + 1.0;
				}
				alt = SurveySetup.alt;
			}
			fprintf(kmlout, "    <Placemark>\n");
			fprintf(kmlout, "      <name>WP: %i</name>\n", mark_n);
			fprintf(kmlout, "      <description>WP: %i, ALT: %fm</description>\n", mark_n++, alt);
			fprintf(kmlout, "      <Point>\n");
			fprintf(kmlout, "        <coordinates>%f,%f,%f</coordinates>\n", np_long, np_lat, alt);
			fprintf(kmlout, "      </Point>\n");
			fprintf(kmlout, "    </Placemark>\n");
		}
		n_y += grid_y;
		lnx = ltx + cos((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
		lny = lty + sin((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
		for (n_x = n_x - grid_x; n_x > -grid_x; n_x -= grid_x) {
			float nx = lnx + cos((SurveySetup.angle) * DEG2RAD) * n_x;
			float ny = lny + sin((SurveySetup.angle) * DEG2RAD) * n_x;
			if (point_in_poly(nx, ny) == 0) {
				continue;
			}
			if (point_in_polynf(nx, ny) != 0) {
				continue;
			}
			float np_long = x2long(nx, lon, mapdata->zoom);
			float np_lat = y2lat(ny, lat, mapdata->zoom);
			float pos_alt = get_altitude(np_lat, np_long);
			float alt = SurveySetup.alt + pos_alt;
			if (SurveySetup.alt_abs == 1) {
				if (SurveySetup.alt < pos_alt + 1.0) {
					SurveySetup.alt = pos_alt + 1.0;
				}
				alt = SurveySetup.alt;
			}
			fprintf(kmlout, "    <Placemark>\n");
			fprintf(kmlout, "      <name>WP: %i</name>\n", mark_n);
			fprintf(kmlout, "      <description>WP: %i, ALT: %fm</description>\n", mark_n++, alt);
			fprintf(kmlout, "      <Point>\n");
			fprintf(kmlout, "        <coordinates>%f,%f,%f</coordinates>\n", np_long, np_lat, alt);
			fprintf(kmlout, "      </Point>\n");
			fprintf(kmlout, "    </Placemark>\n");
		}
	}
	fprintf(kmlout, "  </Document>\n");
	fprintf(kmlout, "</kml>\n");
	fclose(kmlout);
	sprintf(ge_command, "googleearth \"%s\" &", filename);
	system(ge_command);
	return 0;
}

uint8_t survey_set (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (strncmp(name, "cam_lense_", 10) == 0) {
		SurveySetup.lense = atof(name + 10);
	} else if (strncmp(name, "SurveySetup.options", 19) == 0) {
		SurveySetup.options = (int)data;
	} else if (strcmp(name, "SurveySetup.type") == 0) {
		SurveySetup.type++;
		if (SurveySetup.type > 2) {
			SurveySetup.type = 0;
		}
	} else if (strcmp(name, "SurveySetup.pos") == 0) {
		if (button == 4 && SurveySetup.pos < 2000) {
			SurveySetup.pos += 10.0;
		} else if (button == 5 && SurveySetup.pos > 1000) {
			SurveySetup.pos -= 10.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_UINT16, &SurveySetup.pos, 1.0, 10000.0);
		}
	} else if (strcmp(name, "SurveySetup.num") == 0) {
		if (button == 4 && SurveySetup.num < 10) {
			SurveySetup.num += 1.0;
		} else if (button == 5 && SurveySetup.num > 1) {
			SurveySetup.num -= 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_UINT8, &SurveySetup.num, 1.0, 10000.0);
		}
	} else if (strcmp(name, "SurveySetup.interval") == 0) {
		if (button == 4) {
			SurveySetup.interval += 1.0;
		} else if (button == 5 && SurveySetup.interval > 1) {
			SurveySetup.interval -= 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_UINT16, &SurveySetup.interval, 1.0, 10000.0);
		}
	} else if (strcmp(name, "SurveySetup.triggermode") == 0) {
		SurveySetup.triggermode++;
		if (SurveySetup.triggermode > 2) {
			SurveySetup.triggermode = 0;
		}
	} else if (strcmp(name, "cam_del") == 0) {
		int n = 0;
		for (n = 1; n < MAX_POLYPOINTS; n++) {
			PolyPoints[n].p_lat = 0.0;
			PolyPoints[n].p_long = 0.0;
		}
	} else if (strcmp(name, "cam_delnf") == 0) {
		int n = 0;
		for (n = 1; n < MAX_POLYPOINTS; n++) {
			PolyPointsNoFly[n].p_lat = 0.0;
			PolyPointsNoFly[n].p_long = 0.0;
		}
	} else if (strcmp(name, "SurveySetup.mode") == 0) {
		SurveySetup.mode = 1 - SurveySetup.mode;
	} else if (strcmp(name, "SurveySetup.angle") == 0) {
		if (button == 4) {
			if (SurveySetup.angle < 359.0) {
				SurveySetup.angle += 1.0;
			} else {
				SurveySetup.angle = 0.0;
			}
		} else if (button == 5) {
			if (SurveySetup.angle > 0.0) {
				SurveySetup.angle -= 1.0;
			} else {
				SurveySetup.angle = 359.0;
			}
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &SurveySetup.angle, 0.0, 360.0);
		}
	} else if (strcmp(name, "SurveySetup.grid_x") == 0) {
		if (button == 4) {
			SurveySetup.grid_x += 1.0;
		} else if (button == 5) {
			SurveySetup.grid_x -= 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &SurveySetup.grid_x, 1.0, 10000.0);
		}
		if (SurveySetup.grid_x < 1.0) {
			SurveySetup.grid_x = 1.0;
		}
	} else if (strcmp(name, "SurveySetup.grid_y") == 0) {
		if (button == 4) {
			SurveySetup.grid_y += 1.0;
		} else if (button == 5) {
			SurveySetup.grid_y -= 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &SurveySetup.grid_y, 1.0, 10000.0);
		}
		if (SurveySetup.grid_y < 1.0) {
			SurveySetup.grid_y = 1.0;
		}
	} else if (strcmp(name, "SurveySetup.lense") == 0) {
		if (button == 4) {
			SurveySetup.lense += 1.0;
		} else if (button == 5) {
			SurveySetup.lense -= 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &SurveySetup.lense, 1.0, 10000.0);
		}
	} else if (strcmp(name, "SurveySetup.film_width") == 0) {
		if (button == 4) {
			SurveySetup.film_width += 1.0;
		} else if (button == 5) {
			SurveySetup.film_width -= 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &SurveySetup.film_width, 1.0, 10000.0);
		}
	} else if (strcmp(name, "SurveySetup.film_height") == 0) {
		if (button == 4) {
			SurveySetup.film_height += 1.0;
		} else if (button == 5) {
			SurveySetup.film_height -= 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &SurveySetup.film_height, 1.0, 10000.0);
		}
	} else if (strcmp(name, "SurveySetup.sensor_mult") == 0) {
		if (button == 4) {
			SurveySetup.sensor_mult += 0.01;
		} else if (button == 5) {
			SurveySetup.sensor_mult -= 0.01;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &SurveySetup.sensor_mult, 1.0, 10000.0);
		}
	} else if (strcmp(name, "SurveySetup.overlap") == 0) {
		if (button == 4) {
			SurveySetup.overlap += 0.01;
		} else if (button == 5) {
			SurveySetup.overlap -= 0.01;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &SurveySetup.overlap, 1.0, 10000.0);
		}
	} else if (strcmp(name, "SurveySetup.alt") == 0) {
		if (button == 4) {
			SurveySetup.alt += 1.0;
		} else if (button == 5) {
			SurveySetup.alt -= 1.0;
		} else {
			edit_number(setup.view_mode, NUMBER_TYPE_FLOAT, &SurveySetup.alt, 1.0, 10000.0);
		}
		if (SurveySetup.alt_abs == 0) {
			if (SurveySetup.alt < 1.0) {
				SurveySetup.alt = 1.0;
			}
		}
	} else if (strcmp(name, "SurveySetup.alt_abs") == 0) {
		float pos_alt_max = -999999.0;
		int n = 0;
		for (n = 1; n < MAX_WAYPOINTS; n++) {
			if (PolyPoints[n].p_lat != 0.0) {
				float pos_alt = get_altitude(PolyPoints[n].p_lat, PolyPoints[n].p_long);
				if (pos_alt_max < pos_alt) {
					pos_alt_max = pos_alt;
				}
			}
		}
		SurveySetup.alt_abs = 1 - SurveySetup.alt_abs;
		if (SurveySetup.alt_abs == 1) {
			SurveySetup.alt += pos_alt_max;
		} else {
			SurveySetup.alt -= pos_alt_max;
		}
	} else if (strncmp(name, "cam_sensor_", 11) == 0) {
		SurveySetup.film_width = 36.0;
		SurveySetup.film_height = 24.0;
		SurveySetup.sensor_mult = atof(name + 11);
	} else if (strcmp(name, "cam_setup") == 0) {
		map_show_survey_setup = 1 - map_show_survey_setup;
		map_show_poly = 1;
	} else if (strcmp(name, "survey_setup_done") == 0) {
		map_show_survey_setup = 1 - map_show_survey_setup;
	} else if (strcmp(name, "survey_setup_write") == 0) {
		char tmp_str[1024];
		int n = 0;
		FILE *fr;
		sprintf(tmp_str, "%s/survey/%s.pln", get_datadirectory(), SurveySetup.name);
		fr = fopen(tmp_str, "wb");
		if (fr != NULL) {
			fprintf(fr, "#name: %s\n", SurveySetup.name);
			fprintf(fr, "#interval: %i\n", SurveySetup.interval);
			fprintf(fr, "#pos: %i\n", SurveySetup.pos);
			fprintf(fr, "#type: %i\n", SurveySetup.type);
			fprintf(fr, "#num: %i\n", SurveySetup.num);
			fprintf(fr, "#triggermode: %i\n", SurveySetup.triggermode);
			fprintf(fr, "#options: %i\n", SurveySetup.options);
			fprintf(fr, "#mode: %i\n", SurveySetup.mode);
			fprintf(fr, "#angle: %f\n", SurveySetup.angle);
			fprintf(fr, "#grid_x: %f\n", SurveySetup.grid_x);
			fprintf(fr, "#grid_y: %f\n", SurveySetup.grid_y);
			fprintf(fr, "#film_width: %f\n", SurveySetup.film_width);
			fprintf(fr, "#film_height: %f\n", SurveySetup.film_height);
			fprintf(fr, "#sensor_mult: %f\n", SurveySetup.sensor_mult);
			fprintf(fr, "#lense: %f\n", SurveySetup.lense);
			fprintf(fr, "#overlap: %f\n", SurveySetup.overlap);
			fprintf(fr, "#alt: %f\n", SurveySetup.alt);
			fprintf(fr, "#alt_abs: %i\n", SurveySetup.alt_abs);
			for (n = 0; n < MAX_POLYPOINTS; n++) {
				if (PolyPoints[n].p_lat != 0.0) {
					fprintf(fr, "#polypoint:%0.8f,%0.8f\n", PolyPoints[n].p_lat, PolyPoints[n].p_long);
				}
			}
		}
		map_show_survey_setup = 1 - map_show_survey_setup;
		// clear Waypoints
		for (n = 1; n < MAX_WAYPOINTS; n++) {
			WayPoints[ModelActive][n].p_lat = 0.0;
		}
		// add Waypoints
		int pmark_x = long2x(PolyPoints[1].p_long, lon, zoom);
		int pmark_y = lat2y(PolyPoints[1].p_lat, lat, zoom);
		float min_x = pmark_x;
		float min_y = pmark_y;
		float max_x = pmark_x;
		float max_y = pmark_y;
		float pos_alt_max = -999999.0;
		// check box
		for (n = 1; n < MAX_POLYPOINTS; n++) {
			if (PolyPoints[n].p_lat != 0.0) {
				pmark_x = long2x(PolyPoints[n].p_long, lon, zoom);
				pmark_y = lat2y(PolyPoints[n].p_lat, lat, zoom);
				if (min_x > pmark_x) {
					min_x = pmark_x;
				}
				if (min_y > pmark_y) {
					min_y = pmark_y;
				}
				if (max_x < pmark_x) {
					max_x = pmark_x;
				}
				if (max_y < pmark_y) {
					max_y = pmark_y;
				}
				float pos_alt = get_altitude(PolyPoints[n].p_lat, PolyPoints[n].p_long);
				if (pos_alt_max < pos_alt) {
					pos_alt_max = pos_alt;
				}
			}
		}
		float h = 0.0;
		float w = 0.0;
		float mpp = get_m_per_pixel(lat, zoom);
		float dist = 0.0;
		float grid_x = 0.0;
		float grid_y = 0.0;
		if (SurveySetup.alt_abs == 1) {
			dist = SurveySetup.alt - pos_alt_max;
		} else {
			dist = SurveySetup.alt;
		}
		if (dist < 1.0) {
			dist = 1.0;
		}
		if (SurveySetup.mode == 1) {
			grid_x = SurveySetup.grid_x / mpp;
			grid_y = SurveySetup.grid_y / mpp;
		} else {
			calc_fov(SurveySetup.film_width, SurveySetup.film_height, SurveySetup.sensor_mult, SurveySetup.lense, dist, &w, &h);
			grid_x = w / mpp / SurveySetup.overlap;
			grid_y = h / mpp / SurveySetup.overlap;
		}
		n = 1;
		if (SurveySetup.triggermode == 2) {
			WayPoints[ModelActive][n].p_lat = 1.0;
			WayPoints[ModelActive][n].p_long = 0.0;
			WayPoints[ModelActive][n].p_alt = 0.0;
			WayPoints[ModelActive][n].frametype = 0;
			sprintf(WayPoints[ModelActive][n].name, "SHUTTER");
			strcpy(WayPoints[ModelActive][n].command, "SHUTTER_INT");
			WayPoints[ModelActive][n].param1 = (float)SurveySetup.interval;
			WayPoints[ModelActive][n].param2 = (float)0;
			WayPoints[ModelActive][n].param3 = (float)0;
			WayPoints[ModelActive][n].param4 = (float)0;
			if (fr != NULL) {
				fprintf(fr, "CMD;SHUTTER_DIST;%i\n", SurveySetup.interval);
			}
			n++;
		}
		float n_x = 0.0;
		float n_y = 0.0;
		float center_x = min_x + (max_x - min_x) / 2.0;
		float center_y = min_y + (max_y - min_y) / 2.0;
		float max_w = max_y - min_y;
		if (max_w < max_x - min_x) {
			max_w = max_x - min_x;
		}
		float ltx = center_x + cos((45.0 + 180.0 + SurveySetup.angle) * DEG2RAD) * max_w;
		float lty = center_y + sin((45.0 + 180.0 + SurveySetup.angle) * DEG2RAD) * max_w;
		for (n_y = 0.0; n_y <= max_w * 1.5; n_y += grid_y) {
			float lnx = ltx + cos((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
			float lny = lty + sin((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
			for (n_x = 0; n_x < max_w * 1.5; n_x += grid_x) {
				float nx = lnx + cos((SurveySetup.angle) * DEG2RAD) * n_x;
				float ny = lny + sin((SurveySetup.angle) * DEG2RAD) * n_x;
				if (SurveySetup.triggermode == 2) {
					float nx1 = lnx + cos((SurveySetup.angle) * DEG2RAD) * (n_x - grid_x);
					float ny1 = lny + sin((SurveySetup.angle) * DEG2RAD) * (n_x - grid_x);
					float nx2 = lnx + cos((SurveySetup.angle) * DEG2RAD) * (n_x + grid_x);
					float ny2 = lny + sin((SurveySetup.angle) * DEG2RAD) * (n_x + grid_x);
					if ((point_in_poly(nx, ny) == 1 && point_in_poly(nx1, ny1) == 0) || (point_in_poly(nx, ny) == 1 && point_in_poly(nx2, ny2) == 0)) {
					} else {
						continue;
					}
				} else {
					if (point_in_poly(nx, ny) == 0) {
						continue;
					}
					if (point_in_polynf(nx, ny) != 0) {
						continue;
					}
				}
				float np_long = x2long(nx, lon, mapdata->zoom);
				float np_lat = y2lat(ny, lat, mapdata->zoom);
				float pos_alt = get_altitude(np_lat, np_long);
				float alt = SurveySetup.alt + pos_alt;
				if (SurveySetup.alt_abs == 1) {
					if (SurveySetup.alt < pos_alt + 1.0) {
						SurveySetup.alt = pos_alt + 1.0;
					}
					alt = SurveySetup.alt;
				}
				WayPoints[ModelActive][n].p_lat = np_lat;
				WayPoints[ModelActive][n].p_long = np_long;
				WayPoints[ModelActive][n].p_alt = alt;
				WayPoints[ModelActive][n].param1 = 0.0;
				WayPoints[ModelActive][n].param2 = 0.0;
				WayPoints[ModelActive][n].param3 = 0.0;
				WayPoints[ModelActive][n].param4 = 0.0;
				WayPoints[ModelActive][n].type = 0;
				WayPoints[ModelActive][n].frametype = 0;
				sprintf(WayPoints[ModelActive][n].name, "WP%i", n);
				strcpy(WayPoints[ModelActive][n].command, "WAYPOINT");
				if (fr != NULL) {
					fprintf(fr, "WAYPOINT;%f;%f;%f\n", np_lat, np_long, alt);
				}
				n++;
				if (SurveySetup.triggermode == 1) {
					WayPoints[ModelActive][n].p_lat = 1.0;
					WayPoints[ModelActive][n].p_long = 0.0;
					WayPoints[ModelActive][n].p_alt = 0.0;
					WayPoints[ModelActive][n].frametype = 0;
					if (SurveySetup.type == 1) {
						sprintf(WayPoints[ModelActive][n].name, "RELAY%i", SurveySetup.num);
						strcpy(WayPoints[ModelActive][n].command, "RELAY_REP");
						WayPoints[ModelActive][n].param1 = (float)SurveySetup.num;
						WayPoints[ModelActive][n].param2 = (float)2;
						WayPoints[ModelActive][n].param3 = (float)1;
						if (fr != NULL) {
							fprintf(fr, "CMD;RELAY_TOGGLE;%i\n", SurveySetup.num);
						}
					} else if (SurveySetup.type == 2) {
						sprintf(WayPoints[ModelActive][n].name, "SERVO%i", SurveySetup.num);
						strcpy(WayPoints[ModelActive][n].command, "SERVO_REP");
						WayPoints[ModelActive][n].param1 = (float)SurveySetup.num;
						WayPoints[ModelActive][n].param2 = (float)SurveySetup.pos;
						WayPoints[ModelActive][n].param3 = (float)1;
						WayPoints[ModelActive][n].param4 = (float)500;
						if (fr != NULL) {
							fprintf(fr, "CMD;SERVO_TOGGLE;%i;%i\n", SurveySetup.num, SurveySetup.pos);
						}
					} else {
						sprintf(WayPoints[ModelActive][n].name, "SHUTTER%i", n);
						strcpy(WayPoints[ModelActive][n].command, "SHUTTER");
						if (fr != NULL) {
							fprintf(fr, "CMD;SHUTTER\n");
						}
					}
					n++;
				}
			}
			n_y += grid_y;
			lnx = ltx + cos((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
			lny = lty + sin((SurveySetup.angle + 90.0) * DEG2RAD) * n_y;
			for (n_x = n_x - grid_x; n_x > -grid_x; n_x -= grid_x) {
				float nx = lnx + cos((SurveySetup.angle) * DEG2RAD) * n_x;
				float ny = lny + sin((SurveySetup.angle) * DEG2RAD) * n_x;
				if (SurveySetup.triggermode == 2) {
					float nx1 = lnx + cos((SurveySetup.angle) * DEG2RAD) * (n_x - grid_x);
					float ny1 = lny + sin((SurveySetup.angle) * DEG2RAD) * (n_x - grid_x);
					float nx2 = lnx + cos((SurveySetup.angle) * DEG2RAD) * (n_x + grid_x);
					float ny2 = lny + sin((SurveySetup.angle) * DEG2RAD) * (n_x + grid_x);
					if ((point_in_poly(nx, ny) == 1 && point_in_poly(nx1, ny1) == 0) || (point_in_poly(nx, ny) == 1 && point_in_poly(nx2, ny2) == 0)) {
					} else {
						continue;
					}
				} else {
					if (point_in_poly(nx, ny) == 0) {
						continue;
					}
					if (point_in_polynf(nx, ny) != 0) {
						continue;
					}
				}
				float np_long = x2long(nx, lon, mapdata->zoom);
				float np_lat = y2lat(ny, lat, mapdata->zoom);
				float pos_alt = get_altitude(np_lat, np_long);
				float alt = SurveySetup.alt + pos_alt;
				if (SurveySetup.alt_abs == 1) {
					if (SurveySetup.alt < pos_alt + 1.0) {
						SurveySetup.alt = pos_alt + 1.0;
					}
					alt = SurveySetup.alt;
				}
				WayPoints[ModelActive][n].p_lat = np_lat;
				WayPoints[ModelActive][n].p_long = np_long;
				WayPoints[ModelActive][n].p_alt = alt;
				WayPoints[ModelActive][n].param1 = 0.0;
				WayPoints[ModelActive][n].param2 = 0.0;
				WayPoints[ModelActive][n].param3 = 0.0;
				WayPoints[ModelActive][n].param4 = 0.0;
				WayPoints[ModelActive][n].type = 0;
				WayPoints[ModelActive][n].frametype = 0;
				sprintf(WayPoints[ModelActive][n].name, "WP%i", n);
				strcpy(WayPoints[ModelActive][n].command, "WAYPOINT");

				if (fr != NULL) {
					fprintf(fr, "WAYPOINT;%f;%f;%f\n", np_lat, np_long, alt);
				}

				n++;
				if (SurveySetup.triggermode == 1) {
					WayPoints[ModelActive][n].p_lat = 1.0;
					WayPoints[ModelActive][n].p_long = 0.0;
					WayPoints[ModelActive][n].p_alt = 0.0;
					WayPoints[ModelActive][n].frametype = 0;
					if (SurveySetup.type == 1) {
						sprintf(WayPoints[ModelActive][n].name, "RELAY%i", SurveySetup.num);
						strcpy(WayPoints[ModelActive][n].command, "RELAY_REP");
						WayPoints[ModelActive][n].param1 = (float)SurveySetup.num;
						WayPoints[ModelActive][n].param2 = (float)2;
						WayPoints[ModelActive][n].param3 = (float)1;
						if (fr != NULL) {
							fprintf(fr, "CMD;RELAY_TOGGLE;%i\n", SurveySetup.num);
						}
					} else if (SurveySetup.type == 2) {
						sprintf(WayPoints[ModelActive][n].name, "SERVO%i", SurveySetup.num);
						strcpy(WayPoints[ModelActive][n].command, "SERVO_REP");
						WayPoints[ModelActive][n].param1 = (float)SurveySetup.num;
						WayPoints[ModelActive][n].param2 = (float)SurveySetup.pos;
						WayPoints[ModelActive][n].param3 = (float)1;
						WayPoints[ModelActive][n].param4 = (float)500;
						if (fr != NULL) {
							fprintf(fr, "CMD;SERVO_TOGGLE;%i;%i\n", SurveySetup.num, SurveySetup.pos);
						}
					} else {
						sprintf(WayPoints[ModelActive][n].name, "SHUTTER%i", n);
						strcpy(WayPoints[ModelActive][n].command, "SHUTTER");
						if (fr != NULL) {
							fprintf(fr, "CMD;SHUTTER\n");
						}
					}
					n++;
				}
			}
		}
		if (SurveySetup.triggermode == 2) {
			WayPoints[ModelActive][n].p_lat = 1.0;
			WayPoints[ModelActive][n].p_long = 0.0;
			WayPoints[ModelActive][n].p_alt = 0.0;
			WayPoints[ModelActive][n].frametype = 0;
			sprintf(WayPoints[ModelActive][n].name, "SHUTTER");
			strcpy(WayPoints[ModelActive][n].command, "SHUTTER_INT");
			WayPoints[ModelActive][n].param1 = (float)0;
			WayPoints[ModelActive][n].param2 = (float)0;
			WayPoints[ModelActive][n].param3 = (float)0;
			WayPoints[ModelActive][n].param4 = (float)0;
			if (fr != NULL) {
				fprintf(fr, "CMD;SHUTTER_DIST;%i\n", 0);
			}
			n++;
		}
		if (fr != NULL) {
			fclose(fr);
		}
		map_show_poly = 0;
		map_show_wp = 1;
	}
	return 0;
}

void survey_draw_setup (ESContext *esContext) {
	int ny = 1;
	char tmp_str[128];
	float px1 = -0.8;
	float py1 = -0.9;
	float px2 = 0.8;
	float py2 = -0.0;
	reset_buttons();
	draw_box_f3(esContext, px1, py1, 0.002, px2, py2, 0.002, 0, 0, 0, 127);
	draw_box_f3(esContext, px1, py1, 0.005, px2, py1 + 0.06, 0.005, 255, 255, 255, 127);
	draw_rect_f3(esContext, px1, py1, 0.005, px2, py1 + 0.06, 0.005, 255, 255, 255, 255);
	draw_text_button(esContext, "survey_setup_title", setup.view_mode, "Survey-Setup", FONT_PINK, px1, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
	if (SurveySetup.options == 0) {
		draw_text_button(esContext, "SurveySetup.options1", setup.view_mode, "[GRID]", FONT_GREEN, px1 + 0.95, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		draw_text_button(esContext, "SurveySetup.options2", setup.view_mode, "[TRIGGER]", FONT_WHITE, px1 + 1.25, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 1.0);
	} else {
		draw_text_button(esContext, "SurveySetup.options1", setup.view_mode, "[GRID]", FONT_WHITE, px1 + 0.95, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		draw_text_button(esContext, "SurveySetup.options2", setup.view_mode, "[TRIGGER]", FONT_GREEN, px1 + 1.25, py1, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 1.0);
	}

	sprintf(tmp_str, "Name: %s", SurveySetup.name);
	draw_text_button(esContext, "survey_name", setup.view_mode, tmp_str, FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_name_edit, 0.0);
	ny++;

	if (SurveySetup.options == 1) {
		draw_text_button(esContext, "trigger_title", setup.view_mode, "Trigger:", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		if (SurveySetup.triggermode == 1) {
			draw_text_button(esContext, "SurveySetup.triggermode", setup.view_mode, "  Mode: ON EACH WP", FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
			ny++;
			if (SurveySetup.type == 1) {
				draw_text_button(esContext, "SurveySetup.type", setup.view_mode, "  Type: RELAY", FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
				ny++;
				sprintf(tmp_str, "  Relay-Number: %i", SurveySetup.num);
				draw_text_button(esContext, "SurveySetup.num", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
			} else if (SurveySetup.type == 2) {
				draw_text_button(esContext, "SurveySetup.type", setup.view_mode, "  Type: SERVO", FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
				ny++;
				sprintf(tmp_str, "  Servo-Num: %i", SurveySetup.num);
				draw_text_button(esContext, "SurveySetup.num", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
				ny++;
				sprintf(tmp_str, "  Servo-Position: %i", SurveySetup.pos);
				draw_text_button(esContext, "SurveySetup.pos", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
			} else {
				draw_text_button(esContext, "SurveySetup.type", setup.view_mode, "  Type: SHUTTER", FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
			}
		} else if (SurveySetup.triggermode == 2) {
			draw_text_button(esContext, "SurveySetup.triggermode", setup.view_mode, "  Mode: SHUTTER INTERVAL", FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
			ny++;
			sprintf(tmp_str, "  Interval: %im", SurveySetup.interval);
			draw_text_button(esContext, "SurveySetup.interval", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		} else {
			draw_text_button(esContext, "SurveySetup.triggermode", setup.view_mode, "  Mode: NONE", FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		}
		ny++;
	} else if (SurveySetup.mode == 1) {
		// fixed grid
		draw_text_button(esContext, "SurveySetup.mode", setup.view_mode, "Mode: GRID", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		draw_text_button(esContext, "cam_grid", setup.view_mode, "Grid:", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		if (SurveySetup.triggermode == 2) {
			sprintf(tmp_str, "  grid_x: %0.0fm (set by Trigger-Intervall)", SurveySetup.grid_x);
		} else {
			sprintf(tmp_str, "  grid_x: %0.0fm", SurveySetup.grid_x);
		}
		draw_text_button(esContext, "SurveySetup.grid_x", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		sprintf(tmp_str, "  grid_y: %0.0fm", SurveySetup.grid_y);
		draw_text_button(esContext, "SurveySetup.grid_y", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		draw_text_button(esContext, "cam_alt", setup.view_mode, "Misc:", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		sprintf(tmp_str, "  Alt: %0.2f", SurveySetup.alt);
		draw_text_button(esContext, "SurveySetup.alt", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		if (SurveySetup.alt_abs == 1) {
			draw_text_button(esContext, "SurveySetup.alt_abs", setup.view_mode, "ABS", FONT_GREEN, px1 + 0.8, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		} else {
			draw_text_button(esContext, "SurveySetup.alt_abs", setup.view_mode, "REL", FONT_GREEN, px1 + 0.8, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		}
		ny++;
		sprintf(tmp_str, "  Angle: %0.0f", SurveySetup.angle);
		draw_text_button(esContext, "SurveySetup.angle", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
	} else {
		// Cam-Grid
		draw_text_button(esContext, "SurveySetup.mode", setup.view_mode, "Mode: CAM", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		// Lense
		draw_text_button(esContext, "SurveySetup.lense", setup.view_mode, "Lense:", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		draw_text_button(esContext, "cam_lense_20", setup.view_mode, "[20mm]", FONT_GREEN, px1 + 0.8, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_CENTER, ALIGN_TOP, survey_set, 0.0);
		draw_text_button(esContext, "cam_lense_50", setup.view_mode, "[50mm]", FONT_GREEN, px1 + 1.1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_CENTER, ALIGN_TOP, survey_set, 0.0);
		draw_text_button(esContext, "cam_lense_70", setup.view_mode, "[70mm]", FONT_GREEN, px1 + 1.4, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_CENTER, ALIGN_TOP, survey_set, 0.0);
		ny++;
		sprintf(tmp_str, "  focal length: %0.0fmm", SurveySetup.lense);
		draw_text_button(esContext, "SurveySetup.lense", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		// Sensor
		draw_text_button(esContext, "cam_sensor", setup.view_mode, "Sensor:", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		draw_text_button(esContext, "cam_sensor_1.0", setup.view_mode, "[Full]", FONT_GREEN, px1 + 0.8, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_CENTER, ALIGN_TOP, survey_set, 0.0);
		draw_text_button(esContext, "cam_sensor_1.4", setup.view_mode, "[APS-E]", FONT_GREEN, px1 + 1.1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_CENTER, ALIGN_TOP, survey_set, 0.0);
		draw_text_button(esContext, "cam_sensor_1.6", setup.view_mode, "[APS-C]", FONT_GREEN, px1 + 1.4, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_CENTER, ALIGN_TOP, survey_set, 0.0);
		ny++;
		sprintf(tmp_str, "  Film-Width: %0.0fmm", SurveySetup.film_width);
		draw_text_button(esContext, "SurveySetup.film_width", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		sprintf(tmp_str, "  Film-Height: %0.0fmm", SurveySetup.film_height);
		draw_text_button(esContext, "SurveySetup.film_height", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		sprintf(tmp_str, "  Sensor-Mult.: %0.2fx", SurveySetup.sensor_mult);
		draw_text_button(esContext, "SurveySetup.sensor_mult", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		// Overlap/Alt
		draw_text_button(esContext, "SurveySetup.overlap", setup.view_mode, "Misc:", FONT_WHITE, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		sprintf(tmp_str, "  Overlap: %0.2f", SurveySetup.overlap);
		draw_text_button(esContext, "SurveySetup.overlap", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
		sprintf(tmp_str, "  Alt: %0.2f", SurveySetup.alt);
		draw_text_button(esContext, "SurveySetup.alt", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		if (SurveySetup.alt_abs == 1) {
			draw_text_button(esContext, "SurveySetup.alt_abs", setup.view_mode, "ABS", FONT_GREEN, px1 + 0.8, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		} else {
			draw_text_button(esContext, "SurveySetup.alt_abs", setup.view_mode, "REL", FONT_GREEN, px1 + 0.8, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		}
		ny++;
		sprintf(tmp_str, "  Angle: %0.0f", SurveySetup.angle);
		draw_text_button(esContext, "SurveySetup.angle", setup.view_mode, tmp_str, FONT_GREEN, px1, py1 + (float)ny * 0.06, 0.005, 0.06, ALIGN_LEFT, ALIGN_TOP, survey_set, 0.0);
		ny++;
	}
	draw_text_button(esContext, "survey_load", setup.view_mode, "[LOAD]", FONT_GREEN, px1 + 0.02, py2 - 0.075, 0.005, 0.07, ALIGN_LEFT, ALIGN_TOP, survey_load, 0.0);
	draw_text_button(esContext, "survey_save", setup.view_mode, "[SAVE]", FONT_GREEN, px1 + 0.32, py2 - 0.075, 0.005, 0.07, ALIGN_LEFT, ALIGN_TOP, survey_save, 0.0);
	draw_text_button(esContext, "survey_export_kml", setup.view_mode, "[KML]", FONT_GREEN, px2 - 0.62, py2 - 0.075, 0.005, 0.07, ALIGN_RIGHT, ALIGN_TOP, survey_export_kml, 0.0);
	draw_text_button(esContext, "survey_setup_write", setup.view_mode, "[WRITE]", FONT_GREEN, px2 - 0.32, py2 - 0.075, 0.005, 0.07, ALIGN_RIGHT, ALIGN_TOP, survey_set, 0.0);
	draw_text_button(esContext, "survey_setup_done", setup.view_mode, "[CLOSE]", FONT_GREEN, px2 - 0.02, py2 - 0.075, 0.005, 0.07, ALIGN_RIGHT, ALIGN_TOP, survey_set, 0.0);
	draw_rect_f3(esContext, px1, py1, 0.005, px2, py2, 0.005, 255, 255, 255, 255);
}



