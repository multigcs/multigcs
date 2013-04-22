#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <adc.h>
#include <rcflow.h>
#include <sw.h>
#include <usart.h>
#include <ppm.h>



volatile uint8_t RxBuffer[RXBUFFERSIZE];
volatile uint8_t TxBuffer[TXBUFFERSIZE];

volatile uint16_t RxIndex = 0;
volatile uint16_t TxIndex = 0;


volatile uint16_t TxCounter = 0;
volatile uint16_t NbrOfDataToTransfer = 0;
volatile int8_t test_chksum = 0;
volatile int8_t test_chksum_new = 0;

static int8_t temp_buffer[sizeof(RcFlowPluginEmbedded) + 10];

extern void flash_write(void);


void USART_Config (void) {
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_Init(&NVIC_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	// TX-Pin
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// RX-Pin
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

void USART3_IRQHandler(void) {
	if (USART_GetITStatus(USART3, USART_IT_TXE) == SET) {
		USART_ClearITPendingBit(USART3, USART_IT_TXE);
		USART_SendData(USART3, TxBuffer[TxCounter++]);
		if (TxCounter == NbrOfDataToTransfer) {
			USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
			NbrOfDataToTransfer = 0;
			TxCounter = 0;
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		}
	}
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET) {
		uint8_t rxc = USART_ReceiveData(USART3);
		static uint8_t rxc_last = 0;
		static uint8_t rx_flag = 0;
		if (rx_flag == 0) {
			if (rxc == 'A' && rxc_last == 'A') {
				RxIndex = 0;
				rx_flag = 1;
			} else if (rxc == 'P' && rxc_last == 'P') {
				RxIndex = 0;
				rx_flag = 2;
			} else if (rxc == 'L' && rxc_last == 'L') {
				RxIndex = 0;
				rx_flag = 3;
			}
		} else if (rx_flag == 1) {
			if (RxIndex < sizeof(RcData.RcPluginEmbedded)) {
				char *ptr = (char *)&RcData.RcPluginEmbedded[0];
				ptr[RxIndex++] = rxc;
			} else if (RxIndex < sizeof(RcData.RcPluginEmbedded) + sizeof(RcData.RcLinkEmbedded)) {
				char *ptr = (char *)&RcData.RcLinkEmbedded[0];
				ptr[RxIndex++ - sizeof(RcData.RcPluginEmbedded)] = rxc;
			} else {
				flash_write();
				RxIndex = 0;
				rx_flag = 0;
			}
		} else if (rx_flag == 2) {
			static int8_t plugin_num = 0;
			static int8_t chksum = 0;
			static int8_t chksum_new = 0;
			if (RxIndex < 1) {
				plugin_num = rxc;
				RxIndex++;
				chksum_new = plugin_num;
			} else if (RxIndex < 1 + sizeof(RcFlowPluginEmbedded)) {
				temp_buffer[RxIndex++ - 1] = rxc;
				chksum_new ^= rxc;
			} else if (RxIndex < 1 + sizeof(RcFlowPluginEmbedded) + 1) {
				chksum = rxc;
				test_chksum = chksum;
				test_chksum_new = chksum_new;
				if (chksum_new == chksum) {
					char *ptr = (char *)&RcData.RcPluginEmbedded[plugin_num];
					uint8_t n = 0;
					for (n = 0; n < sizeof(RcFlowPluginEmbedded); n++) {
						ptr[n] = temp_buffer[n];
					}
				}
				RxIndex++;
			} else {
				RxIndex = 0;
				rx_flag = 0;
			}
		} else if (rx_flag == 3) {
			static int8_t link_num = 0;
			static int8_t chksum = 0;
			static int8_t chksum_new = 0;
			if (RxIndex < 1) {
				link_num = rxc;
				RxIndex++;
				chksum_new = link_num;
			} else if (RxIndex < 1 + sizeof(RcFlowLinkEmbedded)) {
				temp_buffer[RxIndex++ - 1] = rxc;
				chksum_new ^= rxc;
			} else if (RxIndex < 1 + sizeof(RcFlowLinkEmbedded) + 1) {
				chksum = rxc;
				test_chksum = chksum;
				test_chksum_new = chksum_new;
				if (chksum_new == chksum) {
					char *ptr = (char *)&RcData.RcLinkEmbedded[link_num];
					uint8_t n = 0;
					for (n = 0; n < sizeof(RcFlowLinkEmbedded); n++) {
						ptr[n] = temp_buffer[n];
					}
				}
				RxIndex++;
			} else {
				RxIndex = 0;
				rx_flag = 0;
			}
		} else {
			RxIndex = 0;
			rx_flag = 0;
		}
		rxc_last = rxc;
	}     
}

void Serial_StartSend (void) {
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}

void Serial_SendText (char *text) {
	uint32_t timeout = 0xFFFF;
	uint16_t len = strlen((char *)text);
	while (NbrOfDataToTransfer > 0 && timeout-- > 1);
	if (timeout > 2 && len < 300) {
		strcpy((char *)TxBuffer, (char *)text);

		NbrOfDataToTransfer = len;

		TxCounter = 0;
		Serial_StartSend();
	}
}

char *int2str (char *str, int16_t value, uint8_t mode, uint8_t digit, uint8_t close_str) {
	char tmp_str[12];
	uint8_t n = 0;
	uint8_t n2 = 0;
	if (value < 0) {
		value *= -1;
		str[n2++] = '-';
	}
	while (value > 9) {
		tmp_str[n++] = (value % 10) + 0x30;
		value /= 10;
	}
	tmp_str[n++] = value + 0x30;
	while (n <= digit || n < mode) {
		tmp_str[n++] = '0';
	}
	tmp_str[n++] = 0;
	uint8_t l = n - 1;
	for (n = 0; n < l; n++) {
		if (l - n == digit) {
			str[n2++] = '.';
		}
		str[n2++] = tmp_str[l - 1 - n];
	}
	str[n2++] = 0;
	return str;
}

void Serial_SendInt (int16_t value) {
	char text[16];
	int2str(text, value, 0, 0, 1);
	Serial_SendText(text);
}







