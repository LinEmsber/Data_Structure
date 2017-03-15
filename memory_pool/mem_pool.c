/* A memory pool
 * File: mp.c
 * Author: Lin Emsber
 * Create Date: 2017, Feb, 1
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem_pool.h"
#include "types.h"
#include "generic.h"


/* create a memory pool which has block_count number of block, and each of block's size is block_size
 *
 * @block_size: the size of one block
 * @block_count: the number of block
 */
mem_pool_t * mem_pool_create (uint32_t block_size, uint32_t block_count)
{
	int total_size = block_size * block_count;

	// create a mem_pool
	mem_pool_t * mp;
	mp = malloc ( sizeof( *mp ) );
	if( !mp )
		return NULL;

	// allocate a space
	// uint8_t * space = malloc(block_count * block_size);
	void * space = malloc(total_size);
	if ( !space ){
		free(mp);
		return NULL;
	}

	// set the pool's setting
	mp->block_size = block_size;
	mp->block_count = block_count;

	mp->start = space;
	mp->end = space + (total_size);

	mp->current = space;

	mp->remaing_size = total_size;
	mp->start_block = NULL;
	mp->current_block = NULL;

	return mp;
}


mem_block_t * mem_pool_add_block (mem_pool_t * mp, uint32_t size)
{
	// check mem pool size is enough or not
	if (mp->remaing_size < size)
		return NULL;

	// create a mem_block
	mem_block_t * mb;
	mb = malloc ( sizeof ( *mb ) );
	if ( !mb )
		return NULL;

	// assign memory for this mem_block_t, mb
	mb->mem_block_start = mp->current;
	mb->mem_block_end = mp->current + size;

	mb->block_size = size;
	mb->next = mp->current_block;

	// update status of mem_pool_t, mp
	mp->current = mp->current + size;
	mp->remaing_size = mp->remaing_size - size;
	mp->current_block = mb;

	// If this mem_block_t, mb, is the start block of this mem_pool_t, mp.
	if (mp->start_block = NULL){
		mb->is_start_block = 1;
		mp->start_block = mb;
	}else{
		mb->is_start_block = 0;
	}

	return mb;
}

mem_pool_t * mem_pool_remove_block (mem_pool_t * mp, mem_block_t * mb)
{
	mem_block_t * target_mb = mb;

	// find the target mem_block_t from the mem_pool_t first.
	mem_block_t ** mb_tmp = &(mp->start_block);

	// TODO: fix bug
	while ( *mb_tmp != NULL){

		if (*mb_tmp == target_mb){
			*mb_tmp = (target_mb)->next;
			break;
		}

		*mb_tmp = &(*mb_tmp)->next;
	}


	// update the status of mem_pool_t
	mp->remaing_size -= mb->block_size;
	if (target_mb->is_start_block == 1)
		mp->start_block = mp->start_block->next;

	if (mp->current_block == target_mb)
		mp->current_block = mp->current_block->next;

	// free the target mem_block_t
	SAFE_FREE(target_mb);

	return mp;
}


mem_pool_t * mem_pool_free(mem_pool_t *mp)
{
	// free memory pool
	free(mp->start);

	//
	free(mp);

	mp = NULL;

	return mp;
}
