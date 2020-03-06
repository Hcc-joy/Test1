/*
 * spi.h
 *
 *  Created on: 2019��7��24��
 *      Author: Hcc
 */

#include "sys.h"
#include "stm32l1xx.h"

void SPI2_Init(void);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
u8 SPI2_ReadWriteByte(u8 TxData);
