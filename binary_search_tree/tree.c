/* A multi-thread safe linked list
 * File: tree.c
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */

#include "tree.h"

// ==================compare==================

// number compare function for tree to add node
int compare_number(int original_value, int new_value)
{
	// turn left, return -1
	if(original_value > new_value) {
		return -1;

	// turn right, return 1
	}else if(original_value < new_value) {
		return 1;

	// equal, return 1
	}else {
		return 0;
	}
}

// 		(equal)
// 		0
//          /        \
// 	/		\
// (left)		   (right)
// -1			       1


// ==================tree==================
// create a new binary search tree.
bst_tree_t *tree_create()
{
	bst_tree_t *tree = (bst_tree_t*) malloc (sizeof(bst_tree_t));
	return tree;
}

// initialize binary search tree
void tree_init( bst_tree_t *tree)
{
	tree -> root = NULL;
	tree -> count = 0;
}

// remove the nodes of a tree, including free the memory of nods
void tree_clear_node( bst_tree_t *tree)
{
	node_free(tree->root);
	tree -> root = NULL;
	tree -> count = 0;
}

// deallocate a binary search tree, including remove its nodes
void tree_remove( bst_tree_t *tree)
{
	tree_clear_node(tree);
	free(tree);
}

// return the count of tree
int tree_count(bst_tree_t *tree)
{
	return tree -> count;
}

// ==================node==================
// create a node of binary search tree
bst_node_t *node_create ()
{
	bst_node_t *node = (bst_node_t *)malloc(sizeof(bst_node_t));
	return node;
}

// free the hierarchical nodes(children) of a root/node(parent).
void node_free( bst_node_t *root)
{
	if (root != 0){
		node_free(root->left);
		node_free(root->right);
		free(root);
	}
}
