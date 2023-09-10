#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int bin_sizes[NUM_BINS] = {500, 1000, 1500};

/**
 * Initialize and allocate memory for our memory pools
 */
memory_pool *init_memory()
{
    memory_pool *mem_pools = malloc(sizeof(memory_pool));
    mem_pools->initialized = 500;

    mem_pool *current_bin_pool = NULL; // The pool we are currently allocating

    for (int i = 0; i < NUM_BINS; i++)
    {

        // Create the pool for this bin
        mem_pool *bin_pool = malloc(sizeof(mem_pool));
        bin_pool->bin_size = bin_sizes[i];
        bin_pool->next_bin = NULL;
        bin_pool->num_used = 0;

        // Is this the first bin
        if (i == 0)
        {
            // Make this bin the first bin
            mem_pools->pool = bin_pool;
            current_bin_pool = bin_pool;
        }
        else
        {
            // Let the previous bin point to this one
            current_bin_pool->next_bin = bin_pool;
            current_bin_pool = bin_pool;
        }

        // Create the first block in the pool
        mem_block *current_block = malloc(sizeof(mem_block));
        bin_pool->first_block = current_block;
        current_block->is_free = 1;
        current_block->size = bin_pool->bin_size;
        current_block->next = NULL;
        current_block->mem = malloc(bin_pool->bin_size);
        current_block->pool = bin_pool;

        // Allocate memory for the rest of the pool
        for (int j = 1; j < NUM_BLOCKS_IN_POOL; j++)
        {
            mem_block *new_block = malloc(sizeof(mem_block));
            new_block->is_free = 1;
            new_block->size = bin_pool->bin_size;
            new_block->next = NULL;
            new_block->mem = malloc(bin_pool->bin_size);
            new_block->pool = bin_pool;

            // Let the previous block point to this new block
            current_block->next = new_block;

            // Make the new block the current block
            current_block = new_block;
        }
    }

    return mem_pools;
}

mem_block *mem_alloc(size_t size)
{

    //printf("Alloc size (3) %d \n", size);

    // Safety check, do not go over max
    if (size > MAX_BIN_SIZE)
        return NULL;

    // Find the correct bin
    mem_pool *bin_pool = mem_pools->pool;
    while (bin_pool->bin_size < size)
    {
        bin_pool = bin_pool->next_bin;
    }

    // Find the first available block
    mem_block *ret_block = bin_pool->first_block;
    while (ret_block->is_free == 0)
    { // TODO: Make sure we have available memory
        ret_block = ret_block->next;
    }
    ret_block->is_free = 0;
    bin_pool->num_used++;

    //printf("Num used (3) %d %d \n", bin_pool->bin_size, bin_pool->num_used);

    return ret_block;
}

void mem_free(mem_block *block)
{
    block->is_free = 1;
    mem_pool *bin_pool = block->pool;
    bin_pool->num_used--;
}
