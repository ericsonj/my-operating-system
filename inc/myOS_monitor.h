/**
 * @file   myOS_monitor.h
 * @author Ericson Joseph
 * @date   Apr 14, 2019
 *
 * @brief Monitor ticks state of operating system
 */

#ifndef MYOS_MONITOR_H_
#define MYOS_MONITOR_H_

#include <stdlib.h>
#include <stdint.h>

/**
 * Struct of monitor counters
 */
typedef struct {
    uint32_t start_os;    /**< clock when start myOS*/
    uint32_t idle_ticks;  /**< idle ticks counter*/
    uint32_t ticks_count; /**< ticks_counter */
} os_monitor_s;

/**
 * Get monitor report
 * @return os_monitor_s
 */
os_monitor_s getMonitor();

/**
 * Reset monitor, values to zero
 */
void monitorReset();

#endif /* MYOS_MONITOR_H_ */
