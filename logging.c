
#include <all.h>

static FILE *fr_play = NULL;
char *Logdata = NULL;
int log_startup_time = 0;
uint8_t logmode = 0;
uint8_t logplay = 0;
uint8_t logplay_open = 0;
uint8_t logplay_play = 0;
uint8_t logplay_pause = 0;
uint32_t logplay_msec = 0;
uint32_t logplay_fpos = 0;
uint32_t logplay_startsec = 0;
uint32_t logplay_starttime = 0;
uint8_t logplay_list = 0;
uint8_t logplay_filelist = 0;
uint32_t logrec_starttime = 0;
uint32_t logrec_startsec = 0;
char logplay_file[1024];

void map_log_show (void) {
	FILE *fr_log = NULL;
	char last_line[1025];
	float last_lat = 0.0;
	float last_long = 0.0;
	float last_alt = 0.0;
	if (logplay_file[0] != 0) {
		if ((fr_log = fopen(logplay_file, "r")) == NULL) {
			SDL_Log("logplay: error loading file: %s\n", logplay_file);
			return;
		}
		while (fgets(last_line, 500, fr_log) != 0) {
			if (strncmp(last_line, "GPS;", 4) == 0) {
				uint32_t lsec = 0;
				uint32_t lmicros = 0;
				float p_lat = 0.0;
				float p_long = 0.0;
				float p_alt = 0.0;
				sscanf(last_line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
				if (p_lat != 0.0 && p_long != 0.0) {
//					mark_point(GlobalesContext, p_lat, p_long, p_alt, "", "", 0, 0.1, 0.0, lat, lon, zoom);
					if (last_lat != 0.0 && last_long != 0.0) {
						mark_route(GlobalesContext, last_lat, last_long, last_alt, p_lat, p_long, p_alt, 6, lat, lon, zoom);
					}
					last_lat = p_lat;
					last_long = p_long;
					last_alt = p_alt;
				}
			} else if (strncmp(last_line, "GPS,", 4) == 0) {
				float dn = 0.0;
				float dn2 = 0.0;
				float dn4 = 0.0;
				uint32_t dn3 = 0;
				float p_lat = 0.0;
				float p_long = 0.0;
				float p_alt = 0.0;
				float speed = 0.0;
				int gpsfix = 0;
				int numSat = 0;
				sscanf(last_line, "GPS,%i,%i,%i,%f,%f,%f,%f,%f,%f,%f", &gpsfix, &dn3, &numSat, &dn, &p_lat, &p_long, &dn2, &p_alt, &speed, &dn4);
				if (p_lat != 0.0 && p_long != 0.0) {
//					mark_point(GlobalesContext, p_lat, p_long, p_alt, "", "", 0, 0.1, 0.0, lat, lon, zoom);
					if (last_lat != 0.0 && last_long != 0.0) {
						mark_route(GlobalesContext, last_lat, last_long, last_alt, p_lat, p_long, p_alt, 6, lat, lon, zoom);
					}
					last_lat = p_lat;
					last_long = p_long;
					last_alt = p_alt;
				}
			}
		}
		fclose(fr_log);
	}
}

void logplay_export_kml (char *logfile, char *kmlfile, uint8_t type) {
	SDL_Log("logplay: %s -> %s\n", logfile, kmlfile);
	if (logfile[0] != 0) {
		float p_lat = 0.0;
		float p_long = 0.0;
		float p_alt = 0.0;
		float pitch = 0.0;
		float roll = 0.0;
		float yaw = 0.0;
		float speed = 0.0;
		int gpsfix = 0;
		int numSat = 0;
		char line[1024];
		uint32_t lsec = 0;
		uint32_t lmicros = 0;
		float last_p_long = 0.0;
		float last_p_lat = 0.0;
		float last_p_alt = 0.0;
//		float last_pitch = 0.0;
//		float last_roll = 0.0;
//		float last_yaw = 0.0;
//		uint32_t last_lsec = 0;
//		uint32_t last_lmicros = 0;
		uint16_t point_nr = 0;
	        FILE *fr = NULL;
		FILE *log_fr = NULL;
		log_fr = fopen(logfile, "r");
		if (log_fr != 0) {
		        fr = fopen(kmlfile, "wb");
			if (fr != 0) {
				fprintf(fr, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
//				fprintf(fr, "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
				fprintf(fr, "<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\">\n");

				fprintf(fr, "  <Document>\n");
				fprintf(fr, "    <name>%s</name>\n", "MultiGCS");
				fprintf(fr, "    <description>Flight-Data</description>\n");

if (type & (1<<0)) {
				fprintf(fr, "   <Folder>\n");
				fprintf(fr, "    <name>Route</name>\n");
				fprintf(fr, "    <open>0</open>\n");
				fprintf(fr, "    <visibility>0</visibility>\n");
				fprintf(fr, "    <Style id=\"yellowLineGreenPoly\">\n");
				fprintf(fr, "      <LineStyle>\n");
				fprintf(fr, "        <color>7f00ffff</color>\n");
				fprintf(fr, "        <width>4</width>\n");
				fprintf(fr, "      </LineStyle>\n");
				fprintf(fr, "      <PolyStyle>\n");
				fprintf(fr, "        <color>7f00ff00</color>\n");
				fprintf(fr, "      </PolyStyle>\n");
				fprintf(fr, "    </Style>\n");
				fprintf(fr, "    <Placemark>\n");
				fprintf(fr, "      <name>Absolute Extruded</name>\n");
				fprintf(fr, "      <description>Datalog</description>\n");
				fprintf(fr, "      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
				fprintf(fr, "      <LineString>\n");
				fprintf(fr, "        <extrude>1</extrude>\n");
				fprintf(fr, "        <tessellate>1</tessellate>\n");
				fprintf(fr, "        <altitudeMode>absolute</altitudeMode>\n");
//				fprintf(fr, "        <altitudeMode>relativeToGround</altitudeMode>\n");
				fprintf(fr, "        <coordinates>");
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
						fprintf(fr, " %f,%f,%f \n", p_long, p_lat, p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
					} else if (strncmp(line, "GPS,", 4) == 0) {
						float dn = 0.0;
						float dn2 = 0.0;
						float dn4 = 0.0;
						uint32_t dn3 = 0;
						sscanf(line, "GPS,%i,%i,%i,%f,%f,%f,%f,%f,%f,%f", &gpsfix, &dn3, &numSat, &dn, &p_lat, &p_long, &dn2, &p_alt, &speed, &dn4);
						fprintf(fr, " %f,%f,%f \n", p_long, p_lat, p_alt);
					} else if (strncmp(line, "ATT,", 4) == 0) {
						sscanf(line, "ATT,%f,%f,%f", &pitch, &roll, &yaw);
					}
				}
				fprintf(fr, "        </coordinates>\n");
				fprintf(fr, "      </LineString>\n");
				fprintf(fr, "    </Placemark>\n");
				fprintf(fr, "   </Folder>\n");
}
if (type & (1<<1)) {
				fprintf(fr, "   <Folder>\n");
				fprintf(fr, "    <name>Arrows</name>\n");
				fprintf(fr, "    <open>0</open>\n");
				fprintf(fr, "    <visibility>0</visibility>\n");
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						last_p_long = p_long;
						last_p_lat = p_lat;
						last_p_alt = p_alt;
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);

						fprintf(fr, "    <Style id=\"STYLE%i\">\n", point_nr);
						fprintf(fr, "      <LabelStyle>\n");
						fprintf(fr, "        <scale>0.0</scale>\n");
						fprintf(fr, "      </LabelStyle>\n");
						fprintf(fr, "      <IconStyle>\n");
						fprintf(fr, "        <scale>0.8</scale>\n");
						fprintf(fr, "        <Icon>\n");
						fprintf(fr, "          <href>http://www.earthpoint.us/Dots/GoogleEarth/shapes/arrow.png</href>\n");
						fprintf(fr, "        </Icon>\n");
//						fprintf(fr, "        <tilt>%f</tilt>\n", pitch + 90.0);
//						fprintf(fr, "        <roll>%f</roll>\n", roll);
						fprintf(fr, "        <heading>%f</heading>\n", yaw - 180.0);
						fprintf(fr, "        <color>FFFF0000</color>\n");
						fprintf(fr, "      </IconStyle>\n");
						fprintf(fr, "    </Style>\n");

						fprintf(fr, "    <Placemark>\n");
						fprintf(fr, "      <name>%i</name>\n", point_nr);
						fprintf(fr, "      <styleUrl>#STYLE%i</styleUrl>\n", point_nr);
						fprintf(fr, "      <description><![CDATA[%i.%03i<BR>alt=%fm<BR>pitch=%f<BR>roll=%f<BR>yaw=%f]]></description>\n", lsec, lmicros, p_alt, pitch, roll, yaw);
						fprintf(fr, "      <Point>\n");
						fprintf(fr, "        <extrude>1</extrude>\n");
						fprintf(fr, "        <altitudeMode>absolute</altitudeMode>\n");
						fprintf(fr, "        <coordinates>%f, %f, %f</coordinates>\n", p_long, p_lat, p_alt);
						fprintf(fr, "      </Point>\n");
						fprintf(fr, "      <LookAt>\n");
						fprintf(fr, "        <longitude>%f</longitude>\n", last_p_long);
						fprintf(fr, "        <latitude>%f</latitude>\n", last_p_lat);
						fprintf(fr, "        <altitude>%f</altitude>\n", last_p_alt);
						fprintf(fr, "        <heading>%f</heading>\n", yaw);
						fprintf(fr, "        <tilt>%f</tilt>\n", pitch + 90.0);
						fprintf(fr, "        <roll>%f</roll>\n", roll);
						fprintf(fr, "        <altitudeMode>absolute</altitudeMode>\n");
						fprintf(fr, "      </LookAt>\n");
						fprintf(fr, "    </Placemark>\n");

						point_nr++;
					}
				}
				fprintf(fr, "   </Folder>\n");
}
if (type & (1<<2)) {
				fprintf(fr, "    <Style id=\"multiTrack_n\">\n");
				fprintf(fr, "      <IconStyle>\n");
				fprintf(fr, "        <Icon>\n");
				fprintf(fr, "          <href>http://earth.google.com/images/kml-icons/track-directional/track-0.png</href>\n");
				fprintf(fr, "        </Icon>\n");
				fprintf(fr, "      </IconStyle>\n");
				fprintf(fr, "      <LineStyle>\n");
				fprintf(fr, "        <color>99ffac59</color>\n");
				fprintf(fr, "        <width>6</width>\n");
				fprintf(fr, "      </LineStyle>\n");
				fprintf(fr, "    </Style>\n");
				fprintf(fr, "    <Style id=\"multiTrack_h\">\n");
				fprintf(fr, "      <IconStyle>\n");
				fprintf(fr, "        <scale>1.2</scale>\n");
				fprintf(fr, "        <Icon>\n");
				fprintf(fr, "          <href>http://earth.google.com/images/kml-icons/track-directional/track-0.png</href>\n");
				fprintf(fr, "        </Icon>\n");
				fprintf(fr, "      </IconStyle>\n");
				fprintf(fr, "      <LineStyle>\n");
				fprintf(fr, "        <color>99ffac59</color>\n");
				fprintf(fr, "        <width>8</width>\n");
				fprintf(fr, "      </LineStyle>\n");
				fprintf(fr, "    </Style>\n");
				fprintf(fr, "    <StyleMap id=\"multiTrack\">\n");
				fprintf(fr, "      <Pair>\n");
				fprintf(fr, "        <key>normal</key>\n");
				fprintf(fr, "        <styleUrl>#multiTrack_n</styleUrl>\n");
				fprintf(fr, "      </Pair>\n");
				fprintf(fr, "      <Pair>\n");
				fprintf(fr, "        <key>highlight</key>\n");
				fprintf(fr, "        <styleUrl>#multiTrack_h</styleUrl>\n");
				fprintf(fr, "      </Pair>\n");
				fprintf(fr, "    </StyleMap>\n");

				fprintf(fr, "    <Schema id=\"schema\">\n");
				fprintf(fr, "      <gx:SimpleArrayField name=\"roll\" type=\"float\">\n");
				fprintf(fr, "        <displayName>Roll</displayName>\n");
				fprintf(fr, "      </gx:SimpleArrayField>\n");
				fprintf(fr, "      <gx:SimpleArrayField name=\"pitch\" type=\"float\">\n");
				fprintf(fr, "        <displayName>Pitch</displayName>\n");
				fprintf(fr, "      </gx:SimpleArrayField>\n");
				fprintf(fr, "      <gx:SimpleArrayField name=\"yaw\" type=\"float\">\n");
				fprintf(fr, "        <displayName>Yaw</displayName>\n");
				fprintf(fr, "      </gx:SimpleArrayField>\n");
				fprintf(fr, "      <gx:SimpleArrayField name=\"alt\" type=\"float\">\n");
				fprintf(fr, "        <displayName>Alt</displayName>\n");
				fprintf(fr, "      </gx:SimpleArrayField>\n");
				fprintf(fr, "      <gx:SimpleArrayField name=\"speed\" type=\"float\">\n");
				fprintf(fr, "        <displayName>Speed</displayName>\n");
				fprintf(fr, "      </gx:SimpleArrayField>\n");
				fprintf(fr, "      <gx:SimpleArrayField name=\"gpsfix\" type=\"int\">\n");
				fprintf(fr, "        <displayName>GPS-Fix</displayName>\n");
				fprintf(fr, "      </gx:SimpleArrayField>\n");
				fprintf(fr, "      <gx:SimpleArrayField name=\"numSat\" type=\"int\">\n");
				fprintf(fr, "        <displayName>Sats</displayName>\n");
				fprintf(fr, "      </gx:SimpleArrayField>\n");
				fprintf(fr, "    </Schema>\n");


				fprintf(fr, "    <Folder>\n");
				fprintf(fr, "      <name>Tracks</name>\n");
				fprintf(fr, "      <open>0</open>\n");
				fprintf(fr, "      <visibility>0</visibility>\n");
				fprintf(fr, "      <Placemark>\n");
				fprintf(fr, "        <name>2010-05-28T01:16:35.000Z</name>\n");
				fprintf(fr, "        <styleUrl>#multiTrack</styleUrl>\n");
				fprintf(fr, "        <gx:Track>\n");

				point_nr = 0;
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
						struct tm strukt;
#ifndef WINDOWS
						time_t liczba_sekund = (time_t)(lsec);
						localtime_r(&liczba_sekund, &strukt); 
#endif
						fprintf(fr, "<when>%02d-%02d-%dT%02d:%02d:%02dZ</when>\n", strukt.tm_year + 1900, strukt.tm_mon + 1, strukt.tm_mday, strukt.tm_hour, strukt.tm_min, strukt.tm_sec);
						point_nr++;
					}
				}

				point_nr = 0;
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
						fprintf(fr, "<gx:coord>%f, %f, %f</gx:coord>\n", p_long, p_lat, p_alt);
						point_nr++;
					}
				}


				fprintf(fr, "          <ExtendedData>\n");
				fprintf(fr, "            <SchemaData schemaUrl=\"#schema\">\n");

				fprintf(fr, "              <gx:SimpleArrayData name=\"pitch\">\n");
				point_nr = 0;
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
						fprintf(fr, "<gx:value>%f</gx:value>\n", pitch);
						point_nr++;
					}
				}
				fprintf(fr, "              </gx:SimpleArrayData>\n");

				fprintf(fr, "              <gx:SimpleArrayData name=\"roll\">\n");
				point_nr = 0;
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
						fprintf(fr, "<gx:value>%f</gx:value>\n", roll);
						point_nr++;
					}
				}
				fprintf(fr, "              </gx:SimpleArrayData>\n");

				fprintf(fr, "              <gx:SimpleArrayData name=\"yaw\">\n");
				point_nr = 0;
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
						fprintf(fr, "<gx:value>%f</gx:value>\n", yaw);
						point_nr++;
					}
				}
				fprintf(fr, "              </gx:SimpleArrayData>\n");


				fprintf(fr, "              <gx:SimpleArrayData name=\"alt\">\n");
				point_nr = 0;
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
						fprintf(fr, "<gx:value>%f</gx:value>\n", p_alt);
						point_nr++;
					}
				}
				fprintf(fr, "              </gx:SimpleArrayData>\n");


				fprintf(fr, "              <gx:SimpleArrayData name=\"speed\">\n");
				point_nr = 0;
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
						fprintf(fr, "<gx:value>%f</gx:value>\n", speed);
						point_nr++;
					}
				}
				fprintf(fr, "              </gx:SimpleArrayData>\n");


				fprintf(fr, "              <gx:SimpleArrayData name=\"gpsfix\">\n");
				point_nr = 0;
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
						fprintf(fr, "<gx:value>%i</gx:value>\n", gpsfix);
						point_nr++;
					}
				}
				fprintf(fr, "              </gx:SimpleArrayData>\n");

				fprintf(fr, "              <gx:SimpleArrayData name=\"numSat\">\n");
				point_nr = 0;
				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {
						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);
						fprintf(fr, "<gx:value>%i</gx:value>\n", numSat);
						point_nr++;
					}
				}
				fprintf(fr, "              </gx:SimpleArrayData>\n");

				fprintf(fr, "            </SchemaData>\n");
				fprintf(fr, "          </ExtendedData>\n");

				fprintf(fr, "        </gx:Track>\n");
				fprintf(fr, "      </Placemark>\n");
				fprintf(fr, "    </Folder>\n");
}
if (type & (1<<3)) {

				fprintf(fr, "   <Folder>\n");
				fprintf(fr, "    <name>Tour</name>\n");
				fprintf(fr, "    <open>0</open>\n");
				fprintf(fr, "    <visibility>0</visibility>\n");

				fprintf(fr, "    <gx:Tour>\n");
				fprintf(fr, "      <name>Play me!</name>\n");
				fprintf(fr, "      <gx:Playlist>\n");
				fprintf(fr, "        <gx:AnimatedUpdate>\n");
				fprintf(fr, "          <Update>\n");
				fprintf(fr, "            <targetHref></targetHref>\n");
				fprintf(fr, "            <Change>\n");
				fprintf(fr, "                <IconStyle targetId=\"iconstyle\">\n");
				fprintf(fr, "                  <scale>10.0</scale>\n");
				fprintf(fr, "                </IconStyle>\n");
				fprintf(fr, "            </Change>\n");
				fprintf(fr, "          </Update>\n");
				fprintf(fr, "        </gx:AnimatedUpdate>\n");
				fprintf(fr, "\n");

				last_p_long = 0.0;
//				last_yaw = 0.0;

				fseek(log_fr, 0, SEEK_SET);
				while (fgets(line, 500, log_fr) != NULL) {
					if (strncmp(line, "GPS;", 4) == 0) {

						sscanf(line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
					} else if (strncmp(line, "ATT;", 4) == 0) {
						sscanf(line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &pitch, &roll, &yaw);

/*
						if (last_yaw != 0.0 && last_p_long != 0.0) {
							fprintf(fr, "        <gx:FlyTo>\n");
							fprintf(fr, "          <gx:duration>%i.%03i</gx:duration>\n", lsec - last_lsec, lmicros - last_lmicros);
							fprintf(fr, "          <Camera>\n");
							fprintf(fr, "            <longitude>%f</longitude>\n", last_p_long);
							fprintf(fr, "            <latitude>%f</latitude>\n", last_p_lat);
							fprintf(fr, "            <altitude>%f</altitude>\n", last_p_alt);
							fprintf(fr, "            <heading>%f</heading>\n", last_yaw);
							fprintf(fr, "            <tilt>%f</tilt>\n", last_pitch + 90.0);
							fprintf(fr, "            <roll>%f</roll>\n", last_roll);
							fprintf(fr, "            <altitudeMode>absolute</altitudeMode>\n");
							fprintf(fr, "          </Camera>\n");
							fprintf(fr, "        </gx:FlyTo>\n");
						}
*/
						fprintf(fr, "        <gx:FlyTo>\n");
						fprintf(fr, "          <gx:duration>0.1</gx:duration>\n");
						fprintf(fr, "          <Camera>\n");
						fprintf(fr, "            <longitude>%f</longitude>\n", p_long);
						fprintf(fr, "            <latitude>%f</latitude>\n", p_lat);
						fprintf(fr, "            <altitude>%f</altitude>\n", p_alt);
						fprintf(fr, "            <heading>%f</heading>\n", yaw);
						fprintf(fr, "            <tilt>%f</tilt>\n", pitch + 90.0);
						fprintf(fr, "            <roll>%f</roll>\n", roll);
						fprintf(fr, "            <altitudeMode>absolute</altitudeMode>\n");
						fprintf(fr, "          </Camera>\n");
						fprintf(fr, "        </gx:FlyTo>\n");


//						last_p_long = p_long;
//						last_p_lat = p_lat;
//						last_p_alt = p_alt;
//						last_pitch = pitch;
//						last_roll = roll;
//						last_yaw = yaw;
//						last_lsec = lsec;
//						last_lmicros = lmicros;

					} else if (strncmp(line, "GPS,", 4) == 0) {
						float dn = 0.0;
						float dn2 = 0.0;
						float dn4 = 0.0;
						uint32_t dn3 = 0;
						float p_lat = 0.0;
						float p_long = 0.0;
						sscanf(line, "GPS,%i,%i,%i,%f,%f,%f,%f,%f,%f,%f", &gpsfix, &dn3, &numSat, &dn, &p_lat, &p_long, &dn2, &p_alt, &speed, &dn4);
					} else if (strncmp(line, "ATT,", 4) == 0) {
						sscanf(line, "ATT,%f,%f,%f", &pitch, &roll, &yaw);

						fprintf(fr, "        <gx:FlyTo>\n");
						fprintf(fr, "          <gx:duration>0.1</gx:duration>\n");
						fprintf(fr, "          <Camera>\n");
						fprintf(fr, "            <longitude>%f</longitude>\n", p_long);
						fprintf(fr, "            <latitude>%f</latitude>\n", p_lat);
						fprintf(fr, "            <altitude>%f</altitude>\n", p_alt);
						fprintf(fr, "            <heading>%f</heading>\n", yaw);
						fprintf(fr, "            <tilt>%f</tilt>\n", pitch + 90.0);
						fprintf(fr, "            <roll>%f</roll>\n", roll);
						fprintf(fr, "            <altitudeMode>absolute</altitudeMode>\n");
						fprintf(fr, "          </Camera>\n");
						fprintf(fr, "        </gx:FlyTo>\n");

					}
				}

				fprintf(fr, "        <gx:Wait>\n");
				fprintf(fr, "          <gx:duration>2.4</gx:duration>  <!-- waiting for the AnimatedUpdate to complete -->\n");
				fprintf(fr, "        </gx:Wait>\n");
				fprintf(fr, "\n");
				fprintf(fr, "      </gx:Playlist>\n");
				fprintf(fr, "    </gx:Tour>\n");
				fprintf(fr, "\n");
				fprintf(fr, "    </Folder>\n");
}

				fprintf(fr, "  </Document>\n");
				fprintf(fr, "</kml>\n");
			        fclose(fr);
			}
			fclose(log_fr);
		}
	}
}

uint8_t logplay_cmd_kml (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	logplay_export_kml(logplay_file, "/tmp/export.kml", 0);
	system("(googleearth /tmp/export.kml || google-earth /tmp/export.kml) &");
	return 0;
}

uint8_t logplay_cmd_pause (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	logplay_pause = 1 - logplay_pause;
	return 0;
}

uint8_t logplay_cmd_step (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	logplay_pause = 1;
	if (data < 0.0) {
		logplay_msec += (uint32_t)data;
		logplay_play = 2;
	} else {
		logplay_msec = logplay_fpos;
	}
	return 0;
}

uint8_t logplay_cmd_next (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	logplay_pause = 1;
	logplay_msec = logplay_fpos;
	return 0;
}

uint8_t logplay_cmd_play (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (logplay_file[0] != 0) {
		logplay_play = 1 - logplay_play;
		logplay_pause = 0;
		logplay_msec = 0;
		logplay_starttime = 0;
	} else {
		logplay_list = 1;
	}
	return 0;
}

uint8_t logplay_cmd_open (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	logplay_list = 1 - logplay_list;
	logplay_filelist = 0;
	logplay_play = 0;
	logplay_pause = 0;
	logplay_msec = 0;
	return 0;
}

uint8_t logplay_cmd_open_ok (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	SDL_Log("## open logfile: %s ##\n", name);
	strncpy(logplay_file, name, 1023);
	logplay_list = 0;
	logplay_filelist = 0;
	return 0;
}

uint8_t logplay_cmd_play_updown (char *name, float x, float y, int8_t button, float data, uint8_t action) {
	if (data < 0.0 && logplay_filelist == 0) {
		return 0;
	}
	logplay_filelist += (int)data;
	return 0;
}

void logplay_draw_control (ESContext *esContext, float x1, float y1) {
	float w = 1.2;
	float h = 0.2;
	float x = x1 - w / 2.0;
	float y = y1 - h / 2.0;
	float max = 7.0;
	char tmp_str[1024];

	draw_box_f3(esContext, x, y, 0.002, x + w, y + h, 0.002, 0, 0, 0, 127);
	draw_box_f3(esContext, x + 0.01, y + 0.01, 0.002, x + w - 0.01, y + h / 2 - 0.01, 0.002, 0, 0, 0, 127);
	draw_rect_f3(esContext, x, y, 0.002, x + w, y + h, 0.002, 255, 255, 255, 127);
	draw_image_button(esContext, "rew", setup.view_mode, TEXTURE_PLAYER_REW    , x + w / max * 1, y + h / 4 * 3, 0.003, h / 2, h / 2, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_step, -100.0);
	if (logplay_play == 1) {
		draw_image_button(esContext, "stop", setup.view_mode, TEXTURE_PLAYER_STOP  , x + w / max * 2, y + h / 4 * 3, 0.003, h / 2, h / 2, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_play, 0.0);
	} else {
		draw_image_button(esContext, "play", setup.view_mode, TEXTURE_PLAYER_PLAY  , x + w / max * 2, y + h / 4 * 3, 0.003, h / 2, h / 2, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_play, 0.0);
	}
	draw_image_button(esContext, "pause", setup.view_mode, TEXTURE_PLAYER_PAUSE, x + w / max * 3, y + h / 4 * 3, 0.003, h / 2, h / 2, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_pause, 0.0);
	draw_image_button(esContext, "ffw", setup.view_mode, TEXTURE_PLAYER_FFW    , x + w / max * 4, y + h / 4 * 3, 0.003, h / 2, h / 2, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_step, 100.0);
	draw_image_button(esContext, "open", setup.view_mode, TEXTURE_PLAYER_OPEN  , x + w / max * 5, y + h / 4 * 3, 0.003, h / 2, h / 2, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_open, 0.0);
	draw_image_button(esContext, "kml", setup.view_mode, TEXTURE_PLAYER_KML  , x + w / max * 6, y + h / 4 * 3, 0.003, h / 2, h / 2, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_kml, 0.0);

	struct tm strukt;
#ifndef WINDOWS
	time_t liczba_sekund = (time_t)(logplay_msec / 1000 + logplay_startsec);
	localtime_r(&liczba_sekund, &strukt); 
#endif

//	sprintf(tmp_str, "%02d.%02d.%d %02d:%02d:%02d.%03i", strukt.tm_mday, strukt.tm_mon + 1, strukt.tm_year + 1900, strukt.tm_hour, strukt.tm_min, strukt.tm_sec, logplay_msec % 1000);

tmp_str[0] = 0;

	draw_text_button(esContext, "timer", setup.view_mode, tmp_str, FONT_GREEN, x + w / 2, y + h / 4 * 1, 0.003, 0.06, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_play, 0.0);
	if (logplay_list == 1) {
		draw_box_f3(esContext, x, -0.8, 0.002, x + w, y, 0.002, 0, 0, 0, 200);
		char directory[1024];
#ifndef WINDOWS
		DIR *dir = NULL;
		struct dirent *dir_entry = NULL;
		struct stat statbuf;
		char new_path[1024];
		int n = 0;
		int n2 = 0;
#endif
		draw_text_button(esContext, "up", setup.view_mode, "[^]", FONT_GREEN, x + w - 0.1, -0.8 + 0.05, 0.001, 0.06, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_play_updown, -1.0);
		draw_text_button(esContext, "down", setup.view_mode, "[v]", FONT_GREEN, x + w - 0.1, y - 0.05, 0.001, 0.06, ALIGN_CENTER, ALIGN_CENTER, logplay_cmd_play_updown, 1.0);
		sprintf(directory, "%s/logs", get_datadirectory());


#ifndef WINDOWS
		if ((dir = opendir(directory)) != NULL) {
			while ((dir_entry = readdir(dir)) != 0) {
				if (dir_entry->d_name[1] != '.') {
					sprintf(new_path, "%s/%s", directory, dir_entry->d_name);
					if (lstat(new_path, &statbuf) == 0) {
						if (statbuf.st_mode&S_IFDIR) {
						} else {
							if (logplay_filelist == n2) {
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
								draw_text_button(esContext, new_path, setup.view_mode, tmp_str, FONT_WHITE, x + 0.05, -0.8 + n * 0.1 + 0.15, 0.002, 0.06, 0, 0, logplay_cmd_open_ok, 0.0);
							}
							n++;
						}
					}
				}
				if (n > 10) {
					n2++;
					n = 0;
				}
			}
			closedir(dir);
			dir = NULL;
		}
#endif
	}
}

void LogSave (void) {
	char file[1024];
	sprintf(file, "%s/logs/%i.log", get_datadirectory(), log_startup_time);
	if (Logdata != NULL) {
		SDL_Log("logging: save to file: %s\n", file);
		if (strlen(Logdata) > 200) {
		        FILE *fr;
		        fr = fopen(file, "wb");
			if (fr != 0) {
				fprintf(fr, "%s", Logdata);
			        fclose(fr);
			}
		}
		free(Logdata);
		Logdata = NULL;
	} else {
		SDL_Log("logging: nothing to save\n");
	}
}

void LogInit (void) {
	log_startup_time = time(0);
	if (Logdata != NULL) {
		free(Logdata);
		Logdata = NULL;
	}
	if (Logdata == NULL) {
		Logdata = malloc(1);
		Logdata[0] = 0;
	}
}

void LogAppend (char *line) {
	if (Logdata == NULL) {
		LogInit();
	}
	if (Logdata != NULL) {
		SDL_Log("logging: %s\n", line);
		Logdata = realloc(Logdata, (int)(strlen(Logdata) + strlen(line) + 2));
		strcat(Logdata, line);
		strcat(Logdata, "\n");
	}
}

void Logging (void) {
	if (logplay == 1) {
		char line[1025];
		static char last_line[1025];
		if (logplay_play == 2 && logplay_open == 1) {
			logplay_play = 1;
			logplay_open = 0;
			fclose(fr_play);
			fr_play = NULL;
		}
		if (logplay_play == 0 && logplay_open == 1) {
			logplay_open = 0;
			fclose(fr_play);
			fr_play = NULL;
		}
		if (logplay_play == 1) {
			if (logplay_open == 0 && logplay_file[0] != 0) {
				logplay_open = 1;
				logplay_startsec = 0;
				if ((fr_play = fopen(logplay_file, "r")) == NULL) {
					SDL_Log("logplay: error loading file: %s\n", logplay_file);
				}
				if (fgets(line, 500, fr_play) != 0) {
					strncpy(last_line, line, 1023);
				} else {
					logplay_open = 0;
					logplay_play = 0;
					fclose(fr_play);
					fr_play = NULL;
				}
			}
			static uint32_t lsec = 0;
			static uint32_t lmicros = 0;
			if (fr_play != NULL) {
				while (1 == 1) {
					if (last_line[3] == ';') {
						sscanf(last_line + 4, "%i.%i;", &lsec, &lmicros);
						if (logplay_startsec == 0) {
							logplay_startsec = lsec;
						}
					} else if (last_line[3] == ',') {
						if (logplay_startsec == 0) {
							logplay_startsec = lsec;
						}
					} else {
						if (fgets(line, 500, fr_play) != 0) {
							strncpy(last_line, line, 1023);
//							SDL_Log("NEXT_LINE: %s\n", line);
							if (strncmp(last_line, "GPS,", 4) == 0) {
								lmicros += 200;
								if (lmicros >= 1000) {
									lsec += 1;
									lmicros = 0;
								}
							}
							continue;
						} else {
							SDL_Log("######## file end ########\n");
							logplay_open = 0;
							logplay_play = 0;
							fclose(fr_play);
							fr_play = NULL;
							break;
						}
					}
					logplay_fpos = (lsec - logplay_startsec) * 1000 + lmicros;
//					SDL_Log("%i %i\n", logplay_msec, logplay_fpos);
					if (logplay_msec >= logplay_fpos) {
						if (strncmp(last_line, "GPS;", 4) == 0) {
							float p_lat = 0.0;
							float p_long = 0.0;
							float p_alt = 0.0;
							sscanf(last_line, "GPS;%i.%i;%f;%f;%f", &lsec, &lmicros, &p_lat, &p_long, &p_alt);
							if (p_lat != 0.0 && p_long != 0.0) {
								ModelData[ModelActive].p_lat = p_lat;
								ModelData[ModelActive].p_long = p_long;
								ModelData[ModelActive].p_alt = p_alt;
							}
						} else if (strncmp(last_line, "ATT;", 4) == 0) {
							sscanf(last_line, "ATT;%i.%i;%f;%f;%f", &lsec, &lmicros, &ModelData[ModelActive].pitch, &ModelData[ModelActive].roll, &ModelData[ModelActive].yaw);
						} else if (strncmp(last_line, "GPS,", 4) == 0) {
							float dn = 0.0;
							float dn2 = 0.0;
							float dn4 = 0.0;
							uint32_t dn3 = 0;
							float p_lat = 0.0;
							float p_long = 0.0;
							int gpsfix = 0;
							int numSat = 0;
							sscanf(last_line, "GPS,%i,%i,%i,%f,%f,%f,%f,%f,%f,%f", &gpsfix, &dn3, &numSat, &dn, &p_lat, &p_long, &dn2, &ModelData[ModelActive].p_alt, &ModelData[ModelActive].speed, &dn4);
							ModelData[ModelActive].gpsfix = gpsfix;
							ModelData[ModelActive].numSat = numSat;
							if (p_lat != 0.0 && p_long != 0.0) {
								ModelData[ModelActive].p_lat = p_lat;
								ModelData[ModelActive].p_long = p_long;
							}
						} else if (strncmp(last_line, "ATT,", 4) == 0) {
							sscanf(last_line, "ATT,%f,%f,%f", &ModelData[ModelActive].pitch, &ModelData[ModelActive].roll, &ModelData[ModelActive].yaw);
						}
						if (fgets(line, 500, fr_play) != NULL) {
							strncpy(last_line, line, 1023);
//							SDL_Log("NEXT_LINE: %s\n", line);
							if (strncmp(last_line, "GPS,", 4) == 0) {
								lmicros += 200;
								if (lmicros >= 1000) {
									lsec += 1;
									lmicros = 0;
								}
//								SDL_Log("%i %i\n", logplay_msec, logplay_fpos);
							}
							continue;
						} else {
							SDL_Log("######## file end ########\n");
							logplay_open = 0;
							logplay_play = 0;
							fclose(fr_play);
							fr_play = NULL;
							break;
						}
					} else {
						break;
					}
				}
			}
			if (logplay_pause == 0) {
				if (logplay_starttime == 0) {
					logplay_starttime = SDL_GetTicks();
				}
				logplay_msec = SDL_GetTicks() - logplay_starttime;
			}
		}
	} else if (logmode == 1) {
		char line[1024];
		static float last_lat = 0.0;
		static float last_lon = 0.0;
		static float last_alt = 0.0;
		static int8_t last_sats = 0;
		static float last_pitch = 0.0;
		static float last_roll = 0.0;
		static float last_yaw = 0.0;
		static int16_t last_radio[8];
		static float last_ampere = 0.0;
		static float last_voltage = 0.0;
		static uint8_t last_mode = 0;
		static uint8_t last_armed = 0;
		static uint8_t last_status = 0;
		static uint8_t last_dronetype = 0;
		static uint8_t last_teletype = 0;
		static uint8_t last_heartbeat = 0;
		uint8_t n= 0;
		uint8_t logflag = 0;
		struct timeval tv;
		uint32_t sec = 0;
		uint32_t micros = 0;
		if (logrec_starttime == 0) {
			gettimeofday(&tv, NULL);  
			logrec_starttime = SDL_GetTicks();
			logrec_startsec = tv.tv_sec;
		}
		sec = logrec_startsec + (SDL_GetTicks() - logrec_starttime) / 1000;
		micros = (SDL_GetTicks() - logrec_starttime) % 1000;
		if (last_lat != ModelData[ModelActive].p_lat || last_lon != ModelData[ModelActive].p_long || (int)last_alt != (int)ModelData[ModelActive].p_alt || last_sats != ModelData[ModelActive].numSat) {
			sprintf(line, "GPS;%i.%03i;%f;%f;%f;%f;%i;%i", sec, micros, ModelData[ModelActive].p_lat, ModelData[ModelActive].p_long, ModelData[ModelActive].p_alt - ModelData[ModelActive].alt_offset, ModelData[ModelActive].speed, ModelData[ModelActive].gpsfix, ModelData[ModelActive].numSat);
			LogAppend(line);
			last_lat = ModelData[ModelActive].p_lat;
			last_lon = ModelData[ModelActive].p_long;
			last_alt = ModelData[ModelActive].p_alt;
			last_sats = ModelData[ModelActive].numSat;
		}
		if ((int)last_pitch != (int)ModelData[ModelActive].pitch || (int)last_roll != (int)ModelData[ModelActive].roll || (int)last_yaw != (int)ModelData[ModelActive].yaw) {
			sprintf(line, "ATT;%i.%03i;%f;%f;%f", sec, micros, ModelData[ModelActive].pitch, ModelData[ModelActive].roll, ModelData[ModelActive].yaw);
			LogAppend(line);
			last_pitch = ModelData[ModelActive].pitch;
			last_roll = ModelData[ModelActive].roll;
			last_yaw = ModelData[ModelActive].yaw;
		}
		logflag = 0;
		for (n = 0; n < 8; n++) {
			if (last_radio[n] != ModelData[ModelActive].radio[n]) {
				logflag = 1;
				last_radio[n] = ModelData[ModelActive].radio[n];
			}
		}
		if (logflag == 1) {
			logflag = 0;
			sprintf(line, "RC0;%i.%03i;%i;%i;%i;%i;%i;%i;%i;%i", sec, micros, ModelData[ModelActive].radio[0], ModelData[ModelActive].radio[1], ModelData[ModelActive].radio[2], ModelData[ModelActive].radio[3], ModelData[ModelActive].radio[4], ModelData[ModelActive].radio[5], ModelData[ModelActive].radio[6], ModelData[ModelActive].radio[7]);
			LogAppend(line);
		}
		if (last_voltage != ModelData[ModelActive].voltage || last_voltage != ModelData[ModelActive].voltage || last_ampere != ModelData[ModelActive].ampere) {
			sprintf(line, "AV0;%i.%03i;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f", sec, micros, ModelData[ModelActive].ampere, ModelData[ModelActive].voltage, ModelData[ModelActive].voltage_zell[0], ModelData[ModelActive].voltage_zell[1], ModelData[ModelActive].voltage_zell[2], ModelData[ModelActive].voltage_zell[3], ModelData[ModelActive].voltage_zell[4], ModelData[ModelActive].voltage_zell[5], ModelData[ModelActive].temperature[0], ModelData[ModelActive].temperature[1]);
			LogAppend(line);
			last_ampere = ModelData[ModelActive].ampere;
			last_voltage = ModelData[ModelActive].voltage;
		}
		if (last_mode != ModelData[ModelActive].mode || last_armed != ModelData[ModelActive].armed || last_status != ModelData[ModelActive].status) {
			sprintf(line, "AM0;%i.%03i;%i;%i;%i", sec, micros, ModelData[ModelActive].mode, ModelData[ModelActive].armed, ModelData[ModelActive].status);
			LogAppend(line);
			last_mode = ModelData[ModelActive].mode;
			last_armed = ModelData[ModelActive].armed;
			last_status = ModelData[ModelActive].status;
		}
		if (last_dronetype != ModelData[ModelActive].dronetype || last_teletype != ModelData[ModelActive].teletype) {
			sprintf(line, "MT0;%i.%03i;%i;%i", sec, micros, ModelData[ModelActive].dronetype, ModelData[ModelActive].teletype);
			LogAppend(line);
			last_dronetype = ModelData[ModelActive].dronetype;
			last_teletype = ModelData[ModelActive].teletype;
		}
		if (last_heartbeat == 0 && ModelData[ModelActive].heartbeat > 0) {
			sprintf(line, "HB0;%i.%03i;%i", sec, micros, ModelData[ModelActive].heartbeat);
			LogAppend(line);
			last_heartbeat = 1;
		} if (last_heartbeat != 0 && ModelData[ModelActive].heartbeat == 0) {
			sprintf(line, "HB0;%i.%03i;0", sec, micros);
			LogAppend(line);
			last_heartbeat = 0;
		}
	}
}
