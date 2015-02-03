
typedef struct {
	float temperature;
	float humidity;
	float pressure;
	float wind_speed;
	float wind_direction;
	char sun_rise[128];
	char sun_set[128];
} Weather;

typedef struct {
	char date[3][100];
	int level[8][3];
} SpaceWeather;

extern Weather weather;
extern SpaceWeather spaceweather;

int weather_init (void);
int weather_exit (void);
void weather_draw (ESContext *esContext, float x1, float y1);
void weather_draw_wind (ESContext *esContext, float x1, float y1, uint8_t mode);

