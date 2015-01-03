
#define MAX_POIS 100

typedef struct {
	float p_lat;
	float p_long;
	char name[128];
	uint8_t type;
} PointOfInterest;

typedef struct {
	ESContext *esContext;
	float lat;
	float lon;
	uint8_t zoom;
	uint8_t map_view;
	uint8_t draw_tiles;
	float alpha0;
	float alpha1;
	float alpha2;
	float grid;
	float offset_x1;
	float offset_y1;
	uint8_t map_color;
	uint8_t mapthread_running;
	SDL_Thread *sdl_thread_get_maps1;
	SDL_Thread *sdl_thread_get_maps2;
} GeoMap;

extern GeoMap *mapdata;
extern uint8_t maplen;
extern uint8_t omaplen;
extern char mapnames[20][7][512];
extern char omapnames[20][7][512];
extern PointOfInterest POIs[MAX_POIS];


int long2tilex(float lon, int z);
int lat2tiley(float lat, int z);
float tilex2long(int x, int z);
float tiley2lat(int y, int z);
float y2lat (int y, float lat, float zoom);
float x2long (int x, float lon, float zoom);
int lat2y (float mark_lat, float lat, float zoom);
int long2x (float mark_long, float lon, float zoom);
char *BingtileXYZToQuadKey(char *quadKey, int x, int y, int z);
void map_parseDoc (char *docname);
void get_maps (uint8_t mode, GeoMap *mapdata);
uint8_t map_downloader (char *name, float x, float y, int8_t button, float data, uint8_t action);
int thread_get_maps1 (void *data);
int thread_get_maps2 (void *data);
void draw_quad (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, float roll, float pitch, float yaw, float lat, float lon, uint8_t zoom);
void draw_tracker (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, float pitch, float yaw, float lat, float lon, uint8_t zoom);
void get_dir (float lat_from, float lon_from, float alt_from, float lat_to, float lon_to, float alt_to, float *angle, float *dist1, float *angle_up, float *dist2);
void winkel_line (ESContext *esContext, float x_origin, float y_origin, float winkel, float r1, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float *nx1, float *ny1);
void mark_route (ESContext *esContext, float last_lat, float last_long, float last_alt, float mark_lat, float mark_long, float mark_alt, int8_t type, float lat, float lon, uint8_t zoom);
void mark_tunnel (ESContext *esContext, float last_lat, float last_long, float last_alt, float mark_lat, float mark_long, float mark_alt, uint8_t type, float lat, float lon, uint8_t zoom);
void mark_point (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, char *text, char *command, uint8_t type, float radius, float orbit, float lat, float lon, uint8_t zoom);
void mark_plane (ESContext *esContext, float mark_lat, float mark_long, float mark_alt, char *text, float lat, float lon, uint8_t zoom);
void mark_poi (ESContext *esContext, float mark_lat, float mark_long, char *text, uint8_t type, float lat, float lon, uint8_t zoom);
float get_distance (float from_lat, float from_lon, float to_lat, float to_lon, float alt);
float get_m_per_pixel (float lat, int zoomlevel);
int calc_fov (float film_width, float film_height, float sensor_mult, float lense, float dist, float *w, float *h);

GeoMap *GeoMap_init (void);
void GeoMap_draw (GeoMap *mapdata);
void GeoMap_exit (GeoMap *mapdata);

