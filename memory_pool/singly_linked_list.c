/* A singly linked list using memory pool to allocate memory.
 * File: singly_linked_list.c
 * Author: Lin Emsber
 * Create Date: 2017, Mar, 22
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem_pool.h"
#include "types.h"
#include "generic.h"

typedef struct node node_t;

struct node{
	int val;
	struct node * next;
};

/* create a node */
node_t * node_create(int val)
{
	node_t * n;

	n = malloc( sizeof(*n) );
	if (n == NULL)
		return NULL;

	n -> val = val;
	n -> next = NULL;

	return n;
}

/* add a new node */
int node_add(node_t * head, node_t * n)
{
        if (head == NULL || n == NULL)
                return -1;

	n -> next = head -> next;
	head -> next = n;

        return 0;
}

/* According to the target value to remove a node from a list,
 * and free this target node.
 */
int node_remove(node_t * head, int target_val)
{
        if (head == NULL)
                return -1;

        int ret = -1;

	node_t **pp = &head;
	node_t *entry = head;

	while(entry){
		if(entry->val == target_val){
                        *pp = entry->next;
                        free(entry);
                        ret = 0;
                }

		pp = &entry->next;
		entry = entry->next;
	}

	return ret;
}

/* free all node from a list */
int node_free(node_t * head)
{
	if (head == NULL)
		return -1;

	node_t * current = head;
	node_t * tmp;

	while ( current != NULL ){
		tmp = current;
                current = current -> next;
                free(tmp);
	}

	return 0;
}

/* print the list */
int print_list(node_t * head)
{
	if (head == NULL)
		return -1;

	node_t * current = head;

	while ( current != NULL ){
		printf("%d\n", current->val);
                current = current -> next;
	}

	return 0;
}
