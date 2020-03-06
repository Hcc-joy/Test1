/*
 * relay.h
 *
 *  Created on: 2019Äê8ÔÂ8ÈÕ
 *      Author: Hcc
 */
#include "sys.h"


#ifndef DRIVER_RELAY_H_
#define DRIVER_RELAY_H_

#define DTSH_UART_On()   GPIO_ResetBits(GPIOB, GPIO_Pin_1) 
#define DTSH_UART_Off()  GPIO_SetBits(GPIOB, GPIO_Pin_1)  
#define DTSH_Power_On()  GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define DTSH_Power_Off()  GPIO_SetBits(GPIOB,GPIO_Pin_2)


void  Relay_Init(void);
#endif /* DRIVER_RELAY_H_ */
