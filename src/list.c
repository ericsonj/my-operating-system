#include "list.h"


void LIST_init(struct list_s* list){
    list->length = 0;
    list->firstNode = NULL;
}

bool LIST_isEmpty(struct list_s* list) {
    return (list->firstNode == NULL);
}

void LIST_addFirst(struct list_s *list, struct list_node_s *node) {
    if (node == NULL) {
        return;
    }
    list->length += 1;
    node->nextNode = list->firstNode;
    list->firstNode = node;
}

void LIST_addLast(struct list_s *list, struct list_node_s *node) {
    if (node == NULL) {
        return;
    }
    list->length += 1;
    if (LIST_isEmpty(list)) {
        list->firstNode = node;
        node->nextNode = NULL;
    } else {
        struct list_node_s *last = list->firstNode;
        while (last->nextNode != NULL) {
            last = last->nextNode;
        }
        last->nextNode = node;
        node->nextNode = NULL;
    }
}

void LIST_insert(struct list_s *list, uint32_t index, struct list_node_s *node) {
    if (LIST_isEmpty(list) && index > 0) {
        return;
    }
    if (LIST_isEmpty(list) && index == 0) {
        LIST_addFirst(list, node);
        return;
    }
    if (list->firstNode->nextNode == NULL && index == 1) {
        list->firstNode->nextNode = node;
        node->nextNode = NULL;
        return;
    }
    if (index == 0) {
        LIST_addFirst(list, node);
        return;
    }
    if (index > (list->length - 1)) {
        return;
    }
    uint32_t idx = 1;
    struct list_node_s *current = list->firstNode;
    struct list_node_s *next = list->firstNode->nextNode;
    while (idx < index && next != NULL) {
        current = next;
        next = next->nextNode;
        idx++;
    }
    list->length += 1;
    current->nextNode = node;
    node->nextNode = next;
}

struct list_node_s* LIST_removeLast(struct list_s *list) {
    if (LIST_isEmpty(list)) {
        return NULL;
    }
    if (list->firstNode->nextNode == NULL) {
        list->firstNode = NULL;
        return NULL;
    }
    struct list_node_s *current = list->firstNode;
    struct list_node_s *next = list->firstNode->nextNode;
    while (next->nextNode != NULL) {
        current = next;
        next = next->nextNode;
    }
    list->length -= 1;
    current->nextNode = NULL;
    next->nextNode = NULL;
    return next;
}

struct list_node_s* LIST_removeFirst(struct list_s *list) {
    if (LIST_isEmpty(list)) {
        return NULL;
    }
    struct list_node_s *first = list->firstNode;
    struct list_node_s *aux = list->firstNode->nextNode;
    list->length -= 1;
    list->firstNode = aux;
    first->nextNode = NULL;
    return first;
}

struct list_node_s* LIST_get(struct list_s *list, uint32_t index) {
    if (LIST_isEmpty(list)) {
        return NULL;
    }
    if (index > (list->length - 1)) {
        return NULL;
    }
    uint32_t idx = 0;
    struct list_node_s* node = list->firstNode;
    while (idx < index && node->nextNode != NULL) {
        node = node->nextNode;
        idx++;
    }
    return node;
}

struct list_node_s* LIST_poll(struct list_s *list) {
    struct list_node_s *node = list->firstNode;
    LIST_removeFirst(list);
    return node;
}

struct list_node_s* LIST_peek(struct list_s *list) {
    return list->firstNode;
}

bool LIST_offer(struct list_s *list, struct list_node_s *node) {
    LIST_addLast(list, node);
    return true;
}

uint32_t LIST_size(struct list_s *list) {
    return list->length;
}

void LIST_newNode(struct list_node_s *task, void* object) {
    task->object = object;
}