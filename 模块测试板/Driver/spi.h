/*
 * spi.h
 *
 *  Created on: 2019Äê7ÔÂ24ÈÕ
 *      Author: Hcc
 */

#include "sys.h"
#include "stm32l1xx.h"

void SPI2_Init(void);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
u8 SPI2_ReadWriteByte(u8 TxData);
