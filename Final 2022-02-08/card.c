#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include "card.h"

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

static bool
invrep(card_t c) {
    // Invariante de representación
    bool valid=false;
    valid = c != NULL;
    if((c->type) == normal){
        valid = ((c->num) <= 9);
    }else{
        valid = ((c->num) == 0);
    }
    return valid;
}

card_t
card_new(unsigned int num, color_t color, type_t s) {
    assert(num<=9);
    card_t card = malloc(sizeof(struct s_card));
    card->num = num;
    card->color = color;
    card->type = s;
    assert(invrep(card));
    return card;
}


type_t
card_get_number(card_t card) {
    assert(invrep(card));
    return card->num;
}

color_t
card_get_color(card_t card) {
    assert(invrep(card));
    return card->color;
}

type_t
card_get_type(card_t card) {
    assert(invrep(card));
    return card->type;
}

bool
card_samecolor(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    bool result;
    result = (card_get_color(c1) == card_get_color(c2));
    return result;
}


bool
card_samenum(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    bool result;
    result = (card_get_number(c1) == card_get_number(c2));
    return result;
}

bool
card_compatible(card_t new_card, card_t pile_card) {
    bool compatible=false; 
    assert(invrep(new_card) && invrep(pile_card));
    if(card_samecolor(new_card, pile_card) || (card_get_type(new_card) == change_color)){
        compatible=true;
    }
    else if ((card_get_type(pile_card) == card_get_type(new_card)) && (card_get_type(new_card) == skip))
    {
        compatible=true;
    }
    else if ((card_get_type(pile_card) == card_get_type(new_card)) && (card_get_type(new_card) == normal))
    {
        compatible = card_samenum(new_card, pile_card);
    }
    return compatible;
}

card_t
card_destroy(card_t card) {
    invrep(card);
    free(card);
    return card;
}


