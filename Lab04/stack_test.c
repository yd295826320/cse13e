// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning dyu33's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    
    printf("Does Stack set the currentItemIndex appropriately?\n");      //test stackInit:
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("StackInit(currentItemIndex) passed\n");
    } else {
        printf("StackInit(currentItemIndex) failed\n");
    }
    if (stack.initialized == TRUE) {
        printf("StackInit(initialized) passed\n");
    } else {
        printf("StackInit(initialized) failed\n");
    }
    
    double val = 10.5;
    StackPush(&stack,val);
    struct Stack stack_2 = {};
    if (StackPush(&stack_2,val) == STANDARD_ERROR){
        printf("StackPush(Empty) passed\n");
    }
    else{
        printf("StackPush(Empty) failed\n");
    }
    int random;
    StackInit(&stack_2);
    for (random = 0; random < STACK_SIZE; random++){
        StackPush(&stack_2, random);
    }
    if (StackPush(&stack_2,val) == STANDARD_ERROR){
        printf("StackPush(Full) passed\n");
    }
    else{
        printf("StackPush(Full) failed\n");
    }
    
    StackInit(&stack_2);
    if (StackPop(&stack_2,&val) == STANDARD_ERROR){                              //error
        printf("StackPop(Empty) passed\n");
    }
    else{
        printf("StackPop(Empty) failed\n");
    }
    
    StackInit(&stack);
    if (StackIsEmpty(&stack) == TRUE){
        printf("StackIsEmpty(Empty) passed\n");
    }
    else{
        printf("StackIsEmpty(Empty) failed\n");
    }
    
    StackInit(&stack);
    for (random = 0; random < STACK_SIZE; random++){
        StackPush(&stack, random);
    }
    if (StackIsFull(&stack) == TRUE){
        printf("StackIsFull(Full) passed\n");
    }
    else{
        printf("StackIsFull(Full) failed\n");
    }
    
    StackInit(&stack_2);
    if (StackGetSize(&stack_2) == 0){
        printf("StackGetSize(Empty) passed\n");
    }
    else{
        printf("StackGetSize(Empty) failed\n");
    }
    
    
    BOARD_End();
    
    while (1);
    return 0;
}


