
#include <all.h>

TextureCache TexCache[MAX_TEXCACHE];
GLfloat colors[4] = {1.0f, 0.0f, 0.0f, 1.0f};
float aspect = 1.0;
float alt_zoom = 700.0;
 
void draw_circlePointer_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	float x2 = x1 - cos(start * DEG2RAD) * radius;
	float y2 = y1 - sin(start * DEG2RAD) * radius;
	draw_line_f3(esContext, x1, y1, z1, x2, y2, z1, r, g, b, a);
	draw_circleFilled_f3(esContext, x1, y1, z1, radius_inner, r, g, b, a);
}

void draw_line_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GLfloat vVertices[6];
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;

	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;

	vVertices[0] = x1;
	vVertices[1] = y1;
	vVertices[2] = -2.0 + z1;
	vVertices[3] = x2;
	vVertices[4] = y2;
	vVertices[5] = -2.0 + z2;
	glUseProgram ( userData->programObject2 );
	glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray ( 0 );
	glUniform4fv( userData->colorLoc2, 1, colors );
	glDrawArrays ( GL_LINES, 0, 2 );
}

void draw_circle_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	y1 = y1 * -1;
	GLfloat vVertices[9];
	UserData *userData = esContext->userData;

	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;

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
	for(ii = 0; ii < num_segments; ii++) {
		vVertices[0] = x1;
		vVertices[1] = y1;
		vVertices[2] = -2.0 + z1;
		vVertices[3] = last_x;
		vVertices[4] = last_y;
		vVertices[5] = -2.0 + z1;

		vVertices[6] = x + x1;
		vVertices[7] = y + y1;
		vVertices[8] = -2.0 + z1;
      		glUseProgram ( userData->programObject2 );
		glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
		glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
		glEnableVertexAttribArray ( 0 );
		glUniform4fv( userData->colorLoc2, 1, colors );
		glDrawArrays ( GL_LINES, 1, 3 );


		last_x = x + x1;
		last_y = y + y1;
		tx = -y;
		ty = x;
		x += tx * tangetial_factor;
		y += ty * tangetial_factor;
		x *= radial_factor;
		y *= radial_factor;
	}
}

void draw_circle_f3_slow (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GLfloat vVertices[9];
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;
	GLfloat i = 0.0;
	GLfloat step = 9.0;
	if (radius < 0.05) {
		step = 36;
	} else if (radius < 0.1) {
		step = 18;
	}
	for (i = 0; i < 360.0; i += step) {
		vVertices[0] = x1;
		vVertices[1] = y1;
		vVertices[2] = -2.0 + z1;
		vVertices[3] = x1 + cos(i * DEG2RAD) * radius;
		vVertices[4] = y1 + sin(i * DEG2RAD) * radius;
		vVertices[5] = -2.0 + z1;
		vVertices[6] = x1 + cos((i + step) * DEG2RAD) * radius;
		vVertices[7] = y1 + sin((i + step) * DEG2RAD) * radius;
		vVertices[8] = -2.0 + z1;
      		glUseProgram ( userData->programObject2 );
		glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
		glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
		glEnableVertexAttribArray ( 0 );
		glUniform4fv( userData->colorLoc2, 1, colors );
		glDrawArrays ( GL_LINES, 1, 3 );
	}
}

void draw_circleFilled_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	y1 = y1 * -1;
	GLfloat vVertices[9];
	UserData *userData = esContext->userData;

	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;

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
	for(ii = 0; ii < num_segments; ii++) {
		vVertices[0] = x1;
		vVertices[1] = y1;
		vVertices[2] = -2.0 + z1;
		vVertices[3] = last_x;
		vVertices[4] = last_y;
		vVertices[5] = -2.0 + z1;
		vVertices[6] = x + x1;
		vVertices[7] = y + y1;
		vVertices[8] = -2.0 + z1;
      		glUseProgram ( userData->programObject2 );
		glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
		glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
		glEnableVertexAttribArray ( 0 );
		glUniform4fv( userData->colorLoc2, 1, colors );
		glDrawArrays ( GL_TRIANGLES, 0, 3 );
		last_x = x + x1;
		last_y = y + y1;
		tx = -y;
		ty = x;
		x += tx * tangetial_factor;
		y += ty * tangetial_factor;
		x *= radial_factor;
		y *= radial_factor;
	}
}

void draw_circleFilled_f3_slow (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GLfloat vVertices[9];
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;
	GLfloat i = 0.0;
	GLfloat step = 9.0;
	if (radius < 0.05) {
		step = 36;
	} else if (radius < 0.1) {
		step = 18;
	}
	for (i = 0; i < 360.0; i += step) {
		vVertices[0] = x1;
		vVertices[1] = y1;
		vVertices[2] = -2.0 + z1;
		vVertices[3] = x1 + cos(i * DEG2RAD) * radius;
		vVertices[4] = y1 + sin(i * DEG2RAD) * radius;
		vVertices[5] = -2.0 + z1;
		vVertices[6] = x1 + cos((i + step) * DEG2RAD) * radius;
		vVertices[7] = y1 + sin((i + step) * DEG2RAD) * radius;
		vVertices[8] = -2.0 + z1;
      		glUseProgram ( userData->programObject2 );
		glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
		glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
		glEnableVertexAttribArray ( 0 );
		glUniform4fv( userData->colorLoc2, 1, colors );
		glDrawArrays ( GL_TRIANGLES, 0, 3 );
	}
}

void draw_box_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;

	GLfloat vVertices[] = {
		x1, y1, -2.0f + z1,  // Position 0
		x1, y2, -2.0f + z1,  // Position 1
		x2, y2, -2.0f + z1,   // Position 2
		x2, y1, -2.0f + z1,   // Position 3
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;

	glUseProgram ( userData->programObject2 );
	glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray ( 0 );
	glUniform4fv( userData->colorLoc2, 1, colors );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
}

void draw_box_f3c2 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;

	GLfloat vVertices[] = {
		x1, y1, -2.0f + z1,  // Position 0
		x1, y2, -2.0f + z1,  // Position 1
		x2, y2, -2.0f + z1,   // Position 2
		x2, y1, -2.0f + z1,   // Position 3
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;

	glUseProgram ( userData->programObject2 );
	glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray ( 0 );
	glUniform4fv( userData->colorLoc2, 1, colors );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
}

void draw_tria_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;
	y3 = y3 * -1;

	GLfloat vVertices[] = {
		x1, y1, -2.0 + z1,  // Position 0
		x2, y2, -2.0 + z2,  // Position 1
		x3, y3, -2.0 + z3,   // Position 2
	};
	GLushort indices[] = { 0, 1, 2, 0 };

	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;

	glUseProgram ( userData->programObject2 );
	glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray ( 0 );
	glUniform4fv( userData->colorLoc2, 1, colors );
	glDrawElements ( GL_LINES, 3, GL_UNSIGNED_SHORT, indices );
}

void draw_triaFilled_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;
	y3 = y3 * -1;

	GLfloat vVertices[] = {
		x1, y1, -2.0 + z1,  // Position 0
		x2, y2, -2.0 + z2,  // Position 1
		x3, y3, -2.0 + z3,   // Position 2
	};
	GLushort indices[] = { 0, 1, 2 };

	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;

	glUseProgram ( userData->programObject2 );
	glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray ( 0 );
	glUniform4fv( userData->colorLoc2, 1, colors );
	glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, indices );
}

void draw_image_srtm (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file, float lat1, float lon1, float lat2, float lon2, float alpha0, float alpha1, float alpha2, float grid) {
	UserData *userData = esContext->userData;
	float x1 = (float)x / (float)esContext->width * 2.0 * aspect - 1.0 * aspect;
	float y1 = (float)y / (float)esContext->height * 2.0 - 1.0;
	float x2 = x1 + (float)w / (float)esContext->width * 2.0 * aspect;
	float y2 = y1 + (float)h / (float)esContext->height * 2.0;
	float z = 0.0;
	y1 = y1 * -1;
	y2 = y2 * -1;
	int8_t n = 0;
	int8_t tex_num = -1;
	int8_t old_num = -1;
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
			SDL_Log("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			SDL_Log("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) {
				strncpy(TexCache[tex_num].name, file, 1023);
				TexCache[tex_num].atime = time(0);
			} else {
				SDL_Log("could not load image: %s\n", file);
				unlink(file);
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

		uint8_t subtiles = 2;
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

				uint16_t _alt1 = get_altitude(_thy1, _thx1);
				uint16_t _alt2 = get_altitude(_thy1, _thx2);
				uint16_t _alt3 = get_altitude(_thy2, _thx2);
				uint16_t _alt4 = get_altitude(_thy2, _thx1);

				z1 = z + (float)_alt1 / alt_zoom;
				z2 = z + (float)_alt2 / alt_zoom;
				z3 = z + (float)_alt3 / alt_zoom;
				z4 = z + (float)_alt4 / alt_zoom;

		glUseProgram(userData->programObject);
		glActiveTexture(GL_TEXTURE0);

		GLfloat vVertices[] = {
			tx1, ty1, -2.0 + z1,  // Position 0
			tex1, tey1,          // TexCoord 3
			tx1, ty2, -2.0 + z4,  // Position 1
			tex1,  tey2,         // TexCoord 0 
			tx2, ty2, -2.0 + z3,   // Position 2
			tex2,  tey2,         // TexCoord 1
			tx2, ty1, -2.0 + z2,   // Position 3
			tex2, tey1,         // TexCoord 2
		};
		GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

		glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices );
		glEnableVertexAttribArray ( userData->positionLoc );
		glUniformMatrix4fv( userData->mvpLoc, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix.m[0][0] );

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glVertexAttribPointer ( userData->texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );
		glEnableVertexAttribArray ( userData->texCoordLoc );
		glBindTexture (GL_TEXTURE_2D, TexCache[tex_num].texture );
		glUniform1i ( userData->samplerLoc, 0 );
		glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );


			}
		}

	}
}

void draw_image_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, char *file) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;
	int8_t n = 0;
	int8_t tex_num = -1;
	int8_t old_num = -1;
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
			SDL_Log("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			SDL_Log("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strncpy(TexCache[tex_num].name, file, 1023);
				TexCache[tex_num].atime = time(0);
			} else {
				SDL_Log("could not load image: %s\n", file);
				if (strstr(file, "/MAPS/") > 0) {
					unlink(file);
				}
			}    
		}
	}
	if (TexCache[tex_num].texture != 0) {
		TexCache[tex_num].atime = time(0);
//		SDL_Log("# %s = %i\n", TexCache[tex_num].name, TexCache[tex_num].texture);
		glUseProgram(userData->programObject);
		glActiveTexture(GL_TEXTURE0);

		GLfloat vVertices[] = {
			x1, y1, -2.0 + z,  // Position 0
			0.0f,  0.0f,         // TexCoord 0 
			x1, y2, -2.0 + z,  // Position 1
			0.0f,  1.0f,         // TexCoord 1
			x2, y2, -2.0 + z,   // Position 2
			1.0f,  1.0f,         // TexCoord 2
			x2, y1, -2.0 + z,   // Position 3
			1.0f,  0.0f          // TexCoord 3
		};
		GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

		glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices );
		glEnableVertexAttribArray ( userData->positionLoc );
		glUniformMatrix4fv( userData->mvpLoc, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix.m[0][0] );

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glVertexAttribPointer ( userData->texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );
		glEnableVertexAttribArray ( userData->texCoordLoc );
		glBindTexture (GL_TEXTURE_2D, TexCache[tex_num].texture );
		glUniform1i ( userData->samplerLoc, 0 );
		glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
	}
}

inline void draw_char_f3_fast (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, int8_t tex_num, char num) {
	UserData *userData = esContext->userData;
	int nnn = 0;
	GLfloat vVertices[20];
	GLushort indices[] = {0, 1, 2, 0, 2, 3};
	y1 = y1 * -1;
	y2 = y2 * -1;
	if (num == '\n' || num == '\r') {
		return;
	}
	vVertices[0] = x1;
	vVertices[1] = y1;
	vVertices[2] = -2.0f + z1;
	vVertices[5] = x1;
	vVertices[6] = y2;
	vVertices[7] = -2.0f + z1;
	vVertices[10] = x2;
	vVertices[11] = y2;
	vVertices[12] = -2.0f + z1;
	vVertices[15] = x2;
	vVertices[16] = y1;
	vVertices[17] = -2.0f + z1;
	float tpos_x = (float)(num % 16) / 16;
	float tpos_y = (float)(num / 16) / 16;
	if (num < 0) {
		nnn = num + 256;
		tpos_x = (float)(nnn % 16) / 16;
		tpos_y = (float)(nnn / 16) / 16;
	}
	vVertices[3] = tpos_x;
	vVertices[4] = tpos_y + 0.005;
	vVertices[8] = tpos_x;
	vVertices[9] = tpos_y + 0.0625;
	vVertices[13] = tpos_x + 0.0625;
	vVertices[14] = vVertices[9];
	vVertices[18] = vVertices[13];
	vVertices[19] = vVertices[4];
	glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices );
	glEnableVertexAttribArray ( userData->positionLoc );
	glVertexAttribPointer(userData->texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
	glEnableVertexAttribArray(userData->texCoordLoc);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void draw_text_f3_fast (ESContext *esContext, float x1, float y1, float z1, float w, float h, char *file, char *text) {
	UserData *userData = esContext->userData;
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
			SDL_Log("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num > 0) {
//			SDL_Log("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strncpy(TexCache[tex_num].name, file, 1023);
				TexCache[tex_num].atime = time(0);
			} else {
				SDL_Log("could not load image: %s\n", file);
				unlink(file);
			}    
		}
	}
	if (TexCache[tex_num].texture != 0) {
		TexCache[tex_num].atime = time(0);
		glUseProgram(userData->programObject);
		glActiveTexture(GL_TEXTURE0);
		glUniformMatrix4fv( userData->mvpLoc, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix.m[0][0] );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBindTexture (GL_TEXTURE_2D, TexCache[tex_num].texture );
		glUniform1i(userData->samplerLoc, 0);
		for (n = 0; n < strlen(text); n++) {
			draw_char_f3_fast(esContext, x1 + n * ((float)w * 0.6), y1, z1, x1 + n * ((float)w * 0.6) + w, y1 + h, z1, tex_num, text[n]);
		}
	}
}

void draw_char_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, char *file, char num) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;
	int8_t n = 0;
	int8_t tex_num = -1;
	int8_t old_num = -1;
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
			SDL_Log("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			SDL_Log("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strncpy(TexCache[tex_num].name, file, 1023);
				TexCache[tex_num].atime = time(0);

			} else {
				SDL_Log("could not load image: %s\n", file);
				unlink(file);
			}    
		}
	}
	if (TexCache[tex_num].texture != 0) {
		TexCache[tex_num].atime = time(0);

//		SDL_Log("# %s = %i\n", TexCache[tex_num].name, TexCache[tex_num].texture);

		glUseProgram(userData->programObject);
		glActiveTexture(GL_TEXTURE0);

		GLfloat vVertices[20];
		vVertices[0] = x1;
		vVertices[1] = y1;
		vVertices[2] = -2.0f + z1;
		vVertices[5] = x1;
		vVertices[6] = y2;
		vVertices[7] = -2.0f + z1;
		vVertices[10] = x2;
		vVertices[11] = y2;
		vVertices[12] = -2.0f + z1;
		vVertices[15] = x2;
		vVertices[16] = y1;
		vVertices[17] = -2.0f + z1;

		float tpos_x = (float)(num % 16) / 16;
		float tpos_y = (float)(num / 16) / 16;
		if (num < 0) {
			int nnn = num + 256;
			tpos_x = (float)(nnn % 16) / 16;
			tpos_y = (float)(nnn / 16) / 16;
		}
		if (tpos_x < 0 || tpos_y < 0 || tpos_x > 511 || tpos_y > 511) {
			SDL_Log("CHAR - ERROR\n");
			return;
		}
		vVertices[3] = tpos_x;
		vVertices[4] = tpos_y + 0.005;
		vVertices[8] = tpos_x;
		vVertices[9] = tpos_y + 0.0625;
		vVertices[13] = tpos_x + 0.0625;
		vVertices[14] = tpos_y + 0.0625;
		vVertices[18] = tpos_x + 0.0625;
		vVertices[19] = tpos_y + 0.005;

		GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

		glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices );
		glEnableVertexAttribArray ( userData->positionLoc );

		glUniformMatrix4fv( userData->mvpLoc, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix.m[0][0] );

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glVertexAttribPointer ( userData->texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );
		glEnableVertexAttribArray ( userData->texCoordLoc );
		glBindTexture (GL_TEXTURE_2D, TexCache[tex_num].texture );
		glUniform1i ( userData->samplerLoc, 0 );
		glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
	}
}

int glesInit ( ESContext *esContext ) {
	esContext->userData = malloc(sizeof(UserData));	
	UserData *userData = esContext->userData;
	GLbyte vShaderStr[] =  
		"uniform mat4 u_mvpMatrix;    \n"
		"attribute vec4 a_position;   \n"
		"attribute vec2 a_texCoord;   \n"
		"varying vec2 v_texCoord;     \n"
		"void main()                  \n"
		"{                            \n"
		"   gl_Position = u_mvpMatrix * a_position; \n"
		"   v_texCoord = a_texCoord;  \n"
		"}                            \n";
   
	GLbyte fShaderStr[] =  
		"precision mediump float;                            \n"
		"varying vec2 v_texCoord;                            \n"
		"uniform sampler2D s_texture;                        \n"
		"void main()                                         \n"
		"{                                                   \n"
		"  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
		"}                                                   \n";

	GLbyte vShaderStr2[] =  
		"uniform mat4 u_mvpMatrix;    \n"
		"attribute vec4 a_position;    \n"
		"void main()                  \n"
		"{                            \n"
		"   gl_Position = u_mvpMatrix * a_position;  \n"
		"}                            \n";
   
	GLbyte fShaderStr2[] =  
		"precision mediump float;\n"\
		"uniform vec4  u_color;    \n"
		"void main()                                  \n"
		"{                                            \n"
		"  gl_FragColor = u_color;                    \n"
		"}                                            \n";

	userData->programObject = esLoadProgram ( (const char *)vShaderStr, (const char *)fShaderStr );
	userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
	userData->mvpLoc = glGetUniformLocation( userData->programObject, "u_mvpMatrix" );
	userData->texCoordLoc = glGetAttribLocation ( userData->programObject, "a_texCoord" );
	userData->samplerLoc = glGetUniformLocation ( userData->programObject, "s_texture" );

	userData->programObject2 = esLoadProgram ( (const char *)vShaderStr2, (const char *)fShaderStr2 );
	userData->positionLoc2 = glGetAttribLocation ( userData->programObject2, "a_position" );
	userData->mvpLoc2 = glGetUniformLocation( userData->programObject2, "u_mvpMatrix" );
	userData->colorLoc2 = glGetUniformLocation ( userData->programObject2, "u_color" );

	if (setup.keep_ratio == 0.0) {
		aspect = (GLfloat)esContext->width / (GLfloat)esContext->height;
	} else {
		aspect = setup.keep_ratio;
	}
	esMatrixLoadIdentity( &userData->perspective );

	glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, esContext->width - setup.screen_border_x, esContext->height - setup.screen_border_y);
	esPerspective(&userData->perspective, 53.0f, aspect, 1.0f, 20.0f);

	glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	return GL_TRUE;
}

void draw_rect_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	draw_line_f3(esContext, x1, y1, z1, x2, y1, z1, r, g, b, a);
	draw_line_f3(esContext, x2, y1, z1, x2, y2, z1, r, g, b, a);
	draw_line_f3(esContext, x2, y2, z1, x1, y2, z1, r, g, b, a);
	draw_line_f3(esContext, x1, y2, z1, x1, y1, z1, r, g, b, a);
}

void draw_circleFilled_f3_part (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, float stop, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GLfloat vVertices[18];
	UserData *userData = esContext->userData;
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
	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;
	for (ii = 0; ii < (float)num_segments * stop / 360.0; ii++) {
		if (ii >= (float)num_segments * start / 360.0 && ii < (float)num_segments * stop / 360.0) {
			vVertices[0] = last_x_inner;
			vVertices[1] = last_y_inner;
			vVertices[2] = -2.0 + z1;
			vVertices[3] = last_x;
			vVertices[4] = last_y;
			vVertices[5] = -2.0 + z1;
			vVertices[6] = x1 - x;
			vVertices[7] = y + y1;
			vVertices[8] = -2.0 + z1;
			vVertices[9] = x1 - x_inner;
			vVertices[10] = y_inner + y1;
			vVertices[11] = -2.0 + z1;
			vVertices[12] = vVertices[0];
			vVertices[13] = vVertices[1];
			vVertices[14] = -2.0 + z1;
			vVertices[15] = vVertices[6];
			vVertices[16] = vVertices[7];
			vVertices[17] = -2.0 + z1;
	      		glUseProgram ( userData->programObject2 );
			glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
			glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
			glEnableVertexAttribArray ( 0 );
			glUniform4fv( userData->colorLoc2, 1, colors );
			glDrawArrays ( GL_TRIANGLES, 0, 6 );
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
	}
}

void draw_circleFilled_f3_part_slow (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, float stop, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GLfloat vVertices[18];
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;
	float i = 0.0;
	float last_x = cos(start * DEG2RAD);
	float last_y = sin(start * DEG2RAD);
	for (i = start + 9; i < stop + 8; i += 9) {
		float temp1 = cos(i * DEG2RAD);
		float temp2 = sin(i * DEG2RAD);
		vVertices[0] = x1 + last_x * radius_inner;
		vVertices[1] = y1 + last_y * radius_inner;
		vVertices[2] = -2.0 + z1;
		vVertices[3] = x1 + last_x * radius;
		vVertices[4] = y1 + last_y * radius;
		vVertices[5] = -2.0 + z1;
		vVertices[6] = x1 + temp1 * radius;
		vVertices[7] = y1 + temp2 * radius;
		vVertices[8] = -2.0 + z1;
		vVertices[9] = x1 + temp1 * radius_inner;
		vVertices[10] = y1 + temp2 * radius_inner;
		vVertices[11] = -2.0 + z1;
		vVertices[12] = vVertices[0];
		vVertices[13] = vVertices[1];
		vVertices[14] = -2.0 + z1;
		vVertices[15] = vVertices[6];
		vVertices[16] = vVertices[7];
		vVertices[17] = -2.0 + z1;
      		glUseProgram ( userData->programObject2 );
		glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
		glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
		glEnableVertexAttribArray ( 0 );
		glUniform4fv( userData->colorLoc2, 1, colors );
		glDrawArrays ( GL_TRIANGLES, 0, 6 );
		last_x = temp1;
		last_y = temp2;
	}
}

void draw_box_f3c2b (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;

	GLfloat vVertices[] = {
		x1, y1, -2.0f + z1,  // Position 0
		x1, y2, -2.0f + z1,  // Position 1
		x2, y2, -2.0f + z1,   // Position 2
		x2, y1, -2.0f + z1,   // Position 3
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;

	glUseProgram ( userData->programObject2 );
	glUniformMatrix4fv( userData->mvpLoc2, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix2.m[0][0] );
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray ( 0 );
	glUniform4fv( userData->colorLoc2, 1, colors );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
}

void draw_graph_value (ESContext *esContext, float px1, float py1, float px2, float py2, float pz, uint8_t *data, int16_t len, int16_t pointer, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
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

void draw_trifan_f3 (ESContext *esContext, float *poly_array, uint16_t len, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
}

void resize_border (void) {
	glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, setup.screen_w - setup.screen_border_x, setup.screen_h - setup.screen_border_y);
}

void draw_update (ESContext *esContext) {
	ESMatrix modelview;
	UserData *userData = esContext->userData;

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
}

void draw_init (ESContext *esContext) {
	uint16_t n = 0;
	for (n = 0; n < MAX_TEXCACHE; n++) {
		TexCache[n].name[0] = 0;
		TexCache[n].texture = 0;
	}
	esInitContext(esContext);
	esCreateWindow(esContext, "GL-GCS", setup.screen_w, setup.screen_h, ES_WINDOW_RGB);
	if (! glesInit(esContext)) {
		return;
	}
	esRegisterDrawFunc(esContext, Draw);
	glClearDepthf(2.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void draw_exit (ESContext *esContext) {
#ifdef RPI_NO_X
//	esInitContext(esContext);
//	esContext->userData = &userData;
//	glDeleteProgram(userData->programObject);
//	free(esContext->userData);
	SDL_Log("bcm_host: exit\n");
	bcm_host_deinit();
#endif
	SDL_Log("texture-cache: clear\n");
	int16_t n = 0;
	for (n = 0; n < MAX_TEXCACHE; n++) {
		if (TexCache[n].name[0] != 0 && TexCache[n].texture != 0 ) {
			glDeleteTextures( 1, &TexCache[n].texture );
			TexCache[n].name[0] = 0;
		}
	}
	SDL_Quit();
}
