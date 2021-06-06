#include "xc.h"
#include "stdio.h"
#include <stdint.h>
#include <string.h>
#include "BOARD.h"
#include "Field.h"
#include "BattleBoats.h"
#include "Negotiation.h"
#include "Message.h"
#include "Agent.h"

static AgentState currentState;

int main(void){
    BOARD_Init();
    
    
    printf("Testing AgentInit()\n");
    AgentInit();
    if (currentState == AGENT_STATE_START) {
        printf("PASS AgentInit()\n");
    } 
    else {
        printf("An error occurred in AgentInit()\n");
    }
    
    printf("Testing AgentRun()\n");
    BB_Event testevent1;
    testevent1.type = BB_EVENT_START_BUTTON;
    if (currentState == AGENT_STATE_START) {
        printf("PASS AgentRun() when start\n");
    } 
    else {
        printf("An error occurred in AgentRun() when start\n");
    }
    BB_Event testevent2;
    testevent2.type = BB_EVENT_MESSAGE_SENT;
    Message Result = AgentRun(testevent2);
    printf("%d",Result.type);
    if (currentState == AGENT_STATE_ATTACKING) {
        printf("PASS AgentRun() for no event\n");
    } 
    else {
        printf("An error occurred in AgentRun() for no event\n");
    }

    
     printf("Testing AgentGet/SetState()\n");
    AgentSetState(AGENT_STATE_START);
    AgentState gsTest1 = AgentGetState();
    if (gsTest1 == AGENT_STATE_START){
        printf("Passed Test 1\n");
    }
    else{
        printf("Failed Test 1\n");
    }
    AgentSetState(AGENT_STATE_ATTACKING);
    AgentState gsTest2 = AgentGetState();
    if (gsTest2 == AGENT_STATE_ATTACKING){
        printf("Passed Test 2\n");
    }
    else{
        printf("Failed Test 2\n");
    }
    
    
    
    
}