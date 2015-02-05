
typedef struct {
	char name[1024];
	uint16_t interval;
	uint16_t pos;
	uint8_t type;
	uint8_t num;
	uint8_t triggermode;
	uint8_t options;
	uint8_t mode;
	float angle;
	float grid_x;
	float grid_y;
	float film_width;
	float film_height;
	float sensor_mult;
	float lense;
	float overlap;
	float alt;
	uint8_t alt_abs;
} Survey;

extern Survey SurveySetup;


void survey_parsePolypoint (xmlDocPtr doc, xmlNodePtr cur, int n);
void survey_parsePolypointNoFly (xmlDocPtr doc, xmlNodePtr cur, int n);
void survey_parseDoc (char *docname);
uint8_t survey_load_xml (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t survey_load (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t survey_save_xml (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t survey_save (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t survey_name_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t survey_name_edit (char *name, float x, float y, int8_t button, float data, uint8_t action);

void survey_reroute (ESContext *esContext, float x1, float y1, float x2, float y2, float alt, int nfzone);
int8_t survey_check_intersect_nofly (ESContext *esContext, float lastn_x, float lastn_y, float px1, float py1);
int8_t survey_check_intersect_nofly2point (ESContext *esContext, int nfn, float px, float py, float px2, float py2);

void draw_fov (ESContext *esContext, float p_lat, float p_long, float p_alt, float angle);
uint8_t survey_export_kml (char *name, float x, float y, int8_t button, float data, uint8_t action);
uint8_t survey_set (char *name, float x, float y, int8_t button, float data, uint8_t action);
void survey_draw_setup (ESContext *esContext);

int point_in_poly (float testx, float testy);
int point_in_polynf (float testx, float testy);


