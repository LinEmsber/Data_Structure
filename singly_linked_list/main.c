/* A doubly linked list
 * File: singly_linked_list.c
 * Author: Lin Emsber
 * Create Date: 2017, May, 22
 */

// The simple test and error check:
// valgrind --leak-check=yes -v ./a.out

#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"


int main()
{
	int ret = 0;

	node_t * start = node_create(0);
	node_t * e1 = node_create(10);
	node_t * e2 = node_create(30);
        node_t * e3 = node_create(50);
        node_t * e4 = node_create(70);
        node_t * e5 = node_create(90);
	node_t * e6 = node_create(100);
	node_t * e7 = node_create(200);

	ret = node_insert( start, e1 );
	ret = node_insert( start, e2 );
        ret = node_insert( start, e3 );
        ret = node_insert( start, e4 );
        ret = node_insert( start, e5 );
	ret = node_insert( start, e6 );
	ret = node_insert( start, e7 );

        ret = print_list( start );

        ret = node_delete( start, 30);
        ret = node_delete( start, 100);

        printf("ret: %d\n", ret);

        ret = print_list( start );
        printf("ret: %d\n", ret);

	ret = node_free_all(start);
        printf("ret: %d\n", ret);

	return 0;
}
