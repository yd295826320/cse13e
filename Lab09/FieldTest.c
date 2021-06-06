#include "Field.h"
#include "FieldOled.h"
#include <stdio.h>
#include <stdint.h>
#include "BattleBoats.h"
#include "BOARD.h"

static Field oppField;
static Field ownField;
static SquareStatus SQtest1;
static SquareStatus SQtest2;
static SquareStatus SQtest3;
static SquareStatus SQtest4;


static BoatDirection hor = FIELD_DIR_EAST;
static BoatDirection ver = FIELD_DIR_SOUTH;

int main(void){
    BOARD_Init();
    FieldInit(&ownField, &oppField);
    
    
    printf("FieldInit():\n");
    if (ownField.smallBoatLives == 0) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed\n");
    }
    FieldInit(&ownField, &oppField);
    if (oppField.mediumBoatLives == FIELD_BOAT_SIZE_MEDIUM) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
    
    
    printf("FieldAddBoat: \n");                                                 //question
    FieldInit(&ownField, &oppField);
    int test1 = FieldAddBoat(&ownField, 69, -33, hor, FIELD_BOAT_TYPE_SMALL);
    FieldPrint_UART(&ownField, &oppField);
    if (test1 == 0) {
        printf("Passed Test 1\n");
    }
    int test2 = FieldAddBoat(&ownField, 1, 0, hor, FIELD_BOAT_TYPE_HUGE);
    FieldPrint_UART(&ownField, &oppField);
    if (test2 == 1) {
        printf("Passed Test 2\n");
    }
    int test3 = FieldAddBoat(&ownField, 2, 2, ver, FIELD_BOAT_TYPE_MEDIUM);
    FieldPrint_UART(&ownField, &oppField);
    if (test3 == 1) {
        printf("Passed Test 3\n");
    }
    int test4 = FieldAddBoat(&ownField, 1, 1, ver, FIELD_BOAT_TYPE_SMALL);
    FieldPrint_UART(&ownField, &oppField);
    if (test4 == 0) {
        printf("Passed Test 1\n");
    }
    printf("\n");
    
    
    printf("FieldRegisterEnemyAttack: \n");
    GuessData guess1;
    GuessData guess2;
    guess1.col = 1;
    guess1.row = 1;
    guess2.col = 2;
    guess2.row = 2;
    FieldRegisterEnemyAttack(&ownField, &guess1);
    FieldRegisterEnemyAttack(&ownField, &guess2);
    //FieldPrint_UART(&ownField, &oppField);
    //printf("%d\n",guess1.result);
    //printf("%d\n",guess2.result);
    if (guess1.result == RESULT_HIT) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed Test 1\n");
    }
    if (guess2.result == RESULT_HIT) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed Test 2\n");                                              //question
    }
    printf("\n");
    FieldPrint_UART(&ownField, &oppField);
    
    
    uint8_t row1 = 1;
    uint8_t col1 = 1;
    uint8_t row2 = 3;
    uint8_t col2 = 2;
    printf("FieldSetSquareStatus: \n");
    SQtest3 = FieldSetSquareStatus(&ownField, row1, col1, FIELD_SQUARE_EMPTY);
    //FieldPrint_UART(&ownField, &oppField);
    //printf("%d\n",SQtest3);
    if (SQtest3 == 6) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed\n");
    }
    SQtest4 = FieldSetSquareStatus(&ownField, row2, col2, FIELD_SQUARE_LARGE_BOAT);
    //FieldPrint_UART(&ownField, &oppField);
    //printf("%d\n",SQtest4);
    if (SQtest4 == 2) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
    
    
    printf("FieldGetSquareStatus: \n");
    SQtest1 = FieldGetSquareStatus(&ownField, row1, col1);
    //printf("%d\n",SQtest1);
    if (SQtest1 == 0) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed\n");
    }
    SQtest2 = FieldGetSquareStatus(&ownField, row2, col2);
    //printf("%d\n",SQtest2);
    if (SQtest2 == 3) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
    
    
    printf("FieldUpdateKnowledge():\n");
    SquareStatus updateknow1 = FieldUpdateKnowledge(&ownField, &guess1);
    SquareStatus updateknow2 = FieldUpdateKnowledge(&ownField, &guess2);
    if (ownField.grid[guess1.row][guess1.col] == FIELD_SQUARE_MISS
            && updateknow1 == FIELD_SQUARE_EMPTY) {
        printf("Passed Test 1\n");
    } else {
        printf("Failed Test 1\n");
    }
    if (ownField.grid[guess2.row][guess2.col] == FIELD_SQUARE_HIT
            && updateknow2 == FIELD_SQUARE_MEDIUM_BOAT) {
        printf("Passed Test 2\n");
    } else {
        printf("Failed Test 2\n");
    }
    printf("\n");
    
    
    FieldPrint_UART(&ownField, &oppField);
    printf("FieldGetBoatStates()\n");
    uint8_t boatStates = FieldGetBoatStates(&ownField);
    printf("expect 10 flags, result is %d\n",boatStates);
    
    
    FieldInit(&ownField, &oppField);
    FieldPrint_UART(&ownField, &oppField);
    FieldAIPlaceAllBoats(&ownField);
    FieldPrint_UART(&ownField, &oppField);
}

