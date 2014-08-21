
#include <all.h>
#include <kml.h>

volatile float lat = 50.29;
volatile float lon = 9.12;
volatile uint8_t zoom = 16;
uint8_t map_type = 0;
uint8_t map_type_select = 0;
uint8_t omap_type = 0;
uint8_t omap_type_select = 0;
uint8_t map_view = 0;
uint8_t map_color = 0;
uint8_t map_startup = 0;
uint8_t map_addmode = 0;
float roty = 0.0;
uint8_t uav_active_waypoint = 0;
uint8_t center_map = 1;
uint8_t nav_map = 0;
uint8_t map_show_wp = 0;
uint8_t map_show_notam = 0;
uint8_t map_show_poi = 0;
uint8_t map_rotate = 0;
uint8_t map_side = 1;
uint8_t map_dir = 0;

//#define HTTP_USE_WGET 1

uint8_t map_goto_screen (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	setup.view_mode = (int)data;
	view_mode_next = (int)data;
	return 0;
}

int file_exists (char *fileName) {
	struct stat buf;
	int i = stat(fileName, &buf);
	if (i == 0) {
		return 1;
	}
	return 0;
}

int file_download (char *fileName, char *url) {
	char tmp_file[4024];
#ifdef ANDROID
	SDL_Log("htmlget: %s -> %s\n", url, fileName);
#endif
	sprintf(tmp_file, "%s.tmp", fileName);
	if (htmlget(url, tmp_file) < 0) {
		return -1;
	}
	rename(tmp_file, fileName);
	return 0;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
	int written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

uint8_t map_null (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

uint8_t map_link_open (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	sys_message(name);
#ifdef ANDROID
	Android_JNI_OpenLink(name);
#else
#ifndef WINDOWS
#ifndef OSX
#ifndef RPI_NO_X
	char cmd_str[1024];
	sprintf(cmd_str, "firefox \'%s\' &", name);
	SDL_Log("map: link: %s\n", cmd_str);
	system(cmd_str);
#endif
#endif
#endif
#endif
	return 0;
}

uint8_t map_nav (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	nav_map = 1 - nav_map;
	if (nav_map == 1) {
		center_map = 1;
		map_view = 2;
		map_show_wp = 1;
		map_dir = 1;
	}
	return 0;
}

uint8_t map_center (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	nav_map = 0;
	if (center_map < 2) {
		center_map++;
	} else {
		center_map = 0;
	}
	return 0;
}

uint8_t map_dir_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (map_dir < 1) {
		map_dir++;
	} else {
		map_dir = 0;
	}
	return 0;
}

uint8_t map_rotate_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	map_rotate = 1 - map_rotate;
	return 0;
}

uint8_t map_side_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	map_side = 1 - map_side;
	return 0;
}

uint8_t map_view_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	nav_map = 0;
	if (map_view < 1) {
		map_view++;
	} else {
		map_view = 0;
	}
	return 0;
}

uint8_t map_color_change (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (map_color < 1) {
		map_color++;
	} else {
		map_color = 0;
	}
	return 0;
}

uint8_t change_maptype (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	SDL_Log("map: change_maptype\n");
	if (data == -1) {
		map_type_select = 1 - map_type_select;
	} else {
		map_type = (uint8_t)data;
		map_type_select = 0;
	}
	return 0;
}

uint8_t change_omaptype (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	SDL_Log("map: change_omaptype\n");
	if (data == -1) {
		omap_type_select = 1 - omap_type_select;
	} else {
		omap_type = (uint8_t)data;
		omap_type_select = 0;
	}
	return 0;
}

uint8_t map_zoom (char *name, float x, float y, int8_t button, float data, uint8_t action) {
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

uint8_t show_wp (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if ((int)data == 1) {
		map_show_wp = 1;
	} else {
		map_show_wp = 1 - map_show_wp;
	}
	return 0;
}

uint8_t show_notam (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if ((int)data == 1) {
		map_show_notam = 1;
	} else {
		map_show_notam = 1 - map_show_notam;
	}
	return 0;
}

uint8_t show_poi (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if ((int)data == 1) {
		map_show_poi = 1;
	} else {
		map_show_poi = 1 - map_show_poi;
	}
	return 0;
}

uint8_t map_goto (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (data == -1.0) {
		int tile_y = lat2tiley(ModelData.p_lat, mapdata->zoom) - 1;
		int tile_x = long2tilex(ModelData.p_long, mapdata->zoom) - 1;
		lat = tiley2lat(tile_y, mapdata->zoom);
		lon = tilex2long(tile_x, mapdata->zoom);
	} else {
		int tile_y = lat2tiley(WayPoints[(int)data].p_lat, mapdata->zoom) - 1;
		int tile_x = long2tilex(WayPoints[(int)data].p_long, mapdata->zoom) - 1;
		lat = tiley2lat(tile_y, mapdata->zoom);
		lon = tilex2long(tile_x, mapdata->zoom);
	}
	return 0;
}

uint8_t map_uav2home (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	ModelData.p_lat = WayPoints[0].p_lat;
	ModelData.p_long = WayPoints[0].p_long;
	ModelData.p_alt = WayPoints[0].p_alt;
	return 0;
}

uint8_t map_add (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	map_addmode = 1 - map_addmode;
	map_show_wp = 1;
	return 0;
}

uint8_t map_del (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	uint16_t n = 0;
	uint16_t n2 = waypoint_active + 1;
	for (n = waypoint_active; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[n].p_lat != 0.0) {
			WayPoints[n].p_lat = WayPoints[n2].p_lat;
			WayPoints[n].p_long = WayPoints[n2].p_long;
			WayPoints[n].p_alt = WayPoints[n2].p_alt;
			WayPoints[n].yaw = WayPoints[n2].yaw;
			strncpy(WayPoints[n].name, WayPoints[n2].name, 127);
			strncpy(WayPoints[n].command, WayPoints[n2].command, 127);
			n2++;
		}
	}
	waypoint_active--;
	return 0;
}

void draw_xy (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, float lat, float lon, uint8_t zoom, float *x1, float *y1) {
	int mark_x = long2x(mark_long, lon, zoom);
	int mark_y = lat2y(mark_lat, lat, zoom);
	x1[0] = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	y1[0] = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
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
		esTranslate( &modelview, -mapdata->offset_x1, mapdata->offset_y1, 0.0 );
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
		esTranslate( &modelview, -mapdata->offset_x1, mapdata->offset_y1, 0.0 );
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
	int vx_lat_g;
	int vx_lat_m;
	int vx_lat_s;
	int vx_lon_g;
	int vx_lon_m;
	int vx_lon_s;
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
	sprintf(tmp_str, "%s/MAPS/Airspace.txt", get_datadirectory());
	if (file_exists(tmp_str) == 0) {
		char status_txt[2024];
		sprintf(status_txt, "getting Airspace-Data: Airspace.txt");
		sys_message(status_txt);
		SDL_Log("map: %s\n", status_txt);
		file_download(tmp_str, "http://soaringweb.org/Airspace/DE/Germany_CW10_2013.txt");
	}
        if ((fr = fopen(tmp_str, "rb")) > 0) {
	        while(fgets(line, 200, fr) != NULL) {
			if (strncmp(line, "AN ", 3) == 0) {
				flag1 = 1;
				strncpy(ap_name, line + 3, 49);
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
						dp_top = atof(line + 3) * 0.3048;
					}
				} else if (strncmp(line, "V X=", 4) == 0) {
					vx_lat_g = atoi(line + 4);
					vx_lon_g = atoi(line + 15);
					if (vx_lat_g >= min_lat && vx_lat_g <= max_lat && vx_lon_g >= min_lon && vx_lon_g <= max_lon) {
						vx_lat_m = atoi(line + 7);
						vx_lon_m = atoi(line + 19);
						vx_lat_s = atoi(line + 10);
						vx_lon_s = atoi(line + 22);
						mark_lat = vx_lat_g + (vx_lat_m + (vx_lat_s / 60.0)) / 60.0;
						mark_long = vx_lon_g + (vx_lon_m + (vx_lon_s / 60.0)) / 60.0;
						int mark_x = long2x(mark_long, lon, zoom);
						int mark_y = lat2y(mark_lat, lat, zoom);
						float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
						float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
						float z1 = (float)get_altitude(mark_lat, mark_long) / alt_zoom;
						draw_circleFilled_f3(esContext, x1, y1, z1, 0.01, 0, 255, 0, 255);
					}
				} else if (strncmp(line, "DC ", 3) == 0) {
					if (vx_lat_g >= min_lat && vx_lat_g <= max_lat && vx_lon_g >= min_lon && vx_lon_g <= max_lon) {
						float radius = atof(line + 3);
						mark_lat = vx_lat_g + (vx_lat_m + (vx_lat_s / 60.0)) / 60.0;
						mark_long = vx_lon_g + (vx_lon_m + (vx_lon_s / 60.0)) / 60.0;
						int mark_x = long2x(mark_long, lon, zoom);
						int mark_y = lat2y(mark_lat, lat, zoom);
						float x1 = (float)mark_x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
						float y1 = (float)mark_y / (float)esContext->height * 2.0 - 1.0;
						float z1 = (float)get_altitude(mark_lat, mark_long) / alt_zoom;
						int16_t bx = (x1 / aspect + 1.0) / 2.0 * (float)GlobalesContext->width + 100;
						float next_long = x2long(bx, lon, zoom);
						float dist_nm = get_distance(mark_lat, mark_long, mark_lat, next_long) / 1.85;
						float radius2 = (float)(radius / dist_nm * 100000.0) / (float)esContext->width * 2.0 * aspect;
						draw_circleFilled_f3(esContext, x1, y1, z1 + 0.001, radius2, 255, 0, 0, 64);
						draw_text_f3(esContext, x1, y1, z1, 0.05, 0.05, FONT_BLACK_BG, ap_name);
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
//							SDL_Log("map: %s\n", ap_name);
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
	sprintf(tmp_str, "%s/MAPS/Waypoints_Germany.cup", get_datadirectory());
	if (file_exists(tmp_str) == 0) {
		char status_txt[2024];
		sprintf(status_txt, "getting Airspace-Data: %s", tmp_str);
		sys_message(status_txt);
		SDL_Log("map: %s\n", status_txt);
		file_download(tmp_str, "http://download.xcsoar.org/waypoints/Germany.cup");
	}
        if ((fr = fopen(tmp_str, "rb")) > 0) {
	        while(fgets(line, 500, fr) != NULL) {
			int n = 0;
			int last_p = -1;
			int pn = 0;
			for (n = 0; n < strlen(line); n++) {
				if (line[n] == ',' || line[n] == '\n' || line[n] == '\r') {
					strncpy(tmp_str, line + last_p + 1, n - last_p - 1);
					tmp_str[n - last_p - 1] = 0;
					if (pn == 0) {
						strncpy(wp_name, tmp_str, 49);
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
							strncpy(wp_name2, tmp_str, 49);
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

void map_exit (void) {
	GeoMap_exit(mapdata);
}


void map_draw_buttons (ESContext *esContext) {
	char tmp_str[1024];
	glDisable( GL_DEPTH_TEST );
#ifdef SDLGL
#ifndef WINDOWS
	if (draw_target() == 0) {
		draw_buffer_to_screen(0.9, 0.4, 1.4, 0.85, 0.0, 1.0);
		draw_rect_f3(esContext, 0.9, 0.4, 0.002, 1.4, 0.85, 0.002, 0, 0, 0, 255);
		draw_rect_f3(esContext, 0.9 - 0.005, 0.4 - 0.005, 0.002, 1.4 + 0.005, 0.85 + 0.005, 0.002, 255, 255, 255, 255);
		set_button("goto_hud", setup.view_mode, 0.9, 0.4, 1.4, 0.85, map_goto_screen, (float)VIEW_MODE_HUD, 0);
		sprintf(tmp_str, "Alt: %0.0f", ModelData.p_alt);
		draw_text_button(esContext, "map_alt", setup.view_mode, tmp_str, FONT_GREEN, 0.92, 0.75, 0.003, 0.04, ALIGN_LEFT, ALIGN_CENTER, map_null, 0.0);
		sprintf(tmp_str, "Speed: %0.0f", ModelData.speed);
		draw_text_button(esContext, "map_speed", setup.view_mode, tmp_str, FONT_GREEN, 0.92, 0.8, 0.003, 0.04, ALIGN_LEFT, ALIGN_CENTER, map_null, 0.0);
	}
#endif
#endif
	uint16_t ny = 0;
	uint8_t ny2 = 0;
	uint8_t nn = 0;
	ny++;
	if (map_type_select == 1) {
		ny2 = ny - 1;
		nn = 0;
		for (nn = 0; nn < maplen; nn++) {
			draw_box_f3(esContext, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 0, 0, 0, 200);
			draw_rect_f3(esContext, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 255, 255, 255, 200);
			sprintf(tmp_str, "change_maptype%i", nn);
			draw_button(esContext, tmp_str, setup.view_mode, mapnames[nn][MAP_NAME], FONT_WHITE, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, change_maptype, nn);
			draw_text_f3(esContext, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.003, 0.03, 0.03, FONT_WHITE, mapnames[nn][MAP_COMMENT]);
			ny2++;
		}
	}
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	draw_button(esContext, "change_maptype", setup.view_mode, mapnames[map_type][MAP_NAME], FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, change_maptype, -1);
	ny++;
	if (omap_type_select == 1) {
		ny2 = ny;
		nn = 0;
		for (nn = 0; nn < omaplen; nn++) {
			draw_box_f3(esContext, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 0, 0, 0, 200);
			draw_rect_f3(esContext, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 255, 255, 255, 200);
			sprintf(tmp_str, "change_omaptype%i", nn);
			draw_button(esContext, tmp_str, setup.view_mode, omapnames[nn][MAP_NAME], FONT_WHITE, -1.15, -0.8 + ny2 * 0.12 - 0.055, 0.002, -0.85, -0.8 + ny2 * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, change_omaptype, nn);
			ny2++;
		}
	}
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	draw_button(esContext, "change_omaptype", setup.view_mode, omapnames[omap_type][MAP_NAME], FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, change_omaptype, -1);
	ny++;
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	draw_button(esContext, "map_zoom+", setup.view_mode, "[+]", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_zoom, +1.0);
	ny++;
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	draw_button(esContext, "map_zoom-", setup.view_mode, "[-]", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_zoom, -1.0);
	ny++;
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	draw_button(esContext, "map_home", setup.view_mode, "HOME", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_goto, 0.0);
	ny++;
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	draw_button(esContext, "map_uav", setup.view_mode, "UAV", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_goto, -1.0);
	ny++;
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	if (center_map == 0) {
		draw_button(esContext, "map_center", setup.view_mode, "FREE", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_center, 0.0);
	} else if (center_map == 1) {
		draw_button(esContext, "map_center", setup.view_mode, "CENTER", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_center, 0.0);
	} else {
		draw_button(esContext, "map_center", setup.view_mode, "FOLLOW", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_center, 0.0);
	}
	ny++;
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	if (map_dir == 1) {
		draw_button(esContext, "map_dir", setup.view_mode, "DIR", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_dir_change, 0.0);
	} else if (map_dir == 2) {
		draw_button(esContext, "map_dir", setup.view_mode, "TARGET", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_dir_change, 0.0);
	} else {
		draw_button(esContext, "map_dir", setup.view_mode, "NORTH", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_dir_change, 0.0);
	}
	ny++;
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	if (map_view == 1) {
		draw_button(esContext, "map_3d", setup.view_mode, "3D", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_view_change, 0.0);
	} else {
		draw_button(esContext, "map_3d", setup.view_mode, "2D", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_view_change, 0.0);
	}
	ny++;
	if (map_view == 1) {
		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (map_color == 1) {
			draw_button(esContext, "map_color", setup.view_mode, "AC", FONT_GREEN, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_color_change, 0.0);
		} else {
			draw_button(esContext, "map_color", setup.view_mode, "AC", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_color_change, 0.0);
		}
		ny++;
		draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		if (map_side == 1) {
			draw_button(esContext, "map_side", setup.view_mode, "SIDE", FONT_GREEN, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_side_change, 0.0);
			ny++;
			draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
			draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
			if (map_rotate == 1) {
				draw_button(esContext, "map_rotate", setup.view_mode, "ROTATE", FONT_GREEN, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_rotate_change, 0.0);
			} else {
				draw_button(esContext, "map_rotate", setup.view_mode, "ROTATE", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_rotate_change, 0.0);
			}
			ny++;
		} else {
			draw_button(esContext, "map_side", setup.view_mode, "SIDE", FONT_WHITE, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_side_change, 0.0);
			ny++;
			map_rotate = 0;
			ny++;
		}
	} else {
		map_rotate = 0;
		ny++;
		ny++;
		ny++;
	}
	draw_box_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, -1.45, -0.8 + ny * 0.12 - 0.055, 0.002, -1.15, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	if (ModelData.gpsfix > 0) {
		sprintf(tmp_str, "Fix: %iD", ModelData.gpsfix);
		draw_text_button(esContext, "map_fix", setup.view_mode, tmp_str, FONT_GREEN, -1.3, -0.8 + ny * 0.12 - 0.02, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
		sprintf(tmp_str, "Sat: %i", ModelData.numSat);
		draw_text_button(esContext, "map_sats", setup.view_mode, tmp_str, FONT_GREEN, -1.3, -0.8 + ny * 0.12 + 0.03, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
	} else {
		strcpy(tmp_str, "No Fix");
		draw_text_button(esContext, "map_fix", setup.view_mode, tmp_str, FONT_WHITE, -1.3, -0.8 + ny * 0.12 - 0.02, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
		sprintf(tmp_str, "Sat: %i", ModelData.numSat);
		draw_text_button(esContext, "map_sats", setup.view_mode, tmp_str, FONT_WHITE, -1.3, -0.8 + ny * 0.12 + 0.03, 0.003, 0.04, ALIGN_CENTER, ALIGN_CENTER, map_null, 0.0);
	}
	ny = 0;
	ny++;
	draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	if (map_addmode == 0) {
		draw_button(esContext, "map_add", setup.view_mode, "ADD", FONT_WHITE, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_add, 0.0);
	} else {
		draw_button(esContext, "map_add", setup.view_mode, "ADD", FONT_GREEN, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_add, 0.0);
	}
	ny++;
	if (map_show_wp == 1) {
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_del", setup.view_mode, "DEL", FONT_WHITE, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_del, 0.0);
		ny++;
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "fms_edit", setup.view_mode, "EDIT", FONT_WHITE, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, wpedit_waypoint_edit, (float)setup.view_mode);
		ny++;
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_read_wp", setup.view_mode, "READ", FONT_WHITE, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, read_wp, 0.0);
		ny++;
		draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
		draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
		draw_button(esContext, "map_write_wp", setup.view_mode, "WRITE", FONT_WHITE, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, write_wp, 0.0);
		ny++;
	} else {
		ny++;
		ny++;
		ny++;
		ny++;
	}
//		ny++;
	draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	if (map_show_wp == 1) {
		draw_button(esContext, "map_show_wp", setup.view_mode, "WP", FONT_GREEN, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_wp, 0.0);
	} else {
		draw_button(esContext, "map_show_wp", setup.view_mode, "WP", FONT_WHITE, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_wp, 0.0);
	}
	ny++;
	draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	if (map_show_notam == 1) {
		draw_button(esContext, "map_show_notam", setup.view_mode, "NOTAM", FONT_GREEN, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_notam, 0.0);
	} else {
		draw_button(esContext, "map_show_notam", setup.view_mode, "NOTAM", FONT_WHITE, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_notam, 0.0);
	}
	ny++;
	draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	if (map_show_poi == 1) {
		draw_button(esContext, "map_show_poi", setup.view_mode, "POI", FONT_GREEN, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_poi, 0.0);
	} else {
		draw_button(esContext, "map_show_poi", setup.view_mode, "POI", FONT_WHITE, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, show_poi, 0.0);
	}
	ny++;
#ifndef RPI_NO_X
	draw_box_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 255, 255, 255, 127);
	if (nav_map == 1) {
		draw_button(esContext, "map_nav", setup.view_mode, "NAV", FONT_GREEN, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_nav, 0.0);
	} else {
		draw_button(esContext, "map_nav", setup.view_mode, "NAV", FONT_WHITE, 1.15, -0.8 + ny * 0.12 - 0.055, 0.002, 1.45, -0.8 + ny * 0.12 + 0.055, 0.002, 0.06, ALIGN_CENTER, ALIGN_CENTER, map_nav, 0.0);
	}
	ny++;
#else
	ny++;
#endif
	glEnable( GL_DEPTH_TEST );
}


void display_map (ESContext *esContext, float lat, float lon, uint8_t zoom, uint8_t _map_view, uint8_t draw_tiles, float alpha0, float alpha1, float alpha2, float grid) {
	ESMatrix modelview;
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
	char tmp_str[100];
	// calculate Altitude-Zoom
	uint32_t zz = (1<<zoom);
	alt_zoom = 25500000 / (float)zz;
	int16_t n = 0;

	if (map_startup == 0) {
		map_startup = 1;
		mapdata = GeoMap_init();
	}

	mapdata->lat = lat;
	mapdata->lon = lon;
	mapdata->zoom = zoom;
	mapdata->map_view = _map_view;
	mapdata->esContext = esContext;
	mapdata->draw_tiles = draw_tiles;
	mapdata->alpha0 = alpha0;
	mapdata->alpha1 = alpha1;
	mapdata->alpha2 = alpha2;
	mapdata->grid = grid;
	mapdata->map_color = map_color;


#ifdef SDLGL
#ifndef WINDOWS
	if (draw_target() == 0 && setup.view_mode == VIEW_MODE_MAP) {
		draw_to_buffer();
		hud_draw_horizon(esContext, 0);
		draw_to_screen();
		reset_buttons();
	}
#endif
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
#ifndef ANDROID
		glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -4.5, 4.5);
#else
		glOrthof(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -4.5, 4.5);
#endif
		glMatrixMode( GL_MODELVIEW );
	}
#else
	if (_map_view == 3 || _map_view == 4 || _map_view == 5 || _map_view == 2) {
		_map_view = 0;
	}
#endif
	if (center_map == 1 || _map_view == 3 || _map_view == 4 || _map_view == 5) {
		draw_xy(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), lat, lon, zoom, &mapdata->offset_x1, &mapdata->offset_y1);
		if (mapdata->offset_x1 < -0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0, 0);
		}
		if (mapdata->offset_x1 > 0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0, 0);
		}
		if (mapdata->offset_y1 < -0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0, 0);
		}
		if (mapdata->offset_y1 > 0.8) {
			map_goto("UAV", 0.0, 0.0, 1, -1.0, 0);
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
		esTranslate( &userData->perspective, -mapdata->offset_x1, mapdata->offset_y1, 0.0 );
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
		glTranslatef(-mapdata->offset_x1, mapdata->offset_y1, 0.0);
		if (map_side != 0) {
			glTranslatef(0.0, 0.0, -(ModelData.p_alt - ModelData.alt_offset) / alt_zoom);
		}
	} else if (_map_view == 3 || _map_view == 4 || _map_view == 5) {
		roty = 0.0;
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0015, -0.0068);

		if (setup.hud_view_stab == 1) {
			glRotatef(0.0, 1.0, 0.0, 0.0);
		} else if (setup.hud_view_stab == 2) {
			glRotatef(45.0, 1.0, 0.0, 0.0);
		} else {
			glRotatef(-ModelData.roll, 0.0, 1.0, 0.0);
			glRotatef(-ModelData.pitch, 1.0, 0.0, 0.0);
		}
		glRotatef(ModelData.yaw, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 0.0, 2.0 - 0.00 - (ModelData.p_alt - ModelData.alt_offset) / alt_zoom);
		glTranslatef(-mapdata->offset_x1, mapdata->offset_y1, 0.0);
		glMatrixMode(GL_MODELVIEW);
	} else {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef( 0.0, 0.0, -2.0 );
		glRotatef( roty, 0.0, 0.0, 1.0 );
		glTranslatef( 0.0, 0.0, 2.0 );
	}
#endif

	// Map-Scale Test
	if (zoom > 18) {
		zoom = 18;
	}


	// draw Map
	GeoMap_draw(mapdata);

#ifdef SDLGL
	if (nav_map == 1) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		esTranslate(&modelview, mapdata->offset_x1, -mapdata->offset_y1, 0.0);
		draw_circleFilled_f3_part(esContext, 0.0, 0.0, 0.00, 1.8, 0.75, 0.0, 360.0, 0, 0, 0, 127);
		draw_box_f3(esContext, -3.0, -3.0, 0.002, 3.0, 3.0, 0.002, 0, 0, 0, 127);
		glPopMatrix();
		for (n = 0; n < 360; n += 2) {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			esTranslate(&modelview, 0.0, 0.0, -2.0);
			esTranslate(&modelview, mapdata->offset_x1, -mapdata->offset_y1, 0.0);
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
			esTranslate(&modelview, -mapdata->offset_x1, mapdata->offset_y1, 0.0);
			esTranslate(&modelview, 0.0, 0.0, 2.0);
			glPopMatrix();
		}
	}
#else
	if (nav_map == 1) {
		esMatrixLoadIdentity(&modelview);
		esTranslate(&modelview, mapdata->offset_x1, -mapdata->offset_y1, 0.0);
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
		esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
		draw_circleFilled_f3_part(esContext, 0.0, 0.0, 0.00, 1.8, 0.75, 0.0, 360.0, 0, 0, 0, 127);
		draw_box_f3(esContext, -3.0, -3.0, 0.002, 3.0, 3.0, 0.002, 0, 0, 0, 127);
		for (n = 0; n < 360; n += 2) {
			esMatrixLoadIdentity(&modelview);
			esTranslate(&modelview, 0.0, 0.0, -2.0);
			esTranslate(&modelview, mapdata->offset_x1, -mapdata->offset_y1, 0.0);
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
			esTranslate(&modelview, -mapdata->offset_x1, mapdata->offset_y1, 0.0);
			esTranslate(&modelview, 0.0, 0.0, 2.0);
			esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
			esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
		}
	}
#endif
	// drawing POI's, NOTAM's and Waypoint's
	if (map_show_notam == 1) {
		draw_notam(esContext, mapdata->lat, mapdata->lon, mapdata->zoom);
	}
	if (map_show_poi == 1) {
		draw_waypoints_cup(esContext, mapdata->lat, mapdata->lon, mapdata->zoom);
	}
	if (map_show_wp == 0) {
		for (n = 0; n < MAX_POIS; n++) {
			if (POIs[n].p_lat != 0.0) {
				mark_poi(esContext, POIs[n].p_lat, POIs[n].p_long, POIs[n].name, POIs[n].type, mapdata->lat, mapdata->lon, mapdata->zoom);
			}
		}
	}
	// Mark Tracker-Position
	draw_tracker(esContext, tracker_lat, tracker_long, tracker_alt, tracker_pitch_dir, tracker_pan_dir, mapdata->lat, mapdata->lon, mapdata->zoom);
	// drawing Logfile
	map_log_show();
	// drawing Waypoint-Route
	float last_lat = ModelData.p_lat;
	float last_lon = ModelData.p_long;
	float last_alt = (ModelData.p_alt - ModelData.alt_offset);
	int flag = 0;
	if (map_show_wp == 1) {
		for (n = 1; n < MAX_WAYPOINTS; n++) {
			if (WayPoints[n].p_lat != 0.0) {
				if (n == uav_active_waypoint + 1 && n == waypoint_active) {
					mark_point(esContext, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, WayPoints[n].name, WayPoints[n].command, 3, WayPoints[n].radius, WayPoints[n].orbit, mapdata->lat, mapdata->lon, mapdata->zoom);
				} else if (n == uav_active_waypoint + 1) {
					mark_point(esContext, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, WayPoints[n].name, WayPoints[n].command, 2, WayPoints[n].radius, WayPoints[n].orbit, mapdata->lat, mapdata->lon, mapdata->zoom);
				} else if (n == waypoint_active) {
					mark_point(esContext, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, WayPoints[n].name, WayPoints[n].command, 1, WayPoints[n].radius, WayPoints[n].orbit, mapdata->lat, mapdata->lon, mapdata->zoom);
				} else {
					mark_point(esContext, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, WayPoints[n].name, WayPoints[n].command, 0, WayPoints[n].radius, WayPoints[n].orbit, mapdata->lat, mapdata->lon, mapdata->zoom);
				}
			}
		}
		if (_map_view == 3 || _map_view == 4 || _map_view == 5) {
			if (setup.hud_view_tunnel == 1) {
				mark_tunnel(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset) + 10.6, WayPoints[waypoint_active].p_lat, WayPoints[waypoint_active].p_long, WayPoints[waypoint_active].p_alt, 5, mapdata->lat, mapdata->lon, mapdata->zoom);
			}
		} else {
			draw_quad(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), ModelData.roll, ModelData.pitch, ModelData.yaw, mapdata->lat, mapdata->lon, mapdata->zoom);
		}
		mark_point(esContext, WayPoints[0].p_lat, WayPoints[0].p_long, WayPoints[0].p_alt, WayPoints[0].name, "", 0, 0.0, 0.0, mapdata->lat, mapdata->lon, mapdata->zoom);
		for (n = 1; n < MAX_WAYPOINTS; n++) {
			if (WayPoints[n].p_lat != 0.0) {
				if (flag != 0) {
					mark_route(esContext, last_lat, last_lon, last_alt, WayPoints[n].p_lat, WayPoints[n].p_long, WayPoints[n].p_alt, 0, mapdata->lat, mapdata->lon, mapdata->zoom);
				}
				flag = 1;
				last_lat = WayPoints[n].p_lat;
				last_lon = WayPoints[n].p_long;
				last_alt = WayPoints[n].p_alt;
			}
		}
		mark_route(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), WayPoints[uav_active_waypoint + 1].p_lat, WayPoints[uav_active_waypoint + 1].p_long, WayPoints[uav_active_waypoint + 1].p_alt, 1, mapdata->lat, mapdata->lon, mapdata->zoom);
	//	mark_route(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), WayPoints[waypoint_active].p_lat, WayPoints[waypoint_active].p_long, WayPoints[waypoint_active].p_alt, 1, mapdata->lat, mapdata->lon, mapdata->zoom);
	} else {
		if (_map_view == 3 || _map_view == 4 || _map_view == 5) {
			if (setup.hud_view_tunnel == 1) {
				mark_tunnel(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset) + 10.6, WayPoints[waypoint_active].p_lat, WayPoints[waypoint_active].p_long, WayPoints[waypoint_active].p_alt, 5, mapdata->lat, mapdata->lon, mapdata->zoom);
			}
		} else {
			draw_quad(esContext, ModelData.p_lat, ModelData.p_long, (ModelData.p_alt - ModelData.alt_offset), ModelData.roll, ModelData.pitch, ModelData.yaw, mapdata->lat, mapdata->lon, mapdata->zoom);
		}
	}
#ifdef SDLGL

//	map_kml_parseDoc("test.kml");

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
//		mark_point(esContext, ny2, nx2, nalt, "", "", 0, 0.1, 0.0, mapdata->lat, mapdata->lon, mapdata->zoom);
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
//			mark_point(esContext, ny2, nx2, nalt, "", "", 0, 0.1, 0.0, mapdata->lat, mapdata->lon, mapdata->zoom);
			mark_alt = get_altitude(ny2, nx2);
			if (mark_alt >= (int16_t)nalt) {
				break;
			}
		}
		mark_point(esContext, ny2, nx2, mark_alt, "", "", 5, 0.1, 0.0, mapdata->lat, mapdata->lon, mapdata->zoom);
		if (setup.hud_view_mark == 1) {
			setup.hud_view_mark = 0;
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
	// rotate map back
#ifndef SDLGL
	if (_map_view == 1) {
		esTranslate( &userData->perspective, mapdata->offset_x1, -mapdata->offset_y1, 0.0 );
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
		esTranslate( &modelview, mapdata->offset_x1, -mapdata->offset_y1, 0.0 );
	}
#else
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
#endif
	glDisable( GL_DEPTH_TEST );
	// Scale-Info
	float scale = 100.0;
	float S = 63727982 * cos((mapdata->lat * DEG2RAD)) / pow(2, (mapdata->zoom + 8));
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

	if (mapnames[map_type][MAP_NAME][0] == 0) {
		map_type = 0;
	}

//#ifndef OSX
#ifdef OSX___
	uint16_t cn = 0;
	uint16_t xn = 0;
	uint16_t mn = 0;
	uint16_t an = 0;
	uint8_t tag_start = 0;
	uint8_t tagtype = 0;
	uint8_t attrib_start = 0;
	uint8_t lastc = 0;
	uint8_t tmode = 0;
	char tmp_str2[1024];
	char tmp_str3[1024];
	sprintf(tmp_str, "%s", mapnames[map_type][MAP_COPYRIGHT]);
	for (cn = 0; cn < strlen(mapnames[map_type][MAP_COPYRIGHT]); cn++) {
		if (tmp_str[cn] == '<') {
			tag_start = 1;
		} else if (mapnames[map_type][MAP_COPYRIGHT][cn] == '>') {
			tag_start = 0;
			attrib_start = 0;
		} else if (mapnames[map_type][MAP_COPYRIGHT][cn] == '=') {
			attrib_start = 1;
			an = 0;
		} else if (mapnames[map_type][MAP_COPYRIGHT][cn] == '\'' && attrib_start == 1) {
		} else if (mapnames[map_type][MAP_COPYRIGHT][cn] == '\"' && attrib_start == 1) {
		} else if (mapnames[map_type][MAP_COPYRIGHT][cn] == 'a' && lastc == '<') {
			tagtype = 'a';
		} else if (mapnames[map_type][MAP_COPYRIGHT][cn] == '/' && lastc == '<') {
			tagtype = 0;
		} else if (tag_start == 0 && tagtype == 'a') {
			tmode = 1;
			tmp_str2[mn++] = mapnames[map_type][MAP_COPYRIGHT][cn];
			tmp_str2[mn] = 0;
		} else if (tag_start == 0) {
			tmode = 2;
			tmp_str2[mn++] = mapnames[map_type][MAP_COPYRIGHT][cn];
			tmp_str2[mn] = 0;
		} else if (attrib_start == 1) {
			tmode = 3;
			tmp_str3[an++] = mapnames[map_type][MAP_COPYRIGHT][cn];
			tmp_str3[an] = 0;
		} else {
			if (tmode == 1) {
				draw_text_button(esContext, tmp_str3, setup.view_mode, tmp_str2, FONT_PINK, -1.3 + xn * 0.035, 0.92, 0.0002, 0.06, ALIGN_LEFT, ALIGN_TOP, map_link_open, 0.0);
				xn += strlen(tmp_str2);
			} else if (tmode == 2) {
				draw_text_f3(esContext, -1.3 + xn * 0.035, 0.92, 0.0002, 0.06, 0.06, FONT_BLACK_BG, tmp_str2);
				xn += strlen(tmp_str2);
			}
			tmode = 0;
			mn = 0;
		}
		lastc = tmp_str[cn];
	}
#endif
	if (_map_view != 3 && _map_view != 4 && _map_view != 5 && setup.view_mode == VIEW_MODE_MAP) {
		map_draw_buttons(esContext);
	}
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
	display_map(esContext, lat, lon, zoom, map_view, 1, 1.0, 0.0, 0.0, 0.0);
}



