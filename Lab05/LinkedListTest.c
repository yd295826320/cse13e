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
    int success_LinkedListCreateAfter;
    int success_LinkedListSize;
    int success_LinkedListGetFirst;
    int success_LinkedListGetLast;
    
    
    ListItem *item = LinkedListNew("Head");
    //printf("%s", item->data);
    //printf("\n");
    //check linked list create after
    //verify that nodes are in correct order
    LinkedListPrint(item);
    printf("\n");
    if (item ->nextItem == NULL){
        success_LinkedListNew ++;
    }
    if (item ->previousItem == NULL){
        success_LinkedListNew ++;
    }
    if (strcmp(item ->data, "Head") == 0){
        success_LinkedListNew ++;
    }
    
    ListItem *item1;
    LinkedListCreateAfter(item, "Tail");
    item1 = LinkedListCreateAfter(item, "Middle");
    
    LinkedListPrint(item);
     printf("\n");
    if (strcmp(item1->data, "Middle") == 0){
        success_LinkedListCreateAfter++;
    }
    int index = LinkedListSize(item);
    if (index == 3){
        success_LinkedListSize++;
    }
    
    LinkedListCreateAfter(item, "Apple");
    if (strcmp(item->data, "Apple") == 0){
        success_LinkedListCreateAfter++;
    }
    
    
    
    ListItem *item2 = LinkedListCreateAfter(item, "Banana");
    LinkedListPrint(item);
    printf("\n");
    LinkedListSwapData(item1, item2);
    LinkedListPrint(item);
    printf("\n");
    LinkedListRemove(item2);
    LinkedListPrint(item);
    printf("\n");
    ListItem *item3;
    item3 = LinkedListGetFirst(item);
    if (strcmp(item3->data, "Head") == 0){
        success_LinkedListGetFirst++;
    }
    item3 = LinkedListGetLast(item);
    if (strcmp(item3->data, "Tail") == 0){
        success_LinkedListGetLast++;
    }
    
    printf("%i/3 success_LinkedListNew",success_LinkedListNew);
    printf("\n");
    printf("%i/1 success_LinkedListCreateAfter",success_LinkedListCreateAfter);
    printf("\n");
    printf("%i/1 success_LinkedListSize",success_LinkedListSize);
    printf("\n");
    printf("%i/1 success_LinkedListGetFirst",success_LinkedListGetFirst);
    printf("\n");
    printf("%i/1 success_LinkedListGetLast",success_LinkedListGetLast);
    printf("\n");
    
    
    while(1);
}

