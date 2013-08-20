
#include <userdata.h>
#include <screen_background.h>
#include <main.h>
#include <draw.h>
#include <model.h>

extern int file_exists (char *fileName);

#ifdef SDLGL
Object3d obj3d;
#endif


void screen_background (ESContext *esContext) {
	char tmp_str[1024];
	static float rotate = 0.0;
	rotate += 0.3;

#ifdef SDLGL
	sprintf(tmp_str, "%s/bg.obj", BASE_DIR);
	if (file_exists(tmp_str) != 0) {
		static uint8_t startup = 0;
		if (startup == 0) {
			startup = 1;
			object3d_load(&obj3d);
		}
	
		glTranslatef(0.0, 0.0, -3.2);
		glRotatef(rotate, 1.0, 0.2, 0.3);
		object3d_draw(&obj3d);
		glRotatef(-rotate, 1.0, 0.2, 0.3);
		glTranslatef(0.0, 0.0, 3.2);
	
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
	} else
#endif
	{
		if (contrast == 1) {
			draw_box_f3(esContext, -1.5, -1.0, 0.0, 1.5, 1.0, 0.0, 0, 0, 0, 255);
		} else {
			sprintf(tmp_str, "%s", ModelData.image);
			if (file_exists(tmp_str) != 0) {
				draw_image_f3(esContext, -1.5, -1.0, 1.5, 1.0, 0.0, tmp_str);
				draw_box_f3(esContext, -1.5, -1.0, 0.0, 1.5, 1.0, 0.0, 0, 0, 0, 200);
			}
			sprintf(tmp_str, "%s/textures/logo-%s.png", BASE_DIR, teletypes[ModelData.teletype]);
			if (file_exists(tmp_str) != 0) {
				draw_image_f3(esContext, -1.0, -0.3, 1.0, 0.3, 0.0, tmp_str);
			} else {
				printf("Logo not found: %s\n", tmp_str);
				draw_image_f3(esContext, -1.0, -0.3, 1.0, 0.3, 0.0, TEXTURE_LOGO);
			}
		}
	}
}
