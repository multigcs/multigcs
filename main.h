#ifndef MAIN_H
#define MAIN_H

#ifdef RPI_NO_X
#define SCREEN_W 1280
#define SCREEN_H 720
#else
#define SCREEN_W 1024
#define SCREEN_H 720
#endif

#define PI 3.14159265

#define DEG_TO_RAD (PI / 180.0)
#define RAD_TO_DEG (180.0 / PI)

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

#define TEXTURE_PLAYER_REW BASE_DIR"/textures/player_rew.png"
#define TEXTURE_PLAYER_STOP BASE_DIR"/textures/player_stop.png"
#define TEXTURE_PLAYER_PLAY BASE_DIR"/textures/player_play.png"
#define TEXTURE_PLAYER_PAUSE BASE_DIR"/textures/player_pause.png"
#define TEXTURE_PLAYER_FFW BASE_DIR"/textures/player_ffw.png"
#define TEXTURE_PLAYER_OPEN BASE_DIR"/textures/player_open.png"
#define TEXTURE_PLAYER_KML BASE_DIR"/textures/player_kml.png"

#define ALIGN_LEFT	0
#define ALIGN_TOP	0
#define ALIGN_CENTER	1
#define ALIGN_RIGHT	2
#define ALIGN_BOTTOM	2

#define BUTTON_PRESSED	0
#define BUTTON_MOVED	1
#define BUTTON_RELEASED	2

#define APRS_MAX	5000

extern uint8_t gui_ov_lock;

enum {
	VIEW_MODE_HUD,
	VIEW_MODE_TELEMETRY,
	VIEW_MODE_MAP,
	VIEW_MODE_FMS,
	VIEW_MODE_MODEL,
	VIEW_MODE_FCMENU,
	VIEW_MODE_RCFLOW,
#ifndef ANDROID
	VIEW_MODE_VIDEOLIST,
	VIEW_MODE_TCL,
#endif
	VIEW_MODE_TRACKER,
	VIEW_MODE_SYSTEM,
	VIEW_MODE_LAST,
	VIEW_MODE_WPEDIT,
};

char screennames[VIEW_MODE_LAST + 2][16];

#define MAX_WAYPOINTS 250
typedef struct {
	float p_lat;
	float p_long;
	float p_alt;
	float param1; // radius
	float param2; // wait
	float param3; // orbit
	float param4; // yaw
	char name[128];
	char command[128];
	uint8_t type;
	uint8_t frametype;
} WayPoint;

#define MAX_POLYPOINTS 250
typedef struct {
	float p_lat;
	float p_long;
} PolyPoint;

typedef struct {
	float p_lat;
	float p_long;
	float p_alt;
	uint8_t mode;
	uint8_t num;
} PolyPointNoFly;

enum {
	BUTTON_RELEASE,
	BUTTON_PRESS,
	BUTTON_MOVE,
};

#define MAX_BUTTONS 500
typedef struct {
	char name[200];
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
	uint8_t (*callback) (char *, float, float, int8_t, float, uint8_t);
} Button;

struct list_element {
	char *line;
	struct list_element *next;
};

typedef struct {
	char gcs_gps_port[1024];
	uint32_t gcs_gps_baud;
	char rcflow_port[1024];
	uint32_t rcflow_baud;
	char jeti_port[1024];
	uint32_t jeti_baud;
	char frsky_port[1024];
	uint32_t frsky_baud;
	char tracker_port[1024];
	uint32_t tracker_baud;
	int8_t waypoint_active;
	int8_t polypoint_active;
	int8_t polypointnf_active;
	uint8_t fullscreen;
	uint8_t borderless;
	uint8_t view_mode;
	uint8_t hud_view_screen;
	uint8_t hud_view_stab;
	uint8_t hud_view_map;
	uint8_t hud_view_video;
	uint8_t hud_view_tunnel;
	uint8_t hud_view_mark;
	uint8_t contrast;
	uint16_t screen_w;
	uint16_t screen_h;
	uint16_t screen_border_x;
	uint16_t screen_border_y;
	float keep_ratio;

	char touchscreen_device[200];
	uint8_t calibration_mode;
	int calibration_min_x;
	int calibration_max_x;
	int calibration_min_y;
	int calibration_max_y;

	int8_t speak;
	float volt_min;

	char opencv_file[1025];
	int opencv_device;
	int opencv_features;

	uint8_t qrcheck;

	char videocapture_device[1024];
	uint16_t videocapture_width;
	uint16_t videocapture_height;

	uint16_t webport;
	float gearth_interval;

	uint8_t weather_enable;

	char mavlink_tcp_server[128];
	int mavlink_tcp_port;
	int mavlink_udp_port;

	int mavlink_forward_udp_local_port;
	int mavlink_forward_udp_remote_port;
	char mavlink_forward_udp_remote_ip[128];

#if defined USE_APRS
	char aprs_server[128];
	int aprs_port;
	char aprs_filter[128];
	int aprs_enable;
#endif
} GcsSetup;

extern Button Buttons[MAX_BUTTONS + 1];
extern WayPoint WayPoints[MODELS_MAX][MAX_WAYPOINTS + 1];
extern PolyPoint PolyPoints[MAX_POLYPOINTS + 1];
extern PolyPointNoFly PolyPointsNoFly[MAX_POLYPOINTS + 1];
extern GcsSetup setup;

extern volatile uint8_t gui_running;
extern uint8_t redraw_flag;
extern int8_t waypoint_active;
extern int8_t polypoint_active;
extern uint8_t view_mode_next;
extern char keyboard_key[100];
extern uint8_t keyboard_shift;
extern uint8_t keyboard_altgr;
extern float gcs_roll;
extern float gcs_pitch;
extern float gcs_yaw;
extern uint8_t map_show_profile;
extern uint8_t map_dir;

//#define HTML_DRAWING

#ifdef HTML_DRAWING
#define HTML_MAX 1000000
#define X_CAL (1024 / 3) + (1024 / 2)
#define Y_CAL (720 / 2) + (720 / 2)
extern char display_html[HTML_MAX];
extern char display_html2[HTML_MAX];
#endif

extern char teletypes[16][16];
extern char dronetypes[MAV_TYPE_ENUM_END + 6][32];
extern char pilottypes[MAV_AUTOPILOT_ENUM_END][64];
extern char statetypes[MAV_STATE_ENUM_END][16];

extern ESContext *GlobalesContext;

void draw_text_f (ESContext *esContext, float x1, float y1, float w, float h, char *file, char *text);
void reset_telemetry (uint8_t modelid);
void stop_telemetry (uint8_t modelid);
void set_telemetry (uint8_t modelid, char *device, uint32_t baud);
uint8_t need_bluetooth (void);
void reset_buttons (void);
uint8_t set_button (char *name, uint8_t view_mode, float x1, float y1, float x2, float y2, uint8_t (*callback) (char *, float, float, int8_t, float, uint8_t), float data, uint8_t type);
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

#ifdef SDL2
extern SDL_Window *MainWindow;
#endif

char *get_datadirectory (void);
