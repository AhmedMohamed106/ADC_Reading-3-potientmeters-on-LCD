/* 
 * File:   mcal_external_interrupt.h
 * Author: Ahmed mohamed
 *
 * Created on 09 dec 2023, 04:23 ?
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* section: Includes */

#include "mcal_interrupt_config.h"

/* Section: Macro Declarations */


/* Section: Macro Functions Declarations */
#if EXTERNAL_INTERRUPT_INTX_ENABLE == INTERRUPT_FEATURE_ENABLE
/*this macro will enable INT0 Interrupt on pin number 0 in port B*/
#define  EXT_INT0_InterruptEnable()  (INTCONbits.INT0IE = 1)
/*this macro will disable INT0 Interrupt on pin number 0 in port B*/
#define  EXT_INT0_InterruptDisable()  (INTCONbits.INT0IE = 0)   
/*this macro will clear the flag of INT0*/
#define EXT_INT0_InterruptClearFlag()  (INTCONbits.INT0IF = 0)
/*this macro will select interrupt to occur on rising edge state of (button for example)*/
#define EXT_INT0_RisingEdgeSet()       (INTCON2bits.INTEDG0 = 1)
/*this macro will select interrupt to occur on falling edge state of (button for example)*/
#define EXT_INT0_FallingEdgeSet()      (INTCON2bits.INTEDG0 = 0)

/*this macro will enable INT1 Interrupt on pin number 1 in port B*/
#define  EXT_INT1_InterruptEnable()  (INTCON3bits.INT1IE = 1)
/*this macro will disable INT1 Interrupt on pin number 1 in port B*/
#define  EXT_INT1_InterruptDisable()  (INTCON3bits.INT1IE = 0)   
/*this macro will clear the flag of INT1*/
#define EXT_INT1_InterruptClearFlag()  (INTCON3bits.INT1IF = 0)
/*this macro will select interrupt of INT1 to occur on rising edge state of (button for example)*/
#define EXT_INT1_RisingEdgeSet()       (INTCON2bits.INTEDG1 = 1)
/*this macro will select interrupt of INT1 to occur on falling edge state of (button for example)*/
#define EXT_INT1_FallingEdgeSet()      (INTCON2bits.INTEDG1 = 0)

/*this macro will enable INT2 Interrupt on pin number 1 in port B*/
#define  EXT_INT2_InterruptEnable()  (INTCON3bits.INT2IE = 1)
/*this macro will disable INT2 Interrupt on pin number 1 in port B*/
#define  EXT_INT2_InterruptDisable()  (INTCON3bits.INT2IE = 0)   
/*this macro will clear the flag of INT2*/
#define EXT_INT2_InterruptClearFlag()  (INTCON3bits.INT2IF = 0)
/*this macro will select interrupt of INT2 to occur on rising edge state of (button for example)*/
#define EXT_INT2_RisingEdgeSet()      (INTCON2bits.INTEDG2 = 1)
/*this macro will select interrupt of INT2 to occur on falling edge state of (button for example)*/
#define EXT_INT2_FallingEdgeSet()      (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*this macro will set INT1 interrupt as a high priority interrupt */
#define EXT_INT1_InterruptHighPriorityEnable()  (INTCON3bits.INT1IP = 1)
/*this macro will set INT1 interrupt as a low priority interrupt */
#define EXT_INT1_InterruptLowPriorityEnable()   (INTCON3bits.INT1IP = 0)

/*this macro will set INT2 interrupt as a high priority interrupt */
#define EXT_INT2_InterruptHighPriorityEnable()  (INTCON3bits.INT2IP = 1)
/*this macro will set INT2 interrupt as a low priority interrupt */
#define EXT_INT2_InterruptLowPriorityEnable()   (INTCON3bits.INT2IP = 0)
#endif

#endif

#if EXTERNAL_INTERRUPT_ONCHANGE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*this macro will enable RBx (on change interrupt enable) Interrupt */
#define  EXT_RBx_InterruptEnable()  (INTCONbits.RBIE = 1)
/*this macro will disable RBx (on change interrupt enable) Interrupt */
#define  EXT_RBx_InterruptDisable()  (INTCONbits.RBIE = 0)   
/*this macro will clear the flag of RBx*/
#define EXT_RBx_InterruptClearFlag()  (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*this macro will set RBI as high priority Interrupt*/
#define  EXT_RBx_InterruptHighPriorityEnable() (INTCON2bits.RBIP = 1)
/*this macro will set RBI as low priority Interrupt*/
#define  EXT_RBx_InterruptLowPriorityEnable() (INTCON2bits.RBIP = 0)
#endif
#endif

/* Section: Data Type Declarations */
typedef void (*InterruptHandler)(void); 

typedef enum{
    INTERRUPT_FALING_EDGE = 0,
    INTERRUPT_RISING_EDGE     

}Interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2

}Interrupt_INTx_src;

typedef struct {
    void (* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    Interrupt_INTx_edge edge;
    Interrupt_INTx_src source;
    Interrupt_priority_cfg priority;

}Interrupt_INTx_t;
  

typedef struct{
    void (* EXT_InterruptHandler_HIGH)(void);
    void (* EXT_InterruptHandler_LOW)(void);
    pin_config_t mcu_pin;
    Interrupt_priority_cfg priority;
}Interrupt_RBx_T;


/* Section: Function Declarations */

Std_ReturnType Interrupt_INTx_Init(const Interrupt_INTx_t * int_obj);
Std_ReturnType Interrupt_INTx_DeInit(const Interrupt_INTx_t * int_obj);
Std_ReturnType Interrupt_RBx_Init(const Interrupt_RBx_T * rbx_obj);
Std_ReturnType Interrupt_RBx_DeInit(const Interrupt_RBx_T * rbx_obj);


#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

