#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;
struct node {
	int value;
	void * data;
	struct node * left;
	struct node * right;
};


/* Compare siblings */
int compare_value(int value_1, int value_2)
{
	/* Turn left. */
	if(value_1 > value_2) {
		return -1;
	}

	/* Turn right. */
	else if(value_1 < value_2) {
		return 1;
	}

	/* Equal. */
	else {
		return 0;
	}
}

/* Allocate and initialize a node. */
node_t * bst_create(int _value, void * _data)
{
	node_t * node = (node_t *) malloc ( sizeof(node_t) );
	node -> value = _value;
	node -> data = _data;
	node -> left = NULL;
	node -> right = NULL;

	return node;
}

/* Insert node. */
node_t * bst_insert(node_t * _root, node_t * _node)
{
	if (_node == NULL)
		return NULL;

	if (_root == NULL)
		return _node;

	int compare_ret = compare_value(_root->value, _node->value);

	/* According to the compare_ret to determine to add to left or right. */
	if (compare_ret == -1 ){
		_root->left = bst_insert(_root->left, _node);
	}
	else if (compare_ret == 1 || compare_ret == 0){
		_root->right = bst_insert(_root->right, _node);
	}

        return _root;
}


node_t * bst_min(node_t * node)
{
	if(node == NULL)
		return NULL;

	if (node->left == NULL)
		return node;
	else
		return bst_min(node->left);
}

/* Node remove node.
 *
 * If we find the target node. There are three case:
 * 1. Node to be deleted is leaf: Simply remove it from the tree.
 * 2. Node to be deleted has only one child: Copy the child to the node and delete the child.
 * 3. Node to be deleted has two children:
 *  a. Find the smallest node of the right subtree.
 *  b. Copy the bst_inorder successor's content to this node.
 *  c. Delete the bst_inorder successor. It must be the smallest node of the right subtree.
 */
node_t * bst_remove(node_t * root, int _value)
{
	if (root == NULL)
		return root;

        /* Search recurively. */
	if (_value < root->value) {
		root->left = bst_remove(root->left, _value);
	}

	else if (_value > root->value){
		root->right = bst_remove(root->right, _value);
	}

	else if (_value == root->value){

		/* The node with only one child or no child. */
		if (root->left == NULL) {
			node_t * tmp = root->right;
			free(root);
			return tmp;
		}
		else if (root->right == NULL) {
			node_t * tmp = root->left;
			free(root);
			return tmp;
		}

                /* Node to be deleted has two children. */
                node_t * tmp = bst_min(root->right);

		root->value = tmp->value;
                root->data = tmp->data;

		root->right = bst_remove(root->right, tmp->value);
	}

	return root;
}

node_t * bst_max(node_t * node)
{
	if(node == NULL)
		return NULL;

	if (node->right == NULL)
		return node;
	else
		return bst_max(node->right);
}

int is_bst(node_t * _root)
{
        if (_root == NULL)
                return 1;

        if (_root->left != NULL && bst_max(_root->left)->value > _root->value)
                return 0;

        if (_root->right != NULL && bst_min(_root->right)->value < _root->value)
                return 0;

        if (!is_bst(_root->left) || !is_bst(_root->right))
                return 0;

        return 1;
}

/* Print bst_inorder. */
void bst_inorder(node_t * _root)
{
	if (_root != NULL)
	{
		bst_inorder(_root->left);
		printf("%d \t", _root->value);
		bst_inorder(_root->right);
	}
}


int main()
{
	node_t * root = bst_create(50, NULL);

	node_t * n_1 =  bst_create(30, NULL);
	node_t * n_2 =  bst_create(70, NULL);
	node_t * n_3 =  bst_create(10, NULL);
	node_t * n_4 =  bst_create(40, NULL);
	node_t * n_5 =  bst_create(80, NULL);
	node_t * n_6 =  bst_create(60, NULL);
        node_t * n_7 =  bst_create(65, NULL);
        node_t * n_8 =  bst_create(15, NULL);
        node_t * n_9 =  bst_create(25, NULL);
        node_t * n_10 =  bst_create(5, NULL);
        node_t * n_11 =  bst_create(85, NULL);
        node_t * n_12 =  bst_create(45, NULL);
        node_t * n_13 =  bst_create(55, NULL);
        node_t * n_14 =  bst_create(75, NULL);

	bst_insert(root, n_1);
	bst_insert(root, n_2);
	bst_insert(root, n_3);
	bst_insert(root, n_4);
	bst_insert(root, n_5);
	bst_insert(root, n_6);
        bst_insert(root, n_7);
        bst_insert(root, n_8);
        bst_insert(root, n_9);
        bst_insert(root, n_10);
        bst_insert(root, n_11);
        bst_insert(root, n_12);
        bst_insert(root, n_13);
        bst_insert(root, n_14);

        /*                       50
         *                 /          \
         *              30              70
         *          /       \         /       \
         *        10        40      60        80
         *       /  \      /  \   /    \     /   \
         *      5    15  25   45  55   65  75     85
         */
        /* bst_inorder: 10 30 40 50 60 70 80 */
        bst_inorder(root);
        printf("\n");

        bst_remove(root, 70);
        bst_inorder(root);
        printf("\n");

	return 0;
}
