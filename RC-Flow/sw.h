
#define SW_MAX				10

extern volatile int16_t switches[SW_MAX];

void SW_Config (void);
void SW_Update (void);

