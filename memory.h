#pragma once

#include <stdlib.h>

#define NUM_BLOCKS_IN_POOL 50

#define NUM_BINS 3
#define MAX_BIN_SIZE 1500
#define BIN1 500
#define BIN2 1000
#define BIN3 1500

extern int bin_sizes[NUM_BINS];

typedef struct mem_block
{
    size_t size;
    struct mem_block *next;
    int is_free;
    void *pool; //Pointer to the pool it belongs to
    void *mem; // Pointer to the allocated memory
} mem_block;

// Memory pool, one for each bin
typedef struct mem_pool
{
    size_t bin_size;
    struct mem_block *first_block; // The first block in the pool
    struct mem_pool *next_bin;     // Pointer to the next bin
    int num_used;
} mem_pool;

typedef struct memory_pool_type
{
    mem_pool *pool; // Pointer to the first bin
    int initialized;
} memory_pool;

extern memory_pool *mem_pools;

memory_pool *init_memory();
mem_block *mem_alloc(size_t size);
void mem_free(mem_block *block);
void test_mem_pool();