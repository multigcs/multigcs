
#define MAX_INPUTS	12
#define MAX_OUTPUTS	12
#define MAX_PLUGINS	64
#define MAX_LINKS	64
#define MAX_NAMELEN	16

enum {
	RCFLOW_INOUT_TYPE_BILINEAR,
	RCFLOW_INOUT_TYPE_ONOFF,
	RCFLOW_INOUT_TYPE_LINEAR,
	RCFLOW_INOUT_TYPE_CURVE,
	RCFLOW_INOUT_TYPE_SWITCH,
	RCFLOW_INOUT_TYPE_TEXT,
	RCFLOW_INOUT_TYPE_TEMP,
};

enum {
	RCFLOW_PLUGIN_INPUT,
	RCFLOW_PLUGIN_OUTPUT,
	RCFLOW_PLUGIN_ATV,
	RCFLOW_PLUGIN_LIMIT,
	RCFLOW_PLUGIN_MIXER,
	RCFLOW_PLUGIN_CURVE,
	RCFLOW_PLUGIN_EXPO,
	RCFLOW_PLUGIN_DELAY,
	RCFLOW_PLUGIN_ADC,
	RCFLOW_PLUGIN_SW,
	RCFLOW_PLUGIN_ENC,
	RCFLOW_PLUGIN_PPM,
	RCFLOW_PLUGIN_H120,
	RCFLOW_PLUGIN_SWITCH,
	RCFLOW_PLUGIN_RANGESW,
	RCFLOW_PLUGIN_TIMER,
	RCFLOW_PLUGIN_AND,
	RCFLOW_PLUGIN_OR,
	RCFLOW_PLUGIN_PULSE,
	RCFLOW_PLUGIN_SINUS,
	RCFLOW_PLUGIN_ALARM,
	RCFLOW_PLUGIN_VADC,
	RCFLOW_PLUGIN_VSW,
	RCFLOW_PLUGIN_TCL,
};



typedef struct {
	int16_t value;
	uint8_t type;
	uint8_t option;
} RcFlowSignalEmbedded;

typedef struct {
	uint8_t type;
	uint8_t pad1;
	uint16_t option;
	RcFlowSignalEmbedded input[MAX_INPUTS];
	RcFlowSignalEmbedded output[MAX_OUTPUTS];
} RcFlowPluginEmbedded;

typedef struct {
	uint8_t from[2];
	uint8_t pad1;
	uint8_t pad2;
	uint8_t to[2];
	uint8_t pad3;
	uint8_t pad4;
} RcFlowLinkEmbedded;

typedef struct {
	uint32_t id;
	RcFlowPluginEmbedded RcPluginEmbedded[MAX_PLUGINS];
	RcFlowLinkEmbedded RcLinkEmbedded[MAX_LINKS];
} RcFlowData;


extern volatile RcFlowData RcData;


int16_t rcflow_value_limit(int16_t value, int16_t min, int16_t max);
void rcflow_calc_Embedded(void);
void rcflow_init(void);

