/* ht.c
 *
 * USAGE: gcc -Wall -g ht.c && ./a.out
 * TEST: gcc -Wall -g ht.c && valgrind -v ./a.out
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ht.h"

// struct hash_table * hash_table_create(int _capacity);
// struct hash_element * search(struct hash_table * _ht, char * _key);
// void insert(struct hash_table * _ht, char * _key, void * _data);
// struct hash_element * delete(struct hash_table * _ht, char * _key);
// void display(struct hash_table * _ht);


int main()
{
	struct hash_element * item;

	/* create hash table */
	struct hash_table * ht_entry =  hash_table_create(20);

	int * p_1 = malloc(sizeof(int));
	*p_1 = 1024;
	int * p_2 = malloc(sizeof(int));
	*p_2 = 256;

	insert( ht_entry, "2", p_1 );
	insert( ht_entry, "37", p_2 );

	display(ht_entry);

	/* search item */
	item = search( ht_entry, "37");
	if(item != NULL)
		printf("Element found: %d\n", item->data);
	else
		printf("Element not found\n");

	/* delete item */
	item = delete( ht_entry, "37" );
	free(item);
	item = search( ht_entry, "37");


	if(item != NULL)
		printf("Element found: %d\n", item->data);
	else
		printf("Element not found\n");

	/* clear hash table elements */
	item = delete( ht_entry, "2" );

	/* free memory */
	free(item);
	free(ht_entry->hash_array);
	free(ht_entry);
	free(p_1);
	free(p_2);

	return 0;
}
