/* 
 * File:   ecu_dc_motor.h
 * Author: Ahmed Mohamed
 *
 * Created on 21 sept 2023, 02:58 ?
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section : Includes */

#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define DC_MOTOR_ON_STATUS  0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define dc_motor1 0x00U
#define dc_motor2 0x01U

/* Section: Macro Functions Declarations */
 
/* Section: Data Type Declarations */

typedef struct {

    uint8 dc_motor_port   :4;
    uint8 dc_motor_pin    :3;
    uint8 dc_motor_status :1;
    
}dc_motor_pin_t; 


typedef struct {

    dc_motor_pin_t dc_motor[2];
    
}dc_motor_t; 
/* Section: Function Declarations */


Std_ReturnType dc_motor_initialize(const dc_motor_t* dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor);

#endif	/* ECU_DC_MOTOR_H */

