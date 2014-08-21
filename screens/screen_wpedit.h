

extern uint16_t wpedit_pos;
extern uint16_t wpedit_sel;
extern uint8_t wpedit_last_mode;

uint8_t read_wp (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t write_wp (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_waypoint_edit (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_back (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_waypoint_lat_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_waypoint_lon_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_waypoint_alt_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_waypoint_yaw_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_waypoint_wait_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_waypoint_orbit_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_waypoint_radius_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t wpedit_waypoint_type_select (char *name, float x, float y, int8_t button, float data, uint8_t action);
void screen_wpedit (ESContext *esContext);

