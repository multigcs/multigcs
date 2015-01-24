
/*************************************************************************************************
 Filename: accels.xml
 Object: Accels
 Comment: The accel data.
*************************************************************************************************/

#define ACCELS_OBJID 0xdd9d5fc0 

typedef struct {
	float x;
	float y;
	float z;
	float temperature;
} UAVT_AccelsData;

extern UAVT_AccelsData uavtalk_AccelsData;


/*************************************************************************************************
 Filename: accessorydesired.xml
 Object: AccessoryDesired
 Comment: Desired Auxillary actuator settings.  Comes from @ref ManualControlModule.
*************************************************************************************************/

#define ACCESSORYDESIRED_OBJID 0xc409985a 

typedef struct {
	float AccessoryVal;
} UAVT_AccessoryDesiredData;

extern UAVT_AccessoryDesiredData uavtalk_AccessoryDesiredData;


/*************************************************************************************************
 Filename: actuatorcommand.xml
 Object: ActuatorCommand
 Comment: Contains the pulse duration sent to each of the channels.  Set by @ref ActuatorModule
*************************************************************************************************/

#define ACTUATORCOMMAND_OBJID 0x5324cb8 

typedef struct {
	int16_t Channel[10];
	uint16_t MaxUpdateTime;
	uint8_t UpdateTime;
	uint8_t NumFailedUpdates;
} UAVT_ActuatorCommandData;

extern UAVT_ActuatorCommandData uavtalk_ActuatorCommandData;


/*************************************************************************************************
 Filename: actuatordesired.xml
 Object: ActuatorDesired
 Comment: Desired raw, pitch and yaw actuator settings.  Comes from either @ref StabilizationModule or @ref ManualControlModule depending on FlightMode.
*************************************************************************************************/

#define ACTUATORDESIRED_OBJID 0xca4bc4a4 

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
	float Throttle;
	float UpdateTime;
	float NumLongUpdates;
} UAVT_ActuatorDesiredData;

extern UAVT_ActuatorDesiredData uavtalk_ActuatorDesiredData;


/*************************************************************************************************
 Filename: actuatorsettings.xml
 Object: ActuatorSettings
 Comment: Settings for the @ref ActuatorModule that controls the channel assignments for the mixer based on AircraftType
*************************************************************************************************/

#define ACTUATORSETTINGS_OBJID 0x7d555646 

enum {
	ACTUATORSETTINGS_CHANNELTYPE_PWM = 0,
	ACTUATORSETTINGS_CHANNELTYPE_MK = 1,
	ACTUATORSETTINGS_CHANNELTYPE_ASTEC4 = 2,
	ACTUATORSETTINGS_CHANNELTYPE_PWM_ALARM_BUZZER = 3,
	ACTUATORSETTINGS_CHANNELTYPE_LASTITEM = 4
};

enum {
	ACTUATORSETTINGS_MOTORSSPINWHILEARMED_FALSE = 0,
	ACTUATORSETTINGS_MOTORSSPINWHILEARMED_TRUE = 1,
	ACTUATORSETTINGS_MOTORSSPINWHILEARMED_LASTITEM = 2
};

extern char UAVT_ActuatorSettingsChannelTypeOption[][42];
extern char UAVT_ActuatorSettingsMotorsSpinWhileArmedOption[][42];
typedef struct {
	uint16_t ChannelUpdateFreq[4];
	int16_t ChannelMax[10];
	int16_t ChannelNeutral[10];
	int16_t ChannelMin[10];
	uint8_t ChannelType[10];	// enum
	uint8_t ChannelAddr[10];
	uint8_t MotorsSpinWhileArmed;	// enum
} UAVT_ActuatorSettingsData;

extern UAVT_ActuatorSettingsData uavtalk_ActuatorSettingsData;


/*************************************************************************************************
 Filename: altholdsmoothed.xml
 Object: AltHoldSmoothed
 Comment: The output on the kalman filter on altitude.
*************************************************************************************************/

#define ALTHOLDSMOOTHED_OBJID 0x2bc6b9d2 

typedef struct {
	float Altitude;
	float Velocity;
	float Accel;
} UAVT_AltHoldSmoothedData;

extern UAVT_AltHoldSmoothedData uavtalk_AltHoldSmoothedData;


/*************************************************************************************************
 Filename: altitudeholddesired.xml
 Object: AltitudeHoldDesired
 Comment: Holds the desired altitude (from manual control) as well as the desired attitude to pass through
*************************************************************************************************/

#define ALTITUDEHOLDDESIRED_OBJID 0x495bad6e 

typedef struct {
	float Altitude;
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_AltitudeHoldDesiredData;

extern UAVT_AltitudeHoldDesiredData uavtalk_AltitudeHoldDesiredData;


/*************************************************************************************************
 Filename: altitudeholdsettings.xml
 Object: AltitudeHoldSettings
 Comment: Settings for the @ref AltitudeHold module
*************************************************************************************************/

#define ALTITUDEHOLDSETTINGS_OBJID 0xfec55b42 

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float Ka;
	float PressureNoise;
	float AccelNoise;
	float AccelDrift;
} UAVT_AltitudeHoldSettingsData;

extern UAVT_AltitudeHoldSettingsData uavtalk_AltitudeHoldSettingsData;


/*************************************************************************************************
 Filename: attitudeactual.xml
 Object: AttitudeActual
 Comment: The updated Attitude estimation from @ref AHRSCommsModule.
*************************************************************************************************/

#define ATTITUDEACTUAL_OBJID 0x33dad5e6 

typedef struct {
	float q1;
	float q2;
	float q3;
	float q4;
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_AttitudeActualData;

extern UAVT_AttitudeActualData uavtalk_AttitudeActualData;


/*************************************************************************************************
 Filename: attitudesettings.xml
 Object: AttitudeSettings
 Comment: Settings for the @ref Attitude module used on CopterControl
*************************************************************************************************/

#define ATTITUDESETTINGS_OBJID 0x54e8f342 

enum {
	ATTITUDESETTINGS_ZERODURINGARMING_FALSE = 0,
	ATTITUDESETTINGS_ZERODURINGARMING_TRUE = 1,
	ATTITUDESETTINGS_ZERODURINGARMING_LASTITEM = 2
};

enum {
	ATTITUDESETTINGS_BIASCORRECTGYRO_FALSE = 0,
	ATTITUDESETTINGS_BIASCORRECTGYRO_TRUE = 1,
	ATTITUDESETTINGS_BIASCORRECTGYRO_LASTITEM = 2
};

enum {
	ATTITUDESETTINGS_TRIMFLIGHT_NORMAL = 0,
	ATTITUDESETTINGS_TRIMFLIGHT_START = 1,
	ATTITUDESETTINGS_TRIMFLIGHT_LOAD = 2,
	ATTITUDESETTINGS_TRIMFLIGHT_LASTITEM = 3
};

extern char UAVT_AttitudeSettingsZeroDuringArmingOption[][42];
extern char UAVT_AttitudeSettingsBiasCorrectGyroOption[][42];
extern char UAVT_AttitudeSettingsTrimFlightOption[][42];
typedef struct {
	int16_t X;
	int16_t Y;
	int16_t Z;
} UAVT_AttitudeSettingsAccelBiasType;

typedef struct {
	int16_t X;
	int16_t Y;
	int16_t Z;
} UAVT_AttitudeSettingsGyroBiasType;

typedef struct {
	int16_t Roll;
	int16_t Pitch;
	int16_t Yaw;
} UAVT_AttitudeSettingsBoardRotationType;

typedef struct {
	float GyroGain;
	float AccelKp;
	float AccelKi;
	float AccelTau;
	float YawBiasRate;
	UAVT_AttitudeSettingsAccelBiasType AccelBias;	// int16[3]
	UAVT_AttitudeSettingsGyroBiasType GyroBias;	// int16[3]
	UAVT_AttitudeSettingsBoardRotationType BoardRotation;	// int16[3]
	uint8_t ZeroDuringArming;	// enum
	uint8_t BiasCorrectGyro;	// enum
	uint8_t TrimFlight;	// enum
} UAVT_AttitudeSettingsData;

extern UAVT_AttitudeSettingsData uavtalk_AttitudeSettingsData;


/*************************************************************************************************
 Filename: baroaltitude.xml
 Object: BaroAltitude
 Comment: The raw data from the barometric sensor with pressure, temperature and altitude estimate.
*************************************************************************************************/

#define BAROALTITUDE_OBJID 0x99622e6a 

typedef struct {
	float Altitude;
	float Temperature;
	float Pressure;
} UAVT_BaroAltitudeData;

extern UAVT_BaroAltitudeData uavtalk_BaroAltitudeData;


/*************************************************************************************************
 Filename: cameradesired.xml
 Object: CameraDesired
 Comment: Desired camera outputs.  Comes from @ref CameraStabilization module.
*************************************************************************************************/

#define CAMERADESIRED_OBJID 0x531f544e 

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_CameraDesiredData;

extern UAVT_CameraDesiredData uavtalk_CameraDesiredData;


/*************************************************************************************************
 Filename: camerastabsettings.xml
 Object: CameraStabSettings
 Comment: Settings for the @ref CameraStab mmodule
*************************************************************************************************/

#define CAMERASTABSETTINGS_OBJID 0x3b95ddba 

enum {
	CAMERASTABSETTINGS_INPUT_ACCESSORY0 = 0,
	CAMERASTABSETTINGS_INPUT_ACCESSORY1 = 1,
	CAMERASTABSETTINGS_INPUT_ACCESSORY2 = 2,
	CAMERASTABSETTINGS_INPUT_ACCESSORY3 = 3,
	CAMERASTABSETTINGS_INPUT_ACCESSORY4 = 4,
	CAMERASTABSETTINGS_INPUT_ACCESSORY5 = 5,
	CAMERASTABSETTINGS_INPUT_NONE = 6,
	CAMERASTABSETTINGS_INPUT_LASTITEM = 7
};

enum {
	CAMERASTABSETTINGS_STABILIZATIONMODE_ATTITUDE = 0,
	CAMERASTABSETTINGS_STABILIZATIONMODE_AXISLOCK = 1,
	CAMERASTABSETTINGS_STABILIZATIONMODE_LASTITEM = 2
};

extern char UAVT_CameraStabSettingsInputOption[][42];
extern char UAVT_CameraStabSettingsStabilizationModeOption[][42];
typedef struct {
	uint16_t Roll;
	uint16_t Pitch;
	uint16_t Yaw;
} UAVT_CameraStabSettingsResponseTimeType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_CameraStabSettingsInputType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_CameraStabSettingsInputRangeType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_CameraStabSettingsInputRateType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_CameraStabSettingsStabilizationModeType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_CameraStabSettingsOutputRangeType;

typedef struct {
	float MaxAxisLockRate;
	UAVT_CameraStabSettingsResponseTimeType ResponseTime;	// uint16[3]
	UAVT_CameraStabSettingsInputType Input;	// enum[3]
	UAVT_CameraStabSettingsInputRangeType InputRange;	// uint8[3]
	UAVT_CameraStabSettingsInputRateType InputRate;	// uint8[3]
	UAVT_CameraStabSettingsStabilizationModeType StabilizationMode;	// enum[3]
	UAVT_CameraStabSettingsOutputRangeType OutputRange;	// uint8[3]
} UAVT_CameraStabSettingsData;

extern UAVT_CameraStabSettingsData uavtalk_CameraStabSettingsData;


/*************************************************************************************************
 Filename: faultsettings.xml
 Object: FaultSettings
 Comment: Allows testers to simulate various fault scenarios.
*************************************************************************************************/

#define FAULTSETTINGS_OBJID 0x2778ba3c 

enum {
	FAULTSETTINGS_ACTIVATEFAULT_NOFAULT = 0,
	FAULTSETTINGS_ACTIVATEFAULT_MODULEINITASSERT = 1,
	FAULTSETTINGS_ACTIVATEFAULT_INITOUTOFMEMORY = 2,
	FAULTSETTINGS_ACTIVATEFAULT_INITBUSERROR = 3,
	FAULTSETTINGS_ACTIVATEFAULT_RUNAWAYTASK = 4,
	FAULTSETTINGS_ACTIVATEFAULT_TASKOUTOFMEMORY = 5,
	FAULTSETTINGS_ACTIVATEFAULT_LASTITEM = 6
};

extern char UAVT_FaultSettingsActivateFaultOption[][42];
typedef struct {
	uint8_t ActivateFault;	// enum
} UAVT_FaultSettingsData;

extern UAVT_FaultSettingsData uavtalk_FaultSettingsData;


/*************************************************************************************************
 Filename: firmwareiapobj.xml
 Object: FirmwareIAPObj
 Comment: Queries board for SN, model, revision, and sends reset command
*************************************************************************************************/

#define FIRMWAREIAPOBJ_OBJID 0x5e6e8fdc 

typedef struct {
	uint32_t crc;
	uint16_t Command;
	uint16_t BoardRevision;
	uint8_t Description[100];
	uint8_t CPUSerial[12];
	uint8_t BoardType;
	uint8_t ArmReset;
} UAVT_FirmwareIAPObjData;

extern UAVT_FirmwareIAPObjData uavtalk_FirmwareIAPObjData;


/*************************************************************************************************
 Filename: flightbatterysettings.xml
 Object: FlightBatterySettings
 Comment: Flight Battery configuration.
*************************************************************************************************/

#define FLIGHTBATTERYSETTINGS_OBJID 0xf172bb18 

enum {
	FLIGHTBATTERYSETTINGS_TYPE_LIPO = 0,
	FLIGHTBATTERYSETTINGS_TYPE_A123 = 1,
	FLIGHTBATTERYSETTINGS_TYPE_LICO = 2,
	FLIGHTBATTERYSETTINGS_TYPE_LIFESO4 = 3,
	FLIGHTBATTERYSETTINGS_TYPE_NONE = 4,
	FLIGHTBATTERYSETTINGS_TYPE_LASTITEM = 5
};

enum {
	FLIGHTBATTERYSETTINGS_SENSORTYPE_NONE = 0,
	FLIGHTBATTERYSETTINGS_SENSORTYPE_LASTITEM = 1
};

extern char UAVT_FlightBatterySettingsTypeOption[][42];
extern char UAVT_FlightBatterySettingsSensorTypeOption[][42];
typedef struct {
	float Warning;
	float Alarm;
} UAVT_FlightBatterySettingsVoltageThresholdsType;

typedef struct {
	float VoltageFactor;
	float CurrentFactor;
} UAVT_FlightBatterySettingsSensorCalibrationsType;

typedef struct {
	uint32_t Capacity;
	UAVT_FlightBatterySettingsVoltageThresholdsType VoltageThresholds;	// float[2]
	UAVT_FlightBatterySettingsSensorCalibrationsType SensorCalibrations;	// float[2]
	uint8_t Type;	// enum
	uint8_t NbCells;
	uint8_t SensorType;	// enum
} UAVT_FlightBatterySettingsData;

extern UAVT_FlightBatterySettingsData uavtalk_FlightBatterySettingsData;


/*************************************************************************************************
 Filename: flightbatterystate.xml
 Object: FlightBatteryState
 Comment: Battery status information.
*************************************************************************************************/

#define FLIGHTBATTERYSTATE_OBJID 0x8c0d756 

typedef struct {
	float Voltage;
	float Current;
	float PeakCurrent;
	float AvgCurrent;
	float ConsumedEnergy;
	float EstimatedFlightTime;
} UAVT_FlightBatteryStateData;

extern UAVT_FlightBatteryStateData uavtalk_FlightBatteryStateData;


/*************************************************************************************************
 Filename: flightplancontrol.xml
 Object: FlightPlanControl
 Comment: Control the flight plan script
*************************************************************************************************/

#define FLIGHTPLANCONTROL_OBJID 0x53e3f180 

enum {
	FLIGHTPLANCONTROL_COMMAND_START = 0,
	FLIGHTPLANCONTROL_COMMAND_STOP = 1,
	FLIGHTPLANCONTROL_COMMAND_KILL = 2,
	FLIGHTPLANCONTROL_COMMAND_LASTITEM = 3
};

extern char UAVT_FlightPlanControlCommandOption[][42];
typedef struct {
	uint8_t Command;	// enum
} UAVT_FlightPlanControlData;

extern UAVT_FlightPlanControlData uavtalk_FlightPlanControlData;


/*************************************************************************************************
 Filename: flightplansettings.xml
 Object: FlightPlanSettings
 Comment: Settings for the flight plan module, control the execution of the script
*************************************************************************************************/

#define FLIGHTPLANSETTINGS_OBJID 0x92e9ff76 

typedef struct {
	float Test;
} UAVT_FlightPlanSettingsData;

extern UAVT_FlightPlanSettingsData uavtalk_FlightPlanSettingsData;


/*************************************************************************************************
 Filename: flightplanstatus.xml
 Object: FlightPlanStatus
 Comment: Status of the flight plan script
*************************************************************************************************/

#define FLIGHTPLANSTATUS_OBJID 0x2206ee46 

enum {
	FLIGHTPLANSTATUS_STATUS_STOPPED = 0,
	FLIGHTPLANSTATUS_STATUS_RUNNING = 1,
	FLIGHTPLANSTATUS_STATUS_ERROR = 2,
	FLIGHTPLANSTATUS_STATUS_LASTITEM = 3
};

enum {
	FLIGHTPLANSTATUS_ERRORTYPE_NONE = 0,
	FLIGHTPLANSTATUS_ERRORTYPE_VMINITERROR = 1,
	FLIGHTPLANSTATUS_ERRORTYPE_EXCEPTION = 2,
	FLIGHTPLANSTATUS_ERRORTYPE_IOERROR = 3,
	FLIGHTPLANSTATUS_ERRORTYPE_DIVBYZERO = 4,
	FLIGHTPLANSTATUS_ERRORTYPE_ASSERTERROR = 5,
	FLIGHTPLANSTATUS_ERRORTYPE_ATTRIBUTEERROR = 6,
	FLIGHTPLANSTATUS_ERRORTYPE_IMPORTERROR = 7,
	FLIGHTPLANSTATUS_ERRORTYPE_INDEXERROR = 8,
	FLIGHTPLANSTATUS_ERRORTYPE_KEYERROR = 9,
	FLIGHTPLANSTATUS_ERRORTYPE_MEMORYERROR = 10,
	FLIGHTPLANSTATUS_ERRORTYPE_NAMEERROR = 11,
	FLIGHTPLANSTATUS_ERRORTYPE_SYNTAXERROR = 12,
	FLIGHTPLANSTATUS_ERRORTYPE_SYSTEMERROR = 13,
	FLIGHTPLANSTATUS_ERRORTYPE_TYPEERROR = 14,
	FLIGHTPLANSTATUS_ERRORTYPE_VALUEERROR = 15,
	FLIGHTPLANSTATUS_ERRORTYPE_STOPITERATION = 16,
	FLIGHTPLANSTATUS_ERRORTYPE_WARNING = 17,
	FLIGHTPLANSTATUS_ERRORTYPE_UNKNOWNERROR = 18,
	FLIGHTPLANSTATUS_ERRORTYPE_LASTITEM = 19
};

extern char UAVT_FlightPlanStatusStatusOption[][42];
extern char UAVT_FlightPlanStatusErrorTypeOption[][42];
typedef struct {
	uint32_t ErrorFileID;
	uint32_t ErrorLineNum;
	float Debug[2];
	uint8_t Status;	// enum
	uint8_t ErrorType;	// enum
} UAVT_FlightPlanStatusData;

extern UAVT_FlightPlanStatusData uavtalk_FlightPlanStatusData;


/*************************************************************************************************
 Filename: flightstatus.xml
 Object: FlightStatus
 Comment: Contains major flight status information for other modules.
*************************************************************************************************/

#define FLIGHTSTATUS_OBJID 0x9b6a127e 

enum {
	FLIGHTSTATUS_ARMED_DISARMED = 0,
	FLIGHTSTATUS_ARMED_ARMING = 1,
	FLIGHTSTATUS_ARMED_ARMED = 2,
	FLIGHTSTATUS_ARMED_LASTITEM = 3
};

enum {
	FLIGHTSTATUS_FLIGHTMODE_MANUAL = 0,
	FLIGHTSTATUS_FLIGHTMODE_STABILIZED1 = 1,
	FLIGHTSTATUS_FLIGHTMODE_STABILIZED2 = 2,
	FLIGHTSTATUS_FLIGHTMODE_STABILIZED3 = 3,
	FLIGHTSTATUS_FLIGHTMODE_AUTOTUNE = 4,
	FLIGHTSTATUS_FLIGHTMODE_ALTITUDEHOLD = 5,
	FLIGHTSTATUS_FLIGHTMODE_VELOCITYCONTROL = 6,
	FLIGHTSTATUS_FLIGHTMODE_POSITIONHOLD = 7,
	FLIGHTSTATUS_FLIGHTMODE_LASTITEM = 8
};

extern char UAVT_FlightStatusArmedOption[][42];
extern char UAVT_FlightStatusFlightModeOption[][42];
typedef struct {
	uint8_t Armed;	// enum
	uint8_t FlightMode;	// enum
} UAVT_FlightStatusData;

extern UAVT_FlightStatusData uavtalk_FlightStatusData;


/*************************************************************************************************
 Filename: flighttelemetrystats.xml
 Object: FlightTelemetryStats
 Comment: Maintains the telemetry statistics from the OpenPilot flight computer.
*************************************************************************************************/

#define FLIGHTTELEMETRYSTATS_OBJID 0x2f7e2902 

enum {
	FLIGHTTELEMETRYSTATS_STATUS_DISCONNECTED = 0,
	FLIGHTTELEMETRYSTATS_STATUS_HANDSHAKEREQ = 1,
	FLIGHTTELEMETRYSTATS_STATUS_HANDSHAKEACK = 2,
	FLIGHTTELEMETRYSTATS_STATUS_CONNECTED = 3,
	FLIGHTTELEMETRYSTATS_STATUS_LASTITEM = 4
};

extern char UAVT_FlightTelemetryStatsStatusOption[][42];
typedef struct {
	float TxDataRate;
	float RxDataRate;
	uint32_t TxFailures;
	uint32_t RxFailures;
	uint32_t TxRetries;
	uint8_t Status;	// enum
} UAVT_FlightTelemetryStatsData;

extern UAVT_FlightTelemetryStatsData uavtalk_FlightTelemetryStatsData;


/*************************************************************************************************
 Filename: gcsreceiver.xml
 Object: GCSReceiver
 Comment: A receiver channel group carried over the telemetry link.
*************************************************************************************************/

#define GCSRECEIVER_OBJID 0xcc7e1470 

typedef struct {
	uint16_t Channel[8];
} UAVT_GCSReceiverData;

extern UAVT_GCSReceiverData uavtalk_GCSReceiverData;


/*************************************************************************************************
 Filename: gcstelemetrystats.xml
 Object: GCSTelemetryStats
 Comment: The telemetry statistics from the ground computer
*************************************************************************************************/

#define GCSTELEMETRYSTATS_OBJID 0xabc72744 

enum {
	GCSTELEMETRYSTATS_STATUS_DISCONNECTED = 0,
	GCSTELEMETRYSTATS_STATUS_HANDSHAKEREQ = 1,
	GCSTELEMETRYSTATS_STATUS_HANDSHAKEACK = 2,
	GCSTELEMETRYSTATS_STATUS_CONNECTED = 3,
	GCSTELEMETRYSTATS_STATUS_LASTITEM = 4
};

extern char UAVT_GCSTelemetryStatsStatusOption[][42];
typedef struct {
	float TxDataRate;
	float RxDataRate;
	uint32_t TxFailures;
	uint32_t RxFailures;
	uint32_t TxRetries;
	uint8_t Status;	// enum
} UAVT_GCSTelemetryStatsData;

extern UAVT_GCSTelemetryStatsData uavtalk_GCSTelemetryStatsData;


/*************************************************************************************************
 Filename: gpsposition.xml
 Object: GPSPosition
 Comment: Raw GPS data from @ref GPSModule.  Should only be used by @ref AHRSCommsModule.
*************************************************************************************************/

#define GPSPOSITION_OBJID 0xe2a323b6 

enum {
	GPSPOSITION_STATUS_NOGPS = 0,
	GPSPOSITION_STATUS_NOFIX = 1,
	GPSPOSITION_STATUS_FIX2D = 2,
	GPSPOSITION_STATUS_FIX3D = 3,
	GPSPOSITION_STATUS_LASTITEM = 4
};

extern char UAVT_GPSPositionStatusOption[][42];
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
	uint8_t Status;	// enum
	int8_t Satellites;
} UAVT_GPSPositionData;

extern UAVT_GPSPositionData uavtalk_GPSPositionData;


/*************************************************************************************************
 Filename: gpssatellites.xml
 Object: GPSSatellites
 Comment: Contains information about the GPS satellites in view from @ref GPSModule.
*************************************************************************************************/

#define GPSSATELLITES_OBJID 0x920d998 

typedef struct {
	float Elevation[16];
	float Azimuth[16];
	int8_t SatsInView;
	int8_t PRN[16];
	int8_t SNR[16];
} UAVT_GPSSatellitesData;

extern UAVT_GPSSatellitesData uavtalk_GPSSatellitesData;


/*************************************************************************************************
 Filename: gpssettings.xml
 Object: GPSSettings
 Comment: Settings for the GPS
*************************************************************************************************/

#define GPSSETTINGS_OBJID 0xac5f6370 

enum {
	GPSSETTINGS_DATAPROTOCOL_NMEA = 0,
	GPSSETTINGS_DATAPROTOCOL_UBX = 1,
	GPSSETTINGS_DATAPROTOCOL_LASTITEM = 2
};

extern char UAVT_GPSSettingsDataProtocolOption[][42];
typedef struct {
	uint8_t DataProtocol;	// enum
} UAVT_GPSSettingsData;

extern UAVT_GPSSettingsData uavtalk_GPSSettingsData;


/*************************************************************************************************
 Filename: gpstime.xml
 Object: GPSTime
 Comment: Contains the GPS time from @ref GPSModule.  Required to compute the world magnetic model correctly when setting the home location.
*************************************************************************************************/

#define GPSTIME_OBJID 0xd4478084 

typedef struct {
	int16_t Year;
	int8_t Month;
	int8_t Day;
	int8_t Hour;
	int8_t Minute;
	int8_t Second;
} UAVT_GPSTimeData;

extern UAVT_GPSTimeData uavtalk_GPSTimeData;


/*************************************************************************************************
 Filename: gpsvelocity.xml
 Object: GPSVelocity
 Comment: Raw GPS data from @ref GPSModule.
*************************************************************************************************/

#define GPSVELOCITY_OBJID 0x8245dc80 

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_GPSVelocityData;

extern UAVT_GPSVelocityData uavtalk_GPSVelocityData;


/*************************************************************************************************
 Filename: guidancesettings.xml
 Object: GuidanceSettings
 Comment: Settings for the @ref GuidanceModule
*************************************************************************************************/

#define GUIDANCESETTINGS_OBJID 0x6ea79fb4 

enum {
	GUIDANCESETTINGS_GUIDANCEMODE_DUAL_LOOP = 0,
	GUIDANCESETTINGS_GUIDANCEMODE_VELOCITY_CONTROL = 1,
	GUIDANCESETTINGS_GUIDANCEMODE_LASTITEM = 2
};

enum {
	GUIDANCESETTINGS_THROTTLECONTROL_FALSE = 0,
	GUIDANCESETTINGS_THROTTLECONTROL_TRUE = 1,
	GUIDANCESETTINGS_THROTTLECONTROL_LASTITEM = 2
};

extern char UAVT_GuidanceSettingsGuidanceModeOption[][42];
extern char UAVT_GuidanceSettingsThrottleControlOption[][42];
typedef struct {
	float Kp;
	float Ki;
	float ILimit;
} UAVT_GuidanceSettingsHorizontalPosPIType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_GuidanceSettingsHorizontalVelPIDType;

typedef struct {
	float Kp;
	float Ki;
	float ILimit;
} UAVT_GuidanceSettingsVerticalPosPIType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_GuidanceSettingsVerticalVelPIDType;

typedef struct {
	UAVT_GuidanceSettingsHorizontalPosPIType HorizontalPosPI;	// float[3]
	UAVT_GuidanceSettingsHorizontalVelPIDType HorizontalVelPID;	// float[4]
	UAVT_GuidanceSettingsVerticalPosPIType VerticalPosPI;	// float[3]
	UAVT_GuidanceSettingsVerticalVelPIDType VerticalVelPID;	// float[4]
	float MaxRollPitch;
	int32_t UpdatePeriod;
	uint16_t HorizontalVelMax;
	uint16_t VerticalVelMax;
	uint8_t GuidanceMode;	// enum
	uint8_t ThrottleControl;	// enum
} UAVT_GuidanceSettingsData;

extern UAVT_GuidanceSettingsData uavtalk_GuidanceSettingsData;


/*************************************************************************************************
 Filename: gyrosbias.xml
 Object: GyrosBias
 Comment: The gyro data.
*************************************************************************************************/

#define GYROSBIAS_OBJID 0xe4b6f980 

typedef struct {
	float x;
	float y;
	float z;
} UAVT_GyrosBiasData;

extern UAVT_GyrosBiasData uavtalk_GyrosBiasData;


/*************************************************************************************************
 Filename: gyros.xml
 Object: Gyros
 Comment: The gyro data.
*************************************************************************************************/

#define GYROS_OBJID 0x4228af6 

typedef struct {
	float x;
	float y;
	float z;
	float temperature;
} UAVT_GyrosData;

extern UAVT_GyrosData uavtalk_GyrosData;


/*************************************************************************************************
 Filename: homelocation.xml
 Object: HomeLocation
 Comment: HomeLocation setting which contains the constants to tranlate from longitutde and latitude to NED reference frame.  Automatically set by @ref GPSModule after acquiring a 3D lock.  Used by @ref AHRSCommsModule.
*************************************************************************************************/

#define HOMELOCATION_OBJID 0x5bb3aefc 

enum {
	HOMELOCATION_SET_FALSE = 0,
	HOMELOCATION_SET_TRUE = 1,
	HOMELOCATION_SET_LASTITEM = 2
};

extern char UAVT_HomeLocationSetOption[][42];
typedef struct {
	int32_t Latitude;
	int32_t Longitude;
	float Altitude;
	int32_t ECEF[3];
	float RNE[9];
	float Be[3];
	float g_e;
	uint8_t Set;	// enum
} UAVT_HomeLocationData;

extern UAVT_HomeLocationData uavtalk_HomeLocationData;


/*************************************************************************************************
 Filename: hwsettings.xml
 Object: HwSettings
 Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWSETTINGS_OBJID 0xa1a9b546 

enum {
	HWSETTINGS_CC_RCVRPORT_DISABLED = 0,
	HWSETTINGS_CC_RCVRPORT_PWM = 1,
	HWSETTINGS_CC_RCVRPORT_PPM = 2,
	HWSETTINGS_CC_RCVRPORT_PPM_PWM = 3,
	HWSETTINGS_CC_RCVRPORT_PPM_OUTPUTS = 4,
	HWSETTINGS_CC_RCVRPORT_OUTPUTS = 5,
	HWSETTINGS_CC_RCVRPORT_LASTITEM = 6
};

enum {
	HWSETTINGS_CC_MAINPORT_DISABLED = 0,
	HWSETTINGS_CC_MAINPORT_TELEMETRY = 1,
	HWSETTINGS_CC_MAINPORT_GPS = 2,
	HWSETTINGS_CC_MAINPORT_S_BUS = 3,
	HWSETTINGS_CC_MAINPORT_DSM2 = 4,
	HWSETTINGS_CC_MAINPORT_DSMX__10BIT_ = 5,
	HWSETTINGS_CC_MAINPORT_DSMX__11BIT_ = 6,
	HWSETTINGS_CC_MAINPORT_COMAUX = 7,
	HWSETTINGS_CC_MAINPORT_COMBRIDGE = 8,
	HWSETTINGS_CC_MAINPORT_LASTITEM = 9
};

enum {
	HWSETTINGS_CC_FLEXIPORT_DISABLED = 0,
	HWSETTINGS_CC_FLEXIPORT_TELEMETRY = 1,
	HWSETTINGS_CC_FLEXIPORT_GPS = 2,
	HWSETTINGS_CC_FLEXIPORT_I2C = 3,
	HWSETTINGS_CC_FLEXIPORT_DSM2 = 4,
	HWSETTINGS_CC_FLEXIPORT_DSMX__10BIT_ = 5,
	HWSETTINGS_CC_FLEXIPORT_DSMX__11BIT_ = 6,
	HWSETTINGS_CC_FLEXIPORT_COMAUX = 7,
	HWSETTINGS_CC_FLEXIPORT_COMBRIDGE = 8,
	HWSETTINGS_CC_FLEXIPORT_LASTITEM = 9
};

enum {
	HWSETTINGS_RV_RCVRPORT_DISABLED = 0,
	HWSETTINGS_RV_RCVRPORT_PWM = 1,
	HWSETTINGS_RV_RCVRPORT_PPM = 2,
	HWSETTINGS_RV_RCVRPORT_PPM_OUTPUTS = 3,
	HWSETTINGS_RV_RCVRPORT_OUTPUTS = 4,
	HWSETTINGS_RV_RCVRPORT_LASTITEM = 5
};

enum {
	HWSETTINGS_RV_AUXPORT_DISABLED = 0,
	HWSETTINGS_RV_AUXPORT_TELEMETRY = 1,
	HWSETTINGS_RV_AUXPORT_DSM2 = 2,
	HWSETTINGS_RV_AUXPORT_DSMX__10BIT_ = 3,
	HWSETTINGS_RV_AUXPORT_DSMX__11BIT_ = 4,
	HWSETTINGS_RV_AUXPORT_COMAUX = 5,
	HWSETTINGS_RV_AUXPORT_COMBRIDGE = 6,
	HWSETTINGS_RV_AUXPORT_LASTITEM = 7
};

enum {
	HWSETTINGS_RV_AUXSBUSPORT_DISABLED = 0,
	HWSETTINGS_RV_AUXSBUSPORT_S_BUS = 1,
	HWSETTINGS_RV_AUXSBUSPORT_DSM2 = 2,
	HWSETTINGS_RV_AUXSBUSPORT_DSMX__10BIT_ = 3,
	HWSETTINGS_RV_AUXSBUSPORT_DSMX__11BIT_ = 4,
	HWSETTINGS_RV_AUXSBUSPORT_COMAUX = 5,
	HWSETTINGS_RV_AUXSBUSPORT_COMBRIDGE = 6,
	HWSETTINGS_RV_AUXSBUSPORT_LASTITEM = 7
};

enum {
	HWSETTINGS_RV_FLEXIPORT_DISABLED = 0,
	HWSETTINGS_RV_FLEXIPORT_I2C = 1,
	HWSETTINGS_RV_FLEXIPORT_DSM2 = 2,
	HWSETTINGS_RV_FLEXIPORT_DSMX__10BIT_ = 3,
	HWSETTINGS_RV_FLEXIPORT_DSMX__11BIT_ = 4,
	HWSETTINGS_RV_FLEXIPORT_COMAUX = 5,
	HWSETTINGS_RV_FLEXIPORT_COMBRIDGE = 6,
	HWSETTINGS_RV_FLEXIPORT_LASTITEM = 7
};

enum {
	HWSETTINGS_RV_TELEMETRYPORT_DISABLED = 0,
	HWSETTINGS_RV_TELEMETRYPORT_TELEMETRY = 1,
	HWSETTINGS_RV_TELEMETRYPORT_COMAUX = 2,
	HWSETTINGS_RV_TELEMETRYPORT_COMBRIDGE = 3,
	HWSETTINGS_RV_TELEMETRYPORT_LASTITEM = 4
};

enum {
	HWSETTINGS_RV_GPSPORT_DISABLED = 0,
	HWSETTINGS_RV_GPSPORT_TELEMETRY = 1,
	HWSETTINGS_RV_GPSPORT_GPS = 2,
	HWSETTINGS_RV_GPSPORT_COMAUX = 3,
	HWSETTINGS_RV_GPSPORT_COMBRIDGE = 4,
	HWSETTINGS_RV_GPSPORT_LASTITEM = 5
};

enum {
	HWSETTINGS_TELEMETRYSPEED_2400 = 0,
	HWSETTINGS_TELEMETRYSPEED_4800 = 1,
	HWSETTINGS_TELEMETRYSPEED_9600 = 2,
	HWSETTINGS_TELEMETRYSPEED_19200 = 3,
	HWSETTINGS_TELEMETRYSPEED_38400 = 4,
	HWSETTINGS_TELEMETRYSPEED_57600 = 5,
	HWSETTINGS_TELEMETRYSPEED_115200 = 6,
	HWSETTINGS_TELEMETRYSPEED_LASTITEM = 7
};

enum {
	HWSETTINGS_GPSSPEED_2400 = 0,
	HWSETTINGS_GPSSPEED_4800 = 1,
	HWSETTINGS_GPSSPEED_9600 = 2,
	HWSETTINGS_GPSSPEED_19200 = 3,
	HWSETTINGS_GPSSPEED_38400 = 4,
	HWSETTINGS_GPSSPEED_57600 = 5,
	HWSETTINGS_GPSSPEED_115200 = 6,
	HWSETTINGS_GPSSPEED_LASTITEM = 7
};

enum {
	HWSETTINGS_COMUSBBRIDGESPEED_2400 = 0,
	HWSETTINGS_COMUSBBRIDGESPEED_4800 = 1,
	HWSETTINGS_COMUSBBRIDGESPEED_9600 = 2,
	HWSETTINGS_COMUSBBRIDGESPEED_19200 = 3,
	HWSETTINGS_COMUSBBRIDGESPEED_38400 = 4,
	HWSETTINGS_COMUSBBRIDGESPEED_57600 = 5,
	HWSETTINGS_COMUSBBRIDGESPEED_115200 = 6,
	HWSETTINGS_COMUSBBRIDGESPEED_LASTITEM = 7
};

enum {
	HWSETTINGS_USB_HIDPORT_USBTELEMETRY = 0,
	HWSETTINGS_USB_HIDPORT_RCTRANSMITTER = 1,
	HWSETTINGS_USB_HIDPORT_DISABLED = 2,
	HWSETTINGS_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWSETTINGS_USB_VCPPORT_USBTELEMETRY = 0,
	HWSETTINGS_USB_VCPPORT_COMBRIDGE = 1,
	HWSETTINGS_USB_VCPPORT_DISABLED = 2,
	HWSETTINGS_USB_VCPPORT_LASTITEM = 3
};

enum {
	HWSETTINGS_OPTIONALMODULES_DISABLED = 0,
	HWSETTINGS_OPTIONALMODULES_ENABLED = 1,
	HWSETTINGS_OPTIONALMODULES_LASTITEM = 2
};

extern char UAVT_HwSettingsCC_RcvrPortOption[][42];
extern char UAVT_HwSettingsCC_MainPortOption[][42];
extern char UAVT_HwSettingsCC_FlexiPortOption[][42];
extern char UAVT_HwSettingsRV_RcvrPortOption[][42];
extern char UAVT_HwSettingsRV_AuxPortOption[][42];
extern char UAVT_HwSettingsRV_AuxSBusPortOption[][42];
extern char UAVT_HwSettingsRV_FlexiPortOption[][42];
extern char UAVT_HwSettingsRV_TelemetryPortOption[][42];
extern char UAVT_HwSettingsRV_GPSPortOption[][42];
extern char UAVT_HwSettingsTelemetrySpeedOption[][42];
extern char UAVT_HwSettingsGPSSpeedOption[][42];
extern char UAVT_HwSettingsComUsbBridgeSpeedOption[][42];
extern char UAVT_HwSettingsUSB_HIDPortOption[][42];
extern char UAVT_HwSettingsUSB_VCPPortOption[][42];
extern char UAVT_HwSettingsOptionalModulesOption[][42];
typedef struct {
	uint8_t CameraStab;
	uint8_t GPS;
	uint8_t ComUsbBridge;
	uint8_t Fault;
	uint8_t Altitude;
	uint8_t TxPID;
	uint8_t Autotune;
} UAVT_HwSettingsOptionalModulesType;

typedef struct {
	uint8_t CC_RcvrPort;	// enum
	uint8_t CC_MainPort;	// enum
	uint8_t CC_FlexiPort;	// enum
	uint8_t RV_RcvrPort;	// enum
	uint8_t RV_AuxPort;	// enum
	uint8_t RV_AuxSBusPort;	// enum
	uint8_t RV_FlexiPort;	// enum
	uint8_t RV_TelemetryPort;	// enum
	uint8_t RV_GPSPort;	// enum
	uint8_t TelemetrySpeed;	// enum
	uint8_t GPSSpeed;	// enum
	uint8_t ComUsbBridgeSpeed;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	UAVT_HwSettingsOptionalModulesType OptionalModules;	// enum[7]
	uint8_t DSMxBind;
} UAVT_HwSettingsData;

extern UAVT_HwSettingsData uavtalk_HwSettingsData;


/*************************************************************************************************
 Filename: i2cstats.xml
 Object: I2CStats
 Comment: Tracks statistics on the I2C bus.
*************************************************************************************************/

#define I2CSTATS_OBJID 0xb714823e 

enum {
	I2CSTATS_LAST_ERROR_TYPE_EVENT = 0,
	I2CSTATS_LAST_ERROR_TYPE_FSM = 1,
	I2CSTATS_LAST_ERROR_TYPE_INTERRUPT = 2,
	I2CSTATS_LAST_ERROR_TYPE_LASTITEM = 3
};

enum {
	I2CSTATS_EVENT_LOG_I2C_EVENT_BUS_ERROR = 0,
	I2CSTATS_EVENT_LOG_I2C_EVENT_START = 1,
	I2CSTATS_EVENT_LOG_I2C_EVENT_STARTED_MORE_TXN_READ = 2,
	I2CSTATS_EVENT_LOG_I2C_EVENT_STARTED_MORE_TXN_WRITE = 3,
	I2CSTATS_EVENT_LOG_I2C_EVENT_STARTED_LAST_TXN_READ = 4,
	I2CSTATS_EVENT_LOG_I2C_EVENT_STARTED_LAST_TXN_WRITE = 5,
	I2CSTATS_EVENT_LOG_I2C_EVENT_ADDR_SENT_LEN_EQ_0 = 6,
	I2CSTATS_EVENT_LOG_I2C_EVENT_ADDR_SENT_LEN_EQ_1 = 7,
	I2CSTATS_EVENT_LOG_I2C_EVENT_ADDR_SENT_LEN_EQ_2 = 8,
	I2CSTATS_EVENT_LOG_I2C_EVENT_ADDR_SENT_LEN_GT_2 = 9,
	I2CSTATS_EVENT_LOG_I2C_EVENT_TRANSFER_DONE_LEN_EQ_0 = 10,
	I2CSTATS_EVENT_LOG_I2C_EVENT_TRANSFER_DONE_LEN_EQ_1 = 11,
	I2CSTATS_EVENT_LOG_I2C_EVENT_TRANSFER_DONE_LEN_EQ_2 = 12,
	I2CSTATS_EVENT_LOG_I2C_EVENT_TRANSFER_DONE_LEN_GT_2 = 13,
	I2CSTATS_EVENT_LOG_I2C_EVENT_NACK = 14,
	I2CSTATS_EVENT_LOG_I2C_EVENT_STOPPED = 15,
	I2CSTATS_EVENT_LOG_I2C_EVENT_AUTO = 16,
	I2CSTATS_EVENT_LOG_LASTITEM = 17
};

enum {
	I2CSTATS_STATE_LOG_I2C_STATE_FSM_FAULT = 0,
	I2CSTATS_STATE_LOG_I2C_STATE_BUS_ERROR = 1,
	I2CSTATS_STATE_LOG_I2C_STATE_STOPPED = 2,
	I2CSTATS_STATE_LOG_I2C_STATE_STOPPING = 3,
	I2CSTATS_STATE_LOG_I2C_STATE_STARTING = 4,
	I2CSTATS_STATE_LOG_I2C_STATE_R_MORE_TXN_ADDR = 5,
	I2CSTATS_STATE_LOG_I2C_STATE_R_MORE_TXN_PRE_ONE = 6,
	I2CSTATS_STATE_LOG_I2C_STATE_R_MORE_TXN_PRE_FIRST = 7,
	I2CSTATS_STATE_LOG_I2C_STATE_R_MORE_TXN_PRE_MIDDLE = 8,
	I2CSTATS_STATE_LOG_I2C_STATE_R_MORE_TXN_LAST = 9,
	I2CSTATS_STATE_LOG_I2C_STATE_R_MORE_TXN_POST_LAST = 10,
	I2CSTATS_STATE_LOG_R_LAST_TXN_ADDR = 11,
	I2CSTATS_STATE_LOG_I2C_STATE_R_LAST_TXN_PRE_ONE = 12,
	I2CSTATS_STATE_LOG_I2C_STATE_R_LAST_TXN_PRE_FIRST = 13,
	I2CSTATS_STATE_LOG_I2C_STATE_R_LAST_TXN_PRE_MIDDLE = 14,
	I2CSTATS_STATE_LOG_I2C_STATE_R_LAST_TXN_PRE_LAST = 15,
	I2CSTATS_STATE_LOG_I2C_STATE_R_LAST_TXN_POST_LAST = 16,
	I2CSTATS_STATE_LOG_I2C_STATE_W_MORE_TXN_ADDR = 17,
	I2CSTATS_STATE_LOG_I2C_STATE_W_MORE_TXN_MIDDLE = 18,
	I2CSTATS_STATE_LOG_I2C_STATE_W_MORE_TXN_LAST = 19,
	I2CSTATS_STATE_LOG_I2C_STATE_W_LAST_TXN_ADDR = 20,
	I2CSTATS_STATE_LOG_I2C_STATE_W_LAST_TXN_MIDDLE = 21,
	I2CSTATS_STATE_LOG_I2C_STATE_W_LAST_TXN_LAST = 22,
	I2CSTATS_STATE_LOG_I2C_STATE_NACK = 23,
	I2CSTATS_STATE_LOG_LASTITEM = 24
};

extern char UAVT_I2CStatslast_error_typeOption[][42];
extern char UAVT_I2CStatsevent_logOption[][42];
extern char UAVT_I2CStatsstate_logOption[][42];
typedef struct {
	uint32_t evirq_log[5];
	uint32_t erirq_log[5];
	uint8_t event_errors;
	uint8_t fsm_errors;
	uint8_t irq_errors;
	uint8_t nacks;
	uint8_t timeouts;
	uint8_t last_error_type;	// enum
	uint8_t event_log[5];	// enum
	uint8_t state_log[5];	// enum
} UAVT_I2CStatsData;

extern UAVT_I2CStatsData uavtalk_I2CStatsData;


/*************************************************************************************************
 Filename: magnetometer.xml
 Object: Magnetometer
 Comment: The mag data.
*************************************************************************************************/

#define MAGNETOMETER_OBJID 0x813b55de 

typedef struct {
	float x;
	float y;
	float z;
} UAVT_MagnetometerData;

extern UAVT_MagnetometerData uavtalk_MagnetometerData;


/*************************************************************************************************
 Filename: manualcontrolcommand.xml
 Object: ManualControlCommand
 Comment: The output from the @ref ManualControlModule which descodes the receiver inputs.  Overriden by GCS for fly-by-wire control.
*************************************************************************************************/

#define MANUALCONTROLCOMMAND_OBJID 0x1e82c2d2 

enum {
	MANUALCONTROLCOMMAND_CONNECTED_FALSE = 0,
	MANUALCONTROLCOMMAND_CONNECTED_TRUE = 1,
	MANUALCONTROLCOMMAND_CONNECTED_LASTITEM = 2
};

extern char UAVT_ManualControlCommandConnectedOption[][42];
typedef struct {
	float Throttle;
	float Roll;
	float Pitch;
	float Yaw;
	float Collective;
	uint16_t Channel[9];
	uint8_t Connected;	// enum
} UAVT_ManualControlCommandData;

extern UAVT_ManualControlCommandData uavtalk_ManualControlCommandData;


/*************************************************************************************************
 Filename: manualcontrolsettings.xml
 Object: ManualControlSettings
 Comment: Settings to indicate how to decode receiver input by @ref ManualControlModule.
*************************************************************************************************/

#define MANUALCONTROLSETTINGS_OBJID 0xa240d466 

enum {
	MANUALCONTROLSETTINGS_CHANNELGROUPS_PWM = 0,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_PPM = 1,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_DSM__MAINPORT_ = 2,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_DSM__FLEXIPORT_ = 3,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_S_BUS = 4,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS = 5,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_NONE = 6,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM = 7
};

enum {
	MANUALCONTROLSETTINGS_ARMING_ALWAYS_DISARMED = 0,
	MANUALCONTROLSETTINGS_ARMING_ALWAYS_ARMED = 1,
	MANUALCONTROLSETTINGS_ARMING_ROLL_LEFT = 2,
	MANUALCONTROLSETTINGS_ARMING_ROLL_RIGHT = 3,
	MANUALCONTROLSETTINGS_ARMING_PITCH_FORWARD = 4,
	MANUALCONTROLSETTINGS_ARMING_PITCH_AFT = 5,
	MANUALCONTROLSETTINGS_ARMING_YAW_LEFT = 6,
	MANUALCONTROLSETTINGS_ARMING_YAW_RIGHT = 7,
	MANUALCONTROLSETTINGS_ARMING_LASTITEM = 8
};

enum {
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_NONE = 0,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_RATE = 1,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_ATTITUDE = 2,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_AXISLOCK = 3,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_WEAKLEVELING = 4,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_VIRTUALBAR = 5,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_RELAYRATE = 6,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_RELAYATTITUDE = 7,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_LASTITEM = 8
};

enum {
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_NONE = 0,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_RATE = 1,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_ATTITUDE = 2,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_AXISLOCK = 3,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_WEAKLEVELING = 4,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_VIRTUALBAR = 5,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_RELAYRATE = 6,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_RELAYATTITUDE = 7,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_LASTITEM = 8
};

enum {
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_NONE = 0,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_RATE = 1,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_ATTITUDE = 2,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_AXISLOCK = 3,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_WEAKLEVELING = 4,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_VIRTUALBAR = 5,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_RELAYRATE = 6,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_RELAYATTITUDE = 7,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_LASTITEM = 8
};

enum {
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_MANUAL = 0,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_STABILIZED1 = 1,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_STABILIZED2 = 2,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_STABILIZED3 = 3,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_AUTOTUNE = 4,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_ALTITUDEHOLD = 5,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_VELOCITYCONTROL = 6,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_POSITIONHOLD = 7,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_LASTITEM = 8
};

extern char UAVT_ManualControlSettingsChannelGroupsOption[][42];
extern char UAVT_ManualControlSettingsArmingOption[][42];
extern char UAVT_ManualControlSettingsStabilization1SettingsOption[][42];
extern char UAVT_ManualControlSettingsStabilization2SettingsOption[][42];
extern char UAVT_ManualControlSettingsStabilization3SettingsOption[][42];
extern char UAVT_ManualControlSettingsFlightModePositionOption[][42];
typedef struct {
	int16_t Throttle;
	int16_t Roll;
	int16_t Pitch;
	int16_t Yaw;
	int16_t FlightMode;
	int16_t Collective;
	int16_t Accessory0;
	int16_t Accessory1;
	int16_t Accessory2;
} UAVT_ManualControlSettingsChannelMinType;

typedef struct {
	int16_t Throttle;
	int16_t Roll;
	int16_t Pitch;
	int16_t Yaw;
	int16_t FlightMode;
	int16_t Collective;
	int16_t Accessory0;
	int16_t Accessory1;
	int16_t Accessory2;
} UAVT_ManualControlSettingsChannelNeutralType;

typedef struct {
	int16_t Throttle;
	int16_t Roll;
	int16_t Pitch;
	int16_t Yaw;
	int16_t FlightMode;
	int16_t Collective;
	int16_t Accessory0;
	int16_t Accessory1;
	int16_t Accessory2;
} UAVT_ManualControlSettingsChannelMaxType;

typedef struct {
	uint8_t Throttle;
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
	uint8_t FlightMode;
	uint8_t Collective;
	uint8_t Accessory0;
	uint8_t Accessory1;
	uint8_t Accessory2;
} UAVT_ManualControlSettingsChannelGroupsType;

typedef struct {
	uint8_t Throttle;
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
	uint8_t FlightMode;
	uint8_t Collective;
	uint8_t Accessory0;
	uint8_t Accessory1;
	uint8_t Accessory2;
} UAVT_ManualControlSettingsChannelNumberType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_ManualControlSettingsStabilization1SettingsType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_ManualControlSettingsStabilization2SettingsType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_ManualControlSettingsStabilization3SettingsType;

typedef struct {
	float Deadband;
	UAVT_ManualControlSettingsChannelMinType ChannelMin;	// int16[9]
	UAVT_ManualControlSettingsChannelNeutralType ChannelNeutral;	// int16[9]
	UAVT_ManualControlSettingsChannelMaxType ChannelMax;	// int16[9]
	uint16_t ArmedTimeout;
	UAVT_ManualControlSettingsChannelGroupsType ChannelGroups;	// enum[9]
	UAVT_ManualControlSettingsChannelNumberType ChannelNumber;	// uint8[9]
	uint8_t Arming;	// enum
	UAVT_ManualControlSettingsStabilization1SettingsType Stabilization1Settings;	// enum[3]
	UAVT_ManualControlSettingsStabilization2SettingsType Stabilization2Settings;	// enum[3]
	UAVT_ManualControlSettingsStabilization3SettingsType Stabilization3Settings;	// enum[3]
	uint8_t FlightModeNumber;
	uint8_t FlightModePosition[6];	// enum
} UAVT_ManualControlSettingsData;

extern UAVT_ManualControlSettingsData uavtalk_ManualControlSettingsData;


/*************************************************************************************************
 Filename: mixersettings.xml
 Object: MixerSettings
 Comment: Settings for the @ref ActuatorModule that controls the channel assignments for the mixer based on AircraftType
*************************************************************************************************/

#define MIXERSETTINGS_OBJID 0xf7843140 

extern char UAVT_MixerSettingsCurve2SourceOption[][42];
extern char UAVT_MixerSettingsMixer1TypeOption[][42];
typedef struct {
	float n;
	float n2;
	float n5;
	float n7;
	float n1;
} UAVT_MixerSettingsThrottleCurve1Type;

typedef struct {
	float n;
	float n2;
	float n5;
	float n7;
	float n1;
} UAVT_MixerSettingsThrottleCurve2Type;

typedef struct {
	float MaxAccel;
	float FeedForward;
	float AccelTime;
	float DecelTime;
	UAVT_MixerSettingsThrottleCurve1Type ThrottleCurve1;	// float[5]
	UAVT_MixerSettingsThrottleCurve2Type ThrottleCurve2;	// float[5]
	uint8_t Curve2Source;	// enum
		// Throttle
		// Roll
		// Pitch
		// Yaw
		// Collective
		// Accessory0
		// Accessory1
		// Accessory2
		// Accessory3
		// Accessory4
		// Accessory5
	uint8_t Mixer1Type;	// enum
		// Disabled
		// Motor
		// Servo
		// CameraRoll
		// CameraPitch
		// CameraYaw
		// Accessory0
		// Accessory1
		// Accessory2
		// Accessory3
		// Accessory4
		// Accessory5
	int8_t Mixer1Vector;
	uint8_t Mixer2Type;
	uint8_t Mixer2Vector;
	uint8_t Mixer3Type;
	uint8_t Mixer3Vector;
	uint8_t Mixer4Type;
	uint8_t Mixer4Vector;
	uint8_t Mixer5Type;
	uint8_t Mixer5Vector;
	uint8_t Mixer6Type;
	uint8_t Mixer6Vector;
	uint8_t Mixer7Type;
	uint8_t Mixer7Vector;
	uint8_t Mixer8Type;
	uint8_t Mixer8Vector;
	uint8_t Mixer9Type;
	uint8_t Mixer9Vector;
	uint8_t Mixer10Type;
	uint8_t Mixer10Vector;
} UAVT_MixerSettingsData;

extern UAVT_MixerSettingsData uavtalk_MixerSettingsData;


/*************************************************************************************************
 Filename: mixerstatus.xml
 Object: MixerStatus
 Comment: Status for the matrix mixer showing the output of each mixer after all scaling
*************************************************************************************************/

#define MIXERSTATUS_OBJID 0x124e28a 

typedef struct {
	float Mixer1;
	float Mixer2;
	float Mixer3;
	float Mixer4;
	float Mixer5;
	float Mixer6;
	float Mixer7;
	float Mixer8;
	float Mixer9;
	float Mixer10;
} UAVT_MixerStatusData;

extern UAVT_MixerStatusData uavtalk_MixerStatusData;


/*************************************************************************************************
 Filename: nedaccel.xml
 Object: NedAccel
 Comment: The projection of acceleration in the NED reference frame used by @ref Guidance.
*************************************************************************************************/

#define NEDACCEL_OBJID 0x7c7f5bc0 

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_NedAccelData;

extern UAVT_NedAccelData uavtalk_NedAccelData;


/*************************************************************************************************
 Filename: objectpersistence.xml
 Object: ObjectPersistence
 Comment: Someone who knows please enter this
*************************************************************************************************/

#define OBJECTPERSISTENCE_OBJID 0x99c63292 

enum {
	OBJECTPERSISTENCE_OPERATION_NOP = 0,
	OBJECTPERSISTENCE_OPERATION_LOAD = 1,
	OBJECTPERSISTENCE_OPERATION_SAVE = 2,
	OBJECTPERSISTENCE_OPERATION_DELETE = 3,
	OBJECTPERSISTENCE_OPERATION_FULLERASE = 4,
	OBJECTPERSISTENCE_OPERATION_COMPLETED = 5,
	OBJECTPERSISTENCE_OPERATION_ERROR = 6,
	OBJECTPERSISTENCE_OPERATION_LASTITEM = 7
};

enum {
	OBJECTPERSISTENCE_SELECTION_SINGLEOBJECT = 0,
	OBJECTPERSISTENCE_SELECTION_ALLSETTINGS = 1,
	OBJECTPERSISTENCE_SELECTION_ALLMETAOBJECTS = 2,
	OBJECTPERSISTENCE_SELECTION_ALLOBJECTS = 3,
	OBJECTPERSISTENCE_SELECTION_LASTITEM = 4
};

extern char UAVT_ObjectPersistenceOperationOption[][42];
extern char UAVT_ObjectPersistenceSelectionOption[][42];
typedef struct {
	uint32_t ObjectID;
	uint32_t InstanceID;
	uint8_t Operation;	// enum
	uint8_t Selection;	// enum
} UAVT_ObjectPersistenceData;

extern UAVT_ObjectPersistenceData uavtalk_ObjectPersistenceData;


/*************************************************************************************************
 Filename: overosyncstats.xml
 Object: OveroSyncStats
 Comment: Maintains statistics on transfer rate to and from over
*************************************************************************************************/

#define OVEROSYNCSTATS_OBJID 0x388468b8 

enum {
	OVEROSYNCSTATS_CONNECTED_FALSE = 0,
	OVEROSYNCSTATS_CONNECTED_TRUE = 1,
	OVEROSYNCSTATS_CONNECTED_LASTITEM = 2
};

extern char UAVT_OveroSyncStatsConnectedOption[][42];
typedef struct {
	uint32_t Send;
	uint32_t Received;
	uint32_t DroppedUpdates;
	uint8_t Connected;	// enum
} UAVT_OveroSyncStatsData;

extern UAVT_OveroSyncStatsData uavtalk_OveroSyncStatsData;


/*************************************************************************************************
 Filename: pathaction.xml
 Object: PathAction
 Comment: A waypoint command the pathplanner is to use at a certain waypoint
*************************************************************************************************/

#define PATHACTION_OBJID 0x34595f1c 

enum {
	PATHACTION_MODE_FLYENDPOINT = 0,
	PATHACTION_MODE_FLYVECTOR = 1,
	PATHACTION_MODE_FLYCIRCLERIGHT = 2,
	PATHACTION_MODE_FLYCIRCLELEFT = 3,
	PATHACTION_MODE_DRIVEENDPOINT = 4,
	PATHACTION_MODE_DRIVEVECTOR = 5,
	PATHACTION_MODE_DRIVECIRCLELEFT = 6,
	PATHACTION_MODE_DRIVECIRCLERIGHT = 7,
	PATHACTION_MODE_FIXEDATTITUDE = 8,
	PATHACTION_MODE_SETACCESSORY = 9,
	PATHACTION_MODE_DISARMALARM = 10,
	PATHACTION_MODE_LASTITEM = 11
};

enum {
	PATHACTION_ENDCONDITION_NONE = 0,
	PATHACTION_ENDCONDITION_TIMEOUT = 1,
	PATHACTION_ENDCONDITION_DISTANCETOTARGET = 2,
	PATHACTION_ENDCONDITION_LEGREMAINING = 3,
	PATHACTION_ENDCONDITION_ABOVEALTITUDE = 4,
	PATHACTION_ENDCONDITION_POINTINGTOWARDSNEXT = 5,
	PATHACTION_ENDCONDITION_PYTHONSCRIPT = 6,
	PATHACTION_ENDCONDITION_IMMEDIATE = 7,
	PATHACTION_ENDCONDITION_LASTITEM = 8
};

enum {
	PATHACTION_COMMAND_ONCONDITIONNEXTWAYPOINT = 0,
	PATHACTION_COMMAND_ONNOTCONDITIONNEXTWAYPOINT = 1,
	PATHACTION_COMMAND_ONCONDITIONJUMPWAYPOINT = 2,
	PATHACTION_COMMAND_ONNOTCONDITIONJUMPWAYPOINT = 3,
	PATHACTION_COMMAND_IFCONDITIONJUMPWAYPOINTELSENEXTWAYPOINT = 4,
	PATHACTION_COMMAND_LASTITEM = 5
};

extern char UAVT_PathActionModeOption[][42];
extern char UAVT_PathActionEndConditionOption[][42];
extern char UAVT_PathActionCommandOption[][42];
typedef struct {
	float ModeParameters[4];
	float ConditionParameters[4];
	uint8_t Mode;	// enum
	uint8_t EndCondition;	// enum
	uint8_t Command;	// enum
	uint8_t JumpDestination;
	uint8_t ErrorDestination;
} UAVT_PathActionData;

extern UAVT_PathActionData uavtalk_PathActionData;


/*************************************************************************************************
 Filename: pipxsettings.xml
 Object: PipXSettings
 Comment: PipXtreme configurations options.
*************************************************************************************************/

#define PIPXSETTINGS_OBJID 0xba192bca 

enum {
	PIPXSETTINGS_TELEMETRYCONFIG_DISABLED = 0,
	PIPXSETTINGS_TELEMETRYCONFIG_SERIAL = 1,
	PIPXSETTINGS_TELEMETRYCONFIG_UAVTALK = 2,
	PIPXSETTINGS_TELEMETRYCONFIG_GCS = 3,
	PIPXSETTINGS_TELEMETRYCONFIG_DEBUG = 4,
	PIPXSETTINGS_TELEMETRYCONFIG_LASTITEM = 5
};

enum {
	PIPXSETTINGS_TELEMETRYSPEED_2400 = 0,
	PIPXSETTINGS_TELEMETRYSPEED_4800 = 1,
	PIPXSETTINGS_TELEMETRYSPEED_9600 = 2,
	PIPXSETTINGS_TELEMETRYSPEED_19200 = 3,
	PIPXSETTINGS_TELEMETRYSPEED_38400 = 4,
	PIPXSETTINGS_TELEMETRYSPEED_57600 = 5,
	PIPXSETTINGS_TELEMETRYSPEED_115200 = 6,
	PIPXSETTINGS_TELEMETRYSPEED_LASTITEM = 7
};

enum {
	PIPXSETTINGS_FLEXICONFIG_DISABLED = 0,
	PIPXSETTINGS_FLEXICONFIG_SERIAL = 1,
	PIPXSETTINGS_FLEXICONFIG_UAVTALK = 2,
	PIPXSETTINGS_FLEXICONFIG_GCS = 3,
	PIPXSETTINGS_FLEXICONFIG_PPM_IN = 4,
	PIPXSETTINGS_FLEXICONFIG_PPM_OUT = 5,
	PIPXSETTINGS_FLEXICONFIG_RSSI = 6,
	PIPXSETTINGS_FLEXICONFIG_DEBUG = 7,
	PIPXSETTINGS_FLEXICONFIG_LASTITEM = 8
};

enum {
	PIPXSETTINGS_FLEXISPEED_2400 = 0,
	PIPXSETTINGS_FLEXISPEED_4800 = 1,
	PIPXSETTINGS_FLEXISPEED_9600 = 2,
	PIPXSETTINGS_FLEXISPEED_19200 = 3,
	PIPXSETTINGS_FLEXISPEED_38400 = 4,
	PIPXSETTINGS_FLEXISPEED_57600 = 5,
	PIPXSETTINGS_FLEXISPEED_115200 = 6,
	PIPXSETTINGS_FLEXISPEED_LASTITEM = 7
};

enum {
	PIPXSETTINGS_VCPCONFIG_DISABLED = 0,
	PIPXSETTINGS_VCPCONFIG_SERIAL = 1,
	PIPXSETTINGS_VCPCONFIG_DEBUG = 2,
	PIPXSETTINGS_VCPCONFIG_LASTITEM = 3
};

enum {
	PIPXSETTINGS_VCPSPEED_2400 = 0,
	PIPXSETTINGS_VCPSPEED_4800 = 1,
	PIPXSETTINGS_VCPSPEED_9600 = 2,
	PIPXSETTINGS_VCPSPEED_19200 = 3,
	PIPXSETTINGS_VCPSPEED_38400 = 4,
	PIPXSETTINGS_VCPSPEED_57600 = 5,
	PIPXSETTINGS_VCPSPEED_115200 = 6,
	PIPXSETTINGS_VCPSPEED_LASTITEM = 7
};

enum {
	PIPXSETTINGS_RFSPEED_2400 = 0,
	PIPXSETTINGS_RFSPEED_4800 = 1,
	PIPXSETTINGS_RFSPEED_9600 = 2,
	PIPXSETTINGS_RFSPEED_19200 = 3,
	PIPXSETTINGS_RFSPEED_38400 = 4,
	PIPXSETTINGS_RFSPEED_57600 = 5,
	PIPXSETTINGS_RFSPEED_115200 = 6,
	PIPXSETTINGS_RFSPEED_LASTITEM = 7
};

enum {
	PIPXSETTINGS_MAXRFPOWER_1_25 = 0,
	PIPXSETTINGS_MAXRFPOWER_1_6 = 1,
	PIPXSETTINGS_MAXRFPOWER_3_16 = 2,
	PIPXSETTINGS_MAXRFPOWER_6_3 = 3,
	PIPXSETTINGS_MAXRFPOWER_12_6 = 4,
	PIPXSETTINGS_MAXRFPOWER_25 = 5,
	PIPXSETTINGS_MAXRFPOWER_50 = 6,
	PIPXSETTINGS_MAXRFPOWER_100 = 7,
	PIPXSETTINGS_MAXRFPOWER_LASTITEM = 8
};

extern char UAVT_PipXSettingsTelemetryConfigOption[][42];
extern char UAVT_PipXSettingsTelemetrySpeedOption[][42];
extern char UAVT_PipXSettingsFlexiConfigOption[][42];
extern char UAVT_PipXSettingsFlexiSpeedOption[][42];
extern char UAVT_PipXSettingsVCPConfigOption[][42];
extern char UAVT_PipXSettingsVCPSpeedOption[][42];
extern char UAVT_PipXSettingsRFSpeedOption[][42];
extern char UAVT_PipXSettingsMaxRFPowerOption[][42];
typedef struct {
	uint32_t PairID;
	uint32_t Frequency;
	uint16_t SendTimeout;
	uint8_t TelemetryConfig;	// enum
	uint8_t TelemetrySpeed;	// enum
	uint8_t FlexiConfig;	// enum
	uint8_t FlexiSpeed;	// enum
	uint8_t VCPConfig;	// enum
	uint8_t VCPSpeed;	// enum
	uint8_t RFSpeed;	// enum
	uint8_t MaxRFPower;	// enum
	uint8_t MinPacketSize;
	uint8_t FrequencyCalibration;
	uint8_t AESKey[32];
} UAVT_PipXSettingsData;

extern UAVT_PipXSettingsData uavtalk_PipXSettingsData;


/*************************************************************************************************
 Filename: pipxstatus.xml
 Object: PipXStatus
 Comment: PipXtreme device status.
*************************************************************************************************/

#define PIPXSTATUS_OBJID 0x3fc68a86 

enum {
	PIPXSTATUS_LINKSTATE_DISCONNECTED = 0,
	PIPXSTATUS_LINKSTATE_CONNECTING = 1,
	PIPXSTATUS_LINKSTATE_CONNECTED = 2,
	PIPXSTATUS_LINKSTATE_LASTITEM = 3
};

extern char UAVT_PipXStatusLinkStateOption[][42];
typedef struct {
	uint32_t MinFrequency;
	uint32_t MaxFrequency;
	float FrequencyStepSize;
	uint32_t DeviceID;
	int32_t AFC;
	uint32_t PairIDs[4];
	uint16_t BoardRevision;
	uint16_t Retries;
	uint16_t Errors;
	uint16_t UAVTalkErrors;
	uint16_t Dropped;
	uint16_t Resets;
	uint16_t TXRate;
	uint16_t RXRate;
	uint8_t Description[40];
	uint8_t CPUSerial[12];
	uint8_t BoardType;
	uint8_t FrequencyBand;
	int8_t RSSI;
	uint8_t LinkState;	// enum
	int8_t PairSignalStrengths[4];
} UAVT_PipXStatusData;

extern UAVT_PipXStatusData uavtalk_PipXStatusData;


/*************************************************************************************************
 Filename: positionactual.xml
 Object: PositionActual
 Comment: Contains the current position relative to @ref HomeLocation
*************************************************************************************************/

#define POSITIONACTUAL_OBJID 0xfa9e2d42 

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_PositionActualData;

extern UAVT_PositionActualData uavtalk_PositionActualData;


/*************************************************************************************************
 Filename: positiondesired.xml
 Object: PositionDesired
 Comment: The position the craft is trying t achieve.  Can come from GCS or @ref PathPlanner 
*************************************************************************************************/

#define POSITIONDESIRED_OBJID 0x778dbe24 

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_PositionDesiredData;

extern UAVT_PositionDesiredData uavtalk_PositionDesiredData;


/*************************************************************************************************
 Filename: ratedesired.xml
 Object: RateDesired
 Comment: Status for the matrix mixer showing the output of each mixer after all scaling
*************************************************************************************************/

#define RATEDESIRED_OBJID 0xce8c826 

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_RateDesiredData;

extern UAVT_RateDesiredData uavtalk_RateDesiredData;


/*************************************************************************************************
 Filename: receiveractivity.xml
 Object: ReceiverActivity
 Comment: Monitors which receiver channels have been active within the last second.
*************************************************************************************************/

#define RECEIVERACTIVITY_OBJID 0x1e7c53da 

enum {
	RECEIVERACTIVITY_ACTIVEGROUP_PWM = 0,
	RECEIVERACTIVITY_ACTIVEGROUP_PPM = 1,
	RECEIVERACTIVITY_ACTIVEGROUP_DSM__MAINPORT_ = 2,
	RECEIVERACTIVITY_ACTIVEGROUP_DSM__FLEXIPORT_ = 3,
	RECEIVERACTIVITY_ACTIVEGROUP_S_BUS = 4,
	RECEIVERACTIVITY_ACTIVEGROUP_GCS = 5,
	RECEIVERACTIVITY_ACTIVEGROUP_NONE = 6,
	RECEIVERACTIVITY_ACTIVEGROUP_LASTITEM = 7
};

extern char UAVT_ReceiverActivityActiveGroupOption[][42];
typedef struct {
	uint8_t ActiveGroup;	// enum
	uint8_t ActiveChannel;
} UAVT_ReceiverActivityData;

extern UAVT_ReceiverActivityData uavtalk_ReceiverActivityData;


/*************************************************************************************************
 Filename: relaytuningsettings.xml
 Object: RelayTuningSettings
 Comment: Setting to run a relay tuning algorithm
*************************************************************************************************/

#define RELAYTUNINGSETTINGS_OBJID 0xea358166 

enum {
	RELAYTUNINGSETTINGS_MODE_RATE = 0,
	RELAYTUNINGSETTINGS_MODE_ATTITUDE = 1,
	RELAYTUNINGSETTINGS_MODE_LASTITEM = 2
};

enum {
	RELAYTUNINGSETTINGS_BEHAVIOR_MEASURE = 0,
	RELAYTUNINGSETTINGS_BEHAVIOR_COMPUTE = 1,
	RELAYTUNINGSETTINGS_BEHAVIOR_SAVE = 2,
	RELAYTUNINGSETTINGS_BEHAVIOR_LASTITEM = 3
};

extern char UAVT_RelayTuningSettingsModeOption[][42];
extern char UAVT_RelayTuningSettingsBehaviorOption[][42];
typedef struct {
	float RateGain;
	float AttitudeGain;
	float Amplitude;
	uint8_t HysteresisThresh;
	uint8_t Mode;	// enum
	uint8_t Behavior;	// enum
} UAVT_RelayTuningSettingsData;

extern UAVT_RelayTuningSettingsData uavtalk_RelayTuningSettingsData;


/*************************************************************************************************
 Filename: relaytuning.xml
 Object: RelayTuning
 Comment: The input to the relay tuning.
*************************************************************************************************/

#define RELAYTUNING_OBJID 0xf6ee61be 

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_RelayTuningPeriodType;

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_RelayTuningGainType;

typedef struct {
	UAVT_RelayTuningPeriodType Period;	// float[3]
	UAVT_RelayTuningGainType Gain;	// float[3]
} UAVT_RelayTuningData;

extern UAVT_RelayTuningData uavtalk_RelayTuningData;


/*************************************************************************************************
 Filename: revocalibration.xml
 Object: RevoCalibration
 Comment: Settings for the INS to control the algorithm and what is updated
*************************************************************************************************/

#define REVOCALIBRATION_OBJID 0xc26d37b2 

enum {
	REVOCALIBRATION_BIASCORRECTEDRAW_TRUE = 0,
	REVOCALIBRATION_BIASCORRECTEDRAW_FALSE = 1,
	REVOCALIBRATION_BIASCORRECTEDRAW_LASTITEM = 2
};

extern char UAVT_RevoCalibrationBiasCorrectedRawOption[][42];
typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationaccel_biasType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationaccel_scaleType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationaccel_varType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationgyro_biasType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationgyro_scaleType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationgyro_varType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationgyro_tempcoeffType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationmag_biasType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationmag_scaleType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_RevoCalibrationmag_varType;

typedef struct {
	UAVT_RevoCalibrationaccel_biasType accel_bias;	// float[3]
	UAVT_RevoCalibrationaccel_scaleType accel_scale;	// float[3]
	UAVT_RevoCalibrationaccel_varType accel_var;	// float[3]
	UAVT_RevoCalibrationgyro_biasType gyro_bias;	// float[3]
	UAVT_RevoCalibrationgyro_scaleType gyro_scale;	// float[3]
	UAVT_RevoCalibrationgyro_varType gyro_var;	// float[3]
	UAVT_RevoCalibrationgyro_tempcoeffType gyro_tempcoeff;	// float[3]
	UAVT_RevoCalibrationmag_biasType mag_bias;	// float[3]
	UAVT_RevoCalibrationmag_scaleType mag_scale;	// float[3]
	UAVT_RevoCalibrationmag_varType mag_var;	// float[3]
	uint8_t BiasCorrectedRaw;	// enum
} UAVT_RevoCalibrationData;

extern UAVT_RevoCalibrationData uavtalk_RevoCalibrationData;


/*************************************************************************************************
 Filename: sonaraltitude.xml
 Object: SonarAltitude
 Comment: The raw data from the ultrasound sonar sensor with altitude estimate.
*************************************************************************************************/

#define SONARALTITUDE_OBJID 0x6c5a0cbc 

typedef struct {
	float Altitude;
} UAVT_SonarAltitudeData;

extern UAVT_SonarAltitudeData uavtalk_SonarAltitudeData;


/*************************************************************************************************
 Filename: stabilizationdesired.xml
 Object: StabilizationDesired
 Comment: The desired attitude that @ref StabilizationModule will try and achieve if FlightMode is Stabilized.  Comes from @ref ManaulControlModule.
*************************************************************************************************/

#define STABILIZATIONDESIRED_OBJID 0x4fdbfeea 

enum {
	STABILIZATIONDESIRED_STABILIZATIONMODE_NONE = 0,
	STABILIZATIONDESIRED_STABILIZATIONMODE_RATE = 1,
	STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE = 2,
	STABILIZATIONDESIRED_STABILIZATIONMODE_AXISLOCK = 3,
	STABILIZATIONDESIRED_STABILIZATIONMODE_WEAKLEVELING = 4,
	STABILIZATIONDESIRED_STABILIZATIONMODE_VIRTUALBAR = 5,
	STABILIZATIONDESIRED_STABILIZATIONMODE_RELAYRATE = 6,
	STABILIZATIONDESIRED_STABILIZATIONMODE_RELAYATTITUDE = 7,
	STABILIZATIONDESIRED_STABILIZATIONMODE_LASTITEM = 8
};

extern char UAVT_StabilizationDesiredStabilizationModeOption[][42];
typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_StabilizationDesiredStabilizationModeType;

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
	float Throttle;
	UAVT_StabilizationDesiredStabilizationModeType StabilizationMode;	// enum[3]
} UAVT_StabilizationDesiredData;

extern UAVT_StabilizationDesiredData uavtalk_StabilizationDesiredData;


/*************************************************************************************************
 Filename: stabilizationsettings.xml
 Object: StabilizationSettings
 Comment: PID settings used by the Stabilization module to combine the @ref AttitudeActual and @ref AttitudeDesired to compute @ref ActuatorDesired
*************************************************************************************************/

#define STABILIZATIONSETTINGS_OBJID 0x58275d66 

enum {
	STABILIZATIONSETTINGS_VBARPIROCOMP_FALSE = 0,
	STABILIZATIONSETTINGS_VBARPIROCOMP_TRUE = 1,
	STABILIZATIONSETTINGS_VBARPIROCOMP_LASTITEM = 2
};

enum {
	STABILIZATIONSETTINGS_LOWTHROTTLEZEROINTEGRAL_FALSE = 0,
	STABILIZATIONSETTINGS_LOWTHROTTLEZEROINTEGRAL_TRUE = 1,
	STABILIZATIONSETTINGS_LOWTHROTTLEZEROINTEGRAL_LASTITEM = 2
};

enum {
	STABILIZATIONSETTINGS_LOWTHROTTLEZEROAXIS_FALSE = 0,
	STABILIZATIONSETTINGS_LOWTHROTTLEZEROAXIS_TRUE = 1,
	STABILIZATIONSETTINGS_LOWTHROTTLEZEROAXIS_LASTITEM = 2
};

extern char UAVT_StabilizationSettingsVbarPiroCompOption[][42];
extern char UAVT_StabilizationSettingsLowThrottleZeroIntegralOption[][42];
extern char UAVT_StabilizationSettingsLowThrottleZeroAxisOption[][42];
typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_StabilizationSettingsManualRateType;

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_StabilizationSettingsMaximumRateType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_StabilizationSettingsRollRatePIDType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_StabilizationSettingsPitchRatePIDType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_StabilizationSettingsYawRatePIDType;

typedef struct {
	float Kp;
	float Ki;
	float ILimit;
} UAVT_StabilizationSettingsRollPIType;

typedef struct {
	float Kp;
	float Ki;
	float ILimit;
} UAVT_StabilizationSettingsPitchPIType;

typedef struct {
	float Kp;
	float Ki;
	float ILimit;
} UAVT_StabilizationSettingsYawPIType;

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_StabilizationSettingsVbarSensitivityType;

typedef struct {
	float Kp;
	float Ki;
} UAVT_StabilizationSettingsVbarRollPIType;

typedef struct {
	float Kp;
	float Ki;
} UAVT_StabilizationSettingsVbarPitchPIType;

typedef struct {
	float Kp;
	float Ki;
} UAVT_StabilizationSettingsVbarYawPIType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_StabilizationSettingsLowThrottleZeroAxisType;

typedef struct {
	UAVT_StabilizationSettingsManualRateType ManualRate;	// float[3]
	UAVT_StabilizationSettingsMaximumRateType MaximumRate;	// float[3]
	UAVT_StabilizationSettingsRollRatePIDType RollRatePID;	// float[4]
	UAVT_StabilizationSettingsPitchRatePIDType PitchRatePID;	// float[4]
	UAVT_StabilizationSettingsYawRatePIDType YawRatePID;	// float[4]
	UAVT_StabilizationSettingsRollPIType RollPI;	// float[3]
	UAVT_StabilizationSettingsPitchPIType PitchPI;	// float[3]
	UAVT_StabilizationSettingsYawPIType YawPI;	// float[3]
	UAVT_StabilizationSettingsVbarSensitivityType VbarSensitivity;	// float[3]
	UAVT_StabilizationSettingsVbarRollPIType VbarRollPI;	// float[2]
	UAVT_StabilizationSettingsVbarPitchPIType VbarPitchPI;	// float[2]
	UAVT_StabilizationSettingsVbarYawPIType VbarYawPI;	// float[2]
	float VbarTau;
	float GyroTau;
	float DerivativeGamma;
	float WeakLevelingKp;
	uint8_t RollMax;
	uint8_t PitchMax;
	uint8_t YawMax;
	int8_t VbarGyroSuppress;
	uint8_t VbarPiroComp;	// enum
	uint8_t VbarMaxAngle;
	uint8_t DerivativeCutoff;
	uint8_t MaxAxisLock;
	uint8_t MaxAxisLockRate;
	uint8_t MaxWeakLevelingRate;
	uint8_t LowThrottleZeroIntegral;	// enum
	UAVT_StabilizationSettingsLowThrottleZeroAxisType LowThrottleZeroAxis;	// enum[3]
} UAVT_StabilizationSettingsData;

extern UAVT_StabilizationSettingsData uavtalk_StabilizationSettingsData;


/*************************************************************************************************
 Filename: systemalarms.xml
 Object: SystemAlarms
 Comment: Alarms from OpenPilot to indicate failure conditions or warnings.  Set by various modules.
*************************************************************************************************/

#define SYSTEMALARMS_OBJID 0x7bd9c77a 

enum {
	SYSTEMALARMS_ALARM_UNINITIALISED = 0,
	SYSTEMALARMS_ALARM_OK = 1,
	SYSTEMALARMS_ALARM_WARNING = 2,
	SYSTEMALARMS_ALARM_ERROR = 3,
	SYSTEMALARMS_ALARM_CRITICAL = 4,
	SYSTEMALARMS_ALARM_LASTITEM = 5
};

extern char UAVT_SystemAlarmsAlarmOption[][42];
typedef struct {
	uint8_t OutOfMemory;
	uint8_t StackOverflow;
	uint8_t CPUOverload;
	uint8_t EventSystem;
	uint8_t Telemetry;
	uint8_t ManualControl;
	uint8_t Actuator;
	uint8_t Attitude;
	uint8_t Sensors;
	uint8_t Stabilization;
	uint8_t Guidance;
	uint8_t Battery;
	uint8_t FlightTime;
	uint8_t I2C;
	uint8_t GPS;
	uint8_t BootFault;
} UAVT_SystemAlarmsAlarmType;

typedef struct {
	UAVT_SystemAlarmsAlarmType Alarm;	// enum[16]
} UAVT_SystemAlarmsData;

extern UAVT_SystemAlarmsData uavtalk_SystemAlarmsData;


/*************************************************************************************************
 Filename: systemsettings.xml
 Object: SystemSettings
 Comment: Select airframe type.  Currently used by @ref ActuatorModule to choose mixing from @ref ActuatorDesired to @ref ActuatorCommand
*************************************************************************************************/

#define SYSTEMSETTINGS_OBJID 0xc72a326e 

enum {
	SYSTEMSETTINGS_AIRFRAMETYPE_FIXEDWING = 0,
	SYSTEMSETTINGS_AIRFRAMETYPE_FIXEDWINGELEVON = 1,
	SYSTEMSETTINGS_AIRFRAMETYPE_FIXEDWINGVTAIL = 2,
	SYSTEMSETTINGS_AIRFRAMETYPE_VTOL = 3,
	SYSTEMSETTINGS_AIRFRAMETYPE_HELICP = 4,
	SYSTEMSETTINGS_AIRFRAMETYPE_QUADX = 5,
	SYSTEMSETTINGS_AIRFRAMETYPE_QUADP = 6,
	SYSTEMSETTINGS_AIRFRAMETYPE_HEXA = 7,
	SYSTEMSETTINGS_AIRFRAMETYPE_OCTO = 8,
	SYSTEMSETTINGS_AIRFRAMETYPE_CUSTOM = 9,
	SYSTEMSETTINGS_AIRFRAMETYPE_HEXAX = 10,
	SYSTEMSETTINGS_AIRFRAMETYPE_OCTOV = 11,
	SYSTEMSETTINGS_AIRFRAMETYPE_OCTOCOAXP = 12,
	SYSTEMSETTINGS_AIRFRAMETYPE_OCTOCOAXX = 13,
	SYSTEMSETTINGS_AIRFRAMETYPE_HEXACOAX = 14,
	SYSTEMSETTINGS_AIRFRAMETYPE_TRI = 15,
	SYSTEMSETTINGS_AIRFRAMETYPE_GROUNDVEHICLECAR = 16,
	SYSTEMSETTINGS_AIRFRAMETYPE_GROUNDVEHICLEDIFFERENTIAL = 17,
	SYSTEMSETTINGS_AIRFRAMETYPE_GROUNDVEHICLEMOTORCYCLE = 18,
	SYSTEMSETTINGS_AIRFRAMETYPE_LASTITEM = 19
};

extern char UAVT_SystemSettingsAirframeTypeOption[][42];
typedef struct {
	uint32_t GUIConfigData[4];
	uint8_t AirframeType;	// enum
} UAVT_SystemSettingsData;

extern UAVT_SystemSettingsData uavtalk_SystemSettingsData;


/*************************************************************************************************
 Filename: systemstats.xml
 Object: SystemStats
 Comment: CPU and memory usage from OpenPilot computer. 
*************************************************************************************************/

#define SYSTEMSTATS_OBJID 0x364d1406 

typedef struct {
	uint32_t FlightTime;
	uint32_t EventSystemWarningID;
	uint32_t ObjectManagerCallbackID;
	uint32_t ObjectManagerQueueID;
	uint16_t HeapRemaining;
	uint16_t IRQStackRemaining;
	uint8_t CPULoad;
	int8_t CPUTemp;
} UAVT_SystemStatsData;

extern UAVT_SystemStatsData uavtalk_SystemStatsData;


/*************************************************************************************************
 Filename: taskinfo.xml
 Object: TaskInfo
 Comment: Task information
*************************************************************************************************/

#define TASKINFO_OBJID 0x16e66f76 

extern char UAVT_TaskInfoRunningOption[][42];
typedef struct {
	uint16_t StackRemaining;
	uint8_t Running;	// enum
		// False
		// True
	uint8_t RunningTime;
} UAVT_TaskInfoData;

extern UAVT_TaskInfoData uavtalk_TaskInfoData;


/*************************************************************************************************
 Filename: txpidsettings.xml
 Object: TxPIDSettings
 Comment: Settings used by @ref TxPID optional module to tune PID settings using R/C transmitter
*************************************************************************************************/

#define TXPIDSETTINGS_OBJID 0x42b2d2ae 

enum {
	TXPIDSETTINGS_UPDATEMODE_NEVER = 0,
	TXPIDSETTINGS_UPDATEMODE_WHEN_ARMED = 1,
	TXPIDSETTINGS_UPDATEMODE_ALWAYS = 2,
	TXPIDSETTINGS_UPDATEMODE_LASTITEM = 3
};

enum {
	TXPIDSETTINGS_INPUTS_THROTTLE = 0,
	TXPIDSETTINGS_INPUTS_ACCESSORY0 = 1,
	TXPIDSETTINGS_INPUTS_ACCESSORY1 = 2,
	TXPIDSETTINGS_INPUTS_ACCESSORY2 = 3,
	TXPIDSETTINGS_INPUTS_ACCESSORY3 = 4,
	TXPIDSETTINGS_INPUTS_ACCESSORY4 = 5,
	TXPIDSETTINGS_INPUTS_ACCESSORY5 = 6,
	TXPIDSETTINGS_INPUTS_LASTITEM = 7
};

enum {
	TXPIDSETTINGS_PIDS_DISABLED = 0,
	TXPIDSETTINGS_PIDS_ROLL_RATE_KP = 1,
	TXPIDSETTINGS_PIDS_PITCH_RATE_KP = 2,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_RATE_KP = 3,
	TXPIDSETTINGS_PIDS_YAW_RATE_KP = 4,
	TXPIDSETTINGS_PIDS_ROLL_RATE_KI = 5,
	TXPIDSETTINGS_PIDS_PITCH_RATE_KI = 6,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_RATE_KI = 7,
	TXPIDSETTINGS_PIDS_YAW_RATE_KI = 8,
	TXPIDSETTINGS_PIDS_ROLL_RATE_KD = 9,
	TXPIDSETTINGS_PIDS_PITCH_RATE_KD = 10,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_RATE_KD = 11,
	TXPIDSETTINGS_PIDS_YAW_RATE_KD = 12,
	TXPIDSETTINGS_PIDS_ROLL_RATE_ILIMIT = 13,
	TXPIDSETTINGS_PIDS_PITCH_RATE_ILIMIT = 14,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_RATE_ILIMIT = 15,
	TXPIDSETTINGS_PIDS_YAW_RATE_ILIMIT = 16,
	TXPIDSETTINGS_PIDS_ROLL_ATTITUDE_KP = 17,
	TXPIDSETTINGS_PIDS_PITCH_ATTITUDE_KP = 18,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_ATTITUDE_KP = 19,
	TXPIDSETTINGS_PIDS_YAW_ATTITUDE_KP = 20,
	TXPIDSETTINGS_PIDS_ROLL_ATTITUDE_KI = 21,
	TXPIDSETTINGS_PIDS_PITCH_ATTITUDE_KI = 22,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_ATTITUDE_KI = 23,
	TXPIDSETTINGS_PIDS_YAW_ATTITUDE_KI = 24,
	TXPIDSETTINGS_PIDS_ROLL_ATTITUDE_ILIMIT = 25,
	TXPIDSETTINGS_PIDS_PITCH_ATTITUDE_ILIMIT = 26,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_ATTITUDE_ILIMIT = 27,
	TXPIDSETTINGS_PIDS_YAW_ATTITUDE_ILIMIT = 28,
	TXPIDSETTINGS_PIDS_GYROTAU = 29,
	TXPIDSETTINGS_PIDS_LASTITEM = 30
};

extern char UAVT_TxPIDSettingsUpdateModeOption[][42];
extern char UAVT_TxPIDSettingsInputsOption[][42];
extern char UAVT_TxPIDSettingsPIDsOption[][42];
typedef struct {
	float Instance1;
	float Instance2;
	float Instance3;
} UAVT_TxPIDSettingsMinPIDType;

typedef struct {
	float Instance1;
	float Instance2;
	float Instance3;
} UAVT_TxPIDSettingsMaxPIDType;

typedef struct {
	uint8_t Instance1;
	uint8_t Instance2;
	uint8_t Instance3;
} UAVT_TxPIDSettingsInputsType;

typedef struct {
	uint8_t Instance1;
	uint8_t Instance2;
	uint8_t Instance3;
} UAVT_TxPIDSettingsPIDsType;

typedef struct {
	float ThrottleRange[2];
	UAVT_TxPIDSettingsMinPIDType MinPID;	// float[3]
	UAVT_TxPIDSettingsMaxPIDType MaxPID;	// float[3]
	uint8_t UpdateMode;	// enum
	UAVT_TxPIDSettingsInputsType Inputs;	// enum[3]
	UAVT_TxPIDSettingsPIDsType PIDs;	// enum[3]
} UAVT_TxPIDSettingsData;

extern UAVT_TxPIDSettingsData uavtalk_TxPIDSettingsData;


/*************************************************************************************************
 Filename: velocityactual.xml
 Object: VelocityActual
 Comment: Updated by @ref AHRSCommsModule and used within @ref GuidanceModule for velocity control
*************************************************************************************************/

#define VELOCITYACTUAL_OBJID 0x5a08f61a 

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_VelocityActualData;

extern UAVT_VelocityActualData uavtalk_VelocityActualData;


/*************************************************************************************************
 Filename: velocitydesired.xml
 Object: VelocityDesired
 Comment: Used within @ref GuidanceModule to communicate between the task computing the desired velocity and the PID loop to achieve it (running at different rates).
*************************************************************************************************/

#define VELOCITYDESIRED_OBJID 0x9e946992 

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_VelocityDesiredData;

extern UAVT_VelocityDesiredData uavtalk_VelocityDesiredData;


/*************************************************************************************************
 Filename: watchdogstatus.xml
 Object: WatchdogStatus
 Comment: For monitoring the flags in the watchdog and especially the bootup flags
*************************************************************************************************/

#define WATCHDOGSTATUS_OBJID 0xa207fa7c 

typedef struct {
	uint16_t BootupFlags;
	uint16_t ActiveFlags;
} UAVT_WatchdogStatusData;

extern UAVT_WatchdogStatusData uavtalk_WatchdogStatusData;


/*************************************************************************************************
 Filename: waypointactive.xml
 Object: WaypointActive
 Comment: Indicates the currently active waypoint
*************************************************************************************************/

#define WAYPOINTACTIVE_OBJID 0x1ea5b192 

typedef struct {
	uint8_t Index;
} UAVT_WaypointActiveData;

extern UAVT_WaypointActiveData uavtalk_WaypointActiveData;


/*************************************************************************************************
 Filename: waypoint.xml
 Object: Waypoint
 Comment: A waypoint the aircraft can try and hit.  Used by the @ref PathPlanner module
*************************************************************************************************/

#define WAYPOINT_OBJID 0xd23852dc 

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_WaypointPositionType;

typedef struct {
	UAVT_WaypointPositionType Position;	// float[3]
	float Velocity;
	uint8_t Action;
} UAVT_WaypointData;

extern UAVT_WaypointData uavtalk_WaypointData;

