
extern void screen_device (ESContext *esContext);

void device_set_mode (uint8_t mode);
uint8_t device_get_mode (void);
void device_set_dir (char *text);
char *device_get_dir (void);
void device_reset_filter (void);
void device_add_filter (char *filter);
void device_set_callback (uint8_t (*callback) (char *, float, float, int8_t, float, uint8_t));
