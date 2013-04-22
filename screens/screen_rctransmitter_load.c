
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <math.h>
#include <userdata.h>
#include <main.h>
#include <model.h>
#include <screen_rctransmitter_load.h>
#include <screen_rctransmitter.h>


uint8_t rctransmitter_load_back (char *name, float x, float y, int8_t button, float data) {
	view_mode = VIEW_MODE_RCTRANSMITTER;
	view_mode_next = VIEW_MODE_RCTRANSMITTER;
	return 0;
}

uint8_t rctransmitter_delete_model (char *name, float x, float y, int8_t button, float data) {
	if (name[4] == 0) {
		return 0;
	}
        char line[201];
	printf("remove Model: %s\n", name + 4);
        sprintf(line, "rm /usr/share/gl-gcs/models/%s", name + 4);
	system(line);
	return 0;
}

uint8_t rctransmitter_load_model (char *name, float x, float y, int8_t button, float data) {
	rctransmitter_init();
	char logline[1024];
	if (name[0] == 0) {
		return 0;
	}
//	strcpy(rctransmitter_btaddr, "00:00:00:00:00:00");
//	strcpy(rctransmitter_btpin, "1234");
	if (strcmp(name, "NEW-Model") == 0) {
		int n = 0;
		for (n = 0; n < 8; n++) {
			rctransmitter_dualrate[n] = 100;
			rctransmitter_reverse[n] = 0;
			rctransmitter_expo[n] = 0;
			rctransmitter_center[n] = 0;
		}
//		ModelData.teletype = 0;
		view_mode = VIEW_MODE_RCTRANSMITTER;
		view_mode_next = VIEW_MODE_RCTRANSMITTER;
		rctransmitter_name_edit(name, 0, 0, 0, (int)data + 1);
		return 0;
	}
	printf("loading Model: %s\n", name);
        FILE *fr;
        char line[201];
        char var[101];
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;
	int val4 = 0;
	int val5 = 0;
	int val6 = 0;
	int val7 = 0;
	int val8 = 0;

        sprintf(line, "/usr/share/gl-gcs/models/%s", name);
        fr = fopen(line, "r");
	if (fr != 0) {
	        while(fgets(line, 100, fr) != NULL) {
			if (strncmp(line, "type", 4) == 0) {
				sscanf (line, "%s %i", (char *)&var, &val1);
//				ModelData.teletype = val1;
			} else if (strncmp(line, "dualrate", 8) == 0) {
				sscanf (line, "%s %i %i %i %i %i %i %i %i", (char *)&var, &val1, &val2, &val3, &val4, &val5, &val6, &val7, &val8);
				rctransmitter_dualrate[0] = val1;
				rctransmitter_dualrate[1] = val2;
				rctransmitter_dualrate[2] = val3;
				rctransmitter_dualrate[3] = val4;
				rctransmitter_dualrate[4] = val5;
				rctransmitter_dualrate[5] = val6;
				rctransmitter_dualrate[6] = val7;
				rctransmitter_dualrate[7] = val8;
			} else if (strncmp(line, "reverse", 7) == 0) {
				sscanf (line, "%s %i %i %i %i %i %i %i %i", (char *)&var, &val1, &val2, &val3, &val4, &val5, &val6, &val7, &val8);
				rctransmitter_reverse[0] = val1;
				rctransmitter_reverse[1] = val2;
				rctransmitter_reverse[2] = val3;
				rctransmitter_reverse[3] = val4;
				rctransmitter_reverse[4] = val5;
				rctransmitter_reverse[5] = val6;
				rctransmitter_reverse[6] = val7;
				rctransmitter_reverse[7] = val8;
			} else if (strncmp(line, "expo", 4) == 0) {
				sscanf (line, "%s %i %i %i %i %i %i %i %i", (char *)&var, &val1, &val2, &val3, &val4, &val5, &val6, &val7, &val8);
				rctransmitter_expo[0] = val1;
				rctransmitter_expo[1] = val2;
				rctransmitter_expo[2] = val3;
				rctransmitter_expo[3] = val4;
				rctransmitter_expo[4] = val5;
				rctransmitter_expo[5] = val6;
				rctransmitter_expo[6] = val7;
				rctransmitter_expo[7] = val8;
			} else if (strncmp(line, "center", 6) == 0) {
		                sscanf (line, "%s %i %i %i %i %i %i %i %i", (char *)&var, &val1, &val2, &val3, &val4, &val5, &val6, &val7, &val8);
				rctransmitter_center[0] = val1;
				rctransmitter_center[1] = val2;
				rctransmitter_center[2] = val3;
				rctransmitter_center[3] = val4;
				rctransmitter_center[4] = val5;
				rctransmitter_center[5] = val6;
				rctransmitter_center[6] = val7;
				rctransmitter_center[7] = val8;
			} else if (strncmp(line, "trimm", 5) == 0) {
		                sscanf (line, "%s %i %i %i %i %i %i %i %i", (char *)&var, &val1, &val2, &val3, &val4, &val5, &val6, &val7, &val8);
				rctransmitter_trimm[0] = val1;
				rctransmitter_trimm[1] = val2;
				rctransmitter_trimm[2] = val3;
				rctransmitter_trimm[3] = val4;
				rctransmitter_trimm[4] = val5;
				rctransmitter_trimm[5] = val6;
				rctransmitter_trimm[6] = val7;
				rctransmitter_trimm[7] = val8;
			} else if (strncmp(line, "device", 6) == 0) {
//				sscanf (line, "%s %s", (char *)&var, (char *)&rctransmitter_device);
			} else if (strncmp(line, "baud", 4) == 0) {
				sscanf (line, "%s %i", (char *)&var, &val1);
//				rctransmitter_baud = val1;
			} else if (strncmp(line, "btaddr", 6) == 0) {
//				sscanf (line, "%s %s", (char *)&var, (char *)&rctransmitter_btaddr);
			} else if (strncmp(line, "btpin", 5) == 0) {
//				sscanf (line, "%s %s", (char *)&var, (char *)&rctransmitter_btpin);
			} else if (strncmp(line, "image", 5) == 0) {
				sscanf (line, "%s %s", (char *)&var, (char *)&rctransmitter_image);
			} else if (strncmp(line, "diff_name1", 10) == 0) {
				sscanf (line, "%s %s", (char *)&var, (char *)&diff_name[0]);
			} else if (strncmp(line, "diff_name2", 10) == 0) {
				sscanf (line, "%s %s", (char *)&var, (char *)&diff_name[1]);
			}
		}
		fclose(fr);
		sprintf(logline, "MDL:%s", name);
		LogAppend(logline);
		strcpy(rctransmitter_name, name);
	}
//	view_mode = VIEW_MODE_RCTRANSMITTER;
//	view_mode_next = VIEW_MODE_RCTRANSMITTER;
	rctransmitter_set();
//	reset_telemetrie();
	return 0;
}


void screen_rctransmitter_load (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	char tmp_str[100];
	int n = 0;

#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	draw_title(esContext, "load model");

	draw_button(esContext, "rctransmitter_load_back", VIEW_MODE_RCTRANSMITTER_LOAD, "[BACK]", FONT_WHITE, -1.2, -0.8, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_load_back, 0);

	DIR *dir = NULL;
	struct dirent *dir_entry = NULL;
	struct stat statbuf;
	char directory[200];
	char new_path[400];
	sprintf(directory, "/usr/share/gl-gcs/models");
	if ((dir = opendir(directory)) != NULL) {
		while ((dir_entry = readdir(dir)) != 0) {
			if (dir_entry->d_name[0] != '.' && strstr(dir_entry->d_name, ".png") == 0) {
				sprintf(new_path, "%s/%s", directory, dir_entry->d_name);
				if (lstat(new_path, &statbuf) == 0) {
					sprintf(tmp_str, "%s", dir_entry->d_name);
					draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER_LOAD, tmp_str, FONT_WHITE, -0.5 - 0.15, -0.5 + n * 0.15, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_load_model, n);
					sprintf(tmp_str, "del:%s", dir_entry->d_name);
					draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER_LOAD, "[DELETE]", FONT_WHITE, 0.10 - 0.15, -0.5 + n * 0.15, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_delete_model, n);
					n++;
				}
			}
		}
	}
	sprintf(tmp_str, "%s", "NEW-Model");
	draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER_LOAD, tmp_str, FONT_WHITE, -0.5 - 0.15, -0.5 + n * 0.15, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_load_model, n);

}

