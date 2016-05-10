/* A multi-thread safe linked list
 * File: tree.c
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// ====================typedef====================
typedef struct bst_node bst_node_t
typedef struct bst_tree bst_tree_t

typedef void (*free_cb_t) (void*);


// ====================struct====================
struct bst_node {
	int value;
	void *data;
	struct bst_node *left;
	struct bst_node *right;
};

struct bst_tree {
    struct bst_node *root;
    int count;
};
