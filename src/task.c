/**
 * @file   task.c
 * @author Ericson Joseph
 * @date   Mar 31, 2019
 */
#include "static_memory.h"
#include "task_queue.h"
#include "myOS.h"
#include "task.h"
#include "syscalls.h"

extern task_struct taskList[MAX_TASK_LIST];
extern uint32_t current_task;
extern uint32_t taskListIdx;
extern struct list_s taskQueue;

void taskCreate(uint32_t stackSizeBytes,
                task_type entry_point,
                int8_t priority,
                void *args) {

    taskList[taskListIdx].id       = taskListIdx;
    taskList[taskListIdx].state    = TASK_READY;
    taskList[taskListIdx].priority = priority;
    taskList[taskListIdx].syscall  = NULL;

    uint32_t *stack = (uint32_t *)MEM_malloc(stackSizeBytes);
    initStack(stack, stackSizeBytes, &taskList[taskListIdx].sp, entry_point,
              args);

    TASKQ_addByPriority(&taskQueue, &taskList[taskListIdx]);

    taskListIdx++;
}

void taskDelay(uint32_t delay) {
    taskList[current_task].state      = TASK_WAITING;
    taskList[current_task].wait_state = WAIT_SYSCALL;
    taskList[current_task].ticks      = delay;
    taskList[current_task].syscall    = syscall_sleep;
    scheduler();
}
