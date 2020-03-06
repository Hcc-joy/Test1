/*
 * rs485.h
 *
 *  Created on: 2019年8月1日
 *      Author: Hcc
 */

#ifndef DRIVER_RS485_H_
#define DRIVER_RS485_H_
#include "sys.h"

#define B_USART2_LEN 50
#define DMA_USART2_Channel      DMA1_Channel6
#define C_Lenth_UART2_RX		 200
/*功能码定义 */
#define UP_FH           0xF5
#define Down_FH         0x5F

#define FrameBit        0
#define SUM_HBit        FrameBit+1
#define SUM_LBit        SUM_HBit+1
#define NodeaddressBit  SUM_LBit+1
#define DataLengthBit   NodeaddressBit+1
#define FuncBit         DataLengthBit+1
#define DataComBit      FuncBit+1
#define AvgCurrentCnt  20 //取平均电流次数
#define ShortCircuitCurrent 1000//1.0A

typedef enum
{
	CmdPwoer = 0x63,
	CmdGainCurrent=0x05,
	CmdModulePwoer = 0x73,
	CmdInSleep = 0xB3,
	CmdCheckVersions = 0x68,
	CmdModuleWake = 0x71
}Cmd;
typedef struct nData
{
	u8 FH_AckFlg : 1;
	u8 FRxFinishFlg : 1;
	u8 WakeUpACKFlg : 1;
	u8 PowrUpACKFlg : 1;
	u8 DsthSleepFlg : 1;
	u8 CheckVersionsFlg : 1;
	u8 KeyGpioCheckFlg : 1;
	u8 : 1;
} nData;

void USART2_Init(void);
void RxDataBuff(u8 byte);
void UART_DMA_Config(void);	//UART_RX相应的DMA配置
void ParseRxData(u8 *pData);
u8 CheckData(u8 *pData);
void DataComparisonFun(void);
#endif /* DRIVER_RS485_H_ */

