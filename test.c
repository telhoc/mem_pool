#include <stdio.h>
#include "memory.h"

memory_pool *mem_pools;

void test_mem_pool()
{

    mem_pool *bin_pool = mem_pools->pool;

    mem_block *test1 = mem_alloc(300);
    mem_block *test2 = mem_alloc(300);
    mem_block *test3 = mem_alloc(1000);
    mem_block *test4 = mem_alloc(1200);

    for (int i = 1; i <= NUM_BINS; i++)
    {
        printf("Testing pool %d \n", i);
        printf("pool %x \n", (unsigned int)bin_pool);

        mem_block *block = bin_pool->first_block;
        for (int j = 1; j < NUM_BLOCKS_IN_POOL; j++)
        {
            printf("Block %d Size %d Free %d \n", j, (int)block->size, block->is_free);
            block = block->next;
        }

        bin_pool = bin_pool->next_bin;
    }

    printf("Try free and check now \n");
    mem_free(test1);
    bin_pool = mem_pools->pool;

    for (int i = 1; i <= NUM_BINS; i++)
    {
        printf("Testing pool %d \n", i);
        printf("pool %x \n", (unsigned int)bin_pool);

        mem_block *block = bin_pool->first_block;
        for (int j = 1; j < NUM_BLOCKS_IN_POOL; j++)
        {
            printf("Block %d Size %d Free %d \n", j, (int)block->size, block->is_free);
            block = block->next;
        }

        bin_pool = bin_pool->next_bin;
    }
}

int main() {

  mem_pools = init_memory();
  test_mem_pool();  

}
