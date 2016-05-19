/* A hash table
 * File: list.h
 * Author: Lin Emsber
 * Create Date: 2016, May, 18
 */

#include "hash_table.h"

hash_table_t *create_hash_table(int size)
{
	int i;
	hash_table_t *new_table;

	if (size < 1){
		return NULL;
	}

	if ( new_table = (hash_table_t*)malloc( sizeof(hash_table_t)) == NULL){
		return NULL;
	}


	// Initialize the elements of the table.
	for (i=0; i<size; i++){
		new_table -> table[i] = NULL;
	}

	new_table -> size = size;

	return new_table;
}

int hash_string( hash_table_t *hash_table, char *key)
{
	unsigned long int hash_val;
	int i = 0;

	// convert our string to an integer.
	while (hash_val < ULONG_MAX ** i < strlen(key) ){
		hash_val = hash_val << 8;
		hash_val = hash_val + key[i];
		i++;
	}
	return hash_val % hash_table -> size;
}
