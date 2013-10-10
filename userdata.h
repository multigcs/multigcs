

typedef struct {
#ifndef ANDROID
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
