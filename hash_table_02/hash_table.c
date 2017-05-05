/* hash_table.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"


/* variable */

char err_ptr;
void * HT_ERROR = &err_ptr;


unsigned int hash_table_calc_hash(char* str)
{
	unsigned int hash = 5381;
	int c;
	while ((c = *str++) != 0)
		hash = ((hash << 5) + hash) + c;

	return hash;
}

/* Create a hash table with capacity. */
hash_table_t * hash_table_create(unsigned int _capacity)
{
	hash_table_t * hash_table_entry = malloc( sizeof(*hash_table_entry) );
	if(!hash_table_entry)
		return NULL;

	hash_table_entry->table = malloc(_capacity * sizeof(hash_elem_t) );
	if(hash_table_entry->table == NULL){
		free(hash_table_entry);
		return NULL;
	}

	hash_table_entry->capacity = _capacity;
	hash_table_entry->element_number = 0;

	unsigned int i;
	for(i = 0; i < _capacity; i++)
		hash_table_entry->table[i] = NULL;

	return hash_table_entry;
}

/* Store data in the hash table.
 * If data with the same key are already stored, they are overwritten, and return by
 * the function. Else it return NULL.
 */
void * hash_table_put(hash_table_t * _ht, char * _key, void * _data)
{
	if(_data == NULL)
		return NULL;

	unsigned int hash_code = hash_table_calc_hash(_key) % _ht->capacity;
	hash_elem_t * he = _ht->table[hash_code];

	while(he != NULL) {

		/* find a exist same key */
		if(!strcmp(he->key, _key)) {

			/* replace the old data with new data, and return the old data. */
			void * ret = he->data;
			he->data = _data;

			return ret;
		}
		he = he->next;
	}

	// Getting here means the key doesn't already exist

//	he = malloc( sizeof(hash_elem_t) + strlen(_key)+1 );
	he = malloc( sizeof(hash_elem_t) );
	if(he == NULL)
		return HT_ERROR;

//	strcpy(he->key, _key);
	he->key = _key;
	he->data = _data;

	// Add the element at the beginning of the linked list
	he->next = _ht->table[hash_code];

	_ht->table[hash_code] = he;
	_ht->element_number ++;

	return NULL;
}

/* Retrieve data from the hash table */
void * hash_table_get(hash_table_t * _ht, char * _key)
{
	unsigned int hash_code = hash_table_calc_hash(_key) % _ht->capacity;
	hash_elem_t* he = _ht->table[hash_code];

	while(he != NULL) {
		// printf("%s\n", he->key);
		// printf("%s\n", _key);

		if(!strcmp(he->key, _key)){
			// printf("find it.\n");
			return he->data;
		}

		he = he->next;

	}
	return NULL;
}

/* Remove data from the hash table.
 * Return the data removed from the table so that we can free memory if needed.
 */
void * hash_table_remove(hash_table_t * _ht, char * _key)
{
	unsigned int hash_code = hash_table_calc_hash(_key) % _ht->capacity;
	hash_elem_t * he = _ht->table[hash_code];
	hash_elem_t * prev = NULL;

	while(he != NULL) {

		if(!strcmp(he->key, _key)) {

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

/* List the keys of the hash table. */
void hash_table_list_keys(hash_table_t * _ht, char ** _key_array, size_t _len)
{
	if(_len < _ht->element_number)
		return;

	int key_array_index = 0; //Index to the current string in **k
	int i = _ht->capacity;

	while(--i >= 0) {

		hash_elem_t * he = _ht->table[i];
		while(he) {

			_key_array[key_array_index] = he->key;
			key_array_index++;
			he = he->next;
		}
	}
}

/* List values of the hash table. */
void hash_table_list_values(hash_table_t * _ht, void ** _value_array, size_t _len)
{
	if(_len < _ht->element_number)
		return;

	int value_array_index = 0; //Index to the current string in **v
	int i = _ht->capacity;

	while(--i >= 0) {

		hash_elem_t * he = _ht->table[i];
		while(he) {

			_value_array[value_array_index] = he->data;
			value_array_index++;
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

	if(he)
		_iterator->element = he->next;

	return he;
}

/* Iterate through the hash table's  keys. */
char * hash_table_iterate_keys(hash_elem_iter_t * iterator)
{
	hash_elem_t * he = hash_table_iterate(iterator);
	return (he == NULL ? NULL : he->key);
}

/* Iterate through the hash table's  values. */
void * hash_table_iterate_values(hash_elem_iter_t * iterator)
{
	hash_elem_t * he = hash_table_iterate(iterator);
	return (he == NULL ? NULL : he->data);
}

/* Removes all elements stored in the hash table. */
void hash_table_clear(hash_table_t * _ht, int _free_data)
{
	hash_elem_iter_t it = INIT_HASH_TABLE_ITERATOR(_ht);
	char * k = hash_table_iterate_keys(&it);

	hash_elem_t * he;

	while(k != NULL) {
		he = hash_table_remove(_ht, k);

//		_free_data ? free(hash_table_remove(_ht, k)) : hash_table_remove(_ht, k);

		if ( !he )
			free(he);

		k = hash_table_iterate_keys(&it);
	}
}

/* Destroy the hash table and free memory. */
void hash_table_destroy(hash_table_t * _ht)
{
	hash_table_clear(_ht, 1); // Delete and free all.
	free(_ht->table);
	free(_ht);
}
