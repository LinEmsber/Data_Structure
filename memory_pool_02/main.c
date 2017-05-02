/* memory mem_pool_entry */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mem_pool.h"

#define TEST_COUNT 2

typedef struct test_struct {
	int  id;
	char str[12];
} test_struct;

void string_generator(char* str)
{
	str[11] = 0;
	for(int i = 0; i < 11; i++) {
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

	mem_pool_t * mem_pool_entry = mem_pool_create_pool( sizeof(test_struct), TEST_COUNT );

	srand( (unsigned) time(NULL) );

	for(i = 0; i < TEST_COUNT; i++) {

		test_array[i] = (test_struct*) mem_pool_alloc(mem_pool_entry);
		test_array[i]->id = i;

		string_generator(test_array[i]->str);
		print_test_struct(test_array[i]);
	}

	for(i = 0; i < TEST_COUNT; i++) {
		mem_pool_free(mem_pool_entry, test_array[i]);
	}

	mem_pool_print_info(mem_pool_entry);
	mem_pool_destroy_pool(mem_pool_entry);

#ifdef _DEBUG
	printf("create_pool_count: %d\n", create_pool_count);
#endif

	return 0;
}
