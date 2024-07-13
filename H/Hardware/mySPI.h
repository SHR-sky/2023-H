#ifndef __MYSPI_H
#define __MYSPI_H

#include "sys.h"

void SPI2_Init(void);
uint8_t SPI2_ReadWriteByte(uint8_t TxData);

#endif
