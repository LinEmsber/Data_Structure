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
		if(root -> key > target_node -> key) {

			// If the key of left child is equal the key of target node, we find the
			// node's parent.
			// If the left child is NULL, the while loop would not continue, and
			// return NULL outside this loop.
			if(root -> left != NULL) {
				if(root -> left -> key == target_node -> key)
					return root;
				root = root -> left;
			}

		// trun right to search
		}else{

			if(root -> right != NULL) {
				if(root -> right -> key == target_node -> key)
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

void *node_remove_node(tree_t *tree, int key)
{
	if (tree != NULL)
		return NULL

	node_t *target_node = search_recurively(tree, key);
	node_t *target_node_parent = node_find_parent(tree, target_node);

	// node with both children
	if (target_node -> left != NULL && target_node -> right != NULL){

	}else if (target_node -> left != NULL){

	}else{

	}
}


int delete(node_t** root,int key)
{
	node_t *find=search(*root,key);
	if(find==NULL){
		return 0;
	}

	if(find->left==NULL&&find->right==NULL)
	{
		if(find==*root)
			free(find);
		else
		{
			node_t *parent=findparent(*root,find);
			if(parent->left!=NULL)
				if(parent->left==find)
					parent->left=NULL;
			if(parent->right!=NULL)
				if(parent->right==find)
					parent->right=NULL;
			free(find);
		}
	}
	else if(find->left!=NULL&&find->right==NULL)
	{
		node_t* save=find->left;
		find->val=find->left->val;
		find->right=find->left->right;
		find->left=find->left->left;
		free(save);
	}
	else if(find->right!=NULL&&find->left==NULL)
	{
		node_t* save=find->right;
		find->val=find->right->val;
		find->left=find->right->left;
		find->right=find->right->right;
		free(save);
	}
	else
	{
		node_t* heir=successor(find);
		int key=heir->val;
		if(delete(root,key))
			find->val=key;
	}

	return 1;
}











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


// To remove a node that is with specific value from the hierarchy of a node.
node_t *node_remove_node(node_t *node, int input_value)
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
