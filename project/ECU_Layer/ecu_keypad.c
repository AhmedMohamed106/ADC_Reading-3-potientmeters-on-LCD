

#include "Keypad/ecu_keypad.h"


static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = {{'7','8','9','/'},
                                                              {'4','5','6','*'},
                                                              {'1','2','3','-'},
                                                              {' ','0','=','+'}};



Std_ReturnType keypad_initialize (const keypad_t *keypad){

    
    Std_ReturnType ret = E_OK;
    
    uint8 rows_counter = 0 , columns_counter = 0;
    
    if(NULL == keypad)
    {
        ret = E_NOT_OK; 
    }
    
    else
    {
    
        for (rows_counter = 0; rows_counter < KEYPAD_ROWS; rows_counter++) {
     
            ret = gpio_pin_intialize(&(keypad->keypad_row_pins[KEYPAD_ROWS]));

        }
        
        for (columns_counter = 0; columns_counter < KEYPAD_COLUMNS; columns_counter++) {
     
            ret = gpio_pin_direction_intialize(&(keypad->keypad_columns_pins[KEYPAD_COLUMNS]));

        }

    }
    
    return ret;
        
}
Std_ReturnType keypad_get_value (const keypad_t *keypad , uint8 *value){

    Std_ReturnType ret = E_OK;
    if(NULL == keypad)
    {
        ret = E_NOT_OK; 
    }
    
    else
    {
    
    
         
    }
      

    return ret; 

}


