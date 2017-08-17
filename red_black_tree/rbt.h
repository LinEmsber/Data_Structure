/* The simple implemenataion of red black tree.
 *
 * Reference:
 * https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
 */

#ifndef RBT_H
#define RBT_H

#include <stdio.h>
#include <stdlib.h>


/*
 * TODO:
 * 	rbt_insert function add argument: _root
 *	how to deal with sentinel in argument
 */

struct rbt_node {
	enum {black, red} color;
	int key;
	struct rbt_node * left;
	struct rbt_node * right;
	struct rbt_node * parent;
};

void rbt_init();
int rbt_insert (int);
void rbt_insert_balance(struct rbt_node * p_new );
void rbt_rotate_left(struct rbt_node * p_root);
void rbt_rotate_right(struct rbt_node * p_root);
void rbt_free();
void rbt_display(struct rbt_node * p_root, int level);


struct rbt_node * root;
struct rbt_node * sentinel;

#endif
