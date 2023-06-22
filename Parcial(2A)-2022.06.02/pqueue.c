#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node *first;
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
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


static bool invrep(pqueue q) {
    bool result = false;
    if(q!=NULL){
        struct s_node *node = q->first;
        result = true;
        if(node != NULL){
            while(result && node->next != NULL){
                result = node->priority <= node->next->priority;
                node = node->next;
            }
        }
    }
    return result;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->first = NULL;
    q->size = 0u;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    if (q->first == NULL) {
        q->first = new_node;
    } else {
        if(priority < q->first->priority){
            new_node->next = q->first;
            q->first = new_node;
        } else {
            struct s_node *node = q->first;
            struct s_node *prev = q->first;
            while (node->priority <= priority && node->next != NULL) {
                prev = node;
                node = node->next;
            }
            if(node->priority > priority){
                prev->next = new_node;
                new_node->next = node;
            } else {
                node->next = new_node;
            }
        }
    
    }
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->first == NULL;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
    struct s_node *next_node = node->next;
    destroy_node(node);
    node = next_node;
}
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
