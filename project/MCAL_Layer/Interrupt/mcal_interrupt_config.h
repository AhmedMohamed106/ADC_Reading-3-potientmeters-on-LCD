/* 
 * File:   mcal_interrupt_config.h
 * Author: Ahmed mohamed
 *
 * Created on 09 dec 2023, 04:22 ?
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H
 
/* Section : Includes */
#include <xc.h>
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* Section: Macro Declarations */

#define ZERO_INIT          0
#define ONE_INIT           1

#define INTERRUPT_ENABLE            ONE_INIT
#define INTERRUPT_DISABLE           ZERO_INIT
#define INTERRUPT_OCCUR             ONE_INIT
#define INTERRUPT_NOT_OCCUR         ZERO_INIT
#define INTERRUPT_PRIORITY_ENABLE   ONE_INIT
#define INTERRUPT_PRIORITY_DISABLE  ZERO_INIT


/* Section: Macro Functions Declarations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/*this macro will enable priority levels on interrupts in RCON register*/
#define INTERRUPT_PriorityLevelsEnable()        (RCONbits.IPEN = 1)
/*this macro will disable priority levels on interrupts in RCON register*/
#define INTERRUPT_PriorityLevelsDisable()        (RCONbits.IPEN = 0)
/*this macro will enable High priority global interrupts (bit number 7 in INTCON register)*/
#define INTERRUPT_globalInterruptHighEnable()  (INTCONbits.GIEH = 1)
/*this macro will disable High priority global interrupts (bit number 7 in INTCON register)*/
#define INTERRUPT_globalInterruptHighDisable() (INTCONbits.GIEH = 0)
/*this macro will enable Low priority global interrupts (bit number 6 in INTCON register)*/
#define INTERRUPT_globalInterruptLowEnable()   (INTCONbits.GIEL = 1)
/*this macro will disable Low priority global interrupts (bit number 6 in INTCON register)*/
#define INTERRUPT_globalInterruptLowDisable()   (INTCONbits.GIEL = 0)

#elif INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE

/*this macro will enable all global interrupts (bit number 7 in INTCON register) */
#define INTERRUPT_GlobalInterruptEnable()   (INTCONbits.GIE = 1)
/*this macro will disable all global interrupts (bit number 7 in INTCON register) */
#define INTERRUPT_GlobalInterruptDisable()  (INTCONbits.GIE = 0)
/*this macro will enable all Peripheral interrupts (bit number 6 in INTCON register) */
#define INTERRUPT_PeripheralsInterruptEnable() (INTCONbits.PEIE = 1)
/*this macro will disable all Peripheral interrupts (bit number 6 in INTCON register) */
#define INTERRUPT_PeripheralsInterruptDisable() (INTCONbits.PEIE = 0)
#endif

/* Section: Data Type Declarations */

typedef enum{

    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY 
            
}Interrupt_priority_cfg; 

/* Section: Function Declarations */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

