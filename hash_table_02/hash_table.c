/* hash_table.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

/* Hash function use DJB2 hash algorithm. */
unsigned int hash_table_calc_hash_djb2(char * str)
{
	unsigned int hash = 5381;
	int c;
	while ((c = *str++) != 0)
		hash = ((hash << 5) + hash) + c;

	return hash;
}

/* Hash function use BKDR hash algorithm.  */
unsigned int hash_table_calc_hash_BKDR(char * str)
{
	unsigned int hash = 0;
	unsigned int seed = 131;

	while ( *str ){
		hash = (hash * seed) + (*str);
		str++;
	}

	return hash;
}

/* Create a hash table with the capacity.
 * According to the capacity to create the hash elements, and save them in a table.
 */
hash_table_t * hash_table_create(unsigned int _capacity)
{
	hash_table_t * hash_table_entry = malloc( sizeof(*hash_table_entry) );
	if(!hash_table_entry)
		return NULL;

	hash_table_entry->table = malloc( sizeof(hash_elem_t) * _capacity );
	if(hash_table_entry->table == NULL){
		free(hash_table_entry);
		return NULL;
	}

	unsigned int i;
	hash_table_entry->capacity = _capacity;
	hash_table_entry->element_number = 0;

	for(i = 0; i < _capacity; i++)
		hash_table_entry->table[i] = NULL;

	return hash_table_entry;
}

/* Store data in the hash table with the specific key.
 * If the collision of the keys occurs, we replace the old data with the new data , and return the old data.
 */
void * hash_table_put(hash_table_t * _ht, char * _key, void * _data)
{
	if(_data == NULL)
		return NULL;

	/* check the remaining space of the hash table. */
	if (_ht->capacity == _ht->element_number){
		printf("out of space of the hash table.\n");
		return NULL;
	}

	unsigned int hash_code = hash_table_calc_hash_BKDR(_key) % _ht->capacity;
	hash_elem_t * he = _ht->table[hash_code];

	/* If the hash element have already occupied by the other data. */
	while( he != NULL ){
		if( !strcmp(he->key, _key) ) {

			/* replace the old data with the new data, and return the old data. */
			void * ret = he->data;
			he->data = _data;

			return ret;
		}
		he = he->next;
	}

	/* Getting here means the key does not already exist, and no collision occurs. */
	he = malloc( sizeof(hash_elem_t) );
	if(he == NULL)
		return NULL;

	he->key = _key;
	he->data = _data;

	/* Add the element at the beginning of the linked list. */
	he->next = _ht->table[hash_code];

	_ht->table[hash_code] = he;
	_ht->element_number ++;

	return NULL;
}

/* Using the key to retrieve data from the hash table */
void * hash_table_get(hash_table_t * _ht, char * _key)
{
	unsigned int hash_code = hash_table_calc_hash_BKDR(_key) % _ht->capacity;
	hash_elem_t * he = _ht->table[hash_code];

	while(he != NULL) {

		if(!strcmp(he->key, _key)){
			return he->data;
		}

		he = he->next;
	}
	return NULL;
}


/* Remove the data from the hash table according to the key.
 * Return the data removed from the table, so that we can free its memory if needed.
 */
void * hash_table_remove(hash_table_t * _ht, char * _key)
{
	unsigned int hash_code = hash_table_calc_hash_BKDR(_key) % _ht->capacity;
	hash_elem_t * he = _ht->table[hash_code];
	hash_elem_t * prev = NULL;

	while(he != NULL) {

		if( !strcmp(he->key, _key) ) {

			void * ret = he->data;

			if(prev != NULL)
				prev->next = he->next;
			else
				_ht->table[hash_code] = he->next;

			free(he);
			he = NULL;

			_ht->element_number--;

			return ret;
		}

		prev = he;
		he = he->next;
	}

	return NULL;
}

/* List the keys of the hash table.
 * Using a string to save the keys of the hash table.
 */
void hash_table_list_keys(hash_table_t * _ht, char ** _key_array, size_t _len)
{
	if(_len < _ht->element_number)
		return;

	hash_elem_t * he;
	int key_array_index = 0;
	int i = _ht->capacity;

	while(--i >= 0) {

		he = _ht->table[i];
		while(he) {

			_key_array[key_array_index] = he->key;
			key_array_index++;
			he = he->next;
		}
	}
}

/* List datas of the hash table. */
void hash_table_list_datas(hash_table_t * _ht, void ** _data_array, size_t _len)
{
	if(_len < _ht->element_number)
		return;

	int data_array_index = 0; //Index to the current string in **v
	int i = _ht->capacity;

	while(--i >= 0) {

		hash_elem_t * he = _ht->table[i];
		while(he) {

			_data_array[data_array_index] = he->data;
			data_array_index++;
			he = he->next;
		}
	}
}

/* Iterate through the hash table's elements. */
hash_elem_t * hash_table_iterate(hash_elem_iter_t * _iterator)
{
	while(_iterator->element == NULL) {

		/* _iterator->index is zero based, but hash_table->capacity is one based. */
		if(_iterator->index < _iterator->hash_table->capacity - 1) {

			_iterator->index++;
			_iterator->element = _iterator->hash_table->table[_iterator->index];

		}else{
			return NULL;
		}
	}

	hash_elem_t * he = _iterator->element;

	/* The element of the iterator is set as the element's next hash node for convenient to obtain it
	 * in the next time. */
	if(he)
		_iterator->element = he->next;

	return he;
}

/* Iterate through the hash table's keys. */
char * hash_table_iterate_keys(hash_elem_iter_t * iterator)
{
	hash_elem_t * he = hash_table_iterate(iterator);
	return (he == NULL ? NULL : he->key);
}

/* Iterate through the hash table's datas. */
void * hash_table_iterate_datas(hash_elem_iter_t * iterator)
{
	hash_elem_t * he = hash_table_iterate(iterator);
	return (he == NULL ? NULL : he->data);
}

/* Removes all elements stored in the hash table, and free every hash node of table. */
void hash_table_clear(hash_table_t * _ht, int _free_data)
{
	hash_elem_iter_t it = INIT_HASH_TABLE_ITERATOR(_ht);
	char * k = hash_table_iterate_keys(&it);

	hash_elem_t * he;

	while(k != NULL) {
		he = hash_table_remove(_ht, k);

		if ( !he )
			free(he);

		k = hash_table_iterate_keys(&it);
	}
}

/* Destroy the hash table and free memory. */
void hash_table_destroy(hash_table_t * _ht)
{
	hash_table_clear(_ht, 1);
	free(_ht->table);
	free(_ht);
}
