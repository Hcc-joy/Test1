#include "led.h"
#include "general_type.h"
void MotoTest_Init(void); //电机测试，测试在工作状态内是否有高电平
void LED_Init(void)
{
    
  GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6|GPIO_Pin_7;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //GPIO_SetBits(GPIOB,GPIO_Pin_6);  	
  // MotoTest_Init(); 	     	
}

void MotoTest_Init(void) //电机测试，测试在工作状态内是否有高电平
{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    EXTI_InitTypeDef EXTI_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;

//    //初始化PA0管脚
//    /* Enable GPIOA clock */
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_7;

//    /* Enable SYSCFG clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
//    /* Connect EXTI0 Line to PA0 pin */
//    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource7);

//    /* Configure EXTI0 line */
//    EXTI_InitStructure.EXTI_Line = EXTI_Line7;//中断线7
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//外部中断
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);//初始化

//    /* Enable and set EXTI0 Interrupt to the lowest priority */
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0类型
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
}
//extern u8 MotoStartIOFlg;
//u8 a2[1]={0x02};
//void EXTI9_5_IRQHandler(void)
//{
//  if(EXTI_GetITStatus(EXTI_Line7) != RESET) 
//  {
//    EXTI_ClearITPendingBit(EXTI_Line7);   
//			MotoStartIOFlg=SET;
//      RS485_Send_Data(a2,1);//test
//  }  
//}

void LedShow(u8 Data)
{


}




