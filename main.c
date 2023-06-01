/*
 * File:   main.c
 * Author: VOUFO ASTRI
 *
 * Created on May 26, 2023, 1:49 PM
 */

// Specify the crystal frequency at 20Mhz
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


// Led toggle
void vLedToggle(void)
{
    LED_PIN = ~LED_PIN;
}

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

