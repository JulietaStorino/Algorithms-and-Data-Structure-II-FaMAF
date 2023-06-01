#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node *front;
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    bool result = false;
    if(s != NULL){
        struct s_node *node = s->front;
        result = true;
        if(node != NULL){
            while(result && node->next != NULL){
                result = node->priority >= node->next->priority;
                node = node->next;
            }
        }
    }
    return result;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->front = NULL;
    s->size = 0u;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    if (s->front == NULL) {
        s->front = new_node;
    } else {
        if(priority >= s->front->priority){
            new_node->next = s->front;
            s->front = new_node;
        } else {
            struct s_node *node = s->front;
            struct s_node *prev;
            while (node->priority > priority && node->next != NULL) {
                prev = node;
                node = node->next;
            }
            if(node->priority <= priority){
                prev->next = new_node;
                new_node->next = node;
            } else {
                node->next = new_node;
            }
        }
    
    }
    s->size++;
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return s->size == 0u;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node * killme = s->front;
    s->front = s->front->next;
    killme = destroy_node(killme);
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *node = s->front;
    while (node != NULL) {
        struct s_node *next_node = node->next;
        destroy_node(node);
        node = next_node;
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

