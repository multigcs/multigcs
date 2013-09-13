
enum {
	TRACKER_PAN_ANGLE_MIN,
	TRACKER_PAN_ANGLE_MAX,
	TRACKER_PAN_PULSE_MIN,
	TRACKER_PAN_PULSE_MAX,
	TRACKER_PAN_TRIM,
	TRACKER_PITCH_ANGLE_MIN,
	TRACKER_PITCH_ANGLE_MAX,
	TRACKER_PITCH_PULSE_MIN,
	TRACKER_PITCH_PULSE_MAX,
	TRACKER_PITCH_TRIM,
	TRACKER_MAX,
};

typedef struct {
	char name[200];
	float min;
	float max;
	float value;
} Tracker;

extern Tracker TrackerData[TRACKER_MAX];

extern float tracker_lat;
extern float tracker_long;
extern float tracker_alt;
extern float tracker_pan_dir;
extern float tracker_pan_dir_trimmed;
extern float tracker_pitch_dir;
extern float tracker_pitch_dir_trimmed;

void tracker_set_home (void);
int thread_serial_tracker (void *unused);
void tracker_mode (uint8_t new_mode);
uint8_t tracker_mode_get (void);
uint8_t tracker_init (char *port, uint32_t baud);
void tracker_exit (void);
uint8_t tracker_connection_status (void);
extern void tracker_setup_load(void);
extern void tracker_setup_save(void);
extern void tracker_setup_defaults (void);
