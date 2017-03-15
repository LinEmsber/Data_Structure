/* main */

/* An main function for memory pool.
 * File: main.c
 * Author: Lin Emsber
 * Create Date: 2017, Mar, 13
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem_pool.h"
#include "types.h"


int main()
{
	mem_pool_t * mp_entry;

	mem_block_t *p_0;
	// mem_block_t *p_1;
	// mem_block_t *p_2;

	mp_entry = mem_pool_create(32, 256);
	printf("mp_entry->block_size: %d\n", mp_entry-> block_size);
	printf("mp_entry->block_count: %d\n", mp_entry-> block_count);
	printf("mp_entry->start: %d\n", mp_entry-> start);
	printf("mp_entry->end: %d\n", mp_entry-> end);
	printf("mp_entry->current: %d\n", mp_entry-> current);
	printf("mp_entry->remaing_size: %d\n", mp_entry-> remaing_size);
	printf("mp_entry->start_block: %d\n", mp_entry-> start_block);
	printf("mp_entry->current_block: %d\n", mp_entry-> current_block);

	p_0 = mem_pool_add_block(mp_entry, 32);
	printf("mp_entry->current: %d\n", mp_entry-> current);
	printf("mp_entry->remaing_size: %d\n", mp_entry-> remaing_size);
	printf("mp_entry->start_block: %d\n", mp_entry-> start_block);
	printf("mp_entry->current_block: %d\n", mp_entry-> current_block);

	// p_1 = mem_pool_add_block(mp_entry, 128);
	// printf("mp_entry->remaing_size: %d\n", mp_entry->remaing_size);
	// p_2 = mem_pool_add_block(mp_entry, 512);
	// printf("mp_entry->remaing_size: %d\n", mp_entry->remaing_size);

	// mem_pool_remove_block(mp_entry, p_1);

	mp_entry = mem_pool_free(mp_entry);

	return 0;
}
