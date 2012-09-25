
#ifndef __libced_slist_h_

#define __libced_slist_h_

#include <stdlib.h>

/**
 * @struct slist_node_t
 * @brief Describes a single node in the list
 */
typedef struct slist_node_t {
   void                *data;      /* data for this node */
   struct slist_node_t *next;      /* next node in the list */
} slist_node;

/**
 * @struct slist_t
 * @brief Describes a full list
 */
typedef struct slist_t {
   struct slist_node_t *head;   /* first node in the list */
   struct slist_node_t *tail;   /* last node in the list */
} slist;

#define slist_foreach(iter, list) \
   for (iter = list->head; iter != NULL; iter = iter->next)

/**
 * Adds an item into a list
 * @param l The list to add the item to
 * @param data The data to add
 * @returns 0 on success, otherwise -1
 */
int slist_append(slist **l, void *data);

/**
 * Empties all items out of the list
 * @param l The list to clear
 * @returns 0 on success, otherwise -1
 */
int slist_clear(slist **l);

#endif /* __libced_slist_h_ */
