/* A doubly linked list
 * File: doubly_list.c
 * Author: Lin Emsber
 * Create Date: 2017, May, 19
 */

#include "list.h"


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
                return NUll;
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
	len = l->length;

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
int * list_head_add_node(list_t *list, node_t *node)
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
                return -1;

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


// ====================================================================
// ====================================================================
// ====================================================================
// ====================================================================

// // Push a node to the head of the list
// int * list_head_add_node(list_t *list, node_t *node)

// Push a node to the tail of the list.
int *node_push_list_tail(list_t *list, node_t *node)
{
	node_t *tmp;
	if (!node)
	return 0;

	pthread_mutex_lock(&(list->mutex));

	if (list->length == 0){
		list -> head = list -> tail = node;
	}else{
		tmp = list -> tail;
		tmp -> next = node;

		node -> prev = tmp;
		node -> next = NULL;
	}

	(list -> length)++;
	node -> list = list;

	pthread_mutex_unlock(&(list->mutex));
	return 1;
}

// Pop a node from the tail of list, or the bottom of the stack.
node_t *node_pop_list_tail(list_t *list)
{
	node_t *node;
	pthread_mutex_lock(&(list->mutex));

	node = list -> tail;
	if (node){
		list -> tail = node -> prev;
		if(list -> tail){
			list->tail->next = NULL;
		}
		(list->length)--;

		node->list = NULL;
		node->prev = NULL;
		node->next = NULL;

		if (list->cur == entry)
	            list->cur = NULL;
	}
	if (list->length == 0){
		list -> tail = list -> head = NULL;
	}

	pthread_mutex_unlock(&(list->mutex));
	return node;
}

// To return the position of a node, if it linked in a list. To search the
// position of the node from the start.
int node_get_pos(node_t *node)
{
	int i = 1;
	list_t * list = node -> list;
	node_t *current = list -> head;

	pthread_mutex_lock(&(list->mutex));


	if (list && current){
		while ( current ){
			if (current == node){
				pthread_mutex_unlock(&(list->mutex));
				return i;
			}
			current = current -> next;
			i ++;
		}
	}
	pthread_mutex_unlock(&(list->mutex));
	return 0;
}


// ====================list_operations====================

// Insert a node at a specified position into a list. The position of the list
// is start from 1, not 0.
int list_insert_node(list_t *list, node_t *node, int pos)
{
	int ret;
	node_t *prev;
	node_t *next;

	if (list == NULL || node == NULL ){
		return -1;
	}

	pthread_mutex_lock(&(list->mutex));

	// The position is larger than the length of list, and it cannot be 0.
	if (pos > list->length || pos == 0){
		return -2;

	// check this node is on the list or not.
	}else if (node -> list == list){
		return 0;

	// pos = 1, push node into the head of the list.
	}else if (pos == 1) {
		node_push_list_head(list, node);
		return 1;

	// pos = length, push node into the tail of the list.
	}else if (pos == list->length){
		node_push_list_tail(list, node);
		return 1;

	// pos is the suitable number.
	}else{
		prev = list_pick_node(list, pos-1);
		next = prev -> next;

		if (prev && next){
			prev -> next = node;
			next -> prev = node;

			node -> prev = prev;
			node -> next = next;

			(list -> length)++;
			return 1;
		}
		return -3;
	}
}


// According to the position of the node on the list to remove it.
node_t *list_remove_node_pos(list_t *list, int pos)
{
	node_t *next;
	node_t *prev;

	node_t *node = list_pick_node(list, pos);

	pthread_mutex_lock(&(list->mutex));
	if (node){
		// if the node is the list->head
		if (list->head == node){
			list -> head = list -> next;
		}else{
			list -> prev -> next = list -> next;
		}
		// if the node is the list->tail
		if (list->tail == node){
			list -> tail = list -> prev;
		}else{
			list -> next -> prev = list -> prev;
		}

		(list -> length)--;
		node -> list = NULL;
		node -> prev = NULL;
		node -> next = NULL;

		// the status of list
		if (list -> cur == node){
			list -> cur = NULL;
			list -> pos = 0;
		} else if ( list -> pos > pos){
			(list -> pos)--;
		}

		pthread_mutex_unlock(&(list->mutex));
		return NULL;
	}

	pthread_mutex_unlock(&(list->mutex));
	return node;
}


// Retrieve the node at position in a list, but without removing it from the
// list. Alter the status of the list, pos and cur. The position is start from
// 1, not 0. The last position is equal to the length of the list.
node_t *list_pick_node(list_t *list, int pos)
{
	int i;
	node_t *current;
	current = list -> head;
	pthread_mutex_lock(&(list->mutex));

	if (pos > list->length){
		pthread_mutex_unlock(&(list->mutex));
		return NULL;
	}

	for (i=1; i<pos; i++){
		node = node -> next;
	}

	if(node){
		list->pos = pos;
		list->cur = entry;
	}

	pthread_mutex_unlock(&(list->mutex));
	return node;
}


// To swap two nodes of the list.
void list_swap_nodes( list_t *list, int pos_1, int pos_2)
{
	node_t *node_1 = list_pick_node(list, pos_1);
	node_t *node_2 = list_pick_node(list, pos_2);
	node_t *tmp_pos_1_prev, tmp_pos_2_next;

	pthread_mutex_lock(&(list->mutex));

	tmp_pos_1_next = node_1 -> next;
	tmp_pos_1_prev = node_1 -> prev;

	node_1 -> next = node_2 -> next;
	node_1 -> prev = node_2 -> prev;

	node_2 -> next = tmp_pos_1_next;
	node_2 -> prev = tmp_pos_1_prev;

	pthread_mutex_unlock(&(list->mutex));
}
