
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define HEAD_BYTE1  0xA3    // Decimal 163
#define HEAD_BYTE2  0x95    // Decimal 149

typedef struct {
	uint8_t type;
	uint8_t length;
	char name[4];
	char format[16];
	char labels[64];
} log_Format;

typedef struct {
	char name[16];
	float value;
} log_Parameter;

typedef struct {
	uint8_t  status;
	uint32_t gps_week_ms;
	uint16_t gps_week;
	uint8_t  num_sats;
	int16_t  hdop;
	int32_t  latitude;
	int32_t  longitude;
	int32_t  rel_altitude;
	int32_t  altitude;
	uint32_t ground_speed;
	int32_t  ground_course;
	float    vel_z;
	uint32_t apm_time;
} log_GPS;

typedef struct {
	char msg[64];
} log_Message;

typedef struct {
	uint32_t timestamp;
	float gyro_x, gyro_y, gyro_z;
	float accel_x, accel_y, accel_z;
} log_IMU;

typedef struct {
	uint32_t timestamp;
	uint16_t chan1;
	uint16_t chan2;
	uint16_t chan3;
	uint16_t chan4;
	uint16_t chan5;
	uint16_t chan6;
	uint16_t chan7;
	uint16_t chan8;
} log_RCIN;

typedef struct {
	uint32_t timestamp;
	uint16_t chan1;
	uint16_t chan2;
	uint16_t chan3;
	uint16_t chan4;
	uint16_t chan5;
	uint16_t chan6;
	uint16_t chan7;
	uint16_t chan8;
} log_RCOUT;

typedef struct {
	uint32_t timestamp;
	float   altitude;
	float   pressure;
	int16_t temperature;
} log_BARO;


#define LOG_FORMAT_MSG	  128
#define LOG_PARAMETER_MSG 129
#define LOG_GPS_MSG		  130
#define LOG_IMU_MSG		  131
#define LOG_MESSAGE_MSG	  132
#define LOG_RCIN_MSG      133
#define LOG_RCOUT_MSG     134
#define LOG_IMU2_MSG	  135
#define LOG_BARO_MSG	  136



int main(int argc, char *argv[]) {
	FILE *fd = NULL;
	uint8_t c = 0;
	uint8_t header[2];
	uint8_t fn = 0;
	uint8_t n = 0;
	uint8_t n2 = 0;
	uint8_t valn = 0;
	char vNames[255][16][16];
	log_Format Formats[255];
	printf("%s\n", argv[1]);
	fd = fopen(argv[1], "rb");
	while (fread(header, 2, 1, fd) > 0) {
		if (header[0] == HEAD_BYTE1 && header[1] == HEAD_BYTE2) {
			printf("#HEAD#\n");
			fread(&c, 1, 1, fd);
			printf("TYPE: 0x%02X (%i)\n", c, c);
			switch (c) {
				case LOG_FORMAT_MSG: {
						log_Format logFormat;
						fread(&logFormat, sizeof(log_Format), 1, fd);
						printf("  0x%X, %i\n", logFormat.type, logFormat.length);
						printf("	%0.4s\n", logFormat.name);
						printf("	%0.16s\n", logFormat.format);
						printf("	%0.64s\n", logFormat.labels);
						memcpy(&Formats[fn], &logFormat, sizeof(log_Format));
						valn = 0;
						n2 = 0;
						for (n = 0; n < 64 && logFormat.labels[n] != 0; n++) {
							if (logFormat.labels[n] == ',') {
								printf("#%s\n", vNames[fn][valn]);
								valn++;
								n2 = 0;
							} else {
								vNames[fn][valn][n2] = logFormat.labels[n];
								n2++;
								vNames[fn][valn][n2] = 0;
							}
						}
						if (n2 > 0) {
							printf("#%s\n", vNames[fn][valn]);
							valn++;
						}
						fn++;
						break;
					}
				/*
								case LOG_RCIN_MSG: {
									log_RCIN logRCIN;
									fread(&logRCIN, sizeof(log_RCIN), 1, fd);
									printf("  logRCIN %i\n", logRCIN.timestamp);
									printf("	1 %i\n", logRCIN.chan1);
									printf("	2 %i\n", logRCIN.chan2);
									printf("	3 %i\n", logRCIN.chan3);
									printf("	4 %i\n", logRCIN.chan4);
									printf("	5 %i\n", logRCIN.chan5);
									printf("	6 %i\n", logRCIN.chan6);
									printf("	7 %i\n", logRCIN.chan7);
									printf("	8 %i\n", logRCIN.chan8);
									break;
								}
								case LOG_RCOUT_MSG: {
									log_RCOUT logRCOUT;
									fread(&logRCOUT, sizeof(log_RCOUT), 1, fd);
									printf("  logRCOUT %i\n", logRCOUT.timestamp);
									printf("	1 %i\n", logRCOUT.chan1);
									printf("	2 %i\n", logRCOUT.chan2);
									printf("	3 %i\n", logRCOUT.chan3);
									printf("	4 %i\n", logRCOUT.chan4);
									printf("	5 %i\n", logRCOUT.chan5);
									printf("	6 %i\n", logRCOUT.chan6);
									printf("	7 %i\n", logRCOUT.chan7);
									printf("	8 %i\n", logRCOUT.chan8);
									break;
								}
								case LOG_GPS_MSG: {
									log_GPS logGPS;
									fread(&logGPS, sizeof(log_GPS), 1, fd);
									printf("  logGPS %i\n", logGPS.status);
									printf("	week_ms  %i\n", logGPS.gps_week_ms);
									printf("	week     %i\n", logGPS.gps_week);
									printf("	num_sats %i\n", logGPS.num_sats);
									printf("	hdop     %i\n", logGPS.hdop);
									printf("	lat      %i\n", logGPS.latitude);
									printf("	long     %i\n", logGPS.longitude);
									printf("	rel_alt  %i\n", logGPS.rel_altitude);
									printf("	alt      %i\n", logGPS.altitude);
									printf("	speed    %i\n", logGPS.ground_speed);
									printf("	course   %i\n", logGPS.ground_course);
									printf("	vel_z    %f\n", logGPS.vel_z);
									printf("	apm_time %i\n", logGPS.apm_time);
									break;
								}
								case LOG_MESSAGE_MSG: {
									log_Message logMessage;
									fread(&logMessage, sizeof(log_Message), 1, fd);
									printf("  logMessage %s\n", logMessage.msg);
									break;
								}
								case LOG_IMU_MSG:
								case LOG_IMU2_MSG: {
									log_IMU logIMU;
									fread(&logIMU, sizeof(log_IMU), 1, fd);
									printf("  logIMU %i\n", logIMU.timestamp);
									printf("  gx %f\n", logIMU.gyro_x);
									printf("  gy %f\n", logIMU.gyro_y);
									printf("  gz %f\n", logIMU.gyro_z);
									printf("  ax %f\n", logIMU.accel_x);
									printf("  ay %f\n", logIMU.accel_y);
									printf("  az %f\n", logIMU.accel_z);
									break;
								}
								case LOG_BARO_MSG: {
									log_BARO logBARO;
									fread(&logBARO, sizeof(log_BARO), 1, fd);
									printf("  alt   %f\n", logBARO.altitude);
									printf("  press %f\n", logBARO.pressure);
									printf("  temp  %i\n", logBARO.temperature);
									break;
								}
								case LOG_PARAMETER_MSG: {
									log_Parameter logParameter;
									fread(&logParameter, sizeof(log_Parameter), 1, fd);
									printf("  logParameter %s\n", logParameter.name);
									printf("  value %f\n", logParameter.value);
									break;
								}
				*/
				default: {
						uint8_t buf[1024];
						for (n = 0; n < fn; n++) {
							if (c == Formats[n].type) {
								printf("DYN_FORMAT: %i\n", c);
								printf("DYN_FORMAT: %0.4s\n", Formats[n].name);
								printf("	%0.16s\n", Formats[n].format);
								printf("	%0.64s\n", Formats[n].labels);
								for (valn = 0; valn < 16 && Formats[n].format[valn] != 0; valn++) {
									printf("	%s	", vNames[n][valn]);
									switch (Formats[n].format[valn]) {
										case 'b': {
												int8_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val);
												break;
											}
										case 'B': {
												uint8_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val);
												break;
											}
										case 'h': {
												int16_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val);
												break;
											}
										case 'H': {
												uint16_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val);
												break;
											}
										case 'i': {
												int32_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val);
												break;
											}
										case 'I': {
												uint32_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val);
												break;
											}
										case 'f': {
												float val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%f\n", val);
												break;
											}
										case 'n': {
												char val[4];
												fread(val, sizeof(val), 1, fd);
												printf("	%0.4s\n", val);
												break;
											}
										case 'N': {
												char val[16];
												fread(val, sizeof(val), 1, fd);
												printf("	%0.16s\n", val);
												break;
											}
										case 'Z': {
												char val[64];
												fread(val, sizeof(val), 1, fd);
												printf("	%0.64s\n", val);
												break;
											}
										case 'c': {
												int16_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val * 100);
												break;
											}
										case 'C': {
												uint16_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val * 100);
												break;
											}
										case 'e': {
												int32_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val * 100);
												break;
											}
										case 'E': {
												uint32_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val * 100);
												break;
											}
										case 'L': {
												int32_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val);
												break;
											}
										case 'M': {
												uint8_t val;
												fread(&val, sizeof(val), 1, fd);
												printf("	%i\n", val);
												break;
											}
									}
								}
							}
						}
						break;
					}
			}
		} else {
			//			printf("b1: 0x%02X (%i)\n", header[0], header[0]);
			//			printf("b2: 0x%02X (%i)\n", header[1], header[1]);
		}
	}
	fclose(fd);
}
