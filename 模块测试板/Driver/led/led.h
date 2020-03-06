#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "general_type.h"
#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"


#define ErrorLedOn()      GPIO_SetBits(GPIOB, GPIO_Pin_3); GPIO_ResetBits(GPIOB, GPIO_Pin_4|GPIO_Pin_5)
#define ErrorLedOff()     GPIO_ResetBits(GPIOB, GPIO_Pin_3) 
#define WarningLedOn()    GPIO_SetBits(GPIOB, GPIO_Pin_4); GPIO_ResetBits(GPIOB, GPIO_Pin_3|GPIO_Pin_5) 
#define WarningLedoff()   GPIO_ResetBits(GPIOB, GPIO_Pin_4)
#define NormalLedOn()     GPIO_SetBits(GPIOB, GPIO_Pin_5); GPIO_ResetBits(GPIOB, GPIO_Pin_4|GPIO_Pin_3)  
#define NormalLedOff()    GPIO_ResetBits(GPIOB, GPIO_Pin_5) 

#define MotoTest()        GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)

void LED_Init(void);//
void LedShow(u8 Data);//
void MotoTest_Init(void) ;
#endif  

















