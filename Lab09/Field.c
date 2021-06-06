
#include <stdint.h>
#include <string.h>


#include "BOARD.h"
#include "stdio.h"
#include "BattleBoats.h"
#include "Field.h"
#include "xc.h"
 /**
 * Define the dimensions of the game field. They can be overridden by compile-time specifications.
 * All references to the dimensions of the field should use these constants instead of hard-coding
 * a numeric value so that the field dimensions can be changed with minimal coding changes.
 
#ifndef FIELD_COLS
#define FIELD_COLS 10
#endif
#ifndef FIELD_ROWS
#define FIELD_ROWS 6
#endif


 * Set different constants used for conveying different information about the different locations
 * of the field. These values should be used for the actual storage of the field state, which is
 * almost every usage. For displaying the field using FieldPrint(), the SquareStatus Display enum
 * values should be used instead.
 
typedef enum {
    /// These denote field positions useful for representing the local board
   // An empty field position.
    FIELD_SQUARE_SMALL_BOAT, 	// This position contains part of the small boat.
    FIELD_SQUARE_MEDIUM_BOAT, 	// This position contains part of the medium boat.
    FIELD_SQUARE_LARGE_BOAT, 	// This position contains part of the large boat.
    FIELD_SQUARE_HUGE_BOAT, 	// This position contains part of the huge boat.

    /// These denote field positions useful for representing the enemy's board
    FIELD_SQUARE_UNKNOWN, 		// It is unknown what is here. Useful for denoting a position on the
								// enemy's board that hasn't been checked.
								
	///these statuses may be used on either field:    
    FIELD_SQUARE_HIT,			// A field position that was attacked and contained part of a boat.
    FIELD_SQUARE_MISS, 			// This position was attacked by the enemy, but was empty.

    /// This may be useful for implementing extra-credit features:
    FIELD_SQUARE_CURSOR, 		// This is used merely for use in FieldOled.c for indicating the current
								// cursor when selecting a position to attack.

    /// Occasionally, it may be necessary to indicate an error using a square status:
    FIELD_SQUARE_INVALID,
} SquareStatus;


 * These are the possible results of shots:


typedef enum {
    RESULT_MISS,                //0
    RESULT_HIT,                 //1
    RESULT_SMALL_BOAT_SUNK,     //2
    RESULT_MEDIUM_BOAT_SUNK,    //3
    RESULT_LARGE_BOAT_SUNK,     //4
    RESULT_HUGE_BOAT_SUNK,      //5
} ShotResult;


 * GuessData is used for exchanging coordinate data along with information about of coordinate.
 
typedef struct {
    uint8_t row; // Row of the coordinate that was guessed
    uint8_t col; // Column of the coordinate guessed
    ShotResult result; // result of a shot at this coordinate
} GuessData;


 * A struct for tracking all of the necessary data for an agent's field.

typedef struct {
    uint8_t grid[FIELD_ROWS][FIELD_COLS];
    uint8_t smallBoatLives;
    uint8_t mediumBoatLives;
    uint8_t largeBoatLives;
    uint8_t hugeBoatLives;
} Field;


 * Specify how many boats there exist on the field. There is 1 boat of each of the 4 types, so 4
 * total.

#define FIELD_NUM_BOATS 4


 * Declares direction constants for use with FieldAddShip.
 
typedef enum {
    FIELD_DIR_SOUTH,
    FIELD_DIR_EAST,
} BoatDirection;


 * Constants for specifying which boat the current operation refers to. This is independent of the
 * SquareStatus enum.
 
typedef enum {
    FIELD_BOAT_TYPE_SMALL,
    FIELD_BOAT_TYPE_MEDIUM,
    FIELD_BOAT_TYPE_LARGE,
    FIELD_BOAT_TYPE_HUGE
} BoatType;


 * Track the alive state of the boats. They are arranged as as mutually-exclusive bits so that they
 * can be bitwise ORed together. Used for checking the return value of  `FieldGetBoatStates()`. 
 * 
 * For example, if a field has a MEDIUM boat and a HUGE boat, but the other two boats
 * have been sunk, then its status flag should be:
 * FIELD_BOAT_STATUS_MEDIUM | FIELD_BOAT_STATUS_HUGE, or 0b1010
 *
 
typedef enum {
    FIELD_BOAT_STATUS_SMALL = 0x01,
    FIELD_BOAT_STATUS_MEDIUM = 0x02,
    FIELD_BOAT_STATUS_LARGE = 0x04,
    FIELD_BOAT_STATUS_HUGE = 0x08,
} BoatStatusFlag;


 * This enum lists the number of squares, each boat occupies (and therefore, the number of 
 * lives) that each boat has.
 
typedef enum {
    FIELD_BOAT_SIZE_SMALL = 3,
    FIELD_BOAT_SIZE_MEDIUM = 4,
    FIELD_BOAT_SIZE_LARGE = 5,
    FIELD_BOAT_SIZE_HUGE = 6
} BoatSize;
*/



/**
 * This function is optional, but recommended.   It prints a representation of both
 * fields, similar to the OLED display.
 * @param f The field to initialize.
 * @param p The data to initialize the entire field to, should be a member of enum
 *                     SquareStatus.
 */
void FieldPrint_UART(Field *own_field, Field * opp_field){
    printf("    0 1 2 3 4 5 6 7 8 9  \n");
    printf("   --------------------- \n");
    uint8_t row = 0;
    uint8_t col = 0;
    for (row = 0; row < FIELD_ROWS; row++) {
        printf("%d [ ", row);
        for (col = 0; col < FIELD_COLS; col++) {
            switch (own_field->grid[row][col]){
                case FIELD_SQUARE_SMALL_BOAT:
                    printf("3");
                    break;
                case FIELD_SQUARE_MEDIUM_BOAT:
                    printf("4");
                    break;
                case FIELD_SQUARE_LARGE_BOAT:
                    printf("5");
                    break;
                case FIELD_SQUARE_HUGE_BOAT:
                    printf("6");
                    break;
                case FIELD_SQUARE_UNKNOWN:
                    printf("?");
                    break;
                case FIELD_SQUARE_HIT:
                    printf("H");
                    break;
                case FIELD_SQUARE_MISS:
                    printf("M");
                    break;
                case FIELD_SQUARE_INVALID:
                    printf("!");
                    break;
                case FIELD_SQUARE_EMPTY:
                    printf(".");
                    break;
                }
            printf(" ");
        }
        printf("]\n");
    }
}


/**
 * FieldInit() will initialize two passed field structs for the beginning of play.
 * Each field's grid should be filled with the appropriate SquareStatus (
 * FIELD_SQUARE_EMPTY for your own field, FIELD_SQUARE_UNKNOWN for opponent's).
 * Additionally, your opponent's field's boatLives parameters should be filled
 *  (your own field's boatLives will be filled when boats are added)
 * 
 * FieldAI_PlaceAllBoats() should NOT be called in this function.
 * 
 * @param own_field     //A field representing the agents own ships
 * @param opp_field     //A field representing the opponent's ships
 */
void FieldInit(Field *own_field, Field * opp_field){
    //in a for loop
    uint8_t row;
    uint8_t col;
    for (row = 0; row < FIELD_ROWS; row++) {
        for (col = 0; col < FIELD_COLS; col++) {
            own_field->grid[row][col] = FIELD_SQUARE_EMPTY;
            opp_field->grid[row][col] = FIELD_SQUARE_UNKNOWN;
        }
    }
    //init opp_field with FIELD_NUM_BOATS
    //init own_field with zeros
    opp_field ->smallBoatLives =FIELD_BOAT_SIZE_SMALL; 
    opp_field ->mediumBoatLives =FIELD_BOAT_SIZE_MEDIUM; 
    opp_field ->largeBoatLives =FIELD_BOAT_SIZE_LARGE; 
    opp_field ->hugeBoatLives =FIELD_BOAT_SIZE_HUGE; 
    own_field ->smallBoatLives = 0; 
    own_field ->mediumBoatLives = 0; 
    own_field ->largeBoatLives = 0; 
    own_field ->hugeBoatLives = 0; 
    
}

/**
 * Retrieves the value at the specified field position.
 * @param f     //The Field being referenced
 * @param row   //The row-component of the location to retrieve
 * @param col   //The column-component of the location to retrieve
 * @return  FIELD_SQUARE_INVALID if row and col are not valid field locations
 *          Otherwise, return the status of the referenced square 
 */
SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col){
    //check if row and col are in range of field
    // if in range, return the grid status of field
    if (row <= FIELD_ROWS && col <= FIELD_COLS){
       SquareStatus getStatus = f -> grid[row][col];
       return getStatus;
    }
    return FIELD_SQUARE_INVALID;
}

/**
 * This function provides an interface for setting individual locations within a Field struct. This
 * is useful when FieldAddBoat() doesn't do exactly what you need. For example, if you'd like to use
 * FIELD_SQUARE_CURSOR, this is the function to use.
 * 
 * @param f The Field to modify.
 * @param row The row-component of the location to modify
 * @param col The column-component of the location to modify
 * @param p The new value of the field location
 * @return The old value at that field location
 */
SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p){
    //with given row and colomn
    //save previous data to a var
    //set new status to grid
    //return old status
    if (row <= FIELD_ROWS && col <= FIELD_COLS){
        SquareStatus oldstatus = FieldGetSquareStatus(f, row, col);
        f ->grid[row][col] = p;
        return oldstatus;
    }
    return FIELD_SQUARE_INVALID;
    
}

/**
 * FieldAddBoat() places a single ship on the player's field based on arguments 2-5. Arguments 2, 3
 * represent the x, y coordinates of the pivot point of the ship.  Argument 4 represents the
 * direction of the ship, and argument 5 is the length of the ship being placed. 
 * 
 * All spaces that
 * the boat would occupy are checked to be clear before the field is modified so that if the boat
 * can fit in the desired position, the field is modified as SUCCESS is returned. Otherwise the
 * field is unmodified and STANDARD_ERROR is returned. There is no hard-coded limit to how many
 * times a boat can be added to a field within this function.
 * 
 * In addition, this function should update the appropriate boatLives parameter of the field.
 *
 * So this is valid test code:
 * {
 *   Field myField;
 *   FieldInit(&myField,FIELD_SQUARE_EMPTY);
 *   FieldAddBoat(&myField, 0, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_SMALL);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_MEDIUM);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_HUGE);
 *   FieldAddBoat(&myField, 0, 6, FIELD_BOAT_DIRECTION_SOUTH, FIELD_BOAT_TYPE_SMALL);
 * }
 *
 * should result in a field like:
 *      0 1 2 3 4 5 6 7 8 9
 *     ---------------------
 *  0 [ 3 3 3 . . . 3 . . . ]
 *  1 [ 4 4 4 4 . . 3 . . . ]
 *  2 [ . . . . . . 3 . . . ]
 *  3 [ . . . . . . . . . . ]
 *  4 [ . . . . . . . . . . ]
 *  5 [ . . . . . . . . . . ]
 *     
 * @param f The field to grab data from.
 * @param row The row that the boat will start from, valid range is from 0 and to FIELD_ROWS - 1.
 * @param col The column that the boat will start from, valid range is from 0 and to FIELD_COLS - 1.
 * @param dir The direction that the boat will face once places, from the BoatDirection enum.
 * @param boatType The type of boat to place. Relies on the FIELD_SQUARE_*_BOAT values from the
 * SquareStatus enum.
 * @return SUCCESS for success, STANDARD_ERROR for failure
 */
uint8_t FieldAddBoat(Field *own_field, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type){
    //add boat to the grid of given boat tyoe
    // if boat type == small then boat lives should be equal to 3 if row equal boat lives then success
    uint8_t i = row;
    uint8_t j = col;
    switch(dir){
        case FIELD_DIR_EAST:
            
            while (row < FIELD_ROWS && j < FIELD_COLS){
                if (FieldGetSquareStatus(own_field, row, j) == FIELD_SQUARE_EMPTY){
                    
                    if (boat_type == FIELD_BOAT_TYPE_SMALL){
                        if ((col+FIELD_BOAT_SIZE_SMALL) > FIELD_COLS){
                            return STANDARD_ERROR;
                        }
                        own_field ->grid[row][j] = FIELD_SQUARE_SMALL_BOAT;
                        j++;
                        own_field ->smallBoatLives++;
                        if (j == col + FIELD_BOAT_SIZE_SMALL){
                            break;
                        }
                    }
                    if (boat_type == FIELD_BOAT_TYPE_MEDIUM){
                        if ((col+FIELD_BOAT_SIZE_MEDIUM) > FIELD_COLS){
                            return STANDARD_ERROR;
                        }
                        if (j == col + FIELD_BOAT_SIZE_MEDIUM){
                            break;
                        }
                        own_field ->grid[row][j] = FIELD_SQUARE_MEDIUM_BOAT;
                        j++;
                        own_field ->mediumBoatLives++;
                        
                    }
                    if (boat_type == FIELD_BOAT_TYPE_LARGE){
                        if ((col+FIELD_BOAT_SIZE_LARGE) > FIELD_COLS){
                            return STANDARD_ERROR;
                        }
                        own_field ->grid[row][j] = FIELD_SQUARE_LARGE_BOAT;
                        j++;
                        own_field ->largeBoatLives++;
                        if (j == col + FIELD_BOAT_SIZE_LARGE){
                            break;
                        }
                    }
                    if (boat_type == FIELD_BOAT_TYPE_HUGE){
                        if ((col+FIELD_BOAT_SIZE_HUGE) > FIELD_COLS){
                            return STANDARD_ERROR;
                        }
                        own_field ->grid[row][j] = FIELD_SQUARE_HUGE_BOAT;
                        j++;
                        own_field ->hugeBoatLives++;
                        if (j == col + FIELD_BOAT_SIZE_HUGE){
                            break;
                        }
                    }
                }
                else{
                    return STANDARD_ERROR;
                }
            }
            break;
               
            
        case FIELD_DIR_SOUTH:
            
            while (i < FIELD_ROWS && col < FIELD_COLS){
                if (FieldGetSquareStatus(own_field, i, col) == FIELD_SQUARE_EMPTY){
                    
                    if (boat_type == FIELD_BOAT_TYPE_SMALL){
                        if ((row+FIELD_BOAT_SIZE_SMALL) > FIELD_ROWS){
                            return STANDARD_ERROR;
                        }
                        own_field ->grid[i][col] = FIELD_SQUARE_SMALL_BOAT;
                        i++;
                        own_field ->smallBoatLives++;
                        if (i == row + FIELD_BOAT_SIZE_SMALL){
                            break;
                        }
                    }
                    if (boat_type == FIELD_BOAT_TYPE_MEDIUM){
                        if ((row+FIELD_BOAT_SIZE_MEDIUM) > FIELD_ROWS){
                            return STANDARD_ERROR;
                        }
                        own_field ->grid[i][col] = FIELD_SQUARE_MEDIUM_BOAT;
                        i++;
                        own_field ->mediumBoatLives++;
                        if (i == row + FIELD_BOAT_SIZE_MEDIUM){
                            break;
                        }
                    }
                    if (boat_type == FIELD_BOAT_TYPE_LARGE){
                        if ((row+FIELD_BOAT_SIZE_LARGE) > FIELD_ROWS){
                            return STANDARD_ERROR;
                        }
                        own_field ->grid[i][col] = FIELD_SQUARE_LARGE_BOAT;
                        i++;
                        own_field ->largeBoatLives++;
                        if (i == row + FIELD_BOAT_SIZE_LARGE){
                            break;
                        }
                    }
                    if (boat_type == FIELD_BOAT_TYPE_HUGE){
                        if ((row+FIELD_BOAT_SIZE_HUGE) > FIELD_ROWS){
                            return STANDARD_ERROR;
                        }
                        own_field ->grid[i][col] = FIELD_SQUARE_HUGE_BOAT;
                        i++;
                        own_field ->hugeBoatLives++;
                        if (i == row + FIELD_BOAT_SIZE_HUGE){
                            break;
                        }
                    }
                }
            }
            
            break;
    }
    if (boat_type == FIELD_BOAT_TYPE_SMALL){
        own_field ->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    }
    if (boat_type == FIELD_BOAT_TYPE_MEDIUM){
        own_field ->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    }
    if (boat_type == FIELD_BOAT_TYPE_LARGE){
        own_field ->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    }
    if (boat_type == FIELD_BOAT_TYPE_HUGE){
        own_field ->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
    }
    return SUCCESS;
}

/**
 * This function registers an attack at the gData coordinates on the provided field. This means that
 * 'f' is updated with a FIELD_SQUARE_HIT or FIELD_SQUARE_MISS depending on what was at the
 * coordinates indicated in 'gData'. 'gData' is also updated with the proper HitStatus value
 * depending on what happened AND the value of that field position BEFORE it was attacked. Finally
 * this function also reduces the lives for any boat that was hit from this attack.
 * @param f The field to check against and update.
 * @param gData The coordinates that were guessed. The result is stored in gData->result as an
 *               output.  The result can be a RESULT_HIT, RESULT_MISS, or RESULT_***_SUNK.
 * @return The data that was stored at the field position indicated by gData before this attack.
 */
SquareStatus FieldRegisterEnemyAttack(Field *own_field, GuessData *opp_guess){
    //check your own field, if hit, result is a SquareStatus var
    //return old Status
    SquareStatus CurrentSquare = own_field ->grid[opp_guess ->row][opp_guess ->col];
    switch(CurrentSquare){
        case FIELD_SQUARE_SMALL_BOAT:
            own_field ->smallBoatLives--;
            if (own_field ->smallBoatLives == 0){
                opp_guess ->result = RESULT_SMALL_BOAT_SUNK;
            } 
            else {
                opp_guess ->result = RESULT_HIT;
                own_field ->grid[opp_guess ->row][opp_guess ->col] = FIELD_SQUARE_HIT; 
            }
            break;
        case FIELD_SQUARE_MEDIUM_BOAT:
            own_field ->mediumBoatLives--;
            if (own_field ->mediumBoatLives == 0){
                opp_guess ->result = RESULT_MEDIUM_BOAT_SUNK;
            } 
            else {
                opp_guess ->result = RESULT_HIT;
                own_field ->grid[opp_guess ->row][opp_guess ->col] = FIELD_SQUARE_HIT; 
            }  
            break;
        case FIELD_SQUARE_LARGE_BOAT:
            own_field ->largeBoatLives--;
            if (own_field ->largeBoatLives == 0){
                opp_guess ->result = RESULT_LARGE_BOAT_SUNK;
            } 
            else {
                opp_guess ->result = RESULT_HIT;
                own_field ->grid[opp_guess ->row][opp_guess ->col] = FIELD_SQUARE_HIT; 
            }
            break;
        case FIELD_SQUARE_HUGE_BOAT:
            own_field ->hugeBoatLives--;
            if (own_field ->hugeBoatLives == 0){
                opp_guess ->result = RESULT_HUGE_BOAT_SUNK;
            } 
            else {
                opp_guess ->result = RESULT_HIT;
                own_field ->grid[opp_guess ->row][opp_guess ->col] = FIELD_SQUARE_HIT; 
                //add same here
            } 
            break;
        default:
            opp_guess ->result = RESULT_MISS;
            own_field ->grid[opp_guess ->row][opp_guess ->col] = FIELD_SQUARE_MISS;
            break;
    }
    return CurrentSquare;
}

/**
 * This function updates the FieldState representing the opponent's game board with whether the
 * guess indicated within gData was a hit or not. If it was a hit, then the field is updated with a
 * FIELD_SQUARE_HIT at that position. If it was a miss, display a FIELD_SQUARE_EMPTY instead, as
 * it is now known that there was no boat there. The FieldState struct also contains data on how
 * many lives each ship has. Each hit only reports if it was a hit on any boat or if a specific boat
 * was sunk, this function also clears a boats lives if it detects that the hit was a
 * RESULT_*_BOAT_SUNK.
 * @param f The field to grab data from.
 * @param gData The coordinates that were guessed along with their HitStatus.
 * @return The previous value of that coordinate position in the field before the hit/miss was
 * registered.
 */
SquareStatus FieldUpdateKnowledge(Field *opp_field, const GuessData *own_guess){
    
        if (own_guess ->result == RESULT_SMALL_BOAT_SUNK){
            opp_field ->smallBoatLives = 0;
        }
        if (own_guess ->result == RESULT_MEDIUM_BOAT_SUNK){
            opp_field ->mediumBoatLives = 0;
        }
        if (own_guess ->result == RESULT_LARGE_BOAT_SUNK){
            opp_field ->largeBoatLives = 0;
        }
        if (own_guess ->result == RESULT_HUGE_BOAT_SUNK){
            opp_field ->hugeBoatLives = 0;
        }
        // if boat sunk then clear the lives
    if (own_guess ->result == RESULT_HIT){    
        SquareStatus oldstatus = FieldGetSquareStatus(opp_field, own_guess ->row, own_guess ->col);
        opp_field ->grid[own_guess ->row][own_guess ->col] = FIELD_SQUARE_HIT;
        return oldstatus;
    }
    else if (own_guess->result == RESULT_MISS){
        SquareStatus oldstatus = FieldGetSquareStatus(opp_field, own_guess ->row, own_guess ->col);
        opp_field ->grid[own_guess ->row][own_guess ->col] = FIELD_SQUARE_EMPTY;
        return oldstatus;
    }
    return STANDARD_ERROR;
}

/**
 * This function returns the alive states of all 4 boats as a 4-bit bitfield (stored as a uint8).
 * The boats are ordered from smallest to largest starting at the least-significant bit. So that:
 * 0b00001010 indicates that the small boat and large boat are sunk, while the medium and huge boat
 * are still alive. See the BoatStatus enum for the bit arrangement.
 * @param f The field to grab data from.
 * @return A 4-bit value with each bit corresponding to whether each ship is alive or not.
 */
uint8_t FieldGetBoatStates(const Field *f){
    uint8_t returnFlags = 0;
    if (f->hugeBoatLives != 0) {
        returnFlags |= FIELD_BOAT_STATUS_HUGE;
    }
    if (f->largeBoatLives != 0) {
        returnFlags |= FIELD_BOAT_STATUS_LARGE;
    }
    if (f->mediumBoatLives != 0) {
        returnFlags |= FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->smallBoatLives != 0) {
        returnFlags |= FIELD_BOAT_STATUS_SMALL;
    }
    return returnFlags;
}


/**
 * This function is responsible for placing all four of the boats on a field.
 * 
 * @param f         //agent's own field, to be modified in place.
 * @return SUCCESS if all boats could be placed, STANDARD_ERROR otherwise.
 * 
 * This function should never fail when passed a properly initialized field!
 */
uint8_t FieldAIPlaceAllBoats(Field *own_field){
    uint8_t success = 0;
    uint8_t check1 = STANDARD_ERROR;
    uint8_t check2 = STANDARD_ERROR;
    uint8_t check3 = STANDARD_ERROR;
    uint8_t check4 = STANDARD_ERROR;
    while(1){
        //randomize col, row and dir only up to max
        uint8_t randomdirection = rand() % 2;
        uint8_t randomcol = rand() % FIELD_COLS;
        uint8_t randomrow = rand() % FIELD_ROWS;
        
        if (check1 == STANDARD_ERROR){
            randomdirection = rand() % 2;
            randomcol = rand() % FIELD_COLS;
            randomrow = rand() % FIELD_ROWS;
            check1 = FieldAddBoat(own_field,randomcol,randomrow,randomdirection,FIELD_BOAT_TYPE_SMALL);
            if (check1 == SUCCESS){
                success += 1;
            }
        }
        if (check2 == STANDARD_ERROR){
            randomdirection = rand() % 2;
            randomcol = rand() % FIELD_COLS;
            randomrow = rand() % FIELD_ROWS;
            check2 = FieldAddBoat(own_field,randomcol,randomrow,randomdirection,FIELD_BOAT_TYPE_MEDIUM);
            if (check2 == SUCCESS){
                success += 1;
            }
        }
        if (check3 == STANDARD_ERROR){
            randomdirection = rand() % 2;
            randomcol = rand() % FIELD_COLS;
            randomrow = rand() % FIELD_ROWS;
            check3 = FieldAddBoat(own_field,randomcol,randomrow,randomdirection,FIELD_BOAT_TYPE_LARGE);
            if (check3 == SUCCESS){
                success += 1;
            }
        }
        if (check4 == STANDARD_ERROR){
            randomdirection = rand() % 2;
            randomcol = rand() % FIELD_COLS;
            randomrow = rand() % FIELD_ROWS;
            check4 = FieldAddBoat(own_field,randomcol,randomrow,randomdirection,FIELD_BOAT_TYPE_HUGE);
            if (check4 == SUCCESS){
                success += 1;
            }
        }
        if (success == 4){
            break;
        }
       
        /*
        if (FieldAddBoat(own_field,randomcol,randomrow,boatdir,FIELD_BOAT_TYPE_SMALL)){
            success+=1;
            printf("%d %d %d\n",randomcol, randomrow, boatdir);
        }
        if (FieldAddBoat(own_field,randomcol,randomrow,boatdir,FIELD_BOAT_TYPE_MEDIUM)){
            success+=1;
            printf("MEDIUM");
        }
        if (FieldAddBoat(own_field,randomcol,randomrow,boatdir,FIELD_BOAT_TYPE_LARGE)){
            success+=1;
        }
        if (FieldAddBoat(own_field,randomcol,randomrow,boatdir,FIELD_BOAT_TYPE_HUGE)){
            success+=1;
        }
        if (success == 4){
            break;
        }*/
            //place total 4 boats one for each catagory
            //break after 4 boats placed
    }
    // for each type of boat
    // while fieldaddboat(rand(col)...) != success
    
    return SUCCESS;
    
}

/**
 * Given a field, decide the next guess.
 *
 * This function should not attempt to shoot a square which has already been guessed.
 *
 * You may wish to give this function static variables.  If so, that data should be
 * reset when FieldInit() is called.
 * 
 * @param f an opponent's field.
 * @return a GuessData struct whose row and col parameters are the coordinates of the guess.  The 
 *           result parameter is irrelevant.
 */
GuessData FieldAIDecideGuess(const Field *opp_field){
    GuessData return_guess = {0, 0, 0};
    while(1){
        //randomize col and row
        static uint8_t horizontal = 0;
        static uint8_t vertical = 0;
        horizontal = rand() % 10;
        vertical = rand() % 10;
        return_guess.col = horizontal;
        return_guess.row = vertical;
        if (FieldGetSquareStatus(opp_field,return_guess.row, return_guess.col) == FIELD_SQUARE_UNKNOWN){                        //question
            return return_guess;
        } //check if it is already guessed 
    }
    return return_guess;
    
}

/** 
 * For Extra Credit:  Make the two "AI" functions above 
 * smart enough to beat our AI in more than 55% of games.
 */

