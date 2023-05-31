#include <stdlib.h>
#include <assert.h>
#define INITIAL_CAPACITY 8

#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool invrep(stack s){
    return s != NULL && s->size > 0;
}

stack stack_empty(){
    return NULL;
}

stack stack_push(stack s, stack_elem e){
    if(s == NULL){
        s = malloc(sizeof(struct _s_stack));
        s->elems = calloc(INITIAL_CAPACITY, sizeof(stack_elem));
        s->elems[0] = e;
        s->size = 1;
        s->capacity = INITIAL_CAPACITY;
        return s;
    } else {
        if(s->size == s->capacity){
            s->elems = realloc(s->elems, (s->capacity * 2) * sizeof(stack_elem));
            s->elems[s->size] = e;
            s->size++;
            s->capacity = s->capacity * 2;
        } else {
            s->elems[s->size] = e;
            s->size++;
        }
    }
    assert(invrep(s));
    return s;
}

stack stack_pop(stack s){
    assert(invrep(s));
    s->size--;
    return s;
}

unsigned int stack_size(stack s){
    return s==NULL?0u:s->size; 
}

stack_elem stack_top(stack s){
    assert(invrep(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s){
    return s == NULL || s->size == 0;
}

stack_elem *stack_to_array(stack s){
    stack_elem *result = NULL;
    if(s!=NULL && s->size>0){
        result = calloc(s->size, sizeof(stack_elem));
        for(unsigned int i = 0u; i < s->size; i++){
            result[i] = s->elems[i];
        }
    }
    return result;
}

stack stack_destroy(stack s){
    if(s!=NULL){
        free(s->elems);
        free(s);
    }
    return NULL;
}

