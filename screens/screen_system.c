
#include <all.h>


#define FONT_MAX 32
char *fontnames[FONT_MAX] = {
	"astrology.jhf",
	"cursive.jhf",
	"cyrilc_1.jhf",
	"cyrillic.jhf",
	"futural.jhf",
	"futuram.jhf",
	"gothgbt.jhf",
	"gothgrt.jhf",
	"gothiceng.jhf",
	"gothicger.jhf",
	"gothicita.jhf",
	"gothitt.jhf",
	"greekc.jhf",
	"greek.jhf",
	"greeks.jhf",
	"japanese.jhf",
	"markers.jhf",
	"mathlow.jhf",
	"mathupp.jhf",
	"meteorology.jhf",
	"music.jhf",
	"rowmand.jhf",
	"rowmans.jhf",
	"rowmant.jhf",
	"scriptc.jhf",
	"scripts.jhf",
	"symbolic.jhf",
	"timesg.jhf",
	"timesib.jhf",
	"timesi.jhf",
	"timesrb.jhf",
	"timesr.jhf",
};

static char port_selected[100];
static char baud_selected[100];
static uint8_t resize = 0;

static char view_names[VIEW_MODE_LAST][100] = {
	"HUD",
	"TELEMETRY",
	"MAP",
	"FMS",
	"MODEL",
	"FCMENU",
	"RCFLOW",
#ifndef ANDROID
	"VIDEOLIST",
#ifdef USE_TCL
	"TCL",
#endif
#endif
	"TRACKER",
	"SYSTEM",
};

extern uint8_t view_overview;

uint8_t option_cmd(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (strcmp(name, "WEBSERV") == 0) {
		if (clientmode != 1 && setup.webport != 0) {
			if (webserv_is_running() == 1) {
				webserv_exit();
			} else {
				webserv_init();
			}
		}
	} else if (strcmp(name, "SPEAK") == 0) {
		setup.speak = 1 - setup.speak;
	} else if (strcmp(name, "LOGGING") == 0) {
		logmode = 1 - logmode;
	} else if (strcmp(name, "LOGPLAYER") == 0) {
		logplay = 1 - logplay;
		view_overview = 0;
	} else if (strcmp(name, "EXIT") == 0) {
		SDL_Event user_event;
		user_event.type = SDL_QUIT;
		SDL_PushEvent(&user_event);
	}
	return 0;
}

uint8_t overview_set(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	view_overview = 0;
	setup.view_mode = (int)data;
	view_mode_next = (int)data;
	return 0;
}

uint8_t system_baud_set(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	SDL_Log("BAUD: %s_baud = %s\n", baud_selected, name);
	if (strcmp(baud_selected, "gcs_gps") == 0) {
		setup.gcs_gps_baud = atoi(name);
		gcs_gps_exit();
		gcs_gps_init(setup.gcs_gps_port, setup.gcs_gps_baud);
	} else if (strcmp(baud_selected, "rcflow") == 0) {
		setup.rcflow_baud = atoi(name);
		rcflow_exit();
		rcflow_init(setup.rcflow_port, setup.rcflow_baud);
	} else if (strcmp(baud_selected, "jeti") == 0) {
		setup.jeti_baud = atoi(name);
		jeti_exit();
		jeti_init(setup.jeti_port, setup.jeti_baud);
	} else if (strcmp(baud_selected, "frsky") == 0) {
		setup.frsky_baud = atoi(name);
		frsky_exit();
		frsky_init(setup.frsky_port, setup.frsky_baud);
	} else if (strcmp(baud_selected, "tracker") == 0) {
		setup.tracker_baud = atoi(name);
		tracker_exit();
		tracker_init(setup.tracker_port, setup.tracker_baud);
	}
	return 0;
}

uint8_t system_baud_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	strncpy(baud_selected, name, 99);
	baud_set_callback(system_baud_set);
	baud_set_mode(VIEW_MODE_SYSTEM);
	return 0;
}

uint8_t system_device_set(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	SDL_Log("DEVICE: %s_port = %s\n", port_selected, name);
	if (strcmp(port_selected, "gcs_gps") == 0) {
		strncpy(setup.gcs_gps_port, name, 1023);
	} else if (strcmp(port_selected, "rcflow") == 0) {
		strncpy(setup.rcflow_port, name, 1023);
	} else if (strcmp(port_selected, "jeti") == 0) {
		strncpy(setup.jeti_port, name, 1023);
	} else if (strcmp(port_selected, "frsky") == 0) {
		strncpy(setup.frsky_port, name, 1023);
	} else if (strcmp(port_selected, "tracker") == 0) {
		strncpy(setup.tracker_port, name, 1023);
	}
	if (strcmp(name, "UNSET") != 0) {
		system_baud_change(port_selected, x, y, button, data, 0);
	} else {
		strncpy(baud_selected, name, 99);
		system_baud_set("1200", x, y, button, data, 0);
	}
	return 0;
}

uint8_t system_device_change(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	strncpy(port_selected, name, 99);
	device_set_callback(system_device_set);
	device_reset_filter();
	device_add_filter("ttyUSB");
	device_add_filter("ttyACM");
	device_add_filter("ttyS");
	device_add_filter("cu.");
	device_set_mode(VIEW_MODE_SYSTEM);
	return 0;
}

uint8_t system_dhclient(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	system("dhclient eth0");
	return 0;
}

uint8_t system_update(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	system("echo \"cd /tmp/ ; wget http://www.multixmedia.org/test/AutoQuad/gl-gcs/gl-gcs_last.deb && dpkg -i gl-gcs_last.deb\" > /tmp/gcs.execute");
	SDL_Event user_event;
	user_event.type = SDL_QUIT;
	SDL_PushEvent(&user_event);
	return 0;
}

uint8_t system_null(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

uint8_t system_set_font(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (setup.font < FONT_MAX - 1) {
		setup.font++;
	} else {
		setup.font = 0;
	}
	return 0;
}

uint8_t system_set_side_by_side(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	setup.side_by_side = 1 - setup.side_by_side;
	return 0;
}

uint8_t system_set_ratio(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (data == 0.0) {
		if (setup.keep_ratio == 0.0) {
			setup.keep_ratio = 1.422;
		} else {
			setup.keep_ratio = 0;
		}
	} else if (data > 0.0) {
		setup.keep_ratio += data;
	} else if (data < 0.0) {
		setup.keep_ratio += data;
	}
	if (setup.keep_ratio == 0.0) {
		aspect = (GLfloat)setup.screen_w / (GLfloat)setup.screen_h;
	} else if (setup.keep_ratio < 1.4) {
		setup.keep_ratio = 1.4;
		aspect = setup.keep_ratio;
	} else {
		aspect = setup.keep_ratio;
	}
	resize = 1;
	return 0;
}

uint8_t system_set_fullscreen(char *name, float x, float y, int8_t button, float data, uint8_t action) {
#ifdef SDL2
	if (setup.fullscreen == 0) {
		setup.fullscreen = 1;
		SDL_SetWindowFullscreen(MainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	} else {
		setup.fullscreen = 0;
		SDL_SetWindowFullscreen(MainWindow, 0);
	}
	resize = 1;
#endif
	return 0;
}

uint8_t system_set_border_x(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if ((int)data == 0) {
		setup.screen_border_x = 0;
	} else if ((int)data > 0) {
		setup.screen_border_x += (int)data;
	} else if ((int)data < 0 && setup.screen_border_x >= (int)data) {
		setup.screen_border_x += (int)data;
	}
	resize_border();
	return 0;
}

uint8_t system_set_border_y(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if ((int)data == 0) {
		setup.screen_border_y = 0;
	} else if ((int)data > 0) {
		setup.screen_border_y += (int)data;
	} else if ((int)data < 0 && setup.screen_border_y >= (int)data) {
		setup.screen_border_y += (int)data;
	}
	resize_border();
	return 0;
}

#ifdef SDLGL
void screen_overview(ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	char tmp_str[1024];
	uint8_t n = 0;
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
#endif
	reset_buttons();
	int x = 0;
	int y = 0;
	for (n = 0; n < VIEW_MODE_LAST; n++) {
		if (x >= 4) {
			x = 0;
			y += 1;
		}
#ifndef WINDOWS
#ifndef ANDROID
		draw_to_buffer();
		if (n == VIEW_MODE_HUD) {
			screen_hud(esContext);
		} else if (n == VIEW_MODE_TELEMETRY) {
			screen_telemetry(esContext);
		} else if (n == VIEW_MODE_MODEL) {
			screen_model(esContext);
		} else if (n == VIEW_MODE_RCFLOW) {
			screen_rcflow(esContext);
		} else if (n == VIEW_MODE_FMS) {
			screen_fms(esContext);
		} else if (n == VIEW_MODE_WPEDIT) {
			screen_wpedit(esContext);
		} else if (n == VIEW_MODE_MAP) {
			screen_map(esContext, lat, lon, zoom);
		} else if (n == VIEW_MODE_SYSTEM) {
			screen_system(esContext);
#ifndef ANDROID
		} else if (n == VIEW_MODE_VIDEOLIST) {
			screen_videolist(esContext);
#ifdef USE_TCL
		} else if (n == VIEW_MODE_TCL) {
			screen_tcl(esContext);
#endif
#endif
		} else if (n == VIEW_MODE_TRACKER) {
			screen_tracker(esContext);
		} else if (n == VIEW_MODE_FCMENU) {
			if (ModelData[ModelActive].teletype == TELETYPE_MULTIWII_21) {
				screen_mwi_menu(esContext);
			} else if (ModelData[ModelActive].teletype == TELETYPE_BASEFLIGHT) {
				screen_mwi_menu(esContext);
			} else if (ModelData[ModelActive].teletype == TELETYPE_GPS_NMEA) {
				screen_graph(esContext);
			} else if (ModelData[ModelActive].teletype == TELETYPE_OPENPILOT) {
				screen_openpilot(esContext);
			} else {
				screen_mavlink_menu(esContext);
			}
		}
		draw_to_screen();
		draw_buffer_to_screen(-1.422 + x * 0.71, -0.99 + y * 0.66, -1.422 + x * 0.71 + 0.71, -0.99 + y * 0.66 + 0.66, 0.002, 1.0);
		sprintf(tmp_str, "%s", view_names[n]);
		if (setup.view_mode == n) {
			draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str, FONT_GREEN, -1.422 + 0.35 + x * 0.71, -0.99 + y * 0.66, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, overview_set, (float)n);
		} else {
			draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str, FONT_WHITE, -1.422 + 0.35 + x * 0.71, -0.99 + y * 0.66, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, overview_set, (float)n);
		}
#else
		sprintf(tmp_str, "%s", view_names[n]);
		draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str, FONT_WHITE, -1.422 + 0.35 + x * 0.71, -0.99 + y * 0.66 + 0.3, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, overview_set, (float)n);
#endif
#else
		sprintf(tmp_str, "%s", view_names[n]);
		draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str, FONT_WHITE, -1.422 + 0.35 + x * 0.71, -0.99 + y * 0.66 + 0.3, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, overview_set, (float)n);
#endif
		reset_buttons();
		x++;
	}
	x = 0;
	y = 0;
	for (n = 0; n < VIEW_MODE_LAST; n++) {
		if (x >= 4) {
			x = 0;
			y += 1;
		}
		//		draw_rect_f3(esContext, -1.3 + x * 0.5, -0.8 + y * 0.4, 0.002, -1.3 + x * 0.5 + 0.5, -0.8 + y * 0.4 + 0.4, 0.002, 255, 255, 255, 255);
		//		set_button(view_names[n], setup.view_mode, -1.3 + x * 0.5, -0.8 + y * 0.4, -1.3 + x * 0.5 + 0.5, -0.8 + y * 0.4 + 0.4, overview_set, (float)n, 0);
		draw_rect_f3(esContext, -1.422 + x * 0.71, -0.99 + y * 0.66, 0.002, -1.422 + x * 0.71 + 0.71, -0.99 + y * 0.66 + 0.66, 0.002, 255, 255, 255, 255);
		set_button(view_names[n], setup.view_mode, -1.422 + x * 0.71, -0.99 + y * 0.66, -1.422 + x * 0.71 + 0.71, -0.99 + y * 0.66 + 0.66, overview_set, (float)n, 0);
		x++;
	}
	draw_text_button(esContext, "Options", setup.view_mode, "Options", FONT_PINK, 1.05, 0.55 + -2 * 0.1, 0.002, 0.08, ALIGN_CENTER, ALIGN_TOP, overview_set, (float)0);
	n = 0;
	if (setup.speak == 1) {
		draw_text_button(esContext, "SPEAK", setup.view_mode, "SPEAK", FONT_GREEN, 1.05, 0.45 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	} else {
		draw_text_button(esContext, "SPEAK", setup.view_mode, "SPEAK", FONT_WHITE, 1.05, 0.45 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	}
	if (logmode == 1) {
		draw_text_button(esContext, "LOGGING", setup.view_mode, "LOGGING", FONT_GREEN, 1.05, 0.45 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	} else {
		draw_text_button(esContext, "LOGGING", setup.view_mode, "LOGGING", FONT_WHITE, 1.05, 0.45 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	}
#ifndef OSX
	if (logplay == 1) {
		draw_text_button(esContext, "LOGPLAYER", setup.view_mode, "LOGPLAYER", FONT_GREEN, 1.05, 0.45 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	} else {
		draw_text_button(esContext, "LOGPLAYER", setup.view_mode, "LOGPLAYER", FONT_WHITE, 1.05, 0.45 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	}
#endif
	if (clientmode != 1 && setup.webport != 0) {
		if (webserv_is_running() == 1) {
			draw_text_button(esContext, "WEBSERV", setup.view_mode, "stop Webserver", FONT_GREEN, 1.05, 0.45 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
		} else {
			draw_text_button(esContext, "WEBSERV", setup.view_mode, "start Webserver", FONT_WHITE, 1.05, 0.45 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
		}
	}
	draw_text_button(esContext, "EXIT", setup.view_mode, "EXIT", FONT_GREEN, 1.05, 0.45 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
}
#else
void screen_overview(ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	char tmp_str[1024];
	uint8_t n = 0;
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
#endif
	reset_buttons();
	draw_text_button(esContext, "Screens", setup.view_mode, "Screens", FONT_PINK, -0.8, -0.6 + -2 * 0.1, 0.002, 0.08, ALIGN_CENTER, ALIGN_TOP, overview_set, (float)0);
	for (n = 0; n < VIEW_MODE_LAST; n++) {
		sprintf(tmp_str, "%s", view_names[n]);
		if (setup.view_mode == n) {
			draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str, FONT_GREEN, -0.8, -0.6 + n * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, overview_set, (float)n);
		} else {
			draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str, FONT_WHITE, -0.8, -0.6 + n * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, overview_set, (float)n);
		}
	}
	draw_text_button(esContext, "Options", setup.view_mode, "Options", FONT_PINK, 0.8, -0.6 + -2 * 0.1, 0.002, 0.08, ALIGN_CENTER, ALIGN_TOP, overview_set, (float)0);
	n = 0;
	if (setup.speak == 1) {
		draw_text_button(esContext, "SPEAK", setup.view_mode, "SPEAK", FONT_GREEN, 0.8, -0.6 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	} else {
		draw_text_button(esContext, "SPEAK", setup.view_mode, "SPEAK", FONT_WHITE, 0.8, -0.6 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	}
	if (logmode == 1) {
		draw_text_button(esContext, "LOGGING", setup.view_mode, "LOGGING", FONT_GREEN, 0.8, -0.6 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	} else {
		draw_text_button(esContext, "LOGGING", setup.view_mode, "LOGGING", FONT_WHITE, 0.8, -0.6 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	}
#ifndef OSX
	if (logplay == 1) {
		draw_text_button(esContext, "LOGPLAYER", setup.view_mode, "LOGPLAYER", FONT_GREEN, 0.8, -0.6 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	} else {
		draw_text_button(esContext, "LOGPLAYER", setup.view_mode, "LOGPLAYER", FONT_WHITE, 0.8, -0.6 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
	}
#endif
	n++;
	n++;
	n++;
	draw_text_button(esContext, "EXIT", setup.view_mode, "EXIT", FONT_WHITE, 0.8, -0.6 + n++ * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, option_cmd, 0.0);
}
#endif



void screen_system(ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
#ifndef WINDOWS
	FILE *cmd = NULL;
#endif
	char buffer[1025];
	static char ip[30];
	static char bcast[30];
	static char mask[30];
	static char hostname[30];
	static char dnsserver[30];
	static char gateway[30];
	uint32_t now_time = time(0);
	static uint32_t last_time = 0;
#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
#endif
	draw_title(esContext, "System");
	if (last_time != now_time) {
		strcpy(ip, "---.---.---.---");
		strcpy(bcast, "---.---.---.---");
		strcpy(mask, "---.---.---.---");
		strcpy(dnsserver, "---.---.---.---");
		strcpy(gateway, "---.---.---.---");
#ifndef WINDOWS
#ifndef ANDROID
#ifdef OSX
		if ((cmd = popen("LANG=C ifconfig en0 | grep \"inet \" | sed \"s|[a-zA-Z:]||g\"", "r")) != NULL) {
			while (!feof(cmd)) {
				if (fgets(buffer, 1024, cmd) != NULL) {
					sscanf(buffer, "%s %s %s", (char *)&ip, (char *)&bcast, (char *)&mask);
					//			SDL_Log("## %s, %s, %s ##\n", ip, bcast, mask);
				}
			}
			pclose(cmd);
		}
#else
		if ((cmd = popen("LANG=C ifconfig eth0 | grep \"inet addr:\" | sed \"s|[a-zA-Z:]||g\"", "r")) != NULL) {
			while (!feof(cmd)) {
				if (fgets(buffer, 1024, cmd) != NULL) {
					sscanf(buffer, "%s %s %s", (char *)&ip, (char *)&bcast, (char *)&mask);
					//			SDL_Log("## %s, %s, %s ##\n", ip, bcast, mask);
				}
			}
			pclose(cmd);
		}
		if ((cmd = popen("grep \"^nameserver \" /etc/resolv.conf | cut -d\" \" -f2", "r")) != NULL) {
			while (!feof(cmd)) {
				if (fgets(dnsserver, 1024, cmd) != NULL) {
				}
			}
		}
		pclose(cmd);
		if ((cmd = popen("route -n | grep \" 0.0.0.0.*255.255.255.0 \" | cut -d\" \" -f1", "r")) != NULL) {
			while (!feof(cmd)) {
				if (fgets(gateway, 1024, cmd) != NULL) {
				}
			}
		}
		pclose(cmd);
#endif
		if ((cmd = popen("hostname", "r")) != NULL) {
			while (!feof(cmd)) {
				if (fgets(hostname, 1024, cmd) != NULL) {
				}
			}
		}
		pclose(cmd);
#endif
#endif
		last_time = now_time;
	}
	sprintf(buffer, "Name  : %s", hostname);
	draw_text_f(esContext, -0.5, -0.8 + 1 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "IP    : %s", ip);
	draw_text_f(esContext, -0.5, -0.8 + 3 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "BCAST : %s", bcast);
	draw_text_f(esContext, -0.5, -0.8 + 4 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "MASK  : %s", mask);
	draw_text_f(esContext, -0.5, -0.8 + 5 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "DNS   : %s", dnsserver);
	draw_text_f(esContext, -0.5, -0.8 + 6 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "GATE  : %s", gateway);
	draw_text_f(esContext, -0.5, -0.8 + 7 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	draw_text_button(esContext, "system_dhclient", VIEW_MODE_SYSTEM, "<GET IP OVER DHCP>", FONT_GREEN, 0.0, -0.8 + 9 * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, system_dhclient, 0.0);
	//	draw_text_button(esContext, "system_gcs", VIEW_MODE_SYSTEM, "<UPDATE GCS>", FONT_GREEN, 0.0, -0.8 + 10 * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, system_update, 0.0);
	// Connections-Status
	char tmp_str[100];
	uint8_t n = 0;
	if (ModelData[ModelActive].teletype == TELETYPE_AUTOQUAD || ModelData[ModelActive].teletype == TELETYPE_ARDUPILOT || ModelData[ModelActive].teletype == TELETYPE_MEGAPIRATE_NG) {
		if (mavlink_connection_status(ModelActive) != 0) {
			sprintf(tmp_str, "MAVLINK %s (%i / %i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud, (uint8_t)(time(0)) - mavlink_connection_status(ModelActive));
			draw_text_button(esContext, "mavlink_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "MAVLINK %s (%i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud);
			draw_text_button(esContext, "mavlink_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_text_button(esContext, "mavlink_connection_status", VIEW_MODE_SYSTEM, "MAVLINK", FONT_TRANS, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}
	if (ModelData[ModelActive].teletype == TELETYPE_MULTIWII_21 || ModelData[ModelActive].teletype == TELETYPE_BASEFLIGHT) {
		if (mwi21_connection_status(ModelActive) != 0) {
			sprintf(tmp_str, "MULTIWII21 %s (%i / %i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud, (uint8_t)(time(0)) - mwi21_connection_status(ModelActive));
			draw_text_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "MULTIWII21 %s (%i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud);
			draw_text_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_text_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, "MULTIWII21", FONT_TRANS, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}
	if (ModelData[ModelActive].teletype == TELETYPE_BASEFLIGHT) {
		if (mwi21_connection_status(ModelActive) != 0) {
			sprintf(tmp_str, "BASEFLIGHT %s (%i / %i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud, (uint8_t)(time(0)) - mwi21_connection_status(ModelActive));
			draw_text_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "BASEFLIGHT %s (%i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud);
			draw_text_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_text_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, "BASEFLIGHT", FONT_TRANS, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}
	if (ModelData[ModelActive].teletype == TELETYPE_OPENPILOT) {
		if (openpilot_connection_status(ModelActive) != 0) {
			sprintf(tmp_str, "OPENPILOT %s (%i / %i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud, (uint8_t)(time(0)) - openpilot_connection_status(ModelActive));
			draw_text_button(esContext, "openpilot_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "OPENPILOT %s (%i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud);
			draw_text_button(esContext, "openpilot_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_text_button(esContext, "openpilot_connection_status", VIEW_MODE_SYSTEM, "OPENPILOT", FONT_TRANS, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}
	if (ModelData[ModelActive].teletype == TELETYPE_GPS_NMEA) {
		if (gps_connection_status(ModelActive) != 0) {
			sprintf(tmp_str, "NMEA-GPS %s (%i / %i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud, (uint8_t)(time(0)) - gps_connection_status(ModelActive));
			draw_text_button(esContext, "gps_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "NMEA-GPS %s (%i)", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_baud);
			draw_text_button(esContext, "gps_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_text_button(esContext, "gps_connection_status", VIEW_MODE_SYSTEM, "NMEA-GPS", FONT_TRANS, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}
	if (frsky_connection_status() != 0) {
		sprintf(tmp_str, "FRSKY %s (%i / %i)", setup.frsky_port, setup.frsky_baud, (uint8_t)(time(0)) - frsky_connection_status());
		draw_text_button(esContext, "frsky", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	} else {
		sprintf(tmp_str, "FRSKY %s (%i)", setup.frsky_port, setup.frsky_baud);
		draw_text_button(esContext, "frsky", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	}
	if (jeti_connection_status() != 0) {
		sprintf(tmp_str, "JETI %s (%i / %i)", setup.jeti_port, setup.jeti_baud, (uint8_t)(time(0)) - jeti_connection_status());
		draw_text_button(esContext, "jeti", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	} else {
		sprintf(tmp_str, "JETI %s (%i)", setup.jeti_port, setup.jeti_baud);
		draw_text_button(esContext, "jeti", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	}
	if (gcsgps_connection_status() != 0) {
		sprintf(tmp_str, "GCS-GPS %s (%i / %i)", setup.gcs_gps_port, setup.gcs_gps_baud, (uint8_t)(time(0)) - gcsgps_connection_status());
		draw_text_button(esContext, "gcs_gps", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	} else {
		sprintf(tmp_str, "GCS-GPS %s (%i)", setup.gcs_gps_port, setup.gcs_gps_baud);
		draw_text_button(esContext, "gcs_gps", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	}
	if (rcflow_connection_status() != 0) {
		sprintf(tmp_str, "RCFLOW %s (%i / %i)", setup.rcflow_port, setup.rcflow_baud, (uint8_t)(time(0)) - rcflow_connection_status());
		draw_text_button(esContext, "rcflow", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	} else {
		sprintf(tmp_str, "RCFLOW %s (%i)", setup.rcflow_port, setup.rcflow_baud);
		draw_text_button(esContext, "rcflow", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	}
	if (tracker_connection_status() != 0) {
		sprintf(tmp_str, "TRACKER %s (%i / %i)", setup.tracker_port, setup.tracker_baud, (uint8_t)(time(0)) - tracker_connection_status());
		draw_text_button(esContext, "tracker", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	} else {
		sprintf(tmp_str, "TRACKER %s (%i)", setup.tracker_port, setup.tracker_baud);
		draw_text_button(esContext, "tracker", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.2 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	}

	sprintf(tmp_str, "Font: %s (%i/%i)", fontnames[(int)setup.font], setup.font + 1, FONT_MAX);
	draw_text_button(esContext, "_font", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, 0.55, 0.2, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_font, 0.0);

	sprintf(tmp_str, "Resolution: %ix%i", esContext->width, esContext->height);
	draw_text_button(esContext, "_res", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, 0.55, 0.3, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);

	draw_text_button(esContext, "_border_x", VIEW_MODE_SYSTEM, "X-Border", FONT_GREEN, 0.55, 0.4, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_x, 0.0);
	draw_text_button(esContext, "_border_x--", VIEW_MODE_SYSTEM, "[-]", FONT_GREEN, 0.85, 0.4, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_x, -2.0);
	draw_text_button(esContext, "_border_x++", VIEW_MODE_SYSTEM, "[+]", FONT_GREEN, 0.95, 0.4, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_x, 2.0);
	draw_text_button(esContext, "_border_y", VIEW_MODE_SYSTEM, "Y-Border", FONT_GREEN, 0.55, 0.5, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_y, 0.0);
	draw_text_button(esContext, "_border_y--", VIEW_MODE_SYSTEM, "[-]", FONT_GREEN, 0.85, 0.5, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_y, -2.0);
	draw_text_button(esContext, "_border_y++", VIEW_MODE_SYSTEM, "[+]", FONT_GREEN, 0.95, 0.5, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_y, 2.0);
	sprintf(tmp_str, "Ratio(%0.1f)", setup.keep_ratio);
	draw_text_button(esContext, "ratio", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, 0.55, 0.6, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_ratio, 0.0);
	draw_text_button(esContext, "ratio--", VIEW_MODE_SYSTEM, "[-]", FONT_GREEN, 0.85, 0.6, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_ratio, -0.1);
	draw_text_button(esContext, "ratio++", VIEW_MODE_SYSTEM, "[+]", FONT_GREEN, 0.95, 0.6, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_ratio, 0.1);
	if (setup.side_by_side == 1) {
		draw_text_button(esContext, "side_by_side", VIEW_MODE_SYSTEM, "SideBySide", FONT_PINK, 0.55, 0.7, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_side_by_side, 0.1);
	} else {
		draw_text_button(esContext, "side_by_side", VIEW_MODE_SYSTEM, "SideBySide", FONT_GREEN, 0.55, 0.7, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_side_by_side, 0.1);
	}
#ifndef ANDROID
#ifdef SDL2
	if (setup.fullscreen == 0) {
		draw_text_button(esContext, "fullscreen", VIEW_MODE_SYSTEM, "TOGGLE FULLSCREEN", FONT_WHITE, 0.55, 0.7, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_fullscreen, 0.0);
	} else {
		draw_text_button(esContext, "fullscreen", VIEW_MODE_SYSTEM, "TOGGLE FULLSCREEN", FONT_GREEN, 0.55, 0.7, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_fullscreen, 0.0);
	}
#endif
#endif
	if (setup.weather_enable == 1) {
		draw_text_button(esContext, "copyright", VIEW_MODE_SYSTEM, "Weather-Data copyright by http://www.openweathermap.org", FONT_PINK, 0.0, 0.88, 0.002, 0.04, ALIGN_CENTER, ALIGN_TOP, system_null, 0.0);
	}
	draw_text_button(esContext, "copyright", VIEW_MODE_SYSTEM, "Copyright by Oliver Dippel (oliver@multixmedia.org)", FONT_PINK, 0.0, 0.93, 0.002, 0.04, ALIGN_CENTER, ALIGN_TOP, system_null, 0.0);
	screen_device(esContext);
	screen_baud(esContext);
	if (resize != 0) {
		resize = 0;
#ifdef SDL2
		glResize(esContext, setup.screen_w, setup.screen_h);
#endif
	}
}


