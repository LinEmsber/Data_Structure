/* simple_mem_pool.h */

#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdio.h>
#include <stdlib.h>

/* structure */
typedef struct _mem_pool mem_pool_t;

struct _mem_pool{
	void * start;
	char * next;
	char * end;
};

/* function */
mem_pool_t * mem_pool_create( size_t size );
void mem_pool_destroy( mem_pool_t *mp );
size_t mem_pool_available_space( mem_pool_t *mp );
void * mem_pool_alloc( mem_pool_t *mp, size_t size );
size_t mem_pool_remaining_space( mem_pool_t *mp );


#endif
