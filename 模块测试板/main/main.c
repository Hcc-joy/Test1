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
  delay_init(32);//32Mϵͳʱ��
  LED_Init(); 
  Relay_Init();	
  TM7707_Init();
  ADC_Config();
    while(1)
    {

		
    }
}


/// �ض���c�⺯��printf��USART2
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART2 */
	
	//  RS485_TX_EN();//����Ϊ����ģʽ
		USART_SendData(USART2, (uint8_t) ch);
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		
		return (ch);
}

/// �ض���c�⺯��scanf��USART1
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART2);
}

