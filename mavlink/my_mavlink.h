
#include "GCS_MAVLink/include/mavlink/v1.0/ardupilotmega/mavlink.h"


#define PI 3.14159265
#define toDeg(x) (x*180.0)/PI
#define toRad(x) (PI/180.0) * x

#define MODE_MANUEL 0
#define MODE_RTL 1
#define MODE_POSHOLD 2
#define MODE_MISSION 3
#define MODE_FAILSAVE 4
#define MODE_SETHOME 5

#define MAVLINK_PARAMETER_MAX 500


#define MAV_DATA_STREAM_POSITION_ACTIVE 1
#define MAV_DATA_STREAM_RAW_SENSORS_ACTIVE 1
#define MAV_DATA_STREAM_EXTENDED_STATUS_ACTIVE 1
#define MAV_DATA_STREAM_RAW_CONTROLLER_ACTIVE 1
#define MAV_DATA_STREAM_EXTRA1_ACTIVE 1
#define MAV_DATA_STREAM_EXTRA2_ACTIVE 1 // HUD-
#define MAV_DATA_STREAM_EXTRA3_ACTIVE 1
#define MAV_DATA_STREAM_RC_CHANNELS_ACTIVE 1

#define MAV_DATA_STREAM_POSITION_RATE 5 // in Hz
#define MAV_DATA_STREAM_RAW_SENSORS_RATE 5
#define MAV_DATA_STREAM_EXTENDED_STATUS_RATE 1
#define MAV_DATA_STREAM_RAW_CONTROLLER_RATE 1
#define MAV_DATA_STREAM_EXTRA1_RATE 25
#define MAV_DATA_STREAM_EXTRA2_RATE 2
#define MAV_DATA_STREAM_EXTRA3_RATE 2
#define MAV_DATA_STREAM_RC_CHANNELS_RATE 1

enum MAV_VAR
{
	MAV_VAR_FLOAT=0, /* 32 bit float | */
	MAV_VAR_UINT8=1, /* 8 bit unsigned integer | */
	MAV_VAR_INT8=2, /* 8 bit signed integer | */
	MAV_VAR_UINT16=3, /* 16 bit unsigned integer | */
	MAV_VAR_INT16=4, /* 16 bit signed integer | */
	MAV_VAR_UINT32=5, /* 32 bit unsigned integer | */
	MAV_VAR_INT32=6, /* 32 bit signed integer | */
	MAV_VAR_ENUM_END=7, /*  | */
};


typedef struct {
	int16_t id;
	char name[100];
	char display[100];
	char desc[1024];
	char values[1024];
	char bits[1024];
	char group[20];
	float value;
	float onload;
	float min;
	float max;
	int8_t type;
	uint16_t option1;
	uint16_t option2;
} ValueList;


extern int16_t mission_max;
extern int serial_fd_mavlink;
extern ValueList MavLinkVars[MAVLINK_PARAMETER_MAX];
extern uint8_t droneType;
extern uint8_t autoPilot;
extern int c;
extern int res;
extern char serial_buf[255];
extern uint16_t mavlink_timeout;
extern uint16_t mavlink_maxparam;
extern uint8_t mavlink_update_yaw;

uint8_t mavlink_init (char *port, uint32_t baud);
void mavlink_exit (void);
void mavlink_update (void);
uint8_t mavlink_connection_status (void);
void mavlink_xml_save (FILE *fr);
void mavlink_xml_load (xmlDocPtr doc, xmlNodePtr cur);

void mavlink_web_get (char *url, char *content, char *type);

void mavlink_read_waypoints (void);
void mavlink_send_waypoints (void);

void mavlink_param_xml_meta_load (void);
void mavlink_stop_feeds (void);
void mavlink_send_value (char *name, float val, int8_t type);
void mavlink_set_value (char *name, float val, int8_t type, int16_t id);
void mavlink_handleMessage(mavlink_message_t* msg);
void mavlink_save_to_flash (void);
void mavlink_load_from_flash (void);
void mavlink_send_waypoints (void);
void mavlink_send_message (mavlink_message_t* msg);
void mavlink_param_get_id (uint16_t id);
void mavlink_start_feeds (void);
int mavlink_udp (void *data);

void mavlink_send_cmd_rtl (void);
void mavlink_send_cmd_mission (void);
void mavlink_send_cmd_arm (uint8_t mode);
void mavlink_send_cmd_rtl (void);
void mavlink_send_cmd_land (void);
void mavlink_send_cmd_takeoff (void);
void mavlink_send_cmd_mode (uint8_t mode);
void mavlink_send_cmd_loiter (void);
void mavlink_send_cmd_guided (void);
void mavlink_send_cmd_calibration (void);
void mavlink_send_cmd_calibration_ack (void);
void mavlink_send_cmd_follow (float p_lat, float p_long, float p_alt, float radius);


