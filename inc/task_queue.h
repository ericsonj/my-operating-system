/*
 * File:   task_queue.h
 * Author: Ericson Joseph <ericsonjoseph@gmail.com>
 *
 * Created on March 30, 2019, 9:54 AM
 */

#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include "task.h"

void TASKQ_Init(struct list_s *queue, uint32_t maxSize);

void TASKQ_add(struct list_s *queue, task_struct *_task);

void TASKQ_addByPriority(struct list_s *queue, task_struct *_task);

void TASKQ_addFirst(struct list_s *queue, task_struct *_task);

void TASKQ_insert(struct list_s *queue, uint32_t index, task_struct *_task);

task_struct *TASKQ_poll(struct list_s *queue);

#ifdef __cplusplus
}
#endif

#endif /* TASK_QUEUE_H */
