/*
 * eeprom.c
 *
 *  Created on: 2019年8月8日
 *      Author: Hcc
 */

#include "eeprom.h"



/*------------------------------------------------------------
 Func: EEPROM数据按字节读出
 Note:
-------------------------------------------------------------*/
void EEPROM_ReadBytes(u16 Addr,u8 *Buffer,u16 Length)
{
	u8 *wAddr;
	wAddr=(u8 *)(EEPROM_BASE_ADDR+Addr);
	while(Length--){
		*Buffer++=*wAddr++;
	}
}


/*------------------------------------------------------------
 Func: EEPROM数据读出
 Note:
-------------------------------------------------------------*/
void EEPROM_ReadWords(u16 Addr,u16 *Buffer,u16 Length)
{
	u32 *wAddr;
	wAddr=(u32 *)(EEPROM_BASE_ADDR+Addr);
	while(Length--){
		*Buffer++=*wAddr++;
	}
}

/*------------------------------------------------------------
 Func: EEPROM数据按字节写入
 Note:
-------------------------------------------------------------*/
void EEPROM_WriteBytes(u16 Addr,u8 *Buffer,u16 Length)
{
	u8 *wAddr;
	u8 temp;
	wAddr=(u8 *)(EEPROM_BASE_ADDR+Addr);
	DIS_INT
	FLASH->PEKEYR=PEKEY1;				//unlock
	FLASH->PEKEYR=PEKEY2;
	while(FLASH->PECR&FLASH_PECR_PELOCK);
	FLASH->PECR|=FLASH_PECR_FTDW;		//not fast write
	while(Length--)
		{
			
		temp=*Buffer++;
		if(temp!=0x00)
		{
		*wAddr++=temp;
		while(FLASH->SR&FLASH_SR_BSY);
		}
		else
		{
		  ++wAddr;
	    //while(FLASH->SR&FLASH_SR_BSY);
		}
	}
	FLASH->PECR|=FLASH_PECR_PELOCK;
	EN_INT
}

/*------------------------------------------------------------
 Func: EEPROM数据按字写入
 Note: 字当半字用
-------------------------------------------------------------*/
void EEPROM_WriteWords(u16 Addr,u16 *Buffer,u16 Length)
{
	u32 *wAddr;
	
	wAddr=(u32 *)(EEPROM_BASE_ADDR+Addr);
	DIS_INT
	FLASH->PEKEYR=PEKEY1;				//unlock
	FLASH->PEKEYR=PEKEY2;
	while(FLASH->PECR&FLASH_PECR_PELOCK);
	FLASH->PECR|=FLASH_PECR_FTDW;		//not fast write
	while(Length--){
		*wAddr++=*Buffer++;
		while(FLASH->SR&FLASH_SR_BSY);
	}
	FLASH->PECR|=FLASH_PECR_PELOCK;
	EN_INT
}
