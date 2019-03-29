/**
 * @file   myOS.h
 * @author Ericson Joseph
 * @date   March 2019
 * @brief  Header of myOS Operating System
 */

#ifndef MYOS_H_
#define MYOS_H_

#include <stdint.h>

#define MAX_TASK_LIST 10
#define STACK_SIZE 512
#define PRIORITY_PENDSV ((1 << __NVIC_PRIO_BITS) - 1)

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
    uint32_t ticks;
} task_struct;

typedef void *(*task_type)(void *);

void MyOSInit(void);

void taskDelay(uint32_t delay);

void taskCreate(uint32_t stack[],
                uint32_t stackSizeBytes,
                task_type entry_point,
                void *args);

void taskReturnHook(void *arg);

void addTickCount(void);

uint32_t getTickCount(void);

#endif /* MYOS_H_ */
