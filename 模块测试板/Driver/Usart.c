/*
 * Usart.c
 *
 *  Created on: 2019年9月16日
 *      Author: Hcc
 */
#include "Usart.h"
#define DSTH_Lenth_UART1_RX  200
u8 DSTH_BufferInterl_UART2_RX[200];
u8 DSTH_Buffer_UART_RX[200];

//u8 DSTH_UART_RxLen;
//u8 b_Mark_USART2_RX;

void DSTH_Usart_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);    
   
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART2);	 
		
	 USART_InitStructure.USART_BaudRate = 115200; 
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	 USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	 USART_InitStructure.USART_Parity = USART_Parity_No; 
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	  
     USART_ClearITPendingBit(USART1,USART_IT_RXNE); 
	
	 USART_Init(USART1, &USART_InitStructure);
	 USART_Cmd(USART1, ENABLE);
			
	DSTH_UART_DMA_Config();
	

}
void DSTH_UART_DMA_Config(void)	//UART_RX相应的DMA配置
{
  DMA_InitTypeDef DMA_InitStructure;
	/*开启DMA时钟*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向，从外设读取发送到内存
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有
	
	DMA_DeInit(DMA1_Channel5);   //将DMA的通道6寄存器重设为缺省值  串口1对应的是DMA通道5
	DMA_InitStructure.DMA_BufferSize = 200;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART1->DR;  //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)DSTH_Buffer_UART_RX;  //DMA内存基地址
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道
	DMA_Cmd(DMA1_Channel5, ENABLE);  //正式驱动DMA传输	
	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);   //关闭接收中断
	USART_ClearITPendingBit(USART1, USART_IT_IDLE|USART_IT_RXNE);    //清除空闲中断标志 
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);   //开启空闲中断
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);   //使能串口2 DMA接收



}
u8 DSTH_UartNormalFlg=0;
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  
	{
		u16 len=0;
		USART_ClearITPendingBit(USART1, USART_IT_IDLE);         //清除中断标志
		USART_ReceiveData(USART1);//读取数据 注意：这句必须要，否则不能够清除中断标志位。
		//len = C_Lenth_UART2_RX-DMA_GetCurrDataCounter(DMA_USART2_Channel); //算出接本帧数据长度
		 len = DSTH_Lenth_UART1_RX-DMA1_Channel5->CNDTR;//算出接本帧数据长度
      memcpy(DSTH_BufferInterl_UART2_RX, DSTH_Buffer_UART_RX,len);
		/*恢复DMA指针，等待下一次的接收*/
		//DMA_Cmd(DMA_USART2_Channel, DISABLE );
		DMA1_Channel5->CCR &= (u16)(~DMA_CCR1_EN);
		DMA1_Channel5->CNDTR = DSTH_Lenth_UART1_RX; 
		DMA1_Channel5->CCR |= DMA_CCR1_EN;
    DSTH_UartNormalFlg=SET;//串口确认OK
		//DMA_Cmd(DMA_USART2_Channel, ENABLE);

	}  											 
} 
//门锁发送指令进入测试模式

void Send_DataTO_DSTH(u8* buf, u8 len)
{
	u8 t;
	for (t = 0; t < len; t++)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
		USART_SendData(USART1, buf[t]); 
	}
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //		
	
}

