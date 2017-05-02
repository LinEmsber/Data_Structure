#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef _DEBUG
extern int create_pool_count;
#endif

/* typedef */
// typedef uint8_t * mem_pool_t *;

typedef struct _mem_pool_block mem_pool_block_t;
typedef struct _mem_pool mem_pool_t;

/* structure */
struct _mem_pool_block {
	uint8_t * start;
	uint32_t block_size;

	struct _mem_pool_block * next;
	uint8_t is_block_start;
};

struct _mem_pool {
	uint32_t block_size;
	uint32_t block_count;
	uint8_t * blocks_start_ptr;

	uint8_t * start;
	uint8_t * end;

	struct _mem_pool_block * available_blocks_head;
	struct _mem_pool_block * available_blocks_tail;

	struct _mem_pool * next;
};


/* function */
mem_pool_t * mem_pool_create_pool(size_t _block_size, size_t _block_count);
void mem_pool_destroy_pool(mem_pool_t * pool);

void * mem_pool_alloc(mem_pool_t * _mem_pool);
int mem_pool_free(mem_pool_t * _mem_pool, void * pointer);

void mem_pool_print_info(mem_pool_t * pool);



/**************************/


#define ALLOC_BLOCK_NODE_COUNT 32

#ifdef _DEBUG
int create_pool_count = 0;
#endif

mem_pool_block_t * free_block_ptr = NULL;
mem_pool_block_t * free_block_ptr_end = NULL;

uint8_t * blocks_start = NULL;


int _alloc_blocks(mem_pool_t * _mem_pool, size_t _block_size, size_t _block_count)
{
	// uint32_t block_size = sizeof(mem_pool_block_t);
	uint32_t total_block_size  = _block_size * _block_count;

	uint8_t * start = malloc(total_block_size);
	_mem_pool->blocks_start_ptr = start;

	uint8_t * block_ptr = start;
	uint8_t * end = start + total_block_size;

	/* can't malloc more space(s). */
	if(!block_ptr)
		return 1;

	for(; block_ptr < end; block_ptr += _block_size) {

		mem_pool_block_t * mpb = (mem_pool_block_t *)block_ptr;
		mpb->is_block_start = (block_ptr == start);
		mpb->start = 0;

		/* If it's not starting mpb, set previous mpb's next mpb to this. */
		if(block_ptr != start)
			((mem_pool_block_t *)(block_ptr - _block_size))->next = mpb;

		mpb->block_size = 0;
	}

	/* The last mpb's next points to NULL */
	((mem_pool_block_t *)(end - _block_size))->next = NULL;

	/* If there is mpb pointers before, and still be used.
	 * The "free_block_ptr" would be non-zero, thus, we concatenate newer one list
	 * to the old one's tail.
	 */
	if(free_block_ptr && free_block_ptr_end) {

		free_block_ptr_end->next = (mem_pool_block_t *)start;

	} else {

		/* otherwise, replace the whole "free_block_ptr". */
		free_block_ptr = (mem_pool_block_t *) start;
		printf("free_block_ptr: %p\n", free_block_ptr);
	}

	/*free_block_ptr_end points to the last mpb. */
	free_block_ptr_end = (mem_pool_block_t *)(end - _block_size);

	return 0;
}

mem_pool_block_t * _get_next_block()
{
	mem_pool_block_t * mpb;

	// /* If no more block node, use _alloc_blocks() to generate a new block node list. */
	// if(!free_block_ptr)
	// 	_alloc_blocks();
	//
	// /* If still no more block node, return 0 to stand for error. */
	// if(!free_block_ptr)
	// 	return NULL;

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

	if(!_mem_pool->available_blocks_head)
		return 0;

	mpb = _mem_pool->available_blocks_head;
	count = 1;

	while(mpb != _mem_pool->available_blocks_tail) {
		count++;
		mpb = mpb->next;
	}

	return count;
}

mem_pool_t * _create_pool(uint32_t _block_size, uint32_t _block_count)
{
	mem_pool_t * mp = malloc( sizeof(*mp) );
	if(!mp)
		return NULL;

	uint8_t * space = malloc(_block_count * _block_size);
	if(!space){
		free(mp);
		return NULL;
	}

	/* initialize memory pool */
	mp->start = space;
	mp->end = space + (_block_count * _block_size);

	mp->block_size = _block_size;
	mp->block_count = _block_count;
	mp->next = NULL;

	/* two pointers for operate start and end block */
	mem_pool_block_t * start_block = NULL;
	mem_pool_block_t * end_block = NULL;
	mem_pool_block_t * mpb = NULL;

	/* Check the blocks have been created or not, or we allocate the blocks. */
	if (!free_block_ptr)
		if ( _alloc_blocks(mp, _block_size, _block_count) != 0 )
			return NULL;

	/* assign the correct size to create free blocks. */
	for(; space < mp->end; space += _block_size) {

		/* Get the next block node. */
		mpb = _get_next_block();
		if(!start_block)
			start_block = mpb;

		/* If we can't create any more mpb, free mp and space,
		 * and recover all mp blocks genereated before.
		 */
		if(!mpb) {
			free(mp);
			free(space);

			while(start_block) {
				mem_pool_block_t * next = start_block->next;
				// _init_block(start_block);
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
	mp->available_blocks_head = start_block;
	mp->available_blocks_tail = end_block;

#ifdef _DEBUG
	create_pool_count++;
#endif

	return mp;
}

void mem_pool_print_info(mem_pool_t * _mem_pool)
{
	mem_pool_t * mp = (mem_pool_t *)_mem_pool;
	if( !mp )
		return;

	int pool_id = 0;

	while(mp){
		printf("----- POOL OF SIZE [%d] -----\n", mp->block_size);
		printf("+ The order of memory pool: %d\n", pool_id++);
		printf("+ Total count: %d\n", mp->block_count);
		printf("+ spaces: [%p, %p]\n", mp->start, mp->end);

		if(pool_id == 1)
			printf("+ free blocks: %d\n", _mem_pool_count_free_blocks(mp));
		else
			printf("+ free blocks: -\n");

		mp = mp->next;
	}
}

mem_pool_t * mem_pool_create_pool(size_t _block_size, size_t _block_count)
{
#ifdef _DEBUG
	mem_pool_t * mp = _create_pool(_block_size, _block_count);
	printf("A new pool is created, each block size is: %zu\n", _block_size);
	return mp;
#endif

	return _create_pool(_block_size, _block_count);
}


void mem_pool_destroy_pool(mem_pool_t * _mem_pool)
{
	int count = 100;
	if(!_mem_pool)
		return;

	mem_pool_t * mp = (mem_pool_t *) _mem_pool;
	mem_pool_t * tmp_pool;

	/* from mp head to mp tail */
	while(mp)
	{
		/* Free the space and remove all free blocks from head to tail. */
		free(mp->start);

		/* All the blocks are mansged in the first mp. */
		// if(mp == (mem_pool_t *)_mem_pool) {

			mem_pool_block_t * current = mp->available_blocks_head;
			mem_pool_block_t * tmp;
			printf("current: %p\n", current);

			free(blocks_start);
			// /* from head to tail. */
			// while(current != NULL) {
			//
			// 	printf("%d\n", count++);
			//
			// 	tmp = current;
			// 	current = current->next;
			// 	free(tmp);
			//
			// 	// _init_block(current);
			// }
		// }

		tmp_pool = mp;
		mp = mp->next;
		free(tmp_pool);
		// mp = next_pool;
		// next_pool = mp->next;
		// free(mp);
	}

	return;
}

void * mem_pool_alloc(mem_pool_t * _mem_pool)
{
	mem_pool_t * mp = (mem_pool_t *)_mem_pool;
	mem_pool_t tmp_mp;
	mem_pool_block_t * mpb;
	uint8_t * space;

	/* If no more space, we create a new memory pool. */
	if(!mp->available_blocks_head) {

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
	mpb = mp->available_blocks_head;
	mp->available_blocks_head = mpb->next;
	space = mpb->start;

	if(!mp->available_blocks_head)
		mp->available_blocks_tail = NULL;

	/* initialize space data and recover blocks. */
	memset(space, 0, mpb->block_size);
	// _init_block(mpb);

	return space;
}

int mem_pool_free(mem_pool_t * _mem_pool, void * pointer)
{
	mem_pool_t * mp = (mem_pool_t *)_mem_pool;

	mem_pool_block_t * mpb = _get_next_block();
	if(!mpb)
		return 0;

	// create a new mpb to the free list.
	mpb->block_size = mp->block_size;
	mpb->start = pointer;
	mpb->next = 0;

	if(!mp->available_blocks_head && !mp->available_blocks_tail) {

		mp->available_blocks_head = mp->available_blocks_tail = mpb;
		return 1;

	}

	mp->available_blocks_tail->next = mpb;
	mp->available_blocks_tail = mpb;

	return 1;
}


#endif
