
#include <stdio.h>
					


//CMPE13 Support Library
#include "BOARD.h"
#include "Oled.h"
#include "Leds_Lab06.h"
#include "Ascii.h"
#include "OledDriver.h"
#include "Buttons.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>


/**
 * This function initializes the proper pins such that the buttons 1-4 may be used by modifying
 * the necessary bits in TRISD/TRISF. Only the bits necessary to enable the 1-4 buttons are
 * modified, so that this library does not interfere with other libraries.
 */
void ButtonsInit(void){
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
}

#define MASK_BUTTON_1_DOWN 0x1111
#define MASK_BUTTON_2_DOWN 0x2222
#define MASK_BUTTON_3_DOWN 0x4444
#define MASK_BUTTON_4_DOWN 0x8888

static int Button1_prev;

/**
 * ButtonsCheckEvents function checks the current button states and returns
 *  any events that have occured since its last
 * call.  This function should be called repeatedly in a Timer ISR, though it can
 * be called in main() during testing.
 *
 * In normal use, this function should only be used after ButtonsInit().
 * 
 * This function should assume that the buttons start in an off state with 
 * value 0. Therefore if no buttons are
 * pressed when ButtonsCheckEvents() is first called, 
 * BUTTONS_EVENT_NONE should be returned. 
 * 
 * @return  Each bit of the return value corresponds to one ButtonEvent flag,
 *          as described in Buttons.h.  If no events are detected, BUTTONS_EVENT_NONE is returned.
 * 
 * Note that more than one event can occur simultaneously, though this situation is rare.
 * To handle this, the output should be a bitwise OR of all applicable event flags. 
 * For example, if button 1 was released at the same time that button 2 was pressed,
 * this function should return (BUTTON_EVENT_1UP | BUTTON_EVENT_2DOWN) 
 * 
 */
uint8_t ButtonsCheckEvents(void){
    /*if (BUTTONS_DEBOUNCE_PERIOD > 0){
        BUTTONS_DEBOUNCE_PERIOD--;
        return ButtonsCheckEvents;
    }*/
            
    static uint32_t prev_var = 0;
    prev_var = (prev_var << 4) | BUTTON_STATES();
    uint8_t returnButtonevent = BUTTON_EVENT_NONE;
    static uint8_t prevButtonevent = BUTTON_EVENT_NONE;
    
    if ((prev_var & MASK_BUTTON_1_DOWN) && !(prevButtonevent & BUTTON_EVENT_1DOWN)){
        returnButtonevent |= BUTTON_EVENT_1DOWN;
        prevButtonevent |= BUTTON_EVENT_1DOWN;
    }
    if (!(prev_var & MASK_BUTTON_1_DOWN) && (prevButtonevent & BUTTON_EVENT_1DOWN)){
        returnButtonevent |= BUTTON_EVENT_1UP;
        prevButtonevent |= BUTTON_EVENT_1UP;
    }
    
    if ((prev_var & MASK_BUTTON_2_DOWN) && !(prevButtonevent & MASK_BUTTON_2_DOWN)){
        returnButtonevent |= BUTTON_EVENT_2DOWN;
        prevButtonevent |= BUTTON_EVENT_2DOWN;
    }
    if (!(prev_var & MASK_BUTTON_2_DOWN) && (prevButtonevent & MASK_BUTTON_2_DOWN)){
        returnButtonevent |= BUTTON_EVENT_2UP;
        prevButtonevent |= BUTTON_EVENT_2UP;
    }
    
    if ((prev_var & MASK_BUTTON_3_DOWN) && !(prevButtonevent & BUTTON_EVENT_2DOWN)){
        returnButtonevent |= BUTTON_EVENT_3DOWN;
        prevButtonevent |= BUTTON_EVENT_3DOWN;
    }
    if (!(prev_var & MASK_BUTTON_3_DOWN) && (prevButtonevent & BUTTON_EVENT_2DOWN)){
        returnButtonevent |= BUTTON_EVENT_3UP;
        prevButtonevent |= BUTTON_EVENT_3UP;
    }
    
    if ((prev_var & MASK_BUTTON_4_DOWN) && !(prevButtonevent & BUTTON_EVENT_4DOWN)){
        returnButtonevent |= BUTTON_EVENT_4DOWN;
        prevButtonevent |= BUTTON_EVENT_4DOWN;
    }
    if (!(prev_var & MASK_BUTTON_4_DOWN) && (prevButtonevent & BUTTON_EVENT_4DOWN)){
        returnButtonevent |= BUTTON_EVENT_4UP;
        prevButtonevent |= BUTTON_EVENT_4UP;
    }
    
    
    return returnButtonevent;
}
