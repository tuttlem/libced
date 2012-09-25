
#include "../include/slist.h"

/**
 */
int slist_append(slist **l, void *data) {

   slist_node *node = NULL;

   /* build the list if it doesn't yet exist */
   if (!*l) {
      (*l) = (slist*)malloc(sizeof(slist));
      (*l)->head = (*l)->tail = NULL;
   }

   /* build the node to add */
   node = (slist_node*)malloc(sizeof(slist_node));
   node->data = data;
   node->next = NULL;

   /* test that the tail is ok */
   if (!(*l)->tail) {
      (*l)->head = node;
      (*l)->tail = node;
   } else {
      (*l)->tail->next = node;
      (*l)->tail = (*l)->tail->next;
   }

   return 0;
}

/**
 */
int slist_clear(slist **l) {

   slist_node *node = NULL, *temp = NULL;

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

