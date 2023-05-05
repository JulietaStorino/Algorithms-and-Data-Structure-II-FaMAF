#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* intarface           */

struct _s_dict {
    unsigned int length;
    struct _node_t * first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};



struct _node_t *create_node(key_t k, value_t v) {
    struct _node_t *new_node = malloc(sizeof(struct _node_t));
    new_node->key=k;
    new_node->value=v;
    new_node->next=NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    node->next = NULL;
    free(node);
    node = NULL;
    return node;
}

static bool invrep(dict_t dict) {
    unsigned int aux = dict->length;
    return (aux == dict->length);
}

// --- Interface functions ---

//FUNCIÓN LIBRES
key_t *dict_get_keys(dict_t dict){
    assert(invrep(dict));
    key_t* array = malloc((dict->length) * sizeof(key_t));
    struct _node_t * currentnode = dict->first;
    
    for(unsigned int i = 0; i<(dict->length); i++){
        array[i] = currentnode->key;
        currentnode = currentnode->next;
    }
    return array;
}

dict_t dict_empty(void) {
    dict_t dict = malloc(sizeof(struct _s_dict));
    dict->length = 0;
    dict->first = NULL;
    assert(dict->length == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    struct _node_t * currentnode = dict->first;   
    if(currentnode == NULL){
        dict->first = create_node(word, def);
        dict->length = ((dict->length) + 1);
    } else{
        if(dict_exists(dict,word)){
            while((currentnode->key) != word){
                currentnode = currentnode->next;
            }
            currentnode->value = def;
        }else{
            ++dict->length;
            while((currentnode->next) != NULL){
                currentnode = currentnode->next;
            }
            currentnode->next = create_node(word, def);
        }
    }
    assert(dict_exists(dict,word));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    value_t ret = NULL;
    if(dict_exists(dict,word)){
        struct _node_t * currentnode = dict->first;
        while(currentnode != NULL){
            if(currentnode->key == word){
                break;
            }else{
                currentnode = currentnode->next;
            }
        }
        ret = currentnode->value;
    }
    assert((ret != NULL) == dict_exists(dict,word));
    return ret;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict)); 
    bool ret = false;
    struct _node_t * currentnode = dict->first;
    
    while(currentnode != NULL){
        if(currentnode->key == word){
            ret = true;
            break;
        }else{
            currentnode = currentnode->next;
        }
    }
    assert(invrep(dict)); 
    return ret;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    return (dict->length);
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));

    if(dict_exists(dict, word)){
        struct _node_t * currentnode = dict->first;
        struct _node_t * priornode;
        while(((currentnode->next) != NULL) && (currentnode->key != word)){
            priornode = currentnode;
            currentnode = currentnode->next;
        }
        if(currentnode->key == word){
            if(currentnode->next == NULL){
                priornode->next = NULL;
                destroy_node(currentnode);
            } else{
                priornode->next = currentnode->next;
                destroy_node(currentnode);
            }
        }
        assert(invrep(dict) && !dict_exists(dict,word));
    }
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    struct _node_t * currentnode = dict->first;
    
    dict->length = 0;

    while((currentnode->next) != NULL){
        dict->first = currentnode->next;
        destroy_node(currentnode);
    }
    dict->first = NULL;
    destroy_node(currentnode);
    assert(invrep(dict) && (dict->length == 0));
    return dict;
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}

