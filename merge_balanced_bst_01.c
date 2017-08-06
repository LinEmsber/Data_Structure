/* Merge two balanced binary serach trees.
 *
 * References:
 * http://www.geeksforgeeks.org/archives/17138
 * http://www.geeksforgeeks.org/merge-two-balanced-binary-search-trees/
 */

#include <stdio.h>
#include <stdlib.h>

/* Structure. */
struct bst_node {
	int key;
	void * data;
	struct bst_node* left;
	struct bst_node* right;
};

/* Funciton declaration. */
int * merge_array(int arr_1[], int arr_2[], int arr_1_len, int arr_2_len);
void store_inorder(struct bst_node * node, int inorder[], int * index_ptr);
struct bst_node * sorted_array_to_bst(int arr[], int start, int end);


/* Function. */

/* Create a node of a binary search tree. */
struct bst_node * bst_create(int key)
{
	struct bst_node * node = (struct bst_node *) malloc( sizeof(struct bst_node) );
	node->key = key;
	node->data = NULL;
	node->left = NULL;
	node->right = NULL;

	return node;
}

/* Merge two balanced bst with their roots and their sizes of the nodes. */
struct bst_node * merge_balanced_bst(struct bst_node * root_1, int arr_1_len, struct bst_node * root_2, int arr_2_len)
{
	int i = 0, j = 0;
	int * arr_1 = (int *) malloc( sizeof(int) * arr_1_len );
	int * arr_2 = (int *) malloc( sizeof(int) * arr_2_len );
	int * merged_array;

	/* Store inorder traversal of first tree in an array arr_1[] */
	store_inorder(root_1, arr_1, &i);
	/* Store inorder traversal of second tree in another array arr_2[] */
	store_inorder(root_2, arr_2, &j);

	/* Merge two arrays. */
	merged_array = merge_array(arr_1, arr_2, arr_1_len, arr_2_len);

	/* Convert the sorted array to a bst and return it. */
	return sorted_array_to_bst (merged_array, 0, arr_1_len + arr_2_len - 1);
}


/* Print the keys of an bst in order. */
void print_key_inorder(struct bst_node* node)
{
	if (node == NULL)
		return;

	print_key_inorder(node->left);
	printf("%d ", node->key);
	print_key_inorder(node->right);
}

int * merge_array(int arr_1[], int arr_2[], int arr_1_len, int arr_2_len)
{
	int i = 0, j = 0, k = 0;
	int * merged_array = (int *) malloc( sizeof(int) * (arr_1_len + arr_2_len) );

	while (i < arr_1_len && j < arr_2_len) {

		// Pick the smaler element and put it in merged_array
		if (arr_1[i] < arr_2[j]) {
			merged_array[k] = arr_1[i];
			i++;
		} else {
			merged_array[k] = arr_2[j];
			j++;
		}
		k++;
	}

	/* Store the remaining elements of the first array into merged_array. */
	while (i < arr_1_len) {
		merged_array[k] = arr_1[i];
		i++;
		k++;
	}

	/* Store the remaining elements of the second array into merged_array. */
	while (j < arr_2_len) {
		merged_array[k] = arr_2[j];
		j++;
		k++;
	}

	return merged_array;
}

/* Stores inorder traversal of a tree rooted with node. */
void store_inorder(struct bst_node * node, int inorder[], int * index_ptr)
{
	if (node == NULL)
		return;
	store_inorder(node->left, inorder, index_ptr);

	inorder[*index_ptr] = node->key;
	(*index_ptr)++;  // increase index for next entry

	store_inorder(node->right, inorder, index_ptr);
}

/* Constructs Balanced Binary Search Tree from a sorted array. */
struct bst_node * sorted_array_to_bst(int arr[], int start, int end)
{
	if (start > end)
		return NULL;

	int mid = (start + end) / 2;
	struct bst_node * root = bst_create(arr[mid]);

	root->left =  sorted_array_to_bst(arr, start, mid - 1);
	root->right = sorted_array_to_bst(arr, mid + 1, end);

	return root;
}

int main()
{
	/* Root 1:
	   100
	   /  \
	   50    110
	   / \     \
	   20  70   130
	   */
	struct bst_node * root_1 = bst_create(100);
	root_1->right = bst_create(110);
	root_1->right->right = bst_create(130);
	root_1->left = bst_create(50);
	root_1->left->left = bst_create(20);
	root_1->left->right = bst_create(70);
	printf ("Following is Inorder traversal of the first tree:\n");
	print_key_inorder(root_1);
	printf("\n\n");


	/* Root 2:
	   60
	   /  \
	   40   80
	        /   \
	       75   120
	   */
	struct bst_node * root_2 = bst_create(60);
	root_2->left = bst_create(40);
	root_2->right = bst_create(80);
	root_2->right->left = bst_create(75);
	root_2->right->right = bst_create(120);
	printf ("Following is Inorder traversal of the second tree:\n");
	print_key_inorder(root_2);
	printf("\n\n");

	/* Merge two trees. */
	struct bst_node * merge_tree = merge_balanced_bst(root_1, 6, root_2, 5);

	printf ("Following is Inorder traversal of the merged tree:\n");
	print_key_inorder(merge_tree);
	printf("\n");

	return 0;
}
