#include <stdio.h>
#include "linkedList.h"

/*
Print items based on their type
*/
void printItem(const GENERIC_LIST_ITEM_t *item){
//TODO TASK 5
 //#5
        switch(item->type) 
        {
            case int_type:
                //case statements if you receive different types(char, int or double)
                printf("%ld \n",item->element.i );
                break;
            case char_type:
                printf("%c \n", item->element.c);
                break;
            case double_type:
                printf("%f \n", item->element.d);
                break;
            case string_type:
                printf("%s \n", item->element.s);
                break;
            default: 
                printf("Wrong! \n");
        }
}

/*
Add elements to list. Requires a type and an element. Creates dynamic memory
to hold the GENERIC_LIST_ITEM_t structure
*/
void addElement(GENERIC_LIST_t *list, ELEMENT_TYPE_e type, ELEMENT_t element, char* varName){
  GENERIC_LIST_ITEM_t *item = calloc(1,sizeof(GENERIC_LIST_ITEM_t));
  item->element = element;
  item->type = type;
  item->name = varName;
  GENERIC_LIST_ITEM_t *last_item;
  if(list->size == 0){
    list->head = item;
    list->size = 1;
  }
  else{
    last_item = list->head;
    while(last_item->nextItem != NULL){
      last_item = last_item->nextItem;
    }
    last_item->nextItem = item;
    list->size += 1;
  }
}
/*
Remove item from list at given index
*/
void removeElement(GENERIC_LIST_t *list,int index){
//TODO TASK 8
    //remove the first item
    if(index == 0)
    {
        list -> head = list -> head -> nextItem;
       // free(list->head);
    }
    else if( index > list->size)
    {
        return;
    }
    else{
        GENERIC_LIST_ITEM_t *p ;
        GENERIC_LIST_ITEM_t *previous=list->head;
        int i = 0;
        for(i = 1; i < index; i++)
        {
            previous = list->head->nextItem;
        }
        p = previous->nextItem;
//        p->nextItem = previous->nextItem;
        previous->nextItem = p->nextItem;
    }
    list->size--; 
}

/*
Print the list in sequence
*/
void printList(const GENERIC_LIST_t *list){
//TODO TASK 9
    //
    //printf("List Size: %d \n", list->size);
    GENERIC_LIST_ITEM_t *ptr = list->head;
    //while(ptr != NULL)
    int i = 0;
    for(i=0; i< list->size; i++)
    {
        printItem(ptr);
        ptr = ptr->nextItem;
    }
}


//print function
void printing(const GENERIC_LIST_t *list, char* name){
    GENERIC_LIST_ITEM_t *ptr = list->head;
    int i = 0;
    int match = 3;
    int len = 15;
    for(i=0; i< list->size; i++)
    {
        //check if the name matches and print that single item
        match = strncmp(ptr->name,name,len);
        if (match == 0)
        {
            printItem(ptr);
            return;
        }
        ptr = ptr->nextItem;
    }
}
//search function
GENERIC_LIST_ITEM_t search(const GENERIC_LIST_t *list, char* name)
{
   GENERIC_LIST_ITEM_t *ptr = list->head;
   int i =0;
   int match = 3;
   int len = 15;
   for(i = 0; i < list->size; i++)
   {
      match = strncmp(ptr->name, name, len);
      if (match == 0)
      {
        return *ptr;
      }
      ptr = ptr->nextItem; 
   }
   ptr = NULL;
   return *ptr;
}
