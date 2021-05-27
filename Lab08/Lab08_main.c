// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"


// User libraries


// **** Set any macros or preprocessor directives here ****
#define NORTH 'n'
#define SOUTH 's'
#define EAST 'e'
#define WEST 'w'
#define QUIT 'q'
// **** Declare any data types here ****
//typedef enum{
   // north, south, east, west, quit, none
//}Direction;

// **** Define any global or external variables here ****
static char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
static char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
// **** Declare any function prototypes here ****
void displayRoom(void);

int main()
{
    uint8_t dir = 0;
    uint8_t roomExits = 0;
    if (GameInit() == STANDARD_ERROR){
        printf("Failed to Load Starting Room");
        FATAL_ERROR();
    }
    
    displayRoom();
    /******************************** Your custom code goes below here ********************************/
    int check;
    while (TRUE){
        dir = getchar();
        roomExits = GameGetCurrentRoomExits();
        switch (dir){
            case NORTH:
                if (roomExits & GAME_ROOM_EXIT_NORTH_EXISTS){
                    check = GameGoNorth();
                    if (check == STANDARD_ERROR){
                        FATAL_ERROR();
                    }
                }
                break;
            case SOUTH:
                if (roomExits & GAME_ROOM_EXIT_SOUTH_EXISTS){
                    check = GameGoSouth();
                    if (check == STANDARD_ERROR){
                        FATAL_ERROR();
                    }
                }
                break;
            case EAST:
                if (roomExits & GAME_ROOM_EXIT_EAST_EXISTS){
                    check = GameGoEast();
                    if (check == STANDARD_ERROR){
                        FATAL_ERROR();
                    }
                }
                break;
            case WEST:
                if (roomExits & GAME_ROOM_EXIT_WEST_EXISTS){
                    check = GameGoWest();
                    if (check == STANDARD_ERROR){
                        FATAL_ERROR();
                    }
                }
                break;
            case QUIT:
                printf("Good Bye!");
                exit(0);
                break;
            default:
                printf("Invaild Direction");
                break;
        }
        
        //check if playerhasmoved and update to false
        displayRoom();
        while(getchar()!='\n');
    }
    

    /**************************************************************************************************/
}

void displayRoom(void){
    //get the exit flag locally
    //get title and description save them in global var
    //print title description
    //see which room exist and print them
    //print enter dir message
    GameGetCurrentRoomTitle(title);
    printf("%s\n",title);
    GameGetCurrentRoomDescription(description);
    printf("%s\n",description);
    printf("Exits:");
        if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS) {
            printf("n ");
        }
        if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS) {
            printf("e ");
        }
        if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS) {
            printf("s ");
        }
        if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
            printf("w ");
        }
    printf("\n");
    printf("Pick a direction to go to the next room:");
    
}