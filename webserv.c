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
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_events.h>
#include <model.h>


extern uint16_t webport;
extern void save_screenshot2 (void);
extern volatile uint8_t zoom;
extern uint8_t map_type;
extern char mapnames[20][4][200];

#define BUFSIZE 18096
#define PI 3.14159265

uint8_t webserv_running = 0;
SDL_Thread *thread_webserv = NULL;
int listenfd;

#define header_str "HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n"

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
	sprintf(buffer, header_str, len, "image/png");
	write(fd, buffer, strlen(buffer));
	while ((ret = read(file_fd, buffer, BUFSIZE)) > 0) {
		write(fd,buffer,ret);
	}
	close(file_fd);
}

void webserv_child_dump_file (int fd, char *file, char *type) {
	static char buffer[BUFSIZE + 1];
	int file_fd;
	long len;
	long ret;
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

	sprintf(buffer, header_str, strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));

}

void webserv_child_show_lonlat (int fd) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	sprintf(content, "%f, %f", ModelData.p_long, ModelData.p_lat);
	sprintf(buffer, header_str, strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}


void webserv_child_show_hud (int fd) {
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
	strcat(content, "</script></head><body>\n");
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

	sprintf(buffer, header_str, strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_hud_redraw (int fd) {
	static char buffer[BUFSIZE + 1];
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

	sprintf(buffer, header_str, strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_kml_live (int fd, char *servername) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;

	strcat(content, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	strcat(content, "<kml xmlns=\"http://earth.google.com/kml/2.2\">\n");
	strcat(content, "	<NetworkLink>\n");
	strcat(content, "		<name>MultiGCS</name>\n");
	strcat(content, "		<open>1</open>\n");
//	strcat(content, "		<flyToView>1</flyToView>\n");
	strcat(content, "		<Link>\n");
	sprintf(tmp_str, "			<href>http://%s/model.kml</href>\n", servername);
	strcat(content, tmp_str);
	strcat(content, "			<refreshMode>onInterval</refreshMode>\n");
	strcat(content, "			<refreshInterval>.3</refreshInterval>\n");
	strcat(content, "		</Link>\n");
	strcat(content, "	</NetworkLink>\n");
	strcat(content, "</kml>\n");

	sprintf(buffer, header_str, strlen(content), "application/vnd.google-earth.kml");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_kml_feed (int fd, char *servername) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;

	strcat(content, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	strcat(content, "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
	strcat(content, "	<Document>\n");
	strcat(content, "		<Placemark>\n");
	strcat(content, "			<name>Model</name>\n");


	strcat(content, "			<Model id=\"model_10\">\n");
	strcat(content, "				<extrude>1</extrude>\n");
	strcat(content, "				<altitudeMode>absolute</altitudeMode>\n");
//	strcat(content, "				<altitudeMode>relativeToGround</altitudeMode>\n");
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

//	strcat(content, "			<LookAt>\n");
//	sprintf(tmp_str, "				<longitude>%f</longitude>\n", ModelData.p_long);
//	strcat(content, tmp_str);
//	sprintf(tmp_str, "				<latitude>%f</latitude>\n", ModelData.p_lat);
//	strcat(content, tmp_str);
//	sprintf(tmp_str, "				<heading>%f</heading>\n", ModelData.yaw);
//	strcat(content, tmp_str);
//	strcat(content, "			</LookAt>\n");
	strcat(content, "		</Placemark>\n");
	strcat(content, "	</Document>\n");
	strcat(content, "</kml>\n");

	sprintf(buffer, header_str, strlen(content), "application/vnd.google-earth.kml");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}


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
		strcpy(servername, "");
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
			sprintf(buffer, header_str, strlen(content), "text/plain");
			write(fd, buffer, strlen(buffer));
			write(fd, content, strlen(content));
		} else {
			sprintf(content, "UNKNOWN\n");
			sprintf(buffer, header_str, strlen(content), "text/plain");
			write(fd, buffer, strlen(buffer));
			write(fd, content, strlen(content));
		}
	} else if (strncmp(buffer,"GET ", 4) == 0 || strncmp(buffer,"get ", 4) == 0) {
		// Misc
		if (strncmp(buffer + 4,"/modeldata", 10) == 0) {
			webserv_child_dump_modeldata(fd);
		} else if (strncmp(buffer + 4,"/screenshot", 11) == 0) {
			webserv_child_dump_screen(fd);

		// Google-Earth Live-Feed (Model-Position)
		} else if (strncmp(buffer + 4,"/live.kml", 4) == 0) {
			webserv_child_kml_live(fd, servername);
		} else if (strncmp(buffer + 4,"/model.kml", 8) == 0) {
			webserv_child_kml_feed(fd, servername);
		} else if (strncmp(buffer + 4,"/plane.dae", 4) == 0) {
			sprintf(tmp_str, "%s/plane.dae", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/xml");

		// HTML5 HUD-View + Map
		} else if (strncmp(buffer + 4,"/hud.html", 9) == 0) {
			webserv_child_show_hud(fd);
		} else if (strncmp(buffer + 4,"/hudredraw.js", 13) == 0) {
			webserv_child_hud_redraw(fd);
		} else if (strncmp(buffer + 4,"/map.js", 7) == 0) {
			sprintf(tmp_str, "%s/MAPS/map.js", BASE_DIR);
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
			sprintf(tmp_str, "%s/MAPS/marker.png", BASE_DIR);
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
}

