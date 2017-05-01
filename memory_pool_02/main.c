/* memory pool */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mem_pool.h"

#define TEST_COUNT 4096

typedef struct test_struct {
	int  id;
	char str[16];
} test_struct;

void string_generator(char* str)
{
	str[15] = 0;
	for(int i = 0; i < 15; i++) {
		str[i] = (rand() % 26) + 'a';
	}
}

void print_test_struct(test_struct* test)
{
	printf("%d [%p]: %s\n", test->id, test, test->str);
}

int main()
{
	int i;
	test_struct * test_array[TEST_COUNT];

	mem_pool_handle pool = mem_pool_create_pool( sizeof(test_struct), 4096 );

	srand( (unsigned) time(NULL) );

	for(i = 0; i < TEST_COUNT; i++) {

		test_array[i] = (test_struct*) mem_pool_alloc(pool);
		test_array[i]->id = i;

		string_generator(test_array[i]->str);
		print_test_struct(test_array[i]);
	}

	// for(i = 0; i < TEST_COUNT / 2; i++) {
	// 	mem_pool_free(pool, (uint8_t *)test_array[i]);
	// }
	//
	// // mem_pool_print_info(pool);
	// printf("\n");
	//
	// for(i = TEST_COUNT / 2; i < TEST_COUNT; i++) {
	// 	mem_pool_free(pool, (uint8_t *)test_array[i]);
	// }
	//
	// // mem_pool_print_info(pool);

	mem_pool_destroy_pool(pool);

	return 0;
}
