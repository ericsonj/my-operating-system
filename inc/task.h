/**
 * @file   task.h
 * @author Ericson Joseph
 * @date   Mar 30, 2019
 *
 * @brief   Task definitions and functions
 */

#ifndef TASK_H_
#define TASK_H_

#include <stdint.h>
#include "semphr.h"
#include "queue.h"

typedef void *(*task_type)(void *);

typedef enum { WAIT_TICKS = 1, WAIT_SEMPHR, WAIT_SYSCALL } task_wait_state;

/**
 * State of task in operating system
 */
typedef enum {
    TASK_RUNNING = 1, //!< TASK_RUNNING
    TASK_READY,       //!< TASK_READY
    TASK_WAITING,     //!< TASK_WAITING
    TASK_SUSPENDED    //!< TASK_SUSPENDED
} task_state;

/**
 * Task struct
 */
typedef struct {
    uint32_t id;         /**< ID of task*/
    task_state state;    /**< Task state*/
    uint32_t sp;         /**< Stack pointer of task*/
    int8_t priority;     /**< Priority of task, minimum value: -128 and maximum
                            value: 127*/
    uint32_t ticks;      /**< ticks of task in TASk_WAITING*/
    semaphore_t *semphr; /**< Semaphore pointer of task*/
    queueHandler queue;  /**< Handler queue of task*/
    task_wait_state
        wait_state; /**< Wait state when task_state iqual TASK_WAITING*/
    uint8_t (*syscall)(void *); /**< Syscall function callback*/
} task_struct;

/**
 * Create task in operating system
 * @param stackSizeBytes
 * @param entry_point
 * @param priority
 * @param args
 */
void taskCreate(uint32_t stackSizeBytes,
                task_type entry_point,
                int8_t priority,
                void *args);

/**
 * Put task in TASK_WAITING for 'delay' systicks.
 * @param delay
 */
void taskDelay(uint32_t delay);

#endif /* TASK_H_ */
