
#include <all.h>


static uint8_t show_number = 0;
static uint8_t number_type = 0;
static float number_min = 0;
static float number_max = 0;
static float number_value = 0;
static void *number_value_ptr = NULL;;


uint8_t edit_number_set(char *name, float x, float y, int8_t button, float data, uint8_t action) {
	number_value = atof(name);
	if (number_value > number_max) {
		number_value = number_max;
	}
	if (number_value < number_min) {
		number_value = number_min;
	}
	if (number_type == NUMBER_TYPE_UINT8) {
		uint8_t *value = (uint8_t *)number_value_ptr;
		*value = number_value;
	} else if (number_type == NUMBER_TYPE_INT8) {
		int8_t *value = (int8_t *)number_value_ptr;
		*value = number_value;
	} else if (number_type == NUMBER_TYPE_UINT16) {
		uint16_t *value = (uint16_t *)number_value_ptr;
		*value = number_value;
	} else if (number_type == NUMBER_TYPE_INT16) {
		int16_t *value = (int16_t *)number_value_ptr;
		*value = number_value;
	} else if (number_type == NUMBER_TYPE_UINT32) {
		uint32_t *value = (uint32_t *)number_value_ptr;
		*value = number_value;
	} else if (number_type == NUMBER_TYPE_INT32) {
		int32_t *value = (int32_t *)number_value_ptr;
		*value = number_value;
	} else if (number_type == NUMBER_TYPE_FLOAT) {
		float *value = (float *)number_value_ptr;
		*value = number_value;
	}
	show_number = 255;
	return 0;
}

void edit_number(uint8_t mode, uint8_t type, void *ptr, float min, float max) {
	char tmp_str[1024];
	show_number = mode;
	number_type = type;
	number_min = min;
	number_max = max;
	number_value_ptr = ptr;
	if (number_type == NUMBER_TYPE_UINT8) {
		uint8_t *value = (uint8_t *)number_value_ptr;
		number_value = (float) * value;
		sprintf(tmp_str, "%0.0f", number_value);
	} else if (number_type == NUMBER_TYPE_INT8) {
		int8_t *value = (int8_t *)number_value_ptr;
		number_value = (float) * value;
		sprintf(tmp_str, "%0.0f", number_value);
	} else if (number_type == NUMBER_TYPE_UINT16) {
		uint16_t *value = (uint16_t *)number_value_ptr;
		number_value = (float) * value;
		sprintf(tmp_str, "%0.0f", number_value);
	} else if (number_type == NUMBER_TYPE_INT16) {
		int16_t *value = (int16_t *)number_value_ptr;
		number_value = (float) * value;
		sprintf(tmp_str, "%0.0f", number_value);
	} else if (number_type == NUMBER_TYPE_UINT32) {
		uint32_t *value = (uint32_t *)number_value_ptr;
		number_value = (float) * value;
		sprintf(tmp_str, "%0.0f", number_value);
	} else if (number_type == NUMBER_TYPE_INT32) {
		int32_t *value = (int32_t *)number_value_ptr;
		number_value = (float) * value;
		sprintf(tmp_str, "%0.0f", number_value);
	} else if (number_type == NUMBER_TYPE_FLOAT) {
		float *value = (float *)number_value_ptr;
		number_value = (float) * value;
		sprintf(tmp_str, "%f", number_value);
	}
	keyboard_set_callback(edit_number_set);
	if (number_type == NUMBER_TYPE_FLOAT) {
		keyboard_set_number(tmp_str, 1);
	} else {
		keyboard_set_number(tmp_str, 0);
	}
	keyboard_set_mode(mode);
}

uint8_t screen_number_check(ESContext *esContext) {
	if (show_number != setup.view_mode) {
		return 0;
	}
	return 1;
}

void screen_number(ESContext *esContext) {
	if (show_number != setup.view_mode) {
		return;
	}
	screen_keyboard(esContext);
}

