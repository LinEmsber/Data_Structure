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

#include "types.h"

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
	uint8_t * mem_block_start;     		// the memory block start
	uint8_t * mem_block_end;     		// the memory block end

	uint32_t block_size;			// size of block
	struct mem_block * next;		// point to the next memory pool
};

struct mem_pool {
	uint32_t block_size;			// total memory pool size
	uint32_t block_count;			// the nubmer of memory pool's block

	uint8_t * start;			// the memroy start
	uint8_t * end;				// the memory end
	uint8_t * current;			// the memroy current position
	struct mem_pool * next;			// the next memory pool
};

// ========== functions ==========


#endif
