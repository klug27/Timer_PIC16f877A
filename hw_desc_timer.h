/* 
 * File:   hw_desc_timer0.h
 * Author: VOUFO BOGNING ULRICH ASTRI
 *
 * Created on 26 mai 2023, 14:46
 */

#ifndef HW_DESC_TIMER_H
#define	HW_DESC_TIMER_H

/******************************************************************************
* @file		hw_desc_timer0.h
* @author	VOUFO ASTRI
* @date		26.05.2023
*******************************************************************************/

#include <stdbool.h>

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

/** timer ID */
typedef enum eTimerID_tTag
{
    TIMER_ID0 = 0,   /**< id for timer0 */
    TIMER_ID1 = 1,   /**< id for timer1 */
    TIMER_ID2 = 2,   /**< id for timer2 */
            
    TIMER_ID_MAX
} eTimerID_t;


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
bool bTimerInit(eTimerID_t eTimerNumber);


/** @brief this function allow to insert callback function in the memory
  * @param [IN]  Function     : pointer to data     
  * @param [IN]  u32PeriodMs  : function is called during these period    
  * @return true if the function was successfully registered, false otherwise
 **/
bool bTimer0InsertCallback(cbkFunc_t Function, uint32_t u32PeriodMs);


/** @brief this function is use for delay
  * @param [IN]  u32Delay     : delay (millisecond)    
  * @return none
 **/
void vTimer0DelayMs(uint32_t u32Delay);

#endif	

