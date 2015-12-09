
#include <stdint.h>

extern float sel;
extern float set_sel;
extern float sel2;
extern float set_sel2;
extern uint8_t sel1_mode;
extern uint8_t sel2_mode;


void screen_mavlink_menu(ESContext *esContext);
void mavlink_param_read_file(char *param_file);

void mavlink_meta_get_option(int id, char *name, char *entry);
void mavlink_meta_get_bits(int id, char *name, char *entry);


