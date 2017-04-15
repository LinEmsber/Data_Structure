/* simple_mem_pool.c */


#include "simple_mem_pool.h"


/* function */
mem_pool_t * mem_pool_create( size_t size )
{
	mem_pool_t * mp = malloc( sizeof(*mp) );

	mp->start = (void *) malloc ( sizeof(char) * size );
	mp->next = mp->start;
	mp->end = mp->start + size;

	return mp;
}

void mem_pool_destroy( mem_pool_t *mp )
{
	free(mp->start);
	free(mp);
}

size_t mem_pool_available_space( mem_pool_t *mp )
{
	return mp->end - mp->next;
}

void * mem_pool_alloc( mem_pool_t *mp, size_t size )
{
	if( mem_pool_available_space(mp) < size )
		return NULL;

	void *mem = (void*)mp->next;
	mp->next += size;

	return mem;
}

size_t mem_pool_remaining_space( mem_pool_t *mp )
{
	size_t remaining_space = mem_pool_available_space(mp);

	return remaining_space;
}
