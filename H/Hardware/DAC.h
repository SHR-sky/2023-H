#ifndef __DAC_H__
#define __DAC_H__

#include "sys.h"

//！！！需TIM触发转换，请额外配置TIM
#define DA1_Value_Length 200
#define DA2_Value_Length 200

void DA1_Init(void);
void DA2_Init(void);

void TIM4_Init(void);
void TIM6_Init(void);

//uint16_t DA1_GetValue();
//uint16_t DA2_GetValue();


#endif

