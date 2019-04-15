/**
 * @file   task_queue.h
 * @author Ericson Joseph
 * @date   Apr 1, 2019
 *
 * @brief Queue of task with priority for scheduler planning.
 */
#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include "task.h"

/**
 * Initialize queue.
 * @param queue
 * @param maxSize
 */
void TASKQ_Init(struct list_s *queue, uint32_t maxSize);

/**
 * Add task to queue in last position.
 * @param queue
 * @param _task
 */
void TASKQ_add(struct list_s *queue, task_struct *_task);

/**
 * Add task in queue in order by priority.
 * @param queue
 * @param _task
 */
void TASKQ_addByPriority(struct list_s *queue, task_struct *_task);

/**
 * Add task in first position.
 * @param queue
 * @param _task
 */
void TASKQ_addFirst(struct list_s *queue, task_struct *_task);

/**
 * Insert task in index position.
 * @param queue
 * @param index
 * @param _task
 */
void TASKQ_insert(struct list_s *queue, uint32_t index, task_struct *_task);

/**
 * Retrieves and removes the head (first element) of queue.
 * @param queue
 * @return task_struct
 */
task_struct *TASKQ_poll(struct list_s *queue);

#ifdef __cplusplus
}
#endif

#endif /* TASK_QUEUE_H */
