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
static uint8_t turnnum;
//field oled turn
static FieldOledTurn whoseturn;
static GuessData guessData;
static uint16_t Hash_a;


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
    Message Messageout = {MESSAGE_NONE, 0, 0, 0};
    if (event.type == BB_EVENT_RESET_BUTTON){
        AgentInit();
        //NegotiationScreen
        return Messageout;
    }
    if (event.type = BB_EVENT_ERROR){
        //errorScreen
        
        //set error message
        //return it
    }
    switch(currentState){
        case AGENT_STATE_START:
            if (event.type == BB_EVENT_START_BUTTON){
                currentState = AGENT_STATE_CHALLENGING;
                A = rand();
                Hash_a = NegotiationHash(A);
                Messageout.type = MESSAGE_CHA;
                Messageout.param0 = Hash_a;
                FieldInit(&own_field,&opp_field);
                FieldAIPlaceAllBoats(&own_field);
                FieldAIPlaceAllBoats(&opp_field);
                
            }
            else if(event.type == BB_EVENT_CHA_RECEIVED){
                currentState = AGENT_STATE_ACCEPTING;
                Hash_a = event.param0;
                B = rand();
                Messageout.type = MESSAGE_ACC;
                Messageout.param0 = B;
                
            }
            break;
        case AGENT_STATE_CHALLENGING:
            if (event.type == BB_EVENT_ACC_RECEIVED){
                Messageout.type = MESSAGE_REV;
                B = event.param0;
                Messageout.param0 = A;
                // updata screen
                if (NegotiateCoinFlip(A, B) == HEADS){                                   //question
                    currentState = AGENT_STATE_WAITING_TO_SEND;
                    
                }
                else{
                    currentState = AGENT_STATE_DEFENDING;
                    
                }
                
            }
            break;
        case AGENT_STATE_ACCEPTING:
            if (event.type == BB_EVENT_REV_RECEIVED){
                A = event.param0;
                uint8_t checkcheat = NegotiationVerify(A,Hash_a);
                if (checkcheat == FALSE){
                    currentState = AGENT_STATE_END_SCREEN;
                }
                else{
                    if (NegotiateCoinFlip(A,B) == TAILS){
                        guessData = FieldAIDecideGuess(&opp_field);
                        Messageout.type = MESSAGE_SHO;
                        currentState = AGENT_STATE_ATTACKING;
                    }
                    else{
                        currentState = AGENT_STATE_DEFENDING;
                    }
                }
            }
            break;
        case AGENT_STATE_WAITING_TO_SEND:
            if (event.type == BB_EVENT_MESSAGE_SENT){
                turnnum++;
                guessData = FieldAIDecideGuess(&opp_field);
                Messageout.type = MESSAGE_SHO;
                currentState = AGENT_STATE_ATTACKING;
            }
            break;
        case AGENT_STATE_ATTACKING:
            if (event.type == BB_EVENT_RES_RECEIVED){
                //0 for row 1 for col 2 for guessdata
                guessData.row = event.param0;
                guessData.col = event.param1;
                guessData.result = event.param2;
                FieldUpdateKnowledge(&opp_field, &guessData);
                if (FieldGetBoatStates(&opp_field) == 0b00000000){
                    //victory
                   currentState = AGENT_STATE_END_SCREEN; 
                }
                else{
                    currentState = AGENT_STATE_DEFENDING; 
                }
                
            }
            break;
        case AGENT_STATE_DEFENDING:
            if (event.type == BB_EVENT_SHO_RECEIVED){
                guessData.row = event.param0;
                guessData.col = event.param1;
                FieldRegisterEnemyAttack(&own_field, &guessData);
                Messageout.type = MESSAGE_RES;
                if (FieldGetBoatStates(&own_field) == 0b00000000){
                    //defeat
                   currentState = AGENT_STATE_END_SCREEN; 
                }
                else{
                    currentState = AGENT_STATE_WAITING_TO_SEND; 
                }
            }
            break;
        default:
            
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

//#endif // AGENT_H

