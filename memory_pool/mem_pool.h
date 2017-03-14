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

typedef struct mem_block {
	uint8_t * mem_block_start;     		// the memory block start
	uint8_t * mem_block_end;     		// the memory block end

	uint8_t is_start_block;			// Is this block is the start block in memory pool?

	uint32_t block_size;			// size of block
	struct mem_block * next;		// point to the next memory block
}mem_block_t;

typedef struct mem_pool {

	// elements would not be changed after mem_pool_t be created.
	uint32_t block_size;			// the basic block size
	uint32_t block_count;			// the nubmer of memory pool's block

	uint8_t * start;			// the memroy start
	uint8_t * end;				// the memory end

	// elements would be changed according to the use situation.
	uint8_t * current;			// the memroy current position
	uint8_t remaing_size;			// the remaing memory of memory pool
	struct mem_block * start_block;		// the start block of mem_pool_t
	struct mem_block * current_block;	// the current block of mem_pool_t

}mem_pool_t;


mem_pool_t * mem_pool_create (uint32_t block_size, uint32_t block_count);
mem_pool_t * mem_pool_add_block (mem_pool_t * mp, uint32_t size);
mem_pool_t * mem_pool_remove_block (mem_pool_t * mp, mem_block_t * mb);


#endif
