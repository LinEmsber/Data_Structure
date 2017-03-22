/* A doubly linked list
 * File: singly_linked_list.h
 * Author: Lin Emsber
 * Create Date: 2017, May, 22
 */

#include "singly_linked_list.h"


#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

typedef struct node node_t;

struct node{
	int val;
	struct node * next;
};



node_t * node_create(int val);
int node_add(node_t * head, node_t * n);
int node_remove(node_t * head, int target_val);
int node_free(node_t * head);
int print_list(node_t * head);


#endif
