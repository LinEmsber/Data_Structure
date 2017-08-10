/* tree.h */


#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* typedef */
typedef struct node node_t;
typedef struct tree tree_t;


/* structure */
struct tree
{
        struct node * root;
        int count;
};

struct node
{
        int value;
        void * data;
        struct node * left;
        struct node * right;
};

/* function */


int compare_value(int value_1, int value_2);

node_t * node_create();
void node_remove_all_node(node_t * node);
node_t * node_init(node_t * node);

node_t * node_input_value(node_t * node, int value);
node_t * node_insert_node( node_t * node, int value);

tree_t * tree_create();
tree_t * tree_init( tree_t * tree);

void tree_remove(tree_t * tree);
int tree_count(tree_t * tree);

node_t * search_recurively(node_t * root, int target_value);
node_t * search_iteratively(node_t * root, int target_value);

node_t * node_insert_node( node_t * node, int value);
tree_t * tree_insert_node( tree_t * tree, int value);

node_t * node_min( node_t * node);
node_t * node_min_2(node_t * node);
node_t * tree_min(tree_t * tree);

node_t * node_max( node_t * node);
node_t * node_max_2(node_t * node);
node_t * tree_max(tree_t * tree);

void node_swap(node_t * node_1, node_t * node_2);

node_t* node_find_parent(node_t * node, node_t * target_node);

node_t * node_remove_node(node_t * node, int value);
int * tree_remove_node(tree_t * tree, int input_value);
void node_remove_left_most(node_t * node);

int is_node_contain_value(node_t * _node, int _value);
int is_tree_contain_value(tree_t * tree, int _value);

int node_height(node_t * node);
int tree_height(tree_t * tree);

int print_given_level(node_t * root, int level);

void print_breadth_first_search(node_t * root);

int DFS_pre_order(node_t * root);
int DFS_in_order(node_t * root);
int DFS_post_order(node_t * root);


#endif
