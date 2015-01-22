
#define BOXACC       0
#define BOXBARO      1
#define BOXMAG       2
#define BOXCAMSTAB   3
#define BOXCAMTRIG   4
#define BOXARM       5
#define BOXGPSHOME   6
#define BOXGPSHOLD   7
#define BOXPASSTHRU  8
#define BOXHEADFREE  9
#define BOXBEEPERON  10
#define BOXLEDMAX    11 // we want maximum illumination
#define BOXLLIGHTS   12 // enable landing lights at any altitude
#define BOXHEADADJ   13 // acquire heading for HEADFREE mode


#define MSP_VERSION        	 0
#define MSP_IDENT                100   //out message         multitype + multiwii version + protocol version + capability variable
#define MSP_STATUS               101   //out message         cycletime & errors_count & sensor present & box activation
#define MSP_RAW_IMU              102   //out message         9 DOF
#define MSP_SERVO                103   //out message         8 servos
#define MSP_MOTOR                104   //out message         8 motors
#define MSP_RC                   105   //out message         8 rc chan
#define MSP_RAW_GPS              106   //out message         fix, numsat, lat, lon, alt, speed
#define MSP_COMP_GPS             107   //out message         distance home, direction home
#define MSP_ATTITUDE             108   //out message         2 angles 1 heading
#define MSP_ALTITUDE             109   //out message         1 altitude
#define MSP_BAT                  110   //out message         vbat, powermetersum
#define MSP_RC_TUNING            111   //out message         rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_PID                  112   //out message         up to 16 P I D (8 are used)
#define MSP_BOX                  113   //out message         up to 16 checkbox (11 are used)
#define MSP_MISC                 114   //out message         powermeter trig + 8 free for future use
#define MSP_MOTOR_PINS           115   //out message         which pins are in use for motors & servos, for GUI 
#define MSP_BOXNAMES             116   //out message         the aux switch names
#define MSP_PIDNAMES             117   //out message         the PID names
#define MSP_WP                   118   //out message         get a WP, WP# is in the payload, returns (WP#, lat, lon, alt, flags) WP#0-home, WP#16-poshold
#define MSP_SET_RAW_RC           200   //in message          8 rc chan
#define MSP_SET_RAW_GPS          201   //in message          fix, numsat, lat, lon, alt, speed
#define MSP_SET_PID              202   //in message          up to 16 P I D (8 are used)
#define MSP_SET_BOX              203   //in message          up to 16 checkbox (11 are used)
#define MSP_SET_RC_TUNING        204   //in message          rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_ACC_CALIBRATION      205   //in message          no param
#define MSP_MAG_CALIBRATION      206   //in message          no param
#define MSP_SET_MISC             207   //in message          powermeter trig + 8 free for future use
#define MSP_RESET_CONF           208   //in message          no param
#define MSP_WP_SET               209   //in message          sets a given WP (WP#,lat, lon, alt, flags)
#define MSP_EEPROM_WRITE         250   //in message          no param
#define MSP_DEBUG                254   //out message         debug1,debug2,debug3,debug4

#define MSP_GPSSVINFO            164    //out message         get Signal Strength (only U-Blox)


void mwi21_init (char *port, uint32_t baud);
void mwi21_exit (void);
void mwi21_update (void);
uint8_t mwi21_connection_status (void);
void mwi21_xml_save (FILE *fr);
void mwi21_xml_load (xmlDocPtr doc, xmlNodePtr cur);

void mwi21_cal_acc (void);
void mwi21_cal_mac (void);
void mwi21_get_values (void);
void mwi21_write_rom (void);

void mwi21_web_get (char *url, char *content, char *type);

extern int32_t mwi_status;
extern uint8_t mwi_pid[16][3];
extern uint8_t mwi_set_pid[16][3];
extern uint8_t mwi_set_pid_flag;
extern volatile int16_t mwi_box[16];
extern volatile int16_t mwi_set_box[16];
extern int8_t  mwi_set_box_flag;
extern int16_t mwi_i2cErrors;
extern int16_t mwi_sensors;
extern int16_t mwi_mag_x;
extern int16_t mwi_mag_y;
extern int16_t mwi_mag_z;
extern int16_t cycleTime;
extern char mwi_box_names[16][12];
extern char mwi_pid_names[16][12];


