
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
					


//CMPE13 Support Library
#include "BOARD.h"
#include "Oled.h"
#include "Leds_Lab06.h"
#include "Ascii.h"
#include "OledDriver.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// **** Declare any datatypes here ****
struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};
struct Timer timer = {FALSE, 1};
// **** Define global, module-level, or external variables here ****
enum{
    LEFT, RIGHT
};												 

// **** Declare function prototypes ****


int main(void)
{
    BOARD_Init();
    OledInit();
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
    printf("Welcome to dyu33's lab6 part2 (bounce_switch).  Compiled on %s %s.\n",__TIME__,__DATE__);
    
    
							 
	while(1){
        //poll timer events and react if any occur
        /*initialize leds library
         * while true:
         *    if the timer event flag is set:
         *      if we?re at the last LED:
         *          reverse direction
         *          trigger next LED
         *      else:
         *          trigger next LED*/
        
        LEDS_INIT();
        static char dif = RIGHT;
        static uint8_t pattern = 0x80;
        
        if (timer.event == TRUE){                                               //if event is true
            timer.event = FALSE;                                                //reset it to false
            if (pattern == 0x01){                                               //if the pattern is at right edge
                if (dif == LEFT){
                    pattern <<= 1;                                              //it would move another way
                }
                else if(dif == RIGHT){                                          //change the direction
                    dif = LEFT;
                }
            }
            else if (pattern == 0x80){                                          // this is another event when it is left edge
                if (dif == LEFT){
                    dif = RIGHT;
                }
                else if(dif == RIGHT){
                    pattern >>= 1;
                }
            }
            else{                                                               //if it is in the middle should be move on
                if (dif == LEFT){
                    pattern <<= 1;
                }
                if(dif == RIGHT){
                    pattern >>= 1;
                } 
            }
        }

        LEDS_SET(pattern);
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
    timer.timeRemaining --;
    if (timer.timeRemaining < 0){
        timer.timeRemaining = SWITCH_STATES() + 1;
        timer.event = TRUE;                
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/									
	 
}