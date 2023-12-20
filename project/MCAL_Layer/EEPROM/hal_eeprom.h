/* 
 * File:   hal_eeprom.h
 * Author: Ahmed Mohamed
 *
 * Created on 16 dec 2023, 05:01 ?
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H


/* Section: Macro Declarations */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_external_interrupt.h"


/* Section: Macro Functions Declarations */

/*this macro will clear CFGS bit  : Access Flash program or data EEPROM memory */
#define EEPPROM_CFGS_BitClear()  (EECON1bits.CFGS =0)
/*this macro will clear EEPGD bit  : Access data EEPROM memory*/
#define EEPPROM_EEPGD_BitClear() (EECON1bits.EEPGD = 0)
/*this macro Allows write cycles to Flash program/data EEPROM*/
#define EEPROM_Data_WriteEnable() (EECON1bits.WREN = 1)
/*this macro Inhibits write cycles to Flash program/data EEPROM*/
#define EEPROM_Data_WriteDisable() (EECON1bits.WREN = 0)
/* this macro Initiates a data EEPROM erase/write cycle or a program memory erase cycle or write cycle*/
#define EEPROM_Data_WriteControlInit() (EECON1bits.WR = 1)
/*this macro Initiates an EEPROM read */
#define EEPROM_Data_ReadControlInit() (EECON1bits.RD = 1)

/* Section: Data Type Declarations */

/* Section: Function Declarations */

/**
 * 
 * @param _read_Add
 * @param _data
 * @return 
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 _read_Add , uint8 * _data);

/**
 * 
 * @param _Write_Add
 * @param _data
 * @return 
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 _Write_Add , uint8 _data );


#endif	/* HAL_EEPROM_H */

