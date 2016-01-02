
#include <all.h>
#include <android_gles.h>
#include <SDL_opengles.h>
#include <vectorfont.h>

#define USE_VECTOR_FONTS

#ifdef USE_VECTOR_FONTS
#include <font.h>
#endif

#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#define GL_RGBA	0x1908
#define GL_BGR 0x80E0
#define GL_RGB 0x1907
#endif

static SDLTest_CommonState *state;
static SDL_GLContext *context = NULL;

SDL_Window *MainWindow = NULL;
SDL_GLContext MainGLcontext;
SDL_Surface *WinScreen = NULL;

TextureCache TexCache[MAX_TEXCACHE];
GLfloat colors[4] = {1.0f, 0.0f, 0.0f, 1.0f};
float aspect = 1.0;
float alt_zoom = 700.0;

uint8_t RB_Active = 0;
GLuint RB_texture;

void draw_texture_f3(ESContext *esContext, float x1, float y1, float x2, float y2, float z, GLuint texture);

void esTranslate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz) {
	glTranslatef(tx, ty, tz);
}

void esRotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	glRotatef(angle, x, y, -z);
}

void gl_exit(int rc) {
	int i;
	if (context != NULL) {
		for (i = 0; i < state->num_windows; i++) {
			if (context[i]) {
				SDL_GL_DeleteContext(context[i]);
			}
		}
		SDL_free(context);
	}
	SDLTest_CommonQuit(state);
	exit(rc);
}

/* gluPerspective from http://code.google.com/p/glues/source/checkout */

static void __gluMakeIdentityf(GLfloat m[16]) {
	m[0 + 4 * 0] = 1;
	m[0 + 4 * 1] = 0;
	m[0 + 4 * 2] = 0;
	m[0 + 4 * 3] = 0;
	m[1 + 4 * 0] = 0;
	m[1 + 4 * 1] = 1;
	m[1 + 4 * 2] = 0;
	m[1 + 4 * 3] = 0;
	m[2 + 4 * 0] = 0;
	m[2 + 4 * 1] = 0;
	m[2 + 4 * 2] = 1;
	m[2 + 4 * 3] = 0;
	m[3 + 4 * 0] = 0;
	m[3 + 4 * 1] = 0;
	m[3 + 4 * 2] = 0;
	m[3 + 4 * 3] = 1;
}

void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar) {
	GLfloat m[4][4];
	GLfloat sine, cotangent, deltaZ;
	GLfloat radians = (GLfloat)(fovy / 2.0f * PI / 180.0f);
	deltaZ = zFar - zNear;
	sine = (GLfloat)sin(radians);
	if ((deltaZ == 0.0f) || (sine == 0.0f) || (aspect == 0.0f)) {
		return;
	}
	cotangent = (GLfloat)(cos(radians) / sine);
	__gluMakeIdentityf(&m[0][0]);
	m[0][0] = cotangent / aspect;
	m[1][1] = cotangent;
	m[2][2] = -(zFar + zNear) / deltaZ;
	m[2][3] = -1.0f;
	m[3][2] = -2.0f * zNear * zFar / deltaZ;
	m[3][3] = 0;
	glMultMatrixf(&m[0][0]);
}

void gl_init(ESContext *esContext) {
	int i;
	int value;
	SDL_DisplayMode mode;
	int status;
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	state = SDLTest_CommonCreateState(NULL, SDL_INIT_VIDEO);
	if (!state) {
		gl_exit(2);
	}
	state->window_flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;
	state->gl_red_size = 5;
	state->gl_green_size = 5;
	state->gl_blue_size = 5;
	state->gl_depth_size = 16;
	state->gl_accelerated = 1;
	if (!SDLTest_CommonInit(state)) {
		gl_exit(2);
	}
	context = SDL_calloc(state->num_windows, sizeof(context));
	if (context == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Out of memory!\n");
		gl_exit(2);
	}
	for (i = 0; i < state->num_windows; i++) {
		context[i] = SDL_GL_CreateContext(state->windows[i]);
		if (!context[i]) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_GL_CreateContext(): %s\n", SDL_GetError());
			gl_exit(2);
		}
	}
	if (state->render_flags & SDL_RENDERER_PRESENTVSYNC) {
		SDL_GL_SetSwapInterval(1);
	} else {
		SDL_GL_SetSwapInterval(0);
	}
	SDL_GetCurrentDisplayMode(0, &mode);
	SDL_Log("Screen bpp: %d\n", SDL_BITSPERPIXEL(mode.format));
	SDL_Log("\n");
	SDL_Log("Vendor     : %s\n", glGetString(GL_VENDOR));
	SDL_Log("Renderer   : %s\n", glGetString(GL_RENDERER));
	SDL_Log("Version    : %s\n", glGetString(GL_VERSION));
	SDL_Log("Extensions : %s\n", glGetString(GL_EXTENSIONS));
	SDL_Log("\n");
	for (i = 0; i < state->num_windows; ++i) {
		status = SDL_GL_MakeCurrent(state->windows[i], context[i]);
		if (status) {
			SDL_Log("SDL_GL_MakeCurrent(): %s\n", SDL_GetError());
			continue;
		}
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		SDL_Log("Size       : %i x %i\n", state->window_w, state->window_h);
		state->window_w = mode.w;
		state->window_h = mode.h;
		setup.screen_w = state->window_w;
		setup.screen_h = state->window_h;
		esContext->width = setup.screen_w;
		esContext->height = setup.screen_h;
		if (setup.keep_ratio == 0.0) {
			aspect = (GLfloat)esContext->width / (GLfloat)esContext->height;
		} else {
			aspect = setup.keep_ratio;
		}
		glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, setup.screen_w - setup.screen_border_x, setup.screen_h - setup.screen_border_y);
		gluPerspective(53.0, aspect, 0.001, 7.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//		glShadeModel(GL_SMOOTH);
		//		glEnable(GL_POLYGON_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glShadeModel(GL_FLAT);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	SDL_GL_MakeCurrent(state->windows[0], context[0]);
	// Draw to Texture Buffer
	glGenTextures(1, &RB_texture);
	glBindTexture(GL_TEXTURE_2D, RB_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 0x80E1, 256, 256, 0, 0x80E1, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

int glExit(ESContext *esContext) {
	gl_exit(0);
}

void glResize(ESContext *esContext, int w, int h) {
	int i = 0;
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);
	w = mode.w;
	h = mode.h;
	SDL_Log("Resize     : %i x %i\n", w, h);
	for (i = 0; i < state->num_windows; ++i) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		state->window_w = w;
		state->window_h = h;
		setup.screen_w = state->window_w;
		setup.screen_h = state->window_h;
		esContext->width = setup.screen_w;
		esContext->height = setup.screen_h;
		if (setup.keep_ratio == 0.0) {
			aspect = (GLfloat)esContext->width / (GLfloat)esContext->height;
		} else {
			aspect = setup.keep_ratio;
		}
		glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, setup.screen_w - setup.screen_border_x, setup.screen_h - setup.screen_border_y);
		gluPerspective(53.0, aspect, 0.001, 7.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void object3d_free(Object3d *o3d) {
}

void object3d_draw(Object3d *o3d, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
}

void object3d_save_as_collada(Object3d *o3d, char *filename) {
}

void object3d_load(Object3d *o3d, char *filename) {
}

void object3d_load_data(Object3d *o3d, char *filename) {
}

void draw_surface_f3(ESContext *esContext, float x1, float y1, float x2, float y2, float z, float alpha, SDL_Surface *screen) {
	y1 = y1 * -1;
	y2 = y2 * -1;
	if (screen == NULL) {
		return;
	}
	GLuint texture;
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
		SDL_Log("warning: the image is not truecolor..  this will probably break\n");
		return;
	}
	GLfloat vVertices[] = {
		x1, y1, -2.0f + z,  // Position 0
		x1, y2, -2.0f + z,  // Position 1
		x2, y2, -2.0f + z,   // Position 2
		x2, y1, -2.0f + z,   // Position 3
	};
	GLfloat vTex[] = {
		0.0f,  0.0f,         // TexCoord 0
		0.0f,  1.0f,         // TexCoord 1
		1.0f,  1.0f,         // TexCoord 2
		1.0f,  0.0f          // TexCoord 3
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, screen->w, screen->h, 0, texture_format, GL_UNSIGNED_BYTE, screen->pixels);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0, 1.0, 1.0, 0.2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, vTex);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &texture);
}

uint8_t draw_target(void) {
	return RB_Active;
}

void draw_to_buffer(void) {
	if (RB_Active == 0) {
		RB_Active = 1;
		glPushMatrix();
		glScalef(256.0 / (float)setup.screen_w, 256.0 / (float)setup.screen_h, 1.0);
	}
}

void draw_to_screen(void) {
	if (RB_Active == 1) {
		RB_Active = 0;
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, RB_texture);
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, setup.screen_w / 2 - 128, setup.screen_h / 2 - 128, 256, 256);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void draw_buffer_to_screen(float x1, float y1, float x2, float y2, float z, float alpha) {
	ESContext *esContext;
	draw_texture_f3(esContext, x1, y1, x2, y2, z, RB_texture);
}

void draw_zylinder_f3(ESContext *esContext, float x1, float y1, float z1, float z2, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
}

int glInit(ESContext *esContext) {
	esContext->width = setup.screen_w;
	esContext->height = setup.screen_h;
	gl_init(esContext);
	WinScreen = state->windows[0];
	MainGLcontext = context[0];
	return GL_TRUE;
}

void draw_circlePointer_f3(ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	float x2 = x1 - cos(start * DEG2RAD) * radius;
	float y2 = y1 - sin(start * DEG2RAD) * radius;
	draw_line_f3(esContext, x1, y1, z1, x2, y2, z1, r, g, b, a);
	draw_circleFilled_f3(esContext, x1, y1, z1, radius_inner, r, g, b, a);
}

void draw_line_f3(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GLfloat vVertices[6];
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;
	vVertices[0] = x1;
	vVertices[1] = y1;
	vVertices[2] = -2.0 + z1;
	vVertices[3] = x2;
	vVertices[4] = y2;
	vVertices[5] = -2.0 + z2;
	GLushort indices[] = { 0, 1 };
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, indices);
}

void draw_circle_f3(ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GLfloat vVertices[3 * 360];
	y1 = y1 * -1;
	uint16_t ii = 0;
	float num_segments = radius * 300.0;
	if (num_segments < 100.0) {
		num_segments = 100.0;
	} else if (num_segments > 360.0) {
		num_segments = 360.0;
	}
	if (num_segments > 360.0) {
		num_segments = 360.0;
	}
	float theta = 2 * PI / num_segments;
	float tangetial_factor = tanf(theta);
	float radial_factor = cosf(theta);
	float x = radius;
	float y = 0;
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	for (ii = 0; ii < num_segments; ii++) {
		vVertices[0 + ii * 3] = x + x1;
		vVertices[1 + ii * 3] = y + y1;
		vVertices[2 + ii * 3] = -2.0 + z1;
		float tx = -y;
		float ty = x;
		x += tx * tangetial_factor;
		y += ty * tangetial_factor;
		x *= radial_factor;
		y *= radial_factor;
	}
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_LINE_LOOP, 0, num_segments);
}

void draw_circle_f3_slow(ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
}

void draw_circleFilled_f3(ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	GLfloat vVertices[3 * 180 + 3];
	y1 = y1 * -1;
	uint16_t ii = 0;
	float num_segments = radius * 150.0;
	if (num_segments < 100.0) {
		num_segments = 100.0;
	} else if (num_segments > 180.0) {
		num_segments = 180.0;
	}
	if (num_segments > 180.0) {
		num_segments = 180.0;
	}
	float theta = 2 * PI / num_segments;
	float tangetial_factor = tanf(theta);
	float radial_factor = cosf(theta);
	float x = radius;
	float y = 0;
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	vVertices[0 + ii * 3] = x1;
	vVertices[1 + ii * 3] = y1;
	vVertices[2 + ii * 3] = -2.0 + z1;
	for (ii = 0; ii < num_segments; ii++) {
		vVertices[0 + ii * 3] = x + x1;
		vVertices[1 + ii * 3] = y + y1;
		vVertices[2 + ii * 3] = -2.0 + z1;
		float tx = -y;
		float ty = x;
		x += tx * tangetial_factor;
		y += ty * tangetial_factor;
		x *= radial_factor;
		y *= radial_factor;
	}
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments);
	draw_circle_f3(esContext, x1, y1 * -1, z1, radius, r, g, b, a);
}

void draw_circleFilled_f3_slow(ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
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
		GLushort indices[] = { 0, 1, 2 };
		glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, indices);
	}
}

void draw_box_f3(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
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
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void draw_box_f3c2(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2) {
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
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void draw_tria_f3(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
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
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, indices);
}

void draw_triaFilled_f3(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;
	y3 = y3 * -1;
	GLfloat vVertices[] = {
		x1, y1, -2.0f + z1,  // Position 0
		x2, y2, -2.0f + z2,  // Position 1
		x3, y3, -2.0f + z3,   // Position 2
	};
	GLushort indices[] = { 0, 1, 2 };
	colors[0] = (float)r / 255;
	colors[1] = (float)g / 255;
	colors[2] = (float)b / 255;
	colors[3] = (float)a / 255;
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, indices);
}

void draw_image_srtm(ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file, float lat1, float lon1, float lat2, float lon2, float alpha0, float alpha1, float alpha2,
					 float grid) {
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
			glDeleteTextures(1, &TexCache[tex_num].texture);
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
			//			SDL_Log("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ((TexCache[tex_num].texture = loadImage(file)) != 0) {
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
	uint8_t subtiles = 4;
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
			GLfloat vVertices[] = {
				tx1, ty1, -2.0f + z1,  // Position 0
				tx1, ty2, -2.0f + z4,  // Position 1
				tx2, ty2, -2.0f + z3,   // Position 2
				tx2, ty1, -2.0f + z2,   // Position 3
			};
			GLfloat vTex[] = {
				tex1, tey1,         // TexCoord 3
				tex1, tey2,         // TexCoord 0
				tex2, tey2,         // TexCoord 1
				tex2, tey1,         // TexCoord 2
			};
			GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
			glVertexPointer(3, GL_FLOAT, 0, vVertices);
			glEnableClientState(GL_VERTEX_ARRAY);
			if (TexCache[tex_num].texture != 0) {
				TexCache[tex_num].atime = time(0);
				glEnable(GL_TEXTURE_2D);
				glColor4f(1.0, 1.0, 1.0, 0.2);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, TexCache[tex_num].texture);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, 0, vTex);
				glVertexPointer(3, GL_FLOAT, 0, vVertices);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glDisable(GL_TEXTURE_2D);
			}
			if (alpha1 > 0.0 && ((float)_alt1 > ModelData[ModelActive].p_alt || (float)_alt2 > ModelData[ModelActive].p_alt || (float)_alt3 > ModelData[ModelActive].p_alt ||
								 (float)_alt4 > ModelData[ModelActive].p_alt)) {
				glColor4f(255.0, 0.0, 0.0, alpha1);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
			} else if (alpha2 > 0.0) {
				glColor4f(0.0, 255.0, 0.0, alpha2);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
			}
			if (grid > 0.0) {
				glColor4f(255.0, 255.0, 255.0, grid);
				glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_SHORT, indices);
			}
		}
	}
}

void draw_image_f12(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, char *file) {
}

void draw_image_f3(ESContext *esContext, float x1, float y1, float x2, float y2, float z, char *file) {
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
			glDeleteTextures(1, &TexCache[tex_num].texture);
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
			//			SDL_Log("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ((TexCache[tex_num].texture = loadImage(file)) != 0) {
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
		GLfloat vVertices[] = {
			x1, y1, -2.0f + z,  // Position 0
			x1, y2, -2.0f + z,  // Position 1
			x2, y2, -2.0f + z,   // Position 2
			x2, y1, -2.0f + z,   // Position 3
		};
		GLfloat vTex[] = {
			0.0f,  0.0f,         // TexCoord 0
			0.0f,  1.0f,         // TexCoord 1
			1.0f,  1.0f,         // TexCoord 2
			1.0f,  0.0f          // TexCoord 3
		};
		GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0, 1.0, 1.0, 0.2);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexCache[tex_num].texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, vTex);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
}

void draw_texture_f3(ESContext *esContext, float x1, float y1, float x2, float y2, float z, GLuint texture) {
	y1 = y1 * -1;
	y2 = y2 * -1;
	if (texture != 0) {
		GLfloat vVertices[] = {
			x1, y1, -2.0f + z,  // Position 0
			x1, y2, -2.0f + z,  // Position 1
			x2, y2, -2.0f + z,   // Position 2
			x2, y1, -2.0f + z,   // Position 3
		};
		GLfloat vTex[] = {
			0.0f,  1.0f,         // TexCoord 0
			0.0f,  0.0f,         // TexCoord 1
			1.0f,  0.0f,         // TexCoord 2
			1.0f,  1.0f          // TexCoord 3
		};
		GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, vTex);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
}

#ifdef USE_VECTOR_FONTS
int output_char_gl (char c, float x, float y, float z, float s, GLfloat *vVertices, int ii) {
	int n = c - 32;
	if (c >= 32 && c <= 126) {
		int pn = 0;
		int px = 0;
		int py = 0;
		int last_px = 0;
		int last_py = 0;
		y -= s * 1.2;
		x += s * 0.7;
		s /= 42.0;
		x -= ((float)fontdata[(int)setup.font][n][1] * s) / 2.0;
		for (pn = 2; pn < 112; pn += 2) {
			px = fontdata[(int)setup.font][n][pn];
			py = fontdata[(int)setup.font][n][pn + 1];
			if (pn != 2 && px != -1 && last_px != -1) {
//				glVertex3f(x + (float)last_px * s, y + (float)last_py * s, z);
//				glVertex3f(x + (float)px * s, y + (float)py * s, z);
				vVertices[0 + ii * 6] = x + (float)last_px * s;
				vVertices[1 + ii * 6] = y + (float)last_py * s;
				vVertices[2 + ii * 6] = -2.0 + z;
				vVertices[3 + ii * 6] = x + (float)px * s;
				vVertices[4 + ii * 6] = y + (float)py * s;
				vVertices[5 + ii * 6] = -2.0 + z;
				ii++;
			}
			last_px = px;
			last_py = py;
		}
		return ii;
	}
	return 0.0;
}
#endif

inline void draw_char_f3_fast(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, int8_t tex_num, char num) {
	UserData *userData = esContext->userData;
	int nnn = 0;
	GLfloat vVertices[20];
	GLfloat vTex[20];
	GLushort indices[] = {0, 1, 2, 0, 2, 3};
	y1 = y1 * -1;
	y2 = y2 * -1;
	if (num == '\n' || num == '\r') {
		return;
	}
	vVertices[0] = x1;
	vVertices[1] = y1;
	vVertices[2] = -2.0 + z1;
	vVertices[3] = x1;
	vVertices[4] = y2;
	vVertices[5] = -2.0 + z1;
	vVertices[6] = x2;
	vVertices[7] = y2;
	vVertices[8] = -2.0 + z1;
	vVertices[9] = x2;
	vVertices[10] = y1;
	vVertices[11] = -2.0 + z1;
	float tpos_x = (float)(num % 16) / 16;
	float tpos_y = (float)(num / 16) / 16;
	if (num < 0) {
		nnn = num + 256;
		tpos_x = (float)(nnn % 16) / 16;
		tpos_y = (float)(nnn / 16) / 16;
	}
	vTex[0] = tpos_x;
	vTex[1] = tpos_y + 0.005;
	vTex[2] = tpos_x;
	vTex[3] = tpos_y + 0.0625;
	vTex[4] = tpos_x + 0.0625;
	vTex[5] = tpos_y + 0.0625;
	vTex[6] = tpos_x + 0.0625;
	vTex[7] = tpos_y + 0.005;
	glTexCoordPointer(2, GL_FLOAT, 0, vTex);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void draw_text_f3_fast(ESContext *esContext, float x1, float y1, float z1, float w, float h, char *file, char *text) {
	UserData *userData = esContext->userData;
	int16_t n = 0;
#ifdef USE_VECTOR_FONTS
	int ii = 0;
	GLfloat *vVertices = NULL;
	vVertices = malloc(112 * 6 * sizeof(GLfloat));
	if (h < 0.03) {
		glLineWidth(1);
	} else {
		glLineWidth(2);
	}
	if (strcmp(file, FONT_GREEN_BG) == 0) {
		glColor4f(0.0, 1.0, 0.0, 1.0);
	} else if (strcmp(file, FONT_TRANS) == 0) {
		glColor4f(1.0, 1.0, 1.0, 0.75);
	} else if (strcmp(file, FONT_BLACK_BG) == 0) {
		glColor4f(0.0, 0.0, 0.0, 1.0);
	} else if (strcmp(file, FONT_WHITE) == 0) {
		glColor4f(1.0, 1.0, 1.0, 1.0);
	} else if (strcmp(file, FONT_GREEN) == 0) {
		glColor4f(0.0, 1.0, 0.0, 1.0);
	} else if (strcmp(file, FONT_PINK) == 0) {
		glColor4f(1.0, 0.0, 0.0, 1.0);
	} else {
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
//	glBegin(GL_LINES);
	for (n = 0; n < strlen(text); n++) {
		ii = output_char_gl(text[n], x1 + n * ((float)w * 0.6), -y1, z1, h, vVertices, ii);
		vVertices = realloc(vVertices, (ii + 112) * 6 * sizeof(GLfloat));
	}
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glDrawArrays(GL_LINES, 0, ii * 2);
	free(vVertices);
	glLineWidth(1);
//	glEnd();
#else
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
			glDeleteTextures(1, &TexCache[tex_num].texture);
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num > 0) {
			//			SDL_Log("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ((TexCache[tex_num].texture = loadImage(file)) != 0) {
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
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, TexCache[tex_num].texture);
		for (n = 0; n < strlen(text); n++) {
			draw_char_f3_fast(esContext, x1 + n * ((float)w * 0.6), y1, z1, x1 + n * ((float)w * 0.6) + w, y1 + h, z1, TexCache[tex_num].texture, text[n]);
		}
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
#endif
}

void draw_char_f3(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, char *file, char num) {
}

void draw_rect_f3(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	draw_line_f3(esContext, x1, y1, z1, x2, y1, z1, r, g, b, a);
	draw_line_f3(esContext, x2, y1, z1, x2, y2, z1, r, g, b, a);
	draw_line_f3(esContext, x2, y2, z1, x1, y2, z1, r, g, b, a);
	draw_line_f3(esContext, x1, y2, z1, x1, y1, z1, r, g, b, a);
}

void draw_circleFilled_f3_part(ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, float stop, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
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
	float theta = 2 * PI / num_segments;
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
			GLushort indices[] = { 0, 1, 2, 3, 4, 5 };
			glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
			glVertexPointer(3, GL_FLOAT, 0, vVertices);
			glEnableClientState(GL_VERTEX_ARRAY);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
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

void draw_circleFilled_f3_part_slow(ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, float stop, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
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
		GLushort indices[] = { 0, 1, 2, 3, 4, 5 };
		glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
		last_x = temp1;
		last_y = temp2;
	}
}

void draw_box_f3c2b(ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2) {
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
	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void draw_graph_value(ESContext *esContext, float px1, float py1, float px2, float py2, float pz, uint8_t *data, int16_t len, int16_t pointer, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
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

void draw_trifan_f3(ESContext *esContext, float *poly_array, uint16_t len, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
}

void resize_border(void) {
	glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, setup.screen_w - setup.screen_border_x, setup.screen_h - setup.screen_border_y);
}

void draw_update(ESContext *esContext) {
	float cPlaneLeft[4] = { -1.0, 0.0, 0.0, 0.0};
	float cPlaneRight[4] = {1.0, 0.0, 0.0, 0.0};
	if (setup.side_by_side == 1) {
		static int n = 0;
		if (n == 0) {
#ifndef SDLGL
			esMatrixLoadIdentity(&modelview);
			esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
#else
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
#endif
			glClipPlanef(GL_CLIP_PLANE1, cPlaneRight);
			glEnable(GL_CLIP_PLANE1);
			glScalef(0.5, 1.0, 1.0);
			glTranslatef(1.0 * aspect, 0.0, 0.0);
			n = 1;
		} else {
			SDL_GL_SwapWindow(state->windows[0]);
#ifndef SDLGL
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			esMatrixLoadIdentity(&modelview);
			esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
#else
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
			glClipPlanef(GL_CLIP_PLANE1, cPlaneLeft);
			glEnable(GL_CLIP_PLANE1);
			glScalef(0.5, 1.0, 1.0);
			glTranslatef(-1.0 * aspect, 0.0, 0.0);
			n = 0;
		}
	} else {
		SDL_GL_SwapWindow(state->windows[0]);
#ifndef SDLGL
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		esMatrixLoadIdentity(&modelview);
		esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
#else
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
	}
}

void draw_init(ESContext *esContext) {
	uint16_t n = 0;
	for (n = 0; n < MAX_TEXCACHE; n++) {
		TexCache[n].name[0] = 0;
		TexCache[n].texture = 0;
	}
	glInit(esContext);
}

void draw_exit(ESContext *esContext) {
#ifdef SDL2
	SDL_DestroyWindow(MainWindow);
#endif
	glDeleteTextures(1, &RB_texture);
	glExit(esContext);
	SDL_Log("texture-cache: clear\n");
	int16_t n = 0;
	for (n = 0; n < MAX_TEXCACHE; n++) {
		if (TexCache[n].name[0] != 0 && TexCache[n].texture != 0) {
			glDeleteTextures(1, &TexCache[n].texture);
			TexCache[n].name[0] = 0;
		}
	}
	SDL_Quit();
}
