/*
 * Adc.c
 *
 *  Created on: 2019Äê8ÔÂ16ÈÕ
 *      Author: Hcc
 */

#include "Adc.h"


void ADC_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable the GPIOF or GPIOA Clock */
	  /* Enable The HSI (16Mhz) */
  RCC_HSICmd(ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* Configure PF.11 (ADC Channel11) or PA.05 (ADC Channe5) in analog mode */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Check that HSI oscillator is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
   /* ADCs DeInit */  
  ADC_DeInit(ADC1);
    /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  /* ADC1 Configuration ------------------------------------------------------*/
  
  /* Enable ADC1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel5 or channel1 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_192Cycles);

  /* Define delay between ADC1 conversions */
  ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);
  
  /* Enable ADC1 Power Down during Delay */
  ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
	MySand();
}
u16 ADC_read(void)
{
  u16 g_aAdValue[5];
  u8 i;
  u16 ret;
  u16 max_id,min_id,max_value,min_value;
 
  for(i=0;i<5;i++)
  {
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
     {;}      //Wait the ADRDY flag 
		ADC_SoftwareStartConv(ADC1);                            //ADC1 regular Software Start Conv 
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		{;}   // Test EOC flag 
    g_aAdValue[i]=ADC_GetConversionValue(ADC1);             // Get ADC1 converted data  
  }
  ret=0;
  for(i=1;i<5;i++)
	ret+=g_aAdValue[i];
  ret/=4;
  max_id=1;
  min_id=1;
  max_value=0;
  min_value=0;
  for(i=1;i<5;i++)
  {
    if(g_aAdValue[i]>ret)
    {
      if(g_aAdValue[i]-ret>max_value)
        {
          max_value=g_aAdValue[i]-ret;
          max_id=i;
        }
    }
    else 
     {
       if(ret-g_aAdValue[i]>min_value)
         {
           min_value=ret-g_aAdValue[i];
           min_id=i;
         }
     }
  }
  ret=0;
 for(i=1;i<5;i++)
   {
     if((i!=min_id)&&(i!=max_id))
        ret+=g_aAdValue[i];
   }
  if(min_id!=max_id)
		ret/=2;
  else ret/=3;
 return ret;
    
}      
u32 next;	
int MySand(void)
    {
	  u16 seed;
		int i;
  for(i=0;i<5;i++)
    {
    seed=ADC_read();
    next=next+seed;
		delay_ms(1);
    }
    return next;
    }
int Myrand(void)
{ 
  unsigned long result;
  next *= 1103515245;
  next += 12345;
  result = (unsigned long ) (next / 65536) % 2048;
  return result;
	
}





