

#if defined USE_WIFIBC

typedef struct {
	int channel;
	int freq;
	char comment[128];
} WifiBcChannels;

extern WifiBcChannels wifibc_channels[50];
extern int wifibc_channels_max;

void wifibc_init(void);
void wifibc_exit(void);
SDL_Surface *wifibc_get(void);

#endif

