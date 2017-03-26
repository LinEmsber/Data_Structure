/* A doubly linked list
 * File: singly_linked_list.h
 * Author: Lin Emsber
 * Create Date: 2017, May, 22
 */

#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"


// structure
typedef struct node node_t;

struct node{
	int val;
	struct node * next;
};


// function
node_t * node_create(int val);
int node_insert(node_t * head, node_t * n);
int node_delete(node_t * head, int target_val);
int node_free_all(node_t * head);
int print_list(node_t * head);


#endif
