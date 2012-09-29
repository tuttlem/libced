
#ifndef __libced_dlist_h_

#define __libced_dlist_h_

#include <stdlib.h>

/**
 * @struct dlist_node_t
 * @brief Describes a single node in the list
 */
typedef struct dlist_node_t {
   void                *data;      /* data for this node */
   struct dlist_node_t *next;      /* next node in the list */
   struct dlist_node_t *prev;      /* previoud node in the list */
} dlist_node;

/**
 * @struct dlist_t
 * @brief Describes a full list
 */
typedef struct dlist_t {
   struct dlist_node_t *head;   /* first node in the list */
   struct dlist_node_t *tail;   /* last node in the list */
} dlist;

#define dlist_foreach(iter, list) \
   for (iter = list->head; iter != NULL; iter = iter->next)

#define dlist_foreach_r(iter, list) \
   for (iter = list->tail; iter != NULL; iter = iter->prev)

/**
 * Adds an item into a list
 * @param l The list to add the item to
 * @param data The data to add
 * @returns 0 on success, otherwise -1
 */
int dlist_append(dlist **l, void *data);

/**
 * Empties all items out of the list
 * @param l The list to clear
 * @returns 0 on success, otherwise -1
 */
int dlist_clear(dlist **l);

#endif /* __libced_dlist_h_ */
