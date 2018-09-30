#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;
struct node{
	int val;
	struct node * next;
};

/* Create a node. */
node_t * node_create(int val)
{
	node_t * n;

	n = malloc( sizeof(*n) );
	if (n == NULL)
		return NULL;

	n -> val = val;
	n -> next = NULL;

	return n;
}

/* The new node is always added before the head of the given list. */
int node_insert_front(node_t * head, node_t * n)
{
	if (head == NULL || n == NULL)
		return -1;

	n -> next = head -> next;
	head -> next = n;

	return 0;
}

/* The new node is added after the given node. */
int node_insert_after_node(node_t * prev_node, node_t * n)
{
	if ( prev_node == NULL)
		return -1;

	n -> next = prev_node -> next;
	prev_node -> next = n;

	return 0;
}

/* The new node is always added after the last node of the given list. */
int node_insert_end(node_t * head, node_t * n)
{
	node_t * last = head;

	if ( head == NULL ){
		head = n;
		return 0;
	}

	while ( last -> next != NULL )
		last = last -> next;

	last -> next = n;
	return 0;
}

/*
   I use tool: gdb, to analyze argument, head, and variable, **PP.
   At the begin of this functions:

   (gdb) p *head
   $1 = {val = 0, next = 0x602150}
   (gdb) p head
   $2 = (node_t *) 0x602010
   (gdb) p &head
   $3 = (node_t **) 0x7fffffffdad8

   After the "node_t **pp = &head;" :

   (gdb) p **pp
   $4 = {val = 0, next = 0x602150}
   (gdb) p *pp
   $5 = (node_t *) 0x602010
   (gdb) p pp
   $6 = (node_t **) 0x7fffffffdad8

 */

int node_delete(node_t * head, int target_val)
{
	int ret = -1;
	if (head == NULL)
		return ret;

	node_t **pp = &head;
	node_t *p = head;

	while(p){
		if(p->val == target_val){
			*pp = p->next;
			free(p);
			ret = 0;

			/* Remember to break from the while loop. */
			break;
		}

		pp = &p->next;
		p = p->next;
	}

	return ret;
}

/* Use iterative method to reverse linked list. */
node_t * node_reverse_iterative(node_t * n1)
{
	if(n1 == NULL)
		return NULL;

        node_t * n0 = NULL;
        node_t * tmp;

	/* 1. Store the next node of head (n1->next) to the tmp node (tmp).
	 * 2. Set the next node of head (n1->next) as the prev node of head (n0).
	 * 3. Set the prev node of head (n0) as head (n1).
	 * 4. Set the head (n1) as the tmp node (tmp).
	 */
        while(n1 != NULL){

		/* It similiar swap, but there are four variables: next, n1->next, n0 n1 */
                tmp = n1->next;
                n1->next = n0;
                n0 = n1;
                n1 = tmp;
        }

	return n0;
}


/* Get the previous node */
node_t * previous_node(node_t * head, node_t * target_node)
{
	if(head == target_node || head == NULL)
		return NULL;

	/* Start from the head node to find the target nodes's previous node. */
	node_t * current = head;
	node_t * prev = NULL;

	while(current){

		/* Find the target node */
		if (current == target_node)
			break;

		prev = current;
		current = current->next;
	}

	/* Return target nodes's previous node. */
	return prev;
}

/* Swap two nodes of singly linked list. */
int swap_nodes(node_t ** head, node_t ** node_1, node_t ** node_2)
{
	if (head == NULL|| node_1 == NULL || node_2 == NULL)
		return -1;

	node_t * first = *node_1;
	node_t * second = *node_2;
	node_t * first_prev, * second_prev;
	node_t * tmp = NULL;

	/* Find the target nodes's previous node. */
	first_prev = previous_node(*head, first);
	second_prev = previous_node(*head, second);

	/* Swap the previous nodes of both nodes. */
	if(first_prev)
		first_prev->next = second;
	else
		*head = *node_2;

	if(second_prev)
		second_prev->next = first;
	else
		*head = *node_1;

	/* Swap the next nodes of both nodes */
	tmp = first->next;
	first->next = second->next;
	second->next = tmp;

	return 0;
}

/* Print the list. */
int print_list(node_t * head)
{
	if (head == NULL)
		return -1;

	node_t * current = head;

	while ( current != NULL ){
		printf("%d ", current->val);
		current = current -> next;
	}
	printf("\n");

	return 0;
}

int main()
{
	int ret = 0;
	node_t * tmp;

	/* Create root. */
	node_t * root = node_create(0);

	/* Add nodes. */
	node_t * n_1 = node_create(1);
	node_t * n_3 = node_create(3);
	node_t * n_5 = node_create(5);
	node_t * n_7 = node_create(7);
	ret = node_insert_front(root, n_1);
	ret = node_insert_front(root, n_3);
	ret = node_insert_front(root, n_5);
	ret = node_insert_front(root, n_7);
	print_list(root);

	/* Delete a node.*/
	ret = node_delete(root, 3);
	if (ret == -1)
		printf("Error\n");

	print_list(root);

	/* Reverse list. The root becomes value 10. */
	tmp = node_reverse_iterative(root);
	root = tmp;
	print_list(root);

	/* Delete the list. */
	ret = node_delete(root, 5);
	ret = node_delete(root, 7);
	tmp = node_reverse_iterative(root);
	root = tmp;
	ret = node_delete(root, 1);
	if (ret == -1)
		printf("Error\n");

	print_list(root);

	/* Add nodes. */
	node_t * n_2 = node_create(2);
	node_t * n_4 = node_create(4);
	node_t * n_6 = node_create(6);
	node_t * n_8 = node_create(8);
	ret = node_insert_front(root, n_2);
	ret = node_insert_front(root, n_4);
	ret = node_insert_front(root, n_6);
	ret = node_insert_front(root, n_8);
	if (ret == -1)
		printf("Error\n");

	print_list(root);

	/* Swap the root and the last node. It change the root. */
	swap_nodes(&root, &root, &n_1);
	print_list(root);

	/* Add nodes to the specific node. */
	node_t * n_11 = node_create(11);
	node_t * n_13 = node_create(13);
	ret = node_insert_after_node(n_6, n_11);
	ret = node_insert_after_node(n_6, n_13);
	if (ret == -1)
		printf("Error\n");

	print_list(root);

	/* Add nodes to the end of list. */
	node_t * n_21 = node_create(21);
	node_t * n_23 = node_create(23);
	ret = node_insert_end(root, n_21);
	ret = node_insert_end(root, n_23);
	if (ret == -1)
		printf("Error\n");

	print_list(root);

	return 0;
}
