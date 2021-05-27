#include "UNIXBOARD.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Game.h"
#include "Player.h"
// Define how big the player's inventory is.
//#define INVENTORY_SIZE 4
//static var for number current have
//static array of chars
static uint8_t inventorySize = 0;
static uint8_t inventory[INVENTORY_SIZE] = {0};
/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item){
    //check if it is full
        //send error 
    //store item
    //put the item into array
    //array[i+1]
    if (inventorySize == INVENTORY_SIZE){
        return STANDARD_ERROR;
    }
    else{
        inventory[inventorySize] = item;
        inventorySize++;
        return SUCCESS;
    }
    
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item){
    //declare var to iterate
    //loop through the inventory array
        //check if item exist
        //return SUCCESS;
    uint8_t index = 0;
    while (index < inventorySize){
        if (item == inventory[index]){
            return SUCCESS;
        }
        else{
            index++;
        } 
    }
    return STANDARD_ERROR;
}

