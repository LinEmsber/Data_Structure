/* A doubly linked list
 * File: doubly_list.h
 * Author: Lin Emsber
 * Create Date: 2017, May, 19
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

// ========== typedef ==========
typedef struct node node_t
typedef struct list list_t

typedef void (*free_cb_t) (void*);


// ========== structure ==========

struct node {
        int value;
	struct node * prev;
	struct node * next;
	void * data;
};

struct list {
	struct node * head;
	struct node * tail;
	int length;
};

// ========== function declaration ==========

node_t * node_create(int target_value);
int node_free( node_t * node );
list_t * list_create();
void list_free(list_t *list);
int list_count(list_t *list);
void list_free_node(list_t *list);
int * list_head_add_node(list_t *list, node_t *node);
node_t *list_head_pop_node(list_t *list);

#endif
