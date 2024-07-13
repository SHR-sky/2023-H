#include "DAC.h"

//主频84M
u8 do_ad_flag1;
u8 do_ad_flag2;
uint16_t meDA1_Value[DA1_Value_Length] = {
	2142, 2236, 2329, 2421, 2512, 2600, 2687, 2771, 2852, 2930, 3004, 3075, 3141, 3204, 3262, 3314, 3362, 3405, 3443, 3475, 3501, 3521, 3536, 3545, 3548, 3545, 3536, 3521, 3501, 3475, 3443, 3405, 3362, 3314, 3262, 3204, 3141, 3075, 3004, 2930, 2852, 2771, 2687, 2600, 2512, 2421, 2329, 2236, 2142, 2048, 1954, 1860, 1767, 1675, 1584, 1496, 1409, 1325, 1244, 1166, 1092, 1021, 955, 892, 834, 782, 734, 691, 653, 621, 595, 575, 560, 551, 548, 551, 560, 575, 595, 621, 653, 691, 734, 782, 834, 892, 955, 1021, 1092, 1166, 1244, 1325, 1409, 1496, 1584, 1675, 1767, 1860, 1954, 2048, 2142, 2236, 2329, 2421, 2512, 2600, 2687, 2771, 2852, 2930, 3004, 3075, 3141, 3204, 3262, 3314, 3362, 3405, 3443, 3475, 3501, 3521, 3536, 3545, 3548, 3545, 3536, 3521, 3501, 3475, 3443, 3405, 3362, 3314, 3262, 3204, 3141, 3075, 3004, 2930, 2852, 2771, 2687, 2600, 2512, 2421, 2329, 2236, 2142, 2048, 1954, 1860, 1767, 1675, 1584, 1496, 1409, 1325, 1244, 1166, 1092, 1021, 955, 892, 834, 782, 734, 691, 653, 621, 595, 575, 560, 551, 548, 551, 560, 575, 595, 621, 653, 691, 734, 782, 834, 892, 955, 1021, 1092, 1166, 1244, 1325, 1409, 1496, 1584, 1675, 1767, 1860, 1954, 2048
};
uint16_t meDA2_Value[DA2_Value_Length] = {
	3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548
};

//TIM4 16bit
void TIM4_Init(void){
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); 			//TIM4 时钟使能
	                                                                
	TIM_InternalClockConfig(TIM4);	                                
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;	            //时基结构体
	TIM_TimeBaseInitStructure.TIM_Period = 83; 					//设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0x0; 					//设置预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0; 				//设置时钟分割
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	                                                                
	TIM_SelectOutputTrigger(TIM4,TIM_TRGOSource_Update);			//更新溢出向外触发
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure); 			//时基初始化
	//TIM_Cmd(TIM4, ENABLE);                                          //定时器使能
}


//TIM6 32bit
void TIM6_Init(void){
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE); 			//TIM5 时钟使能
	                                                                
	TIM_InternalClockConfig(TIM6);                                  
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//时基结构体
	TIM_TimeBaseInitStructure.TIM_Period = 83;                     //设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0x0;                   //设置预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;                //设置时钟分割
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	                                                                
	TIM_SelectOutputTrigger(TIM6,TIM_TRGOSource_Update);            //更新溢出向外触发
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);             //时基初始化
	//TIM_Cmd(TIM6, ENABLE);                                          //定时器使能
}

//DAC1; PA4; DMA_CH7; DMA1_Stream5; TIM4;
void DA1_Init(){
	//结构体定义
	GPIO_InitTypeDef  GPIO_InitStructure;	//GPIO结构体
	DAC_InitTypeDef DAC_InitStructure;		//DAC结构体
	DMA_InitTypeDef DMA_InitStructure;		//DMA结构体
	
	//时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);		//使能DAC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);		//使能DMA1时钟
	
	//GPIO配置初始化 PA4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				//PIN4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;			//模拟模式		
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;		//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//GPIO结构体初始化
	
	//DAC配置初始化
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T4_TRGO; 			//！！！定时器触发转换 一次转移数组里的一个数据 TIM4
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);					//DAC1初始化
		//DAC设置数据对齐
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);						//右对齐


	//DMA配置初始化
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;				//DMA_CH7
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 			//循环模式
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;		//内存到外设
	DMA_InitStructure.DMA_BufferSize = DA1_Value_Length;		//传输次数:数组长度
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;		//优先级
		//DMA_FIFO
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)meDA1_Value; 		//内存地址:输出DA值数组
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	//16 bit
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				//内存自增

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(DAC->DHR12R1); 		//外设地址:DAC1地址
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//16 bit
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//外设不自增
	DMA_Init(DMA1_Stream5,&DMA_InitStructure);									//DMA1_Stream5 初始化
	
	DMA_Cmd(DMA1_Stream5,ENABLE);		//DMA1_Stream5 使能
	DAC_DMACmd(DAC_Channel_1, ENABLE);	//DAC1_DMA 使能  	
	DAC_Cmd(DAC_Channel_1,ENABLE); 		//DAC1 使能
	
	NVIC_InitTypeDef NVIC_InitStructure;     /* Configure one bit for preemption priority */
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
	if(DMA_GetITStatus(DMA1_Stream5,DMA_IT_TCIF5)) {//判断通道2是否传输完成
		DMA_ClearITPendingBit(DMA1_Stream5,DMA_IT_TCIF5);    //清除通道2传输完成标志位
		do_ad_flag1 = 1;//把全局标志置位，表示可以同步开始AD转换了
     }
}

//DAC1; PA5; DMA_CH7; DMA1_Stream6; TIM5;
void DA2_Init(){
	//结构体定义
	GPIO_InitTypeDef  GPIO_InitStructure;	//GPIO结构体
	DAC_InitTypeDef DAC_InitStructure;		//DAC结构体
	DMA_InitTypeDef DMA_InitStructure;      //DMA结构体

	//时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);     //使能DAC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);     //使能DMA1时钟
	
	//GPIO配置初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				//PIN5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;            //模拟模式		
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);                  //GPIO结构体初始化
	
	//DAC配置初始化
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;					//！！！定时器触发转换 一次转移数组里的一个数据 TIM5
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;         
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);                            //DAC2初始化
		//DAC设置数据对齐
	DAC_SetChannel2Data(DAC_Align_12b_R, 0);								//右对齐
	
	
	//DMA配置初始化
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;							//DMA_CH7
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         //循环模式
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;                 //内存到外设
	DMA_InitStructure.DMA_BufferSize = DA2_Value_Length;                    //传输次数:数组长度
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   //优先级
		//DMA_FIFO
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)meDA2_Value;			//内存地址:输出DA值数组
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;             
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     //16 bit
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 //内存自增

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(DAC->DHR12R2);			//外设地址:DAC2地址
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;             
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;     //16 bit
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                //外设不自增
	DMA_Init(DMA1_Stream6,&DMA_InitStructure);			                            //DMA1_Stream6 初始化 
	
	NVIC_InitTypeDef NVIC_InitStructure;     /* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);     
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);
	
	DMA_Cmd(DMA1_Stream6,ENABLE);				//DMA1_Stream6 使能
	DAC_DMACmd(DAC_Channel_2, ENABLE);          //DAC2_DMA 使能  	
	DAC_Cmd(DAC_Channel_2,ENABLE);              //DAC2 使能
}

void DMA1_Stream6_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_Stream6,DMA_IT_TCIF6)) {//判断通道2是否传输完成
		DMA_ClearITPendingBit(DMA1_Stream6,DMA_IT_TCIF6);    //清除通道2传输完成标志位
		do_ad_flag2 = 1;//把全局标志置位，表示可以同步开始AD转换了
     }
}

/*
#define DAC_DHR12RD_Address (uint32_t)(DAC_BASE+0x20)
#define DAC_CLK RCC_APB1Periph_DAC
#define DAC_TIM TIM2
#define DAC_TIM_CLK RCC_APB1Periph_TIM2
#define DAC_TRIGGER DAC_Trigger_T2_TRGO

#define DAC_DMA_CLK RCC_AHB1Periph_DMA1
#define DAC_CHANNEL DMA_Channel_7
#define DAC_DMA_STREAM DMA1_Stream5

#define DAC_CH1_GPIO_CLK RCC_AHB1Periph_GPIOA
#define DAC_CH1_GPIO_PORT GPIOA
#define DAC_CH1_GPIO_PIN GPIO_Pin_4
#define DAC_CH1_CHANNEL DAC_Channel_1

#define DAC_TIM2 TIM4
#define DAC_TIM2_CLK RCC_APB1Periph_TIM4
#define DAC_TRIGGER2 DAC_Trigger_T4_TRGO
#define DAC_CH2_GPIO_CLK RCC_AHB1Periph_GPIOA
#define DAC_CH2_GPIO_PORT GPIOA
#define DAC_CH2_GPIO_PIN GPIO_Pin_5
#define DAC_CH2_CHANNEL DAC_Channel_2

#define DAC_DMA_STREAM2 DMA1_Stream6

uint16_t Sine12bit1[200] = {
	2142, 2236, 2329, 2421, 2512, 2600, 2687, 2771, 2852, 2930, 3004, 3075, 3141, 3204, 3262, 3314, 3362, 3405, 3443, 3475, 3501, 3521, 3536, 3545, 3548, 3545, 3536, 3521, 3501, 3475, 3443, 3405, 3362, 3314, 3262, 3204, 3141, 3075, 3004, 2930, 2852, 2771, 2687, 2600, 2512, 2421, 2329, 2236, 2142, 2048, 1954, 1860, 1767, 1675, 1584, 1496, 1409, 1325, 1244, 1166, 1092, 1021, 955, 892, 834, 782, 734, 691, 653, 621, 595, 575, 560, 551, 548, 551, 560, 575, 595, 621, 653, 691, 734, 782, 834, 892, 955, 1021, 1092, 1166, 1244, 1325, 1409, 1496, 1584, 1675, 1767, 1860, 1954, 2048, 2142, 2236, 2329, 2421, 2512, 2600, 2687, 2771, 2852, 2930, 3004, 3075, 3141, 3204, 3262, 3314, 3362, 3405, 3443, 3475, 3501, 3521, 3536, 3545, 3548, 3545, 3536, 3521, 3501, 3475, 3443, 3405, 3362, 3314, 3262, 3204, 3141, 3075, 3004, 2930, 2852, 2771, 2687, 2600, 2512, 2421, 2329, 2236, 2142, 2048, 1954, 1860, 1767, 1675, 1584, 1496, 1409, 1325, 1244, 1166, 1092, 1021, 955, 892, 834, 782, 734, 691, 653, 621, 595, 575, 560, 551, 548, 551, 560, 575, 595, 621, 653, 691, 734, 782, 834, 892, 955, 1021, 1092, 1166, 1244, 1325, 1409, 1496, 1584, 1675, 1767, 1860, 1954, 2048};
uint16_t Sine12bit2[200] = {3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548, 3262, 2512, 1584, 834, 548, 834, 1584, 2512, 3262, 3548};
	
uint32_t DualSine12bit[3200];

void DAC1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	
	RCC_AHB1PeriphClockCmd(DAC_CH1_GPIO_CLK|DAC_CH2_GPIO_CLK, ENABLE);
	
	RCC_APB1PeriphClockCmd(DAC_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = DAC_CH1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(DAC_CH1_GPIO_PORT, &GPIO_InitStructure);

	//GPIO_InitStructure.GPIO_Pin = DAC_CH2_GPIO_PIN;
	//GPIO_Init(DAC_CH2_GPIO_PORT, &GPIO_InitStructure);

	DAC_InitStructure.DAC_Trigger = DAC_TRIGGER;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;
	DAC_Init(DAC_CH1_CHANNEL, &DAC_InitStructure);
	
	DAC_Init(DAC_CH2_CHANNEL, &DAC_InitStructure);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	//DAC_Cmd(DAC_Channel_2, ENABLE);
	
	DAC_DMACmd(DAC_Channel_1, ENABLE);
}

void DAC1_TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(DAC_TIM_CLK, ENABLE);

	// 1M
	TIM_TimeBaseStructure.TIM_Period = 83;
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(DAC_TIM, &TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(DAC_TIM, TIM_TRGOSource_Update);
	
	TIM_Cmd(DAC_TIM, ENABLE);
}

void DAC1_Mode_Init(void)
{
	uint32_t Idx = 0;
	DAC1_Config();
	DAC1_TIM_Config();
	for (Idx = 0; Idx < 200; Idx++) {
		DualSine12bit[Idx] = (Sine12bit1[Idx] << 16) + (Sine12bit2[Idx]);
	}
	DAC1_DMA_Config();
}

void DAC1_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(DAC_DMA_CLK, ENABLE);
	DMA_InitStructure.DMA_Channel = DAC_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(DAC->DHR12R1);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&DualSine12bit ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = 200;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DAC_DMA_STREAM, &DMA_InitStructure);
	DMA_Cmd(DAC_DMA_STREAM, ENABLE);
}

void DAC2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	
	RCC_AHB1PeriphClockCmd(DAC_CH1_GPIO_CLK|DAC_CH2_GPIO_CLK, ENABLE);
	
	RCC_APB1PeriphClockCmd(DAC_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = DAC_CH1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(DAC_CH1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DAC_CH2_GPIO_PIN;
	GPIO_Init(DAC_CH2_GPIO_PORT, &GPIO_InitStructure);

	DAC_InitStructure.DAC_Trigger = DAC_TRIGGER;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;
	DAC_Init(DAC_CH1_CHANNEL, &DAC_InitStructure);
	
	DAC_Init(DAC_CH2_CHANNEL, &DAC_InitStructure);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_Cmd(DAC_Channel_2, ENABLE);
	
	DAC_DMACmd(DAC_Channel_1, ENABLE);
}

void DAC2_TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(DAC_TIM_CLK, ENABLE);

	// 1M
	TIM_TimeBaseStructure.TIM_Period = 83;
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(DAC_TIM, &TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(DAC_TIM, TIM_TRGOSource_Update);
	
	TIM_Cmd(DAC_TIM, ENABLE);
}

void DAC2_Mode_Init(void)
{
	uint32_t Idx = 0;
	DAC_Config();
	DAC_TIM_Config();
	for (Idx = 0; Idx < 200; Idx++) {
		DualSine12bit[Idx] = (Sine12bit1[Idx] << 16) + (Sine12bit2[Idx]);
	}
	DAC_DMA_Config();
}

void DAC2_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(DAC_DMA_CLK, ENABLE);
	DMA_InitStructure.DMA_Channel = DAC_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12RD_Address;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&DualSine12bit ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = 200;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DAC_DMA_STREAM, &DMA_InitStructure);
	DMA_Cmd(DAC_DMA_STREAM, ENABLE);
}
*/
/*
void MyDAC_Init(void)
{
    // DA PC0~PD9 PD14~15 PB0~1
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = (0xc7ff << 0); // Initialize PC0~PD10 PD14~15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = (0x3 << 0);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// 电压 -1.8 ~ 1.8
void DAC_Set_Volt(float volt_v)
{
	u16 volt;
	if(volt_v<-1.8)
	{
		volt_v = -1.8;
	} 
	else if (volt_v>1.8)
	{
		volt_v = 1.8;
	}
	if(volt_v>=0)
	{
		volt = (u16)(volt_v/(float)1.8*(float)8191.0);
	}
	else 
	{
		volt = (u16)((volt_v+(float)(1.8))/(float)1.8*(float)8191.0+(float)8192.0);
	}
    DACCLK = 1;
	delay_us(2);
    //for (int i = 0; i < 100; i++);
    DAC13 = (volt & 0x2000) >> 13;
    DAC12 = (volt & (0x2000 >> 1)) >> 12;
    DAC11 = (volt & (0x2000 >> 2)) >> 11;
    DAC10 = (volt & (0x2000 >> 3)) >> 10;
    DAC9 = (volt & (0x2000 >> 4)) >> 9;
    DAC8 = (volt & (0x2000 >> 5)) >> 8;
    DAC7 = (volt & (0x2000 >> 6)) >> 7;
    DAC6 = (volt & (0x2000 >> 7)) >> 6;
    DAC5 = (volt & (0x2000 >> 8)) >> 5;
    DAC4 = (volt & (0x2000 >> 9)) >> 4;
    DAC3 = (volt & (0x2000 >> 10)) >> 3;
    DAC2 = (volt & (0x2000 >> 11)) >> 2;
    meDAC1 = (volt & (0x2000 >> 12)) >> 1;
    DAC0 = (volt & (0x2000 >> 13));
	delay_us(2);
    DACCLK = 0;
    //for (int i = 0; i < 100; i++);
}
*/
