/**
 * @file   task.h
 * @author Ericson Joseph
 * @date   Mar 30, 2019
 */

#ifndef TASK_H_
#define TASK_H_

#include <stdint.h>
#include "semphr.h"

typedef void *(*task_type)(void *);

typedef enum { WAIT_TICKS = 1, WAIT_SEMPHR } task_wait_state;

typedef enum {
    TASK_RUNNING = 1,
    TASK_READY,
    TASK_WAITING,
    TASK_SUSPENDED
} task_state;

typedef struct {
    uint32_t id;
    task_state state;
    uint32_t sp;
    int8_t priority;
    uint32_t ticks;
    semaphore_t *semphr;
    task_wait_state wait_state;
} task_struct;

void taskCreate(uint32_t stackSizeBytes,
                task_type entry_point,
                int8_t priority,
                void *args);

void taskDelay(uint32_t delay);

#endif /* TASK_H_ */
