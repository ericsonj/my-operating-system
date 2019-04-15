/**
 * @file   queue.h
 * @author Ericson Joseph
 * @date   Apr 7, 2019
 *
 * @brief Simple queue implementation
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
#include "list.h"

typedef struct {
    uint16_t size;       /**< Maximum size of queue.*/
    uint8_t itemSize;    /**< Size in bytes of queue item.*/
    struct list_s *list; /**< Pointer to list*/
} queueHandler;

/**
 * Create queue
 * @param size Maximum size of queue.
 * @param itemSize Size in bytes of queue item.
 * @return queueHandler
 */
queueHandler queueCreate(uint8_t size, uint16_t itemSize);

/**
 * Add element to queue
 * @param queue
 * @param item
 * @return uint8_t Return 1 if queue has space.
 */
uint8_t queueSend(queueHandler queue, void *item);

/**
 * Get item from queue, blocking mode.
 * @param queue
 * @param item
 * @return uint8_t Return 1 if item can be taken
 */
uint8_t queueReceiveBlocking(queueHandler queue, void *item);

#endif /* QUEUE_H_ */
