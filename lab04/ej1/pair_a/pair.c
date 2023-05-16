#include <assert.h>

#include "pair.h"


pair_t pair_new(int x, int y){
    pair_t pair;
    pair.fst = x;
    pair.snd = y;

    return pair;
}

int pair_first(pair_t p){
    return p.fst;
}

int pair_second(pair_t p){
    return p.snd;
}

pair_t pair_swapped(pair_t p){
    pair_t reversed;
    reversed.fst = p.snd;
    reversed.snd = p.fst;

    assert(pair_first(reversed) == pair_second(p) && pair_second(reversed) == pair_first(p));
    return reversed;
}

pair_t pair_destroy(pair_t p){
    return p;
}