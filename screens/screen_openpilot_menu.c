
#include <all.h>

uint16_t sy = 0;


uint8_t UAVT_gui_scroll(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (button == 4) {
		if (sy > 0) {
			sy--;
		}
	} else if (button == 5) {
		sy++;
	}
	reset_buttons();
	return 0;
}


#include "screens/screen_openpilot_guihelper.c"
#include "screens/screen_openpilot_gui.c"
#include "screens/screen_openpilot_guimain.c"


void screen_openpilot(ESContext *esContext) {
	UAVT_gui_show(esContext);
}

