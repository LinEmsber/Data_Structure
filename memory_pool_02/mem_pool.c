#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_pool.h"


#define ALLOC_BLOCK_NODE_COUNT 1024


mem_pool_block_t * free_block_ptr     = 0;
mem_pool_block_t * free_block_ptr_end = 0;


void _alloc_blocks()
{
	uint32_t block_size = sizeof(mem_pool_block_t);
	uint32_t total_block_size  = block_size * ALLOC_BLOCK_NODE_COUNT;

	uint8_t * start = malloc(total_block_size);
	uint8_t * block_ptr = start;
	uint8_t * end = start + total_block_size;

	/* can't malloc more space(s). */
	if(!block_ptr)
		return;

	for(; block_ptr < end; block_ptr += block_size) {

		mem_pool_block_t * mpb = (mem_pool_block_t*)block_ptr;
		mpb->is_block_start = (block_ptr == start);
		mpb->start = 0;

		/* If it's not starting mpb, set previous mpb's next mpb to this. */
		if(block_ptr != start)
			((mem_pool_block_t*)(block_ptr - block_size))->next = mpb;

		mpb->block_size = 0;
	}

	/* The last mpb's next points to NULL */
	((mem_pool_block_t*)(end - block_size))->next = NULL;

	/* If there is mpb pointers before, and still be used.
	 * The "free_block_ptr" would be non-zero, thus, we concatenate newer one list
	 * to the old one's tail.
	 */
	if(free_block_ptr && free_block_ptr_end) {

		free_block_ptr_end->next = (mem_pool_block_t*)start;

	} else {

		/* otherwise, replace the whole "free_block_ptr". */
		free_block_ptr = (mem_pool_block_t*)start;
	}

	/*free_block_ptr_end points to the last mpb. */
	free_block_ptr_end = (mem_pool_block_t*)(end - block_size);
}

mem_pool_block_t * _get_next_block()
{
	mem_pool_block_t * mpb;

	/* If no more block node, use _alloc_blocks() to generate a new block node list. */
	if(!free_block_ptr)
		_alloc_blocks();

	/* If still no more block node, return 0 to stand for error. */
	if(!free_block_ptr)
		return NULL;

	mpb = free_block_ptr;
	free_block_ptr = free_block_ptr->next;

	/* If mpb is the last one, we should set the tail to 0. */
	if(mpb == free_block_ptr_end)
		free_block_ptr_end = NULL;

	return mpb;
}

void _init_block(mem_pool_block_t * _mem_pool_block)
{
	_mem_pool_block->start = 0;
	_mem_pool_block->next = 0;
	_mem_pool_block->block_size = 0;
	_mem_pool_block->is_block_start = 0;

	if(free_block_ptr && free_block_ptr_end){

		free_block_ptr_end->next = _mem_pool_block;
		free_block_ptr_end = _mem_pool_block;

	} else 	{

		free_block_ptr = _mem_pool_block;
		free_block_ptr_end = _mem_pool_block;
	}
}

int _mem_pool_count_free_blocks(mem_pool_t * _mem_pool)
{
	int count;
	mem_pool_block_t * mpb;

	if(!_mem_pool->free_blocks_head)
		return 0;

	mpb = _mem_pool->free_blocks_head;
	count = 1;

	while(mpb != _mem_pool->free_blocks_tail) {
		count++;
		mpb = mpb->next;
	}

	return count;
}

mem_pool_handle _create_pool(uint32_t _block_size, uint32_t _block_count)
{
	mem_pool_t * mp = malloc( sizeof(*mp) );
	if(!mp)
		return NULL;

	uint8_t * space = malloc(_block_count * _block_size);
	if(!space){
		free(mp);
		return NULL;
	}

	mem_pool_block_t * start_block = 0;
	mem_pool_block_t * end_block   = 0;


	mp->start = space;
	mp->end = space + (_block_count * _block_size);

	mp->block_size = _block_size;
	mp->block_count = _block_count;
	mp->next = NULL;

	/* create free nodes. */
	for(; space < mp->end; space += _block_size) {

		/* Get the next block node.
		 * If no more block node, use _alloc_blocks() to generate a new block node list.
		 */
		mem_pool_block_t * mpb = _get_next_block();
		if(!start_block)
			start_block = mpb;

		/* If we can't create any more mpb, free mp and space,
		 * and recover all mp blocks genereated before.
		 */
		if(!mpb) {
			free(mp);
			free(space);

			while(start_block) {
				mem_pool_block_t* next = start_block->next;
				_init_block(start_block);
				start_block = next;
			}

			return NULL;
		}

		mpb->block_size = _block_size;
		mpb->start = space;
		mpb->next = NULL;

		// concat mpb to the tail of block list
		if(end_block)
			end_block->next = mpb;

		end_block = mpb;
	}

	/* pointers to point the first and the last blocks. */
	mp->free_blocks_head = start_block;
	mp->free_blocks_tail = end_block;

	return (uint8_t*)mp;
}

void mem_pool_print_info(mem_pool_handle _mem_pool)
{
	mem_pool_t * mp = (mem_pool_t*)_mem_pool;
	if( !mp )
		return;

	int pool_id = 0;

	while(mp){
		printf("----- POOL OF SIZE [%.4d] -----\n", mp->block_size);
		printf("+ id: %d\n", pool_id++);
		printf("+ count: %d\n", mp->block_count);
		printf("+ spaces: [%p, %p]\n", mp->start, mp->end);

		if(pool_id == 1)
			printf("+ free blocks: %d\n", _mem_pool_count_free_blocks(mp));
		else
			printf("+ free blocks: -\n");

		mp = mp->next;
	}
}

mem_pool_handle mem_pool_create_pool(size_t _block_size, size_t _block_count)
{
#ifdef _DEBUG
	uint8_t * pool = _create_pool(_block_size, _block_count);
	printf("A new pool of [%d] is created!", _block_size);
	return pool;
#endif

	return _create_pool(_block_size, _block_count);
}


void mem_pool_destroy_pool(mem_pool_handle _handle)
{
	if(!_handle)
		return;

	mem_pool_t * mp = (mem_pool_t*)_handle;
	mem_pool_t * next_pool;

	/* from mp head to mp tail */
	while(mp)
	{
		/* Free the space and remove all free blocks from head to tail. */
		free(mp->start);

		/* All the blocks are mansged in the first mp. */
		if(mp == (mem_pool_t*)_handle) {

			mem_pool_block_t * current = mp->free_blocks_head;
			mem_pool_block_t * next;

			/* from head to tail. */
			while(current) {
				next = current->next;
				_init_block(current);
				current = next;
			}
		}

		next_pool = mp->next;
		free(mp);
		mp = next_pool;
	}

	return;
}

uint8_t * mem_pool_alloc(mem_pool_handle handle)
{
	mem_pool_t * mp = (mem_pool_t*)handle;
	mem_pool_t tmp_mp;
	mem_pool_block_t * mpb;
	uint8_t * space;

	/* If no more space, we create a new memory pool. */
	if(!mp->free_blocks_head) {

		mem_pool_t * new_mp = (mem_pool_t *)_create_pool( mp->block_size, mp->block_count << 1);

		if(!new_mp)
			return 0;

		/* No matter how many pools here, all free blocks are managed in the
		 * first memory pool.
		 */
		memcpy(&tmp_mp, mp, sizeof(mem_pool_t));
		memcpy(mp, new_mp, sizeof(mem_pool_t));
		memcpy(new_mp, &tmp_mp, sizeof(mem_pool_t));

		mp->next = new_mp;

	}

	/* get the first free space */
	mpb = mp->free_blocks_head;
	mp->free_blocks_head = mpb->next;
	space = mpb->start;

	if(!mp->free_blocks_head)
		mp->free_blocks_tail = NULL;

	/* initialize space data and recover blocks. */
	memset(space, 0, mpb->block_size);
	_init_block(mpb);

	return space;
}

int mem_pool_free(mem_pool_handle _handle, uint8_t * pointer)
{
	mem_pool_t * mp = (mem_pool_t *)_handle;

	mem_pool_block_t * mpb = _get_next_block();
	if(!mpb)
		return 0;

	// create a new mpb to the free list.
	mpb->block_size = mp->block_size;
	mpb->start = pointer;
	mpb->next = 0;

	if(!mp->free_blocks_head && !mp->free_blocks_tail) {

		mp->free_blocks_head = mp->free_blocks_tail = mpb;
		return 1;

	}

	mp->free_blocks_tail->next = mpb;
	mp->free_blocks_tail = mpb;

	return 1;
}
