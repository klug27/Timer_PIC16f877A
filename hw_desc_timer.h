

#ifndef HW_DESC_TIMER_H
#define	HW_DESC_TIMER_H

/******************************************************************************
* @file		hw_desc_timer.h
* @author	VOUFO ASTRI
* @date		26.05.2023
*******************************************************************************/

#include <stdbool.h>
#include <stdint.h>

 /****************************************************************************
  * 
 *                                                                           *                                     
 *  D E F I N I T I O N                                                      *                                     
 *                                                                           *                                     
 *****************************************************************************/


 /****************************************************************************
 *                                                                           *                                     
 *  T Y P E D E F                                                            *                                     
 *                                                                           *                                     
 *****************************************************************************/

typedef void (*cbkFunc_t)(void); // Callback function 

 /****************************************************************************
 *                                                                           *                                     
 *  E N U M E R A T I O N                                                    *                                     
 *                                                                           *                                     
 *****************************************************************************/


 /****************************************************************************
 *                                                                           *                                     
 *  S T R U C T U R E                                                        *                                     
 *                                                                           *                                     
 *****************************************************************************/



 /****************************************************************************
 *                                                                           *                                     
 *  P U B L I C  F U N C T I O N  I M P L E M E N T A T I O N                *                                     
 *                                                                           *                                     
 *****************************************************************************/

/** @brief this function enable timer 

  * @return true if timer was successfully initialized, false otherwise
 **/
bool bTimerInit(void);


/** @brief this function allow to insert callback function in the memory
  * @param [IN]  Function     : callback function      
  * @param [IN]  u32PeriodMs  : function is called during these period    
  * @return true if the function was successfully registered, false otherwise
 **/
bool bTimerRegCallback(cbkFunc_t Function, uint32_t u32PeriodMs);


/** @brief this function allow to release callback function to the memory
  * @param [IN]  Function     : callback function     
  * @param [IN]  u32PeriodMs  : function is called during these period    
  * @return true if the function was successfully registered, false otherwise
 **/
bool bTimerUnregCallback(cbkFunc_t Function, uint32_t u32PeriodMs);


/** @brief this function is use for delay
  * @param [IN]  u32Delay     : delay (millisecond)    
  * @return none
 **/
void vTimerDelayMs(uint32_t u32Delay);

#endif	

