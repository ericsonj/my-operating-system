/*
 * File:   static_memory.h
 * Author: Ericson Joseph <ericsonjoseph@gmail.com>
 *
 * Created on March 31, 2019, 11:33 AM
 */

#ifndef STATIC_MEMORY_H
#define STATIC_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define __USE_BLOCK_1024__ 0

#if __USE_BLOCK_1024__
#define BLOCK_SIZE_1024 1024 // 1024 BYTES
#define NUM_BLOCK_1024 10
#endif

#define BLOCK_SIZE_512 512 // 256 BYTES
#define NUM_BLOCK_512 20   // 512*20 = 10240 BYTES 10KB

#define BLOCK_SIZE_256 256 // 256 BYTES
#define NUM_BLOCK_256 20   // 256*20 = 5120 BYTES  5KB

#define BLOCK_SIZE_128 128 // 128 BYTES
#define NUM_BLOCK_128 20   // 128*20 = 2560 BYTES  2KB

#define BLOCK_SIZE_64 64 // 63 BYTES
#define NUM_BLOCK_64 40  // 64*40 = 2560 BYTES   2KB

#define BLOCK_SIZE_32 32 // 32 BYTES
#define NUM_BLOCK_32 40  // 32*40 = 1280 BYTES   1KB

#define MASK_MEM_VERSION_MSK 0xC000
#define MASK_MEM_VERSION 0x8000
#define MASK_MEM_SIZE 0x07FF
#define MASK_MEM_FREE 0x2000

typedef uint8_t BYTE;

struct mem_block_s {
    uint16_t dst_size;
};

BYTE mem_32[NUM_BLOCK_32 * (BLOCK_SIZE_32 + sizeof(struct mem_block_s))];
BYTE mem_64[NUM_BLOCK_64 * (BLOCK_SIZE_64 + sizeof(struct mem_block_s))];
BYTE mem_128[NUM_BLOCK_128 * (BLOCK_SIZE_128 + sizeof(struct mem_block_s))];
BYTE mem_256[NUM_BLOCK_256 * (BLOCK_SIZE_256 + sizeof(struct mem_block_s))];
BYTE mem_512[NUM_BLOCK_512 * (BLOCK_SIZE_512 + sizeof(struct mem_block_s))];
#if __USE_BLOCK_1024__
BYTE mem_1024[NUM_BLOCK_1024 * (BLOCK_SIZE_1024 + sizeof(struct mem_block_s))];
#endif

void MEM_init();

void *MEM_malloc(uint32_t size);

void MEM_free(void *prt);

#ifdef __cplusplus
}
#endif

#endif /* STATIC_MEMORY_H */
