
extern int16_t fms_pos;
extern uint16_t fms_sel;

uint8_t fms_add (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t fms_del (char *name, float x, float y, int8_t button, float data, uint8_t action);
void screen_fms (ESContext *esContext);
void wp_load_mission (char *filename);
void wp_save_mission (char *filename);
