
enum {
	MAP_NAME,
	MAP_URL,
	MAP_URL2,
	MAP_FILE,
	MAP_TYPE,
	MAP_COMMENT,
	MAP_COPYRIGHT,
};


#ifndef SDLGL
#define MAP_OVERLAY	1
#else
#define MAP_OVERLAY	2
#endif

extern volatile float lat;
extern volatile float lon;
extern volatile uint8_t zoom;
extern uint16_t map_w;
extern uint16_t map_h;
extern uint8_t map_type;
extern uint8_t map_view;
extern uint8_t uav_active_waypoint;
extern char mapnames[20][7][1024];
extern char omapnames[20][7][1024];
extern uint8_t map_type;
extern uint8_t map_type_select;
extern uint8_t omap_type;
extern uint8_t omap_type_select;
extern uint8_t map_sethome;

extern size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
extern uint8_t map_3d (char *name, float x, float y, int8_t button, float data, uint8_t action);
extern uint8_t change_maptype (char *name, float x, float y, int8_t button, float data, uint8_t action);
extern uint8_t map_zoom (char *name, float x, float y, int8_t button, float data, uint8_t action);
extern uint8_t map_goto (char *name, float x, float y, int8_t button, float data, uint8_t action);
extern uint8_t map_addmode_change (char *name, float x, float y, int8_t button, float data, uint8_t action);
extern uint8_t map_del (char *name, float x, float y, int8_t button, float data, uint8_t action);
extern uint8_t show_wp (char *name, float x, float y, int8_t button, float data, uint8_t action);
extern int file_download (char *fileName, char *url);
extern int file_exists (char *fileName);
extern int long2tilex(float lon, int z) ; 
extern int lat2tiley(float lat, int z); 
extern float tilex2long(int x, int z);
extern float tiley2lat(int y, int z);
extern float y2lat (int y, float lat, float zoom);
extern float x2long (int x, float lon, float zoom);
extern int lat2y (float mark_lat, float lat, float zoom);
extern int long2x (float mark_long, float lon, float zoom);
extern float offset_x1;
extern float offset_y1;
extern uint8_t map_addmode;
extern uint8_t map_poimode;
extern uint8_t map_poly_addmode;
extern uint8_t map_setpos;
extern uint8_t center_map;
extern uint8_t maplen;
extern uint8_t omaplen;

void get_dir (float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to, float *heading, float *dist1, float *angle_up, float *dist2);
void show_dir(ESContext *esContext, uint16_t px, uint16_t py, float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to);
void winkel_line (ESContext *esContext, float x_origin, float y_origin, float winkel, float r1, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float *nx1, float *ny1);
void show_dir_f(ESContext *esContext, float x1, float y1, float zoom, float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float *nx1, float *ny1, float *dist);
void show_dir_ll(ESContext *esContext, float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to);
void mark_route (ESContext *esContext, float last_lat, float last_long, float last_alt, float mark_lat, float mark_long, float mark_alt, int8_t type, float lat, float lon, uint8_t zoom);
void mark_point (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, char *text, char *command, uint8_t type, float radius, float orbit, float lat, float lon, uint8_t zoom);
void screen_map (ESContext *esContext, float lat, float lon, uint8_t zoom);
void display_map (ESContext *esContext, float lat, float lon, uint8_t zoom, uint8_t map_view, uint8_t draw_tiles, float alpha0, float alpha1, float alpha2, float grid);
void map_exit (void);
