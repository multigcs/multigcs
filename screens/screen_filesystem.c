
#include <all.h>

#define FILTER_MAX 10

static int8_t filesystem_page = 0;
static uint8_t show_filesystem = 0;
static uint8_t (*save_callback) (char *, float, float, int8_t, float, uint8_t);
static char filesystem_rootdir[1024];
static char filesystem_filter[FILTER_MAX][1024];
static uint8_t filesystem_filter_num = 0;

void filesystem_set_callback (uint8_t (*callback) (char *, float, float, int8_t, float, uint8_t)) {
	save_callback = callback;
}

uint8_t filesystem_page_move (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (data < 0.0) {
		if (filesystem_page > 0) {
			filesystem_page += (int8_t)data;
		}
	} else {
		filesystem_page += (int8_t)data;
	}
	return 0;
}

void filesystem_set_mode (uint8_t mode) {
	show_filesystem = mode;
//	filesystem_page = 0;
}

uint8_t filesystem_get_mode (void) {
	return show_filesystem;
}

void filesystem_set_dir (char *rootdir) {
	strncpy(filesystem_rootdir, rootdir, 1023);
	filesystem_page = 0;
}

char *filesystem_get_dir (void) {
	return filesystem_rootdir;
}

uint8_t filesystem_filter_match (char *filename) {
	if (filesystem_filter_num == 0) {
		return 1;
	} else {
		uint8_t n = 0;
		for (n = 0; n < filesystem_filter_num; n++) {
			if (strstr(filename, filesystem_filter[n]) > 0) {
				return 1;
			}
		}
	}
	return 0;
}

void filesystem_add_filter (char *filter) {
	if (filesystem_filter_num < FILTER_MAX) {
		strncpy(filesystem_filter[filesystem_filter_num++], filter, 1023);
	} else {
		SDL_Log("ERROR: to many filters\n");
	}
}

void filesystem_reset_filter (void) {
	uint8_t n = 0;
	for (n = 0; n < FILTER_MAX; n++) {
		filesystem_filter[n][0] = 0;
	}
	filesystem_filter_num = 0;
}

uint8_t filesystem_name_cancel (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	show_filesystem = 0;
	(*save_callback)("", x, y, button, 1.0, 0);
	return 0;
}

uint8_t filesystem_name_save (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	show_filesystem = 0;
	(*save_callback)(name, x, y, button, 1.0, 0);
	return 0;
}

uint8_t filesystem_dir_open (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	strncpy(filesystem_rootdir, name, 1023);
	filesystem_page = 0;
	return 0;
}

void screen_filesystem (ESContext *esContext) {
#ifdef SDLGL
	if (draw_target() != 0) {
		return;
	}
#endif
	if (show_filesystem != setup.view_mode) {
		return;
	}

	reset_buttons();
	draw_box_f3(esContext, -1.5, -1.0, 0.002, 1.5, 1.0, 0.002, 0, 0, 0, 200);

	char image_path[128];
	DIR *dir = NULL;
	struct dirent *dir_entry = NULL;
	struct stat statbuf;
	char directory[200];
	char new_path[400];
	char tmp_str[400];
	int16_t n = 0;
	int16_t n2 = 0;
	sprintf(directory, "%s", filesystem_rootdir);
	// Parent
	if ((dir = opendir(directory)) != NULL) {
		while ((dir_entry = readdir(dir)) != 0) {
			if (dir_entry->d_name[1] == '.') {
				if (filesystem_page == n2) {
					sprintf(new_path, "%s", directory);
					dirname(new_path);
					sprintf(image_path, "%s/textures/folder.png", BASE_DIR);
					draw_image_f3(esContext, -1.0 - 0.12, -0.8 + n * 0.1 - 0.02, -1.0 - 0.12 + 0.1, -0.8 + n * 0.1 - 0.02 + 0.1, 0.002, image_path);
					draw_text_button(esContext, new_path, setup.view_mode, dir_entry->d_name, FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, filesystem_dir_open, 0.0);
				}
				n++;
			}
			if (n > 10) {
				n2++;
				n = 0;
			}
		}
		closedir(dir);
		dir = NULL;
	}
	// Directory's
#ifndef WINDOWS
	if ((dir = opendir(directory)) != NULL) {
		while ((dir_entry = readdir(dir)) != 0) {
			if (dir_entry->d_name[0] != '.') {
				sprintf(new_path, "%s/%s", directory, dir_entry->d_name);
				if (lstat(new_path, &statbuf) == 0) {
					if (statbuf.st_mode&S_IFDIR) {
						if (filesystem_page == n2) {
							sprintf(tmp_str, "%s", dir_entry->d_name);
							sprintf(image_path, "%s/textures/folder.png", BASE_DIR);
							draw_image_f3(esContext, -1.0 - 0.12, -0.8 + n * 0.1 - 0.02, -1.0 - 0.12 + 0.1, -0.8 + n * 0.1 - 0.02 + 0.1, 0.002, image_path);
							draw_text_button(esContext, new_path, setup.view_mode, tmp_str, FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, filesystem_dir_open, 0.0);
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
		closedir(dir);
		dir = NULL;
	}
	// File's
	if ((dir = opendir(directory)) != NULL) {
		while ((dir_entry = readdir(dir)) != 0) {
			if (dir_entry->d_name[0] != '.') {
				sprintf(new_path, "%s/%s", directory, dir_entry->d_name);
				if (lstat(new_path, &statbuf) == 0) {
					if (statbuf.st_mode & S_IFDIR) {
					} else if (filesystem_filter_match(dir_entry->d_name) == 1) {
						if (filesystem_page == n2) {
							sprintf(tmp_str, "%s", dir_entry->d_name);
							if (strstr(dir_entry->d_name, ".png\0") > 0) {
								draw_image_f3(esContext, -1.0 - 0.12, -0.8 + n * 0.1 - 0.02, -1.0 - 0.12 + 0.1, -0.8 + n * 0.1 - 0.02 + 0.1, 0.002, new_path);
							} else {
								sprintf(image_path, "%s/textures/file.png", BASE_DIR);
								draw_image_f3(esContext, -1.0 - 0.12, -0.8 + n * 0.1 - 0.02, -1.0 - 0.12 + 0.1, -0.8 + n * 0.1 - 0.02 + 0.1, 0.002, image_path);
							}
							draw_text_button(esContext, new_path, setup.view_mode, tmp_str, FONT_WHITE, -1.0, -0.8 + n * 0.1, 0.002, 0.06, 0, 0, filesystem_name_save, 0.0);
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
		closedir(dir);
		dir = NULL;
	}
#endif
	if (n == 0) {
		filesystem_page = 0;
	}

	draw_scrollbar(esContext, filesystem_page, n2, filesystem_page_move);
	if (filesystem_page > n2) {
		filesystem_page = n2;
	} else if (filesystem_page < 0) {
		filesystem_page = 0;
	}

	draw_text_button(esContext, "show", setup.view_mode, "[CANCEL]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, 1, 0, filesystem_name_cancel, 0.0);

}

