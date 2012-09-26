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
 * @returns A tree pointer
 */
bintree* bintree_create(bintree_cmp c);

/**
 * Destroys a binary tree
 * @param t The tree to destroy
 * @returns 0 on success, otherwise -1
 */
int bintree_destroy(bintree **t);

/**
 * Inserts an item into the tree
 * @param t The tree to insert into
 * @param key The key to store the value with
 * @param data The data to store
 * @returns 0 on success, otherwise -1
 */
int bintree_insert(bintree *t, void *key, void *data);

/**
 * Attempts to find an item in the tree
 * @param t The tree to search
 * @param key The key to look for
 * @returns The data value if the key is found, otherwise NULL
 */
void* bintree_find(bintree *t, void *key);

#endif /* __libced_bintree_h_ */
