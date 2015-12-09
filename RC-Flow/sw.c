#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <adc.h>
#include <rcflow.h>
#include <sw.h>


volatile int16_t switches[SW_MAX];


void SW_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_9 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}


void SW_Update(void) {
	static uint8_t flag = 0;
	static uint8_t stat[10];
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	if (flag == 0) {
		stat[0] = 0;
		stat[1] = 0;
		stat[2] = 0;
		stat[3] = 0;
		stat[4] = 0;
		stat[5] = 0;
		stat[6] = 0;
		stat[7] = 0;
		stat[8] = 0;
		stat[9] = 0;
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) != 0) {
			stat[0] |= (1 << 0);
		}
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) != 0) {
			stat[1] |= (1 << 0);
		}
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) != 0) {
			stat[2] |= (1 << 0);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) != 0) {
			stat[3] |= (1 << 0);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) != 0) {
			stat[4] |= (1 << 0);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) != 0) {
			stat[5] |= (1 << 0);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) != 0) {
			stat[6] |= (1 << 0);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) != 0) {
			stat[7] |= (1 << 0);
		}
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) != 0) {
			stat[8] |= (1 << 0);
		}
		if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) != 0) {
			stat[9] |= (1 << 0);
		}
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_13 | GPIO_Pin_14;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_9 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
	} else {
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0) {
			stat[0] |= (1 << 1);
		}
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 0) {
			stat[1] |= (1 << 1);
		}
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 0) {
			stat[2] |= (1 << 1);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0) {
			stat[3] |= (1 << 1);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0) {
			stat[4] |= (1 << 1);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0) {
			stat[5] |= (1 << 1);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0) {
			stat[6] |= (1 << 1);
		}
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0) {
			stat[7] |= (1 << 1);
		}
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) == 0) {
			stat[8] |= (1 << 1);
		}
		if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) == 0) {
			stat[9] |= (1 << 1);
		}
		switches[0] = stat[2];
		switches[1] = stat[0];
		switches[2] = stat[1];
		switches[3] = stat[5];
		switches[4] = stat[4];
		switches[5] = stat[3];
		switches[6] = stat[9];
		switches[7] = stat[8];
		switches[8] = stat[7];
		switches[9] = stat[6];
		uint8_t n = 0;
		for (n = 0; n < SW_MAX; n++) {
			if (switches[n] == 1) {
				switches[n] = -1000;
			} else if (switches[n] == 2) {
				switches[n] = 1000;
			}
		}
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_13 | GPIO_Pin_14;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_9 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
	}
	flag = 1 - flag;
}

