
#include <all.h>

Weather weather;

SDL_Thread *thread_weather = NULL;

void weather_parseDoc (char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlNodePtr wcur;
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
		SDL_Log("map: Document parsing failed: %s\n", docname);
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		SDL_Log("Document is Empty!!!\n");
		return;
	}
	weather.temperature = 0.0;
	weather.humidity = 0.0;
	weather.pressure = 0.0;
	weather.wind_speed = 0.0;
	weather.wind_direction = 0.0;
	weather.sun_rise[0] = 0;
	weather.sun_set[0] = 0;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"temperature"))) {
			if ((key = xmlGetProp(cur, (const xmlChar *)"value")) != NULL) {
				weather.temperature = atof((char *)key) - 273.15;
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"humidity"))) {
			if ((key = xmlGetProp(cur, (const xmlChar *)"value")) != NULL) {
				weather.humidity = atof((char *)key);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"pressure"))) {
			if ((key = xmlGetProp(cur, (const xmlChar *)"value")) != NULL) {
				weather.pressure = atof((char *)key);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"wind"))) {
			wcur = cur->xmlChildrenNode;
			while (wcur != NULL) {
				if ((!xmlStrcasecmp(wcur->name, (const xmlChar *)"speed"))) {
					if ((key = xmlGetProp(wcur, (const xmlChar *)"value")) != NULL) {
						weather.wind_speed = atof((char *)key);
						xmlFree(key);
					}
				} else if ((!xmlStrcasecmp(wcur->name, (const xmlChar *)"direction"))) {
					if ((key = xmlGetProp(wcur, (const xmlChar *)"value")) != NULL) {
						weather.wind_direction = atof((char *)key);
						xmlFree(key);
					}
				}
				wcur = wcur->next;
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"city"))) {
			wcur = cur->xmlChildrenNode;
			while (wcur != NULL) {
				if ((!xmlStrcasecmp(wcur->name, (const xmlChar *)"sun"))) {
					if ((key = xmlGetProp(wcur, (const xmlChar *)"rise")) != NULL) {
						strcpy(weather.sun_rise, (char *)key);
						xmlFree(key);
					}
					if ((key = xmlGetProp(wcur, (const xmlChar *)"set")) != NULL) {
						strcpy(weather.sun_set, (char *)key);
						xmlFree(key);
					}
				}
				wcur = wcur->next;
			}
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}

int weather_thread (void *data) {
	int n = 0;
	SDL_Log("weather: init thread\n");
	while (gui_running == 1) {
		char url[1024];
		char cmd[1024];
		sprintf(url, "http://api.openweathermap.org/data/2.5/weather?lat=%f&lon=%f&mode=xml", ModelData.p_lat, ModelData.p_long);
//		file_download("/tmp/weather.xml.tmp", url);
		sprintf(cmd, "wget -q -O/tmp/weather.xml.tmp \"%s\"", url);
		system(cmd);
		weather_parseDoc("/tmp/weather.xml.tmp");
//		SDL_Log("weather: temperature %f\n", weather.temperature);
//		SDL_Log("weather: humidity %f\n", weather.humidity);
//		SDL_Log("weather: pressure %f\n", weather.pressure);
//		SDL_Log("weather: wind_speed %f\n", weather.wind_speed);
//		SDL_Log("weather: wind_direction %f\n", weather.wind_direction);
//		SDL_Log("weather: sun_rise %s\n", weather.sun_rise);
//		SDL_Log("weather: sun_set %s\n", weather.sun_set);
		for (n = 0; n < 60 && gui_running == 1; n++) {
			SDL_Delay(1000);
		}
	}
	SDL_Log("weather: exit thread\n");
	return 0;
}

int weather_init (void) {
	SDL_Log("weather: Weather-Data copyright by http://www.openweathermap.org\n");
#ifdef SDL2
	thread_weather = SDL_CreateThread(weather_thread, NULL, NULL);
#else
	thread_weather = SDL_CreateThread(weather_thread, NULL);
#endif
	return 0;
}

int weather_exit (void) {
	SDL_WaitThread(thread_weather, NULL);
	return 0;
}

uint8_t weather_null (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

void weather_draw (ESContext *esContext, float x1, float y1) {
	char tmp_str[128];
	int yn = 0;
	sprintf(tmp_str, "temp %0.1f^C", weather.temperature);
	draw_text_button(esContext, "w_temp", VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1 + yn++ * 0.05, 0.003, 0.04, 0, 0, weather_null, 0);
	sprintf(tmp_str, "humidity %0.1f%%", weather.humidity);
	draw_text_button(esContext, "w_temp", VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1 + yn++ * 0.05, 0.003, 0.04, 0, 0, weather_null, 0);
	sprintf(tmp_str, "pressure %0.1f", weather.pressure);
	draw_text_button(esContext, "w_temp", VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1 + yn++ * 0.05, 0.003, 0.04, 0, 0, weather_null, 0);
	sprintf(tmp_str, "w-speed %0.1fkm/h", weather.wind_speed);
	draw_text_button(esContext, "w_temp", VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1 + yn++ * 0.05, 0.003, 0.04, 0, 0, weather_null, 0);
	sprintf(tmp_str, "w-dir %0.1f^", weather.wind_direction);
	draw_text_button(esContext, "w_temp", VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1 + yn++ * 0.05, 0.003, 0.04, 0, 0, weather_null, 0);
//	sprintf(tmp_str, "sun_rise %s", weather.sun_rise);
//	draw_text_button(esContext, "w_temp", VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1 + yn++ * 0.05, 0.003, 0.04, 0, 0, weather_null, 0);
//	sprintf(tmp_str, "sun_set %s", weather.sun_set);
//	draw_text_button(esContext, "w_temp", VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1, y1 + yn++ * 0.05, 0.003, 0.04, 0, 0, weather_null, 0);
}

void weather_draw_wind (ESContext *esContext, float x1, float y1) {
	char tmp_str[128];
	int yn = 0;
	float arrow_w = 7.0;
	float arrow_l = 0.02;
	float c_radius = 0.045;
	float radius = 0.04;
	float i = weather.wind_direction - 90.0;
	float i2 = weather.wind_direction - 90.0;
	if (map_dir == 1) {
		i -= ModelData.yaw;
	}
	sprintf(tmp_str, "%0.1fkm/h", weather.wind_speed);
	draw_text_button(esContext, "w_temp", VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1 + 0.04, y1 - 0.04 + yn++ * 0.05, 0.003, 0.045, 0, 0, weather_null, 0);
	sprintf(tmp_str, "%0.1f^", weather.wind_direction);
	draw_text_button(esContext, "w_temp", VIEW_MODE_HUD, tmp_str, FONT_WHITE, x1 + 0.04, y1 - 0.05 + yn++ * 0.05, 0.003, 0.045, 0, 0, weather_null, 0);
	x1 += 0.34;
	draw_circleFilled_f3(esContext, x1, y1, 0.002, c_radius, 255, 255, 255, 128);
	draw_circle_f3(esContext, x1, y1, 0.002, c_radius, 255, 255, 255, 255);
	draw_line_f3(esContext, x1 - cos(i2 * DEG2RAD) * radius, y1 - sin(i2 * DEG2RAD) * radius, 0.002, x1 + cos(i2 * DEG2RAD) * radius, y1 + sin(i2 * DEG2RAD) * radius, 0.002, 128, 128, 128, 255);
	draw_line_f3(esContext, x1 + cos(i2 * DEG2RAD) * radius, y1 + sin(i2 * DEG2RAD) * radius, 0.002, x1 + cos((i2 + arrow_w) * DEG2RAD) * (radius - arrow_l), y1 + sin((i2 + arrow_w) * DEG2RAD) * (radius - arrow_l), 0.002, 128, 128, 128, 255);
	draw_line_f3(esContext, x1 + cos(i2 * DEG2RAD) * radius, y1 + sin(i2 * DEG2RAD) * radius, 0.002, x1 + cos((i2 - arrow_w) * DEG2RAD) * (radius - arrow_l), y1 + sin((i2 - arrow_w) * DEG2RAD) * (radius - arrow_l), 0.002, 128, 128, 128, 255);
	draw_line_f3(esContext, x1 - cos(i * DEG2RAD) * radius, y1 - sin(i * DEG2RAD) * radius, 0.002, x1 + cos(i * DEG2RAD) * radius, y1 + sin(i * DEG2RAD) * radius, 0.002, 255, 0, 0, 255);
	draw_line_f3(esContext, x1 + cos(i * DEG2RAD) * radius, y1 + sin(i * DEG2RAD) * radius, 0.002, x1 + cos((i + arrow_w) * DEG2RAD) * (radius - arrow_l), y1 + sin((i + arrow_w) * DEG2RAD) * (radius - arrow_l), 0.002, 255, 0, 0, 255);
	draw_line_f3(esContext, x1 + cos(i * DEG2RAD) * radius, y1 + sin(i * DEG2RAD) * radius, 0.002, x1 + cos((i - arrow_w) * DEG2RAD) * (radius - arrow_l), y1 + sin((i - arrow_w) * DEG2RAD) * (radius - arrow_l), 0.002, 255, 0, 0, 255);
}


