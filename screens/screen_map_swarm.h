
typedef struct {
	uint8_t active;
	int8_t master;
	int8_t slave[9];
	uint8_t options;
	int8_t selected;
	int8_t yaw_mode;
	int8_t rotate;
	int16_t offset_x[9];
	int16_t offset_y[9];
	int16_t offset_z[9];
} Swarm;

extern Swarm SwarmSetup;


uint8_t swarm_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
void swarm_draw_setup (ESContext *esContext);
void latlong_offset (float *p_lat, float *p_long, float *p_alt, float lat_om, float long_om, float alt_om);

