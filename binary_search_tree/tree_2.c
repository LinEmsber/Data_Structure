/* tree.c */

#include "tree.h"


// ======== typedef ========
typedef struct node node_t;
typedef struct tree tree_t;



// ======== compare siblings ========

/* compare two keys to determine the node to turn left or right.
 *
 * 	equal == 0
 * 	/	\
 * left == -1	right == 1
 *
 * @key_1: the value of key_1
 * @key_2: the value of key_2
 */
int compare_key(int key_1, int key_2)
{
	// turn left, return -1
	if(key_1 > key_2) {
		return -1;

	// turn right, return 1
	}else if(key_1 < key_2) {
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
void node_free(node_t *node)
{
        if (node != NULL){
                node_free(node -> left);
                node_free(node -> right);
                free(node);
	}
}


/* Initialize a node.
 *
 * @tree: the node want to initialize.
 */
node_t *node_init(node_t *node)
{
        node -> key = 0;
        node -> data = NULL;
        node -> left = NULL;
        node -> right = NULL;
        return node;
}

/* input a key into a node
 */
node_t *node_input_key(node_t *node, int key)
{
	node -> key = key;
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
		node_free(tree -> root);
		tree -> root = NULL;
		tree -> count = 0;
	}
}



// ======== search ========

/* search a node with a specific key from a tree in recurive method.
 *
 * @root: the tree we want to search
 * @taret_key: the specific key
 */
node_t *search_recurively(node_t *root, int target_key)
{
        if (root == NULL){

                return NULL;

        }else if(target_key == root -> key){

                return root;

        }else{
                if (target_key > root->key){
			search_recurively(root->right, target_key);

		}else if(target_key < root->key){
			search_recurively(root->left, target_key);

		}
        }

	return NULL;
}

/* search a node with a specific key from a tree in iterative method.
 *
 * @root: the tree we want to search
 * @taret_key: the specific key
 */
node_t *search_iteratively(node_t *root, int target_key)
{
        node_t *current = root;

        while ( current != NULL){

                if (target_key == root -> key){
                        return current;
                        break;

                }else if (target_key > root->key){
                        search_iteratively(root->right, target_key);

                }else if(target_key < root->key){
                        search_iteratively(root->left, target_key);


                }
        }

	return NULL;
}

// ======== insert node ========

/* insert a node into a node
 *
 * @node: the node to be inserted node
 * @key: the key of inserted node
 */
node_t *node_insert_node( node_t *node, int key)
{
	if (node == NULL){
		node_t *node = node_create();
		node_init(node);
		node_input_key(node, key);
		return node;

	}else{
                int compare_ret = compare_key(node->key, key);

		// If node -> key > input_key, turn left.
		if (compare_ret == -1 ){
			node -> left = node_insert_node(node->left, key);

		// If node -> key < input_key, turn right.
                // It the input_key has already contained in the tree, and put it in the right side.
                }else if (compare_ret == 1 || compare_ret == 0){
			node -> right = node_insert_node(node->right, key);

                }
		return node;
	}
}

/* insert a node into a tree
 *
 * @tree: the tree to be inserted node
 * @key: the key of inserted node
 */
tree_t *tree_insert_node( tree_t *tree, int key)
{
	tree -> root = node_insert_node(tree->root, key);
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

// ======== remove node ========
void node_swap(node_t *node_1, node_t *node_2)
{
	if (node_1 != NULL && node_2 != NULL){
		node_t *tmp;

		tmp = node_1;
		node_1 = node_2;
		node_2 = tmp;
	}
}


def replace_node_in_parent(self, new_value=None):
    if self.parent:
        if self == self.parent.left_child:
            self.parent.left_child = new_value
        else:
            self.parent.right_child = new_value
    if new_value:
        new_value.parent = self.parent

// ======== remove node ========


def binary_tree_delete(self, key):
    if key < self.key:
        self.left_child.binary_tree_delete(key)
    elif key > self.key:
        self.right_child.binary_tree_delete(key)
    else: # delete the key here
        if self.left_child and self.right_child: # if both children are present
            successor = self.right_child.find_min()
            self.key = successor.key
            successor.binary_tree_delete(successor.key)
        elif self.left_child:   # if the node has only a *left* child
            self.replace_node_in_parent(self.left_child)
        elif self.right_child:  # if the node has only a *right* child
            self.replace_node_in_parent(self.right_child)
        else: # this node has no children
            self.replace_node_in_parent(None)
