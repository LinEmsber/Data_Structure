/*
 * An implementation of binary search tree.
 */


#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

int main(){

	// basic setting
	int i;
	int times = 10;
	bst_node_t *root = NULL;

	// for loop to insert
	// for (i=0; i<times; i++){
	// 	add_node(root, i*10);
	// }

	add_node(root, 1);
	// add_node(root, 2);


	printf("root: %d\n", root->value);
	// printf("height: %d\n", tree_height(root));
	// printf("root: %d\n", root->left->value);
	// printf("root: %d\n", root->right->value);

	// breadth first search
	// printf("breadth_first_search\n");
	// print_breadth_first_search(root);
	return 0;
}
