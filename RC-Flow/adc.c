#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <adc.h>


#define ADC_INPUT_PINS_A		GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
#define ADC_INPUT_PINS_C		GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
#define ADC1_DR_Address			((uint32_t)0x40012308)
#define ADC_SPEED			ADC_SampleTime_28Cycles
#define ADC_AVERANGE			30


static uint8_t ADC_CHANNEL_NUMS[] = {ADC_Channel_10, ADC_Channel_11, ADC_Channel_12, ADC_Channel_13, ADC_Channel_0, ADC_Channel_1, ADC_Channel_2, ADC_Channel_3, ADC_Channel_4, ADC_Channel_5, ADC_Channel_6, ADC_Channel_7};
static uint32_t adc_buffer[ADC_MAX *ADC_AVERANGE];


void ADC_Config(void) {
	uint8_t channel;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
#ifdef ADC_INPUT_PINS_A
	GPIO_InitStructure.GPIO_Pin = ADC_INPUT_PINS_A;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#ifdef ADC_INPUT_PINS_B
	GPIO_InitStructure.GPIO_Pin = ADC_INPUT_PINS_B;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef ADC_INPUT_PINS_C
	GPIO_InitStructure.GPIO_Pin = ADC_INPUT_PINS_C;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA2_Stream0);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)&adc_buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = ADC_MAX * ADC_AVERANGE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0, ENABLE);
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_2;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//	ADC_InitStructure.ADC_ExternalTrigConv=0x00;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = ADC_MAX;
	ADC_Init(ADC1, &ADC_InitStructure);
	//	ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	for (channel = 0; channel < ADC_MAX; channel++) {
		adc_buffer[channel] = 56;
		ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_NUMS[channel], channel + 1, ADC_SPEED);
	}
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
	ADC_DMACmd(ADC1, ENABLE);
}

uint32_t Adc_ReadBuffer(int8_t channel) {
	uint8_t num;
	uint32_t value = 0;
	for (num = 0; num < ADC_AVERANGE; num++) {
		value += adc_buffer[channel + (num * ADC_MAX)];
	}
	return (uint16_t)(value / ADC_AVERANGE);
}

