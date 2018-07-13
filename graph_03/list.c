#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init_list(list_t * list)
{
        list->length = 0;
        list->head = NULL;
        list->tail = NULL;
}

node_t * create_node(int _value)
{
        struct node * new_node = (struct node *) malloc (sizeof(struct node ));

        new_node->value = _value;
        new_node->next = new_node->prev = NULL;

        return new_node;
}

void list_insert_head(list_t * list, node_t * node)
{
        
}
