/**
 * @file   queue.c
 * @author Ericson Joseph
 * @date   Apr 7, 2019
 */

#include <string.h>
#include "syscalls.h"
#include "queue.h"
#include "static_memory.h"
#include "myOS.h"

extern task_struct taskList[MAX_TASK_LIST];
extern uint32_t current_task;
extern uint32_t taskListIdx;
extern struct list_s taskQueue;

queueHandler queueCreate(uint8_t size, uint16_t itemSize) {
    queueHandler resp;
    resp.size           = size;
    resp.itemSize       = itemSize;
    struct list_s *list = (struct list_s *)MEM_malloc(sizeof(struct list_s));
    LIST_init(list);
    resp.list = list;
    return resp;
}

uint8_t queueSend(queueHandler queue, void *item) {

    if (queue.list->length == queue.size) {
        taskList[current_task].state      = TASK_WAITING;
        taskList[current_task].wait_state = WAIT_SYSCALL;
        taskList[current_task].queue      = queue;
        taskList[current_task].syscall    = syscall_queueSendBloking;
        scheduler();
    }
    void *memItem = MEM_malloc(queue.itemSize);
    memcpy(memItem, item, queue.itemSize);
    struct list_node_s *node =
        (struct list_node_s *)MEM_malloc(sizeof(struct list_node_s));
    node->object = memItem;
    LIST_addLast(queue.list, node);
    return 1;
}

uint8_t queueReceiveBlocking(queueHandler queue, void *item) {

    taskList[current_task].state      = TASK_WAITING;
    taskList[current_task].wait_state = WAIT_SYSCALL;
    taskList[current_task].queue      = queue;
    taskList[current_task].syscall    = syscall_queueReceiveBlocking;
    scheduler();

    struct list_node_s *node = LIST_poll(queue.list);
    memcpy(item, node->object, queue.itemSize);
    MEM_free(node->object);
    MEM_free(node);
    return 1;
}
