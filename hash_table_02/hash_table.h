/* hash_table.h */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* typedef */
typedef struct hash_element hash_elem_t;
typedef struct hash_table hash_table_t;
typedef struct hash_element_iter hash_elem_iter_t;

/* strucuture */
struct hash_element {
	struct hash_element * next;
	void * data;
	char * key;
};

struct hash_table {
	unsigned int capacity;
	unsigned int element_number;
	struct hash_element ** table;
};


struct hash_element_iter {
	struct hash_table * hash_table;
	unsigned int index;
	struct hash_element * element;
};

/* MACRO */
#define INIT_HASH_TABLE_ITERATOR(_ht) {_ht, 0, _ht->table[0]}



/* function */

unsigned int hash_table_calc_hash_djb2(char * str);
unsigned int hash_table_calc_hash_BKDR(char * str);

hash_table_t * hash_table_create(unsigned int _capacity);
void * hash_table_put(hash_table_t * _ht, char * _key, void * _data);
void * hash_table_get(hash_table_t * _ht, char * _key);
void * hash_table_remove(hash_table_t * _ht, char * _key);

void hash_table_list_keys(hash_table_t * _ht, char ** _key_array, size_t _len);
void hash_table_list_datas(hash_table_t * _ht, void ** _data_array, size_t _len);

hash_elem_t * hash_table_iterate(hash_elem_iter_t * _iterator);
char * hash_table_iterate_keys(hash_elem_iter_t * iterator);
void * hash_table_iterate_datas(hash_elem_iter_t * iterator);

void hash_table_clear(hash_table_t * _ht, int _free_data);
void hash_table_destroy(hash_table_t * _ht);

#endif
