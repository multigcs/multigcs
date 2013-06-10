
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <math.h>
#include <linux/version.h>
#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <ctype.h>
#include <termios.h>

#include <png.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_events.h>

#ifndef SDLGL
#include "esUtil.h"
#else
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include "GL/gl.h"
#include "GL/glext.h"
#endif

#include <model.h>

#include <geomag70.h>

#include "my_mavlink.h"
#include <userdata.h>
#include <main.h>
#include "my_gps.h"
#include "mwi21.h"
#include "openpilot.h"
#include "jeti.h"
#include "frsky.h"
#include "screen_background.h"
#include "screen_wpedit.h"
#include "screen_map.h"
#include "screen_hud.h"
#include "screen_graph.h"
#include "screen_calibration.h"
#include "screen_telemetry.h"
#include "screen_fms.h"
#include "screen_system.h"
#include "screen_tcl.h"
#include "screen_mavlink_menu.h"
#include "screen_mwi_menu.h"
#include "screen_openpilot_menu.h"
#include "screen_videolist.h"
#include "screen_model.h"
#include "screen_rcflow.h"

// V4L
#ifdef SDLGL
int videodev_start (void);
int videodev_stop (void);
SDL_Surface *videodev_loop (void);
void draw_surface_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, SDL_Surface *screen);
#endif

Model ModelData;
char teletypes[8][15] = {
	"MULTIWII_21",
	"AUTOQUAD",
	"ARDUPILOT",
	"MEGAPIRATE_NG",
	"OPENPILOT",
	"GPS_NMEA",
	"FRSKY",
	"BASEFLIGHT",
};
char modeltypes[5][15] = {
	"MULTICOPTER",
	"HELICOPTER",
	"PLANE",
	"CAR",
	"BOAT",
};
uint8_t fullscreen = 0;
uint16_t screen_w = SCREEN_W;
uint16_t screen_h = SCREEN_H;
uint16_t screen_border_x = 0;
uint16_t screen_border_y = 0;
char keyboard_key[100];
uint8_t keyboard_shift = 0;
uint8_t keyboard_altgr = 0;
SDL_Event event;
char touchscreen_device[200];
uint8_t calibration_mode = 1;
uint16_t calibration_timeout = 200;
int calibration_min_x = 1000;
int calibration_max_x = 3000;
int last_x = 0;
int last_y = 0;
int calibration_min_y = 1000;
int calibration_max_y = 3000;
int touch_fd = -1;
volatile uint8_t gui_running = 1;
uint8_t hud_view = 0;
uint8_t hud_view_map = 0;
uint8_t hud_view_video = 0;
uint8_t hud_view_tunnel = 0;
uint8_t hud_view_mark = 0;
float gcs_roll = 0.0;
float gcs_pitch = 0.0;
float gcs_yaw = 0.0;
float volt_min = 11.0;
int8_t speak = 1;
uint16_t heartbeat_timer = 0;
uint16_t heartbeat_rc_timer = 0;
uint16_t blink_timer = 0;
uint16_t speak_timer = 0;
uint16_t msg_timer = 0;
uint8_t map_mark = 0;
uint8_t redraw_flag = 1;
uint16_t mouse_x = 0;
uint16_t mouse_y = 0;
char jeti_port[1024];
uint32_t jeti_baud = 9600;
char frsky_port[1024];
uint32_t frsky_baud = 9600;
char gcs_gps_port[1024];
uint32_t gcs_gps_baud = 9600;
char telemetrie_port[1024];
uint32_t telemetrie_baud = 57600;
uint8_t telemetrie_type = 0;
uint8_t message = 0;
char message_txt[1024];
WayPoint WayPoints[MAX_WAYPOINTS];
int8_t waypoint_active = 0;
uint8_t view_mode = 0;
uint8_t view_mode_last = 255;
uint8_t view_mode_next = 0;
float trans_count = 0.0;
Button Buttons[MAX_BUTTONS];
int startup_time = 0;
struct list_element *LogLines = NULL;
struct list_element *LogLinesEnd = NULL;
uint8_t contrast = 0;
uint8_t connection_found = 0;

SDL_Thread *thread = NULL;
SDL_Thread *thread_telemetrie = NULL;

#ifdef SDLGL

void save_screenshot (void) {

//	system("xfce4-screenshooter -w -o gimp");
	char name[100];
	char tmp_str[100];

	if (view_mode == VIEW_MODE_HUD) {
		strcpy(name, "hud");
	} else if (view_mode == VIEW_MODE_TELEMETRY) {
		strcpy(name, "telemetry");
	} else if (view_mode == VIEW_MODE_MODEL) {
		strcpy(name, "model");
	} else if (view_mode == VIEW_MODE_RCFLOW) {
		strcpy(name, "rcflow");
	} else if (view_mode == VIEW_MODE_FMS) {
		strcpy(name, "fms");
	} else if (view_mode == VIEW_MODE_WPEDIT) {
		strcpy(name, "fms");
	} else if (view_mode == VIEW_MODE_MAP) {
		strcpy(name, "map");
	} else if (view_mode == VIEW_MODE_VIDEOLIST) {
		strcpy(name, "video");
	} else if (view_mode == VIEW_MODE_SYSTEM) {
		strcpy(name, "system");
	} else if (view_mode == VIEW_MODE_TCL) {
		strcpy(name, "tcl");
	} else if (view_mode == VIEW_MODE_FCMENU) {
		if (ModelData.teletype == TELETYPE_MULTIWII_21) {
			strcpy(name, "mwi");
		} else if (ModelData.teletype == TELETYPE_MULTIWII_21) {
			strcpy(name, "baseflight");
		} else if (ModelData.teletype == TELETYPE_GPS_NMEA) {
			strcpy(name, "nmea");
		} else if (ModelData.teletype == TELETYPE_OPENPILOT) {
			strcpy(name, "openpilot");
		} else if (ModelData.teletype == TELETYPE_FRSKY) {
			strcpy(name, "frsky");
		} else if (ModelData.teletype == TELETYPE_AUTOQUAD) {
			strcpy(name, "mavlink");
		} else {
			strcpy(name, "fcmenu");
		}
	}

	sprintf(tmp_str, "xwd -name \"Multi-GCS\" -out /tmp/screen.dump; ./save_screenshot.sh /tmp/screen.dump %s", name);
	system(tmp_str);

}
#endif



SDL_Surface* CreateSurface(int width,int height) {
	SDL_Surface *display = SDL_GetVideoSurface();
	const SDL_PixelFormat fmt = *(display->format);
	return SDL_CreateRGBSurface(0,width,height, fmt.BitsPerPixel, fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}

void LogSave (char *file) {
        FILE *fr;
	struct list_element *list = LogLines;
        fr = fopen(file, "w");
	if (fr != 0) {
		if (list->line != NULL) {
			fprintf(fr, "%s\n", list->line);
		}
		while (list->next != NULL) {
			list=list->next;
			if (list->line != NULL) {
				fprintf(fr, "%s\n", list->line);
			}
		}
	        fclose(fr);
	} else {
		printf("Can not save log-file: %s\n", file);
	}
}

void LogInit (char *line) {
	LogLines = malloc(sizeof(struct list_element));
	LogLines->line = malloc(strlen(line) + 1);
	strcpy(LogLines->line, line);
	LogLines->next = NULL;
	LogLinesEnd = LogLines;
}

void LogAppend (char *line) {
	LogLinesEnd->next = malloc(sizeof(struct list_element));
	LogLinesEnd = LogLinesEnd->next;
	LogLinesEnd->line = malloc(strlen(line) + 1);
	strcpy(LogLinesEnd->line, line);
	LogLinesEnd->next = NULL;
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

uint8_t set_button (char *name, uint8_t view_mode, float x1, float y1, float x2, float y2, uint8_t (*callback) (char *, float, float, int8_t, float), float data, uint8_t type) {
	uint16_t n = 0;
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
			strcpy(Buttons[n].name, name);
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
	printf("to many buttons\n");
	return 2;
}

int8_t check_button (uint8_t view_mode, float x, float y, uint8_t button, uint8_t event) {
	int16_t n = 0;

	if (event == BUTTON_RELEASE) {
		for (n = 0; n < MAX_BUTTONS; n++) {
			Buttons[n].status = 0;
		}
	} else if (event == BUTTON_MOVE) {
		for (n = 0; n < MAX_BUTTONS; n++) {
			if (Buttons[n].status == BUTTON_PRESS) {
				if (Buttons[n].type == 2) {
					(*Buttons[n].callback)(Buttons[n].name, x - Buttons[n].start_x, y - Buttons[n].start_y, button, Buttons[n].data);
					Buttons[n].start_x = x;
					Buttons[n].start_y = y;
				} else {
					(*Buttons[n].callback)(Buttons[n].name, x, y, button, Buttons[n].data);
				}
				return n;
			}
		}
	}

	for (n = MAX_BUTTONS - 1; n >= 0; n--) {
		if (Buttons[n].name[0] != 0 && Buttons[n].view_mode == view_mode && x > Buttons[n].x1 && x < Buttons[n].x2 && y > Buttons[n].y1 && y < Buttons[n].y2) {
			if (Buttons[n].type == 0 && event == BUTTON_PRESS) {
//				printf("CB: %s\n", Buttons[n].name);
				(*Buttons[n].callback)(Buttons[n].name, x, y, button, Buttons[n].data);
				return n;
			} else if (Buttons[n].type == 1 || Buttons[n].type == 2) {
				if (event == BUTTON_PRESS) {
					Buttons[n].status = event;
					Buttons[n].start_x = x;
					Buttons[n].start_y = y;
					if (Buttons[n].type == 2) {
						(*Buttons[n].callback)(Buttons[n].name, x - Buttons[n].start_x, y - Buttons[n].start_y, button, Buttons[n].data);
						Buttons[n].start_x = x;
						Buttons[n].start_y = y;
					} else {
						(*Buttons[n].callback)(Buttons[n].name, x, y, button, Buttons[n].data);
					}
					return n;
				}
			}
		}
	}
	return -1;
}

uint8_t need_bluetooth (void) {
	if (strstr(telemetrie_port, "/dev/rfcomm") > 0) {
		return 1;
	}
	return 0;
}

void stop_telemetrie (void) {
	mwi21_exit();
	mavlink_exit();
	gps_exit();
	openpilot_exit();
	frsky_mode(0);
}

void reset_telemetrie (void) {
	stop_telemetrie();
	if (ModelData.teletype == TELETYPE_MULTIWII_21) {
		mwi21_init(telemetrie_port, telemetrie_baud);
	} else if (ModelData.teletype == TELETYPE_BASEFLIGHT) {
		mwi21_init(telemetrie_port, telemetrie_baud);
	} else if (ModelData.teletype == TELETYPE_GPS_NMEA) {
		gps_init(telemetrie_port, telemetrie_baud);
	} else if (ModelData.teletype == TELETYPE_OPENPILOT) {
		openpilot_init(telemetrie_port, telemetrie_baud);
	} else if (ModelData.teletype == TELETYPE_FRSKY) {
		frsky_mode(1);
	} else {
		mavlink_init(telemetrie_port, telemetrie_baud);
	}
}

void set_telemetrie (char *device, uint32_t baud) {
	strcpy(telemetrie_port, device);
	telemetrie_baud = baud;
	reset_telemetrie();
}

void setup_waypoints (void) {
	int n = 0;
	for (n = 0; n < MAX_WAYPOINTS; n++) {
		WayPoints[n].p_lat = 0.0;
		WayPoints[n].p_long = 0.0;
		WayPoints[n].p_alt = 0.0;
		WayPoints[n].yaw = 0.0;
		WayPoints[n].radius = 2.0;
		WayPoints[n].wait = 500.0;
		WayPoints[n].orbit = 0.0;
		WayPoints[n].name[0] = 0;
		WayPoints[n].command[0] = 0;
		WayPoints[n].type = 0;
	}

	WayPoints[0].p_lat = 50.29197;
	WayPoints[0].p_long = 9.12764;
	WayPoints[0].p_alt = 125.0;
	WayPoints[0].yaw = 0.0;
	WayPoints[0].radius = 0.0;
	WayPoints[0].wait = 0.0;
	WayPoints[0].orbit = 0.0;
	WayPoints[0].type = 1;
	strcpy(WayPoints[0].name, "HOME");
	strcpy(WayPoints[0].command, "");

	WayPoints[1].p_lat = 50.29057;
	WayPoints[1].p_long = 9.12704;
	WayPoints[1].p_alt = 577.0;
	WayPoints[1].yaw = 0.0;
	WayPoints[1].radius = 0.0;
	WayPoints[1].wait = 0.0;
	WayPoints[1].orbit = 0.0;
	WayPoints[1].type = 2;
	strcpy(WayPoints[1].name, "WP0");
	strcpy(WayPoints[1].command, "");

	WayPoints[2].p_lat = 50.28745;
	WayPoints[2].p_long = 9.12207;
	WayPoints[2].p_alt = 25.0;
	WayPoints[2].yaw = 0.0;
	WayPoints[2].radius = 0.0;
	WayPoints[2].wait = 0.0;
	WayPoints[2].orbit = 0.0;
	WayPoints[2].type = 2;
	strcpy(WayPoints[2].name, "WP1");
	strcpy(WayPoints[2].command, "WAYPOINT");

	WayPoints[3].p_lat = 50.28745;
	WayPoints[3].p_long = 9.12754;
	WayPoints[3].p_alt = 550.0;
	WayPoints[3].yaw = 0.0;
	WayPoints[3].radius = 2.0;
	WayPoints[3].wait = 5000.0;
	WayPoints[3].orbit = 10.0;
	strcpy(WayPoints[3].name, "WP2-Orbit");
	strcpy(WayPoints[3].command, "WAYPOINT");

	strcpy(WayPoints[0].name, "UAV");
	ModelData.p_lat = WayPoints[0].p_lat;
	ModelData.p_long = WayPoints[0].p_long;
	ModelData.p_alt = WayPoints[0].p_alt;
	ModelData.yaw = WayPoints[0].yaw;

	ModelData.sysid = 250;
	ModelData.compid = 0;
}

void sys_message (char *msg) {
	strcpy(message_txt, msg);
	if (message_txt[strlen(message_txt) - 1] == '\n') {
		message_txt[strlen(message_txt) - 1] = 0;
	}
	message = 255;
	redraw_flag = 1;
}

void setup_save (void) {
        FILE *fr;
        int n = 0;
	if (calibration_mode > 0) {
		calibration_mode = 1;
	}
//        printf("** saving file\n");
	char filename[1024];
	sprintf(filename, "%s/setup.cfg", BASE_DIR);
        fr = fopen(filename, "w");
	if (fr != 0) {
	        fprintf(fr, "model_name   %s\n", ModelData.name);
	        fprintf(fr, "view_mode    %i\n", view_mode);
	        fprintf(fr, "contrast     %i\n", contrast);
	        fprintf(fr, "screen_w     %i\n", screen_w);
	        fprintf(fr, "screen_h     %i\n", screen_h);
	        fprintf(fr, "screen_border_x     %i\n", screen_border_x);
	        fprintf(fr, "screen_border_y     %i\n", screen_border_y);
	        fprintf(fr, "fullscreen   %i\n", fullscreen);
	        fprintf(fr, "lat          %0.8f\n", lat);
	        fprintf(fr, "lon          %0.8f\n", lon);
	        fprintf(fr, "zoom         %i\n", zoom);
	        fprintf(fr, "map_type     %i\n", map_type);
	        fprintf(fr, "center_map     %i\n", center_map);
	        fprintf(fr, "waypoint_active     %i\n", waypoint_active);
	        fprintf(fr, "gcs_gps_port     %s\n", gcs_gps_port);
	        fprintf(fr, "gcs_gps_baud     %i\n", gcs_gps_baud);
	        fprintf(fr, "telemetrie_port %s\n", telemetrie_port);
	        fprintf(fr, "telemetrie_baud %i\n", telemetrie_baud);
	        fprintf(fr, "telemetrie_type %i\n", ModelData.teletype);
	        fprintf(fr, "jeti_port %s\n", jeti_port);
	        fprintf(fr, "jeti_baud %i\n", jeti_baud);
	        fprintf(fr, "frsky_port %s\n", frsky_port);
	        fprintf(fr, "frsky_baud %i\n", frsky_baud);
	        fprintf(fr, "volt_min     %0.1f\n", volt_min);
	        fprintf(fr, "speak        %i\n", speak);
	        fprintf(fr, "hud_view     %i\n", hud_view);
	        fprintf(fr, "hud_view_map %i\n", hud_view_map);
	        fprintf(fr, "hud_view_tunnel %i\n", hud_view_tunnel);
	        fprintf(fr, "map_view     %i\n", map_view);
	        fprintf(fr, "touchscreen_device       %s\n", touchscreen_device);
		fprintf(fr, "calibration_mode         %i\n", calibration_mode);
		fprintf(fr, "calibration_min_x        %i\n", calibration_min_x);
		fprintf(fr, "calibration_max_x        %i\n", calibration_max_x);
		fprintf(fr, "calibration_min_y        %i\n", calibration_min_y);
		fprintf(fr, "calibration_max_y        %i\n", calibration_max_y);
		fprintf(fr, "videolist_lastfile       %s\n", videolist_lastfile);
	        fprintf(fr, "\n");
	        fprintf(fr, "[waypoints]\n");
	        for (n = 0; n < MAX_WAYPOINTS; n++) {
	                if (WayPoints[n].p_lat != 0.0) {
	                        fprintf(fr, "name       %s\n", WayPoints[n].name);
	                        fprintf(fr, "command    %s\n", WayPoints[n].command);
	                        fprintf(fr, "lat        %0.8f\n", WayPoints[n].p_lat);
	                        fprintf(fr, "lon        %0.8f\n", WayPoints[n].p_long);
	                        fprintf(fr, "alt        %f\n", WayPoints[n].p_alt);
	                        fprintf(fr, "yaw        %f\n", WayPoints[n].yaw);
	                        fprintf(fr, "wait       %f\n", WayPoints[n].wait);
	                        fprintf(fr, "radius     %f\n", WayPoints[n].radius);
	                        fprintf(fr, "orbit      %f\n", WayPoints[n].orbit);
	                        fprintf(fr, "type       %i\n", WayPoints[n].type);
	                        fprintf(fr, "\n");
	                }
	        }
	        fclose(fr);
	} else {
		printf("Can not save setup-file: %s\n", filename);
	}
}

void setup_load (void) {
        FILE *fr;
        char line[101];
        char var[101];
        char val[101];
        int mode = 0;
        int wp_num = 0;
#ifdef RPI_NO_X
	strcpy(gcs_gps_port, "/dev/ttyAMA0");;
#else
	strcpy(gcs_gps_port, "/dev/ttyUSB20");;
#endif
	gcs_gps_baud = 9600;
	strcpy(telemetrie_port, "/dev/rfcomm0");;
	telemetrie_baud = 115200;
	strcpy(jeti_port, "/dev/ttyUSB10");;
	jeti_baud = 9600;
	strcpy(frsky_port, "/dev/ttyUSB30");;
	frsky_baud = 9600;
	char filename[1024];
	sprintf(filename, "%s/setup.cfg", BASE_DIR);
        fr = fopen (filename, "r");
	if (fr != 0) {
	        while(fgets(line, 100, fr) != NULL) {
	                var[0] = 0;
	                val[0] = 0;
	                sscanf (line, "%s %s", (char *)&var, (char *)&val);
	                printf ("       %s      %s\n", var, val);
	                if (mode == 0) {
	                        if (strcmp(var, "view_mode") == 0) {
					view_mode = atoi(val);
					view_mode_next = view_mode;
	                        } else if (strcmp(var, "model_name") == 0) {
	                                strcpy(ModelData.name, val);
	                        } else if (strcmp(var, "volt_min") == 0) {
					volt_min = atof(val);
	                        } else if (strcmp(var, "contrast") == 0) {
					contrast = atoi(val);
	                        } else if (strcmp(var, "screen_w") == 0) {
					screen_w = atoi(val);
	                        } else if (strcmp(var, "screen_h") == 0) {
					screen_h = atoi(val);
	                        } else if (strcmp(var, "screen_border_x") == 0) {
					screen_border_x = atoi(val);
	                        } else if (strcmp(var, "screen_border_y") == 0) {
					screen_border_y = atoi(val);
	                        } else if (strcmp(var, "speak") == 0) {
					speak = atoi(val);
	                        } else if (strcmp(var, "fullscreen") == 0) {
					fullscreen = atoi(val);
	                        } else if (strcmp(var, "lat") == 0) {
					lat = atof(val);
					printf("lat = %0.8f\n", lat);
	                        } else if (strcmp(var, "lon") == 0) {
	                                lon = atof(val);
					printf("lon = %0.8f\n", lon);
	                        } else if (strcmp(var, "zoom") == 0) {
	                                zoom = atoi(val);
	                        } else if (strcmp(var, "waypoint_active") == 0) {
	                                waypoint_active = atoi(val);
	                        } else if (strcmp(var, "gcs_gps_port") == 0) {
	                                strcpy(gcs_gps_port, val);
	                        } else if (strcmp(var, "gcs_gps_baud") == 0) {
	                                gcs_gps_baud = atoi(val);
	                        } else if (strcmp(var, "telemetrie_port") == 0) {
	                                strcpy(telemetrie_port, val);
	                        } else if (strcmp(var, "telemetrie_baud") == 0) {
	                                telemetrie_baud = atoi(val);
	                        } else if (strcmp(var, "telemetrie_port") == 0) {
	                                strcpy(telemetrie_port, val);
	                        } else if (strcmp(var, "telemetrie_baud") == 0) {
	                                telemetrie_baud = atoi(val);
	                        } else if (strcmp(var, "telemetrie_type") == 0) {
	                                ModelData.teletype = atoi(val);
	                        } else if (strcmp(var, "jeti_port") == 0) {
	                                strcpy(jeti_port, val);
	                        } else if (strcmp(var, "jeti_baud") == 0) {
	                                jeti_baud = atoi(val);
	                        } else if (strcmp(var, "frsky_port") == 0) {
	                                strcpy(frsky_port, val);
	                        } else if (strcmp(var, "frsky_baud") == 0) {
	                                frsky_baud = atoi(val);
	                        } else if (strcmp(var, "map_type") == 0) {
	                                map_type = atoi(val);
	                        } else if (strcmp(var, "center_map") == 0) {
	                                center_map = atoi(val);
	                        } else if (strcmp(var, "touchscreen_device") == 0) {
	                                strcpy(touchscreen_device, val);
	                        } else if (strcmp(var, "calibration_mode") == 0) {
	                                calibration_mode = atoi(val);
	                        } else if (strcmp(var, "calibration_min_x") == 0) {
	                                calibration_min_x = atoi(val);
	                        } else if (strcmp(var, "calibration_max_x") == 0) {
	                                calibration_max_x = atoi(val);
	                        } else if (strcmp(var, "calibration_min_y") == 0) {
	                                calibration_min_y = atoi(val);
	                        } else if (strcmp(var, "calibration_max_y") == 0) {
	                                calibration_max_y = atoi(val);
	                        } else if (strcmp(var, "videolist_lastfile") == 0) {
	                                strcpy(videolist_lastfile, val);
	                        } else if (strcmp(var, "hud_view") == 0) {
	                                hud_view = atoi(val);
	                        } else if (strcmp(var, "hud_view_map") == 0) {
	                                hud_view_map = atoi(val);
	                        } else if (strcmp(var, "hud_view_tunnel") == 0) {
	                                hud_view_tunnel = atoi(val);
	                        } else if (strcmp(var, "map_view") == 0) {
	                                map_view = atoi(val);
	                        } else if (strcmp(var, "[waypoints]") == 0) {
	                                mode = 1;
	                        }
	                } else if (mode == 1) {
	                        if (var[0] == 0) {
	                                if (WayPoints[wp_num].p_lat != 0.0) {
	                                        wp_num++;
	                                        WayPoints[wp_num].p_lat = 0.0;
	                                        WayPoints[wp_num].p_long = 0.0;
	                                        WayPoints[wp_num].p_alt = 0.0;
	                                        WayPoints[wp_num].yaw = 0.0;
	                                        WayPoints[wp_num].name[0] = 0;
	                                        WayPoints[wp_num].command[0] = 0;
	                                        WayPoints[wp_num].type = 0;
	                                }
	                        } else if (strcmp(var, "name") == 0) {
	                                strcpy(WayPoints[wp_num].name, val);
	                        } else if (strcmp(var, "command") == 0) {
	                                strcpy(WayPoints[wp_num].command, val);
	                        } else if (strcmp(var, "lat") == 0) {
	                                WayPoints[wp_num].p_lat = atof(val);
	                        } else if (strcmp(var, "lon") == 0) {
	                                WayPoints[wp_num].p_long = atof(val);
	                        } else if (strcmp(var, "alt") == 0) {
	                                WayPoints[wp_num].p_alt = atof(val);
	                        } else if (strcmp(var, "yaw") == 0) {
	                                WayPoints[wp_num].yaw = atof(val);
	                        } else if (strcmp(var, "wait") == 0) {
	                                WayPoints[wp_num].wait = atof(val);
	                        } else if (strcmp(var, "radius") == 0) {
	                                WayPoints[wp_num].radius = atof(val);
	                        } else if (strcmp(var, "orbit") == 0) {
	                                WayPoints[wp_num].orbit = atof(val);
	                        } else if (strcmp(var, "type") == 0) {
	                                WayPoints[wp_num].type = atoi(val);
	                        }
	                }
	        }
	        fclose(fr);
	} else {
		printf("Can not load setup-file: %s\n", filename);
	}
	if (calibration_mode > 0) {
		calibration_mode = 1;
	}

	strcpy(WayPoints[0].name, ModelData.name);
	ModelData.p_lat = WayPoints[0].p_lat;
	ModelData.p_long = WayPoints[0].p_long;
	ModelData.p_alt = WayPoints[0].p_alt;
	ModelData.yaw = WayPoints[0].yaw;

	strcpy(ModelData.teledevice, telemetrie_port);
	ModelData.telebaud = telemetrie_baud;

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

uint8_t key_pressed = 0;
void check_events (ESContext *esContext, SDL_Event event) {
	static uint8_t mousemode = 0;

	static float mousestart_x = 0.0;
	static float mousestart_y = 0.0;

	if (event.type == SDL_QUIT) {
		ShutDown( esContext );
		exit(0);
	} else if (event.type == SDL_KEYUP) {
		if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "right") == 0) {
			key_pressed &= ~(1<<0);
		} else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "left") == 0) {
			key_pressed &= ~(1<<1);
		} else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "up") == 0) {
			key_pressed &= ~(1<<2);
		} else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "down") == 0) {
			key_pressed &= ~(1<<3);
		} else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "[+]") == 0) {
			key_pressed &= ~(1<<4);
		} else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "[-]") == 0) {
			key_pressed &= ~(1<<5);
		} else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "right shift") == 0 || strcmp(SDL_GetKeyName(event.key.keysym.sym), "left shift") == 0) {
			keyboard_shift = 0;
		} else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "alt gr") == 0) {
			keyboard_altgr = 0;
		}
	} else if (event.type == SDL_KEYDOWN) {
		event.type = 0;
		if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "right shift") == 0 || strcmp(SDL_GetKeyName(event.key.keysym.sym), "left shift") == 0) {
			keyboard_shift = 1;
		}
		if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "alt gr") == 0) {
			keyboard_altgr = 1;
		}

		if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "1") == 0) {
			strcpy(keyboard_key, "!");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "2") == 0) {
			strcpy(keyboard_key, "\"");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "3") == 0) {
			strcpy(keyboard_key, "§");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "4") == 0) {
			strcpy(keyboard_key, "$");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "5") == 0) {
			strcpy(keyboard_key, "%");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "6") == 0) {
			strcpy(keyboard_key, "&");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "7") == 0) {
			strcpy(keyboard_key, "/");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "8") == 0) {
			strcpy(keyboard_key, "(");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "9") == 0) {
			strcpy(keyboard_key, ")");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "0") == 0) {
			strcpy(keyboard_key, "=");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), ",") == 0) {
			strcpy(keyboard_key, ";");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), ".") == 0) {
			strcpy(keyboard_key, ":");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "-") == 0) {
			strcpy(keyboard_key, "_");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "+") == 0) {
			strcpy(keyboard_key, "*");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "#") == 0) {
			strcpy(keyboard_key, "'");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "^") == 0) {
			strcpy(keyboard_key, "°");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "<") == 0) {
			strcpy(keyboard_key, ">");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "world 63") == 0) {
			strcpy(keyboard_key, "?");
		} else if (keyboard_shift == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "world 20") == 0) {
			strcpy(keyboard_key, "`");
		} else if (keyboard_shift == 1) {
			strcpy(keyboard_key, SDL_GetKeyName(event.key.keysym.sym));
			keyboard_key[0] = keyboard_key[0] - 32;
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "7") == 0) {
			strcpy(keyboard_key, "{");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "8") == 0) {
			strcpy(keyboard_key, "[");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "9") == 0) {
			strcpy(keyboard_key, "]");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "0") == 0) {
			strcpy(keyboard_key, "}");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "#") == 0) {
			strcpy(keyboard_key, "`");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "<") == 0) {
			strcpy(keyboard_key, "|");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "e") == 0) {
			strcpy(keyboard_key, "€");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "m") == 0) {
			strcpy(keyboard_key, "µ");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "world 63") == 0) {
			strcpy(keyboard_key, "\\");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "world 20") == 0) {
			strcpy(keyboard_key, "¸");
		} else if (keyboard_altgr == 1 && strcmp(SDL_GetKeyName(event.key.keysym.sym), "q") == 0) {
			strcpy(keyboard_key, "@");
		} else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "world 63") == 0) {
			strcpy(keyboard_key, "ß");
		} else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "world 20") == 0) {
			strcpy(keyboard_key, "´");
		} else {
			strcpy(keyboard_key, SDL_GetKeyName(event.key.keysym.sym));
		}



		redraw_flag = 1;
	} else if (event.type == SDL_MOUSEMOTION) {
		event.type = 0;
		mouse_x = event.button.x;
		mouse_y = event.button.y;
		map_mark = 0;
		float bx = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
		float by = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
		if (check_button(view_mode, bx, by, event.button.button, BUTTON_MOVE) != -1) {
			redraw_flag = 1;
			return;
		}
		if (mousemode == 1) {
			float x1 = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
			float y1 = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
			x1 += offset_x1;
			y1 += offset_y1;
			int16_t bx = (x1 / aspect + 1.0) / 2.0 * (float)esContext->width;
			int16_t by = (y1 + 1.0) / 2.0 * (float)esContext->height;
			float mouse_long = x2long(bx, lon, zoom);
			float mouse_lat = y2lat(by, lat, zoom);
			if (waypoint_active >= 0) {
				if (waypoint_active == 0) {
					WayPoints[waypoint_active].p_alt = get_altitude(mouse_lat, mouse_long);
				} else {
					int16_t zz = get_altitude(mouse_lat, mouse_long);
					if (WayPoints[waypoint_active].p_alt < zz) {
						WayPoints[waypoint_active].p_alt = zz;
					}
				}
				WayPoints[waypoint_active].p_lat = mouse_lat;
				WayPoints[waypoint_active].p_long = mouse_long;
			} else {
				offset_x1 -= x1 - mousestart_x;
				offset_y1 -= y1 - mousestart_y;
			}
		} else	if (view_mode == VIEW_MODE_MAP) {
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
			if (event.button.y > 0 && event.button.y < 60 && event.button.x > 60 && event.button.x < esContext->width - 60) {
				map_mark = 1;
			} else if (event.button.y > esContext->height - 60 && event.button.y < esContext->height && event.button.x > 60 && event.button.x < esContext->width - 60) {
				map_mark = 2;
			} else if (event.button.x > 0 && event.button.x < 60 && event.button.y > 60 && event.button.y < esContext->height - 60) {
				map_mark = 3;
			} else if (event.button.x > esContext->width - 60 && event.button.x < esContext->width && event.button.y > 60 && event.button.y < esContext->height - 60) {
				map_mark = 4;
			}

			x1 += offset_x1;
			y1 += offset_y1;
			int16_t bx = (x1 / aspect + 1.0) / 2.0 * (float)esContext->width;
			int16_t by = (y1 + 1.0) / 2.0 * (float)esContext->height;
			float mouse_long = x2long(bx, lon, zoom);
			float mouse_lat = y2lat(by, lat, zoom);
			int mouse_alt = get_altitude(mouse_lat, mouse_long);

			int ret_dd = 0;
			int ret_dm = 0;
			get_declination(mouse_lat, mouse_long, mouse_alt, &ret_dd, &ret_dm);

			char msg[200];
			sprintf(msg, "POS: %f, %f (ALT_G:%im MAG_D:%id%02im)\n", mouse_lat, mouse_long, mouse_alt, ret_dd, ret_dm);
			sys_message(msg);

		}
		redraw_flag = 1;
	} else if (event.type == SDL_MOUSEBUTTONUP) {
		float bx = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
		float by = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
		if (check_button(view_mode, bx, by, event.button.button, BUTTON_RELEASE) != -1) {
			return;
		}
		if (mousemode == 1) {
			if (offset_x1 < -0.8) {
				int tile_x = long2tilex(lon, zoom);
				tile_x--;
				lon = tilex2long(tile_x, zoom);
				offset_x1 = 0.0;
				mousestart_x = 0.0;
			}
			if (offset_x1 > 0.8) {
				int tile_x = long2tilex(lon, zoom);
				tile_x+= 2;
				lon = tilex2long(tile_x, zoom);
				offset_x1 = 0.0;
				mousestart_x = 0.0;
			}
			if (offset_y1 < -0.8) {
				int tile_y = lat2tiley(lat, zoom);
				tile_y+= 2;
				lat = tiley2lat(tile_y, zoom);
				offset_y1 = 0.0;
				mousestart_y = 0.0;
			}
			if (offset_y1 > 0.8) {
				int tile_y = lat2tiley(lat, zoom);
				tile_y+= 2;
				lat = tiley2lat(tile_y, zoom);
				offset_y1 = 0.0;
				mousestart_y = 0.0;
			}
		}
		mousemode = 0;
		if (waypoint_active < 1) {
			waypoint_active = 1;
		}
	} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		float bx = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
		float by = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
		if (check_button(view_mode, bx, by, event.button.button, BUTTON_PRESS) != -1) {
			return;
		}
		bx += offset_x1;
		by += offset_y1;
		if (event.button.button == 1) {
			if (event.button.y > 0 && event.button.y < 80) {
				if (event.button.x > 0 && event.button.x < 80) {
					if (view_mode_next > 0) {
						view_mode_next = view_mode - 1;
					} else {
						view_mode_next = VIEW_MODE_LAST - 1;
					}
					trans_count = 1.0;
					setup_save();
					return;
				} else if (event.button.x < screen_w && event.button.x > screen_w - 80) {
					view_mode_next = view_mode + 1;
					if (view_mode_next > VIEW_MODE_LAST - 1) {
						view_mode_next = 0;
					}
					trans_count = 1.0;
					setup_save();
					return;
				}
			}
			if (event.button.y > esContext->height - 40 && event.button.y < esContext->height) {
				if (event.button.x > esContext->width - 40 && event.button.x < esContext->width) {
					speak = 1 - speak;
					return;
				}
			}
		}
		if (view_mode == VIEW_MODE_MAP) {
			float x1 = (float)event.button.x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
			float y1 = (float)event.button.y / (float)esContext->height * 2.0 - 1.0;
			x1 += offset_x1;
			y1 += offset_y1;
			int16_t bx = (x1 / aspect + 1.0) / 2.0 * (float)esContext->width;
			int16_t by = (y1 + 1.0) / 2.0 * (float)esContext->height;
			float mouse_long = x2long(bx, lon, zoom);
			float mouse_lat = y2lat(by, lat, zoom);
			if (event.button.button == 1) {
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
				} else if (map_addmode == 1) {
					uint16_t n = 0;
					int16_t nz = get_altitude(mouse_lat, mouse_long);
					if (ModelData.p_alt > nz) {
						nz = ModelData.p_alt;
					}
					if (WayPoints[0].p_alt > nz) {
						nz = WayPoints[0].p_alt;
					}
					for (n = 0; n < MAX_WAYPOINTS; n++) {
						if (WayPoints[n].p_lat == 0.0) {
							WayPoints[n].p_lat = mouse_lat;
							WayPoints[n].p_long = mouse_long;
							WayPoints[n].p_alt = nz;
							WayPoints[n].yaw = 0.0;
							WayPoints[n].orbit = 0.0;
							sprintf(WayPoints[n].name, "WP%i", n);
							strcpy(WayPoints[n].command, "WAYPOINT");
							break;
						}
					}
					map_addmode = 0;
				} else {

					waypoint_active = -1;
					mousestart_x = x1;
					mousestart_y = y1;
					mousemode = 1;

					uint16_t n = 0;
					for (n = 0; n < MAX_WAYPOINTS; n++) {
						if (WayPoints[n].p_lat != 0.0) {
							int16_t mark_x = long2x(WayPoints[n].p_long, lon, zoom);
							int16_t mark_y = lat2y(WayPoints[n].p_lat, lat, zoom);
							if (bx + 20 > mark_x && bx - 20 < mark_x) {
								if (by + 20 > mark_y && by - 20 < mark_y) {
									printf("POINT: %i\n", n);
									waypoint_active = n;
									mousemode = 1;
									break;
								}
							}
						}
					}

				}
			} else if (event.button.button == 3) {
				uint16_t n = 0;
				int16_t nz = get_altitude(mouse_lat, mouse_long);
				if (ModelData.p_alt > nz) {
					nz = ModelData.p_alt;
				}
				if (WayPoints[0].p_alt > nz) {
					nz = WayPoints[0].p_alt;
				}
				for (n = 0; n < MAX_WAYPOINTS; n++) {
					if (WayPoints[n].p_lat == 0.0) {
						WayPoints[n].p_lat = mouse_lat;
						WayPoints[n].p_long = mouse_long;
						WayPoints[n].p_alt = nz;
						WayPoints[n].yaw = 0.0;
						WayPoints[n].orbit = 0.0;
						sprintf(WayPoints[n].name, "WP%i", n);
						strcpy(WayPoints[n].command, "WAYPOINT");
//						printf("GPS;%i;%f;%f;%0.1f;%0.1f\n", time(0), mouse_lat, mouse_long, 25.0, 10.0);
						break;
					}
				}
			} else if (event.button.button == 2) {
				if (waypoint_active >= 0) {
					WayPoints[waypoint_active].p_lat = mouse_lat;
					WayPoints[waypoint_active].p_long = mouse_long;
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
		} else if (view_mode == VIEW_MODE_FCMENU) {
			if (event.button.button == 1) {
			} else if (event.button.button == 2) {
				sel1_mode = 1 - sel1_mode;
			} else if (event.button.button == 3) {
				sel2_mode = 1 - sel2_mode;
			} else if (event.button.button == 4) {
				if (sel1_mode == 0) {
					if (set_sel2 > 0) {
						set_sel2--;
					}
				} else {
					if (set_sel > 0) {
						set_sel--;
					}
				}
			} else if (event.button.button == 5) {
				if (sel1_mode == 0) {
					set_sel2++;
				} else {
					set_sel++;
				}
			} else if (event.button.button == 6) {
				if (sel2_mode == 0) {
					MavLinkVars[selMavLinkVars[(int)sel].id].value -= 0.1;
				} else {
					MavLinkVars[selMavLinkVars[(int)sel].id].value -= 1.0;
				}
			} else if (event.button.button == 7) {
				if (sel2_mode == 0) {
					MavLinkVars[selMavLinkVars[(int)sel].id].value += 0.1;
				} else {
					MavLinkVars[selMavLinkVars[(int)sel].id].value += 1.0;
				}
			} else {
				printf("Button: %i\n", event.button.button);
			}
		}
		redraw_flag = 1;
	}
}

int telemetrie_thread (void *data) {
	while (gui_running == 1) {
		mavlink_update();
		mwi21_update();
		jeti_update();
		SDL_Delay(1);
	}
	printf("** exit thread telemetrie\n");
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
			int diff_x = calibration_max_x - calibration_min_x;
			int diff_y = calibration_max_y - calibration_min_y;
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
							if (calibration_mode == 1 || calibration_mode == 3) {
								calibration_max_x = (int)ev[i].value;
							} else if (calibration_mode == 2 || calibration_mode == 4) {
								calibration_min_x = (int)ev[i].value;
							}
							diff_x = calibration_max_x - calibration_min_x;
							last_x = screen_w - ((int)ev[i].value - calibration_min_x) * (screen_w - 120) / diff_x - 60;
							if (touch == 0) {
								user_event.type=SDL_MOUSEMOTION;
								user_event.button.x = last_x;
								user_event.button.y = last_y;
								SDL_PushEvent(&user_event);
							}
							touch_x = 1;
						} else if (ev[i].code == 1) {
							if (calibration_mode == 1 || calibration_mode == 2) {
								calibration_max_y = (int)ev[i].value;
							} else if (calibration_mode == 3 || calibration_mode == 4) {
								calibration_min_y = (int)ev[i].value;
							}
							diff_y = calibration_max_y - calibration_min_y;
							last_y = screen_h - ((int)ev[i].value - calibration_min_y) * (screen_h - 120) / diff_y - 60;
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
							if (calibration_mode > 0) {
								calibration_mode++;
								if (calibration_mode > 5) {
									calibration_mode = 0;
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
//						printf("%i,%i\n", last_x, last_y);
					}
				}
			}
		}
	}
#endif
	printf("** exit thread touchscreen\n");
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


void Draw (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif

#ifdef RPI_NO_X
	static uint16_t timer = 0;
	timer++;
#else
	uint16_t timer = times(0);
#endif

	if (ModelData.heartbeat != 0) {
		connection_found = 1;
	}

	// set RTL-Waypoints to HOME-Position
	if (view_mode != VIEW_MODE_WPEDIT) {
		uint16_t n = 0;
		for (n = 0; n < MAX_WAYPOINTS; n++) {
			if (WayPoints[n].p_lat != 0.0 && strcmp(WayPoints[n].command, "RTL") == 0) {
				WayPoints[n].p_lat = WayPoints[0].p_lat;
				WayPoints[n].p_long = WayPoints[0].p_long;
				WayPoints[n].p_alt = WayPoints[0].p_alt;
			}
			if (WayPoints[n].p_lat != 0.0 && n > 0 && strcmp(WayPoints[n].command, "LAND") == 0) {
				WayPoints[n].p_lat = WayPoints[n - 1].p_lat;
				WayPoints[n].p_long = WayPoints[n - 1].p_long;
				WayPoints[n].p_alt = WayPoints[n - 1].p_alt;
			}
			if (WayPoints[n].p_lat != 0.0 && n > 0 && strcmp(WayPoints[n].command, "TAKEOFF") == 0) {
				WayPoints[n].p_lat = WayPoints[0].p_lat;
				WayPoints[n].p_long = WayPoints[0].p_long;
				WayPoints[n].p_alt = WayPoints[0].p_alt;
			}
		}
	}

	// Log Model-Position
	static float last_lat = 0.0;
	static float last_lon = 0.0;
	static float last_alt = 0.0;
	if (last_lat != ModelData.p_lat || last_lon != ModelData.p_long || last_alt != ModelData.p_alt) {
		char line[100];
		sprintf(line, "GPS;%i;%f;%f;%0.1f;%0.1f", (int)time(0), ModelData.p_lat, ModelData.p_long, ModelData.p_alt, (float)ModelData.speed);
		LogAppend(line);
		last_lat = ModelData.p_lat;
		last_lon = ModelData.p_long;
		last_alt = ModelData.p_alt;
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
	} else if (strcmp(keyboard_key, "[+]") == 0) {
		key_pressed |= (1<<4);
	} else if (strcmp(keyboard_key, "[-]") == 0) {
		key_pressed |= (1<<5);
	} else if (strcmp(keyboard_key, "h") == 0) {
		int tile_y = lat2tiley(WayPoints[0].p_lat, zoom) - 1;
		int tile_x = long2tilex(WayPoints[0].p_long, zoom) - 1;
		lat = tiley2lat(tile_y, zoom);
		lon = tilex2long(tile_x, zoom);
	} else if (strcmp(keyboard_key, "u") == 0) {
		int tile_y = lat2tiley(ModelData.p_lat, zoom) - 1;
		int tile_x = long2tilex(ModelData.p_long, zoom) - 1;
		lat = tiley2lat(tile_y, zoom);
		lon = tilex2long(tile_x, zoom);
	} else if (strcmp(keyboard_key, "t") == 0) {
		if (map_type < 2) {
			map_type++;
		} else {
			map_type = 0;
		}
	} else if (strcmp(keyboard_key, "tab") == 0) {
		view_mode_next = view_mode + 1;
		if (view_mode_next > VIEW_MODE_LAST - 1) {
			view_mode_next = 0;
		}
		trans_count = 1.0;
		setup_save();
	} else if (strcmp(keyboard_key, "s") == 0) {
		if (view_mode == VIEW_MODE_FMS || view_mode == VIEW_MODE_MAP) {
			send_waypoints();
		}
	} else if (strcmp(keyboard_key, "r") == 0) {
		if (view_mode == VIEW_MODE_FMS || view_mode == VIEW_MODE_MAP) {
			read_waypoints();
		}
	} else if (strcmp(keyboard_key, "print screen") == 0) {
#ifdef SDLGL
		save_screenshot();
#endif
	}

	keyboard_key[0] = 0;
	while(SDL_PollEvent(&event)) {
		check_events(esContext, event);
	}
	if (key_pressed & (1<<0)) {
		ModelData.yaw++;
		if (ModelData.yaw >= 360.0) {
			ModelData.yaw = 0.0;
		}
		redraw_flag = 1;
	}
	if (key_pressed & (1<<1)) {
		ModelData.yaw--;
		if (ModelData.yaw < 0.0) {
			ModelData.yaw = 359.0;
		}
		redraw_flag = 1;
	}
	if (key_pressed & (1<<2)) {
		float nx1 = 0.0;
		float ny1 = 0.0;
		next_point(ModelData.p_lat, ModelData.p_long, ModelData.yaw + 180.0, 0.00016, &nx1, &ny1);
		ModelData.p_lat = nx1;
		ModelData.p_long = ny1;
		int16_t zz = get_altitude(ModelData.p_lat, ModelData.p_long);
		if (ModelData.p_alt < zz + 10) {
			ModelData.p_alt = zz + 10;
		}
		redraw_flag = 1;
	}
	if (key_pressed & (1<<3)) {
		float nx1 = 0.0;
		float ny1 = 0.0;
		next_point(ModelData.p_lat, ModelData.p_long, ModelData.yaw, 0.00016, &nx1, &ny1);
		ModelData.p_lat = nx1;
		ModelData.p_long = ny1;
		int16_t zz = get_altitude(ModelData.p_lat, ModelData.p_long);
		if (ModelData.p_alt < zz + 10) {
			ModelData.p_alt = zz + 10;
		}
		redraw_flag = 1;
	}
	if (key_pressed & (1<<4)) {
		ModelData.p_alt++;
		redraw_flag = 1;
	}
	if (key_pressed & (1<<5)) {
		ModelData.p_alt--;
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
	if (timer - heartbeat_timer > 20 || timer < heartbeat_timer) {
		if (ModelData.heartbeat > 10) {
			ModelData.heartbeat -= 10;
		} else {
			ModelData.heartbeat = 0;
		}
		heartbeat_timer = timer;
		redraw_flag = 1;
	}
	if (ModelData.found_rc == 1 && (timer - heartbeat_rc_timer > 20 || timer < heartbeat_rc_timer)) {
		if (ModelData.heartbeat_rc > 20) {
			ModelData.heartbeat_rc -= 20;
		} else {
			ModelData.heartbeat_rc = 0;
			ModelData.rssi_rx = 0;
			ModelData.rssi_tx = 0;
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
	if (speak == 1) {
		static uint8_t speak = 0;
		if (timer - speak_timer > 200 || timer < speak_timer) {
			speak += 5;
			speak_timer = timer;
		}
		if (speak > 20) {
			speak = 0;
			if (ModelData.found_rc == 1 && ModelData.heartbeat_rc == 0) {
				system("#espeak -v en \"lost rc\" > /dev/null 2> /dev/null &");
			} else 	if (ModelData.heartbeat == 0 && connection_found == 1) {
				system("#espeak -v en \"lost heartbeat\" > /dev/null 2> /dev/null &");
			} else 	if (ModelData.voltage < volt_min) {
				system("#espeak -v en \"low battery\" > /dev/null 2> /dev/null &");
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


#ifndef SDLGL
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	esMatrixLoadIdentity( &modelview );
	esMatrixMultiply( &userData->mvpMatrix, &modelview, &userData->perspective);
#else
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif

	if (view_mode_last != view_mode) {
		view_mode_last = view_mode;
		reset_buttons();
	}

#ifdef RPI_NO_X
	if (calibration_mode > 0) {
		screen_calibration(esContext);
#ifndef SDLGL
		eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
#else
		SDL_GL_SwapBuffers();
		SDL_Delay(20);
#endif
		return;
	}
#endif

#ifdef SDLGL
	if (trans_count > 0.0) {
		trans_count += 10.0;
		if (trans_count < 90.0) {
			transition_rotate_begin(esContext, trans_count);
		} else if (trans_count < 180.0) {
			view_mode = view_mode_next;
			transition_rotate_begin(esContext, trans_count + 180);
		} else {
			trans_count = 0.0;
		}
	}
#else
	view_mode = view_mode_next;
#endif


	if (view_mode == VIEW_MODE_HUD) {
		screen_hud(esContext);
	} else if (view_mode == VIEW_MODE_TELEMETRY) {
		screen_background(esContext);
		screen_telemetry(esContext);
	} else if (view_mode == VIEW_MODE_MODEL) {
		screen_background(esContext);
		screen_model(esContext);
	} else if (view_mode == VIEW_MODE_RCFLOW) {
//		screen_background(esContext);
		screen_rcflow(esContext);
	} else if (view_mode == VIEW_MODE_FMS) {
		screen_fms(esContext);
	} else if (view_mode == VIEW_MODE_WPEDIT) {
		if (wpedit_last_mode == VIEW_MODE_MAP) {
			screen_map(esContext, lat, lon, zoom);
			draw_box_f3(esContext, -1.5, -1.0, 0.002, 1.5, 1.0, 0.002, 0, 0, 0, 200);
		}
		screen_wpedit(esContext);
	} else if (view_mode == VIEW_MODE_MAP) {
		if (map_view == 3) {
			map_view = 0;
		}
		screen_map(esContext, lat, lon, zoom);
	} else if (view_mode == VIEW_MODE_VIDEOLIST) {
		screen_background(esContext);
		screen_videolist(esContext);
	} else if (view_mode == VIEW_MODE_SYSTEM) {
		screen_background(esContext);
		screen_system(esContext);
	} else if (view_mode == VIEW_MODE_TCL) {
//		screen_background(esContext);
		screen_tcl(esContext);
	} else if (view_mode == VIEW_MODE_FCMENU) {
		screen_background(esContext);
		if (ModelData.teletype == TELETYPE_MULTIWII_21) {
			screen_mwi_menu(esContext);
		} else if (ModelData.teletype == TELETYPE_BASEFLIGHT) {
			screen_mwi_menu(esContext);
		} else if (ModelData.teletype == TELETYPE_GPS_NMEA) {
			screen_graph(esContext);
		} else if (ModelData.teletype == TELETYPE_OPENPILOT) {
			screen_openpilot(esContext);
		} else {
			screen_mavlink_menu(esContext);
		}
	}

#ifdef SDLGL
	if (trans_count > 0.0) {
		if (trans_count < 90.0) {
			transition_rotate_end(esContext, trans_count);
		} else if (trans_count < 180.0) {
			view_mode = view_mode_next;
			transition_rotate_end(esContext, trans_count + 180);
		} else {
			trans_count = 0.0;
		}
	}
#endif

#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	glDisable( GL_DEPTH_TEST );
	// Mark Map-Edges
/*
	if (map_mark == 1) {
		draw_box(esContext, 60, 0, esContext->width - 120, 60, 255, 255, 255, 64);
	} else if (map_mark == 2) {
		draw_box(esContext, 60, esContext->height - 60, esContext->width - 80, esContext->height, 255, 255, 255, 64);
	} else if (map_mark == 3) {
		draw_box(esContext, 0, 60, 60, esContext->height - 120, 255, 255, 255, 64);
	} else if (map_mark == 4) {
		draw_box(esContext, esContext->width - 60, 60, esContext->width, esContext->height - 120, 255, 255, 255, 64);
	}
*/
	draw_circleFilled_f3(esContext, 1.25, 0.92, 0.01, (float)ModelData.heartbeat / 4000.0, 255, 0, 0, ModelData.heartbeat * 2);
	if (ModelData.found_rc == 1) {
		draw_circleFilled_f3(esContext, 1.25, 0.87, 0.01, (float)ModelData.heartbeat_rc / 4000.0, 0, 0, 255, ModelData.heartbeat_rc * 2);
	}
	if (contrast == 1) {
		draw_text_f3(esContext, -1.4, -0.95, 0.003, 0.06, 0.06, FONT_WHITE, "<<");
		draw_text_f3(esContext, 1.3, -0.95, 0.003, 0.06, 0.06, FONT_WHITE, ">>");
	} else {
		draw_text_f3(esContext, -1.4, -0.95, 0.003, 0.06, 0.06, FONT_GREEN_BG, "<<");
		draw_text_f3(esContext, 1.3, -0.95, 0.003, 0.06, 0.06, FONT_GREEN_BG, ">>");
	}
	if (message > 0) {
		draw_text_f(esContext, 0.0 - strlen(message_txt) * 0.04 * 0.6 / 2 - 0.012, -0.98, 0.04, 0.04, FONT_BLACK_BG, message_txt);
	}
	if (blink > 128) {
		if (ModelData.found_rc == 1 && ModelData.heartbeat_rc == 0) {
			draw_text_f(esContext, 1.2 - strlen("LOST_RC") * 0.06 * 0.6, 0.9, 0.06, 0.06, FONT_PINK, "LOST_RC");
		} else if (ModelData.heartbeat == 0 && connection_found == 1) {
			draw_text_f(esContext, 1.2 - strlen("LOST_CON") * 0.06 * 0.6, 0.9, 0.06, 0.06, FONT_PINK, "LOST_CON");
		} else if (ModelData.voltage > 1.0 && ModelData.voltage < volt_min) {
			draw_text_f(esContext, 1.2 - strlen("LOW_BAT") * 0.06 * 0.6, 0.9, 0.06, 0.06, FONT_PINK, "LOW_BAT");
		}
	}
	// Speaker
	if (speak == 1) {
		draw_image(esContext, esContext->width - 40, esContext->height - 40, 16, 16, TEXTURE_SPEAKER);
	} else {
		draw_image(esContext, esContext->width - 40, esContext->height - 40, 16, 16, TEXTURE_SPEAKER_MUTE);
	}
	// Mouse-Pointer
	draw_pointer(esContext, mouse_x, mouse_y, 16, 16, TEXTURE_POINTER);
	glEnable( GL_DEPTH_TEST );

#ifndef SDLGL
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
#else
	SDL_GL_SwapBuffers();
	SDL_Delay(15);
#endif
}

void ShutDown ( ESContext *esContext ) {
//	UserData *userData = esContext->userData;

	printf("Shutdown\n");
	printf("* exit threads\n");
	gui_running = 0;
	SDL_Delay(600);
	char file[200];
	sprintf(file, "%s/%i.log", BASE_DIR, startup_time);
	printf("* save log\n");
	LogSave(file);
	printf("* save setup\n");
	setup_save();
	printf("* stop telemetrie\n");
	stop_telemetrie();
	printf("* frsky exit\n");
	frsky_exit();
	printf("* jeti exit\n");
	jeti_exit();
	printf("* gcs_gps exit\n");
	gcs_gps_exit();

	printf("* map exit\n");
	map_exit();
	printf("* telemetry-thread kill\n");
	SDL_KillThread(thread_telemetrie);
#ifdef RPI_NO_X
	printf("* touch-thread kill\n");
	SDL_KillThread(thread);
#endif

#ifdef SDLGL
	printf("* video exit\n");
	videodev_stop();
#endif
	system("killall -9 espeak 2> /dev/nnull > /dev/nnull");

	printf("* clear texture-cache\n");
	int16_t n = 0;
	for (n = 0; n < MAX_TEXCACHE; n++) {
		if (TexCache[n].name[0] != 0 && TexCache[n].texture != 0 ) {
			glDeleteTextures( 1, &TexCache[n].texture );
			TexCache[n].name[0] = 0;
		}
	}

#ifdef RPI_NO_X
//	glDeleteProgram ( userData->programObject );
//	free(esContext->userData);
	printf("* exit bcm_host\n");
	bcm_host_deinit();
#endif
	printf("* exit SDL\n");
	SDL_Quit();

#ifdef SDLGL
	glExit(esContext);
#endif

	printf("* remove tempfile\n");
	system("rm -rf /tmp/gcs.run");
	printf("done\n");
}


ESContext *GlobalesContext = NULL;

int main ( int argc, char *argv[] ) {
	char tmp_name[201];
	ESContext esContext;
#ifndef SDLGL
	UserData userData;
#endif

	time_t liczba_sekund;
	struct tm strukt;
	time(&liczba_sekund);
	localtime_r(&liczba_sekund, &strukt); 
	printf("DATE: %d.%d %d\n", strukt.tm_mday, strukt.tm_mon+1, strukt.tm_year + 1900); 

	sprintf(tmp_name, "%s/MAPS/WMM2010.COF", BASE_DIR);
	init_declination(tmp_name, strukt.tm_year + 1900, strukt.tm_mon+1, strukt.tm_mday);

	uint16_t n = 0;
	for (n = 0; n < MAX_TEXCACHE; n++) {
		TexCache[n].name[0] = 0;
		TexCache[n].texture = 0;
	}

	startup_time = time(0);
	touchscreen_device[0] = 0;

	keyboard_key[0] = 0;

	LogInit("startup");

        FILE *fr;
        char line[201];
	fr = fopen ("test.log", "r");
	if (fr != 0) {
	        while(fgets(line, 200, fr) != NULL) {
			if (strlen(line) > 0) {
				line[strlen(line) - 1] = 0;
			}
			LogAppend(line);
		}
	        fclose(fr);
	} else {
		printf("Can not load log-file: %s\n", "test.log");
	}

	setup_waypoints();
	setup_load();

	strcpy(tmp_name, ModelData.name);


#ifdef RPI_NO_X
	if ((touch_fd = open(touchscreen_device, O_RDONLY)) >= 0) {
		thread = SDL_CreateThread(touchscreen_thread, NULL);
		if ( thread == NULL ) {
			fprintf(stderr, "Thread konnte nicht gestartet werden: %s\n", SDL_GetError());
			return 0;
		}
	} else {
		calibration_mode = 0;
	}
#endif

	frsky_exit();
	frsky_init(frsky_port, frsky_baud);
	jeti_exit();
	jeti_init(jeti_port, jeti_baud);
	gcs_gps_exit();
	gcs_gps_init(gcs_gps_port, gcs_gps_baud);

	printf("Init GL\n");
#ifndef SDLGL
	esInitContext ( &esContext );
	esContext.userData = &userData;

	printf("Init GL#1\n");

	esCreateWindow ( &esContext, "GL-GCS", screen_w, screen_h, ES_WINDOW_RGB );

	printf("Init GL#1b\n");

	if (! glesInit(&esContext)) {

	printf("Init GL#err\n");

		return 0;
	}

	printf("Init GL#2\n");

	esRegisterDrawFunc(&esContext, Draw);

	printf("Init GL#3\n");


	glClearDepthf( 2.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glClearColor(0.0, 0.0, 0.0, 1.0);
#else
	glInit(&esContext);
	videodev_start();
#endif
	SDL_ShowCursor(0);

	printf( "Vendor     : %s\n", glGetString( GL_VENDOR ) );
	printf( "Renderer   : %s\n", glGetString( GL_RENDERER ) );
	printf( "Version    : %s\n", glGetString( GL_VERSION ) );
//	printf( "Extensions : %s\n", glGetString( GL_EXTENSIONS ) );
	printf("\n");

	// preload map on startup for faster view-changes
	printf("PreLoading Maps...\n");
	draw_text_f3(&esContext, -1.4, -0.95, 0.003, 0.06, 0.06, FONT_WHITE, "PreLoading Maps...");
#ifndef SDLGL
	eglSwapBuffers(&esContext.eglDisplay, &esContext.eglSurface);
#else
	SDL_GL_SwapBuffers();
	SDL_Delay(20);
#endif

	screen_map(&esContext, lat, lon, zoom);
	int16_t zz = get_altitude(ModelData.p_lat, ModelData.p_long);
	if (ModelData.p_alt < zz + 10) {
		ModelData.p_alt = zz + 10;
	}

	printf("Init Telemetry-Thread\n");
	reset_telemetrie();
	thread_telemetrie = SDL_CreateThread(telemetrie_thread, NULL);
	if ( thread_telemetrie == NULL ) {
		fprintf(stderr, "Telemetrie-Thread konnte nicht gestartet werden: %s\n", SDL_GetError());
		return 0;
	}

GlobalesContext = &esContext;

	printf("Mainloop\n");
#ifndef SDLGL
	esMainLoop(&esContext);
#else
	while (gui_running == 1) {
		Draw(&esContext);
	}
#endif

	ShutDown(&esContext);

	return 0;
}




