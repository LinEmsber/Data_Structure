/* A doubly linked list
 * File: singly_linked_list.c
 * Author: Lin Emsber
 * Create Date: 2017, May, 22
 */

#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"

/* Create a node. */
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

/* Add a new node to list. */
int node_insert(node_t * head, node_t * n)
{
	if (head == NULL || n == NULL)
		return -1;

	n -> next = head -> next;
	head -> next = n;

	return 0;
}

/* According to the target value to remove a node from a list and free this target node.
 *
 * I use tool: gdb, to analyze argument, head, and variable, **PP.
 * At the begin of this functions:

 * (gdb) p *head
 * $1 = {val = 0, next = 0x602150}
 * (gdb) p head
 * $2 = (node_t *) 0x602010
 * (gdb) p &head
 * $3 = (node_t **) 0x7fffffffdad8

 * After the "node_t **pp = &head;" :

 * (gdb) p **pp
 * $4 = {val = 0, next = 0x602150}
 * (gdb) p *pp
 * $5 = (node_t *) 0x602010
 * (gdb) p pp
 * $6 = (node_t **) 0x7fffffffdad8
 */
int node_delete(node_t * head, int target_val)
{
	if (head == NULL)
		return -1;

	int ret = -1;

	node_t **pp = &head;
	node_t *p = head;

	while(p){
		if(p->val == target_val){
			*pp = p->next;
			free(p);
			ret = 0;

			/* Remember to break from the while loop.
			 * The next two expressions will make errors happen,
			 * because the variable, p, is freed, it cannot be operated.
			 */
			break;
		}

		pp = &p->next;
		p = p->next;
	}

	return ret;
}

/* Free all node from a list. */
int node_free_all(node_t * head)
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

/* Print the list. */
int print_list(node_t * head)
{
	if (head == NULL)
		return -1;

	node_t * current = head;

	while ( current != NULL ){
		printf("%d ", current->val);
		current = current -> next;
	}
	printf("\n");

	return 0;
}

/* Get the previous node */
node_t * previous_node(node_t * head, node_t * target_node)
{
	if(head == target_node || head == NULL)
		return NULL;

	/* Start from the head node to find the target nodes's previous node. */
	node_t * current = head;
	node_t * prev = NULL;

	while(current){

		/* Find the target node */
		if (current == target_node)
			break;

		prev = current;
		current = current->next;
	}

	/* Return target nodes's previous node. */
	return prev;
}


/* Swap two nodes.
 * 1. Find the previous nodes of the both target nodes.
 * 2. Swap the previous nodes of the both nodes, and check if any of both nodes is the head.
 * 3. Swap the next nodes of the both nodes.
 */
int swap_nodes(node_t ** head, node_t ** node_1, node_t ** node_2)
{
	if (head == NULL|| node_1 == NULL || node_2 == NULL)
		return -1;

	node_t * first = *node_1;
	node_t * second = *node_2;
	node_t * first_prev, * second_prev;
	node_t * tmp = NULL;

	/* Find the target nodes's previous node. */
	first_prev = previous_node(*head, first);
	second_prev = previous_node(*head, second);

	/* Swap the first and the second nodes. */
	if(first_prev){
	        first_prev->next = second;
	}
	else{
	        *head = *node_2;
	}

	if(second_prev){
	        second_prev->next = first;
	}
	else{
	        *head = *node_1;
	}

	/* Swap the next nodes of both nodes */
	tmp = first->next;
	first->next = second->next;
	second->next = tmp;

	return 0;
}

/* Use iterative method to reverse linked list. */
node_t * node_reverse_iterative(node_t * head)
{
	if(head == NULL)
		return NULL;

        node_t * prev = NULL;
        node_t * next;

	/* 1. Store the next node as tmp.
	 * 2. Set the next node as prev node.
	 * 3. Set the prev node as original node.
	 * 4. Set the new head as tmp node.
	 */
        while(head != NULL){
                next = head->next;
                head->next = prev;
                prev = head;
                head = next;
        }

	return prev;
}


/* Traversal to the tail node. */
node_t * tail_node(node_t * head)
{
	if ( head == NULL )
		return NULL;

	node_t * current = head;
	node_t * prev = NULL;
	while(current != NULL){
		prev = current;
		current = current->next;
	}
	return prev;
}

/* Reverse linked list.
 * Retrun 0 for success, and -1 for fail.
 */
int node_reverse_return_int(node_t * head)
{
	if(head == NULL)
		return -1;

	node_t * current = head;
	node_t * next = NULL;
	node_t * prev = NULL;

	while ( current != NULL ){
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;

	return 0;
}
