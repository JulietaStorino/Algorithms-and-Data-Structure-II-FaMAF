#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef int list_elem;

typedef struct st_list{
    list_elem elem;
    struct st_list *next;
} *list;

list list_empty(void);
/*
 * DESC: Creates an empty list
 *
 * l = empty();
 *
 * POS: {p --> NULL}
 */

void list_add(list_elem e, list l);
/*
 * DESC: Adds an element to the beginning of the list
 *
 * l = add(e, l);
 *
 * POS: {p --> list l}
 */

bool list_is_empty(list l);
/*
 * DESC: Return true if the list is empty and false otherwise
 *
 * b = is empty(l);
 */

list_elem list_head(list l);
/*
 * DESC: Return the first element of the list
 *
 * e = head(l);
 *
 * PRE: {not is_empty(l)}
 */

void list_tail(list l);
/*
 * DESC: Delete the first element of the list
 *
 * tail(l);
 *
 * PRE: {not is_empty(l)}
 */

void list_addr(list l, list_elem e);
/*
 * DESC: Adds an element to the ending of the list
 *
 * l = addr(e, l);
 *
 * POS: {p --> list l}
 */

unsigned int list_length(list l);
/*
 * DESC: Returns the length of the list
 *
 * length = length(l);
 */

list list_copy(list l);
/*
 * DESC: Makes a copy of list l. Allocates new memory.
 *
 * copy = copy(l);
 *
 * POS: {p == l}
 */

void list_destroy(list l);
/*
 * DESC: Free memory allocated if necessary
 *
 * destroy(l);
 *
 * PRE: {p --> list l}
 * POS: {p --> NULL}
 */

#endif