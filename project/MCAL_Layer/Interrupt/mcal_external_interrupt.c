/* 
 * File:   mcal_external_interrupt.c
 * Author: Ahmed mohamed
 *
 * Created on 09 dec 2023, 04:23 ?
 */

#include "mcal_external_interrupt.h"

/*Pointer to function to hold the callback function to INTx interrupts  */
static InterruptHandler INT0_InterruptHandler = NULL; 
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;

/*Pointer to function to hold the callback function to RBx interrupts*/
static InterruptHandler RB4_InterruptHandler_High = NULL;
static InterruptHandler RB4_InterruptHandler_Low  = NULL;
static InterruptHandler RB5_InterruptHandler_High = NULL;
static InterruptHandler RB5_InterruptHandler_Low  = NULL;
static InterruptHandler RB6_InterruptHandler_High = NULL;
static InterruptHandler RB6_InterruptHandler_Low  = NULL;
static InterruptHandler RB7_InterruptHandler_High = NULL;
static InterruptHandler RB7_InterruptHandler_Low  = NULL;
 

/* Helper functions to initialize interrupt configuration */
static Std_ReturnType Interrupt_INTx_Enable(const Interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const Interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const Interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const Interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const Interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const Interrupt_INTx_t * int_obj);

static Std_ReturnType INT0_Set_InterruptHandler(void (*INTx_InterruptHandler)(void));
static Std_ReturnType INT1_Set_InterruptHandler(void (*INTx_InterruptHandler)(void));
static Std_ReturnType INT2_Set_InterruptHandler(void (*INTx_InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const Interrupt_INTx_t * int_obj);


/**
 * 
 * @param  @ref  
 * @param 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType Interrupt_INTx_Init(const Interrupt_INTx_t * int_obj){

    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
        ret  = Interrupt_INTx_Disable(int_obj);                             /* Disable the external interrupt */
        ret |= Interrupt_INTx_Clear_Flag(int_obj);                          /* Clear the external interrupt flag: interrupt doesn't occur */
        ret |= Interrupt_INTx_Edge_Init(int_obj );                          /* Configure external interrupt edge */
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret |= Interrupt_INTx_Priority_Init(int_obj);                        /* Configure external interrupt priority */
        #endif
        ret |= Interrupt_INTx_Pin_Init(int_obj);                             /*Configure external interrupt pin*/
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);                  /*Configure callback function*/
        ret |= Interrupt_INTx_Enable(int_obj);                               /*Enable the external interrupt*/
    }
    
    return ret;

}

/*ISR (Interrupt service routine implementation for INTx)*/
void INT0_ISR(void){

    /*clear Flag bit : The INT0 external interrupt occurred (must be cleared by software) */
    EXT_INT0_InterruptClearFlag();
    /*some code for configuration*/
    
    /*callback function call to execute some application layered event responding to interrupt */
    if(INT0_InterruptHandler){INT0_InterruptHandler();}
    else{/*Nothing*/}

}
void INT1_ISR(void){

    /*clear Flag bit : The INT1 external interrupt occurred (must be cleared by software) */
    EXT_INT1_InterruptClearFlag();
    /*some code for configuration*/
    
    /*callback function call to execute some application layered event responding to interrupt */
    if(INT1_InterruptHandler){INT1_InterruptHandler();}
    else{/*Nothing*/}

}
void INT2_ISR(void){

    /*clear Flag bit : The INT2 external interrupt occurred (must be cleared by software) */
    EXT_INT2_InterruptClearFlag();
    /*some code for configuration*/
    
    /*callback function call to execute some application layered event responding to interrupt */
    if(INT2_InterruptHandler){INT2_InterruptHandler();}
    else{/*Nothing*/}

}
void RB4_ISR(uint8 RB4_Source){

    /*the external interrupt RB4 occurs : Must be cleared by software*/
    EXT_RBx_InterruptClearFlag();
    /*code: To be executed from MCAL Interrupt Context*/
    /*Application Callback function gets called ever time this ISR executes*/
     if(0 == RB4_Source){
        if(RB4_InterruptHandler_High){ RB4_InterruptHandler_High(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB4_Source){
        if(RB4_InterruptHandler_Low){ RB4_InterruptHandler_Low(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   

}
void RB5_ISR(uint8 RB5_Source){
  /*the external interrupt RB4 occurs : Must be cleared by software*/
    EXT_RBx_InterruptClearFlag();
    /*code: To be executed from MCAL Interrupt Context*/
    /*Application Callback function gets called ever time this ISR executes*/
     if(0 == RB5_Source){
        if(RB5_InterruptHandler_High){ RB5_InterruptHandler_High(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB5_Source){
        if(RB5_InterruptHandler_Low){ RB5_InterruptHandler_Low(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   
    
}
void RB6_ISR(uint8 RB6_Source){
/*the external interrupt RB4 occurs : Must be cleared by software*/
    EXT_RBx_InterruptClearFlag();
    /*code: To be executed from MCAL Interrupt Context*/
    /*Application Callback function gets called ever time this ISR executes*/
     if(0 == RB6_Source){
        if(RB6_InterruptHandler_High){ RB6_InterruptHandler_High(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB6_Source){
        if(RB6_InterruptHandler_Low){ RB6_InterruptHandler_Low(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }  
    

}
void RB7_ISR(uint8 RB7_Source){
/*the external interrupt RB4 occurs : Must be cleared by software*/
    EXT_RBx_InterruptClearFlag();
    /*code: To be executed from MCAL Interrupt Context*/
    /*Application Callback function gets called ever time this ISR executes*/
     if(0 == RB7_Source){
        if(RB7_InterruptHandler_High){ RB7_InterruptHandler_High(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB7_Source){
        if(RB7_InterruptHandler_Low){ RB7_InterruptHandler_Low(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }  


}


/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const Interrupt_INTx_t * int_obj){

    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
        ret  = Interrupt_INTx_Disable(int_obj);
        
    }

}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const Interrupt_RBx_T * rbx_obj){

    Std_ReturnType ret = E_OK;
    if(NULL == rbx_obj)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
        /*This routine will clear the interrupt disable for external interrupt, RBx*/
        EXT_RBx_InterruptDisable();
        /*This routine clears flag bit for the external interrupt RBx*/
        EXT_RBx_InterruptClearFlag();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
       INTERRUPT_PriorityLevelsEnable();
       if(INTERRUPT_LOW_PRIORITY == rbx_obj->priority)
       {
           /*this routine enables All  global Low priority interrupts */
           INTERRUPT_globalInterruptLowEnable(); 
           /*this routine enables external Low priority interrupts for, RBx */
           EXT_RBx_InterruptLowPriorityEnable();
       }
       else if(INTERRUPT_HIGH_PRIORITY == rbx_obj->priority)
       {
           /*this routine enables All  global High priority interrupts */
           INTERRUPT_globalInterruptHighEnable();
           /*this routine enables external high priority interrupts for, RBx */
           EXT_RBx_InterruptHighPriorityEnable();
       }
       else{/*Nothing*/}
#else
       /*this macro enables global interrupts */
        INTERRUPT_GlobalInterruptEnable();
        /*this macro enables peripheral interrupts */
        INTERRUPT_PeripheralsInterruptEnable();
#endif
        /*Initialize the mcu pin for RBx as input */
        ret = gpio_pin_direction_intialize(&(rbx_obj->mcu_pin));
        
        /* Initialize the callback function */
        switch(rbx_obj->mcu_pin.pin)
        {
            case GPIO_PIN4: 
                RB4_InterruptHandler_Low   = rbx_obj->EXT_InterruptHandler_LOW;
                RB4_InterruptHandler_High  = rbx_obj->EXT_InterruptHandler_HIGH;                
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler_Low   = rbx_obj->EXT_InterruptHandler_LOW;
                RB5_InterruptHandler_High  = rbx_obj->EXT_InterruptHandler_HIGH;    
                break;
            case GPIO_PIN6:
               RB6_InterruptHandler_Low   = rbx_obj->EXT_InterruptHandler_LOW;
               RB6_InterruptHandler_High  = rbx_obj->EXT_InterruptHandler_HIGH;    
                
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler_Low   = rbx_obj->EXT_InterruptHandler_LOW;
                RB7_InterruptHandler_High  = rbx_obj->EXT_InterruptHandler_HIGH;    
                break;
            default: ret = E_NOT_OK;

        
        }
        /*this routine sets the interrupt enable for external interrupt ,RBx */
        EXT_RBx_InterruptEnable();        
    }
    return ret;

}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const Interrupt_RBx_T * int_obj){

    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
        EXT_RBx_InterruptDisable();
        EXT_RBx_InterruptClearFlag();
        
    }

}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable(const Interrupt_INTx_t * int_obj){

     Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
        switch(int_obj->source)
        {
            
            case INTERRUPT_EXTERNAL_INT0  :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
               
                 INTERRUPT_globalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralsInterruptEnable();
              
#endif
                EXT_INT0_InterruptEnable();
            break;
            case INTERRUPT_EXTERNAL_INT1 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                 if(INTERRUPT_LOW_PRIORITY == int_obj->priority )
                {
                    INTERRUPT_globalInterruptLowEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority )
                {
                    INTERRUPT_globalInterruptHighEnable();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralsInterruptEnable();
#endif
                EXT_INT1_InterruptEnable();
            break;
            case INTERRUPT_EXTERNAL_INT2 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                 if(INTERRUPT_LOW_PRIORITY == int_obj->priority )
                {
                    INTERRUPT_globalInterruptLowEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority )
                {
                    INTERRUPT_globalInterruptLowEnable();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralsInterruptEnable();
#endif
                EXT_INT2_InterruptEnable();
            break;
            default: ret = E_NOT_OK ;        
        }
    }

     return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable(const Interrupt_INTx_t * int_obj){

     Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
         switch(int_obj->source){
             
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptDisable();
            break;
            case INTERRUPT_EXTERNAL_INT1 :
                EXT_INT1_InterruptDisable();
            break;
            case INTERRUPT_EXTERNAL_INT2 :
                EXT_INT2_InterruptDisable();
            break;
            default: ret = E_NOT_OK ;        
        }
        
    }
     return ret;

}
/**
 * 
 * @param int_obj
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const Interrupt_INTx_t * int_obj){

     Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
         switch(int_obj->source){
             
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority )
                {
                    EXT_INT1_InterruptLowPriorityEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority )
                {
                    EXT_INT1_InterruptHighPriorityEnable();
                }
                else {/*Nothing*/}
            break;
            case INTERRUPT_EXTERNAL_INT2 :
                if(INTERRUPT_LOW_PRIORITY ==int_obj->priority)
                {
                    EXT_INT2_InterruptLowPriorityEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY ==int_obj->priority)
                {
                    EXT_INT2_InterruptHighPriorityEnable();
                }
                else {/*Nothing*/}
                
            break;
            default: ret = E_NOT_OK ;        
        }
        
        
        
    }
     return ret;

}

#endif
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const Interrupt_INTx_t * int_obj){

     Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
     
     return ret;

}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const Interrupt_INTx_t * int_obj){

     Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
    
        ret = E_NOT_OK;
    }
    
    else
    {
        switch(int_obj->source){
           
             case INTERRUPT_EXTERNAL_INT0 : 
                if( INTERRUPT_FALING_EDGE == int_obj->edge )
                {
                    EXT_INT0_FallingEdgeSet();
                }
                else if (INTERRUPT_RISING_EDGE == int_obj->edge )
                {
                    EXT_INT0_RisingEdgeSet();
                }
                else {/*Nothing*/}
            break;
            
            case INTERRUPT_EXTERNAL_INT1 : 
                if( INTERRUPT_FALING_EDGE == int_obj->edge )
                {
                    EXT_INT1_FallingEdgeSet();
                }
                else if (INTERRUPT_RISING_EDGE == int_obj->edge )
                {
                    EXT_INT1_RisingEdgeSet();
                }
                else {/*Nothing*/}
            break;
            case INTERRUPT_EXTERNAL_INT2 :
                if( INTERRUPT_FALING_EDGE == int_obj->edge )
                {
                    EXT_INT2_FallingEdgeSet();
                }
                else if (INTERRUPT_RISING_EDGE == int_obj->edge )
                {
                    EXT_INT2_RisingEdgeSet();
                }
                else {/*Nothing*/}
            break;
            default: ret = E_NOT_OK ;        
        }
    }
     
     return ret;

}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const Interrupt_INTx_t * int_obj){

    Std_ReturnType ret = E_OK;
    if(NULL== int_obj)
    {
        ret = E_NOT_OK;
    } 
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 :
                EXT_INT0_InterruptClearFlag();
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                EXT_INT1_InterruptClearFlag();
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                EXT_INT2_InterruptClearFlag();
                break;
            default: ret = E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param INTx_InterruptHandler
 * @return 
 */
static Std_ReturnType INT0_Set_InterruptHandler(void (*INTx_InterruptHandler)(void)){

    Std_ReturnType ret = E_OK;
    
    if(NULL==INTx_InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    
    else{INT0_InterruptHandler=INTx_InterruptHandler;}
    return ret;
}
/**
 * 
 * @param INTx_InterruptHandler
 * @return 
 */
static Std_ReturnType INT1_Set_InterruptHandler(void (*INTx_InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    
    if(NULL==INTx_InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else{INT1_InterruptHandler=INTx_InterruptHandler;}

    return ret;
}
/**
 * 
 * @param INTx_InterruptHandler
 * @return 
 */
static Std_ReturnType INT2_Set_InterruptHandler(void (*INTx_InterruptHandler)(void)){
    
    Std_ReturnType ret = E_OK;
    
        if(NULL==INTx_InterruptHandler)
        {
            ret = E_NOT_OK;
        }
    
        else{INT2_InterruptHandler=INTx_InterruptHandler;}

    
        
    return ret;
  
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const Interrupt_INTx_t * int_obj){

    Std_ReturnType ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }

    else
    {
        
    switch(int_obj->source){   
             
            case INTERRUPT_EXTERNAL_INT0 : 
                ret = INT0_Set_InterruptHandler(int_obj->EXT_InterruptHandler);
            break;
            case INTERRUPT_EXTERNAL_INT1 :
                ret = INT1_Set_InterruptHandler(int_obj->EXT_InterruptHandler);
            break;
            case INTERRUPT_EXTERNAL_INT2 :
                ret = INT2_Set_InterruptHandler(int_obj->EXT_InterruptHandler);
            break;
            default: ret = E_NOT_OK ;        
        }

}
    return ret;
}



