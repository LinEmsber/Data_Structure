/* A multi-thread safe linked list
 * File: list.h
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// ====================typedef====================
typedef struct list_node node_t
typedef struct linked_list list_t
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
    struct node *head;
    struct node *tail;
    struct node *curr;
    int pos;
    int length;
    pthread_mutex_t mutex;
    free_cb_t free_cb;
    struct list *slices;
};

struct slice {
    struct list *list;
    int offset;
    int length;
};

// ====================list====================

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

// ====================node====================

// create a new node
node_t node_create();
void node_destory( node_t * node );
