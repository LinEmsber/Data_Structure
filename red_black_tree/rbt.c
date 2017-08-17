/* The simple implemenataion of red black tree.
 *
 * Reference:
 * https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
 */

#include <stdio.h>
#include <stdlib.h>

#include "rbt.h"


void rbt_init()
{
	/* The sentinel will be the parent of root node and replace NULL */

	sentinel = (struct rbt_node *) malloc(sizeof(struct rbt_node));
	sentinel->key = -1;
	sentinel->color = black;
	root = sentinel;
}

int rbt_insert (int _key )
{
	struct rbt_node * p_new, * p_root, * p_parent;

	p_parent = sentinel;
	p_root = root;

	/* find the right position for new node and its parent. */
	while( p_root != sentinel ) {

		p_parent = p_root;

		if( _key < p_root->key )
			p_root = p_root->left;

		else if( _key > p_root->key )
			p_root = p_root->right;

		// Duplicate node
		else
			return -1;
	}

	p_new = (struct rbt_node *) malloc(sizeof(struct rbt_node));
	p_new->key = _key;
	p_new->left = sentinel;
	p_new->right = sentinel;
	p_new->color = red;
	p_new->parent = p_parent;

	if(p_parent == sentinel)
		root = p_new;

	else if(p_new ->key < p_parent->key )
		p_parent->left = p_new;

	else
		p_parent->right = p_new;

	rbt_insert_balance(p_new);

	return 0;
}

void rbt_insert_balance(struct rbt_node * p_new )
{
	struct rbt_node * p_uncle, * p_parent, * p_grand;

	/* The new node must be red. Thus, its parent cannot be black. */
	while( p_new->parent->color == red ) {

		p_parent = p_new->parent;
		p_grand = p_parent->parent;

		/* parent is grand parent's left node */
		if( p_parent == p_grand->left ) {

			p_uncle = p_grand->right;

			/* Case L_1 */
			if(p_uncle->color == red ) {
				p_parent->color = black;
				p_uncle->color = black;
				p_grand->color =red;
				p_new = p_grand;
			}

			/* p_uncle is black */
			else  {
				/* Case L_2a */
				if( p_new == p_parent->right) {
					rbt_rotate_left(p_parent);
					p_new = p_parent;
					p_parent = p_new->parent;
				}

				/* Case L_2b */
				p_parent->color = black;
				p_grand->color = red;
				rbt_rotate_right(p_grand);
			}
		}

		/* parent is grand parent's right node */
		else if(p_parent == p_grand->right ) {

			p_uncle = p_grand->left;

			/* Case R_1 */
			if(p_uncle->color == red )  {
				p_parent->color = black;
				p_uncle->color = black;
				p_grand->color =red;
				p_new = p_grand;
			}

			/* p_uncle is black */
			else {
				/* Case R_2a */
				if( p_new == p_parent->left) {
					rbt_rotate_right(p_parent);
					p_new = p_parent;
					p_parent = p_new->parent;
				}

				/* Case R_2b */
				p_parent->color = black;
				p_grand->color = red;
				rbt_rotate_left(p_grand);
			}
		}

	}

	root->color = black;
}


void rbt_rotate_left(struct rbt_node * p_node)
{
	struct rbt_node * p_node_r;

	/* p_node_r is right child of p_node*/
	p_node_r = p_node->right;
	p_node->right= p_node_r->left;

	if(p_node_r->left != sentinel)
		p_node_r->left->parent = p_node;

	p_node_r->parent = p_node->parent;

	if(p_node->parent == sentinel )
		root = p_node_r;

	else if( p_node == p_node->parent->left )
		p_node->parent->left = p_node_r;

	else
		p_node->parent->right = p_node_r;

	p_node_r->left = p_node;
	p_node->parent = p_node_r;
}

void rbt_rotate_right(struct rbt_node * p_node)
{
	struct rbt_node * p_node_l;

	/* p_node_l is left child of p_node*/
	p_node_l = p_node->left;
	p_node->left= p_node_l->right;

	if(p_node_l->right !=sentinel )
		p_node_l->right->parent = p_node;

	p_node_l->parent = p_node->parent;

	if(p_node->parent == sentinel )
		root = p_node_l;

	else if( p_node == p_node->parent->right )
		p_node->parent->right = p_node_l;

	else
		p_node->parent->left = p_node_l;

	p_node_l->right = p_node;
	p_node->parent = p_node_l;
}

void rbt_free()
{
	if (root != NULL && root != sentinel){
		rbt_free(root -> left);
		free(root);
		rbt_free(root -> right);
	}
}


void rbt_display(struct rbt_node * p_root, int level)
{
	int i;
	if ( p_root != sentinel ) {

		rbt_display(p_root->right, level+1);
		printf("\n");

		for(i = 0; i < level; i++)
			printf("    ");

		printf("%d", p_root->key);

		if(p_root->color==red)
			printf("R");
		else
			printf("B");

		rbt_display(p_root->left, level + 1);
	}

	printf("\n");
}
