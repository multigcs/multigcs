
#include <all.h>

char screennames[VIEW_MODE_LAST + 2][16] = {
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
	"LAST",
	"WPEDIT",
};

char teletypes[16][16] = {
	"MULTIWII_21", "AUTOQUAD", "ARDUPILOT", "MEGAPIRATE_NG",
	"OPENPILOT", "GPS_NMEA", "FRSKY", "BASEFLIGHT",
	"HARAKIRI_ML", "---", "---", "---",
};

char statetypes[MAV_STATE_ENUM_END][16] = {
	"UNINIT",
	"BOOT",
	"CALIBRATING",
	"STANDBY",
	"ACTIVE",
	"CRITICAL",
	"EMERGENCY",
	"POWEROFF"
};

char pilottypes[MAV_AUTOPILOT_ENUM_END][64] = {
	"GENERIC",
	"PIXHAWK",
	"SLUGS",
	"ARDUPILOTMEGA",
	"OPENPILOT",
	"GENERIC_WAYPOINTS_ONLY",
	"GENERIC_WAYPOINTS_AND_SIMPLE_NAVIGATION_ONLY",
	"GENERIC_MISSION_FULL",
	"INVALID",
	"PPZ",
	"UDB",
	"FP",
	"PX4",
	"SMACCMPILOT",
	"AUTOQUAD",
	"ARMAZILA",
	"AEROB",
	"ASLUAV",
};

char dronetypes[MAV_TYPE_ENUM_END + 6][32] = {
	"GENERIC",
	"FIXED_WING",
	"QUADROTOR",
	"COAXIAL",
	"HELICOPTER",
	"ANTENNA_TRACKER",
	"GCS",
	"AIRSHIP",
	"FREE_BALLOON",
	"ROCKET",
	"GROUND_ROVER",
	"SURFACE_BOAT",
	"SUBMARINE",
	"HEXAROTOR",
	"OCTOROTOR",
	"TRICOPTER",
	"FLAPPING_WING",
	"KITE",
	"ONBOARD_CONTROLLER",
	"VTOL_DUOROTOR",
	"VTOL_QUADROTOR",
	"22",
	"23",
	"24",
	"25",
	"",
	"BL-Gimbal",
};

GcsSetup setup;
uint8_t gui_ov_lock = 0;
uint8_t key_pressed = 0;
uint8_t ModelActive = 0;
Model ModelData[MODELS_MAX];
Ground GroundData;
char keyboard_key[100];
uint8_t keyboard_shift = 0;
uint8_t keyboard_altgr = 0;
SDL_Event event;
int last_x = 0;
int last_y = 0;
int touch_fd = -1;
volatile uint8_t gui_running = 1;
float gcs_roll = 0.0;
float gcs_pitch = 0.0;
float gcs_yaw = 0.0;
uint32_t heartbeat_timer = 0;
uint32_t heartbeat_rc_timer = 0;
uint32_t blink_timer = 0;
uint32_t speak_timer = 0;
uint32_t msg_timer = 0;
uint8_t redraw_flag = 1;
uint16_t mouse_x = 0;
uint16_t mouse_y = 0;
uint8_t message = 0;
char message_txt[1024];
WayPoint WayPoints[MODELS_MAX][MAX_WAYPOINTS + 1];
PolyPoint PolyPoints[MAX_POLYPOINTS + 1];
PolyPointNoFly PolyPointsNoFly[MAX_POLYPOINTS + 1];
int8_t waypoint_active = 0;
int8_t polypoint_active = 0;
int8_t polypointnf_active = 0;
int8_t polypointnf_num = 0;
uint8_t view_mode_last = 255;
uint8_t view_mode_next = 0;
float trans_count = 0.0;
Button Buttons[MAX_BUTTONS + 1];
uint8_t connection_found = 0;
uint8_t view_overview = 0;
uint8_t view_modellist = 0;
uint8_t view_screenlist = 0;
ESContext *GlobalesContext = NULL;

#ifdef HTML_DRAWING
char display_html[HTML_MAX];
char display_html2[HTML_MAX];
#endif

#ifdef DPF_DISPLAY
SDL_Thread *thread_dpf = NULL;
#endif

SDL_Thread *thread = NULL;
SDL_Thread *thread_telemetry = NULL;

#ifdef SDL2
void SDL_KillThread(SDL_Thread *thread) {
}
#endif

char *get_datadirectory (void) {
	static char datradir[1024];
#if defined WINDOWS
	strcpy(datradir, "MultiGCS");
	char path[1024];
	path[0] = 0;
	SHGetSpecialFolderPath(HWND_DESKTOP, path, CSIDL_PROFILE, FALSE);
	sprintf(datradir, "%s/MultiGCS", path);
#elif defined ANDROID
	strcpy(datradir, "/sdcard/MultiGCS");
#else
	sprintf(datradir, "%s/.multigcs", getenv("HOME"));
#endif
	return datradir;
}

void system_say (char *text) {
	char cmd_str[1024];
	sys_message(text);
#ifndef ANDROID
#ifdef OSX
	sprintf(cmd_str, "say \"%s\" > /dev/null 2> /dev/null &", text);
	system(cmd_str);
#else
	sprintf(cmd_str, "espeak \"%s\" > /dev/null 2> /dev/null &", text);
	system(cmd_str);
#endif
#else
	Android_JNI_SayText(text);
#endif
}

#ifdef SDLGL
void save_screenshot (void) {
	char name[100];
	char tmp_str[100];
	if (setup.view_mode == VIEW_MODE_HUD) {
		strncpy(name, "hud", 99);
	} else if (setup.view_mode == VIEW_MODE_TELEMETRY) {
		strncpy(name, "telemetry", 99);
	} else if (setup.view_mode == VIEW_MODE_MODEL) {
		strncpy(name, "model", 99);
	} else if (setup.view_mode == VIEW_MODE_RCFLOW) {
		strncpy(name, "rcflow", 99);
	} else if (setup.view_mode == VIEW_MODE_FMS) {
		strncpy(name, "fms", 99);
	} else if (setup.view_mode == VIEW_MODE_WPEDIT) {
		strncpy(name, "fms", 99);
	} else if (setup.view_mode == VIEW_MODE_MAP) {
		strncpy(name, "map", 99);
	} else if (setup.view_mode == VIEW_MODE_SYSTEM) {
		strncpy(name, "system", 99);
#ifndef ANDROID
	} else if (setup.view_mode == VIEW_MODE_VIDEOLIST) {
		strncpy(name, "video", 99);
#ifdef USE_TCL
	} else if (setup.view_mode == VIEW_MODE_TCL) {
		strncpy(name, "tcl", 99);
#endif
#endif
	} else if (setup.view_mode == VIEW_MODE_TRACKER) {
		strncpy(name, "tracker", 99);
	} else if (setup.view_mode == VIEW_MODE_FCMENU) {
		strncpy(name, teletypes[ModelData[ModelActive].teletype], 99);
	}
#ifdef SDL2
	sprintf(tmp_str, "xwd -name \"%s\" -out /tmp/screen.dump; ./utils/save_screenshot.sh /tmp/screen.dump %s", SDL_GetWindowTitle(MainWindow), name);
#else
	sprintf(tmp_str, "xwd -name \"Multi-GCS\" -out /tmp/screen.dump; ./utils/save_screenshot.sh /tmp/screen.dump %s", name);
#endif
	system(tmp_str);
}
#endif

void save_screenshot2 (void) {
	char tmp_str[100];
	sprintf(tmp_str, "xwd -name \"Multi-GCS\" -out /tmp/screen.dump; ./utils/save_screenshot.sh /tmp/screen.dump dump");
	system(tmp_str);
}

SDL_Surface* CreateSurface(int width,int height) {
#ifdef SDLGL
	const SDL_PixelFormat fmt = *(WinScreen->format);
	return SDL_CreateRGBSurface(0,width,height, fmt.BitsPerPixel, fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
#else
	return NULL;
#endif
}

void reset_buttons (void) {
	uint16_t n = 0;
	for (n = 0; n < MAX_BUTTONS; n++) {
		Buttons[n].name[0] = 0;
		Buttons[n].view_mode = 0;
		Buttons[n].x1 = 0;
		Buttons[n].y1 = 0;
		Buttons[n].x2 = 0;
		Buttons[n].y2 = 0;
		Buttons[n].data = 0;
		Buttons[n].type = 0;
		Buttons[n].status = 0;
	}
}

uint8_t set_button (char *name, uint8_t view_mode, float x1, float y1, float x2, float y2, uint8_t (*callback) (char *, float, float, int8_t, float, uint8_t), float data, uint8_t type) {
	uint16_t n = 0;
	if (gui_ov_lock == 1) {
		return 0;
	}

	for (n = 0; n < MAX_BUTTONS; n++) {
		if (strcmp(Buttons[n].name, name) == 0) {
			Buttons[n].view_mode = view_mode;
			Buttons[n].x1 = x1;
			Buttons[n].y1 = y1;
			Buttons[n].x2 = x2;
			Buttons[n].y2 = y2;
			Buttons[n].data = data;
			Buttons[n].callback = callback;
			Buttons[n].type = type;
			return 0;
		} else if (Buttons[n].name[0] == 0) {
			strncpy(Buttons[n].name, name, 1023);
			Buttons[n].view_mode = view_mode;
			Buttons[n].x1 = x1;
			Buttons[n].y1 = y1;
			Buttons[n].x2 = x2;
			Buttons[n].y2 = y2;
			Buttons[n].data = data;
			Buttons[n].callback = callback;
			Buttons[n].type = type;
			return 0;
		}
	}
	SDL_Log("to many buttons\n");
	return 2;
}

int8_t check_button (uint8_t view_mode, float x, float y, uint8_t button, uint8_t event) {
	int16_t n = 0;
	if (event == BUTTON_RELEASE) {
		for (n = 0; n < MAX_BUTTONS; n++) {
			if (Buttons[n].status == BUTTON_PRESS) {
				if (Buttons[n].type == 2) {
					(*Buttons[n].callback)(Buttons[n].name, x - Buttons[n].start_x, y - Buttons[n].start_y, button, Buttons[n].data, BUTTON_RELEASED);
					Buttons[n].start_x = x;
					Buttons[n].start_y = y;
				} else {
					(*Buttons[n].callback)(Buttons[n].name, x, y, button, Buttons[n].data, BUTTON_RELEASED);
				}
			}
			Buttons[n].status = 0;
		}
	} else if (event == BUTTON_MOVE) {
		for (n = 0; n < MAX_BUTTONS; n++) {
			if (Buttons[n].status == BUTTON_PRESS) {
				if (Buttons[n].type == 2) {
					(*Buttons[n].callback)(Buttons[n].name, x - Buttons[n].start_x, y - Buttons[n].start_y, button, Buttons[n].data, BUTTON_MOVED);
					Buttons[n].start_x = x;
					Buttons[n].start_y = y;
				} else {
					(*Buttons[n].callback)(Buttons[n].name, x, y, button, Buttons[n].data, BUTTON_MOVED);
				}
				return n;
			}
		}
	}
	for (n = MAX_BUTTONS - 1; n >= 0; n--) {
		if (Buttons[n].name[0] != 0 && Buttons[n].view_mode == view_mode && x > Buttons[n].x1 && x < Buttons[n].x2 && y > Buttons[n].y1 && y < Buttons[n].y2) {
			if (Buttons[n].type == 0 && event == BUTTON_PRESS) {
//				SDL_Log("CB: %s\n", Buttons[n].name);
				if ((*Buttons[n].callback)(Buttons[n].name, x, y, button, Buttons[n].data, BUTTON_PRESSED) == 0) {
					return n;
				}
			} else if (Buttons[n].type == 1 || Buttons[n].type == 2) {
				if (event == BUTTON_PRESS) {
					if (button == 4 || button == 5) {
						(*Buttons[n].callback)(Buttons[n].name, x, y, button, Buttons[n].data, BUTTON_PRESSED);
					} else {
						Buttons[n].status = event;
						Buttons[n].start_x = x;
						Buttons[n].start_y = y;
						if (Buttons[n].type == 2) {
							(*Buttons[n].callback)(Buttons[n].name, x - Buttons[n].start_x, y - Buttons[n].start_y, button, Buttons[n].data, BUTTON_PRESSED);
							Buttons[n].start_x = x;
							Buttons[n].start_y = y;
						} else {
							(*Buttons[n].callback)(Buttons[n].name, x, y, button, Buttons[n].data, BUTTON_PRESSED);
						}
					}
					return n;
				}
			}
		}
	}
	return -1;
}

uint8_t need_bluetooth (void) {
	if (strstr(ModelData[ModelActive].telemetry_port, "/dev/rfcomm") > 0) {
		return 1;
	}
	return 0;
}

void stop_telemetry (uint8_t modelid) {
	mwi21_exit(modelid);
	mavlink_exit(modelid);
	gps_exit(modelid);
	openpilot_exit(modelid);
	frsky_mode(0);
}

void reset_telemetry (uint8_t modelid) {
	stop_telemetry(modelid);
	if (clientmode == 1) {
		return;
	}
#ifdef ANDROID
	Android_JNI_ConnectUsbSerial(ModelData[modelid].telemetry_baud);
#endif
	if (ModelData[modelid].teletype == TELETYPE_MULTIWII_21 || ModelData[modelid].teletype == TELETYPE_BASEFLIGHT) {
		mwi21_init(modelid, ModelData[modelid].telemetry_port, ModelData[modelid].telemetry_baud);
	} else if (ModelData[modelid].teletype == TELETYPE_GPS_NMEA) {
		gps_init(modelid, ModelData[modelid].telemetry_port, ModelData[modelid].telemetry_baud);
	} else if (ModelData[modelid].teletype == TELETYPE_OPENPILOT) {
		openpilot_init(modelid, ModelData[modelid].telemetry_port, ModelData[modelid].telemetry_baud);
	} else if (ModelData[modelid].teletype == TELETYPE_FRSKY) {
		frsky_mode(1);
	} else if (ModelData[modelid].teletype == 255) {
	} else {
		mavlink_init(modelid, ModelData[modelid].telemetry_port, ModelData[modelid].telemetry_baud);
	}
}

void set_telemetry (uint8_t modelid, char *device, uint32_t baud) {
	if (clientmode == 1) {
		return;
	}
//	strncpy(ModelData[modelid].telemetry_port, device, 1023);
//	ModelData[modelid].telemetry_baud = baud;

#ifdef ANDROID
	if (strncmp(ModelData[modelid].telemetry_port, "bt:", 3) == 0) {
		Android_JNI_ConnectSerial(ModelData[modelid].telemetry_port + 3);
	}
#endif
	reset_telemetry(modelid);
}

void setup_waypoints (void) {
	int n = 0;
	int modeln = 0;
	for (n = 0; n < MAX_POLYPOINTS; n++) {
		PolyPoints[n].p_lat = 0.0;
		PolyPoints[n].p_long = 0.0;
	}
	for (n = 0; n < MAX_POLYPOINTS; n++) {
		PolyPointsNoFly[n].p_lat = 0.0;
		PolyPointsNoFly[n].p_long = 0.0;
		PolyPointsNoFly[n].p_alt = 0.0;
		PolyPointsNoFly[n].mode = 0;
		PolyPointsNoFly[n].num = 0;
	}
	for (modeln = 0; modeln < MODELS_MAX; modeln++) {
		for (n = 0; n < MAX_WAYPOINTS; n++) {
			WayPoints[modeln][n].p_lat = 0.0;
			WayPoints[modeln][n].p_long = 0.0;
			WayPoints[modeln][n].p_alt = 0.0;
			WayPoints[modeln][n].param1 = 0.0;
			WayPoints[modeln][n].param2 = 2.0;
			WayPoints[modeln][n].param3 = 0.0;
			WayPoints[modeln][n].param4 = 0.0;
			WayPoints[modeln][n].frametype = 0;
			WayPoints[modeln][n].name[0] = 0;
			WayPoints[modeln][n].command[0] = 0;
			WayPoints[modeln][n].type = 0;
		}
		WayPoints[modeln][0].p_lat = 50.2942581;
		WayPoints[modeln][0].p_long = 9.1228580;
		WayPoints[modeln][0].p_alt = 150.0;
		WayPoints[modeln][0].param1 = 0.0;
		WayPoints[modeln][0].param2 = 2.0;
		WayPoints[modeln][0].param3 = 0.0;
		WayPoints[modeln][0].param4 = 0.0;
		WayPoints[modeln][0].frametype = 0;
		WayPoints[modeln][0].type = 1;
		strncpy(WayPoints[modeln][0].name, "HOME", 127);
		strncpy(WayPoints[modeln][0].command, "", 127);
	}
	GroundData.p_lat = WayPoints[ModelActive][0].p_lat;
	GroundData.p_long = WayPoints[ModelActive][0].p_long;
	GroundData.p_alt = WayPoints[ModelActive][0].p_alt;
	GroundData.dir = 0.0;
	GroundData.active = 0;
	GroundData.followme = 0;
	GroundData.fm_alt = 15.0;
	GroundData.fm_radius = 6.0;
	GroundData.sp_alt = 15.0;
	GroundData.sp_radius = 2.0;
	GroundData.wifibc_rssi[0] = 0;
	GroundData.wifibc_rssi[1] = 0;
	GroundData.wifibc_rssi[2] = 0;
	GroundData.wifibc_rssi[3] = 0;
	SurveySetup.name[0] = 0;
	SurveySetup.interval = 10;
	SurveySetup.pos = 1900;
	SurveySetup.type = 0;
	SurveySetup.num = 0;
	SurveySetup.triggermode = 0;
	SurveySetup.options = 0;
	SurveySetup.mode = 1; // 0 = cam, 1 = fixed distance
	SurveySetup.angle = 0.0;
	SurveySetup.grid_x = 20.0; // abstand in metern
	SurveySetup.grid_y = 20.0; // abstand in metern
	SurveySetup.film_width = 36.0;  // 35 mm standard film
	SurveySetup.film_height = 24.0; // 35 mm standard film
	SurveySetup.sensor_mult = 1.62; // Formatfaktor / APS-C-Sensor (Canon)
	SurveySetup.lense = 20.0; // Brennweite in mm
	SurveySetup.overlap = 1.2;
	SurveySetup.alt = 30.0;
	SurveySetup.alt_abs = 0;
}

void sys_message (char *msg) {
	strncpy(message_txt, msg, 1023);
	if (message_txt[strlen(message_txt) - 1] == '\n') {
		message_txt[strlen(message_txt) - 1] = 0;
	}
	message = 255;
	redraw_flag = 1;
}

void setup_save (void) {
	if (clientmode == 1) {
		return;
	}
	FILE *fr;
	int n = 0;
	int nn = 0;
	if (setup.calibration_mode > 0) {
		setup.calibration_mode = 1;
	}
//	SDL_Log("** saving file\n");
	char filename[1024];
	sprintf(filename, "%s/setup.cfg", get_datadirectory());
	fr = fopen(filename, "wb");
	if (fr != 0) {
		fprintf(fr, "view_mode		%i\n", setup.view_mode);
		fprintf(fr, "contrast		%i\n", setup.contrast);
		fprintf(fr, "screen_w		%i\n", setup.screen_w);
		fprintf(fr, "screen_h		%i\n", setup.screen_h);
		fprintf(fr, "screen_border_x		%i\n", setup.screen_border_x);
		fprintf(fr, "screen_border_y		%i\n", setup.screen_border_y);
		fprintf(fr, "keep_ratio		%f\n", setup.keep_ratio);
		fprintf(fr, "fullscreen		%i\n", setup.fullscreen);
		fprintf(fr, "borderless		%i\n", setup.borderless);
		fprintf(fr, "\n");
		fprintf(fr, "lat			%0.8f\n", lat);
		fprintf(fr, "lon			%0.8f\n", lon);
		fprintf(fr, "zoom			%i\n", zoom);
		fprintf(fr, "map_type		%i\n", map_type);
		fprintf(fr, "omap_type		%i\n", omap_type);
		fprintf(fr, "center_map		%i\n", center_map);
		fprintf(fr, "weather_enable	%i\n", setup.weather_enable);
		fprintf(fr, "\n");
		fprintf(fr, "gcs_gps_port		%s\n", setup.gcs_gps_port);
		fprintf(fr, "gcs_gps_baud		%i\n", setup.gcs_gps_baud);
		fprintf(fr, "\n");
		fprintf(fr, "rcflow_port		%s\n", setup.rcflow_port);
		fprintf(fr, "rcflow_baud		%i\n", setup.rcflow_baud);
		fprintf(fr, "\n");
		fprintf(fr, "jeti_port		%s\n", setup.jeti_port);
		fprintf(fr, "jeti_baud		%i\n", setup.jeti_baud);
		fprintf(fr, "\n");
		fprintf(fr, "frsky_port		%s\n", setup.frsky_port);
		fprintf(fr, "frsky_baud		%i\n", setup.frsky_baud);
		fprintf(fr, "\n");
		fprintf(fr, "tracker_port		%s\n", setup.tracker_port);
		fprintf(fr, "tracker_baud		%i\n", setup.tracker_baud);
		fprintf(fr, "\n");
		fprintf(fr, "volt_min		%0.1f\n", setup.volt_min);
		fprintf(fr, "speak			%i\n", setup.speak);
		fprintf(fr, "\n");
		fprintf(fr, "hud_view_screen		%i\n", setup.hud_view_screen);
		fprintf(fr, "hud_view_video		%i\n", setup.hud_view_video);
		fprintf(fr, "hud_view_map		%i\n", setup.hud_view_map);
		fprintf(fr, "hud_view_tunnel		%i\n", setup.hud_view_tunnel);
		fprintf(fr, "\n");
		fprintf(fr, "map_view		%i\n", map_view);
		fprintf(fr, "map_show_profile	%i\n", map_show_profile);
		fprintf(fr, "\n");
		fprintf(fr, "webport			%i\n", setup.webport);
		fprintf(fr, "\n");
		fprintf(fr, "gearth_interval		%f\n", setup.gearth_interval);
		fprintf(fr, "\n");
		fprintf(fr, "touchscreen_device	%s\n", setup.touchscreen_device);
		fprintf(fr, "calibration_mode	%i\n", setup.calibration_mode);
		fprintf(fr, "calibration_min_x	%i\n", setup.calibration_min_x);
		fprintf(fr, "calibration_max_x	%i\n", setup.calibration_max_x);
		fprintf(fr, "calibration_min_y	%i\n", setup.calibration_min_y);
		fprintf(fr, "calibration_max_y	%i\n", setup.calibration_max_y);
		fprintf(fr, "\n");
		fprintf(fr, "videolist_lastfile	%s\n", videolist_lastfile);
#ifdef USE_WIFIBC
		fprintf(fr, "\n");
		fprintf(fr, "wifibc_device			%s\n", setup.wifibc_device);
		fprintf(fr, "wifibc_channel			%i\n", setup.wifibc_channel);
		fprintf(fr, "wifibc_port			%i\n", setup.wifibc_port);
		fprintf(fr, "wifibc_blocksize			%i\n", setup.wifibc_blocksize);
		fprintf(fr, "wifibc_packetlen			%i\n", setup.wifibc_packetlen);
		fprintf(fr, "wifibc_record				%i\n", setup.wifibc_record);
#endif
#ifdef USE_OPENCV
		fprintf(fr, "\n");
		fprintf(fr, "qrcheck			%i\n", setup.qrcheck);
		fprintf(fr, "opencv_file		%s\n", setup.opencv_file);
		fprintf(fr, "opencv_device		%i\n", setup.opencv_device);
		fprintf(fr, "opencv_features		%i\n", setup.opencv_features);
#endif
#ifdef USE_V4L
		fprintf(fr, "\n");
		fprintf(fr, "videocapture_device	%s\n", setup.videocapture_device);
		fprintf(fr, "videocapture_width	%i\n", setup.videocapture_width);
		fprintf(fr, "videocapture_height	%i\n", setup.videocapture_height);
#endif
		fprintf(fr, "\n");
		fprintf(fr, "mavlink_tcp_server		%s\n", setup.mavlink_tcp_server);
		fprintf(fr, "mavlink_tcp_port		%i\n", setup.mavlink_tcp_port);
		fprintf(fr, "mavlink_udp_port		%i\n", setup.mavlink_udp_port);
		fprintf(fr, "mavlink_forward_udp_local_port		%i\n", setup.mavlink_forward_udp_local_port);
		fprintf(fr, "mavlink_forward_udp_remote_port		%i\n", setup.mavlink_forward_udp_remote_port);
		fprintf(fr, "mavlink_forward_udp_remote_ip		%s\n", setup.mavlink_forward_udp_remote_ip);
#if defined USE_APRS
		fprintf(fr, "\n");
		fprintf(fr, "aprs_server		%s\n", setup.aprs_server);
		fprintf(fr, "aprs_port		%i\n", setup.aprs_port);
		fprintf(fr, "aprs_filter	%s\n", setup.aprs_filter);
		fprintf(fr, "aprs_enable		%i\n", setup.aprs_enable);
#endif
		fprintf(fr, "waypoint_active		%i\n", waypoint_active);
		fprintf(fr, "\n");
		fprintf(fr, "Ground_lat		%f\n", GroundData.p_lat);
		fprintf(fr, "Ground_long		%f\n", GroundData.p_long);
		fprintf(fr, "Ground_alt		%f\n", GroundData.p_alt);
		fprintf(fr, "Ground_dir		%f\n", GroundData.dir);
		fprintf(fr, "Ground_fm_alt	%f\n", GroundData.fm_alt);
		fprintf(fr, "Ground_fm_radius	%f\n", GroundData.fm_radius);
		fprintf(fr, "Ground_sp_alt	%f\n", GroundData.sp_alt);
		fprintf(fr, "Ground_sp_radius	%f\n", GroundData.sp_radius);
		fprintf(fr, "\n");
		fprintf(fr, "SurveySetup.name	%s\n", SurveySetup.name);
		fprintf(fr, "SurveySetup.interval	%i\n", SurveySetup.interval);
		fprintf(fr, "SurveySetup.pos	%i\n", SurveySetup.pos);
		fprintf(fr, "SurveySetup.type	%i\n", SurveySetup.type);
		fprintf(fr, "SurveySetup.num	%i\n", SurveySetup.num);
		fprintf(fr, "SurveySetup.triggermode	%i\n", SurveySetup.triggermode);
		fprintf(fr, "SurveySetup.options	%i\n", SurveySetup.options);
		fprintf(fr, "SurveySetup.mode	%i\n", SurveySetup.mode);
		fprintf(fr, "SurveySetup.angle	%f\n", SurveySetup.angle);
		fprintf(fr, "SurveySetup.grid_x	%f\n", SurveySetup.grid_x);
		fprintf(fr, "SurveySetup.grid_y	%f\n", SurveySetup.grid_y);
		fprintf(fr, "SurveySetup.film_width	%f\n", SurveySetup.film_width);
		fprintf(fr, "SurveySetup.film_height	%f\n", SurveySetup.film_height);
		fprintf(fr, "SurveySetup.sensor_mult	%f\n", SurveySetup.sensor_mult);
		fprintf(fr, "SurveySetup.lense	%f\n", SurveySetup.lense);
		fprintf(fr, "SurveySetup.overlap	%f\n", SurveySetup.overlap);
		fprintf(fr, "SurveySetup.alt		%f\n", SurveySetup.alt);
		fprintf(fr, "SurveySetup.alt_abs	%i\n", SurveySetup.alt_abs);
		fprintf(fr, "\n");
		fprintf(fr, "SwarmSetup.master		%i\n", SwarmSetup.master);
		fprintf(fr, "SwarmSetup.yaw_mode	%i\n", SwarmSetup.yaw_mode);
		fprintf(fr, "SwarmSetup.rotate	%i\n", SwarmSetup.rotate);
		for (n = 0; n < 4; n++) {
			fprintf(fr, "SwarmSetup.slave%i		%i\n", n, SwarmSetup.slave[n]);
			fprintf(fr, "SwarmSetup.offset_x%i	%i\n", n, SwarmSetup.offset_x[n]);
			fprintf(fr, "SwarmSetup.offset_y%i	%i\n", n, SwarmSetup.offset_y[n]);
			fprintf(fr, "SwarmSetup.offset_z%i	%i\n", n, SwarmSetup.offset_z[n]);
		}
		fprintf(fr, "\n");
		fprintf(fr, "ModelActive		%i\n", ModelActive);
		for (n = 0; n < MODELS_MAX; n++) {
			fprintf(fr, "\n");
			fprintf(fr, "[%i]\n", n);
			fprintf(fr, "telemetry_port		%s\n", ModelData[n].telemetry_port);
			fprintf(fr, "telemetry_baud		%i\n", ModelData[n].telemetry_baud);
			fprintf(fr, "deviceid		%s\n", ModelData[n].deviceid);
			fprintf(fr, "use_deviceid		%i\n", ModelData[n].use_deviceid);
			fprintf(fr, "mavlink_sysid		%i\n", ModelData[n].mavlink_sysid);
			fprintf(fr, "mavlink_forward	%i\n", ModelData[n].mavlink_forward);
			fprintf(fr, "model_name		%s\n", ModelData[n].name);
			fprintf(fr, "model_sysstr		%s\n", ModelData[n].sysstr);
			fprintf(fr, "telemetry_type		%i\n", ModelData[n].teletype);
			fprintf(fr, "pilottype		%i\n", ModelData[n].pilottype);
			fprintf(fr, "dronetype		%i\n", ModelData[n].dronetype);
			fprintf(fr, "Model_lat		%f\n", ModelData[n].p_lat);
			fprintf(fr, "Model_long		%f\n", ModelData[n].p_long);
			fprintf(fr, "Model_alt		%f\n", ModelData[n].p_alt);
			fprintf(fr, "Model_alt_offset		%f\n", ModelData[n].alt_offset);
			fprintf(fr, "Model_netip		%s\n", ModelData[n].netip);
			fprintf(fr, "Model_netport		%i\n", ModelData[n].netport);
			fprintf(fr, "Model_get_param		%i\n", ModelData[n].get_param);
			fprintf(fr, "\n");
			fprintf(fr, "[waypoints]\n");
			for (nn = 0; nn < MAX_WAYPOINTS; nn++) {
			if (WayPoints[ModelActive][nn].p_lat != 0.0) {
					fprintf(fr, "name	%s\n", WayPoints[n][nn].name);
					fprintf(fr, "command	%s\n", WayPoints[n][nn].command);
					fprintf(fr, "lat	%0.8f\n", WayPoints[n][nn].p_lat);
					fprintf(fr, "lon	%0.8f\n", WayPoints[n][nn].p_long);
					fprintf(fr, "alt	%f\n", WayPoints[n][nn].p_alt);
					fprintf(fr, "param1	%f\n", WayPoints[n][nn].param1);
					fprintf(fr, "param2	%f\n", WayPoints[n][nn].param2);
					fprintf(fr, "param3	%f\n", WayPoints[n][nn].param3);
					fprintf(fr, "param4	%f\n", WayPoints[n][nn].param4);
					fprintf(fr, "type	%i\n", WayPoints[n][nn].type);
					fprintf(fr, "frametype %i\n", WayPoints[n][nn].frametype);
					fprintf(fr, "\n");
				}
			}
		}
		fprintf(fr, "\n");
		fprintf(fr, "[polypoints]\n");
		for (n = 0; n < MAX_POLYPOINTS; n++) {
			if (PolyPoints[n].p_lat != 0.0) {
				fprintf(fr, "lat	%0.8f\n", PolyPoints[n].p_lat);
				fprintf(fr, "lon	%0.8f\n", PolyPoints[n].p_long);
				fprintf(fr, "\n");
			}
		}
		fprintf(fr, "\n");
		fprintf(fr, "[polypoints_nofly]\n");
		for (n = 0; n < MAX_POLYPOINTS; n++) {
			if (PolyPointsNoFly[n].p_lat != 0.0) {
				fprintf(fr, "lat	%0.8f\n", PolyPointsNoFly[n].p_lat);
				fprintf(fr, "lon	%0.8f\n", PolyPointsNoFly[n].p_long);
				fprintf(fr, "alt	%0.8f\n", PolyPointsNoFly[n].p_alt);
				fprintf(fr, "mode	%i\n", PolyPointsNoFly[n].mode);
				fprintf(fr, "num	%i\n", PolyPointsNoFly[n].num);
				fprintf(fr, "\n");
			}
		}
		fclose(fr);
	} else {
		SDL_Log("Can not save setup-file: %s\n", filename);
	}
}

void setup_load (void) {
	FILE *fr;
	char line[1024];
	char var[1024];
	char val[1024];
	int mode = 0;
	int model_n = 0;
	int wp_num = 0;
	int pp_num = 1;
	int ppnf_num = 1;
	strncpy(setup.gcs_gps_port, "/dev/ttyUSB20", 1023);
	setup.gcs_gps_baud = 9600;
	strncpy(setup.rcflow_port, "/dev/ttyUSB21", 1023);
	setup.rcflow_baud = 115200;
	strncpy(setup.jeti_port, "/dev/ttyUSB10", 1023);
	setup.jeti_baud = 9600;
	strncpy(setup.frsky_port, "/dev/ttyUSB30", 1023);
	setup.frsky_baud = 9600;
	strncpy(setup.tracker_port, "/dev/ttyUSB40", 1023);
	setup.tracker_baud = 38400;
	setup.fullscreen = 0;
	setup.borderless = 0;
	setup.screen_w = SCREEN_W;
	setup.screen_h = SCREEN_H;
	setup.screen_border_x = 0;
	setup.screen_border_y = 0;
	setup.keep_ratio = 1.4222;
	setup.touchscreen_device[0] = 0;
	keyboard_key[0] = 0;
	setup.calibration_mode = 1;
	setup.calibration_min_x = 1000;
	setup.calibration_max_x = 3000;
	setup.calibration_min_y = 1000;
	setup.calibration_max_y = 3000;
	setup.hud_view_screen = 0;
	setup.hud_view_stab = 0;
	setup.hud_view_map = 0;
	setup.hud_view_video = 0;
	setup.hud_view_tunnel = 0;
	setup.hud_view_mark = 0;
	setup.webport = 8080;
	setup.gearth_interval = 1.0;
	setup.volt_min = 11.0;
	setup.speak = 0;
	setup.view_mode = 0;
	setup.contrast = 0;
	strcpy(setup.videocapture_device, "/dev/video0");
	setup.qrcheck = 0;
	setup.weather_enable = 1;
	strcpy(setup.mavlink_tcp_server, "127.0.0.1");
	setup.mavlink_tcp_port = 5760;
	setup.mavlink_udp_port = 14550;
	setup.mavlink_forward_udp_local_port = 14561;
	setup.mavlink_forward_udp_remote_port = 14560;
	strcpy(setup.mavlink_forward_udp_remote_ip, "127.0.0.1");
	map_type = 1;

#ifdef USE_WIFIBC
	strcpy(setup.wifibc_device, "wlan1");
	setup.wifibc_channel = 13;
	setup.wifibc_port = 0;
	setup.wifibc_blocksize = 8;
	setup.wifibc_packetlen = 1024;
	setup.wifibc_record = 0;
#endif

#if defined USE_APRS
	setup.aprs_server[0] = 0;
	strcpy(setup.aprs_server, "146.229.162.182");
	setup.aprs_port = 10153;
	setup.aprs_filter[0] = 0;
	setup.aprs_enable = 0;
	SwarmSetup.active = 0;
	SwarmSetup.yaw_mode = 0;
	SwarmSetup.rotate = 0;
#endif
#ifdef ANDROID
	setup.opencv_device = 0;
#else
	setup.opencv_device = -1;
#endif
	setup.opencv_file[0] = 0;
	setup.opencv_features = 0;
	setup.videocapture_width = 640;
	setup.videocapture_height = 480;
	for (model_n = 0; model_n < MODELS_MAX; model_n++) {
		sprintf(ModelData[model_n].name, "Model%i", model_n + 1);
		strcpy(ModelData[model_n].sysstr, "");
		ModelData[model_n].chancount = 8;
		strcpy(ModelData[model_n].telemetry_port, "");
		ModelData[model_n].telemetry_baud = 115200;
		ModelData[model_n].teletype = 0;
		ModelData[model_n].serial_fd = -1;
		ModelData[model_n].dronetype = 250;
		ModelData[model_n].pilottype = 250;
		strcpy(ModelData[model_n].deviceid, "");
		ModelData[model_n].use_deviceid = 0;
		ModelData[model_n].mavlink_sysid = 0;
		ModelData[model_n].mavlink_forward = 1;

		ModelData[model_n].sysid = 250;
		ModelData[model_n].compid = 0;
		ModelData[model_n].p_lat = 50.2942581;
		ModelData[model_n].p_long = 9.1228580;
		ModelData[model_n].p_alt = 150.0;
		ModelData[model_n].alt_offset = 0.0;

		ModelData[model_n].next_lat = 0.0;
		ModelData[model_n].next_long = 0.0;
		ModelData[model_n].next_alt = 0.0;
		ModelData[model_n].next_count = 0;

		strcpy(ModelData[model_n].netip, "127.0.0.1");
		ModelData[model_n].netport = 5760;
		ModelData[model_n].get_param = 0;
		ModelData[model_n].heartbeat = 0;

		ModelData[model_n].follow = 0;
	}
	model_n = 0;
	char filename[1024];
	sprintf(filename, "%s/setup.cfg", get_datadirectory());
	fr = fopen (filename, "r");
	if (fr != 0) {
	        while(fgets(line, 100, fr) != NULL) {
	                var[0] = 0;
	                val[0] = 0;
	                sscanf (line, "%s %s", (char *)&var, (char *)&val);
	                if (mode == 0) {
	                        if (strcmp(var, "view_mode") == 0) {
					setup.view_mode = atoi(val);
					view_mode_next = setup.view_mode;
	                        } else if (strcmp(var, "volt_min") == 0) {
					setup.volt_min = atof(val);
	                        } else if (strcmp(var, "contrast") == 0) {
					setup.contrast = atoi(val);
	                        } else if (strcmp(var, "screen_w") == 0) {
					setup.screen_w = atoi(val);
	                        } else if (strcmp(var, "screen_h") == 0) {
					setup.screen_h = atoi(val);
	                        } else if (strcmp(var, "screen_border_x") == 0) {
					setup.screen_border_x = atoi(val);
	                        } else if (strcmp(var, "screen_border_y") == 0) {
					setup.screen_border_y = atoi(val);
	                        } else if (strcmp(var, "keep_ratio") == 0) {
					setup.keep_ratio = atof(val);
	                        } else if (strcmp(var, "speak") == 0) {
					setup.speak = atoi(val);
	                        } else if (strcmp(var, "fullscreen") == 0) {
					setup.fullscreen = atoi(val);
	                        } else if (strcmp(var, "borderless") == 0) {
					setup.borderless = atoi(val);
	                        } else if (strcmp(var, "lat") == 0) {
					lat = atof(val);
	                        } else if (strcmp(var, "lon") == 0) {
	                                lon = atof(val);
	                        } else if (strcmp(var, "zoom") == 0) {
	                                zoom = atoi(val);
	                        } else if (strcmp(var, "waypoint_active") == 0) {
	                                waypoint_active = atoi(val);
	                        } else if (strcmp(var, "gcs_gps_port") == 0) {
	                                strncpy(setup.gcs_gps_port, val, 1023);
	                        } else if (strcmp(var, "gcs_gps_baud") == 0) {
	                                setup.gcs_gps_baud = atoi(val);
	                        } else if (strcmp(var, "rcflow_port") == 0) {
	                                strncpy(setup.rcflow_port, val, 1023);
	                        } else if (strcmp(var, "rcflow_baud") == 0) {
	                                setup.rcflow_baud = atoi(val);
	                        } else if (strcmp(var, "jeti_port") == 0) {
	                                strncpy(setup.jeti_port, val, 1023);
	                        } else if (strcmp(var, "jeti_baud") == 0) {
	                                setup.jeti_baud = atoi(val);
	                        } else if (strcmp(var, "frsky_port") == 0) {
	                                strncpy(setup.frsky_port, val, 1023);
	                        } else if (strcmp(var, "frsky_baud") == 0) {
	                                setup.frsky_baud = atoi(val);
	                        } else if (strcmp(var, "tracker_port") == 0) {
	                                strncpy(setup.tracker_port, val, 1023);
	                        } else if (strcmp(var, "tracker_baud") == 0) {
	                                setup.tracker_baud = atoi(val);
	                        } else if (strcmp(var, "map_type") == 0) {
	                                map_type = atoi(val);
	                        } else if (strcmp(var, "omap_type") == 0) {
	                                omap_type = atoi(val);
	                        } else if (strcmp(var, "center_map") == 0) {
	                                center_map = atoi(val);
	                        } else if (strcmp(var, "touchscreen_device") == 0) {
	                                strncpy(setup.touchscreen_device, val, 200);
	                        } else if (strcmp(var, "calibration_mode") == 0) {
	                                setup.calibration_mode = atoi(val);
	                        } else if (strcmp(var, "calibration_min_x") == 0) {
	                                setup.calibration_min_x = atoi(val);
	                        } else if (strcmp(var, "calibration_max_x") == 0) {
	                                setup.calibration_max_x = atoi(val);
	                        } else if (strcmp(var, "calibration_min_y") == 0) {
	                                setup.calibration_min_y = atoi(val);
	                        } else if (strcmp(var, "calibration_max_y") == 0) {
	                                setup.calibration_max_y = atoi(val);
	                        } else if (strcmp(var, "videolist_lastfile") == 0) {
	                                strncpy(videolist_lastfile, val, 1023);
	                        } else if (strcmp(var, "hud_view_screen") == 0) {
	                                setup.hud_view_screen = atoi(val);
	                        } else if (strcmp(var, "hud_view_map") == 0) {
	                                setup.hud_view_map = atoi(val);
	                                setup.hud_view_map = atoi(val);
	                        } else if (strcmp(var, "hud_view_video") == 0) {
	                                setup.hud_view_video = atoi(val);
	                        } else if (strcmp(var, "hud_view_tunnel") == 0) {
	                                setup.hud_view_tunnel = atoi(val);
	                        } else if (strcmp(var, "map_view") == 0) {
	                                map_view = atoi(val);
	                        } else if (strcmp(var, "map_show_profile") == 0) {
	                                map_show_profile = atoi(val);
	                        } else if (strcmp(var, "webport") == 0) {
	                                setup.webport = atoi(val);
	                        } else if (strcmp(var, "gearth_interval") == 0) {
	                                setup.gearth_interval = atoi(val);
#ifdef USE_WIFIBC
	                        } else if (strcmp(var, "wifibc_device") == 0) {
	                                strncpy(setup.wifibc_device, val, 127);
	                        } else if (strcmp(var, "wifibc_channel") == 0) {
	                                setup.wifibc_channel = atoi(val);
	                        } else if (strcmp(var, "wifibc_port") == 0) {
	                                setup.wifibc_port = atoi(val);
	                        } else if (strcmp(var, "wifibc_blocksize") == 0) {
	                                setup.wifibc_blocksize = atoi(val);
	                        } else if (strcmp(var, "wifibc_packetlen") == 0) {
	                                setup.wifibc_packetlen = atoi(val);
	                        } else if (strcmp(var, "wifibc_record") == 0) {
	                                setup.wifibc_record = atoi(val);
#endif
	                        } else if (strcmp(var, "videocapture_device") == 0) {
	                                strncpy(setup.videocapture_device, val, 1023);
	                        } else if (strcmp(var, "qrcheck") == 0) {
	                                setup.qrcheck = atoi(val);
	                        } else if (strcmp(var, "opencv_file") == 0) {
	                                strncpy(setup.opencv_file, val, 1024);
	                        } else if (strcmp(var, "opencv_device") == 0) {
	                                setup.opencv_device = atoi(val);
	                        } else if (strcmp(var, "opencv_features") == 0) {
	                                setup.opencv_features = atoi(val);
	                        } else if (strcmp(var, "videocapture_width") == 0) {
	                                setup.videocapture_width = atoi(val);
	                        } else if (strcmp(var, "videocapture_height") == 0) {
	                                setup.videocapture_height = atoi(val);
	                        } else if (strcmp(var, "Ground_lat") == 0) {
	                                GroundData.p_lat = atof(val);
	                        } else if (strcmp(var, "Ground_long") == 0) {
	                                GroundData.p_long = atof(val);
	                        } else if (strcmp(var, "Ground_alt") == 0) {
	                                GroundData.p_alt = atof(val);
	                        } else if (strcmp(var, "Ground_dir") == 0) {
	                                GroundData.dir = atof(val);
	                        } else if (strcmp(var, "Ground_fm_alt") == 0) {
	                                GroundData.fm_alt = atof(val);
	                        } else if (strcmp(var, "Ground_fm_radius") == 0) {
	                                GroundData.fm_radius = atof(val);
	                        } else if (strcmp(var, "Ground_sp_alt") == 0) {
	                                GroundData.sp_alt = atof(val);
	                        } else if (strcmp(var, "Ground_sp_radius") == 0) {
	                                GroundData.sp_radius = atof(val);
	                        } else if (strcmp(var, "weather_enable") == 0) {
	                                setup.weather_enable = atoi(val);
	                        } else if (strcmp(var, "mavlink_tcp_server") == 0) {
	                                strncpy(setup.mavlink_tcp_server, val, 128);
	                        } else if (strcmp(var, "mavlink_tcp_port") == 0) {
	                                setup.mavlink_tcp_port = atoi(val);
	                        } else if (strcmp(var, "mavlink_udp_port") == 0) {
	                                setup.mavlink_udp_port = atoi(val);
	                        } else if (strcmp(var, "mavlink_forward_udp_local_port") == 0) {
	                                setup.mavlink_forward_udp_local_port = atoi(val);
	                        } else if (strcmp(var, "mavlink_forward_udp_remote_port") == 0) {
	                                setup.mavlink_forward_udp_remote_port = atoi(val);
	                        } else if (strcmp(var, "mavlink_forward_udp_remote_ip") == 0) {
	                                strcpy(setup.mavlink_forward_udp_remote_ip, val);
#if defined USE_APRS
	                        } else if (strcmp(var, "aprs_server") == 0) {
	                                strncpy(setup.aprs_server, val, 128);
	                        } else if (strcmp(var, "aprs_port") == 0) {
	                                setup.aprs_port = atoi(val);
	                        } else if (strcmp(var, "aprs_filter") == 0) {
	                                strncpy(setup.aprs_filter, val, 128);
	                        } else if (strcmp(var, "aprs_enable") == 0) {
	                                setup.aprs_enable = atoi(val);
#endif
	                        } else if (strcmp(var, "SurveySetup.name") == 0) {
	                                strncpy(SurveySetup.name, val, 1000);
	                        } else if (strcmp(var, "SurveySetup.interval") == 0) {
	                               SurveySetup.interval  = atoi(val);
	                        } else if (strcmp(var, "SurveySetup.pos") == 0) {
	                                SurveySetup.pos = atoi(val);
	                        } else if (strcmp(var, "SurveySetup.type") == 0) {
	                                SurveySetup.type = atoi(val);
	                        } else if (strcmp(var, "SurveySetup.num") == 0) {
	                                SurveySetup.num = atoi(val);
	                        } else if (strcmp(var, "SurveySetup.triggermode") == 0) {
	                                SurveySetup.triggermode = atoi(val);
	                        } else if (strcmp(var, "SurveySetup.options") == 0) {
	                                SurveySetup.options = atoi(val);
	                        } else if (strcmp(var, "SurveySetup.mode") == 0) {
	                                SurveySetup.mode = atoi(val);
	                        } else if (strcmp(var, "SurveySetup.angle") == 0) {
	                                SurveySetup.angle = atof(val);
	                        } else if (strcmp(var, "SurveySetup.grid_x") == 0) {
	                                SurveySetup.grid_x = atof(val);
	                        } else if (strcmp(var, "SurveySetup.grid_y") == 0) {
	                                SurveySetup.grid_y = atof(val);
	                        } else if (strcmp(var, "SurveySetup.film_width") == 0) {
	                                SurveySetup.film_width = atof(val);
	                        } else if (strcmp(var, "SurveySetup.film_height") == 0) {
	                                SurveySetup.film_height = atof(val);
	                        } else if (strcmp(var, "SurveySetup.sensor_mult") == 0) {
	                                SurveySetup.sensor_mult = atof(val);
	                        } else if (strcmp(var, "SurveySetup.lense") == 0) {
	                                SurveySetup.lense = atof(val);
	                        } else if (strcmp(var, "SurveySetup.overlap") == 0) {
	                                SurveySetup.overlap = atof(val);
	                        } else if (strcmp(var, "SurveySetup.alt") == 0) {
	                                SurveySetup.alt = atof(val);
	                        } else if (strcmp(var, "SurveySetup.alt_abs") == 0) {
	                                SurveySetup.alt_abs = atoi(val);
	                        } else if (strcmp(var, "SwarmSetup.master") == 0) {
	                                SwarmSetup.master = atoi(val);
	                        } else if (strcmp(var, "SwarmSetup.yaw_mode") == 0) {
	                                SwarmSetup.yaw_mode = atoi(val);
	                        } else if (strcmp(var, "SwarmSetup.rotate") == 0) {
	                                SwarmSetup.rotate = atoi(val);
	                        } else if (strncmp(var, "SwarmSetup.slave", 16) == 0) {
									int nn = atoi(var + 16);
	                                SwarmSetup.slave[nn] = atoi(val);
	                        } else if (strncmp(var, "SwarmSetup.offset_x", 19) == 0) {
									int nn = atoi(var + 19);
	                                SwarmSetup.offset_x[nn] = atoi(val);
	                        } else if (strncmp(var, "SwarmSetup.offset_y", 19) == 0) {
									int nn = atoi(var + 19);
	                                SwarmSetup.offset_y[nn] = atoi(val);
	                        } else if (strncmp(var, "SwarmSetup.offset_z", 19) == 0) {
									int nn = atoi(var + 19);
	                                SwarmSetup.offset_z[nn] = atoi(val);
	                        } else if (strcmp(var, "ModelActive") == 0) {
	                                ModelActive = atoi(val);
	                        } else if (strcmp(var, "model_name") == 0) {
	                                strncpy(ModelData[model_n].name, val, 199);
	                        } else if (strcmp(var, "model_sysstr") == 0) {
	                                strncpy(ModelData[model_n].sysstr, val, 199);
	                        } else if (strcmp(var, "telemetry_port") == 0) {
	                                strncpy(ModelData[model_n].telemetry_port, val, 1023);
	                        } else if (strcmp(var, "telemetry_baud") == 0) {
	                                ModelData[model_n].telemetry_baud = atoi(val);
	                        } else if (strcmp(var, "telemetry_type") == 0) {
	                                ModelData[model_n].teletype = atoi(val);
	                        } else if (strcmp(var, "pilottype") == 0) {
	                                ModelData[model_n].pilottype = atoi(val);
	                        } else if (strcmp(var, "dronetype") == 0) {
	                                ModelData[model_n].dronetype = atoi(val);
	                        } else if (strcmp(var, "deviceid") == 0) {
	                                strcpy(ModelData[model_n].deviceid, val);
	                        } else if (strcmp(var, "use_deviceid") == 0) {
	                                ModelData[model_n].use_deviceid = atoi(val);
	                        } else if (strcmp(var, "mavlink_sysid") == 0) {
	                                ModelData[model_n].mavlink_sysid = atoi(val);
	                        } else if (strcmp(var, "mavlink_forward") == 0) {
	                                ModelData[model_n].mavlink_forward = atoi(val);
	                        } else if (strcmp(var, "Model_lat") == 0) {
	                                ModelData[model_n].p_lat = atof(val);
	                        } else if (strcmp(var, "Model_long") == 0) {
	                                ModelData[model_n].p_long = atof(val);
	                        } else if (strcmp(var, "Model_alt") == 0) {
	                                ModelData[model_n].p_alt = atof(val);
	                        } else if (strcmp(var, "Model_alt_offset") == 0) {
	                                ModelData[model_n].alt_offset = atof(val);
	                        } else if (strcmp(var, "Model_netip") == 0) {
	                                strcpy(ModelData[model_n].netip, val);
	                        } else if (strcmp(var, "Model_netport") == 0) {
	                                ModelData[model_n].netport = atoi(val);
	                        } else if (strcmp(var, "Model_get_param") == 0) {
	                                ModelData[model_n].get_param = atoi(val);
	                        } else if (strcmp(var, "[waypoints]") == 0) {
	                                mode = 1;
									wp_num = 0;
	                        } else if (strcmp(var, "[polypoints]") == 0) {
	                                mode = 2;
	                        } else if (strcmp(var, "[polypoints_nofly]") == 0) {
	                                mode = 3;
	                        } else if (var[0] == '[') {
	                                model_n = atoi(var + 1);
	                                mode = 0;
	                        }
	                } else if (mode == 1) {
	                        if (var[0] == 0) {
									wp_num++;
									WayPoints[model_n][wp_num].p_lat = 0.0;
									WayPoints[model_n][wp_num].p_long = 0.0;
									WayPoints[model_n][wp_num].p_alt = 0.0;
									WayPoints[model_n][wp_num].param1 = 0.0;
									WayPoints[model_n][wp_num].param2 = 0.0;
									WayPoints[model_n][wp_num].param3 = 0.0;
									WayPoints[model_n][wp_num].param4 = 0.0;
									WayPoints[model_n][wp_num].name[0] = 0;
									WayPoints[model_n][wp_num].command[0] = 0;
									WayPoints[model_n][wp_num].type = 0;
									WayPoints[model_n][wp_num].frametype = 0;
	                        } else if (strcmp(var, "name") == 0) {
	                                strncpy(WayPoints[model_n][wp_num].name, val, 127);
	                        } else if (strcmp(var, "command") == 0) {
	                                strncpy(WayPoints[model_n][wp_num].command, val, 127);
	                        } else if (strcmp(var, "lat") == 0) {
	                                WayPoints[model_n][wp_num].p_lat = atof(val);
	                        } else if (strcmp(var, "lon") == 0) {
	                                WayPoints[model_n][wp_num].p_long = atof(val);
	                        } else if (strcmp(var, "alt") == 0) {
	                                WayPoints[model_n][wp_num].p_alt = atof(val);
	                        } else if (strcmp(var, "param1") == 0) {
	                                WayPoints[model_n][wp_num].param1 = atof(val);
	                        } else if (strcmp(var, "param2") == 0) {
	                                WayPoints[model_n][wp_num].param2 = atof(val);
	                        } else if (strcmp(var, "param3") == 0) {
	                                WayPoints[model_n][wp_num].param3 = atof(val);
	                        } else if (strcmp(var, "param4") == 0) {
	                                WayPoints[model_n][wp_num].param4 = atof(val);
	                        } else if (strcmp(var, "type") == 0) {
	                                WayPoints[model_n][wp_num].type = atoi(val);
	                        } else if (strcmp(var, "frametype") == 0) {
	                                WayPoints[model_n][wp_num].frametype = atoi(val);
	                        } else if (strcmp(var, "[polypoints]") == 0) {
	                                mode = 2;
	                        } else if (strcmp(var, "[polypoints_nofly]") == 0) {
	                                mode = 3;
	                        } else if (strcmp(var, "[waypoints]") == 0) {
	                                mode = 1;
									wp_num = 0;
	                        } else if (var[0] == '[') {
	                                model_n = atoi(var + 1);
	                                mode = 0;
	                        }
	                } else if (mode == 2) {
	                        if (var[0] == 0) {
	                                if (PolyPoints[pp_num].p_lat != 0.0) {
	                                        pp_num++;
	                                        PolyPoints[pp_num].p_lat = 0.0;
	                                        PolyPoints[pp_num].p_long = 0.0;
	                                }
	                        } else if (strcmp(var, "lat") == 0) {
	                                PolyPoints[pp_num].p_lat = atof(val);
	                        } else if (strcmp(var, "lon") == 0) {
	                                PolyPoints[pp_num].p_long = atof(val);
	                        } else if (strcmp(var, "[polypoints_nofly]") == 0) {
	                                mode = 3;
	                        } else if (strcmp(var, "[waypoints]") == 0) {
	                                mode = 1;
									wp_num = 0;
	                        } else if (var[0] == '[') {
	                                model_n = atoi(var + 1);
	                                mode = 0;
	                        }
	                } else if (mode == 3) {
	                        if (var[0] == 0) {
	                                if (PolyPointsNoFly[ppnf_num].p_lat != 0.0) {
	                                        ppnf_num++;
	                                        PolyPointsNoFly[ppnf_num].p_lat = 0.0;
	                                        PolyPointsNoFly[ppnf_num].p_long = 0.0;
	                                }
	                        } else if (strcmp(var, "lat") == 0) {
	                                PolyPointsNoFly[ppnf_num].p_lat = atof(val);
	                        } else if (strcmp(var, "lon") == 0) {
	                                PolyPointsNoFly[ppnf_num].p_long = atof(val);
	                        } else if (strcmp(var, "alt") == 0) {
	                                PolyPointsNoFly[ppnf_num].p_alt = atof(val);
	                        } else if (strcmp(var, "mode") == 0) {
	                                PolyPointsNoFly[ppnf_num].mode = atoi(val);
	                        } else if (strcmp(var, "num") == 0) {
	                                PolyPointsNoFly[ppnf_num].num = atoi(val);
									map_polynf_num = PolyPointsNoFly[ppnf_num].num + 1;
	                        } else if (strcmp(var, "[polypoints]") == 0) {
	                                mode = 2;
	                        } else if (strcmp(var, "[waypoints]") == 0) {
	                                mode = 1;
									wp_num = 0;
	                        } else if (var[0] == '[') {
	                                model_n = atoi(var + 1);
	                                mode = 0;
	                        }
	                }
	        }
	        fclose(fr);
	} else {
		SDL_Log("setup: Can not load setup-file: %s\n", filename);
	}
	if (setup.calibration_mode > 0) {
		setup.calibration_mode = 1;
	}
	strncpy(WayPoints[ModelActive][0].name, "HOME", 127);
	serial_info_update();
	for (model_n = 0; model_n < MODELS_MAX; model_n++) {
		if (strcmp(ModelData[model_n].telemetry_port, "UDP") == 0 || strcmp(ModelData[model_n].telemetry_port, "TCP") == 0) {
		} else if (ModelData[model_n].use_deviceid == 1) {
			ModelData[model_n].telemetry_port[0] = 0;
			serial_get_device_by_id(ModelData[model_n].deviceid, ModelData[model_n].telemetry_port);
		}
	}
}

void next_point (float x_origin, float y_origin, float winkel, float r1, float *nx1, float *ny1) {
	float angle = toRad((winkel) * -1.0);
	float x1 = r1 * cos(angle);
	float y1 = r1 * sin(angle);
	*nx1 = x_origin - x1;
	*ny1 = y_origin + y1;
}

void next_point_ll (ESContext *esContext, float mark_long, float mark_lat, float winkel, float r1, float *nx1, float *ny1) {
	float angle = toRad((winkel) * -1.0);
	int mark_x = long2x(mark_long, lon, zoom);
	int mark_y = lat2y(mark_lat, lat, zoom);
	float x1 = r1 * cos(angle);
	float y1 = r1 * sin(angle);
	float new_x = mark_x - x1;
	float new_y = mark_y - y1;
	*nx1 = x2long(new_x, lon, zoom);
	*ny1 = y2lat(new_y, lat, zoom);
}

int calc_fov (float film_width, float film_height, float sensor_mult, float lense, float dist, float *w, float *h) {
	float sensor_width = film_width / sensor_mult;
	float sensor_height = film_height / sensor_mult;
	float dist_mm = dist * 1000;
	float half_fov_w = (atan(sensor_width / (2 * lense)));
	float half_fov_h = (atan(sensor_height / (2 * lense)));
	*w = 2 * (dist_mm * tan(half_fov_w)) / 1000.0;
	*h = 2 * (dist_mm * tan(half_fov_h)) / 1000.0;
	return 0;
}

void check_events (ESContext *esContext, SDL_Event event) {
	static uint8_t mousemode = 0;
	static uint8_t mousewheel_flag = 0;
	static float mousestart_x = 0.0;
	static float mousestart_y = 0.0;

	if (event.type == SDL_QUIT) {
		ShutDown( esContext );
		exit(0);
#ifdef SDL2
	} else if (event.type == SDL_DROPFILE) {
		SDL_Log("## SDL_DROPFILE: %s ##\n", event.drop.file);
	} else if (event.type == SDL_WINDOWEVENT) {
		if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			int w = 0;
			int h = 0;
			SDL_GetWindowSize(MainWindow, &w, &h);
#ifdef SDLGL
			glResize(esContext, w, h);
#endif
		}
	} else if (event.type == SDL_SYSWMEVENT) {
		SDL_Log("## SDL_SYSWMEVENT ##\n");
#else
	} else if (event.type == SDL_VIDEORESIZE) {
#ifdef SDLGL
//		glResize(esContext, event.resize.w, event.resize.h);
#endif
#endif
	} else if (event.type == SDL_KEYUP) {
		char keyname[1024];
		strncpy(keyname, SDL_GetKeyName(event.key.keysym.sym), 1023);
		int n = 0;
		for(n = 0; n < strlen(keyname); n++ ) {
			keyname[n] = tolower(keyname[n]);
		}
		if (strcmp(keyname, "right") == 0) {
			key_pressed &= ~(1<<0);
		} else if (strcmp(keyname, "left") == 0) {
			key_pressed &= ~(1<<1);
		} else if (strcmp(keyname, "up") == 0) {
			key_pressed &= ~(1<<2);
		} else if (strcmp(keyname, "down") == 0) {
			key_pressed &= ~(1<<3);
		} else if (strcmp(keyname, "[+]") == 0 || strcmp(keyname, "keypad +") == 0) {
			key_pressed &= ~(1<<4);
		} else if (strcmp(keyname, "[-]") == 0 || strcmp(keyname, "keypad -") == 0) {
			key_pressed &= ~(1<<5);
		} else if (strcmp(keyname, "[4]") == 0 || strcmp(keyname, "keypad 4") == 0) {
			ModelData[ModelActive].roll -= 3.0;
		} else if (strcmp(keyname, "[6]") == 0 || strcmp(keyname, "keypad 6") == 0) {
			ModelData[ModelActive].roll += 3.0;
		} else if (strcmp(keyname, "[8]") == 0 || strcmp(keyname, "keypad 8") == 0) {
			ModelData[ModelActive].pitch -= 3.0;
		} else if (strcmp(keyname, "[2]") == 0 || strcmp(keyname, "keypad 2") == 0) {
			ModelData[ModelActive].pitch += 3.0;
		} else if (strcmp(keyname, "right shift") == 0 || strcmp(keyname, "left shift") == 0) {
			keyboard_shift = 0;
		} else if (strcmp(keyname, "alt gr") == 0) {
			keyboard_altgr = 0;
		}
	} else if (event.type == SDL_KEYDOWN) {
		char keyname[1024];
		strncpy(keyname, SDL_GetKeyName(event.key.keysym.sym), 1023);
		int n = 0;
		for(n = 0; n < strlen(keyname); n++ ) {
			keyname[n] = tolower(keyname[n]);
		}
		event.type = 0;
		if (strcmp(keyname, "right shift") == 0 || strcmp(keyname, "left shift") == 0) {
			keyboard_shift = 1;
		}
		if (strcmp(keyname, "alt gr") == 0) {
			keyboard_altgr = 1;
		}
		if (keyboard_shift == 1 && strcmp(keyname, "1") == 0) {
			strcpy(keyboard_key, "!");
		} else if (keyboard_shift == 1 && strcmp(keyname, "2") == 0) {
			strcpy(keyboard_key, "\"");
		} else if (keyboard_shift == 1 && strcmp(keyname, "3") == 0) {
			strcpy(keyboard_key, "§");
		} else if (keyboard_shift == 1 && strcmp(keyname, "4") == 0) {
			strcpy(keyboard_key, "$");
		} else if (keyboard_shift == 1 && strcmp(keyname, "5") == 0) {
			strcpy(keyboard_key, "%");
		} else if (keyboard_shift == 1 && strcmp(keyname, "6") == 0) {
			strcpy(keyboard_key, "&");
		} else if (keyboard_shift == 1 && strcmp(keyname, "7") == 0) {
			strcpy(keyboard_key, "/");
		} else if (keyboard_shift == 1 && strcmp(keyname, "8") == 0) {
			strcpy(keyboard_key, "(");
		} else if (keyboard_shift == 1 && strcmp(keyname, "9") == 0) {
			strcpy(keyboard_key, ")");
		} else if (keyboard_shift == 1 && strcmp(keyname, "0") == 0) {
			strcpy(keyboard_key, "=");
		} else if (keyboard_shift == 1 && strcmp(keyname, ",") == 0) {
			strcpy(keyboard_key, ";");
		} else if (keyboard_shift == 1 && strcmp(keyname, ".") == 0) {
			strcpy(keyboard_key, ":");
		} else if (keyboard_shift == 1 && strcmp(keyname, "-") == 0) {
			strcpy(keyboard_key, "_");
		} else if (keyboard_shift == 1 && strcmp(keyname, "+") == 0) {
			strcpy(keyboard_key, "*");
		} else if (keyboard_shift == 1 && strcmp(keyname, "#") == 0) {
			strcpy(keyboard_key, "'");
		} else if (keyboard_shift == 1 && strcmp(keyname, "^") == 0) {
			strcpy(keyboard_key, "°");
		} else if (keyboard_shift == 1 && strcmp(keyname, "<") == 0) {
			strcpy(keyboard_key, ">");
		} else if (keyboard_shift == 1 && strcmp(keyname, "world 63") == 0) {
			strcpy(keyboard_key, "?");
		} else if (keyboard_shift == 1 && strcmp(keyname, "world 20") == 0) {
			strcpy(keyboard_key, "`");
		} else if (keyboard_shift == 1) {
			strcpy(keyboard_key, keyname);
			keyboard_key[0] = keyboard_key[0] - 32;
		} else if (keyboard_altgr == 1 && strcmp(keyname, "7") == 0) {
			strcpy(keyboard_key, "{");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "8") == 0) {
			strcpy(keyboard_key, "[");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "9") == 0) {
			strcpy(keyboard_key, "]");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "0") == 0) {
			strcpy(keyboard_key, "}");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "#") == 0) {
			strcpy(keyboard_key, "`");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "<") == 0) {
			strcpy(keyboard_key, "|");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "e") == 0) {
			strcpy(keyboard_key, "€");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "m") == 0) {
			strcpy(keyboard_key, "µ");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "world 63") == 0) {
			strcpy(keyboard_key, "\\");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "world 20") == 0) {
			strcpy(keyboard_key, "¸");
		} else if (keyboard_altgr == 1 && strcmp(keyname, "q") == 0) {
			strcpy(keyboard_key, "@");
		} else if (strcmp(keyname, "world 63") == 0) {
			strcpy(keyboard_key, "ß");
		} else if (strcmp(keyname, "world 20") == 0) {
			strcpy(keyboard_key, "´");
		} else {
			strncpy(keyboard_key, keyname, 99);
			int n = 0;
			for(n = 0; n < strlen(keyboard_key); n++ ) {
				keyboard_key[n] = tolower(keyboard_key[n]);
			}
		}
		redraw_flag = 1;

#ifdef ANDROID
	} else if (event.type == SDL_MOUSEMOTION) {
	} else if (event.type == SDL_FINGERMOTION) {
		float x = (int)(event.tfinger.x * (float)setup.screen_w);
		float y = (int)(event.tfinger.y * (float)setup.screen_h);
		event.button.button = 1;
		event.button.x = x;
		event.button.y = y;
#else
	} else if (event.type == SDL_MOUSEMOTION) {
#endif
		event.type = 0;
#ifdef SDL2
		// Bug in SDL2 ???
		if (event.button.button == 4) {
			event.button.button = 3;
		}
#endif
		mouse_x = event.button.x;
		mouse_y = event.button.y;
		float bx = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
		float by = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
		if (check_button(setup.view_mode, bx, by, event.button.button, BUTTON_MOVE) != -1) {
			redraw_flag = 1;
			return;
		}
		if (mousemode == 1) {
			float x1 = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
			float y1 = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
			x1 += mapdata->offset_x1;
			y1 += mapdata->offset_y1;
			int16_t bx = (x1 / aspect + 1.0) / 2.0 * (float)esContext->width;
			int16_t by = (y1 + 1.0) / 2.0 * (float)esContext->height;
			float mouse_long = x2long(bx, lon, zoom);
			float mouse_lat = y2lat(by, lat, zoom);
			if (waypoint_active >= 0) {
				if (waypoint_active == 0) {
					WayPoints[ModelActive][waypoint_active].p_alt = get_altitude(mouse_lat, mouse_long);
				} else {
					int16_t zz = get_altitude(mouse_lat, mouse_long);
					if (WayPoints[ModelActive][waypoint_active].p_alt < zz) {
						WayPoints[ModelActive][waypoint_active].p_alt = zz;
					}
				}
				WayPoints[ModelActive][waypoint_active].p_lat = mouse_lat;
				WayPoints[ModelActive][waypoint_active].p_long = mouse_long;
			} else if (polypoint_active >= 0) {
				PolyPoints[polypoint_active].p_lat = mouse_lat;
				PolyPoints[polypoint_active].p_long = mouse_long;
			} else if (polypointnf_active >= 0) {
				PolyPointsNoFly[polypointnf_active].p_lat = mouse_lat;
				PolyPointsNoFly[polypointnf_active].p_long = mouse_long;
			} else {
				mapdata->offset_x1 -= x1 - mousestart_x;
				mapdata->offset_y1 -= y1 - mousestart_y;
			}
		} else	if (setup.view_mode == VIEW_MODE_MAP) {
			float x1 = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
			float y1 = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
			if (x1 > -0.3 && x1 < -0.0 && y1 > 0.9 && y1 < 0.95) {
				return;
			} else if (x1 < 0.3 && x1 > 0.0 && y1 > 0.9 && y1 < 0.95) {
				return;
			} else if (x1 > -0.6 && x1 < -0.3 && y1 > 0.9 && y1 < 0.95) {
				return;
			} else if (x1 < 0.6 && x1 > 0.3 && y1 > 0.9 && y1 < 0.95) {
				return;
			}
			x1 += mapdata->offset_x1;
			y1 += mapdata->offset_y1;
			int16_t bx = (x1 / aspect + 1.0) / 2.0 * (float)esContext->width;
			int16_t by = (y1 + 1.0) / 2.0 * (float)esContext->height;
			float mouse_long = x2long(bx, lon, zoom);
			float mouse_lat = y2lat(by, lat, zoom);
			int mouse_alt = get_altitude(mouse_lat, mouse_long);
			int ret_dd = 0;
			int ret_dm = 0;
			int ret_id = 0;
			int ret_im = 0;
			get_declination(mouse_lat, mouse_long, mouse_alt, &ret_dd, &ret_dm, &ret_id, &ret_im);
			char msg[200];
			sprintf(msg, "POS: %f, %f (ALT_G:%im MAG_D:%id%02im I:%id%02im)\n", mouse_lat, mouse_long, mouse_alt, ret_dd, ret_dm, ret_id, ret_im);
			sys_message(msg);
		}
		redraw_flag = 1;
#ifdef ANDROID
	} else if (event.type == SDL_MOUSEBUTTONUP) {
	} else if (event.type == SDL_FINGERUP) {
		float x = (int)(event.tfinger.x * (float)setup.screen_w);
		float y = (int)(event.tfinger.y * (float)setup.screen_h);
		event.button.button = 1;
		event.button.x = x;
		event.button.y = y;
#else
	} else if (event.type == SDL_MOUSEBUTTONUP) {
#endif
		float bx = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
		float by = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
		if (check_button(setup.view_mode, bx, by, event.button.button, BUTTON_RELEASE) != -1) {
			return;
		}
		if (mousemode == 1) {
			while (mapdata->offset_x1 <= -256.0 / (float)esContext->width * 2.0 * aspect) {
				int tile_x = long2tilex(lon, zoom);
				tile_x--;
				lon = tilex2long(tile_x, zoom);
				mapdata->offset_x1 += 256.0 / (float)esContext->width * 2.0 * aspect;
				mousestart_x = 0.0;
			}
			while (mapdata->offset_x1 >= 256.0 / (float)esContext->width * 2.0 * aspect) {
				int tile_x = long2tilex(lon, zoom);
				tile_x += 1;
				lon = tilex2long(tile_x, zoom);
				mapdata->offset_x1 -= 256.0 / (float)esContext->width * 2.0 * aspect;
				mousestart_x = 0.0;
			}
			if (mapdata->offset_y1 <= -256.0 / (float)esContext->height * 2.0) {
				int tile_y = lat2tiley(lat, zoom);
				tile_y--;
				lat = tiley2lat(tile_y, zoom);
				mapdata->offset_y1 += 256.0 / (float)esContext->height * 2.0;
				mousestart_y = 0.0;
			}
			if (mapdata->offset_y1 >= 256.0 / (float)esContext->height * 2.0) {
				int tile_y = lat2tiley(lat, zoom);
				tile_y += 1;
				lat = tiley2lat(tile_y, zoom);
				mapdata->offset_y1 -= 256.0 / (float)esContext->height * 2.0;
				mousestart_y = 0.0;
			}
		}		mousemode = 0;
		if (waypoint_active < 1) {
			waypoint_active = 1;
		}

#ifdef ANDROID
	} else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEWHEEL) {
	} else if (event.type == SDL_FINGERDOWN) {
		float x = (int)(event.tfinger.x * (float)setup.screen_w);
		float y = (int)(event.tfinger.y * (float)setup.screen_h);
		event.button.button = 1;
		event.button.x = x;
		event.button.y = y;
#else
#ifdef SDL2
	} else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEWHEEL) {
		if (event.type == SDL_MOUSEWHEEL) {
			mousewheel_flag = 1;
			if (event.button.x > 0) {
				event.button.button = 4;
			} else if (event.button.x < 0) {
				event.button.button = 5;
			}
			event.button.x = mouse_x;
			event.button.y = mouse_y;
		}
#else
	} else if (event.type == SDL_MOUSEBUTTONDOWN) {
#endif
#endif
		float bx = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
		float by = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
#ifdef SDL2
//		if (event.type != SDL_MOUSEWHEEL) {
			if (check_button(setup.view_mode, bx, by, event.button.button, BUTTON_PRESS) != -1) {
				return;
			}
//		}
#else
//		printf("EVENT: %f %f \n", bx, by);
		if (check_button(setup.view_mode, bx, by, event.button.button, BUTTON_PRESS) != -1) {
//			printf("BUTTON_CLICKED: %f %f \n", bx, by);
			return;
		}
#endif
		bx += mapdata->offset_x1;
		by += mapdata->offset_y1;
		if (event.button.button == 1) {
			if (event.button.y > esContext->height - 40 && event.button.y < esContext->height) {
				if (event.button.x > esContext->width - 40 && event.button.x < esContext->width) {
					setup.speak = 1 - setup.speak;
					return;
				}
			}
		}
		if (setup.view_mode == VIEW_MODE_MAP) {
			float x1 = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
			float y1 = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
			x1 += mapdata->offset_x1;
			y1 += mapdata->offset_y1;
			int16_t bx = (x1 / aspect + 1.0) / 2.0 * (float)esContext->width;
			int16_t by = (y1 + 1.0) / 2.0 * (float)esContext->height;
			float mouse_long = x2long(bx, lon, zoom);
			float mouse_lat = y2lat(by, lat, zoom);
			if (event.button.button == 1) {
/*
				if (by > 0 && by < 80) {
					int tile_y = lat2tiley(lat, zoom);
					tile_y--;
					lat = tiley2lat(tile_y, zoom);
				} else if (by > esContext->height - 80 && by < esContext->height) {
					int tile_y = lat2tiley(lat, zoom);
					tile_y+= 2;
					lat = tiley2lat(tile_y, zoom);
				} else if (bx > 0 && bx < 80) {
					int tile_x = long2tilex(lon, zoom);
					tile_x--;
					lon = tilex2long(tile_x, zoom);
				} else if (bx > esContext->width - 80 && bx < esContext->width) {
					int tile_x = long2tilex(lon, zoom);
					tile_x++;
					lon = tilex2long(tile_x, zoom);
				} else
*/

				if (map_addmode == 1 && map_show_wp == 1) {
					uint16_t n = 0;
					int16_t nz = get_altitude(mouse_lat, mouse_long);
					if (ModelData[ModelActive].p_alt > nz) {
						nz = ModelData[ModelActive].p_alt;
					}
					if (WayPoints[ModelActive][0].p_alt > nz) {
						nz = WayPoints[ModelActive][0].p_alt;
					}
					for (n = 0; n < MAX_WAYPOINTS; n++) {
						if (WayPoints[ModelActive][n].p_lat == 0.0) {
							WayPoints[ModelActive][n].p_lat = mouse_lat;
							WayPoints[ModelActive][n].p_long = mouse_long;
							WayPoints[ModelActive][n].p_alt = nz;
							WayPoints[ModelActive][n].param1 = 0.0;
							WayPoints[ModelActive][n].param2 = 0.0;
							WayPoints[ModelActive][n].param3 = 0.0;
							WayPoints[ModelActive][n].param4 = 0.0;
							WayPoints[ModelActive][n].type = 0;
							WayPoints[ModelActive][n].frametype = 0;
							sprintf(WayPoints[ModelActive][n].name, "WP%i", n);
							strncpy(WayPoints[ModelActive][n].command, "WAYPOINT", 127);
							break;
						}
					}
				} else if (map_poimode == 1) {
					uint16_t n = 0;
					int16_t nz = get_altitude(mouse_lat, mouse_long);
					for (n = 0; n < MAX_WAYPOINTS; n++) {
						if (WayPoints[ModelActive][n].p_lat == 0.0) {
							WayPoints[ModelActive][n].p_lat = mouse_lat;
							WayPoints[ModelActive][n].p_long = mouse_long;
							WayPoints[ModelActive][n].p_alt = nz;
							WayPoints[ModelActive][n].param1 = 0.0;
							WayPoints[ModelActive][n].param2 = 0.0;
							WayPoints[ModelActive][n].param3 = 0.0;
							WayPoints[ModelActive][n].param4 = 0.0;
							WayPoints[ModelActive][n].type = 0;
							WayPoints[ModelActive][n].frametype = 0;
							sprintf(WayPoints[ModelActive][n].name, "ROI%i", n);
							strncpy(WayPoints[ModelActive][n].command, "SET_ROI", 127);
							break;
						}
					}
					map_poimode = 0;
				} else if (map_poly_addmode == 1 && map_show_poly == 1) {
					uint16_t n = 0;
					for (n = 1; n < MAX_POLYPOINTS; n++) {
						if (PolyPoints[n].p_lat == 0.0) {
							PolyPoints[n].p_lat = mouse_lat;
							PolyPoints[n].p_long = mouse_long;
							break;
						}
					}
				} else if (map_polynf_addmode == 1) {
					uint16_t n = 0;
					uint8_t flag = 0;
					for (n = 0; n < MAX_POLYPOINTS; n++) {
						if (PolyPointsNoFly[n].p_lat != 0.0) {
							int16_t mark_x = long2x(PolyPointsNoFly[n].p_long, lon, zoom);
							int16_t mark_y = lat2y(PolyPointsNoFly[n].p_lat, lat, zoom);
							if (bx + 10 > mark_x && bx - 10 < mark_x) {
								if (by + 10 > mark_y && by - 10 < mark_y) {
									flag = 1;
									map_polynf_num++;
									SDL_Log("NEXT POLYNF: %i\n", map_polynf_num);
									break;
								}
							}
						}
					}
					if (flag == 0) {
						for (n = 1; n < MAX_POLYPOINTS; n++) {
							if (PolyPointsNoFly[n].p_lat == 0.0) {
								PolyPointsNoFly[n].p_lat = mouse_lat;
								PolyPointsNoFly[n].p_long = mouse_long;
								PolyPointsNoFly[n].num = map_polynf_num;
								break;
							}
						}
					}

				} else if (map_sethome == 1) {
					int16_t nz = get_altitude(mouse_lat, mouse_long);
					WayPoints[ModelActive][0].p_lat = mouse_lat;
					WayPoints[ModelActive][0].p_long = mouse_long;
					WayPoints[ModelActive][0].p_alt = nz;
					if (GroundData.active == 0) {
						GroundData.p_lat = WayPoints[ModelActive][0].p_lat;
						GroundData.p_long = WayPoints[ModelActive][0].p_long;
						GroundData.p_alt = WayPoints[ModelActive][0].p_alt;
					}
					map_sethome = 0;
				} else if (map_setpos == 1) {
					GroundData.followme = 0;
					mavlink_send_cmd_follow(ModelActive, mouse_lat, mouse_long, GroundData.sp_alt, GroundData.sp_radius);
				} else {
					waypoint_active = -1;
					polypoint_active = -1;
					polypointnf_active = -1;
					mousestart_x = x1;
					mousestart_y = y1;
					mousemode = 1;
					uint16_t n = 0;
					if (map_show_wp == 1) {
						for (n = 0; n < MAX_WAYPOINTS; n++) {
							if (WayPoints[ModelActive][n].p_lat != 0.0) {
								int16_t mark_x = long2x(WayPoints[ModelActive][n].p_long, lon, zoom);
								int16_t mark_y = lat2y(WayPoints[ModelActive][n].p_lat, lat, zoom);
								if (bx + 20 > mark_x && bx - 20 < mark_x) {
									if (by + 20 > mark_y && by - 20 < mark_y) {
										SDL_Log("WAYPOINT: %i\n", n);
										waypoint_active = n;
										polypoint_active = -1;
										polypointnf_active = -1;
										mousemode = 1;
										break;
									}
								}
							}
						}
					}
					if (map_show_poly == 1) {
						for (n = 0; n < MAX_POLYPOINTS; n++) {
							if (PolyPoints[n].p_lat != 0.0) {
								int16_t mark_x = long2x(PolyPoints[n].p_long, lon, zoom);
								int16_t mark_y = lat2y(PolyPoints[n].p_lat, lat, zoom);
								if (bx + 20 > mark_x && bx - 20 < mark_x) {
									if (by + 20 > mark_y && by - 20 < mark_y) {
										SDL_Log("POLYPOINT: %i\n", n);
										waypoint_active = -1;
										polypoint_active = n;
										polypointnf_active = -1;
										mousemode = 1;
										break;
									}
								}
							}
						}
						for (n = 0; n < MAX_POLYPOINTS; n++) {
							if (PolyPointsNoFly[n].p_lat != 0.0) {
								int16_t mark_x = long2x(PolyPointsNoFly[n].p_long, lon, zoom);
								int16_t mark_y = lat2y(PolyPointsNoFly[n].p_lat, lat, zoom);
								if (bx + 20 > mark_x && bx - 20 < mark_x) {
									if (by + 20 > mark_y && by - 20 < mark_y) {
										SDL_Log("POLYPOINT_NF: %i\n", n);
										waypoint_active = -1;
										polypoint_active = -1;
										polypointnf_active = n;
										mousemode = 1;
										break;
									}
								}
							}
						}
					}
				}
			} else if (event.button.button == 3) {
				uint16_t n = 0;
				int16_t nz = get_altitude(mouse_lat, mouse_long);
				if (ModelData[ModelActive].p_alt > nz) {
					nz = ModelData[ModelActive].p_alt;
				}
				if (WayPoints[ModelActive][0].p_alt > nz) {
					nz = WayPoints[ModelActive][0].p_alt;
				}
				if (map_show_wp == 1) {
					for (n = 0; n < MAX_WAYPOINTS; n++) {
						if (WayPoints[ModelActive][n].p_lat == 0.0) {
							WayPoints[ModelActive][n].p_lat = mouse_lat;
							WayPoints[ModelActive][n].p_long = mouse_long;
							WayPoints[ModelActive][n].p_alt = nz;
							WayPoints[ModelActive][n].param1 = 0.0;
							WayPoints[ModelActive][n].param2 = 0.0;
							WayPoints[ModelActive][n].param3 = 0.0;
							WayPoints[ModelActive][n].param4 = 0.0;
							WayPoints[ModelActive][n].type = 0;
							WayPoints[ModelActive][n].frametype = 0;
							sprintf(WayPoints[ModelActive][n].name, "WP%i", n);
							strncpy(WayPoints[ModelActive][n].command, "WAYPOINT", 127);
//						SDL_Log("GPS;%i;%f;%f;%0.1f;%0.1f\n", time(0), mouse_lat, mouse_long, 25.0, 10.0);
							break;
						}
					}
				}
			} else if (event.button.button == 2) {
				if (map_show_wp == 1) {
					if (waypoint_active >= 0) {
						WayPoints[ModelActive][waypoint_active].p_lat = mouse_lat;
						WayPoints[ModelActive][waypoint_active].p_long = mouse_long;
					}
				}
				if (map_show_poly == 1) {
					if (polypoint_active >= 0) {
						PolyPoints[polypoint_active].p_lat = mouse_lat;
						PolyPoints[polypoint_active].p_long = mouse_long;
					}
					if (polypointnf_active >= 0) {
						PolyPointsNoFly[polypointnf_active].p_lat = mouse_lat;
						PolyPointsNoFly[polypointnf_active].p_long = mouse_long;
					}
				}
			} else if (event.button.button == 4) {
				if (zoom < 18) {
					zoom++;
				}
			} else if (event.button.button == 5) {
				if (zoom > 0) {
					zoom--;
				}
			}
		} else if (setup.view_mode == VIEW_MODE_FCMENU) {
			if (event.button.button == 1) {
			} else if (event.button.button == 2) {
			} else if (event.button.button == 3) {
			} else if (event.button.button == 4) {
				if (set_sel > 0) {
					set_sel--;
				}
			} else if (event.button.button == 5) {
				set_sel++;
			} else if (event.button.button == 6) {
			} else if (event.button.button == 7) {
			} else {
				SDL_Log("Button: %i\n", event.button.button);
			}
		}
		redraw_flag = 1;
#ifdef SDL2
	} else {
		SDL_Log("## UNKNOWN_EVENT: %i (0x%x) ##\n", event.type, event.type);
#endif
	}
	if (mousewheel_flag == 1) {
		mousewheel_flag = 0;
		SDL_Event user_event;
		user_event.type = SDL_MOUSEBUTTONUP;
		user_event.button.x = last_x;
		user_event.button.y = last_y;
		SDL_PushEvent(&user_event);
	}
}

int telemetry_thread (void *data) {
	int modelid = 0;
	while (gui_running == 1) {
		for (modelid = 0; modelid < MODELS_MAX; modelid++) {
			if (clientmode == 1) {
				webclient_update(clientmode_server, clientmode_port);
				SDL_Delay(90);
			} else if (ModelData[modelid].teletype == TELETYPE_MULTIWII_21 || ModelData[modelid].teletype == TELETYPE_BASEFLIGHT) {
				mwi21_update(modelid);
			} else if (ModelData[modelid].teletype == TELETYPE_GPS_NMEA) {
				gps_update(modelid);
			} else if (ModelData[modelid].teletype == TELETYPE_OPENPILOT) {
				openpilot_update(modelid);
			} else if (ModelData[modelid].teletype == 255) {
			} else {
				mavlink_update(modelid);
			}
		}
		static uint16_t utimer = 0;
		if (utimer >= 300 && GroundData.active == 1 && GroundData.followme == 1) {
			SwarmSetup.active = 0;
			mavlink_send_cmd_follow(ModelActive, GroundData.p_lat, GroundData.p_long, GroundData.fm_alt, GroundData.fm_radius);
			utimer = 0;
		}
		if (utimer >= 300 && SwarmSetup.active == 1 && SwarmSetup.master != -1) {
			GroundData.followme = 0;
			float p_lat = 0.0;
			float p_long = 0.0;
			float p_alt = 0.0;
			float p_yaw = 0.0;
			if (SwarmSetup.master == -1) {
				p_lat = GroundData.p_lat;
				p_long = GroundData.p_long;
				p_alt = GroundData.fm_alt;
				p_yaw = 0.0;
			} else {
				p_lat = ModelData[SwarmSetup.master].p_lat;
				p_long = ModelData[SwarmSetup.master].p_long;
				p_alt = ModelData[SwarmSetup.master].p_alt;
				p_yaw = ModelData[SwarmSetup.master].yaw;
			}
			int nn = 0;
			for (nn = 0; nn < 4; nn++) {
				if (SwarmSetup.slave[nn] == -1) {
					continue;
				}
				float off_x = SwarmSetup.offset_x[nn];
				float off_y = SwarmSetup.offset_y[nn];
				if (SwarmSetup.rotate == 1) {
					float radius = sqrt((SwarmSetup.offset_x[nn] * SwarmSetup.offset_x[nn]) + (SwarmSetup.offset_y[nn] * SwarmSetup.offset_y[nn]));
					float angle = p_yaw + 90.0 + atan(SwarmSetup.offset_x[nn] / SwarmSetup.offset_y[nn]) * RAD_TO_DEG;
					off_x = cos(angle * DEG2RAD) * radius;
					off_y = sin(angle * DEG2RAD) * radius;
				}
				latlong_offset(&p_lat, &p_long, &p_alt, off_y, off_x, SwarmSetup.offset_z[nn]);
				if (SwarmSetup.yaw_mode == 1) {
					mavlink_send_cmd_yaw(SwarmSetup.slave[nn], p_yaw, 360.0);
				}
				mavlink_send_cmd_follow(SwarmSetup.slave[nn], p_lat, p_long, p_alt, 2.0);
			}
			utimer = 0;
		}
		utimer++;
		SDL_Delay(1);
	}
	SDL_Log("telemetry: exit thread\n");
	return(0);
}

int touchscreen_thread (void *data) {
#ifdef RPI_NO_X
	while (gui_running == 1) {
		if (touch_fd >= 0) {
			struct input_event ev[64];
			SDL_Event user_event;
			int i = 0;
			int rd = 0;
			static int8_t touch = 0;
			static int8_t touch_x = 0;
			static int8_t touch_y = 0;
			int diff_x = setup.calibration_max_x - setup.calibration_min_x;
			int diff_y = setup.calibration_max_y - setup.calibration_min_y;
			rd = read(touch_fd, ev, sizeof(struct input_event) * 64);
			if (rd >= (int)sizeof(struct input_event)) {
				for (i = 0; i < rd / sizeof(struct input_event); i++) {
					if (ev[i].type == 1 || ev[i].type == 3) {
						if (ev[i].code == 330) {
							if (ev[i].value == 1) {
								touch = 1;
								touch_x = 0;
								touch_y = 0;
							} else if (ev[i].value == 0) {
								touch = 2;
								touch_x = 0;
								touch_y = 0;
							}
						} else if (ev[i].code == 0) {
							if (setup.calibration_mode == 1 || setup.calibration_mode == 3) {
								setup.calibration_max_x = (int)ev[i].value;
							} else if (setup.calibration_mode == 2 || setup.calibration_mode == 4) {
								setup.calibration_min_x = (int)ev[i].value;
							}
							diff_x = setup.calibration_max_x - setup.calibration_min_x;
							last_x = setup.screen_w - ((int)ev[i].value - setup.calibration_min_x) * (setup.screen_w - 120) / diff_x - 60;
							if (touch == 0) {
								user_event.type=SDL_MOUSEMOTION;
								user_event.button.x = last_x;
								user_event.button.y = last_y;
								SDL_PushEvent(&user_event);
							}
							touch_x = 1;
						} else if (ev[i].code == 1) {
							if (setup.calibration_mode == 1 || setup.calibration_mode == 2) {
								setup.calibration_max_y = (int)ev[i].value;
							} else if (setup.calibration_mode == 3 || setup.calibration_mode == 4) {
								setup.calibration_min_y = (int)ev[i].value;
							}
							diff_y = setup.calibration_max_y - setup.calibration_min_y;
							last_y = setup.screen_h - ((int)ev[i].value - setup.calibration_min_y) * (setup.screen_h - 120) / diff_y - 60;
							if (touch == 0) {
								user_event.type=SDL_MOUSEMOTION;
								user_event.button.x = last_x;
								user_event.button.y = last_y;
								SDL_PushEvent(&user_event);
							}
							touch_y = 1;
						}
						if (touch == 2) {
							user_event.type=SDL_MOUSEBUTTONUP;
							user_event.button.x = last_x;
							user_event.button.y = last_y;
							user_event.button.button = 1;
							SDL_PushEvent(&user_event);
							touch = 0;
							touch_x = 0;
							touch_y = 0;
						} else if (touch == 1 && touch_x > 0 && touch_y > 0) {
							if (setup.calibration_mode > 0) {
								setup.calibration_mode++;
								if (setup.calibration_mode > 5) {
									setup.calibration_mode = 0;
									setup_save();
								}
							} else {
								user_event.type=SDL_MOUSEBUTTONDOWN;
								user_event.button.x = last_x;
								user_event.button.y = last_y;
								user_event.button.button = 1;
								SDL_PushEvent(&user_event);
							}
							touch = 0;
							touch_x = 0;
							touch_y = 0;
						}
//						SDL_Log("%i,%i\n", last_x, last_y);
					}
				}
			}
		}
	}
#endif
	SDL_Log("touch: exit thread\n");
	return(0);
}


void transition_rotate_begin (ESContext *esContext, float trans_count) {
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
#ifndef SDLGL
	esTranslate( &userData->perspective, 0.0, 0.0, -2.0 );
	esRotate( &userData->perspective, trans_count, 1.0, 1.0, 1.0 );
	esTranslate( &userData->perspective, 0.0, 0.0, 2.0 );
#else
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef( 0.0, 0.0, -2.0 );
	glRotatef( trans_count, 1.0, 1.0, 1.0 );
	glTranslatef( 0.0, 0.0, 2.0 );
#endif
}

void transition_rotate_end (ESContext *esContext, float trans_count) {
#ifndef SDLGL
	UserData *userData = esContext->userData;
#endif
#ifndef SDLGL
	esTranslate( &userData->perspective, 0.0, 0.0, -2.0 );
	esRotate( &userData->perspective, -trans_count, 1.0, 1.0, 1.0 );
	esTranslate( &userData->perspective, 0.0, 0.0, 2.0 );
#else
	glPopMatrix();
#endif
}

static uint8_t overview_show (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	view_overview = 1 - view_overview;
	return 0;
}

static uint8_t screen_last (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (view_mode_next > 0) {
		view_mode_next = setup.view_mode - 1;
	} else {
		view_mode_next = VIEW_MODE_LAST - 1;
	}
	trans_count = 1.0;
	setup_save();
	return 0;
}

static uint8_t screen_next (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	view_mode_next = setup.view_mode + 1;
	if (view_mode_next > VIEW_MODE_LAST - 1) {
		view_mode_next = 0;
	}
	trans_count = 1.0;
	setup_save();
	return 0;
}

uint8_t screen_select (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (data == -1.0) {
		if (button == 4) {
			screen_last(name, x, y, button, data, action);
		} else if (button == 5) {
			screen_next(name, x, y, button, data, action);
		} else {
			view_screenlist = 1 - view_screenlist;
		}
	} else {
		if (setup.view_mode == (uint8_t)data) {
			view_screenlist = 0;
		} else {
			setup.view_mode = (uint8_t)data;
		}
//		trans_count = 1.0;
		setup_save();
	}
	return 0;
}

static uint8_t model_select (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (data == 0.0) {
		if (button == 4) {
			if (ModelActive > 0) {
				ModelActive--;
			} else {
				ModelActive = MODELS_MAX - 1;
			}
		} else {
			if (ModelActive < MODELS_MAX - 1) {
				ModelActive++;
			} else {
				ModelActive = 0;
			}
		}
	} else if (data == -1.0) {
		if (button == 4) {
			if (ModelActive > 0) {
				ModelActive--;
			} else {
				ModelActive = MODELS_MAX - 1;
			}
		} else if (button == 5) {
			if (ModelActive < MODELS_MAX - 1) {
				ModelActive++;
			} else {
				ModelActive = 0;
			}
		} else {
			view_modellist = 1 - view_modellist;
		}
	} else {
		if (ModelActive == (uint8_t)data - 1) {
			view_modellist = 0;
		} else {
			ModelActive = (uint8_t)data - 1;
		}
	}
	return 0;
}

#ifdef SDLGL
SDL_Joystick *joy1 = NULL;

int8_t joystick_init (void) {
	printf("search for joysticks\n");
	if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {
		fprintf(stderr, "Unable to initialize Joystick: %s\n", SDL_GetError());
		return -1;
	}
	fprintf(stderr, "%i joysticks found\n", SDL_NumJoysticks());
	if (SDL_NumJoysticks() <= 0) {
		return -1;
	}
	joy1 = SDL_JoystickOpen(0);
	if (joy1 == NULL) {
		fprintf(stderr, "could not open joystick\n");
		return -1;
	}
	SDL_JoystickEventState(SDL_QUERY);
	return 0;
}
#endif








void gimbal_update (float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to, float *pitch, float *yaw) {
	/* Alt - Diff */
	float alt = alt_to - alt_from;
	/* Bearing/Heading/Richtung */
	float heading = toDeg(atan2(cos(toRad(lat_from)) * sin(toRad(lat_to)) - sin(toRad(lat_from)) * cos(toRad(lat_to)) * cos(toRad(lon_to) - toRad(lon_from)), sin(toRad(lon_to) - toRad(lon_from)) * cos(toRad(lat_to)))) + 270;
	if (heading > 180) {
		heading -= 360;
	}
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

	*pitch = angle_up * -1.0;
	*yaw = heading;
}




void Draw (ESContext *esContext) {
	int n = 0;
	char tmp_str[1024];
	char tmp_str2[1024];
	char tmp_str3[1024];
	uint32_t timer = SDL_GetTicks() / 10;

	for (n = 0; n < MODELS_MAX; n++) {
		if (ModelData[n].heartbeat != 0) {
			connection_found = 1;
		}
	}


	static uint16_t timg = 0;
	if (timg++ > 15) {
		timg = 0;
		for (n = 0; n < MODELS_MAX; n++) {
			if (ModelData[n].dronetype == 26) {

				ModelData[n].follow = 1;
				if (ModelData[n].follow >= 0) {

float pitch = 0.0;
float yaw = 0.0;

gimbal_update(ModelData[n].p_lat, ModelData[n].p_long, ModelData[n].p_alt, ModelData[ModelData[n].follow].p_lat, ModelData[ModelData[n].follow].p_long, ModelData[ModelData[n].follow].p_alt, &pitch, &yaw);
mavlink_set_gimbal_pos(n, pitch, 0.0, yaw);


				}
			}
		}
	}

#ifdef SDLGL
	static uint16_t timu = 0;
	int16_t values[8];
	if (timu++ > 5) {
		timu = 0;
		if (joy1 != NULL) {
			SDL_JoystickUpdate();
			for (n = 0; n < SDL_JoystickNumAxes(joy1) && n < 8; ++n) {
				int16_t value = SDL_JoystickGetAxis(joy1, n);
				values[n] = value / 66 + 1500;
//				fprintf(stderr, "%i ", values[n]);
			}
//			fprintf(stderr, "\n");
			mavlink_send_channels(ModelActive, values);
		}

//		for (n = 0; n < 8; ++n) {
//			values[n] = 1500;
//		}
//		mavlink_send_channels(ModelActive, values);

	}
#endif



	Logging();
	// set RTL-Waypoints to HOME-Position
	if (setup.view_mode != VIEW_MODE_WPEDIT) {
		uint16_t n = 0;
		for (n = 0; n < MAX_WAYPOINTS; n++) {
			if (WayPoints[ModelActive][n].p_lat != 0.0 && strcmp(WayPoints[ModelActive][n].command, "RTL") == 0) {
				WayPoints[ModelActive][n].p_lat = WayPoints[ModelActive][0].p_lat;
				WayPoints[ModelActive][n].p_long = WayPoints[ModelActive][0].p_long;
				WayPoints[ModelActive][n].p_alt = WayPoints[ModelActive][0].p_alt;
			}
			if (WayPoints[ModelActive][n].p_lat != 0.0 && n > 0 && strcmp(WayPoints[ModelActive][n].command, "LAND") == 0) {
				WayPoints[ModelActive][n].p_lat = WayPoints[ModelActive][n - 1].p_lat;
				WayPoints[ModelActive][n].p_long = WayPoints[ModelActive][n - 1].p_long;
				WayPoints[ModelActive][n].p_alt = WayPoints[ModelActive][n - 1].p_alt;
			}
			if (WayPoints[ModelActive][n].p_lat != 0.0 && n > 0 && strcmp(WayPoints[ModelActive][n].command, "TAKEOFF") == 0) {
				WayPoints[ModelActive][n].p_lat = WayPoints[ModelActive][0].p_lat;
				WayPoints[ModelActive][n].p_long = WayPoints[ModelActive][0].p_long;
				WayPoints[ModelActive][n].p_alt = WayPoints[ModelActive][0].p_alt;
			}
		}
	}
	if (strcmp(keyboard_key, "escape") == 0) {
		ShutDown( esContext );
		exit(0);
	} else if (strcmp(keyboard_key, "right") == 0) {
		key_pressed |= (1<<0);
	} else if (strcmp(keyboard_key, "left") == 0) {
		key_pressed |= (1<<1);
	} else if (strcmp(keyboard_key, "up") == 0) {
		key_pressed |= (1<<2);
	} else if (strcmp(keyboard_key, "down") == 0) {
		key_pressed |= (1<<3);
	} else if (strcmp(keyboard_key, "[+]") == 0 || strcmp(keyboard_key, "keypad +") == 0) {
		key_pressed |= (1<<4);
	} else if (strcmp(keyboard_key, "[-]") == 0 || strcmp(keyboard_key, "keypad -") == 0) {
		key_pressed |= (1<<5);
	} else if (strcmp(keyboard_key, "h") == 0) {
		int tile_y = lat2tiley(WayPoints[ModelActive][0].p_lat, zoom) - 1;
		int tile_x = long2tilex(WayPoints[ModelActive][0].p_long, zoom) - 1;
		lat = tiley2lat(tile_y, zoom);
		lon = tilex2long(tile_x, zoom);
	} else if (strcmp(keyboard_key, "u") == 0) {
		int tile_y = lat2tiley(ModelData[ModelActive].p_lat, zoom) - 1;
		int tile_x = long2tilex(ModelData[ModelActive].p_long, zoom) - 1;
		lat = tiley2lat(tile_y, zoom);
		lon = tilex2long(tile_x, zoom);
	} else if (strcmp(keyboard_key, "t") == 0) {
		if (map_type < 2) {
			map_type++;
		} else {
			map_type = 0;
		}
	} else if (strcmp(keyboard_key, "tab") == 0) {
		view_mode_next = setup.view_mode + 1;
		if (view_mode_next > VIEW_MODE_LAST - 1) {
			view_mode_next = 0;
		}
		trans_count = 1.0;
		setup_save();
	} else if (strcmp(keyboard_key, "s") == 0) {
		if (setup.view_mode == VIEW_MODE_FMS || setup.view_mode == VIEW_MODE_MAP) {
			mavlink_send_waypoints(ModelActive);
		}
	} else if (strcmp(keyboard_key, "r") == 0) {
		if (setup.view_mode == VIEW_MODE_FMS || setup.view_mode == VIEW_MODE_MAP) {
			mavlink_read_waypoints(ModelActive);
		}
	} else if (strcmp(keyboard_key, "print screen") == 0 || strcmp(keyboard_key, "printscreen") == 0) {
#ifdef SDLGL
		save_screenshot();
#endif
	} else if (keyboard_key[0] != 0) {
		SDL_Log("## keyboard_key: %s ##\n", keyboard_key);
	}

	keyboard_key[0] = 0;
	while(SDL_PollEvent(&event)) {
		check_events(esContext, event);
	}
	if (key_pressed & (1<<0)) {
		ModelData[ModelActive].yaw++;
		if (ModelData[ModelActive].yaw >= 360.0) {
			ModelData[ModelActive].yaw = 0.0;
		}
		redraw_flag = 1;
	}
	if (key_pressed & (1<<1)) {
		ModelData[ModelActive].yaw--;
		if (ModelData[ModelActive].yaw < 0.0) {
			ModelData[ModelActive].yaw = 359.0;
		}
		redraw_flag = 1;
	}
	if (key_pressed & (1<<2)) {
		float nx1 = 0.0;
		float ny1 = 0.0;
		next_point(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].yaw + 180.0, 0.000016, &nx1, &ny1);
		ModelData[ModelActive].p_lat = nx1;
		ModelData[ModelActive].p_long = ny1;
		int16_t zz = get_altitude(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long);
		if (ModelData[ModelActive].p_alt < zz + 10) {
			ModelData[ModelActive].p_alt = zz + 10;
		}
		redraw_flag = 1;
	}
	if (key_pressed & (1<<3)) {
		float nx1 = 0.0;
		float ny1 = 0.0;
		next_point(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].yaw, 0.000016, &nx1, &ny1);
		ModelData[ModelActive].p_lat = nx1;
		ModelData[ModelActive].p_long = ny1;
		int16_t zz = get_altitude(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long);
		if (ModelData[ModelActive].p_alt < zz + 10) {
			ModelData[ModelActive].p_alt = zz + 10;
		}
		redraw_flag = 1;
	}
	if (key_pressed & (1<<4)) {
		ModelData[ModelActive].p_alt++;
		redraw_flag = 1;
	}
	if (key_pressed & (1<<5)) {
		ModelData[ModelActive].p_alt--;
		redraw_flag = 1;
	}

	// Status-Messages
	if (timer - msg_timer > 20 || timer < msg_timer) {
		if (message > 20) {
			message -= 20;
		} else {
			message = 0;
		}
		msg_timer = timer;
		redraw_flag = 1;
	}
	if (timer - heartbeat_timer > 10 || timer < heartbeat_timer) {
		for (n = 0; n < MODELS_MAX; n++) {
			if (ModelData[n].heartbeat > 1) {
				ModelData[n].heartbeat -= 1;
			} else {
				ModelData[n].heartbeat = 0;
			}
		}
		heartbeat_timer = timer;
		redraw_flag = 1;
	}
	if (ModelData[ModelActive].found_rc == 1 && (timer - heartbeat_rc_timer > 20 || timer < heartbeat_rc_timer)) {
		for (n = 0; n < MODELS_MAX; n++) {
			if (ModelData[n].heartbeat_rc > 20) {
				ModelData[n].heartbeat_rc -= 20;
			} else {
				ModelData[n].heartbeat_rc = 0;
				ModelData[n].rssi_rx = 0;
				ModelData[n].rssi_tx = 0;
			}
		}
		heartbeat_rc_timer = timer;
		redraw_flag = 1;
	}
	static uint8_t blink = 0;
	if (timer - blink_timer > 20 || timer < blink_timer) {
		blink += 40;
		blink_timer = timer;
		redraw_flag = 1;
	}
	if (setup.speak == 1) {
		static uint8_t speak = 20;
		if (timer - speak_timer > 200 || timer < speak_timer) {
			speak += 5;
			speak_timer = timer;
		}
		if (speak > 40) {
			speak = 0;
			if (ModelData[ModelActive].found_rc == 1 && ModelData[ModelActive].heartbeat_rc == 0) {
				system_say("lost rc");
			} else 	if (ModelData[ModelActive].heartbeat == 0 && connection_found == 1) {
				system_say("lost heartbeat");
			} else 	if ((ModelData[ModelActive].found_rc == 1 || connection_found == 1) && ModelData[ModelActive].voltage > 0.0 && ModelData[ModelActive].voltage < setup.volt_min) {
				system_say("low battery");
			} else {
				static uint8_t say_mode = 0;
				char tmp_str[1024];
				if (say_mode++ == 0 && ModelData[ModelActive].voltage > 0.0) {
					sprintf(tmp_str, "%0.1f volt", ModelData[ModelActive].voltage);
				} else {
					float ground_alt = (float)get_altitude(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long);
					if (ground_alt - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) > 0.0) {
						sprintf(tmp_str, "WARNING, Altitude %i meter , GROUND CONTACT", (int)((ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - ground_alt));
					} else if (ground_alt - (ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) > -2.0) {
						sprintf(tmp_str, "WARNING, Altitude %i meter , TOO LOW", (int)((ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - ground_alt));
					} else if ((ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - ground_alt > 100.0) {
						sprintf(tmp_str, "WARNING, Altitude %i meter , PUBLIC AIRSPACE", (int)((ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - ground_alt));
					} else {
						sprintf(tmp_str, "Altitude %i meter", (int)((ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset) - ground_alt));
					}
					say_mode = 0;
				}
				system_say(tmp_str);
			}
		}
	}
#ifndef SDLGL
	if (redraw_flag == 0) {
		SDL_Delay(1);
		return;
	}
#endif
	redraw_flag = 0;

	if (view_mode_last != setup.view_mode) {
		view_mode_last = setup.view_mode;
		reset_buttons();
	}

#ifndef CONSOLE_ONLY
#ifdef RPI_NO_X
	if (setup.calibration_mode > 0) {
		screen_calibration(esContext);
		draw_update(esContext);
		SDL_Delay(20);
		return;
	}
#endif
#endif
#ifndef ANDROID
#ifdef SDLGL
	if (trans_count > 0.0) {
		trans_count += 10.0;
		if (trans_count < 90.0) {
			transition_rotate_begin(esContext, trans_count);
		} else if (trans_count < 180.0) {
			setup.view_mode = view_mode_next;
			transition_rotate_begin(esContext, trans_count + 180);
		} else {
			trans_count = 0.0;
		}
	}
#else
	setup.view_mode = view_mode_next;
#endif
#else
	setup.view_mode = view_mode_next;
#endif

#ifndef CONSOLE_ONLY
	if (view_overview == 1) {
		screen_overview(esContext);
	} else if (setup.view_mode == VIEW_MODE_HUD) {
		screen_hud(esContext);
	} else if (setup.view_mode == VIEW_MODE_TELEMETRY) {
		screen_background(esContext);
		screen_telemetry(esContext);
	} else if (setup.view_mode == VIEW_MODE_MODEL) {
		screen_background(esContext);
		screen_model(esContext);
	} else if (setup.view_mode == VIEW_MODE_RCFLOW) {
//		screen_background(esContext);
		screen_rcflow(esContext);
	} else if (setup.view_mode == VIEW_MODE_FMS) {
		screen_fms(esContext);
	} else if (setup.view_mode == VIEW_MODE_WPEDIT) {
		if (wpedit_last_mode == VIEW_MODE_MAP) {
			screen_map(esContext, lat, lon, zoom);
			draw_box_f3(esContext, -1.5, -1.0, 0.002, 1.5, 1.0, 0.002, 0, 0, 0, 200);
		}
		screen_wpedit(esContext);
	} else if (setup.view_mode == VIEW_MODE_MAP) {
		if (map_view == 3) {
			map_view = 0;
		}
		screen_map(esContext, lat, lon, zoom);
	} else if (setup.view_mode == VIEW_MODE_SYSTEM) {
		screen_background(esContext);
		screen_system(esContext);
#ifndef ANDROID
	} else if (setup.view_mode == VIEW_MODE_VIDEOLIST) {
		screen_background(esContext);
		screen_videolist(esContext);
#ifdef USE_TCL
	} else if (setup.view_mode == VIEW_MODE_TCL) {
		screen_background(esContext);
		screen_tcl(esContext);
#endif
#endif
	} else if (setup.view_mode == VIEW_MODE_TRACKER) {
		screen_background(esContext);
		screen_tracker(esContext);
	} else if (setup.view_mode == VIEW_MODE_FCMENU) {
		screen_background(esContext);
		if (ModelData[ModelActive].teletype == TELETYPE_MULTIWII_21) {
			screen_mwi_menu(esContext);
		} else if (ModelData[ModelActive].teletype == TELETYPE_BASEFLIGHT) {
			screen_mwi_menu(esContext);
		} else if (ModelData[ModelActive].teletype == TELETYPE_GPS_NMEA) {
			screen_graph(esContext);
		} else if (ModelData[ModelActive].teletype == TELETYPE_OPENPILOT) {
			screen_openpilot(esContext);
		} else if (ModelData[ModelActive].teletype == 255) {
		} else {
			screen_mavlink_menu(esContext);
		}
	}
#endif
#ifdef SDLGL
	if (trans_count > 0.0) {
		if (trans_count < 90.0) {
			transition_rotate_end(esContext, trans_count);
		} else if (trans_count < 180.0) {
			setup.view_mode = view_mode_next;
			transition_rotate_end(esContext, trans_count + 180);
		} else {
			trans_count = 0.0;
		}
	}
#endif

	glDisable( GL_DEPTH_TEST );
	draw_circleFilled_f3(esContext, 1.29, 0.955, 0.0002, (float)ModelData[ModelActive].heartbeat / 3000.0, 255, 0, 0, ModelData[ModelActive].heartbeat * 2);
	if (ModelData[ModelActive].found_rc == 1) {
		draw_circleFilled_f3(esContext, 1.3, 0.87, 0.01, (float)ModelData[ModelActive].heartbeat_rc / 4000.0, 0, 0, 255, ModelData[ModelActive].heartbeat_rc * 2);
	}
	if (view_overview == 0) {
		draw_text_button(esContext, "<<", setup.view_mode, "[<<]", FONT_WHITE, -1.3, -0.95, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, screen_last, 0.0);
		draw_text_button(esContext, ">>", setup.view_mode, "[>>]", FONT_WHITE, 1.3, -0.95, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, screen_next, 0.0);
		sprintf(tmp_str, "%s", ModelData[ModelActive].name);
		draw_text_button(esContext, "MODELSEL", setup.view_mode, tmp_str, FONT_WHITE, 1.0, -0.95, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, model_select, -1.0);
		if (view_modellist == 1) {
			draw_box_f3(esContext, 0.7, -0.88, 0.002, 1.3, -0.88 + 0.1 * MODELS_MAX, 0.002, 0, 0, 0, 200);
			draw_rect_f3(esContext, 0.7, -0.88, 0.002, 1.3, -0.88 + 0.1 * MODELS_MAX, 0.002, 255, 255, 255, 200);
			for (n = 0; n < MODELS_MAX; n++) {
				if (ModelData[n].dronetype == MAV_TYPE_GENERIC) {
					strcpy(tmp_str2, "Generic air vehicle");
					strcpy(tmp_str3, "");
				} else if (ModelData[n].dronetype == MAV_TYPE_FIXED_WING) {
					strcpy(tmp_str2, "Fixed wing aircraft");
					strcpy(tmp_str3, "textures/type_fixedwing.png");
				} else if (ModelData[n].dronetype == MAV_TYPE_QUADROTOR) {
					strcpy(tmp_str2, "Quadrotor");
					strcpy(tmp_str3, "textures/type_quadrotor.png");
				} else if (ModelData[n].dronetype == MAV_TYPE_COAXIAL) {
					strcpy(tmp_str2, "Coaxial helicopter");
					strcpy(tmp_str3, "textures/type_coaxialhelicopter.png");
				} else if (ModelData[n].dronetype == MAV_TYPE_HELICOPTER) {
					strcpy(tmp_str2, "Helicopter");
					strcpy(tmp_str3, "textures/type_helicopter.png");
				} else if (ModelData[n].dronetype == MAV_TYPE_ANTENNA_TRACKER) {
					strcpy(tmp_str2, "Antenna-Tracker");
					strcpy(tmp_str3, "");
				} else if (ModelData[n].dronetype == MAV_TYPE_GCS) {
					strcpy(tmp_str2, "ground control station");
					strcpy(tmp_str3, "textures/type_ground.png");
				} else if (ModelData[n].dronetype == MAV_TYPE_AIRSHIP) {
					strcpy(tmp_str2, "Airship, controlled");
					strcpy(tmp_str3, "");
				} else if (ModelData[n].dronetype == MAV_TYPE_FREE_BALLOON) {
					strcpy(tmp_str2, "Free balloon, uncontrolled");
					strcpy(tmp_str3, "");
				} else if (ModelData[n].dronetype == MAV_TYPE_ROCKET) {
					strcpy(tmp_str2, "Rocket");
					strcpy(tmp_str3, "");
				} else if (ModelData[n].dronetype == MAV_TYPE_GROUND_ROVER) {
					strcpy(tmp_str2, "Ground rover");
					strcpy(tmp_str3, "");
				} else if (ModelData[n].dronetype == MAV_TYPE_SURFACE_BOAT) {
					strcpy(tmp_str2, "Boat");
					strcpy(tmp_str3, "textures/type_boat.png");
				} else if (ModelData[n].dronetype == MAV_TYPE_SUBMARINE) {
					strcpy(tmp_str2, "Submarine");
					strcpy(tmp_str3, "");
				} else if (ModelData[n].dronetype == MAV_TYPE_HEXAROTOR) {
					strcpy(tmp_str2, "Hexarotor");
					strcpy(tmp_str3, "textures/type_hexarotor.png");
				} else if (ModelData[n].dronetype == MAV_TYPE_OCTOROTOR) {
					strcpy(tmp_str2, "Octorotor");
					strcpy(tmp_str3, "");
				} else if (ModelData[n].dronetype == MAV_TYPE_TRICOPTER) {
					strcpy(tmp_str2, "Tricopter");
					strcpy(tmp_str3, "textures/type_tricopter.png");
				} else if (ModelData[n].dronetype == MAV_TYPE_FLAPPING_WING) {
					strcpy(tmp_str2, "Flapping wing");
					strcpy(tmp_str3, "");
				} else if (ModelData[n].dronetype == MAV_TYPE_KITE) {
					strcpy(tmp_str2, "Kite");
					strcpy(tmp_str3, "textures/type_kite.png");
				} else {
					sprintf(tmp_str2, "UNKNOWN_UAV(%i)", ModelData[n].dronetype);
					strcpy(tmp_str3, "");
				}
//				if (tmp_str3[0] != 0) {
//					draw_image_f3(esContext, 0.8 - 0.04, -0.84 + n * 0.1 - 0.04, 0.8 + 0.04, -0.84 + n * 0.1 + 0.04, 0.003, tmp_str3);
//				}

				strcpy(tmp_str2, ModelData[n].sysstr);

				sprintf(tmp_str, "%s", ModelData[n].name);
				if (n == ModelActive) {
					draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str, FONT_GREEN, 1.0, -0.87 + n * 0.1, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, model_select, n + 1);
					sprintf(tmp_str, "MODEL%i", n);
					draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str2, FONT_GREEN, 1.0, -0.82 + n * 0.1, 0.003, 0.03, ALIGN_CENTER, ALIGN_TOP, model_select, n + 1);
				} else {
					draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str, FONT_WHITE, 1.0, -0.87 + n * 0.1, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, model_select, n + 1);
					sprintf(tmp_str, "MODEL%i", n);
					draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str2, FONT_WHITE, 1.0, -0.82 + n * 0.1, 0.003, 0.03, ALIGN_CENTER, ALIGN_TOP, model_select, n + 1);
				}
				if (ModelData[n].heartbeat > 0) {
					draw_circleFilled_f3(esContext, 1.22, -0.84 + n * 0.1, 0.003, (float)ModelData[n].heartbeat / 5000.0, 255, 0, 0, ModelData[n].heartbeat * 2);
					draw_line_f3(esContext, 1.22 - 0.05, -0.84 + n * 0.1 - (ModelData[n].roll / 3000.0), 0.003, 1.22 + 0.05, -0.84 + n * 0.1 + (ModelData[n].roll / 3000.0), 0.003, 255, 255, 255, 255);
				}
			}
		}
		draw_text_button(esContext, "SCREENSEL", setup.view_mode, screennames[setup.view_mode], FONT_WHITE, -1.0, -0.95, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, screen_select, -1.0);
		if (view_screenlist == 1) {
			draw_box_f3(esContext, -1.3, -0.88, 0.002, -0.7, -0.88 + 0.1 * VIEW_MODE_LAST, 0.002, 0, 0, 0, 200);
			draw_rect_f3(esContext, -1.3, -0.88, 0.002, -0.7, -0.88 + 0.1 * VIEW_MODE_LAST, 0.002, 255, 255, 255, 200);
			for (n = 0; n < VIEW_MODE_LAST; n++) {
				sprintf(tmp_str, "screen %i", n);
				sprintf(tmp_str2, "%s", screennames[n]);
				if (n == setup.view_mode) {
					draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str2, FONT_GREEN, -1.0, -0.87 + n * 0.1, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, screen_select, n);
				} else {
					draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str2, FONT_WHITE, -1.0, -0.87 + n * 0.1, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, screen_select, n);
				}
			}
		}


	}
	if (message > 0) {
		draw_text_f(esContext, 0.0 - strlen(message_txt) * 0.05 * 0.6 / 2 - 0.012, -0.99, 0.05, 0.05, FONT_PINK, message_txt);
//		draw_text_f(esContext, -1.35, -0.99, 0.04, 0.04, FONT_PINK, message_txt);
	}
	if (blink > 128) {
		if (ModelData[ModelActive].found_rc == 1 && ModelData[ModelActive].heartbeat_rc == 0) {
			draw_text_f(esContext, 1.2 - strlen("LOST_RC") * 0.06 * 0.6, 0.9, 0.06, 0.06, FONT_PINK, "LOST_RC");
		} else if (ModelData[ModelActive].heartbeat == 0 && connection_found == 1) {
			draw_text_f(esContext, 1.2 - strlen("LOST_CON") * 0.06 * 0.6, 0.9, 0.06, 0.06, FONT_PINK, "LOST_CON");
		} else if (ModelData[ModelActive].voltage > 1.0 && ModelData[ModelActive].voltage < setup.volt_min && connection_found == 1) {
			draw_text_f(esContext, 1.2 - strlen("LOW_BAT") * 0.06 * 0.6, 0.9, 0.06, 0.06, FONT_PINK, "LOW_BAT");
		}
	}
	if (view_overview == 1) {
		draw_text_button(esContext, "M", setup.view_mode, "[M]", FONT_GREEN, 1.29, 0.93, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, overview_show, 0.0);
	} else {
		draw_text_button(esContext, "M", setup.view_mode, "[M]", FONT_WHITE, 1.29, 0.93, 0.003, 0.06, ALIGN_CENTER, ALIGN_TOP, overview_show, 0.0);
	}

	// LogPlay
	if (logplay == 1) {
		logplay_draw_control(esContext, 0.0, 0.85);
	}

#ifndef ANDROID
	// Mouse-Pointer
	draw_pointer(esContext, mouse_x, mouse_y, 16, 16, TEXTURE_POINTER);
#endif
	glEnable( GL_DEPTH_TEST );

#ifdef HTML_DRAWING
	strncpy(display_html2, display_html, HTML_MAX - 1);
	display_html[0] = 0;
	strcat(display_html, "	var canvas = document.getElementById('myCanvas');\n");
	strcat(display_html, "	var context = canvas.getContext('2d');\n");
	strcat(display_html, "	context.clearRect(0, 0, canvas.width, canvas.height);\n");
	strcat(display_html, "	var canvas2 = document.getElementById('myCanvas2');\n");
	strcat(display_html, "	var context2 = canvas2.getContext('2d');\n");
	strcat(display_html, "	context2.clearRect(0, 0, canvas2.width, canvas2.height);\n");
	strcat(display_html, "	context.lineWidth = 1;\n");
	strcat(display_html, "	context.font = 'bold 16px Arial';\n");
	strcat(display_html, "	context2.lineWidth = 1;\n");
	strcat(display_html, "	context2.font = 'bold 16px Arial';\n");
	strcat(display_html, "	context2.beginPath();\n");
	strcat(display_html, "	context2.moveTo(0, 0); context2.lineTo(canvas2.width, 0); context2.lineTo(canvas2.width, canvas2.height); context2.lineTo(0, canvas2.height); context2.lineTo(0, 0);\n");
	strcat(display_html, "	context2.fillStyle = '#000000'; context2.fill();\n");
	strcat(display_html, "	context2.closePath();\n");
#endif

#ifndef CONSOLE_ONLY
	draw_update(esContext);
#endif

	gui_ov_lock = 0;

	SDL_Delay(15);
}

void ShutDown ( ESContext *esContext ) {
	int n = 0;
#ifdef USE_VLC
	vlc_exit();
#endif
#ifdef USE_OPENCV
	openvc_exit();
#endif
#ifdef USE_WIFIBC
	wifibc_exit();
#endif
	serial_monitor_exit();

	SDL_Log("Shutdown\n");
	gui_running = 0;
	SDL_Delay(600);
	LogSave();
	setup_save();
	for (n = 0; n < MODELS_MAX; n++) {
		stop_telemetry(n);
	}

	mavlink_exit_udp();
	mavlink_exit_tcp();
#ifndef WINDOWS
	openpilot_exit_tcp();
#endif
	frsky_exit();
	tracker_exit();
	jeti_exit();
	gcs_gps_exit();
	webserv_exit();
	map_exit();

#ifdef DPF_DISPLAY
	SDL_WaitThread(thread_dpf, NULL);
	dpf_exit();
#endif

	SDL_Log("telemetry: thread kill\n");
	SDL_KillThread(thread_telemetry);
#ifdef RPI_NO_X
	SDL_Log("touch: thread kill\n");
	SDL_KillThread(thread);
#endif

#ifndef OSX
#ifdef SDLGL
#if defined USE_V4L
	videodev_stop();
#endif
#endif
#endif
#ifndef OSX
#ifndef WINDOWS
	system("killall -9 espeak 2> /dev/null > /dev/null");
#endif
#endif

	SDL_Log("draw: exit\n");
	draw_exit(esContext);
	unlink("/tmp/gcs.run");
}

#ifdef DPF_DISPLAY

void dpf_fill (uint8_t r, uint8_t g, uint8_t b);
void dpf_set (uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
uint16_t dpf_draw_string (uint16_t x, uint16_t y, char *string, uint8_t r, uint8_t g, uint8_t b);

int dpf_thread (void *data) {
	char tmp_str[100];
	uint8_t y = 0;
	uint8_t x = 0;
	while (gui_running == 1) {
		dpf_fill(0, 0, 0);

		time_t liczba_sekund;
		struct tm strukt;
		time(&liczba_sekund);
		localtime_r(&liczba_sekund, &strukt); 
		sprintf(tmp_str, "%02i:%02i:%02i", strukt.tm_hour, strukt.tm_min, strukt.tm_sec);

		sprintf(tmp_str, "%s", message_txt);

		dpf_draw_string(10, 10, tmp_str, 0, 255, x);
		x += 20;
		dpf_update();
		SDL_Delay(10);
	}
}
#endif

#ifdef USE_VISTA2D
void glut_timer (int t) {
	Draw(GlobalesContext);
	glutTimerFunc(10, glut_timer, 0);
}
#endif


int main ( int argc, char *argv[] ) {

//glutInit (&argc, argv);

	int n = 0;
	char dir[1024];
#ifndef WINDOWS
	char tmp_name[201];
#endif
	ESContext esContext;
	GlobalesContext = &esContext;
#ifdef USE_VISTA2D
	glutInit (&argc, argv);
#endif
#ifdef WINDOWS
	sprintf(dir, "%s", get_datadirectory());
	mkdir(dir);
	sprintf(dir, "%s/MAPS", get_datadirectory());
	mkdir(dir);
	sprintf(dir, "%s/MAPS/part", get_datadirectory());
	mkdir(dir);
	sprintf(dir, "%s/logs", get_datadirectory());
	mkdir(dir);
	sprintf(dir, "%s/models", get_datadirectory());
	mkdir(dir);
	sprintf(dir, "%s/PARAMS", get_datadirectory());
	mkdir(dir);
	sprintf(dir, "%s/mavlink", get_datadirectory());
	mkdir(dir);
#else
	sprintf(dir, "%s", get_datadirectory());
	mkdir(dir, 0755);
	sprintf(dir, "%s/MAPS", get_datadirectory());
	mkdir(dir, 0755);
	sprintf(dir, "%s/MAPS/part", get_datadirectory());
	mkdir(dir, 0755);
	sprintf(dir, "%s/logs", get_datadirectory());
	mkdir(dir, 0755);
	sprintf(dir, "%s/models", get_datadirectory());
	mkdir(dir, 0755);
	sprintf(dir, "%s/PARAMS", get_datadirectory());
	mkdir(dir, 0755);
	sprintf(dir, "%s/mavlink", get_datadirectory());
	mkdir(dir, 0755);
#endif

	if (argc >= 3 && strcmp(argv[1], "-c") == 0) {
		strncpy(clientmode_server, argv[2], 1023);
		if (argc >= 4) {
			clientmode_port = atoi(argv[3]);
		}
		SDL_Log("clientmode: %s:%i\n", clientmode_server, clientmode_port);
		clientmode = 1;
	}

#ifndef WINDOWS
	time_t liczba_sekund;
	struct tm strukt;
	time(&liczba_sekund);
	localtime_r(&liczba_sekund, &strukt); 
	sprintf(tmp_name, "%s/WMM.COF", BASE_DIR);
	init_declination(tmp_name, strukt.tm_year + 1900, strukt.tm_mon + 1, strukt.tm_mday);
#endif

#ifdef DPF_DISPLAY
	dpf_init();
	SDL_Log("dpf: init thread\n");
#ifdef SDL2
	thread_dpf = SDL_CreateThread(dpf_thread, NULL, NULL);
#else
	thread_dpf = SDL_CreateThread(dpf_thread, NULL);
#endif
#endif

	setup_waypoints();
	setup_load();

#if defined USE_APRS
	if (setup.aprs_enable == 1) {
		aprs_init(setup.aprs_server, setup.aprs_port);
	}
#endif
#ifndef CONSOLE_ONLY
	SDL_Log("init GL\n");
	draw_init(&esContext);
	SDL_ShowCursor(0);
	printf( "* Vendor     : %s\n", glGetString( GL_VENDOR ) );
	printf( "* Renderer   : %s\n", glGetString( GL_RENDERER ) );
	printf( "* Version    : %s\n", glGetString( GL_VERSION ) );
#ifndef OSX
#ifdef SDLGL
#if defined USE_V4L
	videodev_start(setup.videocapture_device, setup.videocapture_width, setup.videocapture_height);
#endif
#endif
#endif
#endif

#ifdef USE_WIFIBC
	wifibc_init();
#endif
#if defined USE_OPENCV
	openvc_init(setup.opencv_file, setup.opencv_device, setup.opencv_features);
#elif defined USE_VLC
	vlc_init(setup.videocapture_device);
#endif

#ifdef RPI_NO_X
	if ((touch_fd = open(setup.touchscreen_device, O_RDONLY)) >= 0) {
		SDL_Log("touch: init thread\n");
#ifdef SDL2
		thread = SDL_CreateThread(touchscreen_thread, NULL, NULL);
#else
		thread = SDL_CreateThread(touchscreen_thread, NULL);
#endif
		if ( thread == NULL ) {
			fprintf(stderr, "touch: Thread konnte nicht gestartet werden: %s\n", SDL_GetError());
			return 0;
		}
	} else {
		setup.calibration_mode = 0;
	}
#endif

#ifndef CONSOLE_ONLY
	// preload map on startup for faster view-changes
	draw_text_f3(&esContext, -1.4, -0.95, 0.003, 0.06, 0.06, FONT_WHITE, "PreLoading Maps...");
	draw_update(&esContext);
	screen_map(&esContext, lat, lon, zoom);
#endif

	int16_t zz = get_altitude(ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long);
	if (ModelData[ModelActive].p_alt < zz + 10) {
		ModelData[ModelActive].p_alt = zz + 10;
	}

#ifdef SDLGL
	joystick_init();
#endif

//	openpilot_init_tcp();
	mavlink_init_udp();
	mavlink_init_tcp();
	mavlink_forward_udp_init();
	frsky_init(setup.frsky_port, setup.frsky_baud);
	jeti_init(setup.jeti_port, setup.jeti_baud);
	gcs_gps_init(setup.gcs_gps_port, setup.gcs_gps_baud);
	rcflow_init(setup.rcflow_port, setup.rcflow_baud);
	tracker_init(setup.tracker_port, setup.tracker_baud);

	if (setup.weather_enable == 1) {
		weather_init();
	}

	serial_monitor_init();

	SDL_Log("telemetry: init thread\n");
	for (n = 0; n < MODELS_MAX; n++) {
		reset_telemetry(n);
	}

#ifdef SDL2
	thread_telemetry = SDL_CreateThread(telemetry_thread, NULL, NULL);
#else
	thread_telemetry = SDL_CreateThread(telemetry_thread, NULL);
#endif
	if ( thread_telemetry == NULL ) {
		fprintf(stderr, "telemetry: thread konnte nicht gestartet werden: %s\n", SDL_GetError());
		return 0;
	}

	SDL_Log("main: start loop\n");
#ifdef CONSOLE_ONLY
	SDL_Log("main: now you can connect via Browser or Google-Earth to port :%i\n", setup.webport);
#endif

#ifdef USE_VISTA2D
	glutTimerFunc(30, glut_timer, 0);
	glutMainLoop();
#else
#ifndef SDLGL
	esMainLoop(&esContext);
#else
	while (gui_running == 1) {
		Draw(&esContext);
	}
#endif
#endif
#if defined USE_APRS
	aprs_exit();
#endif
	weather_exit();
	ShutDown(&esContext);
	return 0;
}


