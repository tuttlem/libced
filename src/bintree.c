
#include "../include/bintree.h"

/**
 */
bintree* bintree_create(bintree_cmp c) {
   /* allocate the tree */
   bintree *t = (bintree*)malloc(sizeof(bintree));

   /* sanity check the memory allocation */
   if (!t) {
      return NULL;
   }

   t->comp = c;
   t->root = NULL;

   return t;
}

/**
 */
void bintree_destroy_branch(bintree_node *n) {
   /* check and destroy any candidate to the left */
   if (c->left) {
      bintree_destroy_branch(c->left);
   }

   /* check and destroy any candidate to the right */
   if (c->right) {
      bintree_destroy_branch(c->right);
   }

   /* release the memory for this node */
   free(c);
}

/**
 */
int bintree_destroy(bintree **t) {
   /* sanity test the tree */
   if (!(*t)) {
      return -1;
   }

   /* destroy the tree at the root */
   bintree_destroy_branch((*t)->root);

   /* destroy the container */
   free(*t);
   *t = NULL;
}

/**
 */
int bintree_insert(bintree *t, void *key, void *data) {
}

/**
 */
void* bintree_find(bintree *t, void *key) {
}

