#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list list_empty(void){
    return NULL;
}

list list_add(list_elem e, list l){
    list new = malloc(sizeof(struct st_list));
    new->elem = e;
    new->next = l;
    l = new;
    return l;
}

bool list_is_empty(list l){
    return l == NULL;
}

list_elem list_head(list l){
    assert(!list_is_empty(l));
    return l->elem;
}

list list_tail(list l){
    assert(!list_is_empty(l));
    list p = l;
    l = l->next;
    free(p);
    return l;
}

list list_addr(list l, list_elem e){
    list p, q;
    q = malloc(sizeof(struct st_list));
    q->elem = e;
    q->next = NULL;
    if(!list_is_empty(l)){
        p = l;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = q;
    } else {
        l = q;
    }
    return l;
}

unsigned int list_length(list l){
    list p = l;
    unsigned int n = 0;
    while(p != NULL){
        n++;
        p = p->next;
    }
    return n;
}

list list_copy(list l){
    if (l == NULL) {
        return NULL;
    }
    list copy = malloc(sizeof(struct st_list));
    copy->elem = l->elem;
    copy->next = NULL;
    list copy_current = copy;
    list l_current = l->next;
    while (l_current != NULL) {
        list new_node = malloc(sizeof(struct st_list));
        new_node->elem = l_current->elem;
        new_node->next = NULL;
        copy_current->next = new_node;
        copy_current = new_node;
        l_current = l_current->next;
    }
    return copy;
}

void list_destroy(list l){
    list p = l;
    if (l != NULL){
        while(l->next != NULL){
            p = l;
            l = l->next;
            free(p);
        }
        free(l);
        l = NULL;
    }
}