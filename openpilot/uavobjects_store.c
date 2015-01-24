
#include <all.h>

UAVT_AccelsData uavtalk_AccelsData;
UAVT_AccessoryDesiredData uavtalk_AccessoryDesiredData;
UAVT_ActuatorCommandData uavtalk_ActuatorCommandData;
UAVT_ActuatorDesiredData uavtalk_ActuatorDesiredData;
char UAVT_ActuatorSettingsChannelTypeOption[][42] = {
	"PWM",
	"MK",
	"ASTEC4",
	"PWM Alarm Buzzer",
};

char UAVT_ActuatorSettingsMotorsSpinWhileArmedOption[][42] = {
	"FALSE",
	"TRUE",
};

UAVT_ActuatorSettingsData uavtalk_ActuatorSettingsData;
UAVT_AltHoldSmoothedData uavtalk_AltHoldSmoothedData;
UAVT_AltitudeHoldDesiredData uavtalk_AltitudeHoldDesiredData;
UAVT_AltitudeHoldSettingsData uavtalk_AltitudeHoldSettingsData;
UAVT_AttitudeActualData uavtalk_AttitudeActualData;
char UAVT_AttitudeSettingsZeroDuringArmingOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_AttitudeSettingsBiasCorrectGyroOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_AttitudeSettingsTrimFlightOption[][42] = {
	"NORMAL",
	"START",
	"LOAD",
};

UAVT_AttitudeSettingsData uavtalk_AttitudeSettingsData;
UAVT_BaroAltitudeData uavtalk_BaroAltitudeData;
UAVT_CameraDesiredData uavtalk_CameraDesiredData;
char UAVT_CameraStabSettingsInputOption[][42] = {
	"Accessory0",
	"Accessory1",
	"Accessory2",
	"Accessory3",
	"Accessory4",
	"Accessory5",
	"None",
};

char UAVT_CameraStabSettingsStabilizationModeOption[][42] = {
	"Attitude",
	"AxisLock",
};

UAVT_CameraStabSettingsData uavtalk_CameraStabSettingsData;
char UAVT_FaultSettingsActivateFaultOption[][42] = {
	"NoFault",
	"ModuleInitAssert",
	"InitOutOfMemory",
	"InitBusError",
	"RunawayTask",
	"TaskOutOfMemory",
};

UAVT_FaultSettingsData uavtalk_FaultSettingsData;
UAVT_FirmwareIAPObjData uavtalk_FirmwareIAPObjData;
char UAVT_FlightBatterySettingsTypeOption[][42] = {
	"LiPo",
	"A123",
	"LiCo",
	"LiFeSO4",
	"None",
};

char UAVT_FlightBatterySettingsSensorTypeOption[][42] = {
	"None",
};

UAVT_FlightBatterySettingsData uavtalk_FlightBatterySettingsData;
UAVT_FlightBatteryStateData uavtalk_FlightBatteryStateData;
char UAVT_FlightPlanControlCommandOption[][42] = {
	"Start",
	"Stop",
	"Kill",
};

UAVT_FlightPlanControlData uavtalk_FlightPlanControlData;
UAVT_FlightPlanSettingsData uavtalk_FlightPlanSettingsData;
char UAVT_FlightPlanStatusStatusOption[][42] = {
	"Stopped",
	"Running",
	"Error",
};

char UAVT_FlightPlanStatusErrorTypeOption[][42] = {
	"None",
	"VMInitError",
	"Exception",
	"IOError",
	"DivByZero",
	"AssertError",
	"AttributeError",
	"ImportError",
	"IndexError",
	"KeyError",
	"MemoryError",
	"NameError",
	"SyntaxError",
	"SystemError",
	"TypeError",
	"ValueError",
	"StopIteration",
	"Warning",
	"UnknownError",
};

UAVT_FlightPlanStatusData uavtalk_FlightPlanStatusData;
char UAVT_FlightStatusArmedOption[][42] = {
	"Disarmed",
	"Arming",
	"Armed",
};

char UAVT_FlightStatusFlightModeOption[][42] = {
	"Manual",
	"Stabilized1",
	"Stabilized2",
	"Stabilized3",
	"Autotune",
	"AltitudeHold",
	"VelocityControl",
	"PositionHold",
};

UAVT_FlightStatusData uavtalk_FlightStatusData;
char UAVT_FlightTelemetryStatsStatusOption[][42] = {
	"Disconnected",
	"HandshakeReq",
	"HandshakeAck",
	"Connected",
};

UAVT_FlightTelemetryStatsData uavtalk_FlightTelemetryStatsData;
UAVT_GCSReceiverData uavtalk_GCSReceiverData;
char UAVT_GCSTelemetryStatsStatusOption[][42] = {
	"Disconnected",
	"HandshakeReq",
	"HandshakeAck",
	"Connected",
};

UAVT_GCSTelemetryStatsData uavtalk_GCSTelemetryStatsData;
char UAVT_GPSPositionStatusOption[][42] = {
	"NoGPS",
	"NoFix",
	"Fix2D",
	"Fix3D",
};

UAVT_GPSPositionData uavtalk_GPSPositionData;
UAVT_GPSSatellitesData uavtalk_GPSSatellitesData;
char UAVT_GPSSettingsDataProtocolOption[][42] = {
	"NMEA",
	"UBX",
};

UAVT_GPSSettingsData uavtalk_GPSSettingsData;
UAVT_GPSTimeData uavtalk_GPSTimeData;
UAVT_GPSVelocityData uavtalk_GPSVelocityData;
char UAVT_GuidanceSettingsGuidanceModeOption[][42] = {
	"DUAL_LOOP",
	"VELOCITY_CONTROL",
};

char UAVT_GuidanceSettingsThrottleControlOption[][42] = {
	"FALSE",
	"TRUE",
};

UAVT_GuidanceSettingsData uavtalk_GuidanceSettingsData;
UAVT_GyrosBiasData uavtalk_GyrosBiasData;
UAVT_GyrosData uavtalk_GyrosData;
char UAVT_HomeLocationSetOption[][42] = {
	"FALSE",
	"TRUE",
};

UAVT_HomeLocationData uavtalk_HomeLocationData;
char UAVT_HwSettingsCC_RcvrPortOption[][42] = {
	"Disabled",
	"PWM",
	"PPM",
	"PPM+PWM",
	"PPM+Outputs",
	"Outputs",
};

char UAVT_HwSettingsCC_MainPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.Bus",
	"DSM2",
	"DSMX (10bit)",
	"DSMX (11bit)",
	"ComAux",
	"ComBridge",
};

char UAVT_HwSettingsCC_FlexiPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"I2C",
	"DSM2",
	"DSMX (10bit)",
	"DSMX (11bit)",
	"ComAux",
	"ComBridge",
};

char UAVT_HwSettingsRV_RcvrPortOption[][42] = {
	"Disabled",
	"PWM",
	"PPM",
	"PPM+Outputs",
	"Outputs",
};

char UAVT_HwSettingsRV_AuxPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"DSM2",
	"DSMX (10bit)",
	"DSMX (11bit)",
	"ComAux",
	"ComBridge",
};

char UAVT_HwSettingsRV_AuxSBusPortOption[][42] = {
	"Disabled",
	"S.Bus",
	"DSM2",
	"DSMX (10bit)",
	"DSMX (11bit)",
	"ComAux",
	"ComBridge",
};

char UAVT_HwSettingsRV_FlexiPortOption[][42] = {
	"Disabled",
	"I2C",
	"DSM2",
	"DSMX (10bit)",
	"DSMX (11bit)",
	"ComAux",
	"ComBridge",
};

char UAVT_HwSettingsRV_TelemetryPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"ComAux",
	"ComBridge",
};

char UAVT_HwSettingsRV_GPSPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"ComAux",
	"ComBridge",
};

char UAVT_HwSettingsTelemetrySpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_HwSettingsGPSSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_HwSettingsComUsbBridgeSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_HwSettingsUSB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwSettingsUSB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"Disabled",
};

char UAVT_HwSettingsOptionalModulesOption[][42] = {
	"Disabled",
	"Enabled",
};

UAVT_HwSettingsData uavtalk_HwSettingsData;
char UAVT_I2CStatslast_error_typeOption[][42] = {
	"EVENT",
	"FSM",
	"INTERRUPT",
};

char UAVT_I2CStatsevent_logOption[][42] = {
	"I2C_EVENT_BUS_ERROR",
	"I2C_EVENT_START",
	"I2C_EVENT_STARTED_MORE_TXN_READ",
	"I2C_EVENT_STARTED_MORE_TXN_WRITE",
	"I2C_EVENT_STARTED_LAST_TXN_READ",
	"I2C_EVENT_STARTED_LAST_TXN_WRITE",
	"I2C_EVENT_ADDR_SENT_LEN_EQ_0",
	"I2C_EVENT_ADDR_SENT_LEN_EQ_1",
	"I2C_EVENT_ADDR_SENT_LEN_EQ_2",
	"I2C_EVENT_ADDR_SENT_LEN_GT_2",
	"I2C_EVENT_TRANSFER_DONE_LEN_EQ_0",
	"I2C_EVENT_TRANSFER_DONE_LEN_EQ_1",
	"I2C_EVENT_TRANSFER_DONE_LEN_EQ_2",
	"I2C_EVENT_TRANSFER_DONE_LEN_GT_2",
	"I2C_EVENT_NACK",
	"I2C_EVENT_STOPPED",
	"I2C_EVENT_AUTO",
};

char UAVT_I2CStatsstate_logOption[][42] = {
	"I2C_STATE_FSM_FAULT",
	"I2C_STATE_BUS_ERROR",
	"I2C_STATE_STOPPED",
	"I2C_STATE_STOPPING",
	"I2C_STATE_STARTING",
	"I2C_STATE_R_MORE_TXN_ADDR",
	"I2C_STATE_R_MORE_TXN_PRE_ONE",
	"I2C_STATE_R_MORE_TXN_PRE_FIRST",
	"I2C_STATE_R_MORE_TXN_PRE_MIDDLE",
	"I2C_STATE_R_MORE_TXN_LAST",
	"I2C_STATE_R_MORE_TXN_POST_LAST",
	"R_LAST_TXN_ADDR",
	"I2C_STATE_R_LAST_TXN_PRE_ONE",
	"I2C_STATE_R_LAST_TXN_PRE_FIRST",
	"I2C_STATE_R_LAST_TXN_PRE_MIDDLE",
	"I2C_STATE_R_LAST_TXN_PRE_LAST",
	"I2C_STATE_R_LAST_TXN_POST_LAST",
	"I2C_STATE_W_MORE_TXN_ADDR",
	"I2C_STATE_W_MORE_TXN_MIDDLE",
	"I2C_STATE_W_MORE_TXN_LAST",
	"I2C_STATE_W_LAST_TXN_ADDR",
	"I2C_STATE_W_LAST_TXN_MIDDLE",
	"I2C_STATE_W_LAST_TXN_LAST",
	"I2C_STATE_NACK",
};

UAVT_I2CStatsData uavtalk_I2CStatsData;
UAVT_MagnetometerData uavtalk_MagnetometerData;
char UAVT_ManualControlCommandConnectedOption[][42] = {
	"False",
	"True",
};

UAVT_ManualControlCommandData uavtalk_ManualControlCommandData;
char UAVT_ManualControlSettingsChannelGroupsOption[][42] = {
	"PWM",
	"PPM",
	"DSM (MainPort)",
	"DSM (FlexiPort)",
	"S.Bus",
	"GCS",
	"None",
};

char UAVT_ManualControlSettingsArmingOption[][42] = {
	"Always Disarmed",
	"Always Armed",
	"Roll Left",
	"Roll Right",
	"Pitch Forward",
	"Pitch Aft",
	"Yaw Left",
	"Yaw Right",
};

char UAVT_ManualControlSettingsStabilization1SettingsOption[][42] = {
	"None",
	"Rate",
	"Attitude",
	"AxisLock",
	"WeakLeveling",
	"VirtualBar",
	"RelayRate",
	"RelayAttitude",
};

char UAVT_ManualControlSettingsStabilization2SettingsOption[][42] = {
	"None",
	"Rate",
	"Attitude",
	"AxisLock",
	"WeakLeveling",
	"VirtualBar",
	"RelayRate",
	"RelayAttitude",
};

char UAVT_ManualControlSettingsStabilization3SettingsOption[][42] = {
	"None",
	"Rate",
	"Attitude",
	"AxisLock",
	"WeakLeveling",
	"VirtualBar",
	"RelayRate",
	"RelayAttitude",
};

char UAVT_ManualControlSettingsFlightModePositionOption[][42] = {
	"Manual",
	"Stabilized1",
	"Stabilized2",
	"Stabilized3",
	"Autotune",
	"AltitudeHold",
	"VelocityControl",
	"PositionHold",
};

UAVT_ManualControlSettingsData uavtalk_ManualControlSettingsData;
char UAVT_MixerSettingsCurve2SourceOption[][42] = {
	"Throttle",
	"Roll",
	"Pitch",
	"Yaw",
	"Collective",
	"Accessory0",
	"Accessory1",
	"Accessory2",
	"Accessory3",
	"Accessory4",
	"Accessory5",
};

char UAVT_MixerSettingsMixer1TypeOption[][42] = {
	"Disabled",
	"Motor",
	"Servo",
	"CameraRoll",
	"CameraPitch",
	"CameraYaw",
	"Accessory0",
	"Accessory1",
	"Accessory2",
	"Accessory3",
	"Accessory4",
	"Accessory5",
};

UAVT_MixerSettingsData uavtalk_MixerSettingsData;
UAVT_MixerStatusData uavtalk_MixerStatusData;
UAVT_NedAccelData uavtalk_NedAccelData;
char UAVT_ObjectPersistenceOperationOption[][42] = {
	"NOP",
	"Load",
	"Save",
	"Delete",
	"FullErase",
	"Completed",
	"Error",
};

char UAVT_ObjectPersistenceSelectionOption[][42] = {
	"SingleObject",
	"AllSettings",
	"AllMetaObjects",
	"AllObjects",
};

UAVT_ObjectPersistenceData uavtalk_ObjectPersistenceData;
char UAVT_OveroSyncStatsConnectedOption[][42] = {
	"False",
	"True",
};

UAVT_OveroSyncStatsData uavtalk_OveroSyncStatsData;
char UAVT_PathActionModeOption[][42] = {
	"FlyEndpoint",
	"FlyVector",
	"FlyCircleRight",
	"FlyCircleLeft",
	"DriveEndpoint",
	"DriveVector",
	"DriveCircleLeft",
	"DriveCircleRight",
	"FixedAttitude",
	"SetAccessory",
	"DisarmAlarm",
};

char UAVT_PathActionEndConditionOption[][42] = {
	"None",
	"TimeOut",
	"DistanceToTarget",
	"LegRemaining",
	"AboveAltitude",
	"PointingTowardsNext",
	"PythonScript",
	"Immediate",
};

char UAVT_PathActionCommandOption[][42] = {
	"OnConditionNextWaypoint",
	"OnNotConditionNextWaypoint",
	"OnConditionJumpWaypoint",
	"OnNotConditionJumpWaypoint",
	"IfConditionJumpWaypointElseNextWaypoint",
};

UAVT_PathActionData uavtalk_PathActionData;
char UAVT_PipXSettingsTelemetryConfigOption[][42] = {
	"Disabled",
	"Serial",
	"UAVTalk",
	"GCS",
	"Debug",
};

char UAVT_PipXSettingsTelemetrySpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_PipXSettingsFlexiConfigOption[][42] = {
	"Disabled",
	"Serial",
	"UAVTalk",
	"GCS",
	"PPM_In",
	"PPM_Out",
	"RSSI",
	"Debug",
};

char UAVT_PipXSettingsFlexiSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_PipXSettingsVCPConfigOption[][42] = {
	"Disabled",
	"Serial",
	"Debug",
};

char UAVT_PipXSettingsVCPSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_PipXSettingsRFSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_PipXSettingsMaxRFPowerOption[][42] = {
	"1.25",
	"1.6",
	"3.16",
	"6.3",
	"12.6",
	"25",
	"50",
	"100",
};

UAVT_PipXSettingsData uavtalk_PipXSettingsData;
char UAVT_PipXStatusLinkStateOption[][42] = {
	"Disconnected",
	"Connecting",
	"Connected",
};

UAVT_PipXStatusData uavtalk_PipXStatusData;
UAVT_PositionActualData uavtalk_PositionActualData;
UAVT_PositionDesiredData uavtalk_PositionDesiredData;
UAVT_RateDesiredData uavtalk_RateDesiredData;
char UAVT_ReceiverActivityActiveGroupOption[][42] = {
	"PWM",
	"PPM",
	"DSM (MainPort)",
	"DSM (FlexiPort)",
	"S.Bus",
	"GCS",
	"None",
};

UAVT_ReceiverActivityData uavtalk_ReceiverActivityData;
char UAVT_RelayTuningSettingsModeOption[][42] = {
	"Rate",
	"Attitude",
};

char UAVT_RelayTuningSettingsBehaviorOption[][42] = {
	"Measure",
	"Compute",
	"Save",
};

UAVT_RelayTuningSettingsData uavtalk_RelayTuningSettingsData;
UAVT_RelayTuningData uavtalk_RelayTuningData;
char UAVT_RevoCalibrationBiasCorrectedRawOption[][42] = {
	"TRUE",
	"FALSE",
};

UAVT_RevoCalibrationData uavtalk_RevoCalibrationData;
UAVT_SonarAltitudeData uavtalk_SonarAltitudeData;
char UAVT_StabilizationDesiredStabilizationModeOption[][42] = {
	"None",
	"Rate",
	"Attitude",
	"AxisLock",
	"WeakLeveling",
	"VirtualBar",
	"RelayRate",
	"RelayAttitude",
};

UAVT_StabilizationDesiredData uavtalk_StabilizationDesiredData;
char UAVT_StabilizationSettingsVbarPiroCompOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_StabilizationSettingsLowThrottleZeroIntegralOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_StabilizationSettingsLowThrottleZeroAxisOption[][42] = {
	"FALSE",
	"TRUE",
};

UAVT_StabilizationSettingsData uavtalk_StabilizationSettingsData;
char UAVT_SystemAlarmsAlarmOption[][42] = {
	"Uninitialised",
	"OK",
	"Warning",
	"Error",
	"Critical",
};

UAVT_SystemAlarmsData uavtalk_SystemAlarmsData;
char UAVT_SystemSettingsAirframeTypeOption[][42] = {
	"FixedWing",
	"FixedWingElevon",
	"FixedWingVtail",
	"VTOL",
	"HeliCP",
	"QuadX",
	"QuadP",
	"Hexa",
	"Octo",
	"Custom",
	"HexaX",
	"OctoV",
	"OctoCoaxP",
	"OctoCoaxX",
	"HexaCoax",
	"Tri",
	"GroundVehicleCar",
	"GroundVehicleDifferential",
	"GroundVehicleMotorcycle",
};

UAVT_SystemSettingsData uavtalk_SystemSettingsData;
UAVT_SystemStatsData uavtalk_SystemStatsData;
char UAVT_TaskInfoRunningOption[][42] = {
	"False",
	"True",
};

UAVT_TaskInfoData uavtalk_TaskInfoData;
char UAVT_TxPIDSettingsUpdateModeOption[][42] = {
	"Never",
	"When Armed",
	"Always",
};

char UAVT_TxPIDSettingsInputsOption[][42] = {
	"Throttle",
	"Accessory0",
	"Accessory1",
	"Accessory2",
	"Accessory3",
	"Accessory4",
	"Accessory5",
};

char UAVT_TxPIDSettingsPIDsOption[][42] = {
	"Disabled",
	"Roll Rate.Kp",
	"Pitch Rate.Kp",
	"Roll+Pitch Rate.Kp",
	"Yaw Rate.Kp",
	"Roll Rate.Ki",
	"Pitch Rate.Ki",
	"Roll+Pitch Rate.Ki",
	"Yaw Rate.Ki",
	"Roll Rate.Kd",
	"Pitch Rate.Kd",
	"Roll+Pitch Rate.Kd",
	"Yaw Rate.Kd",
	"Roll Rate.ILimit",
	"Pitch Rate.ILimit",
	"Roll+Pitch Rate.ILimit",
	"Yaw Rate.ILimit",
	"Roll Attitude.Kp",
	"Pitch Attitude.Kp",
	"Roll+Pitch Attitude.Kp",
	"Yaw Attitude.Kp",
	"Roll Attitude.Ki",
	"Pitch Attitude.Ki",
	"Roll+Pitch Attitude.Ki",
	"Yaw Attitude.Ki",
	"Roll Attitude.ILimit",
	"Pitch Attitude.ILimit",
	"Roll+Pitch Attitude.ILimit",
	"Yaw Attitude.ILimit",
	"GyroTau",
};

UAVT_TxPIDSettingsData uavtalk_TxPIDSettingsData;
UAVT_VelocityActualData uavtalk_VelocityActualData;
UAVT_VelocityDesiredData uavtalk_VelocityDesiredData;
UAVT_WatchdogStatusData uavtalk_WatchdogStatusData;
UAVT_WaypointActiveData uavtalk_WaypointActiveData;
UAVT_WaypointData uavtalk_WaypointData;

