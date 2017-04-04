/* simple_mem_pool.c */


#include "simple_mem_pool.h"


/* function */
mem_pool_t * mem_pool_create( size_t size )
{
	// mem_pool_t * mp;
	// mp = malloc( size + sizeof(*mp) );
	//
	// mp->next = (char*)&mp[1];
	// mp->end = mp->next + size;

	mem_pool_t * mp;
	mp = malloc( sizeof(*mp) );

	mp->next = (void*) malloc (size);
	mp->end = mp->next + size;

	return mp;
}

void mem_pool_destroy( mem_pool_t *mp )
{
	free(mp);
}

size_t mem_pool_available( mem_pool_t *mp )
{
	return mp->end - mp->next;
}

void * mem_pool_alloc( mem_pool_t *mp, size_t size )
{
	if( mem_pool_available(mp) < size )
		return NULL;

	void *mem = (void*)mp->next;
	mp->next += size;

	return mem;
}
