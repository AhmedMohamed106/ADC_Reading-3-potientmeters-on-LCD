/* 
 * File:   hal_adc.c
 * Author: Ahmed Moohamed
 *
 * Created on 17 dec 2023, 05:47 ?
 */
#include "hal_adc.h"

#if ADC_INTERRUPT_STATUS == ADC_INTERRUPT_FEATURE_ENABLE
static void (*Interrupt_handler)(void) = NULL; 
#endif
static inline void adc_input_channel_port_configure(const adc_channel_Select_t _channel);
static inline void adc_select_format_configure(const adc_config_t * _adc);
static inline void adc_voltage_reference_configure(const adc_config_t * _adc);
static Std_ReturnType ADC_Interrupt_Handler(void (*ADC_Handler)(void));
static Std_ReturnType ADC_SetInterrupt_Handler(const adc_config_t *_adc);

/**
 * @Summary       Initialize the ADC
 * @Description   This routine Initialize the ADC
 *                This routine must be called before any other routine is called
 *                This routine should be only called once during system initialization
 * @Preconditions None
 * @param _adc  Pointer to the ADC configuration   
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_config_t *_adc){

    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    { ret = E_NOT_OK;}
    else
    {
        /*Disable the ADC*/
        ADC_ConverterDisable();
        /*Configure the acquisition time*/
        ADC_ACQT_Reg = _adc->acquisition_time;
        /*configure the conversion clock*/
        ADC_ADCS_Reg = _adc->conversion_clock;
        /*configure the default channel*/
        ADC_CHS_Reg = _adc->adc_channel;  
        adc_input_channel_port_configure(_adc->adc_channel);
        /*configure the interrupt*/
#if ADC_INTERRUPT_STATUS == ADC_INTERRUPT_FEATURE_ENABLE
        
        ADC_InterruptEnable();
        ADC_InterruptClearFlag();
        /*configure interrupt priority*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        
        if(INTERRUPT_HIGH_PRIORITY == _adc->priority){
            /*High global interrupt enable*/
            INTERRUPT_globalInterruptHighEnable();
            ADC_HighPriorityEnable();
        }
        else if (INTERRUPT_LOW_PRIORITY == _adc->priority) {
              /*Low global interrupt enable*/
            INTERRUPT_globalInterruptLowEnable();
            ADC_LowPriorityEnable();
        }
        else {/*Nothing*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        //INTCONbits.GIE = 1;
        //INTCONbits.PEIE = 1;
        INTERRUPT_PeripheralsInterruptEnable();        
#endif        
        /*Initialize callback mechanism*/
        //ret = ADC_SetInterrupt_Handler(_adc);
        Interrupt_handler = _adc->ADC_InterruptHandler;
        
#endif        
        /*configure the result format*/
        adc_select_format_configure(_adc);
        /*configure the voltage reference*/
        adc_voltage_reference_configure(_adc);        
        /*Enable the ADC*/
        ADC_ConverterEnable();
        ret = E_OK;
    }

    return ret;
}

/**
 * @Summary       DeInitialize the ADC
 * @Description   This routine DeInitializes the ADC
 *                This routine is called when we wanted to reset the ADC
 *                This routine could be called any time we want to reset the ADC
 * @Preconditions None
 * @param _adc  Pointer to the ADC configuration   
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const adc_config_t *_adc){

    Std_ReturnType ret = E_OK;
    if(NULL == _adc)
    { ret = E_NOT_OK;}
    else
    {
     ADC_ConverterDisable(); 
     /*Disable the interrupt*/
    #if ADC_INTERRUPT_STATUS == ADC_INTERRUPT_FEATURE_ENABLE
     ADC_InterruptDisable();
    #endif
     ret = E_OK;
    
    }
    return ret;
}
/**
 * @Summary       Allows selection of a channel for conversion
 * @Description   This routine is used to select desired channel for conversion  
 * @Preconditions ADC_Init() must be called before this function calling 
 * @param _adc  Pointer to the ADC configuration   
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_SelectChannel(const adc_config_t *_adc , adc_channel_Select_t _channel){

    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    { ret = E_NOT_OK;}
    else
    {
         /* Configure the default channel */
        ADC_CHS_Reg = _channel;  
        adc_input_channel_port_configure(_channel); 
        ret = E_OK;
    }

    return ret;
}
/**
 * @Summary       It starts the conversion A/D process
 * @Description   This routine is used to conversion in desired channel   
 * @Preconditions ADC_Init() must be called before this function calling 
 * @param _adc  Pointer to the ADC configuration   
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_StartConversion(const adc_config_t *_adc){

    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    { ret = E_NOT_OK;}
    else
    {
       ADC_ConvertInPrgress(); 
       ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @return 
 */

/**
 * @Summary      Returns True when the conversion is done otherwise False 
 * @Description   This routine is used to check for conversion complete   
 * @Preconditions ADC_Init() must be called before this function calling 
 *                ADC_StartConversion() must be called before this function calling 
 * @param _adc  Pointer to the ADC configuration
 * @param Conversion_status pointer to the status result of conversion 
 *           True is the conversion is complete
 *           False if not completed
 * @return Status of the function
 *              (E_OK) : The function done successfully
 *              (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc , uint8 *Conversion_status){

    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == Conversion_status))
    { ret = E_NOT_OK;}
    else
    {
        if(0 == ADC_ConvertStatus())
        {*Conversion_status  = 1;}
        else 
        {*Conversion_status = 0;}
        ret = E_OK;
    
    }
    return ret;
}

/**
 * @Summary      Returns the A/D result (converted Digital result )  
 * @Description   This routine is used to get the conversion result   
 * @Preconditions ADC_Init() must be called before this function calling 
 *                ADC_StartConversion() must be called before this function calling 
 * @param _adc  Pointer to the ADC configuration
 * @param Conversion_status pointer to the status result of conversion 
 *           True is the conversion is complete
 *           False if not completed
 * @return Status of the function
 *              (E_OK) : The function done successfully
 *              (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc , adc_result_t *Conversion_result){

    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) && (NULL == Conversion_result))
    { ret = E_NOT_OK;}
    else
    {
     
        if(ADC_RESULT_RIGHT == _adc->format_select)
        {
            *Conversion_result = (adc_result_t)((ADRESH <<  8) + ADRES);
            
        }
        else if(ADC_RESULT_LEFT == _adc->format_select)
        {
            *Conversion_result = (adc_result_t)(((ADRESH  <<  8) + ADRESL) >> 6);
        }
        else {*Conversion_result = (adc_result_t)((ADRESH <<  8) + (ADRESL));}
        ret = E_OK;
    }
    return ret;
}
/**
 * @Summary      Returns the A/D result (converted Digital result )  
 * @Description   This routine is used to get the conversion result   
 * @Preconditions ADC_Init() must be called before this function calling 
 *                ADC_StartConversion() must be called before this function calling 
 * @param _adc  Pointer to the ADC configuration
 * @param _channel channel type selected 
 * @param Conversion_status pointer to the status result of conversion 
 *           True is the conversion is complete
 *           False if not completed
 * @return Status of the function
 *              (E_OK) : The function done successfully
 *              (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t *_adc , adc_channel_Select_t _channel , adc_result_t *Conversion_result){

    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == Conversion_result))
    { ret = E_NOT_OK;}
    else
    {
        /*Select channel*/
        ret = ADC_SelectChannel(_adc , _channel);
        /*start ADC Conversion*/
        ret = ADC_StartConversion(_adc);
        /*check if conversion completed */
        while(ADC_ConvertStatus());
        /*get conversion digital result*/
        ret = ADC_GetConversionResult(_adc , Conversion_result);
    }
    return ret;
    
}

/**
 * @Summary      Returns the A/D result (converted Digital result )  
 * @Description   This routine is used to get the conversion result   
 * @Preconditions ADC_Init() must be called before this function calling 
 *                ADC_StartConversion() must be called before this function calling 
 * @param _adc  Pointer to the ADC configuration
 * @param _channel channel type selected 
 * @param Conversion_status pointer to the status result of conversion 
 *           True is the conversion is complete
 *           False if not completed
 * @return Status of the function
 *              (E_OK) : The function done successfully
 *              (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversion_Interrupt(const adc_config_t *_adc , adc_channel_Select_t _channel){
Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc))
    { ret = E_NOT_OK;}
    else
    {
        /*Clear Flag*/
        ADC_InterruptClearFlag();
        /*Select channel*/
        ret = ADC_SelectChannel(_adc , _channel);
        /*start ADC Conversion*/
        ret = ADC_StartConversion(_adc);
        ret = E_OK;

    }
    return ret;
    


}



static inline void adc_input_channel_port_configure(const adc_channel_Select_t _channel){

    switch(_channel){
    
        case ADC_CHANNEL_AN0:
            SET_BIT(TRISA , _TRISA_RA0_POSN); break;   /*Disable the digital output driver*/
        case ADC_CHANNEL_AN1:
            SET_BIT(TRISA , _TRISA_RA1_POSN); break;   /*Disable the digital output driver*/
        case ADC_CHANNEL_AN2:
            SET_BIT(TRISA , _TRISA_RA2_POSN); break;   /*Disable the digital output driver*/
        case ADC_CHANNEL_AN3:
            SET_BIT(TRISA , _TRISA_RA3_POSN); break;   /*Disable the digital output driver*/
        case ADC_CHANNEL_AN4:
            SET_BIT(TRISA , _TRISA_RA5_POSN); break;   /*Disable the digital output driver*/ 
        case ADC_CHANNEL_AN5:
            SET_BIT(TRISE , _TRISE_RE0_POSN); break;   /*Disable the digital output driver*/ 
        case ADC_CHANNEL_AN6:
            SET_BIT(TRISE , _TRISE_RE1_POSN); break;   /*Disable the digital output driver*/ 
        case ADC_CHANNEL_AN7:
            SET_BIT(TRISE , _TRISE_RE2_POSN); break;   /*Disable the digital output driver*/ 
        case ADC_CHANNEL_AN8: 
            SET_BIT(TRISB , _TRISB_RB2_POSN); break;   /*Disable the digital output driver*/ 
        case ADC_CHANNEL_AN9:
            SET_BIT(TRISB , _TRISB_RB3_POSN); break;   /*Disable the digital output driver*/ 
        case ADC_CHANNEL_AN10:
            SET_BIT(TRISB , _TRISB_RB1_POSN); break;   /*Disable the digital output driver*/ 
        case ADC_CHANNEL_AN11:
            SET_BIT(TRISB , _TRISB_RB4_POSN); break;   /*Disable the digital output driver*/ 
        case ADC_CHANNEL_AN12:
            SET_BIT(TRISB , _TRISB_RB0_POSN); break;   /*Disable the digital output driver*/ 
        default: {/*Nothing*/};
        
    }
}   
static inline void adc_select_format_configure(const adc_config_t * _adc){
  if(ADC_RESULT_RIGHT == _adc->format_select)
        {
            ADC_ResultRightFormat();
        }
        else if(ADC_RESULT_LEFT == _adc->format_select)
        {
            ADC_ResultLeftFormat();
        }
        else{ADC_ResultRightFormat();}
        
}
static inline void adc_voltage_reference_configure(const adc_config_t * _adc){

    if(ADC_REFERENCE_VOLTAGE_ENABLE == _adc->voltage_reference)
        {
            ADC_VoltageReferenceEnable();
        }
        else if(ADC_REFERENCE_VOLTAGE_DISABLE == _adc->voltage_reference)
        {
            ADC_VoltageReferenceDisable();
        }
        else{ADC_VoltageReferenceDisable();}
    
}

/*
static Std_ReturnType ADC_Interrupt_Handler(void (*ADC_Handler)(void)){

    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ADC_Handler)
    {ret =E_NOT_OK;}
    
    else
    {Interrupt_handler = ADC_Handler;
       ret = E_OK;
    }
 

    return ret;
}
*/

/*
static Std_ReturnType ADC_SetInterrupt_Handler(const adc_config_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = ADC_Interrupt_Handler(_adc->ADC_InterruptHandler);
        ret = E_OK;
    }
    return ret;

}

*/

void ADC_ISR(void){

    /*clear the flag if interrupt*/
    ADC_InterruptClearFlag();
    if(Interrupt_handler){Interrupt_handler();}
   
}
