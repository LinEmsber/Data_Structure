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

	void *p_0;
	void *p_1;
	void *p_2;

	mp_entry = mem_pool_create(1024, 8);
	printf("mp_entry->remaing_size: %d\n", mp_entry->remaing_size);


	p_0 = mem_pool_add_block(mp_entry, 1024);
	printf("mp_entry->remaing_size: %d\n", mp_entry->remaing_size);
	p_1 = mem_pool_add_block(mp_entry, 512);
	printf("mp_entry->remaing_size: %d\n", mp_entry->remaing_size);
	p_2 = mem_pool_add_block(mp_entry, 1024);
	printf("mp_entry->remaing_size: %d\n", mp_entry->remaing_size);

	mem_pool_remove_block(mp_entry, p_1);


	return 0;
}
