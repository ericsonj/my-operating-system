/**
 * @file   syscalls.h
 * @author Ericson Joseph
 * @date   Apr 7, 2019
 *
 * @brief Syscall of operating system implementation.
 */

#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#include <stdint.h>

/**
 * Struct of response syscall.
 */
enum Syscall_response {
    SYSCALL_END = 1,       //!< SYSCALL_END
    SYSCALL_IN_PROCESSING, //!< SYSCALL_IN_PROCESSING
    SYSCALL_ERR            //!< SYSCALL_ERR
};

/**
 * Syscall sleep.
 * @param task
 * @return
 */
uint8_t syscall_sleep(void *task);

/**
 * Syscall semaphore
 * @param task
 * @return
 */
uint8_t syscall_semphr(void *task);

/**
 * Syscall queue receive blocking mode.
 * @param task
 * @return
 */
uint8_t syscall_queueReceiveBlocking(void *task);

/**
 * Syscall queue Send blocking mode.
 * @param task
 * @return
 */
uint8_t syscall_queueSendBloking(void *task);

#endif /* SYSCALLS_H_ */
