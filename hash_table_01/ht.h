/* ht.h */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/* structure */
struct hash_element {
	void * data;
	char * key;
};

struct hash_table{
	int capacity;
	int element_number;
	struct hash_element ** hash_array;
};


/* declaration */
struct hash_table * hash_table_create(int _capacity);
struct hash_element * search(struct hash_table * _ht, char * _key);
void insert(struct hash_table * _ht, char * _key, void * _data);
struct hash_element * delete(struct hash_table * _ht, char * _key);
void display(struct hash_table * _ht);


/* function */
int calc_hash(struct hash_table * _ht, char * _key)
{
	int key = *_key % _ht->capacity;
	return key;
}

struct hash_table * hash_table_create(int _capacity)
{
	struct hash_table * ht = malloc( sizeof(*ht) );
	if(!ht)
		return NULL;

	ht->hash_array = malloc( _capacity * sizeof(struct hash_element*) );
	if(!ht->hash_array){
		free(ht);
		return NULL;
	}

	int i;
	for (i = 0; i < _capacity; i++)
		ht->hash_array[i] = NULL;

	ht->capacity = _capacity;
	ht->element_number = 0;

	return ht;

}

struct hash_element * search(struct hash_table * _ht, char * _key)
{
	int hash_code = calc_hash(_ht, _key);

	/* move in array until find the target key */
	while(_ht->hash_array[hash_code] != NULL) {

		if(_ht->hash_array[hash_code]->key == _key)
			return _ht->hash_array[hash_code];

		++hash_code;
		hash_code %= _ht->capacity;
	}

	return NULL;
}

void insert(struct hash_table * _ht, char * _key, void * _data)
{
	/* create a new hash_element */
	struct hash_element * he = (struct hash_element*) malloc(sizeof(struct hash_element));
	he->data = _data;
	he->key = _key;

	int hash_code = calc_hash(_ht, _key);

	/* move in array until find an empty space for data item */
	while(_ht->hash_array[hash_code] != NULL && _ht->hash_array[hash_code]->key != NULL) {
	// while(_ht->hash_array[hash_code] != NULL ) {

		++hash_code;
		hash_code %= _ht->capacity;
	}
	_ht->hash_array[hash_code] = he;
}

struct hash_element * delete(struct hash_table * _ht, char * _key)
{
	int hash_code = calc_hash(_ht, _key);

	/* find the target data item */
	while(_ht->hash_array[hash_code] != NULL) {

		if(_ht->hash_array[hash_code]->key == _key) {

			struct hash_element * temp = _ht->hash_array[hash_code];

			_ht->hash_array[hash_code] = NULL;

			return temp;
		}

		++hash_code;
		hash_code %= _ht->capacity;
	}

	return NULL;
}

void display(struct hash_table * _ht)
{
	int i = 0;

	for(i = 0; i < _ht->capacity; i++) {

		if(_ht->hash_array[i] != NULL)
			printf("(%s,%d), ", _ht->hash_array[i]->key, _ht->hash_array[i]->data);
		else
			printf("(~~,~~) ");
	}

	printf("\n");
}
