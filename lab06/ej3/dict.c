#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    bool result = true;
    if(d != NULL && (d->left != NULL || d->right != NULL)) {
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

static bool dict_is_empty(dict_t dict){
    return (dict == NULL);
}

//If is the root return NULL, otherwise return the father
static dict_t dict_find_father(dict_t dict, key_t word) {
    assert(dict_exists(dict, word));
    dict_t father = NULL;
    if(dict->key != word){
        dict_t previous_node = dict;
        dict_t current_node = dict;
        while(current_node != NULL) {
            previous_node = current_node;
            if(key_eq(word, current_node->key)) {
                break;
            } else if(key_less(word, current_node->key)) {
                current_node = current_node->left;
            } else {
                current_node = current_node->right;
            }
        }
        father = previous_node;
    }
    return father; 
}

//Find where to add a node.
static dict_t dict_find_place(dict_t dict, key_t word) {
    dict_t previous_node = dict;
    dict_t current_node = dict;
    while(current_node != NULL) {
        previous_node = current_node;
        if(key_less(word, current_node->key)) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    return previous_node; 
}

static dict_t dict_create_node( key_t word, value_t def) {
    dict_t new_node = (dict_t)malloc(sizeof(struct _node_t));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->key = word;
    new_node->value = def;
    return new_node;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int length = dict == NULL ? 0u : 1u + dict_length(dict->left) + dict_length(dict->right);
    assert(invrep(dict) && (dict_is_empty(dict) || length > 0u));
    return length;
}

static dict_t dict_remove_node(dict_t dict, dict_t node){
    assert(dict_exists(dict, node->key));
    key_t key = node->key;
    dict_t left_node = node->left;
    dict_t right_node = node->right;
    dict_t father = dict_find_father(dict, node->key);
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    if(father != NULL){
        if(key_less(key, father->key)) {
            father->left = NULL;
        } else {
            father->right = NULL;
        }
    }
    if(father == NULL){
        dict = (left_node!=NULL) ? left_node : right_node;
    }
    if(left_node != NULL){
        if(right_node != NULL){
            dict_t father = dict_find_place(left_node, right_node->key);
            if(father->left==NULL && key_less(right_node->key, father->key)){
                father->left = right_node;
            } else {
                father->right = right_node;
            }
        }   
    }
    return dict;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    dict_t previous_node = dict_find_place(dict, word);
    if(dict_exists(dict, word)) {
        if(previous_node == dict) {
            previous_node->value = def;
        } else if(previous_node->left != NULL && key_eq(previous_node->left->key, word)) {
            previous_node->left->value = def;
        } else {
            previous_node->right->value = def;
        }
    } else {
        dict_t new_node = dict_create_node(word, def);
        if(dict == NULL) {
            dict = new_node;
        } else {
            if(key_less(word, previous_node->key)) {
                previous_node->left = new_node;
            } else {
                previous_node->right = new_node;
            }
        }
    }
    assert(invrep(dict) && key_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    dict_t current_node = dict;
    while(current_node != NULL) {
        if(key_eq(word, current_node->key)) {
            break;
        } else if(key_less(word, current_node->key)) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    assert((current_node != NULL) == dict_exists(dict, word));
    return current_node==NULL ? NULL : current_node->value;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool exists = false;
    if(dict != NULL){
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
    }
    assert(invrep(dict));
    return exists;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    dict_t current_node = dict;
    while(!key_eq(dict->key, word)) {
        if(key_less(word, dict->key)) {
            current_node = dict->left;
        } else {
            current_node = dict->right;
        }
    }
    dict = dict_remove_node(dict, current_node);
    return dict;
}

dict_t dict_remove_all(dict_t dict) {   
    assert(invrep(dict));
    if(dict != NULL) {
        dict_remove(dict, dict->key);
        dict = dict_remove_all(dict->left);
        dict = dict_remove_all(dict->right);
    }
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);
    if (dict != NULL) {
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, ".");
        fprintf(file, "\n");
        dict_dump(dict->left, file);
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    assert(dict_is_empty(dict));
    return NULL;
}