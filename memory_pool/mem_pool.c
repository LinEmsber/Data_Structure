/* A memory pool
 * File: mem_pool.c
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


mem_block_t * mem_pool_alloc (mem_pool_t * mp, uint32_t size)
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
	// mb->next = mp->current_block;

	// update status of mem_pool_t, mp
	mp->current = mp->current + size;
	mp->remaing_size = mp->remaing_size - size;
	mp->current_block = mb;

	// If this mem_block_t, mb, is the start block of this mem_pool_t, mp.
	if (mp->start_block == NULL){
		mb->is_start_block = 1;
		mp->start_block = mb;
		mp->start_block->next = NULL;
	}else{
		mb->is_start_block = 0;

		mem_block_t * tmp;
		tmp = mp->start_block;
		while (tmp){
			tmp = tmp->next;
		}

		tmp->next = mb;
	}

	return mb;
}

int mem_pool_retrieve (mem_pool_t * mp, mem_block_t * mb)
{
	int ret = -1;
	// mem_block_t * target_mb = mb;

	// find the target mem_block_t from the mem_pool_t first.
	// mem_block_t ** mb_head = &(mp->start_block);
	// mem_block_t * entry = (mp->start_block);

	if (mb_head == NULL || entry == NULL)
		printf("NULL\n");

	// while (entry){
	// 	if (entry == target_mb){
	// 		*mb_head = (entry)->next;
	// 		ret = 0;
	// 		break;
	// 	}
	//
	// 	mb_head = &(entry)->next;
	// 	entry = entry->next;
	// }

	// mem_block_t ** mb_tmp = &(mp->start_block);
	//
	// while ( *mb_tmp != NULL){
	//
	// 	if (*mb_tmp == target_mb){
	// 		*mb_tmp = (target_mb)->next;
	// 		break;
	// 	}
	//
	// 	*mb_tmp = (*mb_tmp)->next;
	// }


	// update the status of mem_pool_t
	mp->remaing_size += mb->block_size;
	if (target_mb->is_start_block == 1){

		printf("h2\n");
		// TODO: fix
		mp->start_block = mp->start_block->next;
		mp->start_block->is_start_block = 1;
	}

	if (mp->current_block == target_mb)
		mp->current_block = mp->current_block->next;

	free the target mem_block_t, but not free space
	SAFE_FREE(target_mb);

	return ret;
}


int mem_pool_free(mem_pool_t * mp)
{
	if (mp == NULL)
		return -1;

	// free memory pool
	free(mp->start);

	// mem_pool_t
	free(mp);

	mp = NULL;

	return 0;
}
