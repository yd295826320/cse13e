// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Oled.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****

#define TIMER_FREQ 38
#define TIMER_A 2 * TIMER_FREQ
#define TIMER_B 3 * TIMER_FREQ
#define TIMER_C 5 * TIMER_FREQ

struct Timer timerA = {FALSE, TIMER_A};
struct Timer timerB = {FALSE, TIMER_B};
struct Timer timerC = {FALSE, TIMER_C};


// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();
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
    printf("Welcome to dyu33's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);

    while (1) {
        //poll timer A
            //react to timer A events
            //clear timer A event flag
        /*initialize leds library 
         * initialize timers
         * while true:
         *  if timerA event flag is set:
         *      clear timerA event flag 
         *      print A
         *      toggle LED 1
         *  if timerB event flag is set:. . .*/
        uint8_t LED1;
        uint8_t LED2;
        uint8_t LED3;
        while(TRUE){
            if (timerA.event == TRUE){
                timerA.event = FALSE;
                printf("A ");
                //Timer.timeRemaining = timerA.timeRemaining  
                LED1 = LEDS_GET();
                LEDS_SET(LED1 ^ 0x01);
                
            }
            if (timerB.event == TRUE){
                timerB.event = FALSE;
                printf("B ");
                LED2 = LEDS_GET();
                LEDS_SET(LED2 ^ 0x02);
            }
            if (timerC.event == TRUE){
                timerC.event = FALSE;
                printf("C ");
                LED3 = LEDS_GET();
                LEDS_SET(LED3 ^0x04);
            }
            
        }
        
            
            
        
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    
    //update timerA
    //if timerA has counted down,
        //generate timerA event
        //reset timerA
    /*Clear interrupt flag
     * Decrement timerA?s timeRemaining
     * If TimerA?s timeRemaining is 0:
     *      Set TimerA?s event flag 
     *      Reset TimerA?s timeRemaining
     * If TimerB?s timeRemaining is 0:. . . 
     */
    
    timerA.timeRemaining--;
    if (timerA.timeRemaining == 0){
        timerA.event = TRUE;
        timerA.timeRemaining = TIMER_A;
    }
    timerB.timeRemaining--;
    if (timerB.timeRemaining == 0){
        timerB.event = TRUE;
        timerB.timeRemaining = TIMER_B;
    }
    timerC.timeRemaining--;
    if (timerC.timeRemaining == 0){
        timerC.event = TRUE;
        timerC.timeRemaining = TIMER_C;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}