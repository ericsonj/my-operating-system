/**
 * @file   semphr.h
 * @author Ericson Joseph
 * @date   Mar 31, 2019
 *
 * @brief Semaphore implementation.
 */

#ifndef SEMPHR_H_
#define SEMPHR_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool isTake;    /**< Take flag.*/
    uint32_t ticks; /**< (For future implementations). */
} semaphore_t;

/**s
 * Create binary semaphore, the take flag is set.
 * @param rest
 */
void semaphoreCreate(semaphore_t *rest);

/**
 * Give semaphore, set take flag in false.
 * @param semphr
 */
void semaphoreGive(semaphore_t *semphr);

/**
 * Take semaphore in blocking mode.
 * @param semphr
 */
void semaphoreTakeBlocking(semaphore_t *semphr);

#endif /* SEMPHR_H_ */
