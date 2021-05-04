// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "LinkedList.h"

int main(void)
{   
    int success_LinkedListNew;
    ListItem *item = LinkedListNew("Head");
    //printf("%s", item->data);
    //printf("\n");
    //check linked list create after
    //verify that nodes are in correct order
    LinkedListPrint(item);
    //printf("\n");
    if (item ->nextItem == NULL){
        success_LinkedListNew ++;
    }
    if (item ->previousItem == NULL){
        success_LinkedListNew ++;
    }
    if (strcmp(item ->data, "Head") == 0){
        success_LinkedListNew ++;
    }
    printf("%i",success_LinkedListNew);
    
    
    
    
    while(1);
}

