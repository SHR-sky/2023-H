#ifndef __ADCDMA_H__
#define __ADCDMA_H__

#include "sys.h"  
 
//#define ADC1_DMA_Size  25000 //采样点数
#define ADC1_DMA_Size  1000 //采样点数
 
void ADC_GPIO_Init(void);
void TIM3_Config(void);
void ADC_Config( void );
void ADC_DMA_Trig( u16 Size );
 
#endif
