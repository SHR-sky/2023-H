#ifndef _SERIAL__H_
#define _SERIAL__H_

#include "stdio.h"
#include "sys.h"

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendNumber(uint32_t Number, uint8_t length);
void Serial_SendString(char *String);
void Serial_SendArray(uint8_t *Array, uint16_t length);
void Serial_Printf(char *format, ...);
void Serial_End(void);
uint8_t Serial_LookUpData(void);

#endif
