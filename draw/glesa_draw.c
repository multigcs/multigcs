
#include <all.h>

#include "android_gles.h"
#include "SDL_opengles.h"

static SDLTest_CommonState *state;
static SDL_GLContext *context = NULL;

SDL_Window *MainWindow = NULL;
SDL_GLContext MainGLcontext;
SDL_Surface *WinScreen = NULL;

void gl_update (void);

void esTranslate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz) {
	glTranslatef(tx, ty, tz);
}

void esRotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	glRotatef(angle, x, y, -z);
}


void RenderTestDraw (void) {
	static GLubyte color[8][4] = { {255, 0, 0, 0},
		{255, 0, 0, 255},
		{0, 255, 0, 255},
		{0, 255, 0, 255},
		{0, 255, 0, 255},
		{255, 255, 255, 255},
		{255, 0, 255, 255},
		{0, 0, 255, 255}
	};
	static GLfloat cube[8][3] = { {0.5, 0.5, -0.5},
		{0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, 0.5f, -0.5f},
		{-0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		{-0.5f, -0.5f, 0.5f}
	};
	static GLubyte indices[36] = { 0, 3, 4,
		4, 5, 0,
		0, 5, 6,
		6, 1, 0,
		6, 7, 2,
		2, 1, 6,
		7, 4, 3,
		3, 2, 7,
		5, 4, 7,
		7, 6, 5,
		2, 3, 1,
		3, 0, 1
	};

//	glClearColor(0.0, 0.0, 0.0, 1.0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	glMatrixMode(GL_MODELVIEW);
//	glRotatef(5.0, 1.0, 1.0, 1.0);

	glColorPointer(4, GL_UNSIGNED_BYTE, 0, color);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cube);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
}

void RenderTest (void) {
	while (1) {
		RenderTestDraw();
		gl_update();
	}
}


void gl_exit (int rc) {
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

#define __glPi 3.14159265358979323846

static void __gluMakeIdentityf (GLfloat m[16]) {
    m[0+4*0] = 1; m[0+4*1] = 0; m[0+4*2] = 0; m[0+4*3] = 0;
    m[1+4*0] = 0; m[1+4*1] = 1; m[1+4*2] = 0; m[1+4*3] = 0;
    m[2+4*0] = 0; m[2+4*1] = 0; m[2+4*2] = 1; m[2+4*3] = 0;
    m[3+4*0] = 0; m[3+4*1] = 0; m[3+4*2] = 0; m[3+4*3] = 1;
}

void gluPerspective (GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar) {
    GLfloat m[4][4];
    GLfloat sine, cotangent, deltaZ;
    GLfloat radians=(GLfloat)(fovy/2.0f*__glPi/180.0f);

    deltaZ=zFar-zNear;
    sine=(GLfloat)sin(radians);
    if ((deltaZ==0.0f) || (sine==0.0f) || (aspect==0.0f))
    {
        return;
    }
    cotangent=(GLfloat)(cos(radians)/sine);

    __gluMakeIdentityf(&m[0][0]);
    m[0][0] = cotangent / aspect;
    m[1][1] = cotangent;
    m[2][2] = -(zFar + zNear) / deltaZ;
    m[2][3] = -1.0f;
    m[3][2] = -2.0f * zNear * zFar / deltaZ;
    m[3][3] = 0;
    glMultMatrixf(&m[0][0]);
}


void gl_init (void) {
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
	state->gl_accelerated=1;
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
		float aspectAdjust;
		status = SDL_GL_MakeCurrent(state->windows[i], context[i]);
		if (status) {
			SDL_Log("SDL_GL_MakeCurrent(): %s\n", SDL_GetError());
			continue;
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		state->window_w = 1205;
		state->window_h = 800;
		aspect = (GLfloat)state->window_w / (GLfloat)state->window_h;

		aspectAdjust = 1.0 / ((float)state->window_w / state->window_h);
		glOrthof(-1.5, 1.5, -1.5 * aspectAdjust, 1.5 * aspectAdjust, -20.0, 20.0);

//		glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, state->window_w - setup.screen_border_x, state->window_h - setup.screen_border_y);
//		gluPerspective(53.0, aspect, 0.001, 7.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

//		glClearDepth(1.0);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);

		glEnable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	}
	SDL_GL_MakeCurrent(state->windows[0], context[0]);

	glMatrixMode(GL_MODELVIEW);
//	glRotatef(-90.0, 0.0, 0.0, 1.0);

//	glTranslatef(1.0, 0.0, 0.0);

}

void gl_update (void) {
	SDL_GL_SwapWindow(state->windows[0]);
}

int glExit ( ESContext *esContext ) {
	gl_exit(0);
}

void glResize (ESContext *esContext, int w, int h) {
//	state->window_w = w;
//	state->window_w = h;
//	setup.screen_w = state->window_w;
//	setup.screen_h = state->window_h;
//	esContext->width = setup.screen_w;
//	esContext->height = setup.screen_h;
//	aspect = (GLfloat)state->window_w / (GLfloat)state->window_h;
//	glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, setup.screen_w - setup.screen_border_x, setup.screen_h - setup.screen_border_y);
//	gluPerspective(53.0, aspect, 0.001, 7.0);
}

uint8_t draw_target (void) {
	return 0;
}

void object3d_free (Object3d *o3d) {
}

void object3d_draw (Object3d *o3d, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
}

void object3d_save_as_collada (Object3d *o3d, char *filename) {
}

void object3d_load (Object3d *o3d, char *filename) {
}

void object3d_load_data (Object3d *o3d, char *filename) {
}

void draw_surface_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, SDL_Surface *screen) {
}

void draw_to_buffer (void) {
}

void draw_to_screen (void) {
}

void draw_buffer_to_screen (float x1, float y1, float x2, float y2, float z, float alpha) {
}

void draw_zylinder_f3 (ESContext *esContext, float x1, float y1, float z1, float z2, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
}

int glInit ( ESContext *esContext ) {

	esContext->width = setup.screen_w;
	esContext->height = setup.screen_h;

	gl_init();

	WinScreen = state->windows[0];
	MainGLcontext = context[0];

	setup.screen_w = state->window_w;
	setup.screen_h = state->window_h;
	esContext->width = setup.screen_w;
	esContext->height = setup.screen_h;

	return GL_TRUE;
}



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

	vVertices[0] = x1;
	vVertices[1] = y1;
	vVertices[2] = z1;
	vVertices[3] = x2;
	vVertices[4] = y2;
	vVertices[5] = z2;

	GLushort indices[] = { 0, 1 };

	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, indices);

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
		vVertices[2] = z1;
		vVertices[3] = last_x;
		vVertices[4] = last_y;
		vVertices[5] = z1;

		vVertices[6] = x + x1;
		vVertices[7] = y + y1;
		vVertices[8] = z1;

		GLushort indices[] = { 0, 1, 2 };

		glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(GL_LINES, 3, GL_UNSIGNED_SHORT, indices);
	

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
		vVertices[2] = z1;
		vVertices[3] = x1 + cos(i * DEG2RAD) * radius;
		vVertices[4] = y1 + sin(i * DEG2RAD) * radius;
		vVertices[5] = z1;
		vVertices[6] = x1 + cos((i + step) * DEG2RAD) * radius;
		vVertices[7] = y1 + sin((i + step) * DEG2RAD) * radius;
		vVertices[8] = z1;

		GLushort indices[] = { 0, 1, 2 };

		glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(GL_LINES, 3, GL_UNSIGNED_SHORT, indices);
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
		vVertices[2] = z1;
		vVertices[3] = last_x;
		vVertices[4] = last_y;
		vVertices[5] = z1;
		vVertices[6] = x + x1;
		vVertices[7] = y + y1;
		vVertices[8] = z1;

		GLushort indices[] = { 0, 1, 2 };

		glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, indices);

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
		vVertices[2] = z1;
		vVertices[3] = x1 + cos(i * DEG2RAD) * radius;
		vVertices[4] = y1 + sin(i * DEG2RAD) * radius;
		vVertices[5] = z1;
		vVertices[6] = x1 + cos((i + step) * DEG2RAD) * radius;
		vVertices[7] = y1 + sin((i + step) * DEG2RAD) * radius;
		vVertices[8] = z1;

		GLushort indices[] = { 0, 1, 2 };

		glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, indices);
	}
}

void draw_box_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;

	GLfloat vVertices[] = {
		x1, y1, z1,  // Position 0
		x1, y2, z1,  // Position 1
		x2, y2, z1,   // Position 2
		x2, y1, z1,   // Position 3
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void draw_box_f3c2 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;

	GLfloat vVertices[] = {
		x1, y1, z1,  // Position 0
		x1, y2, z1,  // Position 1
		x2, y2, z1,   // Position 2
		x2, y1, z1,   // Position 3
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void draw_tria_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;
	y3 = y3 * -1;

	GLfloat vVertices[] = {
		x1, y1, z1,  // Position 0
		x2, y2, z2,  // Position 1
		x3, y3, z3,   // Position 2
	};
	GLushort indices[] = { 0, 1, 2, 0 };

	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, indices);
}

void draw_triaFilled_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;
	y3 = y3 * -1;

	GLfloat vVertices[] = {
		x1, y1, z1,  // Position 0
		x2, y2, z2,  // Position 1
		x3, y3, z3,   // Position 2
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
			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
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

		//glUseProgram(userData->programObject);
		glActiveTexture(GL_TEXTURE0);

		GLfloat vVertices[] = {
			tx1, ty1, z1,  // Position 0
			tex1, tey1,          // TexCoord 3
			tx1, ty2, z4,  // Position 1
			tex1,  tey2,         // TexCoord 0 
			tx2, ty2, z3,   // Position 2
			tex2,  tey2,         // TexCoord 1
			tx2, ty1, z2,   // Position 3
			tex2, tey1,         // TexCoord 2
		};
		GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

		//glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices );
		//glEnableVertexAttribArray ( userData->positionLoc );
		//glUniformMatrix4fv( userData->mvpLoc, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix.m[0][0] );

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		//glVertexAttribPointer ( userData->texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );
		//glEnableVertexAttribArray ( userData->texCoordLoc );
//		glBindTexture (GL_TEXTURE_2D, TexCache[tex_num].texture );
		//glUniform1i ( userData->samplerLoc, 0 );
		//glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );


			}
		}

	}
}

void draw_image_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, char *file) {
return;
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
			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
			if ( (TexCache[tex_num].texture = loadImage(file)) != 0 ) { 
				strncpy(TexCache[tex_num].name, file, 1023);
				TexCache[tex_num].atime = time(0);
			} else {
				printf("could not load image: %s\n", file);
				if (strstr(file, "/MAPS/") > 0) {
					unlink(file);
				}
			}    
		}
	}
	if (TexCache[tex_num].texture != 0) {
		TexCache[tex_num].atime = time(0);
//		printf("# %s = %i\n", TexCache[tex_num].name, TexCache[tex_num].texture);
		//glUseProgram(userData->programObject);

		GLfloat vVertices[] = {
			x1, y1, z,  // Position 0
			x1, y2, z,  // Position 1
			x2, y2, z,   // Position 2
			x2, y1, z,   // Position 3
		};
		GLfloat vTex[] = {
			0.0f,  0.0f,         // TexCoord 0 
			0.0f,  1.0f,         // TexCoord 1
			1.0f,  1.0f,         // TexCoord 2
			1.0f,  0.0f          // TexCoord 3
		};
		GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

		glColor4f(1.0, 0.0, 0.0, 1.0);

		glActiveTexture(GL_TEXTURE0);



//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glEnable(GL_BLEND);

		glBindTexture(GL_TEXTURE_2D, TexCache[tex_num].texture);

		glEnableClientState(GL_VERTEX_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, vTex);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

	}
}

inline void draw_char_f3_fast (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, int8_t tex_num, char num) {
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
	vVertices[2] = z1;
	vVertices[3] = x1;
	vVertices[4] = y2;
	vVertices[5] = z1;
	vVertices[6] = x2;
	vVertices[7] = y2;
	vVertices[8] = z1;
	vVertices[9] = x2;
	vVertices[10] = y1;
	vVertices[11] = z1;

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


	glColor4f(0.0, 1.0, 0.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexCache[tex_num].texture);
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, vTex);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, indices);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

}

void draw_text_f3_fast (ESContext *esContext, float x1, float y1, float z1, float w, float h, char *file, char *text) {



static int simplex[95][112] = {
    0,16, /* Ascii 32 */
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,10, /* Ascii 33 */
    5,21, 5, 7,-1,-1, 5, 2, 4, 1, 5, 0, 6, 1, 5, 2,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,16, /* Ascii 34 */
    4,21, 4,14,-1,-1,12,21,12,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,21, /* Ascii 35 */
   11,25, 4,-7,-1,-1,17,25,10,-7,-1,-1, 4,12,18,12,-1,-1, 3, 6,17, 6,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   26,20, /* Ascii 36 */
    8,25, 8,-4,-1,-1,12,25,12,-4,-1,-1,17,18,15,20,12,21, 8,21, 5,20, 3,
   18, 3,16, 4,14, 5,13, 7,12,13,10,15, 9,16, 8,17, 6,17, 3,15, 1,12, 0,
    8, 0, 5, 1, 3, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   31,24, /* Ascii 37 */
   21,21, 3, 0,-1,-1, 8,21,10,19,10,17, 9,15, 7,14, 5,14, 3,16, 3,18, 4,
   20, 6,21, 8,21,10,20,13,19,16,19,19,20,21,21,-1,-1,17, 7,15, 6,14, 4,
   14, 2,16, 0,18, 0,20, 1,21, 3,21, 5,19, 7,17, 7,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   34,26, /* Ascii 38 */
   23,12,23,13,22,14,21,14,20,13,19,11,17, 6,15, 3,13, 1,11, 0, 7, 0, 5,
    1, 4, 2, 3, 4, 3, 6, 4, 8, 5, 9,12,13,13,14,14,16,14,18,13,20,11,21,
    9,20, 8,18, 8,16, 9,13,11,10,16, 3,18, 1,20, 0,22, 0,23, 1,23, 2,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    7,10, /* Ascii 39 */
    5,19, 4,20, 5,21, 6,20, 6,18, 5,16, 4,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,14, /* Ascii 40 */
   11,25, 9,23, 7,20, 5,16, 4,11, 4, 7, 5, 2, 7,-2, 9,-5,11,-7,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,14, /* Ascii 41 */
    3,25, 5,23, 7,20, 9,16,10,11,10, 7, 9, 2, 7,-2, 5,-5, 3,-7,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,16, /* Ascii 42 */
    8,21, 8, 9,-1,-1, 3,18,13,12,-1,-1,13,18, 3,12,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,26, /* Ascii 43 */
   13,18,13, 0,-1,-1, 4, 9,22, 9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,10, /* Ascii 44 */
    6, 1, 5, 0, 4, 1, 5, 2, 6, 1, 6,-1, 5,-3, 4,-4,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2,26, /* Ascii 45 */
    4, 9,22, 9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,10, /* Ascii 46 */
    5, 2, 4, 1, 5, 0, 6, 1, 5, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2,22, /* Ascii 47 */
   20,25, 2,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,20, /* Ascii 48 */
    9,21, 6,20, 4,17, 3,12, 3, 9, 4, 4, 6, 1, 9, 0,11, 0,14, 1,16, 4,17,
    9,17,12,16,17,14,20,11,21, 9,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    4,20, /* Ascii 49 */
    6,17, 8,18,11,21,11, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   14,20, /* Ascii 50 */
    4,16, 4,17, 5,19, 6,20, 8,21,12,21,14,20,15,19,16,17,16,15,15,13,13,
   10, 3, 0,17, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   15,20, /* Ascii 51 */
    5,21,16,21,10,13,13,13,15,12,16,11,17, 8,17, 6,16, 3,14, 1,11, 0, 8,
    0, 5, 1, 4, 2, 3, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    6,20, /* Ascii 52 */
   13,21, 3, 7,18, 7,-1,-1,13,21,13, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,20, /* Ascii 53 */
   15,21, 5,21, 4,12, 5,13, 8,14,11,14,14,13,16,11,17, 8,17, 6,16, 3,14,
    1,11, 0, 8, 0, 5, 1, 4, 2, 3, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   23,20, /* Ascii 54 */
   16,18,15,20,12,21,10,21, 7,20, 5,17, 4,12, 4, 7, 5, 3, 7, 1,10, 0,11,
    0,14, 1,16, 3,17, 6,17, 7,16,10,14,12,11,13,10,13, 7,12, 5,10, 4, 7,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,20, /* Ascii 55 */
   17,21, 7, 0,-1,-1, 3,21,17,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   29,20, /* Ascii 56 */
    8,21, 5,20, 4,18, 4,16, 5,14, 7,13,11,12,14,11,16, 9,17, 7,17, 4,16,
    2,15, 1,12, 0, 8, 0, 5, 1, 4, 2, 3, 4, 3, 7, 4, 9, 6,11, 9,12,13,13,
   15,14,16,16,16,18,15,20,12,21, 8,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   23,20, /* Ascii 57 */
   16,14,15,11,13, 9,10, 8, 9, 8, 6, 9, 4,11, 3,14, 3,15, 4,18, 6,20, 9,
   21,10,21,13,20,15,18,16,14,16, 9,15, 4,13, 1,10, 0, 8, 0, 5, 1, 4, 3,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,10, /* Ascii 58 */
    5,14, 4,13, 5,12, 6,13, 5,14,-1,-1, 5, 2, 4, 1, 5, 0, 6, 1, 5, 2,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   14,10, /* Ascii 59 */
    5,14, 4,13, 5,12, 6,13, 5,14,-1,-1, 6, 1, 5, 0, 4, 1, 5, 2, 6, 1, 6,
   -1, 5,-3, 4,-4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    3,24, /* Ascii 60 */
   20,18, 4, 9,20, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,26, /* Ascii 61 */
    4,12,22,12,-1,-1, 4, 6,22, 6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    3,24, /* Ascii 62 */
    4,18,20, 9, 4, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   20,18, /* Ascii 63 */
    3,16, 3,17, 4,19, 5,20, 7,21,11,21,13,20,14,19,15,17,15,15,14,13,13,
   12, 9,10, 9, 7,-1,-1, 9, 2, 8, 1, 9, 0,10, 1, 9, 2,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   55,27, /* Ascii 64 */
   18,13,17,15,15,16,12,16,10,15, 9,14, 8,11, 8, 8, 9, 6,11, 5,14, 5,16,
    6,17, 8,-1,-1,12,16,10,14, 9,11, 9, 8,10, 6,11, 5,-1,-1,18,16,17, 8,
   17, 6,19, 5,21, 5,23, 7,24,10,24,12,23,15,22,17,20,19,18,20,15,21,12,
   21, 9,20, 7,19, 5,17, 4,15, 3,12, 3, 9, 4, 6, 5, 4, 7, 2, 9, 1,12, 0,
   15, 0,18, 1,20, 2,21, 3,-1,-1,19,16,18, 8,18, 6,19, 5,
    8,18, /* Ascii 65 */
    9,21, 1, 0,-1,-1, 9,21,17, 0,-1,-1, 4, 7,14, 7,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   23,21, /* Ascii 66 */
    4,21, 4, 0,-1,-1, 4,21,13,21,16,20,17,19,18,17,18,15,17,13,16,12,13,
   11,-1,-1, 4,11,13,11,16,10,17, 9,18, 7,18, 4,17, 2,16, 1,13, 0, 4, 0,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   18,21, /* Ascii 67 */
   18,16,17,18,15,20,13,21, 9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5,
    3, 7, 1, 9, 0,13, 0,15, 1,17, 3,18, 5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   15,21, /* Ascii 68 */
    4,21, 4, 0,-1,-1, 4,21,11,21,14,20,16,18,17,16,18,13,18, 8,17, 5,16,
    3,14, 1,11, 0, 4, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,19, /* Ascii 69 */
    4,21, 4, 0,-1,-1, 4,21,17,21,-1,-1, 4,11,12,11,-1,-1, 4, 0,17, 0,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,18, /* Ascii 70 */
    4,21, 4, 0,-1,-1, 4,21,17,21,-1,-1, 4,11,12,11,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   22,21, /* Ascii 71 */
   18,16,17,18,15,20,13,21, 9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5,
    3, 7, 1, 9, 0,13, 0,15, 1,17, 3,18, 5,18, 8,-1,-1,13, 8,18, 8,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,22, /* Ascii 72 */
    4,21, 4, 0,-1,-1,18,21,18, 0,-1,-1, 4,11,18,11,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2, 8, /* Ascii 73 */
    4,21, 4, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,16, /* Ascii 74 */
   12,21,12, 5,11, 2,10, 1, 8, 0, 6, 0, 4, 1, 3, 2, 2, 5, 2, 7,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,21, /* Ascii 75 */
    4,21, 4, 0,-1,-1,18,21, 4, 7,-1,-1, 9,12,18, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,17, /* Ascii 76 */
    4,21, 4, 0,-1,-1, 4, 0,16, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,24, /* Ascii 77 */
    4,21, 4, 0,-1,-1, 4,21,12, 0,-1,-1,20,21,12, 0,-1,-1,20,21,20, 0,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,22, /* Ascii 78 */
    4,21, 4, 0,-1,-1, 4,21,18, 0,-1,-1,18,21,18, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   21,22, /* Ascii 79 */
    9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5, 3, 7, 1, 9, 0,13, 0,15,
    1,17, 3,18, 5,19, 8,19,13,18,16,17,18,15,20,13,21, 9,21,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   13,21, /* Ascii 80 */
    4,21, 4, 0,-1,-1, 4,21,13,21,16,20,17,19,18,17,18,14,17,12,16,11,13,
   10, 4,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   24,22, /* Ascii 81 */
    9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5, 3, 7, 1, 9, 0,13, 0,15,
    1,17, 3,18, 5,19, 8,19,13,18,16,17,18,15,20,13,21, 9,21,-1,-1,12, 4,
   18,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   16,21, /* Ascii 82 */
    4,21, 4, 0,-1,-1, 4,21,13,21,16,20,17,19,18,17,18,15,17,13,16,12,13,
   11, 4,11,-1,-1,11,11,18, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   20,20, /* Ascii 83 */
   17,18,15,20,12,21, 8,21, 5,20, 3,18, 3,16, 4,14, 5,13, 7,12,13,10,15,
    9,16, 8,17, 6,17, 3,15, 1,12, 0, 8, 0, 5, 1, 3, 3,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,16, /* Ascii 84 */
    8,21, 8, 0,-1,-1, 1,21,15,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,22, /* Ascii 85 */
    4,21, 4, 6, 5, 3, 7, 1,10, 0,12, 0,15, 1,17, 3,18, 6,18,21,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,18, /* Ascii 86 */
    1,21, 9, 0,-1,-1,17,21, 9, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,24, /* Ascii 87 */
    2,21, 7, 0,-1,-1,12,21, 7, 0,-1,-1,12,21,17, 0,-1,-1,22,21,17, 0,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,20, /* Ascii 88 */
    3,21,17, 0,-1,-1,17,21, 3, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    6,18, /* Ascii 89 */
    1,21, 9,11, 9, 0,-1,-1,17,21, 9,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,20, /* Ascii 90 */
   17,21, 3, 0,-1,-1, 3,21,17,21,-1,-1, 3, 0,17, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,14, /* Ascii 91 */
    4,25, 4,-7,-1,-1, 5,25, 5,-7,-1,-1, 4,25,11,25,-1,-1, 4,-7,11,-7,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2,14, /* Ascii 92 */
    0,21,14,-3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,14, /* Ascii 93 */
    9,25, 9,-7,-1,-1,10,25,10,-7,-1,-1, 3,25,10,25,-1,-1, 3,-7,10,-7,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,16, /* Ascii 94 */
    6,15, 8,18,10,15,-1,-1, 3,12, 8,17,13,12,-1,-1, 8,17, 8, 0,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2,16, /* Ascii 95 */
    0,-2,16,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    7,10, /* Ascii 96 */
    6,21, 5,20, 4,18, 4,16, 5,15, 6,16, 5,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 97 */
   15,14,15, 0,-1,-1,15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 98 */
    4,21, 4, 0,-1,-1, 4,11, 6,13, 8,14,11,14,13,13,15,11,16, 8,16, 6,15,
    3,13, 1,11, 0, 8, 0, 6, 1, 4, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   14,18, /* Ascii 99 */
   15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4, 3, 6, 1, 8, 0,11,
    0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 100 */
   15,21,15, 0,-1,-1,15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,18, /* Ascii 101 */
    3, 8,15, 8,15,10,14,12,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,12, /* Ascii 102 */
   10,21, 8,21, 6,20, 5,17, 5, 0,-1,-1, 2,14, 9,14,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   22,19, /* Ascii 103 */
   15,14,15,-2,14,-5,13,-6,11,-7, 8,-7, 6,-6,-1,-1,15,11,13,13,11,14, 8,
   14, 6,13, 4,11, 3, 8, 3, 6, 4, 3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,19, /* Ascii 104 */
    4,21, 4, 0,-1,-1, 4,10, 7,13, 9,14,12,14,14,13,15,10,15, 0,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8, 8, /* Ascii 105 */
    3,21, 4,20, 5,21, 4,22, 3,21,-1,-1, 4,14, 4, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,10, /* Ascii 106 */
    5,21, 6,20, 7,21, 6,22, 5,21,-1,-1, 6,14, 6,-3, 5,-6, 3,-7, 1,-7,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,17, /* Ascii 107 */
    4,21, 4, 0,-1,-1,14,14, 4, 4,-1,-1, 8, 8,15, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2, 8, /* Ascii 108 */
    4,21, 4, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   18,30, /* Ascii 109 */
    4,14, 4, 0,-1,-1, 4,10, 7,13, 9,14,12,14,14,13,15,10,15, 0,-1,-1,15,
   10,18,13,20,14,23,14,25,13,26,10,26, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,19, /* Ascii 110 */
    4,14, 4, 0,-1,-1, 4,10, 7,13, 9,14,12,14,14,13,15,10,15, 0,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 111 */
    8,14, 6,13, 4,11, 3, 8, 3, 6, 4, 3, 6, 1, 8, 0,11, 0,13, 1,15, 3,16,
    6,16, 8,15,11,13,13,11,14, 8,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 112 */
    4,14, 4,-7,-1,-1, 4,11, 6,13, 8,14,11,14,13,13,15,11,16, 8,16, 6,15,
    3,13, 1,11, 0, 8, 0, 6, 1, 4, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 113 */
   15,14,15,-7,-1,-1,15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,13, /* Ascii 114 */
    4,14, 4, 0,-1,-1, 4, 8, 5,11, 7,13, 9,14,12,14,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,17, /* Ascii 115 */
   14,11,13,13,10,14, 7,14, 4,13, 3,11, 4, 9, 6, 8,11, 7,13, 6,14, 4,14,
    3,13, 1,10, 0, 7, 0, 4, 1, 3, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,12, /* Ascii 116 */
    5,21, 5, 4, 6, 1, 8, 0,10, 0,-1,-1, 2,14, 9,14,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,19, /* Ascii 117 */
    4,14, 4, 4, 5, 1, 7, 0,10, 0,12, 1,15, 4,-1,-1,15,14,15, 0,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,16, /* Ascii 118 */
    2,14, 8, 0,-1,-1,14,14, 8, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,22, /* Ascii 119 */
    3,14, 7, 0,-1,-1,11,14, 7, 0,-1,-1,11,14,15, 0,-1,-1,19,14,15, 0,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,17, /* Ascii 120 */
    3,14,14, 0,-1,-1,14,14, 3, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    9,16, /* Ascii 121 */
    2,14, 8, 0,-1,-1,14,14, 8, 0, 6,-4, 4,-6, 2,-7, 1,-7,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,17, /* Ascii 122 */
   14,14, 3, 0,-1,-1, 3,14,14,14,-1,-1, 3, 0,14, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   39,14, /* Ascii 123 */
    9,25, 7,24, 6,23, 5,21, 5,19, 6,17, 7,16, 8,14, 8,12, 6,10,-1,-1, 7,
   24, 6,22, 6,20, 7,18, 8,17, 9,15, 9,13, 8,11, 4, 9, 8, 7, 9, 5, 9, 3,
    8, 1, 7, 0, 6,-2, 6,-4, 7,-6,-1,-1, 6, 8, 8, 6, 8, 4, 7, 2, 6, 1, 5,
   -1, 5,-3, 6,-5, 7,-6, 9,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2, 8, /* Ascii 124 */
    4,25, 4,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   39,14, /* Ascii 125 */
    5,25, 7,24, 8,23, 9,21, 9,19, 8,17, 7,16, 6,14, 6,12, 8,10,-1,-1, 7,
   24, 8,22, 8,20, 7,18, 6,17, 5,15, 5,13, 6,11,10, 9, 6, 7, 5, 5, 5, 3,
    6, 1, 7, 0, 8,-2, 8,-4, 7,-6,-1,-1, 8, 8, 6, 6, 6, 4, 7, 2, 8, 1, 9,
   -1, 9,-3, 8,-5, 7,-6, 5,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   23,24, /* Ascii 126 */
    3, 6, 3, 8, 4,11, 6,12, 8,12,10,11,14, 8,16, 7,18, 7,20, 8,21,10,-1,
   -1, 3, 8, 4,10, 6,11, 8,11,10,10,14, 7,16, 6,18, 6,20, 7,21,10,21,12,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};



y1 += h;
int n1 = 0;
float scale = 32.0;
float step = h * 0.6;
for (n1 = 0; n1 < strlen(text); n1++) {

	if (text[n1] - 32 >= 0 && text[n1] - 32 < 95) {
		uint8_t numC = text[n1] - 32;
		int numV = simplex[numC][0];
		int sizeX = simplex[numC][1];
		float step1 = step - (float)sizeX / scale * h;
		x1 += step1 / 2.0 + step / 2.0;
		float last_x = 0.0;
		float last_y = 0.0;
		int last_px = -1;
		int n = 0;
		for (n = 0; n < numV; n++) {
			int px = simplex[numC][2 + n * 2];
			int py = simplex[numC][3 + n * 2];
			float x = (float)px / scale * h + x1;
			float y = (float)-py / scale * h + y1;
			if (px != -1 && last_px != -1) {
				draw_line_f3(esContext, x, y, 0.0, last_x, last_y, z1, 255, 255, 255, 255);
			}
			last_px = px;
			last_x = x;
			last_y = y;
		}
		x1 += step / 2.0 - step1 / 2.0;
	} else {
		x1 += step;
	}
}



/*
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
			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num > 0) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
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
		for (n = 0; n < strlen(text); n++) {
			draw_char_f3_fast(esContext, x1 + n * ((float)w * 0.6), y1, z1, x1 + n * ((float)w * 0.6) + w, y1 + h, z1, tex_num, text[n]);
		}
	}
*/
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
			printf("remove image %s from cache %i (%i)\n", TexCache[tex_num].name, old_num, TexCache[tex_num].atime);
			glDeleteTextures( 1, &TexCache[tex_num].texture );
			TexCache[tex_num].name[0] = 0;
			TexCache[tex_num].texture = 0;
		}
		if (tex_num != -1) {
//			printf("loading image %s in to texture-cache %i %i\n", file, tex_num, TexCache[tex_num].atime);
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

		//glUseProgram(userData->programObject);
		glActiveTexture(GL_TEXTURE0);

		GLfloat vVertices[20];
		vVertices[0] = x1;
		vVertices[1] = y1;
		vVertices[2] = z1;
		vVertices[5] = x1;
		vVertices[6] = y2;
		vVertices[7] = z1;
		vVertices[10] = x2;
		vVertices[11] = y2;
		vVertices[12] = z1;
		vVertices[15] = x2;
		vVertices[16] = y1;
		vVertices[17] = z1;

		float tpos_x = (float)(num % 16) / 16;
		float tpos_y = (float)(num / 16) / 16;
		if (num < 0) {
			int nnn = num + 256;
			tpos_x = (float)(nnn % 16) / 16;
			tpos_y = (float)(nnn / 16) / 16;
		}
		if (tpos_x < 0 || tpos_y < 0 || tpos_x > 511 || tpos_y > 511) {
			printf("CHAR - ERROR\n");
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

		//glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices );
		//glEnableVertexAttribArray ( userData->positionLoc );

		//glUniformMatrix4fv( userData->mvpLoc, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix.m[0][0] );

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		//glVertexAttribPointer ( userData->texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );
		//glEnableVertexAttribArray ( userData->texCoordLoc );
//		glBindTexture (GL_TEXTURE_2D, TexCache[tex_num].texture );
		//glUniform1i ( userData->samplerLoc, 0 );
		//glDrawElements ( GL_LINES, 6, GL_UNSIGNED_SHORT, indices );
	}
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
			vVertices[2] = z1;
			vVertices[3] = last_x;
			vVertices[4] = last_y;
			vVertices[5] = z1;
			vVertices[6] = x1 - x;
			vVertices[7] = y + y1;
			vVertices[8] = z1;
			vVertices[9] = x1 - x_inner;
			vVertices[10] = y_inner + y1;
			vVertices[11] = z1;
			vVertices[12] = vVertices[0];
			vVertices[13] = vVertices[1];
			vVertices[14] = z1;
			vVertices[15] = vVertices[6];
			vVertices[16] = vVertices[7];
			vVertices[17] = z1;

			GLushort indices[] = { 0, 1, 2, 3, 4, 5 };

			glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
			glVertexPointer(3, GL_FLOAT, 0, vVertices);
			glEnableClientState(GL_VERTEX_ARRAY);
			glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, indices);

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
		vVertices[2] = z1;
		vVertices[3] = x1 + last_x * radius;
		vVertices[4] = y1 + last_y * radius;
		vVertices[5] = z1;
		vVertices[6] = x1 + temp1 * radius;
		vVertices[7] = y1 + temp2 * radius;
		vVertices[8] = z1;
		vVertices[9] = x1 + temp1 * radius_inner;
		vVertices[10] = y1 + temp2 * radius_inner;
		vVertices[11] = z1;
		vVertices[12] = vVertices[0];
		vVertices[13] = vVertices[1];
		vVertices[14] = z1;
		vVertices[15] = vVertices[6];
		vVertices[16] = vVertices[7];
		vVertices[17] = z1;


		GLushort indices[] = { 0, 1, 2, 3, 4, 5 };

		glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
		glVertexPointer(3, GL_FLOAT, 0, vVertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

		last_x = temp1;
		last_y = temp2;
	}
}

void draw_box_f3c2b (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2) {
	UserData *userData = esContext->userData;
	y1 = y1 * -1;
	y2 = y2 * -1;

	GLfloat vVertices[] = {
		x1, y1, z1,  // Position 0
		x1, y2, z1,  // Position 1
		x2, y2, z1,   // Position 2
		x2, y1, z1,   // Position 3
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	glColor4f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0);
	glVertexPointer(3, GL_FLOAT, 0, vVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
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
//	aspect = (GLfloat)state->window_w / (GLfloat)state->window_h;
//	glViewport(0 + setup.screen_border_x / 2, 0 + setup.screen_border_y / 2, setup.screen_w - setup.screen_border_x, setup.screen_h - setup.screen_border_y);
//	gluPerspective(53.0, aspect, 0.001, 7.0);
}
