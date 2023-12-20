/* 
 * File:   application.c
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on November 28, 2020, 8:43 PM
 */

#include "application.h"




void ADC_DefaultInterruptHandler(void);

lcd_chr_4bit_t lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_enable.port = PORTC_INDEX,
    .lcd_enable.pin = GPIO_PIN1,
    .lcd_enable.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_enable.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW
};

adc_config_t adc_1 = {
    .ADC_InterruptHandler = ADC_DefaultInterruptHandler,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .format_select = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_REFERENCE_VOLTAGE_DISABLE
};

uint16 adc_res_1 = 0, adc_res_2 = 0, adc_res_3 = 0, adc_res_4 = 0;
uint8 adc_res_1_txt[6], adc_res_2_txt[6], adc_res_3_txt[6], adc_res_4_txt[6];
uint8 ADC_Req = 0;

int main() { 
    Std_ReturnType ret = E_NOT_OK;
    
    application_intialize();
    
    ret = ADC_Init(&adc_1);
    ret = lcd_4bit_initialize(&lcd_1);
    
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 7, "ADC Test");
    __delay_ms(2000);
    ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Pot0: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "Pot1: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "Pot2: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 4, 1, "Pot3: ");
    
    while(1){
        if(0 == ADC_Req){
            ret = ADC_GetConversion_Interrupt(&adc_1, ADC_CHANNEL_AN0);
        }
        else if(1 == ADC_Req){
            ret = ADC_GetConversion_Interrupt(&adc_1, ADC_CHANNEL_AN1);
        }
        else if(2 == ADC_Req){
            ret = ADC_GetConversion_Interrupt(&adc_1, ADC_CHANNEL_AN2);
        }
        else if(3 == ADC_Req){
            ret = ADC_GetConversion_Interrupt(&adc_1, ADC_CHANNEL_AN3);
        }
        else { /* Nothing */ }
        
        ret = short_to_string(adc_res_1, adc_res_1_txt);
        ret = short_to_string(adc_res_2, adc_res_2_txt);
        ret = short_to_string(adc_res_3, adc_res_3_txt);
        ret = short_to_string(adc_res_4, adc_res_4_txt);
        
        ret = lcd_4bit_send_string_pos(&lcd_1, 1, 7, adc_res_1_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 2, 7, adc_res_2_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 3, 7, adc_res_3_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 4, 7, adc_res_4_txt);
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();
}

void ADC_DefaultInterruptHandler(void){
    Std_ReturnType ret = E_NOT_OK;
    if(0 == ADC_Req){
        ret = ADC_GetConversionResult(&adc_1, &adc_res_1);
        ADC_Req = 1;
    }
    else if(1 == ADC_Req){
        ret = ADC_GetConversionResult(&adc_1, &adc_res_2);
        ADC_Req = 2;
    }
    else if(2 == ADC_Req){
        ret = ADC_GetConversionResult(&adc_1, &adc_res_3);
        ADC_Req = 3;
    }
    else if(3 == ADC_Req){
        ret = ADC_GetConversionResult(&adc_1, &adc_res_4);
        ADC_Req = 0;
    }
    else { /* Nothing */ }
}

