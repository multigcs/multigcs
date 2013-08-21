
#ifndef DRAW_H
#define DRAW_H


typedef struct {
	float x;
	float y;
	float z;
} Object3dCord;

typedef struct {
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
} Object3dFace;

typedef struct {
	char name[1024];
	Object3dCord *cords;
	Object3dFace *faces;
	uint32_t faces_num;
	uint32_t cordsID;
	uint32_t facesID;
	float scale;
} Object3d;


extern SrtmCache AltCache[MAX_ALTCACHE];
extern const GLfloat DEG2RAD;

void object3d_load (Object3d *o3d, char *filename);
void object3d_free (Object3d *o3d);
void object3d_draw (Object3d *o3d, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void draw_image_uncache (char *file);
void draw_line_f (ESContext *esContext, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_line (ESContext *esContext, int16_t px1, int16_t py1, int16_t px2, int16_t py2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circle_f (ESContext *esContext, float x1, float y1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circle (ESContext *esContext, int16_t x, int16_t y, int16_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circleFilled_f (ESContext *esContext, float x1, float y1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circleFilled (ESContext *esContext, int16_t x, int16_t y, int16_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_rect_f (ESContext *esContext, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_box_f (ESContext *esContext, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_box (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_rect (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_tria_f (ESContext *esContext, float x1, float y1, float x2, float y2, float x3, float y3, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circleFilled_f3_part_end (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_circleMeter_f3 (ESContext *esContext, float x, float y, float z, float radius, float start1, float start2, float start3, float start4, float value, char *text, char *text2, uint8_t type);
void draw_image_f (ESContext *esContext, float x1, float y1, float x2, float y2, char *file);
void draw_image (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file);
int16_t get_altitude (float lat, float lon);
void draw_pointer (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file);
void draw_text_f3 (ESContext *esContext, float x1, float y1, float z1, float w, float h, char *file, char *text);
void draw_text_f (ESContext *esContext, float x1, float y1, float w, float h, char *file, char *text);
void draw_text (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file, char *text);
int loadPNG(const char *filename);
int loadImage(const char *filename);
void draw_scrollbar (ESContext *esContext, uint16_t page, uint16_t page_max, uint8_t (*callback) (char *, float, float, int8_t, float));
void draw_title (ESContext *esContext, char *text);
uint8_t draw_button (ESContext *esContext, char *name, uint8_t view_mode, char *text, char *font, float x, float y, float z, float h, uint8_t align_x, uint8_t align_y, uint8_t (*callback) (char *, float, float, int8_t, float), float data);

#ifdef SDLGL
uint32_t getpixel(SDL_Surface *surface, int x, int y);
#endif

#endif

