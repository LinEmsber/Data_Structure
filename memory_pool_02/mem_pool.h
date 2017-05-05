/* mp.h */

#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* write the concept of algortihm of this memory pool.
 *
 * allocate three kinds of memory for this data structure.
 * The first is for mem_pool_t, the second is for each of blocks, and the final is for mem_block_t.
 *
 * mem_pool_t controls the total allocated memory, free and used blocks, and the head of the blocks
 * mem_block_t controls the assign memory for user to use, and links to the next mem_block_t.
 */


/* typedef */

typedef struct _mem_pool_block mem_pool_block_t;
typedef struct _mem_pool mem_pool_t;

/* structure */
struct _mem_pool_block {

	uint8_t * block_start;

	uint8_t is_block_start;
	uint32_t block_size;

	struct _mem_pool_block * next;
};

struct _mem_pool {

	uint32_t block_size;
	uint32_t block_count;
	uint8_t * blocks_start_ptr;

	uint8_t * pool_start;
	uint8_t * pool_end;

	struct _mem_pool_block * available_blocks_head;
	struct _mem_pool_block * available_blocks_tail;

	struct _mem_pool * next;
};

/* function declaration */

mem_pool_t * mem_pool_create(size_t _block_size, size_t _block_count);
mem_pool_t * _create_pool(uint32_t _block_size, uint32_t _block_count);
void * mem_pool_alloc(mem_pool_t * _mem_pool);
void mem_pool_destroy_pool(mem_pool_t * _mem_pool);
int mem_pool_free(mem_pool_t * _mem_pool, void * pointer);



/* function implentation */
mem_pool_t * mem_pool_create(size_t _block_size, size_t _block_count);


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
	mp->pool_start = space;
	mp->pool_end = space + (_block_count * _block_size);

	mp->block_size = _block_size;
	mp->block_count = _block_count;
	mp->next = NULL;

	/* two pointers for operate start and end block */
	mem_pool_block_t * start_block = NULL;
	mem_pool_block_t * end_block = NULL;
	mem_pool_block_t * mpb = NULL;

	/* create and initial mem_block_t */
	_create_blocks()


	/* two pointers for operate start and end block */
	mem_pool_block_t * start_block = NULL;
	mem_pool_block_t * end_block = NULL;
	mem_pool_block_t * mpb = NULL;

	/* assign the memory from mem_pool_t to each of created blocks. */
	for ( ; mp->pool_start < mp->pool_end; space += _block_size )

		mpb = _get_next_block();

		mpb->block_size = _block_size;
		mpb->block_start = mp->space;

		mpb = mpb->next;
	}

	/* pointers to point the first and the last blocks. */
	mp->available_blocks_head = start_block;
	mp->available_blocks_tail = end_bloc;
}


void * mem_pool_alloc(mem_pool_t * _mem_pool)
{
	mem_pool_t * mp = (mem_pool_t *)_mem_pool;
	mem_pool_t tmp_mp;
	mem_pool_block_t * mpb;




	/* If no more space, we create a new memory pool. */
	if(!mp->available_blocks_head) {

		mem_pool_t * new_mp = (mem_pool_t *)_create_pool( mp->block_size, mp->block_count << 1);

		if(!new_mp)
			return 0;

		/* All blocks are managed in the first memory pool. */
		memcpy(&tmp_mp, mp, sizeof(mem_pool_t));
		memcpy(mp, new_mp, sizeof(mem_pool_t));
		memcpy(new_mp, &tmp_mp, sizeof(mem_pool_t));

		mp->next = new_mp;
	}

	/* get the first free space */
	mpb = mp->available_blocks_head;
	mp->available_blocks_head = mpb->next;

	/* initialize space data and recover blocks. */
	memset(mp->block_start, 0, mpb->block_size);

	return mp->block_start;
}


void mem_pool_destroy_pool(mem_pool_t * _mem_pool)
{
	if(!_mem_pool)
		return;

	mem_pool_t * mp = (mem_pool_t *) _mem_pool;
	mem_pool_t * tmp_pool;

	/* from mp head to mp tail */
	while(mp)
	{
		/* Free the space and remove all free blocks from head to tail. */
		free(mp->pool_start);

		mem_pool_block_t * current = mp->available_blocks_head;
		mem_pool_block_t * tmp;

		/* from head to tail. */
		while(current != NULL) {

			printf("%d\n", count++);

			tmp = current;
			current = current->next;
			free(tmp);
		}

		tmp_pool = mp;
		mp = mp->next;
		free(tmp_pool);
	}
}


int mem_pool_free(mem_pool_t * _mem_pool, void * pointer)
{
	mem_pool_t * mp = (mem_pool_t *)_mem_pool;

	mem_pool_block_t * mpb = _get_next_block();
	mem_pool_block_t * tmp;
	if(!mpb)
		return 0;

	// create a new mpb to the free list.
	mpb->start = pointer;
	mpb->next = 0;

	if(!mp->available_blocks_head && !mp->available_blocks_tail) {
		mp->available_blocks_head = mp->available_blocks_tail = mpb;
	}

	mp->available_blocks_tail->next = mpb;
	mpb->next = tmp->next;

	return 1;
}



#endif
