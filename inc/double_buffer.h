/**
 * @file   double_buffer.h
 * @author Ericson Joseph
 * @date   Apr 1, 2019
 *
 * @brief Simple double buffer implementation
 */

#ifndef DOUBLE_BUFFER_H_
#define DOUBLE_BUFFER_H_

#include <stdint.h>

/**
 * Init double buffer
 * @param size Size in bytes of input buffer and output buffer.
 */
void DBUFF_initBuffer(uint32_t size);

/**
 * Get value of output buffer by index.
 * @param index
 * @return value
 */
int16_t DBUFF_getValue(uint32_t index);

/**
 * Set value of input buffer by index.
 * @param index
 * @param value
 */
void DBUFF_setValue(uint32_t index, int16_t value);

/**
 * Copy input buffer to output buffer
 */
void DBUFF_flush();

#endif /* DOUBLE_BUFFER_H_ */
