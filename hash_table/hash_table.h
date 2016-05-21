/* A hash table
 * File: list.h
 * Author: Lin Emsber
 * Create Date: 2016, May, 18
 */

#include <stdio.h>
#include <stdlib.h>
#include <limit.h>

// ====================typedef====================

typedef struct entry_s entry_t;
typedef struct hash_table_s hash_table_t;

// ====================struct====================

struct entry_s{
	char *key;
	char *value;
	struct entry_s *next;
}

struct hash_table_s{
	int size;
	struct entry_s **table;
}
