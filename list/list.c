/* A multi-thread safe linked list
 * File: list.c
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */

#include "list.h"


// ====================list====================

// create list
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

// list init
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

// list destroy
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

// return list length
int list_count(list_t *list)
{
	int len;
	pthread_mutex_lock(&(list->mutex));

	len = l->length;

	pthread_mutex_unlock(&(list->mutex));

	return len;
}

// remove list's nodes, and free them.
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

// ====================node====================

// create a new node
node_t node_create()
{
	node_t *node = (node_t *) malloc( sizeof(node_t) );
	return node;
}

// node remove from the list, and free it.
void node_destory( node_t * node )
{
	int pos;
	if (node){
		if(node->list){

			pthread_mutex_lock(&(list->mutex));

			// get the position of node on the list
			pos = get_node_position(node);
			if(pos >= 0){
				remove_node(node->list, pos);
			}

			pthread_mutex_unlock(&(list->mutex));
		}
	}
}

// pop a node from the end of list, or the bottom of the stack.
node_t *node_pop(list_t *list)
{
	node_t *node;
	pthread_mutex_lock(&(list->mutex));

	node = list -> tail;
	if (node){
		list -> tail = node -> prev;
		if(list -> prev){
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


// Retrieve the node at pos in a list, but without removing it from the list.
// Alter the status of the list, pos and cur.
node_t *list_pick_node(list_t *list, int pos)
{
	int i;
	node_t *current;
	current = list -> head;
	pthread_mutex_lock(&(list->mutex));

	if (list->length < pos){
		pthread_mutex_unlock(&(list->mutex));
		return NULL;
	}

	for (i=0; i<pos; i++){
		node = node -> next;
	}

	if(node){
		list->pos = pos;
		list->cur = entry;
	}

	pthread_mutex_unlock(&(list->mutex));
	return node;
}
