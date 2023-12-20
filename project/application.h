/* 
 * File:   application.h
 * Author: Ahmed Mohamed
 * Created on November 28, 2023, 9:53 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */

#include "ECU_Layer/ecu_layer_initialize.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "ECU_Layer/LCD/ecu_chr_lcd.h"
/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
extern lcd_chr_8bit_t _lcd2;
extern lcd_chr_4bit_t _lcd1;
/* Section: Function Declarations */

void application_intialize(void);

#define _XTAL_FREQ 8000000UL

#endif	/* APPLICATION_H */

