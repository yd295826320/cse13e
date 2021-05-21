// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
//CSE13E Support Library
#include "BOARD.h"
#include "Adc.h"
#include "Ascii.h"
#include "Buttons.h"
#include "Leds.h"
#include "Oled.h"
#include "OledDriver.h"


// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>


#define TIMER_2HZ_RESET() (TMR1 = 0)
// **** Set any local typedefs here ****
typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING, EXTRA_CREDIT
} OvenState;

typedef enum {
    Time, Temp
}Selector;

//typedef enum{
//    AdcEvent, ButtonEvent, TimerTickEvent
//}Event;
//enum for time and enum for temp

typedef enum {
    Bake, Toast, Broil
}Toastmode;

typedef struct {
    OvenState state;
    uint16_t cooktime;
    uint16_t cooktimeremain;
    uint16_t temp;
    Toastmode mode;
    Selector selectmode;
    uint16_t buttonpress;
    uint16_t freeRunningTimer;
    uint16_t ElapsedTime;
    uint16_t NUM_SW;
    
    //add more members to this struct
    //add cooktime
    //add cooktime remaining
    //add a temp
} OvenData;
static OvenData ovenData;
// **** Declare any datatypes here ****
#define LONG_PRESS 5
#define Min_Time 1
#define Min_Temp 300
#define NUM_LED 8
#define LED_ON 0xFF
#define OVEN_TOP_ON_5 "\x01\x01\x01\x01\x01"
#define OVEN_TOP_OFF_5 "\x02\x02\x02\x02\x02"
#define OVEN_BOTTOM_ON_5 "\x03\x03\x03\x03\x03"
#define OVEN_BOTTOM_OFF_5 "\x04\x04\x04\x04\x04"
#define DEGREE_SYMBOL "\xF8"

// **** Define any module-level, global, or external variables here ****
//varibles
static uint16_t LED;
static char current_LED;
static uint16_t init_temp;
static uint16_t TimerCountdown = 0;
static uint16_t freerunningtimer_init = 0;
// Events
static uint8_t AdcEvent = FALSE;
static uint8_t ButtonEvent = BUTTON_EVENT_NONE;
static uint16_t TimerTickEvent = FALSE;
static uint8_t inverse = FALSE;
// **** Put any helper functions here ****


/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData){
    //update OLED here
    char display[100] = "";
    
    
    if (ovenData.mode == Bake){                                                 //setup selector cooking and reset pending
        char *mode = "BAKE";
        if (ovenData.state == SETUP || ovenData.state == SELECTOR_CHANGE_PENDING){
            if (ovenData.selectmode == Time){
                sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     | >TIME: %i:%i\n"
                    "|-----|  TEMP:%i%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_OFF_5, mode, ovenData.cooktime / 60, ovenData.cooktime % 60, ovenData.temp,DEGREE_SYMBOL, OVEN_BOTTOM_OFF_5);
            }
            else{
                sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     |  TIME: %i:%i\n"
                    "|-----| >TEMP:%i%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_OFF_5, mode, ovenData.cooktime / 60, ovenData.cooktime % 60, ovenData.temp,DEGREE_SYMBOL, OVEN_BOTTOM_OFF_5);
            }
            
        }
        if (ovenData.state == COOKING){
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     |  TIME: %i:%i\n"
                    "|-----|  TEMP:%i%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_ON_5, mode, ovenData.cooktimeremain / 60, ovenData.cooktimeremain % 60, ovenData.temp,DEGREE_SYMBOL, OVEN_BOTTOM_ON_5);
        }
        
    } 
    if (ovenData.mode == Toast){                                                 //setup selector cooking and reset pending
        char *mode = "Toast";
        if (ovenData.state == SETUP || ovenData.state == SELECTOR_CHANGE_PENDING){
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     |  TIME: %i:%i\n"
                    "|-----|  \n"
                    "|%s|  \n",
                    OVEN_TOP_OFF_5, mode, ovenData.cooktime / 60, ovenData.cooktime % 60, OVEN_BOTTOM_OFF_5);
        }
        else{
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     |  TIME: %i:%i\n"
                    "|-----|  \n"
                    "|%s|  \n",
                    OVEN_TOP_OFF_5, mode, ovenData.cooktimeremain / 60, ovenData.cooktimeremain % 60,  OVEN_BOTTOM_ON_5);
        }
    }
    if (ovenData.mode == Broil){                                                 //setup selector cooking and reset pending
        char *mode = "Broil";
        if (ovenData.state == SETUP || ovenData.state == SELECTOR_CHANGE_PENDING){
            if (ovenData.selectmode == Time){
                sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     | >TIME: %i:%i\n"
                    "|-----|  TEMP:500%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_OFF_5, mode, ovenData.cooktime / 60, ovenData.cooktime % 60,DEGREE_SYMBOL, OVEN_BOTTOM_OFF_5);
            }
        }
            else{
                sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     |  TIME: %i:%i\n"
                    "|-----|  TEMP:500%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_ON_5, mode, ovenData.cooktimeremain / 60, ovenData.cooktimeremain % 60,DEGREE_SYMBOL, OVEN_BOTTOM_OFF_5);
            }
            
        
    }
    OledClear(OLED_COLOR_BLACK);
    OledDrawString(display);
    if (ovenData.state == EXTRA_CREDIT) {                                       //if the state is at the end of cooking
        if (inverse) {
            OledSetDisplayNormal();                                             //if it is true then display normally
        } 
        else {
            OledSetDisplayInverted();                                           //if is false then display the inverse
        }
    }
    OledUpdate();
    
    //row1
    //row2
    //row3
    //row4
//    sprintf(bigString, "%d%s%s%s", row1, row2, row3, row4)
    
    
    // selector either for space or arrow
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void)
{
    switch (ovenData.state){
        case SETUP:
           if (AdcChanged){
                if (ovenData.mode == Bake && ovenData.selectmode == Temp) {
                    ovenData.temp = (AdcRead() >> 2) + Min_Temp;
                } else {
                    ovenData.cooktime = (AdcRead() >> 2) + Min_Time;
                    ovenData.cooktimeremain = ovenData.cooktime;
                }
                updateOvenOLED(ovenData);                                               //inside the ())
            }
           if (ButtonEvent & BUTTON_EVENT_3DOWN){
                ovenData.buttonpress = ovenData.freeRunningTimer;
                ovenData.state = SELECTOR_CHANGE_PENDING;
            }
            if (ButtonEvent & BUTTON_EVENT_4DOWN){
                freerunningtimer_init = ovenData.freeRunningTimer;
                updateOvenOLED(ovenData);
                LEDS_SET(0xFF);                                                 //turn on all the light
                LED = (ovenData.cooktime * 5) / 8;                              //calculate what is 1/8 of the cooktime
                TimerCountdown = 0;                                             //initialize the countdown
                ovenData.state = COOKING;
            }
            
            break;
        case SELECTOR_CHANGE_PENDING:
            if (ButtonEvent & BUTTON_EVENT_3UP){
                ovenData.ElapsedTime = ovenData.freeRunningTimer - ovenData.buttonpress;
                
                if (ovenData.ElapsedTime < LONG_PRESS){                         //if it is a quick press         
                    if (ovenData.mode == Broil){                                //when it is at the broil mode turn to bake mode
                        ovenData.mode = Bake;
                    }
                    else{                                                       //otherwise it would just turn to next one
                        ovenData.mode++;
                    }
                    if (ovenData.mode == Broil){                                //when it is Broil the temp is alway 500
                        init_temp = ovenData.temp;
                        ovenData.temp = 500;
                    } 
                    if (ovenData.mode == Bake){                                 //Bake mode temp would change witht the adc
                        ovenData.temp = init_temp;
                    }                                             
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                }
                else{
                    if (ovenData.selectmode == Time){                           //when it is time switch to temp
                        ovenData.selectmode = Temp;
                    }
                    else{
                        ovenData.selectmode = Time;
                    }
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                }
            }
            break;
        case COOKING:
            if (TimerTickEvent){
                TimerCountdown++;                                               //countint how many times does timertickevent happens
                if (TimerCountdown == LED){                                     //when the event happens with the 8 times and it is should be take off one LED
                    TimerCountdown = 0;
                    current_LED = LEDS_GET();
                    LEDS_SET(current_LED << 1);
                }
                
                
                if (ovenData.cooktimeremain == 0) {                             //when the countdown reach 0, it should go to extra creidt mode and update the LED
                    ovenData.cooktimeremain = ovenData.cooktime;                //reset to the orignal data
                    ovenData.state = EXTRA_CREDIT;
                    updateOvenOLED(ovenData);
                    LEDS_SET(0x00);
                    break;
                }
                if ((ovenData.freeRunningTimer - freerunningtimer_init) % 5 == 0) {  //for every 5 is one sec which should count down one and update the OLED
                    ovenData.cooktimeremain--;
                    updateOvenOLED(ovenData);
                }
            }
            if (ButtonEvent & BUTTON_EVENT_4DOWN){                              //when the button 4 is down it goes to Reset pending
                ovenData.buttonpress = ovenData.freeRunningTimer;
                ovenData.state = RESET_PENDING;
            }
            break;
        case RESET_PENDING:
            if (TimerTickEvent){                                                //same as cooking keep tracks of the timertickevent
                TimerCountdown++;
                if (TimerCountdown == LED){                                     //it will turn off when it is equal to the number of timertickevent                        
                    current_LED = LEDS_GET();
                    TimerCountdown = 0;
                    LEDS_SET(current_LED << 1);
                }
                if ((ovenData.freeRunningTimer - freerunningtimer_init) % 5 == 0) { //count down cooking time left
                    if (ovenData.cooktimeremain) {
                        ovenData.cooktimeremain--;
                        updateOvenOLED(ovenData);
                    }
                }
                ovenData.ElapsedTime = ovenData.freeRunningTimer - ovenData.buttonpress;
                if (ovenData.ElapsedTime >= LONG_PRESS){
                                                                                //end cooking
                    //reset setting
                    ovenData.cooktimeremain = ovenData.cooktime;
                    ovenData.state = SETUP;
                    updateOvenOLED(ovenData);
                    LEDS_SET(0x00);
                    
                }
                
                
            }
            if (ButtonEvent & BUTTON_EVENT_4UP ) { 
                    ovenData.state = COOKING;
            }
            
            break;
        case EXTRA_CREDIT:
            if (TimerTickEvent) {                                               //when the cooking is down if the inverse is False set it to True and if it's true then set to False
                if (inverse) {
                    inverse = FALSE;
                } 
                else {
                    inverse = TRUE;
                }
                updateOvenOLED(ovenData);                       
            }
            if (ButtonEvent & BUTTON_EVENT_4UP) {                               //when we press the button 4 again it will return to set up 
                inverse = TRUE;                                                 //and reset it to True.
                ovenData.state = SETUP;
                updateOvenOLED(ovenData);
            }
            break;
        //default:
            //print ot OLED an error occur
            //and to restart the oven
            //while(1);
            //break;
          
            
        
    }
}


int main()
{
    BOARD_Init();
    LEDS_INIT();
    AdcInit();
    ButtonsInit();
    OledInit();
     //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">
    
    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>
   
    printf("Welcome to dyu33's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    ovenData.state = SETUP;
    ovenData.selectmode = Time;
    ovenData.mode = Bake;
    ovenData.cooktimeremain = 1;
    ovenData.cooktime = 1;
    ovenData.buttonpress = 0;
    ovenData.temp = 350;
    while (1){
        
     if (AdcEvent){ 
            runOvenSM();
            AdcEvent = FALSE;
            
            
        }
        if (ButtonEvent != BUTTON_EVENT_NONE){
            runOvenSM();
            ButtonEvent = BUTTON_EVENT_NONE;
            
        }
        if (TimerTickEvent){
            runOvenSM();
            TimerTickEvent = FALSE;
            
        }
    };
   
}


/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;
    //free run timer
    ovenData.freeRunningTimer ++;
    //add event-checking code here
    
    TimerTickEvent = TRUE;
    
}


/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
   IFS0CLR = 1 << 8;
    
    
    ButtonEvent = ButtonsCheckEvents();
    AdcEvent = AdcChanged();
    
    
    
}
