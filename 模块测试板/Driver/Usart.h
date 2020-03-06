/*
 * Usart.h
 *
 *  Created on: 2019Äê9ÔÂ16ÈÕ
 *      Author: Hcc
 */

#ifndef DRIVER_USART_H_
#define DRIVER_USART_H_

#include "sys.h"


void Send_DataTO_DSTH(u8* buf, u8 len);
void DSTH_Usart_Init(void);
void DSTH_UART_DMA_Config(void);
void  DSTH_InTest_Mode(void);

#endif /* DRIVER_USART_H_ */
