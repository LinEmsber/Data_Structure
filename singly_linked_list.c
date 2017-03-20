/* singly linked list */

#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

struct node{
	int val;
	struct node * next;
};

/* create a node */
node_t * node_t_create(int val)
{
	node_t * n;

	n = malloc( sizeof(*n) );
	if (n == NULL)
		return NULL;

	n -> val = val;
	n -> next = NULL;

	return n;
}

/* add a new node */
int node_add(node_t * head, node_t * n)
{
        if (head == NULL || n == NULL)
                return -1;

	n -> next = head -> next;
	head -> next = n;

        return 0;
}

/* According to the target value to remove a node from a list,
 * and free this target node.
 */
int node_remove(node_t * head, int target_val)
{
        if (head == NULL)
                return -1;

        int ret = -1;

	node_t **pp = &head;
	node_t *entry = head;

	while(entry){
		if(entry->val == target_val){
                        *pp = entry->next;
                        free(entry);
                        ret = 0;
                }

		pp = &entry->next;
		entry = entry->next;
	}

	return ret;
}

/* free all node from a list */
int node_free(node_t * head)
{
	if (head == NULL)
		return -1;

	node_t * current = head;
	node_t * tmp;

	while ( current != NULL ){
		tmp = current;
                current = current -> next;
                free(tmp);
	}

	return 0;
}

/* print the list */
int print_list(node_t * head)
{
	if (head == NULL)
		return -1;

	node_t * current = head;

	while ( current != NULL ){
		printf("%d\n", current->val);
                current = current -> next;
	}

	return 0;
}




int main()
{
	int ret = 0;

	node_t * start = node_t_create(0);
	node_t * e1 = node_t_create(10);
	node_t * e2 = node_t_create(30);
        node_t * e3 = node_t_create(50);
        node_t * e4 = node_t_create(20);
        node_t * e5 = node_t_create(40);

	ret = node_add( start, e1 );
	ret = node_add( start, e2 );
        ret = node_add( start, e3 );
        ret = node_add( start, e4 );
        ret = node_add( start, e5 );

        ret = print_list( start );

        ret = node_remove( start, 30);
        ret = node_remove( start, 10);

        printf("ret: %d\n", ret);

        ret = print_list( start );
        printf("ret: %d\n", ret);

	ret = node_free(start);
        printf("ret: %d\n", ret);

	return 0;
}
