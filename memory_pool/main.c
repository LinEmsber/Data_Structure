/* main */

/* An main function for memory pool.
 * File: main.c
 * Author: Lin Emsber
 * Create Date: 2017, Mar, 13
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem_pool.h"
#include "generic.h"
#include "types.h"


int main()
{
	int ret;
	mem_pool_t * mp_entry;

	mem_block_t *p_0;
	mem_block_t *p_1;
	mem_block_t *p_2;

	// TODO: use this memory pool to implement a signly linked list.

	mp_entry = mem_pool_create(32, 128);
	print_mem_pool(mp_entry);

	p_0 = mem_pool_alloc(mp_entry, 4);
	print_mem_pool(mp_entry);

	p_1 = mem_pool_alloc(mp_entry, 128);
	print_mem_pool(mp_entry);

	p_2 = mem_pool_alloc(mp_entry, 512);
	print_mem_pool(mp_entry);


	mem_pool_retrieve(mp_entry, p_0);
	printf("mem_pool_retrieve\n");
	// mem_pool_retrieve(mp_entry, p_1);
	// mem_pool_retrieve(mp_entry, p_2);
	print_mem_pool(mp_entry);


	ret = mem_pool_free(mp_entry);

	return 0;
}
