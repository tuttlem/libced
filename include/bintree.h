#ifndef __libced_bintree_h_

#define __libced_bintree_h_

#include <stdlib.h>

/*
 * Binary tree implementation
 * http://en.wikipedia.org/wiki/Binary_tree
 */

/**
 * b-tree comparator function signature
 */
typedef int(*bintree_cmp)(const void *, const void *);

/**
 * @struct bintree_node_t
 * #brief Defines the structure of a b-tree node
 */
typedef struct bintree_node_t {
   struct bintree_node_t *left;  /* left leaf node */
   struct bintree_node_t *right; /* right leaf node */

   void *key;                  /* key identifying this node */
   void *data;                 /* data at this node */
} bintree_node;

/**
 * @struct bintree_t
 * @brief Defines a b-tree structure
 */
typedef struct bintree_t {
   bintree_cmp             comp; /* the comparator used on key items */
   struct bintree_node_t  *root; /* root node of the tree */
} bintree;

/**
 * Creates a binary tree
 * @param c The node comparator
 */
bintree* bintree_create(bintree_cmp c);

/**
 * Destroyes a binary tree
 * @param t The tree to destroy
 */
int bintree_destroy(bintree **t);

#endif /* __libced_bintree_h_ */
