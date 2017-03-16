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
	mem_pool_t * mp_entry;

	mem_block_t *p_0;
	mem_block_t *p_1;
	mem_block_t *p_2;

	mp_entry = mem_pool_create(32, 128);
	print_mem_pool(mp_entry);

	p_0 = mem_pool_assign_block(mp_entry, 32);
	print_mem_pool(mp_entry);

	p_1 = mem_pool_assign_block(mp_entry, 128);
	print_mem_pool(mp_entry);

	p_2 = mem_pool_assign_block(mp_entry, 512);
	print_mem_pool(mp_entry);


	mem_pool_retrieve_block(mp_entry, p_1);
	print_mem_pool(mp_entry);


	mp_entry = mem_pool_free(mp_entry);

	return 0;
}
