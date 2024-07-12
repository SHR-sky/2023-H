#include "Serial.h"
#include "stdio.h"
#include "stdarg.h"

void Serial_Init(void)
{

	// USART2_TX PA2 USART2_RX PD3
	// USART2_CTS PD3 USART2_RTS PD4

	/*open the clock*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	/* define the struct */
	GPIO_InitTypeDef GPIO_InitStruct;

	/* 三、配置结构体 */
	
	// TX
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	// GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	/* 四、调用初始化函数，写入寄存器 */
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// RX
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStruct);


	// 发送STM32数据

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStruct);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);

	USART_Cmd(USART2, ENABLE);

	// USART3
	// ---------------------------------------------------------------------------
	// 接收ESP32数据
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE); // 使能DMA传输
	// USART3_TX   GPIOB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// USART3_RX	  GPIOB.11初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// 配置波特率
	USART_InitStructure.USART_BaudRate = 115200;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(USART3, &USART_InitStructure);
	// 使能串口接收中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART3, ENABLE);
	// 清除发送完成标志
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0X06;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0X00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART2, Byte);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t length)
{
	for (int i = 0; i < length; i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	for (int i = 0; String[i] != '\0'; i++)
	{
		Serial_SendByte(String[i]);
	}
}

int pow10[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

void Serial_SendNumber(uint32_t Number, uint8_t length)
{
	for (int i = 0; i < length; i++)
	{
		Serial_SendByte(Number / pow10[length - i - 1] + '0');
		Number = Number - Number / pow10[length - i - 1] * pow10[length - i - 1];
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

uint8_t Serial_LookUpData(void)
{
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)
		return USART_ReceiveData(USART2);
	return 0;
}

extern uint8_t flag;
extern uint8_t mode_flag;
extern int change_phi;

short Res;
void USART2_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)
	{
		Res = USART_ReceiveData(USART2);
		if(Res==0x1)
		{
			flag = 1;
		}
		else 
		{
			mode_flag = 1;
			if(Res == 0x2)
			{
				change_phi += 3;
			}
			else if(Res == 0x3)
			{
				change_phi -= 3;
			}
			else if(Res == 0x4)
			{
				change_phi += 1;
			}
			else
			{
				change_phi -= 1;
			}
		}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		// Write you code
	}
}

void Serial_End(void)
{
	Serial_SendByte(0xff);
	Serial_SendByte(0xff);
	Serial_SendByte(0xff);
}

// 中断发送串口数据
