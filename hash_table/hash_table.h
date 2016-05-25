/* A hash table
 * File: list.h
 * Author: Lin Emsber
 * Create Date: 2016, May, 18
 */

#include <stdio.h>
#include <stdlib.h>
#include <limit.h>

// ====================typedef====================

typedef struct _hash_entry hash_entry;
typedef struct _hash_table hash_table;

// ====================struct====================

struct _hash_entry
{
	void *key;
	void *value;

	unsigned int hash_value;
	struct _hash_entry *next;
};

struct _hash_table
{
	int size;
	int count;
	struct _hash_entry **table;

	unsigned int (*hash_function)(const void *key);
	int (*compare)(const void *, const void *);
};


unsigned int hash(hashtable *, const void *);
unsigned int hash_double(const void *);
unsigned int hash_int(const void *);
unsigned int hash_string(const void *);
int cmp_string(const void *, const void *);
int cmp_double(const void *, const void *);
int cmp_int(const void *, const void *);
unsigned int indexOf(unsigned int , int );
int growTable(hashtable *);
int insert(hashtable *,void *,void *);
void *find(hashtable *,void *);
void *removeKey(hashtable *,void *);
void deleteTable(hashtable *);
