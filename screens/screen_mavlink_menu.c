
#include <userdata.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <main.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include <model.h>
#include <screen_mavlink_menu.h>
#include <screen_keyboard.h>
#include <screen_filesystem.h>
#include <my_mavlink.h>

float sel = 0.0;
float set_sel = 0.0;
float sel2 = 0.0;
float set_sel2 = 0.0;
uint8_t sel1_mode = 0;
uint8_t sel2_mode = 0;
char select_section[100];

#define SLIDER_START	0.45
#define SLIDER_LEN	0.45

uint8_t mavlink_slider_move (char *name, float x, float y, int8_t button, float data) {
	int n = 0;
	int selected = -1;
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name + 1) == 0) {
			selected = n;
			break;
		}
	}

	if (button == 4) {
		if (MavLinkVars[selected].type != 0) {
			MavLinkVars[selected].value += 1;
		} else {
			MavLinkVars[selected].value += 0.01;
		}
	} else if (button == 5) {
		if (MavLinkVars[selected].type != 0) {
			MavLinkVars[selected].value -= 1;
		} else {
			MavLinkVars[selected].value -= 0.01;
		}
	} else {
		float percent = (x - SLIDER_START) * 100.0 / SLIDER_LEN;
		if (percent > 100.0) {
			percent = 100.0;
		} else if (percent < 0.0) {
			percent = 0.0;
		}
		float diff = MavLinkVars[selected].max - MavLinkVars[selected].min;
		float new = percent * diff / 100.0 + MavLinkVars[selected].min;
		if (MavLinkVars[selected].type != 0) {
			int conv = (int)(new);
			new = (float)conv;
		}
		printf("slider: %s %f %f %f %f\n", name + 1, x, percent, new, data);
		MavLinkVars[selected].value = new;
	}

	if (MavLinkVars[selected].value < MavLinkVars[selected].min) {
		MavLinkVars[selected].value = MavLinkVars[selected].min;
	} else if (MavLinkVars[selected].value > MavLinkVars[selected].max) {
		MavLinkVars[selected].value = MavLinkVars[selected].max;
	}

	mavlink_send_value(MavLinkVars[selected].name, MavLinkVars[selected].value, MavLinkVars[selected].type);
	return 0;
}

void mavlink_parseParams1 (xmlDocPtr doc, xmlNodePtr cur, char *name) { 
	int n = 0;
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name) == 0) {
			break;
		}
	}
	if (n == 500 - 1) {
		return 0;
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"Range"))) {
			float min = 0.0;
			float max = 0.0;
			xmlChar *key;

			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			sscanf((char *)key, "%f %f", &min, &max);
			MavLinkVars[n].min = min;
			MavLinkVars[n].max = max;

			printf("	Range: %s: %f -> %f\n", name, min, max);

			xmlFree(key);
		}

		cur = cur->next;
	}
	return;
}

void mavlink_parseParams (xmlDocPtr doc, xmlNodePtr cur) { 
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
			mavlink_parseParams1(doc, cur, (char *)cur->name);
		}
		cur = cur->next;
	}
	return;
}

static void mavlink_parseDoc (char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlChar *key;
	doc = xmlParseFile(docname);
	if (doc == NULL) {
		printf("Document parsing failed: %s\n", docname);
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		printf("Document is Empty!!!\n");
		return;
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

		printf("#3# %s ##\n", cur->name);

		if ((!xmlStrcmp(cur->name, (const xmlChar *)"ArduCopter2"))) {
			mavlink_parseParams(doc, cur);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}

uint8_t mavlink_param_xml_load (char *name, float x, float y, int8_t button, float data) {
	mavlink_parseDoc("/tmp/ParameterMetaData.xml");
}

uint8_t mavlink_param_file_save (char *name, float x, float y, int8_t button, float data) {
	char filename[1024];
	FILE *fr;
	int n = 0;
	sprintf(filename, "%s/PARAMS/%s", BASE_DIR, name);
	if ((fr = fopen(filename, "w")) != 0) {
		fprintf(fr, "# Onboard parameters\n");
		fprintf(fr, "#\n");
		fprintf(fr, "# MAV ID  COMPONENT ID  PARAM NAME  VALUE (FLOAT)\n");
		for (n = 0; n < 500 - 1; n++) {
			if (MavLinkVars[n].name[0] != 0) {
				fprintf(fr, "%i	%i	%s	%f\n", ModelData.sysid, ModelData.compid, MavLinkVars[n].name, MavLinkVars[n].value);
			}
		}
		fprintf(fr, "\n");
		fclose(fr);
		printf("failed to save file: %s\n", filename);
	} else {
		printf("saved file: %s\n", filename);
	}
	return 0;
}

uint8_t mavlink_param_save (char *name, float x, float y, int8_t button, float data) {
	char filename[1024];
	sprintf(filename, "%s.txt", ModelData.name);
	keyboard_set_callback(mavlink_param_file_save);
	keyboard_set_text(filename);
	keyboard_set_mode(VIEW_MODE_FCMENU);
	return 0;
}

uint8_t mavlink_param_file_load (char *name, float x, float y, int8_t button, float data) {
	mavlink_param_read_file(name);
	return 0;
}

uint8_t mavlink_param_load (char *name, float x, float y, int8_t button, float data) {
	char directory[200];
	sprintf(directory, "%s/PARAMS", BASE_DIR);
	filesystem_set_callback(mavlink_param_file_load);
	filesystem_set_dir(directory);
	filesystem_reset_filter();
	filesystem_add_filter(".txt\0");
	filesystem_add_filter(".param\0");
	filesystem_set_mode(VIEW_MODE_FCMENU);
	return 0;
}

uint8_t mavlink_flash (char *name, float x, float y, int8_t button, float data) {
	save_to_flash();
	return 0;
}

uint8_t mavlink_flashload (char *name, float x, float y, int8_t button, float data) {
	load_from_flash();
	return 0;
}

uint8_t mavlink_select_main (char *name, float x, float y, int8_t button, float data) {
	sel2 = (float)data;
	set_sel2 = (float)data;

	strcpy(select_section, name + 8);

	sel1_mode = 1;
	reset_buttons();
	return 0;
}

uint8_t mavlink_select_sel (char *name, float x, float y, int8_t button, float data) {
	uint16_t n = 0;
	printf("%s -- %0.2f\n", name + 1, data);
	if (data == 0.0) {
		sel1_mode = 0;
		reset_buttons();
		return 0;
	}
	for (n = 0; n < 500 - 1; n++) {
		if (strcmp(MavLinkVars[n].name, name + 1) == 0) {
			MavLinkVars[n].value += data;
			mavlink_send_value(MavLinkVars[n].name, MavLinkVars[n].value, MavLinkVars[n].type);
			break;
		}
	}
	return 0;
}

uint8_t mavlink_select_sel_scroll (char *name, float x, float y, int8_t button, float data) {
	if ((int)data > 0) {
		set_sel++;
	} else if (set_sel > 0) {
		set_sel--;
	}
	return 0;
}

void mavlink_param_read_file (char *param_file) {
        FILE *fr;
        char line[1024];
        int tmp_int1;
        int tmp_int2;
        char var1[101];
        char val[101];
        fr = fopen (param_file, "r");
        while(fgets(line, 100, fr) != NULL) {
                var1[0] = 0;
                val[0] = 0;
		if (line[0] != '#' && line[0] != '\n') {
	                sscanf (line, "%i %i %s %s", &tmp_int1, &tmp_int2, (char *)&var1, (char *)&val);
			float new_val = atof(val);
//	                printf ("#%s# = %f\n", var1, new_val);
			uint16_t n = 0;
			uint8_t flag = 0;
			for (n = 0; n < 500; n++) {
				if (strcmp(MavLinkVars[n].name, var1) == 0) {
					float old_val = MavLinkVars[n].value;
					if (old_val != new_val) {
						printf ("CHANGED: %s = %f (OLD: %f)\n", var1, new_val, MavLinkVars[n].value);
						MavLinkVars[n].value = atof(val);
					}
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				for (n = 0; n < 500; n++) {
					if (MavLinkVars[n].name[0] == 0) {
						strcpy(MavLinkVars[n].name, var1);
						MavLinkVars[n].value = atof(val);
						MavLinkVars[n].id = -1;
				                printf ("NEW: %s = %f\n", var1, atof(val));
						break;
					}
				}
			}

		}
        }
        fclose(fr);
}

uint8_t mavlink_param_upload_all (char *name, float x, float y, int8_t button, float data) {
	int n = 0;
	for (n = 0; n < 500 - 1; n++) {
		if (MavLinkVars[n].name[0] != 0) {
			mavlink_send_value(MavLinkVars[n].name, MavLinkVars[n].value, MavLinkVars[n].type);
			SDL_Delay(20);
		}
	}
	return 0;
}

void screen_mavlink_menu (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	int16_t row = 0;
	int16_t col = 0;
	int16_t row2 = 0;
	int16_t n = 0;
	char section[100];
	char tmp_str[100];
	char tmp_str2[100];
	int8_t flag = 0;
	int8_t flag2 = 0;
	draw_title(esContext, "MavLink");

	strcpy(section, mainMavLinkVars[(int)sel2].name);
	row2 = 0;
	for (row = 0; row < 500 - 1; row++) {
		if (strlen(MavLinkVars[row].name) > 3) {
			strcpy(tmp_str, MavLinkVars[row].name);
			for (n = 0; n < strlen(tmp_str) ; n++) {
				if (tmp_str[n] == '_') {
					tmp_str[n] = 0;
					break;
				}
			}
			flag2 = 0;
			for (row2 = 0; row2 < 500 - 1; row2++) {
				if (strcmp(mainMavLinkVars[row2].name, tmp_str) == 0) {
					flag2 = 1;
					break;
				}
			}
			if (flag2 == 0) {
				for (row2 = 0; row2 < 500 - 1; row2++) {
					if (mainMavLinkVars[row2].name[0] == 0) {
						strcpy(mainMavLinkVars[row2].name, tmp_str);
						break;
					}
				}
			}
			flag = 1;
		}
	}
	if (row2 > 0 && set_sel2 >= row2) {
		set_sel2 = row2 - 1;
	}
	row2 = 0;
	for (row = 0; row < 500 - 1; row++) {
		if (strncmp(MavLinkVars[row].name, section, strlen(section)) == 0) {
//			printf("%s - %s\n", section, MavLinkVars[row].name);
			strcpy(selMavLinkVars[row2].name, MavLinkVars[row].name);
			selMavLinkVars[row2].value = MavLinkVars[row].value;
			selMavLinkVars[row2].min = MavLinkVars[row].min;
			selMavLinkVars[row2].max = MavLinkVars[row].max;
			selMavLinkVars[row2].type = MavLinkVars[row].type;
			selMavLinkVars[row2].id = row;
			selMavLinkVars[row2 + 1].name[0] = 0;
			selMavLinkVars[row2 + 1].value = 0.0;
			selMavLinkVars[row2 + 1].min = 0.0;
			selMavLinkVars[row2 + 1].max = 0.0;
			selMavLinkVars[row2 + 1].type = 0;
			selMavLinkVars[row2 + 1].id = 0;
			row2++;
		}
	}
	if (row2 > 0 && set_sel >= row2) {
		set_sel = row2 - 1;
	}

	if (sel1_mode != 1) {
		col = 0;
		row = 0;
		for (n = 0; n < 500; n++) {
			if (mainMavLinkVars[n].name[0] == 0) {
				break;
			}
			sprintf(tmp_str, "mv_main_%s", mainMavLinkVars[n].name);
			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, mainMavLinkVars[n].name, FONT_WHITE, -1.3 + col * 0.5, -0.8 + row * 0.12, 0.002, 0.08, 0, 0, mavlink_select_main, n);
			col++;
			if (col > 4) {
				col = 0;
				row++;
			}
		}
	}
	if (sel1_mode == 1) {
		col = 0;
		row = 0;
		if ((int)set_sel > 0) {
			sprintf(tmp_str, "-scroll_%s", selMavLinkVars[n].name);
			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[^]", FONT_WHITE, 0.0, -0.7 - 0.14, 0.002, 0.08, 1, 0, mavlink_select_sel_scroll, -1.0);
		}

		for (n = 0; n < 10 && n + (int)set_sel < 500; n++) {
			if (selMavLinkVars[n + (int)set_sel].name[0] == 0) {
				break;
			}

//			if (strcmp(selMavLinkVars[n + (int)set_sel].name, diff_name[0]) == 0) {
//				sprintf(tmp_str, "RESET 0%i", n);
//				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "1", FONT_GREEN, -1.4, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, rctransmitter_mavlink_diff, 0);
//			} else {
//				sprintf(tmp_str, "%s 0%i", selMavLinkVars[n + (int)set_sel].name, n);
//				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "1", FONT_WHITE, -1.4, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, rctransmitter_mavlink_diff, 0);
//			}
//			if (strcmp(selMavLinkVars[n + (int)set_sel].name, diff_name[1]) == 0) {
//				sprintf(tmp_str, "RESET 1%i", n);
//				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "2", FONT_GREEN, -1.3, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, rctransmitter_mavlink_diff, 1);
//			} else {
//				sprintf(tmp_str, "%s 1%i", selMavLinkVars[n + (int)set_sel].name, n);
//				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "2", FONT_WHITE, -1.3, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, rctransmitter_mavlink_diff, 1);
//			}

			sprintf(tmp_str, "mv_sel_%s_%i_t", selMavLinkVars[n + (int)set_sel].name, n);
			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, selMavLinkVars[n + (int)set_sel].name, FONT_WHITE, -1.2, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_select_sel, n);

			sprintf(tmp_str, "mv_sel_%s_%i_v", selMavLinkVars[n + (int)set_sel].name, n);

			if (selMavLinkVars[n + (int)set_sel].type != 0) {
				sprintf(tmp_str2, "%i", (int)selMavLinkVars[n + (int)set_sel].value);
			} else {
				sprintf(tmp_str2, "%0.4f", selMavLinkVars[n + (int)set_sel].value);
			}

			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.05, -0.7 + row * 0.14, 0.002, 0.08, 2, 0, mavlink_select_sel, n);


//			sprintf(tmp_str, "a%s", selMavLinkVars[n + (int)set_sel].name);
//			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-1.0]", FONT_WHITE, 0.1, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_select_sel, -1.0);


sprintf(tmp_str, "S%s", selMavLinkVars[n + (int)set_sel].name);
draw_box_f3c2(esContext, SLIDER_START, -0.7 + row * 0.14, 0.001, SLIDER_START + SLIDER_LEN, -0.7 + row * 0.14 + 0.1, 0.001, 55, 55, 55, 220, 75, 45, 85, 100);
draw_box_f3c2(esContext, SLIDER_START, -0.7 + row * 0.14, 0.001, SLIDER_START + ((selMavLinkVars[n + (int)set_sel].value - selMavLinkVars[n + (int)set_sel].min) * SLIDER_LEN / (selMavLinkVars[n + (int)set_sel].max - selMavLinkVars[n + (int)set_sel].min)), -0.7 + row * 0.14 + 0.1, 0.001, 255, 255, 55, 220, 175, 145, 85, 100);
set_button(tmp_str, view_mode, SLIDER_START, -0.7 + row * 0.14, SLIDER_START + SLIDER_LEN, -0.7 + row * 0.14 + 0.1, mavlink_slider_move, (float)row, 1);


/*			if (selMavLinkVars[n + (int)set_sel].type == 0) {
				sprintf(tmp_str, "b%s", selMavLinkVars[n + (int)set_sel].name);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-0.1]", FONT_WHITE, 0.4, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_select_sel, -0.1);

				sprintf(tmp_str, "c%s", selMavLinkVars[n + (int)set_sel].name);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+0.1]", FONT_WHITE, 0.7, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_select_sel, 0.1);
			}
*/

//			sprintf(tmp_str, "d%s", selMavLinkVars[n + (int)set_sel].name);
//			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+1.0]", FONT_WHITE, 1.0, -0.7 + row * 0.14, 0.002, 0.08, 0, 0, mavlink_select_sel, 1.0);

			row++;
		}
		if (n >= 10) {
			sprintf(tmp_str, "+scroll_%s", selMavLinkVars[n + (int)set_sel].name);
			draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[v]", FONT_WHITE, 0.0, 0.7, 0.002, 0.08, 1, 0, mavlink_select_sel_scroll, 1.0);
		}
		draw_button(esContext, "back", VIEW_MODE_FCMENU, "[BACK]", FONT_WHITE, -1.3, 0.8, 0.002, 0.08, 0, 0, mavlink_select_sel, 0.0);
	}


	draw_button(esContext, "load", VIEW_MODE_FCMENU, "[LOAD FILE]", FONT_WHITE, -1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_param_load, 1.0);
	draw_button(esContext, "save", VIEW_MODE_FCMENU, "[SAVE FILE]", FONT_WHITE, -0.5, 0.9, 0.002, 0.06, 1, 0, mavlink_param_save, 1.0);
	draw_button(esContext, "upload", VIEW_MODE_FCMENU, "[UPLOAD ALL]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, 1, 0, mavlink_param_upload_all, 1.0);
	draw_button(esContext, "flash_r", VIEW_MODE_FCMENU, "[LOAD FLASH]", FONT_WHITE, 0.5, 0.9, 0.002, 0.06, 1, 0, mavlink_flashload, 0.0);
	draw_button(esContext, "flash_w", VIEW_MODE_FCMENU, "[WRITE FLASH]", FONT_WHITE, 1.0, 0.9, 0.002, 0.06, 1, 0, mavlink_flash, 0.0);

	draw_button(esContext, "xml_load", VIEW_MODE_FCMENU, "[XML LOAD]", FONT_WHITE, 1.0, 0.8, 0.002, 0.06, 1, 0, mavlink_param_xml_load, 0.0);



	if (flag == 0) {
		draw_text_f(esContext, -0.4, 0.0, 0.05, 0.05, FONT_BLACK_BG, "No Mavlink-Parameters found");
	}

	screen_keyboard(esContext);
	screen_filesystem(esContext);


}

