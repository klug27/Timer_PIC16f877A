Timer 0 Library 
==================
These library is used for PIC16F877A and provides user to generate accurate delay using timer 0.

## Library routines

# Timer0 Library

This library is written in **C** for the **PIC16F877A** and is designed to generate accurate delays using **Timer0**. It is compatible with **MPLAB** and relies on **direct register access** for maximum control and performance.

## Library Routines

- `bTimerInit`
- `bTimerRegCallback`
- `bTimerUnregCallback`
- `vTimerDelayMs`

| Library Routine         | Prototype                                                                 | Description                                                                 | Return Value |
|------------------------|---------------------------------------------------------------------------|-----------------------------------------------------------------------------|--------------|
| **bTimerInit**         | `bool bTimerInit(void);`                                                  | Initializes Timer0 and prepares it for use.                                 | `true` if the timer was successfully initialized; <br> `false` otherwise. |
| **bTimerRegCallback**  | `bool bTimerRegCallback(cbkFunc_t Function, uint32_t u32PeriodMs);`       | Registers a callback function to be triggered periodically by Timer0.       | `true` if the function was successfully registered; <br> `false` otherwise. |
| **bTimerUnregCallback**| `bool bTimerUnregCallback(cbkFunc_t Function, uint32_t u32PeriodMs);`     | Unregisters a previously registered callback function.                       | `true` if the function was successfully unregistered; <br> `false` otherwise. |
| **vTimerDelayMs**      | `void vTimerDelayMs(uint32_t u32Delay);`                                  | Generates a blocking delay in milliseconds using Timer0.                    | None |


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
    /* Toggle led every 500ms */
    bTimerRegCallback(vLedToggle, 500);

    while(1)
    {
    }

    return;
}
```
