/*
 * rs485.c
 *
 *  Created on: 2019年8月1日
 *      Author: Hcc
 */

#include "USART2.h"


u8 AckFremaData[10]={0x5F,0x00,0x00,0x00,0x02,0x06,0x00};
u8 RS485_RX_CNT=0;
u8 RS485_RX_BUF[64];  	//接收缓冲,最大64个字节.
u8 AB_BufferInterl_UART2_RX[C_Lenth_UART2_RX];
u8 AB_Buffer_UART2_RX[C_Lenth_UART2_RX];
u8 B_UART2_RxLen;
u8 b_Mark_USART2_RX;

void USART2_Init(void)
{  

  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	
	/* Configure USART2 Rx (PA.03) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	/* Configure USART2 Tx (PA.02) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);    
   
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);	 
		
	USART_InitStructure.USART_BaudRate = 115200; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	  
   
	USART_Init(USART2, &USART_InitStructure);
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	
	USART_Cmd(USART2, ENABLE);   
	UART_DMA_Config();
}
void UART_DMA_Config(void)	//UART_RXÏàÓ¦µÄDMAÅäÖÃ
{
	DMA_InitTypeDef DMA_InitStructure;
	/*¿ªÆôDMAÊ±ÖÓ*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //Êý¾Ý´«Êä·½Ïò£¬´ÓÍâÉè¶ÁÈ¡·¢ËÍµ½ÄÚ´æ
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //ÍâÉèµØÖ·¼Ä´æÆ÷²»±ä
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //ÄÚ´æµØÖ·¼Ä´æÆ÷µÝÔö
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //Êý¾Ý¿í¶ÈÎª8Î»
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //Êý¾Ý¿í¶ÈÎª8Î»
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //¹¤×÷ÔÚÕý³£»º´æÄ£Ê½
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAÍ¨µÀ xÓµÓÐÖÐÓÅÏÈ¼¶ 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAÍ¨µÀxÃ»ÓÐ
	
	DMA_DeInit(DMA1_Channel6);   //½«DMAµÄÍ¨µÀ6¼Ä´æÆ÷ÖØÉèÎªÈ±Ê¡Öµ  ´®¿Ú1¶ÔÓ¦µÄÊÇDMAÍ¨µÀ5
	DMA_InitStructure.DMA_BufferSize = C_Lenth_UART2_RX;  //DMAÍ¨µÀµÄDMA»º´æµÄ´óÐ¡
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;  //DMAÍâÉèADC»ùµØÖ·
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)AB_Buffer_UART2_RX;  //DMAÄÚ´æ»ùµØÖ·
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);  //¸ù¾ÝDMA_InitStructÖÐÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯DMAµÄÍ¨µÀ
	DMA_Cmd(DMA1_Channel6, ENABLE);  //ÕýÊ½Çý¶¯DMA´«Êä	
		
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);   //¹Ø±Õ½ÓÊÕÖÐ¶Ï
	USART_ClearITPendingBit(USART2, USART_IT_IDLE|USART_IT_RXNE);    //Çå³ý¿ÕÏÐÖÐ¶Ï±êÖ¾ 
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);   //¿ªÆô¿ÕÏÐÖÐ¶Ï
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);   //Ê¹ÄÜ´®¿Ú2 DMA½ÓÊÕ
	
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)  
	{
		u16 len=0;
		USART_ClearITPendingBit(USART2, USART_IT_IDLE);         //Çå³ýÖÐ¶Ï±êÖ¾
		USART_ReceiveData(USART2);//¶ÁÈ¡Êý¾Ý ×¢Òâ£ºÕâ¾ä±ØÐëÒª£¬·ñÔò²»ÄÜ¹»Çå³ýÖÐ¶Ï±êÖ¾Î»¡£
		//len = C_Lenth_UART2_RX-DMA_GetCurrDataCounter(DMA_USART2_Channel); //Ëã³ö½Ó±¾Ö¡Êý¾Ý³¤¶È
		len = C_Lenth_UART2_RX-DMA_USART2_Channel->CNDTR;//Ëã³ö½Ó±¾Ö¡Êý¾Ý³¤¶È
		B_UART2_RxLen=len;

		/*»Ö¸´DMAÖ¸Õë£¬µÈ´ýÏÂÒ»´ÎµÄ½ÓÊÕ*/
		//DMA_Cmd(DMA_USART2_Channel, DISABLE );
		DMA_USART2_Channel->CCR &= (u16)(~DMA_CCR1_EN);
		DMA_USART2_Channel->CNDTR = C_Lenth_UART2_RX; 
		DMA_USART2_Channel->CCR |= DMA_CCR1_EN;
		//DMA_Cmd(DMA_USART2_Channel, ENABLE);
		
	}  											 
} 

u8 CheckData(u8 *pData)
{
	u16 Sum = 0;
	u16 TempSum;
	int i;
	if (*pData != 0xF5|| *pData != 0xA5)
		return 0;
     TempSum = (*(pData + 2)<<8);
	 TempSum |= *(pData + 1);
	
	for (i = 4; i < 4 + *(pData + 3); i++)
	{
		Sum = Sum + *(pData + i);
	}
	if (TempSum == Sum)
	{
		return 1;
	}

	return 0;

}
void ParseRxData(u8 *Data)
{
	if(CheckData(Data)!= SET)
		return;
	switch (*(Data+4))
	{
	case CmdModulePwoer:
		break;
	case CmdInSleep:
		break;
	case CmdGainCurrent:
		break;
	case CmdModuleWake:
		break;

	default:
		break;
	}
}





u8 PrintfCurrentFlg;
void DataComparisonFun(void)
{ 
  int i,j=0;
	u8 versions_i[10]={0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x73};//versions

	for(i=0,j=0;i<8;i++)
	{
		if(AB_Buffer_UART2_RX[i] == versions_i[i])
		{
		 j++;
		}
	}
	if(j==8)
	{
		//delay_ms(10);
		printf(" KDS_DAQ-Current V1.01.003 ");

	}
}
