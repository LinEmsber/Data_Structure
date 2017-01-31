/* A memory pool
 * File: mem_pool.h
 * Author: Lin Emsber
 * Create Date: 2017, Jan, 31
 */


#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MEM_POOL_POOL_SIZ   (1024 * 1024)
#define MEM_POOL_ALIGN_SIZE (8)

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
typedef struct mem_pool_entry mem_pool_entry_t;
typedef struct mem_pool_table mem_pool_table_t;

// ========== strutcture ==========
struct mem_pool_entry {
	void * pool;     		// memory pool
	struct mem_pool_entry * next;	// point to the next memory pool
};

struct mem_pool_table {
	struct mem_pool_entry * head; 		// the head of memory pool
	void * begin; 				// data for internal conduct
	size_t max_size; 			// max pool size of current pool
	size_t used_size;			// used pool size of current pool
	struct mem_pool_entry * mem_pool; 	// the memory pool entry which this table point to currently
};

// ========== functions ==========
mem_pool_table_t *mem_pool_create (size_t size);
void *mem_pool_alloc(mem_pool_table_t *pool, size_t size);
void mem_pool_destroy (mem_pool_table_t *pool);

#endif
