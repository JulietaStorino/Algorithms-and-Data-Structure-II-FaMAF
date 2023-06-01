#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    card_t card;
    player_t player;
    unogame_t next;
};

unogame_t
uno_newgame(card_t card) {
    unogame_t uno; 
        uno = malloc(sizeof(struct s_ugame));
        uno->card = card;
        uno->player = NO_PLAYER;
        uno->next = NULL;
    return uno;
}

card_t
uno_topcard(unogame_t uno) {
    return uno->card;
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    unogame_t new_uno = malloc(sizeof(struct s_ugame));
    new_uno->card = c;
    player_t cardplayer = uno->player;
    if(card_get_type(uno_topcard(uno)) == skip){
        new_uno->player = (cardplayer + 2) % NUM_PLAYERS;
    }else{
        new_uno->player = (cardplayer + 1) % NUM_PLAYERS;
    }
    new_uno->next = uno;
    uno = new_uno;
    return uno;
}

unsigned int
uno_count(unogame_t uno) {
    unsigned int counter = 0u;
    for(unogame_t addrs = uno;addrs != NULL; addrs = addrs->next){
        ++counter;
    }
    return counter;
}

bool
uno_validpile(unogame_t uno) {
    bool ret = true;
    card_t aux = uno->card;
    uno = uno->next;
    unogame_t firstgame;
    for(unogame_t addrs = uno; addrs != NULL; addrs = addrs->next){
        firstgame = addrs;
        ret = ret && card_compatible(aux, addrs->card);
        aux = addrs->card;
    }
    if(card_get_type(uno_topcard(firstgame))== change_color){
        ret = false;
    }

    return ret;
}

color_t
uno_currentcolor(unogame_t uno) {
    card_t aux = uno_topcard(uno);
    return card_get_color(aux);
}

player_t
uno_nextplayer(unogame_t uno) {
    card_t aux = uno_topcard(uno);
    player_t ret = uno->player;
    if(card_get_type(aux)==skip){
        ret = (ret + 2) % NUM_PLAYERS;
    }else{
        ret = (ret + 1) % NUM_PLAYERS;
    }
    return ret;
}



card_t *
uno_pile_to_array(unogame_t uno) {
    unsigned int clength = uno_count(uno);
    card_t *ret = malloc(clength*sizeof(unogame_t));
    for(int i = clength-1; i >= 0; --i){
        ret[i] = uno->card;
        uno = uno->next;
    }
    return ret;
}

unogame_t
uno_destroy(unogame_t uno) {
   unogame_t aux = uno->next;
   while(aux != NULL){
	   card_destroy(uno->card);
	   free(uno);
	   uno = aux;
       aux = aux->next;
   }
   card_destroy(uno->card);
   free(uno);
   return uno;
}
