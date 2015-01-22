



#define ATTITUDEACTUAL_OBJID 0x33DAD5E6
typedef struct {
    float q1;
    float q2;
    float q3;
    float q4;
    float Roll;
    float Pitch;
    float Yaw;
} AttitudeActualData;

#define ACCELS_OBJID 0xDD9D5FC0
typedef struct {
    float x;
    float y;
    float z;
    float temperature;
} AccelsData;

#define FLIGHTTELEMETRYSTATS_OBJID 0x2F7E2902
typedef struct {
    float TxDataRate;
    float RxDataRate;
    uint32_t TxFailures;
    uint32_t RxFailures;
    uint32_t TxRetries;
    uint8_t TeleStatus;
} FlightTelemetryStatsData;

#define GCSTELEMETRYSTATS_OBJID 0xABC72744
typedef struct {
	float TxDataRate;
	float RxDataRate;
	uint32_t TxFailures;
	uint32_t RxFailures;
	uint32_t TxRetries;
	uint8_t TeleStatus;
} GcsTelemetryStatsData;

#define SYSTEMSTATS_OBJID 0x364D1406
typedef struct {
	uint32_t FlightTime;
	uint32_t EventSystemWarningID;
	uint32_t ObjectManagerCallbackID;
	uint32_t ObjectManagerQueueID;
	uint16_t HeapRemaining;
	uint16_t IRQStackRemaining;
	uint8_t CPULoad;
	int8_t CPUTemp;
} SystemStatsData;

#define GYROS_OBJID 0x4228AF6
typedef struct {
	float x;
	float y;
	float z;
	float temperature;
} GyrosData;

#define SYSTEMALARMS_OBJID 0x7BD9C77A
typedef struct {
	uint8_t Alarm[16];
} SystemAlarmsData;

#define STABILIZATIONDESIRED_OBJID 0x4FDBFEEA
typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
	float Throttle;
	uint8_t StabilizationMode[3];
} StabilizationDesiredData;

#define ACTUATORDESIRED_OBJID 0xCA4BC4A4
typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
	float Throttle;
	float UpdateTime;
	float NumLongUpdates;
} ActuatorDesiredData;

#define RELAYTUNING_OBJID 0xF6EE61BE
typedef struct {
	float Period[3];
	float Gain[3];
} RelayTuningData;

#define ACCESSORYDESIRED_OBJID 0xC409985A
typedef struct {
	float AccessoryVal;
} AccessoryDesiredData;

#define MANUALCONTROLCOMMAND_OBJID 0x1E82C2D2
typedef struct {
	float Throttle;
	float Roll;
	float Pitch;
	float Yaw;
	float Collective;
	uint16_t Channel[9];
	uint8_t Connected;
} ManualControlCommandData;
// typedef enum { CONNECTED_FALSE=0, CONNECTED_TRUE=1 } ConnectedOptions;

#define ACTUATORCOMMAND_OBJID 0x5324CB8
typedef struct {
	int16_t Channel[10];
	uint16_t MaxUpdateTime;
	uint8_t UpdateTime;
	uint8_t NumFailedUpdates;
} ActuatorCommandData;

#define RECEIVERACTIVITYDATA_OBJID 0x1E7C53DA
typedef struct {
	uint8_t ActiveGroup;
	uint8_t ActiveChannel;
} ReceiverActivityData;

#define FLIGHTSTATUSDATA_OBJID 0x9B6A127E
typedef struct {
	uint8_t Armed;
	uint8_t FlightMode;
} FlightStatusData;

#define GPSVELOCITYDATA_OBJID 0x8245DC80
typedef struct {
	float North;
	float East;
	float Down;
} GPSVelocityData;

#define GPSPOSITION_OBJID 0xE2A323B6
typedef struct {
	int32_t Latitude;
	int32_t Longitude;
	float Altitude;
	float GeoidSeparation;
	float Heading;
	float Groundspeed;
	float PDOP;
	float HDOP;
	float VDOP;
	uint8_t GpsStatus;
	int8_t Satellites;
} GPSPositionData;

#define STABILIZATIONSETTINGS_OBJID 0x3D03DE86
typedef struct {
	float ManualRate[3];
	float MaximumRate[3];
	float RollRatePID[4];
	float PitchRatePID[4];
	float YawRatePID[4];
	float RollPI[3];
	float PitchPI[3];
	float YawPI[3];
	float VbarSensitivity[3];
	float VbarRollPI[2];
	float VbarPitchPI[2];
	float VbarYawPI[2];
	float VbarTau;
	float GyroTau;
	float DerivativeGamma;
	float WeakLevelingKp;
	uint8_t RollMax;
	uint8_t PitchMax;
	uint8_t YawMax;
	int8_t VbarGyroSuppress;
	uint8_t VbarPiroComp;
	uint8_t VbarMaxAngle;
	uint8_t DerivativeCutoff;
	uint8_t MaxAxisLock;
	uint8_t MaxAxisLockRate;
	uint8_t MaxWeakLevelingRate;
        uint8_t LowThrottleZeroIntegral;
} StabilizationSettingsData;

#define OBJECTPERSISTENCE_OBJID 0x99C63292
typedef struct {
	uint32_t ObjectID;
	uint32_t InstanceID;
	uint8_t Operation;
	uint8_t Selection;
} ObjectPersistenceData;

#define HWSETTINGS_OBJID 0xA1A9B546
typedef struct {
	uint8_t DSMxBind;
	uint8_t CC_RcvrPort;
	uint8_t CC_MainPort;
	uint8_t CC_FlexiPort;
	uint8_t RV_RcvrPort;
	uint8_t RV_AuxPort;
	uint8_t RV_AuxSBusPort;
	uint8_t RV_FlexiPort;
	uint8_t RV_TelemetryPort;
	uint8_t RV_GPSPort;
	uint8_t TelemetrySpeed;
	uint8_t GPSSpeed;
	uint8_t ComUsbBridgeSpeed;
	uint8_t USB_HIDPort;
	uint8_t USB_VCPPort;
	uint8_t OptionalModules[7];
} HwSettingsData;

#define SYSTEMSETTINGS_OBJID 0xC72A326E
typedef struct {
	uint32_t GUIConfigData;
	uint8_t AirframeType;
} SystemSettingsData;


uint8_t openpilot_init (char *port, uint32_t baud);
void openpilot_exit (void);
void openpilot_update (void);
uint8_t openpilot_connection_status (void);
void openpilot_xml_load (xmlDocPtr doc, xmlNodePtr cur);
void openpilot_xml_save (FILE *fr);

extern void openpilot_defaults_StabilizationSettings (StabilizationSettingsData *data);
extern uint8_t openpilot_get;
extern uint8_t openpilot_set;
extern uint8_t openpilot_save;
extern void openpilot_save_to_flash (void);
extern void openpilot_defaults_StabilizationSettings (StabilizationSettingsData *data);
extern void openpilot_defaults_HwSettings (HwSettingsData *data);
extern void openpilot_defaults_SystemSettings (SystemSettingsData *data);
extern void openpilot_request_SystemSettings (void);

extern StabilizationSettingsData OpenpilotStabilizationSettings;
extern HwSettingsData OpenpilotHwSettings;
extern SystemSettingsData OpenpilotSystemSettings;

