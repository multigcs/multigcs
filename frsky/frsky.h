
int thread_serial_frsky(void *unused);
void frsky_mode(uint8_t new_mode);
uint8_t frsky_mode_get(void);
uint8_t frsky_init(char *port, uint32_t baud);
void frsky_exit(void);
uint8_t frsky_connection_status(void);
