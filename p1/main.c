#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <string.h>
//check the character type
int typeCheck(char *check)
{
    char* tokenD = strchr(check,'.');
    char* tokenS = strchr(check, '"');
    char* tokenC = strchr(check, '\'');
    char* tokenL = strchr(check, ']');
    //double type
    if(tokenD )
      return 1;
    //string type
    else if(tokenS)
      return 0;
    //char type
    else if(tokenC)
      return -1;
    //list type
    else if(tokenL)
       return 3;
    //int type
    else
      return 2;
}


int main()
{
    PARSE_RESULT_t* result;
    //generic list
    GENERIC_LIST_t myList;
    //initialize the list
    myList.head = NULL;
    myList.size = 0; 
    //Create element object
    char* LOp;
//    char* RightOp1;
//    char* RightOp2;
    ELEMENT_t element;
    GENERIC_LIST_ITEM_t ITEMLeft={"ab",int_type,element,NULL};
    GENERIC_LIST_ITEM_t ITEMRight1= {"cd",int_type,element, NULL} ;
    GENERIC_LIST_ITEM_t ITEMRight2= {"ef", int_type,element,NULL};
    while(1) {
        char input[100];
        char* ptrInput; 
        printf(">>>"); 
        ptrInput = input;
        //scanf("%14s",ptrInput);
        fgets(ptrInput, 100, stdin);
        result = parse_string(ptrInput);
 
        char* first = result->left_operand;
        char* second = result->right_operand1;
        char* third = result->right_operand2;
        //Test PRINT_OP parsing
        if(result->optype == PRINT_OP){
            LOp = result->left_operand;
            //printList(&myList);
            printing(&myList, LOp);
        }
        //Test APPEND_OP parsing
       else if(result->optype == APPEND_OP){
            printf("Append Variable: %s",result->left_operand);
            //check the type first to make sure it is a list
            int check = typeCheck(result->right_operand1);
            if (check == 3)
            {
              //add element
               LOp = result->left_operand;
               ITEMLeft.name = LOp;
               addElement(&myList, string_type,ITEMLeft.element ,LOp );
            } 
        }
        //Test other parsing
        else{
            //If there are two operands, there must be some arithmetic
            if(result->right_operand2 != NULL){
                //to check the type
                int check = typeCheck(result->right_operand1);
                int index = 0;
                //check if the variable is already in there
                //GENERIC_LIST_ITEM_t lookRight1 = search(&myList, second);
                //GENERIC_LIST_ITEM_t lookRight2 = search(&myList, third);
                switch(result->optype){
                    case ADD_OP: //Test add operation
                        //int type
                        if(check == 2){
                            index++;
                            int x = atoi(result->right_operand1);
                            int y = atoi(result->right_operand2);
                            LOp = result->left_operand;
                            ITEMLeft.name = LOp;
                            int z = x+y;
                            ITEMLeft.element.i = z;
                            addElement(&myList,int_type,ITEMLeft.element,LOp);
                        }
                        //double type
                        if(check == 1){
                            
                            double x = atof(second);
                            double y = atof(third);
                            LOp = first;
                            ITEMLeft.name = LOp;
                            double z = x+y;
                            ITEMLeft.element.d = z;
                            addElement(&myList,double_type,ITEMLeft.element,LOp);
                        }
                        //char type
                        if(check == -1)
                        {
                           GENERIC_LIST_ITEM_t lookRight1 = search(&myList, second);
                           GENERIC_LIST_ITEM_t lookRight2 = search(&myList, third);
                           lookRight1 = ITEMRight1;
                           lookRight2 = ITEMRight2;
                           int x = lookRight1.element.i;
                           int y = lookRight2.element.i;
                           int z = x+y;
                           LOp = result->left_operand;
                           ITEMLeft.name = LOp;
                           ITEMLeft.element.i = z;
                           addElement(&myList, int_type, ITEMLeft.element,LOp);
                        }
                        break;
                    case SUB_OP: // Test sub operation
                        //double type
                        if(check == 1){
                            double x = atof(second);
                            double y = atof(third);
                            LOp = first;
                            ITEMLeft.name = LOp;
                            double z = x-y;
                            ITEMLeft.element.d = z;
                            addElement(&myList,double_type,ITEMLeft.element,LOp);
                        }
                        //int type
                        if(check == 2){
                            int x = atoi(result->right_operand1);
                            int y = atoi(result->right_operand2);
                            LOp = result->left_operand;
                            ITEMLeft.name = LOp;
                            int z = x+y;
                            ITEMLeft.element.i = z;
                            addElement(&myList,int_type,ITEMLeft.element,LOp);
                        }
                        break;
                    case MULT_OP: // Test mult operation
                        //int type
                        if(check == 2){
                            int x = atoi(result->right_operand1);
                            int y = atoi(result->right_operand2);
                            LOp = result->left_operand;
                            ITEMLeft.name = LOp;
                            int z = x*y;
                            ITEMLeft.element.i = z;
                            addElement(&myList,int_type,ITEMLeft.element,LOp);
                        }
                        //double type
                        if(check == 1){
                            double x = atof(second);
                            double y = atof(third);
                            LOp = first;
                            ITEMLeft.name = LOp;
                            double z = x*y;
                            ITEMLeft.element.d = z;
                            addElement(&myList,double_type,ITEMLeft.element,LOp);
                        }
                        break;

                    case DIV_OP: // Test div operation
                        //int type
                        if(check == 2){
                            int x = atoi(result->right_operand1);
                            int y = atoi(result->right_operand2);
                            LOp = result->left_operand;
                            ITEMLeft.name = LOp;
                            int z = x/y;
                            ITEMLeft.element.i = z;
                            addElement(&myList,int_type,ITEMLeft.element,LOp);
                        }
                        //double type
                        if(check == 1){
                            double x = atof(second);
                            double y = atof(third);
                            LOp = first;
                            ITEMLeft.name = LOp;
                            double z = x/y;
                            ITEMLeft.element.d = z;
                            addElement(&myList,double_type,ITEMLeft.element,LOp);
                        }
                        break;
                    default:
                        break;
                }
            }
            //If no second operand, just print left_operand and right_operand1
            //assignment operator
            else{
                int check = typeCheck(second);
                            //int type
                            if(check == 2){
                               LOp = first;
                               ITEMLeft.name = LOp;
                               ITEMLeft.element.i = atoi(second);
                               addElement(&myList,int_type,ITEMLeft.element, LOp);
                            }
                            //if it is a double type
                            else if(check == 1)
                            {
                               LOp = first;
                               ITEMLeft.name = LOp;
                               ITEMLeft.element.d = atof(second);
                               addElement(&myList, double_type, ITEMLeft.element, LOp);
                            }
                            //string
                            else if(check == 0)
                            {
                               LOp = first;
                               ITEMLeft.name = LOp;
                               ITEMLeft.element.s = second;
                               addElement(&myList, string_type, ITEMLeft.element, LOp);
                            }
                            //char type
                            else if(check == -1)
                            {
                               LOp =first;
                               ITEMLeft.name = LOp;
                               ITEMLeft.element.c = second[0];
                               addElement(&myList, char_type, ITEMLeft.element, LOp);
                            }
                            //list
                            else if(check == 3)
                            {
                               LOp = first;
                               ITEMLeft.name = LOp;
                               ITEMLeft.element.s = second;
                               addElement(&myList, string_type, ITEMLeft.element, LOp);
                            }                        
            }
        }
    }
    //We should free the parse_string result here.
    return 0;
}

