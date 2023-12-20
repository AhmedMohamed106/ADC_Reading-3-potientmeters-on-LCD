/* 
 * File:   hal_eeprom.h
 * Author: Ahmed Mohamed
 *
 * Created on 16 dec 2023, 05:01 ?
 */

#include "hal_eeprom.h"

/**
 * 
 * @param _read_Add
 * @param _data
 * @return 
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 _read_Add , uint8 * _data){

    Std_ReturnType ret = E_OK;
    if(NULL == _data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Write the address (10)bits to the EEADR and EEADRH*/
        EEADRH = ((_read_Add>>8) &(0x03));
        EEADR  = ((_read_Add) &(0xFF));
        /*this macro will clear EEPGD bit  : Access data EEPROM memory*/
        EEPPROM_EEPGD_BitClear();
        /*this macro will clear CFGS bit  : Access Flash program or data EEPROM memory */
        EEPPROM_CFGS_BitClear();
        /*this macro Initiates an EEPROM read */
        EEPROM_Data_ReadControlInit();
        /*Wait for two NOP : Required for latency at high frequencies*/
        NOP();
        NOP();
        /*return data*/
        *_data = EEDATA;
        ret = E_OK;
    }

    return ret;
}

/**
 * 
 * @param _Write_Add
 * @param _data
 * @return 
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 _Write_Add , uint8 _data ){
         Std_ReturnType ret = E_NOT_OK;
         uint8 Interrupt_state = INTCONbits.GIE;       
        /*Write the address (10)bits to the EEADR and EEADRH*/
        EEADRH = (uint8)((_Write_Add>>8) & (0x03));
        EEADR  = (uint8)((_Write_Add) & (0xFF));
        /*Write the data We want in EEDATA register*/
        EEDATA = _data;
        /*this macro will clear EEPGD bit  : Access data EEPROM memory*/
        EEPPROM_EEPGD_BitClear();
        /*this macro will clear CFGS bit  : Access Flash program or data EEPROM memory */
        EEPPROM_CFGS_BitClear();
        /*this macro Allows write cycles to Flash program/data EEPROM*/
        EEPROM_Data_WriteEnable();
        /*this macro will disable all global interrupts (bit number 7 in INTCON register) */
        INTERRUPT_GlobalInterruptDisable();
        /*write sequence 55h to EECON2 and write 0AAh to EECON2*/
        EECON2 = 0x55;
        EECON2 = 0xAA;
        /* this macro Initiates a data EEPROM erase/write cycle or a program memory erase cycle or write cycle*/
         EEPROM_Data_WriteControlInit();
         /**/
        while(EECON1bits.WR == 1);
        /*this macro Inhibits write cycles to Flash program/data EEPROM*/
        EEPROM_Data_WriteDisable();
        /*this macro will disable all global interrupts (bit number 7 in INTCON register) */
        INTCONbits.GIE = Interrupt_state;
        ret = E_OK;

return ret;          
}

