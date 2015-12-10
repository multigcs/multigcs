
#ifndef MODEL_H
#define MODEL_H

#define MODELS_MAX 9

enum {
	TELETYPE_MULTIWII_21,
	TELETYPE_AUTOQUAD,
	TELETYPE_ARDUPILOT,
	TELETYPE_MEGAPIRATE_NG,
	TELETYPE_OPENPILOT,
	TELETYPE_GPS_NMEA,
	TELETYPE_FRSKY,
	TELETYPE_BASEFLIGHT,
	TELETYPE_HARAKIRIML,
	TELETYPE_LAST,
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
	float vin;
	float amps;
	uint16_t rpm;
	uint16_t age;
	uint8_t id;
	uint8_t stat;
	uint8_t err;
} EscStat;

typedef struct {
	char name[200];
	char sysstr[200];
	char image[512];
	uint8_t teletype;
	uint8_t dronetype;
	uint8_t pilottype;
	char telebtaddr[200];
	char telebtpin[200];
	uint8_t mode;
	uint8_t status;
	uint8_t armed;
	uint8_t heartbeat;
	uint8_t heartbeat_rc;
	uint8_t found_rc;
	float p_lat;
	float p_long;
	float p_alt;
	float next_lat;
	float next_long;
	float next_alt;
	uint16_t next_count;
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
	float hdop;
	float vdop;
	int16_t radio[16];
	int16_t radio_raw[8];
	float acc_x;
	float acc_y;
	float acc_z;
	float gyro_x;
	float gyro_y;
	float gyro_z;
	float mag_x;
	float mag_y;
	float mag_z;
	float mag2_x;
	float mag2_y;
	float mag2_z;
	float press_abs;
	float press_diff;
	float mnt_pitch;
	float mnt_roll;
	float mnt_yaw;
	uint8_t rssi_rx;
	uint8_t rssi_tx;
	uint8_t rssi_rc_rx;
	uint8_t rssi_rc_tx;
	float voltage_rx;
	float voltage_zell[6];
	float temperature[2];
	float ampere;
	float fc_voltage1;
	float fc_voltage2;
	uint8_t fc_i2c_errors;
	uint16_t fc_status;
	uint8_t chancount;
	uint8_t sysid;
	uint8_t compid;
	uint8_t get_param;
	uint32_t mavlink_update;
	char telemetry_port[1024];
	uint32_t telemetry_baud;
	char deviceid[1024];
	uint8_t use_deviceid;
	uint8_t use_sysid;
	uint8_t mavlink_sysid;
	uint8_t mavlink_org_sysid;
	uint8_t mavlink_forward;
	uint8_t sysid_list[16];
	char netip[16];
	uint16_t netport;
	int netsock;
	int serial_fd;
	float history[255][5];
	uint8_t num_motors;
	EscStat escstat[16];
	int8_t follow;
} Model;

typedef struct {
	float p_lat;
	float p_long;
	float p_alt;
	float dir;
	uint8_t active;
	uint8_t followme;
	float fm_alt;
	float fm_radius;
	float sp_alt;
	float sp_radius;
	int16_t wifibc_rssi[4];
	int8_t gpsfix;
	int8_t numSat;
	float hdop;
	float vdop;
} Ground;

extern uint8_t ModelActive;
extern Model ModelData[MODELS_MAX];
extern Ground GroundData;

#endif
