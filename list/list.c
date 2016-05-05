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

	/* Destroy all entries still in list */
	while((n = shift_entry(list)) != NULL)	{
		/* if there is a tagged_value_t associated to the entry,
		* let's free memory also for it */
		if(e->tagged && e->value)
		list_destroy_tagged_value_internal((tagged_value_t *)e->value, list->free_value_cb);
		else if (list->free_value_cb)
		list->free_value_cb(e->value);

		destroy_entry(e);
	}
}

// ====================node====================

// create a new node
node_t node_create()
{
	node_t *node = (node_t *) malloc( sizeof(node_t) );
	return node;
}

/*
 * Free resources allocated for a list_entry_t structure
 * If the entry is linked in a list this routine will also unlink correctly
 * the entry from the list.
 */
static inline void
destroy_entry(list_entry_t *entry)
{
    long pos;
    if(entry)
    {
        if(entry->list)
        {
            /* entry is linked in a list...let's remove that reference */
            pos = get_entry_position(entry);
            if(pos >= 0)
                remove_entry(entry->list, pos);
        }
        free(entry);
    }
}

void node_destory( node_t * node )
{
	int pos;
	if (node){
		if(node->list){
			pos = get_node_position(node);
			if(pos >= 0){
				remove_node(node->list, pos);
			}
		}
	}
}
