/* A doubly linked list
 * File: singly_linked_list.c
 * Author: Lin Emsber
 * Create Date: 2017, May, 22
 */

// The simple test and error check:
// gcc -g -Wall -std=c99 main.c singly_linked_list.c && valgrind -v ./a.out

#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"

#define NODE_NUMS 10

int main()
{
	int i;
	int ret = 0;

	node_t * p_element[NODE_NUMS];

	/* create a head node */
	node_t * start = node_create(0);

	for (i = 0; i < NODE_NUMS; i ++){

		/* create nodes */
		p_element[i] = node_create(i * 10 + 10);
		if(p_element == NULL)
			printf("error\n");

		/* insert nodes behind head, FILO */
		ret = node_insert( start, p_element[i] );
		if (ret < 0)
			printf("error\n");
	}

        ret = print_list( start );


	/* reverse list */
	for (i = 0; i < NODE_NUMS / 2; i ++){
		swap_nodes( &start, &p_element[i], &p_element[NODE_NUMS - 1 - i]);
	}

	ret = print_list( start );


	/* delete one node from list */
        ret = node_delete( start, 30);
	if (ret < 0)
		printf("error\n");

	ret = node_delete( start, 10);
	if (ret < 0)
		printf("error\n");

        ret = print_list( start );

	/* free all nodes of list */
	ret = node_free_all(start);
	if (ret < 0)
		printf("error\n");

	return 0;
}
