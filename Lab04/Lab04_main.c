// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

    printf("Welcome to dyu33'S RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        printf("Enter floats and + - / * in RPN format:\n");

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        
        strtok(rpn_sentence, "\n");
        int error = RPN_Evaluate(rpn_sentence, &result);
        switch(error){
            case '1':
                printf("RPN_ERROR_STACK_OVERFLOW.\n");
                break;
            case '2':
                printf("RPN_ERROR_STACK_UNDERFLOW.\n");
                break;
            case '3':
                printf("RPN_ERROR_INVALID_TOKEN.\n");
                break;
            case '4':
                printf("RPN_ERROR_DIVIDE_BY_ZERO.\n");
                break;
            case '5':
                printf("RPN_ERROR_TOO_FEW_ITEMS_REMAIN.\n");
                break;
            case '6':
                printf("RPN_ERROR_TOO_MANY_ITEMS_REMAIN.\n");
                break;
            default:
                printf("result = %f\n", result);
                break;   
        }
        
        
    }

    while (1);
}
