/**
 * @file   myOS.c
 * @author Ericson Joseph
 * @date   March 2019
 * @brief  Source of myOS
 */

#include "board.h"
#include "myOS.h"
#include <string.h>
#include "task_queue.h"
#include "static_memory.h"

static uint32_t tickCount = 0;

static void initStack(uint32_t stack[],
                      uint32_t stackSizeBytes,
                      uint32_t *sp,
                      task_type entry_point,
                      void *args);

static void scheduler(void);

void *idle(void *args);

task_struct taskList[MAX_TASK_LIST];
uint32_t current_task;
uint32_t taskListIdx;
struct list_s taskQueue;

uint32_t stackIdle[STACK_SIZE / 4];

void SysTick_Handler(void) {
    addTickCount();
    scheduler();
}

void scheduler(void) {
    __ISB();
    __DSB();
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void MyOSInit(void) {

    MEM_init();
    for (uint32_t i = 0; i < MAX_TASK_LIST; ++i) {
        taskList[i].id    = 0;
        taskList[i].state = 0;
        taskList[i].sp    = 0;
    }
    taskListIdx  = 1;
    current_task = 0;
    taskCreate(stackIdle, STACK_SIZE, idle, 0, (void *)0);
    TASKQ_Init(&taskQueue, 10);
}

void taskCreate(uint32_t stack[],
                uint32_t stackSizeBytes,
                task_type entry_point,
                int8_t priority,
                void *args) {

    taskList[taskListIdx].id       = taskListIdx;
    taskList[taskListIdx].state    = TASK_READY;
    taskList[taskListIdx].priority = priority;
    initStack(stack, stackSizeBytes, &taskList[taskListIdx].sp, entry_point,
              args);

    TASKQ_addByPriority(&taskQueue, &taskList[taskListIdx]);

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

    void *stackDir = &(stack[stackSizeBytes / 4 - 17]);
    *sp            = (uint32_t)stackDir;
}

uint32_t get_next_context(uint32_t current_sp) {

    uint32_t next_sp;

    /*
     * If task is 0
     */
    if (current_task == 0) {
        task_struct *task = TASKQ_poll(&taskQueue);
        if (task != NULL) {
            next_sp      = task->sp;
            current_task = task->id;
        } else {
            next_sp      = taskList[1].sp;
            current_task = 1;
        }
        return next_sp;
    }

    /*
     * Save stack of current task
     */
    taskList[current_task].sp = current_sp;
    if (taskList[current_task].state == TASK_RUNNING) {
        taskList[current_task].state = TASK_READY;
        TASKQ_addByPriority(&taskQueue, &taskList[current_task]);
    }

    /*
     * Update tasks
     */
    for (uint32_t idx = 1; idx < taskListIdx; idx++) {
        task_state state = taskList[idx].state;
        switch (state) {
        case TASK_READY: break;
        case TASK_RUNNING: break;
        case TASK_WAITING:
            taskList[idx].ticks -= 1;
            if (taskList[idx].ticks == 0) {
                taskList[idx].state = TASK_READY;
                TASKQ_addByPriority(&taskQueue, &taskList[idx]);
            }
            break;
        case TASK_SUSPENDED:
            // No implemented yet
            break;
        default: break;
        }
    }

    task_struct *task = TASKQ_poll(&taskQueue);
    if (task == NULL) {
        current_task = 1;
    } else {
        current_task = task->id;
    }

    next_sp = taskList[current_task].sp;

    return next_sp;
}

void taskDelay(uint32_t delay) {
    taskList[current_task].state = TASK_WAITING;
    taskList[current_task].ticks = delay;
    scheduler();
}

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

void addTickCount(void) { tickCount++; }

uint32_t getTickCount(void) { return tickCount; }
