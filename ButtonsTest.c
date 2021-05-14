// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"
#include "Oled.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
//static uint8_t bottomEvent = BUTTON_EVENT_NONE;
// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
struct ButtonState{
    uint8_t event; 
    uint8_t states; 
};
struct ButtonState bottomEvent = {0x00,FALSE};
// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();
    ButtonsInit();
    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
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
    printf("Welcome to dyu33's lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);

    
    printf("Please press some buttons!\n");
    
    while(1){
        char bottom1[] = "----";
        char bottom2[] = "----";
        char bottom3[] = "----";
        char bottom4[] = "----";
        
        
        if (bottomEvent.states == TRUE){
            if (bottomEvent.event & BUTTON_EVENT_1UP) {
                sprintf(bottom1, "UP"); 
            } 
            if (bottomEvent.event & BUTTON_EVENT_1DOWN) {
                sprintf(bottom1, "DOWN");
            } 
            if (bottomEvent.event & BUTTON_EVENT_2UP) {
                sprintf(bottom2, "UP"); 
            } 
            if (bottomEvent.event & BUTTON_EVENT_2DOWN) {
                sprintf(bottom2, "DOWN");
            } 
            if (bottomEvent.event & BUTTON_EVENT_3UP) {
                sprintf(bottom3, "UP"); 
            } 
            if (bottomEvent.event & BUTTON_EVENT_3DOWN) {
                sprintf(bottom3, "DOWN");
            } 
            if (bottomEvent.event & BUTTON_EVENT_4UP) {
                sprintf(bottom4, "UP"); 
            } 
            if (bottomEvent.event & BUTTON_EVENT_4DOWN) {
                sprintf(bottom4, "DOWN");
            } 
            printf("EVENT:1.%s 2.%s 3.%s 4.%s\n",bottom1,bottom2,bottom3,bottom4);
            bottomEvent.states = FALSE;
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
    uint8_t Event = ButtonsCheckEvents();
    if(Event !=  BUTTON_EVENT_NONE && bottomEvent.states == FALSE ){
        bottomEvent.event = Event;
        bottomEvent.states = TRUE;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}
