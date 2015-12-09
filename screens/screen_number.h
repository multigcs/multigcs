
extern void screen_number(ESContext *esContext);


enum {
	NUMBER_TYPE_INT8,
	NUMBER_TYPE_UINT8,
	NUMBER_TYPE_INT16,
	NUMBER_TYPE_UINT16,
	NUMBER_TYPE_INT32,
	NUMBER_TYPE_UINT32,
	NUMBER_TYPE_FLOAT,
};

void edit_number(uint8_t mode, uint8_t type, void *ptr, float min, float max);
uint8_t screen_number_check(ESContext *esContext);

