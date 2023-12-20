#include "ecu_dc_motor.h"

/**
 * @brief Initialize dc motor .
 * @param dc_motor : pointer to the dc motor module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */

static pin_config_t motor_pin1;
static pin_config_t motor_pin2;

Std_ReturnType dc_motor_initialize(const dc_motor_t* dc_motor){
    
    Std_ReturnType ret = E_OK;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        
        motor_pin1.port = dc_motor->dc_motor[dc_motor1].dc_motor_port;
        motor_pin1.pin = dc_motor->dc_motor[dc_motor1].dc_motor_pin;
        motor_pin1.logic = dc_motor->dc_motor[dc_motor1].dc_motor_status;
        motor_pin1.direction = GPIO_DIRECTION_OUTPUT;
                                  
        motor_pin2.port = dc_motor->dc_motor[dc_motor2].dc_motor_port;
        motor_pin2.pin = dc_motor->dc_motor[dc_motor2].dc_motor_pin;
        motor_pin2.logic = dc_motor->dc_motor[dc_motor2].dc_motor_status;
        motor_pin2.direction = GPIO_DIRECTION_OUTPUT;
                                
    
        gpio_pin_intialize(&motor_pin1);
        gpio_pin_intialize(&motor_pin2);
    }
    
    return ret;
}




/**
 * @brief move the dc motor right .
 * @param dc_motor : pointer to the dc motor module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */


Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }

    else
    {

        gpio_pin_write_logic(&motor_pin1, GPIO_HIGH);
        gpio_pin_write_logic(&motor_pin2,  GPIO_LOW);
    }
    
return ret;
   
}



/**
 * @brief move the dc motor left .
 * @param dc_motor : pointer to the dc motor module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */


Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor){
    
    Std_ReturnType ret = E_OK;
        if(NULL == dc_motor)
        {
            ret = E_NOT_OK;
        }

        else
        {

            gpio_pin_write_logic(&motor_pin1, GPIO_LOW);
            gpio_pin_write_logic(&motor_pin2, GPIO_HIGH);

        }

    return ret;
        
    }


/**
 * @brief stop the dc motor .
 * @param dC_motor : pointer to the dc motor module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */

Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor){
    
Std_ReturnType ret = E_OK;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    
    else
    {


            gpio_pin_write_logic(&motor_pin1, GPIO_LOW);
            gpio_pin_write_logic(&motor_pin2, GPIO_LOW);

    }
    
    return ret;
    
}