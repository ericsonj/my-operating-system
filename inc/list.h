/**
 * @file   list.h
 * @author Ericson Joseph
 * @date   Apr 1, 2019
 *
 * @brief Generic list data structure
 */
#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Node struct
 */
struct list_node_s {
    void *object;
    struct list_node_s *nextNode;
};

/**
 * List struct
 */
struct list_s {
    uint32_t length;
    struct list_node_s *firstNode;
};

typedef struct list_s list_s;

/**
 * Initialize generic list.
 * @param list
 */
void LIST_init(struct list_s *list);

/**
 * Check if list is empty.
 * @param list
 * @return bool TRUE if list is empty
 */
bool LIST_isEmpty(struct list_s *list);

/**
 * Add node to list in first position.
 * @param list
 * @param node
 */
void LIST_addFirst(struct list_s *list, struct list_node_s *node);

/**
 * Add node to list in last position.
 * @param list
 * @param node
 */
void LIST_addLast(struct list_s *list, struct list_node_s *node);

/**
 * Add node to list in index position.
 * @param list
 * @param index
 * @param node
 */
void LIST_insert(struct list_s *list, uint32_t index, struct list_node_s *node);

/**
 * Remove and return list_node_s from the list in first position.
 * @param list
 * @return list_node_s
 */
struct list_node_s *LIST_removeFirst(struct list_s *list);

/**
 * Remove and return list_node_s from the list in last position.
 * @param list
 * @return list_node_s
 */
struct list_node_s *LIST_removeLast(struct list_s *list);

/**
 * Return list_node_s from list in index position.
 * @param list
 * @param index
 * @return list_node_s
 */
struct list_node_s *LIST_get(struct list_s *list, uint32_t index);

/**
 * Retrieves and removes the head (first element) of this list.
 * @param list
 * @return
 */
struct list_node_s *LIST_poll(struct list_s *list);

/**
 * Retrieves, but does not remove, the head (first element) of this list.
 * @param list
 * @return
 */
struct list_node_s *LIST_peek(struct list_s *list);

/**
 * Adds the specified element as the tail (last element) of this list.
 * @param list
 * @param node
 * @return bool
 */
bool LIST_offer(struct list_s *list, struct list_node_s *node);

/**
 * Return size of list.
 * @param list
 * @return uint32_t
 */
uint32_t LIST_size(struct list_s *list);

/**
 * Initialize struct list_node_s
 * @param node
 * @param id
 */
void LIST_newNode(struct list_node_s *node, void *id);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */
