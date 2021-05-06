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
    
    
    ListItem *item = LinkedListNew("Head");                                     //create the first item Head
    LinkedListPrint(item);
    printf("\n");
    if (item ->nextItem == NULL){                                               // testing if it create correctly
        success_LinkedListNew ++;
    }
    if (item ->previousItem == NULL){
        success_LinkedListNew ++;
    }
    if (strcmp(item ->data, "Head") == 0){
        success_LinkedListNew ++;
    }
    
    ListItem *item1;                                                            
    item1 = LinkedListCreateAfter(item, "Tail");                                // create the second item
    if (strcmp(item1->data, "Tail") == 0){                                      // test if it created Tail
        success_LinkedListCreateAfter++;
    }
    item1 = LinkedListCreateAfter(item, "Middle");
    
    LinkedListPrint(item);
     printf("\n");
    if (strcmp(item1->data, "Middle") == 0){                                    // testing if the pointer moved to the new item create
        success_LinkedListCreateAfter++;
    }
    int index = LinkedListSize(item);                                           //testing how many item are there, which is should be three
    if (index == 3){
        success_LinkedListSize++;
    }
    
    LinkedListCreateAfter(item, "Apple");
    
    index = LinkedListSize(item);                                               //after create another item, the size should be four
    if (index == 4){
        success_LinkedListSize++;
    }
    
    
    ListItem *item2 = LinkedListCreateAfter(item, "Banana");
    LinkedListPrint(item);
    printf("\n");
    printf("\n");
    printf("Testing swap data for Middle and Banana:\n");                       //swap the Banana and Middle
    LinkedListSwapData(item1, item2);
    LinkedListPrint(item);
    printf("\n");
    printf("\n");
    printf("Testing remove data for Middle:\n");                                //removing the Middle from the list
    LinkedListRemove(item2);
    LinkedListPrint(item);
    printf("\n");
    ListItem *item3;
    ListItem *item4;
    item3 = LinkedListGetFirst(item);
    if (strcmp(item3->data, "Head") == 0){                                      //testing linklist first, at this time shouldbe head
        success_LinkedListGetFirst++;
    }
    item4 = LinkedListGetLast(item);
    if (strcmp(item4->data, "Tail") == 0){                                      //testing linklist last, at this time shouldbe tail
        success_LinkedListGetLast++;
    }
    printf("\n");
    printf("Testing swap data for Head and Tail:\n");                           //swap the Head and Tail
    LinkedListSwapData(item3, item4);
    LinkedListPrint(item);
    printf("\n");
    if (strcmp(item3->data, "Tail") == 0){                                      //testing linklist get first and last, now the head and tail should swaped
        success_LinkedListGetFirst++;
    }
    item4 = LinkedListGetLast(item);
    if (strcmp(item4->data, "Head") == 0){
        success_LinkedListGetLast++;
    }
    printf("\n");
    printf("Testing remove data for Head:\n");                                  //testing remove, removing Head
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

