/* A multi-thread safe linked list
 * File: list.c
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */

#include "list.h"


// ====================list_basic_api====================

// To create a linked list.
list_t * list_create()
{
	list_t *list = (list_t *)malloc(sizeof(list_t));

	if(list) {
		if (list_init(list) != 0) {
			free(list);
			return NULL;
		}
	}
	return list;
}

// To initialize a list that is using mutex for thread-safe.
int list_init(list_t *list)
{
	pthread_mutexattr_t attr;

	if (pthread_mutexattr_init(&attr) != 0) {
		return -1;
	}

	// set attribute as PTHREAD_MUTEX_RECURSIVE.
	// A thread attempting to relock this mutex without first unlocking it
	// will succeed in locking the mutex.
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	if (pthread_mutex_init( &(list->mutex), &attr) != 0) {
		return -1;
	}

	pthread_mutexattr_destroy(&attr);
	return 0;
}

// To destroy a list, including remove all list's node, and free them.
void list_destroy(list_t *list)
{
	if(list){
		while (list->slices){
			slice_destroy(list->slices->value);
		}

		list_clear(list);
		pthread_mutex_destory(&(list->mutex));
		free(list);
	}
}

// Return the length of the list.
int list_count(list_t *list)
{
	int len;
	pthread_mutex_lock(&(list->mutex));

	len = l->length;

	pthread_mutex_unlock(&(list->mutex));

	return len;
}

// To remove all of the list's nodes, and free them.
void list_clear(list_t *list)
{
	node_t * temp;
	node_t * current = list->head;
	pthread_mutex_lock(&(list->mutex));

	// destroy list's nodes
	while( current != NULL ){
		temp = current;
		current = current -> next;
		free(temp);
	}

	pthread_mutex_unlock(&(list->mutex));
}

// ====================node_basic_api====================

// To create a new node.
node_t node_create()
{
	node_t *node = (node_t *) malloc( sizeof(node_t) );
	return node;
}

// A node remove from the list, and free it.
void node_destory( node_t * node )
{
	int pos;
	if (node){
		if(node->list){

			pthread_mutex_lock(&(node->list->mutex));

			// get the position of node on the list
			pos = get_node_position(node);
			if(pos >= 0){
				remove_node(node->list, pos);
			}

			pthread_mutex_unlock(&(node->list->mutex));
		}
	}
}


// ====================node_operations====================

// Push a node to the head of the list
int *node_push_list_head(list_t *list, node_t *node)
{
	node_t *temp;
	if (!node)
	return 0;

	pthread_mutex_lock(&(list->mutex));

	if (list->length == 0){
		list -> head = list -> tail = node;
	}else{
		temp = list -> head;
		temp -> prev = node;

		node -> next = temp;
		node -> prev = NULL;
	}

	(list -> length)++;
	node -> list = list;

	pthread_mutex_unlock(&(list->mutex));
	return 1;
}

// Pop a node from the head of list, or the top of the stack.
node_t *node_pop_list_head(list_t *list)
{
	node_t *node;
	pthread_mutex_lock(&(list->mutex));

	node = list -> head;
	if (node){
		list -> head = node -> next;
		if(list -> head){
			list->head->prev = NULL;
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

// Push a node to the tail of the list.
int *node_push_list_tail(list_t *list, node_t *node)
{
	node_t *temp;
	if (!node)
	return 0;

	pthread_mutex_lock(&(list->mutex));

	if (list->length == 0){
		list -> head = list -> tail = node;
	}else{
		temp = list -> tail;
		temp -> next = node;

		node -> prev = temp;
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
void list_swap_nodes( list_t *list, int pos_1, inst pos_2)
{
	node_t *node_1 = list_pick_node(list, pos_1);
	node_t *node_2 = list_pick_node(list, pos_2);
	node_t *temp_pos_1_prev, temp_pos_2_next;

	pthread_mutex_lock(&(list->mutex));

	temp_pos_1_next = node_1 -> next;
	temp_pos_1_prev = node_1 -> prev;

	node_1 -> next = node_2 -> next;
	node_1 -> prev = node_2 -> prev;

	node_2 -> next = temp_pos_1_next;
	node_2 -> prev = temp_pos_1_prev;

	pthread_mutex_unlock(&(list->mutex));
}
