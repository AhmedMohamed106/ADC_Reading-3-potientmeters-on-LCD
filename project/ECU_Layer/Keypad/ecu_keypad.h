/* 
 * File:   ecu_keypad.h
 * Author: hfcs
 *
 * Created on 19 ??????, 2023, 08:47 ?
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

 /*Section : Includes */

#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define KEYPAD_ROWS     4
#define KEYPAD_COLUMNS  4
/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

typedef struct
{

    pin_config_t keypad_row_pins[KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[KEYPAD_COLUMNS];

}keypad_t;

/* Section: Function Declarations */

Std_ReturnType keypad_initialize (const keypad_t *keypad);
Std_ReturnType keypad_get_value (const keypad_t *keypad , uint8 *value);


#endif	/* ECU_KEYPAD_H */

