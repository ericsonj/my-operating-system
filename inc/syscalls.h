/**
 * @file   syscalls.h
 * @author Ericson Joseph
 * @date   Apr 7, 2019
 */

#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#include <stdint.h>

enum Syscall_response { SYSCALL_END = 1, SYSCALL_IN_PROCESSING, SYSCALL_ERR };

uint8_t syscall_sleep(void *task);

uint8_t syscall_semphr(void *task);

uint8_t syscall_queueReceiveBloking(void *task);

uint8_t syscall_queueSendBloking(void *task);

#endif /* SYSCALLS_H_ */
