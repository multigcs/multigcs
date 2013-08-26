
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <GL/gl.h>
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include <model.h>
#include <userdata.h>
#include <gl_draw.h>
#include <draw.h>
#include <main.h>

#ifdef SDL2
SDL_Window *MainWindow = NULL;
SDL_GLContext MainGLcontext;
#endif
SDL_Surface *WinScreen = NULL;
SDL_Event event;
float alt_zoom = 700.0;

TextureCache TexCache[MAX_TEXCACHE];
GLfloat colors[4] = {1.0f, 0.0f, 0.0f, 1.0f};
float aspect = 1.0;

void esTranslate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz) {
	glTranslatef(tx, ty, tz);
}

void esRotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	glRotatef(angle, x, y, -z);
}

void esMatrixLoadIdentity(ESMatrix *result) {
}

void esMatrixMultiply(ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB) {
}

#define GL_OBJECT_USING_BUFFER

void object3d_load (Object3d *o3d, char *filename) {
	FILE *fr;
	char line[1025];
	uint32_t obj_cords_num = 1;
	o3d->cords = malloc(sizeof(Object3dCord));
	o3d->faces = malloc(sizeof(Object3dFace));
	o3d->faces_num = 1;
	o3d->scale = 0.0;
	fr = fopen (filename, "r");
	if (fr != 0) {
		strncpy(o3d->name, filename, 1023);
	        while(fgets(line, 1024, fr) != NULL) {
			if (strncmp(line, "v ", 2) == 0) {
				float px = 0.0;
				float py = 0.0;
				float pz = 0.0;
		                sscanf (line + 2, "%f %f %f", &px, &py, &pz);
				o3d->cords = realloc(o3d->cords, sizeof(Object3dCord) * (obj_cords_num + 1));
				o3d->cords[obj_cords_num].x = px;
				o3d->cords[obj_cords_num].y = py;
				o3d->cords[obj_cords_num].z = pz;
				obj_cords_num++;
				if (px > o3d->scale) {
					o3d->scale = px;
				}
				if (py > o3d->scale) {
					o3d->scale = py;
				}
				if (pz > o3d->scale) {
					o3d->scale = pz;
				}
			} else if (strncmp(line, "f ", 2) == 0) {
				int p1v = 0;
				int p1t = 0;
				int p1n = 0;
				int p2v = 0;
				int p2t = 0;
				int p2n = 0;
				int p3v = 0;
				int p3t = 0;
				int p3n = 0;
				int p4v = 0;
				int p4t = 0;
				int p4n = 0;

				if (sscanf(line + 2, "%i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", &p1v, &p1t, &p1n, &p2v, &p2t, &p2n, &p3v, &p3t, &p3n, &p4v, &p4t, &p4n) >= 9) {
				} else if (sscanf(line + 2, "%i//%i %i//%i %i//%i %i//%i", &p1v, &p1t, &p2v, &p2t, &p3v, &p3t, &p4v, &p4t) >= 6) {
				} else if (sscanf(line + 2, "%i/%i %i/%i %i/%i %i/%i", &p1v, &p1t, &p2v, &p2t, &p3v, &p3t, &p4v, &p4t) >= 6) {
				} else if (sscanf(line + 2, "%i %i %i %i", &p1v, &p2v, &p3v, &p4v) >= 3) {
				}

				o3d->faces = realloc(o3d->faces, sizeof(Object3dFace) * (o3d->faces_num + 1));
				o3d->faces[o3d->faces_num].a = p1v;
				o3d->faces[o3d->faces_num].b = p2v;
				o3d->faces[o3d->faces_num].c = p3v;
#ifdef GL_OBJECT_USING_BUFFER
				if (p4v == 0) {
					o3d->faces[o3d->faces_num].d = p3v;
				} else {
					o3d->faces[o3d->faces_num].d = p4v;
				}
#else
				o3d->faces[o3d->faces_num].d = p4v;
#endif
				o3d->faces_num++;
			}
		}
		fclose(fr);
//		o3d->scale *= 2.0;
//		o3d->scale /= 2.0;
	}
#ifdef GL_OBJECT_USING_BUFFER
	glGenBuffersARB(1, &o3d->cordsID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, o3d->cordsID);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, obj_cords_num * sizeof(float) * 3, o3d->cords, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(1, &o3d->facesID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, o3d->facesID);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, o3d->faces_num * sizeof(uint32_t) * 4, o3d->faces, GL_STATIC_DRAW_ARB);
#else
	free(o3d->cords);
	free(o3d->faces);
#endif
}

void object3d_free (Object3d *o3d) {
#ifdef GL_OBJECT_USING_BUFFER
	glDeleteBuffersARB(1, &o3d->cordsID);
	o3d->cordsID = 0;
	glDeleteBuffersARB(1, &o3d->facesID);
	o3d->facesID = 0;
#else
	free(o3d->cords);
	free(o3d->faces);
#endif
	o3d->faces_num = 0;
	o3d->scale = 0.0;
	o3d->name[0] = 0;
}

void object3d_draw (Object3d *o3d, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
#ifdef GL_OBJECT_USING_BUFFER
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, o3d->cordsID);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, o3d->facesID);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glPushMatrix();
	glScalef(1.0 / o3d->scale, 1.0 / o3d->scale, 1.0 / o3d->scale);
	glDrawElements(GL_QUADS, o3d->faces_num * 4, GL_UNSIGNED_INT, 0);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
#else
	uint32_t num = 1;
	for (num = 1; num < o3d->faces_num; num++) {
		if (o3d->faces[num].d == 0) {
			glBegin(GL_TRIANGLES);
		} else {
			glBegin(GL_QUADS);
		}
		glVertex3f(o3d->cords[o3d->faces[num].a].x / o3d->scale, o3d->cords[o3d->faces[num].a].y / o3d->scale, o3d->cords[o3d->faces[num].a].z / o3d->scale);
		glVertex3f(o3d->cords[o3d->faces[num].b].x / o3d->scale, o3d->cords[o3d->faces[num].b].y / o3d->scale, o3d->cords[o3d->faces[num].b].z / o3d->scale);
		glVertex3f(o3d->cords[o3d->faces[num].c].x / o3d->scale, o3d->cords[o3d->faces[num].c].y / o3d->scale, o3d->cords[o3d->faces[num].c].z / o3d->scale);
		if (o3d->faces[num].d != 0) {
			glVertex3f(o3d->cords[o3d->faces[num].d].x / o3d->scale, o3d->cords[o3d->faces[num].d].y / o3d->scale, o3d->cords[o3d->faces[num].d].z / o3d->scale);
		}
		glEnd();
	}
#endif
}

void draw_line_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	glBegin(GL_LINES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertex3f(x1, y1, -2.0 + z1);
	glVertex3f(x2, y2, -2.0 + z2);
	glEnd();
}

void draw_circle_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	uint16_t ii = 0;
	float num_segments = radius * 300.0;
	if (num_segments < 100.0) {
		num_segments = 100.0;
	} else if (num_segments > 360.0) {
		num_segments = 360.0;
	}
	float theta = 2 * 3.1415926 / num_segments;
	float tangetial_factor = tanf(theta);
	float radial_factor = cosf(theta);
	float x = radius;//we start at angle = 0
	float y = 0;
	glBegin(GL_LINE_LOOP);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	for(ii = 0; ii < num_segments; ii++) {
		glVertex3f(x + x1, y + y1, -2.0 + z1);
		float tx = -y;
		float ty = x;
		x += tx * tangetial_factor;
		y += ty * tangetial_factor;
		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

void draw_circle_f3_slow (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	GLfloat i = 0.0;
	GLfloat step = 1.0;
	glBegin(GL_LINES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	for (i = 0; i < 360.0; i += step) {
		glVertex3f(x1 + cos(i * DEG2RAD) * radius, y1 + sin(i * DEG2RAD) * radius, -2.0 + z1);
		glVertex3f(x1 + cos((i + step) * DEG2RAD) * radius, y1 + sin((i + step) * DEG2RAD) * radius, -2.0 + z1);
	}
	glEnd();
}

void draw_circleFilled_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	uint16_t ii = 0;
	float num_segments = radius * 300.0;
	if (num_segments < 100.0) {
		num_segments = 100.0;
	} else if (num_segments > 360.0) {
		num_segments = 360.0;
	}
	float theta = 2 * 3.1415926 / num_segments;
	float tangetial_factor = tanf(theta);
	float radial_factor = cosf(theta);
	float x = radius;//we start at angle = 0
	float y = 0;
	float last_x = x + x1;
	float last_y = y + y1;
	float tx = -y;
	float ty = x;
	x += tx * tangetial_factor;
	y += ty * tangetial_factor;
	x *= radial_factor;
	y *= radial_factor;
	glBegin(GL_TRIANGLES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	for(ii = 0; ii < num_segments; ii++) {
		glVertex3f(x1, y1, -2.0 + z1);
		glVertex3f(last_x, last_y, -2.0 + z1);
		glVertex3f(x + x1, y + y1, -2.0 + z1);
		last_x = x + x1;
		last_y = y + y1;
		tx = -y;
		ty = x;
		x += tx * tangetial_factor;
		y += ty * tangetial_factor;
		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

void draw_circleFilled_f3_slow (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	GLfloat i = 0.0;
	for (i = 0; i < 360.0; i += 2) {
		glBegin(GL_TRIANGLES);
		glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
		glVertex3f(x1, y1, -2.0 + z1);
		glVertex3f(x1 + cos(i * DEG2RAD) * radius, y1 + sin(i * DEG2RAD) * radius, -2.0 + z1);
		glVertex3f(x1 + cos((i + 2) * DEG2RAD) * radius, y1 + sin((i + 2) * DEG2RAD) * radius, -2.0 + z1);
		glEnd();
	}
}

void draw_zylinder_f3 (ESContext *esContext, float x1, float y1, float z1, float z2, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	GLfloat i = 0.0;
	for (i = 0; i < 360.0; i += 2) {
		glBegin(GL_TRIANGLES);
		glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
		glVertex3f(x1, y1, -2.0 + z2);
		glVertex3f(x1 + cos(i * DEG2RAD) * radius, y1 + sin(i * DEG2RAD) * radius, -2.0 + z1);
		glVertex3f(x1 + cos((i + 2) * DEG2RAD) * radius, y1 + sin((i + 2) * DEG2RAD) * radius, -2.0 + z1);
		glEnd();
	}
}

void draw_circleFilled_f3_part (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, float stop, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	uint16_t ii = 0;
	float num_segments = radius * 300.0;
	if (num_segments < 100.0) {
		num_segments = 100.0;
	} else if (num_segments > 360.0) {
		num_segments = 360.0;
	}
	float theta = 2 * 3.1415926 / num_segments;
	float tangetial_factor = tanf(theta);
	float radial_factor = cosf(theta);
	float x = radius;
	float y = 0;
	float last_x = x1 - x;
	float last_y = y + y1;
	float tx = -y;
	float ty = x;
	x += tx * tangetial_factor;
	y += ty * tangetial_factor;
	x *= radial_factor;
	y *= radial_factor;
	float x_inner = radius_inner;
	float y_inner = 0;
	float last_x_inner = x1 - x_inner;
	float last_y_inner = y_inner + y1;
	float tx_inner = -y_inner;
	float ty_inner = x_inner;
	x_inner += tx_inner * tangetial_factor;
	y_inner += ty_inner * tangetial_factor;
	x_inner *= radial_factor;
	y_inner *= radial_factor;

	float x_inner3 = radius_inner - radius_inner / 3.0;
	float y_inner3 = 0;
	float last_x_inner3 = x1 - x_inner3;
	float last_y_inner3 = y_inner3 + y1;
	float tx_inner3 = -y_inner3;
	float ty_inner3 = x_inner3;
	x_inner3 += tx_inner3 * tangetial_factor;
	y_inner3 += ty_inner3 * tangetial_factor;
	x_inner3 *= radial_factor;
	y_inner3 *= radial_factor;


	glBegin(GL_TRIANGLES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);

	for (ii = 0; ii < (float)num_segments * stop / 360.0; ii++) {

		if (ii >= (float)num_segments * start / 360.0 && ii < (float)num_segments * stop / 360.0) {

			glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);

			glVertex3f(last_x_inner, last_y_inner, -2.0 + z1);
			glVertex3f(last_x, last_y, -2.0 + z1);
			glVertex3f(x1 - x, y + y1, -2.0 + z1);

			glVertex3f(last_x_inner, last_y_inner, -2.0 + z1);
			glVertex3f(x1 - x, y + y1, -2.0 + z1);
			glVertex3f(x1 - x_inner, y_inner + y1, -2.0 + z1);


			glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0 / 2.0);
			glVertex3f(last_x_inner, last_y_inner, -2.0 + z1);

			glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)0.0);
			glVertex3f(last_x_inner3, last_y_inner3, -2.0 + z1);

			glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)0.0);
			glVertex3f(x1 - x_inner3, y_inner3 + y1, -2.0 + z1);

			glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0 / 2.0);
			glVertex3f(last_x_inner, last_y_inner, -2.0 + z1);

			glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)0.0);
			glVertex3f(x1 - x_inner3, y_inner3 + y1, -2.0 + z1);

			glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0 / 2.0);
			glVertex3f(x1 - x_inner, y_inner + y1, -2.0 + z1);
		}

		last_x = x1 - x;
		last_y = y + y1;
		tx = -y;
		ty = x;
		x += tx * tangetial_factor;
		y += ty * tangetial_factor;
		x *= radial_factor;
		y *= radial_factor;

		last_x_inner = x1 - x_inner;
		last_y_inner = y_inner + y1;
		tx_inner = -y_inner;
		ty_inner = x_inner;
		x_inner += tx_inner * tangetial_factor;
		y_inner += ty_inner * tangetial_factor;
		x_inner *= radial_factor;
		y_inner *= radial_factor;

		last_x_inner3 = x1 - x_inner3;
		last_y_inner3 = y_inner3 + y1;
		tx_inner3 = -y_inner3;
		ty_inner3 = x_inner3;
		x_inner3 += tx_inner3 * tangetial_factor;
		y_inner3 += ty_inner3 * tangetial_factor;
		x_inner3 *= radial_factor;
		y_inner3 *= radial_factor;

	}
	glEnd();
}

void draw_circleFilled_f3_part_slow (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, float stop, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	float i = 0.0;
	float step = 1.0;
	glBegin(GL_TRIANGLES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0 + z1);
	for (i = start; i < stop; i += step) {
		glVertex3f(x1 - cos(i * DEG2RAD) * radius_inner, y1 + sin(i * DEG2RAD) * radius_inner, -2.0 + z1);
		glVertex3f(x1 - cos(i * DEG2RAD) * radius, y1 + sin(i * DEG2RAD) * radius, -2.0 + z1);
		glVertex3f(x1 - cos((i + step) * DEG2RAD) * radius, y1 + sin((i + step) * DEG2RAD) * radius, -2.0 + z1);
		glVertex3f(x1 - cos((i + step) * DEG2RAD) * radius, y1 + sin((i + step) * DEG2RAD) * radius, -2.0 + z1);
		glVertex3f(x1 - cos((i + step) * DEG2RAD) * radius_inner, y1 + sin((i + step) * DEG2RAD) * radius_inner, -2.0 + z1);
		glVertex3f(x1 - cos(i * DEG2RAD) * radius_inner, y1 + sin(i * DEG2RAD) * radius_inner, -2.0 + z1);
	}
	glEnd();
}

void draw_circlePointer_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	if (radius < 0.04) {
		float x2 = x1 - cos(start * DEG2RAD) * radius;
		float y2 = y1 - sin(start * DEG2RAD) * radius;
		draw_line_f3(esContext, x1, y1, z1, x2, y2, z1, r, g, b, a);
		return;
	}
	y1 = y1 * -1;
	float i = start;
	float step = 90.0;
	glBegin(GL_TRIANGLES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0 + z1);
	glVertex3f(x1 - cos(i * DEG2RAD) * radius, y1 + sin(i * DEG2RAD) * radius, -2.0 + z1);
	glVertex3f(x1 - cos((i - step) * DEG2RAD) * radius_inner, y1 + sin((i - step) * DEG2RAD) * radius_inner, -2.0 + z1);
	glVertex3f(x1 - cos((i + step) * DEG2RAD) * radius_inner, y1 + sin((i + step) * DEG2RAD) * radius_inner, -2.0 + z1);
	glEnd();
	draw_circleFilled_f3(esContext, x1, -y1, 0.0, radius_inner, r, g, b, a);
}

void draw_trifan_f3 (ESContext *esContext, float *poly_array, uint16_t len, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	uint16_t n = 0;
	glBegin(GL_TRIANGLE_FAN);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	for (n = 0; n < len; n += 3) {
		glVertex3f(poly_array[n], poly_array[n + 1] * -1, -2.0 + poly_array[n + 2]);
	}
	glEnd();
}

void draw_rect_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	glBegin(GL_LINES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertex3f(x1, y1, -2.0 + z1);
	glVertex3f(x2, y1, -2.0 + z1);
	glVertex3f(x2, y1, -2.0 + z1);
	glVertex3f(x2, y2, -2.0 + z2);
	glVertex3f(x2, y2, -2.0 + z2);
	glVertex3f(x1, y2, -2.0 + z2);
	glVertex3f(x1, y2, -2.0 + z2);
	glVertex3f(x1, y1, -2.0 + z1);
	glEnd();
}

void draw_box_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	glBegin(GL_QUADS);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertex3f(x1, y1, -2.0 + z1);
	glVertex3f(x2, y1, -2.0 + z1);
	glVertex3f(x2, y2, -2.0 + z2);
	glVertex3f(x1, y2, -2.0 + z2);
	glEnd();
}

void draw_box_f3c2 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	glBegin(GL_QUADS);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertex3f(x1, y1, -2.0 + z1);
	glVertex3f(x2, y1, -2.0 + z1);
	glColor4f((float)r2 / 255.0, (float)g2 / 255.0, (float)b2 / 255.0, (float)a2 / 255.0);
	glVertex3f(x2, y2, -2.0 + z2);
	glVertex3f(x1, y2, -2.0 + z2);
	glEnd();
}

void draw_box_f3c2b (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	glBegin(GL_QUADS);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertex3f(x1, y1, -2.0 + z1);
	glColor4f((float)r2 / 255.0, (float)g2 / 255.0, (float)b2 / 255.0, (float)a2 / 255.0);
	glVertex3f(x2, y1, -2.0 + z2);
	glColor4f((float)r2 / 255.0, (float)g2 / 255.0, (float)b2 / 255.0, (float)a2 / 255.0);
	glVertex3f(x2, y2, -2.0 + z2);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertex3f(x1, y2, -2.0 + z1);
	glEnd();
}

void draw_tria_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	y3 = y3 * -1;
	glBegin(GL_TRIANGLES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertex3f(x1, y1, -2.0 + z1);
	glVertex3f(x2, y2, -2.0 + z2);
	glVertex3f(x3, y3, -2.0 + z3);
	glEnd();
}

void draw_surface_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, SDL_Surface *screen) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	if (screen == NULL) {
		return;
	}
	GLuint texture;			// This is a handle to our texture object
	GLenum texture_format;
	GLint  nOfColors;
        nOfColors = screen->format->BytesPerPixel;
        if (nOfColors == 4) {
                if (screen->format->Rmask == 0x000000ff) {
                        texture_format = GL_RGBA;
                } else {
                        texture_format = GL_BGRA;
		}
        } else if (nOfColors == 3) {
                if (screen->format->Rmask == 0x000000ff) {
                        texture_format = GL_RGB;
                } else {
                        texture_format = GL_BGR;
                }
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
		return;
        }
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, screen->w, screen->h, 0, texture_format, GL_UNSIGNED_BYTE, screen->pixels );

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
		glTexCoord2i( 0, 0 );
		glVertex3f(x1, y1, -2.0 + z);
		glTexCoord2i( 1, 0 );
		glVertex3f(x2, y1, -2.0 + z);
		glTexCoord2i( 1, 1 );
		glVertex3f(x2, y2, -2.0 + z);
		glTexCoord2i( 0, 1 );
		glVertex3f(x1, y2, -2.0 + z);
	glEnd();
	glDisable( GL_TEXTURE_2D );

	glDeleteTextures( 1, &texture );
}

void draw_image_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, char *file) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	int16_t n = 0;
	int16_t tex_num = -1;
	int16_t old_num = -1;
	uint32_t atime_min = 0xFFFFFFFF;
	for (n = 0; n < MAX_TEXCACHE; n++) {
		if (strcmp(TexCache[n].name, file) == 0) {
			tex_num = n;
			break;
		} else if (TexCache[n].atime < atime_min) {
			old_num = n;
			atime_min = TexCache[n].atime;
		}
	}
	if (tex_num == -1) {
		for (n = 0; n < MAX_TEXCACHE; n++) {
			if (TexCache[n].name[0] == 0) {
				tex_num = n;
				break;
			}
		}
		if (old_num == -1) {
			old_num = 0;
		}
		if (tex_num == -1) {
			tex_num = old_num;
			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
//			if ( (TexCache[tex_num].texture = loadPNG(file)) != 0 ) { 
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strcpy(TexCache[tex_num].name, file);
				TexCache[tex_num].atime = time(0);
			} else {
//				printf("could not load image: %s\n", file);
				char del_cmd[1024];
				sprintf(del_cmd, "rm \"%s\"", file);
				system(del_cmd);
			}
		}
	}
	if (TexCache[tex_num].texture != 0) {
		TexCache[tex_num].atime = time(0);
//		printf("# %s = %i\n", TexCache[tex_num].name, TexCache[tex_num].texture);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, TexCache[tex_num].texture );
		glBegin( GL_QUADS );
			glTexCoord2i( 0, 0 );
			glVertex3f(x1, y1, -2.0 + z);
			glTexCoord2i( 1, 0 );
			glVertex3f(x2, y1, -2.0 + z);
			glTexCoord2i( 1, 1 );
			glVertex3f(x2, y2, -2.0 + z);
			glTexCoord2i( 0, 1 );
			glVertex3f(x1, y2, -2.0 + z);
		glEnd();
		glDisable( GL_TEXTURE_2D );
	}
}


void draw_image_srtm (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file, float lat1, float lon1, float lat2, float lon2) {
#ifdef CONSOLE_ONLY
	return;
#endif
	float x1 = (float)x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)y / (float)esContext->height * 2.0 - 1.0;
	float x2 = x1 + (float)w / (float)esContext->width * 2.0 * aspect;
	float y2 = y1 + (float)h / (float)esContext->height * 2.0;
	float z = 0.0;
	int16_t n = 0;
	int16_t tex_num = -1;
	int16_t old_num = -1;
	uint32_t atime_min = 0xFFFFFFFF;

	y1 = y1 * -1;
	y2 = y2 * -1;

	for (n = 0; n < MAX_TEXCACHE; n++) {
		if (strcmp(TexCache[n].name, file) == 0) {
			tex_num = n;
			break;
		} else if (TexCache[n].atime < atime_min) {
			old_num = n;
			atime_min = TexCache[n].atime;
		}
	}
	if (tex_num == -1) {
		for (n = 0; n < MAX_TEXCACHE; n++) {
			if (TexCache[n].name[0] == 0) {
				tex_num = n;
				break;
			}
		}
		if (old_num == -1) {
			old_num = 0;
		}
		if (tex_num == -1) {
			tex_num = old_num;
			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
//			if ( (TexCache[tex_num].texture = loadPNG(file)) != 0 ) {
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) {
				strcpy(TexCache[tex_num].name, file);
				TexCache[tex_num].atime = time(0);
			} else {
				printf("could not load image: %s\n", file);
				char del_cmd[200];
				sprintf(del_cmd, "rm %s", file);
				system(del_cmd);
			}
		}
	}
	if (TexCache[tex_num].texture != 0) {
		TexCache[tex_num].atime = time(0);
		float z1 = z;
		float z2 = z;
		float z3 = z;
		float z4 = z;
		uint8_t tx = 0;
		uint8_t ty = 0;
		float dx = x2 - x1;
		float dy = y2 - y1;
		float _hx1 = lon1;
		float _hx2 = lon2;
		float _hy1 = lat1;
		float _hy2 = lat2;
		float _dhx = _hx2 - _hx1;
		float _dhy = _hy2 - _hy1;
		uint8_t subtiles = 5;
		subtiles = (int)((lat1 -  lat2) * 400);
		if (subtiles < 2) {
			subtiles = 2;
		} else if (subtiles > 7) {
			subtiles = 7;
		}
		for (ty = 0; ty < subtiles; ty++) {
			for (tx = 0; tx < subtiles; tx++) {
				float tx1 = x1 + dx / (float)subtiles * (float)tx;
				float tx2 = x1 + dx / (float)subtiles * (float)(tx + 1);
				float ty1 = y1 + dy / (float)subtiles * (float)ty;
				float ty2 = y1 + dy / (float)subtiles * (float)(ty + 1);

				float tex1 = 1.0 / (float)subtiles * (float)tx;
				float tex2 = 1.0 / (float)subtiles * (float)(tx + 1);
				float tey1 = 1.0 / (float)subtiles * (float)ty;
				float tey2 = 1.0 / (float)subtiles * (float)(ty + 1);

				float _thx1 = _hx1 + _dhx / (float)subtiles * (float)tx;
				float _thx2 = _hx1 + _dhx / (float)subtiles * (float)(tx + 1);
				float _thy1 = _hy1 + _dhy / (float)subtiles * (float)ty;
				float _thy2 = _hy1 + _dhy / (float)subtiles * (float)(ty + 1);

				int16_t _alt1 = get_altitude(_thy1, _thx1);
				int16_t _alt2 = get_altitude(_thy1, _thx2);
				int16_t _alt3 = get_altitude(_thy2, _thx2);
				int16_t _alt4 = get_altitude(_thy2, _thx1);

				z1 = z + (float)_alt1 / alt_zoom;
				z2 = z + (float)_alt2 / alt_zoom;
				z3 = z + (float)_alt3 / alt_zoom;
				z4 = z + (float)_alt4 / alt_zoom;

				glEnable( GL_TEXTURE_2D );
				glBindTexture( GL_TEXTURE_2D, TexCache[tex_num].texture );
				glBegin( GL_QUADS );
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glTexCoord2f( tex1, tey1 );
				glVertex3f(tx1, ty1, -2.0 + z1);
				glTexCoord2f( tex2, tey1 );
				glVertex3f(tx2, ty1, -2.0 + z2);
				glTexCoord2f( tex2, tey2 );
				glVertex3f(tx2, ty2, -2.0 + z3);
				glTexCoord2f( tex1, tey2 );
				glVertex3f(tx1, ty2, -2.0 + z4);
				glEnd();
				glDisable( GL_TEXTURE_2D );

				if ((float)_alt1 > ModelData.p_alt || (float)_alt2 > ModelData.p_alt || (float)_alt3 > ModelData.p_alt || (float)_alt4 > ModelData.p_alt) {
					glBegin( GL_QUADS );
					if ((float)_alt1 > ModelData.p_alt) {
						glColor4f(1.0, 0.0, 0.0, 0.2);
					} else {
						glColor4f(1.0, 0.0, 0.0, 0.0);
					}
					glVertex3f(tx1, ty1, -2.0 + z1);
					if ((float)_alt2 > ModelData.p_alt) {
						glColor4f(1.0, 0.0, 0.0, 0.2);
					} else {
						glColor4f(1.0, 0.0, 0.0, 0.0);
					}
					glVertex3f(tx2, ty1, -2.0 + z2);
					if ((float)_alt3 > ModelData.p_alt) {
						glColor4f(1.0, 0.0, 0.0, 0.2);
					} else {
						glColor4f(1.0, 0.0, 0.0, 0.0);
					}
					glVertex3f(tx2, ty2, -2.0 + z3);
					if ((float)_alt4 > ModelData.p_alt) {
						glColor4f(1.0, 0.0, 0.0, 0.2);
					} else {
						glColor4f(1.0, 0.0, 0.0, 0.0);
					}
					glVertex3f(tx1, ty2, -2.0 + z4);
					glEnd();
				}

			}
		}
	}
}

void draw_char_f3_fast (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, int8_t tex_num, char num) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	if (TexCache[tex_num].texture != 0) {
		TexCache[tex_num].atime = time(0);
//		printf("# %s = %i\n", TexCache[tex_num].name, TexCache[tex_num].texture);
		float tpos_x = (float)(num % 16) * 0.0625;
		float tpos_y = (float)(num / 16) * 0.0625;
		if (num < 0) {
			int nnn = num + 256;
			tpos_x = (float)(nnn % 16) * 0.0625;
			tpos_y = (float)(nnn / 16) * 0.0625;
		}
		if (tpos_x < 0 || tpos_y < 0 || tpos_x > 511 || tpos_y > 511) {
			printf("CHAR - ERROR\n");
			return;
		}
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, TexCache[tex_num].texture );
		glBegin( GL_QUADS );
			glTexCoord2f( tpos_x, tpos_y + 0.005 );
			glVertex3f(x1, y1, -2.0 + z1);
			glTexCoord2f( tpos_x + 0.0625, tpos_y + 0.005 );
			glVertex3f(x2, y1, -2.0 + z1);
			glTexCoord2f( tpos_x + 0.0625, tpos_y + 0.0625 );
			glVertex3f(x2, y2, -2.0 + z1);
			glTexCoord2f( tpos_x, tpos_y + 0.0625 );
			glVertex3f(x1, y2, -2.0 + z1);
		glEnd();
		glDisable( GL_TEXTURE_2D );
	}
}

void draw_text_f3_fast (ESContext *esContext, float x1, float y1, float z1, float w, float h, char *file, char *text) {
#ifdef CONSOLE_ONLY
	return;
#endif
	int16_t n = 0;
	int16_t tex_num = -1;
	int16_t old_num = -1;
	uint32_t atime_min = 0xFFFFFFFF;
	for (n = 0; n < MAX_TEXCACHE; n++) {
		if (strcmp(TexCache[n].name, file) == 0) {
			tex_num = n;
			break;
		} else if (TexCache[n].atime < atime_min) {
			old_num = n;
			atime_min = TexCache[n].atime;
		}
	}
	if (tex_num == -1) {
		for (n = 0; n < MAX_TEXCACHE; n++) {
			if (TexCache[n].name[0] == 0) {
				tex_num = n;
				break;
			}
		}
		if (old_num == -1) {
			old_num = 0;
		}
		if (tex_num == -1) {
			tex_num = old_num;
			printf("remove font %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num >= 0) {
			printf("loading font %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strcpy(TexCache[tex_num].name, file);
				TexCache[tex_num].atime = time(0);

			} else {
				printf("could not load image: %s\n", file);
				char del_cmd[200];
				sprintf(del_cmd, "rm %s", file);
				system(del_cmd);
			}    
		}
	}
	for (n = 0; n < strlen(text); n++) {
		draw_char_f3_fast(esContext, x1 + n * ((float)w * 0.6), y1, z1, x1 + n * ((float)w * 0.6) + w, y1 + h, z1, tex_num, text[n]);
	}
}

void draw_char_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, char *file, char num) {
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	int16_t n = 0;
	int16_t tex_num = -1;
	int16_t old_num = -1;
	uint32_t atime_min = 0xFFFFFFFF;
	if (num == '\n' || num == '\r') {
		return;
	}
	for (n = 0; n < MAX_TEXCACHE; n++) {
		if (strcmp(TexCache[n].name, file) == 0) {
			tex_num = n;
			break;
		} else if (TexCache[n].atime < atime_min) {
			old_num = n;
			atime_min = TexCache[n].atime;
		}
	}
	if (tex_num == -1) {
		for (n = 0; n < MAX_TEXCACHE; n++) {
			if (TexCache[n].name[0] == 0) {
				tex_num = n;
				break;
			}
		}
		if (old_num == -1) {
			old_num = 0;
		}
		if (tex_num == -1) {
			tex_num = old_num;
			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
//			if ( (TexCache[tex_num].texture = loadPNG(file)) != 0 ) { 
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strcpy(TexCache[tex_num].name, file);
				TexCache[tex_num].atime = time(0);
			} else {
				printf("could not load image: %s\n", file);
				char del_cmd[200];
				sprintf(del_cmd, "rm %s", file);
				system(del_cmd);
			}
		}
	}
	if (TexCache[tex_num].texture != 0) {
		TexCache[tex_num].atime = time(0);

//		printf("# %s = %i\n", TexCache[tex_num].name, TexCache[tex_num].texture);

		float tpos_x = (float)(num % 16) * 0.0625;
		float tpos_y = (float)(num / 16) * 0.0625;
		if (num < 0) {
			int nnn = num + 256;
			tpos_x = (float)(nnn % 16) * 0.0625;
			tpos_y = (float)(nnn / 16) * 0.0625;
		}
		if (tpos_x < 0 || tpos_y < 0 || tpos_x > 511 || tpos_y > 511) {
			printf("CHAR - ERROR\n");
			return;
		}
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, TexCache[tex_num].texture );
		glBegin( GL_QUADS );
			glTexCoord2f( tpos_x, tpos_y + 0.005 );
			glVertex3f(x1, y1, -2.0 + z1);
			glTexCoord2f( tpos_x + 0.0625, tpos_y + 0.005 );
			glVertex3f(x2, y1, -2.0 + z1);
			glTexCoord2f( tpos_x + 0.0625, tpos_y + 0.0625 );
			glVertex3f(x2, y2, -2.0 + z1);
			glTexCoord2f( tpos_x, tpos_y + 0.0625 );
			glVertex3f(x1, y2, -2.0 + z1);
		glEnd();
		glDisable( GL_TEXTURE_2D );
	}
}

int gl_init (uint16_t w, uint16_t h) {
	glClear( GL_COLOR_BUFFER_BIT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glViewport(0 + screen_border_x / 2, 0 + screen_border_y / 2, w - screen_border_x, h - screen_border_y);
	gluPerspective(53.0, aspect, 0.001, 7.0);
//	glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -5.5, 5.5);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glClearDepth(1.0);
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glDepthMask( GL_TRUE );

	// Transparenz-Aktivieren
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Anti-Alias
//	glEnable(GL_POLYGON_SMOOTH);

	static float mat_shininess[] = {1.0};
	static float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv (GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
/*
	// Lichtquelle 0 einstellen
	static float light0_ambient[] = {1.0, 1.0, 1.0, 1.0};
	static float light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	static float light0_pos[]    = {400.0, 300.0, 800.0, 1.0};
	glLightfv (GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv (GL_LIGHT0, GL_POSITION,light0_pos);
	// Beleuchtungsmodell waehlen
	static float lmodel_ambient[] = {1.0, 1.0, 1.0, 1.0};
	glLightModelfv (GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	// ...und Beleuchtung einschalten. 
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable (GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
*/

	return 0;
}

void glExit (ESContext *esContext) {
}

void glResize (ESContext *esContext, int w, int h) {
#ifndef SDL2
	const SDL_PixelFormat fmt = *(WinScreen->format);
	Uint32 video_flags;
	if (fullscreen == 1) {
		video_flags = SDL_OPENGLBLIT | SDL_FULLSCREEN;
	} else {
		video_flags = SDL_OPENGLBLIT | SDL_RESIZABLE;
	}
	if ((WinScreen = SDL_SetVideoMode(w, h, fmt.BitsPerPixel, video_flags)) == NULL) {
		fprintf(stderr, "Couldn't set GL mode: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
#endif
	if (keep_ratio == 0.0) {
		aspect = (GLfloat)w / (GLfloat)h;
	} else {
		aspect = keep_ratio;
	}
	gl_init(w, h);
	screen_w = w;
	screen_h = h;
	esContext->width = screen_w;
	esContext->height = screen_h;

	char tmp_str[100];
	sprintf(tmp_str, "Resize: %ix%i", screen_w, screen_h);
	sys_message(tmp_str);
}

int glInit ( ESContext *esContext ) {
	int rgb_size[3];
	Uint32 video_flags;

#ifdef SDL2
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ) {
#else
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD | SDL_INIT_TIMER) < 0 ) {
#endif
		fprintf(stderr,"Couldn't initialize SDL: %s\n",SDL_GetError());
		exit( 1 );
	}
#ifdef SDL2
	if (fullscreen == 1) {
		video_flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
	} else {
		video_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	}
	if ((MainWindow = SDL_CreateWindow("Multi-GCS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_w, screen_h, video_flags)) == NULL) {
		fprintf(stderr, "Couldn't create MainWindow: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	WinScreen = SDL_GetWindowSurface(MainWindow);
	MainGLcontext = SDL_GL_CreateContext(MainWindow);
#else
	int bpp = 0;
	if ( SDL_GetVideoInfo()->vfmt->BitsPerPixel <= 8 ) {
		bpp = 8;
	} else {
		bpp = 16;
	}
	if (fullscreen == 1) {
		video_flags = SDL_OPENGLBLIT | SDL_FULLSCREEN;
	} else {
		video_flags = SDL_OPENGLBLIT | SDL_RESIZABLE;
	}
	SDL_WM_SetCaption("Multi-GCS", "");
	if ((WinScreen = SDL_SetVideoMode(screen_w, screen_h, bpp, video_flags)) == NULL) {
		fprintf(stderr, "Couldn't set GL mode: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
#endif
	switch (WinScreen->format->BitsPerPixel) {
	    case 8:
		rgb_size[0] = 3;
		rgb_size[1] = 3;
		rgb_size[2] = 2;
		break;
	    case 15:
	    case 16:
		rgb_size[0] = 5;
		rgb_size[1] = 5;
		rgb_size[2] = 5;
		break;
            default:
		rgb_size[0] = 8;
		rgb_size[1] = 8;
		rgb_size[2] = 8;
		break;
	}
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, rgb_size[0] );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, rgb_size[1] );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, rgb_size[2] );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	printf("GL-Screen BPP: %d\n", WinScreen->format->BitsPerPixel);

	if (keep_ratio == 0.0) {
		aspect = (GLfloat)screen_w / (GLfloat)screen_h;
	} else {
		aspect = keep_ratio;
	}
	printf("aspect: %f\n", aspect);
	gl_init(screen_w, screen_h);

	esContext->width = screen_w;
	esContext->height = screen_h;

	return GL_TRUE;
}

void draw_graph_value (ESContext *esContext, float px1, float py1, float px2, float py2, float pz, uint8_t *data, int16_t len, int16_t pointer, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef CONSOLE_ONLY
	return;
#endif
	uint16_t n = 0;
	float w = px2 - px1;
	float h = py2 - py1;
	uint8_t value1 = 0;
	uint8_t last1 = 0;
	for (n = 0; n < len; n++) {
		int16_t point = pointer + n;
		if (point > len) {
			point -= len;
		}
		value1 = 255 - data[point];
		if (n != 0) {
			float x1 = px1 + (float)(n) / len * w;
			float y1 = py1 + (float)last1 / 255.0 * h;
			float x2 = px1 + (float)(n + 1) / len * w;
			float y2 = py1 + (float)value1 / 255.0 * h;
			draw_line_f3(esContext, x1, y1, pz, x2, y2, pz, r, g, b, a);
		}
		last1 = value1;
	}
}

void resize_border (void) {
	glViewport(0 + screen_border_x / 2, 0 + screen_border_y / 2, screen_w - screen_border_x, screen_h - screen_border_y);
}

