


#include "ecu_relay.h"


/**
 * @brief Initialize relay .
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */

Std_ReturnType relay_initialize(relay_t *const relay){
    
    Std_ReturnType ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , 
        .direction = GPIO_DIRECTION_OUTPUT ,.logic = relay->relay_status};
        
        
        gpio_pin_intialize(&pin_obj);
        
        ret = E_OK;
    }
    
    
    return ret;




}



/**
 * @brief turn the relay on.
 * @param relay : pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_on(relay_t *const relay){
 Std_ReturnType ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , 
        .direction = GPIO_DIRECTION_OUTPUT ,.logic = relay->relay_status};
        
        
        gpio_pin_write_logic (&pin_obj ,GPIO_HIGH);
        
        ret = E_OK;
    }

 return ret;


}


/**
 * @brief turn the relay off.
 * @param relay : pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_off(relay_t *const relay){

 Std_ReturnType ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , 
        .direction = GPIO_DIRECTION_OUTPUT ,.logic = relay->relay_status};
        
        
        gpio_pin_write_logic (&pin_obj ,GPIO_LOW);
        
        ret = E_OK;
    }



 return ret;

}