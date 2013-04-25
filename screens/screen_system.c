
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <math.h>
#include <linux/version.h>
#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <ctype.h>
#include <termios.h>
#include <userdata.h>
#include <main.h>
#include <model.h>
#include <screen_system.h>
#include <my_mavlink.h>
#include <my_gps.h>
#include <frsky.h>
#include <openpilot.h>
#include <mwi21.h>
#include <jeti.h>
#include <screen_device.h>
#include <screen_baud.h>

static char port_selected[100];
static char baud_selected[100];

uint8_t system_baud_set (char *name, float x, float y, int8_t button, float data) {
	printf("BAUD: %s_baud = %s\n", baud_selected, name);
        if (strcmp(baud_selected, "gcs_gps") == 0) {
                gcs_gps_baud = atoi(name);
		gcs_gps_exit();
		gcs_gps_init(gcs_gps_port, gcs_gps_baud);
        } else if (strcmp(baud_selected, "jeti") == 0) {
                jeti_baud = atoi(name);
		jeti_exit();
		jeti_init(jeti_port, jeti_baud);
        } else if (strcmp(baud_selected, "frsky") == 0) {
                frsky_baud = atoi(name);
		frsky_exit();
		frsky_init(frsky_port, frsky_baud);
	}
	return 0;
}

uint8_t system_baud_change (char *name, float x, float y, int8_t button, float data) {
	strcpy(baud_selected, name);
	baud_set_callback(system_baud_set);
	baud_set_mode(VIEW_MODE_SYSTEM);
	return 0;
}

uint8_t system_device_set (char *name, float x, float y, int8_t button, float data) {
	printf("DEVICE: %s_port = %s\n", port_selected, name);
        if (strcmp(port_selected, "gcs_gps") == 0) {
                strcpy(gcs_gps_port, name);
        } else if (strcmp(port_selected, "jeti") == 0) {
                strcpy(jeti_port, name);
        } else if (strcmp(port_selected, "frsky") == 0) {
                strcpy(frsky_port, name);
	}
	if (strcmp(name, "UNSET") != 0) {
		system_baud_change(port_selected, x, y, button, data);
	} else {
		strcpy(baud_selected, name);
		system_baud_set("1200", x, y, button, data);
	}
	return 0;
}

uint8_t system_device_change (char *name, float x, float y, int8_t button, float data) {
	strcpy(port_selected, name);
	device_set_callback(system_device_set);
	device_reset_filter();
	device_add_filter("ttyUSB");
	device_add_filter("ttyACM");
	device_add_filter("ttyS");
	device_set_mode(VIEW_MODE_SYSTEM);
	return 0;
}

uint8_t system_dhclient (char *name, float x, float y, int8_t button, float data) {
	system("dhclient eth0");
	return 0;
}

uint8_t system_update (char *name, float x, float y, int8_t button, float data) {
	system("echo \"cd /tmp/ ; wget http://www.multixmedia.org/test/AutoQuad/gl-gcs/gl-gcs_last.deb && dpkg -i gl-gcs_last.deb\" > /tmp/gcs.execute");
	SDL_Event user_event;
	user_event.type = SDL_QUIT;
	SDL_PushEvent(&user_event);
	return 0;
}

uint8_t system_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t system_set_border_x (char *name, float x, float y, int8_t button, float data) {
	if ((int)data == 0) {
		screen_border_x = 0;
	} else if ((int)data > 0 && screen_border_x >= (int)data) {
		screen_border_x += (int)data;
	} else if ((int)data < 0 && screen_border_x <= (int)data) {
		screen_border_x += (int)data;
	}
	resize_border();
	return 0;
}

uint8_t system_set_border_y (char *name, float x, float y, int8_t button, float data) {
	if ((int)data == 0) {
		screen_border_y = 0;
	} else if ((int)data > 0 && screen_border_y >= (int)data) {
		screen_border_y += (int)data;
	} else if ((int)data < 0 && screen_border_y <= (int)data) {
		screen_border_y += (int)data;
	}
	resize_border();
	return 0;
}


void screen_system (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif
	FILE *cmd = NULL;
	char buffer[1025];
	static char ip[30];
	static char bcast[30];
	static char mask[30];
	static char hostname[30];
	static char dnsserver[30];
	static char gateway[30];

	uint32_t now_time = time(0);
	static uint32_t last_time = 0;

#ifndef SDLGL
	esMatrixLoadIdentity( &modelview );
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
#endif

	draw_title(esContext, "System");

	if (last_time != now_time) {
		strcpy(ip, "---.---.---.---");
		strcpy(bcast, "---.---.---.---");
		strcpy(mask, "---.---.---.---");
		strcpy(dnsserver, "---.---.---.---");
		strcpy(gateway, "---.---.---.---");
		if((cmd = popen("LANG=C ifconfig eth0 | grep \"inet addr:\" | sed \"s|[a-zA-Z:]||g\"", "r")) != NULL) {
			while(!feof(cmd)) {
				if(fgets(buffer, 1024, cmd) != NULL) {
					sscanf(buffer, "%s %s %s", (char *)&ip, (char *)&bcast, (char *)&mask);
		//			printf("## %s, %s, %s ##\n", ip, bcast, mask);
				}
			}
			pclose(cmd);
		}

		if((cmd = popen("grep \"^nameserver \" /etc/resolv.conf | cut -d\" \" -f2", "r")) != NULL) {
			while(!feof(cmd)) {
				if(fgets(dnsserver, 1024, cmd) != NULL) {
				}
			}
		}
		pclose(cmd);

		if((cmd = popen("route -n | grep \" 0.0.0.0.*255.255.255.0 \" | cut -d\" \" -f1", "r")) != NULL) {
			while(!feof(cmd)) {
				if(fgets(gateway, 1024, cmd) != NULL) {
				}
			}
		}
		pclose(cmd);


		if((cmd = popen("hostname", "r")) != NULL) {
			while(!feof(cmd)) {
				if(fgets(hostname, 1024, cmd) != NULL) {
				}
			}
		}
		pclose(cmd);

		last_time = now_time;
	}

	sprintf(buffer, "Name  : %s", hostname);
	draw_text_f(esContext, -0.5, -0.8 + 1 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "IP    : %s", ip);
	draw_text_f(esContext, -0.5, -0.8 + 3 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "BCAST : %s", bcast);
	draw_text_f(esContext, -0.5, -0.8 + 4 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "MASK  : %s", mask);
	draw_text_f(esContext, -0.5, -0.8 + 5 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "DNS   : %s", dnsserver);
	draw_text_f(esContext, -0.5, -0.8 + 6 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);
	sprintf(buffer, "GATE  : %s", gateway);
	draw_text_f(esContext, -0.5, -0.8 + 7 * 0.1, 0.06, 0.06, FONT_GREEN, buffer);

	draw_button(esContext, "system_dhclient", VIEW_MODE_SYSTEM, "<GET IP OVER DHCP>", FONT_GREEN, 0.0, -0.8 + 9 * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, system_dhclient, 0.0);
	draw_button(esContext, "system_gcs", VIEW_MODE_SYSTEM, "<UPDATE GCS>", FONT_GREEN, 0.0, -0.8 + 10 * 0.1, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, system_update, 0.0);

	// Connections-Status
	char tmp_str[100];
	uint8_t n = 0;
	if (ModelData.teletype == TELETYPE_AUTOQUAD || ModelData.teletype == TELETYPE_ARDUPILOT || ModelData.teletype == TELETYPE_MEGAPIRATE_NG) {
		if (mavlink_connection_status() != 0) {
			sprintf(tmp_str, "MAVLINK %s (%i / %i)", telemetrie_port, telemetrie_baud, (uint8_t)(time(0)) - mavlink_connection_status());
			draw_button(esContext, "mavlink_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "MAVLINK %s (%i)", telemetrie_port, telemetrie_baud);
			draw_button(esContext, "mavlink_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_button(esContext, "mavlink_connection_status", VIEW_MODE_SYSTEM, "MAVLINK", FONT_TRANS, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}
	if (ModelData.teletype == TELETYPE_MULTIWII_21 || ModelData.teletype == TELETYPE_BASEFLIGHT) {
		if (mwi21_connection_status() != 0) {
			sprintf(tmp_str, "MULTIWII21 %s (%i / %i)", telemetrie_port, telemetrie_baud, (uint8_t)(time(0)) - mwi21_connection_status());
			draw_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "MULTIWII21 %s (%i)", telemetrie_port, telemetrie_baud);
			draw_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, "MULTIWII21", FONT_TRANS, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}
	if (ModelData.teletype == TELETYPE_BASEFLIGHT) {
		if (mwi21_connection_status() != 0) {
			sprintf(tmp_str, "BASEFLIGHT %s (%i / %i)", telemetrie_port, telemetrie_baud, (uint8_t)(time(0)) - mwi21_connection_status());
			draw_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "BASEFLIGHT %s (%i)", telemetrie_port, telemetrie_baud);
			draw_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_button(esContext, "mwi21_connection_status", VIEW_MODE_SYSTEM, "BASEFLIGHT", FONT_TRANS, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}
	if (ModelData.teletype == TELETYPE_OPENPILOT) {
		if (openpilot_connection_status() != 0) {
			sprintf(tmp_str, "OPENPILOT %s (%i / %i)", telemetrie_port, telemetrie_baud, (uint8_t)(time(0)) - openpilot_connection_status());
			draw_button(esContext, "openpilot_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "OPENPILOT %s (%i)", telemetrie_port, telemetrie_baud);
			draw_button(esContext, "openpilot_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_button(esContext, "openpilot_connection_status", VIEW_MODE_SYSTEM, "OPENPILOT", FONT_TRANS, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}
	if (ModelData.teletype == TELETYPE_GPS_NMEA) {
		if (gps_connection_status() != 0) {
			sprintf(tmp_str, "NMEA-GPS %s (%i / %i)", telemetrie_port, telemetrie_baud, (uint8_t)(time(0)) - gps_connection_status());
			draw_button(esContext, "gps_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		} else {
			sprintf(tmp_str, "NMEA-GPS %s (%i)", telemetrie_port, telemetrie_baud);
			draw_button(esContext, "gps_connection_status", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
		}
	} else {
		draw_button(esContext, "gps_connection_status", VIEW_MODE_SYSTEM, "NMEA-GPS", FONT_TRANS, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_null, 0.0);
	}

	if (frsky_connection_status() != 0) {
		sprintf(tmp_str, "FRSKY %s (%i / %i)", frsky_port, frsky_baud, (uint8_t)(time(0)) - frsky_connection_status());
		draw_button(esContext, "frsky", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	} else {
		sprintf(tmp_str, "FRSKY %s (%i)", frsky_port, frsky_baud);
		draw_button(esContext, "frsky", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	}
	if (jeti_connection_status() != 0) {
		sprintf(tmp_str, "JETI %s (%i / %i)", jeti_port, jeti_baud, (uint8_t)(time(0)) - jeti_connection_status());
		draw_button(esContext, "jeti", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	} else {
		sprintf(tmp_str, "JETI %s (%i)", jeti_port, jeti_baud);
		draw_button(esContext, "jeti", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	}
	if (gcsgps_connection_status() != 0) {
		sprintf(tmp_str, "GCS-GPS %s (%i / %i)", gcs_gps_port, gcs_gps_baud, (uint8_t)(time(0)) - gcsgps_connection_status());
		draw_button(esContext, "gcs_gps", VIEW_MODE_SYSTEM, tmp_str, FONT_GREEN, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	} else {
		sprintf(tmp_str, "GCS-GPS %s (%i)", gcs_gps_port, gcs_gps_baud);
		draw_button(esContext, "gcs_gps", VIEW_MODE_SYSTEM, tmp_str, FONT_WHITE, -1.3, 0.35 + n++ * 0.065, 0.002, 0.04, ALIGN_LEFT, ALIGN_TOP, system_device_change, 0.0);
	}

/*
	draw_button(esContext, "border_x--", VIEW_MODE_SYSTEM, "<", FONT_WHITE, -1.32, 0.0, 0.002, 0.05, ALIGN_CENTER, ALIGN_TOP, system_set_border_x, -2.0);
	draw_button(esContext, "border_x", VIEW_MODE_SYSTEM, "|", FONT_WHITE, -1.25, 0.0, 0.002, 0.05, ALIGN_CENTER, ALIGN_TOP, system_set_border_x, 0.0);
	draw_button(esContext, "border_x++", VIEW_MODE_SYSTEM, ">", FONT_WHITE, -1.18, 0.0, 0.002, 0.05, ALIGN_CENTER, ALIGN_TOP, system_set_border_x, 2.0);

	draw_button(esContext, "border_y--", VIEW_MODE_SYSTEM, "^", FONT_WHITE, 0.0, 0.8, 0.002, 0.05, ALIGN_CENTER, ALIGN_TOP, system_set_border_y, 2.0);
	draw_button(esContext, "border_y", VIEW_MODE_SYSTEM, "---", FONT_WHITE, 0.0, 0.85, 0.002, 0.05, ALIGN_CENTER, ALIGN_TOP, system_set_border_y, 0.0);
	draw_button(esContext, "border_y++", VIEW_MODE_SYSTEM, "v", FONT_WHITE, 0.0, 0.9, 0.002, 0.05, ALIGN_CENTER, ALIGN_TOP, system_set_border_y, -2.0);
*/

	draw_button(esContext, "_border_x", VIEW_MODE_SYSTEM, "X-Border", FONT_GREEN, 0.55, 0.4, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_x, 0.0);
	draw_button(esContext, "_border_x--", VIEW_MODE_SYSTEM, "[-]", FONT_GREEN, 0.85, 0.4, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_x, -2.0);
	draw_button(esContext, "_border_x++", VIEW_MODE_SYSTEM, "[+]", FONT_GREEN, 0.95, 0.4, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_x, 2.0);

	draw_button(esContext, "_border_y", VIEW_MODE_SYSTEM, "Y-Border", FONT_GREEN, 0.55, 0.5, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_y, 0.0);
	draw_button(esContext, "_border_y--", VIEW_MODE_SYSTEM, "[-]", FONT_GREEN, 0.85, 0.5, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_y, -2.0);
	draw_button(esContext, "_border_y++", VIEW_MODE_SYSTEM, "[+]", FONT_GREEN, 0.95, 0.5, 0.002, 0.05, ALIGN_LEFT, ALIGN_TOP, system_set_border_y, 2.0);


	draw_button(esContext, "copyright", VIEW_MODE_SYSTEM, "Copyright by Oliver Dippel (oliver@multixmedia.org)", FONT_PINK, 0.0, 0.9, 0.002, 0.04, ALIGN_CENTER, ALIGN_TOP, system_null, 0.0);


	screen_device(esContext);
	screen_baud(esContext);
}


