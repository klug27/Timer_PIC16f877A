Timer 0 Library 
==================
These library is used for PIC16F877A and provides user to generate accurate delay using timer 0.

## Library routines

- bTimerInit
- bTimerRegCallback
- bTimerUnregCallback
- vTimerDelayMs

|Library routines| Prototypes|Descriptions|Returns|
|:---            |:---      |:---       |:---  |
|**bTimerInit**     |**bool bTimerInit(void);**  |This function ist use to initialize timer 0. |***true*** : The timer has been correctly initialized; <BR> ***false*** : The timer is not initialized; |
|**bTimerRegCallback**   |**bool bTimerRegCallback(cbkFunc_t Function, uint32_t u32PeriodMs);**   |This function ist used to insert callback function in the memory.|***true*** : The function has been correctly registered; otherwise it will returns **false**   |
|**bTimerUnregCallback**   |**bool bTimerUnregCallback(cbkFunc_t Function, uint32_t u32PeriodMs);**   |This function ist used to release callback function in the memory.|***true*** : The function has been correctly unregistered; otherwise it will returns **false**   |
|**vTimerDelayMs**   |**void vTimerDelayMs(uint32_t u32Delay);**   |This function delay in millisecond .|***nothing***|

## Library Example

```c
// Specify the XTAL crystal at 20Mhz
#define _XTAL_FREQ  20000000 
#include "config.h"
#include <xc.h>
#include "hw_desc_timer.h"

#define LED_PIN     PORTBbits.RB0
#define LED_DIR     TRISBbits.TRISB0
#define DIR_INPUT   1
#define DIR_OUTPUT  0
#define CLEAR_PIN   0
#define SET_PIN     1


/* Led toggle function */
void vLedToggle(void)
{
    LED_PIN = ~LED_PIN;
}


/*  main function */
void main(void) {

    /* Configuration of pin 0 of PORTB as output */
    LED_DIR = DIR_OUTPUT;

    /* Initialization of PORTB */
    LED_PIN = CLEAR_PIN;

    /* Initialization of timer 0 */
    bTimerInit();

    /* Registration of callback function */
    bTimerRegCallback(vLedToggle, 500);

    while(1)
    {
    }

    return;
}
```
