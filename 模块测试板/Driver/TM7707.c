/*
 * TM7707.c
 *
 *  Created on: 2019年7月25日
 *      Author: Hcc
 */

#include "sys.h"
#include "spi.h"
#include "stm32l1xx_spi.h"
#include "TM7707.h"
#include "misc.h"

#define TM7707_SCLK_Enable() GPIO_SetBits(GPIOB,GPIO_Pin_13);  
#define TM7707_SCLK_Disable() GPIO_ResetBits(GPIOB,GPIO_Pin_13);  

//#define TM7707_CS_Enable() GPIO_SetBits(GPIOB,GPIO_Pin_12);  
//#define TM7707_CS_Disable() GPIO_ResetBits(GPIOB,GPIO_Pin_12); 
#define TM7707_MISO_H()  GPIO_SetBits(GPIOB,GPIO_Pin_14);  
#define TM7707_MISO_L()  GPIO_ResetBits(GPIOB,GPIO_Pin_14);  

#define TM7707_MOSI() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);  
//Simple delay function
void TM7707_Delay(uint16_t nCount)
{
	uint16_t	i;
	for(i=0; i<nCount; i++)
	{
		__ASM("nop");
	}
}
void TM7707_Dedy(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 	     	
}
void TM7707_GPIOInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	  //GPIOB13,14,15初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PB3~5复用功能输出	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	  //GPIOB13,14,15初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PB3~5复用功能输出	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
	//cs PB 12
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  
}

u8 TM7707ReadBtye(void)
{
 u8  i,dat2=0;
  TM7707_CS_ENABLE();
	TM7707_SCLK_Enable();
	for(i=0;i<8;i++)
	{
	TM7707_SCLK_Disable();
	delay_us(1);
	dat2=(dat2<<1)|TM7707_MOSI();	// 
	delay_us(1);
	TM7707_SCLK_Enable();
  delay_us(1);
	}
	TM7707_SCLK_Enable();
	TM7707_CS_DISABLE();
   return dat2;

}


void TM7707WriteByte( u8 dat1)
{
 u8 i;
 TM7707_CS_ENABLE();
 TM7707_SCLK_Enable();
	for(i=0;i<8;i++)
	{
	TM7707_SCLK_Disable();
	delay_us(1);
   if(dat1&0x80) 
	 {
		 TM7707_MISO_H();	
	 }
   else 
		{			
		 TM7707_MISO_L();
		}
		delay_us(1);
		TM7707_SCLK_Enable();
		delay_us(1);
		dat1<<=1;
	}
	TM7707_SCLK_Enable();
	TM7707_MISO_H();
	TM7707_CS_DISABLE();

}


/* TM7707初始化
 *
 *
 * */
void TM7707_Init(void)
{
  SPI2_Init();
	TM7707_Dedy();
	// Synchronize device clock.
	TM7707_SynchronizeDeviceClock();
	TM7707_TransferByte(REG_CLOCK | WRITE | CH_1); // Write communication register to set clook register.
	TM7707_TransferByte(CLKDIS_0 | CLK_4_9152M | FS_500HZ); // External clock, frequency is 4.9152 MHz and the sampling frequency is 500Hz.
	TM7707_TransferByte(REG_CLOCK | WRITE | CH_2); // Write communication register to set clook register.
	TM7707_TransferByte(CLKDIS_0 | CLK_4_9152M | FS_500HZ); // External clock, frequency is 4.9152 MHz and the sampling frequency is 500Hz.
	TM7707_SelfCalibration(CH_2, GAIN_1);//

}
/////////////////////////////////

/************************************************************************/
/* Function Name:	TM7707_SelfCalibration.								*/
/* Purpose:			Internal channel self-calibration.					*/
/* Resources:		SPI controler and GPIOs.							*/
/* Params:																*/
/*	@uiChannelIndex:	Channel index.									*/
/* Return:			None.												*/
/* Limitation:		None.												*/
/************************************************************************/
void TM7707_SelfCalibration(uint8_t	uiChannelIndex, uint8_t uiGain)
{
	uiChannelIndex = uiChannelIndex % CH_MAX;
	//Write communication register to set setup register.
	TM7707_TransferByte(REG_SETUP | WRITE | uiChannelIndex);
	//Write configuration register, start self-calibration.
	TM7707_TransferByte(MD_CAL_SELF | uiGain | UNIPOLAR | BUF_NO | FSYNC_0);
	// Wait for operation to complete(ablut 180ms).
	TM7707_WaitForDRDY();
}
extern int Time_OutCnt;
void TM7707_WaitForDRDY(void)
{
	Time_OutCnt=5;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)!= 0)
	{
	if(Time_OutCnt==0)
	{
	 break;
	}
	}
}

/************************************************************************/
/* Function Name:	TM7707_SynchronizeDeviceClock.						*/
/* Purpose:			Synchronize TM7707 device clock, keep SCLK pin high	*/
/*					at least 32 cycles.									*/
/* Resources:		SPI controler and GPIOs.							*/
/* Params:			None.												*/
/* Return:			None.												*/
/* Limitation:		None.												*/
/************************************************************************/
void TM7707_SynchronizeDeviceClock(void)
{
	uint8_t i;
	// Keep SCLK pin high at 40 cycles.
	for(i=0; i<5; i++)
	{
		TM7707_TransferByte(0xFF);
	}
}
/*读取TM7707 24位AD值 */
uint32_t TM7707_ReadADCValue(uint8_t uiChannelIndex)
{
uint32_t rtnADValue = 0;
	u32 min=0xFFFFFFFF,max=0;
	uint32_t Sum[20];
	u32 Sum1;
	int i;
	for(i=0;i<7;i++)
	{
	rtnADValue = 0;
	GPIO_SetBits(GPIOB,GPIO_Pin_11);  
	TM7707_TransferByte(REG_DATA | READ | uiChannelIndex);
	TM7707_WaitForDRDY();
	rtnADValue |= TM7707_TransferByte(0xFF);
	rtnADValue <<= 8;
  rtnADValue |= TM7707_TransferByte(0xFF);
	rtnADValue <<= 8;
	rtnADValue |= TM7707_TransferByte(0xFF);
	Sum[i]=rtnADValue;
	}
	for(i=0;i<7;i++)
	{
	 if(min>Sum[i])
	 {
	 min=Sum[i];
	 }
	 if(max<Sum[i])
	 {
	 max=Sum[i];
	 }
	 Sum1=Sum1+Sum[i];
	}
	rtnADValue=(Sum1-max-min)/5;
	return rtnADValue;
}

uint8_t TM7707_TransferByte(uint8_t uiTxData)
{
	uint8_t uiRxData;
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);  	
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2, uiTxData);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);  
	uiRxData = SPI_I2S_ReceiveData(SPI2);
	return uiRxData;
}

