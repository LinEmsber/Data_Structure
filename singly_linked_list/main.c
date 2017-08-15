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

	node_t * p_tail, * p_tmp;
	node_t * p_element[NODE_NUMS];
	node_t * root = node_create(0);

	for (i = 0; i < NODE_NUMS; i ++){

		p_element[i] = node_create(i * 10 + 10);
		if(p_element == NULL)
			printf("error\n");

		/* Insert nodes behind head, FILO. */
		ret = node_insert( root, p_element[i] );
		if (ret < 0)
			printf("error\n");
	}

	printf("Original: \n");
        print_list( root );

	/* Use iterative method to reverse list. */
	printf("Reverse list: \n");
	p_tail = tail_node(root);
	ret = node_reverse_return_int(root);
	if ( ret < 0 )
		return -1;
	print_list(p_tail);

	printf("Reverse list, again: \n");
	p_tmp = node_reverse_iterative(p_tail);
	print_list(p_tmp);


	/* Use swap_nodes() to reverse list. */
	for (i = 0; i < NODE_NUMS / 2; i ++){
		swap_nodes( &root, &p_element[i], &p_element[NODE_NUMS - 1 - i]);
	}

	printf("Use swap_nodes() to reverse list: \n");
	print_list( root );

	/* Delete one node from list */
        ret = node_delete( root, 30);
	if (ret < 0)
		printf("error\n");

	ret = node_delete( root, 10);
	if (ret < 0)
		printf("error\n");

	printf("Delete node 30 and node 10: \n");
        print_list(root);

	/* Free all nodes of list */
	ret = node_free_all(root);
	if (ret < 0)
		printf("error\n");

	return 0;
}
