
#include <all.h>

#define FILTER_MAX 10

static uint8_t show_device = 0;
static uint8_t device_page = 0;
static uint8_t (*save_callback) (char *, float, float, int8_t, float, uint8_t);
static char device_filter[FILTER_MAX][200];
static uint8_t device_filter_num = 0;

void device_set_callback (uint8_t (*callback) (char *, float, float, int8_t, float, uint8_t action)) {
	save_callback = callback;
}

uint8_t device_page_move (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (data < 0.0) {
		if (device_page > 0) {
			device_page += (int8_t)data;
		}
	} else {
		device_page += (int8_t)data;
	}
	return 0;
}

void device_set_mode (uint8_t mode) {
	show_device = mode;
	device_page = 0;
}

uint8_t device_get_mode (void) {
	return show_device;
}

uint8_t device_filter_match (char *filename) {
	if (device_filter_num == 0) {
		return 1;
	} else {
		uint8_t n = 0;
		for (n = 0; n < device_filter_num; n++) {
			if (strstr(filename, device_filter[n]) > 0) {
				return 1;
			}
		}
	}
	return 0;
}

void device_add_filter (char *filter) {
	if (device_filter_num < FILTER_MAX) {
		strncpy(device_filter[device_filter_num++], filter, 199);
	} else {
		SDL_Log("ERROR: to many filters\n");
	}
}

void device_reset_filter (void) {
	uint8_t n = 0;
	for (n = 0; n < FILTER_MAX; n++) {
		device_filter[n][0] = 0;
	}
	device_filter_num = 0;
}

uint8_t device_name_cancel (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	show_device = 0;
	return 0;
}

uint8_t device_null (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	return 0;
}

uint8_t device_name_save (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	show_device = 0;
	(*save_callback)(name, x, y, button, 1.0, 0);
	return 0;
}

#ifdef ANDROID
extern char bt_devices[100][1023];
#endif

void screen_device (ESContext *esContext) {
	if (show_device != setup.view_mode) {
		return;
	}
	reset_buttons();
	draw_box_f3(esContext, -1.5, -1.0, 0.002, 1.5, 1.0, 0.002, 0, 0, 0, 200);
#ifndef WINDOWS
	DIR *dir = NULL;
	struct dirent *dir_entry = NULL;
	struct stat statbuf;
#endif
	char directory[200];
	char new_path[400];
	char tmp_str[400];
	uint8_t n = 0;
	uint8_t n2 = 0;
	sprintf(directory, "%s", "/dev");
	// Device-File's
#ifndef WINDOWS
	if ((dir = opendir(directory)) != NULL) {
		while ((dir_entry = readdir(dir)) != 0) {
			if (dir_entry->d_name[0] != '.') {
				sprintf(new_path, "%s/%s", directory, dir_entry->d_name);
				if (lstat(new_path, &statbuf) == 0) {
					if (statbuf.st_mode & S_IFDIR) {
					} else if (device_filter_match(dir_entry->d_name) == 1) {
						if (device_page == n2) {
							sprintf(tmp_str, "%s", dir_entry->d_name);
							draw_text_button(esContext, new_path, setup.view_mode, tmp_str, FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, device_name_save, 0.0);
							if (serial_info_get(new_path, tmp_str) == 0) {
								draw_text_button(esContext, "-id-", setup.view_mode, tmp_str, FONT_WHITE, -1.0 + 0.05, -0.8 + n * 0.1 + 0.05, 0.002, 0.04, 0, 0, device_null, 0.0);
							}
							sprintf(tmp_str, "/var/lock/LCK..%s", basename(new_path));
							if (file_exists(tmp_str) != 0) {
								draw_text_button(esContext, "-used-", setup.view_mode, "-IN USE-", FONT_PINK, 0.7, -0.8 + n * 0.1 + 0.05, 0.002, 0.04, 0, 0, device_null, 0.0);
							}
						}
						n++;
					}
				}
			}
			if (n > 10) {
				n2++;
				n = 0;
			}
		}
		draw_text_button(esContext, "TCP", setup.view_mode, "TCP", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, device_name_save, 0.0);
		n++;
		draw_text_button(esContext, "UDP", setup.view_mode, "UDP", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, device_name_save, 0.0);
		n++;
		closedir(dir);
		dir = NULL;
	}
#else
	n = 0;
	DWORD Index = 0;
	DWORD dwValueNameLength, dwTypeCode, dwValueLength;
	char ValueName[256];
	char Value[256];
	dwValueNameLength = sizeof(ValueName);
	dwValueLength = sizeof(Value);
	LONG lnResult;
	HKEY hKey;
	lnResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &hKey);
	if (lnResult == ERROR_SUCCESS) {
		while(RegEnumValue(hKey, Index, ValueName, &dwValueNameLength, NULL, &dwTypeCode, (BYTE *)Value, &dwValueLength) == ERROR_SUCCESS) {
			if(dwTypeCode == REG_SZ) {
				sprintf(new_path, "\\\\.\\%s", Value);
				sprintf(tmp_str, "%s (%s)", ValueName, Value);
				draw_text_button(esContext, new_path, setup.view_mode, tmp_str, FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, device_name_save, 0.0);
				n++;
			}
			dwValueNameLength = sizeof(ValueName);
			dwValueLength = sizeof(Value);
			Index++;
		}
		RegCloseKey(hKey);
	}
	if (n == 0) {
		int nnum = 0;
		for (nnum = 1; nnum <= 16; nnum++) {
			if (device_page == n2) {
				sprintf(new_path, "\\\\.\\COM%i", nnum);
				sprintf(tmp_str, "COM%i", nnum);
				draw_text_button(esContext, new_path, setup.view_mode, tmp_str, FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 1, 0, device_name_save, 0.0);
			}
			n++;
		}
	}
#endif
#ifdef ANDROID
	int nnum = 0;
	for (nnum = 0; nnum < 10 && bt_devices[nnum][0] != 0; nnum++) {
		if (device_page == n2) {
			sprintf(tmp_str, "bt:%s", bt_devices[nnum]);
			draw_text_button(esContext, tmp_str, setup.view_mode, tmp_str, FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, device_name_save, 0.0);
		}
		n++;
	}
#endif

	draw_text_button(esContext, "UNSET", setup.view_mode, "UNSET", FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, device_name_save, 0.0);

	if (device_page > 0) {
		sprintf(tmp_str, "^ (%i/%i)", device_page, n2);
		draw_text_button(esContext, "up", setup.view_mode, tmp_str, FONT_WHITE, 0.0, -0.9, 0.002, 0.08, 1, 0, device_page_move, -1.0);
	}
	if (n2 > device_page) {
		sprintf(tmp_str, "v (%i/%i)", device_page, n2);
		draw_text_button(esContext, "down", setup.view_mode, tmp_str, FONT_WHITE, 0.0, 0.8, 0.002, 0.08, 1, 0, device_page_move, +1.0);
	}

	draw_text_button(esContext, "show", setup.view_mode, "[CANCEL]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, 1, 0, device_name_cancel, 0.0);

}

