/* A memory pool
 * File: mp.h
 * Author: Lin Emsber
 * Create Date: 2017, Jan, 31
 */


#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define mp_POOL_SIZ   (1024 * 1024)
#define mp_ALIGN_SIZE (8)

// ========== free ==========
void _safe_free(void **pp)
{
	if (pp != NULL && *pp != NULL){
		free(*pp);
		*pp = NULL;
	}
}

#define SAFE_FREE(p) _safe_free( (void**) &p )

// ========== check NULL ==========
#define CHECK_NULL(p) if ( p == NULL) {return NULL;}


// ========== typedef ==========
typedef struct mp_entry mp_entry_t;
typedef struct mp_table mp_table_t;

// ========== strutcture ==========
struct mp_entry {
	void * pool;     		// memory pool
	struct mp_entry * next;		// point to the next memory pool
};

struct mp_table {
	struct mp_entry * head; 		// the head of memory pool
	void * begin; 				// data for internal conduct
	size_t max_size; 			// max pool size of current pool
	size_t used_size;			// used pool size of current pool
	struct mp_entry * mp; 			// the memory pool entry which this table point to currently
};

// ========== functions ==========
mp_table_t *mp_table_create (size_t size);
void *mp_table_alloc(mp_table_t *pool, size_t size);
void mp_table_destroy (mp_table_t *pool);

#endif
