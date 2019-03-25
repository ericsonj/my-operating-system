/*
 * myOs.h
 *
 *  	Created on: Mar 23, 2019
 *      Author: ericson
 */

#ifndef MYOS_H_
#define MYOS_H_

#include <stdint.h>

#define MAX_TASK_LIST 10
#define STACK_SIZE 512

typedef enum {
    TASK_RUNNING = 1,
    TASK_READY,
    TASK_WAITING,
    TASK_SUSPENDED
} task_state;

typedef struct {
    uint32_t id;      // Task ID
    task_state state; // Task state
    uint32_t sp;      // Task stack pointer
    uint32_t ticks;   // TASK_INTERRUPTABLE ticks
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

#endif /* MYOS_H_ */
