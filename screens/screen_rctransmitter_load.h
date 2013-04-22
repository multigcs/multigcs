

void screen_rctransmitter_load (ESContext *esContext);
uint8_t rctransmitter_add (char *name, float x, float y, int8_t button, float data);
uint8_t rctransmitter_del (char *name, float x, float y, int8_t button, float data);
void screen_rctransmitter (ESContext *esContext);
uint8_t rctransmitter_load_model (char *name, float x, float y, int8_t button, float data);

