/* 
 * File:   hal_timer0.c
 * Author: Ahmed Mohamed
 *
 * Created on 20 December 2023, 01:47 ?
 */
#include "hal_timer0.h"

#if TIMER0_INTERRUPT_STATUS == INTERRUPT_FEATURE_ENABLE
static void (*Timer0InterruptHandler) (void) = NULL;
#endif
static uint16 timer0_preload = ZERO_INIT;

static inline void Timer0_Prescaler_Config(const timer0_config_t * _timer);
static inline void Timer0_Register_Size_Config(const timer0_config_t * _timer);
static inline void Timer0_Mode_Select(const timer0_config_t * _timer);





/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer0_Init(const timer0_config_t *_timer){

    Std_ReturnType ret = E_NOT_OK;
    if(NULL== _timer)
    {
        ret = E_NOT_OK;
    }

    else
    {
        /*Disable the Timer0 module */
        TIMER0_Disable();
        /*timer0 prescaler configuration*/
        Timer0_Prescaler_Config(_timer);
        /*timer0 timer/counter mode selection*/
        Timer0_Mode_Select(_timer);
        /*timer0 Register mode : 8-Bit mode or 16-Bit mode*/
        Timer0_Register_Size_Config(_timer);
        TMR0H = ((_timer->timer0_preload_value) >> 8);
        TMR0L = (uint8)(_timer->timer0_preload_value);
        timer0_preload = _timer->timer0_preload_value;
    #if TIMER0_INTERRUPT_STATUS == INTERRUPT_FEATURE_ENABLE
        
        TIMER0_InterruptEnable();
        TIMER0_InterruptClearFlag();
        Timer0InterruptHandler = _timer->Timer0_InterruptHandler;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            /*High global interrupt enable*/
            INTERRUPT_globalInterruptHighEnable();
            TIMER0_HighPriorityEnable();
        }
        else if (INTERRUPT_LOW_PRIORITY == _adc->priority) {
            /*Low global interrupt enable*/
            INTERRUPT_globalInterruptLowEnable();
            TIMER0_LowPriorityEnable();
        }
        else {/*Nothing*/}
    #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();
    #endif     
    #endif 
        TIMER0_Enable();
        ret = E_OK;
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer0_DeInit(const timer0_config_t *_timer){ 
Std_ReturnType ret = E_NOT_OK;
    if(NULL== _timer)
    {
        ret = E_NOT_OK;
    }

    else
    {
      /*Disable timer 0*/
        TIMER0_Disable();
     #if TIMER0_INTERRUPT_STATUS == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
     #endif
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer0_Write_Value(const timer0_config_t *_timer , uint16 _value){ 
Std_ReturnType ret = E_NOT_OK;
    if(NULL== _timer)
    {
        ret = E_NOT_OK;
    }

    else
    {
    
        TMR0H = ((_value) >> 8);
        TMR0L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer0_Read_Value(const timer0_config_t *_timer , uint16 *_value){ 
Std_ReturnType ret = E_NOT_OK;
uint8 l_timer = ZERO_INIT , h_timer = ZERO_INIT;
    if(NULL== _timer && NULL== _value)
    {
        ret = E_NOT_OK;
    }

    else
    {
       l_timer = TMR0L;  
       h_timer = TMR0H;
       *_value = (uint16)((h_timer << 8) + l_timer);
       ret = E_OK;
        
    }
    return ret;
}

static inline void Timer0_Prescaler_Config(const timer0_config_t * _timer){
    if(TIMER0_PRESCALER_ENABLE == _timer->prescaler_enable)
    {
        TIMER0_PrescalerEnable();
        T0CONbits.T0PS = _timer->Prescale_value;
    }
    else if(TIMER0_PRESCALER_DISABLE == _timer->prescaler_enable)
    {
        TIMER0_PrescalerDisable();
    }
    else {/*Nothing*/}   
} 
static inline void Timer0_Register_Size_Config(const timer0_config_t * _timer){
    if(TIMER0_8BIT_MODE == _timer->timer0_Register_mode)
    {
        TIMER0_8bitModeEnable();
    }
    else if(TIMER0_16BIT_MODE == _timer->timer0_Register_mode)
    {
        TIMER0_16bitModeEnable();
    }
    else {/*Nothing*/}   
} 

static inline void Timer0_Mode_Select(const timer0_config_t * _timer){
  if(TIMER0_TIMER_MODE == _timer->timer_counter_mode)
    {
        TIMER0_TimerModeEnable();
    }
    else if(TIMER0_COUNTER_MODE == _timer->timer_counter_mode)
    {
        TIMER0_CounterModeEnable();
        if(TIMER0_RISING_EDGE_CFG == _timer->edge_select)
        {
            TIMER0_RisingEdgeEnable();
        }
        else if (TIMER0_FALLING_EDGE_CFG == _timer->edge_select)
        {
            TIMER0_FallingEdgeEnable();
        }
        
         else {/*Nothing*/}
    }
    else {/*Nothing*/}   
    

}

void TIMER0_ISR(void){

    /*Clear the interrupt flag*/
    TIMER0_InterruptClearFlag();
    TMR0H = ((timer0_preload) >> 8);
    TMR0L = (uint8)(timer0_preload);
    
    
    /*execute some mcal layer code */
    
    /*configure the callack function*/
    if(Timer0InterruptHandler)
    {Timer0InterruptHandler();}

}
