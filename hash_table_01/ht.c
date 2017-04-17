#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ht.h"


int main()
{
	struct hash_table * ht_entry =  hash_table_create(20);

	int * p_1 = 1024;
	int * p_2 = 256;

	insert( ht_entry, "2", p_1 );
	insert( ht_entry, "37", p_2 );

	display(ht_entry);

	struct hash_element * item = search( ht_entry, "37");
	if(item != NULL)
		printf("Element found: %d\n", item->data);
	else

	// delete( ht_entry, 37 );
	// item = search( ht_entry, 37);
	//
	// if(item != NULL) {
	// 	printf("Element found: %d\n", item->data);
	// } else {
	// 	printf("Element not found\n");
	// }
	// printf("Element not found\n");


	return 0;
}
