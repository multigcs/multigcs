
#if defined USE_APRS

#define APRS_MAX	5000

typedef struct {
	char id[128];
	float lat;
	float lon;
	int tstamp;
} AprsPos;

extern AprsPos aprs_pos[APRS_MAX];

int aprs_init (char *server_ip, int port);
int aprs_exit (void);
void aprs_pos_update(char *id, float lat, float lon);
int aprs_loop (void);

#endif

