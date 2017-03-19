/* main */

/* An main function of doubly linked list.
 * File: main.c
 * Author: Lin Emsber
 * Create Date: 2017, Mar, 19
 */

#include <stdio.h>
#include <stdlib.h>

#include "doubly_list.h"
#include "generic.h"


int main()
{
        list_t * list_entry = list_create();

        node_t * n1 = node_create(10);
        node_t * n2 = node_create(30);
        node_t * n3 = node_create(50);

        list_head_add_node(list_entry, n1);
        list_head_add_node(list_entry, n2);
        list_head_add_node(list_entry, n3);

	return 0;
}
