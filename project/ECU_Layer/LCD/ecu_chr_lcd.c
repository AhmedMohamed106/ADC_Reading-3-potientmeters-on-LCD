
/* 
 * File:   ecu_chr_lcd.c
 * Author: Ahmed Mohamed
 *
 * Created on 03 dec 2023, 01:24 ?
 */

 /*Section : Includes */

#include "ecu_chr_lcd.h"

static Std_ReturnType send_4bits (const lcd_chr_4bit_t * _lcd , uint8 _command_data);
static Std_ReturnType send_4bit_enable_signal(const lcd_chr_4bit_t * _4bit_lcd);
static Std_ReturnType send_8bit_enable_signal(const lcd_chr_8bit_t * _8bit_lcd);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_chr_4bit_t * _lcd , uint8 row , uint8 column);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_chr_8bit_t * _lcd , uint8 row , uint8 column);


Std_ReturnType lcd_4bit_initialize(const lcd_chr_4bit_t * _lcd){
    Std_ReturnType ret = E_OK;
    if(NULL == _lcd)
    {  
        ret = E_NOT_OK;  
    } 
    else
    {
        ret = gpio_pin_intialize(&(_lcd->lcd_rs));
        ret = gpio_pin_intialize(&(_lcd->lcd_enable));
        uint8 i;  
        for (i = 0; i < 4; i++) {   
            ret = gpio_pin_intialize(&(_lcd->lcd_data[i]));
        }
        
        __delay_ms(20);
        ret = lcd_4bit_send_command(_lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
         ret = lcd_4bit_send_command(_lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(150);
        ret = lcd_4bit_send_command(_lcd , _LCD_8BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(_lcd , _LCD_CLEAR);
        ret = lcd_4bit_send_command(_lcd , _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(_lcd , _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(_lcd , _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(_lcd , _LCD_4BIT_MODE_2_LINE);
        
        
        
    }
}

Std_ReturnType lcd_4bit_send_command(const lcd_chr_4bit_t * _lcd , uint8 _command){

    Std_ReturnType ret = E_OK;
    if(NULL == _lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs) , GPIO_LOW);
        ret = send_4bits( _lcd , (_command >>4)); 
        ret = send_4bit_enable_signal(_lcd);
        ret = send_4bits(_lcd , _command);
        ret = send_4bit_enable_signal(_lcd);
    }
}
Std_ReturnType lcd_4bit_send_data(const lcd_chr_4bit_t * _lcd , uint8 _data){

    Std_ReturnType ret = E_OK;    
    if(NULL == _lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs) , GPIO_HIGH);
        ret = send_4bits( _lcd , (_data >>4)); 
        ret = send_4bit_enable_signal(_lcd);
        ret = send_4bits(_lcd , _data);
        ret = send_4bit_enable_signal(_lcd);
    }
    
    return ret;
}

Std_ReturnType lcd_4bit_send_data_pos(const lcd_chr_4bit_t * _lcd ,uint8 row, uint8 column, uint8 _data){

    Std_ReturnType ret = E_OK;
    
    if(NULL == _lcd)
    { 
        ret = E_NOT_OK;
    }
    
    else
    {
        ret  = lcd_4bit_set_cursor(_lcd , row , column);
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs) , GPIO_HIGH);
        ret = send_4bits(_lcd , (_data>>4));
        ret = send_4bit_enable_signal(_lcd);
        ret = send_4bits(_lcd , _data);
    
    }
    
        return ret;


    
}
Std_ReturnType lcd_4bit_send_string(const lcd_chr_4bit_t * _lcd , uint8 * _str){

    Std_ReturnType ret = E_OK;
    uint8 l_str_counter = 0;
    
    if(NULL == _lcd && NULL == _str)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        while(* _str)
        {
            ret = lcd_4bit_send_data(_lcd , * _str++);

        }
    
    }
    return ret;



}
Std_ReturnType lcd_4bit_send_string_pos(const lcd_chr_4bit_t * _lcd , uint8 row, uint8 column, uint8 * _str){

    Std_ReturnType ret = E_OK;
    
    if(NULL == _lcd && NULL == _str)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
       ret = lcd_4bit_set_cursor(_lcd , row , column);
       ret = lcd_4bit_send_string(_lcd , _str);
    
    }



}
Std_ReturnType lcd_4bit_send_custom_char(const lcd_chr_4bit_t * _lcd , uint8 row, uint8 column , const uint8 _chr[] , uint8 mem_pos){

    Std_ReturnType ret = E_OK;
    
    if(NULL == _lcd)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
    
    }

    
    return ret;


}

Std_ReturnType lcd_8bit_initialize(const lcd_chr_8bit_t * _lcd){

    Std_ReturnType ret = E_OK;
    
    if(NULL == _lcd)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        ret = gpio_pin_intialize(&(_lcd->lcd_rs));
        ret = gpio_pin_intialize(&(_lcd->lcd_enable));
        uint8 i;
        for (i = 0; i < 8; i++) {
            
            ret = gpio_pin_intialize(&(_lcd->lcd_data[i]));      
        }
        
         __delay_ms(20);
        ret = lcd_8bit_send_command(_lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(_lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(_lcd , _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(_lcd ,_LCD_CLEAR);
        ret = lcd_8bit_send_command(_lcd , _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(_lcd , _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(_lcd , _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(_lcd , _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(_lcd , 0x80);
        
    }
}
Std_ReturnType lcd_8bit_send_command(const lcd_chr_8bit_t * _lcd , uint8 _command){

 Std_ReturnType ret = E_OK;
    
    if(NULL == _lcd)
    {   
        ret = E_NOT_OK; 
    }
    
    else
    {
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs) , GPIO_LOW);
        uint8 l_pin_counter = 0;
        for (l_pin_counter = 0; l_pin_counter < 8; ++l_pin_counter)
        {
            ret = gpio_pin_write_logic(&(_lcd->lcd_data[l_pin_counter]) , ((_command >> l_pin_counter ) & (uint8)0x01));
        }
        ret = send_8bit_enable_signal(_lcd);
    }
}
Std_ReturnType lcd_8bit_send_data(const lcd_chr_8bit_t * _lcd , uint8 _data){
 
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = 0;
    if(NULL == _lcd)
    { 
        ret = E_NOT_OK;
    }
    
    else
    {
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs) , GPIO_HIGH);
        
        for (l_pin_counter = 0; l_pin_counter < 8; ++l_pin_counter)
        {
            ret = gpio_pin_write_logic(&(_lcd->lcd_data[l_pin_counter]) , (_data >> l_pin_counter ) & (uint8)0x01);
        }     
        ret = send_8bit_enable_signal(_lcd);
    }

  }
Std_ReturnType lcd_8bit_send_data_pos(const lcd_chr_8bit_t * _lcd ,uint8 row, uint8 column, uint8 _data){

    Std_ReturnType ret = E_OK;
    
    if(NULL == _lcd)
    { 
        ret = E_NOT_OK;
    }
    
    else
    {
        ret = lcd_8bit_set_cursor(_lcd , row , column);
        ret = lcd_8bit_send_data(_lcd , _data);
    }
    
    

}
Std_ReturnType lcd_8bit_send_string(const lcd_chr_8bit_t * _lcd , uint8 * _str){

 Std_ReturnType ret = E_OK;
    
    if(NULL == _lcd && NULL == _str)
    { 
        ret = E_NOT_OK;
    }
    
    else
    {        
        
        while(* _str)
        {            
         ret = lcd_8bit_send_data(_lcd , * _str++);
        }
    }
 
     return ret; 
}
Std_ReturnType lcd_8bit_send_string_pos(const lcd_chr_8bit_t * _lcd , uint8 row, uint8 column, uint8 * _str){

Std_ReturnType ret = E_OK;
    
    if(NULL == _lcd && NULL == _str)
    { 
        ret = E_NOT_OK;
    }
    
    else
    {        

        ret = lcd_8bit_set_cursor(_lcd , row , column);    
        ret = lcd_8bit_send_string(_lcd , _str);
      
    }
 
     return ret; 

}
Std_ReturnType lcd_8bit_send_custom_char(const lcd_chr_8bit_t * _lcd , uint8 row, uint8 column , const uint8 _chr[] , uint8 mem_pos){

    Std_ReturnType ret = E_OK;
    return ret;
}



Std_ReturnType byte_to_string(uint8 value , uint8 *str){

    Std_ReturnType ret = E_OK;
    
    if(NULL == str)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
    
        memset(str , '\0' , 4);
        sprintf(str ,"%i" , value);
        
    
    }
      return ret;

}
Std_ReturnType short_to_string(uint16 value , uint8 *str){

      Std_ReturnType ret = E_OK;
    
    if(NULL == str)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
    
         memset(str , '\0' , 6);
        sprintf(str ,"%i" , value);
        
    
    }
        return ret;
}
Std_ReturnType int_to_string(uint32 value , uint8 *str){

  Std_ReturnType ret = E_OK;
    
    if(NULL == str)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
    
          memset(str , '\0' , 11);
        sprintf(str ,"%i" , value);
    
    }
  return ret;


}



// helper functions 
static Std_ReturnType send_4bits (const lcd_chr_4bit_t * _lcd , uint8 _command_data){

    Std_ReturnType ret = E_OK;
    
    
    ret = gpio_pin_write_logic(&(_lcd->lcd_data[0]) , ((_command_data >> 0) & (uint8)0x01)); 
    ret = gpio_pin_write_logic(&(_lcd->lcd_data[1]) , ((_command_data >> 1) & (uint8)0x01)); 
    ret = gpio_pin_write_logic(&(_lcd->lcd_data[2]) , ((_command_data >> 2) & (uint8)0x01)); 
    ret = gpio_pin_write_logic(&(_lcd->lcd_data[3]) , ((_command_data >> 3) & (uint8)0x01)); 
   
    return ret;

}
static Std_ReturnType send_4bit_enable_signal(const lcd_chr_4bit_t * _4bit_lcd){

    Std_ReturnType ret = E_OK;    
    ret  = gpio_pin_write_logic(&(_4bit_lcd->lcd_enable) , GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(_4bit_lcd->lcd_enable) , GPIO_LOW);
    
    return ret;
}
static Std_ReturnType send_8bit_enable_signal(const lcd_chr_8bit_t * _8bit_lcd){

    Std_ReturnType ret = E_OK;    
    ret  = gpio_pin_write_logic(&(_8bit_lcd->lcd_enable) , GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(_8bit_lcd->lcd_enable) , GPIO_LOW);

    return ret;
} 
static Std_ReturnType lcd_4bit_set_cursor(const lcd_chr_4bit_t * _lcd , uint8 row , uint8 column){


    Std_ReturnType ret = E_OK;
    
    column--;
    switch(row){
        case ROW1: ret = lcd_4bit_send_command(_lcd , (0x80 + column));
        break;
        case ROW2: ret = lcd_4bit_send_command(_lcd , (0xc0 + column));
        break; 
        case ROW3: ret = lcd_4bit_send_command(_lcd , (0x94 + column));
        break; 
        case ROW4: ret = lcd_4bit_send_command(_lcd , (0xd4 + column));
        break;
        default: ;

    }
    
    return ret;

}
static Std_ReturnType lcd_8bit_set_cursor(const lcd_chr_8bit_t * _lcd , uint8 row , uint8 column){

    Std_ReturnType ret = E_OK;
    
    column--;
    switch(row){
        case ROW1: ret = lcd_8bit_send_command(_lcd , (0x80 + column));
        break;
        case ROW2: ret = lcd_8bit_send_command(_lcd , (0xc0 + column));
        break; 
        case ROW3: ret = lcd_8bit_send_command(_lcd , (0x94 + column));
        break; 
        case ROW4: ret = lcd_8bit_send_command(_lcd , (0xd4 + column));
        break;
        default: ;

    }
    
    return ret;

}

