// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

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



// **** Set any macros or preprocessor directives here ****



// **** Set any local typedefs here ****
typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
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
    uint16_t buttontime;
    Toastmode mode;
    Selector selectmode;
    uint16_t starttime;
    uint16_t freeRunningTimer;
    uint16_t ElapsedTime;
    //add more members to this struct
    //add cooktime
    //add cooktime remaining
    //add a temp
} OvenData;
OvenData ovenData;
// **** Declare any datatypes here ****
#define LONG_PRESS 5
#define Min_Time 1
#define Min_Temp 300
#define NUM_LED 8
#define OVEN_TOP_ON_5 "\x01\x01\x01\x01\x01"
#define OVEN_TOP_OFF_5 "\x02\x02\x02\x02\x02"
#define OVEN_BOTTOM_ON_5 "\x03\x03\x03\x03\x03"
#define OVEN_BOTTOM_OFF_5 "\x04\x04\x04\x04\x04"
#define DEGREE_SYMBOL "\xF8"

// **** Define any module-level, global, or external variables here ****
static uint8_t AdcEvent = FALSE;
static uint8_t ButtonEvent = FALSE;
static uint8_t TimerTickEvent = FALSE;

// **** Put any helper functions here ****
void updateLED(){
    //ADC% * numbers of LEDS
    if (ovenData.state == COOKING || ovenData.state == RESET_PENDING){
        (NUM_LED * ovenData.cooktimeremain) / ovenData.cooktime;
    }
    else{
        LEDS_SET(0);                         //LED
    }
    
    
}

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData){
    //update OLED here
    char display[100] = "";
    OledClear(OLED_COLOR_BLACK);
    
    int Temp = ovenData.temp;
    if (ovenData.mode == Bake){                                                 //setup selector cooking and reset pending
        char *mode = "BAKE";
  
        if (ovenData.state == SETUP){
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     | >TIME:%i:%i\n"
                    "|-----|  TEMP:%i%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_OFF_5, mode, ovenData.cooktime / 60, ovenData.cooktime % 60, ovenData.temp,DEGREE_SYMBOL, OVEN_BOTTOM_OFF_5);
        }
        if (ovenData.state == COOKING){
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     |  TIME:%i:%i\n"
                    "|-----|  TEMP:%i%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_ON_5, mode, ovenData.cooktimeremain / 60, ovenData.cooktimeremain % 60, ovenData.temp,DEGREE_SYMBOL, OVEN_BOTTOM_ON_5);
        }
        if (ovenData.state == SELECTOR_CHANGE_PENDING || ovenData.state == RESET_PENDING){
            if (ovenData.selectmode == Time){
                char *Time = '>';
                char *Temp = ' ';
            }
            else if (ovenData.selectmode == Temp){
                char *Time = ' ';
                char *Temp = '>';
            }
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     | %cTIME:%i:%i\n"
                    "|-----| %cTEMP:%i%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_ON_5, mode,Time, ovenData.cooktimeremain / 60, ovenData.cooktimeremain % 60,Temp, ovenData.temp,DEGREE_SYMBOL, OVEN_BOTTOM_ON_5);
        }
    } 
    if (ovenData.mode == Toast){                                                 //setup selector cooking and reset pending
        char *mode = "Toast";
  
        if (ovenData.state == SETUP){
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     | >TIME:%i:%i\n"
                    "|-----|  \n"
                    "|%s|  \n",
                    OVEN_TOP_OFF_5, mode, ovenData.cooktime / 60, ovenData.cooktime % 60, OVEN_BOTTOM_OFF_5);
        }
        if (ovenData.state == COOKING){
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     |  TIME:%i:%i\n"
                    "|-----|  \n"
                    "|%s|  \n",
                    OVEN_TOP_OFF_5, mode, ovenData.cooktimeremain / 60, ovenData.cooktimeremain % 60,  OVEN_BOTTOM_ON_5);
        }
    }
    if (ovenData.mode == Broil){                                                 //setup selector cooking and reset pending
        char *mode = "Broil";
  
        if (ovenData.state == SETUP){
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     | >TIME:%i:%i\n"
                    "|-----|  TEMP:%i%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_OFF_5, mode, ovenData.cooktime / 60, ovenData.cooktime % 60, ovenData.temp,DEGREE_SYMBOL, OVEN_BOTTOM_OFF_5);
        }
        if (ovenData.state == COOKING){
            sprintf(display,
                    "|%s|  MODE:%s\n"
                    "|     |  TIME:%i:%i\n"
                    "|-----|  TEMP:%i%sF\n"
                    "|%s|  \n",
                    OVEN_TOP_ON_5, mode, ovenData.cooktimeremain / 60, ovenData.cooktimeremain % 60, ovenData.temp,DEGREE_SYMBOL, OVEN_BOTTOM_OFF_5);
        }
    }
    OledDrawString(display);
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
    //write your SM logic here.
    switch (ovenData.state){
        case SETUP:
            /*
             * if ADCevent == TRUE
             *      update time
             *          only if the selector in at time selector
             *          total cook time gets saved here
             *      update temp
             *          only if the selector is at temp selector
             *          temp gets saved here
             * if buttonEvent & BTN_EVENT_4DOWN
             *      store free running timer to at start time variable (static uint_16)
             *      store total cook time
             *      ovenData.state = COOKING
             * else if buttonEvent & BTN_EVENT_3DOWN
             *      store free running timer to a start time variable (static uin16_t)
             *      ovenData.state = SELECTER_CHANGE_PENDING
             */
            if (AdcChanged){
                if (ovenData.selectmode == Time){
                    ovenData.cooktime = (AdcRead() >> 2) + Min_Time;
                    
                }
                if (ovenData.selectmode == Temp){
                    ovenData.temp = (AdcRead() >> 2) + Min_Temp;
                }
                updateOvenOLED(ovenData);                                               //inside the ())
            }
            if (ButtonsCheckEvents && BUTTON_EVENT_4DOWN){
                ovenData.starttime = ovenData.freeRunningTimer;
                updateOvenOLED(ovenData);
                updateLED(ovenData);
                ovenData.state = COOKING;

            }
            else if (ButtonsCheckEvents && BUTTON_EVENT_3DOWN){
                ovenData.starttime = ovenData.freeRunningTimer;
                ovenData.state = SELECTOR_CHANGE_PENDING;
            }
            break;
        case SELECTOR_CHANGE_PENDING:
            if (ButtonsCheckEvents && BUTTON_EVENT_3UP){
                ovenData.ElapsedTime = ovenData.freeRunningTimer - ovenData.starttime;
                if (ovenData.ElapsedTime < LONG_PRESS){                                  
                    ovenData.mode = (ovenData.mode + 1) % 3;                                             
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                }
                else{
                    ovenData.selectmode = (ovenData.selectmode + 1) % 2;
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                }
            }
            break;
        case COOKING:
            if (TimerTickEvent){
                if (ovenData.cooktime > 0){
                    ovenData.cooktimeremain = ovenData.cooktime - (ovenData.ElapsedTime / 5);
                    updateOvenOLED(ovenData);
                    updateLED(ovenData);
                    ovenData.state = COOKING;
                }
                else{
                     //starttime                                                           //reset setting
                    ovenData.cooktimeremain = ovenData.cooktime;
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                }
            }
            if (BUTTON_EVENT_4DOWN){
                ovenData.starttime = ovenData.freeRunningTimer;
                ovenData.state = RESET_PENDING;
            }
            break;
        case RESET_PENDING:
            if (BUTTON_EVENT_4UP){
                ovenData.state = COOKING;
            }
            if (TimerTickEvent){
                ovenData.ElapsedTime = ovenData.freeRunningTimer - ovenData.starttime;
                if (ovenData.ElapsedTime >= LONG_PRESS){
                                                                                //end cooking
                    //reset setting
                    ovenData.cooktimeremain = ovenData.cooktime;
                    updateOvenOLED(ovenData);
                    updateLED(ovenData);
                    ovenData.state = SETUP;
                }
                else{
                    updateOvenOLED(ovenData);
                    updateLED(ovenData);
                    ovenData.state = RESET_PENDING;
                }
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
    ovenData.cooktimeremain = 0;
    //updateOvenOLED(ovenData);
    while (1){
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags
        if (AdcEvent){                                                          //question
            
            runOvenSM();
            AdcEvent = FALSE;
            //updateOvenOLED(ovenData);
            //updateLED(ovenData);
            
        }
        if (ButtonEvent){
            runOvenSM();
            ButtonEvent = FALSE;
            //updateOvenOLED(ovenData);
            //updateLED(ovenData);
        }
        if (TimerTickEvent){
            runOvenSM();
            TimerTickEvent = FALSE;
            //updateOvenOLED(ovenData);
            //updateLED(ovenData);
        }
    };
    //three different if statement
    /*
        if ADC event{
     *      on event, run runOvenSM
     *      clear event flags
     *      updateLEDS
     *      updateOLED
     *  if Button event
     *      on event, run runOvenSM
     *      clear event flags
     *      updateLEDS
     *      updateOLED
     *  if Timer Tick event
     *      on event, run runOvenSM
     *      clear event flags
     *      updateLEDS
     *      updateOLED
     */
}


/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;
    //free run timer
    ovenData.freeRunningTimer ++;
    //add event-checking code here
    if (ovenData.state == COOKING || ovenData.state == RESET_PENDING){
        TimerTickEvent = TRUE;
    }
    
}


/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;
    if (ButtonsCheckEvents){
        ButtonEvent = TRUE;
    }
    if (AdcChanged){
        AdcEvent = TRUE;
    }
    //add event-checking code here
    //check button event
    //check adc event
    //save adc reading as a var
}