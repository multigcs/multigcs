#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <model.h>


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
//			printf("webserv: ## %s ### %s (%i)##\n", tmp_str, tmp_str + start, start);

			if (strcmp(tmp_str, "name") == 0) {
				strcpy(ModelData.name, tmp_str + start);
			} else if (strcmp(tmp_str, "image") == 0) {
				strcpy(ModelData.image, tmp_str + start);
			} else if (strcmp(tmp_str, "modeltype") == 0) {
				ModelData.modeltype = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "teletype") == 0) {
				ModelData.teletype = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "teledevice") == 0) {
				strcpy(ModelData.teledevice, tmp_str + start);
			} else if (strcmp(tmp_str, "telebaud") == 0) {
				ModelData.telebaud = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "telebtaddr") == 0) {
				strcpy(ModelData.telebtaddr, tmp_str + start);
			} else if (strcmp(tmp_str, "telebtpin") == 0) {
				strcpy(ModelData.telebtpin, tmp_str + start);
			} else if (strcmp(tmp_str, "mode") == 0) {
				ModelData.mode = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "status") == 0) {
				ModelData.status = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "armed") == 0) {
				ModelData.armed = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "heartbeat") == 0) {
				ModelData.heartbeat = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "heartbeat_rc") == 0) {
				ModelData.heartbeat_rc = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "found_rc") == 0) {
				ModelData.found_rc = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "p_lat") == 0) {
				ModelData.p_lat = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "p_long") == 0) {
				ModelData.p_long = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "p_alt") == 0) {
				ModelData.p_alt = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "alt_offset") == 0) {
				ModelData.alt_offset = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "baro") == 0) {
				ModelData.baro = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "pitch") == 0) {
				ModelData.pitch = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "roll") == 0) {
				ModelData.roll = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "yaw") == 0) {
				ModelData.yaw = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "speed") == 0) {
				ModelData.speed = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage") == 0) {
				ModelData.voltage = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "load") == 0) {
				ModelData.load = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "gpsfix") == 0) {
				ModelData.gpsfix = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "numSat") == 0) {
				ModelData.numSat = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio1") == 0) {
				ModelData.radio[0] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio2") == 0) {
				ModelData.radio[1] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio3") == 0) {
				ModelData.radio[2] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio4") == 0) {
				ModelData.radio[3] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio5") == 0) {
				ModelData.radio[4] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio6") == 0) {
				ModelData.radio[5] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio7") == 0) {
				ModelData.radio[6] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio8") == 0) {
				ModelData.radio[7] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio9") == 0) {
				ModelData.radio[8] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio10") == 0) {
				ModelData.radio[9] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio11") == 0) {
				ModelData.radio[10] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio12") == 0) {
				ModelData.radio[11] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio13") == 0) {
				ModelData.radio[12] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio14") == 0) {
				ModelData.radio[13] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio15") == 0) {
				ModelData.radio[14] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "radio16") == 0) {
				ModelData.radio[15] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "acc_x") == 0) {
				ModelData.acc_x = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "acc_y") == 0) {
				ModelData.acc_y = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "acc_z") == 0) {
				ModelData.acc_z = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "gyro_x") == 0) {
				ModelData.gyro_x = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "gyro_y") == 0) {
				ModelData.gyro_y = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "gyro_z") == 0) {
				ModelData.gyro_z = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "rssi_rx") == 0) {
				ModelData.rssi_rx = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "rssi_tx") == 0) {
				ModelData.rssi_tx = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_rx") == 0) {
				ModelData.voltage_rx = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell1") == 0) {
				ModelData.voltage_zell[0] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell2") == 0) {
				ModelData.voltage_zell[1] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell3") == 0) {
				ModelData.voltage_zell[2] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell4") == 0) {
				ModelData.voltage_zell[3] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell5") == 0) {
				ModelData.voltage_zell[4] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "voltage_zell6") == 0) {
				ModelData.voltage_zell[5] = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "temperature1") == 0) {
				ModelData.temperature[0] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "temperature2") == 0) {
				ModelData.temperature[1] = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "ampere") == 0) {
				ModelData.ampere = atof(tmp_str + start);
			} else if (strcmp(tmp_str, "sysid") == 0) {
				ModelData.sysid = atoi(tmp_str + start);
			} else if (strcmp(tmp_str, "compid") == 0) {
				ModelData.compid = atoi(tmp_str + start);
			}
		}
	}
	close(sockfd);
}



