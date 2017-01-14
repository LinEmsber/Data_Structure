/* A ipmlementation of hash table
 * File: hash.h
 * Author: Lin Emsber
 * Create Date: 2017, Jan, 14
 */

#include <stdio.h>
#include <stdlbi.h>

// ===== structure and typedef =====
typedef struct hash_node hash_node_t;
struct hash_node {
	int key;
	int val;
};

typedef struct hash_table hash_table_t;
struct hash_table {
	int size;
	struct hash_node ** storage;
};


// ===== declaration =====
hash_table_t * hash_create(int size);
void hash_destroy(hash_table_t * hash_table);
void hash_set_node(hash_table_t * hash_table, int key, int value);
hash_node_t * hash_get_node(hash_table_t * hash_table, int key);
