/* simple memory pool */

#include <stdio.h>
#include <stdlib.h>

#include "simple_mem_pool.h"

int main()
{
        // mem_pool_t * mem_pool_create( size_t size );
        // void mem_pool_destroy( mem_pool_t *mp );
        // size_t mem_pool_available( mem_pool_t *mp );
        // void * mem_pool_alloc( mem_pool_t *mp, size_t size );

        mem_pool_t * mp;
        void * p_1;
        void * p_2;
        void * p_3;

        mp = mem_pool_create(1024);

        p_1 = mem_pool_alloc(mp, 512);
        if (p_1)
                printf("error\n");

        p_2 = mem_pool_alloc(mp, 200);
        if (p_2)
                printf("error\n");

        // p_3 = mem_pool_alloc(mp, 512);
        // if (p_3)
        //         printf("error\n");


}
