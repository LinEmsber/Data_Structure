/* A multi-thread safe linked list
 * File: list.c
 * Author: Lin Emsber
 * Create Date: 2016, May, 3
 */

#include "list.h"


// ====================list====================

// create list
struct list * list_create()
{
	struct list *list = (linked_list_t *)malloc(sizeof(linked_list_t));
	if(list) {
		if (list_init(list) != 0) {
			free(list);
			return NULL;
		}
	}
	return list;
}

// list init
int list_init(struct list *list)
{
	pthread_mutexattr_t attr;

	if (pthread_mutexattr_init(&attr) != 0) {
		return -1;
	}

	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	if (pthread_mutex_init(&list->lock, &attr) != 0) {
		return -1;
	}

	pthread_mutexattr_destroy(&attr);
	return 0;
}

// list destroy
void list_destroy(struct list *list)
{
	if(list){
		while (list->slices){
			slice_destroy(list->slices->value);
		}

		list_clear(list);

		MUTEX_DESTROY(list->lock);
		free(list);
	}
}
