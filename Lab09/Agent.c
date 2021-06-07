#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "BattleBoats.h"
#include "Agent.h"
#include "Field.h"
#include "Negotiation.h"
#include "FieldOled.h"
#include "Oled.h"
#include "BOARD.h"

static Field own_field;
static Field opp_field;
static AgentState currentState;
//nagotiationDate Hash for yourself and oppo
static NegotiationData hash,A,B;
static NegotiationOutcome coinflip;
static uint8_t turnnum;
//field oled turn
static FieldOledTurn whoseturn;
static GuessData guessData;
static GuessData opp_guess;
//static uint16_t Hash_a;
static SquareStatus previous;
static uint8_t battle_result;

#define defeat 0
#define victory 1

void NegotiationScreen(void);
void  battle(void);
void  screen(void);
/**
 * The Init() function for an Agent sets up everything necessary for an agent before the game
 * starts.  At a minimum, this requires:
 *   -setting the start state of the Agent SM.
 *   -setting turn counter to 0
 * If you are using any other persistent data in Agent SM, that should be reset as well.
 * 
 * It is not advised to call srand() inside of AgentInit.  
 *  */
void AgentInit(void){
    //init Agent Status
    //set your and oppo hashes
    currentState = AGENT_STATE_START;
    A = rand();
    hash = NegotiationHash(A);
    B = rand();
    turnnum = 0;
}

/**
 * AgentRun evolves the Agent state machine in response to an event.
 * 
 * @param  The most recently detected event
 * @return Message, a Message struct to send to the opponent. 
 * 
 * If the returned Message struct is a valid message
 * (that is, not of type MESSAGE_NONE), then it will be
 * passed to the transmission module and sent via UART.
 * This is handled at the top level! AgentRun is ONLY responsible 
 * for generating the Message struct, not for encoding or sending it.
 */
Message AgentRun(BB_Event event){
    //state machine
    BOARD_Init();
    OledInit();
    
    Message Messageout = {MESSAGE_NONE, 0, 0, 0};
    if (event.type == BB_EVENT_RESET_BUTTON){
        AgentInit();
        NegotiationScreen();
        return Messageout;
    }
    if (event.type == BB_EVENT_ERROR){
        //errorScreen
        OledDrawString("ERRORS!\n");
        OledUpdate();
        
        Messageout.type = MESSAGE_ERROR;
        Messageout.param0 = event.param0;
        Messageout.param1 = event.param1;
        Messageout.param2 = event.param2;
        //set error message
        //return it
        return Messageout;
    }
    switch(currentState){
        case AGENT_STATE_START:
            if (event.type == BB_EVENT_START_BUTTON){
                NegotiationScreen();
                currentState = AGENT_STATE_CHALLENGING;
                A = rand();
                hash = NegotiationHash(A);
                Messageout.type = MESSAGE_CHA;
                Messageout.param0 = hash;
                FieldInit(&own_field,&opp_field);
                FieldAIPlaceAllBoats(&own_field);
                
            }
            if(event.type == BB_EVENT_CHA_RECEIVED){
                NegotiationScreen();
                currentState = AGENT_STATE_ACCEPTING;
                hash = event.param0;
                B = rand();
                Messageout.type = MESSAGE_ACC;
                Messageout.param0 = B;
                Messageout.param1 = 0;
                Messageout.param2 = 0;
                FieldInit(&own_field,&opp_field);
                FieldAIPlaceAllBoats(&own_field);
            }
            break;
        case AGENT_STATE_CHALLENGING:
            if (event.type == BB_EVENT_ACC_RECEIVED){
                
                coinflip = NegotiateCoinFlip(A, B);
                if (coinflip == HEADS){                                   //question
                    currentState = AGENT_STATE_WAITING_TO_SEND;
                    whoseturn = FIELD_OLED_TURN_MINE;
                    screen();
                }
                else{
                    currentState = AGENT_STATE_DEFENDING;
                    whoseturn = FIELD_OLED_TURN_THEIRS;
                }
                Messageout.type = MESSAGE_REV;
                B = event.param0;
                Messageout.param0 = A;
                return Messageout;
            }
            break;
        case AGENT_STATE_ACCEPTING:
            if (event.type == BB_EVENT_REV_RECEIVED){
                A = event.param0;
                screen();
                uint8_t checkcheat = NegotiationVerify(A,hash);
                if (checkcheat == FALSE){
                    Messageout.type = -1;//error Message
                    Messageout.param0 = A;
                    Messageout.param1 = hash;
                    currentState = AGENT_STATE_END_SCREEN;
                }
                else{
                    coinflip = NegotiateCoinFlip(A,B);
                    if (coinflip == TAILS){
                        hash = NegotiationHash(A);
                        whoseturn = FIELD_OLED_TURN_MINE;
                        battle();
                        guessData = FieldAIDecideGuess(&opp_field);
                        Messageout.type = MESSAGE_SHO;
                        Messageout.param0 = guessData.row; 
                        Messageout.param1 = guessData.col;
                        Messageout.param2 = 0;
                        currentState = AGENT_STATE_ATTACKING;
                        
                    }
                    else{
                        whoseturn = FIELD_OLED_TURN_THEIRS;
                        battle();
                        currentState = AGENT_STATE_DEFENDING;
                    }
                    return Messageout;
                }
            }
            break;
        case AGENT_STATE_WAITING_TO_SEND:
            if (event.type == BB_EVENT_MESSAGE_SENT){
                turnnum++;
                GuessData AI_guess = FieldAIDecideGuess(&opp_field);
                Messageout.type = MESSAGE_SHO;
                Messageout.param0 = AI_guess.row;
                Messageout.param1 = AI_guess.col;
                currentState = AGENT_STATE_ATTACKING;
                return Messageout;
            }
            break;
        case AGENT_STATE_ATTACKING:
            if (event.type == BB_EVENT_RES_RECEIVED){
                //0 for row 1 for col 2 for guessdata
                FieldUpdateKnowledge(&opp_field, &guessData); 
                guessData.row = event.param0;
                guessData.col = event.param1;
                guessData.result = event.param2;
                Messageout.param0 = guessData.row;
                Messageout.param1 = guessData.col;
                battle();
                
                if (FieldGetBoatStates(&opp_field) == 0b00000000){
                   battle_result == victory;
                   currentState = AGENT_STATE_END_SCREEN; 
                }
                else{
                    whoseturn = FIELD_OLED_TURN_THEIRS;
                    battle();
                    currentState = AGENT_STATE_DEFENDING; 
                    return Messageout;
                }
            }
            break;
        case AGENT_STATE_DEFENDING:
            if (event.type == BB_EVENT_SHO_RECEIVED){
                opp_guess.row = event.param0;
                opp_guess.col = event.param1;
                FieldRegisterEnemyAttack(&own_field, &opp_guess);
                Messageout.param0 = opp_guess.row;
                Messageout.param1 = opp_guess.col;
                Messageout.param2 = opp_guess.result;
                Messageout.type = MESSAGE_RES;
                battle();
                if (FieldGetBoatStates(&own_field) == 0b00000000){
                   battle_result == defeat;
                   currentState = AGENT_STATE_END_SCREEN; 
                   return Messageout;
                }
                else{
                    currentState = AGENT_STATE_WAITING_TO_SEND;
                    whoseturn = FIELD_OLED_TURN_THEIRS;
                    battle();
                    return Messageout;
                }
            }
            break;
        case AGENT_STATE_END_SCREEN:
            OledClear(OLED_COLOR_BLACK);
            char display2[100] = "";
            if (battle_result == defeat){
                sprintf(display2,"You LOST!");
            }
            if (battle_result == victory){
                sprintf(display2,"You WIN!");
            }
            OledDrawString(display2);
            OledUpdate();
            OledClear(OLED_COLOR_BLACK);
            sprintf(display2,"Thanks for playing!");
            OledDrawString(display2);
            OledUpdate();
            break;
    }
    
    
}

/** * 
 * @return Returns the current state that AgentGetState is in.  
 * 
 * This function is very useful for testing AgentRun.
 */
AgentState AgentGetState(void){
    return currentState;
}

/** * 
 * @param Force the agent into the state given by AgentState
 * 
 * This function is very useful for testing AgentRun.
 */
void AgentSetState(AgentState newState){
    currentState = newState;
}

void  screen(void){
    char display[100] = "";
    OledClear(OLED_COLOR_BLACK);
    
    sprintf(display, "CHALLENGING & ACCEPTING\n");
    OledDrawString(display);
    OledUpdate();
}

void  battle(void){
    FieldOledDrawScreen(&own_field, &opp_field, whoseturn, turnnum);
    OledUpdate();
}

void NegotiationScreen(void){
    OledDrawString("This is BattleBoats!\nPress BTN4 to\nchallenge, or wait\nfor opponent.\n");
    OledUpdate();
}
//#endif // AGENT_H

