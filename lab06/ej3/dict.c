#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool is_the_last(dict_t d) {
    return d->left == NULL && d->right == NULL;
}

//Obtains the father of the given node 
static dict_t dict_find(dict_t dict, key_t word) {
    dict_t previous_node = dict;
    dict_t current_node = dict;
    while(current_node != NULL && !key_eq(word, current_node->key)) {
        previous_node = current_node;
        if(key_less(word, current_node->key)) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    return previous_node;   
}

static dict_t dict_create_node(key_t word, value_t def) {
    dict_t new_node = (dict_t)malloc(sizeof(struct _node_t));
    new_node->key = word;
    new_node->value = def;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


static bool invrep(dict_t d) {
    bool result = true;
    if(d != NULL && !is_the_last(d)) {
        if(d->left != NULL && d->right == NULL) {
            result = key_less(d->left->key, d->key) && invrep(d->left);
        } else if(d->left == NULL && d->right != NULL) {
            result = key_less(d->key, d->right->key) && invrep(d->right);
        } else {
            result = key_less(d->left->key, d->key) && key_less(d->key, d->right->key) && invrep(d->left) && invrep(d->right);
        }
    }
    return result;
}

dict_t dict_empty(void) {
    dict_t d = NULL;
    assert(invrep(d) && dict_length(d)==0);
    return d;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if(dict == NULL) {
        dict_t new_node = dict_create_node(word, def);
        dict = new_node;
    } else {
        dict_t previous_node = dict_find(dict, word);
        if(key_less(word, previous_node->key)) {
            dict_t new_node = dict_create_node(word, def);
            previous_node->left = new_node;
        } else if(key_eq(word, previous_node->key)) {
            value_destroy(previous_node->value);
            previous_node->value = def;
        } else {
            dict_t new_node = dict_create_node(word, def);
            previous_node->right = new_node;
        }
    }
    assert(invrep(dict) && dict_exists(dict, word));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool exists = false;
    dict_t current_node = dict;
    while(!exists && current_node != NULL) {
        if(key_eq(word, current_node->key)) {
            exists = true;
        } else if(key_less(word, current_node->key)) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    return exists? current_node->value : NULL;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool exists = false;
    dict_t current_node = dict;
    while(!exists && current_node != NULL) {
        if(key_eq(word, current_node->key)) {
            exists = true;
        } else if(key_less(word, current_node->key)) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    return exists;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int length = dict == NULL ? 0u : 1u + dict_length(dict->left) + dict_length(dict->right);
    assert(invrep(dict) && (dict == NULL || length > 0u));
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    dict_t p = NULL;
    if(dict != NULL){
        if(key_eq(dict->key, word)){
            if(dict->right == NULL){
                p = dict;
                dict = dict->left;
                p->value = value_destroy(p->value);
                p->key = key_destroy(p->key);
                free(p);
                p = NULL;
            }
            else{
                p = dict->right;
                while(p->left != NULL){
                    p = p->left;
                }
                dict->value = value_destroy(dict->value);
                dict->key = key_destroy(dict->key);
                dict->key = string_clone(p->key);
                dict->value = string_clone(p->value);
                dict->right = dict_remove(dict->right, dict->key);
            }
        }
        else if(key_less(dict->key, word)){
            dict->right = dict_remove(dict->right, word);
        }
        else{
            dict->left = dict_remove(dict->left, word);
        }
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL){
        dict->left = dict_remove_all(dict->left);
        dict->right = dict_remove_all(dict->right);
        dict = dict_remove(dict, dict->key);
    }
    assert(invrep(dict) && dict_length(dict) == 0u);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);
    if (dict_length(dict) != 0u) {
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL){
        dict->left = dict_destroy(dict->left);
        dict->right = dict_destroy(dict->right);
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
    }
    dict = NULL;
    assert(dict == NULL);
    return dict;
}
