/* The implentation of hash table.
 *
 * USAGE: gcc -Wall -g main.c hash_table.c && ./a.out
 *
 * memory and error check: gcc -Wall -g main.c hash_table.c && valgrind -v ./a.out
 * GDB: gcc -Wall -g main.c hash_table.c && gdbtui ./a.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash_table.h"
#include "tools.h"

#define TABLE_SIZE 4096 * 16

int main()
{
	unsigned int i;
	srand( (unsigned) time(NULL) );

	void * p;
	char * p_key;
	char * p_data;
	char ** pp_key = random_string_generator(32, TABLE_SIZE);
	char ** pp_data = string_increament(TABLE_SIZE);
	char * pp_key_return[TABLE_SIZE];

	/* create */
	hash_table_t * hash_table_entry = hash_table_create(TABLE_SIZE);

	/* put, get and remove */
	for (i = 0; i < TABLE_SIZE; i++){
		p = hash_table_put(hash_table_entry, pp_key[i], pp_data[i]);
		// if (p != NULL)
		// 	printf("collision\n");
	}

	for (i = 0; i < TABLE_SIZE; i++){
		p = hash_table_get(hash_table_entry, pp_key[i]);
		// printf( "%s\n", (char *)p );
	}

	for (i = 0; i < TABLE_SIZE ; i++){
		hash_table_remove(hash_table_entry, pp_key[i]);
	}
	printf("\n");


	/* the collision of hash function */
	p = hash_table_put(hash_table_entry, "the_first_string", "string_7788");
	if (p != NULL)
		printf("collision\n");

	p = hash_table_put(hash_table_entry, "the_second_string", "string_5566");
	if (p != NULL)
		printf("collision\n");

	hash_table_remove(hash_table_entry, "the_first_string");
	hash_table_remove(hash_table_entry, "the_second_string");


	/* hash_table_list_key */
	for (i = 0; i < TABLE_SIZE; i++){
		hash_table_put(hash_table_entry, pp_key[i], pp_data[i]);
	}

	hash_table_list_keys(hash_table_entry, pp_key_return, TABLE_SIZE);
	for (i = 0; i < TABLE_SIZE; i++){
		// printf( "%s\n", (char *)pp_key_return[i] );
	}
	printf("\n");


	/* iterator */
	hash_elem_iter_t hash_elem_iter_entry = INIT_HASH_TABLE_ITERATOR( hash_table_entry );
	hash_elem_t * hash_elem_entry = hash_table_iterate( &hash_elem_iter_entry );

	while ( hash_elem_entry != NULL){
		// printf("key: %s, data: %s\n", hash_elem_entry->key, (char *) hash_elem_entry->data);
		hash_elem_entry = hash_table_iterate( &hash_elem_iter_entry );
	}
	printf("\n");

	/* iterator 2 */
	hash_elem_iter_t hash_elem_iter_entry_2 = INIT_HASH_TABLE_ITERATOR( hash_table_entry );
	p_key = hash_table_iterate_keys( &hash_elem_iter_entry_2 );

	while (p_key != NULL){
		// printf("key: %s\n", p_key);
		p_key = hash_table_iterate_keys( &hash_elem_iter_entry_2 );
	}
	printf("\n");


	/* iterator 3 */
	hash_elem_iter_t hash_elem_iter_entry_3 = INIT_HASH_TABLE_ITERATOR( hash_table_entry );
	p_data = hash_table_iterate_datas( &hash_elem_iter_entry_3 );

	while ( p_data != NULL){
		// printf("data: %s\n", p_data);
		p_data = hash_table_iterate_datas( &hash_elem_iter_entry_3 );
	}
	printf("\n");

	/* destory */
	hash_table_destroy(hash_table_entry);
	free_string(pp_key, TABLE_SIZE);
	free_string(pp_data, TABLE_SIZE);


	return 0;
}
