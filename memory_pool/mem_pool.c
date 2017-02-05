/* A memory pool
 * File: mp.c
 * Author: Lin Emsber
 * Create Date: 2017, Feb, 1
 */

#include "men_pool.h"

// ========== private functions ==========


// ========== functions ==========


/* create a memory pool which has block_count number of block, and each of block's size is block_size
 *
 * @block_size: the size of one block
 * @block_count: the number of block
 */
mem_pool_t *mem_pool_create (uint32_t block_size, uint32_t block_count)
{

	// create a mem_pool
	mem_pool_t * mp;
	mp = malloc ( sizeof( *mp ) );
	if( !mp )
		return NULL;

	// allocate a space
	void * space = malloc(block_count * block_size);
	if ( !space ){
		free(mp);
		return NULL;
	}

	// set the pool's space
	pool->start = space;
	pool->end = space + (block_count * block_size);

        pool->block_size = block_size;
        pool->block_count = block_count;
        pool->next = 0;

	// create free blocks
        while (space < pool->end){
                space += block_size;
                _alloc_block();
        }

        return mp;
}


/* align byte boundary
 */
uint32_t mem_pool_align(uint32_t size)
{
	return (size + (MEM_POOL_ALIGN_SIZE - 1)) & ~(MEM_POOL_ALIGN_SIZE - 1);
}

/* decide mp_entry size
 */
uint32_t mem_pool_check_size(uint32_t size)
{
	return size <= 0 ? MEM_POOL_SIZE : mem_pool_align(size);
}
