/**
 * @file   semphr.h
 * @author Ericson Joseph
 * @date   Mar 31, 2019
 */

#ifndef SEMPHR_H_
#define SEMPHR_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool isTake;
    uint32_t ticks;
} semaphore_t;

void semaphoreCreate(semaphore_t *rest);

void semaphoreGive(semaphore_t *semphr);

void semaphoreTakeBlocking(semaphore_t *semphr);

#endif /* SEMPHR_H_ */
