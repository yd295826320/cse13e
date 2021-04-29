// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

int main()
{
    BOARD_Init();
    int error;

    printf("\n###### Beginning dyu33's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    
    char test0[] = "1 1 + ";
    double result0;
    double expected0 = 4;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error : Error %i\n", error);
    } else if (result0 != expected0) {
        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("   Success!\n");
    }
    
    char test0_1[] = "0.5 1 + 2 *";
    double result0_1;
    double expected0_1 = 3;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0_1);
    error = RPN_Evaluate(test0_1, &result0_1);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error : Error %i\n", error);
    } else if (result0_1 != expected0_1) {
        printf("   Failed, expected = %f , result = %f\n", expected0_1, result0_1);
    } else {
        printf("   Success!\n");
    }
    
    char test1[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 ";
    double result1;
    int error1;
    printf("Testing RPN_Evaluate with RPN_ERROR_STACK_OVERFLOW\n");
    error1 = RPN_Evaluate(test1, &result1);
    if (error1) {
        printf("   Success, RPN_ERROR_STACK_OVERFLOW %i\n",error1);
    } else {
        printf("    Failed, RPN_ERROR_STACK_OVERFLOW\n");
    }
    
    char test2[] = "1 + ";
    double result2;
    int error2;
    printf("Testing RPN_Evaluate with RPN_ERROR_STACK_UNDERFLOW\n");
    error2 = RPN_Evaluate(test2, &result2);
    if (error2) {
        printf("   Success, RPN_ERROR_STACK_UNDERFLOW %i\n",error2);
    } else {
        printf("    Failed, RPN_ERROR_STACK_UNDERFLOW\n");
    }
    
    char test3[] = "1 1 + &";
    double result3;
    int error3;
    printf("Testing RPN_Evaluate with RPN_ERROR_INVALID_TOKEN\n");
    error3 = RPN_Evaluate(test3, &result3);
    if (error3) {
        printf("   Success, RPN_ERROR_INVALID_TOKEN %i\n",error3);
    } else {
        printf("    Failed, RPN_ERROR_INVALID_TOKEN\n");
    }
    
    char test4[] = "0 0 / ";
    double result4;
    int error4;
    printf("Testing RPN_Evaluate with RPN_ERROR_DIVIDE_BY_ZERO\n");
    error4 = RPN_Evaluate(test4, &result4);
    if (error4) {
        printf("   Success, RPN_ERROR_DIVIDE_BY_ZERO %i\n",error4);
    } else {
        printf("    Failed, RPN_ERROR_DIVIDE_BY_ZERO\n");
    }

    char test5[] = "1 2 + + ";
    double result5;
    int error5;
    printf("Testing RPN_Evaluate with RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n");
    error5 = RPN_Evaluate(test5, &result5);
    if (error5) {
        printf("   Success, RPN_ERROR_TOO_FEW_ITEMS_REMAIN %i\n",error5);
    } else {
        printf("    Failed, RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n");
    }
    
    char test6[] = "1 2 3 + ";
    double result6;
    int error6;
    printf("Testing RPN_Evaluate with RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n");
    error6 = RPN_Evaluate(test6, &result6);
    if (error6) {
        printf("   Success, RPN_ERROR_TOO_MANY_ITEMS_REMAIN %i\n",error6);
    } else {
        printf("    Failed, RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n");
    }
    
    /*printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "123\b34";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n");*/
    BOARD_End();
    while (1);
}


