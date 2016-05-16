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


// ====================list_basic_api====================

// To create a linked list.
struct list * list_create();

// To initialize a list that is using mutex for thread-safe.
int list_init(struct list *list);

// To destroy a list, including remove all list's node, and free them.
void list_destroy(struct list *list);

// Return the length of the list.
int list_count(list_t *list);

// To remove all of the list's nodes, and free them.
void list_clear(list_t *list);

// ====================node_basic_api====================

// To create a new node.
node_t node_create();

// A node remove from the list, and free it.
void node_destory( node_t * node );

// ====================node_operations====================

// Push a node to the head of the list
int *node_push_list_head(list_t *list, node_t *node);

// Pop a node from the head of list, or the top of the stack.
node_t *node_pop_list_head(list_t *list);

// Push a node to the tail of the list.
int *node_push_list_tail(list_t *list, node_t *node);

// Pop a node from the tail of list, or the bottom of the stack.
node_t *node_pop_list_tail(list_t *list);

// To return the position of a node, if it linked in a list. To search the
// position of the node from the start.
int node_get_pos(node_t *node);

// ====================list_operations====================

// Insert a node at a specified position into a list. The position of the list
// is start from 1, not 0.
int list_insert_node(list_t *list, node_t *node, int pos);

// According to the position of the node on the list to remove it.
node_t *list_remove_node_pos(list_t *list, int pos);

// Retrieve the node at position in a list, but without removing it from the
// list. Alter the status of the list, pos and cur. The position is start from
// 1, not 0. The last position is equal to the length of the list.
node_t *list_pick_node(list_t *list, int pos);

// To swap two nodes of the list.
void list_swap_nodes( list_t *list, int pos_1, inst pos_2);

// To iterate over the list.
