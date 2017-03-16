/* Generic functions
 * File: generic.c
 * Author: Lin Emsber
 * Create Date: 2017, Mar, 16
 */



#include <stdio.h>
#include <stdlib.h>
#include "mem_pool.h"


/* A safty way to free memroy */
void _safe_free(void **pp)
{
	if (pp != NULL && *pp != NULL){
		free(*pp);
		*pp = NULL;
	}
}

#define SAFE_FREE(p) _safe_free( (void**) &p )


/* print structure mem_pool_t for debug */
void print_mem_pool( mem_pool_t * mp )
{
	// printf("mp->block_size: %d\n", mp-> block_size);
	// printf("mp->block_count: %d\n", mp-> block_count);
	// printf("mp->start: %d\n", mp-> start);
	// printf("mp->end: %d\n", mp-> end);
	// printf("mp->current: %d\n", mp-> current);
	printf("mp->remaing_size: %d\n", mp-> remaing_size);
	// printf("mp->start_block: %d\n", mp-> start_block);
	// printf("mp->current_block: %d\n", mp-> current_block);
}

/* print structure mem_block_t for debug */
void print_mem_block( mem_block_t * mb )
{
	// printf("mb->mem_block_start: %d\n", mb->mem_block_start);
	// printf("mb->mem_block_end: %d\n", mb->mem_block_end);
	printf("mb->is_start_block: %d\n", mb->is_start_block);
	printf("mb->block_size: %d\n", mb->block_size);
	// printf("mb->next: %d\n", mb->next);
}


/* align byte boundary */
uint32_t size_align(uint32_t size)
{
	return (size + (MEM_POOL_ALIGN_SIZE - 1)) & ~(MEM_POOL_ALIGN_SIZE - 1);
}

/* decide mp_entry size */
uint32_t size_check(uint32_t size)
{
	return size <= 0 ? MEM_POOL_SIZE : size_align(size);
}
