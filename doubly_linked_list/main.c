/* main */

/* An main function of doubly linked list.
 * File: main.c
 * Author: Lin Emsber
 * Create Date: 2017, Mar, 19
 */

#include <stdio.h>
#include <stdlib.h>

#include "doubly_list.h"
#include "generic.h"


#define NODE_NUM 10

int main()
{
        int i;
        node_t * n_tmp;
        node_t * node_array[NODE_NUM];

        list_t * list_entry = list_create();

        // use a node_t array to create many nodes.
        for (i = 0; i < NODE_NUM; i = i + 2){
                node_array[i] = node_create(i);
                list_head_insert_node(list_entry, node_array[i]);
        }


        for (i = 1; i < NODE_NUM; i = i + 2){
                node_array[i] = node_create(i);
                list_tail_insert_node(list_entry, node_array[i]);
        }

        for (i = 0; i < NODE_NUM; i++){
                node_array[i] = node_create(10 + i * 10);
                // list_tail_insert_node(list_entry, node_array[i]);
                // printf("hello\n");
                list_head_insert_node(list_entry, node_array[i]);
        }

        printf("list_count(list_entry): %d\n", list_count(list_entry));


        // free node
        for (i = 0; i < NODE_NUM / 2; i = i + 2){
                n_tmp = list_head_pop_node(list_entry);
                node_free(n_tmp);
        }

        for (i = 1; i < NODE_NUM / 2; i = i + 2){
                n_tmp = list_tail_pop_node(list_entry);
                node_free(n_tmp);
        }

        printf("list_get_node_pos(list, node_array[9]):%d \n", list_get_node_pos(list_entry, node_array[9]));
        printf("%p\n", list_pick_node(list_entry , 2));
        printf("%p\n", node_array[7]);

        for (i = 0; i < 3; i++){
                n_tmp = list_remove_specific_pos_node(list_entry, 0);
                free(n_tmp);
        }

        n_tmp = list_remove_specific_pos_node(list_entry, 1);
        free(n_tmp);

        n_tmp = list_remove_specific_pos_node(list_entry, 2);
        free(n_tmp);

        print_list_head(list_entry->head);

        printf("===== After swap nodes =====\n");

        for (i = 0; i < NODE_NUM / 2; i++){
                list_swap_nodes(list_entry, i, NODE_NUM - 1 - i);
        }
        print_list_head(list_entry->head);

        printf("===== After swap nodes again =====\n");

        for (i = 0; i < NODE_NUM / 2; i++){
                list_swap_nodes(list_entry, NODE_NUM - 1 - i, i);
        }
        print_list_head(list_entry->head);


        // free list
        list_free(list_entry);

	return 0;
}
