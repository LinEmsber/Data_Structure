/* The implentation of hash table.
 *
 * USAGE: gcc -Wall -g main.c hash_table.c && ./a.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "tools.h"

#define TABLE_SIZE 100


int main()
{
	unsigned int i;
	void * p;
	char ** pp = string_increament(20);

	hash_table_t * hash_table_entry = hash_table_create(TABLE_SIZE);

	for (i = 0; i < 20; i++){
		hash_table_put(hash_table_entry, pp[i], pp[i]);
		p = hash_table_get(hash_table_entry, pp[i]);
		printf( "%s\n", p );

	}



	hash_table_destroy(hash_table_entry);
	free_string(pp, 20);

	return 0;
}
