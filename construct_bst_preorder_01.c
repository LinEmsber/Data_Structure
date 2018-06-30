/* A O(n) program for construction of BST from preorder traversal */

#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node * left;
	struct node * right;
};

struct node * new_node (int data)
{
	struct node * temp = (struct node *) malloc( sizeof(struct node) );

	temp->data = data;
	temp->left = temp->right = NULL;

	return temp;
}

/* A recursive helper function to construct binary search tree in preorder. */
struct node * construct_bst_preorder_helper (int array[], int * array_index, int low, int high, int size)
{
	if (*array_index >= size || low > high)
		return NULL;

	struct node * root = new_node ( array[*array_index] );
	*array_index = *array_index + 1;

	if (low == high)
		return root;

	/* Search for the first element which is greater than root. */
	int i;
	for ( i = low; i <= high; ++i )
		if ( array[i] > root->data )
			break;

	root->left = construct_bst_preorder_helper ( array, array_index, *array_index, i - 1, size );
	root->right = construct_bst_preorder_helper ( array, array_index, i, high, size );

	return root;
}

/* Convert an integer array into binary search tree in arrayorder traversal. */
struct node * construct_bst_preorder (int array[], int size)
{
	int array_index = 0;
	return construct_bst_preorder_helper (array, &array_index, 0, size - 1, size);
}

void print_inorder (struct node * node)
{
	if (node == NULL)
		return;
	print_inorder(node->left);
	printf("%d ", node->data);
	print_inorder(node->right);
}

int main ()
{
	int int_arr[] = {1000, 10, 5, 1, 400, 7, 50, 40, 100, 300};
	int size = sizeof( int_arr ) / sizeof( int_arr[0] );

	struct node * root = construct_bst_preorder(int_arr, size);

	printf("Inorder traversal of the constructed tree: \n");
	print_inorder(root);
	printf("\n");

	return 0;
}
