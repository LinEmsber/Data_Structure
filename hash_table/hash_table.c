/* A hash table
 * File: list.h
 * Author: Lin Emsber
 * Create Date: 2016, May, 18
 */

#include "hash_table.h"

unsigned int hash(hash_table *table, const void *key)
{
	unsigned int h = table->hash_function(key);

	h += ~(h << 9);
	h ^= (( h >> 14) | (h << 18));
	h += (h << 4);
	h ^= ((h >> 10) | (h << 22));
	return h;
}

hash_table *hash_table_create(int size)
{
	int i;
	hash_table *new_table;

	if (size < 1){
		return NULL;
	}

	if ( new_table = (hash_table*)malloc( sizeof(hash_table)) == NULL){
		return NULL;
	}


	// Initialize the elements of the table.
	for (i=0; i<size; i++){
		new_table -> table[i] = NULL;
	}

	new_table -> size = size;

	return new_table;
}

// uses the well-known djb2 hash algorithm for strings
unsigned int hash_string(const void *key)
{
	char *string = (char *)key;
	unsigned int hash = 0;
	int string_ch = 0;

	while((string_ch = *string++))
	{
		hash = ((hash << 5) + hash) ^ string_ch;
	}
	return hash;
}



// Create a key-value pair.
entry_t *hash_table_newpair(char *key, char *value)
{
	entry_t *newpair;

	newpair = malloc( sizeof(entry_t);
	if ( newpair == NULL ){
		return NULL;
	}

	newpair -> key = strdup(key);
	if ( newpair -> key == NULL ){
		return NULL;
	}

	newpair -> value = strdup(value);
	if ( newpair -> value == NULL ){
		return NULL;
	}

	newpair -> next = NULL;

	return newpair;
}
