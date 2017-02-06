/* A memory pool
 * File: mp.c
 * Author: Lin Emsber
 * Create Date: 2017, Feb, 1
 */

#include "men_pool.h"

// ========== private functions ==========


// ========== functions ==========


void _alloc_block_nodes(block_size, block_count)
{
	mem_block_t * _free_block_ptr     = 0;
	mem_block_t * _free_block_ptr_end = 0;

	uint32_t _block_size = sizeof(mem_block_t);
	uint32_t size_count  = _block_size * block_count;

	char * start;
	char * block_ptr = start = malloc(size_count);
	char * end = start + size_count;

	// can't malloc more space(s).
	if(!block_ptr)
                return;

	while ( block_ptr < end ) {
		block_ptr += _block_size;

		mem_block_t* block = (mem_block_t*)block_ptr;
		block->is_block_start  = (block_ptr == start);
		block->start = 0;

		// if it's not starting block, set previous block's next block to this.
		if(block_ptr != start)        {
			((mem_block_t*)(block_ptr - _block_size))->next = block;
		}

		block->block_size = 0;
	}

	((mem_block_t*)(end - _block_size))->next = 0;

	if(_free_block_ptr && _free_block_ptr_end) {
		// there's block pointer(s) before, and still some in the "_free_block_ptr",
		// concat newer one list to the old one's tail.
		_free_block_ptr_end->next = (mem_block_t*)start;
	} else {
		// otherwise, replace the whole "_free_block_ptr".
		_free_block_ptr = (mem_block_t*)start;
	}

	_free_block_ptr_end = (mem_block_t*)(end - _block_size);
}


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
	mp->start = space;
	mp->end = space + (block_count * block_size);

	mp->block_size = block_size;
	mp->block_count = block_count;
	mp->next = 0;

	// create free blocks
	while (space < mp->end){
		space += block_size;
		_alloc_block(mp->start, block_size, block_count);
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
