
#if defined USE_APRS

#include <all.h>

#define BUFLEN 20

AprsPos aprs_pos[APRS_MAX];
static int aprs_sock = -1;
SDL_Thread *thread_aprs = NULL;

int aprs_thread(void *data) {
	int n = 0;
	SDL_Log("aprs: init thread\n");
	while (gui_running == 1) {
		for (n = 0; n < 1000; n++) {
			aprs_loop();
		}
		SDL_Delay(1);
	}
	SDL_Log("aprs: exit thread\n");
	return 0;
}

int aprs_init(char *server_ip, int port) {
	struct sockaddr_in server;
	int n = 0;
	for (n = 0; n < APRS_MAX; n++) {
		aprs_pos[n].id[0] = 0;
		aprs_pos[n].lat = 0.0;
		aprs_pos[n].lon = 0.0;
		aprs_pos[n].tstamp = 0;
	}
	aprs_sock = socket(AF_INET , SOCK_STREAM , 0);
	if (aprs_sock == -1) {
		perror("aprs: Could not create socket");
		return -1;
	}
	server.sin_addr.s_addr = inet_addr(server_ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (connect(aprs_sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
		perror("aprs: connection failed.");
		return -1;
	}
	puts("aprs: connected.ok\n");
	char sendstr[1024];
	sprintf(sendstr, "user NOCALL pass -1 vers multigcs\n");
	send(aprs_sock, sendstr, strlen(sendstr), 0);
#ifdef SDL2
	thread_aprs = SDL_CreateThread(aprs_thread, NULL, NULL);
#else
	thread_aprs = SDL_CreateThread(aprs_thread, NULL);
#endif
	return aprs_sock;
}

int aprs_exit(void) {
	SDL_WaitThread(thread_aprs, NULL);
	close(aprs_sock);
	aprs_sock = -1;
	return 0;
}

void aprs_pos_update(char *id, float lat, float lon) {
	int n = 0;
	// filter
	float diff_lat = lat - ModelData[ModelActive].p_lat;
	float diff_lon = lon - ModelData[ModelActive].p_long;
	if (diff_lat < 1.0 && diff_lat > -1.0 && diff_lon < 1.0 && diff_lon > -1.0) {
	} else {
		return;
	}
	for (n = 0; n < APRS_MAX; n++) {
		if (strcmp(id, aprs_pos[n].id) == 0) {
			aprs_pos[n].lat = lat;
			aprs_pos[n].lon = lon;
			aprs_pos[n].tstamp = 0;
			//			SDL_Log("aprs: update(%i) %s %f %f\n", n, id, lat, lon);
			return;
		}
	}
	for (n = 0; n < APRS_MAX; n++) {
		if (aprs_pos[n].id[0] == 0) {
			strcpy(aprs_pos[n].id, id);
			aprs_pos[n].lat = lat;
			aprs_pos[n].lon = lon;
			aprs_pos[n].tstamp = 0;
			//			SDL_Log("aprs: add(%i) %s %f %f\n", n, id, lat, lon);
			return;
		}
	}
	SDL_Log("aprs: no slots left %s\n", id);
}

int aprs_loop(void) {
	char ibuffer[1024];
	char comment[1024];
	char latlon[1024];
	char lid[1024];
	char buf[BUFLEN + 1];
	float lat_m = 0.0;
	float lon_m = 0.0;
	float lat_d = 0.0;
	float lon_d = 0.0;
	char lat_c = ' ';
	char lon_c = ' ';
	int len = 0;
	int n = 0;
	int n2 = 0;
	fd_set fds;
	struct timeval ts;
	ts.tv_sec = 1;
	ts.tv_usec = 0;
	FD_ZERO(&fds);
	if (aprs_sock != 0) {
		FD_SET(aprs_sock, &fds);
	}
	FD_SET(0, &fds);
	int nready = select(aprs_sock + 1, &fds, (fd_set *)0, (fd_set *)0, &ts);
	if (nready < 0) {
		perror("aprs: error");
		return 1;
	} else if (nready == 0) {
		ts.tv_sec = 1;
		ts.tv_usec = 0;
	} else if (aprs_sock != 0 && FD_ISSET(aprs_sock, &fds)) {
		int rv;
		if ((rv = recv(aprs_sock , buf , 1 , 0)) < 0) {
			return 1;
		} else if (rv == 0) {
			SDL_Log("aprs: connection closed by the remote end\n");
			return 0;
		}
		len = 1;
		buf[len] = '\0';
		if (buf[len - 1] == '\n') {
			ibuffer[strlen(ibuffer) - 1] = 0;
			//			SDL_Log("aprs: # %s #\n", ibuffer);
			for (n = 0; n < strlen(ibuffer); n++) {
				if (ibuffer[n] == ':') {
					ibuffer[n] = 0;
					strcpy(lid, ibuffer);
					for (n2 = 0; n2 < strlen(lid); n2++) {
						if (lid[n2] == ',') {
							lid[n2] = 0;
							break;
						}
					}
					if (ibuffer[n + 1] == '!' || ibuffer[n + 1] == '=') {
						strcpy(comment, ibuffer + n + 1 + 19 + 1);
						ibuffer[n + 1 + 19] = 0;
						strcpy(latlon, ibuffer + n + 1 + 1);
						lat_m = atof(latlon + 2);
						lon_m = atof(latlon + 9 + 3);
						latlon[2] = 0;
						latlon[9 + 3] = 0;
						lat_d = atof(latlon) + lat_m / 60.0;
						lon_d = atof(latlon + 9) + lon_m / 60.0;
						lat_c = latlon[7];
						lon_c = latlon[17];
					} else if (ibuffer[n + 1] == '/' || ibuffer[n + 1] == '@') {
						n += 7;
						strcpy(comment, ibuffer + n + 1 + 19 + 1);
						ibuffer[n + 1 + 19] = 0;
						strcpy(latlon, ibuffer + n + 1 + 1);
						lat_m = atof(latlon + 2);
						lon_m = atof(latlon + 9 + 3);
						latlon[2] = 0;
						latlon[9 + 3] = 0;
						lat_d = atof(latlon) + lat_m / 60.0;
						lon_d = atof(latlon + 9) + lon_m / 60.0;
						lat_c = latlon[7];
						lon_c = latlon[17];
					} else {
						comment[0] = 0;
						latlon[0] = 0;
					}
					if (lat_d != 0.0 && lon_d != 0.0) {
						//						SDL_Log("### %s #\n", lid);
						//						SDL_Log("##### %f %c #\n", lat_d, lat_c);
						//						SDL_Log("##### %f %c #\n", lon_d, lon_c);
						//						SDL_Log("######## %s #\n", comment);
						if (lat_c == 'S') {
							lat_d *= -1.0;
						}
						if (lon_c == 'W') {
							lon_d *= -1.0;
						}
						aprs_pos_update(lid, lat_d, lon_d);
						//						SDL_Log("\n\n");
					}
					break;
				}
			}
			ibuffer[0] = 0;
		} else {
			strncat(ibuffer, buf, len);
		}
		fflush(0);
	}
	return 1;
}

#endif


