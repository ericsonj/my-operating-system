/**
 * @file   task.h
 * @author Ericson Joseph
 * @date   Mar 30, 2019
 */

#ifndef TASK_H_
#define TASK_H_

#include <stdint.h>

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
} task_struct;

#endif /* TASK_H_ */
