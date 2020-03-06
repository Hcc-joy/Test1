#include "stm32l1xx.h"
#include "stm32l1xx_tim.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "TM7707.h"

int main(void)
{ 
  TIME_Init();
  TIM3_Init();
  delay_init(32);//32M系统时钟
  LED_Init(); 
  Relay_Init();	
  TM7707_Init();
  ADC_Config();
    while(1)
    {

		
    }
}


/// 重定向c库函数printf到USART2
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART2 */
	
	//  RS485_TX_EN();//设置为发送模式
		USART_SendData(USART2, (uint8_t) ch);
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		
		return (ch);
}

/// 重定向c库函数scanf到USART1
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART2);
}

