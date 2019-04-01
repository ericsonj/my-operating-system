/**
 * @file   double_buffer.h
 * @author Ericson Joseph
 * @date   Apr 1, 2019
 */

#ifndef DOUBLE_BUFFER_H_
#define DOUBLE_BUFFER_H_

#include <stdint.h>

void DBUFF_initBuffer(uint32_t size);

int16_t DBUFF_getValue(uint32_t index);

void DBUFF_setValue(uint32_t index, int16_t value);

void DBUFF_flush();

#endif /* DOUBLE_BUFFER_H_ */
