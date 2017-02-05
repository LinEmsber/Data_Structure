/* A memory pool
 * File: mp.h
 * Author: Lin Emsber
 * Create Date: 2017, Jan, 31
 */


#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define MEM_POOL_SIZE   (1024 * 1024)
#define MEM_POOL_ALIGN_SIZE 8

// ========== free ==========
void _safe_free(void **pp)
{
	if (pp != NULL && *pp != NULL){
		free(*pp);
		*pp = NULL;
	}
}

#define SAFE_FREE(p) _safe_free( (void**) &p )


// ========== typedef ==========
typedef struct mem_block mem_block_t;
typedef struct mem_pool mem_pool_t;


// ========== strutcture ==========
struct mem_block {
	void * pool;     			// memory pool
	uint32_t block_size			// size of block
	struct mem_block * next;		// point to the next memory pool
	uint8_t is_block_start;			// this block is the starting block or not
};

struct mem_pool {
	uint32_t block_size;			// total memory pool size
	uint32_t block_count;			// the nubmer of memory pool's block

	void * start;				// memroy start
	void * end;				// memory end
	struct mem_pool * next;			// the next memory pool
};

// ========== functions ==========


#endif
