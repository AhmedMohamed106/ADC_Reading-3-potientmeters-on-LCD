/* 
 * File:   ecu_relay.h
 * Author: Ahmed Mohamed
 *
 * Created on 04 sept 2023, 05:21 ?
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section : Includes */
#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section: Macro Declarations */

#define RELAY_ON_STATUS 0x01
#define RELAY_OFF_STATUS 0x00

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

typedef struct {

    uint8 relay_port     :4;
    uint8 relay_pin      :3;
    uint8 relay_status   :1;



}relay_t;



/* Section: Function Declarations */





#endif	/* ECU_RELAY_H */
Std_ReturnType relay_initialize(relay_t *const relay);
Std_ReturnType relay_turn_on(relay_t *const relay);
Std_ReturnType relay_turn_off(relay_t *const relay);