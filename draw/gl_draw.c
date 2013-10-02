
#include <all.h>



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

uint8_t RB_Active = 0;
GLuint RB_FramebufferName = 0;
GLuint RB_renderedTexture = 0;
GLuint RB_depthrenderbuffer = 0;
GLenum RB_DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};


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

void object3d_load_data (Object3d *o3d, char *filename) {
	FILE *fr;
	char line[1025];
	o3d->cords = malloc(sizeof(Object3dCord));
	o3d->faces = malloc(sizeof(Object3dFace));
	o3d->cords_num = 0;
	o3d->faces_num = 0;
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
				o3d->cords = realloc(o3d->cords, sizeof(Object3dCord) * (o3d->cords_num + 1));
				o3d->cords[o3d->cords_num].x = px;
				o3d->cords[o3d->cords_num].y = py;
				o3d->cords[o3d->cords_num].z = pz;
				o3d->cords_num++;
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
				o3d->faces[o3d->faces_num].a = p1v - 1;
				o3d->faces[o3d->faces_num].b = p2v - 1;
				o3d->faces[o3d->faces_num].c = p3v - 1;

				if (p4v != 0) {
					o3d->faces_num++;
					o3d->faces = realloc(o3d->faces, sizeof(Object3dFace) * (o3d->faces_num + 1));
					o3d->faces[o3d->faces_num].a = p1v - 1;
					o3d->faces[o3d->faces_num].b = p3v - 1;
					o3d->faces[o3d->faces_num].c = p4v - 1;
				}
				o3d->faces_num++;
			}
		}
		fclose(fr);
//		o3d->scale *= 2.0;
//		o3d->scale /= 2.0;
	}
}

void object3d_load (Object3d *o3d, char *filename) {
	FILE *fr;
	char line[1025];
	o3d->cords = malloc(sizeof(Object3dCord));
	o3d->faces = malloc(sizeof(Object3dFace));
	o3d->cords_num = 0;
	o3d->faces_num = 0;
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
				o3d->cords = realloc(o3d->cords, sizeof(Object3dCord) * (o3d->cords_num + 1));
				o3d->cords[o3d->cords_num].x = px;
				o3d->cords[o3d->cords_num].y = py;
				o3d->cords[o3d->cords_num].z = pz;
				o3d->cords_num++;
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
				o3d->faces[o3d->faces_num].a = p1v - 1;
				o3d->faces[o3d->faces_num].b = p2v - 1;
				o3d->faces[o3d->faces_num].c = p3v - 1;
				if (p4v != 0) {
					o3d->faces_num++;
					o3d->faces = realloc(o3d->faces, sizeof(Object3dFace) * (o3d->faces_num + 1));
					o3d->faces[o3d->faces_num].a = p1v - 1;
					o3d->faces[o3d->faces_num].b = p3v - 1;
					o3d->faces[o3d->faces_num].c = p4v - 1;
				}
				o3d->faces_num++;
			}
		}
		fclose(fr);
//		o3d->scale *= 2.0;
//		o3d->scale /= 2.0;
#ifdef GL_OBJECT_USING_BUFFER
		glGenBuffersARB(1, &o3d->cordsID);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, o3d->cordsID);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, o3d->cords_num * sizeof(float) * 3, o3d->cords, GL_STATIC_DRAW_ARB);
		glGenBuffersARB(1, &o3d->facesID);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, o3d->facesID);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, o3d->faces_num * sizeof(uint32_t) * 4, o3d->faces, GL_STATIC_DRAW_ARB);
#endif
	}
}

void object3d_save_as_collada (Object3d *o3d, char *filename) {
	FILE *fr2;
	float collada_scale = 1.0;
	time_t liczba_sekund;
	struct tm strukt;
	time(&liczba_sekund);
	localtime_r(&liczba_sekund, &strukt); 

	fr2 = fopen(filename, "w");
	fprintf(fr2, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n");
	fprintf(fr2, "<COLLADA xmlns=\"http://www.collada.org/2005/11/COLLADASchema\" version=\"1.4.1\">\n");

	fprintf(fr2, "    <asset>\n");
	fprintf(fr2, "        <contributor>\n");
	fprintf(fr2, "            <authoring_tool>MultiGCS</authoring_tool>\n");
	fprintf(fr2, "        </contributor>\n");
	fprintf(fr2, "        <created>%d-%d-%dT%d:%d:%dZ</created>\n", strukt.tm_year + 1900, strukt.tm_mon + 1, strukt.tm_mday, strukt.tm_hour, strukt.tm_min, strukt.tm_sec);
	fprintf(fr2, "        <up_axis>Z_UP</up_axis>\n");
	fprintf(fr2, "    </asset>\n");

	fprintf(fr2, "    <library_effects>\n");
	fprintf(fr2, "      <effect id=\"EFFECT1\">\n");
	fprintf(fr2, "        <profile_COMMON>\n");
	fprintf(fr2, "          <technique sid=\"common\">\n");
	fprintf(fr2, "            <phong>\n");
	fprintf(fr2, "              <ambient>\n");
	fprintf(fr2, "                <color>1.0 1.0 1.0 1.0</color>\n");
	fprintf(fr2, "              </ambient>\n");
	fprintf(fr2, "              <transparency>\n");
	fprintf(fr2, "                <float>0.3</float>\n");
	fprintf(fr2, "              </transparency>\n");
	fprintf(fr2, "            </phong>\n");
	fprintf(fr2, "          </technique>\n");
	fprintf(fr2, "        </profile_COMMON>\n");
	fprintf(fr2, "      </effect>\n");
	fprintf(fr2, "    </library_effects>\n");

	fprintf(fr2, "    <library_materials>\n");
	fprintf(fr2, "      <material id=\"MATERIAL1\">\n");
	fprintf(fr2, "        <instance_effect url=\"#EFFECT1\"/>\n");
	fprintf(fr2, "      </material>\n");
	fprintf(fr2, "    </library_materials>\n");

	fprintf(fr2, "    <library_geometries>\n");
	fprintf(fr2, "        <geometry id=\"GEOMETRY1\">\n");
	fprintf(fr2, "            <mesh>\n");
	fprintf(fr2, "                <source id=\"MESH_SOURCE1\">\n");
	fprintf(fr2, "                    <float_array id=\"CORDS1\" count=\"%i\">", (o3d->cords_num) * 3);
	uint32_t num = 1;
	for (num = 0; num < o3d->cords_num; num++) {
		fprintf(fr2, "%f %f %f ", o3d->cords[num].x / o3d->scale * collada_scale, o3d->cords[num].y / o3d->scale * collada_scale, o3d->cords[num].z / o3d->scale * collada_scale);
	}
	fprintf(fr2, "</float_array>\n");
	fprintf(fr2, "                    <technique_common>\n");
	fprintf(fr2, "                        <accessor count=\"%i\" source=\"#CORDS1\" stride=\"3\">\n", o3d->cords_num);
	fprintf(fr2, "                            <param name=\"X\" type=\"float\" />\n");
	fprintf(fr2, "                            <param name=\"Y\" type=\"float\" />\n");
	fprintf(fr2, "                            <param name=\"Z\" type=\"float\" />\n");
	fprintf(fr2, "                        </accessor>\n");
	fprintf(fr2, "                    </technique_common>\n");
	fprintf(fr2, "                </source>\n");
	fprintf(fr2, "                <vertices id=\"VERTICES1\">\n");
	fprintf(fr2, "                    <input semantic=\"POSITION\" source=\"#MESH_SOURCE1\" />\n");
	fprintf(fr2, "                </vertices>\n");
	fprintf(fr2, "                <triangles count=\"%i\" material=\"MATERIAL1\">\n", o3d->faces_num);
	fprintf(fr2, "                    <input offset=\"0\" semantic=\"VERTEX\" source=\"#VERTICES1\" />\n");
	fprintf(fr2, "                    <p>");
	for (num = 0; num < o3d->faces_num; num++) {
		fprintf(fr2, "%i %i %i ", o3d->faces[num].a, o3d->faces[num].b, o3d->faces[num].c);
	}
	fprintf(fr2, "</p>\n");
	fprintf(fr2, "                </triangles>\n");
	fprintf(fr2, "            </mesh>\n");
	fprintf(fr2, "        </geometry>\n");
	fprintf(fr2, "    </library_geometries>\n");

	fprintf(fr2, "    <library_nodes>\n");
	fprintf(fr2, "        <node id=\"NODE1\">\n");
	fprintf(fr2, "            <instance_geometry url=\"#GEOMETRY1\">\n");
	fprintf(fr2, "            </instance_geometry>\n");
	fprintf(fr2, "        </node>\n");
	fprintf(fr2, "    </library_nodes>\n");

	fprintf(fr2, "    <library_visual_scenes>\n");
	fprintf(fr2, "        <visual_scene id=\"SCENE1\">\n");
	fprintf(fr2, "            <node name=\"MultiGCS\">\n");
	fprintf(fr2, "                <node id=\"SCENE_NODE1\">\n");
	fprintf(fr2, "                    <instance_node url=\"#NODE1\" />\n");
	fprintf(fr2, "                </node>\n");
	fprintf(fr2, "            </node>\n");
	fprintf(fr2, "        </visual_scene>\n");
	fprintf(fr2, "    </library_visual_scenes>\n");

	fprintf(fr2, "    <scene>\n");
	fprintf(fr2, "        <instance_visual_scene url=\"#SCENE1\" />\n");
	fprintf(fr2, "    </scene>\n");

	fprintf(fr2, "</COLLADA>\n");
	fclose(fr2);
}

void object3d_free (Object3d *o3d) {
#ifdef GL_OBJECT_USING_BUFFER
	if (o3d->cordsID != 0 && o3d->facesID != 0) {
		glDeleteBuffersARB(1, &o3d->cordsID);
		o3d->cordsID = 0;
		glDeleteBuffersARB(1, &o3d->facesID);
		o3d->facesID = 0;
	}
#endif
	free(o3d->cords);
	free(o3d->faces);
	o3d->faces_num = 0;
	o3d->cords_num = 0;
	o3d->scale = 0.0;
	o3d->name[0] = 0;
}

void object3d_draw (Object3d *o3d, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
#ifdef GL_OBJECT_USING_BUFFER
	if (o3d->cordsID != 0 && o3d->facesID != 0) {
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, o3d->cordsID);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, o3d->facesID);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glPushMatrix();
		glScalef(1.0 / o3d->scale, 1.0 / o3d->scale, 1.0 / o3d->scale);
		glDrawElements(GL_TRIANGLES, o3d->faces_num * 3, GL_UNSIGNED_INT, 0);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	}
#else
	uint32_t num = 1;
	for (num = 0; num < o3d->faces_num; num++) {
		glBegin(GL_TRIANGLES);
		glVertex3f(o3d->cords[o3d->faces[num].a].x / o3d->scale, o3d->cords[o3d->faces[num].a].y / o3d->scale, o3d->cords[o3d->faces[num].a].z / o3d->scale);
		glVertex3f(o3d->cords[o3d->faces[num].b].x / o3d->scale, o3d->cords[o3d->faces[num].b].y / o3d->scale, o3d->cords[o3d->faces[num].b].z / o3d->scale);
		glVertex3f(o3d->cords[o3d->faces[num].c].x / o3d->scale, o3d->cords[o3d->faces[num].c].y / o3d->scale, o3d->cords[o3d->faces[num].c].z / o3d->scale);
		glEnd();
	}
#endif
}

void draw_line_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef HTML_DRAWING
	char tmp_str[1024];
	sprintf(tmp_str, "	draw_line(context, %0.0f, %0.0f, %0.0f, %0.0f, '#%0.2x%0.2x%0.2x');\n", x1 * X_CAL, y1 * Y_CAL, x2 * X_CAL, y2 * Y_CAL, r, g, b);
	strcat(display_html, tmp_str);
#endif
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
#ifdef HTML_DRAWING
	char tmp_str[1024];
	sprintf(tmp_str, "	draw_rect(context, %0.0f, %0.0f, %0.0f, %0.0f, 'rgba(%i,%i,%i,%0.3f)');\n", x1 * X_CAL, y1 * Y_CAL, x2 * X_CAL, y2 * Y_CAL, r, g, b, (float)a / 255.0);
	strcat(display_html, tmp_str);
#endif
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
#ifdef HTML_DRAWING
	char tmp_str[1024];
	sprintf(tmp_str, "	draw_box(context, %0.0f, %0.0f, %0.0f, %0.0f, 'rgba(%i,%i,%i,%0.3f)');\n", x1 * X_CAL, y1 * Y_CAL, x2 * X_CAL, y2 * Y_CAL, r, g, b, (float)a / 255.0);
	strcat(display_html, tmp_str);
#endif
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
#ifdef HTML_DRAWING
	char tmp_str[1024];
	sprintf(tmp_str, "	draw_box(context, %0.0f, %0.0f, %0.0f, %0.0f, '#%0.2x%0.2x%0.2x');\n", x1 * X_CAL, y1 * Y_CAL, x2 * X_CAL, y2 * Y_CAL, r, g, b);
	strcat(display_html, tmp_str);
#endif
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
#ifdef HTML_DRAWING
	char tmp_str[1024];
	sprintf(tmp_str, "	draw_box(context, %0.0f, %0.0f, %0.0f, %0.0f, '#%0.2x%0.2x%0.2x');\n", x1 * X_CAL, y1 * Y_CAL, x2 * X_CAL, y2 * Y_CAL, r, g, b);
	strcat(display_html, tmp_str);
#endif
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
#ifdef HTML_DRAWING
	char tmp_str[1024];
	sprintf(tmp_str, "	draw_tria(context, %0.0f, %0.0f, %0.0f, %0.0f, %0.0f, %0.0f, '#%0.2x%0.2x%0.2x');\n", x1 * X_CAL, y1 * Y_CAL, x2 * X_CAL, y2 * Y_CAL, x3 * X_CAL, y3 * Y_CAL, r, g, b);
	strcat(display_html, tmp_str);
#endif
#ifdef CONSOLE_ONLY
	return;
#endif
	y1 = y1 * -1;
	y2 = y2 * -1;
	y3 = y3 * -1;
	glBegin(GL_LINES);
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertex3f(x1, y1, -2.0 + z1);
	glVertex3f(x2, y2, -2.0 + z2);
	glVertex3f(x3, y3, -2.0 + z3);
	glVertex3f(x1, y1, -2.0 + z1);
	glEnd();
}

void draw_triaFilled_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#ifdef HTML_DRAWING
	char tmp_str[1024];
	sprintf(tmp_str, "	draw_triaFilled(context, %0.0f, %0.0f, %0.0f, %0.0f, %0.0f, %0.0f, '#%0.2x%0.2x%0.2x');\n", x1 * X_CAL, y1 * Y_CAL, x2 * X_CAL, y2 * Y_CAL, x3 * X_CAL, y3 * Y_CAL, r, g, b);
	strcat(display_html, tmp_str);
#endif
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
#ifdef HTML_DRAWING
	char tmp_str[1024];
	char tmp_str2[1024];
	int n2;
	int n3 = 0;
	strncpy(tmp_str2, file, 1023);
	for (n2 = 0; n2 < strlen(tmp_str2); n2++) {
		if (tmp_str2[n2] == '/') {
			n3 = n2 + 1;
		} else if (tmp_str2[n2] == '.') {
			tmp_str2[n2] = 0;
			break;
		}
	}
	sprintf(tmp_str, "	var %s = new Image();\n", tmp_str2 + n3);
	strcat(display_html, tmp_str);
	sprintf(tmp_str, "	%s.onload = function() {\n", tmp_str2 + n3);
	strcat(display_html, tmp_str);
	sprintf(tmp_str, "		context2.drawImage(%s, %0.0f, %0.0f, %0.0f, %0.0f);\n", tmp_str2 + n3, x1 * X_CAL, y1 * Y_CAL, (x2 * X_CAL) - (x1 * X_CAL), (y2 * Y_CAL) - (y1 * Y_CAL));
	strcat(display_html, tmp_str);
	sprintf(tmp_str, "	};\n");
	strcat(display_html, tmp_str);
	sprintf(tmp_str, "	%s.src = 'http://127.0.0.1:8080%s';\n", tmp_str2 + n3, file);
	strcat(display_html, tmp_str);
#endif
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
//			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
//			if ( (TexCache[tex_num].texture = loadPNG(file)) != 0 ) { 
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strncpy(TexCache[tex_num].name, file, 1023);
				TexCache[tex_num].atime = time(0);
			} else {
//				printf("could not load image: %s\n", file);
				unlink(file);
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


void draw_image_srtm (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file, float lat1, float lon1, float lat2, float lon2, float alpha0, float alpha1, float alpha2, float grid) {
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

	if (file == NULL || file[0] == 0) {
		file = NULL;
	}

	if (file != NULL) {
		for (n = 0; n < MAX_TEXCACHE; n++) {
			if (strcmp(TexCache[n].name, file) == 0) {
				tex_num = n;
				break;
			} else if (TexCache[n].atime < atime_min) {
				old_num = n;
				atime_min = TexCache[n].atime;
			}
		}
	}
	if (file != NULL && tex_num == -1) {
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
//			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
//			if ( (TexCache[tex_num].texture = loadPNG(file)) != 0 ) {
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) {
				strncpy(TexCache[tex_num].name, file, 1023);
				TexCache[tex_num].atime = time(0);
			} else {
//				printf("could not load image: %s\n", file);
				unlink(file);
			}
		}
	}
	if (TexCache[tex_num].texture != 0) {
		TexCache[tex_num].atime = time(0);
	}
	if (file == NULL || TexCache[tex_num].texture != 0) {
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
/*
		subtiles = (int)((lat1 -  lat2) * 400);
		if (subtiles < 2) {
			subtiles = 2;
		} else if (subtiles > 7) {
			subtiles = 7;
		}
*/
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

				int16_t _alt1 = get_altitude(_thy1, _thx1) - 20;
				int16_t _alt2 = get_altitude(_thy1, _thx2) - 20;
				int16_t _alt3 = get_altitude(_thy2, _thx2) - 20;
				int16_t _alt4 = get_altitude(_thy2, _thx1) - 20;

				z1 = z + (float)_alt1 / alt_zoom;
				z2 = z + (float)_alt2 / alt_zoom;
				z3 = z + (float)_alt3 / alt_zoom;
				z4 = z + (float)_alt4 / alt_zoom;
				if (file != NULL) {
					glEnable( GL_TEXTURE_2D );
					glBindTexture( GL_TEXTURE_2D, TexCache[tex_num].texture );
					glBegin( GL_QUADS );
					glColor4f(1.0, 1.0, 1.0, alpha0);
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
				}
				if ((float)_alt1 > ModelData.p_alt || (float)_alt2 > ModelData.p_alt || (float)_alt3 > ModelData.p_alt || (float)_alt4 > ModelData.p_alt) {
					glBegin( GL_QUADS );
					if ((float)_alt1 > ModelData.p_alt) {
						glColor4f(1.0, 0.0, 0.0, alpha1);
					} else {
						glColor4f(0.0, 1.0, 0.0, alpha2);
					}
					glVertex3f(tx1, ty1, -2.0 + z1);
					if ((float)_alt2 > ModelData.p_alt) {
						glColor4f(1.0, 0.0, 0.0, alpha1);
					} else {
						glColor4f(0.0, 1.0, 0.0, alpha2);
					}
					glVertex3f(tx2, ty1, -2.0 + z2);
					if ((float)_alt3 > ModelData.p_alt) {
						glColor4f(1.0, 0.0, 0.0, alpha1);
					} else {
						glColor4f(0.0, 1.0, 0.0, alpha2);
					}
					glVertex3f(tx2, ty2, -2.0 + z3);
					if ((float)_alt4 > ModelData.p_alt) {
						glColor4f(1.0, 0.0, 0.0, alpha1);
					} else {
						glColor4f(0.0, 1.0, 0.0, alpha2);
					}
					glVertex3f(tx1, ty2, -2.0 + z4);
					glEnd();
				} else if (alpha2 > 0.0) {
					glBegin( GL_QUADS );
					glColor4f(0.0, 1.0, 0.0, alpha2);
					glVertex3f(tx1, ty1, -2.0 + z1);
					glVertex3f(tx2, ty1, -2.0 + z2);
					glVertex3f(tx2, ty2, -2.0 + z3);
					glVertex3f(tx1, ty2, -2.0 + z4);
					glEnd();
				}
				if (grid > 0.0) {
					glBegin(GL_LINE_LOOP);
					glColor4f(1.0, 1.0, 1.0, grid);
					glVertex3f(tx1, ty1, -2.0 + z1 + 0.001);
					glVertex3f(tx2, ty1, -2.0 + z2 + 0.001);
					glVertex3f(tx2, ty2, -2.0 + z3 + 0.001);
					glVertex3f(tx1, ty2, -2.0 + z4 + 0.001);
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
#ifdef HTML_DRAWING
	char color[100];
	if (strcmp(file, FONT_GREEN_BG) == 0) {
		strncpy(color, "green", 99);
	} else if (strcmp(file, FONT_TRANS) == 0) {
		strncpy(color, "gray", 99);
	} else if (strcmp(file, FONT_BLACK_BG) == 0) {
		strncpy(color, "black", 99);
	} else if (strcmp(file, FONT_WHITE) == 0) {
		strncpy(color, "white", 99);
	} else if (strcmp(file, FONT_GREEN) == 0) {
		strncpy(color, "green", 99);
	} else if (strcmp(file, FONT_PINK) == 0) {
		strncpy(color, "red", 99);
	} else {
		strncpy(color, "white", 99);
	}
	char tmp_str[1024];
	sprintf(tmp_str, "	draw_text(context, %0.0f, %0.0f, 'bold %0.0fpx Arial', \"%s\", '%s');\n", x1 * X_CAL, y1 * Y_CAL + (h * 300.0), h * 300.0, text, color);
	strcat(display_html, tmp_str);
#endif
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
//			printf("remove font %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num >= 0) {
//			printf("loading font %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strncpy(TexCache[tex_num].name, file, 1023);
				TexCache[tex_num].atime = time(0);

			} else {
				printf("could not load image: %s\n", file);
				unlink(file);
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
//			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
//			if ( (TexCache[tex_num].texture = loadPNG(file)) != 0 ) { 
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strncpy(TexCache[tex_num].name, file, 1023);
				TexCache[tex_num].atime = time(0);
			} else {
				printf("could not load image: %s\n", file);
				unlink(file);
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
#ifndef OSX
	glewInit();
#endif
	glClear( GL_COLOR_BUFFER_BIT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, w - setup.screen_border_x, h - setup.screen_border_y);
	gluPerspective(53.0, aspect, 0.001, 7.0);
//	glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -5.5, 5.5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);

	glEnable(GL_VERTEX_ARRAY);

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

	// create Render-Buffer
	glGenFramebuffers(1, &RB_FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, RB_FramebufferName);
	glGenTextures(1, &RB_renderedTexture);
 	glBindTexture(GL_TEXTURE_2D, RB_renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, setup.screen_w, setup.screen_h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenRenderbuffers(1, &RB_depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, RB_depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RB_depthrenderbuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RB_renderedTexture, 0);
	glDrawBuffers(1, RB_DrawBuffers);
	draw_to_screen();
	return 0;
}

void glExit (ESContext *esContext) {
	// Delete Render-Buffer
	glDeleteTextures(1, &RB_renderedTexture);
	glDeleteFramebuffers(1, &RB_FramebufferName);
}

void glResize (ESContext *esContext, int w, int h) {
#ifndef SDL2
	const SDL_PixelFormat fmt = *(WinScreen->format);
	Uint32 video_flags;
	if (setup.fullscreen == 1) {
		video_flags = SDL_OPENGLBLIT | SDL_FULLSCREEN;
	} else {
		video_flags = SDL_OPENGLBLIT | SDL_RESIZABLE;
	}
	if ((WinScreen = SDL_SetVideoMode(w, h, fmt.BitsPerPixel, video_flags)) == NULL) {
		fprintf(stderr, "* Couldn't set GL mode: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
#endif
	if (setup.keep_ratio == 0.0) {
		aspect = (GLfloat)w / (GLfloat)h;
	} else {
		aspect = setup.keep_ratio;
	}
	gl_init(w, h);
	setup.screen_w = w;
	setup.screen_h = h;
	esContext->width = setup.screen_w;
	esContext->height = setup.screen_h;

	char tmp_str[100];
	sprintf(tmp_str, "Resize: %ix%i", setup.screen_w, setup.screen_h);
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
		fprintf(stderr,"* Couldn't initialize SDL: %s\n",SDL_GetError());
		exit( 1 );
	}
#ifdef SDL2
	if (setup.fullscreen == 1) {
		video_flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
	} else {
		video_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	}
	if (setup.borderless == 1) {
		video_flags |= SDL_WINDOW_BORDERLESS;
	}
	if ((MainWindow = SDL_CreateWindow("Multi-GCS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, setup.screen_w, setup.screen_h, video_flags)) == NULL) {
		fprintf(stderr, "* Couldn't create MainWindow: %s\n", SDL_GetError());
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
	if (setup.fullscreen == 1) {
		video_flags = SDL_OPENGLBLIT | SDL_FULLSCREEN;
	} else {
		video_flags = SDL_OPENGLBLIT | SDL_RESIZABLE;
	}
	SDL_WM_SetCaption("Multi-GCS", "");
	if ((WinScreen = SDL_SetVideoMode(setup.screen_w, setup.screen_h, bpp, video_flags)) == NULL) {
		fprintf(stderr, "* Couldn't set GL mode: %s\n", SDL_GetError());
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

	printf("* GL-Screen BPP: %d\n", WinScreen->format->BitsPerPixel);

	if (setup.keep_ratio == 0.0) {
		aspect = (GLfloat)setup.screen_w / (GLfloat)setup.screen_h;
	} else {
		aspect = setup.keep_ratio;
	}
	printf("* aspect: %f\n", aspect);
	gl_init(setup.screen_w, setup.screen_h);

	esContext->width = setup.screen_w;
	esContext->height = setup.screen_h;

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
	glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, setup.screen_w - setup.screen_border_x, setup.screen_h - setup.screen_border_y);
}

void draw_to_buffer (void) {
	RB_Active = 1;
	glBindFramebuffer(GL_FRAMEBUFFER, RB_FramebufferName);
	glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void draw_to_screen (void) {
	RB_Active = 0;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, setup.screen_w - setup.screen_border_x, setup.screen_h - setup.screen_border_y);
}

uint8_t draw_target (void) {
	return RB_Active;
}

void draw_buffer_to_screen (float x1, float y1, float x2, float y2, float z, float alpha) {
	y1 = y1 * -1;
	y2 = y2 * -1;
	glColor4f(1.0, 1.0, 1.0, alpha);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, RB_renderedTexture);
	glBegin(GL_QUADS);
		glTexCoord2i( 0, 0 );
		glVertex3f(x1, y2, -2.0 + z);
		glTexCoord2i( 1, 0 );
		glVertex3f(x2, y2, -2.0 + z);
		glTexCoord2i( 1, 1 );
		glVertex3f(x2, y1, -2.0 + z);
		glTexCoord2i( 0, 1 );
		glVertex3f(x1, y1, -2.0 + z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}



