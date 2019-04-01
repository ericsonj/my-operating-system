/* 
 * File:   list.h
 * Author: Ericson Joseph <ericsonjoseph@gmail.com>
 *
 * Created on March 29, 2019, 8:46 PM
 */

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

    struct list_node_s {
        void* object;
        struct list_node_s *nextNode;
    };

    struct list_s {
        uint32_t length;
        struct list_node_s *firstNode;
    };

    typedef struct list_s list_s;

    void LIST_init(struct list_s* list);
    
    bool LIST_isEmpty(struct list_s* list);

    void LIST_addFirst(struct list_s *list, struct list_node_s *node);

    void LIST_addLast(struct list_s *list, struct list_node_s *node);

    void LIST_insert(struct list_s *list, uint32_t index, struct list_node_s *node);

    struct list_node_s* LIST_removeFirst(struct list_s *list);

    struct list_node_s* LIST_removeLast(struct list_s *list);
    
    struct list_node_s* LIST_get(struct list_s *list, uint32_t index);
    
    struct list_node_s* LIST_poll(struct list_s *list);

    struct list_node_s* LIST_peek(struct list_s *list);

    bool LIST_offer(struct list_s *list, struct list_node_s *node);

    uint32_t LIST_size(struct list_s *list);
    
    void LIST_newNode(struct list_node_s *node, void* id);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */

