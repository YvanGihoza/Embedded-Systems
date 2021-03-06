#include <string.h>
#include <stdlib.h>
#include "linkedList.h"

//Enum to hold types of operations
typedef enum optype{ADD_OP,SUB_OP,MULT_OP,DIV_OP,PRINT_OP,APPEND_OP,ASSIGN_OP} OPTYPE_e;

//Result structure to hold operands and operation type
typedef struct parse_result{
    char* left_operand;
    char* right_operand1;
    char* right_operand2;
    OPTYPE_e optype;  
    
} PARSE_RESULT_t;

//element struct
/*typedef struct elt{
   char *value;
   ELEMENT_TYPE_e type;
}ELT_t;*/
//variables check
//structures to hold variables
typedef struct variable{  
//    char *name;
   // ELEMENT_TYPE_e type;
    ELEMENT_t* element;
    GENERIC_LIST_t* list;
} variable_t;

//Command Types
#define PRINT_COMMAND "print("
#define APPEND_COMMAND "append("
//Max length of string input, and max length of variable
#define MAX_BUFFER_LEN 100+1
#define MAX_VAR_LEN 15+1

// parse_string function
PARSE_RESULT_t *parse_string(const char* input_buffer);





