/* 
 * File:   rpn.c
 * Author: Duo Yu
 *
 * Created on April 29, 2021, 2:26 PM
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BOARD.h"
#include "rpn.h"
#include "stack.h"

int isnumber(char * token);
/* RPN_Evaluate() parses and evaluates a string that contains 
 * a valid Reverse Polish Notation string (no newlines!)  
 * @param:  rpn_string - a string in polish notation.  Tokens must be either 
 *          arithmetic operators or numbers.
 * @param:  result - a pointer to a double that will be modified to contain
 *          the return value of the rpn expression.
 * @return: error - if the rpn expression is invalid, 
 *          an appropriate rpn_error value is returned.
 * 
 * RPN_Evaluate supports the following basic arithmetic operations:
 *   + : addition
 *   - : subtraction
 *   * : multiplication
 *   / : division
 * Numeric tokens can be positive or negative, and can be integers or 
 * decimal floats.  RPN_Evaluate should be able to handle strings of 
 * at least 255 length.
 * */
int RPN_Evaluate(char * rpn_string, double * result) {
    char *token;
    double num;
    double num1;
    double num2;
    double num3;
    struct Stack stack = {};
    int check1, check2, check3;
    StackInit(&stack);
    token = strtok(rpn_string, " ");
    while (token != NULL) {
        if (isnumber(token) == FALSE) {
            if (strlen(token) != 1) {
                return RPN_ERROR_INVALID_TOKEN;
            }
            check1 = StackPop(&stack, &num2);
            check2 = StackPop(&stack, &num1);

            if (check1 == STANDARD_ERROR || check2 == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            else if (*token == '+') {
                num = num1 + num2;
                StackPush(&stack, num);
                break;
            }
            else if (*token == '-') {
                num = num1 - num2;
                StackPush(&stack, num);
                break;
            }
            else if (*token == '*') {
                num = num1 * num2;
                StackPush(&stack, num);
                break;
            }
            else if (*token == '/') {
                if (num2 == 0) {
                    return RPN_ERROR_DIVIDE_BY_ZERO;
                } else {
                    num = num1 / num2;
                    StackPush(&stack, num);
                    break;
                }
            }
            else {
                return RPN_ERROR_INVALID_TOKEN;
            }
        }
    
    else{
        num3 = atof(token);  
        check3 = StackPush(&stack, num3);
        if (check3 == STANDARD_ERROR) {
            return RPN_ERROR_STACK_OVERFLOW;
        }
    }

    token = strtok(NULL, " ");
}
// stack->currentItemIndex = *stack.currentItemIndex
if (StackGetSize(&stack) < 1) {
    return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
} else if (StackGetSize(&stack) > 1) { //error
    return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
} 

    *result = num;
    StackPop(&stack, &num);
    num = 0;
    return RPN_NO_ERROR;


}
//== is for conditionals (such as in if statements)
//= is for assigning values

int isnumber(char * token) {
    if ((token[0] == ' ') && (token[1] == '\0')) { //error
        return FALSE;
    }
    int index, period = 0, number = 0;
    char negative = 0x2D;
    char decmial = 0x2E;
    char firstint = 0x30;
    char lastint = 0x39;
    for (index = 0; index < strlen(token); index++) {
        if ((token[index] >= firstint && token[index] <= lastint)) {
            number++;
        } else {
            if (token[index] == negative && (index == 0)) {
                continue;
            }
            if (token[index] == decmial && (period == 0)) {
                period++;
                continue;
            }
            return FALSE;
        }
    }
    if ((number >= 1) && (period <= 1)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**else if(sscanf(token, "%f", &f) != 0){
            StackPush(&stack, atof(token));

        }
 * This function should read through an array of characters, checking for backspace characters. 
 * When it encounters a backspace character, it eliminates the backspace, the preceeding character
 * (if such a character exists), and shifts all subsequent characters as appropriate.
 * @param string_to_modify The string that will be processed for backspaces. 
 *        This string is modified "in place", so it is both an input and an output to the function.
 * @return Returns the size of the resulting string in "string_to_modify".
 *
 * ProcessBackspaces() should be able to handle multiple repeated backspaces and also
 * strings with more backspaces than characters. It should be able to handle strings of at least 255 length.
 * 
 * */
int ProcessBackspaces(char *rpn_sentence) {
    return 0;
}
