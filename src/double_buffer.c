/**
 * @file   double_buffer.c
 * @author Ericson Joseph
 * @date   Apr 1, 2019
 */
#include "double_buffer.h"
#include "static_memory.h"
#include "string.h"

/**
 * Definition of input buffer
 */
int16_t *bufferA;
/**
 * Definition of output buffer
 */
int16_t *bufferB;
/**
 * Definition of size
 */
uint32_t _size;

void DBUFF_initBuffer(uint32_t size) {
    _size   = size;
    bufferA = (int16_t *)MEM_malloc(size);
    bufferB = (int16_t *)MEM_malloc(size);
}

int16_t DBUFF_getValue(uint32_t index) { return bufferB[index]; }

void DBUFF_setValue(uint32_t index, int16_t value) { bufferA[index] = value; }

void DBUFF_flush() { memcpy(bufferB, bufferA, _size); }
