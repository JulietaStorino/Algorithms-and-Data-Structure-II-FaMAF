#include "playerOnB.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _node
{
    struct _node* next;
    type_t e;
};

struct _PlayerOnB
{
    struct _node* head;
    unsigned int score;
    unsigned int size;
};

/**
 * @brief Invariante de represetación
 *
 * @param pob playerOnBoard
 * @return true Si pob es una estructura pob válida (pob puede ser válida y
 *              que la función playerOnB_is_valid(pob) de False)
 * @return false Si pob no es valida
 */
static bool invrep(PlayerOnB pob)
{
    unsigned int score = 0;
    unsigned int size = 0;
    if (pob!=NULL){
        struct _node* head = pob->head;
        while(head != NULL){
            if(head->e == Town){
                score += 1;
            } else if(head->e == City){
                score += 2;
            }
            size += 1;
            head = head->next;
        }
    }
    return (pob==NULL)? false : score==pob->score && size==pob->size;
}

/**
 * @brief Crea un nodo de la lista nuevo
 *
 * @param e Elemento que contendrá el nodo
 * @return struct _node* Nuevo nodo creado o NULL si no hay memoria
 */
static struct _node* create_node(type_t e)
{
    struct _node* res = malloc(sizeof(struct _node));
    if (res != NULL)
    {
        res->e = e;
        res->next = NULL;
    }
    return res;
}

/**
 * @brief Destruye el nodo node
 *
 * @param node Nodo a ser destruido
 * @return struct _node* Devuelve NULL si el nodo se destruyó correctamente
 */
static struct _node* destroy_node(struct _node* node)
{
    if (node != NULL)
    {
        free(node);
        node = NULL;
    }
    assert(node == NULL);
    return node;
}

static PlayerOnB playerOnB_add_builging(PlayerOnB pob, type_t type){
    struct _node* head = pob->head;
    struct _node* new_node = create_node(type);
    if(pob->head == NULL){
        pob->head = new_node;
    } else {
        while(head->next != NULL){
            head = head->next;
        }
        head->next = new_node;
    }
    pob->size += 1;
    return pob;
}

PlayerOnB playerOnB_empty()
{
    PlayerOnB res = malloc(sizeof(struct _PlayerOnB));
    if (res != NULL)
    {
        res->head = NULL;
        res->score = 0;
        res->size = 0;
    }
    return res;
    assert(invrep(res));
}

PlayerOnB playerOnB_add_Road(PlayerOnB pob)
{
    assert(invrep(pob));
    pob = playerOnB_add_builging(pob, Road);
    assert(invrep(pob));
    return pob;
}

PlayerOnB playerOnB_add_Town(PlayerOnB pob)
{
    assert(invrep(pob));
    struct _node* head = pob->head;
    struct _node* new_node = create_node(Town);
    if(pob->head == NULL){
        pob->head = new_node;
    } else {
        while(head->next != NULL){
            head = head->next;
        }
        head->next = new_node;
    }
    pob->size += 1;
    pob->score += 1;
    assert(invrep(pob));
    return pob;
}

/* MODIFICADORES */

PlayerOnB playerOnB_upgrade_town(PlayerOnB pob, Position pos)
{
    assert(invrep(pob));
    if(1 <= pos && pos <= pob->size){
        struct _node *killme = pob->head;
        struct _node *prior = pob->head;
        unsigned int index = 1;
        while(index != pob->size){
            prior = killme;
            killme = killme-> next;
            index++;
        }
        if(killme->e == Town){
            struct _node *next = killme->next;
            destroy_node(killme);
            struct _node* new_node = create_node(City);
            new_node->next = next;
            prior->next = new_node;
            pob->score++;
        }
    }
    assert(invrep(pob));
    return pob;
}

bool playerOnB_is_valid(PlayerOnB pob)
{
    assert(invrep(pob));
    bool valid = pob != NULL;
    struct _node* head = pob->head;
    while(valid && head != NULL){
        if(head->e == Town || head->e == City){
            if(head->next != NULL){
                valid = head->next->e == Road;
                valid = (head->next->next == NULL)? valid : head->next->next->e == Road;
            }
        }
        head = head->next;
    }
    assert(invrep(pob));
    return valid;
}

unsigned int playerOnB_get_score(PlayerOnB pob)
{
    return playerOnB_is_valid(pob) ? pob->score : 0u;
}

unsigned int playerOnB_size(PlayerOnB pob)
{
    return pob->size;
}

void playerOnB_print(PlayerOnB pob)
{
    assert(invrep(pob));
    printf("[ ");
    struct _node* head = pob->head;
    for(unsigned int i = 0u; i < pob->size; i++){
        if(head->e == Road){
            printf("R ");
        } else if(head->e == City){
            printf("C ");
        } else{
            printf("T ");
        }
        head = head->next;
    }
    printf("]\n");
    assert(invrep(pob));
}

type_t* playerOnB_array(PlayerOnB pob)
{
    assert(invrep(pob));
    type_t *array = malloc(pob->size * sizeof(type_t));
    struct _node* head = pob->head;
    for(unsigned int i = 0u; i < pob->size; i++){
        array[i] = head->e;
        head = head->next;
    }
    return array;
    assert(invrep(pob));
}

PlayerOnB playerOnB_destroy(PlayerOnB pob)
{
    if(pob != NULL){
        struct _node* head = pob->head;
        while(head != NULL){
            struct _node* next = head->next;
            destroy_node(head);
            head = next;
        }
        free(pob);
        pob = NULL;
    }
    return pob;
}