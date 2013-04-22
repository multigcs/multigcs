
#include <userdata.h>
#include <main.h>
#include <screen_calibration.h>

void screen_calibration (ESContext *esContext) {
	char tmp_str[100];
#ifdef SDLGL
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#else
	ESMatrix modelview;
	UserData *userData = esContext->userData;
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	draw_title(esContext, "Calibration");

	tmp_str[0] = 0;
	if (calibration_mode == 1) {
		draw_line(esContext, 60 - 20, 60 - 20, 60 + 20, 60 + 20, 255, 255, 255, 255);
		draw_line(esContext, 60 - 20, 60 + 20, 60 + 20, 60 - 20, 255, 255, 255, 255);
		sprintf(tmp_str, "Step 1/5");
	} else if (calibration_mode == 2) {
		draw_line(esContext, esContext->width - 60 - 20, 60 - 20, esContext->width - 60 + 20, 60 + 20, 255, 255, 255, 255);
		draw_line(esContext, esContext->width - 60 - 20, 60 + 20, esContext->width - 60 + 20, 60 - 20, 255, 255, 255, 255);
		sprintf(tmp_str, "Step 2/5");
	} else if (calibration_mode == 3) {
		draw_line(esContext, 60 - 20, esContext->height - 60 - 20, 60 + 20, esContext->height - 60 + 20, 255, 255, 255, 255);
		draw_line(esContext, 60 - 20, esContext->height - 60 + 20, 60 + 20, esContext->height - 60 - 20, 255, 255, 255, 255);
		sprintf(tmp_str, "Step 3/5");
	} else if (calibration_mode == 4) {
		draw_line(esContext, esContext->width - 60 - 20, esContext->height - 60 - 20, esContext->width - 60 + 20, esContext->height - 60 + 20, 255, 255, 255, 255);
		draw_line(esContext, esContext->width - 60 - 20, esContext->height - 60 + 20, esContext->width - 60 + 20, esContext->height - 60 - 20, 255, 255, 255, 255);
		sprintf(tmp_str, "Step 4/5");
	} else if (calibration_mode == 5) {
		if (calibration_timeout > 0) {
			calibration_timeout--;
		} else {
			calibration_mode = 1;
			calibration_timeout = 200;
		}
		sprintf(tmp_str, "OK ? (%i)", calibration_timeout);
		redraw_flag = 1;
	}
	draw_text_f(esContext, 0.0 - strlen(tmp_str) * 0.06 * 0.6 / 2 - 0.012, -0.03, 0.06, 0.06, FONT_GREEN_BG, tmp_str);

#ifdef SDLGL
	glPopMatrix();
#endif

}

