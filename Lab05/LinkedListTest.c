// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "LinkedList.h"

int main(void)
{   
    int success_LinkedListNew = 0;
    int success_LinkedListCreateAfter= 0;
    int success_LinkedListSize = 0;
    int success_LinkedListGetFirst = 0;
    int success_LinkedListGetLast = 0;
    
    
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
    item1 = LinkedListCreateAfter(item, "Tail");
    if (strcmp(item1->data, "Tail") == 0){
        success_LinkedListCreateAfter++;
    }
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
    index = LinkedListSize(item);
    if (index == 4){
        success_LinkedListSize++;
    }
    
    
    ListItem *item2 = LinkedListCreateAfter(item, "Banana");
    LinkedListPrint(item);
    printf("\n");
    printf("\n");
    printf("Testing swap data for Middle and Banana:\n");
    LinkedListSwapData(item1, item2);
    LinkedListPrint(item);
    printf("\n");
    printf("\n");
    printf("Testing remove data for Middle:\n");
    LinkedListRemove(item2);
    LinkedListPrint(item);
    printf("\n");
    ListItem *item3;
    ListItem *item4;
    item3 = LinkedListGetFirst(item);
    if (strcmp(item3->data, "Head") == 0){
        success_LinkedListGetFirst++;
    }
    item4 = LinkedListGetLast(item);
    if (strcmp(item4->data, "Tail") == 0){
        success_LinkedListGetLast++;
    }
    printf("\n");
    printf("Testing swap data for Head and Tail:\n");
    LinkedListSwapData(item3, item4);
    LinkedListPrint(item);
    printf("\n");
    if (strcmp(item3->data, "Tail") == 0){
        success_LinkedListGetFirst++;
    }
    item4 = LinkedListGetLast(item);
    if (strcmp(item4->data, "Head") == 0){
        success_LinkedListGetLast++;
    }
    printf("\n");
    printf("Testing remove data for Head:\n");
    LinkedListRemove(item4);
    LinkedListPrint(item);
    printf("\n");
    
    printf("%i/3 success_LinkedListNew",success_LinkedListNew);
    printf("\n");
    printf("%i/2 success_LinkedListCreateAfter",success_LinkedListCreateAfter);
    printf("\n");
    printf("%i/2 success_LinkedListSize",success_LinkedListSize);
    printf("\n");
    printf("%i/2 success_LinkedListGetFirst",success_LinkedListGetFirst);
    printf("\n");
    printf("%i/2 success_LinkedListGetLast",success_LinkedListGetLast);
    printf("\n");
    
    
    while(1);
}

