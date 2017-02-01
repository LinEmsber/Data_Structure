/* A memory pool
 * File: mem_pool.c
 * Author: Lin Emsber
 * Create Date: 2017, Feb, 1
 */

#include "men_pool.h"

// ========== private functions ==========
static inline bool mpool_extend(mem_pool_entry_t *p, size_t size, mem_pool_table_t *pool);
static inline size_t mpool_align(size_t size);
static inline size_t mpool_decide_create_siz(size_t size);

// ========== functions ==========
mem_pool_table_t *mpool_create (size_t size)
{
	// check does the size is too large induce overflow or not
	size = mpool_decide_create_siz(size);

	// create a mem_pool_table
	mem_pool_table_t * mp = (mem_pool_table_t *) malloc ( sizeof(mem_pool_table_t) );
	CHECK_NULL(mp);

	// create a mem_pool_entry for mem_pool_table
	mp->mem_pool = (mem_pool_entry_t *) malloc ( sizeof(mem_pool_entry_t) );
	CHECK_NULL(mp->mem_pool)

	// allocate specific size of memory for this mem_pool_entry
	mp->mem_pool->pool = malloc(size);
	CHECK_NULL(mp->mem_pool->pool);
	mp->mem_pool->next = NULL;

	// initialize this mem_pool_table
	mp->begin = mp->mem_pool->pool;
	mp->head  = mp->mem_pool;
	mp->usiz  = 0;
	mp->msiz  = size;

	return mp;
}
