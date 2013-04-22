
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <adc.h>
#include <rcflow.h>
#include <sw.h>
#include <usart.h>
#include <ppm.h>


void Delay(__IO uint32_t nCount) {
	while(nCount--) {
		__ASM volatile ("nop");
	}
}

static void SysTickConfig (void) {
	if (SysTick_Config(SystemCoreClock / 100)) {
	}
	NVIC_SetPriority(SysTick_IRQn, 0x0);
}

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define DATA_ID 515161


void flash_write (void) {
	uint32_t Address = ADDR_FLASH_SECTOR_10;
	uint32_t SectorCounter = 0;
	uint32_t *data = (uint32_t *)&RcData;
	uint32_t pos = 0;
	RcData.id = DATA_ID;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR); 
	for (SectorCounter = FLASH_Sector_10; SectorCounter < FLASH_Sector_11; SectorCounter += 8) {
		if (FLASH_EraseSector(SectorCounter, VoltageRange_3) != FLASH_COMPLETE) { 
			Serial_SendText("Error: FLASH_EraseSector\n\r");
			FLASH_Lock(); 
			return;
		}
	}
	while (Address < ADDR_FLASH_SECTOR_11 && pos < sizeof(RcData)) {
		if (FLASH_ProgramWord(Address, data[pos]) == FLASH_COMPLETE) {
			Address += 4;
			pos++;
		} else { 
			Serial_SendText("Error: FLASH_ProgramWord\n\r");
			FLASH_Lock(); 
			return;
		}
	}
	FLASH_Lock(); 
}



void flash_read (void) {
	uint32_t Address = ADDR_FLASH_SECTOR_10;
	uint32_t *data = (uint32_t *)&RcData;
	uint32_t pos = 0;
	RcData.id = 0;
	while (Address < ADDR_FLASH_SECTOR_11 && pos < sizeof(RcData)) {
		data[pos] = *(__IO uint32_t*)Address;
		Address += 4;
		pos++;
	}  
	if (RcData.id != DATA_ID) {
		Serial_SendText("DATA_ERROR\n\r");
		rcflow_init();
	}
}  
 


int main (void) {
	rcflow_init();
	SysTickConfig();
	USART_Config();
	ADC_Config();
	PPM_Config();
	SW_Config();
	SW_Update();
	flash_read();


	int n = 0;
	while (1) {
		SW_Update();

		char tmp_str[100];
		Serial_SendText("ADC:");
		for (n = 0; n < ADC_MAX; n++) {
			sprintf(tmp_str, "%i;", rcflow_value_limit((int)Adc_ReadBuffer(n) / 2 - 1000, -1000, 1000));
			Serial_SendText(tmp_str);
		}
		Serial_SendText("\n\r");

		Serial_SendText("SW:");
		for (n = 0; n < SW_MAX; n++) {
			sprintf(tmp_str, "%i;", switches[n]);
			Serial_SendText(tmp_str);
		}
		Serial_SendText("\n\r");

		for (n = 0; n < 100; n++) {
			rcflow_calc_Embedded();
		}

		uint8_t plugin = 0;
		uint8_t output = 0;
		Serial_SendText("OUT:");
		for (plugin = 0; plugin < MAX_PLUGINS; plugin++) {
			if (RcData.RcPluginEmbedded[plugin].type == RCFLOW_PLUGIN_PPM) {
				for (output = 0; output < 8; output++) {
					if (RcData.RcPluginEmbedded[plugin].input[output].option == 1) {
						PPMOutput_Set(output, RcData.RcPluginEmbedded[plugin].input[output].value * -1);
						Serial_SendInt(RcData.RcPluginEmbedded[plugin].input[output].value * -1);
					} else {
						PPMOutput_Set(output, RcData.RcPluginEmbedded[plugin].input[output].value);
						Serial_SendInt(RcData.RcPluginEmbedded[plugin].input[output].value);
					}
					Serial_SendText(";");
				}
			}
		}
		Serial_SendText("\n\r");
	}
}



