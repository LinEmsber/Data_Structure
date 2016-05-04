/* A multi-thread safe linked list
 * File: list.h
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// ====================typedef====================
struct list_node_s node_t
struct linked_list_s list_t

typedef void (*free_cb_t) (void*);


// ====================struct====================

struct node {
	struct list *list;
	struct node *prev;
	struct node *next;
	void *value;
	int tagged;
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

struct _slice_s {
    struct list *list;
    int offset;
    int length;
};

// ====================list====================

struct list * list_create();
int list_init(struct list *list);
void list_destroy(struct list *list);
