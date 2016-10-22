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


// ======== left most ========

// Return the left most node from a node.
node_t *node_left_most( node_t *node)
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

// Return the left most node from a node.
node_t *tree_left_most(tree_t *tree)
{
	return node_left_most(tree -> root);
}


// ======== right most ========

// Return the right most node from a node.
node_t *node_right_most( node_t *node)
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

// Return the right most node from a node.
node_t *tree_right_most(tree_t *tree)
{
	return node_left_most(tree -> root);
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
node_t* node_find_parent(node_t *root, node_t *target_node)
{
	if(root == target_node){
	    return NULL;
	}

	// start searching from the root
	while(root != NULL){

		// trun left to search
		if(root -> value > target_node -> value) {

			// If the value of left child is equal the value of target node, we find the
			// node's parent.
			// If the left child is NULL, the while loop would not continue, and
			// return NULL outside this loop.
			if(root -> left != NULL) {
				if(root -> left -> value == target_node -> value)
					return root;
				root = root -> left;
			}

		// trun right to search
		}else{

			if(root -> right != NULL) {
				if(root -> right -> value == target_node -> value)
					return root;
				root = root -> right;
			}
		}
	}
	return NULL;
}


// def replace_node_in_parent(self, new_value=None):
//     if self.parent:
//         if self == self.parent.left_child:
//             self.parent.left_child = new_value
//         else:
//             self.parent.right_child = new_value
//     if new_value:
//         new_value.parent = self.parent











// ======== remove node ========

void *node_remove_node(tree_t *tree, int value)
{
	if (tree != NULL)
		return NULL

	node_t *target_node = search_recurively(tree, value);
	node_t *target_node_parent = node_find_parent(tree, target_node);

	// node with both children
	if (target_node -> left != NULL && target_node -> right != NULL){

	}else if (target_node -> left != NULL){

	}else{

	}
}


void delete(tree **root, int value) {
	// Nothing to do if empty tree
	if (*root == NULL) {
		return;
	}

	tree *parent = *root,
		 *current = *root;

	while (current != NULL) {
		// value was found on a node
		if (value == current->value) {

			// delete a leaf node OR an empty tree
			if (current->left == NULL && current->right == NULL) {
				if (current == *root) {
					free(*root);
					*root = NULL;
				} else {
					if (current->value < parent->value) {
						parent->left = NULL;
					} else {
						parent->right = NULL;
					}
					free(current);
				}
			}

			// delete a single-child node
			else if (current->left == NULL || current->right == NULL) {
				// current is the left child of parent
				if (current->value < parent->value) {
					// If current only has right child
					if (current->left == NULL) {
						// parent left child is replaced by current right child.
						parent->left = current->right;
						current->right->parent = parent;
					} else {
						parent->left = current->left;
						current->left->parent = parent;
					}
				// current is the right child of parent
				} else {
					if (current->left == NULL) {
						parent->right = current->right;
						current->right->parent = parent;
					} else {
						parent->right = current->left;
						current->left->parent = parent;
					}
				}
				free(current);
			}

			// delete a double-child node, (ROOT that has two child cannot be deleted)
			else {
				if (current == *root) {
					printf("Sorry, cannot delete root node that has both left and right child!\n");
				} else {
					// the min item of right child, or the most left child of right child
					tree *submin = min(current->right);

					// make a clone of min in right subtree
					tree *clone = malloc(sizeof(tree));

					clone->value = submin->value;
					clone->parent = parent;
					clone->left = current->left;

					if (submin == current->right) {
						clone->right = NULL;
					} else {
						clone->right = current->right;
					}

					// assign clone to parent left/right
					if (current->value < parent->value) {
						parent->left = clone;
					} else {
						parent->right = clone;
					}

					// update parent of the lifted node
					if (submin->value < submin->parent->value) {
						submin->parent->left = NULL;
					} else {
						submin->parent->right = NULL;
					}

					// free min AND current
					free(current);
					free(submin);
				}
			}

			return;

		// continue search for value
		} else {
			parent = current;
			if (value < current->value) {
				current = current->left;
			} else {
				current	= current->right;
			}
		}
	}

	printf("%d is not found in tree\n", value);

}


// To remove a node that is with specific value from the hierarchy of a node.
int node_delete_node(node_t* root, int value)
{
	// find the target node first
	node_t *target_node = search(root, value);
	if(target_node == NULL){
		return 0;
	}

	// If the target node without any child.
	if(target_node -> left == NULL && find -> right == NULL) {

		if(target_node == root){
			free(target_node );
		} else {

			// If the target node is the left child
			if( target_node -> parent -> left == target_node)
				parent->left=NULL;

			// If the target node is the right child
			if( target_node -> parent -> right == target_node)
				parent->right=NULL;

			free(target_node );
		}

	// If the target node has left child
	} else if(target_node -> left != NULL && target_node -> right == NULL) {

		node_t *save = target_node ->left;
		target_node -> value = target_node -> left-> value;
		target_node -> right = target_node -> left-> right;
		target_node -> left = target_node -> left-> left;
		free(save);

	// If the target node has right child
	} else if(target_node -> right != NULL && target_node -> left == NULL) {

		node_t * save = target_node->right;
		target_node -> value = target_node -> right -> value;
		target_node -> left = target_node -> right -> left;
		target_node -> right = target_node -> right -> right;
		free(save);

	} else {
		node_t *heir = successor(target_node);
		int value=heir->value;
		if(delete(root,value))
			target_node->value=value;
	}

	return 1;
}











def binary_tree_delete(self, value):
    if value < self.value:
        self.left_child.binary_tree_delete(value)
    elif value > self.value:
        self.right_child.binary_tree_delete(value)
    else: # delete the value here
        if self.left_child and self.right_child: # if both children are present
            successor = self.right_child.find_min()
            self.value = successor.value
            successor.binary_tree_delete(successor.value)
        elif self.left_child:   # if the node has only a *left* child
            self.replace_node_in_parent(self.left_child)
        elif self.right_child:  # if the node has only a *right* child
            self.replace_node_in_parent(self.right_child)
        else: # this node has no children
            self.replace_node_in_parent(None)



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


// To remove a node that is with specific value from a tree.
tree_t *tree_remove_node(tree_t *tree, int input_value)
{
	node_remove_node(tree->root, input_value);
	(tree->count)--;
	return tree;
}


// ==================operation==================
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
