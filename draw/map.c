
#include <all.h>
#include <kml.h>


uint8_t maplen = 0;
uint8_t omaplen = 0;
char mapnames[20][7][1024];
char omapnames[20][7][1024];
PointOfInterest POIs[MAX_POIS];

GeoMap *mapdata = NULL;


#ifdef USE_FMAP
#include <mp.h>
extern int fdMap;
#endif


int long2tilex(float lon, int z) {
	return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z))); 
}

int lat2tiley(float lat, int z) {
	return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z))); 
}

float tilex2long(int x, int z) {
	return x / pow(2.0, z) * 360.0 - 180;
}

float tiley2lat(int y, int z) {
	float n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
	return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}

float y2lat (int y, float lat, float zoom) {
	int tile_ny = y / 256;
	int tile_y = lat2tiley(lat, zoom);
	float t_lat = tiley2lat(tile_y + tile_ny, zoom);
	float t_lat2 = tiley2lat(tile_y + tile_ny + 1, zoom);
	float t_lat_div = t_lat2 - t_lat;
	int tpos_y = y - tile_ny * 256;
	float mouse_lat = t_lat + t_lat_div * (float)tpos_y / 256.0;
	return mouse_lat;
}

float x2long (int x, float lon, float zoom) {
	int tile_nx = x / 256;
	int tile_x = long2tilex(lon, zoom);
	float t_long = tilex2long(tile_x + tile_nx, zoom);
	float t_long2 = tilex2long(tile_x + tile_nx + 1, zoom);
	float t_long_div = t_long2 - t_long;
	int tpos_x = x - tile_nx * 256;
	float mouse_long = t_long + t_long_div * (float)tpos_x / 256.0;
	return mouse_long;
}


int lat2y (float mark_lat, float lat, float zoom) {
#ifdef USE_FMAP
	if (strcmp(mapnames[map_type][MAP_TYPE], "FMAP") == 0) {
		float vx;
		float vy;
		mpCoordLatLong2Viewport(fdMap, mark_lat, lon, &vx, &vy);
		return setup.screen_h - (int)vy;
	}
#endif
	int tile_y = lat2tiley(lat, zoom);
	int mark_tile_y = lat2tiley(mark_lat, zoom) - tile_y;
	float m_lat = tiley2lat(tile_y + mark_tile_y, zoom);
	float m_lat2 = tiley2lat(tile_y + mark_tile_y + 1, zoom);
	float m_lat_div = m_lat2 - m_lat;
	float m_lat_div2 = mark_lat - m_lat;
	float mark_tile_y_div = 256.0 * m_lat_div2 / m_lat_div;
	float mark_y = mark_tile_y * 256.0 + mark_tile_y_div;
	return (int)mark_y;
}

int long2x (float mark_long, float lon, float zoom) {
#ifdef USE_FMAP
	if (strcmp(mapnames[map_type][MAP_TYPE], "FMAP") == 0) {
		float vx;
		float vy;
		mpCoordLatLong2Viewport(fdMap, lat, mark_long, &vx, &vy);
		return (int)vx;
	}
#endif
	int tile_x = long2tilex(lon, zoom);
	int mark_tile_x = long2tilex(mark_long, zoom) - tile_x;
	float m_long = tilex2long(tile_x + mark_tile_x, zoom);
	float m_long2 = tilex2long(tile_x + mark_tile_x + 1, zoom);
	float m_long_div = m_long2 - m_long;
	float m_long_div2 = mark_long - m_long;
	float mark_tile_x_div = 256.0 * m_long_div2 / m_long_div;
	float mark_x = (float)mark_tile_x * 256.0 + mark_tile_x_div;
	return (int)mark_x;
}




char *BingtileXYZToQuadKey(char *quadKey, int x, int y, int z) {
	int i = 0;
	int n = 0;
	for (i = z; i > 0; i--) {
		int digit = 0;
	        uint8_t mask = 1<<(i - 1);
		if ((x & mask) != 0) {
	            digit += 1;
		}
		if ((y & mask) != 0) {
	            digit += 2;
		}
//		SDL_Log("map: __ %i __\n", digit);
		quadKey[n++] = (digit + 48);
		quadKey[n] = 0;
	}
	return quadKey;
}






static void map_parseMapService (xmlDocPtr doc, xmlNodePtr cur, uint8_t map_service) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(mapnames[map_service][MAP_NAME], (char *)key, 511);
			} else {
				mapnames[map_service][MAP_NAME][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"url"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(mapnames[map_service][MAP_URL], (char *)key, 511);
			} else {
				mapnames[map_service][MAP_URL][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"url2"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(mapnames[map_service][MAP_URL2], (char *)key, 511);
			} else {
				mapnames[map_service][MAP_URL2][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"comment"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(mapnames[map_service][MAP_COMMENT], (char *)key, 511);
			} else {
				mapnames[map_service][MAP_COMMENT][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"copyright"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(mapnames[map_service][MAP_COPYRIGHT], (char *)key, 511);
			} else {
				mapnames[map_service][MAP_COPYRIGHT][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"file"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(mapnames[map_service][MAP_FILE], (char *)key, 511);
			} else {
				mapnames[map_service][MAP_FILE][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"type"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(mapnames[map_service][MAP_TYPE], (char *)key, 511);
			} else {
				mapnames[map_service][MAP_TYPE][0] = 0;
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void map_parseOverlayMapService (xmlDocPtr doc, xmlNodePtr cur, uint8_t omap_service) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(omapnames[omap_service][MAP_NAME], (char *)key, 199);
			} else {
				omapnames[omap_service][MAP_NAME][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"url"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(omapnames[omap_service][MAP_URL], (char *)key, 199);
			} else {
				omapnames[omap_service][MAP_URL][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"copyright"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(omapnames[omap_service][MAP_COPYRIGHT], (char *)key, 511);
			} else {
				omapnames[omap_service][MAP_COPYRIGHT][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"file"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(omapnames[omap_service][MAP_FILE], (char *)key, 199);
			} else {
				omapnames[omap_service][MAP_FILE][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"type"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(omapnames[omap_service][MAP_TYPE], (char *)key, 199);
			} else {
				omapnames[omap_service][MAP_TYPE][0] = 0;
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

void map_parseDoc (char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
//	xmlChar *key;
	maplen = 0;
	omaplen = 0;

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
		SDL_Log("map: Document parsing failed: %s\n", docname);
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
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"service"))) {
			map_parseMapService (doc, cur, maplen++);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"overlay_service"))) {
			map_parseOverlayMapService (doc, cur, omaplen++);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}





void download_map_range (float from_lat, float from_lon, float to_lat, float to_lon, uint8_t zoom) {
	int tile_x = long2tilex(from_lon, zoom);
	int tile_y = lat2tiley(from_lat, zoom);
	int tile_x_max = long2tilex(to_lon, zoom);
	int tile_y_max = lat2tiley(to_lat, zoom);
	uint8_t tiles_x = tile_x_max - tile_x;
	uint8_t tiles_y = tile_y_max - tile_y;
	int x_n = 0;
	int y_n = 0;
	char tile_name[2024];
	char tile_url[2024];
	char tmp_str[2024];
	char tmp_str2[2024];
	float google_tile_long1 = 0;
	float google_tile_long2 = 0;
	float google_tile_long = 0;
	float google_tile_lat = 0;
	if (zoom <= 18) {
		for (y_n = 0; y_n < tiles_y && gui_running == 1; y_n++) {
			for (x_n = 0; x_n < tiles_x && gui_running == 1; x_n++) {
				if (strcmp(mapnames[map_type][MAP_TYPE], "GOOGLE") == 0) {
					sprintf(tile_name, "%s/MAPS/google_%i_%i_%i.png", get_datadirectory(), zoom, tile_x + x_n, tile_y + y_n);
					if (file_exists(tile_name) == 0) {
						/* Google-Maps */
						google_tile_long1 = tilex2long(tile_x + x_n, zoom);
						google_tile_long2 = tilex2long(tile_x + x_n + 1, zoom);
						google_tile_long = google_tile_long1 + (google_tile_long2 - google_tile_long1) / 2;
						google_tile_lat = tiley2lat(tile_y + y_n + 1, zoom);

						sprintf(tile_name, "%s/MAPS/tobig_google_%i_%i_%i.png", get_datadirectory(), zoom, tile_x + x_n, tile_y + y_n);
						sprintf(tile_url, mapnames[map_type][MAP_URL], google_tile_lat, google_tile_long, zoom, 256, 356);
						SDL_Log("map: %s -> %s\n", tile_url, tile_name);
						file_download(tile_name, tile_url);
						// Crop map-image for titles
						sprintf(tmp_str2, mapnames[map_type][MAP_FILE], get_datadirectory(), zoom, tile_x + x_n, tile_y + y_n);
						sprintf(tmp_str, "convert -crop 256x256+0+50 %s %s", tile_name, tmp_str2);
						system(tmp_str);
					}
				} else {
					if (zoom <= 18) {
						sprintf(tile_name, mapnames[map_type][MAP_FILE], get_datadirectory(), zoom, tile_x + x_n, tile_y + y_n);
						if (file_exists(tile_name) == 0) {
							if (strcmp(mapnames[map_type][MAP_TYPE], "ZYX") == 0) {
								sprintf(tile_url, mapnames[map_type][MAP_URL], zoom, tile_y + y_n, tile_x + x_n);
							} else if (strcmp(mapnames[map_type][MAP_TYPE], "ZXY") == 0) {
								sprintf(tile_url, mapnames[map_type][MAP_URL], zoom, tile_x + x_n, tile_y + y_n);
							} else if (strcmp(mapnames[map_type][MAP_TYPE], "XYZ") == 0) {
								sprintf(tile_url, mapnames[map_type][MAP_URL], tile_x + x_n, tile_y + y_n, zoom);
							} else if (strcmp(mapnames[map_type][MAP_TYPE], "TMS") == 0) {
								int ymax = (1<<mapdata->zoom);
								int y = ymax - (tile_y + y_n) - 1;
								sprintf(tile_url, mapnames[map_type][MAP_URL], zoom, tile_x + x_n, y);
							} else if (strcmp(mapnames[map_type][MAP_TYPE], "BING") == 0) {
								char quadKey[100];
								sprintf(tile_url, mapnames[map_type][MAP_URL], BingtileXYZToQuadKey(quadKey, tile_x + x_n, tile_y + y_n, zoom));
							}
							if (strcmp(mapnames[map_type][MAP_TYPE], "FMAP") != 0) {
								SDL_Log("map: %s -> %s\n", tile_url, tile_name);
								file_download(tile_name, tile_url);
							}
						}
					}
				}
			}
		}
	}
}

uint8_t map_downloader (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	uint8_t zoom = 0;
	float lat = 50.2;
	float lon = 9.0;
	for (zoom = 10; zoom < 18; zoom++) {
		download_map_range(lat, lon, lat + 0.5, lon + 0.5, zoom);
	}
//      DE: 47.0 -> 57.0, 5.8 -> 15.3
//	download_map_range(47.0, 5.7, 57.0, 15.4, 11);
//	download_map_range(47.0, 5.7, 57.0, 15.4, 10);
	return 0;
}







void get_maps (uint8_t mode, GeoMap *mapdata) {
	int tile_x = long2tilex(mapdata->lon, mapdata->zoom);
	int tile_y = lat2tiley(mapdata->lat, mapdata->zoom);
	int x_n = 0;
	int y_n = 0;
	char tile_name[2024];
	char tile_url[2024];
	char tmp_str[2024];
	char tmp_str2[2024];
	char url_string[1024];
	char status_txt[2024];
	uint8_t tiles_x = (setup.screen_w + 255) / 256;
	uint8_t tiles_y = (setup.screen_h + 255) / 256;
	uint8_t tiles_num = 0;
	uint8_t tiles_need = 0;
	float google_tile_long1 = 0;
	float google_tile_long2 = 0;
	float google_tile_long = 0;
	float google_tile_lat = 0;
	int16_t step = 2;
	int16_t start = 0;
	int16_t overlay = 0;
	static float lat_last[2] = {0, 0};
	static float lon_last[2] = {0, 0};
	static uint8_t zoom_last[2] = {0, 0};
	if (mode == 0) {
		start = 0;
	} else {
		start = 1;
	}
	if (mapdata->zoom <= 18) {
		for (overlay = 0; overlay <= MAP_OVERLAY && mapdata->mapthread_running == 1; overlay++) {
			for (y_n = -overlay + start; y_n < tiles_y + overlay && mapdata->mapthread_running == 1; y_n += step) {
				for (x_n = -overlay; x_n < tiles_x + overlay && mapdata->mapthread_running == 1; x_n += 1) {
					if (lat_last[mode] != mapdata->lat || lon_last[mode] != mapdata->lon || zoom_last[mode] != mapdata->zoom) {
						lat_last[mode] = mapdata->lat;
						lon_last[mode] = mapdata->lon;
						zoom_last[mode] = mapdata->zoom;
						return;
					}
					if (strncmp(mapnames[map_type][MAP_URL], "file:/", 6) == 0) {
					} else if (strcmp(mapnames[map_type][MAP_TYPE], "GOOGLE") == 0) {
						sprintf(tile_name, "%s/MAPS/google_%i_%i_%i.png", get_datadirectory(), mapdata->zoom, tile_x + x_n, tile_y + y_n);
						if (file_exists(tile_name) == 0) {
							sprintf(status_txt, "getting map-tile: %i_%i_%i.png (%i/%i)", mapdata->zoom, tile_x + x_n, tile_y + y_n, tiles_num + 1, tiles_need);
							sys_message(status_txt);
							/* Google-Maps */
							google_tile_long1 = tilex2long(tile_x + x_n, mapdata->zoom);
							google_tile_long2 = tilex2long(tile_x + x_n + 1, mapdata->zoom);
							google_tile_long = google_tile_long1 + (google_tile_long2 - google_tile_long1) / 2;
							google_tile_lat = tiley2lat(tile_y + y_n + 1, mapdata->zoom);
							sprintf(tile_name, "%s/MAPS/tobig_google_%i_%i_%i.png", get_datadirectory(), mapdata->zoom, tile_x + x_n, tile_y + y_n);
							if (start == 1 && mapnames[map_type][MAP_URL2][0] != 0) {
								sprintf(tile_url, mapnames[map_type][MAP_URL2], google_tile_lat, google_tile_long, mapdata->zoom, 256, 356);
							} else {
								sprintf(tile_url, mapnames[map_type][MAP_URL], google_tile_lat, google_tile_long, mapdata->zoom, 256, 356);
							}
							SDL_Log("map: %s -> %s\n", tile_url, tile_name);
							file_download(tile_name, tile_url);
							// Crop map-image for titles
							sprintf(tmp_str2, "%s/MAPS/google_%i_%i_%i.png", get_datadirectory(), mapdata->zoom, tile_x + x_n, tile_y + y_n);
							sprintf(tmp_str, "convert -crop 256x256+0+50 %s %s", tile_name, tmp_str2);
							system(tmp_str);
						}
					} else if (mapnames[map_type][MAP_FILE][0] != 0) {
						if (mapdata->zoom <= 18) {
							sprintf(tile_name, mapnames[map_type][MAP_FILE], get_datadirectory(), mapdata->zoom, tile_x + x_n, tile_y + y_n);
							if (file_exists(tile_name) == 0) {
								sprintf(status_txt, "getting map-tile: %s", tile_name);
								sys_message(status_txt);
								if (start == 1 && mapnames[map_type][MAP_URL2][0] != 0) {
									strcpy(url_string, mapnames[map_type][MAP_URL2]);
								} else {
									strcpy(url_string, mapnames[map_type][MAP_URL]);
								}
								if (strcmp(mapnames[map_type][MAP_TYPE], "ZYX") == 0) {
									sprintf(tile_url, url_string, mapdata->zoom, tile_y + y_n, tile_x + x_n);
								} else if (strcmp(mapnames[map_type][MAP_TYPE], "ZXY") == 0) {
									sprintf(tile_url, url_string, mapdata->zoom, tile_x + x_n, tile_y + y_n);
								} else if (strcmp(mapnames[map_type][MAP_TYPE], "XYZ") == 0) {
									sprintf(tile_url, url_string, tile_x + x_n, tile_y + y_n, mapdata->zoom);
								} else if (strcmp(mapnames[map_type][MAP_TYPE], "ZMS") == 0) {
									sprintf(tile_url, url_string, mapdata->zoom, tile_x + x_n, tile_y + y_n);
								} else if (strcmp(mapnames[map_type][MAP_TYPE], "TMS") == 0) {
									int ymax = (1<<mapdata->zoom);
									int y = ymax - (tile_y + y_n) - 1;
									sprintf(tile_url, url_string, mapdata->zoom, tile_x + x_n, y);
								} else if (strcmp(mapnames[map_type][MAP_TYPE], "BING") == 0) {
									char quadKey[100];
									sprintf(tile_url, url_string, BingtileXYZToQuadKey(quadKey, tile_x + x_n, tile_y + y_n, mapdata->zoom));
								}
								if (strcmp(mapnames[map_type][MAP_TYPE], "FMAP") != 0) {
									SDL_Log("map: %s -> %s\n", tile_url, tile_name);
									file_download(tile_name, tile_url);
								}
							}
						}
					}



					if (strncmp(omapnames[omap_type][MAP_URL], "file:/", 6) == 0) {
					} else if (omapnames[omap_type][MAP_FILE][0] != 0) {
						if (mapdata->zoom <= 18) {
							sprintf(tile_name, omapnames[omap_type][MAP_FILE], get_datadirectory(), mapdata->zoom, tile_x + x_n, tile_y + y_n);
							if (file_exists(tile_name) == 0) {
								sprintf(status_txt, "getting omap-tile: %s", tile_name);
								sys_message(status_txt);
								if (start == 1 && omapnames[omap_type][MAP_URL2][0] != 0) {
									strcpy(url_string, omapnames[omap_type][MAP_URL2]);
								} else {
									strcpy(url_string, omapnames[omap_type][MAP_URL]);
								}
								if (strcmp(omapnames[omap_type][MAP_TYPE], "ZYX") == 0) {
									sprintf(tile_url, url_string, mapdata->zoom, tile_y + y_n, tile_x + x_n);
								} else if (strcmp(omapnames[omap_type][MAP_TYPE], "ZXY") == 0) {
									sprintf(tile_url, url_string, mapdata->zoom, tile_x + x_n, tile_y + y_n);
								} else if (strcmp(omapnames[omap_type][MAP_TYPE], "XYZ") == 0) {
									sprintf(tile_url, url_string, tile_x + x_n, tile_y + y_n, mapdata->zoom);
								} else if (strcmp(omapnames[omap_type][MAP_TYPE], "ZMS") == 0) {
									sprintf(tile_url, url_string, mapdata->zoom, tile_x + x_n, tile_y + y_n);
								} else if (strcmp(omapnames[omap_type][MAP_TYPE], "TMS") == 0) {
									int ymax = (1<<mapdata->zoom);
									int y = ymax - (tile_y + y_n) - 1;
									sprintf(tile_url, url_string, mapdata->zoom, tile_x + x_n, y);
								} else if (strcmp(omapnames[omap_type][MAP_TYPE], "BING") == 0) {
									char quadKey[100];
									sprintf(tile_url, url_string, BingtileXYZToQuadKey(quadKey, tile_x + x_n, tile_y + y_n, mapdata->zoom));
								}
								if (strcmp(omapnames[omap_type][MAP_TYPE], "FMAP") != 0) {
									SDL_Log("omap: %s -> %s\n", tile_url, tile_name);
									file_download(tile_name, tile_url);
								}
							}
						}
					}
					tiles_num++;
				}
			}
		}
	}
}

void get_srtm (GeoMap *mapdata) {
	char LON[128];
	char LAT[128];
	char file[1024];
	char file2[1024];
	char listfile[1024];
	char line[1024];
	char source[1024];
	char target[1024];
	int16_t lat_m = (int)mapdata->lat;
	int16_t lon_m = (int)mapdata->lon;
	if (lat_m < 0) {
		sprintf(LAT, "S%02i", lat_m * -1 + 1);
	} else {
		sprintf(LAT, "N%02i", lat_m);
	}
	if (lon_m < 0) {
		sprintf(LON, "W%03i", lon_m * -1 + 1);
	} else {
		sprintf(LON, "E%03i", lon_m);
	}
	sprintf(file, "%s%s.hgt", LAT, LON);
	sprintf(file2, "%s/MAPS/%s", get_datadirectory(), file);
	if (file_exists(file2) == 0) {
		sprintf(target, "%s/MAPS/part/", get_datadirectory());
#ifndef WINDOWS
		mkdir(target, 0755);
#else
		mkdir(target);
#endif
		source[0] = 0;
		FILE *fr = NULL;
		sprintf(listfile, "%s/SRTM.list", BASE_DIR);
		fr = fopen (listfile, "r");
		if (fr != NULL) {
			while(fgets(line, 1000, fr) != NULL) {
				if (strstr(line, file) > 0) {
					line[strlen(line) - 1] = 0;
					sprintf(source, "%s", line);
				}
			}
			fclose(fr);
		} else {

			SDL_Log("srtm: list not found: %s\n", listfile);

			sprintf(source, "http://dds.cr.usgs.gov/srtm/version2_1/SRTM3/Eurasia/%s.zip", file);
		}
		if (source[0] != 0) {
			SDL_Log("srtm: getting srtm-data: %s\n", file);
			sprintf(target, "%s/MAPS/part/%s.zip", get_datadirectory(), file);
			SDL_Log("map: get SRTM: %s\n", source);
			if (file_download(target, source) != -1) {
				sprintf(source, "%s/MAPS/part/%s.zip", get_datadirectory(), file);
				sprintf(target, "%s/MAPS/%s", get_datadirectory(), file);
				unzipFile(source, file, target);
				unlink(source);
			}
		} else {
			SDL_Log("srtm: file %s not found\n", file);
		}
	}
}

int thread_get_maps1 (void *data) {
	GeoMap *mapdata = (GeoMap *)data;
	while (mapdata->mapthread_running == 1) {
		get_maps(0, mapdata);
		get_srtm(mapdata);
		SDL_Delay(100);
	}
	SDL_Log("map: exit thread (get_maps1)\n");
	return 0;
}

int thread_get_maps2 (void *data) {
	GeoMap *mapdata = (GeoMap *)data;
	while (mapdata->mapthread_running == 1) {
		get_maps(1, mapdata);
		SDL_Delay(100);
	}
	SDL_Log("map: exit thread (get_maps2)\n");
	return 0;
}

void draw_model (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, float roll, float pitch, float yaw, uint8_t modelid, uint8_t mode, float lat, float lon, uint8_t zoom) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	char tmp_str[1024];
	int mark_x = long2x(mark_long, lon, zoom);
	int mark_y = lat2y(mark_lat, lat, zoom);
	float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	float mark_z = mark_alt / alt_zoom - 0.022;
	uint8_t alpha = 255;
	if (mode == 1) {
		alpha = 127;
	}
	if (map_view == 0) {
		mark_z = 0.001;
	}
	if (center_map == 2) {
		if (x1 < -0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0, 0);
		}
		if (x1 > 0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0, 0);
		}
		if (y1 < -0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0, 0);
		}
		if (y1 > 0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0, 0);
		}
	}
	// Ground-Line
	float z2 = (float)get_altitude(mark_lat, mark_long) / alt_zoom;
	draw_line_f3(esContext, x1, y1, z2, x1, y1, mark_z, 0, 0, 255, alpha);
	draw_circleFilled_f3(esContext, x1, y1, z2, 0.005, 255, 255, 255, alpha);
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -mapdata->offset_x1, mapdata->offset_y1, 0.0 );
	}
#endif

	draw_text_f3(esContext, x1 + 0.04, y1 - 0.04, mark_z, 0.04, 0.04, FONT_WHITE, ModelData[modelid].name);
	sprintf(tmp_str, "%0.0fm", ModelData[modelid].p_alt);
	draw_text_f3(esContext, x1 + 0.04, y1 + 0.0, mark_z, 0.04, 0.04, FONT_WHITE, tmp_str);
	draw_line_f3(esContext, x1, y1, mark_z, x1 + 0.2, y1, mark_z, 255, 255, 255, 127);

	esTranslate( &modelview, x1, -y1, -2.0 + mark_z);
	esRotate( &modelview, yaw, 0.0, 0.0, 1.0 );
	esRotate( &modelview, roll, 0.0, 1.0, 0.0 );
	esRotate( &modelview, pitch, 1.0, 0.0, 0.0 );
	esTranslate( &modelview, -x1, y1, 2.0 - mark_z);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	// Arrow
	draw_line_f3(esContext, x1, y1 - 0.1, mark_z, x1, y1, mark_z, 0, 0, 0, alpha);
	draw_line_f3(esContext, x1, y1 - 0.1, mark_z, x1 - 0.02, y1 - 0.1 + 0.02, mark_z, 0, 0, 0, alpha);
	draw_line_f3(esContext, x1, y1 - 0.1, mark_z, x1 + 0.02, y1 - 0.1 + 0.02, mark_z, 0, 0, 0, alpha);
	// View-Line
	draw_line_f3(esContext, x1, y1 - 10.0, mark_z, x1, y1, mark_z, 255, 255, 255, alpha / 2);

#ifdef SDLGL
	static Object3d obj3d[MAV_TYPE_ENUM_END];
	get_background_model(modelid, tmp_str);
	if (tmp_str[0] != 0) {
		if (strcmp(obj3d[modelid].name, tmp_str) != 0) {
			if (obj3d[modelid].faces_num != 0) {
				object3d_free(&obj3d[modelid]);
			}
			object3d_load(&obj3d[modelid], tmp_str);
		}
		esTranslate( &modelview, x1, -y1, -2.0 + mark_z);
		glScalef(0.1, 0.1, 0.1);
		if (mode == 0) {
			object3d_draw(&obj3d[modelid], 0, 255, 0, 127);
		} else {
			object3d_draw(&obj3d[modelid], 255, 255, 255, 50);
		}
		esTranslate( &modelview, -x1, y1, 2.0 - mark_z);
	} else
#endif
	{
		// Quad
		float size = 0.03;
		glLineWidth(3);
		draw_line_f3(esContext, x1 - size, y1 - size, mark_z, x1 + size, y1 + size, mark_z, 0, 0, 0, alpha);
		draw_line_f3(esContext, x1 - size, y1 + size, mark_z, x1 + size, y1 - size, mark_z, 0, 0, 0, alpha);
		glLineWidth(1);
		draw_circleFilled_f3(esContext, x1 + size, y1 + size, mark_z, 0.012, 255, 0, 0, alpha);
		draw_circleFilled_f3(esContext, x1 - size, y1 + size, mark_z, 0.012, 255, 0, 0, alpha);
		draw_circleFilled_f3(esContext, x1 + size, y1 - size, mark_z, 0.012, 0, 255, 0, alpha);
		draw_circleFilled_f3(esContext, x1 - size, y1 - size, mark_z, 0.012, 0, 255, 0, alpha);
		draw_circle_f3(esContext, x1 + size, y1 + size, mark_z, 0.012, 0, 0, 0, alpha);
		draw_circle_f3(esContext, x1 - size, y1 + size, mark_z, 0.012, 0, 0, 0, alpha);
		draw_circle_f3(esContext, x1 + size, y1 - size, mark_z, 0.012, 0, 0, 0, alpha);
		draw_circle_f3(esContext, x1 - size, y1 - size, mark_z, 0.012, 0, 0, 0, alpha);
	}
#ifdef SDLGL
	glPopMatrix();
#endif
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -mapdata->offset_x1, mapdata->offset_y1, 0.0 );
	}
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
#ifdef SDLGL
	glPopMatrix();
#endif
}

void draw_tracker (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, float pitch, float yaw, float lat, float lon, uint8_t zoom) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	int mark_x = long2x(mark_long, lon, zoom);
	int mark_y = lat2y(mark_lat, lat, zoom);
	float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	float mark_z = mark_alt / alt_zoom - 0.022;
	if (map_view == 0) {
		mark_z = 0.001;
	}
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -mapdata->offset_x1, mapdata->offset_y1, 0.0 );
	}
#endif
	esTranslate( &modelview, x1, -y1, -2.0 + mark_z);
	esRotate( &modelview, yaw, 0.0, 0.0, 1.0 );
	esRotate( &modelview, pitch, 1.0, 0.0, 0.0 );
	esTranslate( &modelview, -x1, y1, 2.02 - mark_z);
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	// Arrow
	draw_line_f3(esContext, x1, y1 - 0.1, mark_z, x1, y1, mark_z, 0, 0, 0, 255);
	draw_line_f3(esContext, x1, y1 - 0.1, mark_z, x1 - 0.02, y1 - 0.1 + 0.02, mark_z, 0, 0, 0, 255);
	draw_line_f3(esContext, x1, y1 - 0.1, mark_z, x1 + 0.02, y1 - 0.1 + 0.02, mark_z, 0, 0, 0, 255);
	// View-Line
	draw_line_f3(esContext, x1, y1 - 10.0, mark_z, x1, y1, mark_z, 255, 255, 255, 128);
	// Position
	draw_circle_f3(esContext, x1, y1, mark_z, 0.015, 0, 0, 0, 255);
#ifdef SDLGL
	glPopMatrix();
#endif
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -mapdata->offset_x1, mapdata->offset_y1, 0.0 );
	}
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_line_f3(esContext, x1, y1, 0.0, x1, y1, mark_z, 0, 0, 255, 255);
#ifdef SDLGL
	glPopMatrix();
#endif
}




/* http://www.movable-type.co.uk/scripts/latlong.html */
/* http://www.kompf.de/gps/distcalc.html */
void get_dir (float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to, float *angle, float *dist1, float *angle_up, float *dist2) {
	/* Alt - Diff */
	float alt = alt_to - alt_from;
	/* Bearing/Heading/Richtung */
	float heading = toDeg(atan2(cos(toRad(lat_from)) * sin(toRad(lat_to)) - sin(toRad(lat_from)) * cos(toRad(lat_to)) * cos(toRad(lon_to) - toRad(lon_from)), sin(toRad(lon_to) - toRad(lon_from)) * cos(toRad(lat_to)))) + 270.0;
	if (heading > 360.0) {
		heading -= 360.0;
	}
	heading = 360.0 - heading;
	/* Distance - Grund */
	float distance1 =   acos(
		cos(toRad( lat_from ))
		* cos(toRad(lat_to))
		* cos(toRad(lon_from) - toRad(lon_to))
		+ sin(toRad(lat_from))
		* sin(toRad(lat_to))
	) * 6378.137;
	/* Distance - Sichtverbindung */
	float distance2 = sqrt(((distance1 * 1000) * (distance1 * 1000)) + (alt * alt));
	*angle = heading;
	*dist1 = distance1;
	*dist2 = distance2;
	/* Steigung */
	*angle_up = (asin(alt / distance2)) * 180 / PI;
}







void winkel_line (ESContext *esContext, float x_origin, float y_origin, float winkel, float r1, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float *nx1, float *ny1) {
	float angle = toRad((winkel + 90.0) * -1.0);
	float x1 = r1 * cos(angle);
	float y1 = r1 * sin(angle);
	draw_line_f(esContext, x_origin, y_origin, x_origin - x1, y_origin + y1, r, g, b, a);
	*nx1 = x_origin - x1;
	*ny1 = y_origin + y1;
}

void mark_route (ESContext *esContext, float last_lat, float last_long, float last_alt, float mark_lat, float mark_long, float mark_alt, int8_t type, float lat, float lon, uint8_t zoom) {
	int mark_x = long2x(last_long, lon, zoom);
	int mark_y = lat2y(last_lat, lat, zoom);
	float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	mark_x = long2x(mark_long, lon, zoom);
	mark_y = lat2y(mark_lat, lat, zoom);
	float x2 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y2 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	float mark_z = mark_alt / alt_zoom;
	float last_z = last_alt / alt_zoom;
	float z1 = (float)get_altitude(last_lat, last_long) / alt_zoom;
	float z2 = (float)get_altitude(mark_lat, mark_long) / alt_zoom;
	if (map_view == 0) {
		last_z = 0.001;
		mark_z = 0.001;
	}
	glLineWidth(3);
	if (type == -1) {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 255, 255, 255, 64);
	} else if (type == 1) {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 255, 0, 0, 128);
	} else if (type == 4) {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 0, 255, 255, 128);
	} else if (type == 5) {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 255, 255, 0, 128);
	} else if (type == 6) {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 255, 0, 0, 255);
	} else {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 255, 255, 255, 255);
	}
	if (map_view == 0) {
		z1 = 0.0;
		z2 = 0.0;
	}
	if (type != 4 && type != 5) {
		draw_triaFilled_f3(esContext, x1, y1, z1, x2, y2, z2, x2, y2, mark_z, 255, 255, 255, 127);
		draw_triaFilled_f3(esContext, x1, y1, last_z, x1, y1, z1, x2, y2, mark_z, 255, 255, 255, 127);
	}
	if (type == 1) {
		draw_line_f3(esContext, x1, y1, z1, x2, y2, z2, 255, 0, 0, 255);
	} else if (type == 2) {
		draw_line_f3(esContext, x1, y1, z1, x2, y2, z2, 255, 0, 255, 128);
	} else if (type == 4) {
	} else if (type == 6) {
		draw_line_f3(esContext, x1, y1, z1, x2, y2, z2, 255, 0, 0, 255);
	} else {
		draw_line_f3(esContext, x1, y1, z1, x2, y2, z2, 255, 255, 0, 255);
	}
	glLineWidth(1);
}

void mark_tunnel (ESContext *esContext, float last_lat, float last_long, float last_alt, float mark_lat, float mark_long, float mark_alt, uint8_t type, float lat, float lon, uint8_t zoom) {
	int mark_x = long2x(last_long, lon, zoom);
	int mark_y = lat2y(last_lat, lat, zoom);
	float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	mark_x = long2x(mark_long, lon, zoom);
	mark_y = lat2y(mark_lat, lat, zoom);
	float x2 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y2 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	float mark_z = mark_alt / alt_zoom;
	float last_z = last_alt / alt_zoom;
	draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 0, 255, 255, 255);
	float nx1 = 0.0;
	float ny1 = 0.0;
	float nx2 = 0.0;
	float ny2 = 0.0;
	float mx1 = 0.0;
	float my1 = 0.0;
	float mx2 = 0.0;
	float my2 = 0.0;
	next_point(x1, y1, ModelData[ModelActive].yaw, 0.001, &nx1, &ny1);
	next_point(x2, y2, ModelData[ModelActive].yaw, 0.001, &nx2, &ny2);
	next_point(x1, y1, ModelData[ModelActive].yaw - 180.0, 0.001, &mx1, &my1);
	next_point(x2, y2, ModelData[ModelActive].yaw - 180.0, 0.001, &mx2, &my2);
	draw_line_f3(esContext, nx1, ny1, last_z - 0.0006, nx2, ny2, mark_z, 0, 255, 255, 127);
	draw_line_f3(esContext, nx1, ny1, last_z + 0.0006, nx2, ny2, mark_z, 0, 255, 255, 127);
	draw_line_f3(esContext, nx1, ny1, last_z - 0.0006, nx1, ny1, last_z + 0.0006, 0, 255, 255, 127);
	draw_line_f3(esContext, mx1, my1, last_z - 0.0006, mx2, my2, mark_z, 0, 255, 255, 127);
	draw_line_f3(esContext, mx1, my1, last_z + 0.0006, mx2, my2, mark_z, 0, 255, 255, 127);
	draw_line_f3(esContext, mx1, my1, last_z - 0.0006, mx1, my1, last_z + 0.0006, 0, 255, 255, 127);
	draw_line_f3(esContext, nx1, ny1, last_z - 0.0006, mx1, my1, last_z - 0.0006, 0, 255, 255, 127);
	draw_line_f3(esContext, nx1, ny1, last_z + 0.0006, mx1, my1, last_z + 0.0006, 0, 255, 255, 127);
	uint8_t nn = 0;
	for (nn = 0; nn < 10; nn++) {
		float sx1 = nx1 + (nx2 - nx1) / 400.0 * (float)nn;
		float sy1 = ny1 + (ny2 - ny1) / 400.0 * (float)nn;
		float sx2 = mx1 + (mx2 - mx1) / 400.0 * (float)nn;
		float sy2 = my1 + (my2 - my1) / 400.0 * (float)nn;
		float sz = last_z + (mark_z - last_z) / 400.0 * (float)nn;
		draw_line_f3(esContext, sx1, sy1, sz - 0.0006, sx1, sy1, sz + 0.0006, 0, 255, 255, 127);
		draw_line_f3(esContext, sx2, sy2, sz - 0.0006, sx2, sy2, sz + 0.0006, 0, 255, 255, 127);
		draw_line_f3(esContext, sx1, sy1, sz - 0.0006, sx2, sy2, sz - 0.0006, 0, 255, 255, 127);
		draw_line_f3(esContext, sx1, sy1, sz + 0.0006, sx2, sy2, sz + 0.0006, 0, 255, 255, 127);
	}
}

void mark_plane (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, char *text, float lat, float lon, uint8_t zoom) {
	int mark_x = long2x(mark_long, lon, zoom);
	int mark_y = lat2y(mark_lat, lat, zoom);
	float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	float z = 0.0;
	if (map_view == 1) {
		z = mark_alt / alt_zoom;
	}
	draw_text_f3(esContext, x1, y1, z, 0.03, 0.03, FONT_GREEN, text);
	draw_circleFilled_f3(esContext, x1, y1, z, 0.01, 255, 255, 0, 255);
}

void mark_point (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, char *text, char *command, uint8_t type, float radius, float orbit, float lat, float lon, uint8_t zoom) {
	char tmp_str[1024];
	int mark_x = long2x(mark_long, lon, zoom);
	int mark_y = lat2y(mark_lat, lat, zoom);
	float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	float z = 0.0;
	float z2 = 0.0;
	if (map_view == 1) {
		z = mark_alt / alt_zoom;
		z2 = (float)get_altitude(mark_lat, mark_long) / alt_zoom;
	}
	if (type == 1) {
		draw_circle_f3(esContext, x1, y1, z, 0.03, 255, 0, 0, 255);
	} else if (type == 2) {
		draw_circle_f3(esContext, x1, y1, z, 0.035, 0, 0, 255, 255);
	} else if (type == 3) {
		draw_circle_f3(esContext, x1, y1, z, 0.035, 0, 0, 255, 255);
		draw_circle_f3(esContext, x1, y1, z, 0.03, 255, 0, 0, 255);
	} else if (type == 5) {
		draw_circleFilled_f3(esContext, x1, y1, z2, 0.01, 0, 255, 0, 255);
		return;
	} else if (type == 6) {
		draw_circleFilled_f3(esContext, x1, y1, z2, 0.01, 0, 255, 255, 127);
		return;
	} else if (type == 7) {
		draw_circleFilled_f3(esContext, x1, y1, z2, 0.01, 255, 255, 0, 127);
		return;
	}

	if (strcmp(command, "RTL") == 0) {
		draw_text_f3(esContext, x1, y1, z, 0.05, 0.05, FONT_GREEN, "RTL");
	} else if (strcmp(command, "TAKEOFF") == 0) {
		draw_text_f3(esContext, x1, y1, z, 0.05, 0.05, FONT_GREEN, "TAKEOFF");
	} else if (strcmp(command, "LAND") == 0) {
		draw_text_f3(esContext, x1, y1, z, 0.05, 0.05, FONT_GREEN, "LAND");
	} else if (strcmp(command, "SET_ROI") == 0) {
		draw_text_f3(esContext, x1, y1, z, 0.05, 0.05, FONT_PINK, "POI");
	} else if (strcmp(command, "SHUTTER") == 0) {
		draw_text_f3(esContext, x1, y1, z, 0.05, 0.05, FONT_PINK, "SHUTTER");
	} else {

#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(x1, -y1, 0.0);
//		glRotatef(-roty, 0.0, 0.0, 1.0);

		draw_text_f3(esContext, 0.0, 0.0, z, 0.05, 0.05, FONT_GREEN, text);

		draw_zylinder_f3(esContext, 0.0, 0.0, z2, z2 + 0.01, 0.01, 255, 0, 0, 255);
		draw_line_f3(esContext, 0.0, 0.0, z, 0.0, 0.0, z2, 0, 255, 0, 255);
		draw_zylinder_f3(esContext, 0.0, 0.0, z + 0.01, z, 0.01, 255, 0, 0, 255);

		draw_circle_f3(esContext, 0.0, 0.0, z, radius / 200.0, 0, 255, 0, 128);
		if (orbit != 0.0) {
			draw_circle_f3(esContext, 0.0, 0.0, z, orbit / 200.0, 0, 0, 255, 128);
			static float rotate = 0.0;
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glRotatef(rotate++, 0.0, 0.0, 1.0);
//			draw_circleFilled_f3(esContext, 0.0 + orbit / 200.0, 0.0, z, 0.01, 255, 0, 0, 255);
			draw_zylinder_f3(esContext, 0.0 + orbit / 200.0, 0.0, z + 0.01, z, 0.01, 255, 0, 0, 255);
			draw_zylinder_f3(esContext, 0.0 + orbit / 200.0, 0.0, z - 0.01, z, 0.01, 255, 0, 0, 255);

			if (orbit < 0.0) {
				rotate -= 2.0;
			} else {
				rotate += 2.0;
			}
			glPopMatrix();
			sprintf(tmp_str, "Orbit=%0.1f", orbit);
			draw_text_f3(esContext, 0.01, 0.05, z, 0.05, 0.05, FONT_GREEN, tmp_str);
		} else {
			draw_text_f3(esContext, 0.01, 0.05, z, 0.05, 0.05, FONT_GREEN, command);
		}

		glPopMatrix();
#else
		draw_text_f3(esContext, x1, y1, z, 0.05, 0.05, FONT_GREEN, text);
		draw_circleFilled_f3(esContext, x1, y1, z2, 0.01, 255, 0, 0, 255);
		draw_line_f3(esContext, x1, y1, z, x1, y1, z2, 0, 255, 0, 255);
		draw_circleFilled_f3(esContext, x1, y1, z, 0.01, 255, 0, 0, 255);
		draw_circle_f3(esContext, x1, y1, z, radius / 200.0, 0, 255, 0, 128);
		if (orbit != 0.0) {
			draw_circle_f3(esContext, x1, y1, z, orbit / 200.0, 0, 0, 255, 128);
			sprintf(tmp_str, "Orbit=%0.1f", orbit);
			draw_text_f3(esContext, x1, y1 + 0.05, z, 0.05, 0.05, FONT_GREEN, tmp_str);
		} else {
			draw_text_f3(esContext, x1, y1 + 0.05, z, 0.05, 0.05, FONT_GREEN, command);
		}
#endif
	}
}

void mark_poi (ESContext *esContext, float mark_lat, float mark_long, char *text, uint8_t type, float lat, float lon, uint8_t zoom) {
	int mark_x = long2x(mark_long, lon, zoom);
	int mark_y = lat2y(mark_lat, lat, zoom);
	float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	float z2 = (float)get_altitude(mark_lat, mark_long) / alt_zoom;
	if (type == 1) {
		char tmp_str[1024];
		sprintf(tmp_str, "%s/textures/poi_airport.png", BASE_DIR);
		draw_image_f3(esContext, x1 - 0.03, y1 - 0.03, x1 + 0.03, y1 + 0.03, z2, tmp_str);
	} else if (type == 2) {
		draw_circle_f3(esContext, x1, y1, z2, 0.03, 0, 255, 0, 255);
	} else {
		draw_circle_f3(esContext, x1, y1, z2, 0.03, 0, 0, 255, 255);
	}
	draw_text_f3(esContext, x1, y1, z2, 0.04, 0.04, FONT_GREEN, text);
}

float get_distance (float from_lat, float from_lon, float to_lat, float to_lon, float alt) {
	// 6378.137 == Radius of earth in Km (add UAV-Altitude to calc ???)
	float distance = acos( 
		cos(toRad(from_lat))
		* cos(toRad(to_lat))
		* cos(toRad(from_lon) - toRad(to_lon))
		+ sin(toRad(from_lat)) 
		* sin(toRad(to_lat))
	) * 6378.137 * 1000.0 + alt;
	return distance;
}

float get_m_per_pixel (float lat, int zoomlevel) {
	float m = 0.0;
	m = (6372798.2 * 2 * M_PI) * cos(toRad(lat)) / pow(2, (zoomlevel + 8));
	return m;
}


void GeoMap_exit (GeoMap *mapdata) {
	if (mapdata->sdl_thread_get_maps1 != NULL) {
		SDL_Log("map: wait thread (get_maps1)\n");
	}
	if (mapdata->sdl_thread_get_maps2 != NULL) {
		SDL_Log("map: wait thread (get_maps2)\n");
	}
	mapdata->mapthread_running = 0;
	if (mapdata->sdl_thread_get_maps1 != NULL) {
		SDL_WaitThread(mapdata->sdl_thread_get_maps1, NULL);
		mapdata->sdl_thread_get_maps1 = NULL;
	}
	if (mapdata->sdl_thread_get_maps2 != NULL) {
		SDL_WaitThread(mapdata->sdl_thread_get_maps2, NULL);
		mapdata->sdl_thread_get_maps2 = NULL;
	}
	free(mapdata);
	mapdata = NULL;
}

GeoMap *GeoMap_init (void) {
	int16_t n = 0;
	GeoMap *mapdata = NULL;
	mapdata = malloc(sizeof(GeoMap));
	mapdata->esContext = NULL;
	mapdata->lat = 50.29;
	mapdata->lon = 9.12;
	mapdata->zoom = 16;
	mapdata->map_view = 0;
	mapdata->draw_tiles = 1;
	mapdata->alpha0 = 1.0;
	mapdata->alpha1 = 1.0;
	mapdata->alpha2 = 1.0;
	mapdata->grid = 1.0;
	mapdata->map_color = 0;
	mapdata->offset_x1 = 0.0;
	mapdata->offset_y1 = 0.0;

	char map_setup_file[1024];
	sprintf(map_setup_file, "%s/map-services.xml", BASE_DIR);
	map_parseDoc(map_setup_file);
	for (n = 0; n < MAX_POIS; n++) {
		POIs[n].name[0] = 0;
		POIs[n].p_lat = 0.0;
		POIs[n].p_long = 0.0;
		POIs[n].type = 0;
	}
	strcpy(POIs[0].name, "Startpukt 1");
	POIs[0].p_lat = 50.54875565;
	POIs[0].p_long = 9.67414856;
	POIs[0].type = 0;
	strcpy(POIs[1].name, "Startpukt 2");
	POIs[1].p_lat = 50.43736267;
	POIs[1].p_long = 9.20448303;
	POIs[1].type = 1;


	mapdata->mapthread_running = 1;
	SDL_Log("map: init thread (get_maps1)\n");
#ifdef SDL2
	mapdata->sdl_thread_get_maps1 = SDL_CreateThread(thread_get_maps1, NULL, (void *)mapdata);
#else
	mapdata->sdl_thread_get_maps1 = SDL_CreateThread(thread_get_maps1, (void *)mapdata);
#endif
	if (mapdata->sdl_thread_get_maps1 == NULL) {
		fprintf(stderr, "map: Unable to create thread_get_maps1: %s\n", SDL_GetError());
	}
	SDL_Log("map: init thread (get_maps2)\n");
#ifdef SDL2
	mapdata->sdl_thread_get_maps2 = SDL_CreateThread(thread_get_maps2, NULL, (void *)mapdata);
#else
	mapdata->sdl_thread_get_maps2 = SDL_CreateThread(thread_get_maps2, (void *)mapdata);
#endif
	if (mapdata->sdl_thread_get_maps2 == NULL) {
		fprintf(stderr, "map: Unable to create thread_get_maps2: %s\n", SDL_GetError());
	}
	return mapdata;
}

void GeoMap_draw (GeoMap *mapdata) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = GlobalesContext->userData;
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply( &userData->mvpMatrix, &modelview, &userData->perspective );
	esMatrixMultiply( &userData->mvpMatrix2, &modelview, &userData->perspective );
#endif


	// calculate Altitude-Zoom
	uint32_t zz = (1<<mapdata->zoom);
	alt_zoom = 25500000 / (float)zz;
	int tile_x = long2tilex(mapdata->lon, mapdata->zoom);
	int tile_y = lat2tiley(mapdata->lat, mapdata->zoom);
	int x_n = 0;
	int y_n = 0;
	char tile_name[1024];
	uint8_t tiles_x = (setup.screen_w + 255) / 256;
	uint8_t tiles_y = (setup.screen_h + 255) / 256;
	uint8_t tiles_num = 0;


	// move map offset
	if (mapdata->map_view != 1 && mapdata->map_view != 3 && mapdata->map_view != 4 && mapdata->map_view != 5) {
		esTranslate( &modelview, -mapdata->offset_x1, mapdata->offset_y1, 0.0 );
	}
#ifndef SDLGL
	esMatrixMultiply( &userData->mvpMatrix, &modelview, &userData->perspective );
	esMatrixMultiply( &userData->mvpMatrix2, &modelview, &userData->perspective );
#endif
	// draw Sky in 3D-Mode
	if (setup.hud_view_video == 0) {
		if (mapdata->map_view == 3 || mapdata->map_view == 5) {
			draw_box_f3c2(mapdata->esContext, -3.0, -3.0, -1.0, 3.0, -3.0, 3.0, 0x01, 0x8e, 0xea, 255, 0x01, 0x8e, 0xea, 255);
			draw_box_f3c2(mapdata->esContext, -3.0, 3.0, -1.0, 3.0, 3.0, 3.0, 0x01, 0x8e, 0xea, 255, 0x01, 0x8e, 0xea, 255);
			draw_box_f3c2b(mapdata->esContext, -3.0, -3.0, -1.0, -3.0, 3.0, 3.0, 0x01, 0x8e, 0xea, 255, 0x01, 0x8e, 0xea, 255);
			draw_box_f3c2b(mapdata->esContext, 3.0, -3.0, -1.0, 3.0, 3.0, 3.0, 0x01, 0x8e, 0xea, 255, 0x01, 0x8e, 0xea, 255);
			draw_box_f3(mapdata->esContext, -3.0, -3.0, 3.0, 3.0, 3.0, 3.0, 0x01, 0x8e, 0xea, 255);
		}
	}
	// draw Titles
	if (mapdata->zoom <= 18 && mapdata->map_view != 4) {
		for (y_n = -MAP_OVERLAY; y_n < tiles_y + MAP_OVERLAY; y_n++) {
			for (x_n = -MAP_OVERLAY; x_n < tiles_x + MAP_OVERLAY; x_n++) {
				float _grid = mapdata->grid;
				if (strncmp(mapnames[map_type][MAP_URL], "file:/", 6) == 0) {
					if (strcmp(mapnames[map_type][MAP_TYPE], "ZYX") == 0) {
						sprintf(tile_name, mapnames[map_type][MAP_URL] + 6, mapdata->zoom, tile_y + y_n, tile_x + x_n);
					} else if (strcmp(mapnames[map_type][MAP_TYPE], "ZXY") == 0) {
						sprintf(tile_name, mapnames[map_type][MAP_URL] + 6, mapdata->zoom, tile_x + x_n, tile_y + y_n);
					} else if (strcmp(mapnames[map_type][MAP_TYPE], "XYZ") == 0) {
						sprintf(tile_name, mapnames[map_type][MAP_URL] + 6, tile_x + x_n, tile_y + y_n, mapdata->zoom);
					} else if (strcmp(mapnames[map_type][MAP_TYPE], "TMS") == 0) {
						int ymax = (1<<mapdata->zoom);
						int y = ymax - (tile_y + y_n) - 1;
						sprintf(tile_name, mapnames[map_type][MAP_URL] + 6, mapdata->zoom, tile_x + x_n, y);
					}
				} else {
					sprintf(tile_name, mapnames[map_type][MAP_FILE], get_datadirectory(), mapdata->zoom, tile_x + x_n, tile_y + y_n);
				}
				if (file_exists(tile_name) == 0) {
					tile_name[0] = 0;
					_grid = 1.0;
				}
				if (mapdata->draw_tiles == 0) {
					tile_name[0] = 0;
				}
				if (mapdata->alpha1 == 0.0 && mapdata->alpha2 == 0.0 && mapdata->map_color == 1) {
					mapdata->alpha1 = 0.5;
					mapdata->alpha2 = 0.5;
				}
				if (mapdata->map_view == 3 || mapdata->map_view == 4 || mapdata->map_view == 5) {
					draw_image_srtm(mapdata->esContext, x_n * 256, y_n * 256, 256, 256, tile_name, tiley2lat(tile_y + y_n, mapdata->zoom), tilex2long(tile_x + x_n, mapdata->zoom), tiley2lat(tile_y + y_n + 1, mapdata->zoom), tilex2long(tile_x + x_n + 1, mapdata->zoom), mapdata->alpha0, mapdata->alpha1, mapdata->alpha2, _grid);
				} else if (mapdata->map_view == 1) {
					draw_image_srtm(mapdata->esContext, x_n * 256, y_n * 256, 256, 256, tile_name, tiley2lat(tile_y + y_n, mapdata->zoom), tilex2long(tile_x + x_n, mapdata->zoom), tiley2lat(tile_y + y_n + 1, mapdata->zoom), tilex2long(tile_x + x_n + 1, mapdata->zoom), mapdata->alpha0, mapdata->alpha1, mapdata->alpha2, _grid);
				} else {
					if (tile_name[0] != 0) {
						draw_image(mapdata->esContext, x_n * 256, y_n * 256, 256, 256, tile_name);
					} else {
						draw_rect(mapdata->esContext, x_n * 256, y_n * 256, x_n * 256 + 256, y_n * 256 + 256, 255, 255, 255, 255);
					}
				}
				if (mapdata->draw_tiles != 0 && omapnames[omap_type][MAP_FILE][0] != 0) {
					if (strncmp(omapnames[map_type][MAP_URL], "file:/", 6) == 0) {
						if (strcmp(omapnames[map_type][MAP_TYPE], "ZYX") == 0) {
							sprintf(tile_name, omapnames[map_type][MAP_URL] + 6, mapdata->zoom, tile_y + y_n, tile_x + x_n);
						} else if (strcmp(omapnames[map_type][MAP_TYPE], "ZXY") == 0) {
							sprintf(tile_name, omapnames[map_type][MAP_URL] + 6, mapdata->zoom, tile_x + x_n, tile_y + y_n);
						} else if (strcmp(omapnames[map_type][MAP_TYPE], "XYZ") == 0) {
							sprintf(tile_name, omapnames[map_type][MAP_URL] + 6, tile_x + x_n, tile_y + y_n, mapdata->zoom);
						} else if (strcmp(omapnames[map_type][MAP_TYPE], "TMS") == 0) {
							int ymax = (1<<mapdata->zoom);
							int y = ymax - (tile_y + y_n) - 1;
							sprintf(tile_name, omapnames[map_type][MAP_URL] + 6, mapdata->zoom, tile_x + x_n, y);
						}
					} else {
						sprintf(tile_name, omapnames[omap_type][MAP_FILE], get_datadirectory(), mapdata->zoom, tile_x + x_n, tile_y + y_n);
					}
					if (file_exists(tile_name) != 0) {
						if (mapdata->map_view == 1) {
							draw_image_srtm(mapdata->esContext, x_n * 256, y_n * 256, 256, 256, tile_name, tiley2lat(tile_y + y_n, mapdata->zoom), tilex2long(tile_x + x_n, mapdata->zoom), tiley2lat(tile_y + y_n + 1, mapdata->zoom), tilex2long(tile_x + x_n + 1, mapdata->zoom), 0.5, 0.0, 0.0, 0.0);
						} else {
							draw_image(mapdata->esContext, x_n * 256, y_n * 256, 256, 256, tile_name);
						}
					}
				}
				tiles_num++;
			}
		}
	}
}
