#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

int main(void){
    bool bprint;
    stack s = stack_empty();
    stack_elem *a = stack_to_array(s);
    bprint = a==NULL;
    printf("stack_to_array() return NULL to an empty stack: %d\n", bprint);
    
    s = stack_push(s, 5);
    s = stack_pop(s);
    bprint = s==NULL;
    printf("stack_pop() still working with a stack of one element: %d\n", bprint);
    
    s = stack_push(s, 5);
    bprint = !stack_is_empty(s);
    printf("If stack is empty, elements can be inserted again: %d\n", bprint);
    
    s = stack_push(s, 6);
    s = stack_push(s, 7);
    s = stack_push(s, 8);
    stack_elem *b = malloc(stack_size(s));
    b = stack_to_array(s);
    bprint = b[0]==5 && b[1]==6 && b[2]==7 && b[3]==8;
    printf("stack_to_array() returns the elements in correct order: %d\n", bprint);

    stack_destroy(s);
    return(EXIT_SUCCESS);
}