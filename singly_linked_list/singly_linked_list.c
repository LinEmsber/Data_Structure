/* A doubly linked list
 * File: singly_linked_list.c
 * Author: Lin Emsber
 * Create Date: 2017, May, 22
 */

#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"

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
int node_insert(node_t * head, node_t * n)
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
int node_delete(node_t * head, int target_val)
{
	if (head == NULL)
		return -1;

	int ret = -1;

	/*
	   I use tool: gdb to analyze argument, head, and variable, **PP.
	   At the begin of this functions:

	   (gdb) p *head
	   $1 = {val = 0, next = 0x602150}
	   (gdb) p head
	   $2 = (node_t *) 0x602010
	   (gdb) p &head
	   $3 = (node_t **) 0x7fffffffdad8

	   After the "node_t **pp = &head;" :

	   (gdb) p **pp
	   $4 = {val = 0, next = 0x602150}
	   (gdb) p *pp
	   $5 = (node_t *) 0x602010
	   (gdb) p pp
	   $6 = (node_t **) 0x7fffffffdad8

	 */

	node_t **pp = &head;
	node_t *entry = head;

	while(entry){
		if(entry->val == target_val){
			*pp = entry->next;
			free(entry);
			ret = 0;

			/* Remember to break from the while loop.
			 * The next two expressions will make errors happen,
			 * because the variable, entry, is freed, it cannot be operated.
			 */
			break;
		}

		pp = &entry->next;
		entry = entry->next;
	}

	return ret;
}

/* free all node from a list */
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

/* print the list */
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

/* get the previous node */
node_t * previous_node(node_t * head, node_t * target_node)
{
	if(head == target_node || head == NULL)
		return NULL;

	/* start from the head node to find the target nodes's previous node. */
	node_t * current = head;
	node_t * previous_target_node = NULL;

	while(current){

		/* find the target node */
		if (current == target_node)
			break;

		previous_target_node = current;
		current = current->next;
	}

	/* return target nodes's previous node. */
	return previous_target_node;
}


/* swap two nodes */
int swap_nodes(node_t **head, node_t **node_1, node_t **node_2)
{
	if (head == NULL|| node_1 == NULL || node_2 == NULL)
		return -1;

	node_t * first = *node_1;
	node_t * second = *node_2;
	node_t * previous_first, * previous_second;

	/* find the target nodes's previous node. */
	previous_first = previous_node(*head, first);
	previous_second = previous_node(*head, second);

	/* swap the first and the second nodes */
	if(previous_first)
		previous_first->next = second;

	if(previous_second)
		previous_second->next = first;

	/* swap the next nodes of both nodes */
	node_t * tmp = NULL;

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

        node_t * pre = NULL;
        node_t * head_next_tmp;

        while(head != NULL){
                head_next_tmp = head->next;
                head->next = pre;
                pre = head;
                head = head_next_tmp;
        }

	return pre;
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
