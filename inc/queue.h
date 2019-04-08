/**
 * @file   queue.h
 * @author Ericson Joseph
 * @date   Apr 7, 2019
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
#include "list.h"

typedef struct {
    uint16_t size;
    uint8_t itemSize;
    struct list_s *list;
} queueHandler;

queueHandler queueCreate(uint8_t size, uint16_t itemSize);

uint8_t queueSend(queueHandler queue, void *item);

uint8_t queueReceiveBloking(queueHandler queue, void *item);

#endif /* QUEUE_H_ */
