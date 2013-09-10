
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curl/curl.h>
#include <stdio.h>
#include <dirent.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_events.h>
#include <SDL_image.h>

#include <model.h>
#include <userdata.h>
#ifndef SDLGL
#include <gles_draw.h>
#else
#include <gl_draw.h>
#endif
#include <draw.h>
#include <main.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <logging.h>


extern uint16_t webport;
extern void save_screenshot2 (void);
extern volatile uint8_t zoom;
extern uint8_t map_type;
extern char mapnames[20][4][200];

#define BUFSIZE 18096
#define PI 3.14159265

static float blender_first_lat = 0.0;
static float blender_first_long = 0.0;
static float blender_first_alt = 0.0;

Object3d obj3d_collada;

uint8_t webserv_running = 0;
SDL_Thread *thread_webserv = NULL;
int listenfd;

#define header_str "HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %i\nConnection: close\nContent-Type: %s\n\n"

void webserv_child_dump_screen (int fd) {
	char buffer[BUFSIZE + 1];
	int file_fd;
	int len;
	int ret;
	save_screenshot2();
	if ((file_fd = open("/tmp/dump.png",O_RDONLY)) == -1) {
		return;
	}
	len = lseek(file_fd, (off_t)0, SEEK_END);
	lseek(file_fd, (off_t)0, SEEK_SET);
	sprintf(buffer, header_str, len, "image/png");
	write(fd, buffer, strlen(buffer));
	while ((ret = read(file_fd, buffer, BUFSIZE)) > 0) {
		write(fd,buffer,ret);
	}
	close(file_fd);
}

void webserv_child_dump_file (int fd, char *file, char *type) {
	char buffer[BUFSIZE + 1];
	int file_fd;
	int len;
	int ret;
	if ((file_fd = open(file,O_RDONLY)) == -1) {
		printf("webserv: file not found: %s\n", file);
		return;
	}
	len = lseek(file_fd, (off_t)0, SEEK_END);
	lseek(file_fd, (off_t)0, SEEK_SET);
	sprintf(buffer, header_str, len, type);
	write(fd, buffer, strlen(buffer));
	while ((ret = read(file_fd, buffer, BUFSIZE)) > 0) {
		write(fd,buffer,ret);
	}
	close(file_fd);
}

void webserv_child_dump_blender (int fd) {
	char buffer[1024];
	char content[1024];
	char tmp_str[100];

	if (blender_first_lat == 0.0 || blender_first_long == 0.0) {
		blender_first_lat = ModelData.p_lat;
		blender_first_long = ModelData.p_long;
		blender_first_alt = ModelData.p_alt;
	}

	content[0] = 0;
	sprintf(tmp_str, "%f %f %f %f %f %f\n", ModelData.pitch, ModelData.roll, ModelData.yaw, (ModelData.p_lat - blender_first_lat), (ModelData.p_long - blender_first_long), (ModelData.p_alt - blender_first_alt));
	strcat(content, tmp_str);

	sprintf(buffer, header_str, (int)strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_dump_modeldata (int fd) {
	char buffer[BUFSIZE + 1];
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

	sprintf(buffer, header_str, (int)strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));

}

void webserv_child_show_lonlat (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	sprintf(content, "%f, %f", ModelData.p_long, ModelData.p_lat);
	sprintf(buffer, header_str, (int)strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}


void webserv_child_show_hud (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;
	strcat(content, "<html><head><title>MultiGCS</title>\n");
	strcat(content, "<script language=\"Javascript\">\n");
	strcat(content, "function xmlhttpGet() {\n");
	strcat(content, "    var xmlHttpReq = false;\n");
	strcat(content, "    var self = this;\n");
	strcat(content, "    if (window.XMLHttpRequest) {\n");
	strcat(content, "        self.xmlHttpReq = new XMLHttpRequest();\n");
	strcat(content, "    } else if (window.ActiveXObject) {\n");
	strcat(content, "        self.xmlHttpReq = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.open('GET', \"/lonlat.txt\", true);\n");
	strcat(content, "    self.xmlHttpReq.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\n");
	strcat(content, "    self.xmlHttpReq.onreadystatechange = function() {\n");
	strcat(content, "        if (self.xmlHttpReq.readyState == 4) {\n");
	strcat(content, "            updatepage(self.xmlHttpReq.responseText);\n");
	strcat(content, "        }\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.send();\n");
	strcat(content, "    setTimeout(xmlhttpGet, 5000);\n");
	strcat(content, "}\n");
	strcat(content, "function updatepage(str){\n");
	strcat(content, "    var data = str.split(',')\n");
	strcat(content, "    lonLat = new OpenLayers.LonLat(data[0], data[1]).transform(new OpenLayers.Projection(\"EPSG:4326\"),map.getProjectionObject());\n");
	strcat(content, "    markers.addMarker(new OpenLayers.Marker(lonLat));\n");
	strcat(content, "    map.setCenter (lonLat, zoom);\n");
	strcat(content, "}\n");
	strcat(content, "\n");
	strcat(content, "function HUDxmlhttpGet() {\n");
	strcat(content, "    var xmlHttpReq = false;\n");
	strcat(content, "    var self = this;\n");
	strcat(content, "    if (window.XMLHttpRequest) {\n");
	strcat(content, "        self.xmlHttpReq = new XMLHttpRequest();\n");
	strcat(content, "    } else if (window.ActiveXObject) {\n");
	strcat(content, "        self.xmlHttpReq = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.open('GET', \"/hudredraw.js\", true);\n");
	strcat(content, "    self.xmlHttpReq.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\n");
	strcat(content, "    self.xmlHttpReq.onreadystatechange = function() {\n");
	strcat(content, "        if (self.xmlHttpReq.readyState == 4) {\n");
	strcat(content, "            HUDupdatepage(self.xmlHttpReq.responseText);\n");
	strcat(content, "        }\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.send();\n");
	strcat(content, "    setTimeout(HUDxmlhttpGet, 100);\n");
	strcat(content, "}\n");
	strcat(content, "function HUDupdatepage(str){\n");
	strcat(content, "	eval(str);\n");
	strcat(content, "}\n");
	strcat(content, "\n");
	strcat(content, "</script>\n");
	strcat(content, "</head><body>\n");
	strcat(content, "<style type=\"text/css\">\n");
	strcat(content, "body {\n");
	strcat(content, "	background-color:#000000;\n");
	strcat(content, "	color:#FFFFFF;\n");
	strcat(content, "}\n");
	strcat(content, "#mapdiv {\n");
	strcat(content, "    width: 50%;\n");
	strcat(content, "    height: 90%;\n");
	strcat(content, "    position: absolute;\n");
	strcat(content, "    right: 10px;\n");
	strcat(content, "    float: none;\n");
	strcat(content, "}\n");
	strcat(content, "</style>\n");
	strcat(content, "<div class=\"mapdiv\" id=\"mapdiv\"></div>\n");
	strcat(content, "<p onclick='JavaScript:xmlhttpGet();'>[UPDATE]</p>\n");
	strcat(content, "<p onclick='JavaScript:HUDxmlhttpGet();'>[HUD UPDATE]</p>\n");
	strcat(content, "    <canvas id=\"myCanvas\" width=\"640\" height=\"640\"></canvas>\n");
	strcat(content, "    <script>\n");
	strcat(content, "	function drawMeter(context, x, y, r, a, b, c, text) {\n");
	strcat(content, "		var centerX = x;\n");
	strcat(content, "		var centerY = y;\n");
	strcat(content, "		endA = 3.141593 + (3.141593 / 180.0 * a);\n");
	strcat(content, "		endB = 3.141593 + (3.141593 / 180.0 * (a + b));\n");
	strcat(content, "		endC = 3.141593 + (3.141593 / 180.0 * (a + b + c));\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(centerX, centerY, r, 3.141593, endA, false);\n");
	strcat(content, "		context.lineWidth = 10;\n");
	strcat(content, "		context.strokeStyle = 'red';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(centerX, centerY, r, endA, endB, false);\n");
	strcat(content, "		context.lineWidth = 10;\n");
	strcat(content, "		context.strokeStyle = 'yellow';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(centerX, centerY, r, endB, endC, false);\n");
	strcat(content, "		context.lineWidth = 10;\n");
	strcat(content, "		context.strokeStyle = 'green';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "		context.fillStyle = 'white';\n");
	strcat(content, "		context.font = 'bold 10px Arial';\n");
	strcat(content, "		context.textAlign = 'center';\n");
	strcat(content, "		context.fillText(text, x, y + 10);\n");
	strcat(content, "	}\n");
	strcat(content, "	function drawPointer(context, x, y, r, v) {\n");
	strcat(content, "		var centerX = x;\n");
	strcat(content, "		var centerY = y;\n");
	strcat(content, "		A = 3.141593 + (3.141593 / 180.0 * v);\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(centerX, centerY, r / 2.0, A - 0.02, A + 0.02, false);\n");
	strcat(content, "		context.lineWidth = r;\n");
	strcat(content, "		context.strokeStyle = 'white';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "	}\n");
	strcat(content, "	function drawHorizon(context, x, y, s, roll, pitch) {\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.moveTo(x, y);\n");
	strcat(content, "		context.lineTo(x + s, y);\n");
	strcat(content, "		var warning = 0;\n");
	strcat(content, "		diff1 = (s / 2) + (roll / 45.0) * (s / 2) + (pitch / 45.0) * (s / 2);\n");
	strcat(content, "		if (diff1 > s) {diff1 = s; warning = 1;};\n");
	strcat(content, "		if (diff1 < 0) {diff1 = 0; warning = 1;};\n");
	strcat(content, "		diff2 = (s / 2) - (roll / 45.0) * (s / 2) + (pitch / 45.0) * (s / 2);\n");
	strcat(content, "		if (diff2 > s) {diff2 = s; warning = 1;};\n");
	strcat(content, "		if (diff2 < 0) {diff2 = 0; warning = 1;};\n");
	strcat(content, "		context.lineTo(x + s, y + s);\n");
	strcat(content, "		context.lineTo(x, y + s);\n");
	strcat(content, "		context.lineTo(x, y);\n");
	strcat(content, "		context.closePath();\n");
	strcat(content, "		context.fillStyle = 'blue';\n");
	strcat(content, "		context.fill();\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.moveTo(x, y + diff1);\n");
	strcat(content, "		context.lineTo(x + s, y + diff2);\n");
	strcat(content, "		context.lineTo(x + s, y + s);\n");
	strcat(content, "		context.lineTo(x, y + s);\n");
	strcat(content, "		context.lineTo(x, y + diff1);\n");
	strcat(content, "		context.closePath();\n");
	strcat(content, "		context.fillStyle = 'brown';\n");
	strcat(content, "		context.fill();\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.moveTo(x + s, y + diff2);\n");
	strcat(content, "		context.lineTo(x, y + diff1);\n");
	strcat(content, "		context.lineWidth = 3;\n");
	strcat(content, "		if (warning == 0) {\n");
	strcat(content, "			context.strokeStyle = 'white';\n");
	strcat(content, "		} else {\n");
	strcat(content, "			context.strokeStyle = 'red';\n");
	strcat(content, "		}\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.moveTo(x + s, y + (s / 2));\n");
	strcat(content, "		context.lineTo(x, y + (s / 2));\n");
	strcat(content, "		context.lineWidth = 1;\n");
	strcat(content, "		context.strokeStyle = 'gray';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "	}\n");
	strcat(content, "\n");
	strcat(content, "	function drawStar(context, x, y, r) {\n");
	strcat(content, "		var x1 = [x, x, x - r, x + r, x, x, x - r, x + r];\n");
	strcat(content, "		var y1 = [y - r, y + r, y, y, y - r, y + r, y, y];\n");
	strcat(content, "		var x2 = [x + r / 5, x - r / 5, x - r / 5, x + r / 5, x - r / 5, x + r / 5, x - r / 5, x + r / 5];\n");
	strcat(content, "		var y2 = [y - r / 5, y + r / 5, y - r / 5, y + r / 5, y - r / 5, y + r / 5, y + r / 5, y - r / 5];\n");
	strcat(content, "		var col = [0, 0, 0, 0, 1, 1, 1, 1];\n");
	strcat(content, "		for (var index = 0; index < x1.length; ++index) {\n");
	strcat(content, "			context.beginPath();\n");
	strcat(content, "			context.moveTo(x, y);\n");
	strcat(content, "			context.lineTo(x1[index], y1[index]);\n");
	strcat(content, "			context.lineTo(x2[index], y2[index]);\n");
	strcat(content, "			context.lineTo(x, y);\n");
	strcat(content, "			context.closePath();\n");
	strcat(content, "			if (col[index] == 0) {\n");
	strcat(content, "				context.fillStyle = 'black';\n");
	strcat(content, "			} else {\n");
	strcat(content, "				context.fillStyle = 'white';\n");
	strcat(content, "			}\n");
	strcat(content, "			context.fill();\n");
	strcat(content, "			context.lineWidth = 1;\n");
	strcat(content, "			if (col[index] == 0) {\n");
	strcat(content, "				context.strokeStyle = 'white';\n");
	strcat(content, "			} else {\n");
	strcat(content, "				context.strokeStyle = 'black';\n");
	strcat(content, "			}\n");
	strcat(content, "			context.stroke();\n");
	strcat(content, "		}\n");
	strcat(content, "	}\n");
	strcat(content, "\n");
	strcat(content, "	function drawCompas(context, x, y, r, dir) {\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(x, y, r, 0, Math.PI * 2, false);\n");
	strcat(content, "		context.fillStyle = 'black';\n");
	strcat(content, "		context.fill();\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(x, y, r / 2, 0, Math.PI * 2, false);\n");
	strcat(content, "		context.lineWidth = 25;\n");
	strcat(content, "		context.strokeStyle = 'white';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "		context.fillStyle = 'black';\n");
	strcat(content, "		context.fill();\n");
	strcat(content, "		context.translate(x, y);\n");
	strcat(content, "		context.rotate(Math.PI / 4);\n");
	strcat(content, "		context.translate(-x, -y);\n");
	strcat(content, "		drawStar(context, x, y, r / 2);\n");
	strcat(content, "		context.translate(x, y);\n");
	strcat(content, "		context.rotate(-Math.PI / 4);\n");
	strcat(content, "		context.translate(-x, -y);\n");
	strcat(content, "		drawStar(context, x, y, r - 26);\n");
	strcat(content, "		context.fillStyle = 'white';\n");
	strcat(content, "		context.font = 'bold 16px Arial';\n");
	strcat(content, "		context.textAlign = 'center';\n");
	strcat(content, "		context.translate(x, y);\n");
	strcat(content, "		context.rotate(Math.PI / 180 * -dir);\n");
	strcat(content, "		var index;\n");
	strcat(content, "		var D = ['NE', 'E', 'SE', 'S', 'SW', 'W', 'NW', 'N'];\n");
	strcat(content, "		for (var index = 0; index < D.length; ++index) {\n");
	strcat(content, "			context.rotate(Math.PI / 4);\n");
	strcat(content, "			context.fillText(D[index], 0, -r + 15);\n");
	strcat(content, "		}\n");
	strcat(content, "		context.translate(-x, -y);\n");
	strcat(content, "		context.fillStyle = 'white';\n");
	strcat(content, "		context.font = 'bold 10px Arial';\n");
	strcat(content, "		context.textAlign = 'center';\n");
	strcat(content, "		context.translate(x, y);\n");
	strcat(content, "		for (var w = 0; w < 360; w += 30) {\n");
	strcat(content, "			context.fillText(w, 0, -r + 25);\n");
	strcat(content, "			context.rotate(Math.PI / 180 * 30);\n");
	strcat(content, "		}\n");
	strcat(content, "		for (var w = 0; w < 360; w += 10) {\n");
	strcat(content, "			context.fillText('|', 0, -r + 35);\n");
	strcat(content, "			context.rotate(Math.PI / 180 * 10);\n");
	strcat(content, "		}\n");
	strcat(content, "		context.rotate(Math.PI / 180 * dir);\n");
	strcat(content, "		context.translate(-x, -y);\n");
	strcat(content, "	}\n");
	strcat(content, "\n");
	strcat(content, "	var canvas = document.getElementById('myCanvas');\n");
	strcat(content, "	var context = canvas.getContext('2d');\n");
	strcat(content, "	context.clearRect(0, 0, canvas.width, canvas.height);\n");
	strcat(content, "	drawMeter(context, 50, 100, 30, 45, 90, 45, 'roll');\n");
	sprintf(tmp_str, "	drawPointer(context, 50, 100, 30, %f);\n", ModelData.roll + 90.0);
	strcat(content, tmp_str);
	strcat(content, "	drawMeter(context, 50, 200, 30, 45, 90, 45, 'pitch');\n");
	sprintf(tmp_str, "	drawPointer(context, 50, 200, 30, %f);\n", ModelData.pitch + 90.0);
	strcat(content, tmp_str);
	sprintf(tmp_str, "	drawHorizon(context, 100, 50, 400, %f, %f);\n", ModelData.roll, ModelData.pitch);
	strcat(content, tmp_str);
	sprintf(tmp_str, "	drawCompas(context, 300, 500, 150, %f);\n", ModelData.yaw);
	strcat(content, tmp_str);

	strcat(content, "    </script>\n");
	strcat(content, "<script src=\"/map.js\"></script><script>\n");
	strcat(content, "map = new OpenLayers.Map(\"mapdiv\");\n");
	strcat(content, "map.addLayer(new OpenLayers.Layer.OSM());\n");
	sprintf(tmp_str, "var lonLat = new OpenLayers.LonLat( %f ,%f ).transform(new OpenLayers.Projection(\"EPSG:4326\"),map.getProjectionObject());\n", ModelData.p_long, ModelData.p_lat);
	strcat(content, tmp_str);

	sprintf(tmp_str, "var zoom=%i;\n", zoom);
	strcat(content, tmp_str);
	strcat(content, "var markers = new OpenLayers.Layer.Markers( \"Markers\" );\n");
	strcat(content, "map.addLayer(markers);\n");
	strcat(content, "markers.addMarker(new OpenLayers.Marker(lonLat));\n");
	strcat(content, "map.setCenter (lonLat, zoom);\n");
//	strcat(content, "setTimeout(xmlhttpGet, 5000);\n");
	strcat(content, "</script></body></html>\n");

	sprintf(buffer, header_str, (int)strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_hud_redraw (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;

	strcat(content, "	var canvas = document.getElementById('myCanvas');\n");
	strcat(content, "	var context = canvas.getContext('2d');\n");

	strcat(content, "	context.clearRect(0, 0, canvas.width, canvas.height);\n");
	strcat(content, "	drawMeter(context, 50, 100, 30, 45, 90, 45, 'roll');\n");
	sprintf(tmp_str, "	drawPointer(context, 50, 100, 30, %f);\n", ModelData.roll + 90.0);
	strcat(content, tmp_str);
	strcat(content, "	drawMeter(context, 50, 200, 30, 45, 90, 45, 'pitch');\n");
	sprintf(tmp_str, "	drawPointer(context, 50, 200, 30, %f);\n", ModelData.pitch + 90.0);
	strcat(content, tmp_str);
	sprintf(tmp_str, "	drawHorizon(context, 100, 50, 400, %f, %f);\n", ModelData.roll, ModelData.pitch);
	strcat(content, tmp_str);
	sprintf(tmp_str, "	drawCompas(context, 300, 500, 150, %f);\n", ModelData.yaw);
	strcat(content, tmp_str);

	sprintf(buffer, header_str, (int)strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_kml_wp (int fd, char *servername) {
	char buffer[BUFSIZE + 1];
	int n = 0;
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;

	strcat(content, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	strcat(content, "<kml xmlns=\"http://earth.google.com/kml/2.2\">\n");

	strcat(content, "  <Document>\n");
	strcat(content, "    <name>Waypoint-List</name>\n");

	for (n = 0; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[n].name[0] != 0) {
			strcat(content, "    <Placemark>\n");
			sprintf(tmp_str, "      <name>%s</name>\n", WayPoints[n].name);
			strcat(content, tmp_str);
			sprintf(tmp_str, "      <description>%s</description>\n", WayPoints[n].command);
			strcat(content, tmp_str);
			strcat(content, "      <Point>\n");
			strcat(content, "        <extrude>1</extrude>\n");
			strcat(content, "        <altitudeMode>absolute</altitudeMode>\n");
			sprintf(tmp_str, "        <coordinates>%f,%f,%f</coordinates>\n", WayPoints[n].p_long, WayPoints[n].p_lat, WayPoints[n].p_alt);
			strcat(content, tmp_str);
			strcat(content, "      </Point>\n");
			strcat(content, "    </Placemark>\n");
		}
	}

	strcat(content, "    <Style id=\"greenLineYellowPoly\">\n");
	strcat(content, "      <LineStyle>\n");
	strcat(content, "        <color>7f00ff00</color>\n");
	strcat(content, "        <width>4</width>\n");
	strcat(content, "      </LineStyle>\n");
	strcat(content, "      <PolyStyle>\n");
	strcat(content, "        <color>7f00ffff</color>\n");
	strcat(content, "      </PolyStyle>\n");
	strcat(content, "    </Style>\n");
	strcat(content, "    <Placemark>\n");
	strcat(content, "      <name>Route</name>\n");
	strcat(content, "      <description>Datalog</description>\n");
	strcat(content, "      <styleUrl>#greenLineYellowPoly</styleUrl>\n");
	strcat(content, "      <LineString>\n");
	strcat(content, "        <extrude>1</extrude>\n");
	strcat(content, "        <tessellate>1</tessellate>\n");
	strcat(content, "        <altitudeMode>absolute</altitudeMode>\n");
	strcat(content, "        <coordinates>");
	for (n = 0; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[n].name[0] != 0) {
			sprintf(tmp_str, " %f,%f,%f \n", WayPoints[n].p_long, WayPoints[n].p_lat, WayPoints[n].p_alt);
			strcat(content, tmp_str);
		}
	}
	strcat(content, "        </coordinates>\n");
	strcat(content, "      </LineString>\n");
	strcat(content, "    </Placemark>\n");

	strcat(content, "  </Document>\n");
	strcat(content, "</kml>\n");

	sprintf(buffer, header_str, (int)strlen(content), "text/xml");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_kml_index (int fd, char *servername) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;

	strcat(content, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	strcat(content, "<kml xmlns=\"http://earth.google.com/kml/2.2\">\n");

	strcat(content, "  <Document>\n");
	strcat(content, "    <name>MultiGCS</name>\n");
	strcat(content, "    <description>Flight-Data</description>\n");

	strcat(content, "	<NetworkLink>\n");
	sprintf(tmp_str, "		<name>%s</name>\n", "Liveview");
	strcat(content, tmp_str);
	strcat(content, "		<visibility>0</visibility>\n");
	strcat(content, "		<refreshVisibility>0</refreshVisibility>\n");
	strcat(content, "		<open>0</open>\n");
	strcat(content, "		<flyToView>0</flyToView>\n");
	strcat(content, "		<Link>\n");
	sprintf(tmp_str, "			<href>http://%s/live.kml</href>\n", servername);
	strcat(content, tmp_str);
	strcat(content, "		</Link>\n");
	strcat(content, "	</NetworkLink>\n");

	strcat(content, "	<NetworkLink>\n");
	sprintf(tmp_str, "		<name>%s</name>\n", "Pilotview");
	strcat(content, tmp_str);
	strcat(content, "		<visibility>0</visibility>\n");
	strcat(content, "		<refreshVisibility>0</refreshVisibility>\n");
	strcat(content, "		<open>0</open>\n");
	strcat(content, "		<flyToView>0</flyToView>\n");
	strcat(content, "		<Link>\n");
	sprintf(tmp_str, "			<href>http://%s/live-pilot.kml</href>\n", servername);
	strcat(content, tmp_str);
	strcat(content, "		</Link>\n");
	strcat(content, "	</NetworkLink>\n");

	strcat(content, "	<NetworkLink>\n");
	sprintf(tmp_str, "		<name>%s</name>\n", "Waypoints");
	strcat(content, tmp_str);
	strcat(content, "		<visibility>0</visibility>\n");
	strcat(content, "		<refreshVisibility>0</refreshVisibility>\n");
	strcat(content, "		<open>0</open>\n");
	strcat(content, "		<flyToView>0</flyToView>\n");
	strcat(content, "		<Link>\n");
	sprintf(tmp_str, "			<href>http://%s/wp.kml</href>\n", servername);
	strcat(content, tmp_str);
	strcat(content, "		</Link>\n");
	strcat(content, "	</NetworkLink>\n");

	strcat(content, "	<Folder>\n");
	strcat(content, "	 <name>Logdata</name>\n");

	struct tm strukt;
	DIR *dir = NULL;
	struct dirent *dir_entry = NULL;
	struct stat statbuf;
	char new_path[400];
	char tmp_str2[400];
	char directory[400];
	sprintf(directory, "%s/.multigcs/logs", getenv("HOME"));
	if ((dir = opendir(directory)) != NULL) {
		while ((dir_entry = readdir(dir)) != 0) {
			if (dir_entry->d_name[1] != '.') {
				sprintf(new_path, "%s/%s", directory, dir_entry->d_name);
				if (lstat(new_path, &statbuf) == 0) {
					if (statbuf.st_mode&S_IFDIR) {
					} else {
						time_t liczba_sekund = (time_t)(atoi(dir_entry->d_name));
						localtime_r(&liczba_sekund, &strukt);
						FILE *f;
						int pos;
						int end;
						f = fopen(new_path, "r");
						pos = ftell(f);
						fseek(f, 0, SEEK_END);
						end = ftell(f);
						fclose(f);
						if ((end - pos) < 1024) {
							sprintf(tmp_str2, "%02d.%02d.%d %02d:%02d:%02d (%iB)", strukt.tm_mday, strukt.tm_mon + 1, strukt.tm_year + 1900, strukt.tm_hour, strukt.tm_min, strukt.tm_sec, (end - pos));
						} else {
							sprintf(tmp_str2, "%02d.%02d.%d %02d:%02d:%02d (%iKB)", strukt.tm_mday, strukt.tm_mon + 1, strukt.tm_year + 1900, strukt.tm_hour, strukt.tm_min, strukt.tm_sec, (end - pos) / 1024);
						}
						strcat(content, "	<NetworkLink>\n");
						sprintf(tmp_str, "		<name>%s</name>\n", tmp_str2);
						strcat(content, tmp_str);
						strcat(content, "		<visibility>0</visibility>\n");
						strcat(content, "		<refreshVisibility>0</refreshVisibility>\n");
						strcat(content, "		<open>0</open>\n");
						strcat(content, "		<flyToView>0</flyToView>\n");
						strcat(content, "		<Link>\n");
						sprintf(tmp_str, "			<href>http://%s/logkml/%s</href>\n", servername, dir_entry->d_name);
						strcat(content, tmp_str);
						strcat(content, "		</Link>\n");
						strcat(content, "	</NetworkLink>\n");
					}
				}
			}
		}
		closedir(dir);
		dir = NULL;
	}
	strcat(content, "	</Folder>\n");
	strcat(content, "  </Document>\n");
	strcat(content, "</kml>\n");

	sprintf(buffer, header_str, (int)strlen(content), "text/xml");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_kml_live (int fd, uint8_t mode, char *servername) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;

	strcat(content, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	strcat(content, "<kml xmlns=\"http://earth.google.com/kml/2.2\">\n");
	strcat(content, "	<NetworkLink>\n");
	strcat(content, "		<name>MultiGCS</name>\n");
	strcat(content, "		<open>1</open>\n");
	strcat(content, "		<flyToView>1</flyToView>\n");
	strcat(content, "		<Link>\n");
	if (mode == 0) {
		sprintf(tmp_str, "			<href>http://%s/model.kml</href>\n", servername);
	} else {
		sprintf(tmp_str, "			<href>http://%s/pilot.kml</href>\n", servername);
	}
	strcat(content, tmp_str);
	strcat(content, "			<refreshMode>onInterval</refreshMode>\n");
	strcat(content, "			<viewRefreshMode>onStop</viewRefreshMode>\n");
	strcat(content, "			<refreshVisibility>0</refreshVisibility>\n");
	sprintf(tmp_str, "			<refreshInterval>%f</refreshInterval>\n", gearth_interval);
	strcat(content, tmp_str);
	strcat(content, "		</Link>\n");
	strcat(content, "	</NetworkLink>\n");
	strcat(content, "</kml>\n");

	sprintf(buffer, header_str, (int)strlen(content), "text/xml");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_kml_feed (int fd, uint8_t mode, char *servername) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;

	strcat(content, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	strcat(content, "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
	strcat(content, "	<Document>\n");
	strcat(content, "		<Placemark>\n");
	if (mode == 0) {
		strcat(content, "			<name>Model</name>\n");
		strcat(content, "			<Model id=\"model_10\">\n");
		strcat(content, "				<extrude>1</extrude>\n");
		strcat(content, "				<altitudeMode>absolute</altitudeMode>\n");
		strcat(content, "				<Location>\n");
		sprintf(tmp_str, "					<longitude>%f</longitude>\n", ModelData.p_long);
		strcat(content, tmp_str);
		sprintf(tmp_str, "					<latitude>%f</latitude>\n", ModelData.p_lat);
		strcat(content, tmp_str);
		sprintf(tmp_str, "					<altitude>%f</altitude>\n", ModelData.p_alt);
		strcat(content, tmp_str);
		strcat(content, "				</Location>\n");
		strcat(content, "				<Orientation>\n");
		sprintf(tmp_str, "					<tilt>%f</tilt>\n", ModelData.pitch * -1);
		strcat(content, tmp_str);
		sprintf(tmp_str, "					<roll>%f</roll>\n", ModelData.roll * -1);
		strcat(content, tmp_str);
		sprintf(tmp_str, "					<heading>%f</heading>\n", ModelData.yaw);
		strcat(content, tmp_str);
		strcat(content, "				</Orientation>\n");
		strcat(content, "				<Scale>\n");
		strcat(content, "					<x>15</x>\n");
		strcat(content, "					<y>15</y>\n");
		strcat(content, "					<z>15</z>\n");
		strcat(content, "				</Scale>\n");
		strcat(content, "				<Link>\n");
		strcat(content, "					<href>plane.dae</href>\n");
		strcat(content, "				</Link>\n");
		strcat(content, "			</Model>\n");
	} else {
		strcat(content, "			<name>Pilot-View</name>\n");
		strcat(content, "			<Camera>\n");
		strcat(content, "				<altitudeMode>absolute</altitudeMode>\n");
		sprintf(tmp_str, "				<longitude>%f</longitude>\n", ModelData.p_long);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<latitude>%f</latitude>\n", ModelData.p_lat);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<altitude>%f</altitude>\n", ModelData.p_alt);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<heading>%f</heading>\n", ModelData.yaw);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<tilt>%f</tilt>\n", ModelData.pitch + 90.0);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<roll>%f</roll>\n", ModelData.roll * -1);
		strcat(content, tmp_str);
		strcat(content, "			</Camera>\n");
	}

	strcat(content, "		</Placemark>\n");
	strcat(content, "	</Document>\n");
	strcat(content, "</kml>\n");

	sprintf(buffer, header_str, (int)strlen(content), "text/xml");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

extern uint8_t get_background_model (char *filename);

void webserv_child (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[BUFSIZE + 1];
	char servername[1024];

	content[0] = 0;

	SDL_Delay(10);

	int size = 0;
	read(fd, buffer + size, BUFSIZE);

	char *host = NULL;
	if ((host = strstr(buffer, "\nHost: ")) > 0) {
		strncpy(servername, host + 7, 1023);
		if (strstr(servername, "\n") > 0) {
			*strstr(servername, "\n") = 0;
		}
		if (strstr(servername, "\r") > 0) {
			*strstr(servername, "\r") = 0;
		}
	} else {
		servername[0] = 0;
	}

//	printf("webserv: ###########################\n");
//	printf("webserv: servername: %s\n", servername);
//	printf("webserv: ###########################\n");
//	printf("%s\n", buffer);
//	printf("webserv: ###########################\n");


	if (strncmp(buffer,"POST ", 5) == 0 || strncmp(buffer,"post ", 5) == 0) {
		if (strncmp(buffer + 5,"/setdata", 8) == 0) {
			int n = 0;
			int l = 0;
			int l2 = 0;
			int start = 0;
			for (n = 5; n < strlen(buffer); n++) {
				if (buffer[n] == '\n') {
					strncpy(tmp_str, buffer + n + 1, 99);
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
					printf("webserv: ## %s ### %s (%i)##\n", tmp_str, tmp_str + start, start);

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
			sprintf(content, "OK\n");
			sprintf(buffer, header_str, (int)strlen(content), "text/plain");
			write(fd, buffer, strlen(buffer));
			write(fd, content, strlen(content));
		} else {
			sprintf(content, "UNKNOWN\n");
			sprintf(buffer, header_str, (int)strlen(content), "text/plain");
			write(fd, buffer, strlen(buffer));
			write(fd, content, strlen(content));
		}
	} else if (strncmp(buffer,"GET ", 4) == 0 || strncmp(buffer,"get ", 4) == 0) {
		// Misc
		if (strncmp(buffer + 4,"/modeldata", 10) == 0) {
			webserv_child_dump_modeldata(fd);
		} else if (strncmp(buffer + 4,"/blender.txt", 12) == 0) {
			webserv_child_dump_blender(fd);

		} else if (strncmp(buffer + 4,"/blender-export.py", 18) == 0) {
			sprintf(tmp_str, "%s/blender-export.py", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/plain");
			blender_first_lat = ModelData.p_lat;
			blender_first_long = ModelData.p_long;
			blender_first_alt = ModelData.p_alt;
		} else if (strncmp(buffer + 4,"/screenshot", 11) == 0) {
			webserv_child_dump_screen(fd);

		// Google-Earth Live-Feed (Model-Position)
		} else if (strncmp(buffer + 4,"/index.kml", 10) == 0) {
			webserv_child_kml_index(fd, servername);
		} else if (strncmp(buffer + 4,"/wp.kml", 7) == 0) {
			webserv_child_kml_wp(fd, servername);
		} else if (strncmp(buffer + 4,"/live.kml", 9) == 0) {
			webserv_child_kml_live(fd, 0, servername);
		} else if (strncmp(buffer + 4,"/live-pilot.kml", 15) == 0) {
			webserv_child_kml_live(fd, 1, servername);
		} else if (strncmp(buffer + 4,"/model.kml", 8) == 0) {
			webserv_child_kml_feed(fd, 0, servername);
		} else if (strncmp(buffer + 4,"/pilot.kml", 8) == 0) {
			webserv_child_kml_feed(fd, 1, servername);

		} else if (strncmp(buffer + 4,"/simple.dae", 11) == 0) {
#ifdef SDLGL
			sprintf(tmp_str, "%s/webserv/simple.dae", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/xml");
#else
			sprintf(tmp_str, "%s/webserv/plane.dae", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/xml");
#endif
		} else if (strncmp(buffer + 4,"/plane.dae", 10) == 0) {
#ifdef SDLGL
			if (get_background_model(tmp_str) == 0) {
				if (obj3d_collada.name[0] == 0) {
					printf("webserv: convert '%s' to collada-format\n", tmp_str);
					object3d_load_data(&obj3d_collada, tmp_str);
					object3d_save_as_collada(&obj3d_collada, "/tmp/plane.dae");
				}
				webserv_child_dump_file(fd, "/tmp/plane.dae", "text/xml");
			} else {
				sprintf(tmp_str, "%s/webserv/plane.dae", BASE_DIR);
				webserv_child_dump_file(fd, tmp_str, "text/xml");
			}
#else
			sprintf(tmp_str, "%s/webserv/plane.dae", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/xml");
#endif


		} else if (strncmp(buffer + 4,"/logkml/", 8) == 0) {
			int n;
			for (n = 5; n < strlen(buffer); n++) {
				if (buffer[n] == ' ') {
					buffer[n] = 0;
					break;
				}
			}
			if (buffer[12] == 0) {
				content[0] = 0;
				struct tm strukt;
				DIR *dir = NULL;
				struct dirent *dir_entry = NULL;
				struct stat statbuf;
				char new_path[400];
				char tmp_str2[400];
				char directory[400];
				sprintf(directory, "%s/.multigcs/logs", getenv("HOME"));
				if ((dir = opendir(directory)) != NULL) {
					while ((dir_entry = readdir(dir)) != 0) {
						if (dir_entry->d_name[1] != '.') {
							sprintf(new_path, "%s/%s", directory, dir_entry->d_name);
							if (lstat(new_path, &statbuf) == 0) {
								if (statbuf.st_mode&S_IFDIR) {
								} else {
									time_t liczba_sekund = (time_t)(atoi(dir_entry->d_name));
									localtime_r(&liczba_sekund, &strukt);
									FILE *f;
									int pos;
									int end;
									f = fopen(new_path, "r");
									pos = ftell(f);
									fseek(f, 0, SEEK_END);
									end = ftell(f);
									fclose(f);
									if ((end - pos) < 1024) {
										sprintf(tmp_str, "%02d.%02d.%d %02d:%02d:%02d (%iB)", strukt.tm_mday, strukt.tm_mon + 1, strukt.tm_year + 1900, strukt.tm_hour, strukt.tm_min, strukt.tm_sec, (end - pos));
									} else {
										sprintf(tmp_str, "%02d.%02d.%d %02d:%02d:%02d (%iKB)", strukt.tm_mday, strukt.tm_mon + 1, strukt.tm_year + 1900, strukt.tm_hour, strukt.tm_min, strukt.tm_sec, (end - pos) / 1024);
									}
									sprintf(tmp_str2, "<A href=\"%s\">%s</A><BR>", dir_entry->d_name, tmp_str);
									strcat(content, tmp_str2);
								}
							}
						}
					}
					closedir(dir);
					dir = NULL;
				}
				sprintf(buffer, header_str, (int)strlen(content), "text/html");
				write(fd, buffer, strlen(buffer));
				write(fd, content, strlen(content));
			} else {
				char tmp_str2[400];
				sprintf(tmp_str, "%s/.multigcs/logs/%s", getenv("HOME"), buffer + 12);
				sprintf(tmp_str2, "/tmp/%s.kml", buffer + 12);
				logplay_export_kml(tmp_str, tmp_str2, 255);
				webserv_child_dump_file(fd, tmp_str2, "text/xml");
			}


#ifdef HTML_DRAWING
		} else if (strncmp(buffer + 4,"/gui.html", 9) == 0) {
			char display_html3[10000];
			display_html3[0] = 0;
			strcat(display_html3, "	<script>\n");
			strcat(display_html3, "	function draw_box (context, x1, y1, x2, y2, color) {\n");
			strcat(display_html3, "		context.beginPath();\n");
			strcat(display_html3, "		context.moveTo(x1, y1); context.lineTo(x2, y1); context.lineTo(x2, y2); context.lineTo(x1, y2); context.lineTo(x1, y1);\n");
			strcat(display_html3, "		context.fillStyle = color; context.fill();\n");
			strcat(display_html3, "		context.closePath();\n");
			strcat(display_html3, "	}\n");
			strcat(display_html3, "	function draw_rect (context, x1, y1, x2, y2, color) {\n");
			strcat(display_html3, "		context.beginPath();\n");
			strcat(display_html3, "		context.moveTo(x1, y1); context.lineTo(x2, y1); context.lineTo(x2, y2); context.lineTo(x1, y2); context.lineTo(x1, y1);\n");
			strcat(display_html3, "		context.strokeStyle = color; context.stroke();\n");
			strcat(display_html3, "		context.closePath();\n");
			strcat(display_html3, "	}\n");
			strcat(display_html3, "	function draw_tria (context, x1, y1, x2, y2, x3, y3, color) {\n");
			strcat(display_html3, "		context.beginPath();\n");
			strcat(display_html3, "		context.moveTo(x1, y1); context.lineTo(x2, y2); context.lineTo(x3, y3); context.lineTo(x1, y1);\n");
			strcat(display_html3, "		context.strokeStyle = color; context.stroke();\n");
			strcat(display_html3, "		context.closePath();\n");
			strcat(display_html3, "	}\n");
			strcat(display_html3, "	function draw_triaFilled (context, x1, y1, x2, y2, x3, y3, color) {\n");
			strcat(display_html3, "		context.beginPath();\n");
			strcat(display_html3, "		context.moveTo(x1, y1); context.lineTo(x2, y2); context.lineTo(x3, y3); context.lineTo(x1, y1);\n");
			strcat(display_html3, "		context.fillStyle = color; context.fill();\n");
			strcat(display_html3, "		context.closePath();\n");
			strcat(display_html3, "	}\n");
			strcat(display_html3, "	function draw_line (context, x1, y1, x2, y2, color) {\n");
			strcat(display_html3, "		context.beginPath();\n");
			strcat(display_html3, "		context.moveTo(x1, y1); context.lineTo(x2, y2);\n");
			strcat(display_html3, "		context.strokeStyle = color; context.stroke();\n");
			strcat(display_html3, "		context.closePath();\n");
			strcat(display_html3, "	}\n");
			strcat(display_html3, "	function draw_text (context, x1, y1, font, text, color) {\n");
			strcat(display_html3, "		context.beginPath();\n");
			strcat(display_html3, "		context.fillStyle = color;\n");
			strcat(display_html3, "		context.font = font;\n");
			strcat(display_html3, "		context.fillText(text, x1, y1);\n");
			strcat(display_html3, "		context.closePath();\n");
			strcat(display_html3, "	}\n");
			strcat(display_html3, "</script>\n");
			strcat(display_html3, "<script language=\"Javascript\">\n");
			strcat(display_html3, "function xmlhttpGet() {\n");
			strcat(display_html3, "    var xmlHttpReq = false;\n");
			strcat(display_html3, "    var self = this;\n");
			strcat(display_html3, "    if (window.XMLHttpRequest) {\n");
			strcat(display_html3, "        self.xmlHttpReq = new XMLHttpRequest();\n");
			strcat(display_html3, "    } else if (window.ActiveXObject) {\n");
			strcat(display_html3, "        self.xmlHttpReq = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
			strcat(display_html3, "    }\n");
			strcat(display_html3, "    self.xmlHttpReq.open('GET', \"/gui-update.js\", true);\n");
			strcat(display_html3, "    self.xmlHttpReq.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\n");
			strcat(display_html3, "    self.xmlHttpReq.onreadystatechange = function() {\n");
			strcat(display_html3, "        if (self.xmlHttpReq.readyState == 4) {\n");
			strcat(display_html3, "            updatepage(self.xmlHttpReq.responseText);\n");
			strcat(display_html3, "        }\n");
			strcat(display_html3, "    }\n");
			strcat(display_html3, "    self.xmlHttpReq.send();\n");
			strcat(display_html3, "    setTimeout(xmlhttpGet, 1000);\n");
			strcat(display_html3, "}\n");
			strcat(display_html3, "function updatepage(str){\n");
			strcat(display_html3, "	eval(str);\n");
			strcat(display_html3, "}\n");
			strcat(display_html3, "\n");
			strcat(display_html3, "</script>\n");
			strcat(display_html3, "<body onload=\"JavaScript:xmlhttpGet();\">\n");
			strcat(display_html3, "	<div style=\"position: relative;\">\n");
			strcat(display_html3, "		<canvas id=\"myCanvas\" width=\"1024\" height=\"720\" style=\"position: absolute; left: 10; top: 70; z-index: 1;\"></canvas>\n");
			strcat(display_html3, "		<canvas id=\"myCanvas2\" width=\"1024\" height=\"720\" style=\"position: absolute; left: 10; top: 70; z-index: 0;\"></canvas>\n");
			strcat(display_html3, "	</div>\n");
			strcat(display_html3, "</body>\n");
			sprintf(buffer, header_str, strlen(display_html3), "text/html");
			write(fd, buffer, strlen(buffer));
			write(fd, display_html3, strlen(display_html3));
		} else if (strncmp(buffer + 4,"/gui-update.js", 14) == 0) {
			sprintf(buffer, header_str, strlen(display_html2), "text/plain");
			write(fd, buffer, strlen(buffer));
			write(fd, display_html2, strlen(display_html2));
#endif
		} else if (strncmp(buffer + 4,"/usr/share/multigcs/", 20) == 0) {
			int n;
			for (n = 5; n < strlen(buffer); n++) {
				if (buffer[n] == ' ') {
					buffer[n] = 0;
					break;
				}
			}
			printf("## %s ##\n", buffer + 4);
			webserv_child_dump_file(fd, buffer + 4, "image/jpg");


		// HTML5 HUD-View + Map
		} else if (strncmp(buffer + 4,"/hud.html", 9) == 0) {
			webserv_child_show_hud(fd);
		} else if (strncmp(buffer + 4,"/hudredraw.js", 13) == 0) {
			webserv_child_hud_redraw(fd);
		} else if (strncmp(buffer + 4,"/map.js", 7) == 0) {
			sprintf(tmp_str, "%s/webserv/map.js", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/html");
		} else if (strncmp(buffer + 4,"/tile/", 6) == 0) {
			int tx = 0;
			int ty = 0;
			int zoom = 0;
			sscanf(buffer + 10, "%i/%i/%i.png", &zoom, &tx, &ty);
			sprintf(tmp_str, mapnames[map_type][2], BASE_DIR, zoom, tx, ty);
			if (strstr(tmp_str, ".jpg\0") > 0) {
				webserv_child_dump_file(fd, tmp_str, "image/jpg");
			} else {
				webserv_child_dump_file(fd, tmp_str, "image/png");
			}
		} else if (strncmp(buffer + 4,"/marker.png", 11) == 0) {
			sprintf(tmp_str, "%s/webserv/marker.png", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "image/png");
		} else if (strncmp(buffer + 4,"/img/marker.png", 15) == 0) {
			sprintf(tmp_str, "%s/webserv/marker.png", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "image/png");
		} else if (strncmp(buffer + 4,"/lonlat.txt", 11) == 0) {
			webserv_child_show_lonlat(fd);
		} else {
			sprintf(tmp_str, "%s/index.html", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/html");
		}
	}
	close(fd);
	return;
}

int webserv_thread (void *data) {
	int listenfd;
	int socketfd;
	socklen_t length;
	static struct sockaddr_in cli_addr;
	static struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(webport);

	if ((listenfd = socket(AF_INET, SOCK_STREAM,0)) < 0) {
		return(1);
	}

	int flags = fcntl(listenfd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(listenfd, F_SETFL, flags);

	int opt = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		return(1);
	}
	if (listen(listenfd, 64) < 0) {
		return(1);
	}

	while (webserv_running == 1) {
		length = sizeof(cli_addr);
		if ((socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length)) >= 0) {
			webserv_child(socketfd);
		}
		SDL_Delay(1);
	}

	close(listenfd);

	printf("webserv: exit thread\n");
	return(0);
}

void webserv_init (void) {
	printf("webserv: init thread\n");
	obj3d_collada.name[0] = 0;
	webserv_running = 1;
#ifdef SDL2
	thread_webserv = SDL_CreateThread(webserv_thread, NULL, NULL);
#else
	thread_webserv = SDL_CreateThread(webserv_thread, NULL);
#endif
	if (thread_webserv == NULL) {
		fprintf(stderr, "webserv: thread konnte nicht gestartet werden: %s\n", SDL_GetError());
	}
	printf("webserv: running on Port: %i\n", webport);
}

void webserv_exit (void) {
	webserv_running = 0;
	if (thread_webserv != NULL) {
		printf("webserv: wait thread\n");
		SDL_WaitThread(thread_webserv, NULL);
		thread_webserv = NULL;
	}
	if (listenfd >= 0) {
		close(listenfd);
	}
#ifdef SDLGL
	if (obj3d_collada.name[0] != 0) {
		object3d_free(&obj3d_collada);
	}
#endif
}

