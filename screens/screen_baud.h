
extern void screen_baud (ESContext *esContext);

void baud_set_mode (uint8_t mode);
uint8_t baud_get_mode (void);
void baud_set_dir (char *text);
char *baud_get_dir (void);
void baud_reset_filter (void);
void baud_add_filter (char *filter);
void baud_set_callback (uint8_t (*callback) (char *, float, float, int8_t, float, uint8_t));
