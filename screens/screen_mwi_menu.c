
#include <stdint.h>
#include <model.h>
#include <userdata.h>
#include <main.h>
#include <screen_mavlink_menu.h>
#include <my_mavlink.h>
#include <mwi21.h>

uint8_t mwi_view = 0;
uint8_t mwi_mode = 1;

uint8_t mwi_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t mwi_cal_acc (char *name, float x, float y, int8_t button, float data) {
	mwi21_cal_acc();
	return 0;
}

uint8_t mwi_cal_mac (char *name, float x, float y, int8_t button, float data) {
	mwi21_cal_mac();
	return 0;
}

uint8_t mwi_write_rom (char *name, float x, float y, int8_t button, float data) {
	mwi21_write_rom();
	return 0;
}

uint8_t mwi_get_values (char *name, float x, float y, int8_t button, float data) {
	mwi21_get_values();
	return 0;
}

uint8_t mwi_view_change (char *name, float x, float y, int8_t button, float data) {
	mwi_view = 1 - mwi_view;
	reset_buttons();
	return 0;
}

uint8_t mwi_status_set (char *name, float x, float y, int8_t button, float data) {
	uint8_t n = (uint8_t)data;
	if (mwi_status & (1<<n)) {
		mwi_status &= ~(1<<n);
	} else {
		mwi_status |= (1<<n);
	}
	return 0;
}

uint8_t mwi_pid_set (char *name, float x, float y, int8_t button, float data) {
	uint8_t n = 0;
	int8_t n2 = 0;
	int8_t v = 0;
	uint8_t nn = (uint8_t)data;
	if (name[5] == '+') {
		v = 1;
	} else if (name[5] == '-') {
		v = -1;
	} else {
		if (button == 4) {
			v = 1;
		} else if (button == 5) {
			v = -1;
		}
	}
	for (n2 = 0; n2 < 10; n2++) {
		mwi_set_pid[n2][0] = mwi_pid[n2][0];
		if (nn == n) {
			mwi_set_pid[n2][0] += v;
		}
		n++;
		mwi_set_pid[n2][1] = mwi_pid[n2][1];
		if (nn == n) {
			mwi_set_pid[n2][1] += v;
		}
		n++;
		mwi_set_pid[n2][2] = mwi_pid[n2][2];
		if (nn == n) {
			mwi_set_pid[n2][2] += v;
		}
		n++;
	}
	mwi_set_pid_flag = 1;
	return 0;
}

uint8_t mwi_box_set (char *name, float x, float y, int8_t button, float data) {
	uint8_t n = 0;
	int8_t n2 = 0;
	int8_t n3 = 0;
	uint8_t nn = (uint8_t)data;
	for (n2 = 0; n2 < 16; n2++) {
		for (n3 = 0; n3 < 12; n3++) {
			if (mwi_set_box[n2] & (1<<n3)) {
				if (n == nn) {
					mwi_set_box[n2] &= ~(1<<n3);
				} else {
					mwi_set_box[n2] |= (1<<n3);
				}
			} else {
				if (n == nn) {
					mwi_set_box[n2] |= (1<<n3);
				} else {
					mwi_set_box[n2] &= ~(1<<n3);
				}
			}
			n++;
		}
	}
	mwi_set_box_flag = 1;
	return 0;
}

uint8_t mwi_sensors_set (char *name, float x, float y, int8_t button, float data) {
	uint8_t n = (uint8_t)data;
	if (mwi_sensors & (1<<n)) {
		mwi_sensors &= ~(1<<n);
	} else {
		mwi_sensors |= (1<<n);
	}
	return 0;
}

void screen_mwi_menu (ESContext *esContext) {
	int16_t n = 0;
	int16_t n2 = 0;
	int16_t n3 = 0;
	char tmp_str[100];
	char tmp_str2[100];

	draw_title(esContext, "MultiWii");

	if (mwi_view == 1) {

		for (n3 = 0; n3 < 4; n3++) {
			if (n3 < 4) {
				float val = (float)ModelData.radio[4 + n3] / 2.0 + 50.0;
				if (val > 100.0) {
					val = 100.0;
				} else if (val < -100.0) {
					val = -100.0;
				}
				draw_circleMeter_f3(esContext, -0.4 + (float)n3 * 0.16 * 3.0, -0.8, 0.001, 0.06, 20.0, 30.0, 70.0, 160.0, val, "", "", 1);
			}
			sprintf(tmp_str2, "   AUX%i", n3 + 1);
			draw_button(esContext, "box", VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.85 + (float)n3 * 0.16 * 3.0, -0.87, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
			if (ModelData.radio[4 + n3] < -40) {
				draw_button(esContext, "box", VIEW_MODE_FCMENU, " L", FONT_GREEN, -0.8 + (float)n3 * 0.16 * 3.0, -0.8, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
				draw_button(esContext, "box", VIEW_MODE_FCMENU, " M", FONT_WHITE, -0.8 + (float)n3 * 0.16 * 3.0 + 0.16, -0.8, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
				draw_button(esContext, "box", VIEW_MODE_FCMENU, " H", FONT_WHITE, -0.8 + (float)n3 * 0.16 * 3.0 + 0.32, -0.8, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
			} else if (ModelData.radio[4 + n3] > 40) {
				draw_button(esContext, "box", VIEW_MODE_FCMENU, " L", FONT_WHITE, -0.8 + (float)n3 * 0.16 * 3.0, -0.8, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
				draw_button(esContext, "box", VIEW_MODE_FCMENU, " M", FONT_WHITE, -0.8 + (float)n3 * 0.16 * 3.0 + 0.16, -0.8, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
				draw_button(esContext, "box", VIEW_MODE_FCMENU, " H", FONT_GREEN, -0.8 + (float)n3 * 0.16 * 3.0 + 0.32, -0.8, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
			} else {
				draw_button(esContext, "box", VIEW_MODE_FCMENU, " L", FONT_WHITE, -0.8 + (float)n3 * 0.16 * 3.0, -0.8, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
				draw_button(esContext, "box", VIEW_MODE_FCMENU, " M", FONT_GREEN, -0.8 + (float)n3 * 0.16 * 3.0 + 0.16, -0.8, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
				draw_button(esContext, "box", VIEW_MODE_FCMENU, " H", FONT_WHITE, -0.8 + (float)n3 * 0.16 * 3.0 + 0.32, -0.8, 0.002, 0.08, 0, 0, mwi_null, (float)n3);
			}
		}
		for (n2 = 0; n2 < 16 && mwi_box_names[n2][0] != 0; n2++) {
			sprintf(tmp_str, "mwi_v%i", n);
			sprintf(tmp_str2, "%s", mwi_box_names[n2]);
			if (n2 < 3 && ! (mwi_sensors & (1<<n2))) {
				draw_button(esContext, "box", VIEW_MODE_FCMENU, tmp_str2, FONT_TRANS, -1.2, -0.7 + (float)n2 * 0.1, 0.002, 0.08, 0, 0, mwi_null, (float)n2);
//			} else if ((n2 == 6 || n2 == 7) && ! (mwi_sensors & (1<<3))) {
//				draw_button(esContext, "box", VIEW_MODE_FCMENU, tmp_str2, FONT_TRANS, -1.2, -0.7 + (float)n2 * 0.1, 0.002, 0.08, 0, 0, mwi_null, (float)n2);
//			} else if ((n2 == 9) && ! (mwi_sensors & (1<<2))) {
//				draw_button(esContext, "box", VIEW_MODE_FCMENU, tmp_str2, FONT_TRANS, -1.2, -0.7 + (float)n2 * 0.1, 0.002, 0.08, 0, 0, mwi_null, (float)n2);
			} else if (mwi_status & (1<<n2)) {
				draw_button(esContext, "box", VIEW_MODE_FCMENU, tmp_str2, FONT_GREEN, -1.2, -0.7 + (float)n2 * 0.1, 0.002, 0.08, 0, 0, mwi_null, (float)n2);
			} else {
				draw_button(esContext, "box", VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.7 + (float)n2 * 0.1, 0.002, 0.08, 0, 0, mwi_null, (float)n2);
			}
		}
		n = 0;
		for (n2 = 0; n2 < 16 && mwi_box_names[n2][0] != 0; n2++) {
			for (n3 = 0; n3 < 12; n3++) {
				sprintf(tmp_str, "mwi_v%i", n);
				if (mwi_set_box[n2] & (1<<n3)) {
					sprintf(tmp_str2, "[x]");
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.8 + (float)n3 * 0.16, -0.7 + (float)n2 * 0.1, 0.002, 0.08, 0, 0, mwi_box_set, (float)n);
				} else {
					sprintf(tmp_str2, "[ ]");
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.8 + (float)n3 * 0.16, -0.7 + (float)n2 * 0.1, 0.002, 0.08, 0, 0, mwi_box_set, (float)n);
				}
				n++;
			}
		}
		draw_button(esContext, "mwi_view", VIEW_MODE_FCMENU, "[BOX]", FONT_WHITE, 0.0, 0.9, 0.002, 0.07, 1, 0, mwi_view_change, 0.0);
	} else {
		draw_button(esContext, "pid", VIEW_MODE_FCMENU, "P", FONT_WHITE, -0.7 + 1.0 * 0.2, -0.8, 0.002, 0.08, 1, 0, mwi_pid_set, (float)0);
		draw_button(esContext, "pid", VIEW_MODE_FCMENU, "I", FONT_WHITE, 0.0 + 1.0 * 0.2, -0.8, 0.002, 0.08, 1, 0, mwi_pid_set, (float)1);
		draw_button(esContext, "pid", VIEW_MODE_FCMENU, "D", FONT_WHITE, 0.7 + 1.0 * 0.2, -0.8, 0.002, 0.08, 1, 0, mwi_pid_set, (float)2);
		for (n2 = 0; n2 < 16 && mwi_pid_names[n2][0]; n2++) {
			sprintf(tmp_str2, "%s", mwi_pid_names[n2]);
			draw_button(esContext, "pid", VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -1.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 0, 0, mwi_null, (float)n2);
			if (n2 < 3) {
				float val = (float)ModelData.radio[n2] / 2.0 + 50.0;
				if (val > 100.0) {
					val = 100.0;
				} else if (val < -100.0) {
					val = -100.0;
				}
				draw_circleMeter_f3(esContext, -0.85, -0.7 + (float)n2 * 0.13 + 0.07, 0.001, 0.06, 20.0, 50.0, 50.0, 160.0, val, "", "", 1);
			}
		}
		n = 0;
		for (n2 = 0; n2 < 16 && mwi_pid_names[n2][0]; n2++) {
			if (n2 == 114) {
				sprintf(tmp_str2, "%0.2f", (float)mwi_pid[n2][0] / 100.0);
				sprintf(tmp_str, "mwi_p-%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -0.7 + 0.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n);
				sprintf(tmp_str, "mwi_p%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.7 + 1.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n);
				sprintf(tmp_str, "mwi_p+%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -0.7 + 2.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n);
				sprintf(tmp_str2, "%0.2f", (float)mwi_pid[n2][1] / 100.0);
				sprintf(tmp_str, "mwi_i-%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -0.0 + 0.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 1.0);
				sprintf(tmp_str, "mwi_i%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.0 + 1.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 1.0);
				sprintf(tmp_str, "mwi_i+%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -0.0 + 2.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 1.0);
			} else if (n2 == 115 || n2 == 116) {
				sprintf(tmp_str2, "%0.2f", (float)mwi_pid[n2][0] / 10.0);
				sprintf(tmp_str, "mwi_p-%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -0.7 + 0.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n);
				sprintf(tmp_str, "mwi_p%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.7 + 1.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n);
				sprintf(tmp_str, "mwi_p+%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -0.7 + 2.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n);
				sprintf(tmp_str2, "%0.2f", (float)mwi_pid[n2][1] / 100.0);
				sprintf(tmp_str, "mwi_i-%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -0.0 + 0.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 1.0);
				sprintf(tmp_str, "mwi_i%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.0 + 1.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 1.0);
				sprintf(tmp_str, "mwi_i+%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -0.0 + 2.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 1.0);
				sprintf(tmp_str2, "%0.3f", (float)mwi_pid[n2][2] / 1000.0);
				sprintf(tmp_str, "mwi_d-%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.7 + 0.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 2.0);
				sprintf(tmp_str, "mwi_d%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.7 + 1.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 2.0);
				sprintf(tmp_str, "mwi_d+%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.7 + 2.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 2.0);
			} else {
				sprintf(tmp_str2, "%0.2f", (float)mwi_pid[n2][0] / 10.0);
				sprintf(tmp_str, "mwi_p-%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -0.7 + 0.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n);
				sprintf(tmp_str, "mwi_p%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.7 + 1.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n);
				sprintf(tmp_str, "mwi_p+%i", n);
				draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -0.7 + 2.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n);
				if (n2 != 118) {
					sprintf(tmp_str2, "%0.3f", (float)mwi_pid[n2][1] / 1000.0);
					sprintf(tmp_str, "mwi_i-%i", n);
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-]", FONT_WHITE, -0.0 + 0.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 1.0);
					sprintf(tmp_str, "mwi_i%i", n);
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, -0.0 + 1.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 1.0);
					sprintf(tmp_str, "mwi_i+%i", n);
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+]", FONT_WHITE, -0.0 + 2.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 1.0);
	
					sprintf(tmp_str2, "%0.0f", (float)mwi_pid[n2][2] / 1.0);
					sprintf(tmp_str, "mwi_d-%i", n);
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[-]", FONT_WHITE, 0.7 + 0.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 2.0);
					sprintf(tmp_str, "mwi_d%i", n);
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, tmp_str2, FONT_WHITE, 0.7 + 1.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 2.0);
					sprintf(tmp_str, "mwi_d+%i", n);
					draw_button(esContext, tmp_str, VIEW_MODE_FCMENU, "[+]", FONT_WHITE, 0.7 + 2.0 * 0.2, -0.7 + (float)n2 * 0.13, 0.002, 0.08, 1, 0, mwi_pid_set, (float)n + 2.0);
				}
			}
			n += 3;
		}
		draw_button(esContext, "mwi_view", VIEW_MODE_FCMENU, "[PID]", FONT_WHITE, 0.0, 0.9, 0.002, 0.07, 1, 0, mwi_view_change, 0.0);
	}
	draw_button(esContext, "mwi_cal_acc", VIEW_MODE_FCMENU, "[CAL_ACC]", FONT_WHITE, -0.8, 0.9, 0.002, 0.07, 1, 0, mwi_cal_acc, 0.0);
	draw_button(esContext, "mwi_cal_mac", VIEW_MODE_FCMENU, "[CAL_MAG]", FONT_WHITE, -0.4, 0.9, 0.002, 0.07, 1, 0, mwi_cal_mac, 0.0);
	draw_button(esContext, "mwi_get_values", VIEW_MODE_FCMENU, "[READ]", FONT_WHITE, 0.4, 0.9, 0.002, 0.07, 1, 0, mwi_get_values, 0.0);
	draw_button(esContext, "mwi_write_rom", VIEW_MODE_FCMENU, "[WRITE_ROM]", FONT_WHITE, 0.8, 0.9, 0.002, 0.07, 1, 0, mwi_write_rom, 0.0);
}

