/* A doubly linked list
 * File: doubly_list.c
 * Author: Lin Emsber
 * Create Date: 2017, May, 19
 */

#include "doubly_list.h"


// create and initialize a new node.
node_t * node_create(int target_value)
{
	node_t *n;
        n = malloc( sizeof(*n) );

        if (n != NULL){
                n->value = target_value;
                n->prev = NULL;
                n->next = NULL;
                n->data = NULL;
        }else{
                free(n);
                return NULL;
        }

	return n;
}


// free a node
int node_free( node_t * node )
{
        if (node){
                free(node);
                return 0;
        }else{
                return -1;
        }
}



// create and initialize a doubly linked list.
list_t * list_create()
{
        list_t * l;
        l = malloc( sizeof (*l) );

	if(l != NULL) {
                l->head = NULL;
                l->tail = NULL;
                l->length = 0;
	}else{
                free(l);
                return NULL;
        }

	return l;
}


// free a list, including free all its node.
void list_free(list_t *list)
{
	if(list){

		list_free_node(list);
		free(list);
	}
}


// Return the length of the list.
int list_count(list_t *list)
{
	int len;
	len = list->length;

	return len;
}

// free all of the list's nodes.
void list_free_node(list_t *list)
{
	node_t * tmp;
	node_t * current = list->head;

	// free all the list's nodes
	while( current != NULL ){
		tmp = current;
		current = current -> next;
		free(tmp);
	}

        // reset list's status
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
}




// Push a node to the head of the list
int list_head_add_node(list_t *list, node_t *node)
{
	if (!node || !list)
        	return -1;

        node_t *tmp;

        // If this list without any node
	if (list->length == 0){
		list -> head = list -> tail = node;

        // add a node behind the original head node
	}else{
		tmp = list -> head;
		tmp -> prev = node;

		node -> next = tmp;
		node -> prev = NULL;
	}

	(list -> length)++;

	return 0;
}

// Pop a node from the head of list, or the top of the stack.
node_t *list_head_pop_node(list_t *list)
{
        if (!list || list->length < 1)
                return NULL;

	node_t *n;
	n = list->head;

	if (n){
                // only one node in this list
                if (list->head == list->tail){
                        list->head = list->tail = NULL;

                }else{
                        list->head = n->next;
			list->head->prev = NULL;
		}

		(list->length)--;

		n->prev = NULL;
		n->next = NULL;
	}

	return n;
}
