/* A memory pool
 * File: mp.c
 * Author: Lin Emsber
 * Create Date: 2017, Feb, 1
 */

#include "men_pool.h"

// ========== private functions ==========


// ========== functions ==========
mp_table_t *mp_create (size_t size)
{
	// check does the size is too large induce overflow or not
	size = mpool_decide_create_siz(size);

	// create a mp_table
	mp_table_t * mp = (mp_table_t *) malloc ( sizeof(mp_table_t) );
	CHECK_NULL(mp);

	// create a mp_entry for mp_table
	mp->mp = (mp_entry_t *) malloc ( sizeof(mp_entry_t) );
	CHECK_NULL(mp->mp)

	// allocate specific size of memory for this mp_entry
	mp->mp->pool = malloc(size);
	CHECK_NULL(mp->mp->pool);
	mp->mp->next = NULL;

	// initialize this mp_table
	mp->begin = mp->mp->pool;
	mp->head  = mp->mp;
	mp->usiz  = 0;
	mp->msiz  = size;

	return mp;
}
