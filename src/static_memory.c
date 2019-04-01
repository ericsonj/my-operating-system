/**
 * @file   static_memory.c
 * @author Ericson Joseph
 * @date   March 2019
 * @brief  Static Memory Allocation
 */

#include "static_memory.h"
#include <string.h>

static uint32_t mem32Size =
    NUM_BLOCK_32 * (BLOCK_SIZE_32 + sizeof(struct mem_block_s));
static uint32_t mem64Size =
    NUM_BLOCK_64 * (BLOCK_SIZE_64 + sizeof(struct mem_block_s));
static uint32_t mem128Size =
    NUM_BLOCK_128 * (BLOCK_SIZE_128 + sizeof(struct mem_block_s));
static uint32_t mem256Size =
    NUM_BLOCK_256 * (BLOCK_SIZE_256 + sizeof(struct mem_block_s));
static uint32_t mem512Size =
    NUM_BLOCK_512 * (BLOCK_SIZE_512 + sizeof(struct mem_block_s));
#if __USE_BLOCK_1024__
static uint32_t mem1024Size =
    NUM_BLOCK_1024 * (BLOCK_SIZE_1024 + sizeof(struct mem_block_s));
#endif

static void MEM_initStaticMem(BYTE mem[], uint32_t memSize, uint32_t blockSize);
static bool MEM_blockIsFree(void *ptr);
static void MEM_setBlockUse(void *ptr);
static void *MEM_mallocBySize(BYTE mem[], uint32_t memSize, uint32_t blockSize);

void MEM_init() {
    MEM_initStaticMem(mem_32, mem32Size, BLOCK_SIZE_32);
    MEM_initStaticMem(mem_64, mem64Size, BLOCK_SIZE_64);
    MEM_initStaticMem(mem_128, mem128Size, BLOCK_SIZE_128);
    MEM_initStaticMem(mem_256, mem256Size, BLOCK_SIZE_256);
    MEM_initStaticMem(mem_512, mem512Size, BLOCK_SIZE_512);
#if __USE_BLOCK_1024__
    MEM_initStaticMem(mem_1024, mem1024Size, BLOCK_SIZE_1024);
#endif
}

void *MEM_malloc(uint32_t size) {
    void *rest = NULL;
    if (size <= BLOCK_SIZE_32) {
        rest = MEM_mallocBySize(mem_32, mem32Size, BLOCK_SIZE_32);
    } else if (size <= BLOCK_SIZE_64) {
        rest = MEM_mallocBySize(mem_64, mem64Size, BLOCK_SIZE_64);
    } else if (size <= BLOCK_SIZE_128) {
        rest = MEM_mallocBySize(mem_128, mem128Size, BLOCK_SIZE_128);
    } else if (size <= BLOCK_SIZE_256) {
        rest = MEM_mallocBySize(mem_256, mem256Size, BLOCK_SIZE_256);
    } else if (size <= BLOCK_SIZE_512) {
        rest = MEM_mallocBySize(mem_512, mem512Size, BLOCK_SIZE_512);
    }
#if __USE_BLOCK_1024__
    else if (size <= BLOCK_SIZE_1024) {
        rest = MEM_mallocBySize(mem_1024, mem1024Size, BLOCK_SIZE_1024);
    }
#endif
    else {
    }
    return rest;
}

void MEM_free(void *prt) {
    BYTE *prt_dst = (BYTE *)prt;
    prt_dst       = (prt_dst - sizeof(struct mem_block_s));
    struct mem_block_s block;
    memcpy(&block, prt_dst, sizeof(struct mem_block_s));
    if ((block.dst_size & MASK_MEM_VERSION_MSK) == MASK_MEM_VERSION) {
        block.dst_size |= MASK_MEM_FREE;
        memcpy(prt_dst, &block, sizeof(struct mem_block_s));
    }
}

void MEM_initStaticMem(BYTE mem[], uint32_t memSize, uint32_t blockSize) {
    uint32_t idx = 0;
    struct mem_block_s block;
    block.padding  = 0xAAAA;
    block.dst_size = 0;
    block.dst_size = blockSize & MASK_MEM_SIZE;
    block.dst_size |= MASK_MEM_FREE;
    block.dst_size |= MASK_MEM_VERSION;
    while ((idx + sizeof(struct mem_block_s) + blockSize) <= memSize) {
        memcpy(&mem[idx], &block, sizeof(struct mem_block_s));
        idx = idx + (sizeof(struct mem_block_s)) + blockSize;
    }
}

bool MEM_blockIsFree(void *ptr) {
    BYTE *dsc_size = (BYTE *)ptr;
    struct mem_block_s block;
    memcpy(&block, dsc_size, sizeof(struct mem_block_s));
    return block.dst_size & MASK_MEM_FREE;
}

void MEM_setBlockUse(void *ptr) {
    BYTE *dsc_size = (BYTE *)ptr;
    struct mem_block_s block;
    memcpy(&block, dsc_size, sizeof(struct mem_block_s));
    block.dst_size &= (~MASK_MEM_FREE);
    memcpy(ptr, &block, sizeof(struct mem_block_s));
}

void *MEM_mallocBySize(BYTE mem[], uint32_t memSize, uint32_t blockSize) {
    uint32_t idx = 0;
    while ((idx + sizeof(struct mem_block_s) + blockSize) <= memSize) {
        if (MEM_blockIsFree(&mem[idx])) {
            MEM_setBlockUse(&mem[idx]);
            bzero(&mem[idx + sizeof(struct mem_block_s)], blockSize);
            return &mem[idx + sizeof(struct mem_block_s)];
        }
        idx = idx + (sizeof(struct mem_block_s)) + blockSize;
    }
    return NULL;
}
