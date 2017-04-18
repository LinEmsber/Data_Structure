/* A doubly linked list
 * File: doubly_list.c
 * Author: Lin Emsber
 * Create Date: 2017, May, 19
 */

#include "doubly_list.h"


// create and initialize a new node.
node_t * node_create(int target_value)
{
	node_t * n = malloc( sizeof(*n) );
        if ( !n )
		return NULL;

        n->value = target_value;
        n->prev = NULL;
        n->next = NULL;
        n->data = NULL;

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
        list_t * l = malloc( sizeof (*l) );

	if( !l )
		return NULL;

        l->head = NULL;
        l->tail = NULL;
        l->length = 0;

	return l;
}


// free a list, including free all its node.
void list_free(list_t * list)
{
	if(list){
		list_free_node(list);
		free(list);
	}
}


// Return the length of the list.
int list_count(list_t * list)
{
	int len;
	len = list->length;

	return len;
}

// free all of the list's nodes.
void list_free_node(list_t * list)
{
	node_t * tmp;
	node_t * current = list->head;

	// free all the list's nodes
	while( current != NULL ){
		tmp = current;
		current = current -> next;
		node_free(tmp);
	}

        // reset list's status
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
}




// Push a node to the head of the list
int list_head_insert_node(list_t * list, node_t * node)
{
	if (!node || !list)
        	return -1;

        node_t * tmp = node;

        // If this list without any node
	if (list->length == 0){
		list -> head = list -> tail = node;

        // add a node behind the original head node
	}else{
		tmp = list -> head;
		list -> head -> prev = node;

		node -> next = tmp;
		node -> prev = NULL;

                list -> head = node;
	}

	(list -> length)++;

	return 0;
}

// Push a node to the tail of the list.
int list_tail_insert_node(list_t * list, node_t * node)
{
        if (!node || !list)
        	return -1;

        node_t * tmp = node;

        if (list->length == 0){
                list -> head = list -> tail = node;
        }else{
                tmp = list -> tail;
                tmp -> next = node;

                node -> prev = tmp;
                node -> next = NULL;

                list -> tail = node;
        }

        (list -> length)++;
        return 0;
}



// Pop a node from the head of list, or the top of the stack.
node_t * list_head_pop_node(list_t * list)
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



// Pop a node from the tail of list, or the bottom of the stack.
node_t * list_tail_pop_node(list_t * list)
{
        if (!list || list->length < 1)
                return NULL;

	node_t * n;
        n = list -> tail;

	if (n){
                // only one node in this list
                if (list->head == list->tail){
                        list->head = list->tail = NULL;

                }else{
                        list->tail = n->prev;
                        list->tail->next = NULL;
                }

                (list->length)--;

                n->prev = NULL;
                n->next = NULL;
	}

	return n;
}

/* print the list from the head node */
int print_list_head(node_t * head)
{
	if (head == NULL)
		return -1;

	node_t * current = head;

	while ( current != NULL ){
		printf("%d\n", current->value);
                current = current -> next;
	}

	return 0;
}

int list_get_node_pos(list_t * list, node_t * node)
{
        int i = 1;
        node_t * current = list -> head;

        if (list && current){
                while ( current ){
                        if (current == node){
                                return i;
                        }
                        current = current -> next;
                        i ++;
                }
        }
        return 0;
}

node_t * list_pick_node(list_t * list, int pos)
{
        int i;
        node_t * current = list -> head;

        if (pos > list->length)
                return NULL;

        for (i = 0; i < pos; i++)
                current = current -> next;

        if (current)
                return current;
        else
                return NULL;
}

node_t * list_remove_specific_pos_node(list_t * list, int pos)
{
        // search the target node first
        node_t * node = list_pick_node(list, pos);
        if (node == NULL)
                return NULL;

        if (node == list->head){
                return list_head_pop_node(list);

        }else if (node == list->tail){
                return list_tail_pop_node(list);

        }else{
                node -> prev -> next = node -> next;
                node -> next -> prev = node -> prev;
        }

        (list -> length)--;

        return node;
}

// TODO: organize the algorithm, make it better.
void list_swap_nodes( list_t * list, int pos_1, int pos_2)
{
	int a;
	int b;

	/* swap two number if pos_1 < pos_2 */
	if (pos_1 > pos_2){
		int t;

		t = pos_2;
		b = pos_1;
		a = t;
	}else{
		a = pos_1;
		b = pos_2;
	}

	node_t * node1 = list_pick_node(list, a);
	node_t * node2 = list_pick_node(list, b);

	struct node * temp;

	temp = node1->next;
	node1->next = node2->next;
	node2->next = temp;

	if (node1->next != NULL)
		node1->next->prev = node1;
	if (node2->next != NULL)
		node2->next->prev = node2;


	/* node1 is the first node of list */
	temp = node1->prev;
	if (temp == NULL){
		node1->prev = node2->prev;
		node1->prev->next = node1;

		list -> head = node2;
		node2->prev = NULL;
	}else{

		node1->prev = node2->prev;
		node2->prev = temp;
	}

	if (node1->prev != NULL)
		node1->prev->next = node1;

	if (node2->prev != NULL)
		node2->prev->next = node2;
}
