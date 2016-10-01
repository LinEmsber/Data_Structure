/* A multi-thread safe linked list
 * File: tree.c
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */

#include "tree.h"

// ==================compare==================

// The number compare function for adding a node to the binary search tree.
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
// To create a new binary search tree.
bst_tree_t *tree_create()
{
	bst_tree_t *tree = (bst_tree_t*) malloc (sizeof(bst_tree_t));
	return tree;
}

// To initialize binary search tree.
void tree_init( bst_tree_t *tree)
{
	tree -> root = NULL;
	tree -> count = 0;
}

// To remove the nodes from a tree, including free the memory of this node.
void tree_clear_node( bst_tree_t *tree)
{
	node_free(tree->root);
	tree -> root = NULL;
	tree -> count = 0;
}

// To deallocate a binary search tree, including remove its all nodes.
void tree_remove( bst_tree_t *tree)
{
	tree_clear_node(tree);
	free(tree);
}

// To return the count of the tree.
int tree_count(bst_tree_t *tree)
{
	return tree -> count;
}

// ==================node==================
// To create a node of binary search tree.
bst_node_t *node_create ()
{
	bst_node_t *node = (bst_node_t *)malloc(sizeof(bst_node_t));
	return node;
}

// To free the hierarchical nodes(children) of a root/node(parent).
void node_free( bst_node_t *root)
{
	if (root != 0){
		node_free(root->left);
		node_free(root->right);
		free(root);
	}
}

// To initialize a node.
bst_node_t *node_init( bst_node_t*node)
{
	node -> value = 0;
	node -> data = NULL;
	node -> left = NULL;
	node -> right = NULL;
	return node;
}

// To input the value to a node.
bst_node_t *node_input_value(bst_node_t*node, int input_value)
{
	node -> value = input_value;
	return node;
}

// To input the data to a node.
bst_node_t *node_input_data(bst_node_t*node, void* input_data)
{
	node -> data = input_data;
	return node;
}


// ==================node add==================
// A node be added a node with value.
bst_node_t *node_add_node( bst_node_t *node, int input_value)
{
	if (node == NULL){
		node = node_create();
		node_init(node);
		node_input_value(node, input_value);
		return node;
	} else {
		// node -> value > input_value, turn left
		if (compare_num(node->value, input_value) == -1 ){
			node -> left = node_add_node(node->left, input_value);
		}

		// node -> value < input_value, turn right
		if (compare_num(node->value, input_value) == 1 ){
			node -> right = node_add_node(node->right, input_value);

		}
		// the input_value has already contained in the tree, put it in
		// the right side.
		if (compare_num(node->value, input_value) == 0 ){
			node -> right = node_add_node(node->right, input_value);
		}

		return node;
	}
}

// A tree be added a node with value.
bst_tree_t *tree_add_node( bst_tree_t *tree, int input_value)
{
	tree -> root = node_add_node(tree->root, input_value);
	(tree -> count) ++;
	return tree;
}



// ==================left most==================
// To return the left most node from a node.
bst_node_t *node_left_most( bst_node_t *node)
{
	while( node != NULL){
		if (node -> left == NULL){
			return node;
		}else{
			node = node -> left;
		}
	}
}

// To return the left most node from a node.
bst_tree_t *tree_left_most(bst_tree_t *tree)
{
	bst_node_t *node = tree->root;
	return node_left_most(node);
}


// ==================remove node==================
// To remove the left most node.
void node_remove_left_most(bst_node_t *node)
{
	if (node != NULL){

		// when the node is the left most node, we remove and free it.
		if (node->left == NULL){
			free(node);

		// the node is not the left most node, so still to find it.
		}else {
			node -> left = node_remove_left_most(node->left);
		}
	}
}


// To remove a node that is with specific value from the hierarchy of a node.
bst_node_t *node_remove_node(bst_node_t *node, int input_value)
{
	if (node != NULL && is_node_contain_value(node, input_value) == 1 ) {

		if(compare_num(node->value, input_value) == 0){

			// the last/only node would be remove.
			if (node->right == NULL && node->left == NULL){
				free(node);
				return NULL;

			//
			}else if(node->right == NULL){
				temp = node->left;
				free(node);
				returm temp;
			}else{
				node->value = left_most(node->right) -> value;
				node_remove_left_most(node->right);
				return node;
			}

		// the input_value is less than node, turn to left child
		}else if (compare_num(node->value, input_value) == -1){
			node->left = node_remove_node(node->left, input_value);

		// the input_value is greater than node, turn to right child
		}else if (compare_num(node->value, input_value) == 1){
			node->right = node_remove_node(node->right,input_value);
		}

	} else{
		printf("node == NULL , or is_node_contain_value() != 1\n");
	}
	return node;
}

// To remove a node that is with specific value from a tree.
bst_tree_t *tree_remove_node(bst_tree_t *tree, int input_value)
{
	node_remove_node(tree->root, input_value);
	(tree->count)--;
	return tree;
}


// ==================operation==================
// To check the value is contained in a hierarchy of a node.
bst_node_t *is_node_contain_value(bst_node_t *node, int iuput_value)
{
	while(1){
		if ( compare_num(node -> value, iuput_value) == -1 ){
			if (node -> left != NULL){
				node = current -> left;
			}else{
				return 0;
			}
		}else if( compare_num(node -> value, iuput_value) == 1 ){
			if (node -> right != NULL){
				node = node -> right;
			}else{
				return 0;
			}
		}else if( compare_num(node -> value, iuput_value) == 0 ){
			return 1;
		}
	}
}

// To check a tree is contained a node with specific value.
bst_tree_t *is_tree_contain_value(bst_tree_t *tree, int iuput_value)
{
	bst_node_t *current;
	current = tree -> root;

	return is_node_contain_value(current, input_value);
}

// Compute the height of a tree, the number of nodes along the longest path
// from the root node down to the farthest leaf node.
int node_height(bst_node_t* node)
{
	if (node == NULL){
		return 0;
	}else{
		// compute the height of each subtree
		int lheight = tree_height(node->left);
		int rheight = tree_height(node->right);

		// use the larger one
		if (lheight > rheight){
			return(lheight+1);
		}else{
			return(rheight+1);
		}
	}
}


// ==================breadth first search==================
// Print nodes at a given level.
int print_given_level(bst_node_t* root, int level)
{
	// check node is exist or not
	if (root == NULL){
		return 0;
	}

	// find the children nodes in recursive way.
	if (level == 1){
		printf("%d ", root->value);
	}else if (level > 1){
		print_given_level(root->left, level-1);
		print_given_level(root->right, level-1);
	}
	return 1;
}

// To print level order traversal a tree
void print_breadth_first_search(bst_node_t* root)
{
	int h = tree_height(root);
	int i;
	for (i=1; i<=h; i++){
		print_given_level(root, i);
	}
	printf("\n");
}



// ==================depth first search==================

/* There are 3 different kinds of depth first traversals.
 *
 * 	pre-order: visit each node before visiting any of its children.
 *
 * 	in-order: visit each node after visiting its left child, but before
 * 		  visiting its right child.
 *
 * 	post-order: visit each node after visiting both of its children.
 *
 */

// The depth first search pre order.
void DFS_pre_order(bst_node_t *root)
{
	int ret = 0;

	if (root == NULL)
		return 0;

	if (root){
		ret = root->value;

		if (root->left)	{
			DFS_in_order(root->left);
		}

		if (root->right){
			DFS_in_order(root->right);
		}
	}
	return ret;
}

// The depth first search in order.
void DFS_in_order(bst_node_t *root)
{
	int ret = 0;

	if (root == NULL)
		return 0;

	if (root){
		if (root->left)	{
			DFS_in_order(root->left);
		}

		ret = root->value;

		if (root->right){
			DFS_in_order(root->right);
		}
	}
	return ret;
}

// The depth first search post order
int DFS_post_order(bst_node_t *root)
{
	int ret = 0;

	if (root == NULL)
		return 0;

	if (root){
		if (root->left)	{
			DFS_post_order(root->left);
		}
		if (root->right){
			DFS_post_order(root->right);
		}

		ret = root->value;
	}
	return ret;
}
