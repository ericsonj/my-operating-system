/**
 * @file   task_queue.c
 * @author Ericson Joseph
 * @date   March 2019
 * @brief  Task queue for priority scheduler
 */

#include <stdlib.h>
#include "list.h"
#include "task_queue.h"
#include "static_memory.h"

static uint32_t _maxSize;

void TASKQ_Init(struct list_s *queue, uint32_t maxSize) {
    _maxSize = maxSize;
    LIST_init(queue);
}

void TASKQ_addFirst(struct list_s *queue, task_struct *_task) {
    struct list_node_s *node =
        (struct list_node_s *)MEM_malloc(sizeof(struct list_node_s));
    if (node != NULL) {
        node->object = _task;
        LIST_addFirst(queue, node);
    }
}

void TASKQ_insert(struct list_s *queue, uint32_t index, task_struct *_task) {
    struct list_node_s *node =
        (struct list_node_s *)MEM_malloc(sizeof(struct list_node_s));
    if (node != NULL) {
        node->object = _task;
        LIST_insert(queue, index, node);
    }
}

void TASKQ_add(struct list_s *queue, task_struct *_task) {
    struct list_node_s *node =
        (struct list_node_s *)MEM_malloc(sizeof(struct list_node_s));
    if (node != NULL) {
        node->object = _task;
        LIST_addLast(queue, node);
    }
}

task_struct *TASKQ_poll(struct list_s *queue) {
    if (LIST_isEmpty(queue)) {
        return NULL;
    }
    struct list_node_s *node = LIST_poll(queue);
    task_struct *aux         = (task_struct *)node->object;
    MEM_free(node);
    return aux;
}

void TASKQ_addByPriority(struct list_s *queue, task_struct *_task) {
    if (LIST_isEmpty(queue)) {
        TASKQ_add(queue, _task);
        return;
    }

    uint32_t idx             = 0;
    struct list_node_s *node = queue->firstNode;
    do {
        task_struct *tsk = (task_struct *)node->object;
        if (_task->priority > tsk->priority) {
            break;
        } else {
            idx++;
            node = node->nextNode;
        }
    } while (node != NULL);

    if (idx > (queue->length - 1)) {
        TASKQ_add(queue, _task);
    } else {
        TASKQ_insert(queue, idx, _task);
    }
}
