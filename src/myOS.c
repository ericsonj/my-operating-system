/*
 * myOS.c
 *
 *  	Created on: Mar 23, 2019
 *      Author: ericson
 */

#include "board.h"
#include "myOS.h"
#include <string.h>

static uint32_t tickCount = 0;

static void initStack(uint32_t stack[],
                      uint32_t stackSizeBytes,
                      uint32_t *sp,
                      task_type entry_point,
                      void *args);

void *idle(void *args);

task_struct taskList[MAX_TASK_LIST];
uint32_t current_task;
uint32_t taskListIdx;

uint32_t stackIdle[STACK_SIZE / 4];

void MyOSInit(void) {

    for (uint32_t i = 0; i < MAX_TASK_LIST; ++i) {
        taskList[i].id    = 0;
        taskList[i].state = 0;
        taskList[i].sp    = 0;
    }
    taskListIdx  = 1;
    current_task = 0;
    taskCreate(stackIdle, STACK_SIZE, idle, (void *)0);
}

void taskCreate(uint32_t stack[],
                uint32_t stackSizeBytes,
                task_type entry_point,
                void *args) {

    taskList[taskListIdx].id    = taskListIdx;
    taskList[taskListIdx].state = TASK_RUNNING;
    initStack(stack, stackSizeBytes, &taskList[taskListIdx].sp, entry_point,
              args);
    taskListIdx++;
}

void initStack(uint32_t stack[],
               uint32_t stackSizeBytes,
               uint32_t *sp,
               task_type entry_point,
               void *args) {

    bzero(stack, stackSizeBytes);

    stack[stackSizeBytes / 4 - 1] = 1 << 24;                  // xPSR
    stack[stackSizeBytes / 4 - 2] = (uint32_t)entry_point;    // PC
    stack[stackSizeBytes / 4 - 3] = (uint32_t)taskReturnHook; // LR
    stack[stackSizeBytes / 4 - 8] = (uint32_t)args;           // R0
    stack[stackSizeBytes / 4 - 9] = 0xFFFFFFF9;               // LR IRQ

    // considerando los 8 registros pusheados
    void *stackDir = &(stack[stackSizeBytes / 4 - 17]);
    *sp            = (uint32_t)stackDir;
}

/*
 * Task Switch
 */
uint32_t get_next_context(uint32_t current_sp) {

    uint32_t next_sp;

    switch (current_task) {
    case 0:
        next_sp      = taskList[current_task + 1].sp;
        current_task = 1;
        break;
    case 1:
        taskList[current_task].sp = current_sp;
        next_sp                   = taskList[current_task + 1].sp;
        current_task              = 2;
        break;
    case 2:
        taskList[current_task].sp = current_sp;
        next_sp                   = taskList[current_task + 1].sp;
        current_task              = 3;
        break;
    case 3:
        taskList[current_task].sp = current_sp;
        next_sp                   = taskList[1].sp;
        current_task              = 1;
        break;
    default:
        while (1) {
            __WFI();
        }
        break;
    }

    return next_sp;
}

/**
 * Task Delay
 */
void taskDelay(uint32_t delay) {
    taskList[current_task].state = TASK_WAITING;
    taskList[current_task].ticks = delay;
    uint32_t tickStart           = tickCount;
    while ((tickCount - tickStart) < (delay - 1)) {
        __WFI();
    }
    taskList[current_task].state = TASK_RUNNING;
}

/**
 * Task Return Hook
 */
void taskReturnHook(void *arg) {
    while (1) {
        __WFI();
    }
}

void *idle(void *args) {
    while (1) {
        __WFI();
    }
}

/**
 * Add tick Count
 */
void addTickCount(void) { tickCount++; }
