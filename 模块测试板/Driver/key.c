/*
 * key.c
 *
 *  Created on: 2019Äê8ÔÂ1ÈÕ
 *      Author: Hcc
 */


#include "key.h"
/*
PA0  adress 1
PA8  adress 2
PA11 adress 2
PA12 adress 4
PA15 adress 5
PC13 adress 6
PC14 adress 7
PC15 adress 8

 */
void AddressKey_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

}
/* */
static GPIO_TypeDef * Port[8]=
{ GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,GPIOC,GPIOC,GPIOC,
};
static uint16_t Pin[8]=
{
 GPIO_Pin_0,GPIO_Pin_8,GPIO_Pin_11,GPIO_Pin_12,GPIO_Pin_15, GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15
};

u8  GetNodeAddress(void)
{  int i;
   u8 NodeAddData=0x00;
  for(i=0;i<8;i++)
  {
    if(GPIO_ReadInputDataBit(Port[i],Pin[i])==RESET)//
    {
      NodeAddData|=(1<<i);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    }
  }
  return NodeAddData;
}
/*       */
void SetKey_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*    */
 void SetKeyStroke(void)
 {
  


 }
