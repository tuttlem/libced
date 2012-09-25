
#include "../include/dlist.h"

/**
 */
int dlist_append(dlist **l, void *data) {

   dlist_node *node = NULL;

   /* build the list if it doesn't yet exist */
   if (!*l) {
      (*l) = (dlist*)malloc(sizeof(dlist));
      (*l)->head = (*l)->tail = NULL;
   }

   /* build the node to add */
   node = (dlist_node*)malloc(sizeof(dlist_node));
   node->data = data;
   node->next = NULL;
   node->prev = NULL;

   /* test that the tail is ok */
   if (!(*l)->tail) {
      (*l)->head = node;
      (*l)->tail = node;
   } else {
      node->prev = (*l)->tail;
      (*l)->tail->next = node;
      (*l)->tail = (*l)->tail->next;
   }

   return 0;
}

/**
 */
int dlist_clear(dlist **l) {

   dlist_node *node = NULL, *temp = NULL;

   /* sanity check the list */
   if (!*l) {
      return 0;
   }

   node = (*l)->head;

   /* keep destroying nodes until there are none left */
   while (node) {
      temp = node->next;
      free(node);
      node = temp;
   }

   free(*l);
   *l = NULL;

   return 0;
}

