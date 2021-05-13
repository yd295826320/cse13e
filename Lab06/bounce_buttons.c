// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"
#include "Oled.h"
#include "Leds_Lab06.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
static uint8_t bottomEvent = BUTTON_EVENT_NONE;
// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();
    ButtonsInit();
    LEDS_INIT();
    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to dyu33's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);
    /*initialize buttons library
     * while true:
     *      if a button event flag is set:
     *          store the current switch positions
        *      if Switch 1 is on and Button up event:
        *          toggle appropriate LEDs for that button
        *      else if Switch 1 is off and Button down event:
        *          toggle appropriate LEDs for that button
     * repeat for other buttons 
     * clear button event flag */
    uint8_t LED1 = 0x01;
    uint8_t LED2 = 0x02;
    uint8_t LED3 = 0x04;
    uint8_t LED4 = 0x08;
    uint8_t LED5 = 0x10;
    uint8_t LED6 = 0x20;
    uint8_t LED7 = 0x40;
    uint8_t LED8 = 0x80;
    ButtonsInit();
    while (TRUE){
        if (bottomEvent != BUTTON_EVENT_NONE){
            uint8_t switchesState = SWITCH_STATES();
            if ((switchesState & SWITCH_STATE_SW1) & BUTTON_EVENT_1UP){
                LEDS_SET(LED1);
                LEDS_SET(LED1 ^ BTN1);
                LEDS_SET(LED2);
                LEDS_SET(LED2 ^ BTN1);
            }
            else if (!(switchesState & SWITCH_STATE_SW1) & BUTTON_EVENT_1DOWN){
                LEDS_SET(LED1);
                LEDS_SET(LED1 ^ BTN1);
                LEDS_SET(LED2);
                LEDS_SET(LED2 ^ BTN1);
            }
            else if ((switchesState & SWITCH_STATE_SW2) & BUTTON_EVENT_2UP){
                LEDS_SET(LED3);
                LEDS_SET(LED3 ^ BTN2);
                LEDS_SET(LED4);
                LEDS_SET(LED4 ^ BTN2);
            }
            else if (!(switchesState & SWITCH_STATE_SW2) & BUTTON_EVENT_2DOWN){
                LEDS_SET(LED3);
                LEDS_SET(LED3 ^ BTN2);
                LEDS_SET(LED4);
                LEDS_SET(LED4 ^ BTN2);
            }
            else if ((switchesState & SWITCH_STATE_SW3) & BUTTON_EVENT_3UP){
                LEDS_SET(LED5);
                LEDS_SET(LED5 ^ BTN3);
                LEDS_SET(LED6);
                LEDS_SET(LED6 ^ BTN3);
            }
            else if (!(switchesState & SWITCH_STATE_SW3) & BUTTON_EVENT_3DOWN){
                LEDS_SET(LED5);
                LEDS_SET(LED5 ^ BTN3);
                LEDS_SET(LED6);
                LEDS_SET(LED6 ^ BTN3);
            }
            else if ((switchesState & SWITCH_STATE_SW4) & BUTTON_EVENT_4UP){
                LEDS_SET(LED7);
                LEDS_SET(LED8 ^ BTN4);
                LEDS_SET(LED7);
                LEDS_SET(LED8 ^ BTN4);
            }
            else if (!(switchesState & SWITCH_STATE_SW4) & BUTTON_EVENT_4DOWN){
                LEDS_SET(LED7);
                LEDS_SET(LED8 ^ BTN4);
                LEDS_SET(LED7);
                LEDS_SET(LED8 ^ BTN4);
            }
            bottomEvent = BUTTON_EVENT_NONE;
        }
    }
    
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    static bottomEvent = ButtonsCheckEvents;
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}