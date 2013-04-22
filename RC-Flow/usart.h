
#define TXBUFFERSIZE   70
#define RXBUFFERSIZE   TXBUFFERSIZE

extern volatile uint8_t RxBuffer[RXBUFFERSIZE];
extern volatile uint8_t TxBuffer[TXBUFFERSIZE];
extern volatile uint16_t RxIndex;
extern volatile uint16_t TxIndex;

void USART_Config (void);
void Serial_StartSend (void);
void Serial_SendText (char *text);
char *int2str (char *str, int16_t value, uint8_t mode, uint8_t digit, uint8_t close_str);
void Serial_SendInt (int16_t value);

