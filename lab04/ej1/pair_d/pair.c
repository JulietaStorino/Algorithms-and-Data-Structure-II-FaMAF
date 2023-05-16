#include <assert.h>
#include <stdlib.h>
#include "pair.h"

struct s_pair_t {
    elem fst;
    elem snd;
};

pair_t pair_new(elem x, elem y){
    pair_t pair = malloc(sizeof(struct s_pair_t));
    pair->fst = x;
    pair->snd = y;

    assert(pair != NULL);
    return pair;
}

elem pair_first(pair_t p){
    assert(p != NULL);
    elem first = p->fst;

    return first;
}

elem pair_second(pair_t p){
    assert(p != NULL);
    elem second = p->snd;

    return second;
}

pair_t pair_swapped(pair_t p){
    assert(p != NULL);
    pair_t q = pair_new(p->snd, p->fst);

    assert(pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p));
    return q;
}

pair_t pair_destroy(pair_t p){
    free(p);
    p = NULL;
    return p;
}