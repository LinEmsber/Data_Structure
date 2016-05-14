/* A multi-thread safe linked list
 * File: list.h
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// ====================typedef====================
typedef struct node node_t
typedef struct list list_t
typedef struct slice slice_t

typedef void (*free_cb_t) (void*);


// ====================struct====================

struct node {
	struct node *prev;
	struct node *next;
	struct list *list;
	void *value;
};

struct list {
	// basic
	struct node *head;
	struct node *tail;
	int length;

	// the status of list
	struct node *cur;
	int pos;

	// special opetaions
	pthread_mutex_t mutex;
	free_cb_t free_cb;
	struct list *slices;
};

struct slice {
	struct list *list;
	int offset;
	int length;
};

// ====================list_basic_api====================


// create list
struct list * list_create();
// list init
int list_init(struct list *list);
// list destroy
void list_destroy(struct list *list);
// return list length
int list_count(list_t *list);
// remove list's nodes, and free them.
void list_clear(list_t *list);

// ====================node_basic_api====================

// create a new node
node_t node_create();
void node_destory( node_t * node );

// ====================node_operations====================

// push a node to the tail of the list.
int *node_push_list_tail(list_t *list, node_t *node)
// push a node to the head of the list
int *node_push_list_head(list_t *list, node_t *node)
// pop a node from the end of list, or the bottom of the stack.
node_t *node_pop(list_t *list)

// ====================list_operations====================

// According to the position of the node on the list to remove it.
node_t *list_remove_node_pos(list_t *list, int pos)
// Retrieve the node at pos in a list, but without removing it from the list.
// Alter the status of the list, pos and cur.
node_t *list_pick_node(list_t *list, int pos)
