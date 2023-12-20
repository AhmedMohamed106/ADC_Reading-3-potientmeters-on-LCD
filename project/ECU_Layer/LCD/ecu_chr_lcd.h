/* 
 * File:   ecu_chr_lcd.h
 * Author: Ahmed Mohamed
 *
 * Created on 03 dec 2023, 01:24 ?
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

 /*Section : Includes */
#include "ecu_chr_lcd_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define _4bit_mode        0x00
#define _8bit_mode        0x01  
#define _XTAL_FREQ 8000000UL
#define   bit_mode       _8bit_mode
          
#define _LCD_CLEAR                      0X01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE                 0X06
#define _LCD_CURSOR_OFF_DISPLAY_ON      0X0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF     0x08
#define _LCD_CURSOR_ON_BLINK_ON         0x0F
#define _LCD_CURSOR_ON_BLINK_OFF        0x0E
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define _LCD_DISPLAY_SHIFT_LEFT         0x18
#define _LCD_8BIT_MODE_2_LINE           0x38
#define _LCD_4BIT_MODE_2_LINE           0x28
#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_START                0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4


/* Section: Macro Functions Declarations */


/* Section: Data Type Declarations */

typedef struct {

    pin_config_t lcd_rs;
    pin_config_t lcd_enable;
    pin_config_t lcd_data[4];
    
      
}lcd_chr_4bit_t;



typedef struct {

    pin_config_t lcd_rs;
    pin_config_t lcd_enable;
    pin_config_t lcd_data[8];
    
      
}lcd_chr_8bit_t;


/* Section: Function Declarations */

//#if bit_mode == _4bit_mode
Std_ReturnType lcd_4bit_initialize(const lcd_chr_4bit_t * _lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_chr_4bit_t * _lcd , uint8 _command);
Std_ReturnType lcd_4bit_send_data(const lcd_chr_4bit_t * _lcd , uint8 _data);
Std_ReturnType lcd_4bit_send_data_pos(const lcd_chr_4bit_t * _lcd ,uint8 row, uint8 column, uint8 _data);
Std_ReturnType lcd_4bit_send_string(const lcd_chr_4bit_t * _lcd , uint8 * _str);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_chr_4bit_t * _lcd , uint8 row, uint8 column, uint8 * _str);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_chr_4bit_t * _lcd , uint8 row, uint8 column , const uint8 _chr[] , uint8 mem_pos);
//#endif

//#if bit_mode == _8bit_mode
Std_ReturnType lcd_8bit_initialize(const lcd_chr_8bit_t * _lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_chr_8bit_t * _lcd , uint8 _command);
Std_ReturnType lcd_8bit_send_data(const lcd_chr_8bit_t * _lcd , uint8 _data);
Std_ReturnType lcd_8bit_send_data_pos(const lcd_chr_8bit_t * _lcd ,uint8 row, uint8 column, uint8 _data);
Std_ReturnType lcd_8bit_send_string(const lcd_chr_8bit_t * _lcd , uint8 * _str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_chr_8bit_t * _lcd , uint8 row, uint8 column, uint8 * _str);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_chr_8bit_t * _lcd , uint8 row, uint8 column , const uint8 _chr[] , uint8 mem_pos);
//#endif

Std_ReturnType byte_to_string(uint8 value , uint8 *str);
Std_ReturnType short_to_string(uint16 value , uint8 *str);
Std_ReturnType int_to_string(uint32 value , uint8 *str);

#endif	/* ECU_CHR_LCD_H */

