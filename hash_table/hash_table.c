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
hash_entry *hash_table_newpair(char *key, char *value)
{
	hash_entry *newpair;

	newpair = malloc( sizeof(hash_entry);
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

int hash_table_insert(hash_table *table, void *key, void *value)
{
	int index;
	hash_entry *new_entry;

	if ( ( ((double)table->count) / (table->size) ) > 0.6 ){
		hash_table_grow(table);
	}

	new_entry = (hash_entry *)malloc(sizeof(hash_entry));
	if (new_entry == NULL){
		return -1;
	}

	hash_entry -> hash_value = hash(table, key);
	hash_entry -> key = key;
	hash_entry -> value = value;

}


int insert(hashtable *table, void *key, void *value)
{
	unsigned int index;
	hashentry *newentry;

	// check to see if the table is getting too full, and if so, enlarge it
	if((((double)table->count)/(table->size))>.6)
	{
		growTable(table);
	}

	newentry = (hashentry *)malloc(sizeof(hashentry));

	if(NULL == newentry)
	{
		return 1;
	}

	//hash the key to be added, and add the k,v pair to the struct
	newentry->hashvalue = hash(table,key);
	newentry->key = key;
	newentry->value = value;

	//find the array index where the new entry will go, and add it to the list of entries at that index
	index = indexOf(newentry->hashvalue,table->size);
	newentry->next = table->hash_array[index];
	table->hash_array[index] = newentry;
	table->count++;

	return 0;
}
