/* The simple implemenataion of avl tree. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct avl_node avl_node_t;
typedef struct avl_tree avl_tree_t;

struct avl_node {
	int value;
	struct avl_node * left;
	struct avl_node * right;
};


struct avl_tree {
	struct avl_node * root;
};


/* Create root new AVL tree. */
avl_tree_t * avl_create()
{
	avl_tree_t * tree = NULL;

	if( ( tree = malloc( sizeof( avl_tree_t ) ) ) == NULL ) {
		return NULL;
	}

	tree->root = NULL;

	return tree;
}

/* Initialize root new node. */
avl_node_t * avl_create_node()
{
	avl_node_t *node = NULL;

	if( ( node = malloc( sizeof( avl_node_t ) ) ) == NULL ) {
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;
	node->value = 0;

	return node;
}

/* Find the height of an AVL node recursively */
int avl_node_height( avl_node_t *node )
{
	int height_left = 0;
	int height_right = 0;

	if( node->left )
		height_left = avl_node_height( node->left );

	if( node->right )
		height_right = avl_node_height( node->right );

	return height_right > height_left ? ++height_right : ++height_left;
}

/* Find the balance of an AVL node */
int avl_balance_factor( avl_node_t *node )
{
	int bf = 0;

	if( node->left  )
		bf += avl_node_height( node->left );

	if( node->right )
		bf -= avl_node_height( node->right );

	return bf ;
}


/* Left Left Rotate */
avl_node_t * avl_rotate_leftleft( avl_node_t *node )
{
 	avl_node_t * root = node;
	avl_node_t * root_left = root->left;

	root->left = root_left->right;
	root_left->right = root;

	return root_left;
}

/* Left Right Rotate */
avl_node_t * avl_rotate_leftright( avl_node_t *node )
{
/*
	// my version
	avl_node_t * root = node;
	avl_node_t * root_left = root->left;
	avl_node_t * tmp = root_left->right->left;

	root->left = root_left->right;
	root->left->left = root_left;
	root->left->left->right = tmp;

	return avl_rotate_leftleft(root);
*/

	avl_node_t * root = node;
	avl_node_t * root_left = root->left;
	avl_node_t * root_left_right = root_left->right;

	root->left = root_left_right->right;
	root_left->right = root_left_right->left;
	root_left_right->left = root_left;
	root_left_right->right = root;

	return root_left_right;
}

/* Right Left Rotate */
avl_node_t * avl_rotate_rightleft( avl_node_t *node )
{
	avl_node_t * root = node;
	avl_node_t * root_right = root->right;
	avl_node_t * root_right_left = root_right->left;

	root->right = root_right_left->left;
	root_right->left = root_right_left->right;
	root_right_left->right = root_right;
	root_right_left->left = root;

	return root_right_left;
}

/* Right Right Rotate */
avl_node_t * avl_rotate_rightright( avl_node_t *node )
{
	avl_node_t * root = node;
	avl_node_t * root_right = root->right;

	root->right = root_right->left;
	root_right->left = root;

	return root_right;
}

/* Balance root given node */
avl_node_t * avl_balance_node( avl_node_t *node )
{
	avl_node_t * new_root = NULL;

	/* Balance our children, if they exist. */
	if( node->left )
		node->left  = avl_balance_node( node->left  );

	if( node->right )
		node->right = avl_balance_node( node->right );

	int bf = avl_balance_factor( node );

	/* Left Heavy */
	if( bf >= 2 ) {

		if( avl_balance_factor( node->left ) <= -1 )
			new_root = avl_rotate_leftright( node );
		else
			new_root = avl_rotate_leftleft( node );

	/* Right Heavy */
	} else if( bf <= -2 ) {

		if( avl_balance_factor( node->right ) >= 1 )
			new_root = avl_rotate_rightleft( node );
		else
			new_root = avl_rotate_rightright( node );

	/* This node is balanced. */
	} else {

		new_root = node;
	}

	return( new_root );
}

/* Balance root given tree */
void avl_balance( avl_tree_t * tree )
{

	avl_node_t * new_root = NULL;

	new_root = avl_balance_node( tree->root );

	if( new_root != tree->root )  {
		tree->root = new_root;
	}
}

/* Insert root new node. */
void avl_insert( avl_tree_t * tree, int value )
{
	avl_node_t * node = NULL;
	avl_node_t * next = NULL;
	avl_node_t * last = NULL;

	if( tree->root == NULL ) {
		node = avl_create_node();
		node->value = value;

		tree->root = node;

	} else {
		next = tree->root;

		while( next != NULL ) {
			last = next;

			if( value < next->value ) {
				next = next->left;

			} else if( value > next->value ) {
				next = next->right;

			/* Have we already inserted this node? */
			} else if( value == next->value ) {
				/* This shouldn't happen. */
			}
		}

		node = avl_create_node();
		node->value = value;

		if( value < last->value )
			last->left = node;

		if( value > last->value )
			last->right = node;
	}

	avl_balance( tree );
}

/* Find the node containing root given value in iterative method. */
avl_node_t * avl_search( avl_tree_t * tree, int value )
{
	avl_node_t * current = tree->root;

	while( current && current->value != value ) {
		if( value > current->value )
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

/* depth first traverse of root node. */
void avl_traverse_node_dfs( avl_node_t * node, int depth )
{
	if( node->left )
		avl_traverse_node_dfs( node->left, depth + 2 );

	printf( "%d: %d\n", node->value, avl_balance_factor( node ) );

	if( node->right )
		avl_traverse_node_dfs( node->right, depth + 2 );
}

void avl_traverse_dfs( avl_tree_t * tree )
{
	avl_traverse_node_dfs( tree->root, 0 );
}

void avl_remove(avl_node_t * node)
{
	if (node != NULL){
		avl_remove(node -> left);
		avl_remove(node -> right);
		free(node);
	}
}

int main( int argc, char ** argv )
{
	int i = 0;
	int value;
	int target_value;
	avl_tree_t * tree = NULL;
	avl_node_t * search_avl = NULL;

	tree = avl_create();

	for( i = 0; i < 10000; i++ ) {

		// value = ((i * i) % 37) + 13;
		value = i + 1337;

		avl_insert( tree, value );

	}

	target_value = ( (3*3) % 37 ) + 13;
	search_avl = avl_search( tree, target_value );
	if (search_avl != NULL)
		printf("find it.\n");
	else
		printf("can not find it.\n");

//	avl_traverse_dfs( tree );

	avl_remove(tree->root);
	free(tree);

	return 0;
}
