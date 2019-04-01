/**
 * @file   myOS.h
 * @author Ericson Joseph
 * @date   March 2019
 * @brief  Header of myOS Operating System
 */

#ifndef MYOS_H_
#define MYOS_H_

#include <stdint.h>
#include "task.h"

#define MAX_TASK_LIST 10
#define STACK_SIZE 512
#define PRIORITY_PENDSV ((1 << __NVIC_PRIO_BITS) - 1)

void MyOSInit(void);

void initStack(uint32_t stack[],
               uint32_t stackSizeBytes,
               uint32_t *sp,
               task_type entry_point,
               void *args);

void taskReturnHook(void *arg);

void addTickCount(void);

uint32_t getTickCount(void);

void scheduler(void);

#endif /* MYOS_H_ */
