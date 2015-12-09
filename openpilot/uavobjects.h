
/*************************************************************************************************
    Filename: acceldesired.xml
    Object: AccelDesired
    Comment: The desired acceleration from navigation
*************************************************************************************************/

#define ACCELDESIRED_OBJID 0x3b7c5b62

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_AccelDesiredData;

extern UAVT_AccelDesiredData uavtalk_AccelDesiredData;


/*************************************************************************************************
    Filename: accels.xml
    Object: Accels
    Comment: The accelerometer sensor data, rotated into body frame.
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

#define ACTUATORSETTINGS_OBJID 0xa3c64272

enum {
	ACTUATORSETTINGS_CHANNELTYPE_PWM = 0,
	ACTUATORSETTINGS_CHANNELTYPE_MK = 1,
	ACTUATORSETTINGS_CHANNELTYPE_ASTEC4 = 2,
	ACTUATORSETTINGS_CHANNELTYPE_PWM_ALARM_BUZZER = 3,
	ACTUATORSETTINGS_CHANNELTYPE_ARMING_LED = 4,
	ACTUATORSETTINGS_CHANNELTYPE_INFO_LED = 5,
	ACTUATORSETTINGS_CHANNELTYPE_LASTITEM = 6
};

enum {
	ACTUATORSETTINGS_MOTORSSPINWHILEARMED_FALSE = 0,
	ACTUATORSETTINGS_MOTORSSPINWHILEARMED_TRUE = 1,
	ACTUATORSETTINGS_MOTORSSPINWHILEARMED_LASTITEM = 2
};

extern char UAVT_ActuatorSettingsChannelTypeOption[][42];
extern char UAVT_ActuatorSettingsMotorsSpinWhileArmedOption[][42];
typedef struct {
	uint16_t ChannelUpdateFreq[6];
	int16_t ChannelMax[10];
	int16_t ChannelNeutral[10];
	int16_t ChannelMin[10];
	uint8_t ChannelType[10];	// enum
	uint8_t ChannelAddr[10];
	uint8_t MotorsSpinWhileArmed;	// enum
} UAVT_ActuatorSettingsData;

extern UAVT_ActuatorSettingsData uavtalk_ActuatorSettingsData;


/*************************************************************************************************
    Filename: airspeedactual.xml
    Object: AirspeedActual
    Comment: UAVO for true airspeed, calibrated airspeed, angle of attack, and angle of slip
*************************************************************************************************/

#define AIRSPEEDACTUAL_OBJID 0x133a3280

typedef struct {
	float TrueAirspeed;
	float CalibratedAirspeed;
	float alpha;
	float beta;
} UAVT_AirspeedActualData;

extern UAVT_AirspeedActualData uavtalk_AirspeedActualData;


/*************************************************************************************************
    Filename: airspeedsettings.xml
    Object: AirspeedSettings
    Comment: Settings for the @ref BaroAirspeed module used on CopterControl or Revolution
*************************************************************************************************/

#define AIRSPEEDSETTINGS_OBJID 0x63f679c

enum {
	AIRSPEEDSETTINGS_AIRSPEEDSENSORTYPE_EAGLETREEAIRSPEEDV3 = 0,
	AIRSPEEDSETTINGS_AIRSPEEDSENSORTYPE_DIYDRONESMPXV5004 = 1,
	AIRSPEEDSETTINGS_AIRSPEEDSENSORTYPE_DIYDRONESMPXV7002 = 2,
	AIRSPEEDSETTINGS_AIRSPEEDSENSORTYPE_GPSONLY = 3,
	AIRSPEEDSETTINGS_AIRSPEEDSENSORTYPE_LASTITEM = 4
};

enum {
	AIRSPEEDSETTINGS_ANALOGPIN_ADC0 = 0,
	AIRSPEEDSETTINGS_ANALOGPIN_ADC1 = 1,
	AIRSPEEDSETTINGS_ANALOGPIN_ADC2 = 2,
	AIRSPEEDSETTINGS_ANALOGPIN_ADC3 = 3,
	AIRSPEEDSETTINGS_ANALOGPIN_ADC4 = 4,
	AIRSPEEDSETTINGS_ANALOGPIN_ADC5 = 5,
	AIRSPEEDSETTINGS_ANALOGPIN_ADC6 = 6,
	AIRSPEEDSETTINGS_ANALOGPIN_ADC7 = 7,
	AIRSPEEDSETTINGS_ANALOGPIN_ADC8 = 8,
	AIRSPEEDSETTINGS_ANALOGPIN_NONE = 9,
	AIRSPEEDSETTINGS_ANALOGPIN_LASTITEM = 10
};

extern char UAVT_AirspeedSettingsAirspeedSensorTypeOption[][42];
extern char UAVT_AirspeedSettingsAnalogPinOption[][42];
typedef struct {
	float Scale;
	uint16_t ZeroPoint;
	uint8_t GPSSamplePeriod_ms;
	uint8_t AirspeedSensorType;	// enum
	uint8_t AnalogPin;	// enum
} UAVT_AirspeedSettingsData;

extern UAVT_AirspeedSettingsData uavtalk_AirspeedSettingsData;


/*************************************************************************************************
    Filename: altitudeholddesired.xml
    Object: AltitudeHoldDesired
    Comment: Holds the desired altitude (from manual control) as well as the desired attitude to pass through
*************************************************************************************************/

#define ALTITUDEHOLDDESIRED_OBJID 0xe7b9c87a

enum {
	ALTITUDEHOLDDESIRED_LAND_FALSE = 0,
	ALTITUDEHOLDDESIRED_LAND_TRUE = 1,
	ALTITUDEHOLDDESIRED_LAND_LASTITEM = 2
};

extern char UAVT_AltitudeHoldDesiredLandOption[][42];
typedef struct {
	float Altitude;
	float ClimbRate;
	float Roll;
	float Pitch;
	float Yaw;
	uint8_t Land;	// enum
} UAVT_AltitudeHoldDesiredData;

extern UAVT_AltitudeHoldDesiredData uavtalk_AltitudeHoldDesiredData;


/*************************************************************************************************
    Filename: altitudeholdsettings.xml
    Object: AltitudeHoldSettings
    Comment: Settings for the @ref AltitudeHold module
*************************************************************************************************/

#define ALTITUDEHOLDSETTINGS_OBJID 0x93e52e4c

typedef struct {
	float PositionKp;
	float VelocityKp;
	float VelocityKi;
	uint16_t AttitudeComp;
	uint8_t MaxRate;
	uint8_t Expo;
	uint8_t Deadband;
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

#define ATTITUDESETTINGS_OBJID 0x2257cf36

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
	ATTITUDESETTINGS_FILTERCHOICE_CCC = 0,
	ATTITUDESETTINGS_FILTERCHOICE_PREMERLANI = 1,
	ATTITUDESETTINGS_FILTERCHOICE_PREMERLANI_GPS = 2,
	ATTITUDESETTINGS_FILTERCHOICE_LASTITEM = 3
};

enum {
	ATTITUDESETTINGS_TRIMFLIGHT_NORMAL = 0,
	ATTITUDESETTINGS_TRIMFLIGHT_START = 1,
	ATTITUDESETTINGS_TRIMFLIGHT_LOAD = 2,
	ATTITUDESETTINGS_TRIMFLIGHT_LASTITEM = 3
};

extern char UAVT_AttitudeSettingsZeroDuringArmingOption[][42];
extern char UAVT_AttitudeSettingsBiasCorrectGyroOption[][42];
extern char UAVT_AttitudeSettingsFilterChoiceOption[][42];
extern char UAVT_AttitudeSettingsTrimFlightOption[][42];
typedef struct {
	int16_t Roll;
	int16_t Pitch;
	int16_t Yaw;
} UAVT_AttitudeSettingsBoardRotationType;

typedef struct {
	float MagKp;
	float MagKi;
	float AccelKp;
	float AccelKi;
	float AccelTau;
	float VertPositionTau;
	float YawBiasRate;
	UAVT_AttitudeSettingsBoardRotationType BoardRotation;	// int16[3]
	uint8_t ZeroDuringArming;	// enum
	uint8_t BiasCorrectGyro;	// enum
	uint8_t FilterChoice;	// enum
	uint8_t TrimFlight;	// enum
} UAVT_AttitudeSettingsData;

extern UAVT_AttitudeSettingsData uavtalk_AttitudeSettingsData;


/*************************************************************************************************
    Filename: attitudesimulated.xml
    Object: AttitudeSimulated
    Comment: The simulated Attitude estimation from @ref Sensors.
*************************************************************************************************/

#define ATTITUDESIMULATED_OBJID 0x9266ce74

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_AttitudeSimulatedVelocityType;

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_AttitudeSimulatedPositionType;

typedef struct {
	float q1;
	float q2;
	float q3;
	float q4;
	float Roll;
	float Pitch;
	float Yaw;
	UAVT_AttitudeSimulatedVelocityType Velocity;	// float[3]
	UAVT_AttitudeSimulatedPositionType Position;	// float[3]
} UAVT_AttitudeSimulatedData;

extern UAVT_AttitudeSimulatedData uavtalk_AttitudeSimulatedData;


/*************************************************************************************************
    Filename: baroairspeed.xml
    Object: BaroAirspeed
    Comment: The raw data from the dynamic pressure sensor with pressure, temperature and airspeed.
*************************************************************************************************/

#define BAROAIRSPEED_OBJID 0x10d6bd7c

enum {
	BAROAIRSPEED_BAROCONNECTED_FALSE = 0,
	BAROAIRSPEED_BAROCONNECTED_TRUE = 1,
	BAROAIRSPEED_BAROCONNECTED_LASTITEM = 2
};

extern char UAVT_BaroAirspeedBaroConnectedOption[][42];
typedef struct {
	float CalibratedAirspeed;
	float GPSAirspeed;
	float TrueAirspeed;
	uint16_t SensorValue;
	uint8_t BaroConnected;	// enum
} UAVT_BaroAirspeedData;

extern UAVT_BaroAirspeedData uavtalk_BaroAirspeedData;


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
    Filename: brushlessgimbalsettings.xml
    Object: BrushlessGimbalSettings
    Comment: Settings for the @ref BrushlessGimbal module
*************************************************************************************************/

#define BRUSHLESSGIMBALSETTINGS_OBJID 0xb50ddc74

enum {
	BRUSHLESSGIMBALSETTINGS_POWERUPSEQUENCE_FALSE = 0,
	BRUSHLESSGIMBALSETTINGS_POWERUPSEQUENCE_TRUE = 1,
	BRUSHLESSGIMBALSETTINGS_POWERUPSEQUENCE_LASTITEM = 2
};

extern char UAVT_BrushlessGimbalSettingsPowerupSequenceOption[][42];
typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_BrushlessGimbalSettingsDampingType;

typedef struct {
	uint16_t Roll;
	uint16_t Pitch;
	uint16_t Yaw;
} UAVT_BrushlessGimbalSettingsMaxDPSType;

typedef struct {
	uint16_t Roll;
	uint16_t Pitch;
	uint16_t Yaw;
} UAVT_BrushlessGimbalSettingsSlewLimitType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_BrushlessGimbalSettingsPowerScaleType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_BrushlessGimbalSettingsMaxAngleType;

typedef struct {
	UAVT_BrushlessGimbalSettingsDampingType Damping;	// float[3]
	UAVT_BrushlessGimbalSettingsMaxDPSType MaxDPS;	// uint16[3]
	UAVT_BrushlessGimbalSettingsSlewLimitType SlewLimit;	// uint16[3]
	UAVT_BrushlessGimbalSettingsPowerScaleType PowerScale;	// uint8[3]
	UAVT_BrushlessGimbalSettingsMaxAngleType MaxAngle;	// uint8[3]
	uint8_t RollFraction;
	uint8_t PowerupSequence;	// enum
} UAVT_BrushlessGimbalSettingsData;

extern UAVT_BrushlessGimbalSettingsData uavtalk_BrushlessGimbalSettingsData;


/*************************************************************************************************
    Filename: cameradesired.xml
    Object: CameraDesired
    Comment: Desired camera outputs.  Comes from @ref CameraStabilization module.
*************************************************************************************************/

#define CAMERADESIRED_OBJID 0x4622ec88

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
	float Bearing;
	float Declination;
} UAVT_CameraDesiredData;

extern UAVT_CameraDesiredData uavtalk_CameraDesiredData;


/*************************************************************************************************
    Filename: camerastabsettings.xml
    Object: CameraStabSettings
    Comment: Settings for the @ref CameraStab mmodule
*************************************************************************************************/

#define CAMERASTABSETTINGS_OBJID 0xfa09a51a

enum {
	CAMERASTABSETTINGS_INPUT_ACCESSORY0 = 0,
	CAMERASTABSETTINGS_INPUT_ACCESSORY1 = 1,
	CAMERASTABSETTINGS_INPUT_ACCESSORY2 = 2,
	CAMERASTABSETTINGS_INPUT_ACCESSORY3 = 3,
	CAMERASTABSETTINGS_INPUT_ACCESSORY4 = 4,
	CAMERASTABSETTINGS_INPUT_ACCESSORY5 = 5,
	CAMERASTABSETTINGS_INPUT_POI = 6,
	CAMERASTABSETTINGS_INPUT_NONE = 7,
	CAMERASTABSETTINGS_INPUT_LASTITEM = 8
};

enum {
	CAMERASTABSETTINGS_STABILIZATIONMODE_ATTITUDE = 0,
	CAMERASTABSETTINGS_STABILIZATIONMODE_AXISLOCK = 1,
	CAMERASTABSETTINGS_STABILIZATIONMODE_LASTITEM = 2
};

extern char UAVT_CameraStabSettingsInputOption[][42];
extern char UAVT_CameraStabSettingsStabilizationModeOption[][42];
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
} UAVT_CameraStabSettingsOutputRangeType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_CameraStabSettingsFeedForwardType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_CameraStabSettingsStabilizationModeType;

typedef struct {
	float MaxAxisLockRate;
	float MaxAccel;
	UAVT_CameraStabSettingsInputType Input;	// enum[3]
	UAVT_CameraStabSettingsInputRangeType InputRange;	// uint8[3]
	UAVT_CameraStabSettingsInputRateType InputRate;	// uint8[3]
	UAVT_CameraStabSettingsOutputRangeType OutputRange;	// uint8[3]
	UAVT_CameraStabSettingsFeedForwardType FeedForward;	// uint8[3]
	UAVT_CameraStabSettingsStabilizationModeType StabilizationMode;	// enum[3]
	uint8_t AttitudeFilter;
	uint8_t InputFilter;
	uint8_t FeedForwardTime;
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
    Filename: fixedwingairspeeds.xml
    Object: FixedWingAirspeeds
    Comment: Settings for the @ref FixedWingPathFollowerModule
*************************************************************************************************/

#define FIXEDWINGAIRSPEEDS_OBJID 0x3fcf7f6

typedef struct {
	float AirSpeedMax;
	float CruiseSpeed;
	float BestClimbRateSpeed;
	float StallSpeedClean;
	float StallSpeedDirty;
	float VerticalVelMax;
} UAVT_FixedWingAirspeedsData;

extern UAVT_FixedWingAirspeedsData uavtalk_FixedWingAirspeedsData;


/*************************************************************************************************
    Filename: fixedwingpathfollowersettingscc.xml
    Object: FixedWingPathFollowerSettingsCC
    Comment: Settings for the @ref FixedWingPathFollowerModule
*************************************************************************************************/

#define FIXEDWINGPATHFOLLOWERSETTINGSCC_OBJID 0xc4623504

typedef struct {
	float Kp;
	float Max;
} UAVT_FixedWingPathFollowerSettingsCCVerticalToPitchCrossFeedType;

typedef struct {
	float Kp;
	float Max;
} UAVT_FixedWingPathFollowerSettingsCCAirspeedToVerticalCrossFeedType;

typedef struct {
	float VerticalVelMax;
	float VectorFollowingGain;
	float OrbitFollowingGain;
	float FollowerIntegralGain;
	float VerticalPosP;
	float HeadingPI[3];
	float AirspeedPI[3];
	UAVT_FixedWingPathFollowerSettingsCCVerticalToPitchCrossFeedType VerticalToPitchCrossFeed;	// float[2]
	UAVT_FixedWingPathFollowerSettingsCCAirspeedToVerticalCrossFeedType AirspeedToVerticalCrossFeed;	// float[2]
	float ThrottlePI[3];
	float RollLimit[3];
	float PitchLimit[3];
	float ThrottleLimit[3];
	int16_t UpdatePeriod;
} UAVT_FixedWingPathFollowerSettingsCCData;

extern UAVT_FixedWingPathFollowerSettingsCCData uavtalk_FixedWingPathFollowerSettingsCCData;


/*************************************************************************************************
    Filename: fixedwingpathfollowersettings.xml
    Object: FixedWingPathFollowerSettings
    Comment: Settings for the @ref FixedWingPathFollowerModule
*************************************************************************************************/

#define FIXEDWINGPATHFOLLOWERSETTINGS_OBJID 0x56c316da

typedef struct {
	float Kp;
	float Max;
} UAVT_FixedWingPathFollowerSettingsVerticalToPitchCrossFeedType;

typedef struct {
	float Kp;
	float Max;
} UAVT_FixedWingPathFollowerSettingsAirspeedToVerticalCrossFeedType;

typedef struct {
	float HorizontalPosP;
	float VerticalPosP;
	float BearingPI[3];
	float PowerPI[3];
	UAVT_FixedWingPathFollowerSettingsVerticalToPitchCrossFeedType VerticalToPitchCrossFeed;	// float[2]
	UAVT_FixedWingPathFollowerSettingsAirspeedToVerticalCrossFeedType AirspeedToVerticalCrossFeed;	// float[2]
	float SpeedPI[3];
	float RollLimit[3];
	float PitchLimit[3];
	float ThrottleLimit[3];
	float OrbitRadius;
	int16_t UpdatePeriod;
} UAVT_FixedWingPathFollowerSettingsData;

extern UAVT_FixedWingPathFollowerSettingsData uavtalk_FixedWingPathFollowerSettingsData;


/*************************************************************************************************
    Filename: fixedwingpathfollowerstatus.xml
    Object: FixedWingPathFollowerStatus
    Comment: Object Storing Debugging Information on PID internals
*************************************************************************************************/

#define FIXEDWINGPATHFOLLOWERSTATUS_OBJID 0xaca80808

typedef struct {
	float Bearing;
	float Speed;
	float Accel;
	float Power;
} UAVT_FixedWingPathFollowerStatusErrorType;

typedef struct {
	float Bearing;
	float Speed;
	float Accel;
	float Power;
} UAVT_FixedWingPathFollowerStatusErrorIntType;

typedef struct {
	float Bearing;
	float Speed;
	float Accel;
	float Power;
} UAVT_FixedWingPathFollowerStatusCommandType;

typedef struct {
	uint8_t Wind;
	uint8_t Stallspeed;
	uint8_t Lowspeed;
	uint8_t Highspeed;
	uint8_t Overspeed;
	uint8_t Lowpower;
	uint8_t Highpower;
	uint8_t Pitchcontrol;
} UAVT_FixedWingPathFollowerStatusErrorsType;

typedef struct {
	UAVT_FixedWingPathFollowerStatusErrorType Error;	// float[4]
	UAVT_FixedWingPathFollowerStatusErrorIntType ErrorInt;	// float[4]
	UAVT_FixedWingPathFollowerStatusCommandType Command;	// float[4]
	UAVT_FixedWingPathFollowerStatusErrorsType Errors;	// uint8[8]
} UAVT_FixedWingPathFollowerStatusData;

extern UAVT_FixedWingPathFollowerStatusData uavtalk_FixedWingPathFollowerStatusData;


/*************************************************************************************************
    Filename: flightbatterysettings.xml
    Object: FlightBatterySettings
    Comment: Flight Battery configuration.
*************************************************************************************************/

#define FLIGHTBATTERYSETTINGS_OBJID 0x94474ece

enum {
	FLIGHTBATTERYSETTINGS_CURRENTPIN_ADC0 = 0,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_ADC1 = 1,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_ADC2 = 2,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_ADC3 = 3,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_ADC4 = 4,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_ADC5 = 5,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_ADC6 = 6,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_ADC7 = 7,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_ADC8 = 8,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_NONE = 9,
	FLIGHTBATTERYSETTINGS_CURRENTPIN_LASTITEM = 10
};

enum {
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_ADC0 = 0,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_ADC1 = 1,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_ADC2 = 2,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_ADC3 = 3,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_ADC4 = 4,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_ADC5 = 5,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_ADC6 = 6,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_ADC7 = 7,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_ADC8 = 8,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_NONE = 9,
	FLIGHTBATTERYSETTINGS_VOLTAGEPIN_LASTITEM = 10
};

enum {
	FLIGHTBATTERYSETTINGS_TYPE_LIPO = 0,
	FLIGHTBATTERYSETTINGS_TYPE_A123 = 1,
	FLIGHTBATTERYSETTINGS_TYPE_LICO = 2,
	FLIGHTBATTERYSETTINGS_TYPE_LIFESO4 = 3,
	FLIGHTBATTERYSETTINGS_TYPE_NONE = 4,
	FLIGHTBATTERYSETTINGS_TYPE_LASTITEM = 5
};

enum {
	FLIGHTBATTERYSETTINGS_SENSORTYPE_DISABLED = 0,
	FLIGHTBATTERYSETTINGS_SENSORTYPE_ENABLED = 1,
	FLIGHTBATTERYSETTINGS_SENSORTYPE_LASTITEM = 2
};

extern char UAVT_FlightBatterySettingsCurrentPinOption[][42];
extern char UAVT_FlightBatterySettingsVoltagePinOption[][42];
extern char UAVT_FlightBatterySettingsTypeOption[][42];
extern char UAVT_FlightBatterySettingsSensorTypeOption[][42];
typedef struct {
	float Warning;
	float Alarm;
} UAVT_FlightBatterySettingsVoltageThresholdsType;

typedef struct {
	float Voltage;
	float Current;
} UAVT_FlightBatterySettingsSensorCalibrationFactorType;

typedef struct {
	float Voltage;
	float Current;
} UAVT_FlightBatterySettingsSensorCalibrationOffsetType;

typedef struct {
	uint8_t BatteryCurrent;
	uint8_t BatteryVoltage;
} UAVT_FlightBatterySettingsSensorTypeType;

typedef struct {
	uint32_t Capacity;
	UAVT_FlightBatterySettingsVoltageThresholdsType VoltageThresholds;	// float[2]
	UAVT_FlightBatterySettingsSensorCalibrationFactorType SensorCalibrationFactor;	// float[2]
	UAVT_FlightBatterySettingsSensorCalibrationOffsetType SensorCalibrationOffset;	// float[2]
	uint8_t CurrentPin;	// enum
	uint8_t VoltagePin;	// enum
	uint8_t Type;	// enum
	uint8_t NbCells;
	UAVT_FlightBatterySettingsSensorTypeType SensorType;	// enum[2]
} UAVT_FlightBatterySettingsData;

extern UAVT_FlightBatterySettingsData uavtalk_FlightBatterySettingsData;


/*************************************************************************************************
    Filename: flightbatterystate.xml
    Object: FlightBatteryState
    Comment: Battery status information.
*************************************************************************************************/

#define FLIGHTBATTERYSTATE_OBJID 0xd2083596

typedef struct {
	float Voltage;
	float Current;
	float BoardSupplyVoltage;
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

#define FLIGHTPLANSTATUS_OBJID 0x3391ec96

enum {
	FLIGHTPLANSTATUS_STATE_STOPPED = 0,
	FLIGHTPLANSTATUS_STATE_RUNNING = 1,
	FLIGHTPLANSTATUS_STATE_ERROR = 2,
	FLIGHTPLANSTATUS_STATE_LASTITEM = 3
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

extern char UAVT_FlightPlanStatusStateOption[][42];
extern char UAVT_FlightPlanStatusErrorTypeOption[][42];
typedef struct {
	uint32_t ErrorFileID;
	uint32_t ErrorLineNum;
	float Debug[2];
	uint8_t State;	// enum
	uint8_t ErrorType;	// enum
} UAVT_FlightPlanStatusData;

extern UAVT_FlightPlanStatusData uavtalk_FlightPlanStatusData;


/*************************************************************************************************
    Filename: flightstatus.xml
    Object: FlightStatus
    Comment: Contains major flight status information for other modules.
*************************************************************************************************/

#define FLIGHTSTATUS_OBJID 0xc2e431ba

enum {
	FLIGHTSTATUS_ARMED_DISARMED = 0,
	FLIGHTSTATUS_ARMED_ARMING = 1,
	FLIGHTSTATUS_ARMED_ARMED = 2,
	FLIGHTSTATUS_ARMED_LASTITEM = 3
};

enum {
	FLIGHTSTATUS_FLIGHTMODE_MANUAL = 0,
	FLIGHTSTATUS_FLIGHTMODE_ACRO = 1,
	FLIGHTSTATUS_FLIGHTMODE_LEVELING = 2,
	FLIGHTSTATUS_FLIGHTMODE_VIRTUALBAR = 3,
	FLIGHTSTATUS_FLIGHTMODE_STABILIZED1 = 4,
	FLIGHTSTATUS_FLIGHTMODE_STABILIZED2 = 5,
	FLIGHTSTATUS_FLIGHTMODE_STABILIZED3 = 6,
	FLIGHTSTATUS_FLIGHTMODE_AUTOTUNE = 7,
	FLIGHTSTATUS_FLIGHTMODE_ALTITUDEHOLD = 8,
	FLIGHTSTATUS_FLIGHTMODE_VELOCITYCONTROL = 9,
	FLIGHTSTATUS_FLIGHTMODE_POSITIONHOLD = 10,
	FLIGHTSTATUS_FLIGHTMODE_RETURNTOHOME = 11,
	FLIGHTSTATUS_FLIGHTMODE_PATHPLANNER = 12,
	FLIGHTSTATUS_FLIGHTMODE_TABLETCONTROL = 13,
	FLIGHTSTATUS_FLIGHTMODE_LASTITEM = 14
};

enum {
	FLIGHTSTATUS_CONTROLSOURCE_GEOFENCE = 0,
	FLIGHTSTATUS_CONTROLSOURCE_FAILSAFE = 1,
	FLIGHTSTATUS_CONTROLSOURCE_TRANSMITTER = 2,
	FLIGHTSTATUS_CONTROLSOURCE_TABLET = 3,
	FLIGHTSTATUS_CONTROLSOURCE_LASTITEM = 4
};

extern char UAVT_FlightStatusArmedOption[][42];
extern char UAVT_FlightStatusFlightModeOption[][42];
extern char UAVT_FlightStatusControlSourceOption[][42];
typedef struct {
	uint8_t Armed;	// enum
	uint8_t FlightMode;	// enum
	uint8_t ControlSource;	// enum
} UAVT_FlightStatusData;

extern UAVT_FlightStatusData uavtalk_FlightStatusData;


/*************************************************************************************************
    Filename: flighttelemetrystats.xml
    Object: FlightTelemetryStats
    Comment: Maintains the telemetry statistics from the OpenPilot flight computer.
*************************************************************************************************/

#define FLIGHTTELEMETRYSTATS_OBJID 0x9e5ba136

enum {
	FLIGHTTELEMETRYSTATS_STATE_DISCONNECTED = 0,
	FLIGHTTELEMETRYSTATS_STATE_HANDSHAKEREQ = 1,
	FLIGHTTELEMETRYSTATS_STATE_HANDSHAKEACK = 2,
	FLIGHTTELEMETRYSTATS_STATE_CONNECTED = 3,
	FLIGHTTELEMETRYSTATS_STATE_LASTITEM = 4
};

extern char UAVT_FlightTelemetryStatsStateOption[][42];
typedef struct {
	float TxDataRate;
	float RxDataRate;
	uint32_t TxFailures;
	uint32_t RxFailures;
	uint32_t TxRetries;
	uint8_t State;	// enum
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

#define GCSTELEMETRYSTATS_OBJID 0x708d0a90

enum {
	GCSTELEMETRYSTATS_STATE_DISCONNECTED = 0,
	GCSTELEMETRYSTATS_STATE_HANDSHAKEREQ = 1,
	GCSTELEMETRYSTATS_STATE_HANDSHAKEACK = 2,
	GCSTELEMETRYSTATS_STATE_CONNECTED = 3,
	GCSTELEMETRYSTATS_STATE_LASTITEM = 4
};

extern char UAVT_GCSTelemetryStatsStateOption[][42];
typedef struct {
	float TxDataRate;
	float RxDataRate;
	uint32_t TxFailures;
	uint32_t RxFailures;
	uint32_t TxRetries;
	uint8_t State;	// enum
} UAVT_GCSTelemetryStatsData;

extern UAVT_GCSTelemetryStatsData uavtalk_GCSTelemetryStatsData;


/*************************************************************************************************
    Filename: geofencesettings.xml
    Object: GeoFenceSettings
    Comment: Radius for simple geofence boundaries
*************************************************************************************************/

#define GEOFENCESETTINGS_OBJID 0xdf5ea7fe

typedef struct {
	uint16_t WarningRadius;
	uint16_t ErrorRadius;
} UAVT_GeoFenceSettingsData;

extern UAVT_GeoFenceSettingsData uavtalk_GeoFenceSettingsData;


/*************************************************************************************************
    Filename: gpsposition.xml
    Object: GPSPosition
    Comment: Raw GPS data from @ref GPSModule.  Should only be used by @ref AHRSCommsModule.
*************************************************************************************************/

#define GPSPOSITION_OBJID 0x628ba538

enum {
	GPSPOSITION_STATE_NOGPS = 0,
	GPSPOSITION_STATE_NOFIX = 1,
	GPSPOSITION_STATE_FIX2D = 2,
	GPSPOSITION_STATE_FIX3D = 3,
	GPSPOSITION_STATE_DIFF3D = 4,
	GPSPOSITION_STATE_LASTITEM = 5
};

extern char UAVT_GPSPositionStateOption[][42];
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
	uint8_t State;	// enum
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
    Filename: groundpathfollowersettings.xml
    Object: GroundPathFollowerSettings
    Comment: Settings for the @ref GroundPathFollowerModule
*************************************************************************************************/

#define GROUNDPATHFOLLOWERSETTINGS_OBJID 0x9090c16

enum {
	GROUNDPATHFOLLOWERSETTINGS_MANUALOVERRIDE_FALSE = 0,
	GROUNDPATHFOLLOWERSETTINGS_MANUALOVERRIDE_TRUE = 1,
	GROUNDPATHFOLLOWERSETTINGS_MANUALOVERRIDE_LASTITEM = 2
};

enum {
	GROUNDPATHFOLLOWERSETTINGS_THROTTLECONTROL_MANUAL = 0,
	GROUNDPATHFOLLOWERSETTINGS_THROTTLECONTROL_PROPORTIONAL = 1,
	GROUNDPATHFOLLOWERSETTINGS_THROTTLECONTROL_AUTO = 2,
	GROUNDPATHFOLLOWERSETTINGS_THROTTLECONTROL_LASTITEM = 3
};

enum {
	GROUNDPATHFOLLOWERSETTINGS_VELOCITYSOURCE_EKF = 0,
	GROUNDPATHFOLLOWERSETTINGS_VELOCITYSOURCE_NEDVEL = 1,
	GROUNDPATHFOLLOWERSETTINGS_VELOCITYSOURCE_GPSPOS = 2,
	GROUNDPATHFOLLOWERSETTINGS_VELOCITYSOURCE_LASTITEM = 3
};

enum {
	GROUNDPATHFOLLOWERSETTINGS_POSITIONSOURCE_EKF = 0,
	GROUNDPATHFOLLOWERSETTINGS_POSITIONSOURCE_GPSPOS = 1,
	GROUNDPATHFOLLOWERSETTINGS_POSITIONSOURCE_LASTITEM = 2
};

extern char UAVT_GroundPathFollowerSettingsManualOverrideOption[][42];
extern char UAVT_GroundPathFollowerSettingsThrottleControlOption[][42];
extern char UAVT_GroundPathFollowerSettingsVelocitySourceOption[][42];
extern char UAVT_GroundPathFollowerSettingsPositionSourceOption[][42];
typedef struct {
	float Kp;
	float Ki;
	float ILimit;
} UAVT_GroundPathFollowerSettingsHorizontalPosPIType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_GroundPathFollowerSettingsHorizontalVelPIDType;

typedef struct {
	UAVT_GroundPathFollowerSettingsHorizontalPosPIType HorizontalPosPI;	// float[3]
	UAVT_GroundPathFollowerSettingsHorizontalVelPIDType HorizontalVelPID;	// float[4]
	float VelocityFeedforward;
	float MaxThrottle;
	int32_t UpdatePeriod;
	uint16_t HorizontalVelMax;
	uint8_t ManualOverride;	// enum
	uint8_t ThrottleControl;	// enum
	uint8_t VelocitySource;	// enum
	uint8_t PositionSource;	// enum
	uint8_t EndpointRadius;
} UAVT_GroundPathFollowerSettingsData;

extern UAVT_GroundPathFollowerSettingsData uavtalk_GroundPathFollowerSettingsData;


/*************************************************************************************************
    Filename: groundtruth.xml
    Object: GroundTruth
    Comment: Ground truth data output by a simulator.
*************************************************************************************************/

#define GROUNDTRUTH_OBJID 0xf178dca8

typedef struct {
	float AccelerationXYZ[3];
	float PositionNED[3];
	float VelocityNED[3];
	float RPY[3];
	float AngularRates[3];
	float TrueAirspeed;
	float CalibratedAirspeed;
	float AngleOfAttack;
	float AngleOfSlip;
} UAVT_GroundTruthData;

extern UAVT_GroundTruthData uavtalk_GroundTruthData;


/*************************************************************************************************
    Filename: gyrosbias.xml
    Object: GyrosBias
    Comment: The online-estimate of gyro bias.
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
    Comment: The rate gyroscope sensor data, in body frame.
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

#define HOMELOCATION_OBJID 0xca32b032

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
	float Be[3];
	int16_t GroundTemperature;
	uint16_t SeaLevelPressure;
	uint8_t Set;	// enum
} UAVT_HomeLocationData;

extern UAVT_HomeLocationData uavtalk_HomeLocationData;


/*************************************************************************************************
    Filename: hottsettings.xml
    Object: HoTTSettings
    Comment: Settings for the @ref HoTT Telemetry Module
*************************************************************************************************/

#define HOTTSETTINGS_OBJID 0x6cbc1102

enum {
	HOTTSETTINGS_SENSOR_DISABLED = 0,
	HOTTSETTINGS_SENSOR_ENABLED = 1,
	HOTTSETTINGS_SENSOR_LASTITEM = 2
};

enum {
	HOTTSETTINGS_WARNING_DISABLED = 0,
	HOTTSETTINGS_WARNING_ENABLED = 1,
	HOTTSETTINGS_WARNING_LASTITEM = 2
};

extern char UAVT_HoTTSettingsSensorOption[][42];
extern char UAVT_HoTTSettingsWarningOption[][42];
typedef struct {
	float MinSpeed;
	float MaxSpeed;
	float NegDifference1;
	float PosDifference1;
	float NegDifference2;
	float PosDifference2;
	float MinHeight;
	float MaxHeight;
	float MaxDistance;
	float MinPowerVoltage;
	float MaxPowerVoltage;
	float MinSensor1Voltage;
	float MaxSensor1Voltage;
	float MinSensor2Voltage;
	float MaxSensor2Voltage;
	float MinCellVoltage;
	float MaxCurrent;
	float MaxUsedCapacity;
	float MinSensor1Temp;
	float MaxSensor1Temp;
	float MinSensor2Temp;
	float MaxSensor2Temp;
	float MaxServoTemp;
	float MinRPM;
	float MaxRPM;
	float MinFuel;
	float MaxServoDifference;
} UAVT_HoTTSettingsLimitType;

typedef struct {
	uint8_t VARIO;
	uint8_t GPS;
	uint8_t EAM;
	uint8_t GAM;
	uint8_t ESC;
} UAVT_HoTTSettingsSensorType;

typedef struct {
	uint8_t AltitudeBeep;
	uint8_t MinSpeed;
	uint8_t MaxSpeed;
	uint8_t NegDifference1;
	uint8_t PosDifference1;
	uint8_t NegDifference2;
	uint8_t PosDifference2;
	uint8_t MinHeight;
	uint8_t MaxHeight;
	uint8_t MaxDistance;
	uint8_t MinPowerVoltage;
	uint8_t MaxPowerVoltage;
	uint8_t MinSensor1Voltage;
	uint8_t MaxSensor1Voltage;
	uint8_t MinSensor2Voltage;
	uint8_t MaxSensor2Voltage;
	uint8_t MinCellVoltage;
	uint8_t MaxCurrent;
	uint8_t MaxUsedCapacity;
	uint8_t MinSensor1Temp;
	uint8_t MaxSensor1Temp;
	uint8_t MinSensor2Temp;
	uint8_t MaxSensor2Temp;
	uint8_t MaxServoTemp;
	uint8_t MinRPM;
	uint8_t MaxRPM;
	uint8_t MinFuel;
	uint8_t MaxServoDifference;
} UAVT_HoTTSettingsWarningType;

typedef struct {
	UAVT_HoTTSettingsLimitType Limit;	// float[27]
	UAVT_HoTTSettingsSensorType Sensor;	// enum[5]
	UAVT_HoTTSettingsWarningType Warning;	// enum[28]
} UAVT_HoTTSettingsData;

extern UAVT_HoTTSettingsData uavtalk_HoTTSettingsData;


/*************************************************************************************************
    Filename: hwcolibri.xml
    Object: HwColibri
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWCOLIBRI_OBJID 0xa0c92448

enum {
	HWCOLIBRI_FRAME_GEMINI = 0,
	HWCOLIBRI_FRAME_LASTITEM = 1
};

enum {
	HWCOLIBRI_RCVRPORT_DISABLED = 0,
	HWCOLIBRI_RCVRPORT_PWM = 1,
	HWCOLIBRI_RCVRPORT_PWM_ADC = 2,
	HWCOLIBRI_RCVRPORT_PPM = 3,
	HWCOLIBRI_RCVRPORT_PPM_ADC = 4,
	HWCOLIBRI_RCVRPORT_PPM_PWM = 5,
	HWCOLIBRI_RCVRPORT_PPM_PWM_ADC = 6,
	HWCOLIBRI_RCVRPORT_PPM_OUTPUTS = 7,
	HWCOLIBRI_RCVRPORT_PPM_OUTPUTS_ADC = 8,
	HWCOLIBRI_RCVRPORT_OUTPUTS = 9,
	HWCOLIBRI_RCVRPORT_OUTPUTS_ADC = 10,
	HWCOLIBRI_RCVRPORT_LASTITEM = 11
};

enum {
	HWCOLIBRI_UART1_DISABLED = 0,
	HWCOLIBRI_UART1_TELEMETRY = 1,
	HWCOLIBRI_UART1_GPS = 2,
	HWCOLIBRI_UART1_I2C = 3,
	HWCOLIBRI_UART1_DSM = 4,
	HWCOLIBRI_UART1_DEBUGCONSOLE = 5,
	HWCOLIBRI_UART1_COMBRIDGE = 6,
	HWCOLIBRI_UART1_MAVLINKTX = 7,
	HWCOLIBRI_UART1_MAVLINKTX_GPS_RX = 8,
	HWCOLIBRI_UART1_HOTT_SUMD = 9,
	HWCOLIBRI_UART1_HOTT_SUMH = 10,
	HWCOLIBRI_UART1_HOTT_TELEMETRY = 11,
	HWCOLIBRI_UART1_FRSKY_SENSOR_HUB = 12,
	HWCOLIBRI_UART1_LIGHTTELEMETRYTX = 13,
	HWCOLIBRI_UART1_PICOC = 14,
	HWCOLIBRI_UART1_LASTITEM = 15
};

enum {
	HWCOLIBRI_UART2_DISABLED = 0,
	HWCOLIBRI_UART2_TELEMETRY = 1,
	HWCOLIBRI_UART2_GPS = 2,
	HWCOLIBRI_UART2_S_BUS = 3,
	HWCOLIBRI_UART2_DSM = 4,
	HWCOLIBRI_UART2_DEBUGCONSOLE = 5,
	HWCOLIBRI_UART2_COMBRIDGE = 6,
	HWCOLIBRI_UART2_MAVLINKTX = 7,
	HWCOLIBRI_UART2_MAVLINKTX_GPS_RX = 8,
	HWCOLIBRI_UART2_HOTT_SUMD = 9,
	HWCOLIBRI_UART2_HOTT_SUMH = 10,
	HWCOLIBRI_UART2_HOTT_TELEMETRY = 11,
	HWCOLIBRI_UART2_FRSKY_SENSOR_HUB = 12,
	HWCOLIBRI_UART2_LIGHTTELEMETRYTX = 13,
	HWCOLIBRI_UART2_PICOC = 14,
	HWCOLIBRI_UART2_LASTITEM = 15
};

enum {
	HWCOLIBRI_UART3_DISABLED = 0,
	HWCOLIBRI_UART3_TELEMETRY = 1,
	HWCOLIBRI_UART3_GPS = 2,
	HWCOLIBRI_UART3_I2C = 3,
	HWCOLIBRI_UART3_DSM = 4,
	HWCOLIBRI_UART3_DEBUGCONSOLE = 5,
	HWCOLIBRI_UART3_COMBRIDGE = 6,
	HWCOLIBRI_UART3_MAVLINKTX = 7,
	HWCOLIBRI_UART3_MAVLINKTX_GPS_RX = 8,
	HWCOLIBRI_UART3_HOTT_SUMD = 9,
	HWCOLIBRI_UART3_HOTT_SUMH = 10,
	HWCOLIBRI_UART3_HOTT_TELEMETRY = 11,
	HWCOLIBRI_UART3_FRSKY_SENSOR_HUB = 12,
	HWCOLIBRI_UART3_LIGHTTELEMETRYTX = 13,
	HWCOLIBRI_UART3_PICOC = 14,
	HWCOLIBRI_UART3_LASTITEM = 15
};

enum {
	HWCOLIBRI_UART4_DISABLED = 0,
	HWCOLIBRI_UART4_TELEMETRY = 1,
	HWCOLIBRI_UART4_GPS = 2,
	HWCOLIBRI_UART4_DSM = 3,
	HWCOLIBRI_UART4_DEBUGCONSOLE = 4,
	HWCOLIBRI_UART4_COMBRIDGE = 5,
	HWCOLIBRI_UART4_MAVLINKTX = 6,
	HWCOLIBRI_UART4_MAVLINKTX_GPS_RX = 7,
	HWCOLIBRI_UART4_HOTT_SUMD = 8,
	HWCOLIBRI_UART4_HOTT_SUMH = 9,
	HWCOLIBRI_UART4_HOTT_TELEMETRY = 10,
	HWCOLIBRI_UART4_LIGHTTELEMETRYTX = 11,
	HWCOLIBRI_UART4_FRSKY_SENSOR_HUB = 12,
	HWCOLIBRI_UART4_PICOC = 13,
	HWCOLIBRI_UART4_LASTITEM = 14
};

enum {
	HWCOLIBRI_USB_HIDPORT_USBTELEMETRY = 0,
	HWCOLIBRI_USB_HIDPORT_RCTRANSMITTER = 1,
	HWCOLIBRI_USB_HIDPORT_DISABLED = 2,
	HWCOLIBRI_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWCOLIBRI_USB_VCPPORT_USBTELEMETRY = 0,
	HWCOLIBRI_USB_VCPPORT_COMBRIDGE = 1,
	HWCOLIBRI_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWCOLIBRI_USB_VCPPORT_PICOC = 3,
	HWCOLIBRI_USB_VCPPORT_DISABLED = 4,
	HWCOLIBRI_USB_VCPPORT_LASTITEM = 5
};

enum {
	HWCOLIBRI_GYRORANGE_250 = 0,
	HWCOLIBRI_GYRORANGE_500 = 1,
	HWCOLIBRI_GYRORANGE_1000 = 2,
	HWCOLIBRI_GYRORANGE_2000 = 3,
	HWCOLIBRI_GYRORANGE_LASTITEM = 4
};

enum {
	HWCOLIBRI_ACCELRANGE_2G = 0,
	HWCOLIBRI_ACCELRANGE_4G = 1,
	HWCOLIBRI_ACCELRANGE_8G = 2,
	HWCOLIBRI_ACCELRANGE_16G = 3,
	HWCOLIBRI_ACCELRANGE_LASTITEM = 4
};

enum {
	HWCOLIBRI_MPU6000RATE_200 = 0,
	HWCOLIBRI_MPU6000RATE_333 = 1,
	HWCOLIBRI_MPU6000RATE_500 = 2,
	HWCOLIBRI_MPU6000RATE_666 = 3,
	HWCOLIBRI_MPU6000RATE_1000 = 4,
	HWCOLIBRI_MPU6000RATE_2000 = 5,
	HWCOLIBRI_MPU6000RATE_4000 = 6,
	HWCOLIBRI_MPU6000RATE_8000 = 7,
	HWCOLIBRI_MPU6000RATE_LASTITEM = 8
};

enum {
	HWCOLIBRI_MPU6000DLPF_256 = 0,
	HWCOLIBRI_MPU6000DLPF_188 = 1,
	HWCOLIBRI_MPU6000DLPF_98 = 2,
	HWCOLIBRI_MPU6000DLPF_42 = 3,
	HWCOLIBRI_MPU6000DLPF_20 = 4,
	HWCOLIBRI_MPU6000DLPF_10 = 5,
	HWCOLIBRI_MPU6000DLPF_5 = 6,
	HWCOLIBRI_MPU6000DLPF_LASTITEM = 7
};

enum {
	HWCOLIBRI_MAGNETOMETER_DISABLED = 0,
	HWCOLIBRI_MAGNETOMETER_INTERNAL = 1,
	HWCOLIBRI_MAGNETOMETER_EXTERNALI2CUART1 = 2,
	HWCOLIBRI_MAGNETOMETER_EXTERNALI2CUART3 = 3,
	HWCOLIBRI_MAGNETOMETER_LASTITEM = 4
};

enum {
	HWCOLIBRI_EXTMAGORIENTATION_TOP0DEGCW = 0,
	HWCOLIBRI_EXTMAGORIENTATION_TOP90DEGCW = 1,
	HWCOLIBRI_EXTMAGORIENTATION_TOP180DEGCW = 2,
	HWCOLIBRI_EXTMAGORIENTATION_TOP270DEGCW = 3,
	HWCOLIBRI_EXTMAGORIENTATION_BOTTOM0DEGCW = 4,
	HWCOLIBRI_EXTMAGORIENTATION_BOTTOM90DEGCW = 5,
	HWCOLIBRI_EXTMAGORIENTATION_BOTTOM180DEGCW = 6,
	HWCOLIBRI_EXTMAGORIENTATION_BOTTOM270DEGCW = 7,
	HWCOLIBRI_EXTMAGORIENTATION_LASTITEM = 8
};

extern char UAVT_HwColibriFrameOption[][42];
extern char UAVT_HwColibriRcvrPortOption[][42];
extern char UAVT_HwColibriUart1Option[][42];
extern char UAVT_HwColibriUart2Option[][42];
extern char UAVT_HwColibriUart3Option[][42];
extern char UAVT_HwColibriUart4Option[][42];
extern char UAVT_HwColibriUSB_HIDPortOption[][42];
extern char UAVT_HwColibriUSB_VCPPortOption[][42];
extern char UAVT_HwColibriGyroRangeOption[][42];
extern char UAVT_HwColibriAccelRangeOption[][42];
extern char UAVT_HwColibriMPU6000RateOption[][42];
extern char UAVT_HwColibriMPU6000DLPFOption[][42];
extern char UAVT_HwColibriMagnetometerOption[][42];
extern char UAVT_HwColibriExtMagOrientationOption[][42];
typedef struct {
	uint8_t Frame;	// enum
	uint8_t RcvrPort;	// enum
	uint8_t Uart1;	// enum
	uint8_t Uart2;	// enum
	uint8_t Uart3;	// enum
	uint8_t Uart4;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t AccelRange;	// enum
	uint8_t MPU6000Rate;	// enum
	uint8_t MPU6000DLPF;	// enum
	uint8_t Magnetometer;	// enum
	uint8_t ExtMagOrientation;	// enum
} UAVT_HwColibriData;

extern UAVT_HwColibriData uavtalk_HwColibriData;


/*************************************************************************************************
    Filename: hwcoptercontrol.xml
    Object: HwCopterControl
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWCOPTERCONTROL_OBJID 0xd599c916

enum {
	HWCOPTERCONTROL_RCVRPORT_DISABLED = 0,
	HWCOPTERCONTROL_RCVRPORT_PWM = 1,
	HWCOPTERCONTROL_RCVRPORT_PPM = 2,
	HWCOPTERCONTROL_RCVRPORT_PPM_PWM = 3,
	HWCOPTERCONTROL_RCVRPORT_PPM_OUTPUTS = 4,
	HWCOPTERCONTROL_RCVRPORT_OUTPUTS = 5,
	HWCOPTERCONTROL_RCVRPORT_LASTITEM = 6
};

enum {
	HWCOPTERCONTROL_MAINPORT_DISABLED = 0,
	HWCOPTERCONTROL_MAINPORT_TELEMETRY = 1,
	HWCOPTERCONTROL_MAINPORT_GPS = 2,
	HWCOPTERCONTROL_MAINPORT_S_BUS = 3,
	HWCOPTERCONTROL_MAINPORT_DSM = 4,
	HWCOPTERCONTROL_MAINPORT_DEBUGCONSOLE = 5,
	HWCOPTERCONTROL_MAINPORT_COMBRIDGE = 6,
	HWCOPTERCONTROL_MAINPORT_MAVLINKTX = 7,
	HWCOPTERCONTROL_MAINPORT_MAVLINKTX_GPS_RX = 8,
	HWCOPTERCONTROL_MAINPORT_FRSKY_SENSOR_HUB = 9,
	HWCOPTERCONTROL_MAINPORT_LIGHTTELEMETRYTX = 10,
	HWCOPTERCONTROL_MAINPORT_LASTITEM = 11
};

enum {
	HWCOPTERCONTROL_FLEXIPORT_DISABLED = 0,
	HWCOPTERCONTROL_FLEXIPORT_TELEMETRY = 1,
	HWCOPTERCONTROL_FLEXIPORT_GPS = 2,
	HWCOPTERCONTROL_FLEXIPORT_I2C = 3,
	HWCOPTERCONTROL_FLEXIPORT_DSM = 4,
	HWCOPTERCONTROL_FLEXIPORT_DEBUGCONSOLE = 5,
	HWCOPTERCONTROL_FLEXIPORT_COMBRIDGE = 6,
	HWCOPTERCONTROL_FLEXIPORT_MAVLINKTX = 7,
	HWCOPTERCONTROL_FLEXIPORT_FRSKY_SENSOR_HUB = 8,
	HWCOPTERCONTROL_FLEXIPORT_LIGHTTELEMETRYTX = 9,
	HWCOPTERCONTROL_FLEXIPORT_LASTITEM = 10
};

enum {
	HWCOPTERCONTROL_USB_HIDPORT_USBTELEMETRY = 0,
	HWCOPTERCONTROL_USB_HIDPORT_RCTRANSMITTER = 1,
	HWCOPTERCONTROL_USB_HIDPORT_DISABLED = 2,
	HWCOPTERCONTROL_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWCOPTERCONTROL_USB_VCPPORT_USBTELEMETRY = 0,
	HWCOPTERCONTROL_USB_VCPPORT_COMBRIDGE = 1,
	HWCOPTERCONTROL_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWCOPTERCONTROL_USB_VCPPORT_DISABLED = 3,
	HWCOPTERCONTROL_USB_VCPPORT_LASTITEM = 4
};

enum {
	HWCOPTERCONTROL_GYRORANGE_250 = 0,
	HWCOPTERCONTROL_GYRORANGE_500 = 1,
	HWCOPTERCONTROL_GYRORANGE_1000 = 2,
	HWCOPTERCONTROL_GYRORANGE_2000 = 3,
	HWCOPTERCONTROL_GYRORANGE_LASTITEM = 4
};

enum {
	HWCOPTERCONTROL_ACCELRANGE_2G = 0,
	HWCOPTERCONTROL_ACCELRANGE_4G = 1,
	HWCOPTERCONTROL_ACCELRANGE_8G = 2,
	HWCOPTERCONTROL_ACCELRANGE_16G = 3,
	HWCOPTERCONTROL_ACCELRANGE_LASTITEM = 4
};

enum {
	HWCOPTERCONTROL_MPU6000RATE_200 = 0,
	HWCOPTERCONTROL_MPU6000RATE_333 = 1,
	HWCOPTERCONTROL_MPU6000RATE_500 = 2,
	HWCOPTERCONTROL_MPU6000RATE_666 = 3,
	HWCOPTERCONTROL_MPU6000RATE_1000 = 4,
	HWCOPTERCONTROL_MPU6000RATE_2000 = 5,
	HWCOPTERCONTROL_MPU6000RATE_4000 = 6,
	HWCOPTERCONTROL_MPU6000RATE_8000 = 7,
	HWCOPTERCONTROL_MPU6000RATE_LASTITEM = 8
};

enum {
	HWCOPTERCONTROL_MPU6000DLPF_256 = 0,
	HWCOPTERCONTROL_MPU6000DLPF_188 = 1,
	HWCOPTERCONTROL_MPU6000DLPF_98 = 2,
	HWCOPTERCONTROL_MPU6000DLPF_42 = 3,
	HWCOPTERCONTROL_MPU6000DLPF_20 = 4,
	HWCOPTERCONTROL_MPU6000DLPF_10 = 5,
	HWCOPTERCONTROL_MPU6000DLPF_5 = 6,
	HWCOPTERCONTROL_MPU6000DLPF_LASTITEM = 7
};

extern char UAVT_HwCopterControlRcvrPortOption[][42];
extern char UAVT_HwCopterControlMainPortOption[][42];
extern char UAVT_HwCopterControlFlexiPortOption[][42];
extern char UAVT_HwCopterControlUSB_HIDPortOption[][42];
extern char UAVT_HwCopterControlUSB_VCPPortOption[][42];
extern char UAVT_HwCopterControlGyroRangeOption[][42];
extern char UAVT_HwCopterControlAccelRangeOption[][42];
extern char UAVT_HwCopterControlMPU6000RateOption[][42];
extern char UAVT_HwCopterControlMPU6000DLPFOption[][42];
typedef struct {
	uint8_t RcvrPort;	// enum
	uint8_t MainPort;	// enum
	uint8_t FlexiPort;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t AccelRange;	// enum
	uint8_t MPU6000Rate;	// enum
	uint8_t MPU6000DLPF;	// enum
} UAVT_HwCopterControlData;

extern UAVT_HwCopterControlData uavtalk_HwCopterControlData;


/*************************************************************************************************
    Filename: hwdiscoveryf4.xml
    Object: HwDiscoveryF4
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWDISCOVERYF4_OBJID 0x416d89a8

enum {
	HWDISCOVERYF4_MAINPORT_DISABLED = 0,
	HWDISCOVERYF4_MAINPORT_TELEMETRY = 1,
	HWDISCOVERYF4_MAINPORT_DEBUGCONSOLE = 2,
	HWDISCOVERYF4_MAINPORT_LASTITEM = 3
};

enum {
	HWDISCOVERYF4_USB_HIDPORT_USBTELEMETRY = 0,
	HWDISCOVERYF4_USB_HIDPORT_RCTRANSMITTER = 1,
	HWDISCOVERYF4_USB_HIDPORT_DISABLED = 2,
	HWDISCOVERYF4_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWDISCOVERYF4_USB_VCPPORT_USBTELEMETRY = 0,
	HWDISCOVERYF4_USB_VCPPORT_COMBRIDGE = 1,
	HWDISCOVERYF4_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWDISCOVERYF4_USB_VCPPORT_DISABLED = 3,
	HWDISCOVERYF4_USB_VCPPORT_LASTITEM = 4
};

extern char UAVT_HwDiscoveryF4MainPortOption[][42];
extern char UAVT_HwDiscoveryF4USB_HIDPortOption[][42];
extern char UAVT_HwDiscoveryF4USB_VCPPortOption[][42];
typedef struct {
	uint8_t MainPort;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
} UAVT_HwDiscoveryF4Data;

extern UAVT_HwDiscoveryF4Data uavtalk_HwDiscoveryF4Data;


/*************************************************************************************************
    Filename: hwflyingf3.xml
    Object: HwFlyingF3
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWFLYINGF3_OBJID 0x472fae5a

enum {
	HWFLYINGF3_RCVRPORT_DISABLED = 0,
	HWFLYINGF3_RCVRPORT_PWM = 1,
	HWFLYINGF3_RCVRPORT_PPM = 2,
	HWFLYINGF3_RCVRPORT_PPM_PWM = 3,
	HWFLYINGF3_RCVRPORT_PPM_OUTPUTS = 4,
	HWFLYINGF3_RCVRPORT_OUTPUTS = 5,
	HWFLYINGF3_RCVRPORT_LASTITEM = 6
};

enum {
	HWFLYINGF3_UART1_DISABLED = 0,
	HWFLYINGF3_UART1_TELEMETRY = 1,
	HWFLYINGF3_UART1_GPS = 2,
	HWFLYINGF3_UART1_S_BUS = 3,
	HWFLYINGF3_UART1_DSM = 4,
	HWFLYINGF3_UART1_DEBUGCONSOLE = 5,
	HWFLYINGF3_UART1_COMBRIDGE = 6,
	HWFLYINGF3_UART1_MAVLINKTX = 7,
	HWFLYINGF3_UART1_MAVLINKTX_GPS_RX = 8,
	HWFLYINGF3_UART1_HOTT_SUMD = 9,
	HWFLYINGF3_UART1_HOTT_SUMH = 10,
	HWFLYINGF3_UART1_HOTT_TELEMETRY = 11,
	HWFLYINGF3_UART1_FRSKY_SENSOR_HUB = 12,
	HWFLYINGF3_UART1_LIGHTTELEMETRYTX = 13,
	HWFLYINGF3_UART1_FRSKY_SPORT_TELEMETRY = 14,
	HWFLYINGF3_UART1_LASTITEM = 15
};

enum {
	HWFLYINGF3_UART2_DISABLED = 0,
	HWFLYINGF3_UART2_TELEMETRY = 1,
	HWFLYINGF3_UART2_GPS = 2,
	HWFLYINGF3_UART2_S_BUS = 3,
	HWFLYINGF3_UART2_DSM = 4,
	HWFLYINGF3_UART2_DEBUGCONSOLE = 5,
	HWFLYINGF3_UART2_COMBRIDGE = 6,
	HWFLYINGF3_UART2_MAVLINKTX = 7,
	HWFLYINGF3_UART2_MAVLINKTX_GPS_RX = 8,
	HWFLYINGF3_UART2_HOTT_SUMD = 9,
	HWFLYINGF3_UART2_HOTT_SUMH = 10,
	HWFLYINGF3_UART2_HOTT_TELEMETRY = 11,
	HWFLYINGF3_UART2_FRSKY_SENSOR_HUB = 12,
	HWFLYINGF3_UART2_LIGHTTELEMETRYTX = 13,
	HWFLYINGF3_UART2_FRSKY_SPORT_TELEMETRY = 14,
	HWFLYINGF3_UART2_LASTITEM = 15
};

enum {
	HWFLYINGF3_UART3_DISABLED = 0,
	HWFLYINGF3_UART3_TELEMETRY = 1,
	HWFLYINGF3_UART3_GPS = 2,
	HWFLYINGF3_UART3_S_BUS = 3,
	HWFLYINGF3_UART3_DSM = 4,
	HWFLYINGF3_UART3_DEBUGCONSOLE = 5,
	HWFLYINGF3_UART3_COMBRIDGE = 6,
	HWFLYINGF3_UART3_MAVLINKTX = 7,
	HWFLYINGF3_UART3_MAVLINKTX_GPS_RX = 8,
	HWFLYINGF3_UART3_HOTT_SUMD = 9,
	HWFLYINGF3_UART3_HOTT_SUMH = 10,
	HWFLYINGF3_UART3_HOTT_TELEMETRY = 11,
	HWFLYINGF3_UART3_FRSKY_SENSOR_HUB = 12,
	HWFLYINGF3_UART3_LIGHTTELEMETRYTX = 13,
	HWFLYINGF3_UART3_FRSKY_SPORT_TELEMETRY = 14,
	HWFLYINGF3_UART3_LASTITEM = 15
};

enum {
	HWFLYINGF3_UART4_DISABLED = 0,
	HWFLYINGF3_UART4_TELEMETRY = 1,
	HWFLYINGF3_UART4_GPS = 2,
	HWFLYINGF3_UART4_S_BUS = 3,
	HWFLYINGF3_UART4_DSM = 4,
	HWFLYINGF3_UART4_DEBUGCONSOLE = 5,
	HWFLYINGF3_UART4_COMBRIDGE = 6,
	HWFLYINGF3_UART4_MAVLINKTX = 7,
	HWFLYINGF3_UART4_MAVLINKTX_GPS_RX = 8,
	HWFLYINGF3_UART4_HOTT_SUMD = 9,
	HWFLYINGF3_UART4_HOTT_SUMH = 10,
	HWFLYINGF3_UART4_HOTT_TELEMETRY = 11,
	HWFLYINGF3_UART4_FRSKY_SENSOR_HUB = 12,
	HWFLYINGF3_UART4_LIGHTTELEMETRYTX = 13,
	HWFLYINGF3_UART4_FRSKY_SPORT_TELEMETRY = 14,
	HWFLYINGF3_UART4_LASTITEM = 15
};

enum {
	HWFLYINGF3_UART5_DISABLED = 0,
	HWFLYINGF3_UART5_TELEMETRY = 1,
	HWFLYINGF3_UART5_GPS = 2,
	HWFLYINGF3_UART5_S_BUS = 3,
	HWFLYINGF3_UART5_DSM = 4,
	HWFLYINGF3_UART5_DEBUGCONSOLE = 5,
	HWFLYINGF3_UART5_COMBRIDGE = 6,
	HWFLYINGF3_UART5_MAVLINKTX = 7,
	HWFLYINGF3_UART5_MAVLINKTX_GPS_RX = 8,
	HWFLYINGF3_UART5_HOTT_SUMD = 9,
	HWFLYINGF3_UART5_HOTT_SUMH = 10,
	HWFLYINGF3_UART5_HOTT_TELEMETRY = 11,
	HWFLYINGF3_UART5_FRSKY_SENSOR_HUB = 12,
	HWFLYINGF3_UART5_LIGHTTELEMETRYTX = 13,
	HWFLYINGF3_UART5_FRSKY_SPORT_TELEMETRY = 14,
	HWFLYINGF3_UART5_LASTITEM = 15
};

enum {
	HWFLYINGF3_USB_HIDPORT_USBTELEMETRY = 0,
	HWFLYINGF3_USB_HIDPORT_RCTRANSMITTER = 1,
	HWFLYINGF3_USB_HIDPORT_DISABLED = 2,
	HWFLYINGF3_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWFLYINGF3_USB_VCPPORT_USBTELEMETRY = 0,
	HWFLYINGF3_USB_VCPPORT_COMBRIDGE = 1,
	HWFLYINGF3_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWFLYINGF3_USB_VCPPORT_DISABLED = 3,
	HWFLYINGF3_USB_VCPPORT_LASTITEM = 4
};

enum {
	HWFLYINGF3_GYRORANGE_250 = 0,
	HWFLYINGF3_GYRORANGE_500 = 1,
	HWFLYINGF3_GYRORANGE_1000 = 2,
	HWFLYINGF3_GYRORANGE_2000 = 3,
	HWFLYINGF3_GYRORANGE_LASTITEM = 4
};

enum {
	HWFLYINGF3_L3GD20RATE_380 = 0,
	HWFLYINGF3_L3GD20RATE_760 = 1,
	HWFLYINGF3_L3GD20RATE_LASTITEM = 2
};

enum {
	HWFLYINGF3_ACCELRANGE_2G = 0,
	HWFLYINGF3_ACCELRANGE_4G = 1,
	HWFLYINGF3_ACCELRANGE_8G = 2,
	HWFLYINGF3_ACCELRANGE_16G = 3,
	HWFLYINGF3_ACCELRANGE_LASTITEM = 4
};

enum {
	HWFLYINGF3_SHIELD_NONE = 0,
	HWFLYINGF3_SHIELD_RCFLYER = 1,
	HWFLYINGF3_SHIELD_CHEBUZZ = 2,
	HWFLYINGF3_SHIELD_BMP085 = 3,
	HWFLYINGF3_SHIELD_LASTITEM = 4
};

extern char UAVT_HwFlyingF3RcvrPortOption[][42];
extern char UAVT_HwFlyingF3Uart1Option[][42];
extern char UAVT_HwFlyingF3Uart2Option[][42];
extern char UAVT_HwFlyingF3Uart3Option[][42];
extern char UAVT_HwFlyingF3Uart4Option[][42];
extern char UAVT_HwFlyingF3Uart5Option[][42];
extern char UAVT_HwFlyingF3USB_HIDPortOption[][42];
extern char UAVT_HwFlyingF3USB_VCPPortOption[][42];
extern char UAVT_HwFlyingF3GyroRangeOption[][42];
extern char UAVT_HwFlyingF3L3GD20RateOption[][42];
extern char UAVT_HwFlyingF3AccelRangeOption[][42];
extern char UAVT_HwFlyingF3ShieldOption[][42];
typedef struct {
	uint8_t RcvrPort;	// enum
	uint8_t Uart1;	// enum
	uint8_t Uart2;	// enum
	uint8_t Uart3;	// enum
	uint8_t Uart4;	// enum
	uint8_t Uart5;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t L3GD20Rate;	// enum
	uint8_t AccelRange;	// enum
	uint8_t Shield;	// enum
} UAVT_HwFlyingF3Data;

extern UAVT_HwFlyingF3Data uavtalk_HwFlyingF3Data;


/*************************************************************************************************
    Filename: hwflyingf4.xml
    Object: HwFlyingF4
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWFLYINGF4_OBJID 0x5796bcc6

enum {
	HWFLYINGF4_RCVRPORT_DISABLED = 0,
	HWFLYINGF4_RCVRPORT_PWM = 1,
	HWFLYINGF4_RCVRPORT_PPM = 2,
	HWFLYINGF4_RCVRPORT_PPM_PWM = 3,
	HWFLYINGF4_RCVRPORT_PPM_OUTPUTS = 4,
	HWFLYINGF4_RCVRPORT_OUTPUTS = 5,
	HWFLYINGF4_RCVRPORT_LASTITEM = 6
};

enum {
	HWFLYINGF4_UART1_DISABLED = 0,
	HWFLYINGF4_UART1_GPS = 1,
	HWFLYINGF4_UART1_S_BUS = 2,
	HWFLYINGF4_UART1_DSM = 3,
	HWFLYINGF4_UART1_HOTT_SUMD = 4,
	HWFLYINGF4_UART1_HOTT_SUMH = 5,
	HWFLYINGF4_UART1_PICOC = 6,
	HWFLYINGF4_UART1_LASTITEM = 7
};

enum {
	HWFLYINGF4_UART2_DISABLED = 0,
	HWFLYINGF4_UART2_TELEMETRY = 1,
	HWFLYINGF4_UART2_GPS = 2,
	HWFLYINGF4_UART2_DSM = 3,
	HWFLYINGF4_UART2_DEBUGCONSOLE = 4,
	HWFLYINGF4_UART2_COMBRIDGE = 5,
	HWFLYINGF4_UART2_MAVLINKTX = 6,
	HWFLYINGF4_UART2_MAVLINKTX_GPS_RX = 7,
	HWFLYINGF4_UART2_FRSKY_SENSOR_HUB = 8,
	HWFLYINGF4_UART2_HOTT_SUMD = 9,
	HWFLYINGF4_UART2_HOTT_SUMH = 10,
	HWFLYINGF4_UART2_LIGHTTELEMETRYTX = 11,
	HWFLYINGF4_UART2_PICOC = 12,
	HWFLYINGF4_UART2_FRSKY_SPORT_TELEMETRY = 13,
	HWFLYINGF4_UART2_LASTITEM = 14
};

enum {
	HWFLYINGF4_UART3_DISABLED = 0,
	HWFLYINGF4_UART3_TELEMETRY = 1,
	HWFLYINGF4_UART3_GPS = 2,
	HWFLYINGF4_UART3_DSM = 3,
	HWFLYINGF4_UART3_DEBUGCONSOLE = 4,
	HWFLYINGF4_UART3_COMBRIDGE = 5,
	HWFLYINGF4_UART3_MAVLINKTX = 6,
	HWFLYINGF4_UART3_MAVLINKTX_GPS_RX = 7,
	HWFLYINGF4_UART3_FRSKY_SENSOR_HUB = 8,
	HWFLYINGF4_UART3_HOTT_SUMD = 9,
	HWFLYINGF4_UART3_HOTT_SUMH = 10,
	HWFLYINGF4_UART3_LIGHTTELEMETRYTX = 11,
	HWFLYINGF4_UART3_PICOC = 12,
	HWFLYINGF4_UART3_FRSKY_SPORT_TELEMETRY = 13,
	HWFLYINGF4_UART3_LASTITEM = 14
};

enum {
	HWFLYINGF4_USB_HIDPORT_USBTELEMETRY = 0,
	HWFLYINGF4_USB_HIDPORT_RCTRANSMITTER = 1,
	HWFLYINGF4_USB_HIDPORT_DISABLED = 2,
	HWFLYINGF4_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWFLYINGF4_USB_VCPPORT_USBTELEMETRY = 0,
	HWFLYINGF4_USB_VCPPORT_COMBRIDGE = 1,
	HWFLYINGF4_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWFLYINGF4_USB_VCPPORT_PICOC = 3,
	HWFLYINGF4_USB_VCPPORT_DISABLED = 4,
	HWFLYINGF4_USB_VCPPORT_LASTITEM = 5
};

enum {
	HWFLYINGF4_GYRORANGE_250 = 0,
	HWFLYINGF4_GYRORANGE_500 = 1,
	HWFLYINGF4_GYRORANGE_1000 = 2,
	HWFLYINGF4_GYRORANGE_2000 = 3,
	HWFLYINGF4_GYRORANGE_LASTITEM = 4
};

enum {
	HWFLYINGF4_ACCELRANGE_2G = 0,
	HWFLYINGF4_ACCELRANGE_4G = 1,
	HWFLYINGF4_ACCELRANGE_8G = 2,
	HWFLYINGF4_ACCELRANGE_16G = 3,
	HWFLYINGF4_ACCELRANGE_LASTITEM = 4
};

enum {
	HWFLYINGF4_MPU6050RATE_200 = 0,
	HWFLYINGF4_MPU6050RATE_333 = 1,
	HWFLYINGF4_MPU6050RATE_500 = 2,
	HWFLYINGF4_MPU6050RATE_666 = 3,
	HWFLYINGF4_MPU6050RATE_1000 = 4,
	HWFLYINGF4_MPU6050RATE_2000 = 5,
	HWFLYINGF4_MPU6050RATE_4000 = 6,
	HWFLYINGF4_MPU6050RATE_8000 = 7,
	HWFLYINGF4_MPU6050RATE_LASTITEM = 8
};

enum {
	HWFLYINGF4_MPU6050DLPF_256 = 0,
	HWFLYINGF4_MPU6050DLPF_188 = 1,
	HWFLYINGF4_MPU6050DLPF_98 = 2,
	HWFLYINGF4_MPU6050DLPF_42 = 3,
	HWFLYINGF4_MPU6050DLPF_20 = 4,
	HWFLYINGF4_MPU6050DLPF_10 = 5,
	HWFLYINGF4_MPU6050DLPF_5 = 6,
	HWFLYINGF4_MPU6050DLPF_LASTITEM = 7
};

enum {
	HWFLYINGF4_MAGNETOMETER_DISABLED = 0,
	HWFLYINGF4_MAGNETOMETER_EXTERNALI2C = 1,
	HWFLYINGF4_MAGNETOMETER_LASTITEM = 2
};

enum {
	HWFLYINGF4_EXTMAGORIENTATION_TOP0DEGCW = 0,
	HWFLYINGF4_EXTMAGORIENTATION_TOP90DEGCW = 1,
	HWFLYINGF4_EXTMAGORIENTATION_TOP180DEGCW = 2,
	HWFLYINGF4_EXTMAGORIENTATION_TOP270DEGCW = 3,
	HWFLYINGF4_EXTMAGORIENTATION_BOTTOM0DEGCW = 4,
	HWFLYINGF4_EXTMAGORIENTATION_BOTTOM90DEGCW = 5,
	HWFLYINGF4_EXTMAGORIENTATION_BOTTOM180DEGCW = 6,
	HWFLYINGF4_EXTMAGORIENTATION_BOTTOM270DEGCW = 7,
	HWFLYINGF4_EXTMAGORIENTATION_LASTITEM = 8
};

extern char UAVT_HwFlyingF4RcvrPortOption[][42];
extern char UAVT_HwFlyingF4Uart1Option[][42];
extern char UAVT_HwFlyingF4Uart2Option[][42];
extern char UAVT_HwFlyingF4Uart3Option[][42];
extern char UAVT_HwFlyingF4USB_HIDPortOption[][42];
extern char UAVT_HwFlyingF4USB_VCPPortOption[][42];
extern char UAVT_HwFlyingF4GyroRangeOption[][42];
extern char UAVT_HwFlyingF4AccelRangeOption[][42];
extern char UAVT_HwFlyingF4MPU6050RateOption[][42];
extern char UAVT_HwFlyingF4MPU6050DLPFOption[][42];
extern char UAVT_HwFlyingF4MagnetometerOption[][42];
extern char UAVT_HwFlyingF4ExtMagOrientationOption[][42];
typedef struct {
	uint8_t RcvrPort;	// enum
	uint8_t Uart1;	// enum
	uint8_t Uart2;	// enum
	uint8_t Uart3;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t AccelRange;	// enum
	uint8_t MPU6050Rate;	// enum
	uint8_t MPU6050DLPF;	// enum
	uint8_t Magnetometer;	// enum
	uint8_t ExtMagOrientation;	// enum
} UAVT_HwFlyingF4Data;

extern UAVT_HwFlyingF4Data uavtalk_HwFlyingF4Data;


/*************************************************************************************************
    Filename: hwfreedom.xml
    Object: HwFreedom
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWFREEDOM_OBJID 0x2db9d4f0

enum {
	HWFREEDOM_OUTPUT_DISABLED = 0,
	HWFREEDOM_OUTPUT_PWM = 1,
	HWFREEDOM_OUTPUT_LASTITEM = 2
};

enum {
	HWFREEDOM_MAINPORT_DISABLED = 0,
	HWFREEDOM_MAINPORT_TELEMETRY = 1,
	HWFREEDOM_MAINPORT_GPS = 2,
	HWFREEDOM_MAINPORT_DSM = 3,
	HWFREEDOM_MAINPORT_DEBUGCONSOLE = 4,
	HWFREEDOM_MAINPORT_COMBRIDGE = 5,
	HWFREEDOM_MAINPORT_MAVLINKTX = 6,
	HWFREEDOM_MAINPORT_MAVLINKTX_GPS_RX = 7,
	HWFREEDOM_MAINPORT_HOTT_SUMD = 8,
	HWFREEDOM_MAINPORT_HOTT_SUMH = 9,
	HWFREEDOM_MAINPORT_HOTT_TELEMETRY = 10,
	HWFREEDOM_MAINPORT_FRSKY_SENSOR_HUB = 11,
	HWFREEDOM_MAINPORT_LIGHTTELEMETRYTX = 12,
	HWFREEDOM_MAINPORT_PICOC = 13,
	HWFREEDOM_MAINPORT_FRSKY_SPORT_TELEMETRY = 14,
	HWFREEDOM_MAINPORT_LASTITEM = 15
};

enum {
	HWFREEDOM_FLEXIPORT_DISABLED = 0,
	HWFREEDOM_FLEXIPORT_TELEMETRY = 1,
	HWFREEDOM_FLEXIPORT_GPS = 2,
	HWFREEDOM_FLEXIPORT_I2C = 3,
	HWFREEDOM_FLEXIPORT_DSM = 4,
	HWFREEDOM_FLEXIPORT_DEBUGCONSOLE = 5,
	HWFREEDOM_FLEXIPORT_COMBRIDGE = 6,
	HWFREEDOM_FLEXIPORT_MAVLINKTX = 7,
	HWFREEDOM_FLEXIPORT_MAVLINKTX_GPS_RX = 8,
	HWFREEDOM_FLEXIPORT_HOTT_SUMD = 9,
	HWFREEDOM_FLEXIPORT_HOTT_SUMH = 10,
	HWFREEDOM_FLEXIPORT_HOTT_TELEMETRY = 11,
	HWFREEDOM_FLEXIPORT_FRSKY_SENSOR_HUB = 12,
	HWFREEDOM_FLEXIPORT_LIGHTTELEMETRYTX = 13,
	HWFREEDOM_FLEXIPORT_PICOC = 14,
	HWFREEDOM_FLEXIPORT_FRSKY_SPORT_TELEMETRY = 15,
	HWFREEDOM_FLEXIPORT_LASTITEM = 16
};

enum {
	HWFREEDOM_RCVRPORT_DISABLED = 0,
	HWFREEDOM_RCVRPORT_PPM = 1,
	HWFREEDOM_RCVRPORT_DSM = 2,
	HWFREEDOM_RCVRPORT_S_BUS = 3,
	HWFREEDOM_RCVRPORT_HOTT_SUMD = 4,
	HWFREEDOM_RCVRPORT_HOTT_SUMH = 5,
	HWFREEDOM_RCVRPORT_LASTITEM = 6
};

enum {
	HWFREEDOM_RADIOPORT_DISABLED = 0,
	HWFREEDOM_RADIOPORT_TELEMETRY = 1,
	HWFREEDOM_RADIOPORT_LASTITEM = 2
};

enum {
	HWFREEDOM_USB_HIDPORT_USBTELEMETRY = 0,
	HWFREEDOM_USB_HIDPORT_RCTRANSMITTER = 1,
	HWFREEDOM_USB_HIDPORT_DISABLED = 2,
	HWFREEDOM_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWFREEDOM_USB_VCPPORT_USBTELEMETRY = 0,
	HWFREEDOM_USB_VCPPORT_COMBRIDGE = 1,
	HWFREEDOM_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWFREEDOM_USB_VCPPORT_PICOC = 3,
	HWFREEDOM_USB_VCPPORT_DISABLED = 4,
	HWFREEDOM_USB_VCPPORT_LASTITEM = 5
};

enum {
	HWFREEDOM_GYRORANGE_250 = 0,
	HWFREEDOM_GYRORANGE_500 = 1,
	HWFREEDOM_GYRORANGE_1000 = 2,
	HWFREEDOM_GYRORANGE_2000 = 3,
	HWFREEDOM_GYRORANGE_LASTITEM = 4
};

enum {
	HWFREEDOM_ACCELRANGE_2G = 0,
	HWFREEDOM_ACCELRANGE_4G = 1,
	HWFREEDOM_ACCELRANGE_8G = 2,
	HWFREEDOM_ACCELRANGE_16G = 3,
	HWFREEDOM_ACCELRANGE_LASTITEM = 4
};

enum {
	HWFREEDOM_MPU6000RATE_200 = 0,
	HWFREEDOM_MPU6000RATE_333 = 1,
	HWFREEDOM_MPU6000RATE_500 = 2,
	HWFREEDOM_MPU6000RATE_666 = 3,
	HWFREEDOM_MPU6000RATE_1000 = 4,
	HWFREEDOM_MPU6000RATE_2000 = 5,
	HWFREEDOM_MPU6000RATE_4000 = 6,
	HWFREEDOM_MPU6000RATE_8000 = 7,
	HWFREEDOM_MPU6000RATE_LASTITEM = 8
};

enum {
	HWFREEDOM_MPU6000DLPF_256 = 0,
	HWFREEDOM_MPU6000DLPF_188 = 1,
	HWFREEDOM_MPU6000DLPF_98 = 2,
	HWFREEDOM_MPU6000DLPF_42 = 3,
	HWFREEDOM_MPU6000DLPF_20 = 4,
	HWFREEDOM_MPU6000DLPF_10 = 5,
	HWFREEDOM_MPU6000DLPF_5 = 6,
	HWFREEDOM_MPU6000DLPF_LASTITEM = 7
};

extern char UAVT_HwFreedomOutputOption[][42];
extern char UAVT_HwFreedomMainPortOption[][42];
extern char UAVT_HwFreedomFlexiPortOption[][42];
extern char UAVT_HwFreedomRcvrPortOption[][42];
extern char UAVT_HwFreedomRadioPortOption[][42];
extern char UAVT_HwFreedomUSB_HIDPortOption[][42];
extern char UAVT_HwFreedomUSB_VCPPortOption[][42];
extern char UAVT_HwFreedomGyroRangeOption[][42];
extern char UAVT_HwFreedomAccelRangeOption[][42];
extern char UAVT_HwFreedomMPU6000RateOption[][42];
extern char UAVT_HwFreedomMPU6000DLPFOption[][42];
typedef struct {
	uint8_t Output;	// enum
	uint8_t MainPort;	// enum
	uint8_t FlexiPort;	// enum
	uint8_t RcvrPort;	// enum
	uint8_t RadioPort;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t AccelRange;	// enum
	uint8_t MPU6000Rate;	// enum
	uint8_t MPU6000DLPF;	// enum
} UAVT_HwFreedomData;

extern UAVT_HwFreedomData uavtalk_HwFreedomData;


/*************************************************************************************************
    Filename: hwquanton.xml
    Object: HwQuanton
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWQUANTON_OBJID 0x176384a6

enum {
	HWQUANTON_RCVRPORT_DISABLED = 0,
	HWQUANTON_RCVRPORT_PWM = 1,
	HWQUANTON_RCVRPORT_PWM_ADC = 2,
	HWQUANTON_RCVRPORT_PPM = 3,
	HWQUANTON_RCVRPORT_PPM_ADC = 4,
	HWQUANTON_RCVRPORT_PPM_PWM = 5,
	HWQUANTON_RCVRPORT_PPM_PWM_ADC = 6,
	HWQUANTON_RCVRPORT_PPM_OUTPUTS = 7,
	HWQUANTON_RCVRPORT_PPM_OUTPUTS_ADC = 8,
	HWQUANTON_RCVRPORT_OUTPUTS = 9,
	HWQUANTON_RCVRPORT_OUTPUTS_ADC = 10,
	HWQUANTON_RCVRPORT_LASTITEM = 11
};

enum {
	HWQUANTON_UART1_DISABLED = 0,
	HWQUANTON_UART1_TELEMETRY = 1,
	HWQUANTON_UART1_GPS = 2,
	HWQUANTON_UART1_I2C = 3,
	HWQUANTON_UART1_DSM = 4,
	HWQUANTON_UART1_DEBUGCONSOLE = 5,
	HWQUANTON_UART1_COMBRIDGE = 6,
	HWQUANTON_UART1_MAVLINKTX = 7,
	HWQUANTON_UART1_MAVLINKTX_GPS_RX = 8,
	HWQUANTON_UART1_HOTT_SUMD = 9,
	HWQUANTON_UART1_HOTT_SUMH = 10,
	HWQUANTON_UART1_HOTT_TELEMETRY = 11,
	HWQUANTON_UART1_FRSKY_SENSOR_HUB = 12,
	HWQUANTON_UART1_LIGHTTELEMETRYTX = 13,
	HWQUANTON_UART1_PICOC = 14,
	HWQUANTON_UART1_FRSKY_SPORT_TELEMETRY = 15,
	HWQUANTON_UART1_LASTITEM = 16
};

enum {
	HWQUANTON_UART2_DISABLED = 0,
	HWQUANTON_UART2_TELEMETRY = 1,
	HWQUANTON_UART2_GPS = 2,
	HWQUANTON_UART2_S_BUS = 3,
	HWQUANTON_UART2_DSM = 4,
	HWQUANTON_UART2_DEBUGCONSOLE = 5,
	HWQUANTON_UART2_COMBRIDGE = 6,
	HWQUANTON_UART2_MAVLINKTX = 7,
	HWQUANTON_UART2_MAVLINKTX_GPS_RX = 8,
	HWQUANTON_UART2_HOTT_SUMD = 9,
	HWQUANTON_UART2_HOTT_SUMH = 10,
	HWQUANTON_UART2_HOTT_TELEMETRY = 11,
	HWQUANTON_UART2_FRSKY_SENSOR_HUB = 12,
	HWQUANTON_UART2_LIGHTTELEMETRYTX = 13,
	HWQUANTON_UART2_PICOC = 14,
	HWQUANTON_UART2_FRSKY_SPORT_TELEMETRY = 15,
	HWQUANTON_UART2_LASTITEM = 16
};

enum {
	HWQUANTON_UART3_DISABLED = 0,
	HWQUANTON_UART3_TELEMETRY = 1,
	HWQUANTON_UART3_GPS = 2,
	HWQUANTON_UART3_I2C = 3,
	HWQUANTON_UART3_DSM = 4,
	HWQUANTON_UART3_DEBUGCONSOLE = 5,
	HWQUANTON_UART3_COMBRIDGE = 6,
	HWQUANTON_UART3_MAVLINKTX = 7,
	HWQUANTON_UART3_MAVLINKTX_GPS_RX = 8,
	HWQUANTON_UART3_HOTT_SUMD = 9,
	HWQUANTON_UART3_HOTT_SUMH = 10,
	HWQUANTON_UART3_HOTT_TELEMETRY = 11,
	HWQUANTON_UART3_FRSKY_SENSOR_HUB = 12,
	HWQUANTON_UART3_LIGHTTELEMETRYTX = 13,
	HWQUANTON_UART3_PICOC = 14,
	HWQUANTON_UART3_FRSKY_SPORT_TELEMETRY = 15,
	HWQUANTON_UART3_LASTITEM = 16
};

enum {
	HWQUANTON_UART4_DISABLED = 0,
	HWQUANTON_UART4_TELEMETRY = 1,
	HWQUANTON_UART4_GPS = 2,
	HWQUANTON_UART4_DSM = 3,
	HWQUANTON_UART4_DEBUGCONSOLE = 4,
	HWQUANTON_UART4_COMBRIDGE = 5,
	HWQUANTON_UART4_MAVLINKTX = 6,
	HWQUANTON_UART4_MAVLINKTX_GPS_RX = 7,
	HWQUANTON_UART4_HOTT_SUMD = 8,
	HWQUANTON_UART4_HOTT_SUMH = 9,
	HWQUANTON_UART4_HOTT_TELEMETRY = 10,
	HWQUANTON_UART4_LIGHTTELEMETRYTX = 11,
	HWQUANTON_UART4_FRSKY_SENSOR_HUB = 12,
	HWQUANTON_UART4_PICOC = 13,
	HWQUANTON_UART4_FRSKY_SPORT_TELEMETRY = 14,
	HWQUANTON_UART4_LASTITEM = 15
};

enum {
	HWQUANTON_UART5_DISABLED = 0,
	HWQUANTON_UART5_TELEMETRY = 1,
	HWQUANTON_UART5_GPS = 2,
	HWQUANTON_UART5_DSM = 3,
	HWQUANTON_UART5_DEBUGCONSOLE = 4,
	HWQUANTON_UART5_COMBRIDGE = 5,
	HWQUANTON_UART5_MAVLINKTX = 6,
	HWQUANTON_UART5_MAVLINKTX_GPS_RX = 7,
	HWQUANTON_UART5_HOTT_SUMD = 8,
	HWQUANTON_UART5_HOTT_SUMH = 9,
	HWQUANTON_UART5_HOTT_TELEMETRY = 10,
	HWQUANTON_UART5_FRSKY_SENSOR_HUB = 11,
	HWQUANTON_UART5_LIGHTTELEMETRYTX = 12,
	HWQUANTON_UART5_PICOC = 13,
	HWQUANTON_UART5_FRSKY_SPORT_TELEMETRY = 14,
	HWQUANTON_UART5_LASTITEM = 15
};

enum {
	HWQUANTON_USB_HIDPORT_USBTELEMETRY = 0,
	HWQUANTON_USB_HIDPORT_RCTRANSMITTER = 1,
	HWQUANTON_USB_HIDPORT_DISABLED = 2,
	HWQUANTON_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWQUANTON_USB_VCPPORT_USBTELEMETRY = 0,
	HWQUANTON_USB_VCPPORT_COMBRIDGE = 1,
	HWQUANTON_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWQUANTON_USB_VCPPORT_PICOC = 3,
	HWQUANTON_USB_VCPPORT_DISABLED = 4,
	HWQUANTON_USB_VCPPORT_LASTITEM = 5
};

enum {
	HWQUANTON_GYRORANGE_250 = 0,
	HWQUANTON_GYRORANGE_500 = 1,
	HWQUANTON_GYRORANGE_1000 = 2,
	HWQUANTON_GYRORANGE_2000 = 3,
	HWQUANTON_GYRORANGE_LASTITEM = 4
};

enum {
	HWQUANTON_ACCELRANGE_2G = 0,
	HWQUANTON_ACCELRANGE_4G = 1,
	HWQUANTON_ACCELRANGE_8G = 2,
	HWQUANTON_ACCELRANGE_16G = 3,
	HWQUANTON_ACCELRANGE_LASTITEM = 4
};

enum {
	HWQUANTON_MPU6000RATE_200 = 0,
	HWQUANTON_MPU6000RATE_333 = 1,
	HWQUANTON_MPU6000RATE_500 = 2,
	HWQUANTON_MPU6000RATE_666 = 3,
	HWQUANTON_MPU6000RATE_1000 = 4,
	HWQUANTON_MPU6000RATE_2000 = 5,
	HWQUANTON_MPU6000RATE_4000 = 6,
	HWQUANTON_MPU6000RATE_8000 = 7,
	HWQUANTON_MPU6000RATE_LASTITEM = 8
};

enum {
	HWQUANTON_MPU6000DLPF_256 = 0,
	HWQUANTON_MPU6000DLPF_188 = 1,
	HWQUANTON_MPU6000DLPF_98 = 2,
	HWQUANTON_MPU6000DLPF_42 = 3,
	HWQUANTON_MPU6000DLPF_20 = 4,
	HWQUANTON_MPU6000DLPF_10 = 5,
	HWQUANTON_MPU6000DLPF_5 = 6,
	HWQUANTON_MPU6000DLPF_LASTITEM = 7
};

enum {
	HWQUANTON_MAGNETOMETER_DISABLED = 0,
	HWQUANTON_MAGNETOMETER_INTERNAL = 1,
	HWQUANTON_MAGNETOMETER_EXTERNALI2CUART1 = 2,
	HWQUANTON_MAGNETOMETER_EXTERNALI2CUART3 = 3,
	HWQUANTON_MAGNETOMETER_LASTITEM = 4
};

enum {
	HWQUANTON_EXTMAGORIENTATION_TOP0DEGCW = 0,
	HWQUANTON_EXTMAGORIENTATION_TOP90DEGCW = 1,
	HWQUANTON_EXTMAGORIENTATION_TOP180DEGCW = 2,
	HWQUANTON_EXTMAGORIENTATION_TOP270DEGCW = 3,
	HWQUANTON_EXTMAGORIENTATION_BOTTOM0DEGCW = 4,
	HWQUANTON_EXTMAGORIENTATION_BOTTOM90DEGCW = 5,
	HWQUANTON_EXTMAGORIENTATION_BOTTOM180DEGCW = 6,
	HWQUANTON_EXTMAGORIENTATION_BOTTOM270DEGCW = 7,
	HWQUANTON_EXTMAGORIENTATION_LASTITEM = 8
};

extern char UAVT_HwQuantonRcvrPortOption[][42];
extern char UAVT_HwQuantonUart1Option[][42];
extern char UAVT_HwQuantonUart2Option[][42];
extern char UAVT_HwQuantonUart3Option[][42];
extern char UAVT_HwQuantonUart4Option[][42];
extern char UAVT_HwQuantonUart5Option[][42];
extern char UAVT_HwQuantonUSB_HIDPortOption[][42];
extern char UAVT_HwQuantonUSB_VCPPortOption[][42];
extern char UAVT_HwQuantonGyroRangeOption[][42];
extern char UAVT_HwQuantonAccelRangeOption[][42];
extern char UAVT_HwQuantonMPU6000RateOption[][42];
extern char UAVT_HwQuantonMPU6000DLPFOption[][42];
extern char UAVT_HwQuantonMagnetometerOption[][42];
extern char UAVT_HwQuantonExtMagOrientationOption[][42];
typedef struct {
	uint8_t RcvrPort;	// enum
	uint8_t Uart1;	// enum
	uint8_t Uart2;	// enum
	uint8_t Uart3;	// enum
	uint8_t Uart4;	// enum
	uint8_t Uart5;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t AccelRange;	// enum
	uint8_t MPU6000Rate;	// enum
	uint8_t MPU6000DLPF;	// enum
	uint8_t Magnetometer;	// enum
	uint8_t ExtMagOrientation;	// enum
} UAVT_HwQuantonData;

extern UAVT_HwQuantonData uavtalk_HwQuantonData;


/*************************************************************************************************
    Filename: hwrevolution.xml
    Object: HwRevolution
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWREVOLUTION_OBJID 0xd9ac7e1a

enum {
	HWREVOLUTION_RCVRPORT_DISABLED = 0,
	HWREVOLUTION_RCVRPORT_PWM = 1,
	HWREVOLUTION_RCVRPORT_PPM = 2,
	HWREVOLUTION_RCVRPORT_PPM_OUTPUTS = 3,
	HWREVOLUTION_RCVRPORT_OUTPUTS = 4,
	HWREVOLUTION_RCVRPORT_LASTITEM = 5
};

enum {
	HWREVOLUTION_AUXPORT_DISABLED = 0,
	HWREVOLUTION_AUXPORT_TELEMETRY = 1,
	HWREVOLUTION_AUXPORT_DSM = 2,
	HWREVOLUTION_AUXPORT_DEBUGCONSOLE = 3,
	HWREVOLUTION_AUXPORT_COMBRIDGE = 4,
	HWREVOLUTION_AUXPORT_MAVLINKTX = 5,
	HWREVOLUTION_AUXPORT_MAVLINKTX_GPS_RX = 6,
	HWREVOLUTION_AUXPORT_HOTT_SUMD = 7,
	HWREVOLUTION_AUXPORT_HOTT_SUMH = 8,
	HWREVOLUTION_AUXPORT_HOTT_TELEMETRY = 9,
	HWREVOLUTION_AUXPORT_PICOC = 10,
	HWREVOLUTION_AUXPORT_FRSKY_SPORT_TELEMETRY = 11,
	HWREVOLUTION_AUXPORT_LASTITEM = 12
};

enum {
	HWREVOLUTION_AUXSBUSPORT_DISABLED = 0,
	HWREVOLUTION_AUXSBUSPORT_S_BUS = 1,
	HWREVOLUTION_AUXSBUSPORT_DSM = 2,
	HWREVOLUTION_AUXSBUSPORT_DEBUGCONSOLE = 3,
	HWREVOLUTION_AUXSBUSPORT_COMBRIDGE = 4,
	HWREVOLUTION_AUXSBUSPORT_MAVLINKTX = 5,
	HWREVOLUTION_AUXSBUSPORT_MAVLINKTX_GPS_RX = 6,
	HWREVOLUTION_AUXSBUSPORT_HOTT_SUMD = 7,
	HWREVOLUTION_AUXSBUSPORT_HOTT_SUMH = 8,
	HWREVOLUTION_AUXSBUSPORT_HOTT_TELEMETRY = 9,
	HWREVOLUTION_AUXSBUSPORT_PICOC = 10,
	HWREVOLUTION_AUXSBUSPORT_FRSKY_SPORT_TELEMETRY = 11,
	HWREVOLUTION_AUXSBUSPORT_LASTITEM = 12
};

enum {
	HWREVOLUTION_FLEXIPORT_DISABLED = 0,
	HWREVOLUTION_FLEXIPORT_I2C = 1,
	HWREVOLUTION_FLEXIPORT_DSM = 2,
	HWREVOLUTION_FLEXIPORT_DEBUGCONSOLE = 3,
	HWREVOLUTION_FLEXIPORT_COMBRIDGE = 4,
	HWREVOLUTION_FLEXIPORT_MAVLINKTX = 5,
	HWREVOLUTION_FLEXIPORT_MAVLINKTX_GPS_RX = 6,
	HWREVOLUTION_FLEXIPORT_HOTT_SUMD = 7,
	HWREVOLUTION_FLEXIPORT_HOTT_SUMH = 8,
	HWREVOLUTION_FLEXIPORT_HOTT_TELEMETRY = 9,
	HWREVOLUTION_FLEXIPORT_PICOC = 10,
	HWREVOLUTION_FLEXIPORT_FRSKY_SPORT_TELEMETRY = 11,
	HWREVOLUTION_FLEXIPORT_LASTITEM = 12
};

enum {
	HWREVOLUTION_TELEMETRYPORT_DISABLED = 0,
	HWREVOLUTION_TELEMETRYPORT_TELEMETRY = 1,
	HWREVOLUTION_TELEMETRYPORT_DEBUGCONSOLE = 2,
	HWREVOLUTION_TELEMETRYPORT_COMBRIDGE = 3,
	HWREVOLUTION_TELEMETRYPORT_LASTITEM = 4
};

enum {
	HWREVOLUTION_GPSPORT_DISABLED = 0,
	HWREVOLUTION_GPSPORT_TELEMETRY = 1,
	HWREVOLUTION_GPSPORT_GPS = 2,
	HWREVOLUTION_GPSPORT_DEBUGCONSOLE = 3,
	HWREVOLUTION_GPSPORT_COMBRIDGE = 4,
	HWREVOLUTION_GPSPORT_LASTITEM = 5
};

enum {
	HWREVOLUTION_USB_HIDPORT_USBTELEMETRY = 0,
	HWREVOLUTION_USB_HIDPORT_RCTRANSMITTER = 1,
	HWREVOLUTION_USB_HIDPORT_DISABLED = 2,
	HWREVOLUTION_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWREVOLUTION_USB_VCPPORT_USBTELEMETRY = 0,
	HWREVOLUTION_USB_VCPPORT_COMBRIDGE = 1,
	HWREVOLUTION_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWREVOLUTION_USB_VCPPORT_PICOC = 3,
	HWREVOLUTION_USB_VCPPORT_DISABLED = 4,
	HWREVOLUTION_USB_VCPPORT_LASTITEM = 5
};

enum {
	HWREVOLUTION_GYRORANGE_250 = 0,
	HWREVOLUTION_GYRORANGE_500 = 1,
	HWREVOLUTION_GYRORANGE_1000 = 2,
	HWREVOLUTION_GYRORANGE_2000 = 3,
	HWREVOLUTION_GYRORANGE_LASTITEM = 4
};

enum {
	HWREVOLUTION_ACCELRANGE_2G = 0,
	HWREVOLUTION_ACCELRANGE_4G = 1,
	HWREVOLUTION_ACCELRANGE_8G = 2,
	HWREVOLUTION_ACCELRANGE_16G = 3,
	HWREVOLUTION_ACCELRANGE_LASTITEM = 4
};

enum {
	HWREVOLUTION_MPU6000RATE_200 = 0,
	HWREVOLUTION_MPU6000RATE_333 = 1,
	HWREVOLUTION_MPU6000RATE_500 = 2,
	HWREVOLUTION_MPU6000RATE_666 = 3,
	HWREVOLUTION_MPU6000RATE_1000 = 4,
	HWREVOLUTION_MPU6000RATE_2000 = 5,
	HWREVOLUTION_MPU6000RATE_4000 = 6,
	HWREVOLUTION_MPU6000RATE_8000 = 7,
	HWREVOLUTION_MPU6000RATE_LASTITEM = 8
};

enum {
	HWREVOLUTION_MPU6000DLPF_256 = 0,
	HWREVOLUTION_MPU6000DLPF_188 = 1,
	HWREVOLUTION_MPU6000DLPF_98 = 2,
	HWREVOLUTION_MPU6000DLPF_42 = 3,
	HWREVOLUTION_MPU6000DLPF_20 = 4,
	HWREVOLUTION_MPU6000DLPF_10 = 5,
	HWREVOLUTION_MPU6000DLPF_5 = 6,
	HWREVOLUTION_MPU6000DLPF_LASTITEM = 7
};

extern char UAVT_HwRevolutionRcvrPortOption[][42];
extern char UAVT_HwRevolutionAuxPortOption[][42];
extern char UAVT_HwRevolutionAuxSBusPortOption[][42];
extern char UAVT_HwRevolutionFlexiPortOption[][42];
extern char UAVT_HwRevolutionTelemetryPortOption[][42];
extern char UAVT_HwRevolutionGPSPortOption[][42];
extern char UAVT_HwRevolutionUSB_HIDPortOption[][42];
extern char UAVT_HwRevolutionUSB_VCPPortOption[][42];
extern char UAVT_HwRevolutionGyroRangeOption[][42];
extern char UAVT_HwRevolutionAccelRangeOption[][42];
extern char UAVT_HwRevolutionMPU6000RateOption[][42];
extern char UAVT_HwRevolutionMPU6000DLPFOption[][42];
typedef struct {
	uint8_t RcvrPort;	// enum
	uint8_t AuxPort;	// enum
	uint8_t AuxSBusPort;	// enum
	uint8_t FlexiPort;	// enum
	uint8_t TelemetryPort;	// enum
	uint8_t GPSPort;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t AccelRange;	// enum
	uint8_t MPU6000Rate;	// enum
	uint8_t MPU6000DLPF;	// enum
} UAVT_HwRevolutionData;

extern UAVT_HwRevolutionData uavtalk_HwRevolutionData;


/*************************************************************************************************
    Filename: hwrevomini.xml
    Object: HwRevoMini
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWREVOMINI_OBJID 0xb265ad64

enum {
	HWREVOMINI_RCVRPORT_DISABLED = 0,
	HWREVOMINI_RCVRPORT_PWM = 1,
	HWREVOMINI_RCVRPORT_PPM = 2,
	HWREVOMINI_RCVRPORT_PPM_PWM = 3,
	HWREVOMINI_RCVRPORT_PPM_OUTPUTS = 4,
	HWREVOMINI_RCVRPORT_OUTPUTS = 5,
	HWREVOMINI_RCVRPORT_LASTITEM = 6
};

enum {
	HWREVOMINI_MAINPORT_DISABLED = 0,
	HWREVOMINI_MAINPORT_TELEMETRY = 1,
	HWREVOMINI_MAINPORT_GPS = 2,
	HWREVOMINI_MAINPORT_S_BUS = 3,
	HWREVOMINI_MAINPORT_DSM = 4,
	HWREVOMINI_MAINPORT_DEBUGCONSOLE = 5,
	HWREVOMINI_MAINPORT_COMBRIDGE = 6,
	HWREVOMINI_MAINPORT_MAVLINKTX = 7,
	HWREVOMINI_MAINPORT_MAVLINKTX_GPS_RX = 8,
	HWREVOMINI_MAINPORT_HOTT_SUMD = 9,
	HWREVOMINI_MAINPORT_HOTT_SUMH = 10,
	HWREVOMINI_MAINPORT_HOTT_TELEMETRY = 11,
	HWREVOMINI_MAINPORT_FRSKY_SENSOR_HUB = 12,
	HWREVOMINI_MAINPORT_LIGHTTELEMETRYTX = 13,
	HWREVOMINI_MAINPORT_PICOC = 14,
	HWREVOMINI_MAINPORT_FRSKY_SPORT_TELEMETRY = 15,
	HWREVOMINI_MAINPORT_LASTITEM = 16
};

enum {
	HWREVOMINI_FLEXIPORT_DISABLED = 0,
	HWREVOMINI_FLEXIPORT_TELEMETRY = 1,
	HWREVOMINI_FLEXIPORT_GPS = 2,
	HWREVOMINI_FLEXIPORT_I2C = 3,
	HWREVOMINI_FLEXIPORT_DSM = 4,
	HWREVOMINI_FLEXIPORT_DEBUGCONSOLE = 5,
	HWREVOMINI_FLEXIPORT_COMBRIDGE = 6,
	HWREVOMINI_FLEXIPORT_MAVLINKTX = 7,
	HWREVOMINI_FLEXIPORT_MAVLINKTX_GPS_RX = 8,
	HWREVOMINI_FLEXIPORT_HOTT_SUMD = 9,
	HWREVOMINI_FLEXIPORT_HOTT_SUMH = 10,
	HWREVOMINI_FLEXIPORT_HOTT_TELEMETRY = 11,
	HWREVOMINI_FLEXIPORT_FRSKY_SENSOR_HUB = 12,
	HWREVOMINI_FLEXIPORT_LIGHTTELEMETRYTX = 13,
	HWREVOMINI_FLEXIPORT_PICOC = 14,
	HWREVOMINI_FLEXIPORT_FRSKY_SPORT_TELEMETRY = 15,
	HWREVOMINI_FLEXIPORT_LASTITEM = 16
};

enum {
	HWREVOMINI_RADIOPORT_DISABLED = 0,
	HWREVOMINI_RADIOPORT_TELEMETRY = 1,
	HWREVOMINI_RADIOPORT_LASTITEM = 2
};

enum {
	HWREVOMINI_USB_HIDPORT_USBTELEMETRY = 0,
	HWREVOMINI_USB_HIDPORT_RCTRANSMITTER = 1,
	HWREVOMINI_USB_HIDPORT_DISABLED = 2,
	HWREVOMINI_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWREVOMINI_USB_VCPPORT_USBTELEMETRY = 0,
	HWREVOMINI_USB_VCPPORT_COMBRIDGE = 1,
	HWREVOMINI_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWREVOMINI_USB_VCPPORT_PICOC = 3,
	HWREVOMINI_USB_VCPPORT_DISABLED = 4,
	HWREVOMINI_USB_VCPPORT_LASTITEM = 5
};

enum {
	HWREVOMINI_GYRORANGE_250 = 0,
	HWREVOMINI_GYRORANGE_500 = 1,
	HWREVOMINI_GYRORANGE_1000 = 2,
	HWREVOMINI_GYRORANGE_2000 = 3,
	HWREVOMINI_GYRORANGE_LASTITEM = 4
};

enum {
	HWREVOMINI_ACCELRANGE_2G = 0,
	HWREVOMINI_ACCELRANGE_4G = 1,
	HWREVOMINI_ACCELRANGE_8G = 2,
	HWREVOMINI_ACCELRANGE_16G = 3,
	HWREVOMINI_ACCELRANGE_LASTITEM = 4
};

enum {
	HWREVOMINI_MPU6000RATE_200 = 0,
	HWREVOMINI_MPU6000RATE_333 = 1,
	HWREVOMINI_MPU6000RATE_500 = 2,
	HWREVOMINI_MPU6000RATE_666 = 3,
	HWREVOMINI_MPU6000RATE_1000 = 4,
	HWREVOMINI_MPU6000RATE_2000 = 5,
	HWREVOMINI_MPU6000RATE_4000 = 6,
	HWREVOMINI_MPU6000RATE_8000 = 7,
	HWREVOMINI_MPU6000RATE_LASTITEM = 8
};

enum {
	HWREVOMINI_MPU6000DLPF_256 = 0,
	HWREVOMINI_MPU6000DLPF_188 = 1,
	HWREVOMINI_MPU6000DLPF_98 = 2,
	HWREVOMINI_MPU6000DLPF_42 = 3,
	HWREVOMINI_MPU6000DLPF_20 = 4,
	HWREVOMINI_MPU6000DLPF_10 = 5,
	HWREVOMINI_MPU6000DLPF_5 = 6,
	HWREVOMINI_MPU6000DLPF_LASTITEM = 7
};

extern char UAVT_HwRevoMiniRcvrPortOption[][42];
extern char UAVT_HwRevoMiniMainPortOption[][42];
extern char UAVT_HwRevoMiniFlexiPortOption[][42];
extern char UAVT_HwRevoMiniRadioPortOption[][42];
extern char UAVT_HwRevoMiniUSB_HIDPortOption[][42];
extern char UAVT_HwRevoMiniUSB_VCPPortOption[][42];
extern char UAVT_HwRevoMiniGyroRangeOption[][42];
extern char UAVT_HwRevoMiniAccelRangeOption[][42];
extern char UAVT_HwRevoMiniMPU6000RateOption[][42];
extern char UAVT_HwRevoMiniMPU6000DLPFOption[][42];
typedef struct {
	uint8_t RcvrPort;	// enum
	uint8_t MainPort;	// enum
	uint8_t FlexiPort;	// enum
	uint8_t RadioPort;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t AccelRange;	// enum
	uint8_t MPU6000Rate;	// enum
	uint8_t MPU6000DLPF;	// enum
} UAVT_HwRevoMiniData;

extern UAVT_HwRevoMiniData uavtalk_HwRevoMiniData;


/*************************************************************************************************
    Filename: hwsparkybgc.xml
    Object: HwSparkyBGC
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWSPARKYBGC_OBJID 0xd76f3a36

enum {
	HWSPARKYBGC_RCVRPORT_DISABLED = 0,
	HWSPARKYBGC_RCVRPORT_PPM = 1,
	HWSPARKYBGC_RCVRPORT_S_BUS = 2,
	HWSPARKYBGC_RCVRPORT_DSM = 3,
	HWSPARKYBGC_RCVRPORT_HOTT_SUMD = 4,
	HWSPARKYBGC_RCVRPORT_HOTT_SUMH = 5,
	HWSPARKYBGC_RCVRPORT_LASTITEM = 6
};

enum {
	HWSPARKYBGC_FLEXIPORT_DISABLED = 0,
	HWSPARKYBGC_FLEXIPORT_TELEMETRY = 1,
	HWSPARKYBGC_FLEXIPORT_DEBUGCONSOLE = 2,
	HWSPARKYBGC_FLEXIPORT_COMBRIDGE = 3,
	HWSPARKYBGC_FLEXIPORT_GPS = 4,
	HWSPARKYBGC_FLEXIPORT_S_BUS = 5,
	HWSPARKYBGC_FLEXIPORT_DSM = 6,
	HWSPARKYBGC_FLEXIPORT_MAVLINKTX = 7,
	HWSPARKYBGC_FLEXIPORT_MAVLINKTX_GPS_RX = 8,
	HWSPARKYBGC_FLEXIPORT_HOTT_TELEMETRY = 9,
	HWSPARKYBGC_FLEXIPORT_FRSKY_SENSOR_HUB = 10,
	HWSPARKYBGC_FLEXIPORT_LIGHTTELEMETRYTX = 11,
	HWSPARKYBGC_FLEXIPORT_FRSKY_SPORT_TELEMETRY = 12,
	HWSPARKYBGC_FLEXIPORT_LASTITEM = 13
};

enum {
	HWSPARKYBGC_USB_HIDPORT_USBTELEMETRY = 0,
	HWSPARKYBGC_USB_HIDPORT_RCTRANSMITTER = 1,
	HWSPARKYBGC_USB_HIDPORT_DISABLED = 2,
	HWSPARKYBGC_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWSPARKYBGC_USB_VCPPORT_USBTELEMETRY = 0,
	HWSPARKYBGC_USB_VCPPORT_COMBRIDGE = 1,
	HWSPARKYBGC_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWSPARKYBGC_USB_VCPPORT_DISABLED = 3,
	HWSPARKYBGC_USB_VCPPORT_LASTITEM = 4
};

enum {
	HWSPARKYBGC_GYRORANGE_250 = 0,
	HWSPARKYBGC_GYRORANGE_500 = 1,
	HWSPARKYBGC_GYRORANGE_1000 = 2,
	HWSPARKYBGC_GYRORANGE_2000 = 3,
	HWSPARKYBGC_GYRORANGE_LASTITEM = 4
};

enum {
	HWSPARKYBGC_ACCELRANGE_2G = 0,
	HWSPARKYBGC_ACCELRANGE_4G = 1,
	HWSPARKYBGC_ACCELRANGE_8G = 2,
	HWSPARKYBGC_ACCELRANGE_16G = 3,
	HWSPARKYBGC_ACCELRANGE_LASTITEM = 4
};

enum {
	HWSPARKYBGC_MPU9150DLPF_256 = 0,
	HWSPARKYBGC_MPU9150DLPF_188 = 1,
	HWSPARKYBGC_MPU9150DLPF_98 = 2,
	HWSPARKYBGC_MPU9150DLPF_42 = 3,
	HWSPARKYBGC_MPU9150DLPF_20 = 4,
	HWSPARKYBGC_MPU9150DLPF_10 = 5,
	HWSPARKYBGC_MPU9150DLPF_5 = 6,
	HWSPARKYBGC_MPU9150DLPF_LASTITEM = 7
};

enum {
	HWSPARKYBGC_MPU9150RATE_200 = 0,
	HWSPARKYBGC_MPU9150RATE_333 = 1,
	HWSPARKYBGC_MPU9150RATE_444 = 2,
	HWSPARKYBGC_MPU9150RATE_500 = 3,
	HWSPARKYBGC_MPU9150RATE_666 = 4,
	HWSPARKYBGC_MPU9150RATE_1000 = 5,
	HWSPARKYBGC_MPU9150RATE_2000 = 6,
	HWSPARKYBGC_MPU9150RATE_4000 = 7,
	HWSPARKYBGC_MPU9150RATE_8000 = 8,
	HWSPARKYBGC_MPU9150RATE_LASTITEM = 9
};

extern char UAVT_HwSparkyBGCRcvrPortOption[][42];
extern char UAVT_HwSparkyBGCFlexiPortOption[][42];
extern char UAVT_HwSparkyBGCUSB_HIDPortOption[][42];
extern char UAVT_HwSparkyBGCUSB_VCPPortOption[][42];
extern char UAVT_HwSparkyBGCGyroRangeOption[][42];
extern char UAVT_HwSparkyBGCAccelRangeOption[][42];
extern char UAVT_HwSparkyBGCMPU9150DLPFOption[][42];
extern char UAVT_HwSparkyBGCMPU9150RateOption[][42];
typedef struct {
	uint8_t RcvrPort;	// enum
	uint8_t FlexiPort;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t AccelRange;	// enum
	uint8_t MPU9150DLPF;	// enum
	uint8_t MPU9150Rate;	// enum
} UAVT_HwSparkyBGCData;

extern UAVT_HwSparkyBGCData uavtalk_HwSparkyBGCData;


/*************************************************************************************************
    Filename: hwsparky.xml
    Object: HwSparky
    Comment: Selection of optional hardware configurations.
*************************************************************************************************/

#define HWSPARKY_OBJID 0x858c848a

enum {
	HWSPARKY_RCVRPORT_DISABLED = 0,
	HWSPARKY_RCVRPORT_PPM = 1,
	HWSPARKY_RCVRPORT_S_BUS = 2,
	HWSPARKY_RCVRPORT_DSM = 3,
	HWSPARKY_RCVRPORT_HOTT_SUMD = 4,
	HWSPARKY_RCVRPORT_HOTT_SUMH = 5,
	HWSPARKY_RCVRPORT_LASTITEM = 6
};

enum {
	HWSPARKY_FLEXIPORT_DISABLED = 0,
	HWSPARKY_FLEXIPORT_TELEMETRY = 1,
	HWSPARKY_FLEXIPORT_DEBUGCONSOLE = 2,
	HWSPARKY_FLEXIPORT_COMBRIDGE = 3,
	HWSPARKY_FLEXIPORT_GPS = 4,
	HWSPARKY_FLEXIPORT_S_BUS = 5,
	HWSPARKY_FLEXIPORT_DSM = 6,
	HWSPARKY_FLEXIPORT_MAVLINKTX = 7,
	HWSPARKY_FLEXIPORT_MAVLINKTX_GPS_RX = 8,
	HWSPARKY_FLEXIPORT_HOTT_TELEMETRY = 9,
	HWSPARKY_FLEXIPORT_FRSKY_SENSOR_HUB = 10,
	HWSPARKY_FLEXIPORT_LIGHTTELEMETRYTX = 11,
	HWSPARKY_FLEXIPORT_FRSKY_SPORT_TELEMETRY = 12,
	HWSPARKY_FLEXIPORT_LASTITEM = 13
};

enum {
	HWSPARKY_MAINPORT_DISABLED = 0,
	HWSPARKY_MAINPORT_TELEMETRY = 1,
	HWSPARKY_MAINPORT_DEBUGCONSOLE = 2,
	HWSPARKY_MAINPORT_COMBRIDGE = 3,
	HWSPARKY_MAINPORT_GPS = 4,
	HWSPARKY_MAINPORT_S_BUS = 5,
	HWSPARKY_MAINPORT_DSM = 6,
	HWSPARKY_MAINPORT_MAVLINKTX = 7,
	HWSPARKY_MAINPORT_MAVLINKTX_GPS_RX = 8,
	HWSPARKY_MAINPORT_HOTT_TELEMETRY = 9,
	HWSPARKY_MAINPORT_FRSKY_SENSOR_HUB = 10,
	HWSPARKY_MAINPORT_LIGHTTELEMETRYTX = 11,
	HWSPARKY_MAINPORT_FRSKY_SPORT_TELEMETRY = 12,
	HWSPARKY_MAINPORT_LASTITEM = 13
};

enum {
	HWSPARKY_OUTPORT_PWM10 = 0,
	HWSPARKY_OUTPORT_PWM7_3ADC = 1,
	HWSPARKY_OUTPORT_PWM8_2ADC = 2,
	HWSPARKY_OUTPORT_PWM9_PWM_IN = 3,
	HWSPARKY_OUTPORT_PWM7_PWM_IN_2ADC = 4,
	HWSPARKY_OUTPORT_LASTITEM = 5
};

enum {
	HWSPARKY_USB_HIDPORT_USBTELEMETRY = 0,
	HWSPARKY_USB_HIDPORT_RCTRANSMITTER = 1,
	HWSPARKY_USB_HIDPORT_DISABLED = 2,
	HWSPARKY_USB_HIDPORT_LASTITEM = 3
};

enum {
	HWSPARKY_USB_VCPPORT_USBTELEMETRY = 0,
	HWSPARKY_USB_VCPPORT_COMBRIDGE = 1,
	HWSPARKY_USB_VCPPORT_DEBUGCONSOLE = 2,
	HWSPARKY_USB_VCPPORT_DISABLED = 3,
	HWSPARKY_USB_VCPPORT_LASTITEM = 4
};

enum {
	HWSPARKY_GYRORANGE_250 = 0,
	HWSPARKY_GYRORANGE_500 = 1,
	HWSPARKY_GYRORANGE_1000 = 2,
	HWSPARKY_GYRORANGE_2000 = 3,
	HWSPARKY_GYRORANGE_LASTITEM = 4
};

enum {
	HWSPARKY_ACCELRANGE_2G = 0,
	HWSPARKY_ACCELRANGE_4G = 1,
	HWSPARKY_ACCELRANGE_8G = 2,
	HWSPARKY_ACCELRANGE_16G = 3,
	HWSPARKY_ACCELRANGE_LASTITEM = 4
};

enum {
	HWSPARKY_MPU9150DLPF_256 = 0,
	HWSPARKY_MPU9150DLPF_188 = 1,
	HWSPARKY_MPU9150DLPF_98 = 2,
	HWSPARKY_MPU9150DLPF_42 = 3,
	HWSPARKY_MPU9150DLPF_20 = 4,
	HWSPARKY_MPU9150DLPF_10 = 5,
	HWSPARKY_MPU9150DLPF_5 = 6,
	HWSPARKY_MPU9150DLPF_LASTITEM = 7
};

enum {
	HWSPARKY_MPU9150RATE_200 = 0,
	HWSPARKY_MPU9150RATE_333 = 1,
	HWSPARKY_MPU9150RATE_444 = 2,
	HWSPARKY_MPU9150RATE_500 = 3,
	HWSPARKY_MPU9150RATE_666 = 4,
	HWSPARKY_MPU9150RATE_1000 = 5,
	HWSPARKY_MPU9150RATE_2000 = 6,
	HWSPARKY_MPU9150RATE_4000 = 7,
	HWSPARKY_MPU9150RATE_8000 = 8,
	HWSPARKY_MPU9150RATE_LASTITEM = 9
};

extern char UAVT_HwSparkyRcvrPortOption[][42];
extern char UAVT_HwSparkyFlexiPortOption[][42];
extern char UAVT_HwSparkyMainPortOption[][42];
extern char UAVT_HwSparkyOutPortOption[][42];
extern char UAVT_HwSparkyUSB_HIDPortOption[][42];
extern char UAVT_HwSparkyUSB_VCPPortOption[][42];
extern char UAVT_HwSparkyGyroRangeOption[][42];
extern char UAVT_HwSparkyAccelRangeOption[][42];
extern char UAVT_HwSparkyMPU9150DLPFOption[][42];
extern char UAVT_HwSparkyMPU9150RateOption[][42];
typedef struct {
	uint8_t RcvrPort;	// enum
	uint8_t FlexiPort;	// enum
	uint8_t MainPort;	// enum
	uint8_t OutPort;	// enum
	uint8_t USB_HIDPort;	// enum
	uint8_t USB_VCPPort;	// enum
	uint8_t DSMxBind;
	uint8_t GyroRange;	// enum
	uint8_t AccelRange;	// enum
	uint8_t MPU9150DLPF;	// enum
	uint8_t MPU9150Rate;	// enum
} UAVT_HwSparkyData;

extern UAVT_HwSparkyData uavtalk_HwSparkyData;


/*************************************************************************************************
    Filename: i2cvmuserprogram.xml
    Object: I2CVMUserProgram
    Comment: Allows GCS to provide a user-defined program to the I2C Virtual Machine
*************************************************************************************************/

#define I2CVMUSERPROGRAM_OBJID 0xed9cc1ac

typedef struct {
	uint32_t Program[20];
} UAVT_I2CVMUserProgramData;

extern UAVT_I2CVMUserProgramData uavtalk_I2CVMUserProgramData;


/*************************************************************************************************
    Filename: i2cvm.xml
    Object: I2CVM
    Comment: Snapshot of the register and RAM state of the I2C Virtual Machine
*************************************************************************************************/

#define I2CVM_OBJID 0x2a6a5146

typedef struct {
	int32_t r0;
	int32_t r1;
	int32_t r2;
	int32_t r3;
	int32_t r4;
	int32_t r5;
	int32_t r6;
	uint16_t pc;
	uint8_t ram[8];
} UAVT_I2CVMData;

extern UAVT_I2CVMData uavtalk_I2CVMData;


/*************************************************************************************************
    Filename: inssettings.xml
    Object: INSSettings
    Comment: Settings for the INS to control the algorithm and what is updated
*************************************************************************************************/

#define INSSETTINGS_OBJID 0x8ccff752

enum {
	INSSETTINGS_COMPUTEGYROBIAS_FALSE = 0,
	INSSETTINGS_COMPUTEGYROBIAS_TRUE = 1,
	INSSETTINGS_COMPUTEGYROBIAS_LASTITEM = 2
};

extern char UAVT_INSSettingsComputeGyroBiasOption[][42];
typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_INSSettingsaccel_varType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_INSSettingsgyro_varType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_INSSettingsmag_varType;

typedef struct {
	float Pos;
	float Vel;
	float VertPos;
} UAVT_INSSettingsgps_varType;

typedef struct {
	UAVT_INSSettingsaccel_varType accel_var;	// float[3]
	UAVT_INSSettingsgyro_varType gyro_var;	// float[3]
	UAVT_INSSettingsmag_varType mag_var;	// float[3]
	UAVT_INSSettingsgps_varType gps_var;	// float[3]
	float baro_var;
	float MagBiasNullingRate;
	uint8_t ComputeGyroBias;	// enum
} UAVT_INSSettingsData;

extern UAVT_INSSettingsData uavtalk_INSSettingsData;


/*************************************************************************************************
    Filename: insstate.xml
    Object: INSState
    Comment: Contains the INS state estimate
*************************************************************************************************/

#define INSSTATE_OBJID 0xae367e26

typedef struct {
	float State[13];
	float Var[13];
} UAVT_INSStateData;

extern UAVT_INSStateData uavtalk_INSStateData;


/*************************************************************************************************
    Filename: loggingsettings.xml
    Object: LoggingSettings
    Comment: Settings for the logging module
*************************************************************************************************/

#define LOGGINGSETTINGS_OBJID 0xa1b7f8a2

enum {
	LOGGINGSETTINGS_LOGBEHAVIOR_LOGONSTART = 0,
	LOGGINGSETTINGS_LOGBEHAVIOR_LOGONARM = 1,
	LOGGINGSETTINGS_LOGBEHAVIOR_LOGOFF = 2,
	LOGGINGSETTINGS_LOGBEHAVIOR_LASTITEM = 3
};

extern char UAVT_LoggingSettingsLogBehaviorOption[][42];
typedef struct {
	uint8_t LogBehavior;	// enum
} UAVT_LoggingSettingsData;

extern UAVT_LoggingSettingsData uavtalk_LoggingSettingsData;


/*************************************************************************************************
    Filename: loggingstats.xml
    Object: LoggingStats
    Comment: Information about logging
*************************************************************************************************/

#define LOGGINGSTATS_OBJID 0x4c859a62

enum {
	LOGGINGSTATS_OPERATION_LOGGING = 0,
	LOGGINGSTATS_OPERATION_IDLE = 1,
	LOGGINGSTATS_OPERATION_DOWNLOAD = 2,
	LOGGINGSTATS_OPERATION_COMPLETE = 3,
	LOGGINGSTATS_OPERATION_ERROR = 4,
	LOGGINGSTATS_OPERATION_LASTITEM = 5
};

extern char UAVT_LoggingStatsOperationOption[][42];
typedef struct {
	uint32_t BytesLogged;
	uint16_t MinFileId;
	uint16_t MaxFileId;
	uint16_t FileRequest;
	uint16_t FileSectorNum;
	uint8_t Operation;	// enum
	uint8_t FileSector[128];
} UAVT_LoggingStatsData;

extern UAVT_LoggingStatsData uavtalk_LoggingStatsData;


/*************************************************************************************************
    Filename: loitercommand.xml
    Object: LoiterCommand
    Comment: Requested movement while in loiter mode
*************************************************************************************************/

#define LOITERCOMMAND_OBJID 0x80d8d4ba

enum {
	LOITERCOMMAND_FRAME_BODY = 0,
	LOITERCOMMAND_FRAME_EARTH = 1,
	LOITERCOMMAND_FRAME_LASTITEM = 2
};

extern char UAVT_LoiterCommandFrameOption[][42];
typedef struct {
	float Forward;
	float Right;
	float Upwards;
	uint8_t Frame;	// enum
} UAVT_LoiterCommandData;

extern UAVT_LoiterCommandData uavtalk_LoiterCommandData;


/*************************************************************************************************
    Filename: magbias.xml
    Object: MagBias
    Comment: The gyro data.
*************************************************************************************************/

#define MAGBIAS_OBJID 0x5043e510

typedef struct {
	float x;
	float y;
	float z;
} UAVT_MagBiasData;

extern UAVT_MagBiasData uavtalk_MagBiasData;


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
    Comment: The output from the @ref ManualControlModule which decodes the receiver inputs.
*************************************************************************************************/

#define MANUALCONTROLCOMMAND_OBJID 0x5c2f58ac

enum {
	MANUALCONTROLCOMMAND_CONNECTED_FALSE = 0,
	MANUALCONTROLCOMMAND_CONNECTED_TRUE = 1,
	MANUALCONTROLCOMMAND_CONNECTED_LASTITEM = 2
};

extern char UAVT_ManualControlCommandConnectedOption[][42];
typedef struct {
	uint16_t Throttle;
	uint16_t Roll;
	uint16_t Pitch;
	uint16_t Yaw;
	uint16_t FlightMode;
	uint16_t Collective;
	uint16_t Accessory0;
	uint16_t Accessory1;
	uint16_t Accessory2;
	uint16_t Arming;
} UAVT_ManualControlCommandChannelType;

typedef struct {
	float Throttle;
	float Roll;
	float Pitch;
	float Yaw;
	uint32_t RawRssi;
	float Collective;
	int16_t Rssi;
	UAVT_ManualControlCommandChannelType Channel;	// uint16[10]
	uint8_t Connected;	// enum
} UAVT_ManualControlCommandData;

extern UAVT_ManualControlCommandData uavtalk_ManualControlCommandData;


/*************************************************************************************************
    Filename: manualcontrolsettings.xml
    Object: ManualControlSettings
    Comment: Settings to indicate how to decode receiver input by @ref ManualControlModule.
*************************************************************************************************/

#define MANUALCONTROLSETTINGS_OBJID 0x837ed6ca

enum {
	MANUALCONTROLSETTINGS_CHANNELGROUPS_PWM = 0,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_PPM = 1,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_DSM__MAINPORT_ = 2,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_DSM__FLEXIPORT_ = 3,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_S_BUS = 4,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS = 5,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_HOTT_SUM = 6,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_NONE = 7,
	MANUALCONTROLSETTINGS_CHANNELGROUPS_LASTITEM = 8
};

enum {
	MANUALCONTROLSETTINGS_RSSITYPE_NONE = 0,
	MANUALCONTROLSETTINGS_RSSITYPE_PWM = 1,
	MANUALCONTROLSETTINGS_RSSITYPE_PPM = 2,
	MANUALCONTROLSETTINGS_RSSITYPE_ADC = 3,
	MANUALCONTROLSETTINGS_RSSITYPE_LASTITEM = 4
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
	MANUALCONTROLSETTINGS_ARMING_SWITCH = 8,
	MANUALCONTROLSETTINGS_ARMING_LASTITEM = 9
};

enum {
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_NONE = 0,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_RATE = 1,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_ATTITUDE = 2,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_AXISLOCK = 3,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_WEAKLEVELING = 4,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_VIRTUALBAR = 5,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_HORIZON = 6,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_RATEMW = 7,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_SYSTEMIDENT = 8,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_POI = 9,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_COORDINATEDFLIGHT = 10,
	MANUALCONTROLSETTINGS_STABILIZATION1SETTINGS_LASTITEM = 11
};

enum {
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_NONE = 0,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_RATE = 1,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_ATTITUDE = 2,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_AXISLOCK = 3,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_WEAKLEVELING = 4,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_VIRTUALBAR = 5,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_HORIZON = 6,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_RATEMW = 7,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_SYSTEMIDENT = 8,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_POI = 9,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_COORDINATEDFLIGHT = 10,
	MANUALCONTROLSETTINGS_STABILIZATION2SETTINGS_LASTITEM = 11
};

enum {
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_NONE = 0,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_RATE = 1,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_ATTITUDE = 2,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_AXISLOCK = 3,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_WEAKLEVELING = 4,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_VIRTUALBAR = 5,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_HORIZON = 6,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_RATEMW = 7,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_SYSTEMIDENT = 8,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_POI = 9,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_COORDINATEDFLIGHT = 10,
	MANUALCONTROLSETTINGS_STABILIZATION3SETTINGS_LASTITEM = 11
};

enum {
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_MANUAL = 0,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_ACRO = 1,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_LEVELING = 2,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_VIRTUALBAR = 3,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_STABILIZED1 = 4,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_STABILIZED2 = 5,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_STABILIZED3 = 6,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_AUTOTUNE = 7,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_ALTITUDEHOLD = 8,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_VELOCITYCONTROL = 9,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_POSITIONHOLD = 10,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_RETURNTOHOME = 11,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_PATHPLANNER = 12,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_TABLETCONTROL = 13,
	MANUALCONTROLSETTINGS_FLIGHTMODEPOSITION_LASTITEM = 14
};

extern char UAVT_ManualControlSettingsChannelGroupsOption[][42];
extern char UAVT_ManualControlSettingsRssiTypeOption[][42];
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
	int16_t Arming;
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
	int16_t Arming;
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
	int16_t Arming;
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
	uint8_t Arming;
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
	uint8_t Arming;
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
	int16_t RssiMax;
	int16_t RssiMin;
	int16_t RssiPwmPeriod;
	UAVT_ManualControlSettingsChannelMinType ChannelMin;	// int16[10]
	UAVT_ManualControlSettingsChannelNeutralType ChannelNeutral;	// int16[10]
	UAVT_ManualControlSettingsChannelMaxType ChannelMax;	// int16[10]
	uint16_t ArmedTimeout;
	UAVT_ManualControlSettingsChannelGroupsType ChannelGroups;	// enum[10]
	uint8_t RssiType;	// enum
	uint8_t RssiChannelNumber;
	UAVT_ManualControlSettingsChannelNumberType ChannelNumber;	// uint8[10]
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

#define MIXERSETTINGS_OBJID 0x20e376cc

enum {
	MIXERSETTINGS_CURVE2SOURCE_THROTTLE = 0,
	MIXERSETTINGS_CURVE2SOURCE_ROLL = 1,
	MIXERSETTINGS_CURVE2SOURCE_PITCH = 2,
	MIXERSETTINGS_CURVE2SOURCE_YAW = 3,
	MIXERSETTINGS_CURVE2SOURCE_COLLECTIVE = 4,
	MIXERSETTINGS_CURVE2SOURCE_ACCESSORY0 = 5,
	MIXERSETTINGS_CURVE2SOURCE_ACCESSORY1 = 6,
	MIXERSETTINGS_CURVE2SOURCE_ACCESSORY2 = 7,
	MIXERSETTINGS_CURVE2SOURCE_ACCESSORY3 = 8,
	MIXERSETTINGS_CURVE2SOURCE_ACCESSORY4 = 9,
	MIXERSETTINGS_CURVE2SOURCE_ACCESSORY5 = 10,
	MIXERSETTINGS_CURVE2SOURCE_LASTITEM = 11
};

enum {
	MIXERSETTINGS_MIXER1TYPE_DISABLED = 0,
	MIXERSETTINGS_MIXER1TYPE_MOTOR = 1,
	MIXERSETTINGS_MIXER1TYPE_SERVO = 2,
	MIXERSETTINGS_MIXER1TYPE_CAMERAROLL = 3,
	MIXERSETTINGS_MIXER1TYPE_CAMERAPITCH = 4,
	MIXERSETTINGS_MIXER1TYPE_CAMERAYAW = 5,
	MIXERSETTINGS_MIXER1TYPE_ACCESSORY0 = 6,
	MIXERSETTINGS_MIXER1TYPE_ACCESSORY1 = 7,
	MIXERSETTINGS_MIXER1TYPE_ACCESSORY2 = 8,
	MIXERSETTINGS_MIXER1TYPE_ACCESSORY3 = 9,
	MIXERSETTINGS_MIXER1TYPE_ACCESSORY4 = 10,
	MIXERSETTINGS_MIXER1TYPE_ACCESSORY5 = 11,
	MIXERSETTINGS_MIXER1TYPE_LASTITEM = 12
};

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
	int8_t ThrottleCurve1;
	int8_t ThrottleCurve2;
	int8_t Roll;
	int8_t Pitch;
	int8_t Yaw;
} UAVT_MixerSettingsMixer1VectorType;

typedef struct {
	float MaxAccel;
	float FeedForward;
	float AccelTime;
	float DecelTime;
	UAVT_MixerSettingsThrottleCurve1Type ThrottleCurve1;	// float[5]
	UAVT_MixerSettingsThrottleCurve2Type ThrottleCurve2;	// float[5]
	uint8_t Curve2Source;	// enum
	uint8_t Mixer1Type;	// enum
	UAVT_MixerSettingsMixer1VectorType Mixer1Vector;	// int8[5]
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
    Filename: modulesettings.xml
    Object: ModuleSettings
    Comment: Optional module enable/disable configuration.
*************************************************************************************************/

#define MODULESETTINGS_OBJID 0x50780700

enum {
	MODULESETTINGS_ADMINSTATE_DISABLED = 0,
	MODULESETTINGS_ADMINSTATE_ENABLED = 1,
	MODULESETTINGS_ADMINSTATE_LASTITEM = 2
};

enum {
	MODULESETTINGS_TELEMETRYSPEED_2400 = 0,
	MODULESETTINGS_TELEMETRYSPEED_4800 = 1,
	MODULESETTINGS_TELEMETRYSPEED_9600 = 2,
	MODULESETTINGS_TELEMETRYSPEED_19200 = 3,
	MODULESETTINGS_TELEMETRYSPEED_38400 = 4,
	MODULESETTINGS_TELEMETRYSPEED_57600 = 5,
	MODULESETTINGS_TELEMETRYSPEED_115200 = 6,
	MODULESETTINGS_TELEMETRYSPEED_LASTITEM = 7
};

enum {
	MODULESETTINGS_GPSSPEED_2400 = 0,
	MODULESETTINGS_GPSSPEED_4800 = 1,
	MODULESETTINGS_GPSSPEED_9600 = 2,
	MODULESETTINGS_GPSSPEED_19200 = 3,
	MODULESETTINGS_GPSSPEED_38400 = 4,
	MODULESETTINGS_GPSSPEED_57600 = 5,
	MODULESETTINGS_GPSSPEED_115200 = 6,
	MODULESETTINGS_GPSSPEED_230400 = 7,
	MODULESETTINGS_GPSSPEED_LASTITEM = 8
};

enum {
	MODULESETTINGS_GPSDATAPROTOCOL_NMEA = 0,
	MODULESETTINGS_GPSDATAPROTOCOL_UBX = 1,
	MODULESETTINGS_GPSDATAPROTOCOL_LASTITEM = 2
};

enum {
	MODULESETTINGS_GPSAUTOCONFIGURE_FALSE = 0,
	MODULESETTINGS_GPSAUTOCONFIGURE_TRUE = 1,
	MODULESETTINGS_GPSAUTOCONFIGURE_LASTITEM = 2
};

enum {
	MODULESETTINGS_COMUSBBRIDGESPEED_2400 = 0,
	MODULESETTINGS_COMUSBBRIDGESPEED_4800 = 1,
	MODULESETTINGS_COMUSBBRIDGESPEED_9600 = 2,
	MODULESETTINGS_COMUSBBRIDGESPEED_19200 = 3,
	MODULESETTINGS_COMUSBBRIDGESPEED_38400 = 4,
	MODULESETTINGS_COMUSBBRIDGESPEED_57600 = 5,
	MODULESETTINGS_COMUSBBRIDGESPEED_115200 = 6,
	MODULESETTINGS_COMUSBBRIDGESPEED_LASTITEM = 7
};

enum {
	MODULESETTINGS_I2CVMPROGRAMSELECT_ENDIANTEST = 0,
	MODULESETTINGS_I2CVMPROGRAMSELECT_MATHTEST = 1,
	MODULESETTINGS_I2CVMPROGRAMSELECT_NONE = 2,
	MODULESETTINGS_I2CVMPROGRAMSELECT_OPBAROALTIMETER = 3,
	MODULESETTINGS_I2CVMPROGRAMSELECT_USER = 4,
	MODULESETTINGS_I2CVMPROGRAMSELECT_LASTITEM = 5
};

enum {
	MODULESETTINGS_MAVLINKSPEED_2400 = 0,
	MODULESETTINGS_MAVLINKSPEED_4800 = 1,
	MODULESETTINGS_MAVLINKSPEED_9600 = 2,
	MODULESETTINGS_MAVLINKSPEED_19200 = 3,
	MODULESETTINGS_MAVLINKSPEED_38400 = 4,
	MODULESETTINGS_MAVLINKSPEED_57600 = 5,
	MODULESETTINGS_MAVLINKSPEED_115200 = 6,
	MODULESETTINGS_MAVLINKSPEED_LASTITEM = 7
};

enum {
	MODULESETTINGS_LIGHTTELEMETRYSPEED_1200 = 0,
	MODULESETTINGS_LIGHTTELEMETRYSPEED_2400 = 1,
	MODULESETTINGS_LIGHTTELEMETRYSPEED_4800 = 2,
	MODULESETTINGS_LIGHTTELEMETRYSPEED_9600 = 3,
	MODULESETTINGS_LIGHTTELEMETRYSPEED_19200 = 4,
	MODULESETTINGS_LIGHTTELEMETRYSPEED_38400 = 5,
	MODULESETTINGS_LIGHTTELEMETRYSPEED_57600 = 6,
	MODULESETTINGS_LIGHTTELEMETRYSPEED_115200 = 7,
	MODULESETTINGS_LIGHTTELEMETRYSPEED_LASTITEM = 8
};

extern char UAVT_ModuleSettingsAdminStateOption[][42];
extern char UAVT_ModuleSettingsTelemetrySpeedOption[][42];
extern char UAVT_ModuleSettingsGPSSpeedOption[][42];
extern char UAVT_ModuleSettingsGPSDataProtocolOption[][42];
extern char UAVT_ModuleSettingsGPSAutoConfigureOption[][42];
extern char UAVT_ModuleSettingsComUsbBridgeSpeedOption[][42];
extern char UAVT_ModuleSettingsI2CVMProgramSelectOption[][42];
extern char UAVT_ModuleSettingsMavlinkSpeedOption[][42];
extern char UAVT_ModuleSettingsLightTelemetrySpeedOption[][42];
typedef struct {
	uint8_t Airspeed;
	uint8_t AltitudeHold;
	uint8_t Autotune;
	uint8_t Battery;
	uint8_t CameraStab;
	uint8_t ComUsbBridge;
	uint8_t FixedWingPathFollower;
	uint8_t Fault;
	uint8_t GPS;
	uint8_t OveroSync;
	uint8_t PathPlanner;
	uint8_t TxPID;
	uint8_t VtolPathFollower;
	uint8_t GroundPathFollower;
	uint8_t GenericI2CSensor;
	uint8_t UAVOMavlinkBridge;
	uint8_t UAVOLighttelemetryBridge;
	uint8_t VibrationAnalysis;
	uint8_t UAVOHoTTBridge;
	uint8_t UAVOFrSKYSensorHubBridge;
	uint8_t PicoC;
	uint8_t UAVOFrSkySPortBridge;
	uint8_t Geofence;
	uint8_t Logging;
} UAVT_ModuleSettingsAdminStateType;

typedef struct {
	UAVT_ModuleSettingsAdminStateType AdminState;	// enum[24]
	uint8_t TelemetrySpeed;	// enum
	uint8_t GPSSpeed;	// enum
	uint8_t GPSDataProtocol;	// enum
	uint8_t GPSAutoConfigure;	// enum
	uint8_t ComUsbBridgeSpeed;	// enum
	uint8_t I2CVMProgramSelect;	// enum
	uint8_t MavlinkSpeed;	// enum
	uint8_t LightTelemetrySpeed;	// enum
} UAVT_ModuleSettingsData;

extern UAVT_ModuleSettingsData uavtalk_ModuleSettingsData;


/*************************************************************************************************
    Filename: mwratesettings.xml
    Object: MWRateSettings
    Comment: PID settings used by the MWRate stabilization settings
*************************************************************************************************/

#define MWRATESETTINGS_OBJID 0xbd3b5f28

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_MWRateSettingsRollRatePIDType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_MWRateSettingsPitchRatePIDType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_MWRateSettingsYawRatePIDType;

typedef struct {
	UAVT_MWRateSettingsRollRatePIDType RollRatePID;	// float[4]
	UAVT_MWRateSettingsPitchRatePIDType PitchRatePID;	// float[4]
	UAVT_MWRateSettingsYawRatePIDType YawRatePID;	// float[4]
	float DerivativeGamma;
	uint8_t RollPitchRate;
	uint8_t YawRate;
} UAVT_MWRateSettingsData;

extern UAVT_MWRateSettingsData uavtalk_MWRateSettingsData;


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
    Filename: nedposition.xml
    Object: NEDPosition
    Comment: Contains the current position relative to @ref HomeLocation
*************************************************************************************************/

#define NEDPOSITION_OBJID 0x1fb15a00

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_NEDPositionData;

extern UAVT_NEDPositionData uavtalk_NEDPositionData;


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
    Filename: oplinksettings.xml
    Object: OPLinkSettings
    Comment: OPLink configurations options.
*************************************************************************************************/

#define OPLINKSETTINGS_OBJID 0x449737bc

enum {
	OPLINKSETTINGS_COORDINATOR_FALSE = 0,
	OPLINKSETTINGS_COORDINATOR_TRUE = 1,
	OPLINKSETTINGS_COORDINATOR_LASTITEM = 2
};

enum {
	OPLINKSETTINGS_PPM_FALSE = 0,
	OPLINKSETTINGS_PPM_TRUE = 1,
	OPLINKSETTINGS_PPM_LASTITEM = 2
};

enum {
	OPLINKSETTINGS_UAVTALK_FALSE = 0,
	OPLINKSETTINGS_UAVTALK_TRUE = 1,
	OPLINKSETTINGS_UAVTALK_LASTITEM = 2
};

enum {
	OPLINKSETTINGS_INPUTCONNECTION_HID = 0,
	OPLINKSETTINGS_INPUTCONNECTION_VCP = 1,
	OPLINKSETTINGS_INPUTCONNECTION_TELEMETRY = 2,
	OPLINKSETTINGS_INPUTCONNECTION_FLEXI = 3,
	OPLINKSETTINGS_INPUTCONNECTION_LASTITEM = 4
};

enum {
	OPLINKSETTINGS_OUTPUTCONNECTION_REMOTEHID = 0,
	OPLINKSETTINGS_OUTPUTCONNECTION_REMOTEVCP = 1,
	OPLINKSETTINGS_OUTPUTCONNECTION_REMOTETELEMETRY = 2,
	OPLINKSETTINGS_OUTPUTCONNECTION_REMOTEFLEXI = 3,
	OPLINKSETTINGS_OUTPUTCONNECTION_TELEMETRY = 4,
	OPLINKSETTINGS_OUTPUTCONNECTION_FLEXI = 5,
	OPLINKSETTINGS_OUTPUTCONNECTION_LASTITEM = 6
};

enum {
	OPLINKSETTINGS_COMSPEED_2400 = 0,
	OPLINKSETTINGS_COMSPEED_4800 = 1,
	OPLINKSETTINGS_COMSPEED_9600 = 2,
	OPLINKSETTINGS_COMSPEED_19200 = 3,
	OPLINKSETTINGS_COMSPEED_38400 = 4,
	OPLINKSETTINGS_COMSPEED_57600 = 5,
	OPLINKSETTINGS_COMSPEED_115200 = 6,
	OPLINKSETTINGS_COMSPEED_LASTITEM = 7
};

enum {
	OPLINKSETTINGS_MAXRFPOWER_1_25 = 0,
	OPLINKSETTINGS_MAXRFPOWER_1_6 = 1,
	OPLINKSETTINGS_MAXRFPOWER_3_16 = 2,
	OPLINKSETTINGS_MAXRFPOWER_6_3 = 3,
	OPLINKSETTINGS_MAXRFPOWER_12_6 = 4,
	OPLINKSETTINGS_MAXRFPOWER_25 = 5,
	OPLINKSETTINGS_MAXRFPOWER_50 = 6,
	OPLINKSETTINGS_MAXRFPOWER_100 = 7,
	OPLINKSETTINGS_MAXRFPOWER_LASTITEM = 8
};

extern char UAVT_OPLinkSettingsCoordinatorOption[][42];
extern char UAVT_OPLinkSettingsPPMOption[][42];
extern char UAVT_OPLinkSettingsUAVTalkOption[][42];
extern char UAVT_OPLinkSettingsInputConnectionOption[][42];
extern char UAVT_OPLinkSettingsOutputConnectionOption[][42];
extern char UAVT_OPLinkSettingsComSpeedOption[][42];
extern char UAVT_OPLinkSettingsMaxRFPowerOption[][42];
typedef struct {
	uint32_t PairID;
	uint32_t MinFrequency;
	uint32_t MaxFrequency;
	uint16_t SendTimeout;
	uint8_t Coordinator;	// enum
	uint8_t PPM;	// enum
	uint8_t UAVTalk;	// enum
	uint8_t InputConnection;	// enum
	uint8_t OutputConnection;	// enum
	uint8_t ComSpeed;	// enum
	uint8_t MaxRFPower;	// enum
	uint8_t MinPacketSize;
	uint8_t FrequencyCalibration;
	uint8_t AESKey[32];
} UAVT_OPLinkSettingsData;

extern UAVT_OPLinkSettingsData uavtalk_OPLinkSettingsData;


/*************************************************************************************************
    Filename: oplinkstatus.xml
    Object: OPLinkStatus
    Comment: OPLink device status.
*************************************************************************************************/

#define OPLINKSTATUS_OBJID 0x25e223f0

enum {
	OPLINKSTATUS_LINKSTATE_DISCONNECTED = 0,
	OPLINKSTATUS_LINKSTATE_CONNECTING = 1,
	OPLINKSTATUS_LINKSTATE_CONNECTED = 2,
	OPLINKSTATUS_LINKSTATE_LASTITEM = 3
};

extern char UAVT_OPLinkStatusLinkStateOption[][42];
typedef struct {
	uint32_t DeviceID;
	uint32_t PairIDs[4];
	uint16_t BoardRevision;
	uint16_t UAVTalkErrors;
	uint16_t TXRate;
	uint16_t RXRate;
	uint16_t TXSeq;
	uint16_t RXSeq;
	uint8_t Description[40];
	uint8_t CPUSerial[12];
	uint8_t BoardType;
	uint8_t RxGood;
	uint8_t RxCorrected;
	uint8_t RxErrors;
	uint8_t RxMissed;
	uint8_t RxFailure;
	uint8_t TxResent;
	uint8_t TxDropped;
	uint8_t TxFailure;
	uint8_t Resets;
	uint8_t Timeouts;
	int8_t RSSI;
	int8_t AFCCorrection;
	uint8_t LinkQuality;
	uint8_t LinkState;	// enum
	int8_t PairSignalStrengths[4];
} UAVT_OPLinkStatusData;

extern UAVT_OPLinkStatusData uavtalk_OPLinkStatusData;


/*************************************************************************************************
    Filename: overosyncsettings.xml
    Object: OveroSyncSettings
    Comment: Settings to control the behavior of the overo sync module
*************************************************************************************************/

#define OVEROSYNCSETTINGS_OBJID 0xa1abc278

enum {
	OVEROSYNCSETTINGS_LOGON_NEVER = 0,
	OVEROSYNCSETTINGS_LOGON_ALWAYS = 1,
	OVEROSYNCSETTINGS_LOGON_ARMED = 2,
	OVEROSYNCSETTINGS_LOGON_LASTITEM = 3
};

extern char UAVT_OveroSyncSettingsLogOnOption[][42];
typedef struct {
	uint8_t LogOn;	// enum
} UAVT_OveroSyncSettingsData;

extern UAVT_OveroSyncSettingsData uavtalk_OveroSyncSettingsData;


/*************************************************************************************************
    Filename: overosyncstats.xml
    Object: OveroSyncStats
    Comment: Maintains statistics on transfer rate to and from over
*************************************************************************************************/

#define OVEROSYNCSTATS_OBJID 0xd2085fac

enum {
	OVEROSYNCSTATS_CONNECTED_FALSE = 0,
	OVEROSYNCSTATS_CONNECTED_TRUE = 1,
	OVEROSYNCSTATS_CONNECTED_LASTITEM = 2
};

extern char UAVT_OveroSyncStatsConnectedOption[][42];
typedef struct {
	uint32_t Send;
	uint32_t Received;
	uint32_t FramesyncErrors;
	uint32_t UnderrunErrors;
	uint32_t DroppedUpdates;
	uint32_t Packets;
	uint8_t Connected;	// enum
} UAVT_OveroSyncStatsData;

extern UAVT_OveroSyncStatsData uavtalk_OveroSyncStatsData;


/*************************************************************************************************
    Filename: pathdesired.xml
    Object: PathDesired
    Comment: The endpoint or path the craft is trying to achieve.  Can come from @ref ManualControl or @ref PathPlanner
*************************************************************************************************/

#define PATHDESIRED_OBJID 0x8f1cd118

enum {
	PATHDESIRED_MODE_FLYENDPOINT = 0,
	PATHDESIRED_MODE_FLYVECTOR = 1,
	PATHDESIRED_MODE_FLYCIRCLERIGHT = 2,
	PATHDESIRED_MODE_FLYCIRCLELEFT = 3,
	PATHDESIRED_MODE_DRIVEENDPOINT = 4,
	PATHDESIRED_MODE_DRIVEVECTOR = 5,
	PATHDESIRED_MODE_DRIVECIRCLELEFT = 6,
	PATHDESIRED_MODE_DRIVECIRCLERIGHT = 7,
	PATHDESIRED_MODE_HOLDPOSITION = 8,
	PATHDESIRED_MODE_CIRCLEPOSITIONLEFT = 9,
	PATHDESIRED_MODE_CIRCLEPOSITIONRIGHT = 10,
	PATHDESIRED_MODE_LAND = 11,
	PATHDESIRED_MODE_LASTITEM = 12
};

extern char UAVT_PathDesiredModeOption[][42];
typedef struct {
	float North;
	float East;
	float Down;
} UAVT_PathDesiredStartType;

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_PathDesiredEndType;

typedef struct {
	UAVT_PathDesiredStartType Start;	// float[3]
	UAVT_PathDesiredEndType End;	// float[3]
	float StartingVelocity;
	float EndingVelocity;
	float ModeParameters;
	uint8_t Mode;	// enum
} UAVT_PathDesiredData;

extern UAVT_PathDesiredData uavtalk_PathDesiredData;


/*************************************************************************************************
    Filename: pathplannersettings.xml
    Object: PathPlannerSettings
    Comment: Settings for the @ref PathPlanner Module
*************************************************************************************************/

#define PATHPLANNERSETTINGS_OBJID 0x77a9e8f0

enum {
	PATHPLANNERSETTINGS_PREPROGRAMMEDPATH_NONE = 0,
	PATHPLANNERSETTINGS_PREPROGRAMMEDPATH_10M_BOX = 1,
	PATHPLANNERSETTINGS_PREPROGRAMMEDPATH_LOGO = 2,
	PATHPLANNERSETTINGS_PREPROGRAMMEDPATH_LASTITEM = 3
};

enum {
	PATHPLANNERSETTINGS_FLASHOPERATION_NONE = 0,
	PATHPLANNERSETTINGS_FLASHOPERATION_FAILED = 1,
	PATHPLANNERSETTINGS_FLASHOPERATION_COMPLETED = 2,
	PATHPLANNERSETTINGS_FLASHOPERATION_SAVE1 = 3,
	PATHPLANNERSETTINGS_FLASHOPERATION_SAVE2 = 4,
	PATHPLANNERSETTINGS_FLASHOPERATION_SAVE3 = 5,
	PATHPLANNERSETTINGS_FLASHOPERATION_SAVE4 = 6,
	PATHPLANNERSETTINGS_FLASHOPERATION_SAVE5 = 7,
	PATHPLANNERSETTINGS_FLASHOPERATION_LOAD1 = 8,
	PATHPLANNERSETTINGS_FLASHOPERATION_LOAD2 = 9,
	PATHPLANNERSETTINGS_FLASHOPERATION_LOAD3 = 10,
	PATHPLANNERSETTINGS_FLASHOPERATION_LOAD4 = 11,
	PATHPLANNERSETTINGS_FLASHOPERATION_LOAD5 = 12,
	PATHPLANNERSETTINGS_FLASHOPERATION_LASTITEM = 13
};

extern char UAVT_PathPlannerSettingsPreprogrammedPathOption[][42];
extern char UAVT_PathPlannerSettingsFlashOperationOption[][42];
typedef struct {
	uint8_t PreprogrammedPath;	// enum
	uint8_t FlashOperation;	// enum
} UAVT_PathPlannerSettingsData;

extern UAVT_PathPlannerSettingsData uavtalk_PathPlannerSettingsData;


/*************************************************************************************************
    Filename: pathstatus.xml
    Object: PathStatus
    Comment: Status of the current path mode  Can come from any @ref PathFollower module
*************************************************************************************************/

#define PATHSTATUS_OBJID 0x1cfb185a

enum {
	PATHSTATUS_STATE_INPROGRESS = 0,
	PATHSTATUS_STATE_COMPLETED = 1,
	PATHSTATUS_STATE_WARNING = 2,
	PATHSTATUS_STATE_CRITICAL = 3,
	PATHSTATUS_STATE_LASTITEM = 4
};

extern char UAVT_PathStatusStateOption[][42];
typedef struct {
	float fractional_progress;
	float error;
	uint8_t State;	// enum
} UAVT_PathStatusData;

extern UAVT_PathStatusData uavtalk_PathStatusData;


/*************************************************************************************************
    Filename: picocsettings.xml
    Object: PicoCSettings
    Comment: Settings for the @ref PicoC Interpreter Module
*************************************************************************************************/

#define PICOCSETTINGS_OBJID 0x5db16ffe

enum {
	PICOCSETTINGS_STARTUP_DISABLED = 0,
	PICOCSETTINGS_STARTUP_ONBOOT = 1,
	PICOCSETTINGS_STARTUP_WHENARMED = 2,
	PICOCSETTINGS_STARTUP_LASTITEM = 3
};

enum {
	PICOCSETTINGS_SOURCE_DISABLED = 0,
	PICOCSETTINGS_SOURCE_DEMO = 1,
	PICOCSETTINGS_SOURCE_INTERACTIVE = 2,
	PICOCSETTINGS_SOURCE_FILE = 3,
	PICOCSETTINGS_SOURCE_LASTITEM = 4
};

enum {
	PICOCSETTINGS_COMSPEED_2400 = 0,
	PICOCSETTINGS_COMSPEED_4800 = 1,
	PICOCSETTINGS_COMSPEED_9600 = 2,
	PICOCSETTINGS_COMSPEED_19200 = 3,
	PICOCSETTINGS_COMSPEED_38400 = 4,
	PICOCSETTINGS_COMSPEED_57600 = 5,
	PICOCSETTINGS_COMSPEED_115200 = 6,
	PICOCSETTINGS_COMSPEED_LASTITEM = 7
};

extern char UAVT_PicoCSettingsStartupOption[][42];
extern char UAVT_PicoCSettingsSourceOption[][42];
extern char UAVT_PicoCSettingsComSpeedOption[][42];
typedef struct {
	uint32_t MaxFileSize;
	uint32_t TaskStackSize;
	uint32_t PicoCStackSize;
	uint8_t BootFileID;
	uint8_t Startup;	// enum
	uint8_t Source;	// enum
	uint8_t ComSpeed;	// enum
} UAVT_PicoCSettingsData;

extern UAVT_PicoCSettingsData uavtalk_PicoCSettingsData;


/*************************************************************************************************
    Filename: picocstatus.xml
    Object: PicoCStatus
    Comment: status information of the @ref PicoC Interpreter Module.
*************************************************************************************************/

#define PICOCSTATUS_OBJID 0xf132538a

enum {
	PICOCSTATUS_COMMAND_IDLE = 0,
	PICOCSTATUS_COMMAND_STARTSCRIPT = 1,
	PICOCSTATUS_COMMAND_USARTMODE = 2,
	PICOCSTATUS_COMMAND_GETSECTOR = 3,
	PICOCSTATUS_COMMAND_SETSECTOR = 4,
	PICOCSTATUS_COMMAND_LOADFILE = 5,
	PICOCSTATUS_COMMAND_SAVEFILE = 6,
	PICOCSTATUS_COMMAND_DELETEFILE = 7,
	PICOCSTATUS_COMMAND_FORMATPARTITION = 8,
	PICOCSTATUS_COMMAND_LASTITEM = 9
};

extern char UAVT_PicoCStatusCommandOption[][42];
typedef struct {
	int16_t ExitValue;
	int16_t TestValue;
	uint16_t SectorID;
	uint8_t FileID;
	uint8_t Command;	// enum
	int8_t CommandError;
	uint8_t Sector[32];
} UAVT_PicoCStatusData;

extern UAVT_PicoCStatusData uavtalk_PicoCStatusData;


/*************************************************************************************************
    Filename: poilocation.xml
    Object: PoiLocation
    Comment: Contains the current Point of interest relative to @ref HomeLocation
*************************************************************************************************/

#define POILOCATION_OBJID 0x17e829b8

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_PoiLocationData;

extern UAVT_PoiLocationData uavtalk_PoiLocationData;


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

#define RECEIVERACTIVITY_OBJID 0xc02377e6

enum {
	RECEIVERACTIVITY_ACTIVEGROUP_PWM = 0,
	RECEIVERACTIVITY_ACTIVEGROUP_PPM = 1,
	RECEIVERACTIVITY_ACTIVEGROUP_DSM__MAINPORT_ = 2,
	RECEIVERACTIVITY_ACTIVEGROUP_DSM__FLEXIPORT_ = 3,
	RECEIVERACTIVITY_ACTIVEGROUP_S_BUS = 4,
	RECEIVERACTIVITY_ACTIVEGROUP_GCS = 5,
	RECEIVERACTIVITY_ACTIVEGROUP_HOTT_SUM = 6,
	RECEIVERACTIVITY_ACTIVEGROUP_NONE = 7,
	RECEIVERACTIVITY_ACTIVEGROUP_LASTITEM = 8
};

extern char UAVT_ReceiverActivityActiveGroupOption[][42];
typedef struct {
	uint8_t ActiveGroup;	// enum
	uint8_t ActiveChannel;
} UAVT_ReceiverActivityData;

extern UAVT_ReceiverActivityData uavtalk_ReceiverActivityData;


/*************************************************************************************************
    Filename: sensorsettings.xml
    Object: SensorSettings
    Comment: Settings for the @ref Attitude module
*************************************************************************************************/

#define SENSORSETTINGS_OBJID 0xadb3b106

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_SensorSettingsAccelBiasType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_SensorSettingsAccelScaleType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_SensorSettingsGyroScaleType;

typedef struct {
	float n;
	float T;
	float T2;
	float T3;
} UAVT_SensorSettingsXGyroTempCoeffType;

typedef struct {
	float n;
	float T;
	float T2;
	float T3;
} UAVT_SensorSettingsYGyroTempCoeffType;

typedef struct {
	float n;
	float T;
	float T2;
	float T3;
} UAVT_SensorSettingsZGyroTempCoeffType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_SensorSettingsMagBiasType;

typedef struct {
	float X;
	float Y;
	float Z;
} UAVT_SensorSettingsMagScaleType;

typedef struct {
	UAVT_SensorSettingsAccelBiasType AccelBias;	// float[3]
	UAVT_SensorSettingsAccelScaleType AccelScale;	// float[3]
	UAVT_SensorSettingsGyroScaleType GyroScale;	// float[3]
	UAVT_SensorSettingsXGyroTempCoeffType XGyroTempCoeff;	// float[4]
	UAVT_SensorSettingsYGyroTempCoeffType YGyroTempCoeff;	// float[4]
	UAVT_SensorSettingsZGyroTempCoeffType ZGyroTempCoeff;	// float[4]
	UAVT_SensorSettingsMagBiasType MagBias;	// float[3]
	UAVT_SensorSettingsMagScaleType MagScale;	// float[3]
	float ZAccelOffset;
} UAVT_SensorSettingsData;

extern UAVT_SensorSettingsData uavtalk_SensorSettingsData;


/*************************************************************************************************
    Filename: sessionmanaging.xml
    Object: SessionManaging
    Comment: Provides session managing to uavtalk
*************************************************************************************************/

#define SESSIONMANAGING_OBJID 0x89034e4a

typedef struct {
	uint32_t ObjectID;
	uint16_t SessionID;
	uint8_t ObjectInstances;
	uint8_t NumberOfObjects;
	uint8_t ObjectOfInterestIndex;
} UAVT_SessionManagingData;

extern UAVT_SessionManagingData uavtalk_SessionManagingData;


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

#define STABILIZATIONDESIRED_OBJID 0xa237dd8e

enum {
	STABILIZATIONDESIRED_STABILIZATIONMODE_NONE = 0,
	STABILIZATIONDESIRED_STABILIZATIONMODE_RATE = 1,
	STABILIZATIONDESIRED_STABILIZATIONMODE_ATTITUDE = 2,
	STABILIZATIONDESIRED_STABILIZATIONMODE_AXISLOCK = 3,
	STABILIZATIONDESIRED_STABILIZATIONMODE_WEAKLEVELING = 4,
	STABILIZATIONDESIRED_STABILIZATIONMODE_VIRTUALBAR = 5,
	STABILIZATIONDESIRED_STABILIZATIONMODE_HORIZON = 6,
	STABILIZATIONDESIRED_STABILIZATIONMODE_RATEMW = 7,
	STABILIZATIONDESIRED_STABILIZATIONMODE_SYSTEMIDENT = 8,
	STABILIZATIONDESIRED_STABILIZATIONMODE_POI = 9,
	STABILIZATIONDESIRED_STABILIZATIONMODE_COORDINATEDFLIGHT = 10,
	STABILIZATIONDESIRED_STABILIZATIONMODE_LASTITEM = 11
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

#define STABILIZATIONSETTINGS_OBJID 0x89f756cc

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

extern char UAVT_StabilizationSettingsVbarPiroCompOption[][42];
extern char UAVT_StabilizationSettingsLowThrottleZeroIntegralOption[][42];
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
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_StabilizationSettingsPoiMaximumRateType;

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
	float Kd;
} UAVT_StabilizationSettingsVbarRollPIDType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
} UAVT_StabilizationSettingsVbarPitchPIDType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
} UAVT_StabilizationSettingsVbarYawPIDType;

typedef struct {
	float Kp;
	float Ki;
	float ILimit;
} UAVT_StabilizationSettingsCoordinatedFlightYawPIType;

typedef struct {
	uint8_t Roll;
	uint8_t Pitch;
	uint8_t Yaw;
} UAVT_StabilizationSettingsRateExpoType;

typedef struct {
	uint8_t Threshold;
	uint8_t Attenuation;
} UAVT_StabilizationSettingsRollRateTPAType;

typedef struct {
	uint8_t Threshold;
	uint8_t Attenuation;
} UAVT_StabilizationSettingsPitchRateTPAType;

typedef struct {
	uint8_t Threshold;
	uint8_t Attenuation;
} UAVT_StabilizationSettingsYawRateTPAType;

typedef struct {
	UAVT_StabilizationSettingsManualRateType ManualRate;	// float[3]
	UAVT_StabilizationSettingsMaximumRateType MaximumRate;	// float[3]
	UAVT_StabilizationSettingsPoiMaximumRateType PoiMaximumRate;	// float[3]
	UAVT_StabilizationSettingsRollRatePIDType RollRatePID;	// float[4]
	UAVT_StabilizationSettingsPitchRatePIDType PitchRatePID;	// float[4]
	UAVT_StabilizationSettingsYawRatePIDType YawRatePID;	// float[4]
	UAVT_StabilizationSettingsRollPIType RollPI;	// float[3]
	UAVT_StabilizationSettingsPitchPIType PitchPI;	// float[3]
	UAVT_StabilizationSettingsYawPIType YawPI;	// float[3]
	UAVT_StabilizationSettingsVbarSensitivityType VbarSensitivity;	// float[3]
	UAVT_StabilizationSettingsVbarRollPIDType VbarRollPID;	// float[3]
	UAVT_StabilizationSettingsVbarPitchPIDType VbarPitchPID;	// float[3]
	UAVT_StabilizationSettingsVbarYawPIDType VbarYawPID;	// float[3]
	float VbarTau;
	float GyroTau;
	float DerivativeGamma;
	float WeakLevelingKp;
	UAVT_StabilizationSettingsCoordinatedFlightYawPIType CoordinatedFlightYawPI;	// float[3]
	uint8_t RollMax;
	uint8_t PitchMax;
	uint8_t YawMax;
	UAVT_StabilizationSettingsRateExpoType RateExpo;	// uint8[3]
	UAVT_StabilizationSettingsRollRateTPAType RollRateTPA;	// uint8[2]
	UAVT_StabilizationSettingsPitchRateTPAType PitchRateTPA;	// uint8[2]
	UAVT_StabilizationSettingsYawRateTPAType YawRateTPA;	// uint8[2]
	int8_t VbarGyroSuppress;
	uint8_t VbarPiroComp;	// enum
	uint8_t VbarMaxAngle;
	uint8_t DerivativeCutoff;
	uint8_t MaxAxisLock;
	uint8_t MaxAxisLockRate;
	uint8_t MaxWeakLevelingRate;
	uint8_t LowThrottleZeroIntegral;	// enum
} UAVT_StabilizationSettingsData;

extern UAVT_StabilizationSettingsData uavtalk_StabilizationSettingsData;


/*************************************************************************************************
    Filename: stateestimation.xml
    Object: StateEstimation
    Comment: Settings for how to estimate the state
*************************************************************************************************/

#define STATEESTIMATION_OBJID 0xba09f7c2

enum {
	STATEESTIMATION_ATTITUDEFILTER_COMPLEMENTARY = 0,
	STATEESTIMATION_ATTITUDEFILTER_INSINDOOR = 1,
	STATEESTIMATION_ATTITUDEFILTER_INSOUTDOOR = 2,
	STATEESTIMATION_ATTITUDEFILTER_LASTITEM = 3
};

enum {
	STATEESTIMATION_NAVIGATIONFILTER_NONE = 0,
	STATEESTIMATION_NAVIGATIONFILTER_RAW = 1,
	STATEESTIMATION_NAVIGATIONFILTER_INS = 2,
	STATEESTIMATION_NAVIGATIONFILTER_LASTITEM = 3
};

extern char UAVT_StateEstimationAttitudeFilterOption[][42];
extern char UAVT_StateEstimationNavigationFilterOption[][42];
typedef struct {
	uint8_t AttitudeFilter;	// enum
	uint8_t NavigationFilter;	// enum
} UAVT_StateEstimationData;

extern UAVT_StateEstimationData uavtalk_StateEstimationData;


/*************************************************************************************************
    Filename: systemalarms.xml
    Object: SystemAlarms
    Comment: Alarms from OpenPilot to indicate failure conditions or warnings.  Set by various modules.
*************************************************************************************************/

#define SYSTEMALARMS_OBJID 0xe25dd70e

enum {
	SYSTEMALARMS_ALARM_UNINITIALISED = 0,
	SYSTEMALARMS_ALARM_OK = 1,
	SYSTEMALARMS_ALARM_WARNING = 2,
	SYSTEMALARMS_ALARM_ERROR = 3,
	SYSTEMALARMS_ALARM_CRITICAL = 4,
	SYSTEMALARMS_ALARM_LASTITEM = 5
};

enum {
	SYSTEMALARMS_CONFIGERROR_STABILIZATION = 0,
	SYSTEMALARMS_CONFIGERROR_MULTIROTOR = 1,
	SYSTEMALARMS_CONFIGERROR_AUTOTUNE = 2,
	SYSTEMALARMS_CONFIGERROR_ALTITUDEHOLD = 3,
	SYSTEMALARMS_CONFIGERROR_VELOCITYCONTROL = 4,
	SYSTEMALARMS_CONFIGERROR_POSITIONHOLD = 5,
	SYSTEMALARMS_CONFIGERROR_PATHPLANNER = 6,
	SYSTEMALARMS_CONFIGERROR_NAVFILTER = 7,
	SYSTEMALARMS_CONFIGERROR_UNSAFETOARM = 8,
	SYSTEMALARMS_CONFIGERROR_UNDEFINED = 9,
	SYSTEMALARMS_CONFIGERROR_NONE = 10,
	SYSTEMALARMS_CONFIGERROR_LASTITEM = 11
};

enum {
	SYSTEMALARMS_MANUALCONTROL_SETTINGS = 0,
	SYSTEMALARMS_MANUALCONTROL_NORX = 1,
	SYSTEMALARMS_MANUALCONTROL_ACCESSORY = 2,
	SYSTEMALARMS_MANUALCONTROL_ALTITUDEHOLD = 3,
	SYSTEMALARMS_MANUALCONTROL_PATHFOLLOWER = 4,
	SYSTEMALARMS_MANUALCONTROL_UNDEFINED = 5,
	SYSTEMALARMS_MANUALCONTROL_NONE = 6,
	SYSTEMALARMS_MANUALCONTROL_LASTITEM = 7
};

enum {
	SYSTEMALARMS_STATEESTIMATION_GYRO_QUEUE_NOT_UPDATING = 0,
	SYSTEMALARMS_STATEESTIMATION_ACCELEROMETER_QUEUE_NOT_UPDATING = 1,
	SYSTEMALARMS_STATEESTIMATION_NO_GPS = 2,
	SYSTEMALARMS_STATEESTIMATION_NO_MAGNETOMETER = 3,
	SYSTEMALARMS_STATEESTIMATION_NO_BAROMETER = 4,
	SYSTEMALARMS_STATEESTIMATION_NO_HOME = 5,
	SYSTEMALARMS_STATEESTIMATION_TOO_FEW_SATELLITES = 6,
	SYSTEMALARMS_STATEESTIMATION_PDOP_TOO_HIGH = 7,
	SYSTEMALARMS_STATEESTIMATION_UNDEFINED = 8,
	SYSTEMALARMS_STATEESTIMATION_NONE = 9,
	SYSTEMALARMS_STATEESTIMATION_LASTITEM = 10
};

extern char UAVT_SystemAlarmsAlarmOption[][42];
extern char UAVT_SystemAlarmsConfigErrorOption[][42];
extern char UAVT_SystemAlarmsManualControlOption[][42];
extern char UAVT_SystemAlarmsStateEstimationOption[][42];
typedef struct {
	uint8_t OutOfMemory;
	uint8_t CPUOverload;
	uint8_t StackOverflow;
	uint8_t SystemConfiguration;
	uint8_t EventSystem;
	uint8_t Telemetry;
	uint8_t ManualControl;
	uint8_t Actuator;
	uint8_t Attitude;
	uint8_t Sensors;
	uint8_t Stabilization;
	uint8_t Geofence;
	uint8_t PathFollower;
	uint8_t PathPlanner;
	uint8_t Battery;
	uint8_t FlightTime;
	uint8_t I2C;
	uint8_t GPS;
	uint8_t AltitudeHold;
	uint8_t BootFault;
} UAVT_SystemAlarmsAlarmType;

typedef struct {
	UAVT_SystemAlarmsAlarmType Alarm;	// enum[20]
	uint8_t ConfigError;	// enum
	uint8_t ManualControl;	// enum
	uint8_t StateEstimation;	// enum
} UAVT_SystemAlarmsData;

extern UAVT_SystemAlarmsData uavtalk_SystemAlarmsData;


/*************************************************************************************************
    Filename: systemident.xml
    Object: SystemIdent
    Comment: The input to the relay tuning.
*************************************************************************************************/

#define SYSTEMIDENT_OBJID 0xadafddf2

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_SystemIdentBetaType;

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_SystemIdentBiasType;

typedef struct {
	float Roll;
	float Pitch;
	float Yaw;
} UAVT_SystemIdentNoiseType;

typedef struct {
	float Tau;
	UAVT_SystemIdentBetaType Beta;	// float[3]
	UAVT_SystemIdentBiasType Bias;	// float[3]
	UAVT_SystemIdentNoiseType Noise;	// float[3]
	float Period;
} UAVT_SystemIdentData;

extern UAVT_SystemIdentData uavtalk_SystemIdentData;


/*************************************************************************************************
    Filename: systemsettings.xml
    Object: SystemSettings
    Comment: Select airframe type.  Currently used by @ref ActuatorModule to choose mixing from @ref ActuatorDesired to @ref ActuatorCommand
*************************************************************************************************/

#define SYSTEMSETTINGS_OBJID 0x6f3bb6b0

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
	uint32_t AirframeCategorySpecificConfiguration[4];
	uint8_t AirframeType;	// enum
} UAVT_SystemSettingsData;

extern UAVT_SystemSettingsData uavtalk_SystemSettingsData;


/*************************************************************************************************
    Filename: systemstats.xml
    Object: SystemStats
    Comment: CPU and memory usage from OpenPilot computer.
*************************************************************************************************/

#define SYSTEMSTATS_OBJID 0x74e632d4

typedef struct {
	uint32_t FlightTime;
	uint32_t HeapRemaining;
	uint32_t EventSystemWarningID;
	uint32_t ObjectManagerCallbackID;
	uint32_t ObjectManagerQueueID;
	uint16_t IRQStackRemaining;
	uint8_t CPULoad;
	int8_t CPUTemp;
} UAVT_SystemStatsData;

extern UAVT_SystemStatsData uavtalk_SystemStatsData;


/*************************************************************************************************
    Filename: tabletinfo.xml
    Object: TabletInfo
    Comment: The information from the tablet to the UAVO.
*************************************************************************************************/

#define TABLETINFO_OBJID 0xb80cc3b2

enum {
	TABLETINFO_CONNECTED_FALSE = 0,
	TABLETINFO_CONNECTED_TRUE = 1,
	TABLETINFO_CONNECTED_LASTITEM = 2
};

enum {
	TABLETINFO_TABLETMODEDESIRED_POSITIONHOLD = 0,
	TABLETINFO_TABLETMODEDESIRED_RETURNTOHOME = 1,
	TABLETINFO_TABLETMODEDESIRED_RETURNTOTABLET = 2,
	TABLETINFO_TABLETMODEDESIRED_PATHPLANNER = 3,
	TABLETINFO_TABLETMODEDESIRED_FOLLOWME = 4,
	TABLETINFO_TABLETMODEDESIRED_LAND = 5,
	TABLETINFO_TABLETMODEDESIRED_CAMERAPOI = 6,
	TABLETINFO_TABLETMODEDESIRED_LASTITEM = 7
};

enum {
	TABLETINFO_POI_FALSE = 0,
	TABLETINFO_POI_TRUE = 1,
	TABLETINFO_POI_LASTITEM = 2
};

extern char UAVT_TabletInfoConnectedOption[][42];
extern char UAVT_TabletInfoTabletModeDesiredOption[][42];
extern char UAVT_TabletInfoPOIOption[][42];
typedef struct {
	int32_t Latitude;
	int32_t Longitude;
	float Altitude;
	uint8_t Connected;	// enum
	uint8_t TabletModeDesired;	// enum
	uint8_t POI;	// enum
} UAVT_TabletInfoData;

extern UAVT_TabletInfoData uavtalk_TabletInfoData;


/*************************************************************************************************
    Filename: taskinfo.xml
    Object: TaskInfo
    Comment: Task information
*************************************************************************************************/

#define TASKINFO_OBJID 0xc6f6d160

enum {
	TASKINFO_RUNNING_FALSE = 0,
	TASKINFO_RUNNING_TRUE = 1,
	TASKINFO_RUNNING_LASTITEM = 2
};

extern char UAVT_TaskInfoRunningOption[][42];
typedef struct {
	uint16_t System;
	uint16_t Actuator;
	uint16_t Attitude;
	uint16_t Sensors;
	uint16_t TelemetryTx;
	uint16_t TelemetryTxPri;
	uint16_t TelemetryRx;
	uint16_t GPS;
	uint16_t ManualControl;
	uint16_t Altitude;
	uint16_t Airspeed;
	uint16_t Stabilization;
	uint16_t AltitudeHold;
	uint16_t PathPlanner;
	uint16_t PathFollower;
	uint16_t FlightPlan;
	uint16_t Com2UsbBridge;
	uint16_t Usb2ComBridge;
	uint16_t OveroSync;
	uint16_t ModemRx;
	uint16_t ModemTx;
	uint16_t ModemStat;
	uint16_t Autotune;
	uint16_t EventDispatcher;
	uint16_t GenericI2CSensor;
	uint16_t UAVOMavlinkBridge;
	uint16_t UAVOLighttelemetryBridge;
	uint16_t UAVORelay;
	uint16_t VibrationAnalysis;
	uint16_t Battery;
	uint16_t UAVOHoTTBridge;
	uint16_t UAVOFrSKYSensorHubBridge;
	uint16_t PicoC;
	uint16_t Logging;
	uint16_t UAVOFrSkySPortBridge;
} UAVT_TaskInfoStackRemainingType;

typedef struct {
	uint8_t System;
	uint8_t Actuator;
	uint8_t Attitude;
	uint8_t Sensors;
	uint8_t TelemetryTx;
	uint8_t TelemetryTxPri;
	uint8_t TelemetryRx;
	uint8_t GPS;
	uint8_t ManualControl;
	uint8_t Altitude;
	uint8_t Airspeed;
	uint8_t Stabilization;
	uint8_t AltitudeHold;
	uint8_t PathPlanner;
	uint8_t PathFollower;
	uint8_t FlightPlan;
	uint8_t Com2UsbBridge;
	uint8_t Usb2ComBridge;
	uint8_t OveroSync;
	uint8_t ModemRx;
	uint8_t ModemTx;
	uint8_t ModemStat;
	uint8_t Autotune;
	uint8_t EventDispatcher;
	uint8_t GenericI2CSensor;
	uint8_t UAVOMavlinkBridge;
	uint8_t UAVOLighttelemetryBridge;
	uint8_t UAVORelay;
	uint8_t VibrationAnalysis;
	uint8_t Battery;
	uint8_t UAVOHoTTBridge;
	uint8_t UAVOFrSKYSBridge;
	uint8_t PicoC;
	uint8_t Logging;
	uint8_t UAVOFrSkySPortBridge;
} UAVT_TaskInfoRunningType;

typedef struct {
	uint8_t System;
	uint8_t Actuator;
	uint8_t Attitude;
	uint8_t Sensors;
	uint8_t TelemetryTx;
	uint8_t TelemetryTxPri;
	uint8_t TelemetryRx;
	uint8_t GPS;
	uint8_t ManualControl;
	uint8_t Altitude;
	uint8_t Airspeed;
	uint8_t Stabilization;
	uint8_t AltitudeHold;
	uint8_t PathPlanner;
	uint8_t PathFollower;
	uint8_t FlightPlan;
	uint8_t Com2UsbBridge;
	uint8_t Usb2ComBridge;
	uint8_t OveroSync;
	uint8_t ModemRx;
	uint8_t ModemTx;
	uint8_t ModemStat;
	uint8_t Autotune;
	uint8_t EventDispatcher;
	uint8_t GenericI2CSensor;
	uint8_t UAVOMavlinkBridge;
	uint8_t UAVOLighttelemetryBridge;
	uint8_t UAVORelay;
	uint8_t VibrationAnalysis;
	uint8_t Battery;
	uint8_t UAVOHoTTBridge;
	uint8_t UAVOFrSKYSensorHubBridge;
	uint8_t PicoC;
	uint8_t Logging;
	uint8_t UAVOFrSkySPortBridge;
} UAVT_TaskInfoRunningTimeType;

typedef struct {
	UAVT_TaskInfoStackRemainingType StackRemaining;	// uint16[35]
	UAVT_TaskInfoRunningType Running;	// enum[35]
	UAVT_TaskInfoRunningTimeType RunningTime;	// uint8[35]
} UAVT_TaskInfoData;

extern UAVT_TaskInfoData uavtalk_TaskInfoData;


/*************************************************************************************************
    Filename: trimanglessettings.xml
    Object: TrimAnglesSettings
    Comment: The trim angle required for the UAV to fly straight and level.
*************************************************************************************************/

#define TRIMANGLESSETTINGS_OBJID 0x4e09a748

typedef struct {
	float Roll;
	float Pitch;
} UAVT_TrimAnglesSettingsData;

extern UAVT_TrimAnglesSettingsData uavtalk_TrimAnglesSettingsData;


/*************************************************************************************************
    Filename: trimangles.xml
    Object: TrimAngles
    Comment: The trim angle required for the UAV to fly straight and level.
*************************************************************************************************/

#define TRIMANGLES_OBJID 0x90b8c0de

typedef struct {
	float Roll;
	float Pitch;
} UAVT_TrimAnglesData;

extern UAVT_TrimAnglesData uavtalk_TrimAnglesData;


/*************************************************************************************************
    Filename: txpidsettings.xml
    Object: TxPIDSettings
    Comment: Settings used by @ref TxPID optional module to tune PID settings using R/C transmitter
*************************************************************************************************/

#define TXPIDSETTINGS_OBJID 0xf25577cc

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
	TXPIDSETTINGS_PIDS_ROLL_VBARSENSITIVITY = 30,
	TXPIDSETTINGS_PIDS_PITCH_VBARSENSITIVITY = 31,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_VBARSENSITIVITY = 32,
	TXPIDSETTINGS_PIDS_YAW_VBARSENSITIVITY = 33,
	TXPIDSETTINGS_PIDS_ROLL_VBAR_KP = 34,
	TXPIDSETTINGS_PIDS_PITCH_VBAR_KP = 35,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_VBAR_KP = 36,
	TXPIDSETTINGS_PIDS_YAW_VBAR_KP = 37,
	TXPIDSETTINGS_PIDS_ROLL_VBAR_KI = 38,
	TXPIDSETTINGS_PIDS_PITCH_VBAR_KI = 39,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_VBAR_KI = 40,
	TXPIDSETTINGS_PIDS_YAW_VBAR_KI = 41,
	TXPIDSETTINGS_PIDS_ROLL_VBAR_KD = 42,
	TXPIDSETTINGS_PIDS_PITCH_VBAR_KD = 43,
	TXPIDSETTINGS_PIDS_ROLL_PITCH_VBAR_KD = 44,
	TXPIDSETTINGS_PIDS_YAW_VBAR_KD = 45,
	TXPIDSETTINGS_PIDS_LASTITEM = 46
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
    Filename: ubloxinfo.xml
    Object: UBloxInfo
    Comment: UBlox specific information
*************************************************************************************************/

#define UBLOXINFO_OBJID 0xc5302b12

typedef struct {
	float swVersion;
	uint32_t ParseErrors;
	uint8_t hwVersion[8];
} UAVT_UBloxInfoData;

extern UAVT_UBloxInfoData uavtalk_UBloxInfoData;


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
    Filename: vibrationanalysisoutput.xml
    Object: VibrationAnalysisOutput
    Comment: FFT output from @VibrationTest module.
*************************************************************************************************/

#define VIBRATIONANALYSISOUTPUT_OBJID 0xd02b0a44

typedef struct {
	float x;
	float y;
	float z;
} UAVT_VibrationAnalysisOutputData;

extern UAVT_VibrationAnalysisOutputData uavtalk_VibrationAnalysisOutputData;


/*************************************************************************************************
    Filename: vibrationanalysissettings.xml
    Object: VibrationAnalysisSettings
    Comment: Settings for the @ref VibrationTest Module
*************************************************************************************************/

#define VIBRATIONANALYSISSETTINGS_OBJID 0x5c5c96b6

enum {
	VIBRATIONANALYSISSETTINGS_FFTWINDOWSIZE_16 = 0,
	VIBRATIONANALYSISSETTINGS_FFTWINDOWSIZE_64 = 1,
	VIBRATIONANALYSISSETTINGS_FFTWINDOWSIZE_256 = 2,
	VIBRATIONANALYSISSETTINGS_FFTWINDOWSIZE_1024 = 3,
	VIBRATIONANALYSISSETTINGS_FFTWINDOWSIZE_LASTITEM = 4
};

enum {
	VIBRATIONANALYSISSETTINGS_TESTINGSTATUS_OFF = 0,
	VIBRATIONANALYSISSETTINGS_TESTINGSTATUS_ON = 1,
	VIBRATIONANALYSISSETTINGS_TESTINGSTATUS_LASTITEM = 2
};

extern char UAVT_VibrationAnalysisSettingsFFTWindowSizeOption[][42];
extern char UAVT_VibrationAnalysisSettingsTestingStatusOption[][42];
typedef struct {
	uint16_t SampleRate;
	uint8_t FFTWindowSize;	// enum
	uint8_t TestingStatus;	// enum
} UAVT_VibrationAnalysisSettingsData;

extern UAVT_VibrationAnalysisSettingsData uavtalk_VibrationAnalysisSettingsData;


/*************************************************************************************************
    Filename: vtolpathfollowersettings.xml
    Object: VtolPathFollowerSettings
    Comment: Settings for the @ref VtolPathFollowerModule
*************************************************************************************************/

#define VTOLPATHFOLLOWERSETTINGS_OBJID 0xc10e2a3e

enum {
	VTOLPATHFOLLOWERSETTINGS_THROTTLECONTROL_FALSE = 0,
	VTOLPATHFOLLOWERSETTINGS_THROTTLECONTROL_TRUE = 1,
	VTOLPATHFOLLOWERSETTINGS_THROTTLECONTROL_LASTITEM = 2
};

enum {
	VTOLPATHFOLLOWERSETTINGS_VELOCITYCHANGEPREDICTION_FALSE = 0,
	VTOLPATHFOLLOWERSETTINGS_VELOCITYCHANGEPREDICTION_TRUE = 1,
	VTOLPATHFOLLOWERSETTINGS_VELOCITYCHANGEPREDICTION_LASTITEM = 2
};

enum {
	VTOLPATHFOLLOWERSETTINGS_YAWMODE_RATE = 0,
	VTOLPATHFOLLOWERSETTINGS_YAWMODE_AXISLOCK = 1,
	VTOLPATHFOLLOWERSETTINGS_YAWMODE_ATTITUDE = 2,
	VTOLPATHFOLLOWERSETTINGS_YAWMODE_PATH = 3,
	VTOLPATHFOLLOWERSETTINGS_YAWMODE_POI = 4,
	VTOLPATHFOLLOWERSETTINGS_YAWMODE_LASTITEM = 5
};

extern char UAVT_VtolPathFollowerSettingsThrottleControlOption[][42];
extern char UAVT_VtolPathFollowerSettingsVelocityChangePredictionOption[][42];
extern char UAVT_VtolPathFollowerSettingsYawModeOption[][42];
typedef struct {
	float Kp;
	float Ki;
	float ILimit;
} UAVT_VtolPathFollowerSettingsHorizontalPosPIType;

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float ILimit;
} UAVT_VtolPathFollowerSettingsHorizontalVelPIDType;

typedef struct {
	UAVT_VtolPathFollowerSettingsHorizontalPosPIType HorizontalPosPI;	// float[3]
	UAVT_VtolPathFollowerSettingsHorizontalVelPIDType HorizontalVelPID;	// float[4]
	float VelocityFeedforward;
	float MaxRollPitch;
	int32_t UpdatePeriod;
	float LandingRate;
	uint16_t HorizontalVelMax;
	uint16_t VerticalVelMax;
	uint8_t ThrottleControl;	// enum
	uint8_t VelocityChangePrediction;	// enum
	uint8_t EndpointRadius;
	uint8_t YawMode;	// enum
} UAVT_VtolPathFollowerSettingsData;

extern UAVT_VtolPathFollowerSettingsData uavtalk_VtolPathFollowerSettingsData;


/*************************************************************************************************
    Filename: vtolpathfollowerstatus.xml
    Object: VtolPathFollowerStatus
    Comment: Monitoring of the VTOL path follower
*************************************************************************************************/

#define VTOLPATHFOLLOWERSTATUS_OBJID 0x3238594c

typedef struct {
	uint8_t FSM_State;
} UAVT_VtolPathFollowerStatusData;

extern UAVT_VtolPathFollowerStatusData uavtalk_VtolPathFollowerStatusData;


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

#define WAYPOINTACTIVE_OBJID 0x1ea5b19c

typedef struct {
	int16_t Index;
} UAVT_WaypointActiveData;

extern UAVT_WaypointActiveData uavtalk_WaypointActiveData;


/*************************************************************************************************
    Filename: waypoint.xml
    Object: Waypoint
    Comment: A waypoint the aircraft can try and hit.  Used by the @ref PathPlanner module
*************************************************************************************************/

#define WAYPOINT_OBJID 0xa6c50a74

enum {
	WAYPOINT_MODE_FLYENDPOINT = 0,
	WAYPOINT_MODE_FLYVECTOR = 1,
	WAYPOINT_MODE_FLYCIRCLERIGHT = 2,
	WAYPOINT_MODE_FLYCIRCLELEFT = 3,
	WAYPOINT_MODE_DRIVEENDPOINT = 4,
	WAYPOINT_MODE_DRIVEVECTOR = 5,
	WAYPOINT_MODE_DRIVECIRCLELEFT = 6,
	WAYPOINT_MODE_DRIVECIRCLERIGHT = 7,
	WAYPOINT_MODE_HOLDPOSITION = 8,
	WAYPOINT_MODE_CIRCLEPOSITIONLEFT = 9,
	WAYPOINT_MODE_CIRCLEPOSITIONRIGHT = 10,
	WAYPOINT_MODE_LAND = 11,
	WAYPOINT_MODE_STOP = 12,
	WAYPOINT_MODE_INVALID = 13,
	WAYPOINT_MODE_LASTITEM = 14
};

extern char UAVT_WaypointModeOption[][42];
typedef struct {
	float North;
	float East;
	float Down;
} UAVT_WaypointPositionType;

typedef struct {
	UAVT_WaypointPositionType Position;	// float[3]
	float Velocity;
	float ModeParameters;
	uint8_t Mode;	// enum
} UAVT_WaypointData;

extern UAVT_WaypointData uavtalk_WaypointData;


/*************************************************************************************************
    Filename: windvelocityactual.xml
    Object: WindVelocityActual
    Comment: Stores 3D wind speed estimation.
*************************************************************************************************/

#define WINDVELOCITYACTUAL_OBJID 0x6d31d2f8

typedef struct {
	float North;
	float East;
	float Down;
} UAVT_WindVelocityActualData;

extern UAVT_WindVelocityActualData uavtalk_WindVelocityActualData;

