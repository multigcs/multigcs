
#ifndef GL_DRAW_H
#define GL_DRAW_H

#define MAX_TEXCACHE 200
#define MAX_ALTCACHE 16
#define PI 3.14159265

typedef struct {
	char name[1024];
	uint32_t atime;
	GLuint texture;
} TextureCache;

typedef struct {
	char name[1024];
	uint32_t atime;
	int16_t data[1201][1201];
} SrtmCache;

extern Uint32 rmask;
extern Uint32 gmask;
extern Uint32 bmask;
extern Uint32 amask;
extern SDL_Surface *WinScreen;
extern SDL_Event event;
extern GLfloat colors[4];
extern TextureCache TexCache[MAX_TEXCACHE];
extern float aspect;
extern float alt_zoom;

void esTranslate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
void esRotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void esMatrixLoadIdentity(ESMatrix *result);
void esMatrixMultiply(ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB);
int loadPNG(const char *filename);
int16_t get_altitude (float lat, float lon);
void draw_image_uncache (char *file);
void draw_image_srtm (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file, float lat1, float lon1, float lat2, float lon2, float alpha0, float alpha1, float alpha2, float grid);
void draw_line_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_line_f (ESContext *esContext, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_line (ESContext *esContext, int16_t px1, int16_t py1, int16_t px2, int16_t py2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circle_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circle_f (ESContext *esContext, float x1, float y1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circle (ESContext *esContext, int16_t x, int16_t y, int16_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circleFilled_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circleFilled_f (ESContext *esContext, float x1, float y1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circleFilled (ESContext *esContext, int16_t x, int16_t y, int16_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_zylinder_f3 (ESContext *esContext, float x1, float y1, float z1, float z2, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_trifan_f3 (ESContext *esContext, float *poly_array, uint16_t len, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_rect_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_box_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_box_f3c2 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2);
void draw_box_f3c2b (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t a2);
void draw_box_f (ESContext *esContext, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_box (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_tria_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_triaFilled_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_tria_f (ESContext *esContext, float x1, float y1, float x2, float y2, float x3, float y3, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_triaFilled_f (ESContext *esContext, float x1, float y1, float x2, float y2, float x3, float y3, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_image_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, char *file);
void draw_image_f (ESContext *esContext, float x1, float y1, float x2, float y2, char *file);
void draw_image (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file);
void draw_pointer (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file);
void draw_char_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, char *file, char num);
void draw_text_f3 (ESContext *esContext, float x1, float y1, float z1, float w, float h, char *file, char *text);
void draw_text_f3_fast (ESContext *esContext, float x1, float y1, float z1, float w, float h, char *file, char *text);
void draw_text_f (ESContext *esContext, float x1, float y1, float w, float h, char *file, char *text);
void draw_text (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file, char *text);
int gl_init(uint16_t w, uint16_t h);
int glInit ( ESContext *esContext );
void glExit ( ESContext *esContext );
void draw_circleFilled_f3_part (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, float stop, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circlePointer_f3 (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circleFilled_f3_part_end (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circleMeter_f3 (ESContext *esContext, float x, float y, float z, float radius, float start1, float start2, float start3, float start4, float value, char *text, char *text2, uint8_t type);
void draw_graph_value (ESContext *esContext, float px1, float py1, float px2, float py2, float pz, uint8_t *data, int16_t len, int16_t pointer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void resize_border (void);
void glResize (ESContext *esContext, int w, int h);
void draw_to_buffer (void);
void draw_to_screen (void);
uint8_t draw_target (void);
void draw_buffer_to_screen (float x1, float y1, float x2, float y2, float z, float alpha);

#endif
