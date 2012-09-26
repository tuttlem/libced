
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
   if (n->left) {
      bintree_destroy_branch(n->left);
   }

   /* check and destroy any candidate to the right */
   if (n->right) {
      bintree_destroy_branch(n->right);
   }

   /* release the memory for this node */
   free(n);
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

   return 0;
}

/**
 * Traverses the tree and finds the most appropriate place to put
 * a new node
 * @returns The added leaf. Failure results in NULL
 */
bintree_node* bintree_create_leaf(bintree *t,
                                  bintree_node *n,
                                  void *key,
                                  void *data) {
   int cval = t->comp(key, n->key);
   bintree_node *l = NULL;

   /* if the comparator told us the keys are the same, bail out
    * as we can't add the same key to this tree more than once */
   if (cval == 0)
      return NULL;

   /* recurse into the structure if required */
   if ((cval == -1) && (n->left)) {
      bintree_create_leaf(t, n->left, key, data);
   } else if ((cval == 1) && (n->right)) {
      bintree_create_leaf(t, n->right, key, data);
   }

   /* create the new leaf */
   l = (bintree_node*)malloc(sizeof(bintree_node));
   l->left = n->right = NULL;
   l->key = key;
   l->data = data;

   /* place the node in the structure */
   if (cval == -1) {
      n->left = l;
   } else if (cval == 1) {
      n->right = l;
   }

   return n;
}

/**
 */
int bintree_insert(bintree *t, void *key, void *data) {

   /* sanity check the tree */
   if (!t) {
      return -1;
   }

   /* sanity check the root */
   if (t->root) {
      /* insert the item */
      return (bintree_create_leaf(t, t->root, key, data) != NULL ? 0 : -1);
   }

   /* the root needs to be constructed */
   t->root = (bintree_node*)malloc(sizeof(bintree_node));
   t->root->left = t->root->right = NULL;
   t->root->key = key;
   t->root->data = data;

   return 0;
}

/**
 * Recurses into the tree searching for a key match
 * @returns The node if one is found, otherwise NULL
 */
bintree_node* bintree_find_leaf(bintree *t,
                                bintree_node *n,
                                void *key) {
   int cval = t->comp(key, n->key);
   bintree_node *leaf = NULL;

   /* if the comparator told us the keys are the same, we have
    * found the value we're looking for! */
   if (cval == 0)
      return n;

   /* recurse into the structure if required */
   if ((cval == -1) && (n->left)) {
      leaf = bintree_find_leaf(t, n->left, key);
   } else if ((cval == 1) && (n->right)) {
      leaf = bintree_find_leaf(t, n->right, key);
   }

   /* send the leaf out */
   return leaf;
}

/**
 */
void* bintree_find(bintree *t, void *key) {

   bintree_node *leaf = NULL;

   /* sanity check the tree */
   if (!t) {
      return NULL;
   }

   /* try to find the right item */
   leaf = bintree_find_leaf(t, t->root, key);

   return leaf != NULL ? leaf->data : NULL;
}

