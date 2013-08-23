
#ifndef MODEL_H
#define MODEL_H

enum {
	TELETYPE_MULTIWII_21,
	TELETYPE_AUTOQUAD,
	TELETYPE_ARDUPILOT,
	TELETYPE_MEGAPIRATE_NG,
	TELETYPE_OPENPILOT,
	TELETYPE_GPS_NMEA,
	TELETYPE_FRSKY,
	TELETYPE_BASEFLIGHT,
	TELETYPE_BASEFLIGHTCLI,
	TELETYPE_HARAKIRIML,
	TELETYPE_CLI,
	TELETYPE_SIMPLEBGC,
	TELETYPE_BRUGI,
	TELETYPE_LAST,
};

enum {
	MODELTYPE_MULTICOPTER,
	MODELTYPE_HELICOPTER,
	MODELTYPE_PLANE,
	MODELTYPE_CAR,
	MODELTYPE_BOAT,
	MODELTYPE_LAST,
};

enum {
	MODEL_MODE_MANUAL,
	MODEL_MODE_POSHOLD,
	MODEL_MODE_MISSION,
	MODEL_MODE_RTL,
};

enum {
	MODEL_DISARMED,
	MODEL_ARMED,
	MODEL_ARMING,
};

typedef struct {
	char name[200];
	char image[200];
	uint8_t modeltype;
	uint8_t teletype;
	char teledevice[20];
	uint32_t telebaud;
	char telebtaddr[20];
	char telebtpin[20];
	uint8_t mode;
	uint8_t status;
	uint8_t armed;
	uint8_t heartbeat;
	uint8_t heartbeat_rc;
	uint8_t found_rc;
	float p_lat;
	float p_long;
	float p_alt;
	float alt_offset;
	float baro;
	float pitch;
	float roll;
	float yaw;
	float speed;
	float voltage;
	float load;
	int8_t gpsfix;
	int8_t numSat;
	int16_t radio[16];
	float acc_x;
	float acc_y;
	float acc_z;
	float gyro_x;
	float gyro_y;
	float gyro_z;
	uint8_t rssi_rx;
	uint8_t rssi_tx;
	float voltage_rx;
	float voltage_zell[6];
	int16_t temperature[2];
	float ampere;
	uint8_t sysid;
	uint8_t compid;
} Model;

extern Model ModelData;
extern char teletypes[16][16];
extern char modeltypes[5][15];

#endif
