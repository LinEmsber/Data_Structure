/* A ipmlementation of hash table
 * File: hash.c
 * Author: Lin Emsber
 * Create Date: 2017, Jan, 14
 */

#include "hash.h"


/* create a hash table
 *
 * @size: how many node in this hash table
 */
hash_table_t * hash_create(int size)
{
	hash_table_t * hash_table = malloc(sizeof(hash_table_t));

	hash_table->size = size;
	hash_table->storage = calloc(size, sizeof(hash_node_t*));

	return hash_table;
}

/* destory a hash table
 *
 * @hash_table: the target hash table
 */
void hash_destroy(hash_table_t * hash_table)
{
	for(int i; i < hash_table->size; i++) {

		hash_node_t * node;
		if((node = hash_table->storage[i])) {
			free(node);
		}
	}

	free(hash_table->storage);
	free(hash_table);
}

/* according a key to insert a node which has key and value into a hash table.
 *
 * @hash_table: the target hash table
 * @key: the key
 * @value: the value
 */
void hash_set_node(hash_table_t * hash_table, int key, int value)
{
	hash_node_t * node;
	int hash = abs(key) % hash_table->size;

	// move in array until an empty node.
	// Since the empty node and hash_table->storage[hash] are must be NULL.
	while ( (node = hash_table->storage[hash]) ) {
		if (hash < hash_table->size - 1) {
			hash++;
		} else {
			hash = 0;
		}
	}

	node = malloc ( sizeof(hash_node_t) );
	node->key = key;
	node->val = value;

	hash_table->storage[hash] = node;
}

/* according a key to get the node from a hash_table
 *
 * @hash_table: the target hash table
 * @key: the key
 */
hash_node_t * hash_get_node(hash_table_t * hash_table, int key)
{
	int hash = abs(key) % hash_table->size;
	hash_node_t * node;

	// move in array until an empty node.
	while ( (node = hash_table->storage[hash]) ) {

		// find it
		if (node->key == key) {
			return node;
		}

		// move to the next node
		if (hash < hash_table->size - 1) {
			hash++;
		} else {
			hash = 0;
		}
	}

	return NULL;
}
