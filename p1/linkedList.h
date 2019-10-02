#include <stdlib.h>

typedef struct generic_list GENERIC_LIST_t;
//Union holds only one of these element types
typedef union element{
//TODO TASK 2
    
    char c;
    signed long int i;
    double d;
    char *s;
 //   char *name;
   GENERIC_LIST_t *list;
} ELEMENT_t;

//Use this enum type to specify which element type is being used
typedef enum element_type{
//TODO TASK 3
   char_type, int_type, double_type, string_type
} ELEMENT_TYPE_e;

//Item in a list; holds element, element type, and the address of the next item
typedef struct generic_list_item{
//TODO TASK 4
    char* name;
    ELEMENT_TYPE_e type;
    //element
    ELEMENT_t element;
    //enum type
   // ELEMENT_TYPE_e type;     
    struct generic_list_item* nextItem;
} GENERIC_LIST_ITEM_t;

//List structure; Has pointer to first item and a size
typedef struct generic_list{
//TODO TASK 6
//    typedef struct GENERIC_LIST_t {
        int size;
        GENERIC_LIST_ITEM_t *head, *last;
  //  }
} GENERIC_LIST_t;
 
void printItem(const GENERIC_LIST_ITEM_t *item); // TASK 5
void addElement(GENERIC_LIST_t *list, ELEMENT_TYPE_e type, ELEMENT_t element, char* name); //TASK 7
//void addElement(GENERIC_LIST_t *list, ELEMENT_TYPE_e type, variable_t var);
void removeElement(GENERIC_LIST_t *list,int index); //TASK 8
void printList(const GENERIC_LIST_t *list); //TASK 9
void printing(const GENERIC_LIST_t *list, char* name);
GENERIC_LIST_ITEM_t search(const GENERIC_LIST_t *list, char* name);
