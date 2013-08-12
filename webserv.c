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
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_events.h>
#include <model.h>

extern void save_screenshot2 (void);

#define BUFSIZE 18096
#define PI 3.14159265

SDL_Thread *thread_webserv = NULL;


void webserv_child_dump_screen (int fd) {
	static char buffer[BUFSIZE + 1];
	int file_fd;
	long len;
	long ret;
	save_screenshot2();
	if ((file_fd = open("/tmp/dump.png",O_RDONLY)) == -1) {
		return;
	}
	len = lseek(file_fd, (off_t)0, SEEK_END);
	lseek(file_fd, (off_t)0, SEEK_SET);
	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", len, "image/png");
	write(fd, buffer, strlen(buffer));
	while ((ret = read(file_fd, buffer, BUFSIZE)) > 0) {
		write(fd,buffer,ret);
	}
}

void webserv_child_dump_modeldata (int fd) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[100];

	content[0] = 0;
	sprintf(tmp_str, "name=%s\n", ModelData.name);
	strcat(content, tmp_str);
	sprintf(tmp_str, "image=%s\n", ModelData.image);
	strcat(content, tmp_str);
	sprintf(tmp_str, "modeltype=%i\n", ModelData.modeltype);
	strcat(content, tmp_str);
	sprintf(tmp_str, "teletype=%i\n", ModelData.teletype);
	strcat(content, tmp_str);
	sprintf(tmp_str, "teledevice=%s\n", ModelData.teledevice);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telebaud=%i\n", ModelData.telebaud);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telebtaddr=%s\n", ModelData.telebtaddr);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telebtpin=%s\n", ModelData.telebtpin);
	strcat(content, tmp_str);
	sprintf(tmp_str, "mode=%i\n", ModelData.mode);
	strcat(content, tmp_str);
	sprintf(tmp_str, "status=%i\n", ModelData.status);
	strcat(content, tmp_str);
	sprintf(tmp_str, "armed=%i\n", ModelData.armed);
	strcat(content, tmp_str);
	sprintf(tmp_str, "heartbeat=%i\n", ModelData.heartbeat);
	strcat(content, tmp_str);
	sprintf(tmp_str, "heartbeat_rc=%i\n", ModelData.heartbeat_rc);
	strcat(content, tmp_str);
	sprintf(tmp_str, "found_rc=%i\n", ModelData.found_rc);
	strcat(content, tmp_str);
	sprintf(tmp_str, "p_lat=%f\n", ModelData.p_lat);
	strcat(content, tmp_str);
	sprintf(tmp_str, "p_long=%f\n", ModelData.p_long);
	strcat(content, tmp_str);
	sprintf(tmp_str, "p_alt=%f\n", ModelData.p_alt);
	strcat(content, tmp_str);
	sprintf(tmp_str, "alt_offset=%f\n", ModelData.alt_offset);
	strcat(content, tmp_str);
	sprintf(tmp_str, "baro=%f\n", ModelData.baro);
	strcat(content, tmp_str);
	sprintf(tmp_str, "pitch=%f\n", ModelData.pitch);
	strcat(content, tmp_str);
	sprintf(tmp_str, "roll=%f\n", ModelData.roll);
	strcat(content, tmp_str);
	sprintf(tmp_str, "yaw=%f\n", ModelData.yaw);
	strcat(content, tmp_str);
	sprintf(tmp_str, "speed=%f\n", ModelData.speed);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage=%f\n", ModelData.voltage);
	strcat(content, tmp_str);
	sprintf(tmp_str, "load=%f\n", ModelData.load);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gpsfix=%i\n", ModelData.gpsfix);
	strcat(content, tmp_str);
	sprintf(tmp_str, "numSat=%i\n", ModelData.numSat);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[0]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[1]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[2]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[3]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[4]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[5]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[6]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[7]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[8]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[9]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[10]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[11]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[12]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[13]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[14]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[15]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "acc_x=%f\n", ModelData.acc_x);
	strcat(content, tmp_str);
	sprintf(tmp_str, "acc_y=%f\n", ModelData.acc_y);
	strcat(content, tmp_str);
	sprintf(tmp_str, "acc_z=%f\n", ModelData.acc_z);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gyro_x=%f\n", ModelData.gyro_x);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gyro_y=%f\n", ModelData.gyro_y);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gyro_z=%f\n", ModelData.gyro_z);
	strcat(content, tmp_str);
	sprintf(tmp_str, "rssi_rx=%i\n", ModelData.rssi_rx);
	strcat(content, tmp_str);
	sprintf(tmp_str, "rssi_tx=%i\n", ModelData.rssi_tx);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_rx=%f\n", ModelData.voltage_rx);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[0]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[1]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[2]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[3]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[4]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[5]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "temperature=%i\n", ModelData.temperature[0]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "temperature=%i\n", ModelData.temperature[1]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "ampere=%f\n", ModelData.ampere);
	strcat(content, tmp_str);
	sprintf(tmp_str, "sysid=%i\n", ModelData.sysid);
	strcat(content, tmp_str);
	sprintf(tmp_str, "compid=%i\n", ModelData.compid);
	strcat(content, tmp_str);

	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));

}

void webserv_child_draw_hud (int fd) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[100];

	content[0] = 0;

	strcat(content, "<!DOCTYPE HTML>");
	strcat(content, "<html>");
	strcat(content, "  <head>");
	strcat(content, "    <style>");
	strcat(content, "      body {");
	strcat(content, "        margin: 0px;");
	strcat(content, "        padding: 0px;");
	strcat(content, "      }");
	strcat(content, "    </style>");
	strcat(content, "  </head>");
	strcat(content, "  <body>");
	strcat(content, "    <canvas id=\"myCanvas\" width=\"800\" height=\"600\"></canvas>");
	strcat(content, "    <script>");
	strcat(content, "      var canvas = document.getElementById('myCanvas');");
	strcat(content, "      var context = canvas.getContext('2d');");
	strcat(content, "      var centerX = canvas.width / 2;");
	strcat(content, "      var centerY = canvas.height / 2;");
	strcat(content, "      var radius = 170;");
	strcat(content, "      context.beginPath();");

	sprintf(tmp_str, "      context.arc(centerX, centerY, radius, %f, %f, false);", ModelData.roll * PI / 180.0, ModelData.roll * PI / 180.0 + PI);
	strcat(content, tmp_str);

	strcat(content, "      context.fillStyle = 'green';");
	strcat(content, "      context.fill();");
	strcat(content, "      context.lineWidth = 5;");
	strcat(content, "      context.strokeStyle = '#003300';");
	strcat(content, "      context.stroke();");
	strcat(content, "    </script>");
	strcat(content, "  </body>");
	strcat(content, "</html>");

	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_show_lonlat (int fd) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	sprintf(content, "%f, %f", ModelData.p_long, ModelData.p_lat);
	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}


void webserv_child_show_map (int fd) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;

	strcat(content, "<html><head><title>MultiGCS</title><script language=\"Javascript\">\n");
	strcat(content, "function xmlhttpGet() {\n");
	strcat(content, "    var xmlHttpReq = false;\n");
	strcat(content, "    var self = this;\n");
	strcat(content, "    if (window.XMLHttpRequest) {\n");
	strcat(content, "        self.xmlHttpReq = new XMLHttpRequest();\n");
	strcat(content, "    } else if (window.ActiveXObject) {\n");
	strcat(content, "        self.xmlHttpReq = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.open('GET', \"/lonlat\", true);\n");
	strcat(content, "    self.xmlHttpReq.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\n");
	strcat(content, "    self.xmlHttpReq.onreadystatechange = function() {\n");
	strcat(content, "        if (self.xmlHttpReq.readyState == 4) {\n");
	strcat(content, "            updatepage(self.xmlHttpReq.responseText);\n");
	strcat(content, "        }\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.send();\n");
	strcat(content, "}\n");
	strcat(content, "function updatepage(str){\n");
	strcat(content, "    var data = str.split(',')\n");
	strcat(content, "    lonLat = new OpenLayers.LonLat(data[0], data[1]).transform(new OpenLayers.Projection(\"EPSG:4326\"),map.getProjectionObject());\n");
	strcat(content, "    markers.addMarker(new OpenLayers.Marker(lonLat));\n");
	strcat(content, "    map.setCenter (lonLat, zoom);\n");
	strcat(content, "}\n");
	strcat(content, "</script></head><body>\n");
	strcat(content, "<p onclick='JavaScript:xmlhttpGet();'>test</p>\n");
	strcat(content, "<div id=\"mapdiv\"></div><script src=\"http://www.openlayers.org/api/OpenLayers.js\"></script><script>\n");
	strcat(content, "map = new OpenLayers.Map(\"mapdiv\");\n");
	strcat(content, "map.addLayer(new OpenLayers.Layer.OSM());\n");
	sprintf(tmp_str, "var lonLat = new OpenLayers.LonLat( %f ,%f ).transform(new OpenLayers.Projection(\"EPSG:4326\"),map.getProjectionObject());\n", ModelData.p_long, ModelData.p_lat);
	strcat(content, tmp_str);
	strcat(content, "var zoom=16;\n");
	strcat(content, "var markers = new OpenLayers.Layer.Markers( \"Markers\" );\n");
	strcat(content, "map.addLayer(markers);\n");
	strcat(content, "markers.addMarker(new OpenLayers.Marker(lonLat));\n");
	strcat(content, "map.setCenter (lonLat, zoom);\n");
	strcat(content, "</script></body></html>\n");

	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));

}

void webserv_child (int fd, int hit) {
	long ret;
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];

	ret =read(fd, buffer, BUFSIZE);
	buffer[ret] = 0;

	printf("webserv: %s\n", buffer);

	if (strncmp(buffer,"GET ", 4) && strncmp(buffer,"get ", 4)) {
		printf("error2\n");
		exit(1);
	}


	if (strncmp(buffer + 4,"/modeldata", 10) == 0) {
		webserv_child_dump_modeldata(fd);
	} else if (strncmp(buffer + 4,"/screenshot", 11) == 0) {
		webserv_child_dump_screen(fd);
	} else if (strncmp(buffer + 4,"/hud", 4) == 0) {
		webserv_child_draw_hud(fd);
	} else if (strncmp(buffer + 4,"/map", 4) == 0) {
		webserv_child_show_map(fd);
	} else if (strncmp(buffer + 4,"/lonlat", 7) == 0) {
		webserv_child_show_lonlat(fd);
	} else {
		sprintf(content, "UNKNOWN\n");
		sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/plain");
		write(fd, buffer, strlen(buffer));
		write(fd, content, strlen(content));
	}


//	sleep(1);
	close(fd);
	exit(1);
}

int webserv_thread (void *data) {
	int pid;
	int listenfd;
	int socketfd;
	int hit;
	socklen_t length;
	static struct sockaddr_in cli_addr;
	static struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(8080);

	if ((listenfd = socket(AF_INET, SOCK_STREAM,0)) < 0) {
		return(1);
	}
	if (bind(listenfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
		return(1);
	}
	if (listen(listenfd,64) < 0) {
		return(1);
	}
	for (hit = 1;; hit++) {
		length = sizeof(cli_addr);
		if ((socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length)) < 0) {
			return(1);
		}

printf("incomming: %i\n", hit);

		if ((pid = fork()) < 0) {
			return(1);
		} else {
			if (pid == 0) {
				close(listenfd);
				webserv_child(socketfd,hit);
			} else {
				close(socketfd);
			}
		}
	}

	printf("** exit thread webserv\n");
	return(0);
}

void webserv_init (void) {
	printf("Init Webserv-Thread\n");
	thread_webserv = SDL_CreateThread(webserv_thread, NULL);
	if (thread_webserv == NULL) {
		fprintf(stderr, "Webserv-Thread konnte nicht gestartet werden: %s\n", SDL_GetError());
	}
}

void webserv_exit (void) {
	printf("* webserv-thread kill\n");
	SDL_KillThread(thread_webserv);
}

