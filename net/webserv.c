
#include <all.h>

#ifndef WINDOWS

extern void save_screenshot2 (void);
extern volatile uint8_t zoom;

#define BUFSIZE 298096
#define PI 3.14159265

#define MENU "<TABLE class=\"menubar\" id=\"menubar\" width=\"100%\" border=\"0\"><TR bgcolor=\"#AAAAAA\"><TH width=\"10%\"><A href=\"/hud.html\">[HUD]</A></TH><TH width=\"10%\"><A href=\"/map.html\">[MAP]</A></TH><TH width=\"10%\"><A href=\"/waypoints.html\">[WAYPOINTS]</A></TH><TH width=\"10%\"><A href=\"/mavlink.html\">[MAVLINK]</A></TH><TH width=\"10%\"><A href=\"/mwii.html\">[MWII]</A></TH><TH width=\"10%\"><A href=\"/logfiles/\">[LOGFILES]</A></TH><TH width=\"10%\"><A href=\"/gcssetup.html\">[SETUP]</A></TH><TH width=\"10%\"><A href=\"/misc.html\">[MISC]</A></TH></TR></TABLE>\n"

static char menu_entrys[16][2][128] = {
	{"/hud.html", "HUD"}, 
	{"/map.html", "MAP"}, 
	{"/waypoints.html", "WAYPOINTS"}, 
	{"/mavlink.html", "MAVLINK"}, 
	{"/mwii.html", "MWII"}, 
	{"/logfiles/", "LOGFILES"}, 
	{"/gcssetup.html", "SETUP"}, 
	{"/misc.html", "MISC"}, 
	{"", ""}, 
};

static Object3d obj3d_collada;
static SDL_Thread *thread_webserv = NULL;
static float blender_first_lat = 0.0;
static float blender_first_long = 0.0;
static float blender_first_alt = 0.0;
static uint8_t webserv_running = 0;
static char last_title[128];
int listenfd;

#define header_str "HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %i\nConnection: close\nContent-Type: %s\n\n"

void webserv_html_head (char *content, char *title) {
	char tmp_str[1024];
	strcat(content, "<HTML>\n");
	strcat(content, "<HEAD>\n");
	sprintf(tmp_str, "  <TITLE>MultiGCS - %s</TITLE>\n", title);
	strcat(content, tmp_str);
	strcat(content, "  <LINK rel=\"stylesheet\" type=\"text/css\" href=\"/style.css\" />\n");
	strcat(content, "</HEAD>\n");
	strcpy(last_title, title);
}

void webserv_html_start (char *content, uint8_t init) {
	char tmp_str[1024];
	int n = 0;
	if (init == 0) {
		strcat(content, "<BODY>\n");
	} else {
		strcat(content, "<BODY onload=\"init();\">\n");
	}
	strcat(content, "<DIV class=\"background\"></DIV>\n");
//	strcat(content, MENU);

	strcat(content, "<TABLE class=\"menubar\" id=\"menubar\" width=\"100%\" border=\"0\"><TR bgcolor=\"#AAAAAA\">");
	for (n = 0; n < 16 && menu_entrys[n][0][0] != 0; n++) {
		if (strcmp(menu_entrys[n][1], last_title) == 0) {
			sprintf(tmp_str, "<TH class=\"menubar_sel\" width=\"10%%\"><A href=\"%s\">%s</A></TH>", menu_entrys[n][0], menu_entrys[n][1]);
		} else {
			sprintf(tmp_str, "<TH width=\"10%%\"><A href=\"%s\">%s</A></TH>", menu_entrys[n][0], menu_entrys[n][1]);
		}
		strcat(content, tmp_str);
	}
	strcat(content, "</TR></TABLE>\n");
	strcat(content, "<BR><BR>\n");
}

void webserv_html_stop (char *content) {
	strcat(content, "<BR><BR>\n");
	strcat(content, "</BODY>\n");
	strcat(content, "</HTML>\n");
}

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
	char content[1024];
	int len;
	int ret;
	if (strncmp(file, "./", 2) == 0) {
		file += 2;
	}
#ifdef ANDROID
	SDL_Log("webserv_child_dump_file: %s\n", file);
#endif
	SDL_RWops *ops_file = SDL_RWFromFile(file, "r");
	if (ops_file == NULL) {
		SDL_Log("webserv: file not found: %s\n", file);
		sprintf(content, "webserv: file not found: %s\n", file);
		sprintf(buffer, header_str, (int)strlen(content), "text/plain");
		write(fd, buffer, strlen(buffer));
		write(fd, content, strlen(content));
		return;
	}
	len = SDL_RWseek(ops_file, 0, SEEK_END);
	SDL_RWseek(ops_file, 0, SEEK_SET);
	sprintf(buffer, header_str, len, type);
	write(fd, buffer, strlen(buffer));
	while ((ret = SDL_RWread(ops_file, buffer, 1, BUFSIZE)) > 0) {
		write(fd, buffer, ret);
	}
	SDL_RWclose(ops_file);
}

void webserv_child_dump_blender (int fd) {
	char buffer[1024];
	char content[BUFSIZE + 1];
	char tmp_str[100];
	if (blender_first_lat == 0.0 || blender_first_long == 0.0) {
		blender_first_lat = ModelData[ModelActive].p_lat;
		blender_first_long = ModelData[ModelActive].p_long;
		blender_first_alt = ModelData[ModelActive].p_alt;
	}
	content[0] = 0;
	sprintf(tmp_str, "%f %f %f %f %f %f\n", ModelData[ModelActive].pitch, ModelData[ModelActive].roll, ModelData[ModelActive].yaw, (ModelData[ModelActive].p_lat - blender_first_lat), (ModelData[ModelActive].p_long - blender_first_long), (ModelData[ModelActive].p_alt - blender_first_alt));
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
	sprintf(tmp_str, "name=%s\n", ModelData[ModelActive].name);
	strcat(content, tmp_str);
	sprintf(tmp_str, "image=%s\n", ModelData[ModelActive].image);
	strcat(content, tmp_str);
	sprintf(tmp_str, "dronetype=%i\n", ModelData[ModelActive].dronetype);
	strcat(content, tmp_str);
	sprintf(tmp_str, "teletype=%i\n", ModelData[ModelActive].teletype);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telemetry_port=%s\n", ModelData[ModelActive].telemetry_port);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telemetry_baud=%i\n", ModelData[ModelActive].telemetry_baud);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telebtaddr=%s\n", ModelData[ModelActive].telebtaddr);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telebtpin=%s\n", ModelData[ModelActive].telebtpin);
	strcat(content, tmp_str);
	sprintf(tmp_str, "mode=%i\n", ModelData[ModelActive].mode);
	strcat(content, tmp_str);
	sprintf(tmp_str, "status=%i\n", ModelData[ModelActive].status);
	strcat(content, tmp_str);
	sprintf(tmp_str, "armed=%i\n", ModelData[ModelActive].armed);
	strcat(content, tmp_str);
	sprintf(tmp_str, "heartbeat=%i\n", ModelData[ModelActive].heartbeat);
	strcat(content, tmp_str);
	sprintf(tmp_str, "heartbeat_rc=%i\n", ModelData[ModelActive].heartbeat_rc);
	strcat(content, tmp_str);
	sprintf(tmp_str, "found_rc=%i\n", ModelData[ModelActive].found_rc);
	strcat(content, tmp_str);
	sprintf(tmp_str, "p_lat=%f\n", ModelData[ModelActive].p_lat);
	strcat(content, tmp_str);
	sprintf(tmp_str, "p_long=%f\n", ModelData[ModelActive].p_long);
	strcat(content, tmp_str);
	sprintf(tmp_str, "p_alt=%f\n", ModelData[ModelActive].p_alt);
	strcat(content, tmp_str);
	sprintf(tmp_str, "alt_offset=%f\n", ModelData[ModelActive].alt_offset);
	strcat(content, tmp_str);
	sprintf(tmp_str, "baro=%f\n", ModelData[ModelActive].baro);
	strcat(content, tmp_str);
	sprintf(tmp_str, "pitch=%f\n", ModelData[ModelActive].pitch);
	strcat(content, tmp_str);
	sprintf(tmp_str, "roll=%f\n", ModelData[ModelActive].roll);
	strcat(content, tmp_str);
	sprintf(tmp_str, "yaw=%f\n", ModelData[ModelActive].yaw);
	strcat(content, tmp_str);
	sprintf(tmp_str, "speed=%f\n", ModelData[ModelActive].speed);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage=%f\n", ModelData[ModelActive].voltage);
	strcat(content, tmp_str);
	sprintf(tmp_str, "load=%f\n", ModelData[ModelActive].load);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gpsfix=%i\n", ModelData[ModelActive].gpsfix);
	strcat(content, tmp_str);
	sprintf(tmp_str, "numSat=%i\n", ModelData[ModelActive].numSat);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[0]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[1]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[2]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[3]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[4]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[5]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[6]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[7]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[8]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[9]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[10]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[11]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[12]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[13]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[14]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData[ModelActive].radio[15]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "acc_x=%f\n", ModelData[ModelActive].acc_x);
	strcat(content, tmp_str);
	sprintf(tmp_str, "acc_y=%f\n", ModelData[ModelActive].acc_y);
	strcat(content, tmp_str);
	sprintf(tmp_str, "acc_z=%f\n", ModelData[ModelActive].acc_z);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gyro_x=%f\n", ModelData[ModelActive].gyro_x);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gyro_y=%f\n", ModelData[ModelActive].gyro_y);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gyro_z=%f\n", ModelData[ModelActive].gyro_z);
	strcat(content, tmp_str);
	sprintf(tmp_str, "rssi_rx=%i\n", ModelData[ModelActive].rssi_rx);
	strcat(content, tmp_str);
	sprintf(tmp_str, "rssi_tx=%i\n", ModelData[ModelActive].rssi_tx);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_rx=%f\n", ModelData[ModelActive].voltage_rx);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData[ModelActive].voltage_zell[0]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData[ModelActive].voltage_zell[1]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData[ModelActive].voltage_zell[2]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData[ModelActive].voltage_zell[3]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData[ModelActive].voltage_zell[4]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData[ModelActive].voltage_zell[5]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "temperature=%f\n", ModelData[ModelActive].temperature[0]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "temperature=%f\n", ModelData[ModelActive].temperature[1]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "ampere=%f\n", ModelData[ModelActive].ampere);
	strcat(content, tmp_str);
	sprintf(tmp_str, "sysid=%i\n", ModelData[ModelActive].sysid);
	strcat(content, tmp_str);
	sprintf(tmp_str, "compid=%i\n", ModelData[ModelActive].compid);
	strcat(content, tmp_str);
	sprintf(tmp_str, "mavlink_update=%i\n", ModelData[ModelActive].mavlink_update);
	strcat(content, tmp_str);

	sprintf(buffer, header_str, (int)strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_show_lonlat (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	sprintf(content, "%f, %f, %.1f, %0.1f", ModelData[ModelActive].p_long, ModelData[ModelActive].p_lat, ModelData[ModelActive].p_alt, ModelData[ModelActive].yaw);
	sprintf(buffer, header_str, (int)strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_show_map (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;
	webserv_html_head(content, "MAP");

#ifdef ANDROID
	strcat(content, "<SCRIPT src=\"http://openlayers.org/api/OpenLayers.js\"></SCRIPT>\n");
#else
	strcat(content, "<SCRIPT src=\"/map.js\"></SCRIPT>\n");
#endif

	strcat(content, "<SCRIPT>\n");
	strcat(content, "function HUDxmlhttpGet() {\n");
	strcat(content, "    var xmlHttpReq = false;\n");
	strcat(content, "    var self = this;\n");
	strcat(content, "    if (window.XMLHttpRequest) {\n");
	strcat(content, "        self.xmlHttpReq = new XMLHttpRequest();\n");
	strcat(content, "    } else if (window.ActiveXObject) {\n");
	strcat(content, "        self.xmlHttpReq = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.open('GET', \"/hudredraw_small.js\", true);\n");
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
	strcat(content, "    setTimeout(xmlhttpGet, 300);\n");
	strcat(content, "}\n");
	strcat(content, "function updatepage(str){\n");
	strcat(content, "    var data = str.split(',')\n");
	strcat(content, "    laenge = data[0];\n");
	strcat(content, "    breite = data[1];\n");
	strcat(content, "    alt = data[2];\n");
	strcat(content, "    yaw = data[3];\n");
	strcat(content, "    model.attributes.alt = alt;\n");
	strcat(content, "    model.attributes.yaw = yaw;\n");
	strcat(content, "    model.move(new OpenLayers.LonLat(laenge,breite).transform(map.displayProjection,map.projection));\n");
	strcat(content, "    map.setCenter(new OpenLayers.LonLat(laenge,breite).transform(map.displayProjection,map.projection));\n");
	strcat(content, "}\n");
	strcat(content, "function wp_add(num, lon, lat) {\n");
	strcat(content, "    var xmlHttpReq = false;\n");
	strcat(content, "    var self = this;\n");
	strcat(content, "    if (window.XMLHttpRequest) {\n");
	strcat(content, "        self.xmlHttpReq = new XMLHttpRequest();\n");
	strcat(content, "    } else if (window.ActiveXObject) {\n");
	strcat(content, "        self.xmlHttpReq = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.open(\"GET\", \"/waypoint_new?wp\" + num + \"=\" + lat + \",\" + lon, true);\n");
	strcat(content, "    self.xmlHttpReq.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\n");
	strcat(content, "    self.xmlHttpReq.onreadystatechange = function() {\n");
	strcat(content, "        if (self.xmlHttpReq.readyState == 4) {\n");
	strcat(content, "            window.location.reload();\n");
	strcat(content, "        }\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.send();\n");
	strcat(content, "}\n");
	sprintf(tmp_str, " var map,model,laenge=%f,breite=%f;\n", ModelData[ModelActive].p_long, ModelData[ModelActive].p_lat);
	strcat(content, tmp_str);
	strcat(content, " var fromProjection = new OpenLayers.Projection(\"EPSG:4326\");   // Transform from WGS 1984\n");
	strcat(content, " var toProjection   = new OpenLayers.Projection(\"EPSG:900913\"); // to Spherical Mercator Projection\n");
	strcat(content, "function init() {\n");
	strcat(content, " var canvas = document.getElementById('small_hudcanvas');\n");
	strcat(content, " var context = canvas.getContext('2d');\n");
	strcat(content, " context.clearRect(0, 0, canvas.width, canvas.height);\n");
	sprintf(tmp_str, " drawHorizon(context, 100, 50, 400, %f, %f);\n", ModelData[ModelActive].roll, ModelData[ModelActive].pitch);
	strcat(content, tmp_str);
	strcat(content, " HUDxmlhttpGet();\n");
	strcat(content, " map = new OpenLayers.Map('mapdiv', {projection: toProjection, displayProjection: fromProjection});\n");
	strcat(content, " var baselayer = new OpenLayers.Layer.OSM(\"Mapnik\",null,{attribution:\"\"});\n");
	strcat(content, " var modellayer = new OpenLayers.Layer.Vector(\"Model\", {\n");
	strcat(content, "                styleMap: new OpenLayers.StyleMap(\n");
	strcat(content, "                     { 'default': \n");
	strcat(content, "                        {\n");
	strcat(content, "                        label: \"${alt}m\",\n");
	strcat(content, "                        fontColor: \"#000000\",\n");
	strcat(content, "                        fontSize: \"16px\",\n");
	strcat(content, "                        fontFamily: \"Courier New, monospace\",\n");
	strcat(content, "                        fontWeight: \"bold\",\n");
	strcat(content, "                        labelAlign: \"cm\",\n");
	strcat(content, "                        labelXOffset: \"0\",\n");
	strcat(content, "                        labelYOffset: \"-20\",\n");
	strcat(content, "                        externalGraphic: \"/model.png\",\n");
	strcat(content, "                        graphicWidth:41,\n");
	strcat(content, "                        graphicHeight:41,\n");
	strcat(content, "                        graphicXOffset:-20,\n");
	strcat(content, "                        graphicYOffset:-20,\n");
	strcat(content, "                        rotation: \"${yaw}\"\n");
	strcat(content, "                    }\n");
	strcat(content, "                })\n");
	strcat(content, " });\n");
	strcat(content, " model = new OpenLayers.Feature.Vector(new OpenLayers.Geometry.Point(laenge,breite).transform(map.displayProjection,map.projection));\n");
	sprintf(tmp_str, " model.attributes.alt = \"%0.1f\";\n", ModelData[ModelActive].p_alt);
	strcat(content, tmp_str);
	sprintf(tmp_str, " model.attributes.yaw = \"%0.1f\";\n", ModelData[ModelActive].yaw);
	strcat(content, tmp_str);
	strcat(content, " modellayer.addFeatures([model]);\n");
	strcat(content, " var markerlayer = new OpenLayers.Layer.Vector(\"Marker\", {\n");
	strcat(content, "                styleMap: new OpenLayers.StyleMap(\n");
	strcat(content, "                     { 'default': \n");
	strcat(content, "                        {\n");
	strcat(content, "                        strokeColor: \"#00FF00\",\n");
	strcat(content, "                        strokeOpacity: 0.5,\n");
	strcat(content, "                        strokeWidth: 3,\n");
	strcat(content, "                        fillColor: \"#FF5500\",\n");
	strcat(content, "                        fillOpacity: 0.5,\n");
	strcat(content, "                        pointRadius: 12,\n");
	strcat(content, "                        pointerEvents: \"visiblePainted\",\n");
	strcat(content, "                        graphicName: \"circle\",\n");
	strcat(content, "                        label: \"${name}\\n${command}\\n${alt}m\",\n");
	strcat(content, "                        fontColor: \"#000000\",\n");
	strcat(content, "                        fontSize: \"16px\",\n");
	strcat(content, "                        fontFamily: \"Courier New, monospace\",\n");
	strcat(content, "                        fontWeight: \"bold\",\n");
	strcat(content, "                        labelAlign: \"cm\",\n");
	strcat(content, "                        labelXOffset: \"0\",\n");
	strcat(content, "                        labelYOffset: \"0\"\n");
	strcat(content, "                    }\n");
	strcat(content, "                })\n");
	strcat(content, " });\n");
	int n = 0;
	for (n = 0; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[ModelActive][n].p_lat != 0.0) {
			sprintf(tmp_str, " marker%i = new OpenLayers.Feature.Vector(new OpenLayers.Geometry.Point(%f, %f).transform(map.displayProjection,map.projection));\n", n, WayPoints[ModelActive][n].p_long, WayPoints[ModelActive][n].p_lat);
			strcat(content, tmp_str);
			sprintf(tmp_str, " marker%i.attributes.name = \"%s\";\n", n, WayPoints[ModelActive][n].name);
			strcat(content, tmp_str);
			sprintf(tmp_str, " marker%i.attributes.command = \"%s\";\n", n, WayPoints[ModelActive][n].command);
			strcat(content, tmp_str);
			sprintf(tmp_str, " marker%i.attributes.alt = \"%0.1f\";\n", n, WayPoints[ModelActive][n].p_alt);
			strcat(content, tmp_str);
			sprintf(tmp_str, " markerlayer.addFeatures([marker%i]);\n", n);
			strcat(content, tmp_str);
           	}
	}
	strcat(content, " var lineLayer = new OpenLayers.Layer.Vector(\"Line Layer\");\n");
	strcat(content, " map.addLayer(lineLayer);\n");
	strcat(content, " map.addControl(new OpenLayers.Control.DrawFeature(lineLayer, OpenLayers.Handler.Path));\n");
	strcat(content, " var points = new Array(\n");
	uint8_t flag = 0;
	int n2 = 1;
	for (n = 0; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[ModelActive][n].p_lat != 0.0) {
			if (flag == 1) {
				strcat(content, ",\n");
			}
			sprintf(tmp_str, "   new OpenLayers.Geometry.Point(%f, %f).transform(map.displayProjection,map.projection)", WayPoints[ModelActive][n].p_long, WayPoints[ModelActive][n].p_lat);
			strcat(content, tmp_str);
			n2 = n + 1;
			flag = 1;
		}
	}
	strcat(content, " );\n");
	strcat(content, "\n");
	strcat(content, " var line = new OpenLayers.Geometry.LineString(points);\n");
	strcat(content, " var style = {\n");
	strcat(content, "  strokeColor: '#0000ff',\n");
	strcat(content, "  strokeOpacity: 0.5,\n");
	strcat(content, "  strokeWidth: 5\n");
	strcat(content, " };\n");
	strcat(content, " var lineFeature = new OpenLayers.Feature.Vector(line, null, style);\n");
	strcat(content, " lineLayer.addFeatures([lineFeature]);\n");
	strcat(content, " map.addLayers([baselayer, markerlayer]);\n");
	strcat(content, " map.addLayers([baselayer, modellayer]);\n");
	sprintf(tmp_str, " map.setCenter(new OpenLayers.LonLat(laenge,breite).transform(map.displayProjection,map.projection), %i);\n", zoom);
	strcat(content, tmp_str);
	strcat(content, "\n");
	strcat(content, " OpenLayers.Control.Click = OpenLayers.Class(OpenLayers.Control, {\n");
	strcat(content, "    defaultHandlerOptions: {\n");
	strcat(content, "        'single': true,\n");
	strcat(content, "        'double': false,\n");
	strcat(content, "        'pixelTolerance': 0,\n");
	strcat(content, "        'stopSingle': false,\n");
	strcat(content, "        'stopDouble': false\n");
	strcat(content, "    },\n");
	strcat(content, "    initialize: function(options) {\n");
	strcat(content, "        this.handlerOptions = OpenLayers.Util.extend({}, this.defaultHandlerOptions);\n");
	strcat(content, "        OpenLayers.Control.prototype.initialize.apply(this, arguments); \n");
	strcat(content, "        this.handler = new OpenLayers.Handler.Click(this, {'click': this.trigger}, this.handlerOptions);\n");
	strcat(content, "    }, \n");
	strcat(content, "    trigger: function(e) {\n");
	strcat(content, "        var lonlat = map.getLonLatFromPixel(e.xy);\n");
	strcat(content, "        lonlat1 = new OpenLayers.LonLat(lonlat.lon,lonlat.lat).transform(toProjection,fromProjection);\n");
	sprintf(tmp_str, "        wp_add(%i, lonlat1.lon, lonlat1.lat);\n", n2);
	strcat(content, tmp_str);
	strcat(content, "    }\n");
	strcat(content, " });\n");
	strcat(content, " var click = new OpenLayers.Control.Click();\n");
	strcat(content, " map.addControl(click);\n");
	strcat(content, " click.activate();\n");
	strcat(content, " xmlhttpGet();\n");
	strcat(content, "}\n");
	strcat(content, "</SCRIPT>\n");
	webserv_html_start(content, 1);
	strcat(content, "<div class=\"mapdiv\" id=\"mapdiv\"></div>\n");
	sprintf(tmp_str, "<div class=\"mapcopyright\" id=\"mapcopyright\">%s</div>\n", mapnames[map_type][MAP_COPYRIGHT]);
	strcat(content, tmp_str);
	strcat(content, "<canvas class=\"small_hudcanvas\" id=\"small_hudcanvas\" width=\"640\" height=\"640\"></canvas>\n");
	webserv_html_stop(content);

	sprintf(buffer, header_str, (int)strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_show_hud (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;
	webserv_html_head(content, "HUD");
	strcat(content, "<SCRIPT>\n");
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
	strcat(content, "function init() {\n");
	strcat(content, "	var canvas = document.getElementById('hudcanvas');\n");
	strcat(content, "	var context = canvas.getContext('2d');\n");
	strcat(content, "	context.clearRect(0, 0, canvas.width, canvas.height);\n");
	strcat(content, "	drawMeter(context, 50, 100, 30, 45, 90, 45, 'roll');\n");
	sprintf(tmp_str, "	drawPointer(context, 50, 100, 30, %f);\n", ModelData[ModelActive].roll + 90.0);
	strcat(content, tmp_str);
	strcat(content, "	drawMeter(context, 50, 200, 30, 45, 90, 45, 'pitch');\n");
	sprintf(tmp_str, "	drawPointer(context, 50, 200, 30, %f);\n", ModelData[ModelActive].pitch + 90.0);
	strcat(content, tmp_str);
	sprintf(tmp_str, "	drawHorizon(context, 100, 50, 400, %f, %f);\n", ModelData[ModelActive].roll, ModelData[ModelActive].pitch);
	strcat(content, tmp_str);
	sprintf(tmp_str, "	drawCompas(context, 300, 500, 150, %f);\n", ModelData[ModelActive].yaw);
	strcat(content, tmp_str);
	strcat(content, "       HUDxmlhttpGet();\n");
	strcat(content, "}\n");
	strcat(content, "</SCRIPT>\n");
	webserv_html_start(content, 1);

	strcat(content, "<CENTER><TABLE width=\"90%\" border=\"0\">\n");
	strcat(content, "<TR><TH>HUD</TH></TR>\n");
	strcat(content, "<TR><TD class=\"hudbg\" align=\"center\"><canvas class=\"hudcanvas\" id=\"hudcanvas\" width=\"600\" height=\"720\"></canvas></TD></TR>\n");
	strcat(content, "</TABLE></CENTER>\n");
	webserv_html_stop(content);

	sprintf(buffer, header_str, (int)strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_show_misc (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	content[0] = 0;
	webserv_html_head(content, "MISC");
	webserv_html_start(content, 0);
	strcat(content, "<CENTER>\n");
	strcat(content, "<H3>Google-Earth Livefeed and Logs</H3>\n");
	strcat(content, "<A href=\"/index.kml\">/index.kml</A><BR>\n");
	strcat(content, "<A href=\"/wp.kml\">/wp.kml</A> (list of all waypoints)<BR>\n");
	strcat(content, "<A href=\"/live.kml\">/live.kml</A><BR>\n");
	strcat(content, "<A href=\"/live-pilot.kml\">/live-pilot.kml</A><BR>\n");
	strcat(content, "<A href=\"/model.kml\">/model.kml</A> (called by live.kml)<BR>\n");
	strcat(content, "<A href=\"/pilot.kml\">/pilot.kml</A> (called by live-pilot.kml)<BR>\n");
	strcat(content, "<A href=\"/plane.dae\">/plane.dae</A> (called by model.kml)<BR>\n");
	strcat(content, "<A href=\"/logkml/\">/logkml/</A> (list of all logfiles in kml-format)<BR>\n");
	strcat(content, "\n");
	strcat(content, "<H3>Blender 3D</H3>\n");
	strcat(content, "<A href=\"/blender-export.py\">/blender-export.py</A> (blender export script)<BR>\n");
	strcat(content, "<A href=\"/blender.txt\">/blender.txt</A> (attitude and position data)<BR>\n");
	strcat(content, "\n");
	strcat(content, "<H3>Misc</H3>\n");
	strcat(content, "<A href=\"/modeldata\">/modeldata</A> (Model-Data / Telemetry-Data)<BR>\n");
	strcat(content, "<A href=\"/screenshot\">/screenshot</A> (take a screenshot of the GUI)<BR>\n");
	strcat(content, "<H3>Copyright</H3>\n");
	strcat(content, "<A href=\"/copyright\">/copyright</A> (Copyright)<BR>\n");
	strcat(content, "<A href=\"/GPLv2.txt\">/GPLv2.txt</A> (GPL v2 or later)<BR>\n");
	strcat(content, "</CENTER>\n");
	webserv_html_stop(content);

	sprintf(buffer, header_str, (int)strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_hud_redraw (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;
	strcat(content, "	var canvas = document.getElementById('hudcanvas');\n");
	strcat(content, "	var context = canvas.getContext('2d');\n");
	strcat(content, "	context.clearRect(0, 0, canvas.width, canvas.height);\n");
	strcat(content, "	drawMeter(context, 50, 100, 30, 45, 90, 45, 'roll');\n");
	sprintf(tmp_str, "	drawPointer(context, 50, 100, 30, %f);\n", ModelData[ModelActive].roll + 90.0);
	strcat(content, tmp_str);
	strcat(content, "	drawMeter(context, 50, 200, 30, 45, 90, 45, 'pitch');\n");
	sprintf(tmp_str, "	drawPointer(context, 50, 200, 30, %f);\n", ModelData[ModelActive].pitch + 90.0);
	strcat(content, tmp_str);
	sprintf(tmp_str, "	drawHorizon(context, 100, 50, 400, %f, %f);\n", ModelData[ModelActive].roll, ModelData[ModelActive].pitch);
	strcat(content, tmp_str);
	sprintf(tmp_str, "	drawCompas(context, 300, 500, 150, %f);\n", ModelData[ModelActive].yaw);
	strcat(content, tmp_str);
	sprintf(buffer, header_str, (int)strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_hud_redraw_small (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;
	strcat(content, "	var canvas = document.getElementById('hudcanvas');\n");
	strcat(content, "	var context = canvas.getContext('2d');\n");
	strcat(content, "	context.clearRect(0, 0, canvas.width, canvas.height);\n");
	sprintf(tmp_str, "	drawHorizon(context, 100, 50, 400, %f, %f);\n", ModelData[ModelActive].roll, ModelData[ModelActive].pitch);
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
		if (WayPoints[ModelActive][n].name[0] != 0) {
			strcat(content, "    <Placemark>\n");
			sprintf(tmp_str, "      <name>%s</name>\n", WayPoints[ModelActive][n].name);
			strcat(content, tmp_str);
			sprintf(tmp_str, "      <description>%s</description>\n", WayPoints[ModelActive][n].command);
			strcat(content, tmp_str);
			strcat(content, "      <Point>\n");
			strcat(content, "        <extrude>1</extrude>\n");
			strcat(content, "        <altitudeMode>absolute</altitudeMode>\n");
			sprintf(tmp_str, "        <coordinates>%f,%f,%f</coordinates>\n", WayPoints[ModelActive][n].p_long, WayPoints[ModelActive][n].p_lat, WayPoints[ModelActive][n].p_alt);
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
		if (WayPoints[ModelActive][n].name[0] != 0) {
			sprintf(tmp_str, " %f,%f,%f \n", WayPoints[ModelActive][n].p_long, WayPoints[ModelActive][n].p_lat, WayPoints[ModelActive][n].p_alt);
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
	sprintf(directory, "%s/logs", get_datadirectory());
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

	sprintf(buffer, header_str, (int)strlen(content), "application/vnd.google-earth.kml+xml");
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
	sprintf(tmp_str, "			<refreshInterval>%f</refreshInterval>\n", setup.gearth_interval);
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
		sprintf(tmp_str, "					<longitude>%f</longitude>\n", ModelData[ModelActive].p_long);
		strcat(content, tmp_str);
		sprintf(tmp_str, "					<latitude>%f</latitude>\n", ModelData[ModelActive].p_lat);
		strcat(content, tmp_str);
		sprintf(tmp_str, "					<altitude>%f</altitude>\n", ModelData[ModelActive].p_alt);
		strcat(content, tmp_str);
		strcat(content, "				</Location>\n");
		strcat(content, "				<Orientation>\n");
		sprintf(tmp_str, "					<tilt>%f</tilt>\n", ModelData[ModelActive].pitch * -1);
		strcat(content, tmp_str);
		sprintf(tmp_str, "					<roll>%f</roll>\n", ModelData[ModelActive].roll * -1);
		strcat(content, tmp_str);
		sprintf(tmp_str, "					<heading>%f</heading>\n", ModelData[ModelActive].yaw);
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
		sprintf(tmp_str, "				<longitude>%f</longitude>\n", ModelData[ModelActive].p_long);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<latitude>%f</latitude>\n", ModelData[ModelActive].p_lat);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<altitude>%f</altitude>\n", ModelData[ModelActive].p_alt);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<heading>%f</heading>\n", ModelData[ModelActive].yaw);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<tilt>%f</tilt>\n", ModelData[ModelActive].pitch + 90.0);
		strcat(content, tmp_str);
		sprintf(tmp_str, "				<roll>%f</roll>\n", ModelData[ModelActive].roll * -1);
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

void webserv_child_waypoints (int fd, char *servername) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;
	int n = 0;
	int n2 = 0;
	float last_lat = 0.0;
	float last_lon = 0.0;
	float last_alt = 0.0;
	float alt = 0.0;
	webserv_html_head(content, "WAYPOINTS");
	strcat(content, "<SCRIPT>\n");
	strcat(content, "function check_option(wp, name) {\n");
	strcat(content, "	var value = document.getElementById(wp + '-' + name).options[document.getElementById(wp + '-' + name).selectedIndex].value;\n");
	strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
	strcat(content, "	xmlHttp.open(\"GET\", \"/waypoint_set?\" + wp + \"&\" + name + \"=\" + value, true);\n");
	strcat(content, "	xmlHttp.send(null);\n");
	strcat(content, "}\n");
	strcat(content, "function check_value(wp, name) {\n");
	strcat(content, "	var value = document.getElementById(wp + '-' + name).value;\n");
	strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
	strcat(content, "	xmlHttp.open(\"GET\", \"/waypoint_set?\" + wp + \"&\" + name + \"=\" + value, true);\n");
	strcat(content, "	xmlHttp.send(null);\n");
	strcat(content, "}\n");
	strcat(content, "</SCRIPT>\n");
	webserv_html_start(content, 0);
	strcat(content, "<CENTER><TABLE width=\"90%\" border=\"0\">\n");
	strcat(content, "<TR class=\"thead\"><TH>ACTIVE</TH><TH>NAME</TH><TH>TYPE</TH><TH>LONG</TH><TH>LAT</TH><TH>ALT</TH><TH>DIST</TH><TH>ACTION</TH><TH>MAP</TH></TR>\n");
	int lc = 0;
	for (n = 0; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[ModelActive][n].p_lat != 0.0) {
			lc = 1 - lc;
			if (lc == 0) {
				strcat(content, "<TR class=\"first\">\n");
			} else {
				strcat(content, "<TR class=\"sec\">\n");
			}
			if (n == waypoint_active) {
				strcat(content, "<TD bgcolor=\"#002200\">&nbsp;</TD>");
			} else {
				strcat(content, "<TD>&nbsp;</TD>");
			}
			sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('wp%i', 'NAME');\" id=\"wp%i-NAME\" value=\"%s\" type=\"text\"></TD>", n, n, WayPoints[ModelActive][n].name);
			strcat(content, tmp_str);
			if (n != 0) {
				sprintf(tmp_str, "<TD><SELECT class=\"form-input\" onchange=\"check_option('wp%i', 'TYPE');\" id=\"wp%i-TYPE\">\n", n, n);
				strcat(content, tmp_str);
				if (WayPoints[ModelActive][n].command[0] == 0) {
					sprintf(tmp_str, " <OPTION value=\"NONE\" selected>NONE</OPTION>\n");
				} else {
					sprintf(tmp_str, " <OPTION value=\"NONE\">NONE</OPTION>\n");
				}
				strcat(content, tmp_str);
				if (strcmp(WayPoints[ModelActive][n].command, "WAYPOINT") == 0) {
					sprintf(tmp_str, " <OPTION value=\"WAYPOINT\" selected>WAYPOINT</OPTION>\n");
				} else {
					sprintf(tmp_str, " <OPTION value=\"WAYPOINT\">WAYPOINT</OPTION>\n");
				}
				strcat(content, tmp_str);
				if (strcmp(WayPoints[ModelActive][n].command, "LOITER_UNLIM") == 0) {
					sprintf(tmp_str, " <OPTION value=\"LOITER_UNLIM\" selected>LOITER_UNLIM</OPTION>\n");
				} else {
					sprintf(tmp_str, " <OPTION value=\"LOITER_UNLIM\">LOITER_UNLIM</OPTION>\n");
				}
				strcat(content, tmp_str);
				if (strcmp(WayPoints[ModelActive][n].command, "LOITER_TURNS") == 0) {
					sprintf(tmp_str, " <OPTION value=\"LOITER_TURNS\" selected>LOITER_TURNS</OPTION>\n");
				} else {
					sprintf(tmp_str, " <OPTION value=\"LOITER_TURNS\">LOITER_TURNS</OPTION>\n");
				}
				strcat(content, tmp_str);
				if (strcmp(WayPoints[ModelActive][n].command, "LOITER_TIME") == 0) {
					sprintf(tmp_str, " <OPTION value=\"LOITER_TIME\" selected>LOITER_TIME</OPTION>\n");
				} else {
					sprintf(tmp_str, " <OPTION value=\"LOITER_TIME\">LOITER_TIME</OPTION>\n");
				}
				strcat(content, tmp_str);
				if (strcmp(WayPoints[ModelActive][n].command, "RTL") == 0) {
					sprintf(tmp_str, " <OPTION value=\"RTL\" selected>RTL</OPTION>\n");
				} else {
					sprintf(tmp_str, " <OPTION value=\"RTL\">RTL</OPTION>\n");
				}
				strcat(content, tmp_str);
				if (strcmp(WayPoints[ModelActive][n].command, "LAND") == 0) {
					sprintf(tmp_str, " <OPTION value=\"LAND\" selected>LAND</OPTION>\n");
				} else {
					sprintf(tmp_str, " <OPTION value=\"LAND\">LAND</OPTION>\n");
				}
				strcat(content, tmp_str);
				if (strcmp(WayPoints[ModelActive][n].command, "TAKEOFF") == 0) {
					sprintf(tmp_str, " <OPTION value=\"TAKEOFF\" selected>TAKEOFF</OPTION>\n");
				} else {
					sprintf(tmp_str, " <OPTION value=\"TAKEOFF\">TAKEOFF</OPTION>\n");
				}
				strcat(content, tmp_str);
				strcat(content, "</SELECT></TD>");
			} else {
				strcat(content, "<TD>&nbsp;</TD>");
			}
			sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('wp%i', 'LAT');\" id=\"wp%i-LAT\" value=\"%f\" type=\"text\"></TD>", n, n, WayPoints[ModelActive][n].p_lat);
			strcat(content, tmp_str);
			sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('wp%i', 'LONG');\" id=\"wp%i-LONG\" value=\"%f\" type=\"text\"></TD>", n, n, WayPoints[ModelActive][n].p_long);
			strcat(content, tmp_str);
			sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('wp%i', 'ALT');\" id=\"wp%i-ALT\" value=\"%f\" type=\"text\"></TD>", n, n, WayPoints[ModelActive][n].p_alt);
			strcat(content, tmp_str);
			float distance1 = 0.0;
			float distance2 = 0.0;
			float winkel_up = 0.0;
			if (last_lat != 0.0) {
				/* Distance - Ground-Level */
				distance1 = acos( 
					cos(toRad(last_lat))
					* cos(toRad(WayPoints[ModelActive][n].p_lat))
					* cos(toRad(last_lon) - toRad(WayPoints[ModelActive][n].p_long))
					+ sin(toRad(last_lat)) 
					* sin(toRad(WayPoints[ModelActive][n].p_lat))
				) * 6378.137 * 1000.0;
				alt = WayPoints[ModelActive][n].p_alt - last_alt;
				/* Distance - Sichtverbindung */
				distance2 = sqrt(((distance1) * (distance1)) + (alt * alt));
				/* Steigung */
				winkel_up = (asin(alt / distance2)) * 180 / PI;
				sprintf(tmp_str, "<TD><NOBR>%0.1fm (%0.1fm / %0.1fGrad)</NOBR></TD>", distance1, distance2, winkel_up);
				strcat(content, tmp_str);
			} else {
				strcat(content, "<TD>&nbsp;</TD>");
			}
			last_lat = WayPoints[ModelActive][n].p_lat;
			last_lon = WayPoints[ModelActive][n].p_long;
			last_alt = WayPoints[ModelActive][n].p_alt;

			if (n != 0) {
				sprintf(tmp_str, "<TD><A href=\"/waypoint_set?wp%i&DEL=1\">DEL</A></TD>", n);
			} else {
				strcpy(tmp_str, "<TD>&nbsp;</TD>");
			}
			strcat(content, tmp_str);

			sprintf(tmp_str, "<TD><A target=\"map\" href=\"https://maps.google.de/maps?q=%f,%f%%28%s%%29&t=k&z=17\">SHOW</A></TD>", WayPoints[ModelActive][n].p_lat, WayPoints[ModelActive][n].p_long, WayPoints[ModelActive][n].name);
			strcat(content, tmp_str);

			strcat(content, "</TR>\n");
			n2 = n + 1;
		}
	}
	sprintf(tmp_str, "<TR bgcolor=\"#111111\"><TD>&nbsp;</TD><TD>&nbsp;</TD><TD>&nbsp;</TD><TD>&nbsp;</TD><TD>&nbsp;</TD><TD>&nbsp;</TD><TD>&nbsp;</TD><TD><A href=\"/waypoint_set?wp%i&ADD=1\">ADD</A></TD><TD>&nbsp;</TD></TR>", n2);
	strcat(content, tmp_str);
	strcat(content, "</TABLE></CENTER>\n");
	webserv_html_stop(content);

	sprintf(buffer, header_str, (int)strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_kml_logfiles (int fd, char *servername, char *buffer2) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;
	int n;
	for (n = 5; n < strlen(buffer2); n++) {
		if (buffer2[n] == ' ') {
			buffer2[n] = 0;
			break;
		}
	}
	if ((strncmp(buffer2 + 4,"/logkml/", 8) == 0 && buffer2[12] == 0) || (strncmp(buffer2 + 4,"/logfiles/", 10) == 0 && buffer2[14] == 0)) {
		struct tm strukt;
		DIR *dir = NULL;
		struct dirent *dir_entry = NULL;
		struct stat statbuf;
		char new_path[400];
		char directory[400];
		content[0] = 0;
		webserv_html_head(content, "LOGFILES");
		webserv_html_start(content, 0);
		strcat(content, "<CENTER><TABLE width=\"90%\" border=\"0\">\n");
		strcat(content, "<TR class=\"thead\"><TH>DATE</TH><TH>SIZE</TH><TH>FORMAT</TH></TR>\n");
		int lc = 0;
		sprintf(directory, "%s/logs", get_datadirectory());
		if ((dir = opendir(directory)) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (dir_entry->d_name[1] != '.') {
					sprintf(new_path, "%s/%s", directory, dir_entry->d_name);
					if (lstat(new_path, &statbuf) == 0) {
						if (statbuf.st_mode&S_IFDIR) {
						} else {
							lc = 1 - lc;
							if (lc == 0) {
								strcat(content, "<TR class=\"first\">");
							} else {
								strcat(content, "<TR class=\"sec\">");
							}
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
								sprintf(tmp_str, "<TD><A href=\"%s\">%02d.%02d.%d %02d:%02d:%02d</A></TD><TD>%iB</TD><TD><A href=\"/logfiles/%s\">RAW</A> <A href=\"/logkml/%s\">KML</A></TD>", dir_entry->d_name, strukt.tm_mday, strukt.tm_mon + 1, strukt.tm_year + 1900, strukt.tm_hour, strukt.tm_min, strukt.tm_sec, (end - pos), dir_entry->d_name, dir_entry->d_name);
							} else {
								sprintf(tmp_str, "<TD><A href=\"%s\">%02d.%02d.%d %02d:%02d:%02d</A></TD><TD>%iKB</TD><TD><A href=\"/logfiles/%s\">RAW</A> <A href=\"/logkml/%s\">KML</A></TD>", dir_entry->d_name, strukt.tm_mday, strukt.tm_mon + 1, strukt.tm_year + 1900, strukt.tm_hour, strukt.tm_min, strukt.tm_sec, (end - pos) / 1024, dir_entry->d_name, dir_entry->d_name);
							}
							strcat(content, tmp_str);
							strcat(content, "</TR>");
						}
					}
				}
			}
			closedir(dir);
			dir = NULL;
		}
		strcat(content, "</TABLE>\n");
		webserv_html_stop(content);

		sprintf(buffer, header_str, (int)strlen(content), "text/html");
		write(fd, buffer, strlen(buffer));
		write(fd, content, strlen(content));
	} else {
		char tmp_str2[1024];
		if (strncmp(buffer2 + 4,"/logkml/", 8) == 0) {
			sprintf(tmp_str, "%s/logs/%s", get_datadirectory(), buffer2 + 12);
			sprintf(tmp_str2, "/tmp/%s.kml", buffer2 + 12);
			logplay_export_kml(tmp_str, tmp_str2, 255);
			webserv_child_dump_file(fd, tmp_str2, "text/xml");
		} else {
			sprintf(tmp_str, "%s/logs/%s", get_datadirectory(), buffer2 + 14);
			webserv_child_dump_file(fd, tmp_str, "text/plain");
		}
	}
}



void gcssetup_set (char *name, char *value) {
	if (strcmp("gcs_gps_port", name) == 0) {
		strcpy(setup.gcs_gps_port, value);
	}
	if (strcmp("gcs_gps_baud", name) == 0) {
		setup.gcs_gps_baud = atoi(value);
	}
	if (strcmp("rcflow_port", name) == 0) {
		strcpy(setup.rcflow_port, value);
	}
	if (strcmp("rcflow_baud", name) == 0) {
		setup.rcflow_baud = atoi(value);
	}
	if (strcmp("telemetry_port", name) == 0) {
		strcpy(ModelData[ModelActive].telemetry_port, value);
	}
	if (strcmp("telemetry_baud", name) == 0) {
		ModelData[ModelActive].telemetry_baud = atoi(value);
	}
	if (strcmp("jeti_port", name) == 0) {
		strcpy(setup.jeti_port, value);
	}
	if (strcmp("jeti_baud", name) == 0) {
		setup.jeti_baud = atoi(value);
	}
	if (strcmp("frsky_port", name) == 0) {
		strcpy(setup.frsky_port, value);
	}
	if (strcmp("frsky_baud", name) == 0) {
		setup.frsky_baud = atoi(value);
	}
	if (strcmp("tracker_port", name) == 0) {
		strcpy(setup.tracker_port, value);
	}
	if (strcmp("tracker_baud", name) == 0) {
		setup.tracker_baud = atoi(value);
	}
	if (strcmp("waypoint_active", name) == 0) {
		setup.waypoint_active = atoi(value);
	}
	if (strcmp("fullscreen", name) == 0) {
		setup.fullscreen = atoi(value);
	}
	if (strcmp("borderless", name) == 0) {
		setup.borderless = atoi(value);
	}
	if (strcmp("view_mode", name) == 0) {
		setup.view_mode = atoi(value);
	}
	if (strcmp("hud_view_screen", name) == 0) {
		setup.hud_view_screen = atoi(value);
	}
	if (strcmp("hud_view_stab", name) == 0) {
		setup.hud_view_stab = atoi(value);
	}
	if (strcmp("hud_view_map", name) == 0) {
		setup.hud_view_map = atoi(value);
	}
	if (strcmp("hud_view_video", name) == 0) {
		setup.hud_view_video = atoi(value);
	}
	if (strcmp("hud_view_tunnel", name) == 0) {
		setup.hud_view_tunnel = atoi(value);
	}
	if (strcmp("hud_view_mark", name) == 0) {
		setup.hud_view_mark = atoi(value);
	}
	if (strcmp("contrast", name) == 0) {
		setup.contrast = atoi(value);
	}
	if (strcmp("screen_w", name) == 0) {
		setup.screen_w = atoi(value);
	}
	if (strcmp("screen_h", name) == 0) {
		setup.screen_h = atoi(value);
	}
	if (strcmp("screen_border_x", name) == 0) {
		setup.screen_border_x = atoi(value);
	}
	if (strcmp("screen_border_y", name) == 0) {
		setup.screen_border_y = atoi(value);
	}
	if (strcmp("keep_ratio", name) == 0) {
		setup.keep_ratio = atof(value);
	}
	if (strcmp("touchscreen_device", name) == 0) {
		strcpy(setup.touchscreen_device, value);
	}
	if (strcmp("calibration_mode", name) == 0) {
		setup.calibration_mode = atoi(value);
	}
	if (strcmp("calibration_min_x", name) == 0) {
		setup.calibration_min_x = atoi(value);
	}
	if (strcmp("calibration_max_x", name) == 0) {
		setup.calibration_max_x = atoi(value);
	}
	if (strcmp("calibration_min_y", name) == 0) {
		setup.calibration_min_y = atoi(value);
	}
	if (strcmp("calibration_max_y", name) == 0) {
		setup.calibration_max_y = atoi(value);
	}
	if (strcmp("speak", name) == 0) {
		setup.speak = atoi(value);
	}
	if (strcmp("volt_min", name) == 0) {
		setup.volt_min = atof(value);
	}
	if (strcmp("qrcheck", name) == 0) {
		setup.qrcheck = atoi(value);
	}
	if (strcmp("opencv_device", name) == 0) {
		setup.opencv_device = atoi(value);
	}
	if (strcmp("opencv_features", name) == 0) {
		setup.opencv_features = atoi(value);
	}
	if (strcmp("videocapture_device", name) == 0) {
		strcpy(setup.videocapture_device, value);
	}
	if (strcmp("videocapture_width", name) == 0) {
		setup.videocapture_width = atoi(value);
	}
	if (strcmp("videocapture_height", name) == 0) {
		setup.videocapture_height = atoi(value);
	}
	if (strcmp("webport", name) == 0) {
		setup.webport = atoi(value);
	}
	if (strcmp("gearth_interval", name) == 0) {
		setup.gearth_interval = atof(value);
	}
}

void webserv_child_gcssetup (int fd, uint8_t mode) {
	DIR *dir = NULL;
	struct dirent *dir_entry = NULL;
	struct stat statbuf;
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char new_path[400];
	char tmp_str[100];
	uint8_t flag = 0;
	content[0] = 0;
	webserv_html_head(content, "SETUP");
	strcat(content, "<SCRIPT>\n");
	strcat(content, "function check_option(name) {\n");
	strcat(content, "	var value = document.getElementById(name).options[document.getElementById(name).selectedIndex].value;\n");
	strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
	strcat(content, "	xmlHttp.open(\"GET\", \"/gcssetup.html?\" + name + \"=\" + value, true);\n");
	strcat(content, "	xmlHttp.send(null);\n");
	strcat(content, "}\n");
	strcat(content, "function check_box(name) {\n");
	strcat(content, "	if (document.getElementById(name).checked) {\n");
	strcat(content, "		value = 1;\n");
	strcat(content, "	} else {\n");
	strcat(content, "		value = 0;\n");
	strcat(content, "	}\n");
	strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
	strcat(content, "	xmlHttp.open(\"GET\", \"/gcssetup.html?\" + name + \"=\" + value, true);\n");
	strcat(content, "	xmlHttp.send(null);\n");
	strcat(content, "}\n");
	strcat(content, "function check_value(name) {\n");
	strcat(content, "	var value = document.getElementById(name).value;\n");
	strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
	strcat(content, "	xmlHttp.open(\"GET\", \"/gcssetup.html?\" + name + \"=\" + value, true);\n");
	strcat(content, "	xmlHttp.send(null);\n");
	strcat(content, "}\n");
	strcat(content, "</SCRIPT>\n");
	webserv_html_start(content, 0);

	strcat(content, "<TABLE class=\"main\">\n");
	strcat(content, "<TR class=\"main\"><TD width=\"160px\" valign=\"top\">\n");

	strcat(content, "<TABLE width=\"100%\">\n");
	strcat(content, "<TR class=\"thead\"><TH>MODE</TH></TR>\n");
	strcat(content, "<TR class=\"first\"><TD><A href=\"/gcssetup.html\">Ports</A></TD></TR>");
	strcat(content, "<TR class=\"first\"><TD><A href=\"/gcssetup1.html\">GUI</A></TD></TR>");
	strcat(content, "<TR class=\"first\"><TD><A href=\"/gcssetup2.html\">TOUCH</A></TD></TR>");
	strcat(content, "<TR class=\"first\"><TD><A href=\"/gcssetup3.html\">ETC</A></TD></TR>");
	strcat(content, "</TABLE>\n");

	strcat(content, "</TD><TD valign=\"top\" width=\"20px\">&nbsp;</TD><TD valign=\"top\">\n");

	strcat(content, "<TABLE width=\"100%\">\n");
	strcat(content, "<TR class=\"thead\"><TH>NAME</TH><TH>VALUE</TH></TR>\n");
	int lc = 0;


	if (mode == 0) {
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>gcs_gps_port</TD>");
		sprintf(tmp_str, " <TD><SELECT class=\"form-input\" onchange=\"check_option('gcs_gps_port');\" id=\"gcs_gps_port\">\n");
		strcat(content, tmp_str);
		flag = 0;
		if ((dir = opendir("/dev")) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (dir_entry->d_name[0] != '.') {
					sprintf(new_path, "%s/%s", "/dev", dir_entry->d_name);
					if (lstat(new_path, &statbuf) == 0) {
						if ( statbuf.st_mode & S_IFDIR) {
						} else {
							if (strstr(new_path, "ttyS") > 0 || strstr(new_path, "ttyUSB") > 0 || strstr(new_path, "ttyACM") > 0) {
								if (strcmp(new_path, setup.gcs_gps_port) == 0) {
									sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", new_path, new_path);
									flag = 1;
								} else {
									sprintf(tmp_str, " <OPTION value=\"%s\">%s</OPTION>\n", new_path, new_path);
								}
								strcat(content, tmp_str);
							}
						}
					}
				}
			}
			closedir(dir);
			dir = NULL;
		}
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", setup.gcs_gps_port, setup.gcs_gps_port);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>gcs_gps_baud</TD>");
		flag = 0;
		strcat(content, " <TD><SELECT class=\"form-input\" onchange=\"check_option('gcs_gps_baud');\" id=\"gcs_gps_baud\">\n");
		if (setup.gcs_gps_baud == 1200) {
			sprintf(tmp_str, " <OPTION value=\"1200\" selected>1200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"1200\">1200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.gcs_gps_baud == 2400) {
			sprintf(tmp_str, " <OPTION value=\"2400\" selected>2400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"2400\">2400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.gcs_gps_baud == 4800) {
			sprintf(tmp_str, " <OPTION value=\"4800\" selected>4800</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"4800\">4800</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.gcs_gps_baud == 9600) {
			sprintf(tmp_str, " <OPTION value=\"9600\" selected>9600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"9600\">9600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.gcs_gps_baud == 19200) {
			sprintf(tmp_str, " <OPTION value=\"19200\" selected>19200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"19200\">19200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.gcs_gps_baud == 38400) {
			sprintf(tmp_str, " <OPTION value=\"38400\" selected>38400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"38400\">38400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.gcs_gps_baud == 57600) {
			sprintf(tmp_str, " <OPTION value=\"57600\" selected>57600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"57600\">57600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.gcs_gps_baud == 115200) {
			sprintf(tmp_str, " <OPTION value=\"115200\" selected>115200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"115200\">115200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%i\" selected>%i</OPTION>\n", setup.gcs_gps_baud, setup.gcs_gps_baud);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>rcflow_port</TD>");
		sprintf(tmp_str, " <TD><SELECT class=\"form-input\" onchange=\"check_option('rcflow_port');\" id=\"rcflow_port\">\n");
		strcat(content, tmp_str);
		flag = 0;
		if ((dir = opendir("/dev")) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (dir_entry->d_name[0] != '.') {
					sprintf(new_path, "%s/%s", "/dev", dir_entry->d_name);
					if (lstat(new_path, &statbuf) == 0) {
						if ( statbuf.st_mode & S_IFDIR) {
						} else {
							if (strstr(new_path, "ttyS") > 0 || strstr(new_path, "ttyUSB") > 0 || strstr(new_path, "ttyACM") > 0) {
								if (strcmp(new_path, setup.rcflow_port) == 0) {
									sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", new_path, new_path);
									flag = 1;
								} else {
									sprintf(tmp_str, " <OPTION value=\"%s\">%s</OPTION>\n", new_path, new_path);
								}
								strcat(content, tmp_str);
							}
						}
					}
				}
			}
			closedir(dir);
			dir = NULL;
		}
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", setup.rcflow_port, setup.rcflow_port);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>rcflow_baud</TD>");
		flag = 0;
		strcat(content, " <TD><SELECT class=\"form-input\" onchange=\"check_option('rcflow_baud');\" id=\"rcflow_baud\">\n");
		if (setup.rcflow_baud == 1200) {
			sprintf(tmp_str, " <OPTION value=\"1200\" selected>1200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"1200\">1200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.rcflow_baud == 2400) {
			sprintf(tmp_str, " <OPTION value=\"2400\" selected>2400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"2400\">2400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.rcflow_baud == 4800) {
			sprintf(tmp_str, " <OPTION value=\"4800\" selected>4800</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"4800\">4800</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.rcflow_baud == 9600) {
			sprintf(tmp_str, " <OPTION value=\"9600\" selected>9600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"9600\">9600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.rcflow_baud == 19200) {
			sprintf(tmp_str, " <OPTION value=\"19200\" selected>19200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"19200\">19200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.rcflow_baud == 38400) {
			sprintf(tmp_str, " <OPTION value=\"38400\" selected>38400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"38400\">38400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.rcflow_baud == 57600) {
			sprintf(tmp_str, " <OPTION value=\"57600\" selected>57600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"57600\">57600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.rcflow_baud == 115200) {
			sprintf(tmp_str, " <OPTION value=\"115200\" selected>115200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"115200\">115200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%i\" selected>%i</OPTION>\n", setup.rcflow_baud, setup.rcflow_baud);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>telemetry_port</TD>");
		sprintf(tmp_str, " <TD><SELECT class=\"form-input\" onchange=\"check_option('telemetry_port');\" id=\"telemetry_port\">\n");
		strcat(content, tmp_str);
		flag = 0;
		if ((dir = opendir("/dev")) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (dir_entry->d_name[0] != '.') {
					sprintf(new_path, "%s/%s", "/dev", dir_entry->d_name);
					if (lstat(new_path, &statbuf) == 0) {
						if ( statbuf.st_mode & S_IFDIR) {
						} else {
							if (strstr(new_path, "ttyS") > 0 || strstr(new_path, "ttyUSB") > 0 || strstr(new_path, "ttyACM") > 0) {
								if (strcmp(new_path, ModelData[ModelActive].telemetry_port) == 0) {
									sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", new_path, new_path);
									flag = 1;
								} else {
									sprintf(tmp_str, " <OPTION value=\"%s\">%s</OPTION>\n", new_path, new_path);
								}
								strcat(content, tmp_str);
							}
						}
					}
				}
			}
			closedir(dir);
			dir = NULL;
		}
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", ModelData[ModelActive].telemetry_port, ModelData[ModelActive].telemetry_port);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>telemetry_baud</TD>");
		flag = 0;
		strcat(content, " <TD><SELECT class=\"form-input\" onchange=\"check_option('telemetry_baud');\" id=\"telemetry_baud\">\n");
		if (ModelData[ModelActive].telemetry_baud == 1200) {
			sprintf(tmp_str, " <OPTION value=\"1200\" selected>1200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"1200\">1200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (ModelData[ModelActive].telemetry_baud == 2400) {
			sprintf(tmp_str, " <OPTION value=\"2400\" selected>2400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"2400\">2400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (ModelData[ModelActive].telemetry_baud == 4800) {
			sprintf(tmp_str, " <OPTION value=\"4800\" selected>4800</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"4800\">4800</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (ModelData[ModelActive].telemetry_baud == 9600) {
			sprintf(tmp_str, " <OPTION value=\"9600\" selected>9600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"9600\">9600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (ModelData[ModelActive].telemetry_baud == 19200) {
			sprintf(tmp_str, " <OPTION value=\"19200\" selected>19200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"19200\">19200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (ModelData[ModelActive].telemetry_baud == 38400) {
			sprintf(tmp_str, " <OPTION value=\"38400\" selected>38400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"38400\">38400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (ModelData[ModelActive].telemetry_baud == 57600) {
			sprintf(tmp_str, " <OPTION value=\"57600\" selected>57600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"57600\">57600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (ModelData[ModelActive].telemetry_baud == 115200) {
			sprintf(tmp_str, " <OPTION value=\"115200\" selected>115200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"115200\">115200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%i\" selected>%i</OPTION>\n", ModelData[ModelActive].telemetry_baud, ModelData[ModelActive].telemetry_baud);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>jeti_port</TD>");
		sprintf(tmp_str, " <TD><SELECT class=\"form-input\" onchange=\"check_option('jeti_port');\" id=\"jeti_port\">\n");
		strcat(content, tmp_str);
		flag = 0;
		if ((dir = opendir("/dev")) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (dir_entry->d_name[0] != '.') {
					sprintf(new_path, "%s/%s", "/dev", dir_entry->d_name);
					if (lstat(new_path, &statbuf) == 0) {
						if ( statbuf.st_mode & S_IFDIR) {
						} else {
							if (strstr(new_path, "ttyS") > 0 || strstr(new_path, "ttyUSB") > 0 || strstr(new_path, "ttyACM") > 0) {
								if (strcmp(new_path, setup.jeti_port) == 0) {
									sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", new_path, new_path);
									flag = 1;
								} else {
									sprintf(tmp_str, " <OPTION value=\"%s\">%s</OPTION>\n", new_path, new_path);
								}
								strcat(content, tmp_str);
							}
						}
					}
				}
			}
			closedir(dir);
			dir = NULL;
		}
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", setup.jeti_port, setup.jeti_port);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>jeti_baud</TD>");
		flag = 0;
		strcat(content, " <TD><SELECT class=\"form-input\" onchange=\"check_option('jeti_baud');\" id=\"jeti_baud\">\n");
		if (setup.jeti_baud == 1200) {
			sprintf(tmp_str, " <OPTION value=\"1200\" selected>1200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"1200\">1200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.jeti_baud == 2400) {
			sprintf(tmp_str, " <OPTION value=\"2400\" selected>2400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"2400\">2400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.jeti_baud == 4800) {
			sprintf(tmp_str, " <OPTION value=\"4800\" selected>4800</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"4800\">4800</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.jeti_baud == 9600) {
			sprintf(tmp_str, " <OPTION value=\"9600\" selected>9600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"9600\">9600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.jeti_baud == 19200) {
			sprintf(tmp_str, " <OPTION value=\"19200\" selected>19200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"19200\">19200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.jeti_baud == 38400) {
			sprintf(tmp_str, " <OPTION value=\"38400\" selected>38400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"38400\">38400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.jeti_baud == 57600) {
			sprintf(tmp_str, " <OPTION value=\"57600\" selected>57600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"57600\">57600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.jeti_baud == 115200) {
			sprintf(tmp_str, " <OPTION value=\"115200\" selected>115200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"115200\">115200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%i\" selected>%i</OPTION>\n", setup.jeti_baud, setup.jeti_baud);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>frsky_port</TD>");
		sprintf(tmp_str, " <TD><SELECT class=\"form-input\" onchange=\"check_option('frsky_port');\" id=\"frsky_port\">\n");
		strcat(content, tmp_str);
		flag = 0;
		if ((dir = opendir("/dev")) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (dir_entry->d_name[0] != '.') {
					sprintf(new_path, "%s/%s", "/dev", dir_entry->d_name);
					if (lstat(new_path, &statbuf) == 0) {
						if ( statbuf.st_mode & S_IFDIR) {
						} else {
							if (strstr(new_path, "ttyS") > 0 || strstr(new_path, "ttyUSB") > 0 || strstr(new_path, "ttyACM") > 0) {
								if (strcmp(new_path, setup.frsky_port) == 0) {
									sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", new_path, new_path);
									flag = 1;
								} else {
									sprintf(tmp_str, " <OPTION value=\"%s\">%s</OPTION>\n", new_path, new_path);
								}
								strcat(content, tmp_str);
							}
						}
					}
				}
			}
			closedir(dir);
			dir = NULL;
		}
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", setup.frsky_port, setup.frsky_port);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>frsky_baud</TD>");
		flag = 0;
		strcat(content, " <TD><SELECT class=\"form-input\" onchange=\"check_option('frsky_baud');\" id=\"frsky_baud\">\n");
		if (setup.frsky_baud == 1200) {
			sprintf(tmp_str, " <OPTION value=\"1200\" selected>1200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"1200\">1200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.frsky_baud == 2400) {
			sprintf(tmp_str, " <OPTION value=\"2400\" selected>2400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"2400\">2400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.frsky_baud == 4800) {
			sprintf(tmp_str, " <OPTION value=\"4800\" selected>4800</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"4800\">4800</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.frsky_baud == 9600) {
			sprintf(tmp_str, " <OPTION value=\"9600\" selected>9600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"9600\">9600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.frsky_baud == 19200) {
			sprintf(tmp_str, " <OPTION value=\"19200\" selected>19200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"19200\">19200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.frsky_baud == 38400) {
			sprintf(tmp_str, " <OPTION value=\"38400\" selected>38400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"38400\">38400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.frsky_baud == 57600) {
			sprintf(tmp_str, " <OPTION value=\"57600\" selected>57600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"57600\">57600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.frsky_baud == 115200) {
			sprintf(tmp_str, " <OPTION value=\"115200\" selected>115200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"115200\">115200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%i\" selected>%i</OPTION>\n", setup.frsky_baud, setup.frsky_baud);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>tracker_port</TD>");
		sprintf(tmp_str, " <TD><SELECT class=\"form-input\" onchange=\"check_option('tracker_port');\" id=\"tracker_port\">\n");
		strcat(content, tmp_str);
		flag = 0;
		if ((dir = opendir("/dev")) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (dir_entry->d_name[0] != '.') {
					sprintf(new_path, "%s/%s", "/dev", dir_entry->d_name);
					if (lstat(new_path, &statbuf) == 0) {
						if ( statbuf.st_mode & S_IFDIR) {
						} else {
							if (strstr(new_path, "ttyS") > 0 || strstr(new_path, "ttyUSB") > 0 || strstr(new_path, "ttyACM") > 0) {
								if (strcmp(new_path, setup.tracker_port) == 0) {
									sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", new_path, new_path);
									flag = 1;
								} else {
									sprintf(tmp_str, " <OPTION value=\"%s\">%s</OPTION>\n", new_path, new_path);
								}
								strcat(content, tmp_str);
							}
						}
					}
				}
			}
			closedir(dir);
			dir = NULL;
		}
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", setup.tracker_port, setup.tracker_port);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>tracker_baud</TD>");
		flag = 0;
		strcat(content, " <TD><SELECT class=\"form-input\" onchange=\"check_option('tracker_baud');\" id=\"tracker_baud\">\n");
		if (setup.tracker_baud == 1200) {
			sprintf(tmp_str, " <OPTION value=\"1200\" selected>1200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"1200\">1200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.tracker_baud == 2400) {
			sprintf(tmp_str, " <OPTION value=\"2400\" selected>2400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"2400\">2400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.tracker_baud == 4800) {
			sprintf(tmp_str, " <OPTION value=\"4800\" selected>4800</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"4800\">4800</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.tracker_baud == 9600) {
			sprintf(tmp_str, " <OPTION value=\"9600\" selected>9600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"9600\">9600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.tracker_baud == 19200) {
			sprintf(tmp_str, " <OPTION value=\"19200\" selected>19200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"19200\">19200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.tracker_baud == 38400) {
			sprintf(tmp_str, " <OPTION value=\"38400\" selected>38400</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"38400\">38400</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.tracker_baud == 57600) {
			sprintf(tmp_str, " <OPTION value=\"57600\" selected>57600</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"57600\">57600</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (setup.tracker_baud == 115200) {
			sprintf(tmp_str, " <OPTION value=\"115200\" selected>115200</OPTION>\n");
			flag = 1;
		} else {
			sprintf(tmp_str, " <OPTION value=\"115200\">115200</OPTION>\n");
		}
		strcat(content, tmp_str);
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%i\" selected>%i</OPTION>\n", setup.tracker_baud, setup.tracker_baud);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
	} else if (mode == 1) {
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>fullscreen</TD>");
		if (setup.fullscreen == 1) {
			strcat(content, "<TD><INPUT class=\"form-input\" onchange=\"check_box('fullscreen');\" id=\"fullscreen\" type=\"checkbox\" checked></TD>\n");
		} else {
			strcat(content, "<TD><INPUT class=\"form-input\" onchange=\"check_box('fullscreen');\" id=\"fullscreen\" type=\"checkbox\"></TD>\n");
		}
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>borderless</TD>");
		if (setup.borderless == 1) {
			strcat(content, "<TD><INPUT class=\"form-input\" onchange=\"check_box('borderless');\" id=\"borderless\" type=\"checkbox\" checked></TD>\n");
		} else {
			strcat(content, "<TD><INPUT class=\"form-input\" onchange=\"check_box('borderless');\" id=\"borderless\" type=\"checkbox\"></TD>\n");
		}
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>view_mode</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('view_mode');\" id=\"view_mode\" value=\"%i\" type=\"text\"></TD>\n", setup.view_mode);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>hud_view_screen</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('hud_view_screen');\" id=\"hud_view_screen\" value=\"%i\" type=\"text\"></TD>\n", setup.hud_view_screen);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>hud_view_stab</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('hud_view_stab');\" id=\"hud_view_stab\" value=\"%i\" type=\"text\"></TD>\n", setup.hud_view_stab);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>hud_view_map</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('hud_view_map');\" id=\"hud_view_map\" value=\"%i\" type=\"text\"></TD>\n", setup.hud_view_map);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>hud_view_video</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('hud_view_video');\" id=\"hud_view_video\" value=\"%i\" type=\"text\"></TD>\n", setup.hud_view_video);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>hud_view_tunnel</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('hud_view_tunnel');\" id=\"hud_view_tunnel\" value=\"%i\" type=\"text\"></TD>\n", setup.hud_view_tunnel);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>hud_view_mark</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('hud_view_mark');\" id=\"hud_view_mark\" value=\"%i\" type=\"text\"></TD>\n", setup.hud_view_mark);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>contrast</TD>");
		if (setup.contrast == 1) {
			strcat(content, "<TD><INPUT class=\"form-input\" onchange=\"check_box('contrast');\" id=\"contrast\" type=\"checkbox\" checked></TD>\n");
		} else {
			strcat(content, "<TD><INPUT class=\"form-input\" onchange=\"check_box('contrast');\" id=\"contrast\" type=\"checkbox\"></TD>\n");
		}
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>screen_w</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('screen_w');\" id=\"screen_w\" value=\"%i\" type=\"text\"></TD>\n", setup.screen_w);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>screen_h</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('screen_h');\" id=\"screen_h\" value=\"%i\" type=\"text\"></TD>\n", setup.screen_h);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>screen_border_x</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('screen_border_x');\" id=\"screen_border_x\" value=\"%i\" type=\"text\"></TD>\n", setup.screen_border_x);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>screen_border_y</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('screen_border_y');\" id=\"screen_border_y\" value=\"%i\" type=\"text\"></TD>\n", setup.screen_border_y);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>keep_ratio</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('keep_ratio');\" id=\"keep_ratio\" value=\"%0.1f\" type=\"text\"></TD>\n", setup.keep_ratio);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
	} else if (mode == 2) {
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>touchscreen_device</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('touchscreen_device');\" id=\"touchscreen_device\" value=\"%s\" type=\"text\"></TD>\n", setup.touchscreen_device);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>calibration_mode</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('calibration_mode');\" id=\"calibration_mode\" value=\"%i\" type=\"text\"></TD>\n", setup.calibration_mode);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>calibration_min_x</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('calibration_min_x');\" id=\"calibration_min_x\" value=\"%i\" type=\"text\"></TD>\n", setup.calibration_min_x);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>calibration_max_x</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('calibration_max_x');\" id=\"calibration_max_x\" value=\"%i\" type=\"text\"></TD>\n", setup.calibration_max_x);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>calibration_min_y</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('calibration_min_y');\" id=\"calibration_min_y\" value=\"%i\" type=\"text\"></TD>\n", setup.calibration_min_y);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>calibration_max_y</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('calibration_max_y');\" id=\"calibration_max_y\" value=\"%i\" type=\"text\"></TD>\n", setup.calibration_max_y);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
	} else {
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>speak</TD>");
		if (setup.speak == 1) {
			strcat(content, "<TD><INPUT class=\"form-input\" onchange=\"check_box('speak');\" id=\"speak\" type=\"checkbox\" checked></TD>\n");
		} else {
			strcat(content, "<TD><INPUT class=\"form-input\" onchange=\"check_box('speak');\" id=\"speak\" type=\"checkbox\"></TD>\n");
		}
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>volt_min</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('volt_min');\" id=\"volt_min\" value=\"%0.1f\" type=\"text\"></TD>\n", setup.volt_min);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>qrcheck</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('qrcheck');\" id=\"qrcheck\" value=\"%i\" type=\"text\"></TD>\n", setup.qrcheck);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>opencv_device</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('opencv_device');\" id=\"opencv_device\" value=\"%i\" type=\"text\"></TD>\n", setup.opencv_device);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>opencv_features</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('opencv_features');\" id=\"opencv_features\" value=\"%i\" type=\"text\"></TD>\n", setup.opencv_features);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>videocapture_device</TD>");
		sprintf(tmp_str, " <TD><SELECT class=\"form-input\" onchange=\"check_option('videocapture_device');\" id=\"videocapture_device\">\n");
		strcat(content, tmp_str);
		flag = 0;
		if ((dir = opendir("/dev")) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (dir_entry->d_name[0] != '.') {
					sprintf(new_path, "%s/%s", "/dev", dir_entry->d_name);
					if (lstat(new_path, &statbuf) == 0) {
						if ( statbuf.st_mode & S_IFDIR) {
						} else {
							if (strstr(new_path, "/dev/video") > 0) {
								if (strcmp(new_path, setup.videocapture_device) == 0) {
									sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", new_path, new_path);
									flag = 1;
								} else {
									sprintf(tmp_str, " <OPTION value=\"%s\">%s</OPTION>\n", new_path, new_path);
								}
								strcat(content, tmp_str);
							}
						}
					}
				}
			}
			closedir(dir);
			dir = NULL;
		}
		if (flag == 0) {
			sprintf(tmp_str, " <OPTION value=\"%s\" selected>%s</OPTION>\n", setup.videocapture_device, setup.videocapture_device);
			strcat(content, tmp_str);
		}
		strcat(content, " </SELECT></TD>\n");
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>videocapture_width</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('videocapture_width');\" id=\"videocapture_width\" value=\"%i\" type=\"text\"></TD>\n", setup.videocapture_width);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>videocapture_height</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('videocapture_height');\" id=\"videocapture_height\" value=\"%i\" type=\"text\"></TD>\n", setup.videocapture_height);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>webport</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('webport');\" id=\"webport\" value=\"%i\" type=\"text\"></TD>\n", setup.webport);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>waypoint_active</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('waypoint_active');\" id=\"waypoint_active\" value=\"%i\" type=\"text\"></TD>\n", setup.waypoint_active);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
		lc = 1 - lc;
		if (lc == 0) {
			strcat(content, "<TR class=\"first\">");
		} else {
			strcat(content, "<TR class=\"sec\">");
		}
		strcat(content, " <TD>gearth_interval</TD>");
		sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('gearth_interval');\" id=\"gearth_interval\" value=\"%0.1f\" type=\"text\"></TD>\n", setup.gearth_interval);
		strcat(content, tmp_str);
		strcat(content, "</TR>");
	}

	strcat(content, "</TABLE><BR><BR>");

	strcat(content, "</TD></TR></TABLE>\n");

	webserv_html_stop(content);

	sprintf(buffer, header_str, (int)strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}


void webserv_child (int fd) {
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[BUFSIZE + 1];
	char servername[1024];
	char type[100];
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
					if (strcmp(tmp_str, "name") == 0) {
						strncpy(ModelData[ModelActive].name, tmp_str + start, 199);
					} else if (strcmp(tmp_str, "image") == 0) {
						strncpy(ModelData[ModelActive].image, tmp_str + start, 511);
					} else if (strcmp(tmp_str, "dronetype") == 0) {
						ModelData[ModelActive].dronetype = atoi(tmp_str + start);
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
						ModelData[ModelActive].mavlink_update = atoi(tmp_str + start);
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
#ifdef ANDROID
		SDL_Log("###################\n");
		SDL_Log("%s", buffer);
		SDL_Log("\n###################\n");
#endif
		if (strncmp(buffer + 4,"/modeldata", 10) == 0) {
			webserv_child_dump_modeldata(fd);

		} else if (strncmp(buffer + 4,"/waypoint_new?", 14) == 0) {
			int wp_num = 0;
			float lat = 0.0;
			float lon = 0.0;
			sscanf(buffer + 4 + 14, "wp%i=%f,%f", &wp_num, &lat, &lon);
			sprintf(WayPoints[ModelActive][wp_num].name, "WP%i", wp_num);
			strcpy(WayPoints[ModelActive][wp_num].command, "WAYPOINT");
			WayPoints[ModelActive][wp_num].p_lat = lat;
			WayPoints[ModelActive][wp_num].p_long = lon;
			WayPoints[ModelActive][wp_num].p_alt = WayPoints[ModelActive][0].p_alt;
			sprintf(content, "done");
			sprintf(buffer, header_str, (int)strlen(content), "text/plain");
		} else if (strncmp(buffer + 4,"/waypoint_set?", 14) == 0) {
			int n = 0;
			int wp_num = 0;
			char name[20];
			char value[20];
			sscanf(buffer + 4 + 14, "wp%i&%[0-9a-zA-Z_]=%s", &wp_num, name, value);
			if (strcmp(name, "NAME") == 0) {
				strcpy(WayPoints[ModelActive][wp_num].name, value);
			} else if (strcmp(name, "TYPE") == 0) {
				strcpy(WayPoints[ModelActive][wp_num].command, value);
			} else if (strcmp(name, "LONG") == 0) {
				WayPoints[ModelActive][wp_num].p_long = atof(value);
			} else if (strcmp(name, "LAT") == 0) {
				WayPoints[ModelActive][wp_num].p_lat = atof(value);
			} else if (strcmp(name, "ALT") == 0) {
				WayPoints[ModelActive][wp_num].p_alt = atof(value);
			} else if (strcmp(name, "DEL") == 0) {
				WayPoints[ModelActive][wp_num].name[0] = 0;
				WayPoints[ModelActive][wp_num].p_lat = 0.0;
				WayPoints[ModelActive][wp_num].p_long = 0.0;
				WayPoints[ModelActive][wp_num].p_alt = 0.0;
			} else if (strcmp(name, "ADD") == 0) {
				sprintf(WayPoints[ModelActive][wp_num].name, "WP%i", n);
				strcpy(WayPoints[ModelActive][wp_num].command, "WAYPOINT");
				WayPoints[ModelActive][wp_num].p_lat = WayPoints[ModelActive][0].p_lat;
				WayPoints[ModelActive][wp_num].p_long = WayPoints[ModelActive][0].p_long;
				WayPoints[ModelActive][wp_num].p_alt = WayPoints[ModelActive][0].p_alt;
			}
			if (strcmp(name, "DEL") == 0 || strcmp(name, "ADD") == 0) {
				sprintf(content, "<meta http-equiv=\"Refresh\" content=\"0; URL=/waypoints.html\">");
				sprintf(buffer, header_str, (int)strlen(content), "text/html");
			} else {
				sprintf(content, "wp set value(%i): %s to %s\n", wp_num, name, value);
				sprintf(buffer, header_str, (int)strlen(content), "text/plain");
			}
			write(fd, buffer, strlen(buffer));
			write(fd, content, strlen(content));
		} else if (strncmp(buffer + 4,"/waypoints.html", 15) == 0) {
			webserv_child_waypoints(fd, servername);
		} else if (strncmp(buffer + 4,"/blender.txt", 12) == 0) {
			webserv_child_dump_blender(fd);
		} else if (strncmp(buffer + 4,"/blender-export.py", 18) == 0) {
			sprintf(tmp_str, "%s/webserv/blender-export.py", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/plain");
			blender_first_lat = ModelData[ModelActive].p_lat;
			blender_first_long = ModelData[ModelActive].p_long;
			blender_first_alt = ModelData[ModelActive].p_alt;
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
			if (get_background_model(ModelActive, tmp_str) == 0) {
				if (obj3d_collada.name[0] == 0) {
					SDL_Log("webserv: convert '%s' to collada-format\n", tmp_str);
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


		} else if (strncmp(buffer + 4,"/logkml/", 8) == 0 || strncmp(buffer + 4,"/logfiles/", 10) == 0) {
			webserv_child_kml_logfiles(fd, servername, buffer);

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
			strcat(display_html3, "		<canvas id=\"hudcanvas\" width=\"1024\" height=\"720\" style=\"position: absolute; left: 10; top: 70; z-index: 1;\"></canvas>\n");
			strcat(display_html3, "		<canvas id=\"hudcanvas2\" width=\"1024\" height=\"720\" style=\"position: absolute; left: 10; top: 70; z-index: 0;\"></canvas>\n");
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
			SDL_Log("## %s ##\n", buffer + 4);
			webserv_child_dump_file(fd, buffer + 4, "image/jpg");
		} else if (strncmp(buffer + 4,"/multigcs.html", 14) == 0) {
			sprintf(tmp_str, "%s/webserv/multigcs.html", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/html");

		// HTML5 HUD-View + Map
		} else if (strncmp(buffer + 4,"/map.html", 9) == 0) {
			webserv_child_show_map(fd);
		} else if (strncmp(buffer + 4,"/hud.html", 9) == 0) {
			webserv_child_show_hud(fd);
		} else if (strncmp(buffer + 4,"/misc.html", 10) == 0) {
			webserv_child_show_misc(fd);
		} else if (strncmp(buffer + 4,"/hudredraw.js", 13) == 0) {
			webserv_child_hud_redraw(fd);
		} else if (strncmp(buffer + 4,"/hudredraw_small.js", 19) == 0) {
			webserv_child_hud_redraw_small(fd);
		} else if (strncmp(buffer + 4,"/gcssetup.html?", 15) == 0) {
			char name[1024];
			char value[1024];
			sscanf(buffer + 4 + 15, "%[0-9a-zA-Z_]=%s", name, value);
			gcssetup_set(name, value);
			strcpy(content, "");
			sprintf(buffer, header_str, (int)strlen(content), "text/html");
			write(fd, buffer, strlen(buffer));
			write(fd, content, strlen(content));

		} else if (strncmp(buffer + 4,"/gcssetup.html", 14) == 0) {
			webserv_child_gcssetup(fd, 0);
		} else if (strncmp(buffer + 4,"/gcssetup1.html", 15) == 0) {
			webserv_child_gcssetup(fd, 1);
		} else if (strncmp(buffer + 4,"/gcssetup2.html", 15) == 0) {
			webserv_child_gcssetup(fd, 2);
		} else if (strncmp(buffer + 4,"/gcssetup3.html", 15) == 0) {
			webserv_child_gcssetup(fd, 3);
		} else if (strncmp(buffer + 4,"/map.js", 7) == 0) {
			sprintf(tmp_str, "%s/webserv/map.js", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/plain");
		} else if (strncmp(buffer + 4,"/tile/", 6) == 0) {
			int tx = 0;
			int ty = 0;
			int zoom = 0;
			sscanf(buffer + 10, "%i/%i/%i", &zoom, &tx, &ty);
			sprintf(tmp_str, mapnames[map_type][MAP_FILE], get_datadirectory(), zoom, tx, ty);
			if (strstr(tmp_str, ".jpg\0") > 0) {
				webserv_child_dump_file(fd, tmp_str, "image/jpg");
			} else {
				webserv_child_dump_file(fd, tmp_str, "image/png");
			}
		} else if (strncmp(buffer + 4,"/lonlat.txt", 11) == 0) {
			webserv_child_show_lonlat(fd);
		} else if (strncmp(buffer + 4,"/marker.png", 11) == 0) {
			sprintf(tmp_str, "%s/webserv/marker.png", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "image/png");
		} else if (strncmp(buffer + 4,"/model.png", 10) == 0) {
			sprintf(tmp_str, "%s/textures/%s.png", BASE_DIR, dronetypes[ModelData[ModelActive].dronetype]);
			webserv_child_dump_file(fd, tmp_str, "image/png");
		} else if (strncmp(buffer + 4,"/img/marker.png", 15) == 0) {
			sprintf(tmp_str, "%s/webserv/marker.png", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "image/png");
		} else if (strncmp(buffer + 4,"/img/model.png", 14) == 0) {
			sprintf(tmp_str, "%s/webserv/model.png", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "image/png");
		} else if (strncmp(buffer + 4,"/style.css", 10) == 0) {
			sprintf(tmp_str, "%s/webserv/style.css", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/plain");
		} else if (strncmp(buffer + 4,"/bg.png", 7) == 0) {
			sprintf(tmp_str, "%s/webserv/bg.png", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "image/png");
		} else if (strncmp(buffer + 4,"/favicon.ico", 12) == 0) {
			sprintf(tmp_str, "%s/webserv/favicon.ico", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "image/png");

		} else if (strncmp(buffer + 4,"/copyright", 10) == 0) {
			sprintf(tmp_str, "%s/webserv/copyright", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/plain");
		} else if (strncmp(buffer + 4,"/GPLv2.txt", 10) == 0) {
			sprintf(tmp_str, "%s/webserv/GPLv2.txt", BASE_DIR);
			webserv_child_dump_file(fd, tmp_str, "text/plain");

#ifndef OSX
#ifdef SDLGL
		} else if (strncmp(buffer + 4,"/video.png", 10) == 0) {
#if defined USE_V4L
			SDL_SavePNG(videodev_loop(), "/tmp/video.png");
			webserv_child_dump_file(fd, "/tmp/video.png", "image/png");
#endif
/*
			char PngBuffer[502249];
			SDL_RWops *rwop = SDL_RWFromMem(PngBuffer, 502249);
			SDL_SavePNG_RW(videodev_loop(), rwop, 1);
			int32_t length = SDL_RWseek(rwop, 0, SEEK_END);
			char buffer[BUFSIZE + 1];
			sprintf(buffer, header_str, 502249, "image/png");
			write(fd, buffer, strlen(buffer));
			write(fd, PngBuffer, 502249);
*/
#endif
#endif
		} else {

			type[0] = 0;
			content[0] = 0;

			mwi21_web_get(ModelActive, buffer + 4, content, type);
			if (type[0] != 0 && content[0] != 0) {
				sprintf(buffer, header_str, (int)strlen(content), type);
				write(fd, buffer, strlen(buffer));
				write(fd, content, strlen(content));
			}

			mavlink_web_get(ModelActive, buffer + 4, content, type);
			if (type[0] != 0 && content[0] != 0) {
				sprintf(buffer, header_str, (int)strlen(content), type);
				write(fd, buffer, strlen(buffer));
				write(fd, content, strlen(content));
			}

			if (type[0] == 0 || content[0] == 0) {
				SDL_Log("###################\n");
				SDL_Log("%s", buffer);
				SDL_Log("\n###################\n");
				sprintf(tmp_str, "%s/webserv/index.html", BASE_DIR);
				webserv_child_dump_file(fd, tmp_str, "text/html");
			}
		}
	}
	close(fd);
	return;
}

#ifndef WINDOWS
int webserv_thread (void *data) {
	int listenfd;
	int socketfd;
	socklen_t length;
	static struct sockaddr_in cli_addr;
	static struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(setup.webport);
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
	SDL_Log("webserv: exit thread\n");
	return(0);
}
#endif

void webserv_init (void) {
	SDL_Log("webserv: init thread\n");
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
	SDL_Log("webserv: running on Port: %i\n", setup.webport);
}

void webserv_exit (void) {
	webserv_running = 0;
	if (thread_webserv != NULL) {
		SDL_Log("webserv: wait thread\n");
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

uint8_t webserv_is_running (void) {
	return webserv_running;
}

#else
uint8_t webserv_is_running (void) {
	return 0;
}

void webserv_init (void) {
}

void webserv_exit (void) {
}

void webserv_html_head (char *content, char *title) {
}

void webserv_html_start (char *content, uint8_t init) {
}

void webserv_html_stop (char *content) {
}
#endif

