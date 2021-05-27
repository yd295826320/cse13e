#include "UNIXBOARD.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Game.h"
#include "Player.h"
// The initial room that Game should initialize to.
//#define STARTING_ROOM 32

static struct{
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t north;
    uint8_t east;
    uint8_t south;
    uint8_t west;
}currentRoom = {};

int LoadRoom(uint16_t roomNumber);

// These variable describe the maximum string length of the room title and description respectively.
// Note that they don't account for the trailing '\0' character implicit with C-style strings.
//#define GAME_MAX_ROOM_TITLE_LENGTH 21
//#define GAME_MAX_ROOM_DESC_LENGTH 255

/**
 * This enum defines flags for checking the return values of GetCurrentRoomExits(). Usage is as
 * follows:
 *
 * if (GetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
 *   // The current room has a west exit.
 * }
 *
 * @see GetCurrentRoomExits
 */
/*typedef enum {
    GAME_ROOM_EXIT_WEST_EXISTS  = 0b0001,
    GAME_ROOM_EXIT_SOUTH_EXISTS = 0b0010,
    GAME_ROOM_EXIT_EAST_EXISTS  = 0b0100,
    GAME_ROOM_EXIT_NORTH_EXISTS = 0b1000
} GameRoomExitFlags;*/
//struct current (title,descibtion, roomexists)
//pizza
/**
 * These function transitions between rooms. Each call should return SUCCESS if the current room has
 * an exit in the correct direction and the new room was able to be loaded, and STANDARD_ERROR
 * otherwise.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded.
 */
int GameGoNorth(void){
    //check if c.north != 0
    //return load(currentroom.north)
    if (currentRoom.north != 0){
        return LoadRoom(currentRoom.north);
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoEast(void){
    if (currentRoom.east != 0){
        return LoadRoom(currentRoom.east);
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoSouth(void){
    if (currentRoom.south != 0){
        return LoadRoom(currentRoom.south);
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoWest(void){
    if (currentRoom.west != 0){
        return LoadRoom(currentRoom.west);
    }
    return STANDARD_ERROR;
}

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void){
    //load initial room(room 0)
    //fopens
    return LoadRoom(STARTING_ROOM);
}

/**
 * Copies the current room title as a NULL-terminated string into the provided character array.
 * Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param title A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possible titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title){
    strncpy(title, currentRoom.title, GAME_MAX_ROOM_TITLE_LENGTH + 1);
    return strlen(title);
}

/**
 * GetCurrentRoomDescription() copies the description of the current room into the argument desc as
 * a C-style string with a NULL-terminating character. The room description is guaranteed to be less
 * -than-or-equal to GAME_MAX_ROOM_DESC_LENGTH characters, so the provided argument must be at least
 * GAME_MAX_ROOM_DESC_LENGTH + 1 characters long. Only a NULL-character is copied if there was an
 * error so that the resultant output string length is 0.
 * @param desc A character array to copy the room description into.
 * @return The length of the string stored into `desc`. Note that the actual number of chars
 *          written into `desc` will be this value + 1 to account for the NULL terminating
 *          character.
 */
int GameGetCurrentRoomDescription(char *desc){
    strncpy(desc, currentRoom.description, GAME_MAX_ROOM_DESC_LENGTH + 1);
    return strlen(desc);
}

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */
uint8_t GameGetCurrentRoomExits(void){
    uint8_t var = 0;
    if (currentRoom.west){
        var ^= GAME_ROOM_EXIT_WEST_EXISTS;
    }
    if (currentRoom.south){
        var ^= GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (currentRoom.east){
        var ^= GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (currentRoom.north){
        var ^= GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    return var;
}



int LoadRoom(uint16_t roomNumber){
    
    FILE *room;
    char roomFileName[50];
    
    sprintf(roomFileName, "RoomFiles/room%d.txt",roomNumber);
    
    if ((room = fopen(roomFileName,"rb")) == NULL){
        return STANDARD_ERROR;
    }
    
    fgetc(room);
    fgetc(room);
    fgetc(room);
    
    uint8_t titleLength = fgetc(room);
    
    if(titleLength == GAME_MAX_ROOM_TITLE_LENGTH || titleLength == 0 || fgets(currentRoom.title, titleLength + 1, room) == NULL || titleLength == EOF){
        
        fclose(room);
        return STANDARD_ERROR;
    }
    
    currentRoom.title[titleLength] = '\0';
    char skip[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t checkf = 0;
    while (1){ //put EOF to end
        uint8_t itemreq = fgetc(room);
        if(itemreq == 0){
            break;
        }
        while(itemreq > 0){
            uint8_t item = fgetc(room);
            if (FindInInventory(item) == TRUE){
                checkf = 1;
                break;
            }
            itemreq --;
        }
        if (checkf == 1){
            break;
        }
        uint8_t descLength = fgetc(room);
        fgets(skip, descLength + 1, room);
        uint8_t containLen = fgetc(room);  
        fseek(room, (containLen), SEEK_CUR);
        fseek(room, 4L, SEEK_CUR);
        if(fgetc(room) == EOF){
            fclose(room);
            return STANDARD_ERROR;
        }
        else{
            fseek(room, -1L, SEEK_CUR);
        }
    }
    
    uint8_t descLength = fgetc(room);
    
    if(descLength == GAME_MAX_ROOM_TITLE_LENGTH || descLength == 0 || fgets(currentRoom.description, descLength + 1, room) == NULL || descLength == EOF){
        fclose(room);
        return STANDARD_ERROR;
    }
    
    currentRoom.description[descLength] = '\0';
    
    uint8_t containLen = fgetc(room);
    while(containLen > 0){;
            uint8_t containitem = fgetc(room);
            AddToInventory(containitem);
            containLen--;
        }
    
    currentRoom.north = fgetc(room);
    currentRoom.east = fgetc(room);
    currentRoom.south = fgetc(room);
    currentRoom.west = fgetc(room);
    fclose(room);
    return SUCCESS;
}
