
uint8_t gps_init(uint8_t modelid, char *port, uint32_t baud);
void gps_exit(uint8_t modelid);
void gps_update(uint8_t modelid);
uint8_t gps_connection_status(uint8_t modelid);

uint8_t gcs_gps_init(char *port, uint32_t baud);
void gcs_gps_exit(void);
uint8_t gcsgps_connection_status(void);

