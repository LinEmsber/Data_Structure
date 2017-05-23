/* tree.c */

#include "tree.h"


/* compare siblings */

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


/* node */

/* Allocate a memory for a node.
*/
node_t * node_create()
{
	node_t * node = (node_t *) malloc ( sizeof(node_t) );
	return node;
}


/* Remove a node, including children of node.
 *
 * @tree: the node want to remove.
 */
void node_remove(node_t * node)
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
node_t * node_init(node_t * node)
{
	node -> value = 0;
	node -> data = NULL;
	node -> left = NULL;
	node -> right = NULL;
	return node;
}

/* input a value into a node
*/
node_t * node_input_value(node_t * node, int value)
{
	node -> value = value;
	return node;
}

/* input a data into a node.
*/
node_t * node_input_data(node_t * node, void *input_data)
{
	node -> data = input_data;
	return node;
}


/* tree */

/* Allocate a memory for a tree.
*/
tree_t *tree_create()
{
	tree_t *tree = (tree_t *) malloc ( sizeof(tree_t) );
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


/* search */

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

/* insert node */

/* insert a node into a node
 *
 * @node: the node to be inserted node
 * @value: the value of inserted node
 */
node_t * node_insert_node( node_t * node, int value)
{
	if (node == NULL){
		node_t * new_node = node_create();
		node_init(new_node);
		node_input_value(node, value);
		return new_node;

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


/* min */

/* Return the minimum node from a node in iterative method.
 *
 * @node: the root node for searching.
 */
node_t * node_min( node_t * node)
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
node_t * node_min_2(node_t * node)
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


/* max */

/* Return the maximun node from a node in iterative method.
 *
 * @node: the root node for searching.
 */
node_t * node_max( node_t * node)
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
node_t * node_max_2(node_t * node)
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

/* node swap */
void node_swap(node_t * node_1, node_t * node_2)
{
	if (node_1 != NULL && node_2 != NULL){
		node_t *tmp;

		tmp = node_1;
		node_1 = node_2;
		node_2 = tmp;
	}
}


/* find parent node */
/* search the parent of the specific node from the root of tree.
 *
 * @root: the root of the tree which we want to search.
 * @target_node: the node which we want to find it parent node.
 */
node_t * node_find_parent(node_t * node, node_t * target_node)
{
	if(node == target_node){
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
					return node;
				node = node -> left;
			}

			// trun right to search
		}else{

			if(node -> right != NULL) {
				if(node -> right -> value == target_node -> value)
					return node;
				node = node -> right;
			}
		}
	}

	// We do not find it.
	return NULL;
}

// node remove node

node_t * node_remove_node(node_t * root, int value)
{
	if (root == NULL)
		return root;

	/* If the value to be deleted is smaller than the root's value. */
	if (value < root->value) {
		root->left = node_remove_node(root->left, value);
	}

	/* If the value to be deleted is greater than the root's value. */
	else if (value > root->value){
		root->right = node_remove_node(root->right, value);
	}

	/* if value is same as root's value. */
	else {
		// node with only one child or no child
		if (root->left == NULL) {
			node_t * temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			node_t * temp = root->left;
			free(root);
			return temp;
		}

		/* If the node with two children, then get the inorder successor
		 * (e.g. the smallest node in the right subtree).
		 */
		node_t * temp = node_min(root->right);

		/* Copy the inorder successor's content to this node. */
		root->value = temp->value;

		/* delete the inorder successor. */
		root->right = node_remove_node(root->right, temp->value);
	}

	return root;
}

// To remove a node that is with specific value from a tree.
int *tree_remove_node(tree_t *tree, int input_value)
{
	node_remove_node(tree->root, input_value);
	(tree->count)--;
	return tree;
}

// To remove the left most node.
void node_remove_left_most(node_t * node)
{
	if (node != NULL){

		// when the node is the left most node, we remove and free it.
		if (node->left == NULL){
			free(node);

		// the node is not the left most node, so still to find it.
		}else {
			node_remove_left_most(node->left);
		}
	}
}

/* operation */

// To check the value is contained in a hierarchy of a node.
node_t * is_node_contain_value(node_t * _node, int _value)
{
	int value = _value;
	node_t * current = _node;

	while(1){
		if ( compare_num(current -> value, _value) == -1 ){
			if (current -> left != NULL){
				current = current -> left;
			}else{
				return 0;
			}
		}else if( compare_num(current -> value, _value) == 1 ){
			if (current -> right != NULL){
				current = current -> right;
			}else{
				return 0;
			}
		}else if( compare_num(current -> value, _value) == 0 ){
			return 1;
		}
	}
}

// To check a tree is contained a node with specific value.
tree_t * is_tree_contain_value(tree_t * tree, int _value)
{
	int value = _value;
	node_t * current = tree -> root;

	return is_node_contain_value(current, value);
}

// Compute the level(height) of a tree, the number of nodes along the longest path
// from the root node down to the farthest leaf node.
int node_level(node_t * node)
{
	if (node == NULL){
		return 0;
	}else{
		// compute the height of each subtree
		int lheight = node_level(node->left);
		int rheight = node_level(node->right);

		// use the larger one
		if (lheight > rheight){
			return lheight + 1;
		}else{
			return rheight + 1;
		}
	}
}

/* breadth first search */

// Print nodes at a given level.
int print_given_level(node_t * root, int level)
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
void print_breadth_first_search(node_t * root)
{
	int h = tree_height(root);
	int i;
	for (i=1; i<=h; i++){
		print_given_level(root, i);
	}
	printf("\n");
}



/* depth first search */

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
