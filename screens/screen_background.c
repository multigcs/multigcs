
#include <userdata.h>
#include <screen_background.h>
#include <main.h>
#include <model.h>
#include <screen_rctransmitter.h>

extern int file_exists (char *fileName);


void screen_background (ESContext *esContext) {
	static float rotate = 0.0;
	rotate += 0.3;
	if (contrast == 1) {
		draw_box_f3(esContext, -1.5, -1.0, 0.0, 1.5, 1.0, 0.0, 0, 0, 0, 255);
	} else {
		char tmp_str[1024];
		sprintf(tmp_str, "%s", rctransmitter_image);
		if (file_exists(tmp_str) != 0) {
			draw_image_f3(esContext, -1.5, -1.0, 1.5, 1.0, 0.0, tmp_str);
			draw_box_f3(esContext, -1.5, -1.0, 0.0, 1.5, 1.0, 0.0, 0, 0, 0, 200);
		}
		sprintf(tmp_str, "/usr/share/gl-gcs/textures/logo-%i.png", ModelData.teletype);
		if (file_exists(tmp_str) != 0) {
			draw_image_f3(esContext, -1.0, -0.3, 1.0, 0.3, 0.0, tmp_str);
		} else {
			draw_image_f3(esContext, -1.0, -0.3, 1.0, 0.3, 0.0, TEXTURE_LOGO);
		}
	}
}
