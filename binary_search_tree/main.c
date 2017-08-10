/* test binary search tree */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"


int main()
{
        // tree
        // tree_t * tree_entry = tree_create();
        // tree_init(tree_entry);
        // tree_remove(tree_entry);

        node_t * root = node_create();

        node_t * n_1 = node_insert_node(root, 60);
        node_t * n_2 = node_insert_node(root, 50);
        node_t * n_3 = node_insert_node(root, 80);
        node_t * n_4 = node_insert_node(root, 20);
        node_t * n_5 = node_insert_node(root, 40);
        node_t * n_6 = node_insert_node(root, 70);
        node_t * n_7 = node_insert_node(root, 10);
        node_t * n_8 = node_insert_node(root, 30);

        // node_remove_node(root, 50);
        node_remove_node(root, 20);

        return 0;
}
