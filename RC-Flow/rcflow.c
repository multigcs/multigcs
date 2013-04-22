#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <adc.h>
#include <rcflow.h>
#include <sw.h>


volatile RcFlowData RcData;


void rcflow_init (void) {
	RcData.RcPluginEmbedded[0].type = RCFLOW_PLUGIN_ADC;
	RcData.RcPluginEmbedded[1].type = RCFLOW_PLUGIN_PPM;
	RcData.RcPluginEmbedded[2].type = RCFLOW_PLUGIN_SW;
	
	RcData.RcLinkEmbedded[0].from[0] = 0;
	RcData.RcLinkEmbedded[0].from[1] = 0;
	RcData.RcLinkEmbedded[0].to[0] = 1;
	RcData.RcLinkEmbedded[0].to[1] = 0;
	
	RcData.RcLinkEmbedded[1].from[0] = 0;
	RcData.RcLinkEmbedded[1].from[1] = 1;
	RcData.RcLinkEmbedded[1].to[0] = 1;
	RcData.RcLinkEmbedded[1].to[1] = 1;
	
	RcData.RcLinkEmbedded[2].from[0] = 0;
	RcData.RcLinkEmbedded[2].from[1] = 2;
	RcData.RcLinkEmbedded[2].to[0] = 1;
	RcData.RcLinkEmbedded[2].to[1] = 2;
}

int16_t rcflow_value_limit (int16_t value, int16_t min, int16_t max) {
	if (value >= max) {
		return max;
	}
	if (value <= min) {
		return min;
	}
	return value;
}


void rcflow_calc_Embedded (void) {
	uint8_t plugin = 0;
#ifdef RPI_NO_X
	uint8_t output = 0;
#endif
	uint8_t link = 0;
	uint8_t n = 0;

	// Zero connected Inputs
	for (link = 0; link < MAX_LINKS; link++) {
		if (RcData.RcLinkEmbedded[link].to[0] != 255 && RcData.RcLinkEmbedded[link].to[1] != 255) {
			RcData.RcPluginEmbedded[RcData.RcLinkEmbedded[link].to[0]].input[RcData.RcLinkEmbedded[link].to[1]].value = 0.0;
		}
	}

	uint8_t output = 0;
	for (plugin = 0; plugin < MAX_PLUGINS; plugin++) {
		if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_ADC) {
			for (output = 0; output < ADC_MAX && output < MAX_OUTPUTS; output++) {
				if (RcData.RcPluginEmbedded[plugin].output[output].option == 1) {
					RcData.RcPluginEmbedded[plugin].output[output].value = rcflow_value_limit((int)Adc_ReadBuffer(output) / 2 - 1000, -1000, 1000) * -1;
				} else {
					RcData.RcPluginEmbedded[plugin].output[output].value = rcflow_value_limit((int)Adc_ReadBuffer(output) / 2 - 1000, -1000, 1000);
				}
			}
		}
	}
	for (plugin = 0; plugin < MAX_PLUGINS; plugin++) {
		if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_SW) {
			for (output = 0; output < SW_MAX && output < MAX_OUTPUTS; output++) {
				RcData.RcPluginEmbedded[plugin].output[output].value = switches[output];
			}
		}
	}

	// Link-Calculation
	for (link = 0; link < MAX_LINKS; link++) {
		if (RcData.RcLinkEmbedded[link].to[0] != 255 && RcData.RcLinkEmbedded[link].to[1] != 255) {
			RcData.RcPluginEmbedded[RcData.RcLinkEmbedded[link].to[0]].input[RcData.RcLinkEmbedded[link].to[1]].value += RcData.RcPluginEmbedded[RcData.RcLinkEmbedded[link].from[0]].output[RcData.RcLinkEmbedded[link].from[1]].value;
			RcData.RcPluginEmbedded[RcData.RcLinkEmbedded[link].to[0]].input[RcData.RcLinkEmbedded[link].to[1]].value = rcflow_value_limit(RcData.RcPluginEmbedded[RcData.RcLinkEmbedded[link].to[0]].input[RcData.RcLinkEmbedded[link].to[1]].value, -1000, 1000);
		}
	}

	// Plugin-Calculation
	for (plugin = 0; plugin < MAX_PLUGINS; plugin++) {
		if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_INPUT) {
			RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value + RcData.RcPluginEmbedded[plugin].input[1].value / 3.0;
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[1].value, -1000, 1000);
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_OUTPUT) {
			RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value + RcData.RcPluginEmbedded[plugin].input[1].value / 3.0;
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[1].value, -1000, 1000);
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_ATV) {
			if (RcData.RcPluginEmbedded[plugin].input[3].value > 0) {
				if (RcData.RcPluginEmbedded[plugin].input[0].value > 0) {
					RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value * RcData.RcPluginEmbedded[plugin].input[1].value / 1000;
				} else if (RcData.RcPluginEmbedded[plugin].input[0].value < 0) {
					RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value * RcData.RcPluginEmbedded[plugin].input[2].value / -1000;
				} else {
					RcData.RcPluginEmbedded[plugin].output[0].value = 0.0;
				}
			} else {
				RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value;
			}
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_MIXER) {
			if (RcData.RcPluginEmbedded[plugin].input[4].value > 0) {
				RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit((RcData.RcPluginEmbedded[plugin].input[0].value * RcData.RcPluginEmbedded[plugin].input[1].value / 1000) + (RcData.RcPluginEmbedded[plugin].input[2].value * RcData.RcPluginEmbedded[plugin].input[3].value / 1000), -1000, 1000);
			} else if (RcData.RcPluginEmbedded[plugin].input[5].value > 0) {
				RcData.RcPluginEmbedded[plugin].output[0].value = 0;
			}
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_LIMIT) {
			if (RcData.RcPluginEmbedded[plugin].input[3].value > 0) {
				RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].input[0].value, RcData.RcPluginEmbedded[plugin].input[2].value, RcData.RcPluginEmbedded[plugin].input[1].value);
			} else {
				RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value;
			}
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_DELAY) {
			if (RcData.RcPluginEmbedded[plugin].input[3].value > 500) {
				float val_up = rcflow_value_limit((RcData.RcPluginEmbedded[plugin].input[1].value + 1000) / 2.0, 0.0, 1000);
				float val_down = rcflow_value_limit((RcData.RcPluginEmbedded[plugin].input[2].value + 1000) / 2.0, 0.0, 1000);
				if (RcData.RcPluginEmbedded[plugin].output[0].value > RcData.RcPluginEmbedded[plugin].input[0].value + val_up) {
					RcData.RcPluginEmbedded[plugin].output[0].value -= val_up;
				} else if (RcData.RcPluginEmbedded[plugin].output[0].value < RcData.RcPluginEmbedded[plugin].input[0].value - val_down) {
					RcData.RcPluginEmbedded[plugin].output[0].value += val_down;
				} else {
					RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value;
				}
			} else {
				RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value;
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_CURVE) {
			int16_t range_begin;
			int16_t range_end;
			float range_pos;
			for (n = 0; n < 7; n++) {
				range_begin = n * 2000 / 6 - 1000;
				range_end = (n + 1) * 2000 / 6 - 1000;
				if (RcData.RcPluginEmbedded[plugin].input[0].value >= range_begin && RcData.RcPluginEmbedded[plugin].input[0].value <= range_end && n < 6) {
					range_pos = (float)(RcData.RcPluginEmbedded[plugin].input[0].value - range_begin) * 1.0 / (float)(range_end - range_begin);
					RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[n + 1].value + (int16_t)((float)(RcData.RcPluginEmbedded[plugin].input[n + 2].value - RcData.RcPluginEmbedded[plugin].input[n + 1].value) * range_pos);
					break;
				}
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_H120) {
			// Reset
			RcData.RcPluginEmbedded[plugin].output[0].value = 0;
			RcData.RcPluginEmbedded[plugin].output[1].value = 0;
			RcData.RcPluginEmbedded[plugin].output[2].value = 0;
			// Roll
			RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value / 2;
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].input[0].value / -2;
			// Nick
			RcData.RcPluginEmbedded[plugin].output[0].value -= RcData.RcPluginEmbedded[plugin].input[1].value / 2;
			RcData.RcPluginEmbedded[plugin].output[1].value -= RcData.RcPluginEmbedded[plugin].input[1].value / 2;
			RcData.RcPluginEmbedded[plugin].output[2].value += RcData.RcPluginEmbedded[plugin].input[1].value;
			// Pitch
			RcData.RcPluginEmbedded[plugin].output[0].value += RcData.RcPluginEmbedded[plugin].input[2].value;
			RcData.RcPluginEmbedded[plugin].output[1].value += RcData.RcPluginEmbedded[plugin].input[2].value;
			RcData.RcPluginEmbedded[plugin].output[2].value += RcData.RcPluginEmbedded[plugin].input[2].value;
			// Limits
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[1].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[2].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[2].value, -1000, 1000);
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_SWITCH) {
			if (RcData.RcPluginEmbedded[plugin].input[2].value > 0) {
				RcData.RcPluginEmbedded[plugin].output[0].value = 0;
				RcData.RcPluginEmbedded[plugin].output[1].value = 0;
				RcData.RcPluginEmbedded[plugin].output[2].value = 0;
				RcData.RcPluginEmbedded[plugin].output[3].value = 0;
			}
			if (RcData.RcPluginEmbedded[plugin].input[3].value < 500) {
				RcData.RcPluginEmbedded[plugin].output[0].value = RcData.RcPluginEmbedded[plugin].input[0].value;
				RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].input[1].value;
			} else if (RcData.RcPluginEmbedded[plugin].input[3].value > 500) {
				RcData.RcPluginEmbedded[plugin].output[2].value = RcData.RcPluginEmbedded[plugin].input[0].value;
				RcData.RcPluginEmbedded[plugin].output[3].value = RcData.RcPluginEmbedded[plugin].input[1].value;
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[1].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[2].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[2].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[3].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[3].value, -1000, 1000);
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_RANGESW) {
			if (RcData.RcPluginEmbedded[plugin].input[0].value >= RcData.RcPluginEmbedded[plugin].input[1].value && RcData.RcPluginEmbedded[plugin].input[0].value <= RcData.RcPluginEmbedded[plugin].input[2].value) {
				RcData.RcPluginEmbedded[plugin].output[0].value = 1000;
			} else {
				RcData.RcPluginEmbedded[plugin].output[0].value = -1000;
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_ALARM) {
			if (RcData.RcPluginEmbedded[plugin].input[0].value >= RcData.RcPluginEmbedded[plugin].input[1].value && RcData.RcPluginEmbedded[plugin].input[0].value <= RcData.RcPluginEmbedded[plugin].input[2].value) {
				RcData.RcPluginEmbedded[plugin].output[0].value = 1000;
			} else {
				RcData.RcPluginEmbedded[plugin].output[0].value = -1000;
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_TIMER) {
			if (RcData.RcPluginEmbedded[plugin].input[1].value > 0) {
				RcData.RcPluginEmbedded[plugin].output[2].value = -1000;
			} else if (RcData.RcPluginEmbedded[plugin].input[0].value > 0 && RcData.RcPluginEmbedded[plugin].output[2].value < RcData.RcPluginEmbedded[plugin].input[2].value) {
				RcData.RcPluginEmbedded[plugin].output[2].value++;
			}
			if (RcData.RcPluginEmbedded[plugin].output[2].value >= RcData.RcPluginEmbedded[plugin].input[2].value) {
				RcData.RcPluginEmbedded[plugin].output[0].value = 1000;
			} else {
				RcData.RcPluginEmbedded[plugin].output[0].value = -1000;
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_AND) {
			if (RcData.RcPluginEmbedded[plugin].input[0].value > 0 && RcData.RcPluginEmbedded[plugin].input[1].value > 0) {
				RcData.RcPluginEmbedded[plugin].output[0].value = 1000;
			} else {
				RcData.RcPluginEmbedded[plugin].output[0].value = -1000;
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_OR) {
			if (RcData.RcPluginEmbedded[plugin].input[0].value > 0 || RcData.RcPluginEmbedded[plugin].input[1].value > 0) {
				RcData.RcPluginEmbedded[plugin].output[0].value = 1000;
			} else {
				RcData.RcPluginEmbedded[plugin].output[0].value = -1000;
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_PULSE) {
			if (RcData.RcPluginEmbedded[plugin].input[0].value > 0 && RcData.RcPluginEmbedded[plugin].output[2].value <= 0) {
				RcData.RcPluginEmbedded[plugin].output[2].value = RcData.RcPluginEmbedded[plugin].input[1].value;
			} else if (RcData.RcPluginEmbedded[plugin].output[2].value > 1) {
				RcData.RcPluginEmbedded[plugin].output[2].value--;
				RcData.RcPluginEmbedded[plugin].output[0].value = 1000;
			} else if (RcData.RcPluginEmbedded[plugin].input[0].value <= 0) {
				RcData.RcPluginEmbedded[plugin].output[2].value = 0;
			}
			if (RcData.RcPluginEmbedded[plugin].output[2].value > 1) {
				RcData.RcPluginEmbedded[plugin].output[0].value = 1000;
			} else {
				RcData.RcPluginEmbedded[plugin].output[0].value = -1000;
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		} else if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_SINUS) {
			uint16_t speed = (RcData.RcPluginEmbedded[plugin].input[0].value + 1000) / 2 / 100;
			if (RcData.RcPluginEmbedded[plugin].output[2].value == 1) {
				if (RcData.RcPluginEmbedded[plugin].output[0].value > -1000 + speed) {
					RcData.RcPluginEmbedded[plugin].output[0].value -= speed;
				} else {
					RcData.RcPluginEmbedded[plugin].output[0].value = -1000;
					RcData.RcPluginEmbedded[plugin].output[2].value = 0;
				}
			} else {
				if (RcData.RcPluginEmbedded[plugin].output[0].value < 1000 - speed) {
					RcData.RcPluginEmbedded[plugin].output[0].value += speed;
				} else {
					RcData.RcPluginEmbedded[plugin].output[0].value = 1000;
					RcData.RcPluginEmbedded[plugin].output[2].value = 1;
				}
			}
			RcData.RcPluginEmbedded[plugin].output[0].value = rcflow_value_limit(RcData.RcPluginEmbedded[plugin].output[0].value, -1000, 1000);
			RcData.RcPluginEmbedded[plugin].output[1].value = RcData.RcPluginEmbedded[plugin].output[0].value * -1.0;
		}
	}
}

