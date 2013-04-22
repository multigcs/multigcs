
#define JETI_BT_L 7
#define JETI_BT_D 6
#define JETI_BT_U 5
#define JETI_BT_R 4

extern char jeti_line1[17];
extern char jeti_line2[17];
extern int jeti_serial_fd;
extern uint8_t jeti_ok;

void jeti_init (char *mdevice, uint32_t baud);
void jeti_exit (void);
void jeti_update (void);
uint8_t jeti_left (char *name, float x, float y, int8_t button, float data);
uint8_t jeti_up (char *name, float x, float y, int8_t button, float data);
uint8_t jeti_down (char *name, float x, float y, int8_t button, float data);
uint8_t jeti_right (char *name, float x, float y, int8_t button, float data);
uint8_t jeti_connection_status (void);

