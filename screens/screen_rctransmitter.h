
extern char rctransmitter_type_names[TELETYPE_LAST][32];
extern char channel_names[16][20];
extern char rctransmitter_name[200];
extern char rctransmitter_device[20];
extern int8_t rctransmitter_dualrate[8];
extern int8_t rctransmitter_reverse[8];
extern int8_t rctransmitter_expo[8];
extern int8_t rctransmitter_center[8];
extern int8_t rctransmitter_trimm[8];
extern int8_t rctransmitter_type;
extern char rctransmitter_btaddr[20];
extern char rctransmitter_btpin[20];
extern uint32_t rctransmitter_baud;
extern char rctransmitter_image[1024];
extern char diff_name[2][100];

extern void screen_rctransmitter (ESContext *esContext);
extern uint8_t rctransmitter_name_edit (char *name, float x, float y, int8_t button, float data);
extern void bt_reconnect (void);
extern void rctransmitter_update (void);
extern void rctransmitter_set (void);
extern uint8_t rctransmitter_mavlink_diff (char *name, float x, float y, int8_t button, float data);
extern void rctransmitter_save (void);
void rctransmitter_init (void);
uint8_t rctransmitter_connection_status (void);
uint8_t rctransmitter_get_type_by_name (char *name);
