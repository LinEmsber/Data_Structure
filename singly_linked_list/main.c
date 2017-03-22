/* A doubly linked list
 * File: singly_linked_list.c
 * Author: Lin Emsber
 * Create Date: 2017, May, 22
 */

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
        node_t * e4 = node_create(20);
        node_t * e5 = node_create(40);

	ret = node_add( start, e1 );
	ret = node_add( start, e2 );
        ret = node_add( start, e3 );
        ret = node_add( start, e4 );
        ret = node_add( start, e5 );

        ret = print_list( start );

        ret = node_remove( start, 30);
        ret = node_remove( start, 10);

        printf("ret: %d\n", ret);

        ret = print_list( start );
        printf("ret: %d\n", ret);

	ret = node_free(start);
        printf("ret: %d\n", ret);

	return 0;
}
