
#include <all.h>

UAVT_AccelDesiredData uavtalk_AccelDesiredData;
UAVT_AccelsData uavtalk_AccelsData;
UAVT_AccessoryDesiredData uavtalk_AccessoryDesiredData;
UAVT_ActuatorCommandData uavtalk_ActuatorCommandData;
UAVT_ActuatorDesiredData uavtalk_ActuatorDesiredData;
char UAVT_ActuatorSettingsChannelTypeOption[][42] = {
	"PWM",
	"MK",
	"ASTEC4",
	"PWM Alarm Buzzer",
	"Arming led",
	"Info led",
};

char UAVT_ActuatorSettingsMotorsSpinWhileArmedOption[][42] = {
	"FALSE",
	"TRUE",
};

UAVT_ActuatorSettingsData uavtalk_ActuatorSettingsData;
UAVT_AirspeedActualData uavtalk_AirspeedActualData;
char UAVT_AirspeedSettingsAirspeedSensorTypeOption[][42] = {
	"EagleTreeAirspeedV3",
	"DIYDronesMPXV5004",
	"DIYDronesMPXV7002",
	"GPSOnly",
};

char UAVT_AirspeedSettingsAnalogPinOption[][42] = {
	"ADC0",
	"ADC1",
	"ADC2",
	"ADC3",
	"ADC4",
	"ADC5",
	"ADC6",
	"ADC7",
	"ADC8",
	"NONE",
};

UAVT_AirspeedSettingsData uavtalk_AirspeedSettingsData;
char UAVT_AltitudeHoldDesiredLandOption[][42] = {
	"FALSE",
	"TRUE",
};

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

char UAVT_AttitudeSettingsFilterChoiceOption[][42] = {
	"CCC",
	"PREMERLANI",
	"PREMERLANI_GPS",
};

char UAVT_AttitudeSettingsTrimFlightOption[][42] = {
	"NORMAL",
	"START",
	"LOAD",
};

UAVT_AttitudeSettingsData uavtalk_AttitudeSettingsData;
UAVT_AttitudeSimulatedData uavtalk_AttitudeSimulatedData;
char UAVT_BaroAirspeedBaroConnectedOption[][42] = {
	"False",
	"True",
};

UAVT_BaroAirspeedData uavtalk_BaroAirspeedData;
UAVT_BaroAltitudeData uavtalk_BaroAltitudeData;
char UAVT_BrushlessGimbalSettingsPowerupSequenceOption[][42] = {
	"FALSE",
	"TRUE",
};

UAVT_BrushlessGimbalSettingsData uavtalk_BrushlessGimbalSettingsData;
UAVT_CameraDesiredData uavtalk_CameraDesiredData;
char UAVT_CameraStabSettingsInputOption[][42] = {
	"Accessory0",
	"Accessory1",
	"Accessory2",
	"Accessory3",
	"Accessory4",
	"Accessory5",
	"POI",
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
UAVT_FixedWingAirspeedsData uavtalk_FixedWingAirspeedsData;
UAVT_FixedWingPathFollowerSettingsCCData uavtalk_FixedWingPathFollowerSettingsCCData;
UAVT_FixedWingPathFollowerSettingsData uavtalk_FixedWingPathFollowerSettingsData;
UAVT_FixedWingPathFollowerStatusData uavtalk_FixedWingPathFollowerStatusData;
char UAVT_FlightBatterySettingsCurrentPinOption[][42] = {
	"ADC0",
	"ADC1",
	"ADC2",
	"ADC3",
	"ADC4",
	"ADC5",
	"ADC6",
	"ADC7",
	"ADC8",
	"NONE",
};

char UAVT_FlightBatterySettingsVoltagePinOption[][42] = {
	"ADC0",
	"ADC1",
	"ADC2",
	"ADC3",
	"ADC4",
	"ADC5",
	"ADC6",
	"ADC7",
	"ADC8",
	"NONE",
};

char UAVT_FlightBatterySettingsTypeOption[][42] = {
	"LiPo",
	"A123",
	"LiCo",
	"LiFeSO4",
	"None",
};

char UAVT_FlightBatterySettingsSensorTypeOption[][42] = {
	"Disabled",
	"Enabled",
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
	"Acro",
	"Leveling",
	"VirtualBar",
	"Stabilized1",
	"Stabilized2",
	"Stabilized3",
	"Autotune",
	"AltitudeHold",
	"VelocityControl",
	"PositionHold",
	"ReturnToHome",
	"PathPlanner",
	"TabletControl",
};

char UAVT_FlightStatusControlSourceOption[][42] = {
	"Geofence",
	"Failsafe",
	"Transmitter",
	"Tablet",
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
UAVT_GeoFenceSettingsData uavtalk_GeoFenceSettingsData;
char UAVT_GPSPositionStatusOption[][42] = {
	"NoGPS",
	"NoFix",
	"Fix2D",
	"Fix3D",
	"Diff3D",
};

UAVT_GPSPositionData uavtalk_GPSPositionData;
UAVT_GPSSatellitesData uavtalk_GPSSatellitesData;
UAVT_GPSTimeData uavtalk_GPSTimeData;
UAVT_GPSVelocityData uavtalk_GPSVelocityData;
char UAVT_GroundPathFollowerSettingsManualOverrideOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_GroundPathFollowerSettingsThrottleControlOption[][42] = {
	"MANUAL",
	"PROPORTIONAL",
	"AUTO",
};

char UAVT_GroundPathFollowerSettingsVelocitySourceOption[][42] = {
	"EKF",
	"NEDVEL",
	"GPSPOS",
};

char UAVT_GroundPathFollowerSettingsPositionSourceOption[][42] = {
	"EKF",
	"GPSPOS",
};

UAVT_GroundPathFollowerSettingsData uavtalk_GroundPathFollowerSettingsData;
UAVT_GroundTruthData uavtalk_GroundTruthData;
UAVT_GyrosBiasData uavtalk_GyrosBiasData;
UAVT_GyrosData uavtalk_GyrosData;
char UAVT_HomeLocationSetOption[][42] = {
	"FALSE",
	"TRUE",
};

UAVT_HomeLocationData uavtalk_HomeLocationData;
char UAVT_HoTTSettingsSensorOption[][42] = {
	"Disabled",
	"Enabled",
};

char UAVT_HoTTSettingsWarningOption[][42] = {
	"Disabled",
	"Enabled",
};

UAVT_HoTTSettingsData uavtalk_HoTTSettingsData;
char UAVT_HwColibriFrameOption[][42] = {
	"Gemini",
};

char UAVT_HwColibriRcvrPortOption[][42] = {
	"Disabled",
	"PWM",
	"PWM+ADC",
	"PPM",
	"PPM+ADC",
	"PPM+PWM",
	"PPM+PWM+ADC",
	"PPM+Outputs",
	"PPM+Outputs+ADC",
	"Outputs",
	"Outputs+ADC",
};

char UAVT_HwColibriUart1Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"I2C",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
};

char UAVT_HwColibriUart2Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.BUS",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
};

char UAVT_HwColibriUart3Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"I2C",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
};

char UAVT_HwColibriUart4Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"LighttelemetryTx",
	"FrSKY Sensor Hub",
	"PicoC",
};

char UAVT_HwColibriUSB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwColibriUSB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"PicoC",
	"Disabled",
};

char UAVT_HwColibriGyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwColibriAccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwColibriMPU6000RateOption[][42] = {
	"200",
	"333",
	"500",
	"666",
	"1000",
	"2000",
	"4000",
	"8000",
};

char UAVT_HwColibriMPU6000DLPFOption[][42] = {
	"256",
	"188",
	"98",
	"42",
	"20",
	"10",
	"5",
};

char UAVT_HwColibriMagnetometerOption[][42] = {
	"Disabled",
	"Internal",
	"ExternalI2CUart1",
	"ExternalI2CUart3",
};

char UAVT_HwColibriExtMagOrientationOption[][42] = {
	"Top0degCW",
	"Top90degCW",
	"Top180degCW",
	"Top270degCW",
	"Bottom0degCW",
	"Bottom90degCW",
	"Bottom180degCW",
	"Bottom270degCW",
};

UAVT_HwColibriData uavtalk_HwColibriData;
char UAVT_HwCopterControlRcvrPortOption[][42] = {
	"Disabled",
	"PWM",
	"PPM",
	"PPM+PWM",
	"PPM+Outputs",
	"Outputs",
};

char UAVT_HwCopterControlMainPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.Bus",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
};

char UAVT_HwCopterControlFlexiPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"I2C",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
};

char UAVT_HwCopterControlUSB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwCopterControlUSB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"Disabled",
};

char UAVT_HwCopterControlGyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwCopterControlAccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwCopterControlMPU6000RateOption[][42] = {
	"200",
	"333",
	"500",
	"666",
	"1000",
	"2000",
	"4000",
	"8000",
};

char UAVT_HwCopterControlMPU6000DLPFOption[][42] = {
	"256",
	"188",
	"98",
	"42",
	"20",
	"10",
	"5",
};

UAVT_HwCopterControlData uavtalk_HwCopterControlData;
char UAVT_HwDiscoveryF4MainPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"DebugConsole",
};

char UAVT_HwDiscoveryF4USB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwDiscoveryF4USB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"Disabled",
};

UAVT_HwDiscoveryF4Data uavtalk_HwDiscoveryF4Data;
char UAVT_HwFlyingF3RcvrPortOption[][42] = {
	"Disabled",
	"PWM",
	"PPM",
	"PPM+PWM",
	"PPM+Outputs",
	"Outputs",
};

char UAVT_HwFlyingF3Uart1Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.Bus",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"FrSKY SPort Telemetry",
};

char UAVT_HwFlyingF3Uart2Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.Bus",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"FrSKY SPort Telemetry",
};

char UAVT_HwFlyingF3Uart3Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.Bus",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"FrSKY SPort Telemetry",
};

char UAVT_HwFlyingF3Uart4Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.Bus",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"FrSKY SPort Telemetry",
};

char UAVT_HwFlyingF3Uart5Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.Bus",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"FrSKY SPort Telemetry",
};

char UAVT_HwFlyingF3USB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwFlyingF3USB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"Disabled",
};

char UAVT_HwFlyingF3GyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwFlyingF3L3GD20RateOption[][42] = {
	"380",
	"760",
};

char UAVT_HwFlyingF3AccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwFlyingF3ShieldOption[][42] = {
	"None",
	"RCFlyer",
	"CheBuzz",
	"BMP085",
};

UAVT_HwFlyingF3Data uavtalk_HwFlyingF3Data;
char UAVT_HwFlyingF4RcvrPortOption[][42] = {
	"Disabled",
	"PWM",
	"PPM",
	"PPM+PWM",
	"PPM+Outputs",
	"Outputs",
};

char UAVT_HwFlyingF4Uart1Option[][42] = {
	"Disabled",
	"GPS",
	"S.Bus",
	"DSM",
	"HoTT SUMD",
	"HoTT SUMH",
	"PicoC",
};

char UAVT_HwFlyingF4Uart2Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"FrSKY Sensor Hub",
	"HoTT SUMD",
	"HoTT SUMH",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwFlyingF4Uart3Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"FrSKY Sensor Hub",
	"HoTT SUMD",
	"HoTT SUMH",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwFlyingF4USB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwFlyingF4USB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"PicoC",
	"Disabled",
};

char UAVT_HwFlyingF4GyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwFlyingF4AccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwFlyingF4MPU6050RateOption[][42] = {
	"200",
	"333",
	"500",
	"666",
	"1000",
	"2000",
	"4000",
	"8000",
};

char UAVT_HwFlyingF4MPU6050DLPFOption[][42] = {
	"256",
	"188",
	"98",
	"42",
	"20",
	"10",
	"5",
};

char UAVT_HwFlyingF4MagnetometerOption[][42] = {
	"Disabled",
	"ExternalI2C",
};

char UAVT_HwFlyingF4ExtMagOrientationOption[][42] = {
	"Top0degCW",
	"Top90degCW",
	"Top180degCW",
	"Top270degCW",
	"Bottom0degCW",
	"Bottom90degCW",
	"Bottom180degCW",
	"Bottom270degCW",
};

UAVT_HwFlyingF4Data uavtalk_HwFlyingF4Data;
char UAVT_HwFreedomOutputOption[][42] = {
	"Disabled",
	"PWM",
};

char UAVT_HwFreedomMainPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwFreedomFlexiPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"I2C",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwFreedomRcvrPortOption[][42] = {
	"Disabled",
	"PPM",
	"DSM",
	"S.Bus",
	"HoTT SUMD",
	"HoTT SUMH",
};

char UAVT_HwFreedomRadioPortOption[][42] = {
	"Disabled",
	"Telemetry",
};

char UAVT_HwFreedomUSB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwFreedomUSB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"PicoC",
	"Disabled",
};

char UAVT_HwFreedomGyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwFreedomAccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwFreedomMPU6000RateOption[][42] = {
	"200",
	"333",
	"500",
	"666",
	"1000",
	"2000",
	"4000",
	"8000",
};

char UAVT_HwFreedomMPU6000DLPFOption[][42] = {
	"256",
	"188",
	"98",
	"42",
	"20",
	"10",
	"5",
};

UAVT_HwFreedomData uavtalk_HwFreedomData;
char UAVT_HwQuantonRcvrPortOption[][42] = {
	"Disabled",
	"PWM",
	"PWM+ADC",
	"PPM",
	"PPM+ADC",
	"PPM+PWM",
	"PPM+PWM+ADC",
	"PPM+Outputs",
	"PPM+Outputs+ADC",
	"Outputs",
	"Outputs+ADC",
};

char UAVT_HwQuantonUart1Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"I2C",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwQuantonUart2Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.BUS",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwQuantonUart3Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"I2C",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwQuantonUart4Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"LighttelemetryTx",
	"FrSKY Sensor Hub",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwQuantonUart5Option[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwQuantonUSB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwQuantonUSB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"PicoC",
	"Disabled",
};

char UAVT_HwQuantonGyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwQuantonAccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwQuantonMPU6000RateOption[][42] = {
	"200",
	"333",
	"500",
	"666",
	"1000",
	"2000",
	"4000",
	"8000",
};

char UAVT_HwQuantonMPU6000DLPFOption[][42] = {
	"256",
	"188",
	"98",
	"42",
	"20",
	"10",
	"5",
};

char UAVT_HwQuantonMagnetometerOption[][42] = {
	"Disabled",
	"Internal",
	"ExternalI2CUart1",
	"ExternalI2CUart3",
};

char UAVT_HwQuantonExtMagOrientationOption[][42] = {
	"Top0degCW",
	"Top90degCW",
	"Top180degCW",
	"Top270degCW",
	"Bottom0degCW",
	"Bottom90degCW",
	"Bottom180degCW",
	"Bottom270degCW",
};

UAVT_HwQuantonData uavtalk_HwQuantonData;
char UAVT_HwRevolutionRcvrPortOption[][42] = {
	"Disabled",
	"PWM",
	"PPM",
	"PPM+Outputs",
	"Outputs",
};

char UAVT_HwRevolutionAuxPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwRevolutionAuxSBusPortOption[][42] = {
	"Disabled",
	"S.Bus",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwRevolutionFlexiPortOption[][42] = {
	"Disabled",
	"I2C",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwRevolutionTelemetryPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"DebugConsole",
	"ComBridge",
};

char UAVT_HwRevolutionGPSPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"DebugConsole",
	"ComBridge",
};

char UAVT_HwRevolutionUSB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwRevolutionUSB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"PicoC",
	"Disabled",
};

char UAVT_HwRevolutionGyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwRevolutionAccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwRevolutionMPU6000RateOption[][42] = {
	"200",
	"333",
	"500",
	"666",
	"1000",
	"2000",
	"4000",
	"8000",
};

char UAVT_HwRevolutionMPU6000DLPFOption[][42] = {
	"256",
	"188",
	"98",
	"42",
	"20",
	"10",
	"5",
};

UAVT_HwRevolutionData uavtalk_HwRevolutionData;
char UAVT_HwRevoMiniRcvrPortOption[][42] = {
	"Disabled",
	"PWM",
	"PPM",
	"PPM+PWM",
	"PPM+Outputs",
	"Outputs",
};

char UAVT_HwRevoMiniMainPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"S.Bus",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwRevoMiniFlexiPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"GPS",
	"I2C",
	"DSM",
	"DebugConsole",
	"ComBridge",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT SUMD",
	"HoTT SUMH",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"PicoC",
	"FrSKY SPort Telemetry",
};

char UAVT_HwRevoMiniRadioPortOption[][42] = {
	"Disabled",
	"Telemetry",
};

char UAVT_HwRevoMiniUSB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwRevoMiniUSB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"PicoC",
	"Disabled",
};

char UAVT_HwRevoMiniGyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwRevoMiniAccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwRevoMiniMPU6000RateOption[][42] = {
	"200",
	"333",
	"500",
	"666",
	"1000",
	"2000",
	"4000",
	"8000",
};

char UAVT_HwRevoMiniMPU6000DLPFOption[][42] = {
	"256",
	"188",
	"98",
	"42",
	"20",
	"10",
	"5",
};

UAVT_HwRevoMiniData uavtalk_HwRevoMiniData;
char UAVT_HwSparkyBGCRcvrPortOption[][42] = {
	"Disabled",
	"PPM",
	"S.Bus",
	"DSM",
	"HoTT SUMD",
	"HoTT SUMH",
};

char UAVT_HwSparkyBGCFlexiPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"DebugConsole",
	"ComBridge",
	"GPS",
	"S.Bus",
	"DSM",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"FrSKY SPort Telemetry",
};

char UAVT_HwSparkyBGCUSB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwSparkyBGCUSB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"Disabled",
};

char UAVT_HwSparkyBGCGyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwSparkyBGCAccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwSparkyBGCMPU9150DLPFOption[][42] = {
	"256",
	"188",
	"98",
	"42",
	"20",
	"10",
	"5",
};

char UAVT_HwSparkyBGCMPU9150RateOption[][42] = {
	"200",
	"333",
	"444",
	"500",
	"666",
	"1000",
	"2000",
	"4000",
	"8000",
};

UAVT_HwSparkyBGCData uavtalk_HwSparkyBGCData;
char UAVT_HwSparkyRcvrPortOption[][42] = {
	"Disabled",
	"PPM",
	"S.Bus",
	"DSM",
	"HoTT SUMD",
	"HoTT SUMH",
};

char UAVT_HwSparkyFlexiPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"DebugConsole",
	"ComBridge",
	"GPS",
	"S.Bus",
	"DSM",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"FrSKY SPort Telemetry",
};

char UAVT_HwSparkyMainPortOption[][42] = {
	"Disabled",
	"Telemetry",
	"DebugConsole",
	"ComBridge",
	"GPS",
	"S.Bus",
	"DSM",
	"MavLinkTX",
	"MavLinkTX_GPS_RX",
	"HoTT Telemetry",
	"FrSKY Sensor Hub",
	"LighttelemetryTx",
	"FrSKY SPort Telemetry",
};

char UAVT_HwSparkyOutPortOption[][42] = {
	"PWM10",
	"PWM7+3ADC",
	"PWM8+2ADC",
	"PWM9+PWM_IN",
	"PWM7+PWM_IN+2ADC",
};

char UAVT_HwSparkyUSB_HIDPortOption[][42] = {
	"USBTelemetry",
	"RCTransmitter",
	"Disabled",
};

char UAVT_HwSparkyUSB_VCPPortOption[][42] = {
	"USBTelemetry",
	"ComBridge",
	"DebugConsole",
	"Disabled",
};

char UAVT_HwSparkyGyroRangeOption[][42] = {
	"250",
	"500",
	"1000",
	"2000",
};

char UAVT_HwSparkyAccelRangeOption[][42] = {
	"2G",
	"4G",
	"8G",
	"16G",
};

char UAVT_HwSparkyMPU9150DLPFOption[][42] = {
	"256",
	"188",
	"98",
	"42",
	"20",
	"10",
	"5",
};

char UAVT_HwSparkyMPU9150RateOption[][42] = {
	"200",
	"333",
	"444",
	"500",
	"666",
	"1000",
	"2000",
	"4000",
	"8000",
};

UAVT_HwSparkyData uavtalk_HwSparkyData;
UAVT_I2CVMUserProgramData uavtalk_I2CVMUserProgramData;
UAVT_I2CVMData uavtalk_I2CVMData;
char UAVT_INSSettingsComputeGyroBiasOption[][42] = {
	"FALSE",
	"TRUE",
};

UAVT_INSSettingsData uavtalk_INSSettingsData;
UAVT_INSStateData uavtalk_INSStateData;
char UAVT_LoggingSettingsLogBehaviorOption[][42] = {
	"LogOnStart",
	"LogOnArm",
	"LogOff",
};

UAVT_LoggingSettingsData uavtalk_LoggingSettingsData;
char UAVT_LoggingStatsOperationOption[][42] = {
	"LOGGING",
	"IDLE",
	"DOWNLOAD",
	"COMPLETE",
	"ERROR",
};

UAVT_LoggingStatsData uavtalk_LoggingStatsData;
char UAVT_LoiterCommandFrameOption[][42] = {
	"Body",
	"Earth",
};

UAVT_LoiterCommandData uavtalk_LoiterCommandData;
UAVT_MagBiasData uavtalk_MagBiasData;
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
	"HoTT SUM",
	"None",
};

char UAVT_ManualControlSettingsRssiTypeOption[][42] = {
	"None",
	"PWM",
	"PPM",
	"ADC",
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
	"Switch",
};

char UAVT_ManualControlSettingsStabilization1SettingsOption[][42] = {
	"None",
	"Rate",
	"Attitude",
	"AxisLock",
	"WeakLeveling",
	"VirtualBar",
	"Horizon",
	"RateMW",
	"SystemIdent",
	"POI",
	"CoordinatedFlight",
};

char UAVT_ManualControlSettingsStabilization2SettingsOption[][42] = {
	"None",
	"Rate",
	"Attitude",
	"AxisLock",
	"WeakLeveling",
	"VirtualBar",
	"Horizon",
	"RateMW",
	"SystemIdent",
	"POI",
	"CoordinatedFlight",
};

char UAVT_ManualControlSettingsStabilization3SettingsOption[][42] = {
	"None",
	"Rate",
	"Attitude",
	"AxisLock",
	"WeakLeveling",
	"VirtualBar",
	"Horizon",
	"RateMW",
	"SystemIdent",
	"POI",
	"CoordinatedFlight",
};

char UAVT_ManualControlSettingsFlightModePositionOption[][42] = {
	"Manual",
	"Acro",
	"Leveling",
	"VirtualBar",
	"Stabilized1",
	"Stabilized2",
	"Stabilized3",
	"Autotune",
	"AltitudeHold",
	"VelocityControl",
	"PositionHold",
	"ReturnToHome",
	"PathPlanner",
	"TabletControl",
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
char UAVT_ModuleSettingsAdminStateOption[][42] = {
	"Disabled",
	"Enabled",
};

char UAVT_ModuleSettingsTelemetrySpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_ModuleSettingsGPSSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
	"230400",
};

char UAVT_ModuleSettingsGPSDataProtocolOption[][42] = {
	"NMEA",
	"UBX",
};

char UAVT_ModuleSettingsGPSAutoConfigureOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_ModuleSettingsComUsbBridgeSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_ModuleSettingsI2CVMProgramSelectOption[][42] = {
	"EndianTest",
	"MathTest",
	"None",
	"OPBaroAltimeter",
	"User",
};

char UAVT_ModuleSettingsMavlinkSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_ModuleSettingsLightTelemetrySpeedOption[][42] = {
	"1200",
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

UAVT_ModuleSettingsData uavtalk_ModuleSettingsData;
UAVT_MWRateSettingsData uavtalk_MWRateSettingsData;
UAVT_NedAccelData uavtalk_NedAccelData;
UAVT_NEDPositionData uavtalk_NEDPositionData;
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
char UAVT_OPLinkSettingsCoordinatorOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_OPLinkSettingsPPMOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_OPLinkSettingsUAVTalkOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_OPLinkSettingsInputConnectionOption[][42] = {
	"HID",
	"VCP",
	"Telemetry",
	"Flexi",
};

char UAVT_OPLinkSettingsOutputConnectionOption[][42] = {
	"RemoteHID",
	"RemoteVCP",
	"RemoteTelemetry",
	"RemoteFlexi",
	"Telemetry",
	"Flexi",
};

char UAVT_OPLinkSettingsComSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

char UAVT_OPLinkSettingsMaxRFPowerOption[][42] = {
	"1.25",
	"1.6",
	"3.16",
	"6.3",
	"12.6",
	"25",
	"50",
	"100",
};

UAVT_OPLinkSettingsData uavtalk_OPLinkSettingsData;
char UAVT_OPLinkStatusLinkStateOption[][42] = {
	"Disconnected",
	"Connecting",
	"Connected",
};

UAVT_OPLinkStatusData uavtalk_OPLinkStatusData;
char UAVT_OveroSyncSettingsLogOnOption[][42] = {
	"Never",
	"Always",
	"Armed",
};

UAVT_OveroSyncSettingsData uavtalk_OveroSyncSettingsData;
char UAVT_OveroSyncStatsConnectedOption[][42] = {
	"False",
	"True",
};

UAVT_OveroSyncStatsData uavtalk_OveroSyncStatsData;
char UAVT_PathDesiredModeOption[][42] = {
	"FlyEndpoint",
	"FlyVector",
	"FlyCircleRight",
	"FlyCircleLeft",
	"DriveEndpoint",
	"DriveVector",
	"DriveCircleLeft",
	"DriveCircleRight",
	"HoldPosition",
	"CirclePositionLeft",
	"CirclePositionRight",
	"Land",
};

UAVT_PathDesiredData uavtalk_PathDesiredData;
char UAVT_PathPlannerSettingsPreprogrammedPathOption[][42] = {
	"NONE",
	"10M_BOX",
	"LOGO",
};

char UAVT_PathPlannerSettingsFlashOperationOption[][42] = {
	"NONE",
	"FAILED",
	"COMPLETED",
	"SAVE1",
	"SAVE2",
	"SAVE3",
	"SAVE4",
	"SAVE5",
	"LOAD1",
	"LOAD2",
	"LOAD3",
	"LOAD4",
	"LOAD5",
};

UAVT_PathPlannerSettingsData uavtalk_PathPlannerSettingsData;
char UAVT_PathStatusStatusOption[][42] = {
	"InProgress",
	"Completed",
	"Warning",
	"Critical",
};

UAVT_PathStatusData uavtalk_PathStatusData;
char UAVT_PicoCSettingsStartupOption[][42] = {
	"Disabled",
	"OnBoot",
	"WhenArmed",
};

char UAVT_PicoCSettingsSourceOption[][42] = {
	"Disabled",
	"Demo",
	"Interactive",
	"File",
};

char UAVT_PicoCSettingsComSpeedOption[][42] = {
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
};

UAVT_PicoCSettingsData uavtalk_PicoCSettingsData;
char UAVT_PicoCStatusCommandOption[][42] = {
	"Idle",
	"StartScript",
	"USARTmode",
	"GetSector",
	"SetSector",
	"LoadFile",
	"SaveFile",
	"DeleteFile",
	"FormatPartition",
};

UAVT_PicoCStatusData uavtalk_PicoCStatusData;
UAVT_PoiLocationData uavtalk_PoiLocationData;
UAVT_PositionActualData uavtalk_PositionActualData;
UAVT_RateDesiredData uavtalk_RateDesiredData;
char UAVT_ReceiverActivityActiveGroupOption[][42] = {
	"PWM",
	"PPM",
	"DSM (MainPort)",
	"DSM (FlexiPort)",
	"S.Bus",
	"GCS",
	"HoTT SUM",
	"None",
};

UAVT_ReceiverActivityData uavtalk_ReceiverActivityData;
UAVT_SensorSettingsData uavtalk_SensorSettingsData;
UAVT_SessionManagingData uavtalk_SessionManagingData;
UAVT_SonarAltitudeData uavtalk_SonarAltitudeData;
char UAVT_StabilizationDesiredStabilizationModeOption[][42] = {
	"None",
	"Rate",
	"Attitude",
	"AxisLock",
	"WeakLeveling",
	"VirtualBar",
	"Horizon",
	"RateMW",
	"SystemIdent",
	"POI",
	"CoordinatedFlight",
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

UAVT_StabilizationSettingsData uavtalk_StabilizationSettingsData;
char UAVT_StateEstimationAttitudeFilterOption[][42] = {
	"Complementary",
	"INSIndoor",
	"INSOutdoor",
};

char UAVT_StateEstimationNavigationFilterOption[][42] = {
	"None",
	"Raw",
	"INS",
};

UAVT_StateEstimationData uavtalk_StateEstimationData;
char UAVT_SystemAlarmsAlarmOption[][42] = {
	"Uninitialised",
	"OK",
	"Warning",
	"Error",
	"Critical",
};

char UAVT_SystemAlarmsConfigErrorOption[][42] = {
	"Stabilization",
	"Multirotor",
	"AutoTune",
	"AltitudeHold",
	"VelocityControl",
	"PositionHold",
	"PathPlanner",
	"NavFilter",
	"UnsafeToArm",
	"Undefined",
	"None",
};

char UAVT_SystemAlarmsManualControlOption[][42] = {
	"Settings",
	"NoRx",
	"Accessory",
	"AltitudeHold",
	"PathFollower",
	"Undefined",
	"None",
};

char UAVT_SystemAlarmsStateEstimationOption[][42] = {
	"Gyro queue not updating",
	"Accelerometer queue not updating",
	"No GPS",
	"No magnetometer",
	"No barometer",
	"No home",
	"Too few satellites",
	"PDOP too high",
	"Undefined",
	"None",
};

UAVT_SystemAlarmsData uavtalk_SystemAlarmsData;
UAVT_SystemIdentData uavtalk_SystemIdentData;
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
char UAVT_TabletInfoConnectedOption[][42] = {
	"False",
	"True",
};

char UAVT_TabletInfoTabletModeDesiredOption[][42] = {
	"PositionHold",
	"ReturnToHome",
	"ReturnToTablet",
	"PathPlanner",
	"FollowMe",
	"Land",
	"CameraPOI",
};

char UAVT_TabletInfoPOIOption[][42] = {
	"False",
	"True",
};

UAVT_TabletInfoData uavtalk_TabletInfoData;
char UAVT_TaskInfoRunningOption[][42] = {
	"False",
	"True",
};

UAVT_TaskInfoData uavtalk_TaskInfoData;
UAVT_TrimAnglesSettingsData uavtalk_TrimAnglesSettingsData;
UAVT_TrimAnglesData uavtalk_TrimAnglesData;
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
	"Roll VbarSensitivity",
	"Pitch VbarSensitivity",
	"Roll+Pitch VbarSensitivity",
	"Yaw VbarSensitivity",
	"Roll Vbar.Kp",
	"Pitch Vbar.Kp",
	"Roll+Pitch Vbar.Kp",
	"Yaw Vbar.Kp",
	"Roll Vbar.Ki",
	"Pitch Vbar.Ki",
	"Roll+Pitch Vbar.Ki",
	"Yaw Vbar.Ki",
	"Roll Vbar.Kd",
	"Pitch Vbar.Kd",
	"Roll+Pitch Vbar.Kd",
	"Yaw Vbar.Kd",
};

UAVT_TxPIDSettingsData uavtalk_TxPIDSettingsData;
UAVT_UBloxInfoData uavtalk_UBloxInfoData;
UAVT_VelocityActualData uavtalk_VelocityActualData;
UAVT_VelocityDesiredData uavtalk_VelocityDesiredData;
UAVT_VibrationAnalysisOutputData uavtalk_VibrationAnalysisOutputData;
char UAVT_VibrationAnalysisSettingsFFTWindowSizeOption[][42] = {
	"16",
	"64",
	"256",
	"1024",
};

char UAVT_VibrationAnalysisSettingsTestingStatusOption[][42] = {
	"Off",
	"On",
};

UAVT_VibrationAnalysisSettingsData uavtalk_VibrationAnalysisSettingsData;
char UAVT_VtolPathFollowerSettingsThrottleControlOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_VtolPathFollowerSettingsVelocityChangePredictionOption[][42] = {
	"FALSE",
	"TRUE",
};

char UAVT_VtolPathFollowerSettingsYawModeOption[][42] = {
	"Rate",
	"AxisLock",
	"Attitude",
	"Path",
	"POI",
};

UAVT_VtolPathFollowerSettingsData uavtalk_VtolPathFollowerSettingsData;
UAVT_VtolPathFollowerStatusData uavtalk_VtolPathFollowerStatusData;
UAVT_WatchdogStatusData uavtalk_WatchdogStatusData;
UAVT_WaypointActiveData uavtalk_WaypointActiveData;
char UAVT_WaypointModeOption[][42] = {
	"FlyEndpoint",
	"FlyVector",
	"FlyCircleRight",
	"FlyCircleLeft",
	"DriveEndpoint",
	"DriveVector",
	"DriveCircleLeft",
	"DriveCircleRight",
	"HoldPosition",
	"CirclePositionLeft",
	"CirclePositionRight",
	"Land",
	"Stop",
	"Invalid",
};

UAVT_WaypointData uavtalk_WaypointData;
UAVT_WindVelocityActualData uavtalk_WindVelocityActualData;

