/* 
 * File:   mcal_internal_interrupt.h
 * Author: Ahmed mohamed
 *
 * Created on 09 dec 2023, 04:22 ?
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/* section: Includes */
#include "mcal_interrupt_config.h"

/* Section : Includes */

/* Section: Macro Declarations */
#if ADC_INTERRUPT_STATUS == ADC_INTERRUPT_FEATURE_ENABLE
/* this routine enables the interrupt for the ADC module */
#define ADC_InterruptEnable()   (PIE1bits.ADIE = 1)
/* this routine disables the interrupt for the ADC module */
#define ADC_InterruptDisable()   (PIE1bits.ADIE = 0)
/*this routine  clears the flag of ADC module */
#define ADC_InterruptClearFlag()  (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*this routine configure the ADC priority as high priority*/
#define ADC_HighPriorityEnable()  (IPR1bits.ADIP = 1)
/*this routine configure the ADC priority as low priority*/
#define ADC_LowPriorityEnable()  (IPR1bits.ADIP = 0)
#endif

#endif

#if TIMER0_INTERRUPT_STATUS == INTERRUPT_FEATURE_ENABLE
/* this routine enables the interrupt for the Timer0 module */
#define TIMER0_InterruptEnable()    (INTCONbits.TMR0IE = 1)
/* this routine disables the interrupt for the Timer0 module */
#define TIMER0_InterruptDisable()   (INTCONbits.TMR0IE = 0)
/*this routine  clears the flag of ADC module */
#define TIMER0_InterruptClearFlag() (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*this routine configure the Timer0 priority as high priority*/
#define TIMER0_HighPriorityEnable()  (INTCON2bits.TMR0IP = 1)
/*this routine configure the Timer0 priority as low priority*/
#define TIMER0_LowPriorityEnable()   (INTCON2bits.TMR0IP = 0)
#endif
#endif

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

