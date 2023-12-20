/* 
 * File:   hal_timer0.h
 * Author: Ahmed Mohamed
 *
 * Created on 20 December 2023, 01:47 ?
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H
/*Section: Includes */
 #include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
 
/* Section: Macro Declarations */

//prescaler values
#define TIMER0_PRESCALER_ENABLE  0x01U
#define TIMER0_PRESCALER_DISABLE 0x00U

//mode bit register values
#define TIMER0_8BIT_MODE   0x01U
#define TIMER0_16BIT_MODE  0x01U

//ede select values 
#define TIMER0_RISING_EDGE_CFG  0x01U
#define TIMER0_FALLING_EDGE_CFG 0x00U

//timer0 modes timer | counter
#define TIMER0_TIMER_MODE    0x01U
#define TIMER0_COUNTER_MODE  0x00U
/* Section: Macro Functions Declarations */

/**
 * @brief Configure Timer0 enables to work : Timer0 On/Off Control bit
 * @note TIMER0_Enable() : will enable timer0
 * @note TIMER0_Disable(): will disable timer0
 */
#define TIMER0_Enable()   (T0CONbits.TMR0ON = 1)
#define TIMER0_Disable()  (T0CONbits.TMR0ON = 0)

/**
 * @brief Configure Timer0 Bit Mode : Timer0 8-Bit/16-Bit Control bit
 * @note TIMER0_8bitModeEnable() : Timer0 is configured as an 8-bit timer/counter 
 * @note TIMER0_16bitModeEnable(): Timer0 is configured as a 16-bit timer/counter
 */
#define TIMER0_8bitModeEnable()  (T0CONbits.T08BIT = 1)
#define TIMER0_16bitModeEnable() (T0CONbits.T08BIT = 0)

/**
 * @brief Configure Timer0 Clock source Internal or External : Timer0 Clock Source Select bit
 * @note TIMER0_TimerMode() :  External cock source (Transition on T0CKI pin) 
 * @note TIMER0_CounterMode():   Internal instruction cycle clock source (CLKO)
 */
#define TIMER0_TimerModeEnable() (T0CONbits.T0CS =   0)
#define TIMER0_CounterModeEnable() (T0CONbits.T0CS = 1)

/**
 * @brief Configure Timer0 Source Edge Select : Rising or Falling Edge 
 * @note TIMER0_RisingEdgeEnable() :  Increment on low-to-high transition on T0CKI pin  
 * @note TIMER0_FallingEdgeEnable():  Increment on high-to-low transition on T0CKI pin
 */
#define TIMER0_RisingEdgeEnable() (T0CONbits.T0SE = 0)
#define TIMER0_FallingEdgeEnable() (T0CONbits.T0SE = 1)

/**
 * @brief Configure Timer0 SPrescaler Assignment : Assigned or not assigned 
 * @note TIMER0_PrescalerEnable() :  Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output  
 * @note TIMER0_PrescalerDisable(): TImer0 prescaler is not assigned. Timer0 clock input bypasses prescaler. 
 */
#define TIMER0_PrescalerEnable()   (T0CONbits.PSA = 0)
#define TIMER0_PrescalerDisable()  (T0CONbits.PSA = 1)

/* Section: Data Type Declarations */
typedef enum {
    TIMER0_PRESCALER_DIV_2 = 0,      /* 000 = 1:2   Prescale value */
    TIMER0_PRESCALER_DIV_4,          /* 001 = 1:4   Prescale value */
    TIMER0_PRESCALER_DIV_8,          /* 010 = 1:8   Prescale value */
    TIMER0_PRESCALER_DIV_16,         /* 011 = 1:16  Prescale value */
    TIMER0_PRESCALER_DIV_32,         /* 100 = 1:32  Prescale value */
    TIMER0_PRESCALER_DIV_64,         /* 101 = 1:64  Prescale value */
    TIMER0_PRESCALER_DIV_128,        /* 110 = 1:128 Prescale value */
    TIMER0_PRESCALER_DIV_256         /* 111 = 1:256 Prescale value */
}timer0_prescaler_select_t;

typedef struct {

#if TIMER0_INTERRUPT_STATUS == INTERRUPT_FEATURE_ENABLE    
    void (*Timer0_InterruptHandler)(void);
    Interrupt_priority_cfg  priority;
#endif 
    timer0_prescaler_select_t Prescale_value;
    uint16 timer0_preload_value;    
    uint8 timer0_Register_mode      :1;
    uint8 edge_select               :1;
    uint8 prescaler_enable          :1;
    uint8 timer_counter_mode        :1;
    uint8 timer0_reserved           :4; 
    
    
}timer0_config_t;

/* Section: Function Declarations */
Std_ReturnType Timer0_Init(const timer0_config_t *_timer);
Std_ReturnType Timer0_DeInit(const timer0_config_t *_timer);
Std_ReturnType Timer0_Write_Value(const timer0_config_t *_timer , uint16 _value);
Std_ReturnType Timer0_Read_Value(const timer0_config_t *_timer , uint16 *_value);



#endif	/* HAL_TIMER0_H */

