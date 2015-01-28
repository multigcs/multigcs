
#include <all.h>

uint8_t clientmode = 0;
char clientmode_server[1024];
uint16_t clientmode_port = 8080;

#ifndef WINDOWS

void webclient_mavlink_get (char *server, uint16_t port) {
	int sockfd;
	int n = 0;
	char tmp_str[1024];
	char sendline[1024];
	char recvline[5001];
	struct sockaddr_in servaddr;
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		return;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(server);
	servaddr.sin_port = htons(port);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	sprintf(sendline, "GET /mavlink_value_get HTTP/1.1\nHost: %s:%i\n\n", server, port);
	sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

	SDL_Delay(100);

	n = recvfrom(sockfd, recvline, 5000, 0, NULL, NULL);
	recvline[n] = 0;

	for (n = 5; n < strlen(recvline); n++) {
		if (recvline[n] == '\n') {
			strncpy(tmp_str, recvline + n + 1, 100);
			int id1 = 0;
			int id2 = 0;
			char name[100];
			float value = 0.0;
			int type = 0;
			sscanf(tmp_str, "%i %i %[0-9a-zA-Z_] %f %i", &id1, &id2, name, &value, &type);
			mavlink_set_value(0, name, value, type, -1);
//			SDL_Log("webserv: ## %s = %f ##\n", name, value);
		}
	}
	close(sockfd);
}

void webclient_update (char *server, uint16_t port) {
	int sockfd;
	int n = 0;
	char tmp_str[100];
	char sendline[100];
	char recvline[1024];
	struct sockaddr_in servaddr;
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		return;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(server);
	servaddr.sin_port = htons(port);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	sprintf(sendline, "GET /modeldata HTTP/1.1\nHost: %s:%i\n\n", server, port);

	sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	n = recvfrom(sockfd, recvline, 1023, 0, NULL, NULL);
	recvline[n] = 0;

	int flag = 0;
	int l = 0;
	int l2 = 0;
	int start = 0;
	for (n = 5; n < strlen(recvline); n++) {
		if (recvline[n] == '\n') {
			strncpy(tmp_str, recvline + n + 1, 99);
			tmp_str[99] = 0;
			l2 = strlen(tmp_str);
			for (l = 0; l < l2; l++) {
				if (tmp_str[l] == '=') {
					tmp_str[l] = 0;
					start = l + 1;
				} else if (tmp_str[l] == '\n') {
					tmp_str[l] = 0;
					break;
				}
			}
//			SDL_Log("webserv: ## %s ### %s (%i)##\n", tmp_str, tmp_str + start, start);

			if (strcmp(tmp_str, "name") == 0) {
				strncpy(ModelData[ModelActive].name, tmp_str + start, 199);
			} else if (strcmp(tmp_str, "image") == 0) {
				strncpy(ModelData[ModelActive].image, tmp_str + start, 511);
			} else if (strcmp(tmp_str, "modeltype") == 0) {
				ModelData[ModelActive].modeltype = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "teletype") == 0) {
				ModelData[ModelActive].teletype = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "telemetry_port") == 0) {
				strncpy(ModelData[ModelActive].telemetry_port, tmp_str + start, 199);
			} else if (strcmp(tmp_str, "telemetry_baud") == 0) {
				ModelData[ModelActive].telemetry_baud = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "telebtaddr") == 0) {
				strncpy(ModelData[ModelActive].telebtaddr, tmp_str + start, 199);
			} else if (strcmp(tmp_str, "telebtpin") == 0) {
				strncpy(ModelData[ModelActive].telebtpin, tmp_str + start, 199);
			} else if (strcmp(tmp_str, "mode") == 0) {
				ModelData[ModelActive].mode = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "status") == 0) {
				ModelData[ModelActive].status = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "armed") == 0) {
				ModelData[ModelActive].armed = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "heartbeat") == 0) {
				ModelData[ModelActive].heartbeat = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "heartbeat_rc") == 0) {
				ModelData[ModelActive].heartbeat_rc = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "found_rc") == 0) {
				ModelData[ModelActive].found_rc = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "p_lat") == 0) {
				ModelData[ModelActive].p_lat = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "p_long") == 0) {
				ModelData[ModelActive].p_long = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "p_alt") == 0) {
				ModelData[ModelActive].p_alt = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "alt_offset") == 0) {
				ModelData[ModelActive].alt_offset = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "baro") == 0) {
				ModelData[ModelActive].baro = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "pitch") == 0) {
				ModelData[ModelActive].pitch = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "roll") == 0) {
				ModelData[ModelActive].roll = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "yaw") == 0) {
				ModelData[ModelActive].yaw = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "speed") == 0) {
				ModelData[ModelActive].speed = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage") == 0) {
				ModelData[ModelActive].voltage = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "load") == 0) {
				ModelData[ModelActive].load = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "gpsfix") == 0) {
				ModelData[ModelActive].gpsfix = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "numSat") == 0) {
				ModelData[ModelActive].numSat = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio1") == 0) {
				ModelData[ModelActive].radio[0] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio2") == 0) {
				ModelData[ModelActive].radio[1] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio3") == 0) {
				ModelData[ModelActive].radio[2] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio4") == 0) {
				ModelData[ModelActive].radio[3] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio5") == 0) {
				ModelData[ModelActive].radio[4] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio6") == 0) {
				ModelData[ModelActive].radio[5] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio7") == 0) {
				ModelData[ModelActive].radio[6] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio8") == 0) {
				ModelData[ModelActive].radio[7] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio9") == 0) {
				ModelData[ModelActive].radio[8] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio10") == 0) {
				ModelData[ModelActive].radio[9] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio11") == 0) {
				ModelData[ModelActive].radio[10] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio12") == 0) {
				ModelData[ModelActive].radio[11] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio13") == 0) {
				ModelData[ModelActive].radio[12] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio14") == 0) {
				ModelData[ModelActive].radio[13] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio15") == 0) {
				ModelData[ModelActive].radio[14] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio16") == 0) {
				ModelData[ModelActive].radio[15] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "acc_x") == 0) {
				ModelData[ModelActive].acc_x = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "acc_y") == 0) {
				ModelData[ModelActive].acc_y = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "acc_z") == 0) {
				ModelData[ModelActive].acc_z = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "gyro_x") == 0) {
				ModelData[ModelActive].gyro_x = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "gyro_y") == 0) {
				ModelData[ModelActive].gyro_y = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "gyro_z") == 0) {
				ModelData[ModelActive].gyro_z = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "rssi_rx") == 0) {
				ModelData[ModelActive].rssi_rx = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "rssi_tx") == 0) {
				ModelData[ModelActive].rssi_tx = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_rx") == 0) {
				ModelData[ModelActive].voltage_rx = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell1") == 0) {
				ModelData[ModelActive].voltage_zell[0] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell2") == 0) {
				ModelData[ModelActive].voltage_zell[1] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell3") == 0) {
				ModelData[ModelActive].voltage_zell[2] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell4") == 0) {
				ModelData[ModelActive].voltage_zell[3] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell5") == 0) {
				ModelData[ModelActive].voltage_zell[4] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell6") == 0) {
				ModelData[ModelActive].voltage_zell[5] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "temperature1") == 0) {
				ModelData[ModelActive].temperature[0] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "temperature2") == 0) {
				ModelData[ModelActive].temperature[1] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "ampere") == 0) {
				ModelData[ModelActive].ampere = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "sysid") == 0) {
				ModelData[ModelActive].sysid = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "compid") == 0) {
				ModelData[ModelActive].compid = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "mavlink_update") == 0) {
				if (ModelData[ModelActive].mavlink_update < atoi(tmp_str + start)) {
					ModelData[ModelActive].mavlink_update = atoi(tmp_str + start);
					flag = 1;
				}
			}
		}
	}
	close(sockfd);
	if (flag == 1) {
		webclient_mavlink_get(server, port);
		return;
	}
}


void webclient_send_value (char *server, uint16_t port, char *name, float value, int type) {
	int sockfd;
	int n = 0;
	char sendline[100];
	char recvline[1024];
	struct sockaddr_in servaddr;

	SDL_Log("%s %f %i\n", name, value, type);

	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		return;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(server);
	servaddr.sin_port = htons(port);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	sprintf(sendline, "GET /mavlink_value_set?%s=%f&%i HTTP/1.1\nHost: %s:%i\n\n", name, value, type, server, port);

	sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	n = recvfrom(sockfd, recvline, 1023, 0, NULL, NULL);
	recvline[n] = 0;

	close(sockfd);
}

#else
void webclient_update (char *server, uint16_t port) {
}
#endif

