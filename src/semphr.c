/**
 * @file   semphr.c
 * @author Ericson Joseph
 * @date   Mar 31, 2019
 */
#include <stdlib.h>
#include "semphr.h"
#include "myOS.h"

extern task_struct taskList[MAX_TASK_LIST];
extern uint32_t current_task;
extern uint32_t taskListIdx;
extern struct list_s taskQueue;

void semaphoreCreate(semaphore_t *rest) {
    rest->isTake = true;
    rest->ticks  = -1;
}

void semaphoreGive(semaphore_t *semphr) { semphr->isTake = false; }

void semaphoreTakeBlocking(semaphore_t *semphr) {
    if (semphr != NULL && semphr->isTake) {
        taskList[current_task].semphr     = semphr;
        taskList[current_task].state      = TASK_WAITING;
        taskList[current_task].wait_state = WAIT_SEMPHR;
        scheduler();
    }
    semphr->isTake = true;
}
