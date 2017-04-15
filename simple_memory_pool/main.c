/* simple memory pool
 *
 * USAGE: gcc -Wall -std=c99 main.c simple_mem_pool.c && ./a.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simple_mem_pool.h"

#define BLOCK_NUMS 100

int main()
{
        int i, j;

        size_t remaining;
        mem_pool_t * mp_entry;
        void * p_block[BLOCK_NUMS];

        /* The string for copying into each p_block */
	char str_for_copy[8] = "ABCDEFG";


        /* memory pool create */
        mp_entry = mem_pool_create(1024);
        if (!mp_entry)
                printf("error\n");

        for (i = 0; i < BLOCK_NUMS; i++){

                /* allocate the memory block for every p_block. */
                p_block[i] = mem_pool_alloc(mp_entry, 8);
                if (!p_block[i])
                        printf("error\n");

                /* write some string into p_block[i] */
                strncpy(p_block[i], str_for_copy, 7);

                for (j = 0; j < 7; j++){
			str_for_copy[j] ++;
			str_for_copy[j] = ( (str_for_copy[j] - 65) % 52) + 65;
		}

		printf("string: %s\n", str_for_copy);

        }

        /* print the remaining space of the memory pool */
        remaining = mem_pool_remaining_space( mp_entry );
        printf("The remaining space of memory pool: %lu\n", remaining);

        /* free the memory pool */
        mem_pool_destroy(mp_entry);

        return 0;
}
