/**
 * @file   syscalls.c
 * @author Ericson Joseph
 * @date   Apr 7, 2019
 */
#include "stdlib.h"
#include "task.h"
#include "list.h"
#include "syscalls.h"

uint8_t syscall_sleep(void *task) {
    task_struct *currentTask = (task_struct *)task;
    currentTask->ticks -= 1;
    if (currentTask->ticks == 0) {
        return SYSCALL_END;
    }
    return SYSCALL_IN_PROCESSING;
}

uint8_t syscall_semphr(void *task) {
    task_struct *currentTask = (task_struct *)task;
    semaphore_t *sem         = currentTask->semphr;
    if (sem != NULL && sem->isTake == false) {
        return SYSCALL_END;
    }
    return SYSCALL_IN_PROCESSING;
}

uint8_t syscall_queueReceiveBlocking(void *task) {
    task_struct *currentTask = (task_struct *)task;
    queueHandler queue       = currentTask->queue;
    if (!LIST_isEmpty(queue.list)) {
        return SYSCALL_END;
    }
    return SYSCALL_IN_PROCESSING;
}

uint8_t syscall_queueSendBloking(void *task) {
    task_struct *currentTask = (task_struct *)task;
    queueHandler queue       = currentTask->queue;
    if (queue.list->length < queue.size) {
        return SYSCALL_END;
    }
    return SYSCALL_IN_PROCESSING;
}
