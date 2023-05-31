#include <assert.h>
#include <stdlib.h>
#include "pair.h"

struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y){
    pair_t pair = malloc(sizeof(struct s_pair_t));
    pair->fst = x;
    pair->snd = y;

    assert(pair != NULL);
    return pair;
}

int pair_first(pair_t p){
    assert(p != NULL);
    int first = p->fst;

    return first;
}

int pair_second(pair_t p){
    assert(p != NULL);
    int second = p->snd;

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