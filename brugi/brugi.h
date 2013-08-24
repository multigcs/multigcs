
typedef struct {
	float value;
	float min;
	float max;
	float scale;
	float offset;
	float step;
	uint8_t type;
} BrugiValue;

typedef struct {
	BrugiValue vers;
	BrugiValue gyroPitchKp;
	BrugiValue gyroPitchKi;
	BrugiValue gyroPitchKd;
	BrugiValue gyroRollKp;
	BrugiValue gyroRollKi;
	BrugiValue gyroRollKd;
	BrugiValue accTimeConstant;
	BrugiValue mpuLPF;
	BrugiValue angleOffsetPitch;
	BrugiValue angleOffsetRoll;
	BrugiValue dirMotorPitch;
	BrugiValue dirMotorRoll;
	BrugiValue motorNumberPitch;
	BrugiValue motorNumberRoll;
	BrugiValue maxPWMmotorPitch;
	BrugiValue maxPWMmotorRoll;
	BrugiValue minRCPitch;
	BrugiValue maxRCPitch;
	BrugiValue minRCRoll;
	BrugiValue maxRCRoll;
	BrugiValue rcGain;
	BrugiValue rcLPF;
	BrugiValue rcModePPM;
	BrugiValue rcChannelPitch;
	BrugiValue rcChannelRoll;
	BrugiValue rcMid;
	BrugiValue rcAbsolute;
	BrugiValue accOutput;
	BrugiValue enableGyro;
	BrugiValue enableACC;
	BrugiValue axisReverseZ;
	BrugiValue axisSwapXY;
} BrugiSetup;

void brugi_update (void);
uint8_t brugi_connection_status (void);
void brugi_init (char *port, uint32_t baud);
void brugi_exit (void);
void brugi_send_cmd (char *cmd);
void brugi_set_value (char *var, float val);
extern BrugiSetup brugi_setup;
