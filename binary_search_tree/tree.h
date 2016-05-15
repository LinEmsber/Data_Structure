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

// ==================compare==================

// The number compare function for adding a node to the binary search tree.
int compare_number(int original_value, int new_value);


// ==================tree==================
// To create a new binary search tree.
bst_tree_t *tree_create();

// To initialize binary search tree.
void tree_init( bst_tree_t *tree);

// To remove the nodes from a tree, including free the memory of this node.
void tree_clear_node( bst_tree_t *tree);

// To deallocate a binary search tree, including remove its all nodes.
void tree_remove( bst_tree_t *tree);

// To return the count of the tree.
int tree_count(bst_tree_t *tree);


// ==================node==================
// To create a node of binary search tree.
bst_node_t *node_create ();

// To free the hierarchical nodes(children) of a root/node(parent).
void node_free( bst_node_t *root);

// To initialize a node.
bst_node_t *node_init( bst_node_t*node);

// To input the value to a node.
bst_node_t *node_input_value(bst_node_t*node, int input_value);


// ==================node add==================
// A node be added a node with value.
bst_node_t *node_add_node( bst_node_t *node, int input_value);

// A tree be added a node with value.
bst_tree_t *tree_add_node( bst_tree_t *tree, int input_value);


// ==================left most==================
// To return the left most node from a node.
bst_node_t *node_left_most( bst_node_t *node);

// To return the left most node from a node.
bst_tree_t *tree_left_most(bst_tree_t *tree);


// ==================remove node==================
// To remove the left most node.
void node_remove_left_most(bst_node_t *node);

// To remove a node that is with specific value from the hierarchy of a node.
bst_node_t *node_remove_node(bst_node_t *node, int input_value);

// To remove a node that is with specific value from a tree.
bst_tree_t *tree_remove_node(bst_tree_t *tree, int input_value);


// ==================operation==================
// To check the value is contained in a hierarchy of a node.
bst_node_t *is_node_contain_value(bst_node_t *node, int iuput_value);

// To check a tree is contained a node with specific value.
bst_tree_t *is_tree_contain_value(bst_tree_t *tree, int iuput_value);

// Compute the height of a tree, the number of nodes along the longest path
// from the root node down to the farthest leaf node.
int node_height(bst_node_t* node);


// ==================breadth first search==================
// Print nodes at a given level.
int print_given_level(bst_node_t* root, int level);

// To print level order traversal a tree
void print_breadth_first_search(bst_node_t* root);


// ==================depth first search==================
// The depth first search pre order.
void DFS_pre_order(bst_node_t *root);

// The depth first search in order.
void DFS_in_order(bst_node_t *root);

// The depth first search post order
void DFS_post_order(bst_node_t *root);
