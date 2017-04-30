/* memory pool */

#include <stdio.h>
#include <stdlib.h>

#include "mem_pool.h"

#define TEST_COUNT 32

typedef struct test_struct {
	int  id;
	char str[16];
} test_struct;

void generate_str(char* str)
{
	str[15] = 0;
	for(int i = 0; i < 15; i++)
	{
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
	mem_pool_handle pool = mem_pool_create_pool( sizeof(test_struct), TEST_COUNT );

	for(i = 0; i < TEST_COUNT; i++) {

		test_array[i] = (test_struct*)mem_pool_alloc(pool);
		test_array[i]->id = i;

		generate_str(test_array[i]->str);

		print_test_struct(test_array[i]);
	}

	mem_pool_print_info(pool);

	mem_pool_destroy_pool(pool);

	return 0;
}
