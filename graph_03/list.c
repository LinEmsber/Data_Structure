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

void list_head_insert_node(list_t * list, node_t * node)
{

        if (list->length == 0){
                list->head = list->tail = node;
        } else {
                node_t * tmp = list->head;
                list->head->prev = node;

                node->next = tmp;
                node->prev = NULL;

                list->head = node;
        }

        (list->length)++;
}

node_t * list_tail_pop_node(list_t * list)
{
        node_t * tmp = list->tail;

        if (tmp){
                if (list->head == list->tail) {
                        list->head = list->tail = NULL;
                } else {
                        list->tail = n->prev;
                        list->tail->next = NULL;
                }

                (list->length)--;
                // tmp->prev = tmp->tail = NULL/
        }

        return tmp;
}
