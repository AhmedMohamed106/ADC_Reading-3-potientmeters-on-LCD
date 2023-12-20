
#include "ecu_seven_seg.h"



    
Std_ReturnType seven_segment_initialize(const segment_t *seg)
{
    Std_ReturnType ret = E_OK;
    if(NULL == seg)
    {
        ret = E_NOT_OK; 
    }
    
    else
        
    {
        
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN3])); 
    
    
    }
    



}
Std_ReturnType seven_segment_write_number(const segment_t *seg , uint8 number)
{
    Std_ReturnType ret = E_OK;
    if((NULL == seg) && (number > 9))
    {
        ret = E_NOT_OK; 
    }
    
    else
        
    {
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]),number & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]),(number >> 1) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]),(number >> 2) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]),(number >> 3) & 0x01);


    }




}