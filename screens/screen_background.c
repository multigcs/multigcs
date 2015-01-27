
#include <all.h>

extern int file_exists (char *fileName);

#ifdef SDLGL
Object3d obj3d;
#endif


uint8_t get_background_model (char *filename) {
	char tmp_str[1024];
	sprintf(tmp_str, "%s/obj3d/%s.obj", BASE_DIR, modeltypes[ModelData[ModelActive].modeltype]);
	if (file_exists(tmp_str) != 0) {
		strncpy(filename, tmp_str, 1023);
		return 0;
	}
	sprintf(tmp_str, "%s/obj3d/%s.obj", BASE_DIR, teletypes[ModelData[ModelActive].teletype]);
	if (file_exists(tmp_str) != 0) {
		strncpy(filename, tmp_str, 1023);
		return 0;
	}
	sprintf(tmp_str, "%s/obj3d/bg.obj", BASE_DIR);
	if (file_exists(tmp_str) != 0) {
		strncpy(filename, tmp_str, 1023);
		return 0;
	}
	filename[0] = 0;
	return 1;
}

void screen_background (ESContext *esContext) {
	char tmp_str[1024];
	static float rotate = 0.0;
	rotate += 0.3;

#ifndef ANDROID
#ifdef SDLGL
	if (get_background_model(tmp_str) == 0) {
		static uint8_t startup = 0;
		if (startup == 0 || strcmp(obj3d.name, tmp_str) != 0) {
			startup = 1;
			if (obj3d.faces_num != 0) {
				object3d_free(&obj3d);
			}
			object3d_load(&obj3d, tmp_str);
		}
		glTranslatef(0.0, 0.0, -3.2);

		if (ModelData[ModelActive].heartbeat == 0) {
			glRotatef(rotate, 1.0, 0.2, 0.3);
		} else {
			glRotatef(ModelData[ModelActive].pitch + 90.0, 1.0, 0.0, 0.0);
			glRotatef(ModelData[ModelActive].roll, 0.0, 1.0, 0.0);
		}


		object3d_draw(&obj3d, 155, 155, 255, 10);

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
	} else {
		if (setup.contrast == 1) {
			draw_box_f3(esContext, -1.5, -1.0, 0.0, 1.5, 1.0, 0.0, 0, 0, 0, 255);
		} else {
			sprintf(tmp_str, "%s", ModelData[ModelActive].image);
			if (file_exists(tmp_str) != 0) {
				draw_image_f3(esContext, -1.5, -1.0, 1.5, 1.0, 0.0, tmp_str);
				draw_box_f3(esContext, -1.5, -1.0, 0.0, 1.5, 1.0, 0.0, 0, 0, 0, 200);
			} else {
				sprintf(tmp_str, "%s/textures/logo-%s.png", BASE_DIR, teletypes[ModelData[ModelActive].teletype]);
				if (file_exists(tmp_str) != 0) {
					draw_image_f3(esContext, -1.0, -0.3, 1.0, 0.3, 0.0, tmp_str);
				} else {
					SDL_Log("Logo not found: %s\n", tmp_str);
					draw_image_f3(esContext, -1.0, -0.3, 1.0, 0.3, 0.0, TEXTURE_LOGO);
				}
			}
		}
	}
#else
	if (setup.contrast == 1) {
		draw_box_f3(esContext, -1.5, -1.0, 0.0, 1.5, 1.0, 0.0, 0, 0, 0, 255);
	} else {
		sprintf(tmp_str, "%s", ModelData[ModelActive].image);
		if (file_exists(tmp_str) != 0) {
			draw_image_f3(esContext, -1.5, -1.0, 1.5, 1.0, 0.0, tmp_str);
			draw_box_f3(esContext, -1.5, -1.0, 0.0, 1.5, 1.0, 0.0, 0, 0, 0, 200);
		} else {
			sprintf(tmp_str, "%s/textures/logo-%s.png", BASE_DIR, teletypes[ModelData[ModelActive].teletype]);
			if (file_exists(tmp_str) != 0) {
				draw_image_f3(esContext, -1.0, -0.3, 1.0, 0.3, 0.0, tmp_str);
			} else {
				SDL_Log("Logo not found: %s\n", tmp_str);
				draw_image_f3(esContext, -1.0, -0.3, 1.0, 0.3, 0.0, TEXTURE_LOGO);
			}
		}
	}
#endif
#endif
}
