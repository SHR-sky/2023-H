#include "Delay.h"
u8 per_us;				//每1us定时器节拍
u32 per_ms;	

static u8  fac_us=0;		   
static u16 fac_ms=0;
void delay_init(u8 SYSCLK)
{
  SysTick->CTRL&=~(1<<2);
  fac_us=SYSCLK/8;
  fac_ms=((u32)SYSCLK*1000)/8;
}

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void delay_us(uint32_t xus)
{
  u32 temp;	    	 
  SysTick->LOAD=xus*fac_us;  		 
  SysTick->VAL=0x00;
  SysTick->CTRL=0x01 ;	 
  do
  {
    temp=SysTick->CTRL;
  }while((temp&0x01)&&!(temp&(1<<16)));
  SysTick->CTRL=0x00;
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void delay_ms(uint32_t xms)
{
	while(xms--)
	{
		delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void delay_s(uint32_t xs)
{
	while(xs--)
	{
		delay_ms(1000);
	}
} 
