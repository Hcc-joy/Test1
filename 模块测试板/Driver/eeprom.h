/*
 * eeprom.h
 *
 *  Created on: 2019?8?8?
 *      Author: Hcc
 */

#ifndef DRIVER_EEPROM_H_
#define DRIVER_EEPROM_H_

#include "sys.h"
#define EEPROM_BASE_ADDR	0x08080000	//
#define EEPROM_BYTE_SIZE	0x0FFF//

#define PEKEY1	0x89ABCDEF		//FLASH_PEKEYR
#define PEKEY2	0x02030405		//FLASH_PEKEYR

#define EN_INT      	__enable_irq();		//???????
#define DIS_INT     	__disable_irq();	//???????
#define TimeSetAddress     0
#define TimeSetDataLength  13

#define StartRunTimeAddress 13
#define StartRunTimeDataLength 10
void EEPROM_ReadBytes(u16 Addr,u8 *Buffer,u16 Length);
void EEPROM_ReadWords(u16 Addr,u16 *Buffer,u16 Length);
void EEPROM_WriteBytes(u16 Addr,u8 *Buffer,u16 Length);
void EEPROM_WriteWords(u16 Addr,u16 *Buffer,u16 Length);
#endif /* DRIVER_EEPROM_H_ */
