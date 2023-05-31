#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
};

static bool invrep(stack s){
    return (s != NULL); 
}

stack stack_empty(){
    return NULL;
}

stack stack_push(stack s, stack_elem e){
    stack new = malloc(sizeof(struct _s_stack));
    new->elem = e;
    if (s == NULL){
        new->next = NULL;
    } else {
        new->next = s;
    }
    assert(invrep(new));
    return new;
}

stack stack_pop(stack s){
    assert(invrep(s));
    stack new = s->next;
    free(s);
    return new;
}

unsigned int stack_size(stack s){
    unsigned int size = 0u;
    while (s != NULL){
        size++;
        s = s->next;
    }
    return size;
}

stack_elem stack_top(stack s){
    assert(invrep(s));
    return s->elem;
}

bool stack_is_empty(stack s){
    return s == NULL;
}

stack_elem *stack_to_array(stack s){
    stack_elem *array = NULL;
    if (s != NULL){
        unsigned int size = stack_size(s);
        array = calloc(sizeof(stack_elem), size);
        for(unsigned int i = 1u; i <= size; i++){
            array[size - i] = s->elem;
            s = s->next;
        }
    }
    return array;
}

stack stack_destroy(stack s){
    while (s != NULL){
        stack next = s->next;
        free(s);
        s = next;
    }
    return NULL;
}