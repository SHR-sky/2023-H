#include "DAC.h"

// 主频84M
u8 do_ad_flag1;
uint16_t meDA1_Value[DA1_Value_Length] = {
	2142, 2236, 2329, 2421, 2512, 2600, 2687, 2771, 2852, 2930, 3004, 3075, 3141, 3204, 3262, 3314, 3362, 3405, 3443, 3475, 3501, 3521, 3536, 3545, 3548, 3545, 3536, 3521, 3501, 3475, 3443, 3405, 3362, 3314, 3262, 3204, 3141, 3075, 3004, 2930, 2852, 2771, 2687, 2600, 2512, 2421, 2329, 2236, 2142, 2048, 1954, 1860, 1767, 1675, 1584, 1496, 1409, 1325, 1244, 1166, 1092, 1021, 955, 892, 834, 782, 734, 691, 653, 621, 595, 575, 560, 551, 548, 551, 560, 575, 595, 621, 653, 691, 734, 782, 834, 892, 955, 1021, 1092, 1166, 1244, 1325, 1409, 1496, 1584, 1675, 1767, 1860, 1954, 2048, 2142, 2236, 2329, 2421, 2512, 2600, 2687, 2771, 2852, 2930, 3004, 3075, 3141, 3204, 3262, 3314, 3362, 3405, 3443, 3475, 3501, 3521, 3536, 3545, 3548, 3545, 3536, 3521, 3501, 3475, 3443, 3405, 3362, 3314, 3262, 3204, 3141, 3075, 3004, 2930, 2852, 2771, 2687, 2600, 2512, 2421, 2329, 2236, 2142, 2048, 1954, 1860, 1767, 1675, 1584, 1496, 1409, 1325, 1244, 1166, 1092, 1021, 955, 892, 834, 782, 734, 691, 653, 621, 595, 575, 560, 551, 548, 551, 560, 575, 595, 621, 653, 691, 734, 782, 834, 892, 955, 1021, 1092, 1166, 1244, 1325, 1409, 1496, 1584, 1675, 1767, 1860, 1954, 2048};
uint16_t meDA2_Value[DA2_Value_Length] = {
	3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548};

// TIM4 16bit
void TIM4_Init(void)
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // TIM4 时钟使能

	TIM_InternalClockConfig(TIM4);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				// 时基结构体
	TIM_TimeBaseInitStructure.TIM_Period = 83;						// 设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0x0;					// 设置预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;				// 设置时钟分割
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式

	TIM_SelectOutputTrigger(TIM4, TIM_TRGOSource_Update); // 更新溢出向外触发
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);	  // 时基初始化
	TIM_Cmd(TIM4, ENABLE);								  // 定时器使能
}

// TIM6 32bit
void TIM6_Init(void)
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); // TIM5 时钟使能

	TIM_InternalClockConfig(TIM6);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				// 时基结构体
	TIM_TimeBaseInitStructure.TIM_Period = 83;						// 设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0x0;					// 设置预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;				// 设置时钟分割
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式

	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update); // 更新溢出向外触发
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);	  // 时基初始化
	TIM_Cmd(TIM6, ENABLE);								  // 定时器使能
}

// DAC1; PA4; DMA_CH7; DMA1_Stream5; TIM4;
void DA1_Init()
{
	// 结构体定义
	GPIO_InitTypeDef GPIO_InitStructure; // GPIO结构体
	DAC_InitTypeDef DAC_InitStructure;	 // DAC结构体
	DMA_InitTypeDef DMA_InitStructure;	 // DMA结构体

	// 时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);	  // 使能DAC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  // 使能DMA1时钟

	// GPIO配置初始化 PA4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	 // PIN4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; // 模拟模式
	//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);			 // GPIO结构体初始化

	// DAC配置初始化
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T4_TRGO; // ！！！定时器触发转换 一次转移数组里的一个数据 TIM4
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure); // DAC1初始化
												 // DAC设置数据对齐
	DAC_SetChannel1Data(DAC_Align_12b_R, 0); // 右对齐

	// DMA配置初始化
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;			// DMA_CH7
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;			// 循环模式
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // 内存到外设
	DMA_InitStructure.DMA_BufferSize = DA1_Value_Length;	// 传输次数:数组长度
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;	// 优先级
														  // DMA_FIFO
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;

	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)meDA1_Value; // 内存地址:输出DA值数组
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // 16 bit
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				// 内存自增

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (DAC->DHR12R1); // 外设地址:DAC1地址
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16 bit
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// 外设不自增
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);									// DMA1_Stream5 初始化

	DMA_Cmd(DMA1_Stream5, ENABLE);	   // DMA1_Stream5 使能
	DAC_DMACmd(DAC_Channel_1, ENABLE); // DAC1_DMA 使能
	DAC_Cmd(DAC_Channel_1, ENABLE);	   // DAC1 使能

	NVIC_InitTypeDef NVIC_InitStructure; /* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_ITConfig(DMA1_Stream5, DMA_IT_TC, ENABLE);
}

void DMA1_Stream5_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA1_Stream5, DMA_IT_TCIF5))
	{													   // 判断通道2是否传输完成
		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5); // 清除通道2传输完成标志位
		do_ad_flag1 = 1;								   // 把全局标志置位，表示可以同步开始AD转换了
	}
}

// DAC1; PA5; DMA_CH7; DMA1_Stream6; TIM5;
void DA2_Init()
{
	// 结构体定义
	GPIO_InitTypeDef GPIO_InitStructure; // GPIO结构体
	DAC_InitTypeDef DAC_InitStructure;	 // DAC结构体
	DMA_InitTypeDef DMA_InitStructure;	 // DMA结构体

	// 时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);	  // 使能DAC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  // 使能DMA1时钟

	// GPIO配置初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	 // PIN5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; // 模拟模式
	//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);			 // GPIO结构体初始化

	// DAC配置初始化
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO; // ！！！定时器触发转换 一次转移数组里的一个数据 TIM5
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_2, &DAC_InitStructure); // DAC2初始化
												 // DAC设置数据对齐
	DAC_SetChannel2Data(DAC_Align_12b_R, 0); // 右对齐

	// DMA配置初始化
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;			// DMA_CH7
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;			// 循环模式
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // 内存到外设
	DMA_InitStructure.DMA_BufferSize = DA2_Value_Length;	// 传输次数:数组长度
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;	// 优先级
														  // DMA_FIFO
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;

	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)meDA2_Value; // 内存地址:输出DA值数组
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // 16 bit
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				// 内存自增

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (DAC->DHR12R2); // 外设地址:DAC2地址
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16 bit
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// 外设不自增
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);									// DMA1_Stream6 初始化

	DMA_Cmd(DMA1_Stream6, ENABLE);	   // DMA1_Stream6 使能
	DAC_DMACmd(DAC_Channel_2, ENABLE); // DAC2_DMA 使能
	DAC_Cmd(DAC_Channel_2, ENABLE);	   // DAC2 使能
}
