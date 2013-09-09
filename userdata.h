
#include <stdint.h>
#ifdef SDLGL
#ifndef OSX
#define NO_SDL_GLEXT
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include "esUtil.h"
#endif


typedef struct {
#ifndef SDLGL
	GLuint programObject;
	GLint  positionLoc;
	GLint  mvpLoc;
	GLint  texCoordLoc;
	GLint  samplerLoc;
	ESMatrix  mvpMatrix;
	GLuint programObject2;
	GLint  positionLoc2;
	GLint  mvpLoc2;
	GLint  colorLoc2;
	GLuint textureId[10];
	ESMatrix  mvpMatrix2;
	ESMatrix perspective;
#endif
} UserData;

#ifdef SDLGL

typedef struct _escontext {
	void*       userData;
	GLint       width;
	GLint       height;
} ESContext;

typedef struct {
	GLfloat   m[4][4];
} ESMatrix;

#endif
