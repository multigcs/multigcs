
#include <libudev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <math.h>
#include <userdata.h>
#include <serial.h>
#include <main.h>
#include <model.h>
#include <screen_model.h>
#include <screen_rctransmitter.h>
#include <screen_rctransmitter_load.h>
#include <my_mavlink.h>
#include <frsky.h>
#include <SDL/SDL_thread.h>

enum {
	FLAG_CALIBRATION,
	FLAG_2,
	FLAG_3,
	FLAG_4,
	FLAG_5,
	FLAG_6,
	FLAG_7,
	FLAG_8,
};


SDL_Thread *sdl_thread_get_image;

char new_name[200];
uint8_t new_name_cnt = 0;
char channel_names[16][20];
char channel_names_sources[32][20];
char rctransmitter_name[200];
char rctransmitter_btaddr[20];
char rctransmitter_device[20];
char rctransmitter_type_names[TELETYPE_LAST][32];
int8_t rctransmitter_last_change = -1;
int8_t rctransmitter_value[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int8_t rctransmitter_input[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int8_t rctransmitter_last_input[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int8_t rctransmitter_dualrate[8] = {100, 100, 100, 100, 100, 100, 100, 100};
int8_t rctransmitter_reverse[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int8_t rctransmitter_expo[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int8_t rctransmitter_center[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int8_t rctransmitter_channels[8] = {0, 1, 2, 3, 8, 9, 10, 11};
int8_t rctransmitter_trimm[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
int8_t rctransmitter_flags[8] = {0, 0, 0, 0, 0, 0, 0, 0};

uint8_t rctransmitter_name_edit_mode = 0;
uint8_t rctransmitter_btpin_edit_mode = 0;
uint8_t rctransmitter_btscan_mode = 0;
uint8_t rctransmitter_baud_change_mode = 0;
int8_t rctransmitter_channels_select_mode = -1;
int8_t rctransmitter_trimm_select_mode = -1;
char rctransmitter_btscan_list[10][200];
char rctransmitter_btpin[20];
uint8_t rctransmitter_device_select_mode = 0;
uint32_t rctransmitter_baud = 115200;
uint8_t rctransmitter_image_change_mode = 0;
uint8_t rctransmitter_image_flag = 0;
char rctransmitter_image[1024];
int8_t diff[2];
char diff_name[2][100];
int serial_open(char *mdevice, uint32_t baud);
uint8_t startup = 0;
static int serial_fd_rc = -1;
int c, res;
char serial_buf[255];
static uint32_t last_connection = 1;

uint8_t rctransmitter_connection_status (void) {
	if (serial_fd_rc == -1) {
		return 0;
	}
	return last_connection;
}

uint8_t get_device (char *device) {
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;
	struct udev_device *dev;
	char device_path[100];
	uint8_t device_ok = 0;
	udev = udev_new();
	if (!udev) {
		printf("Can't create udev\n");
		return 0;
	}
	enumerate = udev_enumerate_new(udev);
	udev_enumerate_add_match_subsystem(enumerate, "hidraw");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);
	udev_list_entry_foreach(dev_list_entry, devices) {
		const char *path;
		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);
		strcpy(device_path, udev_device_get_devnode(dev));
		dev = udev_device_get_parent_with_subsystem_devtype(dev, "usb", "usb_device");
		if (!dev) {
			printf("Unable to find parent usb device.");
			continue;
		}
//		printf("%s\n", udev_device_get_sysattr_value(dev,"product"));
		if (strcmp("239a", udev_device_get_sysattr_value(dev,"idVendor")) == 0 && strcmp("1002", udev_device_get_sysattr_value(dev, "idProduct")) == 0 && strncmp("rCos-UAV", udev_device_get_sysattr_value(dev,"product"), 8) == 0) {
			strcpy(device, device_path);
			printf("Found RC-Device: %s\n", udev_device_get_sysattr_value(dev,"product"));
			device_ok = 1;
		}
		udev_device_unref(dev);
	}
	udev_enumerate_unref(enumerate);
	udev_unref(udev);
	return device_ok;
}

int thread_get_image (void *unused) {
	return(0);
	while (rctransmitter_image_change_mode != 0 && gui_running == 1) {
		system("cd /tmp/ ; mplayer -vo png -frames 1 tv:// > /dev/null 2> /dev/null");
		system("convert -scale 512x512! /tmp/00000001.png /tmp/capture.png");
		rctransmitter_image_flag = 1;
		SDL_Delay(500);
	}
	printf("exit thread get_image\n");
	return(0);
}

uint8_t rctransmitter_eeprom_save (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

int rctransmitter_thread (void *data) {
	return(0);
	while (gui_running == 1) {
		rctransmitter_update();
	}
	printf("exit thread rctransmitter\n");
	return 0;
}

void rctransmitter_init (void) {
	if (startup == 0) {
		startup = 1;
		char device_path[100];
		diff[0] = 0;
		diff_name[0][0] = 0;
		diff[1] = 0;
		diff_name[1][0] = 0;
		if (get_device(device_path) == 1) {
			if ((serial_fd_rc = open(device_path, O_RDWR)) >= 0) {
				SDL_Thread *thread_rctransmitter;
				thread_rctransmitter = SDL_CreateThread(rctransmitter_thread, NULL);
				if ( thread_rctransmitter == NULL ) {
					fprintf(stderr, "RC-Transmitter-Thread konnte nicht gestartet werden: %s\n", SDL_GetError());
				}
			}
		}
	}
}

uint8_t rctransmitter_mavlink_diff (char *name, float x, float y, int8_t button, float data) {
	if (strncmp(name, "RESET", 5) == 0) {
		diff_name[(int)data][0] = 0;
	} else {
		char tmp_str[100];
		int num = 0;
		sscanf(name, "%s %i", tmp_str, &num);
		strcpy(diff_name[(int)data], tmp_str);
	}
	rctransmitter_save();
	return 0;
}

void rctransmitter_set (void) {
	uint8_t src[256];
	int n = 0;
	if (startup == 0) {
		rctransmitter_init();
	}
	if (serial_fd_rc != -1) {
		src[0] = 255;
		src[1] = 255;
		src[2] = 'r';
		for (n = 0; n < 8; n++) {
//			printf("rev: %i = %i\n", n, rctransmitter_reverse[n]);
			src[n + 3] = (int8_t)rctransmitter_reverse[n];
		}
		write(serial_fd_rc, src, 8 + 3);
		src[2] = 'd';
		for (n = 0; n < 8; n++) {
			src[n + 3] = (int8_t)rctransmitter_dualrate[n];
		}
		write(serial_fd_rc, src, 8 + 3);
		src[2] = 'c';
		for (n = 0; n < 8; n++) {
			src[n + 3] = (int8_t)rctransmitter_center[n];
		}
		write(serial_fd_rc, src, 8 + 3);
		src[2] = 'C';
		for (n = 0; n < 8; n++) {
			src[n + 3] = (int8_t)rctransmitter_channels[n];
		}
		write(serial_fd_rc, src, 8 + 3);
		src[2] = 't';
		for (n = 0; n < 8; n++) {
			src[n + 3] = (int8_t)rctransmitter_trimm[n];
		}
		write(serial_fd_rc, src, 8 + 3);
		src[2] = 'f';
		for (n = 0; n < 8; n++) {
			src[n + 3] = (int8_t)rctransmitter_flags[n];
		}
		write(serial_fd_rc, src, 8 + 3);
	}
}

void rctransmitter_save (void) {
	rctransmitter_set();
	if (rctransmitter_name[0] == 0) {
		return;
	}
	printf("save model: %s\n", rctransmitter_name);
	FILE *fr;
	int n = 0;
	char line[101];
	system("mkdir -p /usr/share/gl-gcs/models");
	sprintf(line, "/usr/share/gl-gcs/models/%s", rctransmitter_name);
	fr = fopen(line, "w");
	if (fr != 0) {
		fprintf(fr, "type	%i\n", ModelData.teletype);
		fprintf(fr, "dualrate	");
		for (n = 0; n < 8; n++) {
		        fprintf(fr, "%i ", rctransmitter_dualrate[n]);
		}
	        fprintf(fr, "\n");
	        fprintf(fr, "reverse	");
		for (n = 0; n < 8; n++) {
		        fprintf(fr, "%i ", rctransmitter_reverse[n]);
		}
	        fprintf(fr, "\n");
	        fprintf(fr, "expo	");
		for (n = 0; n < 8; n++) {
		        fprintf(fr, "%i ", rctransmitter_expo[n]);
		}
	        fprintf(fr, "\n");
	        fprintf(fr, "center	");
		for (n = 0; n < 8; n++) {
		        fprintf(fr, "%i ", rctransmitter_center[n]);
		}
	        fprintf(fr, "\n");
	        fprintf(fr, "trimm	");
		for (n = 0; n < 8; n++) {
		        fprintf(fr, "%i ", rctransmitter_trimm[n]);
		}
	        fprintf(fr, "\n");
	        fprintf(fr, "btaddr	%s\n", rctransmitter_btaddr);
	        fprintf(fr, "btpin	%s\n", rctransmitter_btpin);
	        fprintf(fr, "device	%s\n", rctransmitter_device);
	        fprintf(fr, "baud	%i\n", rctransmitter_baud);
	        fprintf(fr, "image	%s\n", rctransmitter_image);

	        fprintf(fr, "diff_name1	%s\n", diff_name[0]);
	        fprintf(fr, "diff_name2	%s\n", diff_name[1]);

		fclose(fr);
	} else {
		printf("failed to save file: %s\n", line);
	}
}

void bt_reconnect (void) {
	stop_telemetrie();
	if (strstr(rctransmitter_device, "rfcomm") > 0) {
		printf("reconnect bluetooth\n");
		system("rfcomm unbind 0 > /dev/null 2>&1");
		system("killall bluetooth-agent > /dev/null 2>&1");
		usleep(1000000);
		char tmp_str[100];
		sprintf(tmp_str, "nohup bluetooth-agent %s > /tmp/bt_agent.log 2>&1 &", rctransmitter_btpin);
		system(tmp_str);
		printf("# %s \n", tmp_str);
		usleep(2000000);
		sprintf(tmp_str, "nohup rfcomm connect 0 %s > /tmp/bt_connect.log 2>&1 &", rctransmitter_btaddr);
		system(tmp_str);
		printf("# %s \n", tmp_str);
		usleep(5000000);
	}
//	set_telemetrie(rctransmitter_device, rctransmitter_baud);
}

uint8_t rctransmitter_null (char *name, float x, float y, int8_t button, float data) {
	return 0;
}

uint8_t rctransmitter_calibration_start (char *name, float x, float y, int8_t button, float data) {
	rctransmitter_flags[FLAG_CALIBRATION] = (int8_t)data;
	rctransmitter_set();
	return 0;
}

uint8_t rctransmitter_channels_select (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	rctransmitter_channels_select_mode = (int)data;
	rctransmitter_last_change = -1;
	return 0;
}

uint8_t rctransmitter_trimm_select (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	rctransmitter_trimm_select_mode = (int)data;
	rctransmitter_last_change = -1;
	return 0;
}

uint8_t rctransmitter_channels_set (char *name, float x, float y, int8_t button, float data) {
	rctransmitter_channels[(int)data] = atoi(name);
	rctransmitter_channels_select_mode = -1;
	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_trimm_set (char *name, float x, float y, int8_t button, float data) {
	rctransmitter_trimm[(int)data] = atoi(name);
	rctransmitter_trimm_select_mode = -1;
	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_device_select (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	rctransmitter_device_select_mode = 1;
	return 0;
}

uint8_t rctransmitter_device_set (char *name, float x, float y, int8_t button, float data) {
	sprintf(rctransmitter_device, "/dev/%s", name);
	rctransmitter_device_select_mode = 0;
	reset_buttons();
	if (strstr(rctransmitter_device, "rfcomm") > 0) {
		rctransmitter_baud = 115200;
	}
	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_btscan (char *name, float x, float y, int8_t button, float data) {
	rctransmitter_btscan_mode = 1;
	return 0;
}

uint8_t rctransmitter_reconnect (char *name, float x, float y, int8_t button, float data) {
//	if (strstr(rctransmitter_device, "rfcomm") > 0) {
//		bt_reconnect();
//	} else {
//		set_telemetrie(rctransmitter_device, rctransmitter_baud);
//	}
//	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_baud_change (char *name, float x, float y, int8_t button, float data) {
	rctransmitter_baud_change_mode = 1;
	return 0;
}

uint8_t rctransmitter_baud_set (char *name, float x, float y, int8_t button, float data) {
//	rctransmitter_baud = atoi(name);
	rctransmitter_baud_change_mode = 0;
//	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_image_change (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	rctransmitter_image_change_mode = 1;
	sdl_thread_get_image = SDL_CreateThread(thread_get_image, NULL);
	if ( sdl_thread_get_image == NULL ) {
		fprintf(stderr, "Unable to create thread_get_image: %s\n", SDL_GetError());
	}
	return 0;
}

uint8_t rctransmitter_image_set (char *name, float x, float y, int8_t button, float data) {
	char tmp_str[1024];
	if (data == 2.0) {
		strcpy(rctransmitter_image, name);
	} else if (data == 1.0) {
		system("cd /tmp ; mplayer -vo png -frames 1 tv:// > /dev/null 2> /dev/null");
//		sprintf(tmp_str, "/usr/share/gl-gcs/models/%s.png", rctransmitter_name);
//		rename("/tmp/00000001.png", tmp_str);
		sprintf(tmp_str, "convert -scale 512x512! /tmp/00000001.png /usr/share/gl-gcs/models/%s.png", rctransmitter_name);
		system(tmp_str);
		draw_image_uncache(tmp_str);
		strcpy(rctransmitter_image, tmp_str);;
	}
	rctransmitter_image_change_mode = 0;
	rctransmitter_save();
	reset_buttons();
	return 0;
}

uint8_t rctransmitter_btaddr_set (char *name, float x, float y, int8_t button, float data) {
	printf("set BT-Addr: %s\n", name);
	sscanf(name, "%s", (char *)&rctransmitter_btaddr);
	rctransmitter_btscan_mode = 0;
	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_model_load (char *name, float x, float y, int8_t button, float data) {
	view_mode = VIEW_MODE_RCTRANSMITTER_LOAD;
	view_mode_next = VIEW_MODE_RCTRANSMITTER_LOAD;
	return 0;
}

uint8_t rctransmitter_type_change (char *name, float x, float y, int8_t button, float data) {
	if (ModelData.teletype < TELETYPE_LAST - 1) {
		ModelData.teletype++;
	} else {
		ModelData.teletype = 0;
	}
	reset_telemetrie();
	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_dualrate_dec (char *name, float x, float y, int8_t button, float data) {
	if (rctransmitter_dualrate[(int)data] > 0) {
		rctransmitter_dualrate[(int)data]--;
		rctransmitter_save();
	}
	return 0;
}

uint8_t rctransmitter_dualrate_inc (char *name, float x, float y, int8_t button, float data) {
	if (rctransmitter_dualrate[(int)data] < 100) {
		rctransmitter_dualrate[(int)data]++;
		rctransmitter_save();
	}
	return 0;
}

uint8_t rctransmitter_expo_dec (char *name, float x, float y, int8_t button, float data) {
	if (rctransmitter_expo[(int)data] > 0) {
		rctransmitter_expo[(int)data]--;
		rctransmitter_save();
	}
	return 0;
}

uint8_t rctransmitter_expo_inc (char *name, float x, float y, int8_t button, float data) {
	if (rctransmitter_expo[(int)data] < 100) {
		rctransmitter_expo[(int)data]++;
		rctransmitter_save();
	}
	return 0;
}

uint8_t rctransmitter_reverse_toggle (char *name, float x, float y, int8_t button, float data) {
	rctransmitter_reverse[(int)data] = 1 - rctransmitter_reverse[(int)data];
	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_center_dec (char *name, float x, float y, int8_t button, float data) {
	if (rctransmitter_center[(int)data] > -30) {
		rctransmitter_center[(int)data]--;
		rctransmitter_save();
	}
	return 0;
}

uint8_t rctransmitter_center_inc (char *name, float x, float y, int8_t button, float data) {
	if (rctransmitter_center[(int)data] < 30) {
		rctransmitter_center[(int)data]++;
		rctransmitter_save();
	}
	return 0;
}

uint8_t rctransmitter_btpin_cancel (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	rctransmitter_btpin_edit_mode = 0;
	rctransmitter_load_model(rctransmitter_name, 0, 0, 0, 0);
	view_mode = VIEW_MODE_RCTRANSMITTER;
	view_mode_next = VIEW_MODE_RCTRANSMITTER;
	return 0;
}

uint8_t rctransmitter_btpin_save (char *name, float x, float y, int8_t button, float data) {
	new_name[4] = 0;
	reset_buttons();
	strcpy(rctransmitter_btpin, new_name);
	rctransmitter_btpin_edit_mode = 0;
	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_btpin_edit (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	strcpy(new_name, rctransmitter_btpin);
	new_name_cnt = 0;
	rctransmitter_btpin_edit_mode = 1;
	return 0;
}

uint8_t rctransmitter_name_cancel (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	rctransmitter_name_edit_mode = 0;
	rctransmitter_load_model(rctransmitter_name, 0, 0, 0, 0);
	view_mode = VIEW_MODE_RCTRANSMITTER;
	view_mode_next = VIEW_MODE_RCTRANSMITTER;
	return 0;
}

uint8_t rctransmitter_name_save (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	strcpy(rctransmitter_name, new_name);
	rctransmitter_name_edit_mode = 0;
	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_name_edit (char *name, float x, float y, int8_t button, float data) {
	reset_buttons();
	if ((int)data > 0) {
		sprintf(new_name, "model_%i", (int)data);
	} else {
		strcpy(new_name, rctransmitter_name);
	}
	new_name_cnt = 0;
	rctransmitter_name_edit_mode = 1;
	return 0;
}

uint8_t rctransmitter_pos_char (char *name, float x, float y, int8_t button, float data) {
	new_name_cnt = (int)data;
	return 0;
}

uint8_t rctransmitter_add_char (char *name, float x, float y, int8_t button, float data) {
	if (data == 0) {
		new_name[new_name_cnt] = data;
		new_name_cnt--;
	} else if (new_name[new_name_cnt] == 0) {
		new_name[new_name_cnt + 1] = 0;
		new_name[new_name_cnt] = data;
		new_name_cnt++;
	} else {
		new_name[new_name_cnt] = data;
		new_name_cnt++;
	}
	rctransmitter_save();
	return 0;
}

uint8_t rctransmitter_get_type_by_name (char *name) {
	if (strcmp(name, "MULTIWII_21") == 0) {
		return TELETYPE_MULTIWII_21;
	} else if (strcmp(name, "AUTOQUAD") == 0) {
		return TELETYPE_AUTOQUAD;
	} else if (strcmp(name, "ARDUPILOT") == 0) {
		return TELETYPE_ARDUPILOT;
	} else if (strcmp(name, "MEGAPIRATE_NG") == 0) {
		return TELETYPE_MEGAPIRATE_NG;
	} else if (strcmp(name, "OPENPILOT") == 0) {
		return TELETYPE_OPENPILOT;
	} else if (strcmp(name, "GPS_NMEA") == 0) {
		return TELETYPE_GPS_NMEA;
	} else if (strcmp(name, "FRSKY") == 0) {
		return TELETYPE_FRSKY;
	} else if (strcmp(name, "BASEFLIGHT") == 0) {
		return TELETYPE_BASEFLIGHT;
	} else {
		return 255;
	}
	return 0;
}

void rctransmitter_update (void) {
	char tmp_str[100];
	int n = 0;
	int n2 = 0;
	if (startup == 0) {
		strcpy(rctransmitter_type_names[TELETYPE_MULTIWII_21], "MULTIWII_21");
		strcpy(rctransmitter_type_names[TELETYPE_AUTOQUAD], "AUTOQUAD");
		strcpy(rctransmitter_type_names[TELETYPE_ARDUPILOT], "ARDUPILOT");
		strcpy(rctransmitter_type_names[TELETYPE_MEGAPIRATE_NG], "MEGAPIRATE_NG");
		strcpy(rctransmitter_type_names[TELETYPE_OPENPILOT], "OPENPILOT");
		strcpy(rctransmitter_type_names[TELETYPE_GPS_NMEA], "GPS_NMEA");
		strcpy(rctransmitter_type_names[TELETYPE_FRSKY], "FRSKY");
		strcpy(rctransmitter_type_names[TELETYPE_BASEFLIGHT], "BASEFLIGHT");
		rctransmitter_init();
	}
	if (serial_fd_rc != -1) {
		res = read(serial_fd_rc, tmp_str, 36);
		last_connection = time(0);
		if (res < 0) {
			return;
		} else if (tmp_str[2] == 'r') {
			for (n2 = 0; n2 < 8; n2++) {
				rctransmitter_reverse[n2] = (int8_t)tmp_str[n2 + 3];
			}
		} else if (tmp_str[2] == 'p') {
			for (n2 = 0; n2 < 8; n2++) {
				rctransmitter_value[n2] = (int8_t)tmp_str[n2 + 3];
			}
			if (frsky_mode_get() == 1) {
				for (n2 = 0; n2 < 8; n2++) {
					ModelData.radio[n2] = (int8_t)tmp_str[n2 + 3];
				}
			}



		} else if (tmp_str[2] == 'f') {
			for (n2 = 0; n2 < 8; n2++) {
				rctransmitter_flags[n2] = (int8_t)tmp_str[n2 + 3];
			}
		} else if (tmp_str[2] == 'D') {
			for (n2 = 0; n2 < 2; n2++) {
				diff[n2] = (int8_t)tmp_str[n2 + 3];
			}
			if (diff[0] != 0 && diff_name[0][0] != '0') {
				for (n = 0; n < 500 - 1; n++) {
					if (strcmp(MavLinkVars[n].name, diff_name[0]) == 0) {
						MavLinkVars[n].value += (float)diff[0] / 10.0;
						char msg[100];
						sprintf(msg, "%s: %f", MavLinkVars[n].name, MavLinkVars[n].value);
						sys_message(msg);
						mavlink_send_value(MavLinkVars[n].name, MavLinkVars[n].value);
						break;
					}
				}
			}
			if (diff[1] != 0 && diff_name[1][0] != '0') {
				for (n = 0; n < 500 - 1; n++) {
					if (strcmp(MavLinkVars[n].name, diff_name[1]) == 0) {
						MavLinkVars[n].value += (float)diff[1] / 10.0;
						char msg[100];
						sprintf(msg, "%s: %f", MavLinkVars[n].name, MavLinkVars[n].value);
						sys_message (msg);
						break;
					}
				}
			}
		} else if (tmp_str[2] == 'i') {
			uint8_t max = 0;
			for (n2 = 0; n2 < 32; n2++) {
				rctransmitter_input[n2] = (int8_t)tmp_str[n2 + 3];
//				printf("%i: %i \n", n2, (int8_t)rctransmitter_input[n2]);
				if (rctransmitter_last_input[n2] != rctransmitter_input[n2]) {
					if (rctransmitter_last_input[n2] - rctransmitter_input[n2] > 30 ) {
						if (rctransmitter_last_input[n2] - rctransmitter_input[n2] > max ) {
							max = rctransmitter_last_input[n2] - rctransmitter_input[n2];
							rctransmitter_last_change = n2;
						}
					} else if (rctransmitter_input[n2] - rctransmitter_last_input[n2] > 30 ) {
						if (rctransmitter_input[n2] - rctransmitter_last_input[n2] > max ) {
							max = rctransmitter_last_input[n2] - rctransmitter_input[n2];
							rctransmitter_last_change = n2;
						}
					}
				}
				rctransmitter_last_input[n2] = rctransmitter_input[n2];
			}
		}
	}
}


void screen_rctransmitter (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif

	draw_title(esContext, "RC-Transmitter");

	char tmp_str[100];
	char tmp_str2[100];
	int n = 0;
	int n2 = 0;

	strcpy(channel_names_sources[0], "ADC0");
	strcpy(channel_names_sources[1], "ADC1");
	strcpy(channel_names_sources[2], "ADC2");
	strcpy(channel_names_sources[3], "ADC3");
	strcpy(channel_names_sources[4], "ADC4");
	strcpy(channel_names_sources[5], "ADC5");
	strcpy(channel_names_sources[6], "ADC6");
	strcpy(channel_names_sources[7], "ADC7");
	strcpy(channel_names_sources[8], "SW1");
	strcpy(channel_names_sources[9], "SW2");
	strcpy(channel_names_sources[10], "SW3");
	strcpy(channel_names_sources[11], "SW4");
	strcpy(channel_names_sources[12], "SW5");
	strcpy(channel_names_sources[13], "SW6");
	strcpy(channel_names_sources[14], "ROT_ENC1");
	strcpy(channel_names_sources[15], "ROT_ENC2");
	strcpy(channel_names_sources[16], "EXT0");
	strcpy(channel_names_sources[17], "EXT1");
	strcpy(channel_names_sources[18], "EXT2");
	strcpy(channel_names_sources[19], "EXT3");
	strcpy(channel_names_sources[20], "EXT4");
	strcpy(channel_names_sources[21], "EXT5");
	strcpy(channel_names_sources[22], "EXT6");
	strcpy(channel_names_sources[23], "EXT7");


	strcpy(channel_names[0], "ROLL");
	strcpy(channel_names[1], "PITCH");
	strcpy(channel_names[2], "THROTTLE");
	strcpy(channel_names[3], "YAW");
	strcpy(channel_names[4], "AUX1");
	strcpy(channel_names[5], "AUX2");
	strcpy(channel_names[6], "AUX3");
	strcpy(channel_names[7], "AUX4");
	if (ModelData.teletype == TELETYPE_AUTOQUAD) {
		strcpy(channel_names[4], "GEAR");
		strcpy(channel_names[5], "MAN");
		strcpy(channel_names[6], "RTL/SH");
		strcpy(channel_names[7], "AUX3");
	}

#ifndef SDLGL
	esMatrixLoadIdentity(&modelview);
	esMatrixMultiply(&userData->mvpMatrix, &modelview, &userData->perspective);
	esMatrixMultiply(&userData->mvpMatrix2, &modelview, &userData->perspective);
#endif

	if (rctransmitter_btscan_mode > 0) {
		FILE *cmd = NULL;
		char buffer[1025];
		if (rctransmitter_btscan_mode == 1) {
			n = 0;
			if((cmd = popen("LANG=C hcitool scan | grep \"[0-9A-Za-z][0-9A-Za-z]:[0-9A-Za-z][0-9A-Za-z]\"", "r")) != NULL) {
				while(!feof(cmd)) {
					if(fgets(buffer, 1024, cmd) != NULL) {
						strcpy(rctransmitter_btscan_list[n], buffer);
						rctransmitter_btscan_list[n + 1][0] = 0;
						n++;
					}
				}
				pclose(cmd);
			}
		}
		for (n = 0; n < 10; n++) {
			if (rctransmitter_btscan_list[n][0] == 0) {
				break;
			}
			draw_button(esContext, rctransmitter_btscan_list[n], VIEW_MODE_RCTRANSMITTER, rctransmitter_btscan_list[n], FONT_WHITE, -0.5, -0.3 + n * 0.14, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_btaddr_set, n);
		}

		rctransmitter_btscan_mode = 2;
		return;

	} else if (rctransmitter_image_change_mode == 1) {
		sprintf(tmp_str, "BACK");
		draw_button(esContext, "capture_back", VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -0.9, -0.6 + n * 0.2, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, rctransmitter_image_set, 0.0);
		n++;
		sprintf(tmp_str, "CAPTURE");
		draw_button(esContext, "/tmp/capture.png", VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -0.9, -0.6 + n * 0.2, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, rctransmitter_image_set, 1.0);
		if (rctransmitter_image_flag == 1) {
			rctransmitter_image_flag = 0;
			draw_image_uncache("/tmp/capture.png");
		}
		draw_image_f3(esContext, 0.0, -0.6 + n * 0.2 - 0.08, 0.25, -0.6 + n * 0.2 + 0.1, 0.002, "/tmp/capture.png");
		n++;
		DIR *dir = NULL;
		struct dirent *dir_entry = NULL;
		char directory[200];
		sprintf(directory, "/usr/share/gl-gcs/models");
		if ((dir = opendir(directory)) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (strstr(dir_entry->d_name, ".png") > 0) {
					sprintf(tmp_str, "%s/%s", directory, dir_entry->d_name);
					draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, dir_entry->d_name, FONT_WHITE, -0.9, -0.6 + n * 0.2, 0.002, 0.08, ALIGN_LEFT, ALIGN_TOP, rctransmitter_image_set, 2.0);
					draw_image_f3(esContext, 0.0, -0.6 + n * 0.2 - 0.08, 0.25, -0.6 + n * 0.2 + 0.1, 0.002, tmp_str);
					n++;
				}
			}
		}
		return;
	} else if (rctransmitter_baud_change_mode == 1) {
		sprintf(tmp_str, "%i", 9600);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -0.9, -0.6 + n * 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_baud_set, n);
		n++;
		sprintf(tmp_str, "%i", 38400);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -0.9, -0.6 + n * 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_baud_set, n);
		n++;
		sprintf(tmp_str, "%i", 57600);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -0.9, -0.6 + n * 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_baud_set, n);
		n++;
		sprintf(tmp_str, "%i", 115200);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -0.9, -0.6 + n * 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_baud_set, n);
		n++;
		return;
	} else if (rctransmitter_channels_select_mode >= 0) {
		for (n = 0; n < 8; n++) {
			draw_circleMeter_f3(esContext, -0.90 - 0.1, -0.55 + n * 0.08, 0.002, 0.06, 20.0, 50.0, 50.0, 160.0, rctransmitter_input[n] / 2 + 50, "", "", 1);
			sprintf(tmp_str, "%i %s", n, channel_names_sources[n]);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -0.9, -0.6 + n * 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_channels_set, rctransmitter_channels_select_mode);
			if (rctransmitter_channels[rctransmitter_channels_select_mode] == n) {
				draw_text_f3(esContext, -0.9 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, ">");
			}
			if (rctransmitter_last_change == n && (n < 4 || n > 7)) {
				draw_text_f3(esContext, -0.9 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
				rctransmitter_channels_set(tmp_str, 0.0, 0.0, 1, (float)rctransmitter_channels_select_mode);
			} else if (rctransmitter_last_change == n) {
				draw_text_f3(esContext, -0.9 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
			}

			draw_circleMeter_f3(esContext, -0.0 - 0.1, -0.55 + n * 0.08, 0.002, 0.06, 20.0, 50.0, 50.0, 160.0, rctransmitter_input[n + 8] / 2 + 50, "", "", 1);
			sprintf(tmp_str, "%i %s", n + 8, channel_names_sources[n + 8]);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, 0.0, -0.6 + n * 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_channels_set, rctransmitter_channels_select_mode);
			if (rctransmitter_channels[rctransmitter_channels_select_mode] == n + 8) {
				draw_text_f3(esContext, 0.0 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, ">");
			}
			if (rctransmitter_last_change == n + 8 && (n + 8 < 4 || n + 8 > 7)) {
				draw_text_f3(esContext, 0.0 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
				rctransmitter_channels_set(tmp_str, 0.0, 0.0, 1, (float)rctransmitter_channels_select_mode);
			} else if (rctransmitter_last_change == n + 8) {
				draw_text_f3(esContext, 0.0 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
			}

			draw_circleMeter_f3(esContext, 0.6 - 0.1, -0.55 + n * 0.08, 0.002, 0.06, 20.0, 50.0, 50.0, 160.0, rctransmitter_input[n + 16] / 2 + 50, "", "", 1);
			sprintf(tmp_str, "%i %s", n + 16, channel_names_sources[n + 16]);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, 0.6, -0.6 + n * 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_channels_set, rctransmitter_channels_select_mode);
			if (rctransmitter_channels[rctransmitter_channels_select_mode] == n + 16) {
				draw_text_f3(esContext, 0.6 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, ">");
			}
			if (rctransmitter_last_change == n + 16 && (n + 16 < 4 || n + 16 > 7)) {
				draw_text_f3(esContext, 0.6 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
				rctransmitter_channels_set(tmp_str, 0.6, 0.0, 1, (float)rctransmitter_channels_select_mode);
			} else if (rctransmitter_last_change == n + 16) {
				draw_text_f3(esContext, 0.6 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
			}
		}
		return;
	} else if (rctransmitter_trimm_select_mode >= 0) {
		if (rctransmitter_trimm[rctransmitter_trimm_select_mode] == -1) {
			sprintf(tmp_str, ">%i %s", -1, "NONE");
		} else {
			sprintf(tmp_str, "%i %s", -1, "NONE");
		}
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -0.9, -0.6 - 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_trimm_set, rctransmitter_trimm_select_mode);
		for (n = 0; n < 8; n++) {
			draw_circleMeter_f3(esContext, -0.90 - 0.1, -0.55 + n * 0.08, 0.002, 0.06, 20.0, 50.0, 50.0, 160.0, rctransmitter_input[n] / 2 + 50, "", "", 1);
			sprintf(tmp_str, "%i %s", n, channel_names_sources[n]);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -0.9, -0.6 + n * 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_trimm_set, rctransmitter_trimm_select_mode);
			if (rctransmitter_trimm[rctransmitter_trimm_select_mode] == n) {
				draw_text_f3(esContext, -0.9 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, ">");
			}
			if (rctransmitter_last_change == n && (n < 4 || n > 7)) {
				draw_text_f3(esContext, -0.9 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
				rctransmitter_trimm_set(tmp_str, 0.0, 0.0, 1, (float)rctransmitter_trimm_select_mode);
			} else if (rctransmitter_last_change == n) {
				draw_text_f3(esContext, -0.9 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
			}
			draw_circleMeter_f3(esContext, -0.0 - 0.1, -0.55 + n * 0.08, 0.002, 0.06, 20.0, 50.0, 50.0, 160.0, rctransmitter_input[n + 8] / 2 + 50, "", "", 1);
			sprintf(tmp_str, "%i %s", n + 8, channel_names_sources[n + 8]);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, 0.0, -0.6 + n * 0.08, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_trimm_set, rctransmitter_trimm_select_mode);
			if (rctransmitter_trimm[rctransmitter_trimm_select_mode] == n + 8) {
				draw_text_f3(esContext, 0.0 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, ">");
			}
			if (rctransmitter_last_change == n + 8 && (n + 8 < 4 || n + 8 > 7)) {
				draw_text_f3(esContext, 0.0 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
				rctransmitter_trimm_set(tmp_str, 0.0, 0.0, 1, (float)rctransmitter_trimm_select_mode);
			} else if (rctransmitter_last_change == n + 8) {
				draw_text_f3(esContext, 0.0 - 0.05, -0.6 + n * 0.08, 0.002, 0.06, 0.06, FONT_WHITE, "<");
			}
		}
		return;
	} else if (rctransmitter_device_select_mode == 1) {
		DIR *dir = NULL;
		struct dirent *dir_entry = NULL;
		char directory[200];
		uint8_t bt_flag = 0;
		static uint8_t bt_exists = 0;
		sprintf(directory, "/dev");
		if ((dir = opendir(directory)) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (strstr(dir_entry->d_name, "ttyACM") > 0 || strstr(dir_entry->d_name, "ttyS") > 0 || strstr(dir_entry->d_name, "ttyUSB") || strstr(dir_entry->d_name, "ttyAMA") > 0) {
					draw_button(esContext, dir_entry->d_name, VIEW_MODE_RCTRANSMITTER, dir_entry->d_name, FONT_WHITE, -0.5 - 0.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_device_set, n);
					if (strcmp(gcs_gps_port + 5, dir_entry->d_name) == 0) {
						draw_button(esContext, dir_entry->d_name, VIEW_MODE_RCTRANSMITTER, "in use (gps)", FONT_WHITE, -0.5 + 0.4, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_device_set, n);
					}
					if (strcmp(jeti_port + 5, dir_entry->d_name) == 0) {
						draw_button(esContext, dir_entry->d_name, VIEW_MODE_RCTRANSMITTER, "in use (jeti)", FONT_WHITE, -0.5 + 0.4, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_device_set, n);
					}
					n++;
				} else if (strstr(dir_entry->d_name, "rfcomm") > 0) {
					draw_button(esContext, dir_entry->d_name, VIEW_MODE_RCTRANSMITTER, dir_entry->d_name, FONT_WHITE, -0.5 - 0.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_device_set, n);
					bt_flag = 1;
					n++;
				}
			}
		}
		if (bt_exists == 0) {
			if (system("hcitool dev | grep -s -q \":[0-9a-zA-Z]\"") == 0) {
				bt_exists = 1;
			} else {
				bt_exists = 2;
			}
		}
		if (bt_flag == 0 && bt_exists == 1) {
			draw_button(esContext, "rfcomm0", VIEW_MODE_RCTRANSMITTER, "rfcomm0", FONT_WHITE, -0.5 - 0.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_device_set, n);
		}
		return;
	} else if (rctransmitter_btpin_edit_mode == 1) {
		for (n = 0; n < 4; n++) {
			sprintf(tmp_str2, "%c", new_name[n]);
			sprintf(tmp_str, "set_char_%i", n);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str2, FONT_WHITE, -0.9 + n * 0.08, -0.6, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_pos_char, n);
			if (n == new_name_cnt) {
				draw_button(esContext, "mark", VIEW_MODE_RCTRANSMITTER, "^", FONT_WHITE, -0.9 + n * 0.08, -0.5, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_pos_char, n);
			}
		}
		draw_button(esContext, "btpin_save", VIEW_MODE_RCTRANSMITTER, "[SAVE]", FONT_WHITE, 0.3, -0.6, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_btpin_save, 0);
		draw_button(esContext, "rcbtpin_cancel", VIEW_MODE_RCTRANSMITTER, "[CANCEL]", FONT_WHITE, 0.6, -0.6, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_btpin_cancel, 0);
		uint8_t x = 0;
		uint8_t y = 0;
		for (n = 48; n < 59; n++) {
			sprintf(tmp_str2, "%c", n);
			sprintf(tmp_str, "add_char_%i", n);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str2, FONT_WHITE, -1.1 + x * 0.14, -0.3 + y * 0.14, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_add_char, n);
			if (x > 14) {
				y++;
				x = 0;
			} else {
				x++;
			}
		}
		sprintf(tmp_str2, "[END]");
		sprintf(tmp_str, "add_char_%i", 0);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str2, FONT_WHITE, -1.1 + x * 0.14, -0.3 + y * 0.14, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_add_char, 0);
		return;
	} else if (rctransmitter_name_edit_mode == 1) {
		for (n = 0; n < strlen(new_name) + 1; n++) {
			if (new_name[n] != 0) {
				sprintf(tmp_str2, "%c", new_name[n]);
			} else {
				sprintf(tmp_str2, "[END]");
			}
			sprintf(tmp_str, "set_char_%i", n);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str2, FONT_WHITE, -0.9 + n * 0.08, -0.6, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_pos_char, n);
			if (n == new_name_cnt) {
				draw_button(esContext, "mark", VIEW_MODE_RCTRANSMITTER, "^", FONT_WHITE, -0.9 + n * 0.08, -0.5, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_pos_char, n);
			}
		}
		draw_button(esContext, "rcname_save", VIEW_MODE_RCTRANSMITTER, "[SAVE]", FONT_WHITE, 0.3, -0.6, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_name_save, 0);
		draw_button(esContext, "rcname_cancel", VIEW_MODE_RCTRANSMITTER, "[CANCEL]", FONT_WHITE, 0.6, -0.6, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_name_cancel, 0);
		uint8_t x = 0;
		uint8_t y = 0;
		for (n = 33; n < 150; n++) {
			sprintf(tmp_str2, "%c", n);
			sprintf(tmp_str, "add_char_%i", n);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str2, FONT_WHITE, -1.1 + x * 0.14, -0.3 + y * 0.14, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_add_char, n);
			if (x > 14) {
				y++;
				x = 0;
			} else {
				x++;
			}
		}
		sprintf(tmp_str2, "[END]");
		sprintf(tmp_str, "add_char_%i", 0);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, tmp_str2, FONT_WHITE, -1.1 + x * 0.14, -0.3 + y * 0.14, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_add_char, 0);
		return;
	}
	draw_button(esContext, "rctransmitter_model_load", VIEW_MODE_RCTRANSMITTER, "[MODEL]", FONT_WHITE, -1.2, -0.8, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_model_load, 0);
	sprintf(tmp_str, "%s", rctransmitter_name);
	draw_button(esContext, "rctransmitter_name_edit", VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, -1.2 + 0.3, -0.8, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_name_edit, 0);
	draw_button(esContext, "rctransmitter_image_change", VIEW_MODE_RCTRANSMITTER, "[IMAGE]", FONT_WHITE, -0.3, -0.8, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_image_change, 0);

	draw_image_f3(esContext, 0.0, -0.85, 0.2, -0.7, 0.002, rctransmitter_image);
	draw_text_f3(esContext, -0.5 - strlen("DUALRATE") * 0.06 * 0.6 / 2 - 0.012, -0.6, 0.002, 0.06, 0.06, FONT_WHITE, "DUALRATE");
	draw_text_f3(esContext, 0.0 - strlen("EXPONENTIAL") * 0.06 * 0.6 / 2 - 0.012, -0.6, 0.002, 0.06, 0.06, FONT_WHITE, "EXPONENTIAL");
	draw_text_f3(esContext, 0.5 - strlen("REVERSE") * 0.06 * 0.6 / 2 - 0.012, -0.6, 0.002, 0.06, 0.06, FONT_WHITE, "REVERSE");
	draw_text_f3(esContext, 1.0 - strlen("CENTER") * 0.06 * 0.6 / 2 - 0.012, -0.6, 0.002, 0.06, 0.06, FONT_WHITE, "CENTER");
	for (n = 0; n < 8; n++) {
		if (n < 4) {
			draw_circleMeter_f3(esContext, -1.22, -0.43 + n * 0.12, 0.002, 0.06, 20.0, 50.0, 50.0, 160.0, rctransmitter_value[n] / 2 + 50, "", "", 1);
		} else {
			draw_circleMeter_f3(esContext, -1.22, -0.43 + n * 0.12, 0.002, 0.06, 20.0, 33.0, 66.0, 160.0, rctransmitter_value[n] / 2 + 50, "", "", 1);
		}
		draw_circleMeter_f3(esContext, -1.1, -0.41 + n * 0.12, 0.002, 0.03, 20.0, 50.0, 50.0, 160.0, rctransmitter_input[rctransmitter_channels[n]] / 2 + 50, "", "", 1);

		draw_button(esContext, channel_names[n], VIEW_MODE_RCTRANSMITTER, channel_names[n], FONT_WHITE, -1.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_LEFT, ALIGN_TOP, rctransmitter_channels_select, n);
		draw_text_f3(esContext, -1.05, -0.5 + 0.06 + n * 0.12, 0.002, 0.04, 0.04, FONT_WHITE, channel_names_sources[rctransmitter_channels[n]]);

		sprintf(tmp_str, "%i%%", rctransmitter_dualrate[n]);
		draw_text_f3(esContext, -0.5 - strlen(tmp_str) * 0.06 * 0.6 / 2 - 0.012, -0.5 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, tmp_str);
		sprintf(tmp_str, "rctransmitter_%i", n2++);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, "[-]", FONT_WHITE, -0.5 - 0.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_dualrate_dec, n);
		sprintf(tmp_str, "rctransmitter_%i", n2++);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, "[+]", FONT_WHITE, -0.5 + 0.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_dualrate_inc, n);

		sprintf(tmp_str, "%i%%", rctransmitter_expo[n]);
		draw_text_f3(esContext, 0.0 - strlen(tmp_str) * 0.06 * 0.6 / 2 - 0.012, -0.5 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, tmp_str);
		sprintf(tmp_str, "rctransmitter_%i", n2++);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, "[-]", FONT_WHITE, 0.0 - 0.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_expo_dec, n);
		sprintf(tmp_str, "rctransmitter_%i", n2++);
		draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, "[+]", FONT_WHITE, 0.0 + 0.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_expo_inc, n);
		sprintf(tmp_str, "rctransmitter_%i", n2++);
		if (rctransmitter_reverse[n] == 0) {
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, "[NORMAL]", FONT_WHITE, 0.5, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_reverse_toggle, n);
		} else {
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, "[REVERSE]", FONT_WHITE, 0.5, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_reverse_toggle, n);
		}
		if (rctransmitter_trimm[n] != -1) {
			sprintf(tmp_str, "%s", channel_names_sources[rctransmitter_trimm[n]]);
			sprintf(tmp_str2, "trimm_%i%%", n);
			draw_button(esContext, tmp_str2, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, 1.0, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_trimm_select, n);
		} else {
			sprintf(tmp_str, "%i%%", rctransmitter_center[n]);
			sprintf(tmp_str2, "trimm_%i%%", n);
			draw_button(esContext, tmp_str2, VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, 1.0, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_trimm_select, n);
			sprintf(tmp_str, "rctransmitter_%i", n2++);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, "[-]", FONT_WHITE, 1.0 - 0.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_center_dec, n);
			sprintf(tmp_str, "rctransmitter_%i", n2++);
			draw_button(esContext, tmp_str, VIEW_MODE_RCTRANSMITTER, "[+]", FONT_WHITE, 1.0 + 0.15, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_center_inc, n);
		}
	}
	n++;
/*
	draw_text_f3(esContext, -1.15, -0.5 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "DEVICE");
	if (rctransmitter_device[0] == 0) {
		strcpy(rctransmitter_device, "/dev/rfcomm0");
	}
	sprintf(tmp_str, "%s [SELECT]", rctransmitter_device);
	draw_button(esContext, "device_select", VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, 0.3, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_RIGHT, ALIGN_TOP, rctransmitter_device_select, 0);
	sprintf(tmp_str, "%i [CHANGE]", rctransmitter_baud);
	draw_button(esContext, "rc_baud", VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, 1.0, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_RIGHT, ALIGN_TOP, rctransmitter_baud_change, n);
	n++;
	if (strstr(rctransmitter_device, "rfcomm") > 0) {
		draw_text_f3(esContext, -1.15, -0.5 + n * 0.12, 0.002, 0.06, 0.06, FONT_WHITE, "BLUETOOTH");
		if (rctransmitter_btaddr[0] == 0) {
			strcpy(rctransmitter_btaddr, "00:00:00:00:00:00");
		}
		sprintf(tmp_str, "%s [RESCAN]", rctransmitter_btaddr);
		draw_button(esContext, "bt_scan", VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, 0.3, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_RIGHT, ALIGN_TOP, rctransmitter_btscan, n);
		sprintf(tmp_str, "%s [CHANGE]", rctransmitter_btpin);
		draw_button(esContext, "bt_pin", VIEW_MODE_RCTRANSMITTER, tmp_str, FONT_WHITE, 1.0, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_RIGHT, ALIGN_TOP, rctransmitter_btpin_edit, n);
	}
	n++;
	draw_button(esContext, "rcreconnect", VIEW_MODE_RCTRANSMITTER, "[RECONNECT]", FONT_WHITE, 0.0, -0.5 + n * 0.12, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_reconnect, n);

	if (rctransmitter_flags[FLAG_CALIBRATION] == 2) {
		draw_button(esContext, "rccalibration", VIEW_MODE_RCTRANSMITTER, "[CALIBRATION MIN/MAX]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_calibration_start, 3);
	} else if (rctransmitter_flags[FLAG_CALIBRATION] == 3) {
		draw_button(esContext, "rccalibration", VIEW_MODE_RCTRANSMITTER, "[CALIBRATION CENTER]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_calibration_start, 0);
	} else {
		draw_button(esContext, "rccalibration", VIEW_MODE_RCTRANSMITTER, "[CALIBRATION]", FONT_WHITE, 0.0, 0.93, 0.002, 0.04, ALIGN_CENTER, ALIGN_TOP, rctransmitter_calibration_start, 1);
	}

	draw_button(esContext, "RESET 0", VIEW_MODE_RCTRANSMITTER, "[RESET DIFF1]", FONT_WHITE, -1.4, 0.9, 0.002, 0.05, 0, 0, rctransmitter_mavlink_diff, 0);
	draw_button(esContext, "RESET 1", VIEW_MODE_RCTRANSMITTER, "[RESET DIFF2]", FONT_WHITE, -1.0, 0.9, 0.002, 0.05, 0, 0, rctransmitter_mavlink_diff, 1);
*/

	if (rctransmitter_flags[FLAG_CALIBRATION] == 2) {
		draw_button(esContext, "rccalibration", VIEW_MODE_RCTRANSMITTER, "[CALIBRATION MIN/MAX]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_calibration_start, 3);
	} else if (rctransmitter_flags[FLAG_CALIBRATION] == 3) {
		draw_button(esContext, "rccalibration", VIEW_MODE_RCTRANSMITTER, "[CALIBRATION CENTER]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_calibration_start, 0);
	} else {
		draw_button(esContext, "rccalibration", VIEW_MODE_RCTRANSMITTER, "[CALIBRATION]", FONT_WHITE, 0.0, 0.9, 0.002, 0.06, ALIGN_CENTER, ALIGN_TOP, rctransmitter_calibration_start, 1);
	}


}

