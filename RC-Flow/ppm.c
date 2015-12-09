#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <adc.h>
#include <rcflow.h>
#include <sw.h>
#include <usart.h>
#include <ppm.h>


static uint16_t ppm_channel_values[16];



void PPM_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	GPIO_InitStructure.GPIO_Pin = PPM1_OUTPUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PPM1_OUTPUT_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(PPM1_OUTPUT_PORT, PPM1_OUTPUT_PINS, PPM1_OUTPUT_AF);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = PPM_PRESCALE - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);
	TIM_Cmd(TIM3, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
}

void PPMOutput_Set(int8_t channel, int16_t value) {
	ppm_channel_values[channel] = value / 4;
}

void TIM3_IRQHandler(void) {
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
	static uint16_t total_len = 0;
	static uint16_t pulse = 0;
	static uint16_t capture = 0;
	static uint8_t updown = 0;
	static uint8_t channel = 0;
	static uint8_t mchannel = 0;
	if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET) {
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
		capture = TIM_GetCapture3(TIM3);
		if (GPIO_ReadInputDataBit(PPM1_OUTPUT_PORT, PPM1_OUTPUT_PIN) != 0) {
			updown = 1;
		} else {
			updown = 0;
		}
		if (updown == 0) {
			pulse = 300;
			TIM_SetCompare3(TIM3, capture + pulse * PPM_SCALE);
			total_len += pulse;
		} else {
			if (channel < 8) {
				pulse = (1000 - 300 + ppm_channel_values[channel]);
				TIM_SetCompare3(TIM3, capture + pulse * PPM_SCALE);
				total_len += pulse;
				channel++;
			} else {
				TIM_SetCompare3(TIM3, capture + (7000) * PPM_SCALE);
				channel = 0;
				total_len = 0;
			}
		}
	}
}
