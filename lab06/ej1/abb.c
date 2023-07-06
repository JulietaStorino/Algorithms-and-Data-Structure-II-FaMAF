#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool is_a_leaf(abb tree) {
    return tree->left == NULL && tree->right == NULL;
}

//Obtains the father of the given node 
static abb abb_find(abb tree, abb_elem e) {
    abb previous_node = tree;
    abb current_node = tree;
    while(current_node != NULL & !elem_eq(e, current_node->elem)) {
        previous_node = current_node;
        if(elem_less(e, current_node->elem)) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    return previous_node;   
}

static abb abb_create_node(abb_elem e) {
    abb new_node = (abb)malloc(sizeof(struct _s_abb));
    new_node->elem = e;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

static bool invrep(abb tree) {
    bool result = true;
    if(tree != NULL && !is_a_leaf(tree)) {
        if(tree->left != NULL && tree->right == NULL) {
            result = elem_less(tree->left->elem, tree->elem) && invrep(tree->left);
        } else if(tree->left == NULL && tree->right != NULL) {
            result = elem_less(tree->elem, tree->right->elem) && invrep(tree->right);
        } else {
            result = elem_less(tree->left->elem, tree->elem) && elem_less(tree->elem, tree->right->elem) && invrep(tree->left) && invrep(tree->right);
        }
    }
    return result;
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(tree == NULL) {
        abb new_node = abb_create_node(e);
        tree = new_node;
    } else {
        abb previous_node = abb_find(tree, e);
        if(elem_less(e, previous_node->elem)) {
            abb new_node = abb_create_node(e);
            previous_node->left = new_node;
        } else if(e > previous_node->elem) {
            abb new_node = abb_create_node(e);
            previous_node->right = new_node;
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    assert(invrep(tree));
    bool exists = false;
    abb current_node = tree;
    while(!exists && current_node != NULL) {
        if(elem_eq(e, current_node->elem)) {
            exists = true;
        } else if(elem_less(e, current_node->elem)) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    assert(invrep(tree));
    unsigned int length = tree == NULL ? 0u : 1u + abb_length(tree->left) + abb_length(tree->right);
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0u));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree != NULL) {
        if (elem_eq(e, tree->elem)) {
            if (tree->left == NULL && tree->right == NULL) {
                free(tree);
                tree = NULL;
            } else if (tree->left == NULL) {
                abb killme = tree;
                tree = tree->right;
                free(killme);
                killme = NULL;
            } else if (tree->right == NULL) {
                abb killme = tree;
                tree = tree->left;
                free(killme);
                killme = NULL;
            } else {
                abb tree_search = tree->left;
                while (tree->left != NULL  || tree->right != NULL) {
                    tree_search = tree_search->right;
                }
                tree->elem = tree_search->elem;
                tree->left = abb_remove(tree->left, tree->elem);             
            }
        } else if(elem_less(e, tree->elem)) {
            tree->left = abb_remove(tree->left, e);
        } else {
            tree->right = abb_remove(tree->right, e);
        }        
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e = tree->elem;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb current_node = tree;
    while(current_node->right != NULL) {
        current_node = current_node->right;
    }
    max_e = current_node->elem;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb current_node = tree;
    while(current_node->left != NULL) {
        current_node = current_node->left;
    }
    min_e = current_node->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    if(tree != NULL) {
        tree->left = abb_destroy(tree->left);
        tree->right = abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }
    return NULL;
}