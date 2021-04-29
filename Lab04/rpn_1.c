#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BOARD.h"
#include "rpn.h"
#include "stack.h"


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
int RPN_Evaluate(char * rpn_string, double * result){
    char *token;
    double num;
    double num1;
    double num2;
    struct Stack stack;
    int check1, check2, check3;
    token = strtok(rpn_string, " ");
    while (token != NULL){
        if (((token[0] == '+') || (token[0] == '-') || (token[0] == '/') || (token[0] == '*')) && (strlen(token) == 1)){
            check1 = StackPop(&stack, &num2);
            check2 = StackPop(&stack, &num1);
            
            if (check1 == STANDARD_ERROR || check2 == STANDARD_ERROR){
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            else{
                if (strcmp(token, "+") == 0){
                    num = num1 + num2;
                    StackPush(&stack, num);                                     //error
                }
                if (strcmp(token, "-") == 0){
                    num = num1 - num2;
                    StackPush(&stack, num);
                }
                if (strcmp(token, "*") == 0){
                    num = num1 * num2;
                    StackPush(&stack, num);
                }
                if (strcmp(token, "/") == 0){
                    if (num2 == 0){
                        return RPN_ERROR_DIVIDE_BY_ZERO;
                    }
                    else{
                        num = num1 / num2;
                    StackPush(&stack, num);
                    }
                }
            }
        }
        else if (isnumber(&token) == TRUE){
            check3 = StackPush(&stack, atof(token));
            if (check3 == STANDARD_ERROR){
                return RPN_ERROR_STACK_OVERFLOW;
            }
        }
        else{
            return RPN_ERROR_INVALID_TOKEN;
        }
        token = strtok(NULL, " ");
    }
    // stack->currentItemIndex = *stack.currentItemIndex
    if (StackIsEmpty(&stack) == TRUE){
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    else if (stack.currentItemIndex > 1){                                     //error
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }
    else{
        StackPop(&stack, &num);                                                 //error
        *result = num;
        return RPN_NO_ERROR;
        
    }
}
//== is for conditionals (such as in if statements)
//= is for assigning values
int isnumber(char *token){
    if ((token[0] == ' ') && (token[1] == '\0')){                                     //error
        return FALSE;
    }
    if (token[0] == '-'){
        token++;
    }
    char *index = token;
    int x = -1;
    // \0
    for(;*index != '\0'; index++){
        if (*index == '0'){
            break;
        }
        else if (*index == '1'){
            break;
        }
        else if (*index == '2'){
            break;
        }
        else if (*index == '3'){
            break;
        }
        else if (*index == '4'){
            break;
        }
        else if (*index == '5'){
            break;
        }
        else if (*index == '6'){
            break;
        }
        else if (*index == '7'){
            break;
        }
        else if (*index == '8'){
            break;
        }
        else if (*index == '9'){
            break;
        }
        else if (*index == '.'){
            x++;
                if (x > 0){
                    return FALSE;
                }
            break;
        }
        else{
            return FALSE;
        }
        /*switch(*index){
            case '0':
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
            case '.':
                x++;
                if (x > 0){
                    return FALSE;
                }
            default:
                return FALSE;
        }*/
    }
    return TRUE;
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
int ProcessBackspaces(char *rpn_sentence){
    return 0;
}
