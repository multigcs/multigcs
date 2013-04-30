#ifndef MAIN_H
#define MAIN_H

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_events.h>

#ifndef SDLGL
#include "gles_draw.h"
#else
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include "gl_draw.h"
#endif
#include "draw.h"

#define SCREEN_W 1024
#define SCREEN_H 720

#define PI 3.14159265

#define FONT_GREEN_BG BASE_DIR"/fonts/font1.png"
#define FONT_TRANS BASE_DIR"/fonts/font2.png"
#define FONT_BLACK_BG BASE_DIR"/fonts/font3.png"
#define FONT_WHITE BASE_DIR"/fonts/font4.png"
#define FONT_GREEN BASE_DIR"/fonts/font5.png"
#define FONT_PINK BASE_DIR"/fonts/font6.png"

#define TEXTURE_LOGO BASE_DIR"/textures/autoquad-logo.png"
#define TEXTURE_QUAD BASE_DIR"/textures/autoquad-quad.png"
#define TEXTURE_HUD_FRAME BASE_DIR"/textures/hud_frame.png"
#define TEXTURE_POINTER BASE_DIR"/textures/pointer.png"
#define TEXTURE_SPEAKER BASE_DIR"/textures/speaker.png"
#define TEXTURE_SPEAKER_MUTE BASE_DIR"/textures/speaker_mute.png"

#define ALIGN_LEFT	0
#define ALIGN_TOP	0
#define ALIGN_CENTER	1
#define ALIGN_RIGHT	2
#define ALIGN_BOTTOM	2

enum {
	VIEW_MODE_HUD,
	VIEW_MODE_TELEMETRY,
	VIEW_MODE_MAP,
	VIEW_MODE_FMS,
	VIEW_MODE_ND,
	VIEW_MODE_MODEL,
	VIEW_MODE_RCFLOW,
	VIEW_MODE_FCMENU,
	VIEW_MODE_VIDEOLIST,
	VIEW_MODE_TCL,
	VIEW_MODE_SYSTEM,
	VIEW_MODE_LAST,
	VIEW_MODE_WPEDIT,
};

#define MAX_WAYPOINTS 250
typedef struct {
	float p_lat;
	float p_long;
	float p_alt;
	float yaw;
	float radius;
	float wait;
	float orbit;
	char name[128];
	char command[128];
	uint8_t type;
} WayPoint;

enum {
	BUTTON_RELEASE,
	BUTTON_PRESS,
	BUTTON_MOVE,
};

#define MAX_BUTTONS 500
typedef struct {
	char name[100];
	uint8_t view_mode;
	float x1;
	float y1;
	float x2;
	float y2;
	float data;
	uint8_t type;
	uint8_t status;
	float start_x;
	float start_y;
	uint8_t (*callback) (char *, float, float, int8_t, float);
} Button;

struct list_element {
	char *line;
	struct list_element *next;
};

extern struct list_element *LogLines;
extern struct list_element *LogLinesEnd;

extern float volt_min;
extern int8_t speak;
extern uint8_t fullscreen;
extern uint16_t heartbeat_timer;
extern uint16_t blink_timer;
extern uint16_t speak_timer;
extern uint16_t msg_timer;
extern uint8_t map_mark;
extern uint8_t redraw_flag;
extern uint16_t mouse_x;
extern uint16_t mouse_y;
extern char gcs_gps_port[1024];
extern uint32_t gcs_gps_baud;
extern char telemetrie_port[1024];
extern uint32_t telemetrie_baud;
extern char jeti_port[1024];
extern uint32_t jeti_baud;
extern char frsky_port[1024];
extern uint32_t frsky_baud;
extern uint8_t message;
extern char message_txt[1024];
extern WayPoint WayPoints[MAX_WAYPOINTS];
extern int8_t waypoint_active;
extern uint8_t view_mode;
extern uint8_t view_mode_next;
extern float trans_count;
extern Button Buttons[MAX_BUTTONS];
extern SDL_Event event;
extern char touchscreen_device[200];
extern uint8_t calibration_mode;
extern uint16_t calibration_timeout;
extern int calibration_min_x;
extern int calibration_max_x;
extern int size_x;
extern int last_x;
extern int calibration_min_y;
extern int calibration_max_y;
extern int size_y;
extern int last_y;
extern int touch_fd;
extern volatile uint8_t gui_running;
extern uint8_t hud_view;
extern uint8_t hud_view_map;
extern uint8_t hud_view_video;
extern uint8_t hud_view_tunnel;
extern uint8_t hud_view_mark;
extern float gcs_roll;
extern float gcs_pitch;
extern float gcs_yaw;
extern uint8_t contrast;
extern uint16_t screen_w;
extern uint16_t screen_h;
extern uint16_t screen_border_x;
extern uint16_t screen_border_y;
extern char keyboard_key[100];
extern uint8_t keyboard_shift;
extern uint8_t keyboard_altgr;

extern ESContext *GlobalesContext;

void LogAppend(char *line);
void LogSave(char *file);
void draw_text_f (ESContext *esContext, float x1, float y1, float w, float h, char *file, char *text);
void reset_telemetrie (void);
void stop_telemetrie (void);
void set_telemetrie (char *device, uint32_t baud);
uint8_t need_bluetooth (void);
void reset_buttons (void);
uint8_t set_button (char *name, uint8_t view_mode, float x1, float y1, float x2, float y2, uint8_t (*callback) (char *, float, float, int8_t, float), float data, uint8_t type);
int8_t check_button (uint8_t view_mode, float x, float y, uint8_t button, uint8_t event);
void setup_waypoints (void);
void sys_message (char *msg);
void setup_save (void);
void setup_load (void);
void check_events (ESContext *esContext, SDL_Event event);
int touchscreen (void *data);
void transition_rotate_begin (ESContext *esContext, float trans_count);
void transition_rotate_end (ESContext *esContext, float trans_count);
void ShutDown (ESContext *esContext);
void Draw (ESContext *esContext);
void next_point (float x_origin, float y_origin, float winkel, float r1, float *nx1, float *ny1);
void next_point_ll (ESContext *esContext, float x_origin, float y_origin, float winkel, float r1, float *nx1, float *ny1);

#endif

