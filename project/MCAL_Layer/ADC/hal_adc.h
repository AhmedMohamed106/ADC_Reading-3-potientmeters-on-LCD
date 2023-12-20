/* 
 * File:   hal_adc.h
 * Author: Ahmed Mohamed
 *
 * Created on 17 DEC 2023, 05:47 ?
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section : Includes */
#include "hal_adc_cfg.h"
/* Section: Macro Declarations */
/**
 * @brief Analog-To-Digital Port Configuration Control
 * @note  When ADC_AN4_ANALOG_CONFIG is configured, this means
 *        AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 */

#define ADC_AN0_ANALOG_CONFIG   0x0E  /*1110*/
#define ADC_AN1_ANALOG_CONFIG   0x0D  /*1101*/
#define ADC_AN2_ANALOG_CONFIG   0x0C  /*1100*/
#define ADC_AN3_ANALOG_CONFIG   0x0B  /*1011*/
#define ADC_AN4_ANALOG_CONFIG   0x0A  /*1010*/
#define ADC_AN5_ANALOG_CONFIG   0x09  /*1001*/
#define ADC_AN6_ANALOG_CONFIG   0x08  /*1000*/
#define ADC_AN7_ANALOG_CONFIG   0x07  /*0111*/
#define ADC_AN8_ANALOG_CONFIG   0x06  /*0110*/
#define ADC_AN9_ANALOG_CONFIG   0x05  /*0101*/
#define ADC_AN10_ANALOG_CONFIG  0x04  /*0100*/
#define ADC_AN11_ANALOG_CONFIG  0x03  /*0011*/
#define ADC_AN12_ANALOG_CONFIG  0x02  /*0010*/
#define ADC_ALL_ANx_ANALOG_CONFIG    0x00 /*0000*/
#define ADC_ALL_ANx_DIGITAL_CONFIG   0x0F /*1111*/

#define ADC_RESULT_RIGHT   0x01U
#define ADC_RESULT_LEFT    0x00U

#define ADC_CONVERSION_COMPLETED   0x01U
#define ADC_CONVERSION_IN_PROGRESS 0x00U


#define ADC_REFERENCE_VOLTAGE_ENABLE     0x01U
#define ADC_REFERENCE_VOLTAGE_DISABLE    0x00U

#define ADC_CHS_Reg    ADCON0bits.CHS
#define ADC_ACQT_Reg   ADCON2bits.ACQT
#define ADC_ADCS_Reg   ADCON2bits. ADCS
/* Section: Macro Functions Declarations */

/*ADCON0 Configuration*/
/**
 *@brief Analog-To-Digital Control
 * @note ADC_ConverterEnable()  : Enable Analog-To-Digital
 *       ADC_ConverterDisable() : Disable ADC_ConvertEnable 
 */
#define ADC_ConverterEnable()  (ADCON0bits.ADON = 1)
#define ADC_ConverterDisable() (ADCON0bits.ADON = 0)

/**
 *@brief Analog-To-Digital Conversion Status
 * @note ADC_ConvertInPrgress()  : Analog-To-Digital Conversion is in progress Mode
 *       ADC_ConvertStatus()    :  Analog-To-Digital Conversion Idle Mode check
 */
#define ADC_ConvertInPrgress()  (ADCON0bits.GODONE = 1)
#define ADC_ConvertStatus()     (ADCON0bits.GO_nDONE)

/*ADCON1 Configuration*/
/**
 * @brief Voltage Reference Configuration
 * @note  ADC_VoltageReferenceEnable()  :    Voltage Reference VREF source Enable  (Reference -> VRFF- & VRFF-) 
 *        ADC_VoltageReferenceDisable() :    Voltage Reference VREF source Disable (Reference -> VDD & VSS)
 */
#define ADC_VoltageReferenceEnable()   do{ADCON1bits.VCFG1 = 1;\
                                          ADCON1bits.VCFG0 = 1;\
                                          }while(0);

#define ADC_VoltageReferenceDisable()   do{ADCON1bits.VCFG1= 0;\
                                          ADCON1bits.VCFG0 = 0;\
                                          }while(0 );

/**
 * @brief Analog-To-Digital port configuration control 
 * @note Example : ADC_ANALOG_DIGITAL_PORT_CONFIG (ADC_AN4_ANALOG_CONFIG);
         When ADC_AN4_ANALOG_CONFIG is configured, this means 
 *       AN4,AN3,AN2,AN1,AN0 are a analog configured
 *       @ref Analog-To-Digital port configuration control 
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG (_ANx_CONFIG) (ADCON1bits.PCFG = _ANx_CONFIG)

/*ADCON2 Configuration*/
/**
 * @brief A/D Result Format Select Configuration (Right | Left justified) 10-bits digital output register  
 * @note  ADC_ResultRightFormat() :     Right  digital Converted output register value (ADRESL have LSB 8 bits &  ADRESH have MSB 2 bits) 
 *        ADC_ResultLeftFormat () :     Left   digital Converted output register value (ADRESH have MSB 8 bits &  ADRESL have LSB 2 bits)  
 */
#define ADC_ResultRightFormat()   (ADCON2bits.ADFM = 1)
#define ADC_ResultLeftFormat()    (ADCON2bits.ADFM = 0)



/* Section: Data Type Declarations */ 

/**
 * @brief Analog Channel Select
 */
typedef enum {

    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
         
}adc_channel_Select_t;

/**
 * @brief A/D Acquisition Time Select bits
 * @note Acquisition time (sampling time) is the time required for the (ADC) to 
 *       capture the input voltage during sampling   
 * @note acquisition time of a successive Approximation Register (SAR) ADC is the amount of seconds
 *       required to charge the holding capacitor on the front of end of ADC     
 */

typedef enum {

    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD

}adc_acquisition_time_t;

/**
 * @brief A/D Conversion Clock select
 * @note If the A/D FRC cock source is selected, a delay oof one TCY (instruction cycle)    
 *       is added before the A/D clock starts    
 * @note this allows the sleep instruction to be executed before starting a conversion        
 */
typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC, /*(clock derived from A/D RC oscillator)*/
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t;
typedef struct {
#if ADC_INTERRUPT_STATUS == ADC_INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);           /* @ref Pointer to function for callback function if needed */
    Interrupt_priority_cfg priority;
#endif
    //pin_config_t adc_pin;                       /* @ref pin_config_t */
    adc_channel_Select_t adc_channel;             /* @ref adc_channel_Select_t */
    adc_conversion_clock_t conversion_clock;      /* @ref adc_conversion_clock_t */
    adc_acquisition_time_t acquisition_time;      /* @ref adc_acquisition_time_t */
    uint8 voltage_reference : 1;                   /* Voltage reference configuration */
    uint8 format_select     : 1;                   /* A/D Result Format Select */
    uint8 ADC_Reserved      : 6;
    

}adc_config_t;
typedef uint16 adc_result_t;
/* Section: Function Declarations */

Std_ReturnType ADC_Init(const adc_config_t *_adc);

Std_ReturnType ADC_DeInit(const adc_config_t *_adc);

Std_ReturnType ADC_SelectChannel(const adc_config_t *_adc , adc_channel_Select_t _channel);

Std_ReturnType ADC_StartConversion(const adc_config_t *_adc);

Std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc , uint8 *Conversion_status);

Std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc , adc_result_t *Conversion_result);

Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t *_adc , adc_channel_Select_t _channel , adc_result_t *Conversion_result);

Std_ReturnType ADC_GetConversion_Interrupt(const adc_config_t *_adc , adc_channel_Select_t _channel);

#endif	/* HAL_ADC_H */

