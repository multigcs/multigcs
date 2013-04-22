
#define PPM_PRESCALE 42 // 72000000Hz / 18 = 4000000Hz (expr 168000000 / 4000000 == 42)
#define PPM_MS 4000	// 4000000Hz / 4000 = 1000Hz (1ms)
#define PPM_SCALE 4

#define PPM1_OUTPUT_PIN			GPIO_Pin_8
#define PPM1_OUTPUT_PORT		GPIOC
#define PPM1_OUTPUT_PINS		GPIO_PinSource8
#define PPM1_OUTPUT_AF			GPIO_AF_TIM3

void PPM_Config (void);
void PPMOutput_Set (int8_t channel, int16_t value);

