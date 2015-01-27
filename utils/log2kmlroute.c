/*

Copyright 2014 by Oliver Dippel <o dot dippel AT gmx dot de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define HEAD_BYTE1  0xA3
#define HEAD_BYTE2  0x95
#define LOG_FORMAT_MSG	  128

typedef struct {
    uint8_t type;
    uint8_t length;
    char name[4];
    char format[16];
    char labels[64];
} log_Format;

int main (int argc, char *argv[]) {
	FILE *fd = NULL;
	uint8_t c = 0;
	uint8_t header[2];
	uint8_t fn = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t valn = 0;
	uint8_t absolute = 0;
	char vNames[255][16][16];
	log_Format Formats[255];
	if (argc < 2 || argc > 3 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "USAGE: \n");
		fprintf(stderr, "	%s [-a] LOGFILE\n", argv[0]);
		fprintf(stderr, "\n");
		fprintf(stderr, "	  -a      : Relative Alt\n", argv[0]);
		fprintf(stderr, "	  LOGFILE : Logfile (Binary-Flash-Format)\n", argv[0]);
		fprintf(stderr, "\n");
		exit(1);
	}
	if (strcmp(argv[1], "-a") == 0) {
		absolute = 1;
		n++;
	}
	fd = fopen(argv[n + 1], "rb");
	if (fd == NULL) {
		fprintf(stderr, "failed open logfile: %s\n", argv[n + 1]);
		exit(1);
	}
	printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	printf("<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
	printf("  <Document>\n");
	printf("    <name>Mission</name>\n");
	printf("    <description>File: %s</description>\n", argv[n + 1]);
	printf("    <Style id=\"yellowLineGreenPoly\">\n");
	printf("      <LineStyle>\n");
	printf("        <color>7f00ffff</color>\n");
	printf("        <width>4</width>\n");
	printf("      </LineStyle>\n");
	printf("      <PolyStyle>\n");
	printf("        <color>7f00ff00</color>\n");
	printf("      </PolyStyle>\n");
	printf("    </Style>\n");
	printf("    <Placemark>\n");
	printf("      <name>Route</name>\n");
	printf("      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
	printf("      <LineString>\n");
	printf("        <extrude>1</extrude>\n");
	printf("        <tessellate>1</tessellate>\n");
	if (absolute == 1) {
		printf("        <altitudeMode>absolute</altitudeMode>\n");
	} else {
		printf("        <altitudeMode>relativeToGround</altitudeMode>\n");
	}
	printf("        <coordinates>\n");

	while (fread(header, 2, 1, fd) > 0) {
		if (header[0] == HEAD_BYTE1 && header[1] == HEAD_BYTE2) {
			fread(&c, 1, 1, fd);
			switch (c) {
				case LOG_FORMAT_MSG: {
					log_Format logFormat;
					fread(&logFormat, sizeof(log_Format), 1, fd);
					memcpy(&Formats[fn], &logFormat, sizeof(log_Format));
					valn = 0;
					n2 = 0;
					for (n = 0; n < 64 && logFormat.labels[n] != 0; n++) {
						if (logFormat.labels[n] == ',') {
							valn++;
							n2 = 0;
						} else {
							vNames[fn][valn][n2] = logFormat.labels[n];
							n2++;
							vNames[fn][valn][n2] = 0;
						}
					}
					if (n2 > 0) {
						valn++;
					}
					fn++;
					break;
				}
				default: {
					uint8_t buf[1024];
					for (n = 0; n < fn; n++) {
						if (c == Formats[n].type) {
							uint8_t stat = 0;
							float lat = 0.0;
							float lon = 0.0;
							float alt_rel = 0.0;
							float alt = 0.0;
							//fprintf(stderr, "%0.4s\n", Formats[n].name);
							for (valn = 0; valn < 16 && Formats[n].format[valn] != 0; valn++) {
								//fprintf(stderr, "	%s	", vNames[n][valn]);
								if (strcmp(Formats[n].name, "GPS") == 0) {
									if (strcmp(vNames[n][valn], "Status") == 0) {
											uint8_t val;
											fread(&val, sizeof(val), 1, fd);
											stat = val;
											continue;
									} else if (strcmp(vNames[n][valn], "Lat") == 0) {
											int32_t val;
											fread(&val, sizeof(val), 1, fd);
											lat = (float)val / 10000000.0;
											//fprintf(stderr, "	%f\n", (float)val / 10000000.0);
											continue;
									} else if (strcmp(vNames[n][valn], "Lng") == 0) {
											int32_t val;
											fread(&val, sizeof(val), 1, fd);
											lon = (float)val / 10000000.0;
											//fprintf(stderr, "	%f\n", (float)val / 10000000.0);
											continue;
									} else if (strcmp(vNames[n][valn], "RelAlt") == 0) {
											int32_t val;
											fread(&val, sizeof(val), 1, fd);
											alt_rel = (float)val / 100.0;
											//fprintf(stderr, "	%f\n", (float)val / 100.0);
											continue;
									} else if (strcmp(vNames[n][valn], "Alt") == 0) {
											int32_t val;
											fread(&val, sizeof(val), 1, fd);
											alt = (float)val / 100.0;
											//fprintf(stderr, "	%f\n", (float)val / 100.0);
											continue;
									}
								}
								switch (Formats[n].format[valn]) {
									case 'b': {
										int8_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%i\n", val);
										break;
									}
									case 'B': {
										uint8_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%i\n", val);
										break;
									}
									case 'h': {
										int16_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%i\n", val);
										break;
									}
									case 'H': {
										uint16_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%i\n", val);
										break;
									}
									case 'i': {
										int32_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%i\n", val);
										break;
									}
									case 'I': {
										uint32_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%i\n", val);
										break;
									}
									case 'f': {
										float val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%f\n", val);
										break;
									}
									case 'n': {
										char val[4];
										fread(val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%0.4s\n", val);
										break;
									}
									case 'N': {
										char val[16];
										fread(val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%0.16s\n", val);
										break;
									}
									case 'Z': {
										char val[64];
										fread(val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%0.64s\n", val);
										break;
									}
									case 'c': {
										int16_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%f\n", (float)val / 100.0);
										break;
									}
									case 'C': {
										uint16_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%f\n", (float)val / 100.0);
										break;
									}
									case 'e': {
										int32_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%f\n", (float)val / 100.0);
										break;
									}
									case 'E': {
										uint32_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%f\n", (float)val / 100.0);
										break;
									}
									case 'L': {
										int32_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%f\n", (float)val / 10000000.0);
										break;
									}
									case 'M': {
										uint8_t val;
										fread(&val, sizeof(val), 1, fd);
										//fprintf(stderr, "	%i\n", val);
										break;
									}
								}
							}
							if (strcmp(Formats[n].name, "GPS") == 0 && stat == 3 && lon != 0.0 && lat != 0.0) {
								printf("          %f,%f,%f\n", lon, lat, alt_rel);
							}
						}
					}
					break;
				}
			}
		}
	}

	printf("        </coordinates>\n");
	printf("      </LineString>\n");
	printf("    </Placemark>\n");
	printf("  </Document>\n");
	printf("</kml>\n");

	fclose(fd);


}
