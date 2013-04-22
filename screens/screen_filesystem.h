
extern void screen_filesystem (ESContext *esContext);

void filesystem_set_mode (uint8_t mode);
uint8_t filesystem_get_mode (void);
void filesystem_set_dir (char *text);
char *filesystem_get_dir (void);
void filesystem_reset_filter (void);
void filesystem_add_filter (char *filter);
void filesystem_set_callback (uint8_t (*callback) (char *, float, float, int8_t, float));
