
extern uint8_t logmode;
extern uint8_t logplay;
extern uint8_t logplay_open;
extern uint8_t logplay_play;
extern uint8_t logplay_pause;
extern uint32_t logplay_msec;
extern uint32_t logplay_startsec;
extern uint8_t logplay_list;
extern uint8_t logplay_filelist;
extern char logplay_file[1024];
extern int log_startup_time;
extern char *Logdata;


uint8_t logging_set_mode (char *name, float x, float y, int8_t button, float data, uint8_t action);
void logplay_export_kml (char *logfile, char *kmlfile, uint8_t type);
uint8_t logplay_cmd_kml (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t logplay_cmd_pause (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t logplay_cmd_step (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t logplay_cmd_play (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t logplay_cmd_open (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t logplay_cmd_open_ok (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t logplay_cmd_play_updown (char *name, float x, float y, int8_t button, float data, uint8_t action);
void logplay_draw_control (ESContext *esContext, float x1, float y1);
void map_log_show (void);

void LogSave (void);
void LogInit (void);
void LogAppend (char *line);
void Logging (void);
