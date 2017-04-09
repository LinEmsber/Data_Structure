/* A doubly linked list
 * File: doubly_list.h
 * Author: Lin Emsber
 * Create Date: 2017, May, 19
 */

#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <stdio.h>
#include <stdlib.h>

// ========== typedef ==========
typedef struct node node_t;
typedef struct list list_t;

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

/* node operation */
node_t * node_create(int target_value);
int node_free( node_t * node );

/* list operation */
list_t * list_create();
void list_free(list_t * list);
int list_count(list_t * list);
void list_free_node(list_t * list);

/* node insert and pop */
int list_head_insert_node(list_t * list, node_t * node);
int list_tail_insert_node(list_t * list, node_t * node);
node_t * list_head_pop_node(list_t * list);
node_t * list_tail_pop_node(list_t * list);

/* The operations of list and node */
int print_list(node_t * head);
int list_get_node_pos(list_t * list, node_t * node);
node_t * list_pick_node(list_t * list, int pos);
node_t * list_remove_specific_pos_node(list_t * list, int pos);
void list_swap_nodes( list_t * list, int pos_1, int pos_2);


#endif
