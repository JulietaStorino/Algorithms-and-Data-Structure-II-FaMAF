#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef int list_elem;

typedef struct st_list *list;

struct st_list{
    list_elem elem;
    list next;
};

list list_empty(void);
/*
 * DESC: Creates an empty list
 *
 * l = empty();
 *
 * POS: {l --> NULL}
 */

list list_add(list_elem e, list l);
/*
 * DESC: Adds an element to the beginning of the list
 *
 * l = add(e, l);
 *
 * POS: {l --> list}
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

list list_tail(list l);
/*
 * DESC: Delete the first element of the list
 *
 * l = tail(l);
 *
 * PRE: {not is_empty(l)}
 */

list list_addr(list l, list_elem e);
/*
 * DESC: Adds an element to the ending of the list
 *
 * l = addr(e, l);
 *
 * POS: {l --> list}
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
 * POS: {copy == l}
 */

void list_destroy(list l);
/*
 * DESC: Free memory allocated if necessary
 *
 * destroy(l);
 *
 * PRE: {l --> list}
 * POS: {l --> NULL}
 */

#endif