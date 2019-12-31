#ifndef __SYS_H
#define __SYS_H	 
#include "stm32l1xx.h"
#include "general_type.h"
#include "stm32l1xx_tim.h"
#include "stm32l1xx_spi.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_usart.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_adc.h"
#include "stm32l1xx_adc.h"
#include "stm32l1xx_iwdg.h"
#include "stm32l1xx_wwdg.h"
#include "stm32l1xx_dma.h"
#include "stm32l1xx_adc.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_syscfg.h"
#include "misc.h"
#include "TM7707.h"
#include "led.h"
#include "delay.h"
#include "USART2.h"
#include "relay.h"
#include "key.h"
#include "eeprom.h"
#include "TIM.h"
#include "Adc.h"
//#include "WDG.h"
#include <string.h>
#include <stdio.h>
#include <Usart.h>

//JTAG模式设置定义
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	

/////////////////////////////////////////////////////////////////  
void TIME_Init(void);
void Sys_Soft_Reset(void);      //系统软复位
void Sys_Standby(void);         //待机模式 	
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//设置偏移地址
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);//设置NVIC分组
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//设置中断
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);//外部中断配置函数(只对GPIOA~G)
void JTAG_Set(u8 mode);
//////////////////////////////////////////////////////////////////////////////
//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址



#endif











