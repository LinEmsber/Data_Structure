/* tree.c */

#include "tree.h"


// ======== typedef ========
typedef struct node node_t;
typedef struct tree tree_t;



// ======== compare siblings ========

/* compare two values to determine the node to turn left or right.
 *
 * 	equal == 0
 * 	/	\
 * left == -1	right == 1
 *
 * @value_1: the value of value_1
 * @value_2: the value of value_2
 */
int compare_value(int value_1, int value_2)
{
	// turn left, return -1
	if(value_1 > value_2) {
		return -1;

		// turn right, return 1
	}else if(value_1 < value_2) {
		return 1;

		// equal, return 1
	}else {
		return 0;
	}
}


// ======== node ========

/* Allocate a memory for a node.
 */
node_t *node_create()
{
	node_t *node = (node_t *) malloc ( sizeof(node_t) );
	return node;
}


/* Remove a node, including children of node.
 *
 * @tree: the node want to remove.
 */
void node_remove(node_t *node)
{
	if (node != NULL){
		node_remove(node -> left);
		node_remove(node -> right);
		free(node);
	}
}


/* Initialize a node.
 *
 * @tree: the node want to initialize.
 */
node_t *node_init(node_t *node)
{
	node -> value = 0;
	node -> data = NULL;
	node -> left = NULL;
	node -> right = NULL;
	return node;
}

/* input a value into a node
 */
node_t *node_input_value(node_t *node, int value)
{
	node -> value = value;
	return node;
}

/* input a data into a node.
 */
node_t *node_input_data(node_t *node, void *input_data)
{
	node -> data = input_data;
	return node;
}


// ======== tree ========

/* Allocate a memory for a tree.
 */
tree_t *tree_create()
{
	tree_t *tree = (tree_t*) malloc ( sizeof(tree_t) );
	return tree;
}


/* Initialize a tree.
 *
 * @tree: the tree want to initialize.
 */
void tree_init( tree_t *tree)
{
	tree -> root = NULL;
	tree -> count = 0;
}


/* Remove a tree.
 *
 * @tree: the tree want to remove.
 */
void tree_remove(tree_t *tree)
{
	if ( tree != NULL && tree->root != NULL ){
		node_remove(tree -> root);
		tree -> root = NULL;
		tree -> count = 0;
	}
}

/* Return the count of the tree.
 *
 * @tree: the tree we want to count node.
 */
int tree_count(tree_t *tree)
{
	return tree -> count;
}


// ======== search ========

/* search a node with a specific value from a tree in recurive method.
 *
 * @root: the tree we want to search
 * @taret_value: the specific value
 */
node_t *search_recurively(node_t *root, int target_value)
{
	if (root == NULL){

		return NULL;

	}else if(target_value == root -> value){

		return root;

	}else{
		if (target_value > root->value){
			search_recurively(root->right, target_value);

		}else if(target_value < root->value){
			search_recurively(root->left, target_value);

		}
	}

	return NULL;
}

/* search a node with a specific value from a tree in iterative method.
 *
 * @root: the tree we want to search
 * @taret_value: the specific value
 */
node_t *search_iteratively(node_t *root, int target_value)
{
	node_t *current = root;

	while ( current != NULL){

		if (target_value == root -> value){
			return current;
			break;

		}else if (target_value > root->value){
			search_iteratively(root->right, target_value);

		}else if(target_value < root->value){
			search_iteratively(root->left, target_value);


		}
	}

	return NULL;
}

// ======== insert node ========

/* insert a node into a node
 *
 * @node: the node to be inserted node
 * @value: the value of inserted node
 */
node_t *node_insert_node( node_t *node, int value)
{
	if (node == NULL){
		node_t *node = node_create();
		node_init(node);
		node_input_value(node, value);
		return node;

	}else{
		int compare_ret = compare_value(node->value, value);

		// If node -> value > input_value, turn left.
		if (compare_ret == -1 ){
			node -> left = node_insert_node(node->left, value);

			// If node -> value < input_value, turn right.
			// It the input_value has already contained in the tree, and put it in the right side.
		}else if (compare_ret == 1 || compare_ret == 0){
			node -> right = node_insert_node(node->right, value);

		}
		return node;
	}
}

/* insert a node into a tree
 *
 * @tree: the tree to be inserted node
 * @value: the value of inserted node
 */
tree_t *tree_insert_node( tree_t *tree, int value)
{
	tree -> root = node_insert_node(tree->root, value);
	(tree -> count) ++;

	return tree;
}


// ======== min ========

/* Return the minimum node from a node in iterative method.
 *
 * @node: the root node for searching.
 */
node_t *node_min( node_t *node)
{
	if (node == NULL)
		return NULL;

	node_t *target_node = NULL;

	while( node != NULL){
		if (node -> left == NULL){
			target_node = node;
		}else{
			node = node -> left;
		}
	}

	return target_node;
}

/* Return the minimum node from a node in recursive method.
 *
 * @node: the root node for searching.
 */
node_t *node_min_2(node_t* node)
{
	if(node == NULL)
		return NULL;

	if (node->left == NULL)
		return node;
	else
		return node_min_2(node->left);
}

/* Return the minimum node from a tree in recursive method.
 *
 * @node: the tree for searching.
 */
node_t *tree_min(tree_t *tree)
{
	return node_min_2(tree -> root);
}


// ======== max ========

/* Return the maximun node from a node in iterative method.
 *
 * @node: the root node for searching.
 */
node_t *node_max( node_t *node)
{
	if (node == NULL)
		return NULL;

	node_t *target_node = NULL;

	while( node != NULL){
		if (node -> right == NULL){
			target_node = node;
		}else{
			node = node -> right;
		}
	}

	return target_node;
}

/* Return the minimum node from a node in recursive method.
 *
 * @node: the root node for searching.
 */
node_t * node_max_2(node_t* node)
{
	if(node == NULL)
		return NULL;

	if (node->right == NULL)
		return node;
	else
		return node_max_2(node->right);
}

/* Return the minimum node from a node in recursive method.
 *
 * @node: the root node for searching.
 */
node_t *tree_max(tree_t *tree)
{
	return node_max_2(tree -> root);
}

// ======== node swap ========
void node_swap(node_t *node_1, node_t *node_2)
{
	if (node_1 != NULL && node_2 != NULL){
		node_t *tmp;

		tmp = node_1;
		node_1 = node_2;
		node_2 = tmp;
	}
}


// ======== find parent node ========
/* search the parent of the specific node from the root of tree.
 *
 * @root: the root of the tree which we want to search.
 * @target_node: the node which we want to find it parent node.
 */
node_t* node_find_parent(node_t *node, node_t *target_node)
{
	if(root == target_node){
		return NULL;
	}

	// start searching from the root
	while(node != NULL){

		// trun left to search
		if(node -> value > target_node -> value) {

			// If the value of left child is equal the value of target node, we find the
			// node's parent.
			// If the left child is NULL, the while loop would not continue, and
			// return NULL outside this loop.
			if(node -> left != NULL) {
				if(node -> left -> value == target_node -> value)
					return root;
				node = node -> left;
			}

			// trun right to search
		}else{

			if(node -> right != NULL) {
				if(node -> right -> value == target_node -> value)
					return root;
				node = node -> right;
			}
		}
	}

	// We do not find it.
	return NULL;
}


// ======== find successor ========
// There are two cases here:
//
// 1. The node has a right subtree.
// If the given node has a right subtree then by the BST property the next larger key must be in the right subtree. Since all keys in a right subtree are larger than the key of the given node, the successor must be the smallest of all those keys in the right subtree.
//
// 2. The node does not have a right subtree.
// In this case we will have to look up the tree since that's the only place we might find the next larger key. There is no point looking at the left subtree as all keys in the left subtree are guaranteed to be smaller than the key in the given tree.

/* Find the node's successor
 *
 * @node: the successor of node which we want find
 */
node_t *node_successor(node_t * node)
{
	if( node != NULL )
		node = node -> right;

	while(node != NULL){

		if(node -> left == NULL)
			return node;
		else
			node = node -> left;
	}
	return node;
}


// ======== remove node ========


/* remove a node with specific value from a hierarchy of node
 *
 * @node: the hierarchy of node
 * @value: the specific value of node
 *
 * On success, 0 is returned. On error, -1 is returned.
 */
int node_remove_node(node_t *node, int value)
{
	node_t * target_node = search_recurively(*node, value);

	if(target_node == NULL){
		return 1;

	} else {
		// The target node without any child
		if(target_node -> left == NULL && target_node -> right == NULL)	{

			// If the target node is the first node
			if(target_node == *node){
				free(target_node);

			}else{
				// Find the parent
				node_t *parent = node_find_parent(target_node);

				// If the target node is the left child
				if( parent -> left == target_node)
					parent -> left = NULL;

				// If the target node is the right child
				if( parent -> right == target_node)
					parent -> right = NULL;

				free(target_node );
			}

		// If the target node only has left child
		} else if(target_node -> left != NULL && target_node -> right == NULL) {

			node_t *tmp = target_node;
			target_node = target_node -> left;
			free(tmp);

		// If the target node only has right child
		} else if(target_node -> right != NULL && target_node -> left == NULL) {

			node_t *tmp = target_node;
			target_node = target_node -> right;
			free(tmp);

		// The target node has two children
		}else{
			node_t *heir = node_successor(target_node);
			int value = heir -> value;
			if(node_remove_node(target_node, value))
				target_node -> value = value;
		}
	}
	return 0;
}

/* grab a node which would be removed with specific value from a hierarchy of node
 *
 * @node: the root of node
 * @value: the specific value of node
 *
 * On success, the target node is returned. On error, NULL is returned.
 */
node_t *node_remove_node_2(node_t *target_node, int value)
{
	node_t *tmp;

	if (target_node == NULL){
		return target_node;

	}else if (value < target_node->value){
		target_node->left = node_remove_node_2(target_node->left, value);

	}else if (value > target_node->value){
		target_node->right = node_remove_node_2(target_node->left, value);

	// two children
	}else if (target_node->left != NULL && target_node->right != NULL){
		tmp = node_min_2(target_node->right);
		target_node->value = tmp->value;
		target_node->right = node_remove_node_2(target_node->right,target_node->value);

	// zero or one child
	}else{
		tmp = target_node;
		if(target_node->left == NULL){
			target_node=target_node->right;

		} else if(target_node->right == NULL){
			target_node=target_node->left;

		}
		free(tmp);
	}
	return target_node;

}


// To remove a node that is with specific value from a tree.
int *tree_remove_node(tree_t *tree, int input_value)
{
	node_remove_node(tree->root, input_value);
	(tree->count)--;
	return tree;
}

// To remove the left most node.
void node_remove_left_most(node_t *node)
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

// ================== operation ==================
// To check the value is contained in a hierarchy of a node.
node_t *is_node_contain_value(node_t *node, int iuput_value)
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
tree_t *is_tree_contain_value(tree_t *tree, int iuput_value)
{
	node_t *current;
	current = tree -> root;

	return is_node_contain_value(current, input_value);
}

// Compute the height of a tree, the number of nodes along the longest path
// from the root node down to the farthest leaf node.
int node_height(node_t* node)
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
int print_given_level(node_t* root, int level)
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
void print_breadth_first_search(node_t* root)
{
	int h = tree_height(root);
	int i;
	for (i=1; i<=h; i++){
		print_given_level(root, i);
	}
	printf("\n");
}



// ================== depth first search ==================

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
void DFS_pre_order(node_t *root)
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
void DFS_in_order(node_t *root)
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
int DFS_post_order(node_t *root)
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
