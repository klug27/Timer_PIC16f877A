
#include <stdbool.h>
#include <xc.h>
#include "hw_desc_timer.h"

/******************************************************************************
* @file		hw_desc_timer.c
* @author	VOUFO ASTRI
* @date		26.05.2023
*******************************************************************************/

 /****************************************************************************
  * 
 *                                                                           *                                     
 *  D E F I N I T I O N                                                      *                                     
 *                                                                           *                                     
 *****************************************************************************/

#define NULLPTR                           ((void*)0)
#define INTCON_GIE_BIT                    (7)
#define GLOBAL_INTERRUPT_ENABLE_MSK       (1 << INTCON_GIE_BIT)
#define INTCON_TMR0IE_BIT                 (5)
#define TIMER0_OVF_INTERRRUPT_ENABLE_MSK  (1 << INTCON_TMR0IE_BIT)
#define INTCON_TMR0IF_BIT                 (2)
#define TIMER0_INTERRRUPT_FLAG            (1 << INTCON_TMR0IF_BIT)
#define CLEAR_REG                         (0)
#define READ_FLAG(REG,BIT)                (REG & (1 << BIT))
#define CLEAR_FLAG(REG,BIT)                REG &= ~(1 << BIT)
#define SET_FLAG(REG,BIT)                  REG |= (1 << BIT)
#define OPTION_REG_T0CS_BIT                (5)
#define CLK_SRC_T0CKI_PIN                  (1 << OPTION_REG_T0CS_BIT)
#define CLK_SRC_INTERNAL_CLOCK_MSK         (0 << OPTION_REG_T0CS_BIT)
#define TIMER0_CLKSRC_MSK                  CLK_SRC_INTERNAL_CLOCK
#define OPTION_REG_CLEAR_REG               (0x3F)
#define OPTION_REG_PS_START_BIT            (0)
#define OPTION_REG_PSA_BIT                 (3)
#define PRESC_ASSIGN_TO_TIMER_MSK          (0 << OPTION_REG_PSA_BIT)      
#define PS_DIV2                            (0)
#define PS_DIV4                            (1)
#define PS_DIV8                            (2)
#define PS_DIV16                           (3)
#define PS_DIV32                           (4)
#define PS_DIV64                           (5)
#define PS_DIV128                          (6)
#define PS_DIV256                          (7)
#define TIMER0_PRESCALER                   PS_DIV32
#define PRESCALER_MSK                      (TIMER0_PRESCALER << OPTION_REG_PS_START_BIT)
#ifndef _XTAL_FREQ
#define _XTAL_FREQ                         20000000UL
#endif
#define FREQ_TIMER0                        ((uint32_t)_XTAL_FREQ/(1 << (3 + TIMER0_PRESCALER)))
#define TIMER0_EXTRA_CYCLE                 (2)
#define TIMER0_MAX_CYCLE                   (uint16_t)(256)
#define TIMER_TICK                         (1000)   // timer overflow every 1ms => 1/1000Hz
#define TIMER0_PERIOD                      (TIMER0_MAX_CYCLE - (uint8_t)(FREQ_TIMER0/TIMER_TICK) + TIMER0_EXTRA_CYCLE)
#define TIMER_ZERO                         (0)
#define TIMER_ONE                          (1)

 /****************************************************************************
 *                                                                           *                                     
 *  P R I V A T E  F U N C T I O N  I M P L E M E N T A T I O N              *                                     
 *                                                                           *                                     
 *****************************************************************************/


 /****************************************************************************
 *                                                                           *                                     
 *  E N U M E R A T I O N                                                    *                                     
 *                                                                           *                                     
 *****************************************************************************/

typedef enum eDriverState_tTag
{
    TIMER_DRIVER_INITIALIZED   = 1,     /**< Timer is initialize */
    TIMER_DRIVER_UNINITIALIZED = 2,     /**< Timer is unitialize */
            
    TIMER_DRIVER_MAX
} eDriverState_t;


 /****************************************************************************
 *                                                                           *                                     
 *  S T R U C T U R E                                                        *                                     
 *                                                                           *                                     
 *****************************************************************************/

/** Definition on timer control block structure */
typedef struct sTimerCtrlBlock_tTag
{
    cbkFunc_t       Function;               ///< callback function
    uint32_t        u32PeriodMs;            ///< period (in millisecond) of called function
    uint32_t        u32NextTime;            ///< the function will be called after the elapsed period
    uint32_t        u32TickMs;              ///< millisecond ticks
    eDriverState_t  eState;                 ///< timer state : Ininitialized or not
} sTimerCtrlBlock_t;

 /****************************************************************************
 *                                                                           *                                     
 *  P R I V A T E  V A R I A B L E                                           *                                     
 *                                                                           *                                     
 *****************************************************************************/

/** Callback data  */
static volatile sTimerCtrlBlock_t sTimerCtrl = 
{.Function    = NULLPTR, .u32PeriodMs = TIMER_ZERO, .u32TickMs = TIMER_ZERO, 
     .u32NextTime = TIMER_ZERO, .eState   = TIMER_DRIVER_UNINITIALIZED
};

 /****************************************************************************
 *                                                                           *                                     
 *  P R I V A T E  F U N C T I O N  I M P L E M E N T A T I O N              *                                     
 *                                                                           *                                     
 *****************************************************************************/


 /****************************************************************************
 *                                                                           *                                     
 *  P U B L I C  F U N C T I O N  I M P L E M E N T A T I O N                *                                     
 *                                                                           *                                     
 *****************************************************************************/

bool bTimerInit(void)
{
    if (TIMER_DRIVER_UNINITIALIZED == sTimerCtrl.eState)
    {
        /* set timer state : timer is initialized */
        sTimerCtrl.eState = TIMER_DRIVER_INITIALIZED;
                
        /* Enable timer0 interrupt */
        INTCON = (GLOBAL_INTERRUPT_ENABLE_MSK |
                  TIMER0_OVF_INTERRRUPT_ENABLE_MSK);

        /* set timer prediviser, timer source and prescaler */
        OPTION_REG = (CLK_SRC_INTERNAL_CLOCK_MSK |
                      PRESC_ASSIGN_TO_TIMER_MSK  |
                      PRESCALER_MSK);

        /* set timer period */
        TMR0 = (uint8_t)TIMER0_PERIOD;
    }
    
    return (TIMER_DRIVER_INITIALIZED == sTimerCtrl.eState);
}


bool bTimerRegCallback(cbkFunc_t Function, uint32_t u32PeriodMs)
{
    bool bRet = false;
    
    if ((Function != NULLPTR) && 
        (u32PeriodMs != TIMER_ZERO) && 
        (TIMER_DRIVER_INITIALIZED == sTimerCtrl.eState))
    {
        /* Function was registered */
        bRet = true;
        
        /* registration of callback function and it period */
        sTimerCtrl.Function    = Function;
        sTimerCtrl.u32PeriodMs = u32PeriodMs;
        sTimerCtrl.u32NextTime = u32PeriodMs + sTimerCtrl.u32TickMs;
    }
    
    return bRet;
}


bool bTimerUnregCallback(cbkFunc_t Function, uint32_t u32PeriodMs)
{
    bool bRet = false;
    
    if ((Function != NULLPTR) && 
        (u32PeriodMs != TIMER_ZERO) && 
        (TIMER_DRIVER_INITIALIZED == sTimerCtrl.eState))
    {
        /* Function was registered */
        bRet = true;
        
        /* registration of callback function and it period */
        sTimerCtrl.Function    = NULLPTR;
        sTimerCtrl.u32PeriodMs = TIMER_ZERO;
        sTimerCtrl.u32NextTime = TIMER_ZERO;
    }
    
    return bRet;
}


void vTimerDelayMs(uint32_t u32Delay)
{
    /* Recovery of current time */
    uint32_t u32CurrentTime = (uint32_t)~(sTimerCtrl.u32TickMs) + TIMER_ONE ;
    
    if (u32Delay != TIMER_ZERO)
    {   
        while(sTimerCtrl.u32TickMs + u32CurrentTime <= u32Delay);
    }
}


/** @brief timer0 interrupt handler    
  * @return none
 **/
void __interrupt() vTimer0InterruptHandler(void)
{
    if (READ_FLAG(INTCON, INTCON_TMR0IF_BIT))
    {     
        /* incrementation of ticks */
        sTimerCtrl.u32TickMs++;
        
        if ((sTimerCtrl.Function != NULLPTR) && 
            (sTimerCtrl.u32PeriodMs != TIMER_ZERO) &&
            (sTimerCtrl.u32TickMs >= sTimerCtrl.u32NextTime))
        {
            /* we compute the next period */
            sTimerCtrl.u32NextTime += sTimerCtrl.u32PeriodMs;

            /* We call the function */
            (sTimerCtrl.Function)();
        }
            
        /* set timer period */
        TMR0 = (uint8_t)TIMER0_PERIOD;
        
        /* Clear timer interrupt flag */
        CLEAR_FLAG(INTCON, INTCON_TMR0IF_BIT);
    }
}