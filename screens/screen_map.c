
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <termios.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curl/curl.h>
#include <GL/gl.h>
#include <SDL.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include <model.h>
#include <userdata.h>
#include <main.h>
#include <screen_map.h>
#include <my_mavlink.h>
#include <screen_wpedit.h>

volatile float lat = 50.29;
volatile float lon = 9.12;
volatile uint8_t zoom = 16;
uint8_t map_type = 0;
uint8_t map_type_select = 0;
uint8_t omap_type = 0;
uint8_t omap_type_select = 0;
uint8_t map_view = 0;
uint8_t map_startup = 0;
float offset_x1 = 0.0;
float offset_y1 = 0.0;
uint8_t map_addmode = 0;
float roty = 0.0;
uint8_t uav_active_waypoint = 0;
uint8_t center_map = 0;
uint8_t nav_map = 0;
uint8_t map_show_log = 0;
uint8_t map_show_wp = 0;
uint8_t map_show_notam = 0;
uint8_t map_show_poi = 0;
uint8_t map_rotate = 0;
uint8_t map_side = 1;
uint8_t map_dir = 0;

static uint8_t mapthread_running = 0;

SDL_Thread *sdl_thread_get_maps1;
SDL_Thread *sdl_thread_get_maps2;

//#define HTTP_USE_WGET 1

// Nokia-Maps
// http://2.maps.nlp.nokia.com/maptile/2.1/maptile/d3617790e3/hybrid.day/14/8594/5542/256/png8?lg=ENG&app_id=SqE1xcSngCd3m4a1zEGb&token=r0sR1DzqDkS6sDnh902FWQ&xnlp=CL_JSMv2.5.0.3,SID_B8E4FEB7-98FF-4052-928E-27D45293A80C

// Bing-Maps
// http://ecn.dynamic.t1.tiles.virtualearth.net/comp/ch/120203302111?mkt=de-de&it=A,G,L&shading=hill


uint8_t maplen = 0;
uint8_t omaplen = 0;

char mapnames[20][4][200];
char omapnames[20][4][200];

PointOfInterest POIs[MAX_POIS];

static void die(char *msg) {
	printf("map: %s", msg);
	return;
}

void map_parseMapService (xmlDocPtr doc, xmlNodePtr cur, uint8_t map_service) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(mapnames[map_service][MAP_NAME], (char *)key);
			} else {
				mapnames[map_service][MAP_NAME][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"url"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(mapnames[map_service][MAP_URL], (char *)key);
			} else {
				mapnames[map_service][MAP_URL][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"file"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(mapnames[map_service][MAP_FILE], (char *)key);
			} else {
				mapnames[map_service][MAP_FILE][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"type"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(mapnames[map_service][MAP_TYPE], (char *)key);
			} else {
				mapnames[map_service][MAP_TYPE][0] = 0;
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

void map_parseOverlayMapService (xmlDocPtr doc, xmlNodePtr cur, uint8_t omap_service) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(omapnames[omap_service][MAP_NAME], (char *)key);
			} else {
				omapnames[omap_service][MAP_NAME][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"url"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(omapnames[omap_service][MAP_URL], (char *)key);
			} else {
				omapnames[omap_service][MAP_URL][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"file"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(omapnames[omap_service][MAP_FILE], (char *)key);
			} else {
				omapnames[omap_service][MAP_FILE][0] = 0;
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"type"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strcpy(omapnames[omap_service][MAP_TYPE], (char *)key);
			} else {
				omapnames[omap_service][MAP_TYPE][0] = 0;
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

static void map_parseDoc (char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
//	xmlChar *key;
	maplen = 0;
	omaplen = 0;
	doc = xmlParseFile(docname);
	if (doc == NULL) {
		printf("map: Document parsing failed: %s\n", docname);
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		die("Document is Empty!!!\n");
		return;
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"service"))) {
			map_parseMapService (doc, cur, maplen++);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"overlay_service"))) {
			map_parseOverlayMapService (doc, cur, omaplen++);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}


void map_exit (void) {
	if (sdl_thread_get_maps1 != NULL) {
		printf("map: wait thread (get_maps1)\n");
	}
	if (sdl_thread_get_maps2 != NULL) {
		printf("map: wait thread (get_maps2)\n");
	}
	mapthread_running = 0;
	if (sdl_thread_get_maps1 != NULL) {
		SDL_WaitThread(sdl_thread_get_maps1, NULL);
		sdl_thread_get_maps1 = NULL;
	}
	if (sdl_thread_get_maps2 != NULL) {
		SDL_WaitThread(sdl_thread_get_maps2, NULL);
		sdl_thread_get_maps2 = NULL;
	}
}

int file_exists (char *fileName) {
	struct stat buf;
	int i = stat ( fileName, &buf );
	if ( i == 0 ) {
		return 1;
	}
	return 0;
}

int file_download (char *fileName, char *url) {
	char tmp_file[4024];
	sprintf(tmp_file, "%s.tmp", fileName);
#ifdef HTTP_USE_WGET
	char tmp_cmd[4024];
	sprintf(tmp_cmd, "wget -q -O %s \"%s\"", tmp_file, url);
	system(tmp_cmd);
#else
	CURL *curl_handle;
	FILE *bodyfile;
	bodyfile = fopen(tmp_file,"w");
	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT , "Map-Viewer Dev-0.01");
	if (bodyfile == NULL) {
		curl_easy_cleanup(curl_handle);
		return -1;
	}
	curl_easy_perform(curl_handle);
	fclose(bodyfile);
	curl_easy_cleanup(curl_handle);
#endif
	rename(tmp_file, fileName);
	return 0;
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
//		printf("map: __ %i __\n", digit);
		quadKey[n++] = (digit + 48);
		quadKey[n] = 0;
	}
	return quadKey;
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
		for (y_n = 0; y_n < tiles_y && mapthread_running == 1; y_n++) {
			for (x_n = 0; x_n < tiles_x && mapthread_running == 1; x_n++) {
				if (strcmp(mapnames[map_type][MAP_TYPE], "GOOGLE") == 0) {
					sprintf(tile_name, "%s/MAPS/google_%i_%i_%i.png", BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
					if (file_exists(tile_name) == 0) {
						/* Google-Maps */
						google_tile_long1 = tilex2long(tile_x + x_n, zoom);
						google_tile_long2 = tilex2long(tile_x + x_n + 1, zoom);
						google_tile_long = google_tile_long1 + (google_tile_long2 - google_tile_long1) / 2;
						google_tile_lat = tiley2lat(tile_y + y_n + 1, zoom);

						sprintf(tile_name, "%s/MAPS/tobig_google_%i_%i_%i.png", BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
						sprintf(tile_url, mapnames[map_type][MAP_URL], google_tile_lat, google_tile_long, zoom, 256, 356);
						printf("map: %s -> %s\n", tile_url, tile_name);
						file_download(tile_name, tile_url);
						// Crop map-image for titles
						sprintf(tmp_str2, mapnames[map_type][MAP_FILE], BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
						sprintf(tmp_str, "convert -crop 256x256+0+50 %s %s", tile_name, tmp_str2);
						system(tmp_str);
					}
				} else {
					if (zoom <= 18) {
						sprintf(tile_name, mapnames[map_type][MAP_FILE], BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
						if (file_exists(tile_name) == 0) {
							if (strcmp(mapnames[map_type][MAP_TYPE], "ZYX") == 0) {
								sprintf(tile_url, mapnames[map_type][MAP_URL], zoom, tile_y + y_n, tile_x + x_n);
							} else if (strcmp(mapnames[map_type][MAP_TYPE], "ZXY") == 0) {
								sprintf(tile_url, mapnames[map_type][MAP_URL], zoom, tile_x + x_n, tile_y + y_n);
							} else if (strcmp(mapnames[map_type][MAP_TYPE], "XYZ") == 0) {
								sprintf(tile_url, mapnames[map_type][MAP_URL], tile_x + x_n, tile_y + y_n, zoom);
							} else if (strcmp(mapnames[map_type][MAP_TYPE], "BING") == 0) {
								char quadKey[100];
								sprintf(tile_url, mapnames[map_type][MAP_URL], BingtileXYZToQuadKey(quadKey, tile_x + x_n, tile_y + y_n, zoom));
							}
							printf("map: %s -> %s\n", tile_url, tile_name);
							file_download(tile_name, tile_url);
						}
					}
				}
			}
		}
	}
}

uint8_t map_downloader (char *name, float x, float y, int8_t button, float data) {
	uint8_t zoom = 0;
	float lat = 50.2;
	float lon = 9.0;

/*
DE:
	47.0 -> 57.0, 5.8 -> 15.3
*/

	for (zoom = 10; zoom < 18; zoom++) {
		download_map_range(lat, lon, lat + 0.5, lon + 0.5, zoom);
	}

//	download_map_range(47.0, 5.7, 57.0, 15.4, 11);
//	download_map_range(47.0, 5.7, 57.0, 15.4, 10);


	return 0;
}

void get_maps (uint8_t mode) {
	int tile_x = long2tilex(lon, zoom);
	int tile_y = lat2tiley(lat, zoom);
	int x_n = 0;
	int y_n = 0;
	char tile_name[2024];
	char tile_url[2024];
	char tmp_str[2024];
	char tmp_str2[2024];
	char status_txt[2024];
	uint8_t tiles_x = (screen_w + 255) / 256;
	uint8_t tiles_y = (screen_h + 255) / 256;
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
	if (zoom <= 18) {
		for (overlay = 0; overlay <= MAP_OVERLAY && mapthread_running == 1; overlay++) {
			for (y_n = -overlay + start; y_n < tiles_y + overlay && mapthread_running == 1; y_n += step) {
				for (x_n = -overlay; x_n < tiles_x + overlay && mapthread_running == 1; x_n += 1) {
					if (lat_last[mode] != lat || lon_last[mode] != lon || zoom_last[mode] != zoom) {
						lat_last[mode] = lat;
						lon_last[mode] = lon;
						zoom_last[mode] = zoom;
						return;
					}
					if (strcmp(mapnames[map_type][MAP_TYPE], "GOOGLE") == 0) {
						sprintf(tile_name, "%s/MAPS/google_%i_%i_%i.png", BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
						if (file_exists(tile_name) == 0) {
							sprintf(status_txt, "getting map-tile: %i_%i_%i.png (%i/%i)", zoom, tile_x + x_n, tile_y + y_n, tiles_num + 1, tiles_need);
							printf("map: %s\n", status_txt);
							/* Google-Maps */
							google_tile_long1 = tilex2long(tile_x + x_n, zoom);
							google_tile_long2 = tilex2long(tile_x + x_n + 1, zoom);
							google_tile_long = google_tile_long1 + (google_tile_long2 - google_tile_long1) / 2;
							google_tile_lat = tiley2lat(tile_y + y_n + 1, zoom);
							sprintf(tile_name, "%s/MAPS/tobig_google_%i_%i_%i.png", BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
							sprintf(tile_url, mapnames[map_type][MAP_URL], google_tile_lat, google_tile_long, zoom, 256, 356);
							printf("map: %s -> %s\n", tile_url, tile_name);
							file_download(tile_name, tile_url);
							// Crop map-image for titles
							sprintf(tmp_str2, "%s/MAPS/google_%i_%i_%i.png", BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
							sprintf(tmp_str, "convert -crop 256x256+0+50 %s %s", tile_name, tmp_str2);
							system(tmp_str);
						}
					} else {
						if (zoom <= 18) {
							sprintf(tile_name, mapnames[map_type][MAP_FILE], BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
							if (file_exists(tile_name) == 0) {
								sprintf(status_txt, "getting map-tile: %s", tile_name);
								sys_message(status_txt);
								printf("map: %s\n", status_txt);
								if (strcmp(mapnames[map_type][MAP_TYPE], "ZYX") == 0) {
									sprintf(tile_url, mapnames[map_type][MAP_URL], zoom, tile_y + y_n, tile_x + x_n);
								} else if (strcmp(mapnames[map_type][MAP_TYPE], "ZXY") == 0) {
									sprintf(tile_url, mapnames[map_type][MAP_URL], zoom, tile_x + x_n, tile_y + y_n);
								} else if (strcmp(mapnames[map_type][MAP_TYPE], "XYZ") == 0) {
									sprintf(tile_url, mapnames[map_type][MAP_URL], tile_x + x_n, tile_y + y_n, zoom);
								} else if (strcmp(mapnames[map_type][MAP_TYPE], "BING") == 0) {
									char quadKey[100];
									sprintf(tile_url, mapnames[map_type][MAP_URL], BingtileXYZToQuadKey(quadKey, tile_x + x_n, tile_y + y_n, zoom));
								}
								printf("map: %s -> %s\n", tile_url, tile_name);
								file_download(tile_name, tile_url);
							}
						}
					}
					if (omapnames[omap_type][MAP_FILE][0] != 0) {
						sprintf(tile_name, omapnames[omap_type][MAP_FILE], BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
						if (file_exists(tile_name) == 0) {
							sprintf(tmp_str2, "%s_org.png", tile_name);
							sprintf(tile_url, omapnames[omap_type][MAP_URL], zoom, tile_x + x_n, tile_y + y_n);
							printf("map: %s -> %s\n", tile_url, tmp_str2);
							file_download(tmp_str2, tile_url);
							sprintf(tmp_str, "convert -channel Alpha -evaluate Divide 2 %s %s.tmp.png", tmp_str2, tile_name);
							system(tmp_str);
							sprintf(tmp_str, "mv %s.tmp.png %s", tile_name, tile_name);
							system(tmp_str);
						}
					}
					tiles_num++;
				}
			}
		}
	}
	if (strcmp(mapnames[map_type][MAP_NAME], "GAPI") == 0 || strcmp(mapnames[map_type][MAP_TYPE], "GOOGLE") == 0) {
		sprintf(tile_name, "%s/MAPS/google.png", BASE_DIR);
		sprintf(tile_url, "http://maps.gstatic.com/intl/de_ALL/mapfiles/poweredby.png");
		if (file_exists(tile_name) == 0) {
			file_download(tile_name, tile_url);
		}
	}
}

void get_srtm (void) {
	char file[256];
	char file2[256];
	int8_t lat_m = (int)lat;
	int8_t lon_m = (int)lon;
	sprintf(file, "N%02iE%03i.hgt", lat_m, lon_m);
	sprintf(file2, "%s/MAPS/%s", BASE_DIR, file);
	if (file_exists(file2) == 0) {
		printf("map: getting srtm-data: %s\n", file);
		char cmd_str[1024];
		sprintf(cmd_str, "mkdir -p %s/MAPS/part/ ; wget -q -O %s/MAPS/part/%s.zip http://dds.cr.usgs.gov/srtm/version2_1/SRTM3/Eurasia/%s.zip", BASE_DIR, BASE_DIR, file, file);
		printf("map: %s\n", cmd_str);
		system(cmd_str);
		sprintf(cmd_str, "cd %s/MAPS/part/ ; unzip %s.zip ; rm -rf %s.zip ; mv %s ../", BASE_DIR, file, file, file);
		system(cmd_str);
	}
}

int thread_get_maps1 (void *unused) {
	while (mapthread_running == 1) {
		get_maps(0);
		get_srtm();
		SDL_Delay(100);
	}
	printf("map: exit thread (get_maps1)\n");
	return 0;
}

int thread_get_maps2 (void *unused) {
	while (mapthread_running == 1) {
		get_maps(1);
		SDL_Delay(100);
	}
	printf("map: exit thread (get_maps2)\n");
	return 0;
}


size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
	int written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

uint8_t map_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t map_nav (char *name, float x, float y, int8_t button, float data) {
	nav_map = 1 - nav_map;
	if (nav_map == 1) {
		center_map = 1;
		map_view = 2;
		map_show_wp = 1;
		map_dir = 1;
	}
	return 0;
}

uint8_t map_center (char *name, float x, float y, int8_t button, float data) {
	nav_map = 0;
	if (center_map < 2) {
		center_map++;
	} else {
		center_map = 0;
	}
	return 0;
}

uint8_t map_dir_change (char *name, float x, float y, int8_t button, float data) {
	if (map_dir < 1) {
		map_dir++;
	} else {
		map_dir = 0;
	}
	return 0;
}

uint8_t map_rotate_change (char *name, float x, float y, int8_t button, float data) {
	map_rotate = 1 - map_rotate;
	return 0;
}

uint8_t map_side_change (char *name, float x, float y, int8_t button, float data) {
	map_side = 1 - map_side;
	return 0;
}

uint8_t map_view_change (char *name, float x, float y, int8_t button, float data) {
	nav_map = 0;
	if (map_view < 1) {
		map_view++;
	} else {
		map_view = 0;
	}
	return 0;
}

uint8_t change_maptype (char *name, float x, float y, int8_t button, float data) {
	printf("map: change_maptype\n");
	if (data == -1) {
		map_type_select = 1 - map_type_select;
	} else {
		map_type = (uint8_t)data;
		map_type_select = 0;
	}
	return 0;
}

uint8_t change_omaptype (char *name, float x, float y, int8_t button, float data) {
	printf("map: change_omaptype\n");
	if (data == -1) {
		omap_type_select = 1 - omap_type_select;
	} else {
		omap_type = (uint8_t)data;
		omap_type_select = 0;
	}
	return 0;
}

uint8_t map_zoom (char *name, float x, float y, int8_t button, float data) {
	if (data < 0.0) {
		if (zoom > 0) {
			zoom--;
		}
	} else {
		if (zoom < 18) {
			zoom++;
		}
	}
	return 0;
}

uint8_t show_wp (char *name, float x, float y, int8_t button, float data) {
	if ((int)data == 1) {
		map_show_wp = 1;
	} else {
		map_show_wp = 1 - map_show_wp;
	}
	return 0;
}

uint8_t show_notam (char *name, float x, float y, int8_t button, float data) {
	if ((int)data == 1) {
		map_show_notam = 1;
	} else {
		map_show_notam = 1 - map_show_notam;
	}
	return 0;
}

uint8_t show_poi (char *name, float x, float y, int8_t button, float data) {
	if ((int)data == 1) {
		map_show_poi = 1;
	} else {
		map_show_poi = 1 - map_show_poi;
	}
	return 0;
}

uint8_t show_log (char *name, float x, float y, int8_t button, float data) {
	map_show_log = 1 - map_show_log;
	return 0;
}

uint8_t map_goto (char *name, float x, float y, int8_t button, float data) {
	if (data == -1.0) {
		int tile_y = lat2tiley(ModelData.p_lat, zoom) - 1;
		int tile_x = long2tilex(ModelData.p_long, zoom) - 1;
		lat = tiley2lat(tile_y, zoom);
		lon = tilex2long(tile_x, zoom);
	} else {
		int tile_y = lat2tiley(WayPoints[(int)data].p_lat, zoom) - 1;
		int tile_x = long2tilex(WayPoints[(int)data].p_long, zoom) - 1;
		lat = tiley2lat(tile_y, zoom);
		lon = tilex2long(tile_x, zoom);
	}
	return 0;
}

uint8_t map_uav2home (char *name, float x, float y, int8_t button, float data) {
	ModelData.p_lat = WayPoints[0].p_lat;
	ModelData.p_long = WayPoints[0].p_long;
	ModelData.p_alt = WayPoints[0].p_alt;
	return 0;
}

uint8_t map_export_kml (char *name, float x, float y, int8_t button, float data) {
	// draw log
/*
	if (LogLines != NULL) {
		int r_tim = 0;
		float r_lat = 0.0;
		float r_lon = 0.0;
		float r_alt = 0.0;
		float r_vel = 0.0;
		struct list_element *liste = LogLines;
	        FILE *fr;
		char filename[100];
		sprintf(filename, "%s/%i.kml", BASE_DIR, 0);
	        fr = fopen(filename, "w");
		if (fr != 0) {
			fprintf(fr, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
			fprintf(fr, "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
			fprintf(fr, "  <Document>\n");
//			fprintf(fr, "    <name>%s</name>\n", rctransmitter_name);
			fprintf(fr, "    <description>Flight-Data</description>\n");
			fprintf(fr, "    <Style id=\"yellowLineGreenPoly\">\n");
			fprintf(fr, "      <LineStyle>\n");
			fprintf(fr, "        <color>7f00ffff</color>\n");
			fprintf(fr, "        <width>4</width>\n");
			fprintf(fr, "      </LineStyle>\n");
			fprintf(fr, "      <PolyStyle>\n");
			fprintf(fr, "        <color>7f00ff00</color>\n");
			fprintf(fr, "      </PolyStyle>\n");
			fprintf(fr, "    </Style>\n");
			fprintf(fr, "    <Placemark>\n");
			fprintf(fr, "      <name>Absolute Extruded</name>\n");
			fprintf(fr, "      <description>Datalog</description>\n");
			fprintf(fr, "      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
			fprintf(fr, "      <LineString>\n");
			fprintf(fr, "        <extrude>1</extrude>\n");
			fprintf(fr, "        <tessellate>1</tessellate>\n");
//			fprintf(fr, "        <altitudeMode>absolute</altitudeMode>\n");
			fprintf(fr, "        <altitudeMode>relativeToGround</altitudeMode>\n");
			fprintf(fr, "        <coordinates>\n");
			if (liste->line != NULL) {
				if (strncmp(liste->line, "GPS;", 4) == 0) {
					sscanf(liste->line, "GPS;%i;%f;%f;%f;%f", &r_tim, &r_lat, &r_lon, &r_alt, &r_vel);
					fprintf(fr, "%f, %f, %f\n", r_lon, r_lat, r_alt);
				}
			}
			while (liste->next != NULL) {
				liste=liste->next;
				if (liste->line != NULL) {
					if (strncmp(liste->line, "GPS;", 4) == 0) {
						sscanf(liste->line, "GPS;%i;%f;%f;%f;%f", &r_tim, &r_lat, &r_lon, &r_alt, &r_vel);
						fprintf(fr, "%f, %f, %f\n", r_lon, r_lat, r_alt);
					}
				}
			}
			fprintf(fr, "        </coordinates>\n");
			fprintf(fr, "      </LineString>\n");
			fprintf(fr, "    </Placemark>\n");
			fprintf(fr, "  </Document>\n");
			fprintf(fr, "</kml>\n");

		        fclose(fr);
		} else {
			printf("map: Can not save kml-file: %s\n", filename);
		}
	}
*/
	return 0;
}

uint8_t map_add (char *name, float x, float y, int8_t button, float data) {
	map_addmode = 1 - map_addmode;
	map_show_wp = 1;
	return 0;
}

uint8_t map_del (char *name, float x, float y, int8_t button, float data) {
	uint16_t n = 0;
	uint16_t n2 = waypoint_active + 1;
	for (n = waypoint_active; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[n].p_lat != 0.0) {
			WayPoints[n].p_lat = WayPoints[n2].p_lat;
			WayPoints[n].p_long = WayPoints[n2].p_long;
			WayPoints[n].p_alt = WayPoints[n2].p_alt;
			WayPoints[n].yaw = WayPoints[n2].yaw;
			strcpy(WayPoints[n].name, WayPoints[n2].name);
			strcpy(WayPoints[n].command, WayPoints[n2].command);
			n2++;
		}
	}
	waypoint_active--;
	return 0;
}
 
int long2tilex(float lon, int z)  { 
	return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z))); 
}

int lat2tiley(float lat, int z) { 
	return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z))); 
}

float tilex2long(int x, int z)  {
	return x / pow(2.0, z) * 360.0 - 180;
}

float tiley2lat(int y, int z)  {
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

void draw_quad (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, float roll, float pitch, float yaw, float lat, float lon, uint8_t zoom) {
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

	if (center_map == 2) {
		if (x1 < -0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0);
		}
		if (x1 > 0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0);
		}
		if (y1 < -0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0);
		}
		if (y1 > 0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0);
		}
	}


#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -offset_x1, offset_y1, 0.0 );
	}
#endif
	esTranslate( &modelview, x1, -y1, -2.0 + mark_z);
	esRotate( &modelview, yaw, 0.0, 0.0, 1.0 );
	esRotate( &modelview, roll, 0.0, 1.0, 0.0 );
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

	// Quad
	float size = 0.03;
	draw_line_f3(esContext, x1 - size - 0.003, y1 - size, mark_z, x1 + size - 0.003, y1 + size, mark_z, 0, 0, 0, 255);
	draw_line_f3(esContext, x1 - size + 0.003, y1 - size, mark_z, x1 + size + 0.003, y1 + size, mark_z, 0, 0, 0, 255);
	draw_line_f3(esContext, x1 - size - 0.003, y1 + size, mark_z, x1 + size - 0.003, y1 - size, mark_z, 0, 0, 0, 255);
	draw_line_f3(esContext, x1 - size + 0.003, y1 + size, mark_z, x1 + size + 0.003, y1 - size, mark_z, 0, 0, 0, 255);
	draw_line_f3(esContext, x1 - size, y1 - size, mark_z, x1 + size, y1 + size, mark_z, 255, 0, 0, 255);
	draw_line_f3(esContext, x1 - size, y1 + size, mark_z, x1 + size, y1 - size, mark_z, 255, 0, 0, 255);
	draw_circleFilled_f3(esContext, x1 + size, y1 + size, mark_z, 0.015, 255, 0, 0, 255);
	draw_circleFilled_f3(esContext, x1 - size, y1 + size, mark_z, 0.015, 255, 0, 0, 255);
	draw_circleFilled_f3(esContext, x1 + size, y1 - size, mark_z, 0.015, 0, 255, 0, 255);
	draw_circleFilled_f3(esContext, x1 - size, y1 - size, mark_z, 0.015, 0, 255, 0, 255);
	draw_circle_f3(esContext, x1 + size, y1 + size, mark_z, 0.015, 0, 0, 0, 255);
	draw_circle_f3(esContext, x1 - size, y1 + size, mark_z, 0.015, 0, 0, 0, 255);
	draw_circle_f3(esContext, x1 + size, y1 - size, mark_z, 0.015, 0, 0, 0, 255);
	draw_circle_f3(esContext, x1 - size, y1 - size, mark_z, 0.015, 0, 0, 0, 255);

#ifdef SDLGL
	glPopMatrix();
#endif

#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -offset_x1, offset_y1, 0.0 );
	}
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	draw_line_f3(esContext, x1, y1, 0.0, x1, y1, mark_z, 0, 0, 255, 255);

#ifdef SDLGL
	glPopMatrix();
#endif

}

void draw_xy (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, float lat, float lon, uint8_t zoom, float *x1, float *y1) {
	int mark_x = long2x(mark_long, lon, zoom);
	int mark_y = lat2y(mark_lat, lat, zoom);
	x1[0] = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	y1[0] = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
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

void show_dir (ESContext *esContext, uint16_t px, uint16_t py, float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	GLfloat x1 = (float)px / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	GLfloat y1 = (float)py / (float)esContext->height * 2.0 - 1.0;
//	y1 = y1 * -1;
	char tmp_str[50];

	/* Alt - Diff */
	float alt = alt_to - alt_from;

	/* Bearing/Heading/Richtung */
	float heading = toDeg(atan2(cos(toRad(lat_from)) * sin(toRad(lat_to)) - sin(toRad(lat_from)) * cos(toRad(lat_to)) * cos(toRad(lon_to) - toRad(lon_from)), sin(toRad(lon_to) - toRad(lon_from)) * cos(toRad(lat_to)))) + 270;
	if (heading > 360) {
		heading -= 360;
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

	/* Steigung */
	float angle_up = (asin(alt / distance2)) * 180 / PI;

	sprintf(tmp_str, "%0.2f m - %0.2f", distance1 * 1000, heading);
	draw_text(esContext, px + 50, py - 20, 20, 20, FONT_GREEN, tmp_str);

	sprintf(tmp_str, "%0.2f m - %0.2f m - %0.1f", alt, distance2, angle_up);
	draw_text(esContext, px + 50, py, 20, 20, FONT_GREEN, tmp_str);

#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -offset_x1, offset_y1, 0.0 );
	}
#endif
	esTranslate( &modelview, x1, -y1, -2.0 );
	esRotate( &modelview, heading, 0.0, 0.0, 1.0 );
	esTranslate( &modelview, -x1, y1, 2.02 );
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_line_f(esContext, x1, y1, x1, y1 - 2.5, 0, 255, 0, 255);
#ifdef SDLGL
	glPopMatrix();
#endif

#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -offset_x1, offset_y1, 0.0 );
	}
#endif
	esTranslate( &modelview, x1, -y1, -2.0 );
	esRotate( &modelview, ModelData.yaw, 0.0, 0.0, 1.0 );
	esTranslate( &modelview, -x1, y1, 2.02 );
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_line_f(esContext, x1, y1, x1, y1 - 2.5, 255, 0, 0, 255);
#ifdef SDLGL
	glPopMatrix();
#endif
}

void winkel_line (ESContext *esContext, float x_origin, float y_origin, float winkel, float r1, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float *nx1, float *ny1) {
	float angle = toRad((winkel + 90.0) * -1.0);
	float x1 = r1 * cos(angle);
	float y1 = r1 * sin(angle);
	draw_line_f(esContext, x_origin, y_origin, x_origin - x1, y_origin + y1, r, g, b, a);
	*nx1 = x_origin - x1;
	*ny1 = y_origin + y1;
}

void show_dir_f(ESContext *esContext, float x1, float y1, float zoom, float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float *nx1, float *ny1, float *dist) {
	/* Bearing/Heading/Richtung */
	float heading = toDeg(atan2(cos(toRad(lat_from)) * sin(toRad(lat_to)) - sin(toRad(lat_from)) * cos(toRad(lat_to)) * cos(toRad(lon_to) - toRad(lon_from)), sin(toRad(lon_to) - toRad(lon_from)) * cos(toRad(lat_to)))) + 270;
	if (heading > 360) {
		heading -= 360;
	}
	heading = 360.0 - heading;
	/* Distance - Grund */
	float distance1 =  acos( 
		cos(toRad( lat_from ))
		* cos(toRad(lat_to))
		* cos(toRad(lon_from) - toRad(lon_to))
		+ sin(toRad(lat_from)) 
		* sin(toRad(lat_to))
	) * 6378.137;
	/* Distance - Sichtverbindung */
	winkel_line(esContext, x1, y1, heading, distance1 / zoom, r, g, b, a, nx1, ny1);
	*dist = distance1;
}

void show_dir_ll(ESContext *esContext, float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	int mark_x = long2x(lon_from, lon, zoom);
	int mark_y = lat2y(lat_from, lat, zoom);
	float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
	char tmp_str[50];

	/* Alt - Diff */
	float alt = alt_to - alt_from;

	/* Bearing/Heading/Richtung */
	float heading = toDeg(atan2(cos(toRad(lat_from)) * sin(toRad(lat_to)) - sin(toRad(lat_from)) * cos(toRad(lat_to)) * cos(toRad(lon_to) - toRad(lon_from)), sin(toRad(lon_to) - toRad(lon_from)) * cos(toRad(lat_to)))) + 270;
	if (heading > 360) {
		heading -= 360;
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

	/* Steigung */
	float angle_up = (asin(alt / distance2)) * 180 / PI;
	sprintf(tmp_str, "%0.2f m - %0.2f", distance1 * 1000, heading);
//	draw_text(esContext, px + 50, py - 20, 20, 20, FONT_GREEN, tmp_str);
	sprintf(tmp_str, "%0.2f m - %0.2f m - %0.1f", alt, distance2, angle_up);
//	draw_text(esContext, px + 50, py, 20, 20, FONT_GREEN, tmp_str);

#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -offset_x1, offset_y1, 0.0 );
	}
#endif
	esTranslate( &modelview, x1, -y1, -2.0 );
	esRotate( &modelview, heading, 0.0, 0.0, 1.0 );
	esTranslate( &modelview, -x1, y1, 2.02 );
#ifndef SDLGL
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
	draw_line_f(esContext, x1, y1, x1, y1 - 2.5, 0, 255, 0, 64);
	draw_line_f(esContext, x1, y1, x1, y1 - 0.2, 255, 255, 0, 255);

	draw_line_f(esContext, x1, y1 - 0.2, x1 + 0.01, y1 - 0.19, 255, 255, 0, 255);
	draw_line_f(esContext, x1, y1 - 0.2, x1 - 0.01, y1 - 0.19, 255, 255, 0, 255);
#ifdef SDLGL
	glPopMatrix();
#endif
}

void mark_route (ESContext *esContext, float last_lat, float last_long, float last_alt, float mark_lat, float mark_long, float mark_alt, uint8_t type, float lat, float lon, uint8_t zoom) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
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
	if (map_view == 0) {
		last_z = 0.001;
		mark_z = 0.001;
	}
/*
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	if (map_view != 1 && map_view != 3) {
		esTranslate( &modelview, -offset_x1, offset_y1, 0.0 );
	}
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif
*/
	if (type == -1) {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 255, 255, 255, 64);
	} else if (type == 1) {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 255, 0, 0, 128);
	} else if (type == 4) {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 0, 255, 255, 128);
	} else if (type == 5) {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 255, 255, 0, 128);
	} else {
		draw_line_f3(esContext, x1, y1, last_z, x2, y2, mark_z, 255, 255, 255, 255);
	}

	float z1 = (float)get_altitude(last_lat, last_long) / alt_zoom;
	float z2 = (float)get_altitude(mark_lat, mark_long) / alt_zoom;
	if (map_view == 0) {
		z1 = 0.0;
		z2 = 0.0;
	}

	if (type != 4 && type != 5) {
		draw_triaFilled_f3(esContext, x1, y1, z1, x2, y2, z2, x2, y2, mark_z, 255, 255, 255, 127);
		draw_triaFilled_f3(esContext, x1, y1, last_z, x1, y1, z1, x2, y2, mark_z, 255, 255, 255, 127);
	}

	if (type == 1) {
		draw_line_f3(esContext, x1, y1, 0.001, x2, y2, 0.001, 255, 0, 0, 128);
	} else if (type == 4) {
	} else {
		draw_line_f3(esContext, x1, y1, 0.001, x2, y2, 0.001, 255, 255, 255, 255);
	}
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
	next_point(x1, y1, ModelData.yaw, 0.001, &nx1, &ny1);
	next_point(x2, y2, ModelData.yaw, 0.001, &nx2, &ny2);
	next_point(x1, y1, ModelData.yaw - 180.0, 0.001, &mx1, &my1);
	next_point(x2, y2, ModelData.yaw - 180.0, 0.001, &mx2, &my2);
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
	}

	if (strcmp(command, "RTL") == 0) {
		draw_text_f3(esContext, x1 + 0.01, y1 + 0.1, 0.001, 0.05, 0.05, FONT_GREEN, "RTL");
	} else if (strcmp(command, "TAKEOFF") == 0) {
		draw_text_f3(esContext, x1 + 0.01, y1 + 0.05, 0.001, 0.05, 0.05, FONT_GREEN, "TAKEOFF");
	} else if (strcmp(command, "LAND") == 0) {
		draw_text_f3(esContext, x1 + 0.01, y1 + 0.15, 0.001, 0.05, 0.05, FONT_GREEN, "LAND");
	} else {

#ifdef SDLGL
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(x1, -y1, 0.0);
		glRotatef(-roty, 0.0, 0.0, 1.0);

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
		char tmp_str[128];
		sprintf(tmp_str, "%s/textures/poi_airport.png", BASE_DIR);
		draw_image_f3(esContext, x1 - 0.03, y1 - 0.03, x1 + 0.03, y1 + 0.03, z2, tmp_str);
	} else if (type == 2) {
		draw_circle_f3(esContext, x1, y1, z2, 0.03, 0, 255, 0, 255);
	} else {
		draw_circle_f3(esContext, x1, y1, z2, 0.03, 0, 0, 255, 255);
	}
	draw_text_f3(esContext, x1, y1, z2, 0.04, 0.04, FONT_GREEN, text);
}

float get_distance (float from_lat, float from_lon, float to_lat, float to_lon) {
	float distance1 = acos( 
		cos(toRad(from_lat))
		* cos(toRad(to_lat))
		* cos(toRad(from_lon) - toRad(to_lon))
		+ sin(toRad(from_lat)) 
		* sin(toRad(to_lat))
	) * 6378.137 * 1000.0;
	return distance1;
}

/*
Info at: http://www.winpilot.com/usersguide/userairspace.asp
OLD: Data: http://soaringweb.org/Airspace/DE/DE120312.txt
Data: http://soaringweb.org/Airspace/DE/Germany_CW10_2013.txt
*/
void draw_notam (ESContext *esContext, float lat, float lon, uint8_t zoom) {
	FILE *fr;
	char line[201];
	int dp_lat_g;
	int dp_lat_m;
	int dp_lat_s;
//	char dp_lat_d;
	int dp_lon_g;
	int dp_lon_m;
	int dp_lon_s;
//	char dp_lon_d;
	uint8_t flag1 = 0;
	float mark_lat = 0.0;
	float mark_long = 0.0;
	float first_x1 = 0.0;
	float first_y1 = 0.0;
	float first_z1 = 0.0;
	float last_x1 = 0.0;
	float last_y1 = 0.0;
	float last_z1 = 0.0;
	float dp_x_min = 10000.0;
	float dp_x_max = -10000.0;
	float dp_y_min = 10000.0;
	float dp_y_max = -10000.0;
	float dp_z_min = 10000.0;
	float dp_z_max = -10000.0;
	float dp_top = 0.0;
	float poly_array[99];
	uint16_t len = 0;
	char ap_name[50];
	int max_lat = y2lat(0, lat, zoom);
	int min_lon = x2long(0, lon, zoom);
	int min_lat = y2lat(esContext->height, lat, zoom);
	int max_lon = x2long(esContext->width, lon, zoom);
	char tmp_str[128];
	sprintf(tmp_str, "%s/MAPS/Airspace.txt", BASE_DIR);
	if (file_exists(tmp_str) == 0) {
		char status_txt[2024];
		sprintf(status_txt, "getting Airspace-Data: Airspace.txt");
		sys_message(status_txt);
		printf("map: %s\n", status_txt);
		file_download(tmp_str, "http://soaringweb.org/Airspace/DE/Germany_CW10_2013.txt");
	}
        if ((fr = fopen(tmp_str, "r")) > 0) {
	        while(fgets(line, 200, fr) != NULL) {
			if (strncmp(line, "AN ", 3) == 0) {
				flag1 = 1;
				strcpy(ap_name, line + 3);
				dp_x_min = 10000.0;
				dp_x_max = -10000.0;
				dp_y_min = 10000.0;
				dp_y_max = -10000.0;
				dp_z_min = 10000.0;
				dp_z_max = -10000.0;
				dp_top = 0.0;
				len = 3;
//				if (strncmp("WIESBADEN", ap_name, 9) != 0) {
//					flag1 = 0;
//				}
			} else if (line[0] == '\n' || line[0] == '\r') {
				flag1 = 0;
				if (last_x1 != 0.0 && first_x1 != 0.0) {
					draw_line_f3(esContext, last_x1, last_y1, last_z1, first_x1, first_y1, first_z1, 0, 255, 0, 255);
					draw_triaFilled_f3(esContext, last_x1, last_y1, last_z1, first_x1, first_y1, first_z1, first_x1, first_y1, 0.0, 255, 0, 0, 64);
					draw_triaFilled_f3(esContext, last_x1, last_y1, 0.0, last_x1, last_y1, last_z1, first_x1, first_y1, 0.0, 255, 0, 0, 64);
					poly_array[0] = dp_x_min + (dp_x_max - dp_x_min) / 2.0;
					poly_array[1] = dp_y_min + (dp_y_max - dp_y_min) / 2.0;
					poly_array[2] = first_z1;
					poly_array[len++] = first_x1;
					poly_array[len++] = first_y1;
					poly_array[len++] = first_z1;
					draw_trifan_f3(esContext, poly_array, len, 255, 0, 0, 64);
					draw_text_f3(esContext, dp_x_min + (dp_x_max - dp_x_min) / 2.0, dp_y_min + (dp_y_max - dp_y_min) / 2.0, first_z1, 0.05, 0.05, FONT_BLACK_BG, ap_name);
				}
				first_x1 = 0.0;
				first_y1 = 0.0;
				first_z1 = 0.0;
				last_x1 = 0.0;
				last_y1 = 0.0;
				last_z1 = 0.0;
			} else if (flag1 == 1) {
				if (strncmp(line, "AL ", 3) == 0) {
					if (strncmp(line + 3, "GND", 3) != 0) {
						flag1 = 0;
					}
				} else if (strncmp(line, "AH ", 3) == 0) {
					if (strstr(line + 3, "MSL") > 0) {
						dp_top = atof(line + 3);
					} else {
						dp_top = atof(line + 3) * 0,3048;
					}
				} else if (strncmp(line, "DP ", 3) == 0) {
					dp_lat_g = atoi(line + 3);
					dp_lon_g = atoi(line + 14);
					if (dp_lat_g >= min_lat && dp_lat_g <= max_lat && dp_lon_g >= min_lon && dp_lon_g <= max_lon) {
						dp_lat_m = atoi(line + 6);
						dp_lon_m = atoi(line + 18);
						dp_lat_s = atoi(line + 9);
						dp_lon_s = atoi(line + 21);
//						dp_lat_d = line[12];
//						dp_lon_d = line[24];
						mark_lat = dp_lat_g + (dp_lat_m + (dp_lat_s / 60.0)) / 60.0;
						mark_long = dp_lon_g + (dp_lon_m + (dp_lon_s / 60.0)) / 60.0;
						int mark_x = long2x(mark_long, lon, zoom);
						int mark_y = lat2y(mark_lat, lat, zoom);
						float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
						float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
						if (dp_top == 0.0) {
							dp_top = (float)get_altitude(mark_lat, mark_long);
						}
						float z1 = dp_top / alt_zoom;
						draw_circleFilled_f3(esContext, x1, y1, z1, 0.01, 0, 255, 0, 255);
						if (last_x1 != 0.0) {
							draw_line_f3(esContext, last_x1, last_y1, last_z1, x1, y1, z1, 0, 255, 0, 255);
							draw_triaFilled_f3(esContext, last_x1, last_y1, last_z1, x1, y1, z1, x1, y1, 0.0, 255, 0, 0, 64);
							draw_triaFilled_f3(esContext, last_x1, last_y1, 0.0, last_x1, last_y1, last_z1, x1, y1, 0.0, 255, 0, 0, 64);
						} else {
//							printf("map: %s\n", ap_name);
							first_x1 = x1;
							first_y1 = y1;
							first_z1 = z1;
						}
						poly_array[len++] = x1;
						poly_array[len++] = y1;
						poly_array[len++] = z1;
						last_x1 = x1;
						last_y1 = y1;
						last_z1 = z1;
						if (dp_x_min > x1) {
							dp_x_min = x1;
						}
						if (dp_x_max < x1) {
							dp_x_max = x1;
						}
						if (dp_y_min > y1) {
							dp_y_min = y1;
						}
						if (dp_y_max < y1) {
							dp_y_max = y1;
						}
						if (dp_z_min > z1) {
							dp_z_min = z1;
						}
						if (dp_z_max < z1) {
							dp_z_max = z1;
						}
					} else {
						flag1 = 0;
					}
				}
			}
		}
		fclose(fr);
	}
	return;
}

/*
Data: http://download.xcsoar.org/waypoints/Germany.cup
"Aac 1Zl Aachen",,DE,5048.850N,00611.483E,189.0m,1,,,,"AACHEN"
"Frankfurt Main",,DE,5002.000N,00834.233E,110.0m,5,070,4010.0m,119.900,"Flugplatz"
*/
void draw_waypoints_cup (ESContext *esContext, float lat, float lon, uint8_t zoom) {
	FILE *fr;
	char line[501];
	char tmp_str[128];
	char wp_name[50];
	char wp_name2[50];
	float wp_lat = 0.0;
	float wp_lon = 0.0;
//	float wp_alt = 0.0;
	int max_lat = y2lat(0, lat, zoom);
	int min_lon = x2long(0, lon, zoom);
	int min_lat = y2lat(esContext->height, lat, zoom);
	int max_lon = x2long(esContext->width, lon, zoom);
	sprintf(tmp_str, "%s/MAPS/Waypoints_Germany.cup", BASE_DIR);
	if (file_exists(tmp_str) == 0) {
		char status_txt[2024];
		sprintf(status_txt, "getting Airspace-Data: %s", tmp_str);
		sys_message(status_txt);
		printf("map: %s\n", status_txt);
		file_download(tmp_str, "http://download.xcsoar.org/waypoints/Germany.cup");
	}
        if ((fr = fopen(tmp_str, "r")) > 0) {
	        while(fgets(line, 500, fr) != NULL) {
			int n = 0;
			int last_p = -1;
			int pn = 0;
			for (n = 0; n < strlen(line); n++) {
				if (line[n] == ',' || line[n] == '\n' || line[n] == '\r') {
					strncpy(tmp_str, line + last_p + 1, n - last_p - 1);
					tmp_str[n - last_p - 1] = 0;
					if (pn == 0) {
						strcpy(wp_name, tmp_str);
					} else if (pn == 3) {
						float min = atof(tmp_str + 2);
						tmp_str[2] = 0;
						wp_lat = atof(tmp_str) + min / 60.0;
					} else if (pn == 4) {
						float min = atof(tmp_str + 3);
						tmp_str[3] = 0;
						wp_lon = atof(tmp_str) + min / 60.0;
//					} else if (pn == 5) {
//						wp_alt = atof(tmp_str);
					} else if (pn == 10) {
						if ((int)wp_lat >= min_lat && (int)wp_lat <= max_lat && (int)wp_lon >= min_lon && (int)wp_lon <= max_lon) {
							strcpy(wp_name2, tmp_str);
							mark_poi(esContext, wp_lat, wp_lon, wp_name, 0, lat, lon, zoom);
						}
					}
					last_p = n;
					pn++;
				}
			}
		}
		fclose(fr);
	}
	return;
}

void display_map (ESContext *esContext, float lat, float lon, uint8_t zoom, uint8_t _map_view, uint8_t draw_tiles, float alpha1, float alpha2, float grid) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	char tmp_str[100];
	// calculate Altitude-Zoom
	uint32_t zz = (1<<zoom);
	alt_zoom = 25500000 / (float)zz;
	int tile_x = long2tilex(lon, zoom);
	int tile_y = lat2tiley(lat, zoom);
	int x_n = 0;
	int y_n = 0;
	char tile_name[1024];
	uint8_t tiles_x = (screen_w + 255) / 256;
	uint8_t tiles_y = (screen_h + 255) / 256;
	uint8_t tiles_num = 0;
	int16_t n = 0;

	reset_buttons();
#ifdef SDLGL
	if (_map_view == 1) {
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective(53.0, aspect, 0.001, 5.0);
		glMatrixMode( GL_MODELVIEW );
	} else if (_map_view == 3 || _map_view == 4 || _map_view == 5) {
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective(53.0, aspect, 0.001, 5.0);
		glMatrixMode( GL_MODELVIEW );
	} else {
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -4.5, 4.5);
		glMatrixMode( GL_MODELVIEW );
	}
#else
	if (_map_view == 3 || _map_view == 4 || _map_view == 5 || _map_view == 2) {
		_map_view = 0;
	}
#endif
	map_view = _map_view;
	if (center_map == 1 || _map_view == 3 || _map_view == 4 || _map_view == 5) {
		draw_xy(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), lat, lon, zoom, &offset_x1, &offset_y1);
		if (offset_x1 < -0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0);
		}
		if (offset_x1 > 0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0);
		}
		if (offset_y1 < -0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0);
		}
		if (offset_y1 > 0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0);
		}
	}
	if (map_startup == 0) {
		map_startup = 1;
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

		mapthread_running = 1;
		printf("map: init thread (get_maps1)\n");
#ifdef SDL2
		sdl_thread_get_maps1 = SDL_CreateThread(thread_get_maps1, NULL, NULL);
#else
		sdl_thread_get_maps1 = SDL_CreateThread(thread_get_maps1, NULL);
#endif
		if ( sdl_thread_get_maps1 == NULL ) {
			fprintf(stderr, "map: Unable to create thread_get_maps1: %s\n", SDL_GetError());
		}

		printf("map: init thread (get_maps2)\n");
#ifdef SDL2
		sdl_thread_get_maps2 = SDL_CreateThread(thread_get_maps2, NULL, NULL);
#else
		sdl_thread_get_maps2 = SDL_CreateThread(thread_get_maps2, NULL);
#endif
		if ( sdl_thread_get_maps2 == NULL ) {
			fprintf(stderr, "map: Unable to create thread_get_maps2: %s\n", SDL_GetError());
		}

	}
	if (map_rotate == 1) {
		roty += 1.3;
		if (roty >= 360.0) {
			roty = 0.0;
		}
	} else if (map_dir == 1) {
		roty = ModelData.yaw;
	} else if (map_dir == 2) {
		roty = ModelData.yaw;
	} else {
		roty = 0.0;
	}


	// rotate map
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply( &userData->mvpMatrix, &modelview, &userData->perspective );
	esMatrixMultiply( &userData->mvpMatrix2, &modelview, &userData->perspective );

	if (_map_view == 1) {
		esTranslate( &userData->perspective, 0.0, 0.0, -3.0 );
		if (map_side != 0) {
			esRotate( &userData->perspective, 45.0, 1.0, 0.0, 0.0 );
		}
		if (roty != 0.0) {
			esRotate( &userData->perspective, roty, 0.0, 0.0, -1.0 );
		}
		esTranslate( &userData->perspective, 0.0, 0.0, 2.0 );
		esTranslate( &userData->perspective, -offset_x1, offset_y1, 0.0 );
	} else if (_map_view == 3 || _map_view == 4 || _map_view == 5) {
	} else {
		esTranslate( &userData->perspective, 0.0, 0.0, 0.5 );
		esTranslate( &userData->perspective, 0.0, 0.0, -2.0 );
		esRotate( &userData->perspective, roty, 0.0, 0.0, -1.0 );
		esTranslate( &userData->perspective, 0.0, 0.0, -0.5 );
		esTranslate( &userData->perspective, 0.0, 0.0, 2.0 );
	}
#else
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	if (_map_view == 1) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef( 0.0, 0.0, -2.0 );
		if (map_side != 0) {
			glRotatef( -45.0, 1.0, 0.0, 0.0 );
		}
		if (roty != 0.0) {
			glRotatef(roty, 0.0, 0.0, 1.0 );
		}
		glTranslatef( 0.0, 0.0, 2.0 );
		glTranslatef(-offset_x1, offset_y1, 0.0);
	} else if (_map_view == 3 || _map_view == 4 || _map_view == 5) {
		roty = 0.0;
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0015, -0.0068);
		glRotatef(-ModelData.roll, 0.0, 1.0, 0.0);
		glRotatef(-ModelData.pitch, 1.0, 0.0, 0.0);
		glRotatef(ModelData.yaw, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 0.0, 2.0 - 0.00 - (ModelData.p_alt - ModelData.alt_offset) / alt_zoom);
		glTranslatef(-offset_x1, offset_y1, 0.0);
		glMatrixMode(GL_MODELVIEW);
	} else {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef( 0.0, 0.0, -2.0 );
		glRotatef( roty, 0.0, 0.0, 1.0 );
		glTranslatef( 0.0, 0.0, 2.0 );
	}
#endif


	// move map offset
	if (_map_view != 1 && _map_view != 3 && _map_view != 4 && _map_view != 5) {
		esTranslate( &modelview, -offset_x1, offset_y1, 0.0 );
	}
#ifndef SDLGL
	esMatrixMultiply( &userData->mvpMatrix, &modelview, &userData->perspective );
	esMatrixMultiply( &userData->mvpMatrix2, &modelview, &userData->perspective );
#endif


	// draw Sky in 3D-Mode
	if (_map_view == 3 || _map_view == 5) {
		draw_box_f3c2(esContext, -3.0, -3.0, -1.0, 3.0, -3.0, 3.0, 0x01, 0x8e, 0xea, 255, 0x01, 0x8e, 0xea, 255);
		draw_box_f3c2(esContext, -3.0, 3.0, -1.0, 3.0, 3.0, 3.0, 0x01, 0x8e, 0xea, 255, 0x01, 0x8e, 0xea, 255);
		draw_box_f3c2b(esContext, -3.0, -3.0, -1.0, -3.0, 3.0, 3.0, 0x01, 0x8e, 0xea, 255, 0x01, 0x8e, 0xea, 255);
		draw_box_f3c2b(esContext, 3.0, -3.0, -1.0, 3.0, 3.0, 3.0, 0x01, 0x8e, 0xea, 255, 0x01, 0x8e, 0xea, 255);
		draw_box_f3(esContext, -3.0, -3.0, 3.0, 3.0, 3.0, 3.0, 0x01, 0x8e, 0xea, 255);
	}

	// Map-Scale Test
	if (zoom == 19) {
		zoom = 18;
//		glScalef( 2.0, 2.0, 1.0 );
	} else {
		zoom = zoom;
	}

	// draw Titles
	if (zoom <= 18 && _map_view != 4) {
		for (y_n = -MAP_OVERLAY; y_n < tiles_y + MAP_OVERLAY; y_n++) {
			for (x_n = -MAP_OVERLAY; x_n < tiles_x + MAP_OVERLAY; x_n++) {
				sprintf(tile_name, mapnames[map_type][MAP_FILE], BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
				if (file_exists(tile_name) != 0) {
					if (draw_tiles == 0) {
						tile_name[0] = 0;
					}
					if (_map_view == 3 || _map_view == 4 || _map_view == 5) {
						draw_image_srtm(esContext, x_n * 256, y_n * 256, 256, 256, tile_name, tiley2lat(tile_y + y_n, zoom), tilex2long(tile_x + x_n, zoom), tiley2lat(tile_y + y_n + 1, zoom), tilex2long(tile_x + x_n + 1, zoom), alpha1, alpha2, grid);
					} else if (_map_view == 1) {
						draw_image_srtm(esContext, x_n * 256, y_n * 256, 256, 256, tile_name, tiley2lat(tile_y + y_n, zoom), tilex2long(tile_x + x_n, zoom), tiley2lat(tile_y + y_n + 1, zoom), tilex2long(tile_x + x_n + 1, zoom), alpha1, alpha2, grid);
					} else {
						draw_image(esContext, x_n * 256, y_n * 256, 256, 256, tile_name);
					}
				} else {
					char tmp_str[128];
					sprintf(tmp_str, "%s/textures/loading.png", BASE_DIR);
					draw_image(esContext, x_n * 256, y_n * 256, 256, 256, tmp_str);
				}
				if (draw_tiles != 0 && omapnames[omap_type][MAP_FILE][0] != 0) {
					sprintf(tile_name, omapnames[omap_type][MAP_FILE], BASE_DIR, zoom, tile_x + x_n, tile_y + y_n);
					if (file_exists(tile_name) != 0) {
						if (_map_view == 1) {
							draw_image_srtm(esContext, x_n * 256, y_n * 256, 256, 256, tile_name, tiley2lat(tile_y + y_n, zoom), tilex2long(tile_x + x_n, zoom), tiley2lat(tile_y + y_n + 1, zoom), tilex2long(tile_x + x_n + 1, zoom), 0.0, 0.0, 0.0);
						} else {
							draw_image(esContext, x_n * 256, y_n * 256, 256, 256, tile_name);
						}
					}
				}
				tiles_num++;
			}
		}
	}

#ifdef SDLGL
	if (nav_map == 1) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		esTranslate(&modelview, offset_x1, -offset_y1, 0.0);
		draw_circleFilled_f3_part(esContext, 0.0, 0.0, 0.00, 1.8, 0.75, 0.0, 360.0, 0, 0, 0, 127);
		draw_box_f3(esContext, -3.0, -3.0, 0.002, 3.0, 3.0, 0.002, 0, 0, 0, 127);
		glPopMatrix();
		for (n = 0; n < 360; n += 2) {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			esTranslate(&modelview, 0.0, 0.0, -2.0);
			esTranslate(&modelview, offset_x1, -offset_y1, 0.0);
			esRotate(&modelview, ((float)n), 0.0, 0.0, 1.0);
			esTranslate(&modelview, 0.0, 0.0, 2.0);
			if (n % 10 == 0) {
				draw_line_f3(esContext, 0.0, 0.8, 0.003, 0.0, 0.85, 0.003, 255, 255, 255, 255);
				char tmp_str[1024];
				sprintf(tmp_str, "%i", n);
				draw_text_f3(esContext, 0.0 - strlen(tmp_str) * 0.05 * 0.6 / 2.0 - 0.01, -0.8, 0.003, 0.05, 0.05, FONT_WHITE, tmp_str);
			} else {
				draw_line_f3(esContext, 0.0, 0.8, 0.003, 0.0, 0.83, 0.003, 255, 255, 255, 255);
			}
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			esTranslate(&modelview, 0.0, 0.0, -2.0);
			esRotate(&modelview, ((float)n) + 5.0, 0.0, 0.0, 1.0);
			esTranslate(&modelview, -offset_x1, offset_y1, 0.0);
			esTranslate(&modelview, 0.0, 0.0, 2.0);
			glPopMatrix();
		}
	}
#else
	if (nav_map == 1) {
		esMatrixLoadIdentity(&modelview);
		esTranslate(&modelview, offset_x1, -offset_y1, 0.0);
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
		draw_circleFilled_f3_part(esContext, 0.0, 0.0, 0.00, 1.8, 0.75, 0.0, 360.0, 0, 0, 0, 127);
		draw_box_f3(esContext, -3.0, -3.0, 0.002, 3.0, 3.0, 0.002, 0, 0, 0, 127);
		for (n = 0; n < 360; n += 2) {
			esMatrixLoadIdentity(&modelview);
			esTranslate(&modelview, 0.0, 0.0, -2.0);
			esTranslate(&modelview, offset_x1, -offset_y1, 0.0);
			esRotate(&modelview, ((float)n), 0.0, 0.0, 1.0);
			esTranslate(&modelview, 0.0, 0.0, 2.0);
			esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
			esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
			if (n % 10 == 0) {
				draw_line_f3(esContext, 0.0, 0.8, 0.003, 0.0, 0.85, 0.003, 255, 255, 255, 255);
				char tmp_str[1024];
				sprintf(tmp_str, "%i", n);
				draw_text_f3(esContext, 0.0 - strlen(tmp_str) * 0.05 * 0.6 / 2.0 - 0.01, -0.8, 0.003, 0.05, 0.05, FONT_WHITE, tmp_str);
			} else {
				draw_line_f3(esContext, 0.0, 0.8, 0.003, 0.0, 0.83, 0.003, 255, 255, 255, 255);
			}
			esMatrixLoadIdentity(&modelview);
			esTranslate(&modelview, 0.0, 0.0, -2.0);
			esRotate(&modelview, ((float)n) + 5.0, 0.0, 0.0, 1.0);
			esTranslate(&modelview, -offset_x1, offset_y1, 0.0);
			esTranslate(&modelview, 0.0, 0.0, 2.0);
			esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
			esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
		}
	}
#endif

	// drawing POI's, NOTAM's and Waypoint's
	if (map_show_notam == 1) {
		draw_notam(esContext, lat, lon, zoom);
	}
	if (map_show_poi == 1) {
		draw_waypoints_cup(esContext, lat, lon, zoom);
	}
	if (map_show_wp == 0) {
		for (n = 0; n < MAX_POIS; n++) {
			if (POIs[n].p_lat != 0.0) {
				mark_poi(esContext, POIs[n].p_lat, POIs[n].p_long, POIs[n].name, POIs[n].type, lat, lon, zoom);
			}
		}
	}

	// drawing Waypoint-Route
	float last_lat = ModelData.p_lat;
	float last_lon = ModelData.p_long;
	float last_alt = (ModelData.p_alt - ModelData.alt_offset);
	int flag = 0;

	if (map_show_wp == 1) {
		for (n = 1; n < MAX_WAYPOINTS; n++) {
			if (WayPoints[n].p_lat != 0.0) {
				if (n == uav_active_waypoint + 1 && n == waypoint_active) {
					mark_point(esContext, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, WayPoints[n].name, WayPoints[n].command, 3, WayPoints[n].radius, WayPoints[n].orbit, lat, lon, zoom);
				} else if (n == uav_active_waypoint + 1) {
					mark_point(esContext, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, WayPoints[n].name, WayPoints[n].command, 2, WayPoints[n].radius, WayPoints[n].orbit, lat, lon, zoom);
				} else if (n == waypoint_active) {
					mark_point(esContext, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, WayPoints[n].name, WayPoints[n].command, 1, WayPoints[n].radius, WayPoints[n].orbit, lat, lon, zoom);
				} else {
					mark_point(esContext, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, WayPoints[n].name, WayPoints[n].command, 0, WayPoints[n].radius, WayPoints[n].orbit, lat, lon, zoom);
				}
			}
		}
		if (map_view == 3 || map_view == 4 || _map_view == 5) {
			if (hud_view_tunnel == 1) {
				mark_tunnel(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset) + 10.6, WayPoints[waypoint_active].p_lat, WayPoints[waypoint_active].p_long, WayPoints[waypoint_active].p_alt, 5, lat, lon, zoom);
			}
		} else {
			draw_quad(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), ModelData.roll, ModelData.pitch, ModelData.yaw, lat, lon, zoom);
		}
		mark_point(esContext, WayPoints[0].p_lat, WayPoints[0].p_long, WayPoints[0].p_alt, WayPoints[0].name, "", 0, 0.0, 0.0, lat, lon, zoom);
		for (n = 1; n < MAX_WAYPOINTS; n++) {
			if (WayPoints[n].p_lat != 0.0) {
				if (flag != 0) {
					mark_route(esContext, last_lat, last_lon, last_alt, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, 0, lat, lon, zoom);
				}
				flag = 1;
				last_lat = WayPoints[n].p_lat;
				last_lon = WayPoints[n].p_long;
				last_alt = WayPoints[n].p_alt;
			}
		}
		mark_route(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), WayPoints[uav_active_waypoint + 1].p_lat, WayPoints[uav_active_waypoint + 1].p_long, WayPoints[uav_active_waypoint + 1].p_alt, 1, lat, lon, zoom);
	//	mark_route(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), WayPoints[waypoint_active].p_lat, WayPoints[waypoint_active].p_long, WayPoints[waypoint_active].p_alt, 1, lat, lon, zoom);
	} else {
		if (map_view == 3 || map_view == 4 || _map_view == 5) {
			if (hud_view_tunnel == 1) {
				mark_tunnel(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset) + 10.6, WayPoints[waypoint_active].p_lat, WayPoints[waypoint_active].p_long, WayPoints[waypoint_active].p_alt, 5, lat, lon, zoom);
			}
		} else {
			draw_quad(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), ModelData.roll, ModelData.pitch, ModelData.yaw, lat, lon, zoom);
		}
	}


#ifdef SDLGL
	// Camview - Target-Marking
	float nx2 = 0.0;
	float ny2 = 0.0;
	float nf = 0.0;
	float mark_alt = 0.0;
	float DEG2RAD = 3.14159 / 180.0;
	float distance = 0.0;
	float nalt = 0.0;
	for (nf = 1; nf < 1024; nf += 20) {
		next_point_ll(esContext, ModelData.p_long, ModelData.p_lat, ModelData.yaw * -1.0 - 90.0, nf, &nx2, &ny2);
		distance = get_distance(ModelData.p_lat, ModelData.p_long, ny2, nx2);
		nalt = (ModelData.p_alt - ModelData.alt_offset) + distance * tan(ModelData.pitch * DEG2RAD * 0.7);
//		mark_point(esContext, ny2, nx2, nalt, "", "", 0, 0.1, 0.0, lat, lon, zoom);
		mark_alt = get_altitude(ny2, nx2);
		if (mark_alt >= (int16_t)nalt) {
			break;
		}
	}
	if (nf < 1024 && nf > 20) {
		for (nf -= 20; nf < 1024; nf += 1) {
			next_point_ll(esContext, ModelData.p_long, ModelData.p_lat, ModelData.yaw * -1.0 - 90.0, nf, &nx2, &ny2);
			distance = get_distance(ModelData.p_lat, ModelData.p_long, ny2, nx2);
			nalt = (ModelData.p_alt - ModelData.alt_offset) + distance * tan(ModelData.pitch * DEG2RAD * 0.7);
//			mark_point(esContext, ny2, nx2, nalt, "", "", 0, 0.1, 0.0, lat, lon, zoom);
			mark_alt = get_altitude(ny2, nx2);
			if (mark_alt >= (int16_t)nalt) {
				break;
			}
		}
		mark_point(esContext, ny2, nx2, mark_alt, "", "", 5, 0.1, 0.0, lat, lon, zoom);
		if (hud_view_mark == 1) {
			hud_view_mark = 0;
			for (n = 0; n < MAX_WAYPOINTS; n++) {
				if (WayPoints[n].p_lat == 0.0) {
					WayPoints[n].p_lat = ny2;
					WayPoints[n].p_long = nx2;
					WayPoints[n].p_alt = mark_alt;
					WayPoints[n].yaw = ModelData.yaw;
					sprintf(WayPoints[n].name, "MARK%i", n);
					strcpy(WayPoints[n].command, "POI");
					break;
				}
			}
		}
	}
#endif
	if (nav_map != 1 && map_show_log == 1) {
		// draw log
/*
		if (LogLines != NULL) {
			int r_tim = 0;
			float r_lat = 0.0;
			float r_lon = 0.0;
			float r_alt = 0.0;
			float r_vel = 0.0;
			struct list_element *liste = LogLines;
			flag = 0;
			if (liste->line != NULL) {
				if (strncmp(liste->line, "GPS;", 4) == 0) {
					sscanf(liste->line, "GPS;%i;%f;%f;%f;%f", &r_tim, &r_lat, &r_lon, &r_alt, &r_vel);
					last_lat = r_lat;
					last_lon = r_lon;
					last_alt = r_alt;
					flag = 1;
				}
			}
			while (liste->next != NULL) {
				liste=liste->next;
				if (liste->line != NULL) {
					if (strncmp(liste->line, "GPS;", 4) == 0) {
						sscanf(liste->line, "GPS;%i;%f;%f;%f;%f", &r_tim, &r_lat, &r_lon, &r_alt, &r_vel);
						if (flag != 0) {
							mark_route(esContext, last_lat, last_lon, last_alt, r_lat, r_lon, r_alt, 0, lat, lon, zoom);
						}
						last_lat = r_lat;
						last_lon = r_lon;
						last_alt = r_alt;
						flag = 1;
					}
				}
			}
		}
*/
	}


	// rotate map back
#ifndef SDLGL
	if (_map_view == 1) {
		esTranslate( &userData->perspective, offset_x1, -offset_y1, 0.0 );
		esTranslate( &userData->perspective, 0.0, 0.0, -2.0 );
		if (roty != 0.0) {
			esRotate( &userData->perspective, roty, 0.0, 0.0, 1.0 );
		}
		if (map_side != 0) {
			esRotate( &userData->perspective, -45.0, 1.0, 0.0, 0.0 );
		}
		esTranslate( &userData->perspective, 0.0, 0.0, 3.0 );
	} else if (_map_view == 3 || _map_view == 4 || _map_view == 5) {
	} else {
		esTranslate( &userData->perspective, 0.0, 0.0, 0.5 );
		esTranslate( &userData->perspective, 0.0, 0.0, -2.0 );
		esRotate( &userData->perspective, roty, 0.0, 0.0, 1.0 );
		esTranslate( &userData->perspective, 0.0, 0.0, -0.5 );
		esTranslate( &userData->perspective, 0.0, 0.0, 2.0 );
	}

	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);

	// move map offset back
	if (_map_view != 1 && _map_view != 3 && _map_view != 4 && _map_view != 5) {
		esTranslate( &modelview, offset_x1, -offset_y1, 0.0 );
	}

#else
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
#endif

	glDisable( GL_DEPTH_TEST );


	// Scale-Info
	float scale = 100.0;
	float S = 63727982 * cos((lat * DEG2RAD)) / pow(2, (zoom + 8));
	scale = (int)(100 * S) / 200 * 200;
	if (zoom < 14) {
		scale = (int)(100 * S) / 1000 * 1000;
	} else if (scale <= 100.0) {
		scale = 100.0;
	}
	draw_box(esContext, 10, esContext->height - 50, (scale / S), 5, 0, 0, 255, 128);
	draw_rect(esContext, 10, esContext->height - 50, (scale / S), 5, 0, 0, 0, 255);
	sprintf(tmp_str, "%0.1fkm (Z:%i)", scale / 1000.0, zoom);
	draw_text(esContext, 10, esContext->height - 40, 8, 8, FONT_BLACK_BG, tmp_str);


	if (strcmp(mapnames[map_type][MAP_NAME], "GAPI") == 0 || strcmp(mapnames[map_type][MAP_TYPE], "GOOGLE") == 0) {
		sprintf(tile_name, "%s/MAPS/google.png", BASE_DIR);
		if (file_exists(tile_name) != 0) {
			draw_image(esContext, 1, screen_h - 30, 62, 29, tile_name);
		}
		draw_text_f3(esContext, -1.2, 0.955, 0.003, 0.025, 0.04, FONT_GREEN, "Grafiken (c)2012 AeroWest, DigitalGlobe, GeoBasis-DE/BKG, GeoContent, GeoEye, TerraMetrics, Kartendaten (c)2012 GeoBasis-DE/BKG ((c)2009), Google");
	}
	if (_map_view != 3 && _map_view != 4 && _map_view != 5) {
//		draw_button(esContext, "map_uav2home", VIEW_MODE_MAP, "UAV->HOME", FONT_GREEN_BG, -0.9, -0.96, 0.002, 0.06, 1, 0, map_uav2home, 0.0);
		uint8_t ny = 0;
		ny++;
		if (map_type_select == 1) {
			uint8_t ny2 = ny;
			uint8_t nn = 0;
			for (nn = 0; nn < maplen; nn++) {
				draw_box_f3(esContext, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 0, 0, 0, 200);
				draw_rect_f3(esContext, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 255, 255, 255, 200);
				sprintf(tmp_str, "change_maptype%i", nn);
				draw_button(esContext, tmp_str, VIEW_MODE_MAP, mapnames[nn][MAP_NAME], FONT_WHITE, -1.0, -0.8 + ny2++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, change_maptype, nn);
			}
		}
		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "change_maptype", VIEW_MODE_MAP, mapnames[map_type][MAP_NAME], FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, change_maptype, -1);

		if (omap_type_select == 1) {
			uint8_t ny2 = ny;
			uint8_t nn = 0;
			for (nn = 0; nn < omaplen; nn++) {
				draw_box_f3(esContext, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 0, 0, 0, 200);
				draw_rect_f3(esContext, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 255, 255, 255, 200);
				sprintf(tmp_str, "change_omaptype%i", nn);
				draw_button(esContext, tmp_str, VIEW_MODE_MAP, omapnames[nn][MAP_NAME], FONT_WHITE, -1.0, -0.8 + ny2++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, change_omaptype, nn);
			}
		}
		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "change_omaptype", VIEW_MODE_MAP, omapnames[omap_type][MAP_NAME], FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, change_omaptype, -1);

		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_zoom+", VIEW_MODE_MAP, "[+]", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_zoom, +1.0);
		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_zoom-", VIEW_MODE_MAP, "[-]", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_zoom, -1.0);
		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_home", VIEW_MODE_MAP, "HOME", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_goto, 0.0);
		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_uav", VIEW_MODE_MAP, "UAV", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_goto, -1.0);
		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (center_map == 0) {
			draw_button(esContext, "map_center", VIEW_MODE_MAP, "FREE", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_center, 0.0);
		} else if (center_map == 1) {
			draw_button(esContext, "map_center", VIEW_MODE_MAP, "CENTER", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_center, 0.0);
		} else {
			draw_button(esContext, "map_center", VIEW_MODE_MAP, "FOLLOW", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_center, 0.0);
		}
#ifndef RPI_NO_X
		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (nav_map == 1) {
			draw_button(esContext, "map_nav", VIEW_MODE_MAP, "NAV", FONT_GREEN, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_nav, 0.0);
		} else {
			draw_button(esContext, "map_nav", VIEW_MODE_MAP, "NAV", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_nav, 0.0);
		}
#else
		ny++;
#endif

		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (map_dir == 1) {
			draw_button(esContext, "map_dir", VIEW_MODE_MAP, "DIR", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_dir_change, 0.0);
		} else if (map_dir == 2) {
			draw_button(esContext, "map_dir", VIEW_MODE_MAP, "TARGET", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_dir_change, 0.0);
		} else {
			draw_button(esContext, "map_dir", VIEW_MODE_MAP, "NORTH", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_dir_change, 0.0);
		}

		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (map_view == 1) {
			draw_button(esContext, "map_3d", VIEW_MODE_MAP, "3D", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_view_change, 0.0);
		} else {
			draw_button(esContext, "map_3d", VIEW_MODE_MAP, "2D", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_view_change, 0.0);
		}

		if (map_view == 1) {
			draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
			draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
			if (map_side == 1) {
				draw_button(esContext, "map_side", VIEW_MODE_MAP, "SIDE", FONT_GREEN, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_side_change, 0.0);
				draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
				draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
				if (map_rotate == 1) {
					draw_button(esContext, "map_rotate", VIEW_MODE_MAP, "ROTATE", FONT_GREEN, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_rotate_change, 0.0);
				} else {
					draw_button(esContext, "map_rotate", VIEW_MODE_MAP, "ROTATE", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_rotate_change, 0.0);
				}
			} else {
				draw_button(esContext, "map_side", VIEW_MODE_MAP, "SIDE", FONT_WHITE, -1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_side_change, 0.0);
				map_rotate = 0;
				ny++;
			}
		} else {
			map_rotate = 0;
			ny++;
			ny++;
		}

		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (ModelData.gpsfix > 0) {
			sprintf(tmp_str, "Fix: %iD", ModelData.gpsfix);
			draw_button(esContext, "map_fix", VIEW_MODE_MAP, tmp_str, FONT_GREEN, -1.3, -0.8 + ny * 0.12 - 0.02, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
			sprintf(tmp_str, "Sat: %i", ModelData.numSat);
			draw_button(esContext, "map_sats", VIEW_MODE_MAP, tmp_str, FONT_GREEN, -1.3, -0.8 + ny * 0.12 + 0.03, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
		} else {
			strcpy(tmp_str, "No Fix");
			draw_button(esContext, "map_fix", VIEW_MODE_MAP, tmp_str, FONT_WHITE, -1.3, -0.8 + ny * 0.12 - 0.02, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
			sprintf(tmp_str, "Sat: %i", ModelData.numSat);
			draw_button(esContext, "map_sats", VIEW_MODE_MAP, tmp_str, FONT_WHITE, -1.3, -0.8 + ny * 0.12 + 0.03, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
		}

		ny = 0;
		ny++;
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (map_addmode == 0) {
			draw_button(esContext, "map_add", VIEW_MODE_MAP, "ADD", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_add, 0.0);
		} else {
			draw_button(esContext, "map_add", VIEW_MODE_MAP, "ADD", FONT_GREEN, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_add, 0.0);
		}
		if (map_show_wp == 1) {
			draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
			draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
			draw_button(esContext, "map_del", VIEW_MODE_MAP, "DEL", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_del, 0.0);
			draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
			draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
			draw_button(esContext, "fms_edit", VIEW_MODE_MAP, "EDIT", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, wpedit_waypoint_edit, (float)VIEW_MODE_MAP);
		} else {
			ny++;
			ny++;
		}
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_read_wp", VIEW_MODE_MAP, "READ", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, read_wp, 0.0);
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_write_wp", VIEW_MODE_MAP, "WRITE", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, write_wp, 0.0);

		ny++;
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (map_show_wp == 1) {
			draw_button(esContext, "map_show_wp", VIEW_MODE_MAP, "WP", FONT_GREEN, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_wp, 0.0);
		} else {
			draw_button(esContext, "map_show_wp", VIEW_MODE_MAP, "WP", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_wp, 0.0);
		}
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (map_show_log == 1) {
			draw_button(esContext, "map_show_log", VIEW_MODE_MAP, "LOG", FONT_GREEN, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_log, 0.0);
		} else {
			draw_button(esContext, "map_show_log", VIEW_MODE_MAP, "LOG", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_log, 0.0);
		}

		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (map_show_notam == 1) {
			draw_button(esContext, "map_show_notam", VIEW_MODE_MAP, "NOTAM", FONT_GREEN, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_notam, 0.0);
		} else {
			draw_button(esContext, "map_show_notam", VIEW_MODE_MAP, "NOTAM", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_notam, 0.0);
		}

		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (map_show_poi == 1) {
			draw_button(esContext, "map_show_poi", VIEW_MODE_MAP, "POI", FONT_GREEN, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_poi, 0.0);
		} else {
			draw_button(esContext, "map_show_poi", VIEW_MODE_MAP, "POI", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_poi, 0.0);
		}


		ny++;
		ny++;
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (ModelData.gpsfix > 0) {
			sprintf(tmp_str, "Alt: %0.0f", ModelData.p_alt);
			draw_button(esContext, "map_alt", VIEW_MODE_MAP, tmp_str, FONT_GREEN, 1.3, -0.8 + ny * 0.12 - 0.02, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
			sprintf(tmp_str, "Speed: %0.0f", ModelData.speed);
			draw_button(esContext, "map_speed", VIEW_MODE_MAP, tmp_str, FONT_GREEN, 1.3, -0.8 + ny * 0.12 + 0.03, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
		} else {
			sprintf(tmp_str, "Alt: %0.0f", ModelData.p_alt);
			draw_button(esContext, "map_alt", VIEW_MODE_MAP, tmp_str, FONT_WHITE, 1.3, -0.8 + ny * 0.12 - 0.02, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
			sprintf(tmp_str, "Speed: %0.0f", ModelData.speed);
			draw_button(esContext, "map_speed", VIEW_MODE_MAP, tmp_str, FONT_WHITE, 1.3, -0.8 + ny * 0.12 + 0.03, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
		}

/*
		ny++;
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_downloader", VIEW_MODE_MAP, "MD", FONT_WHITE, 1.3, -0.8 + ny++ * 0.12, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_downloader, 0.0);
*/

//		draw_button(esContext, "map_export_kml", VIEW_MODE_MAP, "KML", FONT_WHITE, 0.9, -0.96, 0.002, 0.06, 1, 0, map_export_kml, 1.0);
//		map_view = 0;
	}
	glEnable( GL_DEPTH_TEST );
#ifdef SDLGL

	if (_map_view == 3 || _map_view == 4 || _map_view == 5) {
		roty = 0.0;
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	glPopMatrix();
#endif


}

void screen_map (ESContext *esContext, float lat, float lon, uint8_t zoom) {
	display_map(esContext, lat, lon, zoom, map_view, 1, 0.0, 0.0, 0.0);
}
